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
    #ifdef L0_STATIC_LOADER_BUILD
    void context_at_exit_destructor()
    {
        if (ze_lib::context) {
            delete ze_lib::context;
            ze_lib::context = nullptr;
        }
    }
    bool delayContextDestruction = false;
    bool loaderTeardownCallbackReceived = false;
    bool loaderTeardownRegistrationEnabled = false;

    /// @brief Callback function to handle loader teardown events.
    ///
    /// This function sets the `loaderTeardownCallbackReceived` flag to true,
    /// indicating that a loader teardown callback has been received.
    /// It is intended to be used as a static callback during the loader's
    /// teardown process.
    void staticLoaderTeardownCallback() {
        loaderTeardownCallbackReceived = true;
    }
    #endif
    /**
     * @brief Removes a teardown callback from the context's callback registry.
     *
     * This function checks if a teardown callback with the specified index exists
     * in the context's teardownCallbacks map. If it exists, the callback is removed.
     *
     * @param index The unique identifier of the teardown callback to remove.
     */
    void applicationTeardownCallback(uint32_t index) {
        std::lock_guard<std::mutex> lock(ze_lib::context->teardownCallbacksMutex);
        if (ze_lib::context->teardownCallbacks.find(index) != ze_lib::context->teardownCallbacks.end()) {
            if (ze_lib::context->debugTraceEnabled) {
                std::string message = "applicationTeardownCallback received for index: " + std::to_string(index);
                ze_lib::context->debug_trace_message(message, "");
            }
            ze_lib::context->teardownCallbacks.erase(index);
        }
    }
    bool destruction = false;

    ///////////////////////////////////////////////////////////////////////////////
    __zedlllocal context_t::context_t()
    {
        debugTraceEnabled = getenv_tobool( "ZE_ENABLE_LOADER_DEBUG_TRACE" );
    };

    ///////////////////////////////////////////////////////////////////////////////
    __zedlllocal context_t::~context_t()
    {
#ifdef L0_STATIC_LOADER_BUILD
        if (loaderTeardownRegistrationEnabled && !loaderTeardownCallbackReceived) {
            loaderTeardownCallback(loaderTeardownCallbackIndex);
        }
        if (loader) {
            FREE_DRIVER_LIBRARY( loader );
        }
#else
        // Given the loader teardown, notify the registered callbacks that the loader is being torn down.
        for (auto &callback : teardownCallbacks) {
            callback.second();
        }
        // Clear the teardown callbacks map once the callbacks have been executed.
        teardownCallbacks.clear();
#endif
        ze_lib::destruction = true;
    };

    //////////////////////////////////////////////////////////////////////////
    __zedlllocal ze_result_t context_t::Init(ze_init_flags_t flags, bool sysmanOnly, ze_init_driver_type_desc_t* desc)
    {
        ze_result_t result;
        ze_api_version_t version = ZE_API_VERSION_CURRENT;
#ifdef L0_STATIC_LOADER_BUILD
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
        ze_api_version_t current_api_version = version;
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

        if (version > current_api_version) {
            version = current_api_version;
            std::string message = "ze_lib Context Init() Static Loader Requesting Loader API Version v" + std::to_string(ZE_MAJOR_VERSION(version)) + "." + std::to_string(ZE_MINOR_VERSION(version));
            debug_trace_message(message, "");
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
#ifdef L0_STATIC_LOADER_BUILD
        loaderContextAccessAllowed = false;
        loader::context_t *loaderContext = nullptr;
#else
        loader::context_t *loaderContext = loader::context;
#endif
        if (sysmanOnly && loaderContextAccessAllowed && loaderContext != nullptr) {
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
            #ifdef L0_STATIC_LOADER_BUILD
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
            #ifdef L0_STATIC_LOADER_BUILD
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
#ifdef L0_STATIC_LOADER_BUILD
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
        #ifdef L0_STATIC_LOADER_BUILD
        std::call_once(ze_lib::context->initTeardownCallbacksOnce, [this]() {
            if (!delayContextDestruction) {
                std::atexit(context_at_exit_destructor);
            }
            // Get the function pointer for zelRegisterTeardownCallback from the dynamic loader
            typedef ze_result_t (ZE_APICALL *zelRegisterTeardownCallback_t)(
                zel_loader_teardown_callback_t,
                zel_application_teardown_callback_t*,
                uint32_t*);
            auto pfnZelRegisterTeardownCallback = reinterpret_cast<zelRegisterTeardownCallback_t>(
                GET_FUNCTION_PTR(loader, "zelRegisterTeardownCallback"));
            if (pfnZelRegisterTeardownCallback != nullptr) {
                auto register_teardown_result = pfnZelRegisterTeardownCallback(staticLoaderTeardownCallback, &loaderTeardownCallback, &loaderTeardownCallbackIndex);
                if (register_teardown_result != ZE_RESULT_SUCCESS) {
                    std::string message = "ze_lib Context Init() zelRegisterTeardownCallback failed with ";
                    debug_trace_message(message, to_string(register_teardown_result));
                } else {
                    loaderTeardownRegistrationEnabled = true;
                    std::string message = "ze_lib Context Init() zelRegisterTeardownCallback completed for the static loader with";
                    debug_trace_message(message, to_string(register_teardown_result));
                }
            }
        });
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
#ifdef L0_STATIC_LOADER_BUILD
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
#ifdef L0_STATIC_LOADER_BUILD
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
        if (ze_lib::context) {
            // Given the driver teardown, notify the registered callbacks that the loader is being torn down.
            for (auto &callback : ze_lib::context->teardownCallbacks) {
                callback.second();
            }
            // Clear the registered callbacks now that they have been called.
            ze_lib::context->teardownCallbacks.clear();
        }

        ze_lib::destruction = true;
    }
    return result;
}

void ZE_APICALL
zelSetDelayLoaderContextTeardown()
{
    #ifdef L0_STATIC_LOADER_BUILD
    if (!ze_lib::delayContextDestruction) {
        ze_lib::delayContextDestruction = true;
    }
    #endif
}

/// @brief Registers a teardown callback function to be invoked during loader teardown.
///
/// This function allows an application to register a callback that will be called when the loader is being torn down.
/// The loader provides a callback function pointer to the application, which the application should call to notify
/// the loader that it is tearing down. The loader will then remove the application's callback from its list of registered callbacks.
///
/// @param[in] application_callback
///     The application's callback function to be called during loader teardown. Must not be nullptr.
/// @param[out] loader_callback
///     Pointer to the loader's callback function. The application should call this function to notify the loader of teardown.
/// @param[out] index
///     Pointer to a uint32_t that will receive the index assigned to the registered callback.
///
/// @return
///     - ZE_RESULT_SUCCESS: The callback was successfully registered.
///     - ZE_RESULT_ERROR_INVALID_ARGUMENT: The application_callback parameter is nullptr.
///     - ZE_RESULT_ERROR_UNINITIALIZED: The loader context is not initialized.
ze_result_t ZE_APICALL
zelRegisterTeardownCallback(
   zel_loader_teardown_callback_t application_callback, // [in] Application's callback function to be called during loader teardown
   zel_application_teardown_callback_t *loader_callback, // [out] Pointer to the loader's callback function
   uint32_t *index // [out] Index assigned to the registered callback
) {
    ze_result_t result = ZE_RESULT_SUCCESS;
    if (nullptr == application_callback) {
        return ZE_RESULT_ERROR_INVALID_ARGUMENT;
    }
    if (!ze_lib::context) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }
    {
        std::lock_guard<std::mutex> lock(ze_lib::context->teardownCallbacksMutex);
        // Assign the loader's callback function to the application callback such that the application can notify the loader
        // that it is tearing down. The loader will then remove the application's callback from the list of callbacks.
        *loader_callback = ze_lib::applicationTeardownCallback;
        // Increment the teardown callback count and assign the index to the application callback.
        ze_lib::context->teardownCallbacksCount.fetch_add(1);
        *index = ze_lib::context->teardownCallbacksCount.load();
        ze_lib::context->teardownCallbacks.insert(std::pair<uint32_t, zel_loader_teardown_callback_t>(*index, application_callback));
        if (ze_lib::context->debugTraceEnabled) {
            std::string message = "Registered teardown callback with index: " + std::to_string(*index);
            ze_lib::context->debug_trace_message(message, "");
        }
    }
    return result;
}

/// @brief Checks if the Level Zero loader is currently in the teardown state.
///
/// This function determines whether the loader is in the process of being destroyed or is otherwise
/// unavailable for further API calls. It performs several checks, including:
/// - Whether the loader's destruction flag is set or the context is null.
/// - On Windows with dynamic loading, it checks for loader teardown notifications,
///   registration status, and the stability of the loader by attempting to call `loaderDriverGet`.
/// - If any of these checks indicate the loader is in teardown or unstable, the function returns true.
///
/// @return true if the loader is in teardown or unstable; false otherwise.
bool ZE_APICALL
zelCheckIsLoaderInTearDown() {
    if (ze_lib::destruction || ze_lib::context == nullptr) {
        return true;
    }
    #if defined(L0_STATIC_LOADER_BUILD) && defined(_WIN32)
    static bool loaderIsStable = true;
    if (!loaderIsStable) {
        if (ze_lib::context->debugTraceEnabled) {
            std::string message = "Loader Teardown check failed before, exiting.";
            ze_lib::context->debug_trace_message(message, "");
        }
        return true;
    }
    if (ze_lib::loaderTeardownCallbackReceived) {
        if (ze_lib::context->debugTraceEnabled) {
            std::string message = "Loader Teardown Notification Received, loader in teardown state.";
            ze_lib::context->debug_trace_message(message, "");
        }
        loaderIsStable = false;
        return true;
    }
    if (!ze_lib::loaderTeardownRegistrationEnabled) {
        try {
            if (!ze_lib::context->loaderDriverGet) {
                if (ze_lib::context->debugTraceEnabled) {
                    std::string message = "LoaderDriverGet is a bad pointer. Exiting stability checker.";
                    ze_lib::context->debug_trace_message(message, "");
                }
                loaderIsStable = false;
                return true;
            }

            uint32_t driverCount = 0;
            ze_result_t result = ZE_RESULT_ERROR_UNINITIALIZED;
            result = ze_lib::context->loaderDriverGet(&driverCount, nullptr);
            if (result != ZE_RESULT_SUCCESS || driverCount == 0) {
                if (ze_lib::context->debugTraceEnabled) {
                    std::string message = "Loader stability check failed. Exiting stability checker.";
                    ze_lib::context->debug_trace_message(message, "");
                }
                loaderIsStable = false;
                return true;
            }
        } catch (...) {
            if (ze_lib::context->debugTraceEnabled) {
                std::string message = "Loader stability check failed. Exception occurred.";
                ze_lib::context->debug_trace_message(message, "");
            }
            loaderIsStable = false;
            return true;
        }
    }
    #endif
    return false;
}

void ZE_APICALL
zelLoaderContextTeardown()
{
    #ifdef L0_STATIC_LOADER_BUILD
    if (ze_lib::delayContextDestruction && ze_lib::context) {
        delete ze_lib::context;
        ze_lib::context = nullptr;
    }
    #endif
}

ze_result_t ZE_APICALL
zelEnableTracingLayer()
{
    #ifdef L0_STATIC_LOADER_BUILD
    if(nullptr == ze_lib::context->loader)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *zelEnableTracingLayerInternal_t)();
    auto enableDynamicTracing = reinterpret_cast<zelEnableTracingLayerInternal_t>(
            GET_FUNCTION_PTR(ze_lib::context->loader, "zelEnableTracingLayer") );
    return enableDynamicTracing();
    #else
    if (ze_lib::context->dynamicTracingSupported == false) {
        return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }
    if (ze_lib::context->tracingLayerEnableCounter.fetch_add(1) == 0) {
        ze_lib::context->zeDdiTable.exchange(ze_lib::context->pTracingZeDdiTable);
    }
    #endif
    return ZE_RESULT_SUCCESS;
}

ze_result_t ZE_APICALL
zelDisableTracingLayer()
{
    #ifdef L0_STATIC_LOADER_BUILD
    if(nullptr == ze_lib::context->loader)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    typedef ze_result_t (ZE_APICALL *zelDisableTracingLayerInternal_t)();
    auto disableDynamicTracing = reinterpret_cast<zelDisableTracingLayerInternal_t>(
            GET_FUNCTION_PTR(ze_lib::context->loader, "zelDisableTracingLayer") );
    return disableDynamicTracing();
    #else
    if (ze_lib::context->dynamicTracingSupported == false) {
        return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }
    if (ze_lib::context->tracingLayerEnableCounter.fetch_sub(1) <= 1) {
        ze_lib::context->zeDdiTable.exchange(&ze_lib::context->initialzeDdiTable);
    }
    #endif
    return ZE_RESULT_SUCCESS;
}

} //extern "c"