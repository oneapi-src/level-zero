/*
 *
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_libddi.cpp
 *
 */
#include "ze_lib.h"
#ifndef DYNAMIC_LOAD_LOADER
#include "ze_ddi.h"
#endif

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////

#ifdef DYNAMIC_LOAD_LOADER
    __zedlllocal ze_result_t context_t::zeDdiTableInit(ze_api_version_t version)
    {
        ze_result_t result = ZE_RESULT_SUCCESS;
        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetGlobalProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Global );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetRTASBuilderExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetRTASBuilderExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.RTASBuilderExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetRTASParallelOperationExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetRTASParallelOperationExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.RTASParallelOperationExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetDriverProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetDriverProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Driver );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetDriverExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetDriverExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.DriverExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetDeviceProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetDeviceExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetDeviceExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.DeviceExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetContextProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetContextProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Context );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetCommandQueueProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetCommandQueueProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.CommandQueue );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetCommandListProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetCommandListExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetCommandListExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.CommandListExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetEventProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetEventProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Event );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetEventExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetEventExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.EventExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetEventPoolProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetEventPoolProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.EventPool );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetFenceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetFenceProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Fence );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetImageProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetImageProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Image );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetImageExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetImageExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.ImageExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetKernelProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetKernelProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Kernel );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetKernelExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetKernelExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.KernelExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetMemProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetMemProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Mem );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetMemExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetMemExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.MemExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetModuleProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Module );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetModuleBuildLogProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetModuleBuildLogProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.ModuleBuildLog );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetPhysicalMemProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetPhysicalMemProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.PhysicalMem );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetSamplerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetSamplerProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.Sampler );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetVirtualMemProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetVirtualMemProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzeDdiTable.VirtualMem );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetFabricEdgeExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetFabricEdgeExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.FabricEdgeExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<ze_pfnGetFabricVertexExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetFabricVertexExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzeDdiTable.FabricVertexExp );
        }

        return result;
    }
#else
    __zedlllocal ze_result_t context_t::zeDdiTableInit(ze_api_version_t version)
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetGlobalProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Global );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetRTASBuilderExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.RTASBuilderExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetRTASParallelOperationExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.RTASParallelOperationExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetDriverProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Driver );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetDriverExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.DriverExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetDeviceProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetDeviceExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.DeviceExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetContextProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Context );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetCommandQueueProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.CommandQueue );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetCommandListProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetCommandListExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.CommandListExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetEventProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Event );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetEventExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.EventExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetEventPoolProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.EventPool );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetFenceProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Fence );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetImageProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Image );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetImageExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.ImageExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetKernelProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Kernel );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetKernelExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.KernelExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetMemProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Mem );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetMemExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.MemExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetModuleProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Module );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetModuleBuildLogProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.ModuleBuildLog );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetPhysicalMemProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.PhysicalMem );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetSamplerProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Sampler );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetVirtualMemProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.VirtualMem );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetFabricEdgeExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.FabricEdgeExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zeGetFabricVertexExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.FabricVertexExp );
        }

        return result;
    }
#endif

} // namespace ze_lib
