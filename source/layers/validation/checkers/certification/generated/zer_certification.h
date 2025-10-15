/*
 * ***THIS FILE IS GENERATED. ***
 *
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_certification.h
 *
 */
#pragma once
#include "../zel_global_certification_state.h"
#include "zer_entry_points.h"

namespace validation_layer {
class ZERcertificationCheckerGenerated : public ZERValidationEntryPoints {
public:
    virtual ze_result_t zerGetLastErrorDescriptionPrologue( const char** ppString ) override {
        if (GlobalCertificationState::getInstance().certification_version < ZE_API_VERSION_1_14) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        return ZE_RESULT_SUCCESS;
    }
    virtual ze_result_t zerTranslateDeviceHandleToIdentifierPrologue( ze_device_handle_t hDevice ) override {
        if (GlobalCertificationState::getInstance().certification_version < ZE_API_VERSION_1_14) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        return ZE_RESULT_SUCCESS;
    }
    virtual ze_result_t zerTranslateIdentifierToDeviceHandlePrologue( uint32_t identifier ) override {
        if (GlobalCertificationState::getInstance().certification_version < ZE_API_VERSION_1_14) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        return ZE_RESULT_SUCCESS;
    }
    virtual ze_result_t zerGetDefaultContextPrologue( void ) override {
        if (GlobalCertificationState::getInstance().certification_version < ZE_API_VERSION_1_14) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        return ZE_RESULT_SUCCESS;
    }
};
} // namespace validation_layer
