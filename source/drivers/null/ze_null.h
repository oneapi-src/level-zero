/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_null.h
 *
 */
#pragma once
#include <stdlib.h>
#include <vector>
#include "ze_ddi.h"
#include "zet_ddi.h"
#include "zes_ddi.h"
#include "ze_util.h"
#include "ze_ddi_common.h"

#ifndef ZEL_NULL_DRIVER_ID
#define ZEL_NULL_DRIVER_ID 1
#endif

namespace driver
{
    extern ze_dditable_driver_t pCore;
    extern zet_dditable_driver_t pTools;
    extern zes_dditable_driver_t pSysman;
    struct __zedlllocal BaseNullHandle : ze_handle_t {
        BaseNullHandle() {
            pCore = &driver::pCore;
            pTools = &driver::pTools;
            pSysman = &driver::pSysman;
        }
    };
    ///////////////////////////////////////////////////////////////////////////////
    class __zedlllocal context_t
    {
    public:
        ze_api_version_t version = ZE_API_VERSION_CURRENT;

        ze_dditable_t   zeDdiTable = {};
        zet_dditable_t  zetDdiTable = {};
        zes_dditable_t  zesDdiTable = {};
        std::vector<BaseNullHandle*> globalBaseNullHandle;
        bool ddiExtensionRequested = false;
        context_t();
        ~context_t() {
            for (auto handle : globalBaseNullHandle) {
                delete handle;
            }
        }

        void* get( void )
        {
            static uint64_t count = 0x80800000;
            if (ddiExtensionRequested) {
                globalBaseNullHandle.push_back(new BaseNullHandle());
                return reinterpret_cast<void*>(globalBaseNullHandle.back());
            } else {
                return reinterpret_cast<void*>( ++count );
            }
        }
    };

    extern context_t context;
} // namespace driver

namespace instrumented
{
    //////////////////////////////////////////////////////////////////////////
    struct tracer_data_t
    {
        ze_bool_t enabled = false;

        void* userData = nullptr;

        ze_callbacks_t zePrologueCbs = {};
        ze_callbacks_t zeEpilogueCbs = {};
    };

    ///////////////////////////////////////////////////////////////////////////////
    class __zedlllocal context_t
    {
    public:
        ze_bool_t enableTracing = false;
        std::vector< tracer_data_t > tracerData;

        context_t();
        ~context_t() = default;
    };

    extern context_t context;
} // namespace instrumented
