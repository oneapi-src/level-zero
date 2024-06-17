/*
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_${name}_checker.cpp
 *
 */
#include "zel_${name}_checker.h"

namespace validation_layer
{
    class ${name}Checker ${name}_checker;

    ${name}Checker::${name}Checker() {
        enable${name} = getenv_tobool( "ZEL_ENABLE_${env_name}_CHECKER" );
        if(enable${name}) {
            ${name}Checker::ZE${name}Checker *zeChecker = new ${name}Checker::ZE${name}Checker;
            ${name}Checker::ZES${name}Checker *zesChecker = new ${name}Checker::ZES${name}Checker;
            ${name}Checker::ZET${name}Checker *zetChecker = new ${name}Checker::ZET${name}Checker;
            ${name}_checker.zeValidation = zeChecker;
            ${name}_checker.zetValidation = zetChecker;
            ${name}_checker.zesValidation = zesChecker;
            validation_layer::context.validationHandlers.push_back(&${name}_checker);
        }
    }

    ${name}Checker::~${name}Checker() {
        if(enable${name}) {
            delete ${name}_checker.zeValidation;
            delete ${name}_checker.zetValidation;
            delete ${name}_checker.zesValidation;
        }
    }
}