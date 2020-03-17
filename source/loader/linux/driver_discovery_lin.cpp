/*
 *
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "source/loader/driver_discovery.h"

#include "source/inc/ze_util.h"

namespace loader {

static const char *knownDriverNames[] = {
    MAKE_LIBRARY_NAME("ze_intel_gpu", "0.8"),
};

std::vector<DriverLibraryPath> discoverEnabledDrivers() {
    std::vector<DriverLibraryPath> enabledDrivers;
    for (auto path : knownDriverNames) {
        enabledDrivers.emplace_back(path);
    }
    return enabledDrivers;
}

} // namespace loader
