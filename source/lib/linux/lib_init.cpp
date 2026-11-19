/*
 *
 * Copyright (C) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "../ze_lib.h"

namespace ze_lib
{
#if !defined(L0_STATIC_LOADER_BUILD) && !defined(L0_STATIC_LOADER_BUILD_NO_DLL)
    void __attribute__((constructor)) createLibContext() {
        context = new context_t;
    }
void __attribute__((destructor)) deleteLibContext() {
    delete context;
} 
#endif

}