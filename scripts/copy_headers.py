#! /usr/bin/env python3
"""
 Copyright (C) 2025 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import argparse
import glob
import os
import shutil
import time

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("out_dir", type=str, help="Root of the loader repository.")
    args = parser.parse_args()

    start = time.time()

    incpath = os.path.join(args.out_dir, "include")
    extra_incpath = os.path.join(incpath, "level_zero")

    def ignore(thedir, contents):
        if thedir == incpath:
            return ["level_zero"]
        return []

    shutil.copytree(incpath, extra_incpath, ignore=ignore, dirs_exist_ok=True)
    print("\nCompleted in %.1f seconds!"%(time.time() - start))
