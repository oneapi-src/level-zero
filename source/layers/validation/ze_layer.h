/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_layer.h
 *
 */
#pragma once
#include "ze_ddi.h"
#include "zet_ddi.h"
#include "ze_util.h"

namespace layer
{
    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        ze_api_version_t version = ZE_API_VERSION_1_0;

        bool enableParameterValidation = false;
        bool enableHandleLifetime = false;
        bool enableMemoryTracker = false;
        bool enableThreadingValidation = false;

        ze_dditable_t   zeDdiTable = {};
        zet_dditable_t  zetDdiTable = {};

        context_t();
        ~context_t();
    };

    extern context_t context;
}
