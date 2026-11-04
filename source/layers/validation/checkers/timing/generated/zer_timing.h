/*
 * ***THIS FILE IS GENERATED. ***
 * See timing.h.mako for modifications
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_timing.h
 *
 */
#pragma once
#include "../zel_global_timing_state.h"
#include "zer_entry_points.h"

namespace validation_layer {
class ZERtimingCheckerGenerated : public ZERValidationEntryPoints {
public:
    virtual ze_result_t zerGetLastErrorDescriptionPrologue( const char** ppString ) override {
        GlobalTimingState::getInstance().recordStart();
        return ZE_RESULT_SUCCESS;
    }
    virtual ze_result_t zerGetLastErrorDescriptionEpilogue( const char** ppString , ze_result_t result) override {
        GlobalTimingState::getInstance().recordEnd("zerGetLastErrorDescription");
        return ZE_RESULT_SUCCESS;
    }
    virtual ze_result_t zerTranslateDeviceHandleToIdentifierPrologue( ze_device_handle_t hDevice ) override {
        GlobalTimingState::getInstance().recordStart();
        return ZE_RESULT_SUCCESS;
    }
    virtual ze_result_t zerTranslateDeviceHandleToIdentifierEpilogue( ze_device_handle_t hDevice , uint32_t result) override {
        GlobalTimingState::getInstance().recordEnd("zerTranslateDeviceHandleToIdentifier");
        return ZE_RESULT_SUCCESS;
    }
    virtual ze_result_t zerTranslateIdentifierToDeviceHandlePrologue( uint32_t identifier ) override {
        GlobalTimingState::getInstance().recordStart();
        return ZE_RESULT_SUCCESS;
    }
    virtual ze_result_t zerTranslateIdentifierToDeviceHandleEpilogue( uint32_t identifier , ze_device_handle_t result) override {
        GlobalTimingState::getInstance().recordEnd("zerTranslateIdentifierToDeviceHandle");
        return ZE_RESULT_SUCCESS;
    }
    virtual ze_result_t zerGetDefaultContextPrologue( void ) override {
        GlobalTimingState::getInstance().recordStart();
        return ZE_RESULT_SUCCESS;
    }
    virtual ze_result_t zerGetDefaultContextEpilogue( ze_context_handle_t result ) override {
        GlobalTimingState::getInstance().recordEnd("zerGetDefaultContext");
        return ZE_RESULT_SUCCESS;
    }
};
} // namespace validation_layer
