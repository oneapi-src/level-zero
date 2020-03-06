/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "zet_lib.h"

namespace zet_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    ze_result_t context_t::Init()
    {
        loader = LOAD_DRIVER_LIBRARY( MAKE_LIBRARY_NAME( "ze_loader", L0_LOADER_VERSION) );

        if( NULL == loader )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetGlobalProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.Global );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetDeviceProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetCommandListProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.CommandList );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetModuleProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.Module );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetKernelProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetKernelProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.Kernel );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricGroupProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricGroupProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.MetricGroup );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.Metric );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricTracerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricTracerProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.MetricTracer );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricQueryPoolProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricQueryPoolProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.MetricQueryPool );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetMetricQueryProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetMetricQueryProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.MetricQuery );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetTracerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetTracerProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.Tracer );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.Sysman );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanPowerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanPowerProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.SysmanPower );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanFrequencyProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanFrequencyProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.SysmanFrequency );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanEngineProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanEngineProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.SysmanEngine );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanStandbyProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanStandbyProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.SysmanStandby );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanFirmwareProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanFirmwareProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.SysmanFirmware );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanMemoryProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanMemoryProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.SysmanMemory );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanFabricPortProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanFabricPortProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.SysmanFabricPort );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanTemperatureProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanTemperatureProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.SysmanTemperature );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanPsuProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanPsuProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.SysmanPsu );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanFanProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanFanProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.SysmanFan );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanLedProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanLedProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.SysmanLed );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanRasProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanRasProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.SysmanRas );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanDiagnosticsProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanDiagnosticsProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.SysmanDiagnostics );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetSysmanEventProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetSysmanEventProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.SysmanEvent );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zet_pfnGetDebugProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zetGetDebugProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_0, &ddiTable.Debug );
        }

        return result;
    }
} // namespace zet_lib
