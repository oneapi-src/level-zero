/*
 * ***THIS FILE IS GENERATED. ***
 * See handle_lifetime.h.mako for modifications
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_handle_lifetime.h
 *
 */

#pragma once
#include "zer_entry_points.h"


namespace validation_layer
{

    class ZERHandleLifetimeValidation : public ZERValidationEntryPoints {
    public:
                ze_result_t zerTranslateDeviceHandleToIdentifierPrologue( ze_device_handle_t hDevice ) override;
                    };

}
