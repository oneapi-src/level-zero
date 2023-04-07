"""
 Copyright (C) 2019-2021 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import os
import re
import util

templates_dir = os.path.join(os.path.dirname(os.path.realpath(__file__)), "templates")
tracing_templates_dir = os.path.join(templates_dir, "tracing")
validation_templates_dir = os.path.join(templates_dir, "validation")

"""
    generates c/c++ files from the specification documents
"""
def _mako_ddi_cpp(path, namespace, tags, version, specs, meta):
    template = "ddi.h.mako"
    fin = os.path.join(templates_dir, template)

    filename = "%s_ddi.h"%(namespace)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    return util.makoWrite(
        fin, fout,
        ver=version,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)

"""
    generates c/c++ files from the specification documents
"""
def _mako_lib_cpp(path, namespace, tags, version, specs, meta):
    loc = 0
    template = "libapi.cpp.mako"
    fin = os.path.join(templates_dir, template)

    name = "%s_libapi"%(namespace)
    filename = "%s.cpp"%(name)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        name = name,
        ver=version,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta = meta)

    template = "libddi.cpp.mako"
    fin = os.path.join(templates_dir, template)

    name = "%s_libddi"%(namespace)
    filename = "%s.cpp"%(name)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        name=name,
        ver=version,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)
    return loc

"""
    generates c/c++ files from the specification documents
"""
def _mako_wrapper_cpp(path, namespace, tags, version, specs, meta):
    loc = 0
    template = "wprapi.cpp.mako"
    fin = os.path.join(templates_dir, template)

    name = "%s_wprapi"%(namespace)
    filename = "%s.cpp"%(name)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        name = name,
        ver=version,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta = meta)
    return loc

"""
    generates c/c++ files from the specification documents
"""
def _mako_loader_cpp(path, namespace, tags, version, specs, meta):
    print("make_loader_cpp path %s namespace %s version %s\n" %(path, namespace, version))
    loc = 0
    template = "ldrddi.h.mako"
    fin = os.path.join(templates_dir, template)

    name = "%s_ldrddi"%(namespace)
    filename = "%s.h"%(name)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        name=name,
        ver=version,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)

    template = "ldrddi.cpp.mako"
    fin = os.path.join(templates_dir, template)

    name = "%s_ldrddi"%(namespace)
    filename = "%s.cpp"%(name)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        name=name,
        ver=version,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)
    return loc

"""
    generates c/c++ files from the specification documents
"""

# 'input_file_name' : (output_dir, output_filename)
validation_files = {
    'valddi.cpp.mako': ('','valddi.cpp'),
    'entry_points.h.mako' : ('common', 'entry_points.h'),
    'param.cpp.mako' : ('parameter_validation', 'parameter_validation.cpp'),
    'param.h.mako' : ('parameter_validation', 'parameter_validation.h'),
    'handle_lifetime.h.mako' : ('handle_lifetime_tracking', 'handle_lifetime.h'),
    'handle_lifetime.cpp.mako' : ('handle_lifetime_tracking', 'handle_lifetime.cpp')
}

def _mako_validation_layer_cpp(path, namespace, tags, version, specs, meta):
    loc = 0
    
    for input_file in validation_files:
        dstpath = os.path.join(path, "validation")
        os.makedirs(dstpath, exist_ok=True)

        template = input_file
        fin = os.path.join(validation_templates_dir, template)

        filename = "%s_%s"%(namespace, validation_files[input_file][1])
        dstpath = os.path.join(dstpath, validation_files[input_file][0])
        fout = os.path.join(dstpath, filename)

        print("Generating %s..."%fout)
        loc += util.makoWrite(
            fin, fout,
            name=filename,
            ver=version,
            namespace=namespace,
            tags=tags,
            specs=specs,
            meta=meta)

    return loc


"""
    generates c/c++ files from the specification documents
"""
def _mako_tracing_layer_h(path, namespace, tags, version, specs, meta):
    dstpath = os.path.join(path, "layers")
    os.makedirs(dstpath, exist_ok=True)

    template = "trc_setters.h.mako"
    fin = os.path.join(tracing_templates_dir, template)

    name = "zel_tracing_register_cb"
    filename = "%s.h"%(name)
    fout = os.path.join(dstpath, filename)

    print("Generating %s..."%fout)
    return util.makoWrite(
        fin, fout,
        name=name,
        ver=version,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)


"""
    generates c/c++ files from the specification documents
"""
def _mako_tracing_layer_cpp(path, namespace, tags, version, specs, meta):
    dstpath = os.path.join(path, "tracing")
    os.makedirs(dstpath, exist_ok=True)

    template = "trcddi.cpp.mako"
    fin = os.path.join(tracing_templates_dir, template)

    name = "%s_trcddi"%(namespace)
    filename = "%s.cpp"%(name)
    fout = os.path.join(dstpath, filename)

    print("Generating %s..."%fout)
    loc = util.makoWrite(
        fin, fout,
        name=name,
        ver=version,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)

    template = "trc_setters.cpp.mako"
    fin = os.path.join(tracing_templates_dir, template)

    name = "ze_tracing_register_cb"
    filename = "%s.cpp"%(name)
    fout = os.path.join(dstpath, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        name=name,
        ver=version,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)

    template = "trc_cb_struct.h.mako"
    fin = os.path.join(tracing_templates_dir, template)

    name = "ze_tracing_cb_structs"
    filename = "%s.h"%(name)
    fout = os.path.join(dstpath, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        name=name,
        ver=version,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)

    return loc

"""
    generates c/c++ files from the specification documents
"""
def _mako_tracing_lib_cpp(path, namespace, tags, version, specs, meta):
    dstpath = os.path.join(path, "lib")
    os.makedirs(dstpath, exist_ok=True)

    template = "trc_register_cb_libapi.cpp.mako"
    fin = os.path.join(tracing_templates_dir, template)

    name = "ze_tracing_register_cb_libapi"
    filename = "%s.cpp"%(name)
    fout = os.path.join(dstpath, filename)

    print("Generating %s..."%fout)
    return util.makoWrite(
        fin, fout,
        name=name,
        ver=version,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)

"""
    generates c/c++ files from the specification documents
"""
def _mako_null_driver_cpp(path, namespace, tags, version, specs, meta):
    dstpath = os.path.join(path, "null")
    os.makedirs(dstpath, exist_ok=True)

    template = "nullddi.cpp.mako"
    fin = os.path.join(templates_dir, template)

    name = "%s_nullddi"%(namespace)
    filename = "%s.cpp"%(name)
    fout = os.path.join(dstpath, filename)

    print("Generating %s..."%fout)
    return util.makoWrite(
        fin, fout,
        name=name,
        ver=version,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)

"""
Entry-point:
    generates lib code
"""
def generate_lib(path, section, namespace, tags, version, specs, meta):
    dstpath = os.path.join(path, "lib")
    os.makedirs(dstpath, exist_ok=True)

    loc = 0
    loc += _mako_lib_cpp(dstpath, namespace, tags, version, specs, meta)
    print("Generated %s lines of code.\n"%loc)

"""
Entry-point:
    generates loader for level_zero driver
"""
def generate_loader(path, section, namespace, tags, version, specs, meta):
    dstpath = os.path.join(path, "loader")
    os.makedirs(dstpath, exist_ok=True)

    loc = 0
    loc += _mako_loader_cpp(dstpath, namespace, tags, version, specs, meta)
    print("Generated %s lines of code.\n"%loc)

"""
Entry-point:
    generates layers for level_zero driver
"""
def generate_layers(path, section, namespace, tags, version, specs, meta):
    print("GL section %s\n"%section)
    print("GL namespace %s\n"%namespace)
    layer_dstpath = os.path.join(path, "layers")
    include_dstpath = os.path.join(path, "../include")
    os.makedirs(layer_dstpath, exist_ok=True)
    os.makedirs(include_dstpath, exist_ok=True)

    loc = 0
    loc += _mako_validation_layer_cpp(layer_dstpath, namespace, tags, version, specs, meta)
    print("VALIDATION Generated %s lines of code.\n"%loc)
    if section == "core":
        loc += _mako_tracing_layer_cpp(layer_dstpath, namespace, tags, version, specs, meta)
        print("TRACING Generated %s lines of code.\n"%loc)
        loc += _mako_tracing_lib_cpp(path, namespace, tags, version, specs, meta)
        print("TRACING Generated %s lines of code.\n"%loc)       
        loc += _mako_tracing_layer_h(include_dstpath, namespace, tags, version, specs, meta)
        print("TRACING header Generated %s lines of code.\n"%loc)

"""
Entry-point:
    generates drivers for level_zero driver
"""
def generate_drivers(path, section, namespace, tags, version, specs, meta):
    dstpath = os.path.join(path, "drivers")
    os.makedirs(dstpath, exist_ok=True)

    loc = 0
    loc += _mako_null_driver_cpp(dstpath, namespace, tags, version, specs, meta)
    print("Generated %s lines of code.\n"%loc)
