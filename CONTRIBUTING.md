# Contributing

We encourage anyone who wants to contribute to submit
[Issues](https://github.com/oneapi-src/level-zero/issues) and
[Pull Requests](https://github.com/oneapi-src/level-zero/pulls). We will help
review these for proper alignment with the
[Level Zero Specification](https://oneapi-src.github.io/level-zero-spec/level-zero/latest/index.html).

## Git Hooks Setup

To enable automatic copyright year updates and other git hooks, run:

```bash
python3 .githooks/setup.py
```

Or on Windows:
```cmd
python .githooks\setup.py
```

This configures your local repository to use the shared git hooks. The pre-commit hook will automatically update copyright years in modified files before each commit.

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

As part of each Level Zero specification update, .mako scripts are updated which generate the code for the Level Zero Loader and layers.
When one contributes updates to the Level Zero Loader or Layers, one must update the code in [Level Zero Loader Mako Scripts](scripts/templates) to ensure that the new code is not lost in the next specification update.

To generate the code from the scripts, run the following commands:

* Clone the specification repo: `git clone https://github.com/oneapi-src/level-zero-spec.git level-zero-spec`
* Checkout the specification version in the specification repo, for example:
  * `cd level-zero-spec`
  * `git checkout v1.12.15`
* Generate the specification JSON file and Headers:
  * `cd level-zero-spec/scripts`
  * `python3 ./run.py --debug '--!html' '--!rst' '--!build' --ver 1.12`
* Copy the Headers From Spec to Loader repo
  * `cp level-zero-spec/include/* level-zero/include/`
* Execute the json2src script in the level-zero repo with the input.json in the specification repo with the corresponding spec version, for example:
  * `./level-zero/scripts/json2src.py --ver 1.12 --api-json level-zero-spec/scripts/input.json .`

These scripts update the code with what would be generated in the next specification update.

## Updating the Loader Version

When releasing a new version of the Level Zero Loader, the following steps must be performed:

### 1. Update the Version Number

The loader version is defined in the root [CMakeLists.txt](CMakeLists.txt) file using semantic versioning (https://semver.org/):

```cmake
project(level-zero VERSION 1.28.3)
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
* Has the code updated the templates? see here [Generating Level Zero Loader and Layer files from scripts](#generating-level-zero-loader-and-layer-files-from-scripts)

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
