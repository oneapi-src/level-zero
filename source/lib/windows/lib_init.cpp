/*
 *
 * Copyright (C) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "../ze_lib.h"
#ifndef L0_STATIC_LOADER_BUILD
#include "../loader/ze_loader_internal.h"
#endif

namespace ze_lib
{
#ifndef L0_STATIC_LOADER_BUILD
    /*
    * DllMain is called by the OS when the DLL is loaded or unloaded.
    * When modifying the code here, be aware of the restrictions on what can be done
    * inside DllMain. See https://learn.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-best-practices
    * for more information.
    */
    extern "C" BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
        if (fdwReason == DLL_PROCESS_DETACH) {
            delete context;
            delete loader::context;
        } else if (fdwReason == DLL_PROCESS_ATTACH) {
            context = new context_t;
            loader::context = new loader::context_t;
        }
        return TRUE;
    }      

#endif
}
