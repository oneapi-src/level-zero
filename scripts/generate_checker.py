"""
 Copyright (C) 2024 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import os
import re
import util
import argparse

templates_dir = os.path.join(os.path.dirname(os.path.realpath(__file__)), "templates/checker/")

"""
    generates checker files from the templates
"""
if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("name", type=str, help="Name of your Validation Layer checker in the form of 'CheckerName'.")
    parser.add_argument("out_dir", type=str, help="Root of the loader repository.")
    args = parser.parse_args()
    name = args.name
    env_name = name.upper()
    srcpath = os.path.join(args.out_dir, "source/layers/validation/checkers/")
    srcpath = os.path.join(srcpath, name)
    if not os.path.exists(srcpath):
        os.makedirs(srcpath)
    print("Generating Checker Template for %s\n" %(name))
    loc = 0
    template = "template.h.mako"
    fin = os.path.join(templates_dir, template)

    filename = "zel_%s_checker.h"%(name)
    fout = os.path.join(srcpath, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        name=name)

    template = "template.cpp.mako"
    fin = os.path.join(templates_dir, template)

    filename = "zel_%s_checker.cpp"%(name)
    fout = os.path.join(srcpath, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        name=name,
        env_name=env_name)

    template = "template.cmake.mako"
    fin = os.path.join(templates_dir, template)

    filename = "CMakeLists.txt"
    fout = os.path.join(srcpath, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        name=name,
        TARGET_NAME="${TARGET_NAME}",
        CMAKE_CURRENT_LIST_DIR="${CMAKE_CURRENT_LIST_DIR}")