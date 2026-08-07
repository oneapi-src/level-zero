/*
 *
 * Copyright (C) 2019-2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "ze_loader_utils.h"

#include "driver_discovery.h"
#include <algorithm>
#include <iostream>
#include <set>

#ifdef __linux__
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif // __linux__

namespace loader
{
    ze_handle_t* loaderDispatch = nullptr;
    zer_dditable_t *defaultZerDdiTable = nullptr;
    ///////////////////////////////////////////////////////////////////////////////
    context_t *context;

    void context_t::debug_trace_message(std::string message, std::string result) {
        if (debugTraceEnabled) {
            std::cerr << "ZE_LOADER_DEBUG_TRACE:" << message << result << std::endl;
        }
        zel_logger->log_trace(message + result);
    };

    std::string to_string(const ze_init_flags_t flags) {
        if (flags & ZE_INIT_FLAG_GPU_ONLY) {
            return "ZE_INIT_FLAG_GPU_ONLY";
        } else if (flags & ZE_INIT_FLAG_VPU_ONLY) {
            return "ZE_INIT_FLAG_VPU_ONLY";
        } else if (flags == 0) {
            return "0(ZE_INIT_ALL_DRIVER_TYPES_ENABLED)";
        } else {
            return (std::to_string(static_cast<int>(flags)));
        }
    }

    std::string to_string(const ze_init_driver_type_desc_t *desc) {
        std::string flags_value;
        if (desc->flags & ZE_INIT_DRIVER_TYPE_FLAG_GPU) {
            flags_value+= "|ZE_INIT_DRIVER_TYPE_FLAG_GPU|";
        }
        if (desc->flags & ZE_INIT_DRIVER_TYPE_FLAG_NPU) {
            flags_value+= "|ZE_INIT_DRIVER_TYPE_FLAG_NPU|";
        }
        return flags_value;
    }

    bool driverSortComparator(const driver_t &a, const driver_t &b) {
        if (a.pciOrderingRequested) {
            if (a.driverType == ZEL_DRIVER_TYPE_OTHER) {
                return false;
            }
            if (a.driverType == ZEL_DRIVER_TYPE_MIXED && b.driverType == ZEL_DRIVER_TYPE_OTHER) {
                return true;
            } else if(a.driverType == ZEL_DRIVER_TYPE_MIXED) {
                return false;
            }
            return a.driverType > b.driverType;
        }
        return a.driverType < b.driverType;
    }

    void context_t::driverOrdering(driver_vector_t *drivers) {
        std::string orderStr = getenv_string("ZEL_DRIVERS_ORDER");
        if (orderStr.empty()) {
            return; // No ordering specified
        }

        std::vector<DriverOrderSpec> specs = parseDriverOrder(orderStr);

        if (specs.empty()) {
            if (debugTraceEnabled) {
                std::string message = "driverOrdering: ZEL_DRIVERS_ORDER parsing failed or empty: " + orderStr;
                debug_trace_message(message, "");
            }
            return;
        }

        if (debugTraceEnabled) {
            std::string message = "driverOrdering:ZEL_DRIVERS_ORDER parsing successful: " + orderStr + ", specs count: " + std::to_string(specs.size());
            debug_trace_message(message, "");
        }

        // Create a copy of the original driver vector for reference
        driver_vector_t originalDrivers = *drivers;

        driver_vector_t discreteGPUDrivers;
        driver_vector_t integratedGPUDrivers;
        driver_vector_t npuDrivers;
        driver_vector_t gpuDrivers;

        std::vector<uint32_t> discreteGPUIndices;
        std::vector<uint32_t> integratedGPUIndices;
        std::vector<uint32_t> npuIndices;
        std::vector<uint32_t> gpuIndices;

        // Group drivers by type and track their original indices
        for (uint32_t i = 0; i < originalDrivers.size(); ++i) {
            const auto& driver = originalDrivers[i];
            if (driver.slotState == driver_slot_state_t::Unloaded) {
                continue; // Unloaded slots are not eligible for type/index based ordering.
            }
            switch (driver.driverType) {
                case ZEL_DRIVER_TYPE_DISCRETE_GPU:
                    discreteGPUDrivers.push_back(driver);
                    discreteGPUIndices.push_back(i);
                    break;
                case ZEL_DRIVER_TYPE_INTEGRATED_GPU:
                    integratedGPUDrivers.push_back(driver);
                    integratedGPUIndices.push_back(i);
                    break;
                case ZEL_DRIVER_TYPE_GPU:
                    gpuDrivers.push_back(driver);
                    gpuIndices.push_back(i);
                    break;
                case ZEL_DRIVER_TYPE_NPU:
                    npuDrivers.push_back(driver);
                    npuIndices.push_back(i);
                    break;
                case ZEL_DRIVER_TYPE_OTHER:
                    npuDrivers.push_back(driver);
                    npuIndices.push_back(i);
                    break;
                case ZEL_DRIVER_TYPE_MIXED:
                    // Mixed drivers go to gpuDrivers
                    gpuDrivers.push_back(driver);
                    gpuIndices.push_back(i);
                    break;
                default:
                    break;
            }
        }

        // Create new ordered driver vector
        driver_vector_t orderedDrivers;
        std::set<uint32_t> usedGlobalIndices;
        std::set<std::pair<zel_driver_type_t, uint32_t>> usedTypeIndices;

        // Apply ordering specifications
        for (const auto& spec : specs) {
            switch (spec.type) {
                case DriverOrderSpecType::BY_GLOBAL_INDEX:
                    if (spec.globalIndex < originalDrivers.size() &&
                        originalDrivers[spec.globalIndex].slotState != driver_slot_state_t::Unloaded &&
                        usedGlobalIndices.find(spec.globalIndex) == usedGlobalIndices.end()) {
                        orderedDrivers.push_back(originalDrivers[spec.globalIndex]);
                        usedGlobalIndices.insert(spec.globalIndex);
                    }
                    break;

                case DriverOrderSpecType::BY_TYPE:
                    // Add all drivers of this type that haven't been used
                    {
                        std::vector<uint32_t>* typeIndices = nullptr;
                        switch (spec.driverType) {
                            case ZEL_DRIVER_TYPE_DISCRETE_GPU:
                                typeIndices = &discreteGPUIndices;
                                break;
                            case ZEL_DRIVER_TYPE_INTEGRATED_GPU:
                                typeIndices = &integratedGPUIndices;
                                break;
                            case ZEL_DRIVER_TYPE_GPU:
                                typeIndices = &gpuIndices;
                                break;
                            case ZEL_DRIVER_TYPE_NPU:
                            case ZEL_DRIVER_TYPE_OTHER:
                                typeIndices = &npuIndices;
                                break;
                            default:
                                break;
                        }

                        if (typeIndices) {
                            for (uint32_t globalIdx : *typeIndices) {
                                if (usedGlobalIndices.find(globalIdx) == usedGlobalIndices.end()) {
                                    orderedDrivers.push_back(originalDrivers[globalIdx]);
                                    usedGlobalIndices.insert(globalIdx);
                                }
                            }
                        }
                    }
                    break;

                case DriverOrderSpecType::BY_TYPE_AND_INDEX:
                    {
                        std::vector<uint32_t>* typeIndices = nullptr;
                        switch (spec.driverType) {
                            case ZEL_DRIVER_TYPE_DISCRETE_GPU:
                                typeIndices = &discreteGPUIndices;
                                break;
                            case ZEL_DRIVER_TYPE_INTEGRATED_GPU:
                                typeIndices = &integratedGPUIndices;
                                break;
                            case ZEL_DRIVER_TYPE_GPU:
                                typeIndices = &gpuIndices;
                                break;
                            case ZEL_DRIVER_TYPE_NPU:
                            case ZEL_DRIVER_TYPE_OTHER:
                                typeIndices = &npuIndices;
                                break;
                            default:
                                break;
                        }

                        if (typeIndices && spec.typeIndex < typeIndices->size()) {
                            auto typeIndexPair = std::make_pair(spec.driverType, spec.typeIndex);
                            if (usedTypeIndices.find(typeIndexPair) == usedTypeIndices.end()) {
                                uint32_t globalIdx = (*typeIndices)[spec.typeIndex];
                                if (usedGlobalIndices.find(globalIdx) == usedGlobalIndices.end()) {
                                    orderedDrivers.push_back(originalDrivers[globalIdx]);
                                    usedGlobalIndices.insert(globalIdx);
                                    usedTypeIndices.insert(typeIndexPair);
                                }
                            }
                        }
                    }
                    break;
            }
        }

        // Add remaining drivers in their original order
        for (uint32_t i = 0; i < originalDrivers.size(); ++i) {
            if (usedGlobalIndices.find(i) == usedGlobalIndices.end()) {
                orderedDrivers.push_back(originalDrivers[i]);
            }
        }

        // Replace the original driver vector with the ordered one
        *drivers = std::move(orderedDrivers);

        if (debugTraceEnabled) {
            std::string message = "driverOrdering: Drivers after ZEL_DRIVERS_ORDER:";
            for (uint32_t i = 0; i < drivers->size(); ++i) {
                message += "\n[" + std::to_string(i) + "] Driver Type: " + std::to_string((*drivers)[i].driverType) + " Driver Name: " + (*drivers)[i].name;
            }
            debug_trace_message(message, "");
        }
    }

    bool context_t::driverSorting(driver_vector_t *drivers, ze_init_driver_type_desc_t* desc, bool sysmanOnly) {
        ze_init_driver_type_desc_t permissiveDesc = {};
        permissiveDesc.stype = ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC;
        permissiveDesc.pNext = nullptr;
        permissiveDesc.flags = UINT32_MAX;
        if (sysmanOnly) {
            return true; // Sorting not fully supported by the spec due to missing zesDriverGetProperties for sysman drivers.
        }
        for (auto &driver : *drivers) {
            uint32_t pCount = 0;
            std::vector<ze_driver_handle_t> driverHandles;
            if (driver.slotState == driver_slot_state_t::Unloaded) {
                continue; // Unloaded slots must not be probed or re-typed.
            }
            driver.pciOrderingRequested = loader::context->pciOrderingRequested;
            ze_result_t res = ZE_RESULT_SUCCESS;
            if (desc && driver.dditable.ze.Global.pfnInitDrivers) {
                if (driver.initDriversStatus != ZE_RESULT_SUCCESS) {
                    if (debugTraceEnabled) {
                        std::string message = "driverSorting " + driver.name + " failed, zeInitDrivers returned ";
                        debug_trace_message(message, loader::to_string(driver.initDriversStatus));
                    }
                    continue;
                }
                if (debugTraceEnabled) {
                    std::string message = "driverSorting " + driver.name + " using zeInitDrivers(" + loader::to_string(&permissiveDesc) + ")";
                    debug_trace_message(message, "");
                }
                pCount = 0;
                res = driver.dditable.ze.Global.pfnInitDrivers(&pCount, nullptr, &permissiveDesc);
                // Verify that this driver successfully init in the call above.
                if (res != ZE_RESULT_SUCCESS) {
                    if (debugTraceEnabled) {
                        std::string message = "driverSorting " + driver.name + " zeInitDrivers(" + loader::to_string(&permissiveDesc) + ") returning ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    continue;
                }
                driverHandles.resize(pCount);
                // Use the driver's init function to query the driver handles and read the properties.
                res = driver.dditable.ze.Global.pfnInitDrivers(&pCount, driverHandles.data(), &permissiveDesc);
                // Verify that this driver successfully init in the call above.
                if (res != ZE_RESULT_SUCCESS) {
                    if (debugTraceEnabled) {
                        std::string message = "driverSorting " + driver.name + " zeInitDrivers(" + loader::to_string(&permissiveDesc) + ") returning ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    continue;
                }
            } else if (driver.dditable.ze.Driver.pfnGet) {
                if (driver.initStatus != ZE_RESULT_SUCCESS || !driver.legacyInitAttempted) {
                    if (debugTraceEnabled) {
                        std::string message = "driverSorting " + driver.name + " failed, zeInit returned ";
                        debug_trace_message(message, loader::to_string(driver.initStatus));
                    }
                    continue;
                }
                if (debugTraceEnabled) {
                    std::string message = "driverSorting " + driver.name + " using zeDriverGet";
                    debug_trace_message(message, "");
                }
                res = driver.dditable.ze.Driver.pfnGet(&pCount, nullptr);
                // Verify that this driver successfully init in the call above.
                if (res != ZE_RESULT_SUCCESS) {
                    if (debugTraceEnabled) {
                        std::string message = "driverSorting " + driver.name + " zeDriverGet returning ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    continue;
                }
                driverHandles.resize(pCount);
                res = driver.dditable.ze.Driver.pfnGet(&pCount, driverHandles.data());
                // Verify that this driver successfully init in the call above.
                if (res != ZE_RESULT_SUCCESS) {
                    if (debugTraceEnabled) {
                        std::string message = "driverSorting " + driver.name + " zeDriverGet returning ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    continue;
                }
            } else {
                res = ZE_RESULT_ERROR_UNINITIALIZED;
                if (debugTraceEnabled) {
                    std::string message = "driverSorting " + driver.name + " zeDriverGet and zeInitDrivers not supported, skipping driver with error ";
                    debug_trace_message(message, loader::to_string(res));
                }
                continue;
            }

            for (auto handle : driverHandles) {
                uint32_t extensionCount = 0;
                if (driver.zerddiInitResult == ZE_RESULT_SUCCESS)
                    driver.zerDriverHandle = handle;
                ze_result_t res = driver.dditable.ze.Driver.pfnGetExtensionProperties(handle, &extensionCount, nullptr);
                if (res != ZE_RESULT_SUCCESS) {
                    if (loader::context->debugTraceEnabled) {
                        std::string message = "driverSorting " + driver.name + " failed, zeDriverGetExtensionProperties returned ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    return res;
                }
                std::vector<ze_driver_extension_properties_t> extensionProperties(extensionCount);
                res = driver.dditable.ze.Driver.pfnGetExtensionProperties(handle, &extensionCount, extensionProperties.data());
                if (res != ZE_RESULT_SUCCESS) {
                    if (loader::context->debugTraceEnabled) {
                        std::string message = "driverSorting " + driver.name + " failed, zeDriverGetExtensionProperties returned ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    return res;
                }
                if (extensionCount > 0) {
                    for (uint32_t extIndex = 0; extIndex < extensionCount; extIndex++) {
                        if (strcmp(extensionProperties[extIndex].name, ZE_DRIVER_DDI_HANDLES_EXT_NAME) == 0 && (!(extensionProperties[extIndex].version >= ZE_DRIVER_DDI_HANDLES_EXT_VERSION_1_1))) {
                            // Driver supports DDI Handles but not the required version for ZER APIs so set the driverHandle to nullptr
                            driver.zerDriverHandle = nullptr;
                            driver.zerDriverDDISupported = false;
                            break;
                        }
                    }

                }
                driver.properties = {};
                driver.properties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
                driver.properties.pNext = nullptr;
                ze_driver_properties_t driverProperties = {};
                driverProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
                driverProperties.pNext = &driver.properties;
                res = driver.dditable.ze.Driver.pfnGetProperties(handle, &driverProperties);
                if (res != ZE_RESULT_SUCCESS) {
                    if (debugTraceEnabled) {
                        std::string message = "driverSorting " + driver.name + " failed, zeDriverGetProperties returned ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    continue;
                }
                driver.driverDDIHandleSupportQueried = true;
                
                if (!(driver.properties.flags & ZE_DRIVER_DDI_HANDLE_EXT_FLAG_DDI_HANDLE_EXT_SUPPORTED) || !loader::context->driverDDIPathDefault) {
                    if (debugTraceEnabled) {
                        std::string message = "driverSorting: Driver DDI Handles Not Supported for " + driver.name;
                        debug_trace_message(message, "");
                    }
                } else {
                    if (debugTraceEnabled) {
                        std::string message = "driverSorting: Driver DDI Handles Supported for " + driver.name;
                        debug_trace_message(message, "");
                    }
                }
                
                uint32_t deviceCount = 0;
                res = driver.dditable.ze.Device.pfnGet( handle, &deviceCount, nullptr );
                if( ZE_RESULT_SUCCESS != res ) {
                    if (debugTraceEnabled) {
                        std::string message = "driverSorting " + driver.name + " failed, zeDeviceGet returned ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    continue;
                }
                if (deviceCount == 0) {
                    if (debugTraceEnabled) {
                        std::string message = "driverSorting " + driver.name + " failed, zeDeviceGet returned 0 devices";
                        debug_trace_message(message, "");
                    }
                    continue;
                }
                std::vector<ze_device_handle_t> deviceHandles(deviceCount);
                res = driver.dditable.ze.Device.pfnGet( handle, &deviceCount, deviceHandles.data() );
                if( ZE_RESULT_SUCCESS != res ) {
                    if (debugTraceEnabled) {
                        std::string message = "driverSorting " + driver.name + " failed, zeDeviceGet returned ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    continue;
                }
                bool integratedGPU = false;
                bool discreteGPU = false;
                bool npu = false;
                bool other = false;
                for( auto device : deviceHandles ) {
                    ze_device_properties_t deviceProperties = {};
                    deviceProperties.stype = ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES;
                    deviceProperties.pNext = nullptr;
                    res = driver.dditable.ze.Device.pfnGetProperties(device, &deviceProperties);
                    if( ZE_RESULT_SUCCESS != res ) {
                        if (debugTraceEnabled) {
                            std::string message = "driverSorting " + driver.name + " failed, zeDeviceGetProperties returned ";
                            debug_trace_message(message, loader::to_string(res));
                        }
                        continue;
                    }
                    if (deviceProperties.type == ZE_DEVICE_TYPE_GPU) {
                        if (deviceProperties.flags & ZE_DEVICE_PROPERTY_FLAG_INTEGRATED) {
                            integratedGPU = true;
                        } else {
                            discreteGPU = true;
                        }
                    } else  if (deviceProperties.type == ZE_DEVICE_TYPE_VPU) {
                        npu = true;
                    } else {
                        other = true;
                    }
                }
                if (driver.driverType == ZEL_DRIVER_TYPE_NPU && npu == false) {
                    // Driver was forced to NPU but no NPU devices found, skip updating type.
                    continue;
                }
                if (integratedGPU && discreteGPU && (other || npu)) {
                    driver.driverType = ZEL_DRIVER_TYPE_MIXED;
                } else if (integratedGPU && discreteGPU) {
                    driver.driverType = ZEL_DRIVER_TYPE_GPU;
                } else if (integratedGPU) {
                    driver.driverType = ZEL_DRIVER_TYPE_INTEGRATED_GPU;
                } else if (discreteGPU) {
                    driver.driverType = ZEL_DRIVER_TYPE_DISCRETE_GPU;
                } else if (npu) {
                    driver.driverType = ZEL_DRIVER_TYPE_NPU;
                } else if (other) {
                    driver.driverType = ZEL_DRIVER_TYPE_OTHER;
                }
            }
        }

        // Sort drivers in ascending order of driver type unless ZE_ENABLE_PCI_ID_DEVICE_ORDER, then in descending order with MIXED and OTHER at the end.
        std::sort(drivers->begin(), drivers->end(), driverSortComparator);

        if (debugTraceEnabled) {
            std::string message = "Drivers after sorting:";
            for (const auto& driver : *drivers) {
                message += "\nDriver Type: " + std::to_string(driver.driverType) + " Driver Name: " + driver.name;
            }
            debug_trace_message(message, "");
        }

        // Apply driver ordering based on ZEL_DRIVERS_ORDER environment variable
        driverOrdering(drivers);

        return true;
    }

    ze_result_t context_t::init_driver(driver_t &driver, ze_init_flags_t flags, ze_init_driver_type_desc_t* desc) {
        bool loadDriver = false;
        // Implicit paths never resurrect an unloaded slot: an unrelated component calling
        // zeInitDrivers must not silently bring back a driver the application deliberately
        // unloaded. This is a state, not a blacklist -- zelReloadDriver clears it and loads the
        // library itself before reaching here.
        if (driver.slotState == driver_slot_state_t::Unloaded) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        if (debugTraceEnabled) {
            std::string message = "Initializing driver " + driver.name + " with type " + std::to_string(driver.driverType);\
            debug_trace_message(message, "");
        }
        if ((!desc && (flags == 0 || flags & ZE_INIT_FLAG_GPU_ONLY)) || (desc && desc->flags & ZE_INIT_DRIVER_TYPE_FLAG_GPU)) {
            if (driver.driverType == ZEL_DRIVER_TYPE_GPU || driver.driverType == ZEL_DRIVER_TYPE_DISCRETE_GPU || driver.driverType == ZEL_DRIVER_TYPE_INTEGRATED_GPU) {
                if (debugTraceEnabled) {
                    std::string message = "init driver " + driver.name + " found GPU Supported Driver.";
                    debug_trace_message(message, "");
                }
                loadDriver = true;
            }
        }
        if ((!desc && (flags == 0 || flags & ZE_INIT_FLAG_VPU_ONLY)) || (desc && desc->flags & ZE_INIT_DRIVER_TYPE_FLAG_NPU)) {
            if (driver.driverType == ZEL_DRIVER_TYPE_NPU || driver.driverType == ZEL_DRIVER_TYPE_OTHER) {
                if (debugTraceEnabled) {
                    std::string message = "init driver " + driver.name + " found VPU/NPU Supported Driver.";
                    debug_trace_message(message, "");
                }
                loadDriver = true;
            }
        }

        loadDriver = !driver.handle && driver.customDriver ? true : loadDriver;

        if (loadDriver && !driver.handle) {
            auto handle = LOAD_DRIVER_LIBRARY( driver.name.c_str() );
            if( NULL != handle )
            {
                if (debugTraceEnabled) {
#if !defined(_WIN32) && !defined(ANDROID)
                    struct link_map *dlinfo_map;
                    if (dlinfo(handle, RTLD_DI_LINKMAP, &dlinfo_map) == 0) {
                        debug_trace_message("init driver " + driver.name + " resolved path: ", std::string(dlinfo_map->l_name));
                    }
#elif defined(_WIN32)
                    char resolved[MAX_PATH];
                    if (GetModuleFileNameA(static_cast<HMODULE>(handle), resolved, MAX_PATH)) {
                        debug_trace_message("init driver " + driver.name + " resolved path: ", std::string(resolved));
                    }
#endif
                }
                driver.handle = handle;
                // This copy now owns a dlopen/LoadLibrary reference of its own; unload must
                // release it or the module stays mapped.
                driver.libraryLoadCount++;
            } else {
                std::string loadLibraryErrorValue;
                GET_LIBRARY_ERROR(loadLibraryErrorValue);
                if (debugTraceEnabled) {
                    std::string errorMessage = "init driver " + driver.name + " failed, Load Library of " + driver.name + " failed with ";
                    debug_trace_message(errorMessage, loadLibraryErrorValue);
                }
                return ZE_RESULT_ERROR_UNINITIALIZED;
            }
        }

        if (driver.handle && !driver.ddiInitialized) {
            auto res = loader::zeloaderInitDriverDDITables(&driver);
            if (res != ZE_RESULT_SUCCESS) {
                if (debugTraceEnabled) {
                    std::string message = "init driver " + driver.name + " failed, zeloaderInitDriverDDITables returned ";
                    debug_trace_message(message, loader::to_string(res));
                }
                driver.zeddiInitResult = res;
            } else {
                driver.zeddiInitResult = ZE_RESULT_SUCCESS;
            }
            res = loader::zesloaderInitDriverDDITables(&driver);
            if (res != ZE_RESULT_SUCCESS) {
                if (debugTraceEnabled) {
                    std::string message = "init driver " + driver.name + " failed, zesloaderInitDriverDDITables returned ";
                    debug_trace_message(message, loader::to_string(res));
                }
                driver.zesddiInitResult = res;
            } else {
                driver.zesddiInitResult = ZE_RESULT_SUCCESS;
            }
            res = loader::zetloaderInitDriverDDITables(&driver);
            if (res != ZE_RESULT_SUCCESS) {
                if (debugTraceEnabled) {
                    std::string message = "init driver " + driver.name + " failed, zetloaderInitDriverDDITables returned ";
                    debug_trace_message(message, loader::to_string(res));
                }
                driver.zetddiInitResult = res;
            } else {
                driver.zetddiInitResult = ZE_RESULT_SUCCESS;
            }
            res = loader::zerloaderInitDriverDDITables(&driver);
            if (res != ZE_RESULT_SUCCESS) {
                if (debugTraceEnabled) {
                    std::string message = "init driver " + driver.name + " failed, zerloaderInitDriverDDITables returned ";
                    debug_trace_message(message, loader::to_string(res));
                }
                driver.zerddiInitResult = res;
                driver.zerDriverHandle = nullptr;
            } else {
                driver.zerddiInitResult = ZE_RESULT_SUCCESS;
            }

            if (driver.zeddiInitResult != ZE_RESULT_SUCCESS && driver.zesddiInitResult != ZE_RESULT_SUCCESS) {
                if (debugTraceEnabled) {
                    std::string message = "init driver " + driver.name + " failed to initialize both core and sysman DDIs, skipping driver.";
                    debug_trace_message(message, "");
                }
                return ZE_RESULT_ERROR_UNINITIALIZED;
            }

            driver.ddiInitialized = true;
            driver.slotState = driver_slot_state_t::Loaded;
        }

        if (!driver.handle && !driver.ddiInitialized) {
            if (debugTraceEnabled) {
                std::string message = "init driver " + driver.name + " does not match the requested flags or desc, skipping driver.";
                debug_trace_message(message, "");
            }
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }

        return ZE_RESULT_SUCCESS;
    }

    ///////////////////////////////////////////////////////////////////////////////
    ze_result_t context_t::init()
    {
        if (driverEnvironmentQueried) {
            return ZE_RESULT_SUCCESS;
        }
        loader::context->instrumentationEnabled = getenv_tobool( "ZET_ENABLE_PROGRAM_INSTRUMENTATION" );
        loader::context->pciOrderingRequested = getenv_tobool( "ZE_ENABLE_PCI_ID_DEVICE_ORDER" );
        loader::loaderDispatch = new ze_handle_t();
        loader::loaderDispatch->pCore = new ze_dditable_driver_t();
        loader::loaderDispatch->pCore->version = ZE_API_VERSION_CURRENT;
        loader::loaderDispatch->pCore->isValidFlag = 1;
        loader::loaderDispatch->pTools = new zet_dditable_driver_t();
        loader::loaderDispatch->pTools->version = ZE_API_VERSION_CURRENT;
        loader::loaderDispatch->pTools->isValidFlag = 1;
        loader::loaderDispatch->pSysman = new zes_dditable_driver_t();
        loader::loaderDispatch->pSysman->version = ZE_API_VERSION_CURRENT;
        loader::loaderDispatch->pSysman->isValidFlag = 1;
        loader::loaderDispatch->pRuntime = new zer_dditable_driver_t();
        loader::loaderDispatch->pRuntime->version = ZE_API_VERSION_CURRENT;
        loader::loaderDispatch->pRuntime->isValidFlag = 1;
        {
            uint32_t dtMode = getenv_tomode( "ZE_ENABLE_LOADER_DEBUG_TRACE" );
            const uint32_t loggingMode = getenv_tomode("ZEL_ENABLE_LOADER_LOGGING");
            debugTraceEnabled = (dtMode != 0);
            debugTraceAdvanced = (dtMode == 2) || (loggingMode == 2);
        }
        if (debugTraceAdvanced) {
            std::cerr << "ZE_LOADER_DEBUG_TRACE: WARNING: ZE_ENABLE_LOADER_DEBUG_TRACE is deprecated and will be removed in a future release." << std::endl;
            std::cerr << "ZE_LOADER_DEBUG_TRACE: WARNING: Use ZEL_LOADER_LOG_CONSOLE=1 with ZEL_LOADER_LOGGING_LEVEL=trace instead." << std::endl;
        }
        // DDI Driver Extension Path is enabled by default.
        // This can be overridden by the environment variable ZE_ENABLE_LOADER_DRIVER_DDI_PATH.
        std::string ddiPathConfig = getenv_string("ZE_ENABLE_LOADER_DRIVER_DDI_PATH");
        if (ddiPathConfig.empty()) {
            driverDDIPathDefault = true;
        } else if (strcmp(ddiPathConfig.c_str(), "1") == 0 || strcmp(ddiPathConfig.c_str(), "true") == 0) {
            driverDDIPathDefault = true;
        } else if (strcmp(ddiPathConfig.c_str(), "0") == 0 || strcmp(ddiPathConfig.c_str(), "false") == 0) {
            driverDDIPathDefault = false;
        } else {
            driverDDIPathDefault = true; // fallback to the default for any other value
        }
        auto discoveredDrivers = discoverEnabledDrivers();
        std::string loadLibraryErrorValue;

#ifdef L0_STATIC_LOADER_BUILD
        zel_logger = createLogger("Static Loader");
#else
        zel_logger = createLogger("Dynamic Loader");
#endif

        if (zel_logger->getLevel() != loader::LogLevel::off) {
            std::string ver_msg = "Loader Version " +
                std::to_string(LOADER_VERSION_MAJOR) + "." +
                std::to_string(LOADER_VERSION_MINOR) + "." +
                std::to_string(LOADER_VERSION_PATCH) + " " +
                LOADER_VERSION_SHA;
            zel_logger->log_info(ver_msg);
        }

        add_loader_version();
        std::string loaderLibraryPath;
        auto loaderLibraryPathEnv = getenv_string("ZEL_LIBRARY_PATH");
        if (!loaderLibraryPathEnv.empty()) {
            loaderLibraryPath = loaderLibraryPathEnv;
        }
#ifdef _WIN32
        else {
            loaderLibraryPath = readLevelZeroLoaderLibraryPath();
        }
#endif
        if (debugTraceEnabled)
            debug_trace_message("Using Loader Library Path: ",
                (debugTraceAdvanced && loaderLibraryPath.empty()) ? "Not set" : loaderLibraryPath);

        if (debugTraceEnabled && driverDDIPathDefault) {
            debug_trace_message("DDI Driver Extension Path is Enabled", "");
        }

        // To allow for two different sets of drivers to be in use between sysman and core/tools, we use and store the drivers in two vectors.
        // alldrivers stores all the drivers for cleanup when the library exits.
        zeDrivers.reserve( discoveredDrivers.size() + getenv_tobool( "ZE_ENABLE_NULL_DRIVER" ) );
        zesDrivers.reserve( discoveredDrivers.size() + getenv_tobool( "ZE_ENABLE_NULL_DRIVER" ) );
        allDrivers.reserve( discoveredDrivers.size() + getenv_tobool( "ZE_ENABLE_NULL_DRIVER" ) );
        if( getenv_tobool( "ZE_ENABLE_NULL_DRIVER" ) )
        {
            zel_logger->log_info("Enabling Null Driver");
            std::string nullDriverPath = create_library_path( MAKE_LIBRARY_NAME( "ze_null", L0_LOADER_VERSION ), loaderLibraryPath.c_str());
            if (debugTraceEnabled) {
                if (debugTraceAdvanced)
                    debug_trace_message("Null Driver Library Path (requested): ", nullDriverPath);
                else
                    debug_trace_message("ze_null Driver Init", "");
            }
            auto handle = LOAD_DRIVER_LIBRARY( nullDriverPath.c_str() );
            if( NULL != handle )
            {
                if (debugTraceEnabled && debugTraceAdvanced) {
#if !defined(_WIN32) && !defined(ANDROID)
                    struct link_map *dlinfo_map;
                    if (dlinfo(handle, RTLD_DI_LINKMAP, &dlinfo_map) == 0) {
                        debug_trace_message("Null Driver Library Path (resolved): ", std::string(dlinfo_map->l_name));
                    }
#elif defined(_WIN32)
                    char resolved[MAX_PATH];
                    if (GetModuleFileNameA(static_cast<HMODULE>(handle), resolved, MAX_PATH)) {
                        debug_trace_message("Null Driver Library Path (resolved): ", std::string(resolved));
                    }
#endif
                }
                allDrivers.emplace_back();
                allDrivers.rbegin()->handle = handle;
                allDrivers.rbegin()->libraryLoadCount = 1;
                allDrivers.rbegin()->name = "ze_null";
            } else if (debugTraceEnabled) {
                GET_LIBRARY_ERROR(loadLibraryErrorValue);
                std::string errorMessage = "Load Library of " + nullDriverPath + " failed with ";
                debug_trace_message(errorMessage, loadLibraryErrorValue);
                loadLibraryErrorValue.clear();
            }
        }

        for( const auto& driverInfo : discoveredDrivers )
        {
            if (discoveredDrivers.size() == 1) {
                auto handle = LOAD_DRIVER_LIBRARY( driverInfo.path.c_str() );
                if( NULL != handle )
                {
                    if (debugTraceEnabled) {
                        std::string message = "Loading Driver " + driverInfo.path + " succeeded";
#if !defined(_WIN32) && !defined(ANDROID)
                        // TODO: implement same message for windows, move dlinfo to ze_util.h as a macro
                        struct link_map *dlinfo_map;
                        if (dlinfo(handle, RTLD_DI_LINKMAP, &dlinfo_map) == 0) {
                            message += " from: " + std::string(dlinfo_map->l_name);
                        }
#endif
                        debug_trace_message(message, "");
                    }
                    allDrivers.emplace_back();
                    allDrivers.rbegin()->handle = handle;
                allDrivers.rbegin()->libraryLoadCount = 1;
                    allDrivers.rbegin()->name = driverInfo.path;
                    allDrivers.rbegin()->customDriver = driverInfo.customDriver;
                } else if (debugTraceEnabled) {
                    GET_LIBRARY_ERROR(loadLibraryErrorValue);
                    std::string errorMessage = "Load Library of " + driverInfo.path + " failed with ";
                    debug_trace_message(errorMessage, loadLibraryErrorValue);
                    loadLibraryErrorValue.clear();
                }
            } else {
                allDrivers.emplace_back();
                allDrivers.rbegin()->handle = nullptr;
                allDrivers.rbegin()->name = driverInfo.path;
                allDrivers.rbegin()->customDriver = driverInfo.customDriver;
                allDrivers.rbegin()->driverType = driverInfo.driverType;
            }
        }
        if(allDrivers.size()==0){
            if (debugTraceEnabled) {
                std::string message = "0 Drivers Discovered";
                debug_trace_message(message, "");
            }
            zel_logger->log_error("0 Drivers Discovered");
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        std::copy(allDrivers.begin(), allDrivers.end(), std::back_inserter(zeDrivers));
        std::copy(allDrivers.begin(), allDrivers.end(), std::back_inserter(zesDrivers));
        // The copies alias allDrivers' module handle but do not own a reference to it. Only the
        // copy that actually called LOAD_DRIVER_LIBRARY may release one.
        for (auto &drv : zeDrivers)  drv.libraryLoadCount = 0;
        for (auto &drv : zesDrivers) drv.libraryLoadCount = 0;

        typedef ze_result_t (ZE_APICALL *getVersion_t)(zel_component_version_t *version);
        if( getenv_tobool( "ZE_ENABLE_VALIDATION_LAYER" ) )
        {
            zel_logger->log_info("Validation Layer Enabled");
            std::string validationLayerLibraryPath = create_library_path(MAKE_LAYER_NAME( "ze_validation_layer" ), loaderLibraryPath.c_str());
            if (debugTraceEnabled && debugTraceAdvanced)
                debug_trace_message("Validation Layer Library Path (requested): ", validationLayerLibraryPath);
            validationLayer = LOAD_DRIVER_LIBRARY( validationLayerLibraryPath.c_str() );
            if(validationLayer)
            {
                if (debugTraceEnabled && debugTraceAdvanced) {
#if !defined(_WIN32) && !defined(ANDROID)
                    struct link_map *dlinfo_map;
                    if (dlinfo(validationLayer, RTLD_DI_LINKMAP, &dlinfo_map) == 0) {
                        debug_trace_message("Validation Layer Library Path (resolved): ", std::string(dlinfo_map->l_name));
                    }
#elif defined(_WIN32)
                    char resolved[MAX_PATH];
                    if (GetModuleFileNameA(static_cast<HMODULE>(validationLayer), resolved, MAX_PATH)) {
                        debug_trace_message("Validation Layer Library Path (resolved): ", std::string(resolved));
                    }
#endif
                }
                // Inject this loader instance's logger into the validation layer
                // so both share a single file handle and mutex.
                using SetLoggerFn = void (*)(loader::ZeLogger *);
                auto setLogger = reinterpret_cast<SetLoggerFn>(
                    GET_FUNCTION_PTR(validationLayer, "zelLoaderSetLogger"));
                if (setLogger) {
                    setLogger(zel_logger.get());
                }

                auto getVersion = reinterpret_cast<getVersion_t>(
                    GET_FUNCTION_PTR(validationLayer, "zelLoaderGetVersion"));
                zel_component_version_t compVersion;
                if(getVersion && ZE_RESULT_SUCCESS == getVersion(&compVersion))
                {
                    compVersions.push_back(compVersion);
                }
            } else if (debugTraceEnabled) {
                GET_LIBRARY_ERROR(loadLibraryErrorValue);
                std::string errorMessage = "Load Library of " + std::string(MAKE_LAYER_NAME( "ze_validation_layer" )) + " failed with ";
                debug_trace_message(errorMessage, loadLibraryErrorValue);
                loadLibraryErrorValue.clear();
            }
        }

        if (getenv_tobool( "ZE_ENABLE_TRACING_LAYER" )) {
            zel_logger->log_info("Tracing Layer Enabled");
            tracingLayerEnabled = true;
        }
        std::string tracingLayerLibraryPath = create_library_path(MAKE_LAYER_NAME( "ze_tracing_layer" ), loaderLibraryPath.c_str());
        if (debugTraceEnabled)
            debug_trace_message(debugTraceAdvanced ? "Tracing Layer Library Path (requested): " : "Tracing Layer Library Path: ", tracingLayerLibraryPath);
        tracingLayer = LOAD_DRIVER_LIBRARY( tracingLayerLibraryPath.c_str() );
        if(tracingLayer)
        {
            if (debugTraceEnabled && debugTraceAdvanced) {
#if !defined(_WIN32) && !defined(ANDROID)
                struct link_map *dlinfo_map;
                if (dlinfo(tracingLayer, RTLD_DI_LINKMAP, &dlinfo_map) == 0) {
                    debug_trace_message("Tracing Layer Library Path (resolved): ", std::string(dlinfo_map->l_name));
                }
#elif defined(_WIN32)
                char resolved[MAX_PATH];
                if (GetModuleFileNameA(static_cast<HMODULE>(tracingLayer), resolved, MAX_PATH)) {
                    debug_trace_message("Tracing Layer Library Path (resolved): ", std::string(resolved));
                }
#endif
            }
            auto getVersion = reinterpret_cast<getVersion_t>(
                GET_FUNCTION_PTR(tracingLayer, "zelLoaderGetVersion"));
            zel_component_version_t compVersion;
            if(getVersion && ZE_RESULT_SUCCESS == getVersion(&compVersion))
            {
                compVersions.push_back(compVersion);
            }
        } else if (debugTraceEnabled) {
            GET_LIBRARY_ERROR(loadLibraryErrorValue);
            std::string errorMessage = "Load Library of " + std::string(MAKE_LAYER_NAME( "ze_tracing_layer" )) + " failed with ";
            debug_trace_message(errorMessage, loadLibraryErrorValue);
            loadLibraryErrorValue.clear();
        }

        if( getenv_tobool( "ZET_ENABLE_API_TRACING_EXP" ) ) {
            auto depr_msg = "ZET_ENABLE_API_TRACING_EXP is deprecated. Use ZE_ENABLE_TRACING_LAYER instead";
            zel_logger->log_warning(depr_msg);
            std::cout << depr_msg << std::endl;
        }

        forceIntercept = getenv_tobool( "ZE_ENABLE_LOADER_INTERCEPT" );

        // Default sysmanInstance Drivers to be the zeDrivers list unless zesInit is called during init.
        sysmanInstanceDrivers = &zeDrivers;

        if(forceIntercept || allDrivers.size() > 1){
             intercept_enabled = true;
             zel_logger->log_info("Intercept Enabled");
        }

        driverEnvironmentQueried = true;

        // Set default driver zer DDI table to the first driver in the list before sorting.
        // Leave the zer Driver Handle as nullptr until init when the drivers are sorted and initialized.
        loader::defaultZerDdiTable = &loader::context->zeDrivers.front().dditable.zer;

        zel_logger->log_info("zeInit succeeded");
        return ZE_RESULT_SUCCESS;
    };

    ///////////////////////////////////////////////////////////////////////////////
    context_t::~context_t()
    {
        std::string freeLibraryErrorValue;
        if (validationLayer) {
            auto free_result = FREE_DRIVER_LIBRARY( validationLayer );
            auto failure = FREE_DRIVER_LIBRARY_FAILURE_CHECK(free_result);
            if (debugTraceEnabled && failure) {
                GET_LIBRARY_ERROR(freeLibraryErrorValue);
                if (!freeLibraryErrorValue.empty()) {
                    std::string errorMessage = "Free Library Failed for ze_validation_layer with ";
                    debug_trace_message(errorMessage, freeLibraryErrorValue);
                    freeLibraryErrorValue.clear();
                }
            }
        }
        if (tracingLayer) {
            auto free_result = FREE_DRIVER_LIBRARY( tracingLayer );
            auto failure = FREE_DRIVER_LIBRARY_FAILURE_CHECK(free_result);
            if (debugTraceEnabled && failure) {
                GET_LIBRARY_ERROR(freeLibraryErrorValue);
                if (!freeLibraryErrorValue.empty()) {
                    std::string errorMessage = "Free Library Failed for ze_tracing_layer with ";
                    debug_trace_message(errorMessage, freeLibraryErrorValue);
                    freeLibraryErrorValue.clear();
                }
            }
        }

        // Collect all unique driver handles from allDrivers, zeDrivers, and zesDrivers
        // to ensure we free each library exactly once, avoiding double-free issues
        std::set<HMODULE> uniqueHandles;
        for (const auto& drv : allDrivers) {
            if (drv.handle) {
                uniqueHandles.insert(drv.handle);
            }
        }
        for (const auto& drv : zeDrivers) {
            if (drv.handle) {
                uniqueHandles.insert(drv.handle);
            }
        }
        for (const auto& drv : zesDrivers) {
            if (drv.handle) {
                uniqueHandles.insert(drv.handle);
            }
        }

        // Free each unique driver library exactly once
        for (auto handle : uniqueHandles)
        {
            auto free_result = FREE_DRIVER_LIBRARY( handle );
            auto failure = FREE_DRIVER_LIBRARY_FAILURE_CHECK(free_result);
            if (debugTraceEnabled && failure) {
                GET_LIBRARY_ERROR(freeLibraryErrorValue);
                if (!freeLibraryErrorValue.empty()) {
                    std::string errorMessage = "Free Library Failed With ";
                    debug_trace_message(errorMessage, freeLibraryErrorValue);
                    freeLibraryErrorValue.clear();
                }
            }
        }
        if (loader::loaderDispatch) {
            loader_driver_ddi::zeDestroyDDiDriverTables(loader::loaderDispatch->pCore);
            loader_driver_ddi::zetDestroyDDiDriverTables(loader::loaderDispatch->pTools);
            loader_driver_ddi::zesDestroyDDiDriverTables(loader::loaderDispatch->pSysman);
            loader_driver_ddi::zerDestroyDDiDriverTables(loader::loaderDispatch->pRuntime);
            delete loader::loaderDispatch;
            loader::loaderDispatch = nullptr;
        }
    };

    // A permanently zeroed dispatch table. Every generated intercept function pulls its function
    // pointer out of the object's dditable and returns UNINITIALIZED when that pointer is null, so
    // aiming a retired wrapper here makes all ~340 entry points fail safely with no generated-code
    // changes. It must be a real object and never nullptr: the generated code dereferences the
    // dditable pointer itself without a check.
    dditable_t deadDditable = {};

    bool context_t::isDriverInUse(const dditable_t *dditable)
    {
        // A driver is considered in use if any child object created through it is still live in the
        // loader's object factories. These are the primary stateful resources an application
        // creates and must destroy before a driver can be safely unloaded.
        return ze_context_factory.countByDditable(dditable) > 0
            || ze_command_queue_factory.countByDditable(dditable) > 0
            || ze_command_list_factory.countByDditable(dditable) > 0
            || ze_event_pool_factory.countByDditable(dditable) > 0
            || ze_event_factory.countByDditable(dditable) > 0
            || ze_fence_factory.countByDditable(dditable) > 0
            || ze_image_factory.countByDditable(dditable) > 0
            || ze_sampler_factory.countByDditable(dditable) > 0
            || ze_module_factory.countByDditable(dditable) > 0
            || ze_kernel_factory.countByDditable(dditable) > 0
            || ze_physical_mem_factory.countByDditable(dditable) > 0;
    }

    driver_t *context_t::findDriverSlot(ze_driver_handle_t hDriver)
    {
        if (nullptr == hDriver) {
            return nullptr;
        }
        // Compare against the wrapper objects this loader actually issued. Testing intercept_enabled
        // and casting is not sufficient: whether a handle is wrapped is decided per driver by
        // ZE_DRIVER_DDI_HANDLE_EXT support, so an unwrapped handle would be a wild read.
        auto zeObj = reinterpret_cast<ze_driver_object_t *>(hDriver);
        auto zesObj = reinterpret_cast<zes_driver_object_t *>(hDriver);
        for (auto *vec : { &zeDrivers, &zesDrivers }) {
            for (auto &drv : *vec) {
                for (auto *obj : drv.zeDriverObjects) {
                    if (obj == zeObj) return &drv;
                }
                for (auto *obj : drv.zesDriverObjects) {
                    if (obj == zesObj) return &drv;
                }
            }
        }
        return nullptr;
    }

    void context_t::retireDriverChildObjects(const driver_t &driver)
    {
        const dditable_t *ddi = &driver.dditable;

        // The reverse maps are keyed by the very wrapper objects about to be retired, so purge them
        // first; the deleted-entry lookup in zeCommandListAppend* would otherwise read freed keys.
        {
            std::lock_guard<std::mutex> lock(image_handle_map_lock);
            for (auto it = image_handle_map.begin(); it != image_handle_map.end(); ) {
                if (it->first && it->first->dditable == ddi) it = image_handle_map.erase(it);
                else ++it;
            }
        }
        {
            std::lock_guard<std::mutex> lock(sampler_handle_map_lock);
            for (auto it = sampler_handle_map.begin(); it != sampler_handle_map.end(); ) {
                if (it->first && it->first->dditable == ddi) it = sampler_handle_map.erase(it);
                else ++it;
            }
        }

        // Everything below driver level is retired permanently -- never rebound. A reloaded driver
        // may be a different, newer build with different interfaces, so handing it a device or
        // context handle minted by the previous load would be a use-after-free at best. Most of
        // these factories (devices, fabric vertices/edges, the zes and zet_metric families) never
        // call release(), so without this they would outlive the library holding a stale raw
        // pointer and a dditable aimed at a slot that has come back to life.
        //
        // The wrappers themselves must outlive the unload: the application still holds their
        // handles. Extracting them from the factory frees the raw-handle key, so a reloaded library
        // that reuses the same pointer values cannot collide with a stale entry.
#define RETIRE( factory )                                                                       \
        for (auto &obj : factory.extractByDditable(ddi)) {                                      \
            obj->handle = nullptr;                                                              \
            obj->dditable = &deadDditable;                                                      \
            retiredHandleObjects.emplace_back(std::move(obj));                                  \
        }

        RETIRE(ze_command_list_factory);
        RETIRE(ze_command_queue_factory);
        RETIRE(ze_context_factory);
        RETIRE(ze_device_factory);
        RETIRE(ze_event_factory);
        RETIRE(ze_event_pool_factory);
        RETIRE(ze_executable_graph_factory);
        RETIRE(ze_external_semaphore_ext_factory);
        RETIRE(ze_fabric_edge_factory);
        RETIRE(ze_fabric_vertex_factory);
        RETIRE(ze_fence_factory);
        RETIRE(ze_graph_factory);
        RETIRE(ze_image_factory);
        RETIRE(ze_kernel_factory);
        RETIRE(ze_module_build_log_factory);
        RETIRE(ze_module_factory);
        RETIRE(ze_physical_mem_factory);
        RETIRE(ze_rtas_builder_exp_factory);
        RETIRE(ze_rtas_builder_ext_factory);
        RETIRE(ze_rtas_parallel_operation_exp_factory);
        RETIRE(ze_rtas_parallel_operation_ext_factory);
        RETIRE(ze_sampler_factory);
        RETIRE(zes_device_factory);
        RETIRE(zes_diag_factory);
        RETIRE(zes_engine_factory);
        RETIRE(zes_fabric_port_factory);
        RETIRE(zes_fan_factory);
        RETIRE(zes_firmware_factory);
        RETIRE(zes_freq_factory);
        RETIRE(zes_led_factory);
        RETIRE(zes_mem_factory);
        RETIRE(zes_overclock_factory);
        RETIRE(zes_perf_factory);
        RETIRE(zes_psu_factory);
        RETIRE(zes_pwr_factory);
        RETIRE(zes_ras_factory);
        RETIRE(zes_sched_factory);
        RETIRE(zes_standby_factory);
        RETIRE(zes_temp_factory);
        RETIRE(zes_vf_factory);
        RETIRE(zet_command_list_factory);
        RETIRE(zet_context_factory);
        RETIRE(zet_debug_session_factory);
        RETIRE(zet_device_factory);
        RETIRE(zet_driver_factory);
        RETIRE(zet_kernel_factory);
        RETIRE(zet_metric_decoder_exp_factory);
        RETIRE(zet_metric_factory);
        RETIRE(zet_metric_group_factory);
        RETIRE(zet_metric_programmable_exp_factory);
        RETIRE(zet_metric_query_factory);
        RETIRE(zet_metric_query_pool_factory);
        RETIRE(zet_metric_streamer_factory);
        RETIRE(zet_metric_tracer_exp_factory);
        RETIRE(zet_module_factory);
        RETIRE(zet_tracer_exp_factory);

#undef RETIRE
    }

    void context_t::refreshDefaultZerDdiTable()
    {
        for (auto &drv : zeDrivers) {
            if (drv.slotState == driver_slot_state_t::Loaded) {
                loader::defaultZerDdiTable = &drv.dditable.zer;
                defaultZerDriverHandle = drv.zerDriverDDISupported ? drv.zerDriverHandle : nullptr;
                return;
            }
        }
        // Nothing is loaded. The zer entry points dereference this table without a null check, so
        // it has to point at a real (zeroed) table rather than nullptr.
        loader::defaultZerDdiTable = &deadDditable.zer;
        defaultZerDriverHandle = nullptr;
    }

    ze_result_t context_t::unloadDriver(ze_driver_handle_t hDriver, zel_unload_driver_flags_t flags)
    {
        if (nullptr == hDriver) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }

        std::lock_guard<std::mutex> lock(sortMutex);

        driver_t *slot = findDriverSlot(hDriver);
        if (!slot) {
            // Not one of our wrappers. If it is the raw handle of a driver on the
            // ZE_DRIVER_DDI_HANDLE_EXT path, say so explicitly: that handle is memory owned by the
            // library we would unmap, so there is nothing the loader could keep valid across the
            // unload and nothing to rebind on reload.
            for (auto &drv : zeDrivers) {
                if (drv.slotState != driver_slot_state_t::Unloaded && drv.zerDriverHandle == hDriver) {
                    if (debugTraceEnabled) {
                        debug_trace_message("zelUnloadDriver: driver uses DDI handles, cannot unload ", drv.name);
                    }
                    return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
                }
            }
            if (debugTraceEnabled) {
                debug_trace_message("zelUnloadDriver: driver handle not found", "");
            }
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }

        if (slot->slotState == driver_slot_state_t::Unloaded) {
            return ZE_RESULT_SUCCESS; // idempotent
        }

        const std::string targetName = slot->name;

        // Safety gate: refuse to unload a driver that still owns live child objects, across every
        // copy of the slot. ZEL_UNLOAD_DRIVER_FLAG_FORCE skips it -- which is exactly what a driver
        // whose kernel-mode component has been removed needs, since the application is left holding
        // objects it can never cleanly destroy. Those objects are retired below, so the calls the
        // application makes on them fail with UNINITIALIZED instead of faulting.
        if (!(flags & ZEL_UNLOAD_DRIVER_FLAG_FORCE)) {
            for (auto *vec : { &zeDrivers, &zesDrivers, &allDrivers }) {
                for (auto &drv : *vec) {
                    if (drv.name == targetName && isDriverInUse(&drv.dditable)) {
                        if (debugTraceEnabled) {
                            debug_trace_message("zelUnloadDriver: driver still in use: ", targetName);
                        }
                        return ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE;
                    }
                }
            }
        }

        HMODULE targetModule = nullptr;
        uint32_t pendingFrees = 0;

        // Empty every copy of the slot in place. Slots are never erased and never re-sorted: an
        // object_t stores &driver_t::dditable, a pointer *into* the driver vector, so relocating an
        // element would dangle every live handle of every driver, not just this one. Reusing the
        // slot at a fixed index is also what makes same-handle rebinding possible on reload --
        // refilling this dditable gives the parked wrapper an entirely new dispatch table at an
        // unchanged address.
        for (auto *vec : { &zeDrivers, &zesDrivers, &allDrivers }) {
            for (auto &drv : *vec) {
                if (drv.name != targetName) {
                    continue;
                }

                retireDriverChildObjects(drv);

                // Park the driver wrappers rather than releasing them: the application still holds
                // these handles, and reload rebinds them onto the fresh driver. Releasing here is a
                // use-after-free the moment the application touches the handle again.
                for (auto &obj : ze_driver_factory.extractByDditable(&drv.dditable)) {
                    obj->handle = nullptr;
                    parkedZeDriverObjects.emplace_back(std::move(obj));
                }
                for (auto &obj : zes_driver_factory.extractByDditable(&drv.dditable)) {
                    obj->handle = nullptr;
                    parkedZesDriverObjects.emplace_back(std::move(obj));
                }

                if (!targetModule && drv.handle) {
                    targetModule = drv.handle;
                }
                // Release exactly as many references as this copy took. The module is mapped once
                // per copy that loaded it; free too few and it stays resident, and "reload to a
                // fresh state" would silently be a no-op.
                pendingFrees += drv.libraryLoadCount;
                drv.reloadLibraryLoadCount = drv.libraryLoadCount;
                drv.reloadDdiInitialized = drv.ddiInitialized;
                drv.libraryLoadCount = 0;

                // Zero the dispatch tables in place. The parked wrappers still point here, so every
                // call through them now returns UNINITIALIZED until reload refills it.
                drv.dditable = {};
                drv.properties = {};
                drv.handle = nullptr;
                drv.zerDriverHandle = nullptr;
                drv.zerDriverDDISupported = true;
                drv.driverInuse = false;
                drv.ddiInitialized = false;
                drv.legacyInitAttempted = false;
                drv.driverDDIHandleSupportQueried = false;
                drv.initStatus = ZE_RESULT_ERROR_UNINITIALIZED;
                drv.initSysManStatus = ZE_RESULT_ERROR_UNINITIALIZED;
                drv.initDriversStatus = ZE_RESULT_ERROR_UNINITIALIZED;
                drv.zeddiInitResult = ZE_RESULT_ERROR_UNINITIALIZED;
                drv.zetddiInitResult = ZE_RESULT_ERROR_UNINITIALIZED;
                drv.zesddiInitResult = ZE_RESULT_ERROR_UNINITIALIZED;
                drv.zerddiInitResult = ZE_RESULT_ERROR_UNINITIALIZED;
                // name, driverType, customDriver, pciOrderingRequested, wrapperModePinned and the
                // wrapper registries are deliberately preserved: this is a state, not a verdict.
                drv.slotState = driver_slot_state_t::Unloaded;
            }
        }

        if (targetModule) {
            for (uint32_t i = 0; i < pendingFrees; ++i) {
                auto free_result = FREE_DRIVER_LIBRARY(targetModule);
                auto failure = FREE_DRIVER_LIBRARY_FAILURE_CHECK(free_result);
                if (debugTraceEnabled && failure) {
                    std::string freeLibraryErrorValue;
                    GET_LIBRARY_ERROR(freeLibraryErrorValue);
                    if (!freeLibraryErrorValue.empty()) {
                        debug_trace_message("zelUnloadDriver: Free Library Failed for " + targetName + " with ", freeLibraryErrorValue);
                    }
                }
            }
        }

        refreshDefaultZerDdiTable();

        if (debugTraceEnabled) {
            debug_trace_message("zelUnloadDriver: unloaded driver ", targetName);
        }

        return ZE_RESULT_SUCCESS;
    }

    ze_result_t context_t::reloadDriver(ze_driver_handle_t hDriver)
    {
        if (nullptr == hDriver) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }

        std::lock_guard<std::mutex> lock(sortMutex);

        driver_t *slot = findDriverSlot(hDriver);
        if (!slot) {
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        if (slot->slotState != driver_slot_state_t::Unloaded) {
            return ZE_RESULT_ERROR_INVALID_ARGUMENT;
        }

        const std::string targetName = slot->name;

        // Take a reference of our own before touching any slot state, so a library that cannot be
        // mapped leaves everything exactly as it was. The slot stays Unloaded and reload can be
        // retried -- unloading a driver is a state, never a blacklist.
        auto probeModule = LOAD_DRIVER_LIBRARY(targetName.c_str());
        if (nullptr == probeModule) {
            if (debugTraceEnabled) {
                std::string loadLibraryErrorValue;
                GET_LIBRARY_ERROR(loadLibraryErrorValue);
                debug_trace_message("zelReloadDriver: Load Library of " + targetName + " failed with ", loadLibraryErrorValue);
            }
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }

        ze_result_t result = ZE_RESULT_SUCCESS;
        HMODULE reloadedModule = nullptr;

        for (auto *vec : { &zeDrivers, &zesDrivers, &allDrivers }) {
            for (auto &drv : *vec) {
                if (drv.name != targetName || drv.slotState != driver_slot_state_t::Unloaded) {
                    continue;
                }

                drv.initStatus = ZE_RESULT_SUCCESS;
                drv.initSysManStatus = ZE_RESULT_SUCCESS;
                drv.initDriversStatus = ZE_RESULT_SUCCESS;
                drv.slotState = driver_slot_state_t::Discovered;

                if (drv.reloadLibraryLoadCount == 0 && !drv.reloadDdiInitialized) {
                    continue; // discovery-time alias; fixed up once the module is known
                }

                // Load here rather than letting init_driver do it: init_driver gates the load on
                // driverType matching the requested flags, and a slot that was previously loaded
                // must come back regardless of its type. With handle already set, init_driver goes
                // straight to rebuilding every DDI table from scratch against the new module, so a
                // newer UMD's interfaces are picked up wholesale and no pointer from the previous
                // load survives.
                if (!drv.handle) {
                    auto handle = LOAD_DRIVER_LIBRARY(drv.name.c_str());
                    if (nullptr == handle) {
                        result = ZE_RESULT_ERROR_UNINITIALIZED;
                        continue;
                    }
                    drv.handle = handle;
                    drv.libraryLoadCount++;
                }
                reloadedModule = drv.handle;

                auto res = init_driver(drv, 0, nullptr);
                if (res != ZE_RESULT_SUCCESS) {
                    if (debugTraceEnabled) {
                        debug_trace_message("zelReloadDriver: init_driver failed for " + targetName + " with ", loader::to_string(res));
                    }
                    result = res;
                }
            }
        }

        // Copies that never owned a reference still need to see the module so their (unused) state
        // is consistent with the rest of the slot.
        if (reloadedModule) {
            for (auto *vec : { &zeDrivers, &zesDrivers, &allDrivers }) {
                for (auto &drv : *vec) {
                    if (drv.name == targetName && !drv.handle) {
                        drv.handle = reloadedModule;
                        drv.slotState = driver_slot_state_t::Loaded;
                    }
                }
            }
        }

        // Drop our own reference now that the slot copies hold theirs.
        FREE_DRIVER_LIBRARY(probeModule);

        driver_t *zeSlot = nullptr;
        driver_t *zesSlot = nullptr;
        for (auto &drv : zeDrivers) {
            if (drv.name == targetName) { zeSlot = &drv; break; }
        }
        for (auto &drv : *sysmanInstanceDrivers) {
            if (drv.name == targetName) { zesSlot = &drv; break; }
        }

        if (!zeSlot || !zeSlot->ddiInitialized) {
            if (debugTraceEnabled) {
                debug_trace_message("zelReloadDriver: DDI tables unavailable after reload of ", targetName);
            }
            return result == ZE_RESULT_SUCCESS ? ZE_RESULT_ERROR_UNINITIALIZED : result;
        }

        // Bring the driver up and collect the raw handles it reports now. Preferring
        // zeInitDrivers matches how the loader enumerates today; zeInit/zeDriverGet is the fallback
        // for a driver that only implements the legacy path.
        std::vector<ze_driver_handle_t> freshZeHandles;
        {
            ze_init_driver_type_desc_t permissiveDesc = {};
            permissiveDesc.stype = ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC;
            permissiveDesc.pNext = nullptr;
            permissiveDesc.flags = UINT32_MAX;

            uint32_t count = 0;
            auto pfnInitDrivers = zeSlot->dditable.ze.Global.pfnInitDrivers;
            if (pfnInitDrivers && ZE_RESULT_SUCCESS == pfnInitDrivers(&count, nullptr, &permissiveDesc) && count) {
                freshZeHandles.resize(count);
                if (ZE_RESULT_SUCCESS != pfnInitDrivers(&count, freshZeHandles.data(), &permissiveDesc)) {
                    freshZeHandles.clear();
                } else {
                    freshZeHandles.resize(count);
                }
            }
            if (freshZeHandles.empty() && zeSlot->dditable.ze.Global.pfnInit && zeSlot->dditable.ze.Driver.pfnGet) {
                if (ZE_RESULT_SUCCESS == zeSlot->dditable.ze.Global.pfnInit(0)) {
                    zeSlot->legacyInitAttempted = true;
                    count = 0;
                    if (ZE_RESULT_SUCCESS == zeSlot->dditable.ze.Driver.pfnGet(&count, nullptr) && count) {
                        freshZeHandles.resize(count);
                        if (ZE_RESULT_SUCCESS != zeSlot->dditable.ze.Driver.pfnGet(&count, freshZeHandles.data())) {
                            freshZeHandles.clear();
                        } else {
                            freshZeHandles.resize(count);
                        }
                    }
                }
            }
        }

        std::vector<zes_driver_handle_t> freshZesHandles;
        if (zesSlot && zesSlot->ddiInitialized && zesSlot->dditable.zes.Global.pfnInit &&
            zesSlot->dditable.zes.Driver.pfnGet) {
            if (ZE_RESULT_SUCCESS == zesSlot->dditable.zes.Global.pfnInit(0)) {
                uint32_t count = 0;
                if (ZE_RESULT_SUCCESS == zesSlot->dditable.zes.Driver.pfnGet(&count, nullptr) && count) {
                    freshZesHandles.resize(count);
                    if (ZE_RESULT_SUCCESS != zesSlot->dditable.zes.Driver.pfnGet(&count, freshZesHandles.data())) {
                        freshZesHandles.clear();
                    } else {
                        freshZesHandles.resize(count);
                    }
                }
            }
        }

        // Rebind the parked wrappers onto the fresh raw handles, in issue order. The wrapper
        // pointer -- the value the application holds -- never changes; only what it dispatches to.
        // Its dditable already points at this slot's storage, which init_driver has just refilled
        // from the new module. Re-keying the factory under the fresh raw handle means a subsequent
        // zeInitDrivers/zeDriverGet hands back the identical wrapper.
        {
            size_t next = 0;
            std::vector<ze_driver_object_t *> stillLive;
            for (auto *obj : zeSlot->zeDriverObjects) {
                auto it = std::find_if(parkedZeDriverObjects.begin(), parkedZeDriverObjects.end(),
                    [obj](const std::unique_ptr<ze_driver_object_t> &p) { return p.get() == obj; });
                if (it == parkedZeDriverObjects.end()) {
                    stillLive.push_back(obj);
                    continue;
                }
                if (next < freshZeHandles.size()) {
                    obj->handle = freshZeHandles[next++];
                    obj->dditable = &zeSlot->dditable;
                    ze_driver_factory.adopt(obj->handle, std::move(*it));
                    stillLive.push_back(obj);
                } else {
                    // The reloaded driver reports fewer drivers than the previous build did. There
                    // is nothing to bind this wrapper to, so retire it permanently rather than
                    // leave it aimed at a live slot with a handle from the old load.
                    if (debugTraceEnabled) {
                        debug_trace_message("zelReloadDriver: retiring surplus driver handle for ", targetName);
                    }
                    obj->handle = nullptr;
                    obj->dditable = &deadDditable;
                    retiredHandleObjects.emplace_back(std::move(*it));
                }
                parkedZeDriverObjects.erase(it);
            }
            zeSlot->zeDriverObjects = std::move(stillLive);
        }

        if (zesSlot) {
            size_t next = 0;
            std::vector<zes_driver_object_t *> stillLive;
            for (auto *obj : zesSlot->zesDriverObjects) {
                auto it = std::find_if(parkedZesDriverObjects.begin(), parkedZesDriverObjects.end(),
                    [obj](const std::unique_ptr<zes_driver_object_t> &p) { return p.get() == obj; });
                if (it == parkedZesDriverObjects.end()) {
                    stillLive.push_back(obj);
                    continue;
                }
                if (next < freshZesHandles.size()) {
                    obj->handle = freshZesHandles[next++];
                    obj->dditable = &zesSlot->dditable;
                    zes_driver_factory.adopt(obj->handle, std::move(*it));
                    stillLive.push_back(obj);
                } else {
                    obj->handle = nullptr;
                    obj->dditable = &deadDditable;
                    retiredHandleObjects.emplace_back(std::move(*it));
                }
                parkedZesDriverObjects.erase(it);
            }
            zesSlot->zesDriverObjects = std::move(stillLive);
        }

        // A slot that has ever issued wrapper handles keeps issuing wrapper handles. If the
        // reloaded UMD now advertises ZE_DRIVER_DDI_HANDLE_EXT and we switched to raw handles, the
        // application's original driver handle could not be preserved across the reload at all.
        for (auto *vec : { &zeDrivers, &zesDrivers, &allDrivers }) {
            for (auto &drv : *vec) {
                if (drv.name == targetName) {
                    drv.wrapperModePinned = true;
                    drv.slotState = driver_slot_state_t::Loaded;
                }
            }
        }

        // Leave driverDDIHandleSupportQueried false so the next enumeration re-queries extension
        // and driver properties from the new module rather than trusting the old build's answers.
        refreshDefaultZerDdiTable();

        if (debugTraceEnabled) {
            debug_trace_message("zelReloadDriver: reloaded driver ", targetName);
        }

        return result;
    }

    void context_t::add_loader_version(){
        zel_component_version_t compVersion = {};
        string_copy_s(compVersion.component_name, LOADER_COMP_NAME, ZEL_COMPONENT_STRING_SIZE - 1);
        compVersion.spec_version = ZE_API_VERSION_CURRENT;
        compVersion.component_lib_version.major = LOADER_VERSION_MAJOR;
        compVersion.component_lib_version.minor = LOADER_VERSION_MINOR;
        compVersion.component_lib_version.patch = LOADER_VERSION_PATCH;

        compVersions.push_back(compVersion);
    }

}
