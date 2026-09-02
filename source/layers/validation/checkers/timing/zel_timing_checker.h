/*
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_timing_checker.h
 *
 */

#pragma once

#include "generated/ze_timing.h"
#include "generated/zes_timing.h"
#include "generated/zet_timing.h"
#include "generated/zer_timing.h"
#include "ze_api.h"
#include "ze_validation_layer.h"
#include "zel_global_timing_state.h"

namespace validation_layer {

class __zedlllocal timingChecker : public validationChecker {
public:
  timingChecker();
  ~timingChecker();
  class ZEtimingChecker : public ZEtimingCheckerGenerated {};
  class ZEStimingChecker : public ZEStimingCheckerGenerated {};
  class ZETtimingChecker : public ZETtimingCheckerGenerated {};
  class ZERtimingChecker : public ZERtimingCheckerGenerated {};

  bool enabletiming = false;

  GlobalTimingState &globalTimingState = GlobalTimingState::getInstance();
};
extern class timingChecker timing_checker;
} // namespace validation_layer
