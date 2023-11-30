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

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    context_t *context;

    void context_t::debug_trace_message(std::string message, std::string result) {
        std::string debugTracePrefix = "ZE_LOADER_DEBUG_TRACE:";
        std::cerr << debugTracePrefix << message << result << std::endl;
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

    ze_result_t context_t::check_drivers(ze_init_flags_t flags) {
        if (debugTraceEnabled) {
            std::string message = "check_drivers(" + std::string("flags=") + loader::to_string(flags) + ")";
            debug_trace_message(message, "");
        }
        bool return_first_driver_result=false;
        if(drivers.size()==1) {
            return_first_driver_result=true;
        }

        for(auto it = drivers.begin(); it != drivers.end(); )
        {
            std::string freeLibraryErrorValue;
            ze_result_t result = init_driver(*it, flags);
            if(result != ZE_RESULT_SUCCESS) {
                if (it->handle) {
                    auto free_result = FREE_DRIVER_LIBRARY(it->handle);
                    auto failure = FREE_DRIVER_LIBRARY_FAILURE_CHECK(free_result);
                    if (debugTraceEnabled && failure) {
                        GET_LIBRARY_ERROR(freeLibraryErrorValue);
                        if (!freeLibraryErrorValue.empty()) {
                            std::string errorMessage = "Free Library Failed on " + it->name + " with ";
                            debug_trace_message(errorMessage, freeLibraryErrorValue);
                            freeLibraryErrorValue.clear();
                        }
                    }
                }
                if (debugTraceEnabled) {
                    std::string errorMessage = "Check Drivers Failed on " + it->name + " , driver will be removed. zeInit failed with ";
                    debug_trace_message(errorMessage, loader::to_string(result));
                }
                it = drivers.erase(it);
                if(return_first_driver_result)
                    return result;
            }
            else {
                it++;
            }
        }

        if(drivers.size() == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;

        return ZE_RESULT_SUCCESS;
    }

    ze_result_t context_t::init_driver(driver_t driver, ze_init_flags_t flags) {

        auto getTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(driver.handle, "zeGetGlobalProcAddrTable"));
        if(!getTable) {
            if (debugTraceEnabled) {
                std::string errorMessage = "init driver " + driver.name + " failed, zeGetGlobalProcAddrTable function pointer null. Returning ";
                debug_trace_message(errorMessage, loader::to_string(ZE_RESULT_ERROR_UNINITIALIZED));
            }
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        
        ze_global_dditable_t global;
        auto getTableResult = getTable(ZE_API_VERSION_CURRENT, &global);
        if(getTableResult != ZE_RESULT_SUCCESS) {
            if (debugTraceEnabled) {
                std::string errorMessage = "init driver " + driver.name + " failed, zeGetGlobalProcAddrTable() failed with ";
                debug_trace_message(errorMessage, loader::to_string(getTableResult));
            }
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        
        if(nullptr == global.pfnInit) {
            if (debugTraceEnabled) {
                std::string errorMessage = "init driver " + driver.name + " failed, zeInit function pointer null. Returning ";
                debug_trace_message(errorMessage, loader::to_string(ZE_RESULT_ERROR_UNINITIALIZED));
            }
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }

        if(nullptr != validationLayer) {
            getTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(validationLayer, "zeGetGlobalProcAddrTable") );
            if(!getTable) {
                if (debugTraceEnabled) {
                    std::string errorMessage = "init driver " + driver.name + " failed, zeGetGlobalProcAddrTable function pointer null with validation layer. Returning ";
                    debug_trace_message(errorMessage, loader::to_string(ZE_RESULT_ERROR_UNINITIALIZED));
                }
                return ZE_RESULT_ERROR_UNINITIALIZED;
            }
            getTableResult = getTable( version, &global);
            if(getTableResult != ZE_RESULT_SUCCESS) {
                if (debugTraceEnabled) {
                    std::string errorMessage = "init driver " + driver.name + " failed, zeGetGlobalProcAddrTable() with validation layer failed with ";
                    debug_trace_message(errorMessage, loader::to_string(ZE_RESULT_ERROR_UNINITIALIZED));
                }
                return ZE_RESULT_ERROR_UNINITIALIZED;
            }
        }

        if(nullptr != tracingLayer) {
            getTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(tracingLayer, "zeGetGlobalProcAddrTable") );
            if(!getTable) {
                if (debugTraceEnabled) {
                    std::string errorMessage = "init driver " + driver.name + " failed, zeGetGlobalProcAddrTable function pointer null with tracing layer. Returning ";
                    debug_trace_message(errorMessage, loader::to_string(ZE_RESULT_ERROR_UNINITIALIZED));
                }
                return ZE_RESULT_ERROR_UNINITIALIZED;
            }
            getTableResult = getTable( version, &global);
            if(getTableResult != ZE_RESULT_SUCCESS) {
                if (debugTraceEnabled) {
                    std::string errorMessage = "init driver " + driver.name + " failed, zeGetGlobalProcAddrTable() with tracing layer failed with ";
                    debug_trace_message(errorMessage, loader::to_string(ZE_RESULT_ERROR_UNINITIALIZED));
                }
                return ZE_RESULT_ERROR_UNINITIALIZED;
            }
        }

        auto pfnInit = global.pfnInit;
        if(nullptr == pfnInit) {
            if (debugTraceEnabled) {
                std::string errorMessage = "init driver " + driver.name + " failed, zeInit function pointer null. Returning ";
                debug_trace_message(errorMessage, loader::to_string(ZE_RESULT_ERROR_UNINITIALIZED));
            }
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }

        ze_result_t res = pfnInit(flags);
        if (debugTraceEnabled) {
            std::string message = "init driver " + driver.name + " zeInit(" + loader::to_string(flags) + ") returning ";
            debug_trace_message(message, loader::to_string(res));
        }
        return res;
    }

    ///////////////////////////////////////////////////////////////////////////////
    ze_result_t context_t::init()
    {
        debugTraceEnabled = getenv_tobool( "ZE_ENABLE_LOADER_DEBUG_TRACE" );
        auto discoveredDrivers = discoverEnabledDrivers();
        std::string loadLibraryErrorValue;

        drivers.reserve( discoveredDrivers.size() + getenv_tobool( "ZE_ENABLE_NULL_DRIVER" ) );
        if( getenv_tobool( "ZE_ENABLE_NULL_DRIVER" ) )
        {
            auto handle = LOAD_DRIVER_LIBRARY( MAKE_LIBRARY_NAME( "ze_null", L0_LOADER_VERSION ) );
            if (debugTraceEnabled) {
                std::string message = "ze_null Driver Init";
                debug_trace_message(message, "");
            }
            if( NULL != handle )
            {
                drivers.emplace_back();
                drivers.rbegin()->handle = handle;
                drivers.rbegin()->name = "ze_null";
            } else if (debugTraceEnabled) {
                GET_LIBRARY_ERROR(loadLibraryErrorValue);
                std::string errorMessage = "Load Library of " + std::string(MAKE_LIBRARY_NAME( "ze_null", L0_LOADER_VERSION )) + " failed with ";
                debug_trace_message(errorMessage, loadLibraryErrorValue);
                loadLibraryErrorValue.clear();
            }
        }

        for( auto name : discoveredDrivers )
        {
            auto handle = LOAD_DRIVER_LIBRARY( name.c_str() );
            if (debugTraceEnabled) {
                std::string message = "Loading Driver " + name;
                debug_trace_message(message, "");
            }
            if( NULL != handle )
            {
                drivers.emplace_back();
                drivers.rbegin()->handle = handle;
                drivers.rbegin()->name = name;
            } else if (debugTraceEnabled) {
                GET_LIBRARY_ERROR(loadLibraryErrorValue);
                std::string errorMessage = "Load Library of " + name + " failed with ";
                debug_trace_message(errorMessage, loadLibraryErrorValue);
                loadLibraryErrorValue.clear();
            }
        }
        if(drivers.size()==0)
            return ZE_RESULT_ERROR_UNINITIALIZED;

        add_loader_version();
        std::string loaderLibraryPath;
#ifdef _WIN32
        loaderLibraryPath = readLevelZeroLoaderLibraryPath();
#endif
        typedef ze_result_t (ZE_APICALL *getVersion_t)(zel_component_version_t *version);
        if( getenv_tobool( "ZE_ENABLE_VALIDATION_LAYER" ) )
        {
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

        if( getenv_tobool( "ZE_ENABLE_TRACING_LAYER" ) )
        {
            std::string tracingLayerLibraryPath = create_library_path(MAKE_LAYER_NAME( "ze_tracing_layer" ), loaderLibraryPath.c_str());
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
        }

        if( getenv_tobool( "ZET_ENABLE_API_TRACING_EXP" ) ) {
            std::cout << "ZET_ENABLE_API_TRACING_EXP is deprecated. Use ZE_ENABLE_TRACING_LAYER instead" << std::endl;
        }

        forceIntercept = getenv_tobool( "ZE_ENABLE_LOADER_INTERCEPT" );

        if(forceIntercept || drivers.size() > 1)
             intercept_enabled = true;

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

        for( auto& drv : drivers )
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
