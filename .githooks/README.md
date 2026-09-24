# Git Hooks

This directory contains git hooks for the repository.

## Setup

To enable the git hooks, run:

```bash
python3 .githooks/setup.py
```

Or on Windows:
```cmd
python .githooks\setup.py
```

This configures git to use hooks from this directory instead of the default `.git/hooks`.

**Note:** The hooks are written in Python for cross-platform compatibility (Linux, macOS, Windows).

## Available Hooks

### pre-commit

Automatically updates copyright years in files being committed. The hook:
- Runs `scripts/update_copyright.py` on modified files
- Updates copyright year ranges (e.g., 2019-2024 → 2019-2025)
- Adds single years where missing (e.g., 2019 → 2019-2025)
- Automatically stages the copyright changes
- Works across Linux, macOS, and Windows

The hook only modifies files already staged for commit and will not cause the commit to fail.
