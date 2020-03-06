/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_api.h
 *
 */
#ifndef _ZE_API_H
#define _ZE_API_H
#if defined(__cplusplus)
#pragma once
#endif

// standard headers
#include <stdint.h>
#include <stddef.h>

// 'core' API headers
#include "ze_common.h"
#include "ze_driver.h"
#include "ze_device.h"
#include "ze_cmdqueue.h"
#include "ze_cmdlist.h"
#include "ze_image.h"
#include "ze_barrier.h"
#include "ze_module.h"
#include "ze_residency.h"
#include "ze_cl_interop.h"
#include "ze_event.h"
#include "ze_sampler.h"
#include "ze_memory.h"
#include "ze_fence.h"
#include "ze_copy.h"

#endif // _ZE_API_H