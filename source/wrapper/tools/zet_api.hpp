/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_api.hpp
 *
 */
#ifndef _ZET_API_HPP
#define _ZET_API_HPP
#if defined(__cplusplus)
#pragma once

// C API headers
#include "zet_api.h"

// 'core' C++ API headers
#include "ze_api.hpp"

// 'tools' API headers
#include "zet_common.hpp"
#include "zet_driver.hpp"
#include "zet_device.hpp"
#include "zet_cmdlist.hpp"
#include "zet_sysman.hpp"
#include "zet_module.hpp"
#include "zet_pin.hpp"
#include "zet_metric.hpp"
#include "zet_debug.hpp"
#include "zet_tracing.hpp"

#endif // defined(__cplusplus)
#endif // _ZET_API_HPP