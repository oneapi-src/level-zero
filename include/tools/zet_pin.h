/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_pin.h
 *
 * @brief Intel 'One API' Level-Zero Tool APIs for Program Instrumentation (PIN)
 *
 */
 
#ifndef _ZET_PIN_H
#define _ZET_PIN_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_ZET_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::zet_profile_info_t
typedef enum _zet_profile_info_version_t
{
    ZET_PROFILE_INFO_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),///< version 0.91

} zet_profile_info_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supportted profile features
typedef enum _zet_profile_flag_t
{
    ZET_PROFILE_FLAG_REGISTER_REALLOCATION = ZE_BIT(0), ///< request the compiler attempt to minimize register usage as much as
                                                    ///< possible to allow for instrumentation
    ZET_PROFILE_FLAG_FREE_REGISTER_INFO = ZE_BIT(1),///< request the compiler generate free register info

} zet_profile_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Profiling meta-data for instrumentation
typedef struct _zet_profile_info_t
{
    zet_profile_info_version_t version;             ///< [in] ::ZET_PROFILE_INFO_VERSION_CURRENT
    zet_profile_flag_t flags;                       ///< [out] indicates which flags were enabled during compilation
    uint32_t numTokens;                             ///< [out] number of tokens immediately following this structure

} zet_profile_info_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported profile token types
typedef enum _zet_profile_token_type_t
{
    ZET_PROFILE_TOKEN_TYPE_FREE_REGISTER,           ///< GRF info

} zet_profile_token_type_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Profile free register token detailing unused registers in the current
///        function
typedef struct _zet_profile_free_register_token_t
{
    zet_profile_token_type_t type;                  ///< [out] type of token
    uint32_t size;                                  ///< [out] total size of the token, in bytes
    uint32_t count;                                 ///< [out] number of register sequences immediately following this
                                                    ///< structure

} zet_profile_free_register_token_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Profile register sequence detailing consecutive bytes, all of which
///        are unused
typedef struct _zet_profile_register_sequence_t
{
    uint32_t start;                                 ///< [out] starting byte in the register table, representing the start of
                                                    ///< unused bytes in the current function
    uint32_t count;                                 ///< [out] number of consecutive bytes in the sequence, starting from start

} zet_profile_register_sequence_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve profiling information generated for the kernel.
/// 
/// @details
///     - Module must be created using the following build option:
///         + "-zet-profile-flags <n>" - enable generation of profile
///           information
///         + "<n>" must be a combination of ::zet_profile_flag_t, in hex
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hKernel`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pInfo`
__ze_api_export ze_result_t __zecall
zetKernelGetProfileInfo(
    zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
    zet_profile_info_t* pInfo                       ///< [out] pointer to profile info
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZET_PIN_H
