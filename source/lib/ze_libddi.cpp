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
    __zedlllocal ze_result_t context_t::zeDdiTableInit()
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetGlobalProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Global );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetRTASBuilderExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetRTASBuilderExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.RTASBuilderExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetRTASParallelOperationExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetRTASParallelOperationExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.RTASParallelOperationExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetDriverProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetDriverProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Driver );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetDriverExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetDriverExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.DriverExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetDeviceProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetDeviceExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetDeviceExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.DeviceExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetContextProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetContextProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Context );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetCommandQueueProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetCommandQueueProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.CommandQueue );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetCommandListProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetCommandListExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetCommandListExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.CommandListExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetEventProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetEventProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Event );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetEventExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetEventExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.EventExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetEventPoolProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetEventPoolProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.EventPool );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetFenceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetFenceProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Fence );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetImageProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetImageProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Image );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetImageExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetImageExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.ImageExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetKernelProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetKernelProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Kernel );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetKernelExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetKernelExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.KernelExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetMemProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetMemProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Mem );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetMemExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetMemExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.MemExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetModuleProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Module );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetModuleBuildLogProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetModuleBuildLogProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.ModuleBuildLog );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetPhysicalMemProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetPhysicalMemProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.PhysicalMem );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetSamplerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetSamplerProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Sampler );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetVirtualMemProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetVirtualMemProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.VirtualMem );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetFabricEdgeExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetFabricEdgeExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.FabricEdgeExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetFabricVertexExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetFabricVertexExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.FabricVertexExp );
        }

        return result;
    }
#else
    __zedlllocal ze_result_t context_t::zeDdiTableInit()
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetGlobalProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Global );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetRTASBuilderExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.RTASBuilderExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetRTASParallelOperationExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.RTASParallelOperationExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetDriverProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Driver );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetDriverExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.DriverExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetDeviceProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetDeviceExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.DeviceExp );
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
            result = zeGetCommandListExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.CommandListExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetEventProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Event );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetEventExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.EventExp );
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
            result = zeGetImageExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.ImageExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetKernelProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Kernel );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetKernelExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.KernelExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetMemProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.Mem );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetMemExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.MemExp );
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
            result = zeGetFabricEdgeExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.FabricEdgeExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeGetFabricVertexExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzeDdiTable.FabricVertexExp );
        }

        return result;
    }
#endif

} // namespace ze_lib
