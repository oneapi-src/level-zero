/*
 *
 * Copyright (C) 2020-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_loader_api.cpp
 *
 */

#include "ze_loader_internal.h"
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
zeLoaderInit();

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for verifying usable L0 Drivers for Loader to report
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderDriverCheck(ze_init_flags_t flags);


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


ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderTranslateHandleInternal(
   zel_handle_type_t handleType,         //Handle type
   void *handleIn,                        //Input: handle to translate from loader handle to driver handle 
   void **handleOut);                      //Output: Pointer to handleOut is set to driver handle if successful


#if defined(__cplusplus)
}
#endif