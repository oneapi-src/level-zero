# `scripts/`

Tooling for this repository. Most of it exists because a large share of the files
committed under `source/` are **generated**, not hand-written.

## Code generation

Most files under `source/`, plus `include/layers/zel_tracing_register_cb.h`, are
rendered from the Mako templates in [`templates/`](templates) using metadata
produced by the [specification repository](https://github.com/oneapi-src/level-zero-spec).
They are committed to git, so an ordinary build never regenerates them and needs
no Python at all.

**If you change one of those files by hand, your change is deleted the next time
anyone regenerates.** Edit the matching `templates/*.mako` instead. See
[Vetting a change before CI](../CONTRIBUTING.md#vetting-a-change-before-ci).

The pieces, outermost first:

| File | Role |
|---|---|
| `spec_metadata.py` | Entry point. Regenerates from the archived metadata, reports drift, and re-archives on a spec update. |
| `spec_metadata/` | The archived metadata: `input.json` (verbatim spec intermediate) and `spec_metadata.json` (manifest — spec tag, commit, API version, checksum). |
| `json2src.py` | The generator. Reads the metadata, drives `generate_code.py`, then merges and cleans up intermediates. |
| `generate_code.py` | Maps each template in `templates/` to its output path, for the lib, loader, layers and null driver. |
| `util.py` | `makoWrite()` — renders one template to one file and records it. Shared by every generator here. |
| `templates/` | The Mako templates. **This is where source changes to generated files belong.** |

Layering is strict: `spec_metadata.py` → `json2src.py` → `generate_code.py` →
`util.py`. Nothing above reimplements what is below; `spec_metadata.py` shells out
to `json2src.py` so there is exactly one code path that generates loader sources.

### `spec_metadata.py`

```bash
python3 scripts/spec_metadata.py regen     # regenerate the tree in place
python3 scripts/spec_metadata.py check     # report what a regen would change; never fails
python3 scripts/spec_metadata.py refresh --spec-repo <clone>   # re-archive after a spec release
```

`regen` and `check` need only Mako. `refresh` also needs PyYAML and a clone of the
spec repository, and is normally run by the `Update Spec` workflow rather than by
hand.

`regen` refuses to run if the archived metadata's API version disagrees with the
`@version` banner in `include/ze_api.h`, which is what stops a spec header bump
from regenerating the tree against the previous spec.

`scripts/spec_metadata/input.json` is checksummed byte-for-byte, so
[`.gitattributes`](../.gitattributes) marks it `-text`; without that a Windows
checkout rewrites its line endings and the checksum fails.

## Validation layer

| File | Role |
|---|---|
| `generate_checker.py` | Scaffolds a new validation-layer checker from `templates/checker/`. See the [validation layer CONTRIBUTING](../source/layers/validation/CONTRIBUTING.md). |
| `plot_resource_tracker.py` | Plots the CSV emitted by the system resource tracker checker. Standalone; needs `matplotlib`. |

## Packaging (Windows)

| File | Role |
|---|---|
| `generate_wix_guid.py` | Prints a fresh UUID. Called from `CMakeLists.txt` to mint the WiX product GUID; see [Product GUID Management](../CONTRIBUTING.md#3-product-guid-management). |
| `wix_env_installation.wxs` | WiX patch fragment that sets environment variables during MSI installation. |
| `level_zero_sdk_setup.ps1` | PowerShell environment setup shipped with the Windows SDK package. |
