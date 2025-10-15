/*
 * Copyright (C) 2020-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_layer.h
 *
 */
#pragma once
#include "ze_ddi.h"
#include "zer_ddi.h"
#include "ze_util.h"
#include "tracing_imp.h"

namespace tracing_layer
{
    ///////////////////////////////////////////////////////////////////////////////
    class __zedlllocal context_t
    {
    public:
        ze_api_version_t version = ZE_API_VERSION_CURRENT;

        ze_dditable_t   zeDdiTable = {};
        zer_dditable_t  zerDdiTable = {};

        context_t();
        ~context_t();
    };

    extern context_t context;
} // namespace tracing_layer
