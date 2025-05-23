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
#ifndef L0_STATIC_LOADER_BUILD
#include "zes_ddi.h"
#endif

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////

#ifdef L0_STATIC_LOADER_BUILD
    __zedlllocal ze_result_t context_t::zesDdiTableInit(ze_api_version_t version)
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zes_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetGlobalProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzesDdiTable.Global );
            initialzesDdiTable.Global.pfnInit = reinterpret_cast<zes_pfnInit_t>(
                GET_FUNCTION_PTR(loader, "zesInit") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetDeviceProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Device );
            initialzesDdiTable.Device.pfnGetProperties = reinterpret_cast<zes_pfnDeviceGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceGetProperties") );
            initialzesDdiTable.Device.pfnGetState = reinterpret_cast<zes_pfnDeviceGetState_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceGetState") );
            initialzesDdiTable.Device.pfnReset = reinterpret_cast<zes_pfnDeviceReset_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceReset") );
            initialzesDdiTable.Device.pfnProcessesGetState = reinterpret_cast<zes_pfnDeviceProcessesGetState_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceProcessesGetState") );
            initialzesDdiTable.Device.pfnPciGetProperties = reinterpret_cast<zes_pfnDevicePciGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesDevicePciGetProperties") );
            initialzesDdiTable.Device.pfnPciGetState = reinterpret_cast<zes_pfnDevicePciGetState_t>(
                GET_FUNCTION_PTR(loader, "zesDevicePciGetState") );
            initialzesDdiTable.Device.pfnPciGetBars = reinterpret_cast<zes_pfnDevicePciGetBars_t>(
                GET_FUNCTION_PTR(loader, "zesDevicePciGetBars") );
            initialzesDdiTable.Device.pfnPciGetStats = reinterpret_cast<zes_pfnDevicePciGetStats_t>(
                GET_FUNCTION_PTR(loader, "zesDevicePciGetStats") );
            initialzesDdiTable.Device.pfnEnumDiagnosticTestSuites = reinterpret_cast<zes_pfnDeviceEnumDiagnosticTestSuites_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumDiagnosticTestSuites") );
            initialzesDdiTable.Device.pfnEnumEngineGroups = reinterpret_cast<zes_pfnDeviceEnumEngineGroups_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumEngineGroups") );
            initialzesDdiTable.Device.pfnEventRegister = reinterpret_cast<zes_pfnDeviceEventRegister_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEventRegister") );
            initialzesDdiTable.Device.pfnEnumFabricPorts = reinterpret_cast<zes_pfnDeviceEnumFabricPorts_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumFabricPorts") );
            initialzesDdiTable.Device.pfnEnumFans = reinterpret_cast<zes_pfnDeviceEnumFans_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumFans") );
            initialzesDdiTable.Device.pfnEnumFirmwares = reinterpret_cast<zes_pfnDeviceEnumFirmwares_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumFirmwares") );
            initialzesDdiTable.Device.pfnEnumFrequencyDomains = reinterpret_cast<zes_pfnDeviceEnumFrequencyDomains_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumFrequencyDomains") );
            initialzesDdiTable.Device.pfnEnumLeds = reinterpret_cast<zes_pfnDeviceEnumLeds_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumLeds") );
            initialzesDdiTable.Device.pfnEnumMemoryModules = reinterpret_cast<zes_pfnDeviceEnumMemoryModules_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumMemoryModules") );
            initialzesDdiTable.Device.pfnEnumPerformanceFactorDomains = reinterpret_cast<zes_pfnDeviceEnumPerformanceFactorDomains_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumPerformanceFactorDomains") );
            initialzesDdiTable.Device.pfnEnumPowerDomains = reinterpret_cast<zes_pfnDeviceEnumPowerDomains_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumPowerDomains") );
            initialzesDdiTable.Device.pfnGetCardPowerDomain = reinterpret_cast<zes_pfnDeviceGetCardPowerDomain_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceGetCardPowerDomain") );
            initialzesDdiTable.Device.pfnEnumPsus = reinterpret_cast<zes_pfnDeviceEnumPsus_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumPsus") );
            initialzesDdiTable.Device.pfnEnumRasErrorSets = reinterpret_cast<zes_pfnDeviceEnumRasErrorSets_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumRasErrorSets") );
            initialzesDdiTable.Device.pfnEnumSchedulers = reinterpret_cast<zes_pfnDeviceEnumSchedulers_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumSchedulers") );
            initialzesDdiTable.Device.pfnEnumStandbyDomains = reinterpret_cast<zes_pfnDeviceEnumStandbyDomains_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumStandbyDomains") );
            initialzesDdiTable.Device.pfnEnumTemperatureSensors = reinterpret_cast<zes_pfnDeviceEnumTemperatureSensors_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumTemperatureSensors") );
            initialzesDdiTable.Device.pfnEccAvailable = reinterpret_cast<zes_pfnDeviceEccAvailable_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEccAvailable") );
            initialzesDdiTable.Device.pfnEccConfigurable = reinterpret_cast<zes_pfnDeviceEccConfigurable_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEccConfigurable") );
            initialzesDdiTable.Device.pfnGetEccState = reinterpret_cast<zes_pfnDeviceGetEccState_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceGetEccState") );
            initialzesDdiTable.Device.pfnSetEccState = reinterpret_cast<zes_pfnDeviceSetEccState_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceSetEccState") );
            initialzesDdiTable.Device.pfnGet = reinterpret_cast<zes_pfnDeviceGet_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceGet") );
            initialzesDdiTable.Device.pfnSetOverclockWaiver = reinterpret_cast<zes_pfnDeviceSetOverclockWaiver_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceSetOverclockWaiver") );
            initialzesDdiTable.Device.pfnGetOverclockDomains = reinterpret_cast<zes_pfnDeviceGetOverclockDomains_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceGetOverclockDomains") );
            initialzesDdiTable.Device.pfnGetOverclockControls = reinterpret_cast<zes_pfnDeviceGetOverclockControls_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceGetOverclockControls") );
            initialzesDdiTable.Device.pfnResetOverclockSettings = reinterpret_cast<zes_pfnDeviceResetOverclockSettings_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceResetOverclockSettings") );
            initialzesDdiTable.Device.pfnReadOverclockState = reinterpret_cast<zes_pfnDeviceReadOverclockState_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceReadOverclockState") );
            initialzesDdiTable.Device.pfnEnumOverclockDomains = reinterpret_cast<zes_pfnDeviceEnumOverclockDomains_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumOverclockDomains") );
            initialzesDdiTable.Device.pfnResetExt = reinterpret_cast<zes_pfnDeviceResetExt_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceResetExt") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zes_pfnGetDeviceExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetDeviceExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzesDdiTable.DeviceExp );
            initialzesDdiTable.DeviceExp.pfnEnumEnabledVFExp = reinterpret_cast<zes_pfnDeviceEnumEnabledVFExp_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumEnabledVFExp") );
            initialzesDdiTable.DeviceExp.pfnGetSubDevicePropertiesExp = reinterpret_cast<zes_pfnDeviceGetSubDevicePropertiesExp_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceGetSubDevicePropertiesExp") );
            initialzesDdiTable.DeviceExp.pfnEnumActiveVFExp = reinterpret_cast<zes_pfnDeviceEnumActiveVFExp_t>(
                GET_FUNCTION_PTR(loader, "zesDeviceEnumActiveVFExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetDriverProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetDriverProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Driver );
            initialzesDdiTable.Driver.pfnEventListen = reinterpret_cast<zes_pfnDriverEventListen_t>(
                GET_FUNCTION_PTR(loader, "zesDriverEventListen") );
            initialzesDdiTable.Driver.pfnEventListenEx = reinterpret_cast<zes_pfnDriverEventListenEx_t>(
                GET_FUNCTION_PTR(loader, "zesDriverEventListenEx") );
            initialzesDdiTable.Driver.pfnGet = reinterpret_cast<zes_pfnDriverGet_t>(
                GET_FUNCTION_PTR(loader, "zesDriverGet") );
            initialzesDdiTable.Driver.pfnGetExtensionProperties = reinterpret_cast<zes_pfnDriverGetExtensionProperties_t>(
                GET_FUNCTION_PTR(loader, "zesDriverGetExtensionProperties") );
            initialzesDdiTable.Driver.pfnGetExtensionFunctionAddress = reinterpret_cast<zes_pfnDriverGetExtensionFunctionAddress_t>(
                GET_FUNCTION_PTR(loader, "zesDriverGetExtensionFunctionAddress") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zes_pfnGetDriverExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetDriverExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzesDdiTable.DriverExp );
            initialzesDdiTable.DriverExp.pfnGetDeviceByUuidExp = reinterpret_cast<zes_pfnDriverGetDeviceByUuidExp_t>(
                GET_FUNCTION_PTR(loader, "zesDriverGetDeviceByUuidExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetDiagnosticsProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetDiagnosticsProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Diagnostics );
            initialzesDdiTable.Diagnostics.pfnGetProperties = reinterpret_cast<zes_pfnDiagnosticsGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesDiagnosticsGetProperties") );
            initialzesDdiTable.Diagnostics.pfnGetTests = reinterpret_cast<zes_pfnDiagnosticsGetTests_t>(
                GET_FUNCTION_PTR(loader, "zesDiagnosticsGetTests") );
            initialzesDdiTable.Diagnostics.pfnRunTests = reinterpret_cast<zes_pfnDiagnosticsRunTests_t>(
                GET_FUNCTION_PTR(loader, "zesDiagnosticsRunTests") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetEngineProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetEngineProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Engine );
            initialzesDdiTable.Engine.pfnGetProperties = reinterpret_cast<zes_pfnEngineGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesEngineGetProperties") );
            initialzesDdiTable.Engine.pfnGetActivity = reinterpret_cast<zes_pfnEngineGetActivity_t>(
                GET_FUNCTION_PTR(loader, "zesEngineGetActivity") );
            initialzesDdiTable.Engine.pfnGetActivityExt = reinterpret_cast<zes_pfnEngineGetActivityExt_t>(
                GET_FUNCTION_PTR(loader, "zesEngineGetActivityExt") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetFabricPortProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetFabricPortProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.FabricPort );
            initialzesDdiTable.FabricPort.pfnGetProperties = reinterpret_cast<zes_pfnFabricPortGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesFabricPortGetProperties") );
            initialzesDdiTable.FabricPort.pfnGetLinkType = reinterpret_cast<zes_pfnFabricPortGetLinkType_t>(
                GET_FUNCTION_PTR(loader, "zesFabricPortGetLinkType") );
            initialzesDdiTable.FabricPort.pfnGetConfig = reinterpret_cast<zes_pfnFabricPortGetConfig_t>(
                GET_FUNCTION_PTR(loader, "zesFabricPortGetConfig") );
            initialzesDdiTable.FabricPort.pfnSetConfig = reinterpret_cast<zes_pfnFabricPortSetConfig_t>(
                GET_FUNCTION_PTR(loader, "zesFabricPortSetConfig") );
            initialzesDdiTable.FabricPort.pfnGetState = reinterpret_cast<zes_pfnFabricPortGetState_t>(
                GET_FUNCTION_PTR(loader, "zesFabricPortGetState") );
            initialzesDdiTable.FabricPort.pfnGetThroughput = reinterpret_cast<zes_pfnFabricPortGetThroughput_t>(
                GET_FUNCTION_PTR(loader, "zesFabricPortGetThroughput") );
            initialzesDdiTable.FabricPort.pfnGetFabricErrorCounters = reinterpret_cast<zes_pfnFabricPortGetFabricErrorCounters_t>(
                GET_FUNCTION_PTR(loader, "zesFabricPortGetFabricErrorCounters") );
            initialzesDdiTable.FabricPort.pfnGetMultiPortThroughput = reinterpret_cast<zes_pfnFabricPortGetMultiPortThroughput_t>(
                GET_FUNCTION_PTR(loader, "zesFabricPortGetMultiPortThroughput") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetFanProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetFanProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Fan );
            initialzesDdiTable.Fan.pfnGetProperties = reinterpret_cast<zes_pfnFanGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesFanGetProperties") );
            initialzesDdiTable.Fan.pfnGetConfig = reinterpret_cast<zes_pfnFanGetConfig_t>(
                GET_FUNCTION_PTR(loader, "zesFanGetConfig") );
            initialzesDdiTable.Fan.pfnSetDefaultMode = reinterpret_cast<zes_pfnFanSetDefaultMode_t>(
                GET_FUNCTION_PTR(loader, "zesFanSetDefaultMode") );
            initialzesDdiTable.Fan.pfnSetFixedSpeedMode = reinterpret_cast<zes_pfnFanSetFixedSpeedMode_t>(
                GET_FUNCTION_PTR(loader, "zesFanSetFixedSpeedMode") );
            initialzesDdiTable.Fan.pfnSetSpeedTableMode = reinterpret_cast<zes_pfnFanSetSpeedTableMode_t>(
                GET_FUNCTION_PTR(loader, "zesFanSetSpeedTableMode") );
            initialzesDdiTable.Fan.pfnGetState = reinterpret_cast<zes_pfnFanGetState_t>(
                GET_FUNCTION_PTR(loader, "zesFanGetState") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetFirmwareProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetFirmwareProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Firmware );
            initialzesDdiTable.Firmware.pfnGetProperties = reinterpret_cast<zes_pfnFirmwareGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesFirmwareGetProperties") );
            initialzesDdiTable.Firmware.pfnFlash = reinterpret_cast<zes_pfnFirmwareFlash_t>(
                GET_FUNCTION_PTR(loader, "zesFirmwareFlash") );
            initialzesDdiTable.Firmware.pfnGetFlashProgress = reinterpret_cast<zes_pfnFirmwareGetFlashProgress_t>(
                GET_FUNCTION_PTR(loader, "zesFirmwareGetFlashProgress") );
            initialzesDdiTable.Firmware.pfnGetConsoleLogs = reinterpret_cast<zes_pfnFirmwareGetConsoleLogs_t>(
                GET_FUNCTION_PTR(loader, "zesFirmwareGetConsoleLogs") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zes_pfnGetFirmwareExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetFirmwareExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzesDdiTable.FirmwareExp );
            initialzesDdiTable.FirmwareExp.pfnGetSecurityVersionExp = reinterpret_cast<zes_pfnFirmwareGetSecurityVersionExp_t>(
                GET_FUNCTION_PTR(loader, "zesFirmwareGetSecurityVersionExp") );
            initialzesDdiTable.FirmwareExp.pfnSetSecurityVersionExp = reinterpret_cast<zes_pfnFirmwareSetSecurityVersionExp_t>(
                GET_FUNCTION_PTR(loader, "zesFirmwareSetSecurityVersionExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetFrequencyProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetFrequencyProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Frequency );
            initialzesDdiTable.Frequency.pfnGetProperties = reinterpret_cast<zes_pfnFrequencyGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyGetProperties") );
            initialzesDdiTable.Frequency.pfnGetAvailableClocks = reinterpret_cast<zes_pfnFrequencyGetAvailableClocks_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyGetAvailableClocks") );
            initialzesDdiTable.Frequency.pfnGetRange = reinterpret_cast<zes_pfnFrequencyGetRange_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyGetRange") );
            initialzesDdiTable.Frequency.pfnSetRange = reinterpret_cast<zes_pfnFrequencySetRange_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencySetRange") );
            initialzesDdiTable.Frequency.pfnGetState = reinterpret_cast<zes_pfnFrequencyGetState_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyGetState") );
            initialzesDdiTable.Frequency.pfnGetThrottleTime = reinterpret_cast<zes_pfnFrequencyGetThrottleTime_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyGetThrottleTime") );
            initialzesDdiTable.Frequency.pfnOcGetCapabilities = reinterpret_cast<zes_pfnFrequencyOcGetCapabilities_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyOcGetCapabilities") );
            initialzesDdiTable.Frequency.pfnOcGetFrequencyTarget = reinterpret_cast<zes_pfnFrequencyOcGetFrequencyTarget_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyOcGetFrequencyTarget") );
            initialzesDdiTable.Frequency.pfnOcSetFrequencyTarget = reinterpret_cast<zes_pfnFrequencyOcSetFrequencyTarget_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyOcSetFrequencyTarget") );
            initialzesDdiTable.Frequency.pfnOcGetVoltageTarget = reinterpret_cast<zes_pfnFrequencyOcGetVoltageTarget_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyOcGetVoltageTarget") );
            initialzesDdiTable.Frequency.pfnOcSetVoltageTarget = reinterpret_cast<zes_pfnFrequencyOcSetVoltageTarget_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyOcSetVoltageTarget") );
            initialzesDdiTable.Frequency.pfnOcSetMode = reinterpret_cast<zes_pfnFrequencyOcSetMode_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyOcSetMode") );
            initialzesDdiTable.Frequency.pfnOcGetMode = reinterpret_cast<zes_pfnFrequencyOcGetMode_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyOcGetMode") );
            initialzesDdiTable.Frequency.pfnOcGetIccMax = reinterpret_cast<zes_pfnFrequencyOcGetIccMax_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyOcGetIccMax") );
            initialzesDdiTable.Frequency.pfnOcSetIccMax = reinterpret_cast<zes_pfnFrequencyOcSetIccMax_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyOcSetIccMax") );
            initialzesDdiTable.Frequency.pfnOcGetTjMax = reinterpret_cast<zes_pfnFrequencyOcGetTjMax_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyOcGetTjMax") );
            initialzesDdiTable.Frequency.pfnOcSetTjMax = reinterpret_cast<zes_pfnFrequencyOcSetTjMax_t>(
                GET_FUNCTION_PTR(loader, "zesFrequencyOcSetTjMax") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetLedProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetLedProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Led );
            initialzesDdiTable.Led.pfnGetProperties = reinterpret_cast<zes_pfnLedGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesLedGetProperties") );
            initialzesDdiTable.Led.pfnGetState = reinterpret_cast<zes_pfnLedGetState_t>(
                GET_FUNCTION_PTR(loader, "zesLedGetState") );
            initialzesDdiTable.Led.pfnSetState = reinterpret_cast<zes_pfnLedSetState_t>(
                GET_FUNCTION_PTR(loader, "zesLedSetState") );
            initialzesDdiTable.Led.pfnSetColor = reinterpret_cast<zes_pfnLedSetColor_t>(
                GET_FUNCTION_PTR(loader, "zesLedSetColor") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetMemoryProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetMemoryProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Memory );
            initialzesDdiTable.Memory.pfnGetProperties = reinterpret_cast<zes_pfnMemoryGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesMemoryGetProperties") );
            initialzesDdiTable.Memory.pfnGetState = reinterpret_cast<zes_pfnMemoryGetState_t>(
                GET_FUNCTION_PTR(loader, "zesMemoryGetState") );
            initialzesDdiTable.Memory.pfnGetBandwidth = reinterpret_cast<zes_pfnMemoryGetBandwidth_t>(
                GET_FUNCTION_PTR(loader, "zesMemoryGetBandwidth") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zes_pfnGetOverclockProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetOverclockProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzesDdiTable.Overclock );
            initialzesDdiTable.Overclock.pfnGetDomainProperties = reinterpret_cast<zes_pfnOverclockGetDomainProperties_t>(
                GET_FUNCTION_PTR(loader, "zesOverclockGetDomainProperties") );
            initialzesDdiTable.Overclock.pfnGetDomainVFProperties = reinterpret_cast<zes_pfnOverclockGetDomainVFProperties_t>(
                GET_FUNCTION_PTR(loader, "zesOverclockGetDomainVFProperties") );
            initialzesDdiTable.Overclock.pfnGetDomainControlProperties = reinterpret_cast<zes_pfnOverclockGetDomainControlProperties_t>(
                GET_FUNCTION_PTR(loader, "zesOverclockGetDomainControlProperties") );
            initialzesDdiTable.Overclock.pfnGetControlCurrentValue = reinterpret_cast<zes_pfnOverclockGetControlCurrentValue_t>(
                GET_FUNCTION_PTR(loader, "zesOverclockGetControlCurrentValue") );
            initialzesDdiTable.Overclock.pfnGetControlPendingValue = reinterpret_cast<zes_pfnOverclockGetControlPendingValue_t>(
                GET_FUNCTION_PTR(loader, "zesOverclockGetControlPendingValue") );
            initialzesDdiTable.Overclock.pfnSetControlUserValue = reinterpret_cast<zes_pfnOverclockSetControlUserValue_t>(
                GET_FUNCTION_PTR(loader, "zesOverclockSetControlUserValue") );
            initialzesDdiTable.Overclock.pfnGetControlState = reinterpret_cast<zes_pfnOverclockGetControlState_t>(
                GET_FUNCTION_PTR(loader, "zesOverclockGetControlState") );
            initialzesDdiTable.Overclock.pfnGetVFPointValues = reinterpret_cast<zes_pfnOverclockGetVFPointValues_t>(
                GET_FUNCTION_PTR(loader, "zesOverclockGetVFPointValues") );
            initialzesDdiTable.Overclock.pfnSetVFPointValues = reinterpret_cast<zes_pfnOverclockSetVFPointValues_t>(
                GET_FUNCTION_PTR(loader, "zesOverclockSetVFPointValues") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetPerformanceFactorProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetPerformanceFactorProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.PerformanceFactor );
            initialzesDdiTable.PerformanceFactor.pfnGetProperties = reinterpret_cast<zes_pfnPerformanceFactorGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesPerformanceFactorGetProperties") );
            initialzesDdiTable.PerformanceFactor.pfnGetConfig = reinterpret_cast<zes_pfnPerformanceFactorGetConfig_t>(
                GET_FUNCTION_PTR(loader, "zesPerformanceFactorGetConfig") );
            initialzesDdiTable.PerformanceFactor.pfnSetConfig = reinterpret_cast<zes_pfnPerformanceFactorSetConfig_t>(
                GET_FUNCTION_PTR(loader, "zesPerformanceFactorSetConfig") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetPowerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetPowerProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Power );
            initialzesDdiTable.Power.pfnGetProperties = reinterpret_cast<zes_pfnPowerGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesPowerGetProperties") );
            initialzesDdiTable.Power.pfnGetEnergyCounter = reinterpret_cast<zes_pfnPowerGetEnergyCounter_t>(
                GET_FUNCTION_PTR(loader, "zesPowerGetEnergyCounter") );
            initialzesDdiTable.Power.pfnGetLimits = reinterpret_cast<zes_pfnPowerGetLimits_t>(
                GET_FUNCTION_PTR(loader, "zesPowerGetLimits") );
            initialzesDdiTable.Power.pfnSetLimits = reinterpret_cast<zes_pfnPowerSetLimits_t>(
                GET_FUNCTION_PTR(loader, "zesPowerSetLimits") );
            initialzesDdiTable.Power.pfnGetEnergyThreshold = reinterpret_cast<zes_pfnPowerGetEnergyThreshold_t>(
                GET_FUNCTION_PTR(loader, "zesPowerGetEnergyThreshold") );
            initialzesDdiTable.Power.pfnSetEnergyThreshold = reinterpret_cast<zes_pfnPowerSetEnergyThreshold_t>(
                GET_FUNCTION_PTR(loader, "zesPowerSetEnergyThreshold") );
            initialzesDdiTable.Power.pfnGetLimitsExt = reinterpret_cast<zes_pfnPowerGetLimitsExt_t>(
                GET_FUNCTION_PTR(loader, "zesPowerGetLimitsExt") );
            initialzesDdiTable.Power.pfnSetLimitsExt = reinterpret_cast<zes_pfnPowerSetLimitsExt_t>(
                GET_FUNCTION_PTR(loader, "zesPowerSetLimitsExt") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetPsuProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetPsuProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Psu );
            initialzesDdiTable.Psu.pfnGetProperties = reinterpret_cast<zes_pfnPsuGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesPsuGetProperties") );
            initialzesDdiTable.Psu.pfnGetState = reinterpret_cast<zes_pfnPsuGetState_t>(
                GET_FUNCTION_PTR(loader, "zesPsuGetState") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetRasProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetRasProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Ras );
            initialzesDdiTable.Ras.pfnGetProperties = reinterpret_cast<zes_pfnRasGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesRasGetProperties") );
            initialzesDdiTable.Ras.pfnGetConfig = reinterpret_cast<zes_pfnRasGetConfig_t>(
                GET_FUNCTION_PTR(loader, "zesRasGetConfig") );
            initialzesDdiTable.Ras.pfnSetConfig = reinterpret_cast<zes_pfnRasSetConfig_t>(
                GET_FUNCTION_PTR(loader, "zesRasSetConfig") );
            initialzesDdiTable.Ras.pfnGetState = reinterpret_cast<zes_pfnRasGetState_t>(
                GET_FUNCTION_PTR(loader, "zesRasGetState") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zes_pfnGetRasExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetRasExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzesDdiTable.RasExp );
            initialzesDdiTable.RasExp.pfnGetStateExp = reinterpret_cast<zes_pfnRasGetStateExp_t>(
                GET_FUNCTION_PTR(loader, "zesRasGetStateExp") );
            initialzesDdiTable.RasExp.pfnClearStateExp = reinterpret_cast<zes_pfnRasClearStateExp_t>(
                GET_FUNCTION_PTR(loader, "zesRasClearStateExp") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetSchedulerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetSchedulerProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Scheduler );
            initialzesDdiTable.Scheduler.pfnGetProperties = reinterpret_cast<zes_pfnSchedulerGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesSchedulerGetProperties") );
            initialzesDdiTable.Scheduler.pfnGetCurrentMode = reinterpret_cast<zes_pfnSchedulerGetCurrentMode_t>(
                GET_FUNCTION_PTR(loader, "zesSchedulerGetCurrentMode") );
            initialzesDdiTable.Scheduler.pfnGetTimeoutModeProperties = reinterpret_cast<zes_pfnSchedulerGetTimeoutModeProperties_t>(
                GET_FUNCTION_PTR(loader, "zesSchedulerGetTimeoutModeProperties") );
            initialzesDdiTable.Scheduler.pfnGetTimesliceModeProperties = reinterpret_cast<zes_pfnSchedulerGetTimesliceModeProperties_t>(
                GET_FUNCTION_PTR(loader, "zesSchedulerGetTimesliceModeProperties") );
            initialzesDdiTable.Scheduler.pfnSetTimeoutMode = reinterpret_cast<zes_pfnSchedulerSetTimeoutMode_t>(
                GET_FUNCTION_PTR(loader, "zesSchedulerSetTimeoutMode") );
            initialzesDdiTable.Scheduler.pfnSetTimesliceMode = reinterpret_cast<zes_pfnSchedulerSetTimesliceMode_t>(
                GET_FUNCTION_PTR(loader, "zesSchedulerSetTimesliceMode") );
            initialzesDdiTable.Scheduler.pfnSetExclusiveMode = reinterpret_cast<zes_pfnSchedulerSetExclusiveMode_t>(
                GET_FUNCTION_PTR(loader, "zesSchedulerSetExclusiveMode") );
            initialzesDdiTable.Scheduler.pfnSetComputeUnitDebugMode = reinterpret_cast<zes_pfnSchedulerSetComputeUnitDebugMode_t>(
                GET_FUNCTION_PTR(loader, "zesSchedulerSetComputeUnitDebugMode") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetStandbyProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetStandbyProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Standby );
            initialzesDdiTable.Standby.pfnGetProperties = reinterpret_cast<zes_pfnStandbyGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesStandbyGetProperties") );
            initialzesDdiTable.Standby.pfnGetMode = reinterpret_cast<zes_pfnStandbyGetMode_t>(
                GET_FUNCTION_PTR(loader, "zesStandbyGetMode") );
            initialzesDdiTable.Standby.pfnSetMode = reinterpret_cast<zes_pfnStandbySetMode_t>(
                GET_FUNCTION_PTR(loader, "zesStandbySetMode") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zes_pfnGetTemperatureProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetTemperatureProcAddrTable") );
            result = getTableWithCheck(getTable, version, &initialzesDdiTable.Temperature );
            initialzesDdiTable.Temperature.pfnGetProperties = reinterpret_cast<zes_pfnTemperatureGetProperties_t>(
                GET_FUNCTION_PTR(loader, "zesTemperatureGetProperties") );
            initialzesDdiTable.Temperature.pfnGetConfig = reinterpret_cast<zes_pfnTemperatureGetConfig_t>(
                GET_FUNCTION_PTR(loader, "zesTemperatureGetConfig") );
            initialzesDdiTable.Temperature.pfnSetConfig = reinterpret_cast<zes_pfnTemperatureSetConfig_t>(
                GET_FUNCTION_PTR(loader, "zesTemperatureSetConfig") );
            initialzesDdiTable.Temperature.pfnGetState = reinterpret_cast<zes_pfnTemperatureGetState_t>(
                GET_FUNCTION_PTR(loader, "zesTemperatureGetState") );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zes_pfnGetVFManagementExpProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zesGetVFManagementExpProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzesDdiTable.VFManagementExp );
            initialzesDdiTable.VFManagementExp.pfnGetVFCapabilitiesExp = reinterpret_cast<zes_pfnVFManagementGetVFCapabilitiesExp_t>(
                GET_FUNCTION_PTR(loader, "zesVFManagementGetVFCapabilitiesExp") );
            initialzesDdiTable.VFManagementExp.pfnGetVFMemoryUtilizationExp2 = reinterpret_cast<zes_pfnVFManagementGetVFMemoryUtilizationExp2_t>(
                GET_FUNCTION_PTR(loader, "zesVFManagementGetVFMemoryUtilizationExp2") );
            initialzesDdiTable.VFManagementExp.pfnGetVFEngineUtilizationExp2 = reinterpret_cast<zes_pfnVFManagementGetVFEngineUtilizationExp2_t>(
                GET_FUNCTION_PTR(loader, "zesVFManagementGetVFEngineUtilizationExp2") );
            initialzesDdiTable.VFManagementExp.pfnGetVFCapabilitiesExp2 = reinterpret_cast<zes_pfnVFManagementGetVFCapabilitiesExp2_t>(
                GET_FUNCTION_PTR(loader, "zesVFManagementGetVFCapabilitiesExp2") );
            initialzesDdiTable.VFManagementExp.pfnGetVFPropertiesExp = reinterpret_cast<zes_pfnVFManagementGetVFPropertiesExp_t>(
                GET_FUNCTION_PTR(loader, "zesVFManagementGetVFPropertiesExp") );
            initialzesDdiTable.VFManagementExp.pfnGetVFMemoryUtilizationExp = reinterpret_cast<zes_pfnVFManagementGetVFMemoryUtilizationExp_t>(
                GET_FUNCTION_PTR(loader, "zesVFManagementGetVFMemoryUtilizationExp") );
            initialzesDdiTable.VFManagementExp.pfnGetVFEngineUtilizationExp = reinterpret_cast<zes_pfnVFManagementGetVFEngineUtilizationExp_t>(
                GET_FUNCTION_PTR(loader, "zesVFManagementGetVFEngineUtilizationExp") );
            initialzesDdiTable.VFManagementExp.pfnSetVFTelemetryModeExp = reinterpret_cast<zes_pfnVFManagementSetVFTelemetryModeExp_t>(
                GET_FUNCTION_PTR(loader, "zesVFManagementSetVFTelemetryModeExp") );
            initialzesDdiTable.VFManagementExp.pfnSetVFTelemetrySamplingIntervalExp = reinterpret_cast<zes_pfnVFManagementSetVFTelemetrySamplingIntervalExp_t>(
                GET_FUNCTION_PTR(loader, "zesVFManagementSetVFTelemetrySamplingIntervalExp") );
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
            zesGetGlobalProcAddrTable( version, &initialzesDdiTable.Global );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetDeviceProcAddrTable( version, &initialzesDdiTable.Device );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zesGetDeviceExpProcAddrTable( version, &initialzesDdiTable.DeviceExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetDriverProcAddrTable( version, &initialzesDdiTable.Driver );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zesGetDriverExpProcAddrTable( version, &initialzesDdiTable.DriverExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetDiagnosticsProcAddrTable( version, &initialzesDdiTable.Diagnostics );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetEngineProcAddrTable( version, &initialzesDdiTable.Engine );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetFabricPortProcAddrTable( version, &initialzesDdiTable.FabricPort );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetFanProcAddrTable( version, &initialzesDdiTable.Fan );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetFirmwareProcAddrTable( version, &initialzesDdiTable.Firmware );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zesGetFirmwareExpProcAddrTable( version, &initialzesDdiTable.FirmwareExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetFrequencyProcAddrTable( version, &initialzesDdiTable.Frequency );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetLedProcAddrTable( version, &initialzesDdiTable.Led );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetMemoryProcAddrTable( version, &initialzesDdiTable.Memory );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zesGetOverclockProcAddrTable( version, &initialzesDdiTable.Overclock );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetPerformanceFactorProcAddrTable( version, &initialzesDdiTable.PerformanceFactor );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetPowerProcAddrTable( version, &initialzesDdiTable.Power );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetPsuProcAddrTable( version, &initialzesDdiTable.Psu );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetRasProcAddrTable( version, &initialzesDdiTable.Ras );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zesGetRasExpProcAddrTable( version, &initialzesDdiTable.RasExp );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetSchedulerProcAddrTable( version, &initialzesDdiTable.Scheduler );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetStandbyProcAddrTable( version, &initialzesDdiTable.Standby );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesGetTemperatureProcAddrTable( version, &initialzesDdiTable.Temperature );
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zesGetVFManagementExpProcAddrTable( version, &initialzesDdiTable.VFManagementExp );
        }

        return result;
    }
#endif

} // namespace ze_lib
