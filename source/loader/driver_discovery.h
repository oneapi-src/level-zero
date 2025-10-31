/*
 *
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once

#include <string>
#include <vector>
#include "ze_loader_internal.h"

namespace loader {

struct DriverLibraryPath {
    std::string path;
    bool customDriver;
    zel_driver_type_t driverType = ZEL_DRIVER_TYPE_FORCE_UINT32;
    DriverLibraryPath(const std::string& p, bool isCustom = false, zel_driver_type_t type = ZEL_DRIVER_TYPE_FORCE_UINT32)
        : path(p), customDriver(isCustom), driverType(type) {}
};

std::vector<DriverLibraryPath> discoverEnabledDrivers();

} // namespace loader
