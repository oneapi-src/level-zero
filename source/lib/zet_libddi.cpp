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
    __zedlllocal ze_result_t context_t::zetDdiTableInit(ze_api_version_t version)
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zet_pfnGetMetricDecoderExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricDecoderExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzetDdiTable.MetricDecoderExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zet_pfnGetMetricProgrammableExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricProgrammableExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzetDdiTable.MetricProgrammableExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zet_pfnGetMetricTracerExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricTracerExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzetDdiTable.MetricTracerExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetDeviceProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zet_pfnGetDeviceExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetDeviceExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzetDdiTable.DeviceExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetContextProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetContextProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.Context );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetCommandListProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetKernelProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetKernelProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.Kernel );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetModuleProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.Module );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetDebugProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetDebugProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.Debug );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.Metric );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zet_pfnGetMetricExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzetDdiTable.MetricExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricGroupProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricGroupProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.MetricGroup );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zet_pfnGetMetricGroupExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricGroupExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzetDdiTable.MetricGroupExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricQueryProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricQueryProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.MetricQuery );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricQueryPoolProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricQueryPoolProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.MetricQueryPool );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricStreamerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricStreamerProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.MetricStreamer );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetTracerExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetTracerExpProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzetDdiTable.TracerExp );
        }

        return result;
    }
#else
    __zedlllocal ze_result_t context_t::zetDdiTableInit(ze_api_version_t version)
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zetGetMetricDecoderExpProcAddrTable( version, &initialzetDdiTable.MetricDecoderExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zetGetMetricProgrammableExpProcAddrTable( version, &initialzetDdiTable.MetricProgrammableExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zetGetMetricTracerExpProcAddrTable( version, &initialzetDdiTable.MetricTracerExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetDeviceProcAddrTable( version, &initialzetDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zetGetDeviceExpProcAddrTable( version, &initialzetDdiTable.DeviceExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetContextProcAddrTable( version, &initialzetDdiTable.Context );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetCommandListProcAddrTable( version, &initialzetDdiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetKernelProcAddrTable( version, &initialzetDdiTable.Kernel );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetModuleProcAddrTable( version, &initialzetDdiTable.Module );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetDebugProcAddrTable( version, &initialzetDdiTable.Debug );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricProcAddrTable( version, &initialzetDdiTable.Metric );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zetGetMetricExpProcAddrTable( version, &initialzetDdiTable.MetricExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricGroupProcAddrTable( version, &initialzetDdiTable.MetricGroup );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zetGetMetricGroupExpProcAddrTable( version, &initialzetDdiTable.MetricGroupExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricQueryProcAddrTable( version, &initialzetDdiTable.MetricQuery );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricQueryPoolProcAddrTable( version, &initialzetDdiTable.MetricQueryPool );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricStreamerProcAddrTable( version, &initialzetDdiTable.MetricStreamer );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetTracerExpProcAddrTable( version, &initialzetDdiTable.TracerExp );
        }

        return result;
    }
#endif

} // namespace ze_lib
