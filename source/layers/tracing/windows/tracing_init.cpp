/*
 *
 * Copyright (C) 2019-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "../tracing_imp.h"
#include <windows.h>

namespace tracing_layer {
/*
 * DllMain is called by the OS when the DLL is loaded or unloaded.
 * When modifying the code here, be aware of the restrictions on what can be done
 * inside DllMain. See https://learn.microsoft.com/en-us/windows/win32/dlls/dynamic-link-library-best-practices
 * for more information.
 */
extern "C" BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_DETACH) {
      delete pGlobalAPITracerContextImp;
    } else if (fdwReason == DLL_PROCESS_ATTACH) {
      pGlobalAPITracerContextImp = new APITracerContextImp;
    }
   return TRUE;
}
} // namespace tracing_layer
