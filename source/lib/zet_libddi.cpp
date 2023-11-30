/*
 *
 * Copyright (C) 2019-2022 Intel Corporation
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
    __zedlllocal ze_result_t context_t::zetInit()
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetDeviceProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &zetDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetContextProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetContextProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &zetDdiTable.Context );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetCommandListProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &zetDdiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetKernelProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetKernelProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &zetDdiTable.Kernel );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetModuleProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &zetDdiTable.Module );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetDebugProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetDebugProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &zetDdiTable.Debug );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &zetDdiTable.Metric );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricGroupProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricGroupProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &zetDdiTable.MetricGroup );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricGroupExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricGroupExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &zetDdiTable.MetricGroupExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricQueryProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricQueryProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &zetDdiTable.MetricQuery );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricQueryPoolProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricQueryPoolProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &zetDdiTable.MetricQueryPool );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricStreamerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricStreamerProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &zetDdiTable.MetricStreamer );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetTracerExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetTracerExpProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &zetDdiTable.TracerExp );
        }

        return result;
    }
#else
    __zedlllocal ze_result_t context_t::zetInit()
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetDeviceProcAddrTable( ZE_API_VERSION_CURRENT, &zetDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetContextProcAddrTable( ZE_API_VERSION_CURRENT, &zetDdiTable.Context );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetCommandListProcAddrTable( ZE_API_VERSION_CURRENT, &zetDdiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetKernelProcAddrTable( ZE_API_VERSION_CURRENT, &zetDdiTable.Kernel );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetModuleProcAddrTable( ZE_API_VERSION_CURRENT, &zetDdiTable.Module );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetDebugProcAddrTable( ZE_API_VERSION_CURRENT, &zetDdiTable.Debug );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricProcAddrTable( ZE_API_VERSION_CURRENT, &zetDdiTable.Metric );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricGroupProcAddrTable( ZE_API_VERSION_CURRENT, &zetDdiTable.MetricGroup );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricGroupExpProcAddrTable( ZE_API_VERSION_CURRENT, &zetDdiTable.MetricGroupExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricQueryProcAddrTable( ZE_API_VERSION_CURRENT, &zetDdiTable.MetricQuery );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricQueryPoolProcAddrTable( ZE_API_VERSION_CURRENT, &zetDdiTable.MetricQueryPool );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetMetricStreamerProcAddrTable( ZE_API_VERSION_CURRENT, &zetDdiTable.MetricStreamer );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetGetTracerExpProcAddrTable( ZE_API_VERSION_CURRENT, &zetDdiTable.TracerExp );
        }

        return result;
    }
#endif

} // namespace ze_lib
