/*
 *
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_certification_checker.h
 *
 */

#pragma once

#include "ze_api.h"

namespace validation_layer {
class GlobalCertificationState {
public:
  static GlobalCertificationState &getInstance() {
    static GlobalCertificationState instance;
    return instance;
  }
  bool default_mode = true;
  ze_api_version_t certification_version = ZE_API_VERSION_1_0;
};
} // namespace validation_layer
