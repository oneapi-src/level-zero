/*
 * ***THIS FILE IS GENERATED. ***
 * See param.cpp.mako for modifications
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zer_parameter_validation.cpp
 *
 */
#include "ze_validation_layer.h"
#include "param_validation.h"

namespace validation_layer
{

    ze_result_t
    ZERParameterValidation::zerGetLastErrorDescriptionPrologue(
        const char** ppString                           ///< [in,out] pointer to a null-terminated array of characters describing
                                                        ///< cause of error.
        )
    {
        if( nullptr == ppString )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZERParameterValidation::zerTranslateDeviceHandleToIdentifierPrologue(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZERParameterValidation::zerTranslateIdentifierToDeviceHandlePrologue(
        uint32_t identifier                             ///< [in] integer identifier of the device
        )
    {
        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZERParameterValidation::zerGetDefaultContextPrologue(
        void
        )
    {
        return ZE_RESULT_SUCCESS;
    }

}