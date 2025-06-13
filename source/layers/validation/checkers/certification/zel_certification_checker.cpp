/*
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_certification_checker.cpp
 *
 */
#include "zel_certification_checker.h"
#include "ze_api.h"

namespace validation_layer {
class certificationChecker certification_checker;
using ze_checker = certificationChecker::ZEcertificationChecker;

certificationChecker::certificationChecker() {
  enablecertification = getenv_tobool("ZEL_ENABLE_CERTIFICATION_CHECKER");
  if (enablecertification) {
    certificationChecker::ZEcertificationChecker *zeChecker =
        new certificationChecker::ZEcertificationChecker;
    certificationChecker::ZEScertificationChecker *zesChecker =
        new certificationChecker::ZEScertificationChecker;
    certificationChecker::ZETcertificationChecker *zetChecker =
        new certificationChecker::ZETcertificationChecker;
    ze_api_version_t certification_version = ZE_API_VERSION_CURRENT;
    const auto certification_version_string =
        getenv_string("ZEL_CERTIFICATION_CHECKER_VERSION");
    if (!certification_version_string.empty()) {
      const auto major = certification_version_string.substr(
          0, certification_version_string.find('.'));
      const auto minor = certification_version_string.substr(
          certification_version_string.find('.') + 1);
      certification_version = static_cast<ze_api_version_t>(
          ZE_MAKE_VERSION(std::stoi(major), std::stoi(minor)));
      globalCertificationState.default_mode = false;
    }
    globalCertificationState.certification_version = certification_version;
    certification_checker.zeValidation = zeChecker;
    certification_checker.zetValidation = zetChecker;
    certification_checker.zesValidation = zesChecker;
    validation_layer::context.validationHandlers.push_back(
        &certification_checker);
  }
}

certificationChecker::~certificationChecker() {
  if (enablecertification) {
    delete certification_checker.zeValidation;
    delete certification_checker.zetValidation;
    delete certification_checker.zesValidation;
  }
}

ze_result_t ze_checker::zeDriverGetApiVersionEpilogue(
    ze_driver_handle_t hDriver, ze_api_version_t *version, ze_result_t result) {
  auto &globalCertificationState = GlobalCertificationState::getInstance();
  if (result == ZE_RESULT_SUCCESS && version != nullptr &&
      globalCertificationState.default_mode) {
    globalCertificationState.certification_version = *version;
  }
  return ZE_RESULT_SUCCESS;
}

} // namespace validation_layer
