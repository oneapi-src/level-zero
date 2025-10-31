/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_null.cpp
 *
 */
#include "ze_null.h"
#include <cstring>

namespace driver
{
    //////////////////////////////////////////////////////////////////////////
    context_t context;
    ze_dditable_driver_t pCore;
    zet_dditable_driver_t pTools;
    zes_dditable_driver_t pSysman;
    zer_dditable_driver_t pRuntime;

    //////////////////////////////////////////////////////////////////////////
    context_t::context_t()
    {
        auto ddi_test_disable = getenv_string( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT" );
        #ifndef ZEL_NULL_DRIVER_ID
        #define ZEL_NULL_DRIVER_ID 1
        #endif
        std::string null_driver_id_str = std::to_string(ZEL_NULL_DRIVER_ID);
        ddiExtensionSupported = (ddi_test_disable != null_driver_id_str && ddi_test_disable != "3");
        
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
            auto pNext = reinterpret_cast<ze_base_properties_t *>(pDriverProperties->pNext);
            while (pNext) {
                if (pNext->stype == ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES && context.ddiExtensionSupported) {
                    ze_driver_ddi_handles_ext_properties_t *pDdiHandlesExtProperties = reinterpret_cast<ze_driver_ddi_handles_ext_properties_t *>(pNext);
                    pDdiHandlesExtProperties->flags = ze_driver_ddi_handle_ext_flag_t::ZE_DRIVER_DDI_HANDLE_EXT_FLAG_DDI_HANDLE_EXT_SUPPORTED;
                }
                pNext = reinterpret_cast<ze_base_properties_t *>(pNext->pNext);
            }
            pDriverProperties->driverVersion = 0;

            return ZE_RESULT_SUCCESS;
        };
        
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

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.EventPool.pfnCreate = [](
            ze_context_handle_t,
            const ze_event_pool_desc_t* desc,
            uint32_t,
            ze_device_handle_t*,
            ze_event_pool_handle_t* phEventPool )
        {
            *phEventPool = reinterpret_cast<ze_event_pool_handle_t>(context.get());
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Event.pfnCreate = [](
            ze_event_pool_handle_t,
            const ze_event_desc_t* desc,
            ze_event_handle_t* phEvent )
        {
            *phEvent = reinterpret_cast<ze_event_handle_t>(context.get());
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.CommandList.pfnCreate = [](
            ze_context_handle_t,
            ze_device_handle_t,
            const ze_command_list_desc_t* desc,
            ze_command_list_handle_t* phCommandList )
        {
            *phCommandList = reinterpret_cast<ze_command_list_handle_t>(context.get());
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.CommandList.pfnCreateImmediate = [](
            ze_context_handle_t,
            ze_device_handle_t,
            const ze_command_queue_desc_t* desc,
            ze_command_list_handle_t* phCommandListImmediate )
        {
            *phCommandListImmediate = reinterpret_cast<ze_command_list_handle_t>(context.get());
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.CommandQueue.pfnCreate = [](
            ze_context_handle_t,
            ze_device_handle_t,
            const ze_command_queue_desc_t* desc,
            ze_command_queue_handle_t* phCommandQueue )
        {
            *phCommandQueue = reinterpret_cast<ze_command_queue_handle_t>(context.get());
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Context.pfnCreate = [](
            ze_driver_handle_t,
            const ze_context_desc_t*,
            ze_context_handle_t* phContext )
        {
            *phContext = reinterpret_cast<ze_context_handle_t>(context.get());
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Context.pfnDestroy = [](
            ze_context_handle_t )
        {
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.CommandList.pfnDestroy = [](
            ze_command_list_handle_t )
        {
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.CommandQueue.pfnDestroy = [](
            ze_command_queue_handle_t )
        {
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.EventPool.pfnDestroy = [](
            ze_event_pool_handle_t )
        {
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Event.pfnDestroy = [](
            ze_event_handle_t )
        {
            return ZE_RESULT_SUCCESS;
        };
        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Module.pfnCreate = [](
            ze_context_handle_t,
            ze_device_handle_t,
            const ze_module_desc_t*,
            ze_module_handle_t* phModule,
            ze_module_build_log_handle_t* phModuleBuildLog )
        {
            *phModule = reinterpret_cast<ze_module_handle_t>(context.get());
            if (phModuleBuildLog) {
                *phModuleBuildLog = reinterpret_cast<ze_module_build_log_handle_t>(context.get());
            }
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Module.pfnDestroy = [](
            ze_module_handle_t )
        {
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.ModuleBuildLog.pfnDestroy = [](
            ze_module_build_log_handle_t )
        {
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.ModuleBuildLog.pfnGetString = [](
            ze_module_build_log_handle_t,
            size_t* pSize,
            char* pBuildLog )
        {
            const char* log = "Build log not available.";
            *pSize = strlen(log) + 1;
            if (pBuildLog) {
            #if defined(_WIN32)
                strncpy_s( pBuildLog, *pSize, log, *pSize );
            #else
                strncpy( pBuildLog, log, *pSize );
            #endif
            }
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.PhysicalMem.pfnCreate = [](
            ze_context_handle_t,
            ze_device_handle_t,
            ze_physical_mem_desc_t*,
            ze_physical_mem_handle_t* phPhysicalMemory )
        {
            *phPhysicalMemory = reinterpret_cast<ze_physical_mem_handle_t>(context.get());
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.PhysicalMem.pfnDestroy = []( ze_context_handle_t,
            ze_physical_mem_handle_t )
        {
            return ZE_RESULT_SUCCESS;
        };
        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Fence.pfnCreate = [](
            ze_command_queue_handle_t,
            const ze_fence_desc_t*,
            ze_fence_handle_t* phFence )
        {
            *phFence = reinterpret_cast<ze_fence_handle_t>(context.get());
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Fence.pfnDestroy = [](
            ze_fence_handle_t )
        {
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Image.pfnCreate = [](
            ze_context_handle_t,
            ze_device_handle_t,
            const ze_image_desc_t*,
            ze_image_handle_t* phImage )
        {
            *phImage = reinterpret_cast<ze_image_handle_t>(context.get());
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Image.pfnDestroy = [](
            ze_image_handle_t )
        {
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Sampler.pfnCreate = [](
            ze_context_handle_t,
            ze_device_handle_t,
            const ze_sampler_desc_t*,
            ze_sampler_handle_t* phSampler )
        {
            *phSampler = reinterpret_cast<ze_sampler_handle_t>(context.get());
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Sampler.pfnDestroy = [](
            ze_sampler_handle_t )
        {
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Kernel.pfnCreate = [](
            ze_module_handle_t,
            const ze_kernel_desc_t*,
            ze_kernel_handle_t* phKernel )
        {
            *phKernel = reinterpret_cast<ze_kernel_handle_t>(context.get());
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Kernel.pfnDestroy = [](
            ze_kernel_handle_t )
        {
            return ZE_RESULT_SUCCESS;
        };

        //////////////////////////////////////////////////////////////////////////
        zeDdiTable.Device.pfnGetProperties = [](
            ze_device_handle_t,
            ze_device_properties_t* pDeviceProperties )
        {
            ze_device_properties_t deviceProperties = {};
            deviceProperties.stype = ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES;
            deviceProperties.type = ZE_DEVICE_TYPE_GPU;

            // Check compile-time definitions first
            #ifdef ZEL_NULL_DRIVER_TYPE_NPU
            deviceProperties.type = ZE_DEVICE_TYPE_VPU;
            #endif

            #ifdef ZEL_NULL_DRIVER_TYPE_GPU
            deviceProperties.type = ZE_DEVICE_TYPE_GPU;
            #endif

            // Environment variable can override
            auto driver_type = getenv_string( "ZEL_TEST_NULL_DRIVER_TYPE" );
            if (std::strcmp(driver_type.c_str(), "NPU") == 0) {
                deviceProperties.type = ZE_DEVICE_TYPE_VPU;
            } else if (std::strcmp(driver_type.c_str(), "GPU") == 0) {
                deviceProperties.type = ZE_DEVICE_TYPE_GPU;
            }
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

            char *env_str = context.setenv_var_with_driver_id("zeDeviceGetCommandQueueGroupProperties", ZEL_NULL_DRIVER_ID);
            context.env_vars.push_back(env_str);

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

            char *env_str = context.setenv_var_with_driver_id("zeDeviceGetMemoryProperties", ZEL_NULL_DRIVER_ID);
            context.env_vars.push_back(env_str);

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
            
            char *env_str = context.setenv_var_with_driver_id("zeDeviceGetMemoryAccessProperties", ZEL_NULL_DRIVER_ID);
            context.env_vars.push_back(env_str);

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
                ze_driver_extension_properties_t tracingExtension = {};
#if defined(_WIN32)
                strcpy_s( tracingExtension.name, ZET_API_TRACING_EXP_NAME );
#else
                strcpy( tracingExtension.name, ZET_API_TRACING_EXP_NAME );
#endif
                tracingExtension.version = ZET_API_TRACING_EXP_VERSION_1_0;
                pExtensionProperties[0] = tracingExtension;
                
                ze_driver_extension_properties_t ddiHandlesExtension = {};
#if defined(_WIN32)
                strcpy_s( ddiHandlesExtension.name, ZE_DRIVER_DDI_HANDLES_EXT_NAME );
#else
                strcpy( ddiHandlesExtension.name, ZE_DRIVER_DDI_HANDLES_EXT_NAME );
#endif

                auto ddi_version_env = getenv_string("ZEL_TEST_DDI_HANDLES_EXT_VERSION");
                if (!ddi_version_env.empty() && ddi_version_env == "1_0") {
                    ddiHandlesExtension.version = ZE_DRIVER_DDI_HANDLES_EXT_VERSION_1_0;
                } else {
                    ddiHandlesExtension.version = ZE_DRIVER_DDI_HANDLES_EXT_VERSION_1_1;
                }
                
                pExtensionProperties[1] = ddiHandlesExtension;
            }
            *pCount = 2;

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
        pCore.Driver = &zeDdiTable.Driver;
        pCore.Device = &zeDdiTable.Device;
        pCore.Mem = &zeDdiTable.Mem;
        pCore.CommandList = &zeDdiTable.CommandList;
        pCore.CommandQueue = &zeDdiTable.CommandQueue;
        pCore.Context = &zeDdiTable.Context;
        pCore.Event = &zeDdiTable.Event;
        pCore.EventPool = &zeDdiTable.EventPool;
        pCore.Module = &zeDdiTable.Module;
        pCore.ModuleBuildLog = &zeDdiTable.ModuleBuildLog;
        pCore.PhysicalMem = &zeDdiTable.PhysicalMem;
        pCore.Kernel = &zeDdiTable.Kernel;
        pCore.Fence = &zeDdiTable.Fence;
        pCore.Image = &zeDdiTable.Image;
        pCore.Sampler = &zeDdiTable.Sampler;
        pCore.isValidFlag = 1;
        pCore.version = ZE_API_VERSION_CURRENT;
        pTools.MetricGroup = &zetDdiTable.MetricGroup;
        pTools.Metric = &zetDdiTable.Metric;
        pTools.MetricQuery = &zetDdiTable.MetricQuery;
        pTools.MetricStreamer = &zetDdiTable.MetricStreamer;
        pTools.isValidFlag = 1;
        pTools.version = ZE_API_VERSION_CURRENT;
        pSysman.Driver = &zesDdiTable.Driver;
        pSysman.isValidFlag = 1;
        pSysman.version = ZE_API_VERSION_CURRENT;

        static zer_global_dditable_t runtimeDdiTable;
        runtimeDdiTable.pfnGetLastErrorDescription = driver::zerGetLastErrorDescription;
        runtimeDdiTable.pfnTranslateDeviceHandleToIdentifier = driver::zerTranslateDeviceHandleToIdentifier;
        runtimeDdiTable.pfnTranslateIdentifierToDeviceHandle = driver::zerTranslateIdentifierToDeviceHandle;
        runtimeDdiTable.pfnGetDefaultContext = driver::zerGetDefaultContext;

        pRuntime.Global = &runtimeDdiTable;
        pRuntime.isValidFlag = 1;
        pRuntime.version = ZE_API_VERSION_CURRENT;
    }

    char *context_t::setenv_var_with_driver_id(const std::string &key, uint32_t driverId)
    {
        std::string env = key + "=" + std::to_string(driverId);
        char *env_str = strdup_safe(env.c_str());
        putenv_safe(env_str);
        return env_str;
    }

    context_t::~context_t()
    {
        for (auto handle : globalBaseNullHandle)
        {
            delete handle;
        }

        for (const auto &env_var : env_vars)
        {
            free(env_var);
        }
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
