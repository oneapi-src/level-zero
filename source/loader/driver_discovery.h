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

using DriverLibraryPath = std::string;

std::vector<DriverLibraryPath> discoverEnabledDrivers();

} // namespace loader
