/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_ldrddi.h
 *
 */
#pragma once

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
}

namespace loader_driver_ddi
{
    __zedlllocal void ZE_APICALL
    zerDestroyDDiDriverTables(zer_dditable_driver_t* pDdiTable);
    __zedlllocal ze_result_t ZE_APICALL
    zerGetLastErrorDescription(
        const char** ppString                           ///< [in,out] pointer to a null-terminated array of characters describing
                                                        ///< cause of error.
        );
    __zedlllocal uint32_t ZE_APICALL
    zerTranslateDeviceHandleToIdentifier(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        );
    __zedlllocal ze_device_handle_t ZE_APICALL
    zerTranslateIdentifierToDeviceHandle(
        uint32_t identifier                             ///< [in] integer identifier of the device
        );
    __zedlllocal ze_context_handle_t ZE_APICALL
    zerGetDefaultContext(
        void
        );
}

#if defined(__cplusplus)
extern "C" {
#endif

__zedlllocal void ZE_APICALL
zerGetGlobalProcAddrTableLegacy();

#if defined(__cplusplus)
};
#endif
