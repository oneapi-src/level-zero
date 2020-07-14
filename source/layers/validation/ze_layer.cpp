/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_layer.cpp
 *
 */
#include "ze_layer.h"

namespace layer
{
    context_t context;

    ///////////////////////////////////////////////////////////////////////////////
    context_t::context_t()
    {
        enableParameterValidation = getenv_tobool( "ZE_ENABLE_PARAMETER_VALIDATION" );
        enableHandleLifetime = getenv_tobool( "ZE_ENABLE_HANDLE_LIFETIME" );
        enableMemoryTracker = getenv_tobool( "ZE_ENABLE_MEMORY_TRACKER" );
        enableThreadingValidation = getenv_tobool( "ZE_ENABLE_THREADING_VALIDATION" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    context_t::~context_t()
    {
    }
}
