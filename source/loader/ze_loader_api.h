/*
 *
 * Copyright (C) 2020-2025 Intel Corporation
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
/// @deprecated This function is deprecated and will be removed in a future release.
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderDriverCheck(ze_init_flags_t flags, ze_init_driver_type_desc_t* desc, ze_global_dditable_t *globalInitStored, zes_global_dditable_t *sysmanGlobalInitStored, bool *requireDdiReinit, bool sysmanOnly);


///////////////////////////////////////////////////////////////////////////////
/// @brief Internal function for Setting the ZE ddi table for the Tracing Layer.
///
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderTracingLayerInit(std::atomic<ze_dditable_t *> &zeDdiTable);

///////////////////////////////////////////////////////////////////////////////
/// @brief Internal function for Setting the ZER ddi table for the Tracing Layer.
///
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelLoaderZerTracingLayerInit(std::atomic<zer_dditable_t *> &zerDdiTable);


///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for getting tracing lib handle
///
/// @returns
///     - ::handle to tracing library
ZE_DLLEXPORT HMODULE ZE_APICALL
zeLoaderGetTracingHandle();

///////////////////////////////////////////////////////////////////////////////
/// @brief Get pointer to Loader Context
///
/// @returns
///     - ::Pointer to the Loader's Context
ZE_DLLEXPORT loader::context_t *ZE_APICALL
zelLoaderGetContext();

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


///////////////////////////////////////////////////////////////////////////////
/// @brief Proof-of-concept: unload a single driver identified by its handle.
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelUnloadDriverInternal(
   ze_driver_handle_t hDriver);           //Input: driver handle to unload


///////////////////////////////////////////////////////////////////////////////
/// @brief Proof-of-concept: unload a single driver, optionally forcing the unload
///        even when the driver still owns live child objects.
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelUnloadDriverExtInternal(
   ze_driver_handle_t hDriver,            //Input: driver handle to unload
   zel_unload_driver_flags_t flags);      //Input: combination of ::zel_unload_driver_flag_t


///////////////////////////////////////////////////////////////////////////////
/// @brief Proof-of-concept: reload a previously unloaded driver into its original
///        slot and rebind the supplied driver handle onto the fresh driver.
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
ZE_DLLEXPORT ze_result_t ZE_APICALL
zelReloadDriverInternal(
   ze_driver_handle_t hDriver);           //Input: driver handle to reload


#if defined(__cplusplus)
}
#endif