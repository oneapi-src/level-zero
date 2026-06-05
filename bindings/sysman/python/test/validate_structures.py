#!/usr/bin/env python3
##
# Copyright (C) 2026 Intel Corporation
#
# SPDX-License-Identifier: MIT
#
##

"""
Validates that Python ctypes structures in pyzes.py match the C structures
defined in the Level-Zero headers (include/zes_api.h, include/ze_api.h).
"""

import re
import sys
from pathlib import Path
from typing import List, Optional, Tuple

# Type mapping from C to Python ctypes
C_TO_PYTHON_TYPE_MAP = {
    # Structure types
    "ze_structure_type_t": "c_int32",
    "zes_structure_type_t": "c_int32",
    # Pointer types
    "void*": "c_void_p",
    "const void*": "c_void_p",
    # Base C types
    "char": "c_char",
    "uint8_t": "c_ubyte",
    "uint16_t": "c_uint16",
    "uint32_t": "c_uint32",
    "uint64_t": "c_uint64",
    "int8_t": "c_int8",
    "int16_t": "c_int16",
    "int32_t": "c_int32",
    "int64_t": "c_int64",
    "float": "c_float",
    "double": "c_double",
}


def parse_c_structure(
    header_content: str, struct_name: str
) -> Optional[List[Tuple[str, str]]]:
    """
    Parse a C structure definition from header content.
    Returns list of (field_name, field_type) tuples.
    """
    # Find the structure definition
    pattern = rf"typedef\s+struct\s+_{struct_name}\s*\{{\s*(.*?)\}}\s*{struct_name}\s*;"
    match = re.search(pattern, header_content, re.DOTALL)

    if not match:
        return None

    struct_body = match.group(1)
    fields = []

    # Parse each field line
    field_pattern = r"^\s*([a-zA-Z_][\w\s\*]+?)\s+([a-zA-Z_]\w+)(\[[^\]]+\])?\s*;.*?$"

    for line in struct_body.split("\n"):
        # Skip comments and empty lines
        line = re.sub(r"///.*$", "", line).strip()
        if not line or line.startswith("//"):
            continue

        match = re.match(field_pattern, line)
        if match:
            field_type = match.group(1).strip()
            field_name = match.group(2).strip()
            array_spec = match.group(3)

            # Construct the full type
            if array_spec:
                full_type = f"{field_type}{array_spec}"
            else:
                full_type = field_type

            fields.append((field_name, full_type))

    return fields if fields else None


def parse_python_structure(
    pyzes_content: str, struct_name: str
) -> Optional[List[Tuple[str, str]]]:
    """
    Parse a Python ctypes structure definition from pyzes.py.
    Returns list of (field_name, field_type) tuples.
    """
    # Find the class definition
    pattern = (
        rf"class\s+{struct_name}\s*\(_PrintableStructure\):.*?_fields_\s*=\s*\[(.*?)\]"
    )
    match = re.search(pattern, pyzes_content, re.DOTALL)

    if not match:
        return None

    fields_str = match.group(1)
    fields = []

    # Parse each field tuple
    field_pattern = r'\(\s*"([^"]+)"\s*,\s*([^\)]+?)\s*\)'

    for field_match in re.finditer(field_pattern, fields_str):
        field_name = field_match.group(1).strip()
        field_type = field_match.group(2).strip().rstrip(",")
        fields.append((field_name, field_type))

    return fields if fields else None


def normalize_c_type(c_type: str) -> str:
    """
    Convert C type to expected Python ctypes representation.
    """
    c_type = c_type.strip()

    # Handle arrays: char[SIZE] -> c_char * SIZE
    array_match = re.match(r"(\w+)\[([^\]]+)\]", c_type)
    if array_match:
        base_type = array_match.group(1)
        size = array_match.group(2)
        python_base = C_TO_PYTHON_TYPE_MAP.get(base_type, base_type)
        return f"{python_base} * {size}"

    # Map type if in dictionary, otherwise keep as-is
    return C_TO_PYTHON_TYPE_MAP.get(c_type, c_type)


def types_are_equivalent(type1: str, type2: str) -> bool:
    """Check if two types are equivalent."""
    if type1 == type2:
        return True

    # Check array types with same base and size
    array_match1 = re.match(r"(\w+)\s*\*\s*(.+)", type1)
    array_match2 = re.match(r"(\w+)\s*\*\s*(.+)", type2)

    if array_match1 and array_match2:
        base1, size1 = array_match1.groups()
        base2, size2 = array_match2.groups()

        if base1 == base2 and size1 == size2:
            return True

    return False


def compare_structures(
    c_fields: List[Tuple[str, str]], py_fields: List[Tuple[str, str]], struct_name: str
) -> List[str]:
    """
    Compare C and Python structure fields.
    Returns list of error messages (empty if structures match).
    """
    errors = []

    if len(c_fields) != len(py_fields):
        errors.append(
            f"Field count mismatch: C has {len(c_fields)} fields, Python has {len(py_fields)} fields"
        )

    # Compare field by field
    max_len = max(len(c_fields), len(py_fields))
    for i in range(max_len):
        if i >= len(c_fields):
            py_name, py_type = py_fields[i]
            errors.append(f"Extra field in Python: ({py_name}, {py_type})")
            continue

        if i >= len(py_fields):
            c_name, c_type = c_fields[i]
            errors.append(f"Missing field in Python: ({c_name}, {c_type})")
            continue

        c_name, c_type = c_fields[i]
        py_name, py_type = py_fields[i]

        # Check field name
        if c_name != py_name:
            errors.append(
                f"Field {i}: name mismatch - C: '{c_name}' ({c_type}), Python: '{py_name}' ({py_type})"
            )
            # Skip type comparison when names don't match - they're different fields
            continue

        # Check field type (only if names match)
        expected_type = normalize_c_type(c_type)
        if not types_are_equivalent(expected_type, py_type):
            errors.append(
                f"Field '{c_name}' (position {i}): type mismatch - C: '{c_type}' -> '{expected_type}', Python: '{py_type}'"
            )

    return errors


def get_all_structures_from_pyzes(pyzes_content: str) -> List[str]:
    """
    Extract all structure names that inherit from _PrintableStructure in pyzes.py.
    Returns list of structure names.
    """
    structures = []
    pattern = r"^class\s+(\w+)\(_PrintableStructure\):"

    for match in re.finditer(pattern, pyzes_content, re.MULTILINE):
        struct_name = match.group(1)
        structures.append(struct_name)

    return structures


def main():
    """Main validation function."""
    script_dir = Path(__file__).parent
    repo_root = script_dir.parent.parent.parent.parent

    # Paths
    zes_header = repo_root / "include" / "zes_api.h"
    ze_header = repo_root / "include" / "ze_api.h"
    pyzes_file = repo_root / "bindings" / "sysman" / "python" / "source" / "pyzes.py"

    # Check files exist
    for file_path in [zes_header, ze_header, pyzes_file]:
        if not file_path.exists():
            print(f"❌ FAIL: Required file not found: {file_path}")
            return 1

    # Read files
    zes_content = zes_header.read_text()
    ze_content = ze_header.read_text()
    pyzes_content = pyzes_file.read_text()

    # Dynamically discover all structures from pyzes.py
    structures_to_check = get_all_structures_from_pyzes(pyzes_content)

    if not structures_to_check:
        print("❌ FAIL: No structures found in pyzes.py")
        return 1

    print(f"Found {len(structures_to_check)} structures in pyzes.py")

    all_errors = {}
    structures_checked = 0
    structures_not_in_headers = []

    for struct_name in structures_to_check:
        # Parse from C header
        c_fields = parse_c_structure(zes_content, struct_name)
        if c_fields is None:
            # Try ze_api.h for core structures
            c_fields = parse_c_structure(ze_content, struct_name)

        if c_fields is None:
            structures_not_in_headers.append(struct_name)
            continue

        # Parse from Python
        py_fields = parse_python_structure(pyzes_content, struct_name)
        if py_fields is None:
            print(f"❌ FAIL: Structure '{struct_name}' not found in pyzes.py")
            all_errors[struct_name] = ["Structure not found in pyzes.py"]
            continue

        # Compare
        errors = compare_structures(c_fields, py_fields, struct_name)
        if errors:
            all_errors[struct_name] = errors
        else:
            structures_checked += 1

    # Report results
    print()
    print("=" * 70)
    print("Structure Validation Summary")
    print("=" * 70)
    print(f"Total structures found in pyzes.py: {len(structures_to_check)}")
    print(f"Structures validated successfully: {structures_checked}")

    if structures_not_in_headers:
        print(f"Structures not found in C headers: {len(structures_not_in_headers)}")
        for struct_name in structures_not_in_headers:
            print(f"  • {struct_name}")

    if all_errors:
        print(f"Structures with mismatches: {len(all_errors)}")
        print("=" * 70)
        print()
        print(f"❌ FAIL: {len(all_errors)} structure(s) have validation errors:\n")
        for struct_name, errors in all_errors.items():
            print(f"Structure: {struct_name}")
            for error in errors:
                print(f"  • {error}")
            print()
        return 1
    else:
        print("Structures with mismatches: 0")
        print("=" * 70)
        print()
        print("✅ All structure validations passed!")
        return 0


if __name__ == "__main__":
    sys.exit(main())
