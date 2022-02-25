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

namespace validation_layer
{
    context_t context;

    ///////////////////////////////////////////////////////////////////////////////
    context_t::context_t()
    {
        enableParameterValidation = getenv_tobool( "ZE_ENABLE_PARAMETER_VALIDATION" );
        enableHandleLifetime = getenv_tobool( "ZE_ENABLE_HANDLE_LIFETIME" );
        enableMemoryTracker = getenv_tobool( "ZE_ENABLE_MEMORY_TRACKER" );
        enableThreadingValidation = getenv_tobool( "ZE_ENABLE_THREADING_VALIDATION" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    context_t::~context_t()
    {
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


#if defined(__cplusplus)
};
#endif
