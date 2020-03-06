/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#pragma once
#include "ze_api.h"
#include "ze_ddi.h"
#include "ze_util.h"
#include <vector>

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        HMODULE loader = nullptr;

        context_t();
        ~context_t();

        ze_result_t Init();

        ze_dditable_t   ddiTable = {};
    };

    extern context_t context;

} // namespace ze_lib
