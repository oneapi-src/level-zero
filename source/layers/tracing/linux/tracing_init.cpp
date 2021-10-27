/*
 *
 * Copyright (C) 2019-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "../tracing_imp.h"

namespace tracing_layer
{
    void __attribute__((constructor)) createAPITracerContextImp() {
        pGlobalAPITracerContextImp = new struct APITracerContextImp;
    }

    void __attribute__((destructor)) deleteAPITracerContextImp() {
        delete pGlobalAPITracerContextImp;
    }
}
