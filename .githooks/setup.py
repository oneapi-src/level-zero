#! /usr/bin/env python3
"""
 Copyright (C) 2025-2026 Intel Corporation

 SPDX-License-Identifier: MIT

"""
"""
Setup script to configure git hooks for this repository.
This script is cross-platform compatible (Linux, macOS, Windows).
"""

import subprocess
import sys
from pathlib import Path

def main():
    """Configure git to use the .githooks directory."""
    try:
        # Get the root directory of the repo
        result = subprocess.run(
            ['git', 'rev-parse', '--show-toplevel'],
            capture_output=True,
            text=True,
            check=True
        )
        repo_root = Path(result.stdout.strip())
        githooks_dir = repo_root / '.githooks'
        
        # Configure git to use .githooks directory
        subprocess.run(
            ['git', 'config', 'core.hooksPath', str(githooks_dir)],
            check=True
        )
        
        print("Git hooks configured successfully!")
        print("The pre-commit hook will now automatically update copyright years.")
        
        return 0
    
    except subprocess.CalledProcessError as e:
        print(f"Error configuring git hooks: {e}", file=sys.stderr)
        return 1
    except Exception as e:
        print(f"Unexpected error: {e}", file=sys.stderr)
        return 1

if __name__ == '__main__':
    sys.exit(main())
