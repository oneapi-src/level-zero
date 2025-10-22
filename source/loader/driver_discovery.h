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

namespace loader {

struct DriverLibraryPath {
    std::string path;
    bool customDriver;
    
    DriverLibraryPath(const std::string& p, bool isCustom = false) 
        : path(p), customDriver(isCustom) {}
};

std::vector<DriverLibraryPath> discoverEnabledDrivers();

} // namespace loader
