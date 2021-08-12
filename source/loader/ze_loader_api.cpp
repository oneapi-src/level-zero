/*
 *
 * Copyright (C) 2020-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_loader_api.cpp
 *
 */

#include "ze_loader.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for initializing loader
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeLoaderInit(ze_init_flags_t flags)
{
    return loader::context->init(flags);
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for getting tracing lib handle
///
/// @returns
///     - ::handle to tracing library
ZE_DLLEXPORT HMODULE ZE_APICALL
zeLoaderGetTracingHandle()
{
    return loader::context->tracingLayer;
}

ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderGetVersionsInternal(
   size_t *num_elems,                     //Pointer to num versions to get.  
   zel_component_version_t *versions)    //Pointer to array of versions. If set to NULL, num_elems is returned
{
    if(nullptr == versions){
        *num_elems = loader::context->compVersions.size();
        return ZE_RESULT_SUCCESS;
    }
    auto size = *num_elems > loader::context->compVersions.size() ? loader::context->compVersions.size() : *num_elems;
    memcpy(versions, loader::context->compVersions.data(), size * sizeof(zel_component_version_t));

    return ZE_RESULT_SUCCESS;
}

#if defined(__cplusplus)
}
#endif