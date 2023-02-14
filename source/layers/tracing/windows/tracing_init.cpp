/*
 *
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: Apache 2.0
 *
 */
#include "../tracing_imp.h"
#include <Windows.h>

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
