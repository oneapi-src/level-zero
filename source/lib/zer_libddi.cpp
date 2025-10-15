/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_libddi.cpp
 *
 */
#include "ze_lib.h"
#ifndef L0_STATIC_LOADER_BUILD
#include "zer_ddi.h"
#endif

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////

#ifdef L0_STATIC_LOADER_BUILD
    __zedlllocal ze_result_t context_t::zerDdiTableInit(ze_api_version_t version)
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            auto getTable = reinterpret_cast<zer_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "zerGetGlobalProcAddrTable") );
            getTableWithCheck(getTable, version, &initialzerDdiTable.Global );
            initialzerDdiTable.Global.pfnGetLastErrorDescription = reinterpret_cast<zer_pfnGetLastErrorDescription_t>(
                GET_FUNCTION_PTR(loader, "zerGetLastErrorDescription") );
            initialzerDdiTable.Global.pfnTranslateDeviceHandleToIdentifier = reinterpret_cast<zer_pfnTranslateDeviceHandleToIdentifier_t>(
                GET_FUNCTION_PTR(loader, "zerTranslateDeviceHandleToIdentifier") );
            initialzerDdiTable.Global.pfnTranslateIdentifierToDeviceHandle = reinterpret_cast<zer_pfnTranslateIdentifierToDeviceHandle_t>(
                GET_FUNCTION_PTR(loader, "zerTranslateIdentifierToDeviceHandle") );
            initialzerDdiTable.Global.pfnGetDefaultContext = reinterpret_cast<zer_pfnGetDefaultContext_t>(
                GET_FUNCTION_PTR(loader, "zerGetDefaultContext") );
        }

        return result;
    }
#else
    __zedlllocal ze_result_t context_t::zerDdiTableInit(ze_api_version_t version)
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            // Optional
            zerGetGlobalProcAddrTable( version, &initialzerDdiTable.Global );
        }

        return result;
    }
#endif

} // namespace ze_lib
