/*
 * Copyright (C) 2024-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_template_checker.cpp
 *
 */
#include "zel_template_checker.h"

namespace validation_layer
{
    class validationCheckerTemplate templateChecker;

    validationCheckerTemplate::validationCheckerTemplate() {
        enableValidationCheckerTemplate = getenv_tobool( "ZEL_ENABLE_VALIDATION_CHECKER_TEMPLATE" );
        if(enableValidationCheckerTemplate) {
            validationCheckerTemplate::ZEvalidationCheckerTemplate *zeChecker = new validationCheckerTemplate::ZEvalidationCheckerTemplate;
            validationCheckerTemplate::ZESvalidationCheckerTemplate *zesChecker = new validationCheckerTemplate::ZESvalidationCheckerTemplate;
            validationCheckerTemplate::ZETvalidationCheckerTemplate *zetChecker = new validationCheckerTemplate::ZETvalidationCheckerTemplate;
            validationCheckerTemplate::ZERvalidationCheckerTemplate *zerChecker = new validationCheckerTemplate::ZERvalidationCheckerTemplate;
            templateChecker.zeValidation = zeChecker;
            templateChecker.zetValidation = zetChecker;
            templateChecker.zesValidation = zesChecker;
            templateChecker.zerValidation = zerChecker;
            validation_layer::context.getInstance().validationHandlers.push_back(&templateChecker);
        }
    }

    validationCheckerTemplate::~validationCheckerTemplate() {
        if(enableValidationCheckerTemplate) {
            delete templateChecker.zeValidation;
            delete templateChecker.zetValidation;
            delete templateChecker.zesValidation;
            delete templateChecker.zerValidation;
        }
    }

    ze_result_t
    validationCheckerTemplate::ZEvalidationCheckerTemplate::zeInitPrologue(
        ze_init_flags_t flags)
    {
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t
    validationCheckerTemplate::ZESvalidationCheckerTemplate::zesInitPrologue(
        zes_init_flags_t flags)
    {
        return ZE_RESULT_SUCCESS;
    }

    ze_result_t
    validationCheckerTemplate::ZETvalidationCheckerTemplate::zetModuleGetDebugInfoPrologue(
        zet_module_handle_t hModule,
        zet_module_debug_info_format_t format,
        size_t* pSize,
        uint8_t* pDebugInfo
        )
    {
        return ZE_RESULT_SUCCESS;
    }

}