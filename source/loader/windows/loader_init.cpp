/*
 *
 * Copyright (C) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "../ze_loader_internal.h"

namespace loader
{
#ifdef DYNAMIC_LOAD_LOADER
    extern "C" BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
        if (fdwReason == DLL_PROCESS_DETACH) {
            delete context;
        } else if (fdwReason == DLL_PROCESS_ATTACH) {
            context = new context_t;
        }
        return TRUE;
    }
#endif
}