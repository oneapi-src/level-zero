/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "ze_loader_utils.h"

#include "driver_discovery.h"
#include <iostream>

#ifdef __linux__
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif // __linux__

namespace loader
{
    ze_handle_t* loaderDispatch = nullptr;
    ze_dditable_t* loaderZeDdiTable = nullptr;
    zet_dditable_t* loaderZetDdiTable = nullptr;
    zes_dditable_t* loaderZesDdiTable = nullptr;
    zer_dditable_t *defaultZerDdiTable = nullptr;
    ///////////////////////////////////////////////////////////////////////////////
    context_t *context;

    void context_t::debug_trace_message(std::string message, std::string result) {
        if (zel_logger->log_to_console){
            std::string debugTracePrefix = "ZE_LOADER_DEBUG_TRACE:";
            std::cerr << debugTracePrefix << message << result << std::endl;
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
        *drivers = orderedDrivers;

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
                if (debugTraceEnabled) {
                    std::string message = "driverSorting " + driver.name + " zeDriverGet and zeInitDrivers not supported, skipping driver";
                    debug_trace_message(message, loader::to_string(res));
                }
                continue;
            }

            for (auto handle : driverHandles) {
                uint32_t extensionCount = 0;
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
                    if (driver.zerDriverHandle != nullptr) {
                        driver.zerDriverHandle = reinterpret_cast<ze_driver_handle_t>(
                            loader::context->ze_driver_factory.getInstance(driver.zerDriverHandle, &driver.dditable));
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
                    } else {
                        other = true;
                    }
                }
                if (integratedGPU && discreteGPU && other) {
                    driver.driverType = ZEL_DRIVER_TYPE_MIXED;
                } else if (integratedGPU && discreteGPU) {
                    driver.driverType = ZEL_DRIVER_TYPE_GPU;
                } else if (integratedGPU) {
                    driver.driverType = ZEL_DRIVER_TYPE_INTEGRATED_GPU;
                } else if (discreteGPU) {
                    driver.driverType = ZEL_DRIVER_TYPE_DISCRETE_GPU;
                } else if (other) {
                    driver.driverType = ZEL_DRIVER_TYPE_OTHER;
                }
            }
        }

        // Sort drivers in ascending order of driver type unless ZE_ENABLE_PCI_ID_DEVICE_ORDER, then in decending order with MIXED and OTHER at the end.
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

    /**
     * @brief Checks and initializes drivers based on the provided flags and descriptors.
     *
     * This function performs the following operations:
     * 1. If debug tracing is enabled, logs the input parameters.
     * 2. If `zeInitDrivers` is not supported by the driver and it is called first, returns `ZE_RESULT_ERROR_UNINITIALIZED`.
     * 3. Determines the appropriate driver vector (`zeDrivers` or `zesDrivers`) based on the input parameters.
     * 4. Iterates over the drivers and attempts to initialize each driver:
     *    - If initialization fails and the driver is not in use, removes the driver from the list.
     *    - If the number of drivers becomes one and interception is not forced, sets the `requireDdiReinit` flag to true.
     *    - If the initialization fails and `return_first_driver_result` is true, returns the result immediately.
     *    - If initialization succeeds, marks the driver as in use.
     * 5. If no drivers are left, returns `ZE_RESULT_ERROR_UNINITIALIZED`.
     * 6. Returns `ZE_RESULT_SUCCESS` if at least one driver is successfully initialized.
     *
     * @param flags Initialization flags.
     * @param desc Driver type descriptor (optional).
     * @param globalInitStored Pointer to global DDI table for initialization.
     * @param sysmanGlobalInitStored Pointer to Sysman global DDI table for initialization.
     * @param requireDdiReinit Pointer to a boolean flag indicating if DDI reinitialization is required.
     * @param sysmanOnly Boolean flag indicating if only Sysman drivers should be checked.
     * @return `ZE_RESULT_SUCCESS` if at least one driver is successfully initialized, otherwise an appropriate error code.
     */
    ze_result_t context_t::check_drivers(ze_init_flags_t flags, ze_init_driver_type_desc_t* desc, ze_global_dditable_t *globalInitStored, zes_global_dditable_t *sysmanGlobalInitStored, bool *requireDdiReinit, bool sysmanOnly) {
        if (debugTraceEnabled) {
            if (desc) {
                std::string message = "check_drivers(" + std::string("desc->flags=") + loader::to_string(desc) + ")";
                debug_trace_message(message, "");
            } else {
                std::string message = "check_drivers(" + std::string("flags=") + loader::to_string(flags) + ")";
                debug_trace_message(message, "");
            }
        }
        // If zeInitDrivers is not supported by this driver, but zeInitDrivers is called first, then return uninitialized.
        if (desc && !loader::context->initDriversSupport) {
            if (debugTraceEnabled) {
                std::string message = "zeInitDrivers called first, but not supported by driver, returning uninitialized.";
                debug_trace_message(message, "");
            }
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }


        bool return_first_driver_result=false;
        std::string initName = "zeInit";
        driver_vector_t *drivers = &zeDrivers;
        // If desc is set, then this is zeInitDrivers.
        if (desc) {
            initName = "zeInitDrivers";
        }
        // If this is sysmanOnly check_drivers, then zesInit is being called and we need to use zesDrivers.
        if (sysmanOnly) {
            drivers = &zesDrivers;
            initName = "zesInit";
        }
        if(drivers->size()==1) {
            return_first_driver_result=true;
        }
        bool pciOrderingRequested = getenv_tobool( "ZE_ENABLE_PCI_ID_DEVICE_ORDER" );
        loader::context->instrumentationEnabled = getenv_tobool( "ZET_ENABLE_PROGRAM_INSTRUMENTATION" );

        for(auto it = drivers->begin(); it != drivers->end(); )
        {
            it->pciOrderingRequested = pciOrderingRequested;
            std::string freeLibraryErrorValue;
            ze_result_t result = init_driver(*it, flags, desc, globalInitStored, sysmanGlobalInitStored, sysmanOnly);
            if(result != ZE_RESULT_SUCCESS) {
                // If the driver has already been init and handles are to be read, then this driver cannot be removed from the list.
                // Also, if any driver supports zeInitDrivers, then no driver can be removed to allow for different sets of drivers.
                if (!it->driverInuse && !loader::context->initDriversSupport) {
                    if (debugTraceEnabled) {
                        std::string errorMessage = "Check Drivers Failed on " + it->name + " , driver will be removed. " + initName + " failed with ";
                        debug_trace_message(errorMessage, loader::to_string(result));
                    }
                    it = drivers->erase(it);
                    // If the number of drivers is now ==1, then we need to reinit the ddi tables to pass through.
                    // If ZE_ENABLE_LOADER_INTERCEPT is set to 1, then even if drivers were removed, don't reinit the ddi tables.
                    if (drivers->size() == 1 && !loader::context->forceIntercept) {
                        *requireDdiReinit = true;
                    }
                } else {
                    it++;
                }
                if(return_first_driver_result)
                    return result;
            } else {
                // If this is a single driver system, then the first success for this driver needs to be set.
                it->driverInuse = true;
                it++;
            }
        }

        if(drivers->size() == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // Set default driver handle and DDI table to the first driver in the list before sorting.
        loader::context->defaultZerDriverHandle = loader::context->zeDrivers.front().zerDriverHandle;
        loader::defaultZerDdiTable = &loader::context->zeDrivers.front().dditable.zer;
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t context_t::init_driver(driver_t &driver, ze_init_flags_t flags, ze_init_driver_type_desc_t* desc, ze_global_dditable_t *globalInitStored, zes_global_dditable_t *sysmanGlobalInitStored, bool sysmanOnly) {
        if (sysmanOnly) {
            auto getTable = reinterpret_cast<zes_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(driver.handle, "zesGetGlobalProcAddrTable"));
            if(!getTable) {
                if (debugTraceEnabled) {
                    std::string errorMessage = "init driver " + driver.name + " failed, zesGetGlobalProcAddrTable function pointer null. Returning ";
                    debug_trace_message(errorMessage, loader::to_string(ZE_RESULT_ERROR_UNINITIALIZED));
                }
                return ZE_RESULT_ERROR_UNINITIALIZED;
            }

            zes_global_dditable_t global;
            auto getTableResult = getTable(this->configured_version, &global);
            if(getTableResult != ZE_RESULT_SUCCESS) {
                if (debugTraceEnabled) {
                    std::string errorMessage = "init driver " + driver.name + " failed, zesGetGlobalProcAddrTable() failed with ";
                    debug_trace_message(errorMessage, loader::to_string(getTableResult));
                }
                return ZE_RESULT_ERROR_UNINITIALIZED;
            }

            if(nullptr == global.pfnInit) {
                if (debugTraceEnabled) {
                    std::string errorMessage = "init driver " + driver.name + " failed, zesInit function pointer null. Returning ";
                    debug_trace_message(errorMessage, loader::to_string(ZE_RESULT_ERROR_UNINITIALIZED));
                }
                return ZE_RESULT_ERROR_UNINITIALIZED;
            }

            // Use the previously init ddi table pointer to zesInit to allow for intercept of the zesInit calls
            ze_result_t res = sysmanGlobalInitStored->pfnInit(flags);
            // Verify that this driver successfully init in the call above.
            if (driver.initSysManStatus != ZE_RESULT_SUCCESS) {
                res = driver.initSysManStatus;
            }
            if (debugTraceEnabled) {
                std::string message = "init driver " + driver.name + " zesInit(" + loader::to_string(flags) + ") returning ";
                debug_trace_message(message, loader::to_string(res));
            }
            return res;
        } else {
            if (!desc) {
                auto pfnInit = driver.dditable.ze.Global.pfnInit;
                if(nullptr == pfnInit || globalInitStored->pfnInit == nullptr) {
                    if (debugTraceEnabled) {
                        std::string errorMessage = "init driver " + driver.name + " failed, zeInit function pointer null. Returning ";
                        debug_trace_message(errorMessage, loader::to_string(ZE_RESULT_ERROR_UNINITIALIZED));
                    }
                    return ZE_RESULT_ERROR_UNINITIALIZED;
                }

                // Use the previously init ddi table pointer to zeInit to allow for intercept of the zeInit calls
                ze_result_t res = globalInitStored->pfnInit(flags);
                // Verify that this driver successfully init in the call above.
                if (res != ZE_RESULT_SUCCESS || driver.initStatus != ZE_RESULT_SUCCESS) {
                    if (driver.initStatus != ZE_RESULT_SUCCESS)
                        res = driver.initStatus;
                    if (debugTraceEnabled) {
                        std::string message = "init driver (global ddi) " + driver.name + " zeInit(" + loader::to_string(flags) + ") returning ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    return res;
                }
            } else {
                auto pfnInitDrivers = driver.dditable.ze.Global.pfnInitDrivers;
                if(nullptr == pfnInitDrivers || globalInitStored->pfnInitDrivers == nullptr) {
                    if (debugTraceEnabled) {
                        std::string errorMessage = "init driver " + driver.name + " failed, pfnInitDrivers function pointer null. Returning ";
                        debug_trace_message(errorMessage, loader::to_string(ZE_RESULT_ERROR_UNINITIALIZED));
                    }
                    return ZE_RESULT_ERROR_UNINITIALIZED;
                }

                uint32_t pCount = 0;
                // Use the previously init ddi table pointer to zeInitDrivers to allow for intercept of the zeInitDrivers calls
                ze_result_t res = globalInitStored->pfnInitDrivers(&pCount, nullptr, desc);
                // Verify that this driver successfully init in the call above.
                if (res != ZE_RESULT_SUCCESS || driver.initDriversStatus != ZE_RESULT_SUCCESS) {
                    if (driver.initDriversStatus != ZE_RESULT_SUCCESS)
                        res = driver.initDriversStatus;
                    if (debugTraceEnabled) {
                        std::string message = "init driver (global ddi) " + driver.name + " zeInitDrivers(" + loader::to_string(desc) + ") returning ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    return res;
                }
            }
            return ZE_RESULT_SUCCESS;
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    ze_result_t context_t::init()
    {
        if (driverEnvironmentQueried) {
            return ZE_RESULT_SUCCESS;
        }
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
        loader::loaderZeDdiTable = new ze_dditable_t();
        loader::loaderZetDdiTable = new zet_dditable_t();
        loader::loaderZesDdiTable = new zes_dditable_t();
        loader::defaultZerDdiTable = new zer_dditable_t();
        debugTraceEnabled = getenv_tobool( "ZE_ENABLE_LOADER_DEBUG_TRACE" );
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

        zel_logger = createLogger();

        if ((getenv_string("ZEL_LOADER_LOGGING_LEVEL") == "trace") && !debugTraceEnabled) {
            debugTraceEnabled = true;
            zel_logger->log_to_console = false;
        }

        if (zel_logger->logging_enabled)
            zel_logger->get_base_logger()->info("Loader Version {}.{}.{} {}", LOADER_VERSION_MAJOR, LOADER_VERSION_MINOR, LOADER_VERSION_PATCH, LOADER_VERSION_SHA);

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
            debug_trace_message("Using Loader Library Path: ", loaderLibraryPath);

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
            auto handle = LOAD_DRIVER_LIBRARY( create_library_path( MAKE_LIBRARY_NAME( "ze_null", L0_LOADER_VERSION ), loaderLibraryPath.c_str()).c_str());
            if (debugTraceEnabled) {
                std::string message = "ze_null Driver Init";
                debug_trace_message(message, "");
            }
            if( NULL != handle )
            {
                allDrivers.emplace_back();
                allDrivers.rbegin()->handle = handle;
                allDrivers.rbegin()->name = "ze_null";
            } else if (debugTraceEnabled) {
                GET_LIBRARY_ERROR(loadLibraryErrorValue);
                std::string errorMessage = "Load Library of " + create_library_path( MAKE_LIBRARY_NAME( "ze_null", L0_LOADER_VERSION ), loaderLibraryPath.c_str()) + " failed with ";
                debug_trace_message(errorMessage, loadLibraryErrorValue);
                loadLibraryErrorValue.clear();
            }
        }

        for( auto name : discoveredDrivers )
        {
            auto handle = LOAD_DRIVER_LIBRARY( name.c_str() );
            if( NULL != handle )
            {
                if (debugTraceEnabled) {
                    std::string message = "Loading Driver " + name + " succeeded";
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
                allDrivers.rbegin()->name = name;
            } else if (debugTraceEnabled) {
                GET_LIBRARY_ERROR(loadLibraryErrorValue);
                std::string errorMessage = "Load Library of " + name + " failed with ";
                debug_trace_message(errorMessage, loadLibraryErrorValue);
                loadLibraryErrorValue.clear();
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

        typedef ze_result_t (ZE_APICALL *getVersion_t)(zel_component_version_t *version);
        if( getenv_tobool( "ZE_ENABLE_VALIDATION_LAYER" ) )
        {
            zel_logger->log_info("Validation Layer Enabled");
            std::string validationLayerLibraryPath = create_library_path(MAKE_LAYER_NAME( "ze_validation_layer" ), loaderLibraryPath.c_str());
            validationLayer = LOAD_DRIVER_LIBRARY( validationLayerLibraryPath.c_str() );
            if(validationLayer)
            {
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
            debug_trace_message("Tracing Layer Library Path: ", tracingLayerLibraryPath);
        tracingLayer = LOAD_DRIVER_LIBRARY( tracingLayerLibraryPath.c_str() );
        if(tracingLayer)
        {
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

        for( auto& drv : allDrivers )
        {
            if (drv.handle) {
                auto free_result = FREE_DRIVER_LIBRARY( drv.handle );
                auto failure = FREE_DRIVER_LIBRARY_FAILURE_CHECK(free_result);
                if (debugTraceEnabled && failure) {
                    GET_LIBRARY_ERROR(freeLibraryErrorValue);
                    if (!freeLibraryErrorValue.empty()) {
                        std::string errorMessage = "Free Library Failed for " + drv.name + " With ";
                        debug_trace_message(errorMessage, freeLibraryErrorValue);
                        freeLibraryErrorValue.clear();
                    }
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
