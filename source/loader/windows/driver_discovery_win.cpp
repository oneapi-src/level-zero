/*
 *
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "source/loader/driver_discovery.h"

#include <windows.h>

#include <cassert>
#include <cfgmgr32.h>
#include <devpkey.h>
#include <devguid.h>
#include <iostream>
#include <sstream>
#include <string>

namespace loader {

std::vector<DriverLibraryPath> discoverDriversBasedOnDisplayAdapters(const GUID rguid);

std::vector<DriverLibraryPath> discoverEnabledDrivers() {

    std::vector<DriverLibraryPath> enabledDrivers;

    DWORD envBufferSize = 65535;
    std::string altDrivers;
    altDrivers.resize(envBufferSize);

    // ZE_ENABLE_ALT_DRIVERS is for development/debug only
    envBufferSize = GetEnvironmentVariable("ZE_ENABLE_ALT_DRIVERS", &altDrivers[0], envBufferSize);
    if (!envBufferSize) {
        // Standard drivers discovered from registry - not custom
        auto displayDrivers = discoverDriversBasedOnDisplayAdapters(GUID_DEVCLASS_DISPLAY);
        auto computeDrivers = discoverDriversBasedOnDisplayAdapters(GUID_DEVCLASS_COMPUTEACCELERATOR);
        enabledDrivers.insert(enabledDrivers.end(), displayDrivers.begin(), displayDrivers.end());
        enabledDrivers.insert(enabledDrivers.end(), computeDrivers.begin(), computeDrivers.end());
    } else {
        // Alternative drivers from environment variable - these are custom
        std::stringstream ss(altDrivers.c_str());
        while (ss.good()) {
            std::string substr;
            getline(ss, substr, ',');
            enabledDrivers.emplace_back(substr, true, ZEL_DRIVER_TYPE_FORCE_UINT32);
        }
    }

    return enabledDrivers;
}

bool isStagedDriverPathSetForDisplayAdapter(DEVINST dnDevNode) {
    static constexpr char stagedDriverPathKey[] = "LevelZeroStagedDriverPath";

    HKEY hkey = {};
    CONFIGRET configErr = CM_Open_DevNode_Key(dnDevNode, KEY_QUERY_VALUE, 0,
                                              RegDisposition_OpenExisting, &hkey,
                                              CM_REGISTRY_SOFTWARE);

    if (CR_SUCCESS != configErr) {
        assert(false && "CM_Open_DevNode_Key failed");
        return false;
    }

    DWORD regValueType = {};
    DWORD pathSize = {};
    LSTATUS regOpStatus = RegQueryValueExA(hkey, stagedDriverPathKey, NULL,
                                           &regValueType, NULL, &pathSize);

    bool isStagedDriverPathSet = false;
    if (ERROR_SUCCESS == regOpStatus) {
        isStagedDriverPathSet = true;
    }

    regOpStatus = RegCloseKey(hkey);
    assert((ERROR_SUCCESS == regOpStatus) && "RegCloseKey failed");

    return isStagedDriverPathSet;
}

bool isDeviceAvailable(DEVINST devnode) {
    ULONG devStatus = {};
    ULONG devProblem = {};
    auto configErr = CM_Get_DevNode_Status(&devStatus, &devProblem, devnode, 0);

    if (CR_SUCCESS != configErr) {
        assert(false && "CM_Get_DevNode_Status failed");
        return false;
    }

    bool isInInvalidState = (devStatus & DN_HAS_PROBLEM)
                            && (devProblem == CM_PROB_NEED_RESTART);
    if (! isStagedDriverPathSetForDisplayAdapter(devnode)) {
        isInInvalidState |= (DN_NEED_RESTART == (devStatus & DN_NEED_RESTART));
    }
    isInInvalidState |= (devStatus & DN_HAS_PROBLEM)
                             && (devProblem == CM_PROB_DISABLED);


    return false == isInInvalidState;
}

DriverLibraryPath readDriverPathForDisplayAdapter(DEVINST dnDevNode) {
    static constexpr char levelZeroDriverPathKey[] = "LevelZeroDriverPath";

    HKEY hkey = {};
    CONFIGRET configErr = CM_Open_DevNode_Key(dnDevNode, KEY_QUERY_VALUE, 0,
                                              RegDisposition_OpenExisting, &hkey,
                                              CM_REGISTRY_SOFTWARE);

    if (CR_SUCCESS != configErr) {
        assert(false && "CM_Open_DevNode_Key failed");
        return DriverLibraryPath("", false);
    }

    DWORD regValueType = {};
    DWORD pathSize = {};
    LSTATUS regOpStatus = RegQueryValueExA(hkey, levelZeroDriverPathKey, NULL,
                                           &regValueType, NULL, &pathSize);

    std::string driverPath;
    if ((ERROR_SUCCESS == regOpStatus) && (REG_SZ == regValueType)) {
        driverPath.resize(pathSize);
        regOpStatus = RegQueryValueExA(hkey, levelZeroDriverPathKey, NULL,
                                       &regValueType, (LPBYTE) & *driverPath.begin(),
                                       &pathSize);
        if (ERROR_SUCCESS != regOpStatus) {
            assert(false && "RegQueryValueExA failed");
            driverPath.clear();
        }
    }

    regOpStatus = RegCloseKey(hkey);
    assert((ERROR_SUCCESS == regOpStatus) && "RegCloseKey failed");

    return DriverLibraryPath(driverPath, false);
}

std::wstring readDisplayAdaptersDeviceIdsList(const GUID rguid) {
    OLECHAR displayGuidStr[MAX_GUID_STRING_LEN];

    int strFromGuidErr = StringFromGUID2(rguid, displayGuidStr,
                                        MAX_GUID_STRING_LEN);
    if (MAX_GUID_STRING_LEN != strFromGuidErr) {
        assert(false && "StringFromGUID2 failed");
        return L"";
    }

    std::wstring deviceIdList;
    CONFIGRET getDeviceIdListErr = CR_BUFFER_SMALL;
    while (CR_BUFFER_SMALL == getDeviceIdListErr) {
        ULONG deviceIdListSize = {};
        ULONG deviceIdListFlags = CM_GETIDLIST_FILTER_CLASS | CM_GETIDLIST_FILTER_PRESENT;
        auto getDeviceIdListSizeErr = CM_Get_Device_ID_List_SizeW(&deviceIdListSize,
                                                                  displayGuidStr,
                                                                  deviceIdListFlags);
        if (CR_SUCCESS != getDeviceIdListSizeErr) {
            assert(false && "CM_Get_Device_ID_List_size failed");
            break;
        }

        deviceIdList.resize(deviceIdListSize);
        getDeviceIdListErr = CM_Get_Device_ID_ListW(displayGuidStr,
                                                    &*deviceIdList.begin(),
                                                    deviceIdListSize,
                                                    deviceIdListFlags);
    }

    return deviceIdList;
}

std::vector<DriverLibraryPath> discoverDriversBasedOnDisplayAdapters(const GUID rguid) {
    std::vector<DriverLibraryPath> enabledDrivers;
    auto deviceIdList = readDisplayAdaptersDeviceIdsList(rguid);
    if (deviceIdList.empty()) {
        return enabledDrivers;
    }

    auto isNotDeviceListEnd = [](wchar_t *it) { return '\0' != it[0]; };
    auto getNextDeviceInList = [](wchar_t *it) { return it + wcslen(it) + 1; };

    auto deviceIdIt = &*deviceIdList.begin();
    for (; isNotDeviceListEnd(deviceIdIt); deviceIdIt = getNextDeviceInList(deviceIdIt)) {
        DEVINST devinst = {};
        if (CR_SUCCESS != CM_Locate_DevNodeW(&devinst, deviceIdIt, 0)) {
            assert(false && "CM_Locate_DevNodeW failed");
            continue;
        }

        if (false == isDeviceAvailable(devinst)) {
            continue;
        }

        auto driverPath = readDriverPathForDisplayAdapter(devinst);

        if (driverPath.path.empty()) {
            continue;
        }

        bool alreadyOnTheList = (enabledDrivers.end() != std::find_if(enabledDrivers.begin(), enabledDrivers.end(), 
            [&driverPath](const DriverLibraryPath& d) { return d.path == driverPath.path; }));
        if (alreadyOnTheList) {
            continue;
        }
        driverPath.customDriver = false;
        if (rguid == GUID_DEVCLASS_DISPLAY) {
            driverPath.driverType = ZEL_DRIVER_TYPE_GPU;
        } else if (rguid == GUID_DEVCLASS_COMPUTEACCELERATOR) {
            driverPath.driverType = ZEL_DRIVER_TYPE_NPU;
        } else {
            driverPath.driverType = ZEL_DRIVER_TYPE_FORCE_UINT32;
        }

        enabledDrivers.push_back(std::move(driverPath));
    }
    return enabledDrivers;
}

} // namespace loader
