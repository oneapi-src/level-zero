/*
 *
 * Copyright (C) 2019-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_null.cpp
 *
 */
#include "ze_null.h"

namespace driver
{
    //////////////////////////////////////////////////////////////////////////
    context_t context;

    //////////////////////////////////////////////////////////////////////////
    context_t::context_t()
    {
        zesDdiTable.Driver.pfnGet = [](
            uint32_t* pCount,
            ze_driver_handle_t* phDrivers )
        {
            *pCount = 1;
            if( nullptr != phDrivers ) *reinterpret_cast<void**>( phDrivers ) = context.get();
            return ZE_RESULT_SUCCESS;
        };
        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Driver.pfnGet = [](
            uint32_t* pCount,
            ze_driver_handle_t* phDrivers )
        {
            *pCount = 1;
            if( nullptr != phDrivers ) *reinterpret_cast<void**>( phDrivers ) = context.get();
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGet = [](
            ze_driver_handle_t,
            uint32_t* pCount,
            ze_device_handle_t* phDevices )
        {
            *pCount = 1;
            if( nullptr != phDevices ) *reinterpret_cast<void**>( phDevices ) = context.get();
            return ZE_RESULT_SUCCESS;
        };

        //pfnCreateEventPool

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Driver.pfnGetApiVersion = [](
            ze_driver_handle_t,
            ze_api_version_t* version )
        {
            *version = context.version;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Driver.pfnGetProperties = [](
            ze_driver_handle_t,
            ze_driver_properties_t* pDriverProperties )
        {
            ze_driver_properties_t driverProperties = {};
            driverProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
            //driverProperties.uuid
            driverProperties.driverVersion = 0;

            *pDriverProperties = driverProperties;
            return ZE_RESULT_SUCCESS;
        };

        //pfnGetIPCProperties
        
        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Mem.pfnAllocShared = [](
            ze_context_handle_t,
            const ze_device_mem_alloc_desc_t*,
            const ze_host_mem_alloc_desc_t*,
            size_t size,
            size_t alignment,
            ze_device_handle_t,
            void** pptr)
        {
            *pptr = malloc(size);
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Mem.pfnAllocDevice = [](
            ze_context_handle_t,
            const ze_device_mem_alloc_desc_t*,
            size_t size,
            size_t alignment,
            ze_device_handle_t,
            void** pptr)
        {
            *pptr = malloc(size);
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Mem.pfnAllocHost = [](
            ze_context_handle_t,
            const ze_host_mem_alloc_desc_t*,
            size_t size,
            size_t alignment,
            void** pptr)
        {
            *pptr = malloc(size);
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Mem.pfnFree = [](
            ze_context_handle_t,
            void* ptr)
        {
            free(ptr);
            return ZE_RESULT_SUCCESS;
        };

        //pfnGetMemProperties
        //pfnGetMemAddressRange
        //pfnGetMemIpcHandle
        //pfnOpenMemIpcHandle
        //pfnCloseMemIpcHandle

        //////////////////////////////////////////////////////////////////////////
        //pfnGetSubDevices

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGetProperties = [](
            ze_device_handle_t,
            ze_device_properties_t* pDeviceProperties )
        {
            ze_device_properties_t deviceProperties = {};
            deviceProperties.stype = ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES;
            deviceProperties.type = ZE_DEVICE_TYPE_GPU;
#if defined(_WIN32)
            strcpy_s( deviceProperties.name, "Null Device" );
#else
            strcpy( deviceProperties.name, "Null Device" );
#endif

            *pDeviceProperties = deviceProperties;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGetComputeProperties = [](
            ze_device_handle_t,
            ze_device_compute_properties_t* pComputeProperties )
        {
            ze_device_compute_properties_t computeProperties = {};
            computeProperties.stype = ZE_STRUCTURE_TYPE_DEVICE_COMPUTE_PROPERTIES;

            *pComputeProperties = computeProperties;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGetCommandQueueGroupProperties = [](
            ze_device_handle_t,
            uint32_t* pCount,
            ze_command_queue_group_properties_t* pCommandQueueGroupProperties )
        {
            if( nullptr != pCommandQueueGroupProperties )
            {
                ze_command_queue_group_properties_t commandQueueGroupProperties = {};
                commandQueueGroupProperties.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES;
                commandQueueGroupProperties.flags =
                    ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COPY |
                    ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE;

                *pCommandQueueGroupProperties = commandQueueGroupProperties;
            }
            *pCount = 1;

            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGetMemoryProperties = [](
            ze_device_handle_t,
            uint32_t* pCount,
            ze_device_memory_properties_t* pMemProperties )
        {
            ze_device_memory_properties_t memoryProperties = {};
            memoryProperties.stype = ZE_STRUCTURE_TYPE_DEVICE_MEMORY_PROPERTIES;

            *pCount = 1;
            if( nullptr != pMemProperties ) *pMemProperties = memoryProperties;

            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGetMemoryAccessProperties = [](
            ze_device_handle_t,
            ze_device_memory_access_properties_t* pMemAccessProperties )
        {
            ze_device_memory_access_properties_t memoryAccessProperties = {};
            memoryAccessProperties.stype = ZE_STRUCTURE_TYPE_DEVICE_MEMORY_ACCESS_PROPERTIES;

            *pMemAccessProperties = memoryAccessProperties;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGetCacheProperties = [](
            ze_device_handle_t,
            uint32_t* pCount,
            ze_device_cache_properties_t* pCacheProperties )
        {
            if( nullptr != pCacheProperties )
            {
                ze_device_cache_properties_t cacheProperties = {};
                cacheProperties.stype = ZE_STRUCTURE_TYPE_DEVICE_CACHE_PROPERTIES;

                *pCacheProperties = cacheProperties;
            }
            *pCount = 1;

            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGetImageProperties = [](
            ze_device_handle_t,
            ze_device_image_properties_t* pImageProperties )
        {
            ze_device_image_properties_t imageProperties = {};
            imageProperties.stype = ZE_STRUCTURE_TYPE_DEVICE_IMAGE_PROPERTIES;

            *pImageProperties = imageProperties;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Driver.pfnGetExtensionProperties = [](
            ze_driver_handle_t,
            uint32_t* pCount,
            ze_driver_extension_properties_t* pExtensionProperties )
        {
            if( nullptr != pExtensionProperties )
            {
                ze_driver_extension_properties_t driverExtensionProperties = {};
#if defined(_WIN32)
                strcpy_s( driverExtensionProperties.name, ZET_API_TRACING_EXP_NAME );
#else
                strcpy( driverExtensionProperties.name, ZET_API_TRACING_EXP_NAME );
#endif
                driverExtensionProperties.version = ZET_API_TRACING_EXP_VERSION_1_0;

                *pExtensionProperties = driverExtensionProperties;
            }
            *pCount = 1;

            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zetDdiTable.MetricGroup.pfnGet = [](
            zet_device_handle_t,
            uint32_t* pCount,
            zet_metric_group_handle_t* phMetricGroups )
        {
            *pCount = 1;
            if( nullptr != phMetricGroups ) *reinterpret_cast<void**>( phMetricGroups ) = context.get();
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zetDdiTable.MetricGroup.pfnGetProperties = [](
            zet_metric_group_handle_t,
            zet_metric_group_properties_t* pProperties )
        {
            zet_metric_group_properties_t metricGroupProperties = {};
            metricGroupProperties.stype = ZET_STRUCTURE_TYPE_METRIC_GROUP_PROPERTIES;
            metricGroupProperties.metricCount = 1;
            metricGroupProperties.samplingType = 
                ZET_METRIC_GROUP_SAMPLING_TYPE_FLAG_EVENT_BASED |
                ZET_METRIC_GROUP_SAMPLING_TYPE_FLAG_TIME_BASED;
#if defined(_WIN32)
            strcpy_s( metricGroupProperties.name, "Null Metric Group" );
#else
            strcpy( metricGroupProperties.name, "Null Metric Group" );
#endif

            *pProperties = metricGroupProperties;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zetDdiTable.MetricGroup.pfnCalculateMetricValues = [](
            zet_metric_group_handle_t,
            zet_metric_group_calculation_type_t,
            size_t,
            const uint8_t*,
            uint32_t* pMetricValueCount,
            zet_typed_value_t* pMetricValues )
        {
            *pMetricValueCount = 1;
            if( pMetricValues ) *pMetricValues = {};
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zetDdiTable.Metric.pfnGet = [](
            zet_metric_group_handle_t,
            uint32_t* pCount,
            zet_metric_handle_t* phMetrics )
        {
            *pCount = 1;
            if( nullptr != phMetrics ) *reinterpret_cast<void**>( phMetrics ) = context.get();
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zetDdiTable.Metric.pfnGetProperties = [](
            zet_metric_handle_t,
            zet_metric_properties_t* pProperties )
        {
            zet_metric_properties_t metricProperties = {};
            metricProperties.stype = ZET_STRUCTURE_TYPE_METRIC_PROPERTIES;
            metricProperties.metricType = ZET_METRIC_TYPE_DURATION;
            metricProperties.resultType = ZET_VALUE_TYPE_UINT32;
#if defined(_WIN32)
            strcpy_s( metricProperties.name, "Null Metric" );
            strcpy_s( metricProperties.resultUnits, "ns" );

#else
            strcpy( metricProperties.name, "Null Metric" );
            strcpy( metricProperties.resultUnits, "ns" );
#endif
            
            *pProperties = metricProperties;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zetDdiTable.MetricQuery.pfnGetData = [](
            zet_metric_query_handle_t,
            size_t* pRawDataSize,
            uint8_t* pRawData )
        {
            *pRawDataSize = 1;
            if( pRawData ) *pRawData = 0;
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zetDdiTable.MetricStreamer.pfnReadData = [](
            zet_metric_streamer_handle_t,
            uint32_t,
            size_t* pRawDataSize,
            uint8_t* pRawData )
        {
            *pRawDataSize = 1;
            if( pRawData ) *pRawData = 0;
            return ZE_RESULT_SUCCESS;
        };
    }
} // namespace driver

namespace instrumented
{
    //////////////////////////////////////////////////////////////////////////
    context_t context;

    //////////////////////////////////////////////////////////////////////////
    context_t::context_t()
    {
        //////////////////////////////////////////////////////////////////////////
        enableTracing = getenv_tobool( "ZET_ENABLE_API_TRACING_EXP" );
        if( enableTracing )
        {
            tracerData.emplace_back(); // reserve index 0

            //////////////////////////////////////////////////////////////////////////
            driver::context.zetDdiTable.TracerExp.pfnCreate = [](
                zet_context_handle_t,
                const zet_tracer_exp_desc_t* desc,
                zet_tracer_exp_handle_t* phTracer )
            {
                context.tracerData.emplace_back();
                auto index = context.tracerData.size() - 1;
                context.tracerData[ index ].userData = desc->pUserData;

                *phTracer = reinterpret_cast<decltype( *phTracer )>( index );
                return ZE_RESULT_SUCCESS;
            };

            //////////////////////////////////////////////////////////////////////////
            driver::context.zetDdiTable.TracerExp.pfnSetPrologues = [](
                zet_tracer_exp_handle_t hTracer,
                zet_core_callbacks_t* pCoreCbs)
            {
                auto index = reinterpret_cast<size_t>( hTracer );

                context.tracerData[ index ].zePrologueCbs = *pCoreCbs;
                return ZE_RESULT_SUCCESS;
            };

            //////////////////////////////////////////////////////////////////////////
            driver::context.zetDdiTable.TracerExp.pfnSetEpilogues = [](
                zet_tracer_exp_handle_t hTracer,
                zet_core_callbacks_t* pCoreCbs)
            {
                auto index = reinterpret_cast<size_t>( hTracer );

                context.tracerData[ index ].zeEpilogueCbs = *pCoreCbs;
                return ZE_RESULT_SUCCESS;
            };

            //////////////////////////////////////////////////////////////////////////
            driver::context.zetDdiTable.TracerExp.pfnSetEnabled = [](
                zet_tracer_exp_handle_t hTracer,
                ze_bool_t enable )
            {
                auto index = reinterpret_cast<size_t>( hTracer );
                context.tracerData[ index ].enabled = enable;

                return ZE_RESULT_SUCCESS;
            };
        }
    }
} // namespace instrumented
