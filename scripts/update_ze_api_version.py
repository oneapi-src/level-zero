#!/usr/bin/env python3
"""
 Copyright (C) 2026 Intel Corporation

 SPDX-License-Identifier: MIT

Script to update ZE_API_VERSION_CURRENT value in a new dump file to match the old dump file.
This ensures ABI compatibility by reverting the version to the previous value.
"""

import re
import sys
import argparse


def get_ze_api_version_current_value(dump_file_path):
    """Extract the ZE_API_VERSION_CURRENT value from a dump file."""
    try:
        with open(dump_file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # Pattern to match ZE_API_VERSION_CURRENT and its value
        pattern = r"'name'\s*=>\s*'ZE_API_VERSION_CURRENT',\s*\n\s*'value'\s*=>\s*'(\d+)'"
        match = re.search(pattern, content)
        
        if match:
            return match.group(1)
        else:
            print(f"Error: Could not find ZE_API_VERSION_CURRENT in {dump_file_path}")
            return None
    except FileNotFoundError:
        print(f"Error: File {dump_file_path} not found")
        return None
    except Exception as e:
        print(f"Error reading {dump_file_path}: {e}")
        return None


def update_ze_api_version_current(dump_file_path, old_value, new_value):
    """Update ZE_API_VERSION_CURRENT value in the dump file."""
    try:
        with open(dump_file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # Pattern to match ZE_API_VERSION_CURRENT and replace its value
        pattern = r"('name'\s*=>\s*'ZE_API_VERSION_CURRENT',\s*\n\s*'value'\s*=>\s*')(\d+)(')"
        
        def replace_value(match):
            if match.group(2) == new_value:
                return match.group(1) + old_value + match.group(3)
            return match.group(0)  # No change if value doesn't match expected
        
        updated_content = re.sub(pattern, replace_value, content)
        
        # Check if any replacement was made
        if updated_content == content:
            print(f"Warning: No replacement made. Expected to find value '{new_value}' but it was not found.")
            return False
        
        # Write the updated content back to the file
        with open(dump_file_path, 'w', encoding='utf-8') as f:
            f.write(updated_content)
        
        print(f"Successfully updated ZE_API_VERSION_CURRENT from '{new_value}' to '{old_value}' in {dump_file_path}")
        return True
        
    except Exception as e:
        print(f"Error updating {dump_file_path}: {e}")
        return False


def main():
    parser = argparse.ArgumentParser(
        description="Update ZE_API_VERSION_CURRENT in new dump file to match old dump file"
    )
    parser.add_argument(
        "old_dump", 
        help="Path to the old dump file (reference for the target value)"
    )
    parser.add_argument(
        "new_dump", 
        help="Path to the new dump file (to be modified)"
    )
    parser.add_argument(
        "--dry-run", 
        action="store_true", 
        help="Show what would be changed without actually modifying the file"
    )
    
    args = parser.parse_args()
    
    # Get the ZE_API_VERSION_CURRENT value from the old dump
    old_value = get_ze_api_version_current_value(args.old_dump)
    if old_value is None:
        sys.exit(1)
    
    # Get the ZE_API_VERSION_CURRENT value from the new dump
    new_value = get_ze_api_version_current_value(args.new_dump)
    if new_value is None:
        sys.exit(1)
    
    print(f"Old dump ({args.old_dump}) ZE_API_VERSION_CURRENT value: {old_value}")
    print(f"New dump ({args.new_dump}) ZE_API_VERSION_CURRENT value: {new_value}")
    
    if old_value == new_value:
        print("Values are already the same. No update needed.")
        sys.exit(0)
    
    if args.dry_run:
        print(f"DRY RUN: Would update ZE_API_VERSION_CURRENT from '{new_value}' to '{old_value}' in {args.new_dump}")
        sys.exit(0)
    
    # Perform the update
    success = update_ze_api_version_current(args.new_dump, old_value, new_value)
    
    if success:
        # Verify the change
        updated_value = get_ze_api_version_current_value(args.new_dump)
        if updated_value == old_value:
            print("Verification successful: Value has been updated correctly.")
        else:
            print(f"Verification failed: Expected '{old_value}', but found '{updated_value}'")
            sys.exit(1)
    else:
        sys.exit(1)


if __name__ == "__main__":
    main()
