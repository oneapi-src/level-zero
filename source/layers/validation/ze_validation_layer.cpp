/*
 *
 * Copyright (C) 2019-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_validation_layer.cpp
 *
 */
#include "ze_validation_layer.h"
#include "param_validation.h"
#include <memory>

namespace validation_layer
{
    context_t& context = context_t::getInstance();

    ///////////////////////////////////////////////////////////////////////////////
    context_t::context_t()
    {
        enableHandleLifetime = getenv_tobool( "ZE_ENABLE_HANDLE_LIFETIME" );
        if (enableHandleLifetime) {
            handleLifetime = std::make_unique<HandleLifetimeValidation>();
        }
        enableThreadingValidation = getenv_tobool( "ZE_ENABLE_THREADING_VALIDATION" );
        verboseLogging = getenv_tobool( "ZEL_LOADER_LOGGING_ENABLE_SUCCESS_PRINT" );

        // Point at the process-lifetime no-op logger until the loader calls
        // zelLoaderSetLogger().  This is never null, so call sites need no null check.
        // Thread-safety: zelLoaderSetLogger() writes this field exactly once on the
        // init thread before zeDdiTable.exchange() makes the layer reachable.
        logger = loader::noopLogger();
    }

    ///////////////////////////////////////////////////////////////////////////////
    context_t::~context_t()
    {
        validationHandlers.clear();
    }
} // namespace validation_layer


#if defined(__cplusplus)
extern "C" {
#endif

ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderGetVersion(zel_component_version_t *version)
{
    if(version == nullptr)
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;
    string_copy_s(version->component_name, VALIDATION_COMP_NAME, ZEL_COMPONENT_STRING_SIZE);
    version->spec_version = ZE_API_VERSION_CURRENT;
    version->component_lib_version.major = LOADER_VERSION_MAJOR;
    version->component_lib_version.minor = LOADER_VERSION_MINOR;
    version->component_lib_version.patch = LOADER_VERSION_PATCH;

    return ZE_RESULT_SUCCESS;
}

/// @brief Called by the loader immediately after dlopen to share its logger.
///        Replaces the no-op default so that validation-layer messages flow
///        through the same sink as the loader.
ZE_DLLEXPORT void ZE_APICALL
zelLoaderSetLogger(loader::ZeLogger *loaderLogger)
{
    if (loaderLogger) {
        validation_layer::context_t::getInstance().logger = loaderLogger;
    }
}

#if defined(__cplusplus)
};
#endif
