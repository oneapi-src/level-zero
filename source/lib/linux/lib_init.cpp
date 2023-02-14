/*
 *
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: Apache 2.0
 *
 */

#include "../ze_lib.h"

namespace ze_lib
{

    void __attribute__((constructor)) createLibContext() {
        context = new context_t;
    } 

    void __attribute__((destructor)) deleteLibContext() {
        delete context;
    } 

}