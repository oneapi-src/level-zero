/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#pragma once
#include "ze_singleton.h"

//////////////////////////////////////////////////////////////////////////
struct dditable_t
{
    ze_dditable_t   ze;
    zet_dditable_t  zet;
};

//////////////////////////////////////////////////////////////////////////
template<typename _handle_t>
class object_t
{
public:
    using handle_t = _handle_t;

    handle_t    handle;
    dditable_t* dditable;

    object_t() = delete;

    object_t( handle_t _handle, dditable_t* _dditable )
        : handle( _handle ), dditable( _dditable )
    {
    }

    ~object_t() = default;
};
