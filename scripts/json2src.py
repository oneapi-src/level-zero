#! /usr/bin/env python3
"""
 Copyright (C) 2019-2025 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import argparse
import util
import generate_code
import os, sys
import time
import json
import re

"""
    helper for adding mutually-exclusive boolean arguments "--name" and "--skip-name"
"""
def add_argument(parser, name, help, default=False):
    group = parser.add_mutually_exclusive_group(required=False)
    group.add_argument("--" + name, dest=name, help="Enable "+help, action="store_true")
    group.add_argument("--skip-" + name, dest=name, help="Skip "+help, action="store_false")
    parser.set_defaults(**{name:default})

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    add_argument(parser, "lib", "generation of lib files.", True)
    add_argument(parser, "loader", "generation of loader files.", True)
    add_argument(parser, "layers", "generation of validation layer files.", True)
    add_argument(parser, "drivers", "generation of null driver files.", True)
    parser.add_argument("--debug", action='store_true', help="dump intermediate data to disk.")
    parser.add_argument("--sections", type=list, default=None, help="Optional list of sections for which to generate source, default is all")
    parser.add_argument("--ver", type=str, default="1.0", help="specification version to generate.")
    parser.add_argument('--api-json', nargs='?', type=argparse.FileType('r'), default=sys.stdin, help="JSON file containing the API specification, by default read from stdin")
    parser.add_argument("out_dir", type=str, help="Root of the loader repository.")
    args = parser.parse_args()

    input = json.loads(args.api_json.read())

    start = time.time()

    srcpath = os.path.join(args.out_dir, "source")

    for idx, specs in enumerate(input['specs']):
        config = input['configs'][idx]
        if args.sections == None or config['name'] in args.sections:
            if args.lib:
                generate_code.generate_lib(srcpath, config['name'], config['namespace'], config['tags'], args.ver, specs, input['meta'])
            if args.loader:
                generate_code.generate_loader(srcpath, config['name'], config['namespace'], config['tags'], args.ver, specs, input['meta'])
            if args.layers:
                generate_code.generate_layers(srcpath, config['name'], config['namespace'], config['tags'], args.ver, specs, input['meta'])
            if args.drivers:
                generate_code.generate_drivers(srcpath, config['name'], config['namespace'], config['tags'], args.ver, specs, input['meta'])

    def merge_header_files(input_files, output_file):
        """
        Merges the unique content of multiple header files into a single output file.

        Args:
            input_files: A list of paths to the input header files.
            output_file: The path to the output file.
        """
        try:
            unique_lines = set()
            for infile_path in input_files:
                try:
                    with open(infile_path, 'r') as infile:
                        inside_factory = False
                        for line in infile:
                            if '/// factories' in line:
                                inside_factory = True
                                continue
                            if '/// end factories' in line:
                                inside_factory = False
                                continue
                            if inside_factory:
                                unique_lines.add(line)
                except FileNotFoundError:
                    print(f"Error: Input file not found: {infile_path}")
                    return

            with open(output_file, 'w') as outfile:
                for line in sorted(unique_lines):
                    outfile.write(line)
            print(f"Successfully merged unique header file content into: {output_file}")
        except Exception as e:
            print(f"An error occurred: {e}")

    header_files = [
        'source/loader/ze_loader_internal_tmp.h',
        'source/loader/zet_loader_internal_tmp.h',
        'source/loader/zes_loader_internal_tmp.h',
        'source/loader/zer_loader_internal_tmp.h'
    ]
    output_file = 'source/loader/ze_loader_internal_factories.h'
    merge_header_files(header_files, output_file)
    def replace_factory_section(input_file, factory_file, output_file):
        """
        Replaces the content between '/// factory' and '/// end factory' in the input file
        with the content from the factory file and writes the result to the output file.

        Args:
            input_file: The path to the input file.
            factory_file: The path to the factory file.
            output_file: The path to the output file.
        """
        try:
            with open(input_file, 'r') as infile:
                lines = infile.readlines()

            with open(factory_file, 'r') as factory:
                factory_lines = factory.readlines()

            output_lines = []
            inside_factory = False

            for line in lines:
                if '/// factories' in line:
                    inside_factory = True
                    output_lines.append(line)
                    output_lines.extend(factory_lines)
                elif '/// end factories' in line:
                    inside_factory = False
                if not inside_factory:
                    output_lines.append(line)

            with open(output_file, 'w') as outfile:
                outfile.writelines(output_lines)

            print(f"Successfully replaced factory section in: {output_file}")
        except Exception as e:
            print(f"An error occurred: {e}")

    input_file = 'source/loader/ze_loader_internal_tmp.h'
    factory_file = 'source/loader/ze_loader_internal_factories.h'
    output_file = 'source/loader/ze_loader_internal.h'
    replace_factory_section(input_file, factory_file, output_file)

    def region_start_regex(name):
        # Matches:
        #   #if !defined(__GNUC__)
        #   #pragma region <name>
        #   #endif
        return re.compile(
            rf'(?m)^\s*#if\s*!defined\(__GNUC__\)\s*\r?\n'
            rf'^\s*#pragma\s+region\s+{re.escape(name)}\s*\r?\n'
            rf'^\s*#endif\s*'
        )

    def region_end_regex():
        # Matches:
        #   #if !defined(__GNUC__)
        #   #pragma endregion
        #   #endif
        return re.compile(
            r'(?m)^\s*#if\s*!defined\(__GNUC__\)\s*\r?\n'
            r'^\s*#pragma\s+endregion\s*\r?\n'
            r'^\s*#endif\s*'
        )

    def find_region_span(text, name):
        """
        Return (region_body_start, region_body_end) character indices for region <name>.
        region_body_start: after region opening marker
        region_body_end: start of region closing marker
        """
        open_m = region_start_regex(name).search(text)
        if not open_m:
            return None
        close_m = region_end_regex().search(text, open_m.end())
        if not close_m:
            return None
        return (open_m.end(), close_m.start())

    def extract_region_body(text, name):
        region_span = find_region_span(text, name)
        if not region_span:
            return ""
        region_body_start, region_body_end = region_span
        return text[region_body_start:region_body_end]

    def replace_region_body(text, name, new_body):
        region_span = find_region_span(text, name)
        if not region_span:
            return text
        region_body_start, region_body_end = region_span
        # Keep opening and closing markers exactly as-is; replace only body.
        return text[:region_body_start] + new_body + text[region_body_end:]

    # Merge ze/zer tracing tmp headers into a single final header
    ze_tracing_tmp = os.path.join(args.out_dir, 'include', 'layers', 'ze_tracing_register_cb_tmp.h')
    zer_tracing_tmp = os.path.join(args.out_dir, 'include', 'layers', 'zer_tracing_register_cb_tmp.h')
    final_tracing_hdr = os.path.join(args.out_dir, 'include', 'layers', 'zel_tracing_register_cb.h')

    if os.path.exists(ze_tracing_tmp):
        with open(ze_tracing_tmp, 'r') as f: ze_txt = f.read()
        zer_txt = ""
        if os.path.exists(zer_tracing_tmp):
            with open(zer_tracing_tmp, 'r') as f: zer_txt = f.read()
        else:
            print("zer_tracing_register_cb_tmp.h not found!")

        # Merge region bodies in order (ze then zer)
        callbacks_body = extract_region_body(ze_txt, 'callbacks') + "\n" + extract_region_body(zer_txt, 'callbacks')
        reg_callbacks_body = extract_region_body(ze_txt, 'register_callbacks') + "\n" + extract_region_body(zer_txt, 'register_callbacks')

        # Replace in base (ze) while preserving wrappers
        merged = replace_region_body(ze_txt, 'callbacks', callbacks_body)
        merged = replace_region_body(merged, 'register_callbacks', reg_callbacks_body)

        os.makedirs(os.path.dirname(final_tracing_hdr), exist_ok=True)
        with open(final_tracing_hdr, 'w') as f: f.write(merged)

        print(f"Successfully merged tracing header contents in: {final_tracing_hdr}")
    else:
        print("ze_tracing_register_cb_tmp.h not found!")

    # Delete temporary and factory files
    files_to_delete = [
        'source/loader/ze_loader_internal_tmp.h',
        'source/loader/zet_loader_internal_tmp.h',
        'source/loader/zes_loader_internal_tmp.h',
        'source/loader/zer_loader_internal_tmp.h',
        'source/loader/ze_loader_internal_factories.h',
        'include/layers/ze_tracing_register_cb_tmp.h',
        'include/layers/zer_tracing_register_cb_tmp.h'
    ]

    for file_path in files_to_delete:
        try:
            os.remove(file_path)
            print(f"Deleted file: {file_path}")
        except FileNotFoundError:
            print(f"File not found, could not delete: {file_path}")
        except Exception as e:
            print(f"An error occurred while deleting {file_path}: {e}")

    if args.debug:
        util.makoFileListWrite("generated.json")

    print("\nCompleted in %.1f seconds!"%(time.time() - start))
