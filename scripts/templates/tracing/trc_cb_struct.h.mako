<%
import re
from templates import helper as th
%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
    X=x.upper()
%>/*
 *
 * Copyright (C) 2021-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}.h
 *
 */
#ifndef ${name}_H
#define ${name}_H
#if defined(__cplusplus)
#pragma once
#endif

#include "${x}_api.h"
#include "layers/zel_tracing_register_cb.h"



%for tbl in th.get_zel_pfncbtables(specs, meta, n, tags):
///////////////////////////////////////////////////////////////////////////////
/// @brief Table of ${tbl['name']} callback functions pointers
typedef struct _${tbl['type']}
{
    %for obj in tbl['functions']:
    ${th.append_ws(th.make_pfncb_type(n, tags, obj), 63)} ${th.make_pfncb_name(n, tags, obj)};
    %endfor
} ${tbl['type']};

%endfor
///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all callbacks
typedef struct _zel_all_core_callbacks_t
{
%for tbl in th.get_zel_pfncbtables(specs, meta, n, tags):
    ${th.append_ws(tbl['type'], 35)} ${tbl['name']};
%endfor
} zel_all_core_callbacks_t;



#endif // ${name}_H
