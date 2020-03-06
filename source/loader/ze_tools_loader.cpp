/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "ze_loader.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    zet_driver_factory_t                zet_driver_factory;
    zet_device_factory_t                zet_device_factory;
    zet_command_list_factory_t          zet_command_list_factory;
    zet_module_factory_t                zet_module_factory;
    zet_kernel_factory_t                zet_kernel_factory;
    zet_metric_group_factory_t          zet_metric_group_factory;
    zet_metric_factory_t                zet_metric_factory;
    zet_metric_tracer_factory_t         zet_metric_tracer_factory;
    zet_metric_query_pool_factory_t     zet_metric_query_pool_factory;
    zet_metric_query_factory_t          zet_metric_query_factory;
    zet_tracer_factory_t                zet_tracer_factory;
    zet_sysman_factory_t                zet_sysman_factory;
    zet_sysman_pwr_factory_t            zet_sysman_pwr_factory;
    zet_sysman_freq_factory_t           zet_sysman_freq_factory;
    zet_sysman_engine_factory_t         zet_sysman_engine_factory;
    zet_sysman_standby_factory_t        zet_sysman_standby_factory;
    zet_sysman_firmware_factory_t       zet_sysman_firmware_factory;
    zet_sysman_mem_factory_t            zet_sysman_mem_factory;
    zet_sysman_fabric_port_factory_t    zet_sysman_fabric_port_factory;
    zet_sysman_temp_factory_t           zet_sysman_temp_factory;
    zet_sysman_psu_factory_t            zet_sysman_psu_factory;
    zet_sysman_fan_factory_t            zet_sysman_fan_factory;
    zet_sysman_led_factory_t            zet_sysman_led_factory;
    zet_sysman_ras_factory_t            zet_sysman_ras_factory;
    zet_sysman_diag_factory_t           zet_sysman_diag_factory;
    zet_sysman_event_factory_t          zet_sysman_event_factory;
    zet_debug_session_factory_t         zet_debug_session_factory;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetInit
    ze_result_t __zecall
    zetInit(
        ze_init_flag_t flags                            ///< [in] initialization flags
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        for( auto& drv : context.drivers )
        {
            if( ZE_RESULT_SUCCESS == result )
            {
                result = drv.dditable.zet.Global.pfnInit( flags );
            }
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnAttach = dditable->zet.Debug.pfnAttach;
        if( nullptr == pfnAttach )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnAttach( hDevice, config, hDebug );

        try
        {
            // convert driver handle to loader handle
            *hDebug = reinterpret_cast<zet_debug_session_handle_t>(
                zet_debug_session_factory.getInstance( *hDebug, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugDetach
    ze_result_t __zecall
    zetDebugDetach(
        zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnDetach = dditable->zet.Debug.pfnDetach;
        if( nullptr == pfnDetach )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnDetach( hDebug );

        // release loader handle
        zet_debug_session_factory.release( hDebug );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugGetNumThreads
    ze_result_t __zecall
    zetDebugGetNumThreads(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t* pNumThreads                           ///< [out] the maximal number of threads
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnGetNumThreads = dditable->zet.Debug.pfnGetNumThreads;
        if( nullptr == pfnGetNumThreads )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnGetNumThreads( hDebug, pNumThreads );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnReadEvent = dditable->zet.Debug.pfnReadEvent;
        if( nullptr == pfnReadEvent )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnReadEvent( hDebug, timeout, size, buffer );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugInterrupt
    ze_result_t __zecall
    zetDebugInterrupt(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid                               ///< [in] the thread to inerrupt or ::ZET_DEBUG_THREAD_ALL
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnInterrupt = dditable->zet.Debug.pfnInterrupt;
        if( nullptr == pfnInterrupt )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnInterrupt( hDebug, threadid );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugResume
    ze_result_t __zecall
    zetDebugResume(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t threadid                               ///< [in] the thread to resume or ::ZET_DEBUG_THREAD_ALL
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnResume = dditable->zet.Debug.pfnResume;
        if( nullptr == pfnResume )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnResume( hDebug, threadid );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnReadMemory = dditable->zet.Debug.pfnReadMemory;
        if( nullptr == pfnReadMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnReadMemory( hDebug, threadid, memSpace, address, size, buffer );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnWriteMemory = dditable->zet.Debug.pfnWriteMemory;
        if( nullptr == pfnWriteMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnWriteMemory( hDebug, threadid, memSpace, address, size, buffer );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnReadState = dditable->zet.Debug.pfnReadState;
        if( nullptr == pfnReadState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnReadState( hDebug, threadid, offset, size, buffer );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->dditable;
        auto pfnWriteState = dditable->zet.Debug.pfnWriteState;
        if( nullptr == pfnWriteState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDebug = reinterpret_cast<zet_debug_session_object_t*>( hDebug )->handle;

        // forward to device-driver
        result = pfnWriteState( hDebug, threadid, offset, size, buffer );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnGet = dditable->zet.MetricGroup.pfnGet;
        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGet( hDevice, pCount, phMetricGroups );

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
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnGetProperties( hMetricGroup, pProperties );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->dditable;
        auto pfnCalculateMetricValues = dditable->zet.MetricGroup.pfnCalculateMetricValues;
        if( nullptr == pfnCalculateMetricValues )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnCalculateMetricValues( hMetricGroup, rawDataSize, pRawData, pMetricValueCount, pMetricValues );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->dditable;
        auto pfnGet = dditable->zet.Metric.pfnGet;
        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnGet( hMetricGroup, pCount, phMetrics );

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
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMetric = reinterpret_cast<zet_metric_object_t*>( hMetric )->handle;

        // forward to device-driver
        result = pfnGetProperties( hMetric, pProperties );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnActivateMetricGroups = dditable->zet.Device.pfnActivateMetricGroups;
        if( nullptr == pfnActivateMetricGroups )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phMetricGroups ) && ( i < count ); ++i )
            phMetricGroups[ i ] = reinterpret_cast<zet_metric_group_object_t*>( phMetricGroups[ i ] )->handle;

        // forward to device-driver
        result = pfnActivateMetricGroups( hDevice, count, phMetricGroups );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnOpen = dditable->zet.MetricTracer.pfnOpen;
        if( nullptr == pfnOpen )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // convert loader handle to driver handle
        hNotificationEvent = ( hNotificationEvent ) ? reinterpret_cast<ze_event_object_t*>( hNotificationEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnOpen( hDevice, hMetricGroup, desc, hNotificationEvent, phMetricTracer );

        try
        {
            // convert driver handle to loader handle
            *phMetricTracer = reinterpret_cast<zet_metric_tracer_handle_t>(
                zet_metric_tracer_factory.getInstance( *phMetricTracer, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMetricTracerMarker = dditable->zet.CommandList.pfnAppendMetricTracerMarker;
        if( nullptr == pfnAppendMetricTracerMarker )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hMetricTracer = reinterpret_cast<zet_metric_tracer_object_t*>( hMetricTracer )->handle;

        // forward to device-driver
        result = pfnAppendMetricTracerMarker( hCommandList, hMetricTracer, value );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerClose
    ze_result_t __zecall
    zetMetricTracerClose(
        zet_metric_tracer_handle_t hMetricTracer        ///< [in][release] handle of the metric tracer
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_tracer_object_t*>( hMetricTracer )->dditable;
        auto pfnClose = dditable->zet.MetricTracer.pfnClose;
        if( nullptr == pfnClose )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMetricTracer = reinterpret_cast<zet_metric_tracer_object_t*>( hMetricTracer )->handle;

        // forward to device-driver
        result = pfnClose( hMetricTracer );

        // release loader handle
        zet_metric_tracer_factory.release( hMetricTracer );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_tracer_object_t*>( hMetricTracer )->dditable;
        auto pfnReadData = dditable->zet.MetricTracer.pfnReadData;
        if( nullptr == pfnReadData )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMetricTracer = reinterpret_cast<zet_metric_tracer_object_t*>( hMetricTracer )->handle;

        // forward to device-driver
        result = pfnReadData( hMetricTracer, maxReportCount, pRawDataSize, pRawData );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnCreate = dditable->zet.MetricQueryPool.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // convert loader handle to driver handle
        hMetricGroup = reinterpret_cast<zet_metric_group_object_t*>( hMetricGroup )->handle;

        // forward to device-driver
        result = pfnCreate( hDevice, hMetricGroup, desc, phMetricQueryPool );

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
    ze_result_t __zecall
    zetMetricQueryPoolDestroy(
        zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_query_pool_object_t*>( hMetricQueryPool )->dditable;
        auto pfnDestroy = dditable->zet.MetricQueryPool.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMetricQueryPool = reinterpret_cast<zet_metric_query_pool_object_t*>( hMetricQueryPool )->handle;

        // forward to device-driver
        result = pfnDestroy( hMetricQueryPool );

        // release loader handle
        zet_metric_query_pool_factory.release( hMetricQueryPool );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_query_pool_object_t*>( hMetricQueryPool )->dditable;
        auto pfnCreate = dditable->zet.MetricQuery.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMetricQueryPool = reinterpret_cast<zet_metric_query_pool_object_t*>( hMetricQueryPool )->handle;

        // forward to device-driver
        result = pfnCreate( hMetricQueryPool, index, phMetricQuery );

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
    ze_result_t __zecall
    zetMetricQueryDestroy(
        zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_query_object_t*>( hMetricQuery )->dditable;
        auto pfnDestroy = dditable->zet.MetricQuery.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<zet_metric_query_object_t*>( hMetricQuery )->handle;

        // forward to device-driver
        result = pfnDestroy( hMetricQuery );

        // release loader handle
        zet_metric_query_factory.release( hMetricQuery );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryReset
    ze_result_t __zecall
    zetMetricQueryReset(
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_query_object_t*>( hMetricQuery )->dditable;
        auto pfnReset = dditable->zet.MetricQuery.pfnReset;
        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<zet_metric_query_object_t*>( hMetricQuery )->handle;

        // forward to device-driver
        result = pfnReset( hMetricQuery );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricQueryBegin
    ze_result_t __zecall
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
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

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
    ze_result_t __zecall
    zetCommandListAppendMetricQueryEnd(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        ze_event_handle_t hCompletionEvent              ///< [in][optional] handle of the completion event to signal
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMetricQueryEnd = dditable->zet.CommandList.pfnAppendMetricQueryEnd;
        if( nullptr == pfnAppendMetricQueryEnd )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->handle;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<zet_metric_query_object_t*>( hMetricQuery )->handle;

        // convert loader handle to driver handle
        hCompletionEvent = ( hCompletionEvent ) ? reinterpret_cast<ze_event_object_t*>( hCompletionEvent )->handle : nullptr;

        // forward to device-driver
        result = pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hCompletionEvent );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricMemoryBarrier
    ze_result_t __zecall
    zetCommandListAppendMetricMemoryBarrier(
        zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->dditable;
        auto pfnAppendMetricMemoryBarrier = dditable->zet.CommandList.pfnAppendMetricMemoryBarrier;
        if( nullptr == pfnAppendMetricMemoryBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hCommandList = reinterpret_cast<zet_command_list_object_t*>( hCommandList )->handle;

        // forward to device-driver
        result = pfnAppendMetricMemoryBarrier( hCommandList );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_metric_query_object_t*>( hMetricQuery )->dditable;
        auto pfnGetData = dditable->zet.MetricQuery.pfnGetData;
        if( nullptr == pfnGetData )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMetricQuery = reinterpret_cast<zet_metric_query_object_t*>( hMetricQuery )->handle;

        // forward to device-driver
        result = pfnGetData( hMetricQuery, pRawDataSize, pRawData );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_module_object_t*>( hModule )->dditable;
        auto pfnGetDebugInfo = dditable->zet.Module.pfnGetDebugInfo;
        if( nullptr == pfnGetDebugInfo )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hModule = reinterpret_cast<zet_module_object_t*>( hModule )->handle;

        // forward to device-driver
        result = pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetKernelGetProfileInfo
    ze_result_t __zecall
    zetKernelGetProfileInfo(
        zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
        zet_profile_info_t* pInfo                       ///< [out] pointer to profile info
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_kernel_object_t*>( hKernel )->dditable;
        auto pfnGetProfileInfo = dditable->zet.Kernel.pfnGetProfileInfo;
        if( nullptr == pfnGetProfileInfo )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hKernel = reinterpret_cast<zet_kernel_object_t*>( hKernel )->handle;

        // forward to device-driver
        result = pfnGetProfileInfo( hKernel, pInfo );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_device_object_t*>( hDevice )->dditable;
        auto pfnGet = dditable->zet.Sysman.pfnGet;
        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zet_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGet( hDevice, version, phSysman );

        try
        {
            // convert driver handle to loader handle
            *phSysman = reinterpret_cast<zet_sysman_handle_t>(
                zet_sysman_factory.getInstance( *phSysman, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDeviceGetProperties
    ze_result_t __zecall
    zetSysmanDeviceGetProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_sysman_properties_t* pProperties            ///< [in] Structure that will contain information about the device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnDeviceGetProperties = dditable->zet.Sysman.pfnDeviceGetProperties;
        if( nullptr == pfnDeviceGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDeviceGetProperties( hSysman, pProperties );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerGetSupportedModes = dditable->zet.Sysman.pfnSchedulerGetSupportedModes;
        if( nullptr == pfnSchedulerGetSupportedModes )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerGetSupportedModes( hSysman, pCount, pModes );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanSchedulerGetCurrentMode
    ze_result_t __zecall
    zetSysmanSchedulerGetCurrentMode(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_sched_mode_t* pMode                         ///< [in] Will contain the current scheduler mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerGetCurrentMode = dditable->zet.Sysman.pfnSchedulerGetCurrentMode;
        if( nullptr == pfnSchedulerGetCurrentMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerGetCurrentMode( hSysman, pMode );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerGetTimeoutModeProperties = dditable->zet.Sysman.pfnSchedulerGetTimeoutModeProperties;
        if( nullptr == pfnSchedulerGetTimeoutModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerGetTimeoutModeProperties( hSysman, getDefaults, pConfig );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerGetTimesliceModeProperties = dditable->zet.Sysman.pfnSchedulerGetTimesliceModeProperties;
        if( nullptr == pfnSchedulerGetTimesliceModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerGetTimesliceModeProperties( hSysman, getDefaults, pConfig );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerSetTimeoutMode = dditable->zet.Sysman.pfnSchedulerSetTimeoutMode;
        if( nullptr == pfnSchedulerSetTimeoutMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerSetTimeoutMode( hSysman, pProperties, pNeedReboot );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerSetTimesliceMode = dditable->zet.Sysman.pfnSchedulerSetTimesliceMode;
        if( nullptr == pfnSchedulerSetTimesliceMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerSetTimesliceMode( hSysman, pProperties, pNeedReboot );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerSetExclusiveMode = dditable->zet.Sysman.pfnSchedulerSetExclusiveMode;
        if( nullptr == pfnSchedulerSetExclusiveMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerSetExclusiveMode( hSysman, pNeedReboot );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnSchedulerSetComputeUnitDebugMode = dditable->zet.Sysman.pfnSchedulerSetComputeUnitDebugMode;
        if( nullptr == pfnSchedulerSetComputeUnitDebugMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnSchedulerSetComputeUnitDebugMode( hSysman, pNeedReboot );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPerformanceProfileGetSupported = dditable->zet.Sysman.pfnPerformanceProfileGetSupported;
        if( nullptr == pfnPerformanceProfileGetSupported )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPerformanceProfileGetSupported( hSysman, pCount, pProfiles );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPerformanceProfileGet
    ze_result_t __zecall
    zetSysmanPerformanceProfileGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_perf_profile_t* pProfile                    ///< [in] The performance profile currently loaded.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPerformanceProfileGet = dditable->zet.Sysman.pfnPerformanceProfileGet;
        if( nullptr == pfnPerformanceProfileGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPerformanceProfileGet( hSysman, pProfile );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPerformanceProfileSet
    ze_result_t __zecall
    zetSysmanPerformanceProfileSet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_perf_profile_t profile                      ///< [in] The performance profile to load.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPerformanceProfileSet = dditable->zet.Sysman.pfnPerformanceProfileSet;
        if( nullptr == pfnPerformanceProfileSet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPerformanceProfileSet( hSysman, profile );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnProcessesGetState = dditable->zet.Sysman.pfnProcessesGetState;
        if( nullptr == pfnProcessesGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnProcessesGetState( hSysman, pCount, pProcesses );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDeviceReset
    ze_result_t __zecall
    zetSysmanDeviceReset(
        zet_sysman_handle_t hSysman                     ///< [in] Sysman handle for the device
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnDeviceReset = dditable->zet.Sysman.pfnDeviceReset;
        if( nullptr == pfnDeviceReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDeviceReset( hSysman );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDeviceGetRepairStatus
    ze_result_t __zecall
    zetSysmanDeviceGetRepairStatus(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
        zet_repair_status_t* pRepairStatus              ///< [in] Will indicate if the device was repaired
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnDeviceGetRepairStatus = dditable->zet.Sysman.pfnDeviceGetRepairStatus;
        if( nullptr == pfnDeviceGetRepairStatus )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDeviceGetRepairStatus( hSysman, pRepairStatus );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetProperties
    ze_result_t __zecall
    zetSysmanPciGetProperties(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_pci_properties_t* pProperties               ///< [in] Will contain the PCI properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPciGetProperties = dditable->zet.Sysman.pfnPciGetProperties;
        if( nullptr == pfnPciGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPciGetProperties( hSysman, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetState
    ze_result_t __zecall
    zetSysmanPciGetState(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_pci_state_t* pState                         ///< [in] Will contain the PCI properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPciGetState = dditable->zet.Sysman.pfnPciGetState;
        if( nullptr == pfnPciGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPciGetState( hSysman, pState );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPciGetBars = dditable->zet.Sysman.pfnPciGetBars;
        if( nullptr == pfnPciGetBars )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPciGetBars( hSysman, pCount, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPciGetStats
    ze_result_t __zecall
    zetSysmanPciGetStats(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle of the device.
        zet_pci_stats_t* pStats                         ///< [in] Will contain a snapshot of the latest stats.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPciGetStats = dditable->zet.Sysman.pfnPciGetStats;
        if( nullptr == pfnPciGetStats )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPciGetStats( hSysman, pStats );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPowerGet = dditable->zet.Sysman.pfnPowerGet;
        if( nullptr == pfnPowerGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPowerGet( hSysman, pCount, phPower );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPower ) && ( i < *pCount ); ++i )
                phPower[ i ] = reinterpret_cast<zet_sysman_pwr_handle_t>(
                    zet_sysman_pwr_factory.getInstance( phPower[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerGetProperties
    ze_result_t __zecall
    zetSysmanPowerGetProperties(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        zet_power_properties_t* pProperties             ///< [in] Structure that will contain property data.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnGetProperties = dditable->zet.SysmanPower.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zet_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetProperties( hPower, pProperties );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnGetEnergyCounter = dditable->zet.SysmanPower.pfnGetEnergyCounter;
        if( nullptr == pfnGetEnergyCounter )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zet_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetEnergyCounter( hPower, pEnergy );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnGetLimits = dditable->zet.SysmanPower.pfnGetLimits;
        if( nullptr == pfnGetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zet_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetLimits( hPower, pSustained, pBurst, pPeak );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnSetLimits = dditable->zet.SysmanPower.pfnSetLimits;
        if( nullptr == pfnSetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zet_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnSetLimits( hPower, pSustained, pBurst, pPeak );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnGetEnergyThreshold = dditable->zet.SysmanPower.pfnGetEnergyThreshold;
        if( nullptr == pfnGetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zet_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnGetEnergyThreshold( hPower, pThreshold );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPowerSetEnergyThreshold
    ze_result_t __zecall
    zetSysmanPowerSetEnergyThreshold(
        zet_sysman_pwr_handle_t hPower,                 ///< [in] Handle for the component.
        double threshold                                ///< [in] The energy threshold to be set in joules.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_pwr_object_t*>( hPower )->dditable;
        auto pfnSetEnergyThreshold = dditable->zet.SysmanPower.pfnSetEnergyThreshold;
        if( nullptr == pfnSetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zet_sysman_pwr_object_t*>( hPower )->handle;

        // forward to device-driver
        result = pfnSetEnergyThreshold( hPower, threshold );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFrequencyGet = dditable->zet.Sysman.pfnFrequencyGet;
        if( nullptr == pfnFrequencyGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFrequencyGet( hSysman, pCount, phFrequency );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFrequency ) && ( i < *pCount ); ++i )
                phFrequency[ i ] = reinterpret_cast<zet_sysman_freq_handle_t>(
                    zet_sysman_freq_factory.getInstance( phFrequency[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetProperties
    ze_result_t __zecall
    zetSysmanFrequencyGetProperties(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_freq_properties_t* pProperties              ///< [in] The frequency properties for the specified domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetProperties = dditable->zet.SysmanFrequency.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetProperties( hFrequency, pProperties );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetAvailableClocks = dditable->zet.SysmanFrequency.pfnGetAvailableClocks;
        if( nullptr == pfnGetAvailableClocks )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetAvailableClocks( hFrequency, pCount, phFrequency );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetRange = dditable->zet.SysmanFrequency.pfnGetRange;
        if( nullptr == pfnGetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetRange( hFrequency, pLimits );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnSetRange = dditable->zet.SysmanFrequency.pfnSetRange;
        if( nullptr == pfnSetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnSetRange( hFrequency, pLimits );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyGetState
    ze_result_t __zecall
    zetSysmanFrequencyGetState(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_freq_state_t* pState                        ///< [in] Frequency state for the specified domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetState = dditable->zet.SysmanFrequency.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetState( hFrequency, pState );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetThrottleTime = dditable->zet.SysmanFrequency.pfnGetThrottleTime;
        if( nullptr == pfnGetThrottleTime )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnGetThrottleTime( hFrequency, pThrottleTime );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcGetCapabilities
    ze_result_t __zecall
    zetSysmanFrequencyOcGetCapabilities(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_oc_capabilities_t* pOcCapabilities          ///< [in] Pointer to the capabilities structure ::zet_oc_capabilities_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetCapabilities = dditable->zet.SysmanFrequency.pfnOcGetCapabilities;
        if( nullptr == pfnOcGetCapabilities )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcGetCapabilities( hFrequency, pOcCapabilities );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcGetConfig
    ze_result_t __zecall
    zetSysmanFrequencyOcGetConfig(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        zet_oc_config_t* pOcConfiguration               ///< [in] Pointer to the configuration structure ::zet_oc_config_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetConfig = dditable->zet.SysmanFrequency.pfnOcGetConfig;
        if( nullptr == pfnOcGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcGetConfig( hFrequency, pOcConfiguration );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcSetConfig = dditable->zet.SysmanFrequency.pfnOcSetConfig;
        if( nullptr == pfnOcSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcSetConfig( hFrequency, pOcConfiguration, pDeviceRestart );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetIccMax = dditable->zet.SysmanFrequency.pfnOcGetIccMax;
        if( nullptr == pfnOcGetIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcGetIccMax( hFrequency, pOcIccMax );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcSetIccMax
    ze_result_t __zecall
    zetSysmanFrequencyOcSetIccMax(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcSetIccMax = dditable->zet.SysmanFrequency.pfnOcSetIccMax;
        if( nullptr == pfnOcSetIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcSetIccMax( hFrequency, ocIccMax );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetTjMax = dditable->zet.SysmanFrequency.pfnOcGetTjMax;
        if( nullptr == pfnOcGetTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcGetTjMax( hFrequency, pOcTjMax );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFrequencyOcSetTjMax
    ze_result_t __zecall
    zetSysmanFrequencyOcSetTjMax(
        zet_sysman_freq_handle_t hFrequency,            ///< [in] Handle for the component.
        double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcSetTjMax = dditable->zet.SysmanFrequency.pfnOcSetTjMax;
        if( nullptr == pfnOcSetTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zet_sysman_freq_object_t*>( hFrequency )->handle;

        // forward to device-driver
        result = pfnOcSetTjMax( hFrequency, ocTjMax );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnEngineGet = dditable->zet.Sysman.pfnEngineGet;
        if( nullptr == pfnEngineGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnEngineGet( hSysman, pCount, phEngine );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phEngine ) && ( i < *pCount ); ++i )
                phEngine[ i ] = reinterpret_cast<zet_sysman_engine_handle_t>(
                    zet_sysman_engine_factory.getInstance( phEngine[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEngineGetProperties
    ze_result_t __zecall
    zetSysmanEngineGetProperties(
        zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
        zet_engine_properties_t* pProperties            ///< [in] The properties for the specified engine group.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_engine_object_t*>( hEngine )->dditable;
        auto pfnGetProperties = dditable->zet.SysmanEngine.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEngine = reinterpret_cast<zet_sysman_engine_object_t*>( hEngine )->handle;

        // forward to device-driver
        result = pfnGetProperties( hEngine, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEngineGetActivity
    ze_result_t __zecall
    zetSysmanEngineGetActivity(
        zet_sysman_engine_handle_t hEngine,             ///< [in] Handle for the component.
        zet_engine_stats_t* pStats                      ///< [in] Will contain a snapshot of the engine group activity counters.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_engine_object_t*>( hEngine )->dditable;
        auto pfnGetActivity = dditable->zet.SysmanEngine.pfnGetActivity;
        if( nullptr == pfnGetActivity )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEngine = reinterpret_cast<zet_sysman_engine_object_t*>( hEngine )->handle;

        // forward to device-driver
        result = pfnGetActivity( hEngine, pStats );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnStandbyGet = dditable->zet.Sysman.pfnStandbyGet;
        if( nullptr == pfnStandbyGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnStandbyGet( hSysman, pCount, phStandby );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phStandby ) && ( i < *pCount ); ++i )
                phStandby[ i ] = reinterpret_cast<zet_sysman_standby_handle_t>(
                    zet_sysman_standby_factory.getInstance( phStandby[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanStandbyGetProperties
    ze_result_t __zecall
    zetSysmanStandbyGetProperties(
        zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zet_standby_properties_t* pProperties           ///< [in] Will contain the standby hardware properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_standby_object_t*>( hStandby )->dditable;
        auto pfnGetProperties = dditable->zet.SysmanStandby.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hStandby = reinterpret_cast<zet_sysman_standby_object_t*>( hStandby )->handle;

        // forward to device-driver
        result = pfnGetProperties( hStandby, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanStandbyGetMode
    ze_result_t __zecall
    zetSysmanStandbyGetMode(
        zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zet_standby_promo_mode_t* pMode                 ///< [in] Will contain the current standby mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_standby_object_t*>( hStandby )->dditable;
        auto pfnGetMode = dditable->zet.SysmanStandby.pfnGetMode;
        if( nullptr == pfnGetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hStandby = reinterpret_cast<zet_sysman_standby_object_t*>( hStandby )->handle;

        // forward to device-driver
        result = pfnGetMode( hStandby, pMode );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanStandbySetMode
    ze_result_t __zecall
    zetSysmanStandbySetMode(
        zet_sysman_standby_handle_t hStandby,           ///< [in] Handle for the component.
        zet_standby_promo_mode_t mode                   ///< [in] New standby mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_standby_object_t*>( hStandby )->dditable;
        auto pfnSetMode = dditable->zet.SysmanStandby.pfnSetMode;
        if( nullptr == pfnSetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hStandby = reinterpret_cast<zet_sysman_standby_object_t*>( hStandby )->handle;

        // forward to device-driver
        result = pfnSetMode( hStandby, mode );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFirmwareGet = dditable->zet.Sysman.pfnFirmwareGet;
        if( nullptr == pfnFirmwareGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFirmwareGet( hSysman, pCount, phFirmware );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFirmware ) && ( i < *pCount ); ++i )
                phFirmware[ i ] = reinterpret_cast<zet_sysman_firmware_handle_t>(
                    zet_sysman_firmware_factory.getInstance( phFirmware[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFirmwareGetProperties
    ze_result_t __zecall
    zetSysmanFirmwareGetProperties(
        zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        zet_firmware_properties_t* pProperties          ///< [in] Pointer to an array that will hold the properties of the firmware
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_firmware_object_t*>( hFirmware )->dditable;
        auto pfnGetProperties = dditable->zet.SysmanFirmware.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<zet_sysman_firmware_object_t*>( hFirmware )->handle;

        // forward to device-driver
        result = pfnGetProperties( hFirmware, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFirmwareGetChecksum
    ze_result_t __zecall
    zetSysmanFirmwareGetChecksum(
        zet_sysman_firmware_handle_t hFirmware,         ///< [in] Handle for the component.
        uint32_t* pChecksum                             ///< [in] Calculated checksum of the installed firmware.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_firmware_object_t*>( hFirmware )->dditable;
        auto pfnGetChecksum = dditable->zet.SysmanFirmware.pfnGetChecksum;
        if( nullptr == pfnGetChecksum )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<zet_sysman_firmware_object_t*>( hFirmware )->handle;

        // forward to device-driver
        result = pfnGetChecksum( hFirmware, pChecksum );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_firmware_object_t*>( hFirmware )->dditable;
        auto pfnFlash = dditable->zet.SysmanFirmware.pfnFlash;
        if( nullptr == pfnFlash )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<zet_sysman_firmware_object_t*>( hFirmware )->handle;

        // forward to device-driver
        result = pfnFlash( hFirmware, pImage, size );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnMemoryGet = dditable->zet.Sysman.pfnMemoryGet;
        if( nullptr == pfnMemoryGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnMemoryGet( hSysman, pCount, phMemory );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phMemory ) && ( i < *pCount ); ++i )
                phMemory[ i ] = reinterpret_cast<zet_sysman_mem_handle_t>(
                    zet_sysman_mem_factory.getInstance( phMemory[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanMemoryGetProperties
    ze_result_t __zecall
    zetSysmanMemoryGetProperties(
        zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zet_mem_properties_t* pProperties               ///< [in] Will contain memory properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_mem_object_t*>( hMemory )->dditable;
        auto pfnGetProperties = dditable->zet.SysmanMemory.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMemory = reinterpret_cast<zet_sysman_mem_object_t*>( hMemory )->handle;

        // forward to device-driver
        result = pfnGetProperties( hMemory, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanMemoryGetState
    ze_result_t __zecall
    zetSysmanMemoryGetState(
        zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zet_mem_state_t* pState                         ///< [in] Will contain the current health and allocated memory.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_mem_object_t*>( hMemory )->dditable;
        auto pfnGetState = dditable->zet.SysmanMemory.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMemory = reinterpret_cast<zet_sysman_mem_object_t*>( hMemory )->handle;

        // forward to device-driver
        result = pfnGetState( hMemory, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanMemoryGetBandwidth
    ze_result_t __zecall
    zetSysmanMemoryGetBandwidth(
        zet_sysman_mem_handle_t hMemory,                ///< [in] Handle for the component.
        zet_mem_bandwidth_t* pBandwidth                 ///< [in] Will contain a snapshot of the bandwidth counters.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_mem_object_t*>( hMemory )->dditable;
        auto pfnGetBandwidth = dditable->zet.SysmanMemory.pfnGetBandwidth;
        if( nullptr == pfnGetBandwidth )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hMemory = reinterpret_cast<zet_sysman_mem_object_t*>( hMemory )->handle;

        // forward to device-driver
        result = pfnGetBandwidth( hMemory, pBandwidth );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFabricPortGet = dditable->zet.Sysman.pfnFabricPortGet;
        if( nullptr == pfnFabricPortGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFabricPortGet( hSysman, pCount, phPort );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPort ) && ( i < *pCount ); ++i )
                phPort[ i ] = reinterpret_cast<zet_sysman_fabric_port_handle_t>(
                    zet_sysman_fabric_port_factory.getInstance( phPort[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortGetProperties
    ze_result_t __zecall
    zetSysmanFabricPortGetProperties(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zet_fabric_port_properties_t* pProperties       ///< [in] Will contain properties of the Fabric Port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetProperties = dditable->zet.SysmanFabricPort.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zet_sysman_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetProperties( hPort, pProperties );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetLinkType = dditable->zet.SysmanFabricPort.pfnGetLinkType;
        if( nullptr == pfnGetLinkType )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zet_sysman_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetLinkType( hPort, verbose, pLinkType );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortGetConfig
    ze_result_t __zecall
    zetSysmanFabricPortGetConfig(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zet_fabric_port_config_t* pConfig               ///< [in] Will contain configuration of the Fabric Port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetConfig = dditable->zet.SysmanFabricPort.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zet_sysman_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetConfig( hPort, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortSetConfig
    ze_result_t __zecall
    zetSysmanFabricPortSetConfig(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        const zet_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_fabric_port_object_t*>( hPort )->dditable;
        auto pfnSetConfig = dditable->zet.SysmanFabricPort.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zet_sysman_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnSetConfig( hPort, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFabricPortGetState
    ze_result_t __zecall
    zetSysmanFabricPortGetState(
        zet_sysman_fabric_port_handle_t hPort,          ///< [in] Handle for the component.
        zet_fabric_port_state_t* pState                 ///< [in] Will contain the current state of the Fabric Port
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetState = dditable->zet.SysmanFabricPort.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zet_sysman_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetState( hPort, pState );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetThroughput = dditable->zet.SysmanFabricPort.pfnGetThroughput;
        if( nullptr == pfnGetThroughput )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zet_sysman_fabric_port_object_t*>( hPort )->handle;

        // forward to device-driver
        result = pfnGetThroughput( hPort, pThroughput );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnTemperatureGet = dditable->zet.Sysman.pfnTemperatureGet;
        if( nullptr == pfnTemperatureGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnTemperatureGet( hSysman, pCount, phTemperature );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phTemperature ) && ( i < *pCount ); ++i )
                phTemperature[ i ] = reinterpret_cast<zet_sysman_temp_handle_t>(
                    zet_sysman_temp_factory.getInstance( phTemperature[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureGetProperties
    ze_result_t __zecall
    zetSysmanTemperatureGetProperties(
        zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        zet_temp_properties_t* pProperties              ///< [in] Will contain the temperature sensor properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_temp_object_t*>( hTemperature )->dditable;
        auto pfnGetProperties = dditable->zet.SysmanTemperature.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zet_sysman_temp_object_t*>( hTemperature )->handle;

        // forward to device-driver
        result = pfnGetProperties( hTemperature, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureGetConfig
    ze_result_t __zecall
    zetSysmanTemperatureGetConfig(
        zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        zet_temp_config_t* pConfig                      ///< [in] Returns current configuration.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_temp_object_t*>( hTemperature )->dditable;
        auto pfnGetConfig = dditable->zet.SysmanTemperature.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zet_sysman_temp_object_t*>( hTemperature )->handle;

        // forward to device-driver
        result = pfnGetConfig( hTemperature, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanTemperatureSetConfig
    ze_result_t __zecall
    zetSysmanTemperatureSetConfig(
        zet_sysman_temp_handle_t hTemperature,          ///< [in] Handle for the component.
        const zet_temp_config_t* pConfig                ///< [in] New configuration.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_temp_object_t*>( hTemperature )->dditable;
        auto pfnSetConfig = dditable->zet.SysmanTemperature.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zet_sysman_temp_object_t*>( hTemperature )->handle;

        // forward to device-driver
        result = pfnSetConfig( hTemperature, pConfig );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_temp_object_t*>( hTemperature )->dditable;
        auto pfnGetState = dditable->zet.SysmanTemperature.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zet_sysman_temp_object_t*>( hTemperature )->handle;

        // forward to device-driver
        result = pfnGetState( hTemperature, pTemperature );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnPsuGet = dditable->zet.Sysman.pfnPsuGet;
        if( nullptr == pfnPsuGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnPsuGet( hSysman, pCount, phPsu );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPsu ) && ( i < *pCount ); ++i )
                phPsu[ i ] = reinterpret_cast<zet_sysman_psu_handle_t>(
                    zet_sysman_psu_factory.getInstance( phPsu[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPsuGetProperties
    ze_result_t __zecall
    zetSysmanPsuGetProperties(
        zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        zet_psu_properties_t* pProperties               ///< [in] Will contain the properties of the power supply.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_psu_object_t*>( hPsu )->dditable;
        auto pfnGetProperties = dditable->zet.SysmanPsu.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPsu = reinterpret_cast<zet_sysman_psu_object_t*>( hPsu )->handle;

        // forward to device-driver
        result = pfnGetProperties( hPsu, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanPsuGetState
    ze_result_t __zecall
    zetSysmanPsuGetState(
        zet_sysman_psu_handle_t hPsu,                   ///< [in] Handle for the component.
        zet_psu_state_t* pState                         ///< [in] Will contain the current state of the power supply.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_psu_object_t*>( hPsu )->dditable;
        auto pfnGetState = dditable->zet.SysmanPsu.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hPsu = reinterpret_cast<zet_sysman_psu_object_t*>( hPsu )->handle;

        // forward to device-driver
        result = pfnGetState( hPsu, pState );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnFanGet = dditable->zet.Sysman.pfnFanGet;
        if( nullptr == pfnFanGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnFanGet( hSysman, pCount, phFan );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFan ) && ( i < *pCount ); ++i )
                phFan[ i ] = reinterpret_cast<zet_sysman_fan_handle_t>(
                    zet_sysman_fan_factory.getInstance( phFan[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanGetProperties
    ze_result_t __zecall
    zetSysmanFanGetProperties(
        zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zet_fan_properties_t* pProperties               ///< [in] Will contain the properties of the fan.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_fan_object_t*>( hFan )->dditable;
        auto pfnGetProperties = dditable->zet.SysmanFan.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zet_sysman_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnGetProperties( hFan, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanGetConfig
    ze_result_t __zecall
    zetSysmanFanGetConfig(
        zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        zet_fan_config_t* pConfig                       ///< [in] Will contain the current configuration of the fan.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_fan_object_t*>( hFan )->dditable;
        auto pfnGetConfig = dditable->zet.SysmanFan.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zet_sysman_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnGetConfig( hFan, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanFanSetConfig
    ze_result_t __zecall
    zetSysmanFanSetConfig(
        zet_sysman_fan_handle_t hFan,                   ///< [in] Handle for the component.
        const zet_fan_config_t* pConfig                 ///< [in] New fan configuration.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_fan_object_t*>( hFan )->dditable;
        auto pfnSetConfig = dditable->zet.SysmanFan.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zet_sysman_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnSetConfig( hFan, pConfig );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_fan_object_t*>( hFan )->dditable;
        auto pfnGetState = dditable->zet.SysmanFan.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zet_sysman_fan_object_t*>( hFan )->handle;

        // forward to device-driver
        result = pfnGetState( hFan, units, pSpeed );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnLedGet = dditable->zet.Sysman.pfnLedGet;
        if( nullptr == pfnLedGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnLedGet( hSysman, pCount, phLed );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phLed ) && ( i < *pCount ); ++i )
                phLed[ i ] = reinterpret_cast<zet_sysman_led_handle_t>(
                    zet_sysman_led_factory.getInstance( phLed[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLedGetProperties
    ze_result_t __zecall
    zetSysmanLedGetProperties(
        zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        zet_led_properties_t* pProperties               ///< [in] Will contain the properties of the LED.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_led_object_t*>( hLed )->dditable;
        auto pfnGetProperties = dditable->zet.SysmanLed.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<zet_sysman_led_object_t*>( hLed )->handle;

        // forward to device-driver
        result = pfnGetProperties( hLed, pProperties );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLedGetState
    ze_result_t __zecall
    zetSysmanLedGetState(
        zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        zet_led_state_t* pState                         ///< [in] Will contain the current state of the LED.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_led_object_t*>( hLed )->dditable;
        auto pfnGetState = dditable->zet.SysmanLed.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<zet_sysman_led_object_t*>( hLed )->handle;

        // forward to device-driver
        result = pfnGetState( hLed, pState );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanLedSetState
    ze_result_t __zecall
    zetSysmanLedSetState(
        zet_sysman_led_handle_t hLed,                   ///< [in] Handle for the component.
        const zet_led_state_t* pState                   ///< [in] New state of the LED.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_led_object_t*>( hLed )->dditable;
        auto pfnSetState = dditable->zet.SysmanLed.pfnSetState;
        if( nullptr == pfnSetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<zet_sysman_led_object_t*>( hLed )->handle;

        // forward to device-driver
        result = pfnSetState( hLed, pState );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnRasGet = dditable->zet.Sysman.pfnRasGet;
        if( nullptr == pfnRasGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnRasGet( hSysman, pCount, phRas );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phRas ) && ( i < *pCount ); ++i )
                phRas[ i ] = reinterpret_cast<zet_sysman_ras_handle_t>(
                    zet_sysman_ras_factory.getInstance( phRas[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanRasGetProperties
    ze_result_t __zecall
    zetSysmanRasGetProperties(
        zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        zet_ras_properties_t* pProperties               ///< [in] Structure describing RAS properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_ras_object_t*>( hRas )->dditable;
        auto pfnGetProperties = dditable->zet.SysmanRas.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zet_sysman_ras_object_t*>( hRas )->handle;

        // forward to device-driver
        result = pfnGetProperties( hRas, pProperties );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_ras_object_t*>( hRas )->dditable;
        auto pfnGetConfig = dditable->zet.SysmanRas.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zet_sysman_ras_object_t*>( hRas )->handle;

        // forward to device-driver
        result = pfnGetConfig( hRas, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanRasSetConfig
    ze_result_t __zecall
    zetSysmanRasSetConfig(
        zet_sysman_ras_handle_t hRas,                   ///< [in] Handle for the component.
        const zet_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_ras_object_t*>( hRas )->dditable;
        auto pfnSetConfig = dditable->zet.SysmanRas.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zet_sysman_ras_object_t*>( hRas )->handle;

        // forward to device-driver
        result = pfnSetConfig( hRas, pConfig );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_ras_object_t*>( hRas )->dditable;
        auto pfnGetState = dditable->zet.SysmanRas.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zet_sysman_ras_object_t*>( hRas )->handle;

        // forward to device-driver
        result = pfnGetState( hRas, clear, pTotalErrors, pDetails );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventGet
    ze_result_t __zecall
    zetSysmanEventGet(
        zet_sysman_handle_t hSysman,                    ///< [in] Sysman handle for the device
        zet_sysman_event_handle_t* phEvent              ///< [out] The event handle for the specified device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnEventGet = dditable->zet.Sysman.pfnEventGet;
        if( nullptr == pfnEventGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnEventGet( hSysman, phEvent );

        try
        {
            // convert driver handle to loader handle
            *phEvent = reinterpret_cast<zet_sysman_event_handle_t>(
                zet_sysman_event_factory.getInstance( *phEvent, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_event_object_t*>( hEvent )->dditable;
        auto pfnGetConfig = dditable->zet.SysmanEvent.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<zet_sysman_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnGetConfig( hEvent, pConfig );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanEventSetConfig
    ze_result_t __zecall
    zetSysmanEventSetConfig(
        zet_sysman_event_handle_t hEvent,               ///< [in] The event handle for the device
        const zet_event_config_t* pConfig               ///< [in] New event configuration (list of registered events).
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_event_object_t*>( hEvent )->dditable;
        auto pfnSetConfig = dditable->zet.SysmanEvent.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<zet_sysman_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnSetConfig( hEvent, pConfig );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_event_object_t*>( hEvent )->dditable;
        auto pfnGetState = dditable->zet.SysmanEvent.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hEvent = reinterpret_cast<zet_sysman_event_object_t*>( hEvent )->handle;

        // forward to device-driver
        result = pfnGetState( hEvent, clear, pEvents );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnListen = dditable->zet.SysmanEvent.pfnListen;
        if( nullptr == pfnListen )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // convert loader handles to driver handles
        for( size_t i = 0; ( nullptr != phEvents ) && ( i < count ); ++i )
            phEvents[ i ] = reinterpret_cast<zet_sysman_event_object_t*>( phEvents[ i ] )->handle;

        // forward to device-driver
        result = pfnListen( hDriver, timeout, count, phEvents, pEvents );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_object_t*>( hSysman )->dditable;
        auto pfnDiagnosticsGet = dditable->zet.Sysman.pfnDiagnosticsGet;
        if( nullptr == pfnDiagnosticsGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hSysman = reinterpret_cast<zet_sysman_object_t*>( hSysman )->handle;

        // forward to device-driver
        result = pfnDiagnosticsGet( hSysman, pCount, phDiagnostics );

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phDiagnostics ) && ( i < *pCount ); ++i )
                phDiagnostics[ i ] = reinterpret_cast<zet_sysman_diag_handle_t>(
                    zet_sysman_diag_factory.getInstance( phDiagnostics[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetSysmanDiagnosticsGetProperties
    ze_result_t __zecall
    zetSysmanDiagnosticsGetProperties(
        zet_sysman_diag_handle_t hDiagnostics,          ///< [in] Handle for the component.
        zet_diag_properties_t* pProperties              ///< [in] Structure describing the properties of a diagnostics test suite
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_diag_object_t*>( hDiagnostics )->dditable;
        auto pfnGetProperties = dditable->zet.SysmanDiagnostics.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDiagnostics = reinterpret_cast<zet_sysman_diag_object_t*>( hDiagnostics )->handle;

        // forward to device-driver
        result = pfnGetProperties( hDiagnostics, pProperties );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_diag_object_t*>( hDiagnostics )->dditable;
        auto pfnGetTests = dditable->zet.SysmanDiagnostics.pfnGetTests;
        if( nullptr == pfnGetTests )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDiagnostics = reinterpret_cast<zet_sysman_diag_object_t*>( hDiagnostics )->handle;

        // forward to device-driver
        result = pfnGetTests( hDiagnostics, pCount, pTests );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_sysman_diag_object_t*>( hDiagnostics )->dditable;
        auto pfnRunTests = dditable->zet.SysmanDiagnostics.pfnRunTests;
        if( nullptr == pfnRunTests )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDiagnostics = reinterpret_cast<zet_sysman_diag_object_t*>( hDiagnostics )->handle;

        // forward to device-driver
        result = pfnRunTests( hDiagnostics, start, end, pResult );

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_driver_object_t*>( hDriver )->dditable;
        auto pfnCreate = dditable->zet.Tracer.pfnCreate;
        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<zet_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnCreate( hDriver, desc, phTracer );

        try
        {
            // convert driver handle to loader handle
            *phTracer = reinterpret_cast<zet_tracer_handle_t>(
                zet_tracer_factory.getInstance( *phTracer, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerDestroy
    ze_result_t __zecall
    zetTracerDestroy(
        zet_tracer_handle_t hTracer                     ///< [in][release] handle of tracer object to destroy
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_tracer_object_t*>( hTracer )->dditable;
        auto pfnDestroy = dditable->zet.Tracer.pfnDestroy;
        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTracer = reinterpret_cast<zet_tracer_object_t*>( hTracer )->handle;

        // forward to device-driver
        result = pfnDestroy( hTracer );

        // release loader handle
        zet_tracer_factory.release( hTracer );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerSetPrologues
    ze_result_t __zecall
    zetTracerSetPrologues(
        zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                 ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_tracer_object_t*>( hTracer )->dditable;
        auto pfnSetPrologues = dditable->zet.Tracer.pfnSetPrologues;
        if( nullptr == pfnSetPrologues )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTracer = reinterpret_cast<zet_tracer_object_t*>( hTracer )->handle;

        // forward to device-driver
        result = pfnSetPrologues( hTracer, pCoreCbs );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerSetEpilogues
    ze_result_t __zecall
    zetTracerSetEpilogues(
        zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                 ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_tracer_object_t*>( hTracer )->dditable;
        auto pfnSetEpilogues = dditable->zet.Tracer.pfnSetEpilogues;
        if( nullptr == pfnSetEpilogues )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTracer = reinterpret_cast<zet_tracer_object_t*>( hTracer )->handle;

        // forward to device-driver
        result = pfnSetEpilogues( hTracer, pCoreCbs );

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerSetEnabled
    ze_result_t __zecall
    zetTracerSetEnabled(
        zet_tracer_handle_t hTracer,                    ///< [in] handle of the tracer
        ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zet_tracer_object_t*>( hTracer )->dditable;
        auto pfnSetEnabled = dditable->zet.Tracer.pfnSetEnabled;
        if( nullptr == pfnSetEnabled )
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

        // convert loader handle to driver handle
        hTracer = reinterpret_cast<zet_tracer_object_t*>( hTracer )->handle;

        // forward to device-driver
        result = pfnSetEnabled( hTracer, enable );

        return result;
    }

} // namespace loader

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_global_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetGlobalProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.Global );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnInit                                     = loader::zetInit;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.Global;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetGlobalProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zetGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetDeviceProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.Device );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnActivateMetricGroups                     = loader::zetDeviceActivateMetricGroups;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.Device;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetDeviceProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zetGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetCommandListProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.CommandList );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnAppendMetricTracerMarker                 = loader::zetCommandListAppendMetricTracerMarker;
            pDdiTable->pfnAppendMetricQueryBegin                   = loader::zetCommandListAppendMetricQueryBegin;
            pDdiTable->pfnAppendMetricQueryEnd                     = loader::zetCommandListAppendMetricQueryEnd;
            pDdiTable->pfnAppendMetricMemoryBarrier                = loader::zetCommandListAppendMetricMemoryBarrier;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.CommandList;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetCommandListProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetCommandListProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zetGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_module_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetModuleProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.Module );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetDebugInfo                             = loader::zetModuleGetDebugInfo;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.Module;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetModuleProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetModuleProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zetGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_kernel_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetKernelProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetKernelProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.Kernel );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProfileInfo                           = loader::zetKernelGetProfileInfo;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.Kernel;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetKernelProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetKernelProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zetGetMetricGroupProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_group_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricGroupProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetMetricGroupProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.MetricGroup );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::zetMetricGroupGet;
            pDdiTable->pfnGetProperties                            = loader::zetMetricGroupGetProperties;
            pDdiTable->pfnCalculateMetricValues                    = loader::zetMetricGroupCalculateMetricValues;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.MetricGroup;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetMetricGroupProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetMetricGroupProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zetGetMetricProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetMetricProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.Metric );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::zetMetricGet;
            pDdiTable->pfnGetProperties                            = loader::zetMetricGetProperties;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.Metric;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetMetricProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetMetricProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricTracer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetMetricTracerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_tracer_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricTracerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetMetricTracerProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.MetricTracer );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnOpen                                     = loader::zetMetricTracerOpen;
            pDdiTable->pfnClose                                    = loader::zetMetricTracerClose;
            pDdiTable->pfnReadData                                 = loader::zetMetricTracerReadData;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.MetricTracer;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetMetricTracerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetMetricTracerProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zetGetMetricQueryPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_pool_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricQueryPoolProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetMetricQueryPoolProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.MetricQueryPool );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zetMetricQueryPoolCreate;
            pDdiTable->pfnDestroy                                  = loader::zetMetricQueryPoolDestroy;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.MetricQueryPool;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetMetricQueryPoolProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetMetricQueryPoolProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zetGetMetricQueryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricQueryProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetMetricQueryProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.MetricQuery );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
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
            *pDdiTable = loader::context.drivers.front().dditable.zet.MetricQuery;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetMetricQueryProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetMetricQueryProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Tracer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetTracerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_tracer_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetTracerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetTracerProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.Tracer );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnCreate                                   = loader::zetTracerCreate;
            pDdiTable->pfnDestroy                                  = loader::zetTracerDestroy;
            pDdiTable->pfnSetPrologues                             = loader::zetTracerSetPrologues;
            pDdiTable->pfnSetEpilogues                             = loader::zetTracerSetEpilogues;
            pDdiTable->pfnSetEnabled                               = loader::zetTracerSetEnabled;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.Tracer;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetTracerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetTracerProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sysman table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetSysmanProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.Sysman );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGet                                      = loader::zetSysmanGet;
            pDdiTable->pfnDeviceGetProperties                      = loader::zetSysmanDeviceGetProperties;
            pDdiTable->pfnSchedulerGetSupportedModes               = loader::zetSysmanSchedulerGetSupportedModes;
            pDdiTable->pfnSchedulerGetCurrentMode                  = loader::zetSysmanSchedulerGetCurrentMode;
            pDdiTable->pfnSchedulerGetTimeoutModeProperties        = loader::zetSysmanSchedulerGetTimeoutModeProperties;
            pDdiTable->pfnSchedulerGetTimesliceModeProperties      = loader::zetSysmanSchedulerGetTimesliceModeProperties;
            pDdiTable->pfnSchedulerSetTimeoutMode                  = loader::zetSysmanSchedulerSetTimeoutMode;
            pDdiTable->pfnSchedulerSetTimesliceMode                = loader::zetSysmanSchedulerSetTimesliceMode;
            pDdiTable->pfnSchedulerSetExclusiveMode                = loader::zetSysmanSchedulerSetExclusiveMode;
            pDdiTable->pfnSchedulerSetComputeUnitDebugMode         = loader::zetSysmanSchedulerSetComputeUnitDebugMode;
            pDdiTable->pfnPerformanceProfileGetSupported           = loader::zetSysmanPerformanceProfileGetSupported;
            pDdiTable->pfnPerformanceProfileGet                    = loader::zetSysmanPerformanceProfileGet;
            pDdiTable->pfnPerformanceProfileSet                    = loader::zetSysmanPerformanceProfileSet;
            pDdiTable->pfnProcessesGetState                        = loader::zetSysmanProcessesGetState;
            pDdiTable->pfnDeviceReset                              = loader::zetSysmanDeviceReset;
            pDdiTable->pfnDeviceGetRepairStatus                    = loader::zetSysmanDeviceGetRepairStatus;
            pDdiTable->pfnPciGetProperties                         = loader::zetSysmanPciGetProperties;
            pDdiTable->pfnPciGetState                              = loader::zetSysmanPciGetState;
            pDdiTable->pfnPciGetBars                               = loader::zetSysmanPciGetBars;
            pDdiTable->pfnPciGetStats                              = loader::zetSysmanPciGetStats;
            pDdiTable->pfnPowerGet                                 = loader::zetSysmanPowerGet;
            pDdiTable->pfnFrequencyGet                             = loader::zetSysmanFrequencyGet;
            pDdiTable->pfnEngineGet                                = loader::zetSysmanEngineGet;
            pDdiTable->pfnStandbyGet                               = loader::zetSysmanStandbyGet;
            pDdiTable->pfnFirmwareGet                              = loader::zetSysmanFirmwareGet;
            pDdiTable->pfnMemoryGet                                = loader::zetSysmanMemoryGet;
            pDdiTable->pfnFabricPortGet                            = loader::zetSysmanFabricPortGet;
            pDdiTable->pfnTemperatureGet                           = loader::zetSysmanTemperatureGet;
            pDdiTable->pfnPsuGet                                   = loader::zetSysmanPsuGet;
            pDdiTable->pfnFanGet                                   = loader::zetSysmanFanGet;
            pDdiTable->pfnLedGet                                   = loader::zetSysmanLedGet;
            pDdiTable->pfnRasGet                                   = loader::zetSysmanRasGet;
            pDdiTable->pfnEventGet                                 = loader::zetSysmanEventGet;
            pDdiTable->pfnDiagnosticsGet                           = loader::zetSysmanDiagnosticsGet;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.Sysman;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetSysmanProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetSysmanProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPower table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanPowerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_power_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanPowerProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetSysmanPowerProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.SysmanPower );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zetSysmanPowerGetProperties;
            pDdiTable->pfnGetEnergyCounter                         = loader::zetSysmanPowerGetEnergyCounter;
            pDdiTable->pfnGetLimits                                = loader::zetSysmanPowerGetLimits;
            pDdiTable->pfnSetLimits                                = loader::zetSysmanPowerSetLimits;
            pDdiTable->pfnGetEnergyThreshold                       = loader::zetSysmanPowerGetEnergyThreshold;
            pDdiTable->pfnSetEnergyThreshold                       = loader::zetSysmanPowerSetEnergyThreshold;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.SysmanPower;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetSysmanPowerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetSysmanPowerProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFrequency table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFrequencyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_frequency_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanFrequencyProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetSysmanFrequencyProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.SysmanFrequency );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zetSysmanFrequencyGetProperties;
            pDdiTable->pfnGetAvailableClocks                       = loader::zetSysmanFrequencyGetAvailableClocks;
            pDdiTable->pfnGetRange                                 = loader::zetSysmanFrequencyGetRange;
            pDdiTable->pfnSetRange                                 = loader::zetSysmanFrequencySetRange;
            pDdiTable->pfnGetState                                 = loader::zetSysmanFrequencyGetState;
            pDdiTable->pfnGetThrottleTime                          = loader::zetSysmanFrequencyGetThrottleTime;
            pDdiTable->pfnOcGetCapabilities                        = loader::zetSysmanFrequencyOcGetCapabilities;
            pDdiTable->pfnOcGetConfig                              = loader::zetSysmanFrequencyOcGetConfig;
            pDdiTable->pfnOcSetConfig                              = loader::zetSysmanFrequencyOcSetConfig;
            pDdiTable->pfnOcGetIccMax                              = loader::zetSysmanFrequencyOcGetIccMax;
            pDdiTable->pfnOcSetIccMax                              = loader::zetSysmanFrequencyOcSetIccMax;
            pDdiTable->pfnOcGetTjMax                               = loader::zetSysmanFrequencyOcGetTjMax;
            pDdiTable->pfnOcSetTjMax                               = loader::zetSysmanFrequencyOcSetTjMax;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.SysmanFrequency;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetSysmanFrequencyProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetSysmanFrequencyProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEngine table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanEngineProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_engine_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanEngineProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetSysmanEngineProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.SysmanEngine );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zetSysmanEngineGetProperties;
            pDdiTable->pfnGetActivity                              = loader::zetSysmanEngineGetActivity;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.SysmanEngine;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetSysmanEngineProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetSysmanEngineProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanStandby table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanStandbyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_standby_dditable_t* pDdiTable        ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanStandbyProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetSysmanStandbyProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.SysmanStandby );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zetSysmanStandbyGetProperties;
            pDdiTable->pfnGetMode                                  = loader::zetSysmanStandbyGetMode;
            pDdiTable->pfnSetMode                                  = loader::zetSysmanStandbySetMode;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.SysmanStandby;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetSysmanStandbyProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetSysmanStandbyProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFirmware table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFirmwareProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_firmware_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanFirmwareProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetSysmanFirmwareProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.SysmanFirmware );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zetSysmanFirmwareGetProperties;
            pDdiTable->pfnGetChecksum                              = loader::zetSysmanFirmwareGetChecksum;
            pDdiTable->pfnFlash                                    = loader::zetSysmanFirmwareFlash;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.SysmanFirmware;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetSysmanFirmwareProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetSysmanFirmwareProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanMemory table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanMemoryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_memory_dditable_t* pDdiTable         ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanMemoryProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetSysmanMemoryProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.SysmanMemory );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zetSysmanMemoryGetProperties;
            pDdiTable->pfnGetState                                 = loader::zetSysmanMemoryGetState;
            pDdiTable->pfnGetBandwidth                             = loader::zetSysmanMemoryGetBandwidth;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.SysmanMemory;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetSysmanMemoryProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetSysmanMemoryProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFabricPort table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFabricPortProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_fabric_port_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanFabricPortProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetSysmanFabricPortProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.SysmanFabricPort );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zetSysmanFabricPortGetProperties;
            pDdiTable->pfnGetLinkType                              = loader::zetSysmanFabricPortGetLinkType;
            pDdiTable->pfnGetConfig                                = loader::zetSysmanFabricPortGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zetSysmanFabricPortSetConfig;
            pDdiTable->pfnGetState                                 = loader::zetSysmanFabricPortGetState;
            pDdiTable->pfnGetThroughput                            = loader::zetSysmanFabricPortGetThroughput;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.SysmanFabricPort;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetSysmanFabricPortProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetSysmanFabricPortProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanTemperature table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanTemperatureProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_temperature_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanTemperatureProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetSysmanTemperatureProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.SysmanTemperature );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zetSysmanTemperatureGetProperties;
            pDdiTable->pfnGetConfig                                = loader::zetSysmanTemperatureGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zetSysmanTemperatureSetConfig;
            pDdiTable->pfnGetState                                 = loader::zetSysmanTemperatureGetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.SysmanTemperature;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetSysmanTemperatureProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetSysmanTemperatureProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanPsu table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanPsuProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_psu_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanPsuProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetSysmanPsuProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.SysmanPsu );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zetSysmanPsuGetProperties;
            pDdiTable->pfnGetState                                 = loader::zetSysmanPsuGetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.SysmanPsu;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetSysmanPsuProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetSysmanPsuProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanFan table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanFanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_fan_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanFanProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetSysmanFanProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.SysmanFan );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zetSysmanFanGetProperties;
            pDdiTable->pfnGetConfig                                = loader::zetSysmanFanGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zetSysmanFanSetConfig;
            pDdiTable->pfnGetState                                 = loader::zetSysmanFanGetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.SysmanFan;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetSysmanFanProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetSysmanFanProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanLed table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanLedProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_led_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanLedProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetSysmanLedProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.SysmanLed );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zetSysmanLedGetProperties;
            pDdiTable->pfnGetState                                 = loader::zetSysmanLedGetState;
            pDdiTable->pfnSetState                                 = loader::zetSysmanLedSetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.SysmanLed;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetSysmanLedProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetSysmanLedProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanRas table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanRasProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_ras_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanRasProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetSysmanRasProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.SysmanRas );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zetSysmanRasGetProperties;
            pDdiTable->pfnGetConfig                                = loader::zetSysmanRasGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zetSysmanRasSetConfig;
            pDdiTable->pfnGetState                                 = loader::zetSysmanRasGetState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.SysmanRas;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetSysmanRasProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetSysmanRasProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanDiagnostics table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanDiagnosticsProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_diagnostics_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanDiagnosticsProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetSysmanDiagnosticsProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.SysmanDiagnostics );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetProperties                            = loader::zetSysmanDiagnosticsGetProperties;
            pDdiTable->pfnGetTests                                 = loader::zetSysmanDiagnosticsGetTests;
            pDdiTable->pfnRunTests                                 = loader::zetSysmanDiagnosticsRunTests;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.SysmanDiagnostics;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetSysmanDiagnosticsProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetSysmanDiagnosticsProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's SysmanEvent table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
__zedllexport ze_result_t __zecall
zetGetSysmanEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_sysman_event_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanEventProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetSysmanEventProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.SysmanEvent );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnGetConfig                                = loader::zetSysmanEventGetConfig;
            pDdiTable->pfnSetConfig                                = loader::zetSysmanEventSetConfig;
            pDdiTable->pfnGetState                                 = loader::zetSysmanEventGetState;
            pDdiTable->pfnListen                                   = loader::zetSysmanEventListen;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.SysmanEvent;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetSysmanEventProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetSysmanEventProcAddrTable") );
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
__zedllexport ze_result_t __zecall
zetGetDebugProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_debug_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context.drivers.size() < 1 )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : loader::context.drivers )
    {
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetDebugProcAddrTable_t>(
                GET_FUNCTION_PTR( drv.handle, "zetGetDebugProcAddrTable") );
            result = getTable( version, &drv.dditable.zet.Debug );
        }
    }

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context.drivers.size() > 1 ) || loader::context.forceIntercept )
        {
            // return pointers to loader's DDIs
            pDdiTable->pfnAttach                                   = loader::zetDebugAttach;
            pDdiTable->pfnDetach                                   = loader::zetDebugDetach;
            pDdiTable->pfnGetNumThreads                            = loader::zetDebugGetNumThreads;
            pDdiTable->pfnReadEvent                                = loader::zetDebugReadEvent;
            pDdiTable->pfnInterrupt                                = loader::zetDebugInterrupt;
            pDdiTable->pfnResume                                   = loader::zetDebugResume;
            pDdiTable->pfnReadMemory                               = loader::zetDebugReadMemory;
            pDdiTable->pfnWriteMemory                              = loader::zetDebugWriteMemory;
            pDdiTable->pfnReadState                                = loader::zetDebugReadState;
            pDdiTable->pfnWriteState                               = loader::zetDebugWriteState;
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context.drivers.front().dditable.zet.Debug;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context.validationLayer ))
    {
        auto getTable = reinterpret_cast<zet_pfnGetDebugProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context.validationLayer, "zetGetDebugProcAddrTable") );
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif
