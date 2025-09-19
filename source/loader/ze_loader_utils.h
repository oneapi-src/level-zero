/*
 *
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#pragma once
#include "ze_loader_internal.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <cstdlib>
#include <algorithm>


namespace loader
{
   // Helper function to map driver type string to enum
    inline zel_driver_type_t stringToDriverType(const std::string& typeStr) {
        if (typeStr == "DISCRETE_GPU_ONLY") {
            return ZEL_DRIVER_TYPE_DISCRETE_GPU;
        } else if (typeStr == "GPU") {
            return ZEL_DRIVER_TYPE_GPU;
        } else if (typeStr == "INTEGRATED_GPU_ONLY") {
            return ZEL_DRIVER_TYPE_INTEGRATED_GPU;
        } else if (typeStr == "NPU") {
            return ZEL_DRIVER_TYPE_NPU;
        }
        return ZEL_DRIVER_TYPE_FORCE_UINT32; // Invalid
    }

    // Helper function to trim whitespace
    inline std::string trim(const std::string& str) {
        const std::string whitespace = " \t\n\r\f\v";
        size_t start = str.find_first_not_of(whitespace);
        if (start == std::string::npos) return "";
        size_t end = str.find_last_not_of(whitespace);
        return str.substr(start, end - start + 1);
    }

    enum DriverOrderSpecType { BY_GLOBAL_INDEX, BY_TYPE, BY_TYPE_AND_INDEX };

    // Structure to hold parsed ordering instructions
    struct DriverOrderSpec {
        DriverOrderSpecType type;
        uint32_t globalIndex = 0;
        zel_driver_type_t driverType = ZEL_DRIVER_TYPE_FORCE_UINT32;
        uint32_t typeIndex = 0;
    };

    // Parse ZEL_DRIVERS_ORDER environment variable
    inline std::vector<DriverOrderSpec> parseDriverOrder(const std::string& orderStr) {
        std::vector<DriverOrderSpec> specs;

        // Split by comma
        std::vector<std::string> tokens;
        std::stringstream ss(orderStr);
        std::string token;

        while (std::getline(ss, token, ',')) {
            token = trim(token);
            if (token.empty()) continue;

            DriverOrderSpec spec;

            // Check if it contains a colon (type:index format)
            size_t colonPos = token.find(':');
            if (colonPos != std::string::npos) {
                // Format: <driver_type>:<driver_index>
                std::string typeStr = trim(token.substr(0, colonPos));
                std::string indexStr = trim(token.substr(colonPos + 1));

                spec.driverType = stringToDriverType(typeStr);
                if (spec.driverType == ZEL_DRIVER_TYPE_FORCE_UINT32) {
                    continue; // Invalid driver type, skip
                }

                try {
                    spec.typeIndex = std::stoul(indexStr);
                    spec.type = DriverOrderSpecType::BY_TYPE_AND_INDEX;
                    specs.push_back(spec);
                } catch (const std::exception&) {
                    // Invalid index, skip
                    continue;
                }
            } else {
                // Check if it's a pure number (global index) or driver type
                try {
                    spec.globalIndex = std::stoul(token);
                    spec.type = DriverOrderSpecType::BY_GLOBAL_INDEX;
                    specs.push_back(spec);
                } catch (const std::exception&) {
                    // Not a number, try as driver type
                    spec.driverType = stringToDriverType(token);
                    if (spec.driverType != ZEL_DRIVER_TYPE_FORCE_UINT32) {
                        spec.type = DriverOrderSpecType::BY_TYPE;
                        specs.push_back(spec);
                    }
                }
            }
        }

        return specs;
    }
} // namespace loader