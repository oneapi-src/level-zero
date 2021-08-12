/*
 *
 * Copyright (C) 2019-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "ze_loader.h"

#include "driver_discovery.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    context_t *context;

    ///////////////////////////////////////////////////////////////////////////////
    ze_result_t context_t::init(ze_init_flags_t flags)
    {
        auto discoveredDrivers = discoverEnabledDrivers();

        drivers.reserve( discoveredDrivers.size() + getenv_tobool( "ZE_ENABLE_NULL_DRIVER" ) );
        if( getenv_tobool( "ZE_ENABLE_NULL_DRIVER" ) )
        {
            auto handle = LOAD_DRIVER_LIBRARY( MAKE_LIBRARY_NAME( "ze_null", L0_LOADER_VERSION ) );
            if( NULL != handle )
            {
                drivers.emplace_back();
                drivers.rbegin()->handle = handle;
            }
        }

        for( auto name : discoveredDrivers )
        {
            auto handle = LOAD_DRIVER_LIBRARY( name.c_str() );
            if( NULL != handle )
            {
                auto getTable = reinterpret_cast<ze_pfnGetGlobalProcAddrTable_t>(
                    GET_FUNCTION_PTR(handle, "zeGetGlobalProcAddrTable"));
                ze_global_dditable_t global;
                auto getTableResult = getTable(ZE_API_VERSION_CURRENT, &global);
                if(!getTable) {
                    FREE_DRIVER_LIBRARY(handle);
                    continue;
                }
                if(getTableResult != ZE_RESULT_SUCCESS) {
                    FREE_DRIVER_LIBRARY(handle);
                    continue;
                }
                
                auto pfnInit = global.pfnInit;
                if(nullptr == pfnInit) {
                    FREE_DRIVER_LIBRARY(handle);
                    continue;
                }

                if(pfnInit(flags) != ZE_RESULT_SUCCESS) {
                    FREE_DRIVER_LIBRARY(handle);
                    continue;
                }

                drivers.emplace_back();
                drivers.rbegin()->handle = handle;
            }
        }

        if(drivers.size()==0)
            return ZE_RESULT_ERROR_UNINITIALIZED;

        add_loader_version();
        typedef ze_result_t (ZE_APICALL *getVersion_t)(zel_component_version_t *version);
        if( getenv_tobool( "ZE_ENABLE_VALIDATION_LAYER" ) )
        {
            validationLayer = LOAD_DRIVER_LIBRARY( MAKE_LAYER_NAME( "ze_validation_layer" ) );
            if(validationLayer)
            {
                auto getVersion = reinterpret_cast<getVersion_t>(
                    GET_FUNCTION_PTR(validationLayer, "zelLoaderGetVersion"));
                zel_component_version_t version;
                if(getVersion && ZE_RESULT_SUCCESS == getVersion(&version))
                {   
                    compVersions.push_back(version);
                }
            }
        }

        if( getenv_tobool( "ZE_ENABLE_TRACING_LAYER" ) )
        {
            tracingLayer = LOAD_DRIVER_LIBRARY( MAKE_LAYER_NAME( "ze_tracing_layer" ) );
            if(tracingLayer)
            {
                auto getVersion = reinterpret_cast<getVersion_t>(
                    GET_FUNCTION_PTR(tracingLayer, "zelLoaderGetVersion"));
                zel_component_version_t version;
                if(getVersion && ZE_RESULT_SUCCESS == getVersion(&version))
                {   
                    compVersions.push_back(version);
                }
            }
        }

        forceIntercept = getenv_tobool( "ZE_ENABLE_LOADER_INTERCEPT" );

        return ZE_RESULT_SUCCESS;
    };

    ///////////////////////////////////////////////////////////////////////////////
    context_t::~context_t()
    {
        FREE_DRIVER_LIBRARY( validationLayer );
        FREE_DRIVER_LIBRARY( tracingLayer );

        for( auto& drv : drivers )
        {
            FREE_DRIVER_LIBRARY( drv.handle );
        }
    };

    void context_t::add_loader_version(){
        zel_component_version_t version = {};
        strncpy(version.component_name, LOADER_COMP_NAME, ZEL_COMPONENT_STRING_SIZE);
        version.spec_version = ZE_API_VERSION_CURRENT;
        version.component_lib_version.major = LOADER_VERSION_MAJOR;
        version.component_lib_version.minor = LOADER_VERSION_MINOR;
        version.component_lib_version.patch = LOADER_VERSION_PATCH;

        compVersions.push_back(version);
    }

}
