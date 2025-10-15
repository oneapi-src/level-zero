/*
 * ***THIS FILE IS GENERATED. ***
 * See entry_points.h.mako for modifications
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_entry_points.h
 *
 */
#pragma once
#include "zer_api.h"

namespace validation_layer
{

class ZERValidationEntryPoints {
public:
    virtual ze_result_t zerGetLastErrorDescriptionPrologue( const char** ppString ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zerGetLastErrorDescriptionEpilogue( const char** ppString , ze_result_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zerTranslateDeviceHandleToIdentifierPrologue( ze_device_handle_t hDevice ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zerTranslateDeviceHandleToIdentifierEpilogue( ze_device_handle_t hDevice , uint32_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zerTranslateIdentifierToDeviceHandlePrologue( uint32_t identifier ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zerTranslateIdentifierToDeviceHandleEpilogue( uint32_t identifier , ze_device_handle_t result) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zerGetDefaultContextPrologue( void ) {return ZE_RESULT_SUCCESS;}
    virtual ze_result_t zerGetDefaultContextEpilogue( ze_context_handle_t result ) {return ZE_RESULT_SUCCESS;}
    virtual ~ZERValidationEntryPoints() {}
};
}