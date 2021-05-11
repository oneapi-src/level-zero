/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_lib.cpp
 *
 */
#include "ze_lib.h"
#ifndef DYNAMIC_LOAD_LOADER
#include "../loader/ze_loader_api.h"
#endif

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    context_t *context;

    ///////////////////////////////////////////////////////////////////////////////
    context_t::context_t()
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    context_t::~context_t()
    {
#ifdef DYNAMIC_LOAD_LOADER
        FREE_DRIVER_LIBRARY( loader );
#endif
    };

    //////////////////////////////////////////////////////////////////////////
    __zedlllocal ze_result_t context_t::Init()
    {
        ze_result_t result;
#ifdef DYNAMIC_LOAD_LOADER
        loader = LOAD_DRIVER_LIBRARY( MAKE_LIBRARY_NAME( "ze_loader", L0_LOADER_VERSION) );

        if( NULL == loader )
            return ZE_RESULT_ERROR_UNINITIALIZED;
          
        typedef ze_result_t (ZE_APICALL *loaderInit_t)();
        auto loaderInit = reinterpret_cast<loaderInit_t>(
                GET_FUNCTION_PTR(loader, "zeLoaderInit") );
        result = loaderInit();
        if( ZE_RESULT_SUCCESS == result ) {
            typedef HMODULE (ZE_APICALL *getTracing_t)();
            auto getTracing = reinterpret_cast<getTracing_t>(
                GET_FUNCTION_PTR(loader, "zeLoaderGetTracingHandle") );
            tracing_lib = getTracing();
        }
#else
        result = zeLoaderInit();
        if( ZE_RESULT_SUCCESS == result ) {
            tracing_lib = zeLoaderGetTracingHandle();
        }
        
#endif


        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeInit();
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetInit();
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesInit();
        } 

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zelTracingInit();
        }

        return result;
    }

} // namespace ze_lib
