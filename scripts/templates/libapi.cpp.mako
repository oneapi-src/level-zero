<%!
import re
from templates import helper as th

def define_dbg(obj, tags):
    if re.match("class", obj['type']):
        return True
    if 'class' not in obj or obj['class'] in tags:
        return re.match("enum", obj['type']) or re.match("struct|union", obj['type'])
    return False

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
 * @brief C++ static library for ${n}
 *
 */
#include "${x}_lib.h"

extern "C" {

%for s in specs:
## FUNCTION ###################################################################
%for obj in th.filter_items(s['objects'], 'type', 'function'):
///////////////////////////////////////////////////////////////////////////////
%if 'condition' in obj:
#if ${th.subt(n, tags, obj['condition'])}
%endif
%for line in th.make_desc_lines(n, tags, obj):
/// ${line}
%endfor
%for line in th.make_details_lines(n, tags, obj):
/// ${line}
%endfor
/// 
%for line in th.make_returns_lines(n, tags, obj, meta=meta):
/// ${line}
%endfor
${x}_result_t ${X}_APICALL
${th.make_func_name(n, tags, obj)}(
    %for line in th.make_param_lines(n, tags, obj):
    ${line}
    %endfor
    )
{
%if re.match("Init", obj['name']):
%if re.match("zes", n):
    #ifdef DYNAMIC_LOAD_LOADER
    if (!${x}_lib::context) {
        ${x}_lib::context = new ${x}_lib::context_t;
    }
    #endif
    static ${x}_result_t result = ${X}_RESULT_SUCCESS;
    std::call_once(${x}_lib::context->initOnceSysMan, [flags]() {
        result = ${x}_lib::context->Init(flags, true, nullptr);

    });

    if( ${X}_RESULT_SUCCESS != result )
        return result;

    if(ze_lib::destruction) {
        return ${X}_RESULT_ERROR_UNINITIALIZED;
    }

    auto ${th.make_pfn_name(n, tags, obj)} = ${x}_lib::context->${n}DdiTable.load()->${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)};
    if( nullptr == ${th.make_pfn_name(n, tags, obj)} ) {
        if(!ze_lib::context->isInitialized)
            return ${X}_RESULT_ERROR_UNINITIALIZED;
        else
            return ${X}_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    return ${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );
}
%else:
%if re.match("InitDrivers", obj['name']):
    ${x}_result_t result = ${X}_RESULT_SUCCESS;
    #ifdef DYNAMIC_LOAD_LOADER
    if (!${x}_lib::context) {
        ${x}_lib::context = new ${x}_lib::context_t;
    }
    #endif
    std::call_once(${x}_lib::context->initOnceDrivers, [desc,&result]() {
        result = ${x}_lib::context->Init(0, false, desc);
        return result;
    });

    if (result != ${X}_RESULT_SUCCESS) {
        return result;
    }

    if(ze_lib::destruction) {
        return ${X}_RESULT_ERROR_UNINITIALIZED;
    }

    auto ${th.make_pfn_name(n, tags, obj)} = ${x}_lib::context->${n}DdiTable.load()->${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)};
    if( nullptr == ${th.make_pfn_name(n, tags, obj)} ) {
        if(!ze_lib::context->isInitialized)
            return ${X}_RESULT_ERROR_UNINITIALIZED;
        else
            return ${X}_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }

    result = ${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );

    if (result == ${X}_RESULT_SUCCESS) {
        if (phDrivers) {
            ze_lib::context->${n}Inuse = true;
        }
    }

    return result;
%else:
    static ${x}_result_t result = ${X}_RESULT_SUCCESS;
    #ifdef DYNAMIC_LOAD_LOADER
    if (!${x}_lib::context) {
        ${x}_lib::context = new ${x}_lib::context_t;
    }
    #endif
    std::call_once(${x}_lib::context->initOnce, [flags]() {
        result = ${x}_lib::context->Init(flags, false, nullptr);

        if( ${X}_RESULT_SUCCESS != result )
            return result;

        if(ze_lib::destruction) {
            return ${X}_RESULT_ERROR_UNINITIALIZED;
        }

        auto ${th.make_pfn_name(n, tags, obj)} = ${x}_lib::context->${n}DdiTable.load()->${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)};
        if( nullptr == ${th.make_pfn_name(n, tags, obj)} ) {
            if(!ze_lib::context->isInitialized)
                return ${X}_RESULT_ERROR_UNINITIALIZED;
            else
                return ${X}_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }

        result = ${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );
        return result;
    });

    if(ze_lib::destruction) {
        result = ${X}_RESULT_ERROR_UNINITIALIZED;
    }

    return result;
%endif
}
%endif
%else:
    if(ze_lib::destruction) {
        return ${X}_RESULT_ERROR_UNINITIALIZED;
    }

%if re.match(r"\w+DriverGet$", th.make_func_name(n, tags, obj)):
    if (${x}_lib::context->${n}DdiTable == nullptr) {
        return ${X}_RESULT_ERROR_UNINITIALIZED;
    }

%endif
    auto ${th.make_pfn_name(n, tags, obj)} = ${x}_lib::context->${n}DdiTable.load()->${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)};
    if( nullptr == ${th.make_pfn_name(n, tags, obj)} ) {
        if(!ze_lib::context->isInitialized)
            return ${X}_RESULT_ERROR_UNINITIALIZED;
        else
            return ${X}_RESULT_ERROR_UNSUPPORTED_FEATURE;
    }
%if re.match(r"\w+DriverGet$", th.make_func_name(n, tags, obj)):
    ze_lib::context->${n}Inuse = true;
%endif

    return ${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );
}
%endif
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif

%endfor
%endfor
} // extern "C"
