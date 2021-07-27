/*
 *
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "source/loader/driver_discovery.h"

#include "source/inc/ze_util.h"
#include <iostream>
#include <sstream>
#include <string>

namespace loader {

static const char *knownDriverNames[] = {
    MAKE_LIBRARY_NAME("ze_intel_gpu", "1"),
    MAKE_LIBRARY_NAME("ze_intel_vpu", "1"),
};

std::vector<DriverLibraryPath> discoverEnabledDrivers() {
  std::vector<DriverLibraryPath> enabledDrivers;
  const char *altDrivers = nullptr;

  // ZE_ENABLE_ALT_DRIVERS is for development/debug only
  altDrivers = getenv("ZE_ENABLE_ALT_DRIVERS");
  if (altDrivers == nullptr) {
    for (auto path : knownDriverNames) {
      enabledDrivers.emplace_back(path);
    }
  } else {
    std::stringstream ss(altDrivers);
    while (ss.good()) {
      std::string substr;
      getline(ss, substr, ',');
      enabledDrivers.emplace_back(substr);
    }
  }
  return enabledDrivers;
}

} // namespace loader
