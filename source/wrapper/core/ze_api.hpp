/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_api.hpp
 *
 */
#ifndef _ZE_API_HPP
#define _ZE_API_HPP
#if defined(__cplusplus)
#pragma once

// C API headers
#include "ze_api.h"

// standard headers
#include <stdint.h>
#include <string.h>
#include <exception>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>

// 'core' API headers
#include "ze_common.hpp"
#include "ze_driver.hpp"
#include "ze_device.hpp"
#include "ze_cmdqueue.hpp"
#include "ze_cmdlist.hpp"
#include "ze_image.hpp"
#include "ze_barrier.hpp"
#include "ze_module.hpp"
#include "ze_residency.hpp"
#include "ze_cl_interop.hpp"
#include "ze_event.hpp"
#include "ze_sampler.hpp"
#include "ze_memory.hpp"
#include "ze_fence.hpp"
#include "ze_copy.hpp"

#endif // defined(__cplusplus)
#endif // _ZE_API_HPP