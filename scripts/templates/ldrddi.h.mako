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
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ${name}.h
 *
 */
#pragma once

namespace loader
{
    ///////////////////////////////////////////////////////////////////////////////
    // Forward declaration for driver_t so this header can reference loader::driver_t*
    // without requiring inclusion of ze_loader_internal.h (which includes this file).
    struct driver_t;
    ///////////////////////////////////////////////////////////////////////////////
    %for obj in th.extract_objs(specs, r"handle"):
    %if 'class' in obj:
    <%
        _handle_t = th.subt(n, tags, obj['name'])
        _object_t = re.sub(r"(\w+)_handle_t", r"\1_object_t", _handle_t)
        _factory_t = re.sub(r"(\w+)_handle_t", r"\1_factory_t", _handle_t)
    %>using ${th.append_ws(_object_t, 35)} = object_t < ${_handle_t} >;
    using ${th.append_ws(_factory_t, 35)} = singleton_factory_t < ${_object_t}, ${_handle_t} >;

    %endif
    %endfor
    __${x}dlllocal ze_result_t ${X}_APICALL
    ${n}loaderInitDriverDDITables(loader::driver_t *driver);
}

namespace loader_driver_ddi
{
    __${x}dlllocal void ${X}_APICALL
    ${n}DestroyDDiDriverTables(${n}_dditable_driver_t* pDdiTable);
    %for obj in th.extract_objs(specs, r"function"):
    %if not (re.match(r"Init", obj['name']) or re.match(r"\w+InitDrivers$", th.make_func_name(n, tags, obj)) or re.match(r"\w+DriverGet$", th.make_func_name(n, tags, obj))):
    __${x}dlllocal ${obj['return_type']} ${X}_APICALL
    ${th.make_func_name(n, tags, obj)}(
        %for line in th.make_param_lines(n, tags, obj):
        ${line}
        %endfor
        );
    %endif
    %endfor
}

#if defined(__cplusplus)
extern "C" {
#endif

%for tbl in th.get_pfntables(specs, meta, n, tags):
__${x}dlllocal void ${X}_APICALL
${tbl['export']['name']}Legacy();
__${x}dlllocal ze_result_t ${X}_APICALL
${tbl['export']['name']}FromDriver(loader::driver_t *driver);
%endfor

#if defined(__cplusplus)
};
#endif
