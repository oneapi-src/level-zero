/*
 * Copyright (C) 2020-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_tracing_libddi.cpp
 * Perhaps have this generated at some point.
 *
 */
#include "ze_lib.h"
#include "layers/zel_tracing_ddi.h"

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////

#ifdef DYNAMIC_LOAD_LOADER
    __zedlllocal ze_result_t context_t::zelTracingInit()
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<zel_pfnGetTracerApiProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zelGetTracerApiProcAddrTable") );
            result = getTable( ZE_API_VERSION_CURRENT, &zelTracingDdiTable.Tracer);
        }

        return result;
    }
#else
    __zedlllocal ze_result_t context_t::zelTracingInit()
    {
        ze_result_t result;
        result = zelGetTracerApiProcAddrTable( ZE_API_VERSION_CURRENT, &zelTracingDdiTable.Tracer);
        return result;
    }
#endif
} // namespace ze_lib
