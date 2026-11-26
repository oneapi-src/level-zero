# pyzes Examples

This directory contains example scripts demonstrating how to use the pyzes module.

The examples are installed as the `pyzes.examples` subpackage, so they don't add a top-level `examples` package to `site-packages` that could conflict with other projects.

## Using Examples After Installation

**These instructions are for users who installed pyzes via pip:**

After installing pyzes via pip:
```bash
pip install pyzes
```

You can run examples directly:
```bash
python3 -m pyzes.examples.pyzes_example
python3 -m pyzes.examples.pyzes_black_box_test -h
```

---

## If You Cloned the Repository

If you cloned the level-zero repository locally, run the examples directly from the repository:

```bash
cd bindings/sysman/python/source/pyzes/examples
python3 pyzes_example.py
python3 pyzes_black_box_test.py -h
```

The scripts add `bindings/sysman/python/source` to `sys.path`, so they import the local `pyzes` without installing it.

---

## Requirements

- Python 3.10+
- Intel GPU with Level-Zero drivers installed
- pyzes module

---

## pyzes_black_box_test.py Coverage

| Option | Test | APIs exercised |
|--------|------|----------------|
| `-D`, `--driverproperties` | Driver properties | `zesDriverGetProperties`, `zesDriverGetApiVersion`, `zesDriverGetPciDeviceProperties`, `zesDriverGetExtensionProperties`, `zesDriverGetExtensionFunctionAddress` |
| `-g`, `--global` | Global operations | `zesDeviceGetProperties` with the `zes_device_index_ext_properties_t` and `zes_device_gpu_topology_ext_properties_t` extensions chained, `zesDeviceGetSubDevicePropertiesExp`, `zesDriverGetDeviceByUuidExp`, `zesDeviceProcessesGetState` |

`zesDriverGetPciDeviceProperties` lists every supported device on the PCI bus, including devices with no kernel mode driver bound. A revision of `0xFF` is flagged as "device not responding". On drivers that return `ZE_RESULT_ERROR_UNSUPPORTED_FEATURE`, the test reports it as not supported instead of failing.

Run `python3 pyzes_black_box_test.py -h` for the full list of options.
