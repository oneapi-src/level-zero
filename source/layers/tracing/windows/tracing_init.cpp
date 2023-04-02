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
extern "C" BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_DETACH) {
      delete pGlobalAPITracerContextImp;
    } else if (fdwReason == DLL_PROCESS_ATTACH) {
      pGlobalAPITracerContextImp = new APITracerContextImp;
    }
   return TRUE;
}
} // namespace tracing_layer
