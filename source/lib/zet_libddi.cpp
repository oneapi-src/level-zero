/*
 *
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_libddi.cpp
 *
 */
#include "ze_lib.h"
#ifndef DYNAMIC_LOAD_LOADER
#include "zet_ddi.h"
#endif

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////

#ifdef DYNAMIC_LOAD_LOADER
    __zedlllocal ze_result_t context_t::zetDdiTableInit()
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricDecoderExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricDecoderExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricDecoderExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricProgrammableExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricProgrammableExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricProgrammableExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricTracerExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricTracerExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricTracerExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetDeviceProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetDeviceExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetDeviceExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.DeviceExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetContextProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetContextProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.Context );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetCommandListProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetKernelProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetKernelProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.Kernel );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetModuleProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.Module );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetDebugProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetDebugProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.Debug );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.Metric );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricGroupProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricGroupProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricGroup );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricGroupExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricGroupExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricGroupExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricQueryProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricQueryProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricQuery );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricQueryPoolProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricQueryPoolProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricQueryPool );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricStreamerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricStreamerProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricStreamer );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetTracerExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetTracerExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.TracerExp );
        }

        return result;
    }
#else
    __zedlllocal ze_result_t context_t::zetDdiTableInit()
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricDecoderExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricDecoderExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricProgrammableExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricProgrammableExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricTracerExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricTracerExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetDeviceProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetDeviceExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.DeviceExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetContextProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.Context );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetCommandListProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetKernelProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.Kernel );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetModuleProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.Module );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetDebugProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.Debug );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.Metric );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricGroupProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricGroup );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricGroupExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricGroupExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricQueryProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricQuery );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricQueryPoolProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricQueryPool );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricStreamerProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.MetricStreamer );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetTracerExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzetDdiTable.TracerExp );
        }

        return result;
    }
#endif

} // namespace ze_lib
