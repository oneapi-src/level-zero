/*
 * Copyright (C) 2020-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_tracing_libapi.cpp
 *
 * @brief C++ static library for zel tracing layer API.
 *
 * Perhaps generate this from scripts in the future.
 */
#include "ze_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates a tracer on the context.
/// 
/// @details
///     - The tracer is created in the disabled state.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function must be thread-safe.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == desc->pUserData`
///         + `nullptr == phTracer`
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
ze_result_t ZE_APICALL
zelTracerCreate(
    const zel_tracer_desc_t* desc,              ///< [in] pointer to tracer descriptor
    zel_tracer_handle_t* phTracer               ///< [out] pointer to handle of tracer object created
    )
{
    if(ze_lib::context->inTeardown)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    auto pfnCreate = ze_lib::context->zelTracingDdiTable.Tracer.pfnCreate;
    if( nullptr == pfnCreate )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    return pfnCreate( desc, phTracer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a tracer.
/// 
/// @details
///     - The application must **not** call this function from simultaneous
///       threads with the same tracer handle.
///     - The implementation of this function must be thread-safe.
///     - The implementation of this function will stall and wait on any
///       outstanding threads executing callbacks before freeing any Host
///       allocations associated with this tracer.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t ZE_APICALL
zelTracerDestroy(
    zel_tracer_handle_t hTracer                 ///< [in][release] handle of tracer object to destroy
    )
{
    if(ze_lib::context->inTeardown)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    auto pfnDestroy = ze_lib::context->zelTracingDdiTable.Tracer.pfnDestroy;
    if( nullptr == pfnDestroy )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    return pfnDestroy( hTracer );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the collection of callbacks to be executed **before** driver
///        execution.
/// 
/// @details
///     - The application only needs to set the function pointers it is
///       interested in receiving; all others should be 'nullptr'
///     - The application must ensure that no other threads are executing
///       functions for which the tracing functions are changing.
///     - The application must **not** call this function from simultaneous
///       threads with the same tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCoreCbs`
ze_result_t ZE_APICALL
zelTracerSetPrologues(
    zel_tracer_handle_t hTracer,                ///< [in] handle of the tracer
    zel_core_callbacks_t* pCoreCbs              ///< [in] pointer to table of 'core' callback function pointers
    )
{
    if(ze_lib::context->inTeardown)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    auto pfnSetPrologues = ze_lib::context->zelTracingDdiTable.Tracer.pfnSetPrologues;
    if( nullptr == pfnSetPrologues )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    return pfnSetPrologues( hTracer, pCoreCbs );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the collection of callbacks to be executed **after** driver
///        execution.
/// 
/// @details
///     - The application only needs to set the function pointers it is
///       interested in receiving; all others should be 'nullptr'
///     - The application must ensure that no other threads are executing
///       functions for which the tracing functions are changing.
///     - The application must **not** call this function from simultaneous
///       threads with the same tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCoreCbs`
ze_result_t ZE_APICALL
zelTracerSetEpilogues(
    zel_tracer_handle_t hTracer,                ///< [in] handle of the tracer
    zel_core_callbacks_t* pCoreCbs              ///< [in] pointer to table of 'core' callback function pointers
    )
{
    if(ze_lib::context->inTeardown)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    auto pfnSetEpilogues = ze_lib::context->zelTracingDdiTable.Tracer.pfnSetEpilogues;
    if( nullptr == pfnSetEpilogues )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    return pfnSetEpilogues( hTracer, pCoreCbs );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Enables (or disables) the tracer
/// 
/// @details
///     - The application must **not** call this function from simultaneous
///       threads with the same tracer handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hTracer`
ze_result_t ZE_APICALL
zelTracerSetEnabled(
    zel_tracer_handle_t hTracer,                ///< [in] handle of the tracer
    ze_bool_t enable                            ///< [in] enable the tracer if true; disable if false
    )
{
    if(ze_lib::context->inTeardown)
        return ZE_RESULT_ERROR_UNINITIALIZED;
    auto pfnSetEnabled = ze_lib::context->zelTracingDdiTable.Tracer.pfnSetEnabled;
    if( nullptr == pfnSetEnabled )
        return ZE_RESULT_ERROR_UNINITIALIZED;

    return pfnSetEnabled( hTracer, enable );
}

} // extern "C"
