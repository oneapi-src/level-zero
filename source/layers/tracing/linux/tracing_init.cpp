/*
 *
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: Apache 2.0
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
