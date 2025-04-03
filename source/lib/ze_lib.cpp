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
#include "../loader/ze_loader_internal.h"
#include <thread>
#include <future>
#include <stdexcept>

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    context_t *context = nullptr;
    #ifdef DYNAMIC_LOAD_LOADER
    void context_at_exit_destructor()
    {
        if (ze_lib::context) {
            delete ze_lib::context;
            ze_lib::context = nullptr;
        }
    }
    bool delayContextDestruction = false;
    #endif
    bool destruction = false;

    ///////////////////////////////////////////////////////////////////////////////
    __zedlllocal context_t::context_t()
    {
        debugTraceEnabled = getenv_tobool( "ZE_ENABLE_LOADER_DEBUG_TRACE" );
    };

    ///////////////////////////////////////////////////////////////////////////////
    __zedlllocal context_t::~context_t()
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
        ze_api_version_t version = ZE_API_VERSION_CURRENT;
#ifdef DYNAMIC_LOAD_LOADER
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
            debug_trace_message("Static Loader Using Loader Library Path: ", loaderLibraryPath);
        std::string loaderFullLibraryPath = create_library_path(MAKE_LIBRARY_NAME( "ze_loader", L0_LOADER_VERSION), loaderLibraryPath.c_str());
        loader = LOAD_DRIVER_LIBRARY(loaderFullLibraryPath.c_str());

        if( NULL == loader ) {
            std::string message = "ze_lib Context Init() Loader Library Load Failed with ";
            debug_trace_message(message, to_string(ZE_RESULT_ERROR_UNINITIALIZED));
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }

        typedef ze_result_t (ZE_APICALL *loaderInit_t)();
        auto loaderInit = reinterpret_cast<loaderInit_t>(
                GET_FUNCTION_PTR(loader, "zeLoaderInit") );
        result = loaderInit();
        if( ZE_RESULT_SUCCESS != result ) {
            std::string message = "ze_lib Context Init() Loader Init Failed with ";
            debug_trace_message(message, to_string(result));
            return result;
        }

        size_t size = 0;
        result = zelLoaderGetVersions(&size, nullptr);
        if (ZE_RESULT_SUCCESS != result) {
            std::string message = "ze_lib Context Init() zelLoaderGetVersions Failed with";
            debug_trace_message(message, to_string(result));
            return result;
        }

        std::vector<zel_component_version_t> versions(size);
        result = zelLoaderGetVersions(&size, versions.data());
        if (ZE_RESULT_SUCCESS != result) {
            std::string message = "ze_lib Context Init() zelLoaderGetVersions Failed to read component versions with ";
            debug_trace_message(message, to_string(result));
            return result;
        }

        bool zeInitDriversSupport = true;
        const std::string loader_name = "loader";
        for (auto &component : versions) {
            if (loader_name == component.component_name) {
                version = component.spec_version;
                std::string message = "ze_lib Context Init() Static Loader Found Loader Version v" + std::to_string(component.component_lib_version.major) + "." + std::to_string(component.component_lib_version.minor) + "." + std::to_string(component.component_lib_version.patch);
                debug_trace_message(message, "");
                if(component.component_lib_version.major == 1) {
                    if (component.component_lib_version.minor < 18) {
                        std::string message = "ze_lib Context Init() Version Does not support zeInitDrivers";
                        debug_trace_message(message, "");
                        zeInitDriversSupport = false;
                    }
                } else {
                    std::string message = "ze_lib Context Init() Loader version is too new, returning ";
                    debug_trace_message(message, to_string(ZE_RESULT_ERROR_UNSUPPORTED_VERSION));
                    return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
                }
            }
        }

        typedef HMODULE (ZE_APICALL *getTracing_t)();
        auto getTracing = reinterpret_cast<getTracing_t>(
            GET_FUNCTION_PTR(loader, "zeLoaderGetTracingHandle") );
        if (getTracing == nullptr) {
            std::string message = "ze_lib Context Init() zeLoaderGetTracingHandle missing, returning ";
            debug_trace_message(message, to_string(ZE_RESULT_ERROR_UNINITIALIZED));
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        tracing_lib = getTracing();
        typedef ze_result_t (ZE_APICALL *zelLoaderTracingLayerInit_t)(std::atomic<ze_dditable_t *> &zeDdiTable);
        auto loaderTracingLayerInit = reinterpret_cast<zelLoaderTracingLayerInit_t>(
                GET_FUNCTION_PTR(loader, "zelLoaderTracingLayerInit") );
        if (loaderTracingLayerInit == nullptr) {
            std::string message = "ze_lib Context Init() zelLoaderTracingLayerInit missing, disabling dynamic tracer support ";
            debug_trace_message(message, "");
            this->dynamicTracingSupported = false;
        }
        typedef loader::context_t * (ZE_APICALL *zelLoaderGetContext_t)();
        auto loaderGetContext = reinterpret_cast<zelLoaderGetContext_t>(
                GET_FUNCTION_PTR(loader, "zelLoaderGetContext") );
        if (loaderGetContext == nullptr) {
            std::string message = "ze_lib Context Init() zelLoaderGetContext missing";
            debug_trace_message(message, "");
        }

        std::string version_message = "Loader API Version to be requested is v" + std::to_string(ZE_MAJOR_VERSION(version)) + "." + std::to_string(ZE_MINOR_VERSION(version));
        debug_trace_message(version_message, "");
        loaderDriverGet = reinterpret_cast<ze_pfnDriverGet_t>(GET_FUNCTION_PTR(loader, "zeDriverGet"));
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
        bool loaderContextAccessAllowed = true;
#ifdef DYNAMIC_LOAD_LOADER
        loader::context_t *loaderContext = nullptr;
        if (loaderGetContext == nullptr) {
            loaderContextAccessAllowed = false;
        } else {
            loaderContext = loaderGetContext();
        }
#else
        loader::context_t *loaderContext = loader::context;
#endif
        if (sysmanOnly && loaderContextAccessAllowed) {
            loaderContext->sysmanInstanceDrivers = &loaderContext->zesDrivers;
        }

        // Always call the inits for all the ddi tables before checking which drivers are usable to enable Instrumentation correctly.

        // Init the ZE DDI Tables
        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeDdiTableInit(version);
            if (result != ZE_RESULT_SUCCESS) {
                std::string message = "ze_lib Context Init() zeDdiTableInit failed with ";
                debug_trace_message(message, to_string(result));
            }
        }
        // Init the ZET DDI Tables
        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetDdiTableInit(version);
            if( ZE_RESULT_SUCCESS != result ) {
                std::string message = "ze_lib Context Init() zetDdiTableInit failed with ";
                debug_trace_message(message, to_string(result));
            }
        }
        // Init the ZES DDI Tables
        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesDdiTableInit(version);
            if (result != ZE_RESULT_SUCCESS) {
                std::string message = "ze_lib Context Init() zesDdiTableInit failed with ";
                debug_trace_message(message, to_string(result));
            }
        }
        // Init the Tracing API DDI Tables
        if( ZE_RESULT_SUCCESS == result )
        {
            result = zelTracingDdiTableInit(version);
            if (result != ZE_RESULT_SUCCESS) {
                std::string message = "ze_lib Context Init() zelTracingDdiTableInit failed with ";
                debug_trace_message(message, to_string(result));
            }
        }
        // Init the stored ddi tables for the tracing layer
        if( ZE_RESULT_SUCCESS == result )
        {
            #ifdef DYNAMIC_LOAD_LOADER
            if (loaderTracingLayerInit) {
                result = loaderTracingLayerInit(this->pTracingZeDdiTable);
            }
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
            if (zeInitDriversSupport) {
                typedef ze_result_t (ZE_APICALL *zelLoaderDriverCheck_t)(ze_init_flags_t flags, ze_init_driver_type_desc_t* desc, ze_global_dditable_t *globalInitStored, zes_global_dditable_t *sysmanGlobalInitStored, bool *requireDdiReinit, bool sysmanOnly);
                auto loaderDriverCheck = reinterpret_cast<zelLoaderDriverCheck_t>(
                        GET_FUNCTION_PTR(loader, "zelLoaderDriverCheck") );
                if (loaderDriverCheck == nullptr) {
                    std::string message = "ze_lib Context Init() zelLoaderDriverCheck missing, returning ";
                    debug_trace_message(message, to_string(ZE_RESULT_ERROR_UNINITIALIZED));
                    return ZE_RESULT_ERROR_UNINITIALIZED;
                }
                result = loaderDriverCheck(flags, desc, &ze_lib::context->initialzeDdiTable.Global, &ze_lib::context->initialzesDdiTable.Global, &requireDdiReinit, sysmanOnly);
            } else {
                typedef ze_result_t (ZE_APICALL *zelLoaderDriverCheck_t)(ze_init_flags_t flags, ze_global_dditable_t *globalInitStored, zes_global_dditable_t *sysmanGlobalInitStored, bool *requireDdiReinit, bool sysmanOnly);
                auto loaderDriverCheck = reinterpret_cast<zelLoaderDriverCheck_t>(
                        GET_FUNCTION_PTR(loader, "zelLoaderDriverCheck") );
                if (loaderDriverCheck == nullptr) {
                    std::string message = "ze_lib Context Init() zelLoaderDriverCheck missing, returning ";
                    debug_trace_message(message, to_string(ZE_RESULT_ERROR_UNINITIALIZED));
                    return ZE_RESULT_ERROR_UNINITIALIZED;
                }
                result = loaderDriverCheck(flags, &ze_lib::context->initialzeDdiTable.Global, &ze_lib::context->initialzesDdiTable.Global, &requireDdiReinit, sysmanOnly);
            }
            #else
            result = zelLoaderDriverCheck(flags, desc, &ze_lib::context->initialzeDdiTable.Global, &ze_lib::context->initialzesDdiTable.Global, &requireDdiReinit, sysmanOnly);
            #endif
            if (result != ZE_RESULT_SUCCESS) {
                std::string message = "ze_lib Context Init() zelLoaderDriverCheck failed with ";
                debug_trace_message(message, to_string(result));
            }
            // If a driver was removed from the driver list, then the ddi tables need to be reinit to allow for passthru directly to the driver.
            if (requireDdiReinit && loaderContextAccessAllowed) {
                // If a user has already called the core apis, then ddi table reinit is not possible due to handles already being read by the user.
                if (!sysmanOnly && !ze_lib::context->zeInuse) {
                    // reInit the ZE DDI Tables
                    if( ZE_RESULT_SUCCESS == result )
                    {
                        result = zeDdiTableInit(version);
                    }
                    // reInit the ZET DDI Tables
                    if( ZE_RESULT_SUCCESS == result )
                    {
                        result = zetDdiTableInit(version);
                    }
                    // If ze/zet ddi tables have been reinit and no longer use the intercept layer, then handles passed to zelLoaderTranslateHandleInternal do not require translation.
                    // Setting intercept_enabled==false changes the behavior of zelLoaderTranslateHandleInternal to avoid translation.
                    // Translation is only required if the intercept layer is enabled for the ZE handle types.
                    loaderContext->intercept_enabled = false;
                }
                // If a user has already called the zes/ze apis, then ddi table reinit is not possible due to handles already being read by the user.
                if (!(ze_lib::context->zesInuse || ze_lib::context->zeInuse)) {
                    // reInit the ZES DDI Tables
                    if( ZE_RESULT_SUCCESS == result )
                    {
                        result = zesDdiTableInit(version);
                    }
                }
            }
        }

        if( ZE_RESULT_SUCCESS == result )
        {
#ifdef DYNAMIC_LOAD_LOADER
            // Init Dynamic Loader's Lib Context:
            auto initDriversLoader = reinterpret_cast<ze_pfnInitDrivers_t>(
                GET_FUNCTION_PTR(loader, "zeInitDrivers") );
            auto initLoader = reinterpret_cast<ze_pfnInit_t>(
                GET_FUNCTION_PTR(loader, "zeInit") );
            if (initDriversLoader == nullptr && initLoader == nullptr) {
                std::string message = "ze_lib Context Init() zeInitDrivers and zeInit missing, returning ";
                debug_trace_message(message, to_string(ZE_RESULT_ERROR_UNINITIALIZED));
                return ZE_RESULT_ERROR_UNINITIALIZED;
            }
            if (!desc) {
                result = initLoader(flags);
            } else if (initDriversLoader != nullptr) {
                uint32_t pInitDriversCount = 0;
                result = initDriversLoader(&pInitDriversCount, nullptr, desc);
            } else {
                ze_init_flags_t init_flags = flags;
                if (desc) {
                    if(desc->flags & ZE_INIT_DRIVER_TYPE_FLAG_GPU) {
                        init_flags = ZE_INIT_FLAG_GPU_ONLY;
                    } else if(desc->flags & ZE_INIT_DRIVER_TYPE_FLAG_NPU) {
                        init_flags = ZE_INIT_FLAG_VPU_ONLY;
                    } else {
                        init_flags = 0;
                    }
                }
                result = initLoader(init_flags);
            }
            if (result != ZE_RESULT_SUCCESS) {
                std::string message = "ze_lib Context Init() zeInitDrivers or zeInit failed with ";
                debug_trace_message(message, to_string(result));
                return result;
            }
#endif
            isInitialized = true;
        }
        #ifdef DYNAMIC_LOAD_LOADER
        if (!delayContextDestruction) {
            std::atexit(context_at_exit_destructor);
        }
        #endif
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
#ifdef DYNAMIC_LOAD_LOADER
    if(nullptr == ze_lib::context->loader)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *zelLoaderTranslateHandleInternal_t)(zel_handle_type_t handleType, void *handleIn, void **handleOut);
    auto translateHandle = reinterpret_cast<zelLoaderTranslateHandleInternal_t>(
            GET_FUNCTION_PTR(ze_lib::context->loader, "zelLoaderTranslateHandleInternal") );
    return translateHandle(handleType, handleIn, handleOut);
#else
    return zelLoaderTranslateHandleInternal(handleType, handleIn, handleOut);
#endif
}

ze_result_t ZE_APICALL
zelSetDriverTeardown()
{
    ze_result_t result = ZE_RESULT_SUCCESS;
    if (!ze_lib::destruction) {
        ze_lib::destruction = true;
    }
    return result;
}

void ZE_APICALL
zelSetDelayLoaderContextTeardown()
{
    #ifdef DYNAMIC_LOAD_LOADER
    if (!ze_lib::delayContextDestruction) {
        ze_lib::delayContextDestruction = true;
    }
    #endif
}

#ifdef DYNAMIC_LOAD_LOADER
#define ZEL_STABILITY_CHECK_RESULT_SUCCESS 0
#define ZEL_STABILITY_CHECK_RESULT_DRIVER_GET_NULL 1
#define ZEL_STABILITY_CHECK_RESULT_DRIVER_GET_FAILED 2
#define ZEL_STABILITY_CHECK_RESULT_EXCEPTION 3

/**
 * @brief Performs a stability check for the Level Zero loader.
 *
 * This function checks the stability of the Level Zero loader by verifying
 * the presence of the loader module, the validity of the `zeDriverGet` function
 * pointer, and the ability to retrieve driver information. The result of the
 * stability check is communicated through the provided promise.
 *
 * @param stabilityPromise A promise object used to communicate the result of
 *                         the stability check. The promise is set with one of
 *                         the following values:
 *                         - ZEL_STABILITY_CHECK_RESULT_DRIVER_GET_NULL: The
 *                           `zeDriverGet` function pointer is invalid.
 *                         - ZEL_STABILITY_CHECK_RESULT_DRIVER_GET_FAILED: The
 *                           loader failed to retrieve driver information.
 *                         - ZEL_STABILITY_CHECK_RESULT_EXCEPTION: An
 *                           exception occurred during the stability check.
 *                         - ZEL_STABILITY_CHECK_RESULT_SUCCESS: The stability
 *                           check was successful.
 *
 * @note If debug tracing is enabled, debug messages are logged for each failure
 *       scenario.
 * @note If the Loader is completely torn down, this thread is expected to be killed
 *      due to invalid memory access and the stability check will determine a failure.
 *
 * @exception This function catches all exceptions internally and does not throw.
 */
void stabilityCheck(std::promise<int> stabilityPromise) {
    try {
        if (!ze_lib::context->loaderDriverGet) {
            if (ze_lib::context->debugTraceEnabled) {
                std::string message = "LoaderDriverGet is a bad pointer. Exiting stability checker thread.";
                ze_lib::context->debug_trace_message(message, "");
            }
            stabilityPromise.set_value(ZEL_STABILITY_CHECK_RESULT_DRIVER_GET_NULL);
            return;
        }

        uint32_t driverCount = 0;
        ze_result_t result = ZE_RESULT_ERROR_UNINITIALIZED;
        result = ze_lib::context->loaderDriverGet(&driverCount, nullptr);
        if (result != ZE_RESULT_SUCCESS || driverCount == 0) {
            if (ze_lib::context->debugTraceEnabled) {
                std::string message = "Loader stability check failed. Exiting stability checker thread.";
                ze_lib::context->debug_trace_message(message, "");
            }
            stabilityPromise.set_value(ZEL_STABILITY_CHECK_RESULT_DRIVER_GET_FAILED);
            return;
        }
        stabilityPromise.set_value(ZEL_STABILITY_CHECK_RESULT_SUCCESS);
        return;
    } catch (...) {
        stabilityPromise.set_value(ZEL_STABILITY_CHECK_RESULT_EXCEPTION);
        return;
    }
}
#endif

/**
 * @brief Checks if the loader is in the process of tearing down.
 *
 * This function determines whether the loader is in a teardown state by
 * checking the destruction flag or the context pointer. If the loader is
 * dynamically loaded thru the static loader code path, then it performs
 * an additional stability check using a separate thread that could be killed.
 *
 * @return true if the loader is in teardown based on the stack variablrs
 *         or the stability check fails; false otherwise.
 *
 * @note If the macro DYNAMIC_LOAD_LOADER is defined, a stability checker
 *       thread is launched to perform additional checks. Any exceptions
 *       or errors during this process are logged if debug tracing is enabled.
 */
bool ZE_APICALL
zelCheckIsLoaderInTearDown() {
    if (ze_lib::destruction || ze_lib::context == nullptr) {
        return true;
    }
    #ifdef DYNAMIC_LOAD_LOADER
    std::promise<int> stabilityPromise;
    std::future<int> resultFuture = stabilityPromise.get_future();
    int result = -1;
    try {
        // Launch the stability checker thread
        std::thread stabilityThread(stabilityCheck, std::move(stabilityPromise));
        result = resultFuture.get(); // Blocks until the result is available
        if (ze_lib::context->debugTraceEnabled) {
            std::string message = "Stability checker thread completed with result: " + std::to_string(result);
            ze_lib::context->debug_trace_message(message, "");
        }
        stabilityThread.join();
    } catch (const std::exception& e) {
        if (ze_lib::context->debugTraceEnabled) {
            std::string message = "Exception caught in parent thread: " + std::string(e.what());
            ze_lib::context->debug_trace_message(message, "");
        }
    } catch (...) {
        if (ze_lib::context->debugTraceEnabled) {
            std::string message = "Unknown exception caught in parent thread.";
            ze_lib::context->debug_trace_message(message, "");
        }
    }
    if (result != ZEL_STABILITY_CHECK_RESULT_SUCCESS) {
        if (ze_lib::context->debugTraceEnabled) {
            std::string message = "Loader stability check failed with result: " + std::to_string(result);
            ze_lib::context->debug_trace_message(message, "");
        }
        return true;
    }
    #endif
    return false;
}

void ZE_APICALL
zelLoaderContextTeardown()
{
    #ifdef DYNAMIC_LOAD_LOADER
    if (ze_lib::delayContextDestruction && ze_lib::context) {
        delete ze_lib::context;
        ze_lib::context = nullptr;
    }
    #endif
}

ze_result_t ZE_APICALL
zelEnableTracingLayer()
{
    if (ze_lib::context->dynamicTracingSupported == false) {
        return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }
    if (ze_lib::context->tracingLayerEnableCounter.fetch_add(1) == 0) {
        ze_lib::context->zeDdiTable.exchange(ze_lib::context->pTracingZeDdiTable);
    }
    return ZE_RESULT_SUCCESS;
}

ze_result_t ZE_APICALL
zelDisableTracingLayer()
{
    if (ze_lib::context->dynamicTracingSupported == false) {
        return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }
    if (ze_lib::context->tracingLayerEnableCounter.fetch_sub(1) <= 1) {
        ze_lib::context->zeDdiTable.exchange(&ze_lib::context->initialzeDdiTable);
    }
    return ZE_RESULT_SUCCESS;
}

} //extern "c"