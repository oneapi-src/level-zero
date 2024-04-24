/*
 *
 * Copyright (C) 2019-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_lib.h
 *
 */
#pragma once
#include "ze_api.h"
#include "ze_ddi.h"
#include "zet_api.h"
#include "zet_ddi.h"
#include "zes_api.h"
#include "zes_ddi.h"
#include "layers/zel_tracing_api.h"
#include "layers/zel_tracing_ddi.h"
#include "ze_util.h"
#include <vector>
#include <mutex>
#include <atomic>

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
#ifdef DYNAMIC_LOAD_LOADER
        HMODULE loader = nullptr;
#endif

        context_t();
        ~context_t();

        std::once_flag initOnce;
        std::once_flag initOnceSysMan;

        ze_result_t Init(ze_init_flags_t flags, bool sysmanOnly);

        ze_result_t zeInit();
        std::atomic<ze_dditable_t *>  zeDdiTable = {nullptr};

        ze_result_t zetInit();
        std::atomic<zet_dditable_t *> zetDdiTable = {nullptr};

        ze_result_t zesInit();
        std::atomic<zes_dditable_t *> zesDdiTable = {nullptr};

        ze_result_t zelTracingInit();
        zel_tracing_dditable_t  zelTracingDdiTable = {};
        std::atomic<ze_dditable_t *> pTracingZeDdiTable = {nullptr};
        std::atomic<zet_dditable_t *> pTracingZetDdiTable = {nullptr};
        std::atomic<zes_dditable_t *> pTracingZesDdiTable = {nullptr};
        ze_dditable_t initialzeDdiTable;
        zet_dditable_t initialzetDdiTable;
        zes_dditable_t initialzesDdiTable;
        std::atomic_uint32_t tracingLayerEnableCounter{0};

        HMODULE tracing_lib = nullptr;
        bool isInitialized = false;
        bool inTeardown = false;
    };

    extern context_t *context;
    extern bool destruction;

} // namespace ze_lib
