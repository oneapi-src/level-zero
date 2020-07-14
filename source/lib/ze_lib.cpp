/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_lib.cpp
 *
 */
#include "ze_lib.h"

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    context_t context;


    ///////////////////////////////////////////////////////////////////////////////
    context_t::context_t()
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    context_t::~context_t()
    {
        FREE_DRIVER_LIBRARY( loader );
    };

    //////////////////////////////////////////////////////////////////////////
    __zedlllocal ze_result_t context_t::Init()
    {
        loader = LOAD_DRIVER_LIBRARY( MAKE_LIBRARY_NAME( "ze_loader", L0_LOADER_VERSION) );

        if( NULL == loader )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        ze_result_t result = ZE_RESULT_SUCCESS;

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zeInit();
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zetInit();
        }

        if( ZE_RESULT_SUCCESS == result )
        {
            result = zesInit();
        } 

        return result;
    }

} // namespace ze_lib
