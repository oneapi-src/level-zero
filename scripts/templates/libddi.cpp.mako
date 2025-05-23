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
#ifndef L0_STATIC_LOADER_BUILD
#include "${n}_ddi.h"
#endif

namespace ${x}_lib
{
    ///////////////////////////////////////////////////////////////////////////////

#ifdef L0_STATIC_LOADER_BUILD
    __zedlllocal ${x}_result_t context_t::${n}DdiTableInit(ze_api_version_t version)
    {
        ${x}_result_t result = ${X}_RESULT_SUCCESS;

    %for tbl in th.get_pfntables(specs, meta, n, tags):
        if( ${X}_RESULT_SUCCESS == result )
        {
    %if tbl['optional'] == True:
            // Optional
            auto getTable = reinterpret_cast<${tbl['pfn']}>(
                GET_FUNCTION_PTR(loader, "${tbl['export']['name']}") );
            getTableWithCheck(getTable, version, &initial${n}DdiTable.${tbl['name']} );
    %else:
            auto getTable = reinterpret_cast<${tbl['pfn']}>(
                GET_FUNCTION_PTR(loader, "${tbl['export']['name']}") );
            result = getTableWithCheck(getTable, version, &initial${n}DdiTable.${tbl['name']} );
    %endif
            %for obj in tbl['functions']:
            initial${n}DdiTable.${tbl['name']}.${th.make_pfn_name(n, tags, obj)} = reinterpret_cast<${th.make_pfn_type(n, tags, obj)}>(
                GET_FUNCTION_PTR(loader, "${th.make_func_name(n, tags, obj)}") );
            %endfor
        }

    %endfor
        return result;
    }
#else
    __zedlllocal ${x}_result_t context_t::${n}DdiTableInit(ze_api_version_t version)
    {
        ${x}_result_t result = ${X}_RESULT_SUCCESS;

    %for tbl in th.get_pfntables(specs, meta, n, tags):
        if( ${X}_RESULT_SUCCESS == result )
        {
            %if tbl['optional'] == True:
            // Optional
            ${tbl['export']['name']}( version, &initial${n}DdiTable.${tbl['name']} );
            %else:
            result = ${tbl['export']['name']}( version, &initial${n}DdiTable.${tbl['name']} );
            %endif
        }

    %endfor
        return result;
    }
#endif

} // namespace ${x}_lib
