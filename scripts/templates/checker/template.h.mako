/*
 *
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zel_${name}_checker.h
 *
 */

#pragma once 

#include <string>
#include "ze_api.h"
#include "ze_validation_layer.h"

namespace validation_layer
{
    class __zedlllocal ${name}Checker : public validationChecker{
        public:
            ${name}Checker();
            ~${name}Checker();

            class ZE${name}Checker : public ZEValidationEntryPoints {};
            class ZES${name}Checker : public ZESValidationEntryPoints {};
            class ZET${name}Checker : public ZETValidationEntryPoints {};
        bool enable${name} = false;
    };
    extern class ${name}Checker ${name}_checker;
}