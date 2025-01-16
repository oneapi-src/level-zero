/*
 *
 * Copyright (C) 2019-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "ze_loader_internal.h"

#include "driver_discovery.h"
#include <iostream>

#ifdef __linux__
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif // __linux__

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    context_t *context;

    void context_t::debug_trace_message(std::string message, std::string result) {
        if (zel_logger->log_to_console){
            std::string debugTracePrefix = "ZE_LOADER_DEBUG_TRACE:";
            std::cerr << debugTracePrefix << message << result << std::endl;
        }

        zel_logger->log_trace(message + result);
    };

    std::string to_string(const ze_result_t result) {
        if (result == ZE_RESULT_SUCCESS) {
            return "ZE_RESULT_SUCCESS";
        } else if (result == ZE_RESULT_NOT_READY) {
            return "ZE_RESULT_NOT_READY";
        } else if (result == ZE_RESULT_ERROR_UNINITIALIZED) {
            return "ZE_RESULT_ERROR_UNINITIALIZED";
        } else if (result == ZE_RESULT_ERROR_DEVICE_LOST) {
            return "ZE_RESULT_ERROR_DEVICE_LOST";
        } else if (result == ZE_RESULT_ERROR_INVALID_ARGUMENT) {
            return "ZE_RESULT_ERROR_INVALID_ARGUMENT";
        } else if (result == ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY) {
            return "ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY";
        } else if (result == ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY) {
            return "ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY";
        } else if (result == ZE_RESULT_ERROR_MODULE_BUILD_FAILURE) {
            return "ZE_RESULT_ERROR_MODULE_BUILD_FAILURE";
        } else if (result == ZE_RESULT_ERROR_MODULE_LINK_FAILURE) {
            return "ZE_RESULT_ERROR_MODULE_LINK_FAILURE";
        } else if (result == ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS) {
            return "ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS";
        } else if (result == ZE_RESULT_ERROR_NOT_AVAILABLE) {
            return "ZE_RESULT_ERROR_NOT_AVAILABLE";
        } else if (result == ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE) {
            return "ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE";
        } else if (result == ZE_RESULT_WARNING_DROPPED_DATA) {
            return "ZE_RESULT_WARNING_DROPPED_DATA";
        } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_VERSION) {
            return "ZE_RESULT_ERROR_UNSUPPORTED_VERSION";
        } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE) {
            return "ZE_RESULT_ERROR_UNSUPPORTED_FEATURE";
        } else if (result == ZE_RESULT_ERROR_INVALID_NULL_HANDLE) {
            return "ZE_RESULT_ERROR_INVALID_NULL_HANDLE";
        } else if (result == ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE) {
            return "ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE";
        } else if (result == ZE_RESULT_ERROR_INVALID_NULL_POINTER) {
            return "ZE_RESULT_ERROR_INVALID_NULL_POINTER";
        } else if (result == ZE_RESULT_ERROR_INVALID_SIZE) {
            return "ZE_RESULT_ERROR_INVALID_SIZE";
        } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_SIZE) {
            return "ZE_RESULT_ERROR_UNSUPPORTED_SIZE";
        } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT) {
            return "ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT";
        } else if (result == ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT) {
            return "ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT";
        } else if (result == ZE_RESULT_ERROR_INVALID_ENUMERATION) {
            return "ZE_RESULT_ERROR_INVALID_ENUMERATION";
        } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION) {
            return "ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION";
        } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT) {
            return "ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT";
        } else if (result == ZE_RESULT_ERROR_INVALID_NATIVE_BINARY) {
            return "ZE_RESULT_ERROR_INVALID_NATIVE_BINARY";
        } else if (result == ZE_RESULT_ERROR_INVALID_GLOBAL_NAME) {
            return "ZE_RESULT_ERROR_INVALID_GLOBAL_NAME";
        } else if (result == ZE_RESULT_ERROR_INVALID_KERNEL_NAME) {
            return "ZE_RESULT_ERROR_INVALID_KERNEL_NAME";
        } else if (result == ZE_RESULT_ERROR_INVALID_FUNCTION_NAME) {
            return "ZE_RESULT_ERROR_INVALID_FUNCTION_NAME";
        } else if (result == ZE_RESULT_ERROR_INVALID_GROUP_SIZE_DIMENSION) {
            return "ZE_RESULT_ERROR_INVALID_GROUP_SIZE_DIMENSION";
        } else if (result == ZE_RESULT_ERROR_INVALID_GLOBAL_WIDTH_DIMENSION) {
            return "ZE_RESULT_ERROR_INVALID_GLOBAL_WIDTH_DIMENSION";
        } else if (result == ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_INDEX) {
            return "ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_INDEX";
        } else if (result == ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_SIZE) {
            return "ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_SIZE";
        } else if (result == ZE_RESULT_ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE) {
            return "ZE_RESULT_ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE";
        } else if (result == ZE_RESULT_ERROR_INVALID_MODULE_UNLINKED) {
            return "ZE_RESULT_ERROR_INVALID_MODULE_UNLINKED";
        } else if (result == ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE) {
            return "ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE";
        } else if (result == ZE_RESULT_ERROR_OVERLAPPING_REGIONS) {
            return "ZE_RESULT_ERROR_OVERLAPPING_REGIONS";
        } else if (result == ZE_RESULT_ERROR_UNKNOWN) {
            return "ZE_RESULT_ERROR_UNKNOWN";
        } else {
            return std::to_string(static_cast<int>(result));
        }
    }

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

    bool driverSortComparitor(const driver_t &a, const driver_t &b) {
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
     * 5. Sorts the drivers in ascending order of driver type using `driverSortComparitor`.
     * 6. Logs the sorted driver list if debug tracing is enabled.
     * 7. If no drivers are left, returns `ZE_RESULT_ERROR_UNINITIALIZED`.
     * 8. Returns `ZE_RESULT_SUCCESS` if at least one driver is successfully initialized.
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

        // Sort drivers in ascending order of driver type unless ZE_ENABLE_PCI_ID_DEVICE_ORDER, then in decending order with MIXED and OTHER at the end.
        std::sort(drivers->begin(), drivers->end(), driverSortComparitor);

        if (debugTraceEnabled) {
            std::string message = "Drivers after sorting:";
            for (const auto& driver : *drivers) {
                message += "\nDriver Type: " + std::to_string(driver.driverType) + " Driver Name: " + driver.name;
            }
            debug_trace_message(message, "");
        }

        if(drivers->size() == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;

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
            auto getTableResult = getTable(ZE_API_VERSION_CURRENT, &global);
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
            if (driver.initStatus != ZE_RESULT_SUCCESS) {
                res = driver.initStatus;
            }
            if (debugTraceEnabled) {
                std::string message = "init driver " + driver.name + " zesInit(" + loader::to_string(flags) + ") returning ";
                debug_trace_message(message, loader::to_string(res));
            }
            return res;
        } else {
            uint32_t pCount = 0;
            std::vector<ze_driver_handle_t> driverHandles;

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
                if (driver.initStatus != ZE_RESULT_SUCCESS) {
                    res = driver.initStatus;
                    if (debugTraceEnabled) {
                        std::string message = "init driver " + driver.name + " zeInit(" + loader::to_string(flags) + ") returning ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    return res;
                }
                res = driver.dditable.ze.Driver.pfnGet(&pCount, nullptr);
                // Verify that this driver successfully init in the call above.
                if (res != ZE_RESULT_SUCCESS) {
                    if (debugTraceEnabled) {
                        std::string message = "init driver " + driver.name + " zeDriverGet(" + loader::to_string(desc) + ") returning ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    return res;
                }
                driverHandles.resize(pCount);
                res = driver.dditable.ze.Driver.pfnGet(&pCount, driverHandles.data());
                // Verify that this driver successfully init in the call above.
                if (res != ZE_RESULT_SUCCESS) {
                    if (debugTraceEnabled) {
                        std::string message = "init driver " + driver.name + " zeDriverGet(" + loader::to_string(desc) + ") returning ";
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

                pCount = 0;
                // Use the previously init ddi table pointer to zeInit to allow for intercept of the zeInit calls
                ze_result_t res = globalInitStored->pfnInitDrivers(&pCount, nullptr, desc);
                // Verify that this driver successfully init in the call above.
                if (driver.initDriversStatus != ZE_RESULT_SUCCESS) {
                    res = driver.initDriversStatus;
                    if (debugTraceEnabled) {
                        std::string message = "init driver " + driver.name + " zeInitDrivers(" + loader::to_string(desc) + ") returning ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    return res;
                }

                // Reset pCount to 0 when calling the driver init function from the driver's ddi table.
                pCount = 0;
                res = driver.dditable.ze.Global.pfnInitDrivers(&pCount, nullptr, desc);
                // Verify that this driver successfully init in the call above.
                if (res != ZE_RESULT_SUCCESS) {
                    if (debugTraceEnabled) {
                        std::string message = "init driver " + driver.name + " zeInitDrivers(" + loader::to_string(desc) + ") returning ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    return res;
                }
                driverHandles.resize(pCount);
                // Use the driver's init function to query the driver handles and read the properties.
                res = driver.dditable.ze.Global.pfnInitDrivers(&pCount, driverHandles.data(), desc);
                // Verify that this driver successfully init in the call above.
                if (res != ZE_RESULT_SUCCESS) {
                    if (debugTraceEnabled) {
                        std::string message = "init driver " + driver.name + " zeInitDrivers(" + loader::to_string(desc) + ") returning ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    return res;
                }
            }

            for (auto handle : driverHandles) {
                ze_driver_properties_t properties;
                ze_result_t res = driver.dditable.ze.Driver.pfnGetProperties(handle, &properties);
                if (res != ZE_RESULT_SUCCESS) {
                    if (debugTraceEnabled) {
                        std::string message = "init driver " + driver.name + " failed, zeDriverGetProperties returned ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    return res;
                }
                driver.properties = properties;
                uint32_t deviceCount = 0;
                res = driver.dditable.ze.Device.pfnGet( handle, &deviceCount, nullptr );
                if( ZE_RESULT_SUCCESS != res ) {
                    if (debugTraceEnabled) {
                        std::string message = "init driver " + driver.name + " failed, zeDeviceGet returned ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    return res;
                }
                if (deviceCount == 0) {
                    if (debugTraceEnabled) {
                        std::string message = "init driver " + driver.name + " failed, zeDeviceGet returned 0 devices";
                        debug_trace_message(message, "");
                    }
                    return ZE_RESULT_ERROR_UNINITIALIZED;
                }
                std::vector<ze_device_handle_t> deviceHandles(deviceCount);
                res = driver.dditable.ze.Device.pfnGet( handle, &deviceCount, deviceHandles.data() );
                if( ZE_RESULT_SUCCESS != res ) {
                    if (debugTraceEnabled) {
                        std::string message = "init driver " + driver.name + " failed, zeDeviceGet returned ";
                        debug_trace_message(message, loader::to_string(res));
                    }
                    return res;
                }
                bool integratedGPU = false;
                bool discreteGPU = false;
                bool other = false;
                for( auto device : deviceHandles ) {
                    ze_device_properties_t deviceProperties;
                    res = driver.dditable.ze.Device.pfnGetProperties(device, &deviceProperties);
                    if( ZE_RESULT_SUCCESS != res ) {
                        if (debugTraceEnabled) {
                            std::string message = "init driver " + driver.name + " failed, zeDeviceGetProperties returned ";
                            debug_trace_message(message, loader::to_string(res));
                        }
                        return res;
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
            return ZE_RESULT_SUCCESS;
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    ze_result_t context_t::init()
    {
        if (driverEnvironmentQueried) {
            return ZE_RESULT_SUCCESS;
        }
        debugTraceEnabled = getenv_tobool( "ZE_ENABLE_LOADER_DEBUG_TRACE" );
        auto discoveredDrivers = discoverEnabledDrivers();
        std::string loadLibraryErrorValue;

        auto log_directory = getenv_string("ZEL_LOADER_LOG_DIR");
        if (log_directory.empty()) {
            std::string home_dir;
#ifdef _WIN32
            home_dir = getenv_string("USERPROFILE");
            if (home_dir == ""){
                auto home_drive = getenv_string("HOMEDRIVE");
                auto home_path = getenv_string("HOMEPATH");
                if ((home_drive != "") && (home_path != "")) {
                    home_dir = home_drive + home_path;
                } else {
                    home_dir = ".";
                }
            }
            log_directory = home_dir + "\\" + LOADER_LOG_FILE_DIRECTORY;
#else
            home_dir = getenv_string("HOME");

            if (home_dir == "") {
                auto pwdir = getpwuid(getuid())->pw_dir;
                home_dir = (pwdir == NULL) ? "." : std::string(pwdir);
            }
            log_directory = home_dir + "/" + LOADER_LOG_FILE_DIRECTORY;
#endif
        }
        auto loader_file = getenv_string("ZEL_LOADER_LOG_FILE");
        if (loader_file.empty()){
            loader_file = LOADER_LOG_FILE;
        } else {
            auto log_depr_msg = "ZEL_LOADER_LOG_FILE will be deprecated in a future release";
            std::cout << log_depr_msg << std::endl;
        }

        std::string full_log_file_path = "";
#ifdef _WIN32
        full_log_file_path = log_directory + "\\" + loader_file;
#else
        full_log_file_path = log_directory + "/" + loader_file;
#endif
        auto logging_enabled = getenv_tobool( "ZEL_ENABLE_LOADER_LOGGING" );

        auto log_level = getenv_string("ZEL_LOADER_LOGGING_LEVEL");
        zel_logger =  std::make_shared<Logger>("ze_loader", full_log_file_path, !log_level.empty() ? log_level : "warn", logging_enabled);
        if ((log_level == "trace") && !debugTraceEnabled) {
            debugTraceEnabled = true;
            zel_logger->log_to_console = false;
        }

        if (!logging_enabled){
            zel_logger->set_level(spdlog::level::off);
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
#ifndef _WIN32
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
