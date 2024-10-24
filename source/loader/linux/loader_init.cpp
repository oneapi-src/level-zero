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
#ifndef DYNAMIC_LOAD_LOADER
    void __attribute__((constructor)) createLoaderContext() {
        printf("loader created context lib dynamic\n");
        context = new context_t;
    }

    void __attribute__((destructor)) deleteLoaderContext() {
        printf("loader destroyed context lib dynamic\n");
        delete context;
    }
#endif
}