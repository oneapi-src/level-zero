/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "ze_loader.h"

#include "driver_discovery.h"

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    context_t context;


    ///////////////////////////////////////////////////////////////////////////////
    context_t::context_t()
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
                drivers.emplace_back();
                drivers.rbegin()->handle = handle;
            }

        }

        if( getenv_tobool( "ZE_ENABLE_VALIDATION_LAYER" ) )
        {
            validationLayer = LOAD_DRIVER_LIBRARY( MAKE_VALIDATION_LAYER_NAME( "ze_validation_layer" ) );
        }

        forceIntercept = getenv_tobool( "ZE_ENABLE_LOADER_INTERCEPT" );
    };

    ///////////////////////////////////////////////////////////////////////////////
    context_t::~context_t()
    {
        FREE_DRIVER_LIBRARY( validationLayer );

        for( auto& drv : drivers )
        {
            FREE_DRIVER_LIBRARY( drv.handle );
        }
    };
}
