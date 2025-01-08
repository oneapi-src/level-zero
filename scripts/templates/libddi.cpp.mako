<%!
import re
from templates import helper as th
%><%
    n=namespace
    N=n.upper()

    x=tags['$x']
    X=x.upper()
%>/*
 *
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}.cpp
 *
 */
#include "${x}_lib.h"
#ifndef DYNAMIC_LOAD_LOADER
#include "${n}_ddi.h"
#endif

namespace ${x}_lib
{
    ///////////////////////////////////////////////////////////////////////////////

#ifdef DYNAMIC_LOAD_LOADER
    __zedlllocal ${x}_result_t context_t::${n}DdiTableInit()
    {
        ${x}_result_t result = ${X}_RESULT_SUCCESS;

    %for tbl in th.get_pfntables(specs, meta, n, tags):
        if( ${X}_RESULT_SUCCESS == result )
        {
    %if tbl['optional'] == True:
            // Optional
            auto getTable = reinterpret_cast<${tbl['pfn']}>(
                GET_FUNCTION_PTR(loader, "${tbl['export']['name']}") );
            getTable( ${X}_API_VERSION_CURRENT, &initial${n}DdiTable.${tbl['name']} );
    %else:
            auto getTable = reinterpret_cast<${tbl['pfn']}>(
                GET_FUNCTION_PTR(loader, "${tbl['export']['name']}") );
            result = getTable( ${X}_API_VERSION_CURRENT, &initial${n}DdiTable.${tbl['name']} );
    %endif
        }

    %endfor
        return result;
    }
#else
    __zedlllocal ${x}_result_t context_t::${n}DdiTableInit()
    {
        ${x}_result_t result = ${X}_RESULT_SUCCESS;

    %for tbl in th.get_pfntables(specs, meta, n, tags):
        if( ${X}_RESULT_SUCCESS == result )
        {
            %if tbl['optional'] == True:
            // Optional
            ${tbl['export']['name']}( ${X}_API_VERSION_CURRENT, &initial${n}DdiTable.${tbl['name']} );
            %else:
            result = ${tbl['export']['name']}( ${X}_API_VERSION_CURRENT, &initial${n}DdiTable.${tbl['name']} );
            %endif
        }

    %endfor
        return result;
    }
#endif

} // namespace ${x}_lib
