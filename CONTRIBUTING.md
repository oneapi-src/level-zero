# Contributing

We encourage anyone who wants to contribute to submit
[Issues](https://github.com/oneapi-src/level-zero/issues) and
[Pull Requests](https://github.com/oneapi-src/level-zero/pulls). We will help
review these for proper alignment with the
[Level Zero Specification](https://oneapi-src.github.io/level-zero-spec/level-zero/latest/index.html).

## C++ Coding Standards

* C++14 maximum support
* Avoid C Arrays, replace with `std::array<>` / `std::vector<>`
* Avoid "magic numbers"
* Avoid C-style memory allocations in favor of C++
* Use `nullptr` instead of `NULL`
* Don't add `void` to empty argument lists
* Use `std::unique_ptr` in place of `std::auto_ptr`

## Naming Conventions

* The functionality in the Level Zero Loader and layers which follow the Level Zero spec must follow these naming conventions:

  * https://oneapi-src.github.io/level-zero-spec/level-zero/latest/core/INTRO.html#naming-convention

* If the contributions are adding new functionality unique to the Level Zero Loader (ie not Level Zero Spec related):
  * Level Zero Loader specific APIs must have the prefix: `zel`
    * see here for examples: [Loader API Documentation](doc/loader_api.md)

## Generating Level Zero Loader and Layer files from scripts

Most of the files under `source/`, plus `include/layers/zel_tracing_register_cb.h`, are **generated** from the Mako templates in [scripts/templates](scripts/templates). They are committed to git, so an ordinary build never regenerates them.

**If you edit a generated file directly, your change is deleted the next time anyone regenerates**, and the build usually breaks then rather than now. Put the change in the matching `scripts/templates/*.mako` instead, then regenerate. See [scripts/README.md](scripts/README.md) for how the generators fit together.

The metadata needed to regenerate is archived in the repository under `scripts/spec_metadata/`, so no clone of the specification repository is required:

```bash
python3 scripts/spec_metadata.py regen
```

This rewrites the generated files in place from the spec release the loader currently targets. Review `git diff` and commit the result along with your template change.

### Regenerating against a different specification release

Only needed when moving the loader to a new specification release; this is normally done by the `Update Spec` workflow rather than by hand.

* Clone the specification repo: `git clone https://github.com/oneapi-src/level-zero-spec.git level-zero-spec`
* Check out the release to move to, for example:
  * `cd level-zero-spec && git checkout v1.17.24`
* Copy the headers from the spec repo into the loader: `cp level-zero-spec/include/* level-zero/include/`
* Re-archive the metadata and regenerate, from the loader repo:
  * `python3 scripts/spec_metadata.py refresh --spec-repo ../level-zero-spec`
  * `python3 scripts/spec_metadata.py regen`

`refresh` derives the API version from the release tag that is checked out. Do not
pass a `--ver` below that release: the version is a maximum-version filter over the
specification metadata, so a value that is too low silently drops every function
added after it. The result still compiles — it is simply a loader missing those
exports.

## Vetting a change before CI

CI regenerates the loader sources from the archived metadata and then builds and
tests the result, so a hand-edit to a generated file fails there even though it
built fine locally. These checks run the same things locally, cheapest first.

**1. Would a regeneration change anything you did not expect?**

```bash
python3 scripts/spec_metadata.py check
```

Lists files that a regeneration would rewrite, and never fails. Some drift is
normal — comment and doc-string wording changes upstream in the spec between
releases. What matters is whether *your* file is in that list. If it is, the change
belongs in a template. Add `--diff` to see exactly what would change.

**2. Does the regenerated tree still build and test?**

This is the check that actually gates a pull request.

```bash
python3 scripts/spec_metadata.py regen
mkdir -p build && cd build
cmake -D CMAKE_BUILD_TYPE=Release -D BUILD_L0_LOADER_TESTS=1 -D INSTALL_NULL_DRIVER=1 ..
make -j$(nproc)
ZEL_LIBRARY_PATH=$PWD/lib ctest -V
```

A compile error naming a symbol you added is the signature of the failure this
guards against: the symbol was written into a generated file, and regeneration
removed it. `ZEL_LIBRARY_PATH` is required — without it the suite runs against a
system loader and fails misleadingly.

`regen` rewrites committed files in the working tree. Run it on a clean tree so
`git diff` shows only what regeneration changed, and use `git checkout -- source/
include/` to undo it.

**3. Spelling.**

```bash
codespell
```

Configuration lives in [.codespellrc](.codespellrc), so no arguments are needed.
Note that spelling fixes applied to a *generated* file are lost on regeneration —
they have to go upstream into the specification repository.

## Updating the Loader Version

When releasing a new version of the Level Zero Loader, the following steps must be performed:

### 1. Update the Version Number

The loader version is defined in the root [CMakeLists.txt](CMakeLists.txt) file using semantic versioning (https://semver.org/):

```cmake
project(level-zero VERSION 1.32.0)
```

Update the version number according to the type of changes:
* **MAJOR version** (X.0.0): Incompatible API changes
* **MINOR version** (1.X.0): Add functionality in a backward compatible manner
* **PATCH version** (1.28.X): Backward compatible bug fixes

### 2. Update the CHANGELOG.md

Add a new version section at the top of [CHANGELOG.md](CHANGELOG.md) following this format:

```markdown
## v1.28.3
* Brief description of change 1
* Brief description of change 2 with PR reference (#123)
* feature: Description for new features
* fix: Description for bug fixes
```

Guidelines for changelog entries:
* Use present tense for descriptions
* Prefix feature additions with `feature:`
* Prefix bug fixes with `fix:`
* Include PR numbers when applicable using `(#123)` format
* List the most significant changes first
* Keep descriptions concise and user-focused

### 3. Product GUID Management

The `PRODUCT_GUID.txt` file in the root directory stores the version number and a unique GUID for Windows installer packages. **This is managed automatically by CMake** when you update the version:

**Automatic GUID Generation Process:**
1. When CMake runs, it checks if `PRODUCT_GUID.txt` exists
2. If the version in the file doesn't match `PROJECT_VERSION` in CMakeLists.txt, CMake automatically:
   * Generates a new UUID using `scripts/generate_wix_guid.py`
   * Updates `PRODUCT_GUID.txt` with the new version and GUID
3. The GUID is used for Windows WiX installer generation via `CPACK_WIX_PRODUCT_GUID`

**Manual GUID Update (Rarely Needed):**
If you need to manually generate a new GUID:
```bash
python3 scripts/generate_wix_guid.py
```

Then update `PRODUCT_GUID.txt` with:
```
<version>
<new-guid>
```

**Important Notes:**
* The PRODUCT_GUID should change with each version to ensure proper Windows installer upgrade behavior
* The automatic update happens during CMake configuration, so the file may change after running cmake
* Commit the updated `PRODUCT_GUID.txt` along with version changes

### 4. Version Update Checklist

When preparing a version release:
- [ ] Update version number in [CMakeLists.txt](CMakeLists.txt)
- [ ] Add new version section to [CHANGELOG.md](CHANGELOG.md) with all changes
- [ ] Run CMake to automatically update PRODUCT_GUID.txt
- [ ] Commit all version-related file changes together
- [ ] Create a git tag for the release: `git tag -a v1.28.3 -m "Release v1.28.3"`
- [ ] Verify the version is correctly reflected in build outputs

## Code Review

Quality Code Review of the oneAPI Level Zero Loader & Layers is important for all Maintainers and Contributors to ensure that quality updates are added to the Loader and Layers for customers of oneAPI Level Zero.

### Review Checklist

When performing a code review please refer to this checklist to guide your comments:

* Does the code follow C++ Coding Standards? [C++ Coding Standards](#c-coding-standards).
* Does the code follow the Level Zero naming conventions? [Naming Conventions](#naming-conventions).
* Does the code follow the Level Zero specification? See here for the latest spec: https://oneapi-src.github.io/level-zero-spec/level-zero/latest/index.html.
* Is the code for the Validation Layer? Please review the following: [Validation Layer README](source/layers/validation/README.md).
* Is the code for the Tracing Layer? Please review the following: [Tracing Layer README](source/layers/tracing/README.md).
* Is the code "Vendor & Platform agnostic"? ie Are the changes in the loader or in the layers ignorant of the implementation in the L0 drivers?
* Is the Code Modular or can the code be Modular? ie Can the code be added to common functions used in loader or layer common functions or is it for a specific usecase?
* Can the code handle Multiple Driver or Device environments? Verify that the changes work within the [Intercept Layer](source/loader/ze_ldrddi.cpp) which is used when multiple drivers are present and that support works across devices.
* Has the code updated the templates? see here [Generating Level Zero Loader and Layer files from scripts](#generating-level-zero-loader-and-layer-files-from-scripts). If a file under `source/` was changed, check whether that file is generated: a hand-edit there is lost on the next regeneration and must move into the matching `scripts/templates/*.mako`. See [Vetting a change before CI](#vetting-a-change-before-ci).

## Sign Your Work

Please use the sign-off line at the end of your patch. Your signature certifies
that you wrote the patch or otherwise have the right to pass it on as an
open-source patch. To do so, if you can certify the below
(from [developercertificate.org](http://developercertificate.org/)):

```
Developer Certificate of Origin
Version 1.1

Copyright (C) 2004, 2006 The Linux Foundation and its contributors.
660 York Street, Suite 102,
San Francisco, CA 94110 USA

Everyone is permitted to copy and distribute verbatim copies of this
license document, but changing it is not allowed.

Developer's Certificate of Origin 1.1

By making a contribution to this project, I certify that:

(a) The contribution was created in whole or in part by me and I
    have the right to submit it under the open source license
    indicated in the file; or

(b) The contribution is based upon previous work that, to the best
    of my knowledge, is covered under an appropriate open source
    license and I have the right under that license to submit that
    work with modifications, whether created in whole or in part
    by me, under the same open source license (unless I am
    permitted to submit under a different license), as indicated
    in the file; or

(c) The contribution was provided directly to me by some other
    person who certified (a), (b) or (c) and I have not modified
    it.

(d) I understand and agree that this project and the contribution
    are public and that a record of the contribution (including all
    personal information I submit with it, including my sign-off) is
    maintained indefinitely and may be redistributed consistent with
    this project or the open source license(s) involved.
```

Then add a line to every git commit message:

    Signed-off-by: Kris Smith <kris.smith@email.com>

Use your real name (sorry, no pseudonyms or anonymous contributions).

If you set your `user.name` and `user.email` git configs, you can sign your
commit automatically with `git commit -s`.
