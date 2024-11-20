/*
 *
 * Copyright (C) 2019-2024 Intel Corporation
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
    __zedlllocal ze_result_t context_t::zesDdiTableInit(ze_api_version_t version)
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zes_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetGlobalProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzesDdiTable.Global );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetDeviceProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zes_pfnGetDeviceExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetDeviceExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzesDdiTable.DeviceExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetDriverProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetDriverProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Driver );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zes_pfnGetDriverExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetDriverExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzesDdiTable.DriverExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetDiagnosticsProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetDiagnosticsProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Diagnostics );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetEngineProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetEngineProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Engine );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetFabricPortProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetFabricPortProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.FabricPort );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetFanProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetFanProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Fan );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetFirmwareProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetFirmwareProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Firmware );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zes_pfnGetFirmwareExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetFirmwareExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzesDdiTable.FirmwareExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetFrequencyProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetFrequencyProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Frequency );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetLedProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetLedProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Led );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetMemoryProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetMemoryProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Memory );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zes_pfnGetOverclockProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetOverclockProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzesDdiTable.Overclock );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetPerformanceFactorProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetPerformanceFactorProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.PerformanceFactor );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetPowerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetPowerProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Power );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetPsuProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetPsuProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Psu );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetRasProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetRasProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Ras );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zes_pfnGetRasExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetRasExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzesDdiTable.RasExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSchedulerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSchedulerProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Scheduler );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetStandbyProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetStandbyProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Standby );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetTemperatureProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetTemperatureProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Temperature );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zes_pfnGetVFManagementExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetVFManagementExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzesDdiTable.VFManagementExp );
        }

        return result;
    }
#else
    __zedlllocal ze_result_t context_t::zesDdiTableInit(ze_api_version_t version)
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zesGetGlobalProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Global );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetDeviceProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zesGetDeviceExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.DeviceExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetDriverProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Driver );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zesGetDriverExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.DriverExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetDiagnosticsProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Diagnostics );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetEngineProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Engine );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetFabricPortProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.FabricPort );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetFanProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Fan );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetFirmwareProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Firmware );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zesGetFirmwareExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.FirmwareExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetFrequencyProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Frequency );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetLedProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Led );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetMemoryProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Memory );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zesGetOverclockProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Overclock );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetPerformanceFactorProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.PerformanceFactor );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetPowerProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Power );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetPsuProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Psu );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetRasProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Ras );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zesGetRasExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.RasExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetSchedulerProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Scheduler );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetStandbyProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Standby );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetTemperatureProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.Temperature );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zesGetVFManagementExpProcAddrTable( ZE_API_VERSION_CURRENT, &initialzesDdiTable.VFManagementExp );
        }

        return result;
    }
#endif

} // namespace ze_lib
