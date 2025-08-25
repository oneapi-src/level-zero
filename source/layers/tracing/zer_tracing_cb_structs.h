/*
 *
 * Copyright (C) 2021-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_tracing_cb_structs.h
 *
 */
#ifndef zer_tracing_cb_structs_H
#define zer_tracing_cb_structs_H
#if defined(__cplusplus)
#pragma once
#endif

#include "zer_api.h"
#include "layers/zel_tracing_register_cb.h"



///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Global callback functions pointers
typedef struct _zel_zer_global_callbacks_t
{
    zer_pfnGetLastErrorDescriptionCb_t                              pfnGetLastErrorDescriptionCb;
    zer_pfnTranslateDeviceHandleToIdentifierCb_t                    pfnTranslateDeviceHandleToIdentifierCb;
    zer_pfnTranslateIdentifierToDeviceHandleCb_t                    pfnTranslateIdentifierToDeviceHandleCb;
    zer_pfnGetDefaultContextCb_t                                    pfnGetDefaultContextCb;
} zel_zer_global_callbacks_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all callbacks
typedef struct _zel_zer_all_callbacks_t
{
    zel_zer_global_callbacks_t          Global;
} zel_zer_all_callbacks_t;



#endif // zer_tracing_cb_structs_H
