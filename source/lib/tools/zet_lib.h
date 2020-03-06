/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#pragma once
#include "zet_api.h"
#include "zet_ddi.h"
#include "ze_util.h"
#include <vector>

namespace zet_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        HMODULE loader = nullptr;

        context_t();
        ~context_t();

        ze_result_t Init();

        zet_dditable_t  ddiTable = {};
    };

    extern context_t context;

} // namespace zet_lib
