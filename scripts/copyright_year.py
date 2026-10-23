#! /usr/bin/env python3
"""
 Copyright (C) 2026 Intel Corporation

 SPDX-License-Identifier: MIT

 Checks or updates the year in the Intel copyright header of changed files.

 A file that is changed should carry the current year in its copyright line.
 If the current year is 2026, a single year 2024 becomes 2024-2026 and a range
 2019-2025 becomes 2019-2026. Only the Intel line is touched. Third-party
 copyright lines, and files with no copyright line at all, are left alone.

 Subcommands:
   check    report stale years; exit 1 if any are found (used by CI)
   update   rewrite stale years in place (run locally before committing)

 Which files are processed:
   * With no paths (the default), only files that git reports as changed are
     processed: everything changed since the merge base with --base (default
     origin/master), including staged and unstaged edits. Untracked files and
     files you have not changed are NOT processed.
   * With paths, exactly those files are processed. git is not needed.
 Nothing is ever staged; review the result with 'git diff' and stage it yourself.

 Outside a git checkout (for example an unpacked source RPM or tarball), or if
 git is not installed, there are no changed files to find. With no paths the
 script prints a note and exits 0 without touching anything.

 Most files under source/ are generated from scripts/templates/*.mako. If one of
 those is reported, update the matching template too, or the next regeneration
 puts the old year back.

 Exit status: 0 nothing stale, 1 stale years found (check only), 2 error.
"""
import argparse
import datetime
import os
import re
import shutil
import subprocess
import sys

SCRIPTS_DIR = os.path.dirname(os.path.realpath(__file__))
DEFAULT_REPO_ROOT = os.path.dirname(SCRIPTS_DIR)

# A copyright header sits at the top of the file; there is no need to scan
# further, and stopping early avoids matching copyright text in code or docs.
HEADER_LINES = 30

# Matched on bytes so that encoding and line endings are preserved on rewrite.
COPYRIGHT_RE = re.compile(
    rb"(Copyright \(C\) )(\d{4})(?:-(\d{4}))?( Intel Corporation)", re.IGNORECASE)


def eprint(*args):
    print(*args, file=sys.stderr)


def git(repo_root, *args):
    result = subprocess.run(["git", "-C", repo_root] + list(args),
                            capture_output=True, text=True)
    if result.returncode != 0:
        raise RuntimeError("git %s failed: %s" % (" ".join(args), result.stderr.strip()))
    return result.stdout


def is_git_checkout(repo_root):
    """True if repo_root is the top of a git work tree and git is installed."""
    if shutil.which("git") is None:
        return False
    try:
        top = git(repo_root, "rev-parse", "--show-toplevel").strip()
    except RuntimeError:
        return False
    # An unpacked source tree can sit inside some unrelated repository (a home
    # directory under version control, say); that repository's changes are not ours.
    return os.path.realpath(top) == repo_root


def changed_files(repo_root, base):
    try:
        merge_base = git(repo_root, "merge-base", base, "HEAD").strip()
    except RuntimeError as e:
        raise RuntimeError("%s\n       Fetch %s, or pass --base <ref> for your upstream branch." % (e, base))
    # Diffing the merge base against the working tree covers committed, staged
    # and unstaged changes in one call. Deleted files are filtered out.
    out = git(repo_root, "diff", "--name-only", "--diff-filter=ACMR", "-z", merge_base)
    return [name for name in out.split("\0") if name]


def is_binary(data):
    return b"\0" in data[:8192]


def fix_header(data, year):
    """Return (new_data, findings); findings is a list of (line, old, new)."""
    lines = data.splitlines(keepends=True)
    findings = []
    for index, line in enumerate(lines[:HEADER_LINES]):
        match = COPYRIGHT_RE.search(line)
        if not match:
            continue
        first = int(match.group(2))
        last = int(match.group(3)) if match.group(3) else first
        if last >= year:
            continue
        replacement = match.group(1) + b"%d-%d" % (first, year) + match.group(4)
        lines[index] = line[:match.start()] + replacement + line[match.end():]
        findings.append((index + 1, match.group(0).decode(), replacement.decode()))
    return b"".join(lines), findings


def run(args):
    repo_root = os.path.realpath(args.repo_root)
    if args.paths:
        paths = [os.path.relpath(os.path.realpath(p), repo_root) for p in args.paths]
    elif not is_git_checkout(repo_root):
        print("%s is not a git checkout (or git is not installed), so there are no changed "
              "files to %s. Nothing to do. Pass file paths to process specific files."
              % (repo_root, args.command))
        return 0
    else:
        paths = changed_files(repo_root, args.base)

    stale = 0
    for rel in sorted(set(paths)):
        path = os.path.join(repo_root, rel)
        if not os.path.isfile(path):
            if args.paths:
                eprint("error: %s is not a file" % rel)
                return 2
            continue
        with open(path, "rb") as fin:
            data = fin.read()
        if is_binary(data):
            continue
        new_data, findings = fix_header(data, args.year)
        for line, old, new in findings:
            stale += 1
            if args.github:
                print("::error file=%s,line=%d::Stale copyright year: '%s' should be '%s'. "
                      "Run 'python3 scripts/copyright_year.py update'." % (rel, line, old, new))
            else:
                print("%s:%d: %s -> %s" % (rel, line, old, new))
        if findings and args.command == "update":
            with open(path, "wb") as fout:
                fout.write(new_data)

    if args.command == "update":
        print("Updated %d copyright line(s)." % stale if stale else "All copyright years are current.")
        return 0
    if stale:
        sys.stdout.flush()
        eprint("%d stale copyright line(s). Run 'python3 scripts/copyright_year.py update' to fix." % stale)
        return 1
    print("All copyright years are current.")
    return 0


def main():
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--repo-root", default=DEFAULT_REPO_ROOT,
                        help="root of the level-zero checkout (default: %(default)s)")
    parser.add_argument("--base", default="origin/master",
                        help="ref to diff against when no paths are given (default: %(default)s)")
    parser.add_argument("--year", type=int, default=datetime.date.today().year,
                        help="year to require (default: the current year)")
    subparsers = parser.add_subparsers(dest="command", required=True)

    check = subparsers.add_parser(
        "check", help="report stale years; exit 1 if any are found",
        description="Report stale copyright years without changing any file. With no paths, "
                    "only files git reports as changed since the merge base with --base are checked.")
    check.add_argument("--github", action="store_true",
                       help="emit GitHub Actions error annotations")
    update = subparsers.add_parser(
        "update", help="rewrite stale years in place",
        description="Rewrite stale copyright years in place. With no paths, only files git "
                    "reports as changed since the merge base with --base are updated.")
    for sub in (check, update):
        sub.add_argument("paths", nargs="*",
                         help="files to process; if omitted, only the files git reports as changed")
    update.set_defaults(github=False)

    args = parser.parse_args()
    try:
        return run(args)
    except (OSError, RuntimeError) as e:
        eprint("error: %s" % e)
        return 2


if __name__ == "__main__":
    sys.exit(main())
