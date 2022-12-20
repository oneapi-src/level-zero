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

    void __attribute__((constructor)) createLoaderContext() {
        context = new context_t;
    }

    void __attribute__((destructor)) deleteLoaderContext() {
        delete context;
    }

}