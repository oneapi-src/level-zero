/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_object.h
 *
 */
#pragma once
#include "ze_singleton.h"
#include "ze_ddi_common.h"

//////////////////////////////////////////////////////////////////////////
struct dditable_t
{
    ze_dditable_t   ze;
    zet_dditable_t  zet;
    zes_dditable_t  zes;
    zer_dditable_t  zer;
};

namespace loader {

	extern ze_handle_t* loaderDispatch;

}

//////////////////////////////////////////////////////////////////////////
template<typename _handle_t>
class object_t
{
public:
    using handle_t = _handle_t;
    ze_dditable_driver_t *pCore;
    zet_dditable_driver_t *pTools;
    zes_dditable_driver_t *pSysman;
    zer_dditable_driver_t *pRuntime;
    handle_t    handle;
    dditable_t* dditable;

    object_t() = delete;

    object_t( handle_t _handle, dditable_t* _dditable )
        : handle( _handle ), dditable( _dditable )
    {
        pCore = loader::loaderDispatch->pCore;
        pTools = loader::loaderDispatch->pTools;
        pSysman = loader::loaderDispatch->pSysman;
        pRuntime = loader::loaderDispatch->pRuntime;
    }

    ~object_t() = default;
};
