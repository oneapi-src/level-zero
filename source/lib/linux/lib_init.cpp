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
#ifndef DYNAMIC_LOAD_LOADER
    void __attribute__((constructor)) createLibContext() {
        context = new context_t;
    }
void __attribute__((destructor)) deleteLibContext() {
    delete context;
} 
#endif

}