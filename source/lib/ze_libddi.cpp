/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_libddi.cpp
 *
 */
#include "ze_lib.h"

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    __zedlllocal ze_result_t context_t::zeInit()
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetGlobalProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.Global );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetDriverProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetDriverProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.Driver );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetDeviceProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetContextProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetContextProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.Context );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetCommandQueueProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetCommandQueueProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.CommandQueue );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetCommandListProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetEventProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetEventProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.Event );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetEventPoolProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetEventPoolProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.EventPool );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetFenceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetFenceProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.Fence );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetImageProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetImageProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.Image );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetKernelProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetKernelProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.Kernel );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetMemProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetMemProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.Mem );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetModuleProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.Module );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetModuleBuildLogProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetModuleBuildLogProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.ModuleBuildLog );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetPhysicalMemProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetPhysicalMemProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.PhysicalMem );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetSamplerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetSamplerProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.Sampler );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<ze_pfnGetVirtualMemProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zeGetVirtualMemProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &zeDdiTable.VirtualMem );
        }

        return result;
    }
} // namespace ze_lib
