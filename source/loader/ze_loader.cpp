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

    void context_t::debug_trace_error(std::string errorMessage, std::string errorValue) {
        std::string debugTracePrefix = "ZE_LOADER_DEBUG_TRACE:";
        std::cerr << debugTracePrefix << errorMessage << errorValue << std::endl;
    };

    ze_result_t context_t::check_drivers(ze_init_flags_t flags) {
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
                            debug_trace_error(errorMessage, freeLibraryErrorValue);
                            freeLibraryErrorValue.clear();
                        }
                    }
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
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        
        ze_global_dditable_t global;
        auto getTableResult = getTable(ZE_API_VERSION_CURRENT, &global);
        if(getTableResult != ZE_RESULT_SUCCESS) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        
        if(nullptr == global.pfnInit) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }

        if(nullptr != validationLayer) {
            getTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(validationLayer, "zeGetGlobalProcAddrTable") );
            if(!getTable)
                return ZE_RESULT_ERROR_UNINITIALIZED;
            getTableResult = getTable( version, &global);
            if(getTableResult != ZE_RESULT_SUCCESS) {
                return ZE_RESULT_ERROR_UNINITIALIZED;
            }
        }

        if(nullptr != tracingLayer) {
            getTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(tracingLayer, "zeGetGlobalProcAddrTable") );
            if(!getTable)
                return ZE_RESULT_ERROR_UNINITIALIZED;
            getTableResult = getTable( version, &global);
            if(getTableResult != ZE_RESULT_SUCCESS) {
                return ZE_RESULT_ERROR_UNINITIALIZED;
            }
        }

        auto pfnInit = global.pfnInit;
        if(nullptr == pfnInit) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }

        return pfnInit(flags);
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
            if( NULL != handle )
            {
                drivers.emplace_back();
                drivers.rbegin()->handle = handle;
                drivers.rbegin()->name = "ze_null";
            } else if (debugTraceEnabled) {
                GET_LIBRARY_ERROR(loadLibraryErrorValue);
                std::string errorMessage = "Load Library of " + std::string(MAKE_LIBRARY_NAME( "ze_null", L0_LOADER_VERSION )) + " failed with ";
                debug_trace_error(errorMessage, loadLibraryErrorValue);
                loadLibraryErrorValue.clear();
            }
        }

        for( auto name : discoveredDrivers )
        {
            auto handle = LOAD_DRIVER_LIBRARY( name.c_str() );
            if( NULL != handle )
            {
                drivers.emplace_back();
                drivers.rbegin()->handle = handle;
                drivers.rbegin()->name = name;
            } else if (debugTraceEnabled) {
                GET_LIBRARY_ERROR(loadLibraryErrorValue);
                std::string errorMessage = "Load Library of " + name + " failed with ";
                debug_trace_error(errorMessage, loadLibraryErrorValue);
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
                debug_trace_error(errorMessage, loadLibraryErrorValue);
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
                debug_trace_error(errorMessage, loadLibraryErrorValue);
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
                    debug_trace_error(errorMessage, freeLibraryErrorValue);
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
                    debug_trace_error(errorMessage, freeLibraryErrorValue);
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
                        debug_trace_error(errorMessage, freeLibraryErrorValue);
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
