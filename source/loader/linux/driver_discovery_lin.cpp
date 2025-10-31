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

#include <dlfcn.h>
#include <unistd.h>
#include <dirent.h>

#include <vector>
#include <fstream>
#include <sys/stat.h>
// Helper to split a colon-separated path string
static std::vector<std::string> splitPaths(const std::string& paths) {
  std::vector<std::string> result;
  std::stringstream ss(paths);
  std::string item;
  while (std::getline(ss, item, ':')) {
    if (!item.empty()) result.push_back(item);
  }
  return result;
}

// Helper to check if a file exists and is readable
static bool fileExistsReadable(const std::string& path) {
  struct stat sb;
  return (stat(path.c_str(), &sb) == 0) && (access(path.c_str(), R_OK) == 0);
}

// Helper to get all library search paths from LD_LIBRARY_PATH, standard locations, and /etc/ld.so.conf
static std::vector<std::string> getLibrarySearchPaths() {
  std::vector<std::string> paths;
  // LD_LIBRARY_PATH
  const char* ldLibPath = getenv("LD_LIBRARY_PATH");
  if (ldLibPath) {
    auto split = splitPaths(ldLibPath);
    paths.insert(paths.end(), split.begin(), split.end());
  }
  // Standard locations
  paths.push_back("/lib");
  paths.push_back("/usr/lib");
  paths.push_back("/usr/local/lib");
  // /etc/ld.so.conf and included files
  std::ifstream ldSoConf("/etc/ld.so.conf");
  if (ldSoConf) {
    std::string line;
    while (std::getline(ldSoConf, line)) {
      if (line.empty()) continue;
      if (line.find("include ") == 0) {
        std::string pattern = line.substr(8);
        // Simple glob: /etc/ld.so.conf.d/*.conf
        std::string dir = pattern.substr(0, pattern.find_last_of('/'));
        std::string ext = pattern.substr(pattern.find_last_of('.'));
        DIR* d = opendir(dir.c_str());
        if (d) {
          struct dirent* ent;
          while ((ent = readdir(d)) != nullptr) {
            std::string fname = ent->d_name;
            if (fname.size() > ext.size() && fname.substr(fname.size()-ext.size()) == ext) {
              std::ifstream incFile(dir + "/" + fname);
              std::string incLine;
              while (std::getline(incFile, incLine)) {
                if (!incLine.empty() && incLine[0] != '#')
                  paths.push_back(incLine);
              }
            }
          }
          closedir(d);
        }
      } else if (line[0] != '#') {
        paths.push_back(line);
      }
    }
  }
  return paths;
}

// Main function: search for a library file in all known library paths
static bool libraryExistsInSearchPaths(const std::string& filename) {
  auto paths = getLibrarySearchPaths();
  for (const auto& dir : paths) {
    std::string fullPath = dir + "/" + filename;
    if (fileExistsReadable(fullPath)) {
      return true;
    }
  }
  return false;
}

namespace loader {

static const char *knownDriverNames[] = {
    MAKE_LIBRARY_NAME("ze_intel_gpu", "1"),
    MAKE_LIBRARY_NAME("ze_intel_gpu_legacy1", "1"),
    MAKE_LIBRARY_NAME("ze_intel_vpu", "1"),
    MAKE_LIBRARY_NAME("ze_intel_npu", "1"),
};

std::vector<DriverLibraryPath> discoverEnabledDrivers() {
  std::vector<DriverLibraryPath> enabledDrivers;
  const char *altDrivers = nullptr;

  // ZE_ENABLE_ALT_DRIVERS is for development/debug only
  altDrivers = getenv("ZE_ENABLE_ALT_DRIVERS");
  if (altDrivers == nullptr) {
    // Standard drivers - not custom
    for (auto path : knownDriverNames) {
      if (libraryExistsInSearchPaths(path)) {
        // Extract the base library name for robust driver type detection
        // path is like "libze_intel_gpu.so.1"
        std::string libName = path;

        // Remove "lib" prefix if present
        if (libName.compare(0, 3, "lib") == 0) {
          libName = libName.substr(3);
        }

        // Remove file extension
        size_t dotPos = libName.find('.');
        if (dotPos != std::string::npos) {
          libName = libName.substr(0, dotPos);
        }

        // Now match against the core driver name (e.g., "ze_intel_gpu", "ze_intel_npu")
        // Check for exact matches or word boundaries to avoid substring false positives
        zel_driver_type_t driverType = ZEL_DRIVER_TYPE_FORCE_UINT32;

        // Check more specific patterns first to avoid partial matches
        if (libName == "ze_intel_gpu" || libName == "ze_intel_gpu_legacy1") {
          driverType = ZEL_DRIVER_TYPE_GPU;
        } else if (libName == "ze_intel_vpu" || libName == "ze_intel_npu") {
          driverType = ZEL_DRIVER_TYPE_NPU;
        }

        enabledDrivers.emplace_back(path, false, driverType);
      }
    }
  } else {
    // Alternative drivers from environment variable - these are custom
    std::stringstream ss(altDrivers);
    while (ss.good()) {
      std::string substr;
      getline(ss, substr, ',');
      enabledDrivers.emplace_back(substr, true);
    }
  }
  return enabledDrivers;
}

} // namespace loader
