/*
 *
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: Apache 2.0
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