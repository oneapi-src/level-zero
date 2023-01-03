/*
 *
 * Copyright (C) 2019-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_libddi.cpp
 *
 */
#include "ze_lib.h"
#ifndef DYNAMIC_LOAD_LOADER
#include "zes_ddi.h"
#endif

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////

#ifdef DYNAMIC_LOAD_LOADER
    __zedlllocal ze_result_t context_t::zesInit()
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetGlobalProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Global );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetDeviceProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetDriverProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetDriverProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Driver );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetDiagnosticsProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetDiagnosticsProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Diagnostics );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetEngineProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetEngineProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Engine );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetFabricPortProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetFabricPortProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.FabricPort );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetFanProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetFanProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Fan );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetFirmwareProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetFirmwareProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Firmware );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetFrequencyProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetFrequencyProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Frequency );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetLedProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetLedProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Led );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetMemoryProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetMemoryProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Memory );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetOverclockProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetOverclockProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Overclock );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetPerformanceFactorProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetPerformanceFactorProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.PerformanceFactor );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetPowerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetPowerProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Power );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetPsuProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetPsuProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Psu );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetRasProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetRasProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Ras );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSchedulerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSchedulerProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Scheduler );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetStandbyProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetStandbyProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Standby );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetTemperatureProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetTemperatureProcAddrTable") );
            result = getTable( ZE_API_VERSION_1_5, &zesDdiTable.Temperature );
        }

        return result;
    }
#else
    __zedlllocal ze_result_t context_t::zesInit()
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetGlobalProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Global );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetDeviceProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetDriverProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Driver );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetDiagnosticsProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Diagnostics );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetEngineProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Engine );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetFabricPortProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.FabricPort );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetFanProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Fan );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetFirmwareProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Firmware );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetFrequencyProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Frequency );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetLedProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Led );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetMemoryProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Memory );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetOverclockProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Overclock );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetPerformanceFactorProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.PerformanceFactor );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetPowerProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Power );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetPsuProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Psu );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetRasProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Ras );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetSchedulerProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Scheduler );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetStandbyProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Standby );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetTemperatureProcAddrTable( ZE_API_VERSION_1_5, &zesDdiTable.Temperature );
        }

        return result;
    }
#endif

} // namespace ze_lib
