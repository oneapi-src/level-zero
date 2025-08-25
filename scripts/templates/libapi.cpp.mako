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
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}.cpp
 *
 * @brief C++ static library for ${n}
 *
 */
#include "${x}_lib.h"
%if n == 'zer':
#include "error_state.h"
%endif

extern "C" {

%for s in specs:
## FUNCTION ###################################################################
%for obj in th.filter_items(s['objects'], 'type', 'function'):
<%
    ret_type = obj['return_type']
    failure_return = None
    if ret_type != 'ze_result_t':
        failure_return = th.get_first_failure_return(obj)
%>///////////////////////////////////////////////////////////////////////////////
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
${ret_type} ${X}_APICALL
${th.make_func_name(n, tags, obj)}(
    %for line in th.make_param_lines(n, tags, obj):
    ${line}
    %endfor
    )
{
%if re.match("Init", obj['name']):
%if re.match("zes", n):
    #ifdef L0_STATIC_LOADER_BUILD
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
    #ifdef L0_STATIC_LOADER_BUILD
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
    #ifdef L0_STATIC_LOADER_BUILD
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
    #ifdef L0_STATIC_LOADER_BUILD
    %if ret_type == 'ze_result_t':
    ze_result_t result = ${X}_RESULT_SUCCESS;
    %endif
    if(ze_lib::destruction) {
        %if ret_type == 'ze_result_t':
        return ${X}_RESULT_ERROR_UNINITIALIZED;
        %else:
        %if n == 'zer':
        error_state::setErrorDesc("ERROR UNINITIALIZED");
        %endif
        return ${failure_return};
        %endif
    }
%if re.match(r"\w+DriverGet$", th.make_func_name(n, tags, obj)):
    if (!${x}_lib::context || ${x}_lib::context->${n}DdiTable == nullptr) {
        return ${X}_RESULT_ERROR_UNINITIALIZED;
    }
%endif
    %if re.match(r"\w+GetLastErrorDescription", th.make_func_name(n, tags, obj)) and n == 'zer':
    error_state::getErrorDesc(ppString);
    if (ppString && *ppString && strlen(*ppString) > 0)
    {
        return ZE_RESULT_SUCCESS;
    }
    %endif
    %if ret_type == 'ze_result_t':
    static const ${th.make_pfn_type(n, tags, obj)} ${th.make_pfn_name(n, tags, obj)} = [&result] {
        auto ${th.make_pfn_name(n, tags, obj)} = ${x}_lib::context->${n}DdiTable.load()->${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)};
        if( nullptr == ${th.make_pfn_name(n, tags, obj)} ) {
            result = ${X}_RESULT_ERROR_UNSUPPORTED_FEATURE;
        }
        return ${th.make_pfn_name(n, tags, obj)};
    }();
    if (result != ${X}_RESULT_SUCCESS) {
        return result;
    }
    %else:
    static const ${th.make_pfn_type(n, tags, obj)} ${th.make_pfn_name(n, tags, obj)} = [] {
        auto ${th.make_pfn_name(n, tags, obj)} = ${x}_lib::context->${n}DdiTable.load()->${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)};
        return ${th.make_pfn_name(n, tags, obj)};
    }();
    if (nullptr == ${th.make_pfn_name(n, tags, obj)}) {
        %if n == 'zer':
        error_state::setErrorDesc("ERROR UNSUPPORTED FEATURE");
        %endif
        return ${failure_return};
    }    
    %endif
    return ${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );
    #else
    if(ze_lib::destruction) {
        %if ret_type == 'ze_result_t':
        return ${X}_RESULT_ERROR_UNINITIALIZED;
        %else:
        %if n == 'zer':
        error_state::setErrorDesc("ERROR UNINITIALIZED");
        %endif
        return ${failure_return};
        %endif
    }

%if re.match(r"\w+DriverGet$", th.make_func_name(n, tags, obj)):
    if (${x}_lib::context->${n}DdiTable == nullptr) {
        return ${X}_RESULT_ERROR_UNINITIALIZED;
    }

%endif
    %if re.match(r"\w+GetLastErrorDescription", th.make_func_name(n, tags, obj)) and n == 'zer':
    error_state::getErrorDesc(ppString);
    if (ppString && *ppString && strlen(*ppString) > 0)
    {
        return ZE_RESULT_SUCCESS;
    }
    %endif
    auto ${th.make_pfn_name(n, tags, obj)} = ${x}_lib::context->${n}DdiTable.load()->${th.get_table_name(n, tags, obj)}.${th.make_pfn_name(n, tags, obj)};
    if( nullptr == ${th.make_pfn_name(n, tags, obj)} ) {
        %if ret_type == 'ze_result_t':
        if(!ze_lib::context->isInitialized)
            return ${X}_RESULT_ERROR_UNINITIALIZED;
        else
            return ${X}_RESULT_ERROR_UNSUPPORTED_FEATURE;
        %elif ret_type != 'ze_result_t' and n == 'zer':
        if(!ze_lib::context->isInitialized)
            error_state::setErrorDesc("ERROR UNINITIALIZED");
        else
            error_state::setErrorDesc("ERROR UNSUPPORTED FEATURE");
        return ${failure_return};
        %else:
        return ${failure_return};
        %endif
    }
%if re.match(r"\w+DriverGet$", th.make_func_name(n, tags, obj)):
    ze_lib::context->${n}Inuse = true;
%endif

    return ${th.make_pfn_name(n, tags, obj)}( ${", ".join(th.make_param_lines(n, tags, obj, format=["name"]))} );
    #endif
}
%endif
%if 'condition' in obj:
#endif // ${th.subt(n, tags, obj['condition'])}
%endif

%endfor
%endfor
} // extern "C"
