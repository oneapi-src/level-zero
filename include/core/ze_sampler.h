/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_sampler.h
 *
 * @brief Intel 'One API' Level-Zero APIs for Sampler
 *
 */
 
#ifndef _ZE_SAMPLER_H
#define _ZE_SAMPLER_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_ZE_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_sampler_desc_t
typedef enum _ze_sampler_desc_version_t
{
    ZE_SAMPLER_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ), ///< version 0.91

} ze_sampler_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sampler addressing modes
typedef enum _ze_sampler_address_mode_t
{
    ZE_SAMPLER_ADDRESS_MODE_NONE = 0,               ///< No coordinate modifications for out-of-bounds image access.
    ZE_SAMPLER_ADDRESS_MODE_REPEAT,                 ///< Out-of-bounds coordinates are wrapped back around.
    ZE_SAMPLER_ADDRESS_MODE_CLAMP,                  ///< Out-of-bounds coordinates are clamped to edge.
    ZE_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,        ///< Out-of-bounds coordinates are clamped to border color which is (0.0f,
                                                    ///< 0.0f, 0.0f, 0.0f) if image format swizzle contains alpha, otherwise
                                                    ///< (0.0f, 0.0f, 0.0f, 1.0f).
    ZE_SAMPLER_ADDRESS_MODE_MIRROR,                 ///< Out-of-bounds coordinates are mirrored starting from edge.

} ze_sampler_address_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sampler filtering modes
typedef enum _ze_sampler_filter_mode_t
{
    ZE_SAMPLER_FILTER_MODE_NEAREST = 0,             ///< No coordinate modifications for out of bounds image access.
    ZE_SAMPLER_FILTER_MODE_LINEAR,                  ///< Out-of-bounds coordinates are wrapped back around.

} ze_sampler_filter_mode_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sampler descriptor
typedef struct _ze_sampler_desc_t
{
    ze_sampler_desc_version_t version;              ///< [in] ::ZE_SAMPLER_DESC_VERSION_CURRENT
    ze_sampler_address_mode_t addressMode;          ///< [in] Sampler addressing mode to determine how out-of-bounds
                                                    ///< coordinates are handled.
    ze_sampler_filter_mode_t filterMode;            ///< [in] Sampler filter mode to determine how samples are filtered.
    ze_bool_t isNormalized;                         ///< [in] Are coordinates normalized [0, 1] or not.

} ze_sampler_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates sampler object.
/// 
/// @details
///     - The sampler can only be used on the device on which it was created.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phSampler`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_SAMPLER_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->addressMode
///         + desc->filterMode
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
__ze_api_export ze_result_t __zecall
zeSamplerCreate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_sampler_desc_t* desc,                  ///< [in] pointer to sampler descriptor
    ze_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys sampler object
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the sampler before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this module
///     - The application may **not** call this function from simultaneous
///       threads with the same sampler handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSampler`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
__ze_api_export ze_result_t __zecall
zeSamplerDestroy(
    ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_SAMPLER_H
