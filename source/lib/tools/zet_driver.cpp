/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "zet_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Initialize the 'One API' driver and must be called before any other
///        API function.
/// 
/// @details
///     - If this function is not called then all other functions will return
///       ::ZE_RESULT_ERROR_UNINITIALIZED.
///     - Only one instance of a driver per process will be initialized.
///     - This function is thread-safe for scenarios where multiple libraries
///       may initialize the driver simultaneously.
/// 
/// @remarks
///   _Analogues_
///     - **cuInit**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + flags
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
ze_result_t __zecall
zetInit(
    ze_init_flag_t flags                            ///< [in] initialization flags
    )
{
    auto result = zet_lib::context.Init();
    if( ZE_RESULT_SUCCESS != result )
        return result;

    auto pfnInit = zet_lib::context.ddiTable.Global.pfnInit;
    if( nullptr == pfnInit )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnInit( flags );
}

} // extern "C"
