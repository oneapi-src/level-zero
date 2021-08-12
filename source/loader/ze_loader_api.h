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
#include "loader/ze_loader.h"

#define TRACING_COMP_NAME "loader"

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
zeLoaderInit(ze_init_flags_t flags);


///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for getting tracing lib handle
///
/// @returns
///     - ::handle to tracing library
ZE_DLLEXPORT HMODULE ZE_APICALL
zeLoaderGetTracingHandle();


///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for getting version
///
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderGetVersion(zel_component_version_t *version);


///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for getting versions of all components
///
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderGetVersionsInternal(
   size_t *num_elems,                     //Pointer to num versions to get.  
   zel_component_version_t *versions);    //Pointer to array of versions. If set to NULL, num_elems is returned

#if defined(__cplusplus)
}
#endif