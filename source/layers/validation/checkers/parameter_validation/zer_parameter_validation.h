/*
 * ***THIS FILE IS GENERATED. ***
 * See param.h.mako for modifications
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_parameter_validation.h
 *
 */

#pragma once
#include "ze_validation_layer.h"
#include "zer_entry_points.h"


namespace validation_layer
{

    class ZERParameterValidation : public ZERValidationEntryPoints {
    public:
        ze_result_t zerGetLastErrorDescriptionPrologue( const char** ppString ) override;
        ze_result_t zerTranslateDeviceHandleToIdentifierPrologue( ze_device_handle_t hDevice ) override;
        ze_result_t zerTranslateIdentifierToDeviceHandlePrologue( uint32_t identifier ) override;
        ze_result_t zerGetDefaultContextPrologue( void ) override;
    };
}