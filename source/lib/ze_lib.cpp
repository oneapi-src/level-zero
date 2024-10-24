/*
 *
 * Copyright (C) 2019-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_lib.cpp
 *
 */
#include "ze_lib.h"
#include "../loader/ze_loader_api.h"

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    #ifndef DYNAMIC_LOAD_LOADER
    context_t *context;
    #else
    context_t *context = new context_t;
    #endif
    bool destruction = false;

    ///////////////////////////////////////////////////////////////////////////////
    context_t::context_t()
    {
    #ifdef DYNAMIC_LOAD_LOADER
        printf("Context created static\n");
    #else
        printf("Context created dynamic\n");
    #endif
    };

    ///////////////////////////////////////////////////////////////////////////////
    context_t::~context_t()
    {
#ifdef DYNAMIC_LOAD_LOADER
        if (loader) {
            FREE_DRIVER_LIBRARY( loader );
        }
#endif
        ze_lib::destruction = true;
    };

    //////////////////////////////////////////////////////////////////////////
    __zedlllocal ze_result_t context_t::Init(ze_init_flags_t flags, bool sysmanOnly, ze_init_driver_type_desc_t* desc)
    {
        ze_result_t result;
#ifdef DYNAMIC_LOAD_LOADER
        std::string loaderLibraryPath;
#ifdef _WIN32
        loaderLibraryPath = readLevelZeroLoaderLibraryPath();
#endif
        std::string loaderFullLibraryPath = create_library_path(MAKE_LIBRARY_NAME( "ze_loader", L0_LOADER_VERSION), loaderLibraryPath.c_str());
        loader = LOAD_DRIVER_LIBRARY(loaderFullLibraryPath.c_str());

        if( NULL == loader ) {
            printf("loader load failed\n");
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }

        typedef ze_result_t (ZE_APICALL *loaderInit_t)();
        auto loaderInit = reinterpret_cast<loaderInit_t>(
                GET_FUNCTION_PTR(loader, "zeLoaderInit") );
        printf("calling loader init static\n");
        result = loaderInit();
        if( ZE_RESULT_SUCCESS != result ) {
            return result;
        }
        typedef HMODULE (ZE_APICALL *getTracing_t)();
        auto getTracing = reinterpret_cast<getTracing_t>(
            GET_FUNCTION_PTR(loader, "zeLoaderGetTracingHandle") );
        tracing_lib = getTracing();
        typedef ze_result_t (ZE_APICALL *zelLoaderDriverCheck_t)(ze_init_flags_t flags, ze_init_driver_type_desc_t* desc, ze_global_dditable_t *globalInitStored, zes_global_dditable_t *sysmanGlobalInitStored, bool *requireDdiReinit, bool sysmanOnly);
        auto loaderDriverCheck = reinterpret_cast<zelLoaderDriverCheck_t>(
                GET_FUNCTION_PTR(loader, "zelLoaderDriverCheck") );
        typedef ze_result_t (ZE_APICALL *zelLoaderTracingLayerInit_t)(std::atomic<ze_dditable_t *> &zeDdiTable);
        auto loaderTracingLayerInit = reinterpret_cast<zelLoaderTracingLayerInit_t>(
                GET_FUNCTION_PTR(loader, "zelLoaderTracingLayerInit") );
        typedef loader::context_t * (ZE_APICALL *zelLoaderGetContext_t)();
        auto loaderGetContext = reinterpret_cast<zelLoaderGetContext_t>(
                GET_FUNCTION_PTR(loader, "zelLoaderGetContext") );
#else
        result = zeLoaderInit();
        if( ZE_RESULT_SUCCESS == result ) {
            tracing_lib = zeLoaderGetTracingHandle();
        }

#endif

        if ( ZE_RESULT_SUCCESS == result )
        {
            ze_lib::context->zeDdiTable.exchange(&ze_lib::context->initialzeDdiTable);
            ze_lib::context->zetDdiTable.exchange(&ze_lib::context->initialzetDdiTable);
            ze_lib::context->zesDdiTable.exchange(&ze_lib::context->initialzesDdiTable);
        }

        // Given zesInit, then zesDrivers needs to be used as the sysmanInstanceDrivers;
#ifdef DYNAMIC_LOAD_LOADER
        loader::context = loaderGetContext();
#endif
        if (sysmanOnly) {
            loader::context->sysmanInstanceDrivers = &loader::context->zesDrivers;
        }

        // Always call the inits for all the ddi tables before checking which drivers are usable to enable Instrumentation correctly.

        // Init the ZE DDI Tables
        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeDdiTableInit();
        }
        // Init the ZET DDI Tables
        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetDdiTableInit();
        }
        // Init the ZES DDI Tables
        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesDdiTableInit();
        }
        // Init the Tracing API DDI Tables
        if( ZE_RESULT_SUCCESS == result )
        {
            result = zelTracingDdiTableInit();
        }
        // Init the stored ddi tables for the tracing layer
        if( ZE_RESULT_SUCCESS == result )
        {
            #ifdef DYNAMIC_LOAD_LOADER
            result = loaderTracingLayerInit(this->pTracingZeDdiTable);
            #else
            result = zelLoaderTracingLayerInit(this->pTracingZeDdiTable);
            #endif
        }
        // End DDI Table Inits

        // Check which drivers and layers can be init on this system.
        if( ZE_RESULT_SUCCESS == result)
        {
            // Check which drivers support the ze_driver_flag_t specified
            // No need to check if only initializing sysman
            bool requireDdiReinit = false;
            #ifdef DYNAMIC_LOAD_LOADER
            result = loaderDriverCheck(flags, desc, &ze_lib::context->initialzeDdiTable.Global, &ze_lib::context->initialzesDdiTable.Global, &requireDdiReinit, sysmanOnly);
            #else
            result = zelLoaderDriverCheck(flags, desc, &ze_lib::context->initialzeDdiTable.Global, &ze_lib::context->initialzesDdiTable.Global, &requireDdiReinit, sysmanOnly);
            #endif
            // If a driver was removed from the driver list, then the ddi tables need to be reinit to allow for passthru directly to the driver.
            if (requireDdiReinit) {
                // If a user has already called the core apis, then ddi table reinit is not possible due to handles already being read by the user.
                if (!sysmanOnly && !ze_lib::context->zeInuse) {
                    // reInit the ZE DDI Tables
                    if( ZE_RESULT_SUCCESS == result )
                    {
                        result = zeDdiTableInit();
                    }
                    // reInit the ZET DDI Tables
                    if( ZE_RESULT_SUCCESS == result )
                    {
                        result = zetDdiTableInit();
                    }
                    // If ze/zet ddi tables have been reinit and no longer use the intercept layer, then handles passed to zelLoaderTranslateHandleInternal do not require translation.
                    // Setting intercept_enabled==false changes the behavior of zelLoaderTranslateHandleInternal to avoid translation.
                    // Translation is only required if the intercept layer is enabled for the ZE handle types.
                    loader::context->intercept_enabled = false;
                }
                // If a user has already called the zes/ze apis, then ddi table reinit is not possible due to handles already being read by the user.
                if (!(ze_lib::context->zesInuse || ze_lib::context->zeInuse)) {
                    // reInit the ZES DDI Tables
                    if( ZE_RESULT_SUCCESS == result )
                    {
                        result = zesDdiTableInit();
                    }
                }
            }
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            isInitialized = true;
        }

        return result;
    }

} // namespace ze_lib

extern "C" {


ze_result_t ZE_APICALL
zelLoaderGetVersions(
   size_t *num_elems,                     //Pointer to num versions to get.
   zel_component_version_t *versions)     //Pointer to array of versions. If set to NULL, num_elems is returned
{
#ifdef DYNAMIC_LOAD_LOADER
    if(nullptr == ze_lib::context->loader)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *zelLoaderGetVersions_t)(size_t *num_elems, zel_component_version_t *versions);
    auto getVersions = reinterpret_cast<zelLoaderGetVersions_t>(
            GET_FUNCTION_PTR(ze_lib::context->loader, "zelLoaderGetVersionsInternal") );
    return getVersions(num_elems, versions);
#else
    return zelLoaderGetVersionsInternal(num_elems, versions);
#endif
}


ze_result_t ZE_APICALL
zelLoaderTranslateHandle(
   zel_handle_type_t handleType,
   void *handleIn,
   void **handleOut)

{
    return zelLoaderTranslateHandleInternal(handleType, handleIn, handleOut);
}

ze_result_t ZE_APICALL
zelSetDriverTeardown()
{
    ze_result_t result = ZE_RESULT_SUCCESS;
    if (!ze_lib::destruction) {
        ze_lib::context->inTeardown = true;
    }
    return result;
}

ze_result_t ZE_APICALL
zelEnableTracingLayer()
{
    if (ze_lib::context->tracingLayerEnableCounter.fetch_add(1) == 0) {
        ze_lib::context->zeDdiTable.exchange(ze_lib::context->pTracingZeDdiTable);
    }
    return ZE_RESULT_SUCCESS;
}

ze_result_t ZE_APICALL
zelDisableTracingLayer()
{
    if (ze_lib::context->tracingLayerEnableCounter.fetch_sub(1) <= 1) {
        ze_lib::context->zeDdiTable.exchange(&ze_lib::context->initialzeDdiTable);
    }
    return ZE_RESULT_SUCCESS;
}

} //extern "c"