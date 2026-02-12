# pyzes Examples

This directory contains example scripts demonstrating how to use the pyzes module.

**IMPORTANT:** The usage instructions below apply to pyzes installed via pip. If you've cloned this repository locally, you should run the examples directly from the `test/` directory in the repository root instead.

## Using Examples After Installation

**These instructions are for users who installed pyzes via pip:**

After installing pyzes via pip:
```bash
pip install pyzes
```

You can run examples directly:
```bash
python3 -m examples.pyzes_example
python3 -m examples.pyzes_black_box_test -h
```

---

## If You Cloned the Repository

If you cloned the level-zero repository locally, run the examples directly from the repository:

```bash
cd bindings/sysman/python/source/examples
python3 pyzes_example.py
python3 pyzes_black_box_test.py -h
```

The examples in this `source/examples/` directory are packaged for pip distribution only.

---

## Requirements

- Python 3.10+
- Intel GPU with Level-Zero drivers installed
- pyzes module
