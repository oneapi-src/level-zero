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
