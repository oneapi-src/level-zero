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

#include "generated/ze_certification.h"
#include "generated/zes_certification.h"
#include "generated/zet_certification.h"
#include "ze_api.h"
#include "ze_validation_layer.h"
#include "zel_global_certification_state.h"

namespace validation_layer {

class __zedlllocal certificationChecker : public validationChecker {
public:
  certificationChecker();
  ~certificationChecker();
  class ZEcertificationChecker : public ZEcertificationCheckerGenerated {
    ze_result_t zeDriverGetApiVersionEpilogue(ze_driver_handle_t hDriver,
                                              ze_api_version_t *version,
                                              ze_result_t result) override;
  };
  class ZEScertificationChecker : public ZEScertificationCheckerGenerated {};
  class ZETcertificationChecker : public ZETcertificationCheckerGenerated {};

  bool enablecertification = false;

  GlobalCertificationState &globalCertificationState =
      GlobalCertificationState::getInstance();
};
extern class certificationChecker certification_checker;
} // namespace validation_layer
