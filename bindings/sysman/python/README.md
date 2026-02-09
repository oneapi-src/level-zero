# drivers.gpu.compute.pyzes
pyzes
======

Python bindings to the Intel Level-Zero-Driver Library
------------------------------------------------

Provides a Python interface to GPU management and monitoring functions.

This is a wrapper around the Level-Zero-Driver library.
For information about the Level-Zero-Driver library, see the spec document
https://oneapi-src.github.io/level-zero-spec/level-zero/latest/index.html

Download the latest package from: https://github.com/oneapi-src/level-zero

The level-zero header file contains function documentation that is relevant
to this wrapper. The header file is distributed with driver (ze_api.h and zes_api.h)

This module does not handles allocating structs before returning the desired value.
Non-success codes are returned and respective error is printed.

REQUIREMENTS
------------
- **Python 3.10** (required)
- ctypes module (included in standard Python library)
- Level Zero driver installed on the system

INSTALLATION
------------
```bash
# Ensure you have Python 3.10 installed
python3.10 --version

# Install the package (when available)
pip install pyzes
```

USAGE
-----
```
>>> from pyzes import *
>>> rc = zesInit(0)
>>> driver_count = c_uint32(0)
>>> rc = pyzes.zesDriverGet(byref(driver_count), None)
>>> print(f"Driver Count: {driver_count.value}")

```

## C Structure and its python module class ##
struct zes_process_state_t {

zes_structure_type_t stype
[in] type of this structure

const void *pNext
[in][optional] must be null or a pointer to an extension-specific structure (i.e. contains stype and pNext).

uint32_t processId
[out] Host OS process ID.

uint64_t memSize
[out] Device memory size in bytes allocated by this process (may not necessarily be resident on the device at the time of reading).

uint64_t sharedSize
[out] The size of shared device memory mapped into this process (may not necessarily be resident on the device at the time of reading).

zes_engine_type_flags_t engines
[out] Bitfield of accelerator engine types being used by this process.
}

Python Class
class zes_process_state_t(Structure):
    _fields_ = [
        ("pid", c_uint32),
        ("command", c_char * ZES_STRING_PROPERTY_SIZE),
        ("memSize", c_uint64),      # in bytes
        ("sharedMemSize", c_uint64),# in bytes
        ("engineType", zes_engine_type_flags_t),
        ("subdeviceId", c_uint32),
    ]


FUNCTIONS
---------
Python methods wrap Level-Zero-Driver functions, implemented in a C shared library.
Each function's use is the same:
- C function output parameters are filled in with values, and return codes are returned.

```
ze_result_t zesDeviceGetProperties(
    zes_device_handle_t hDevice,
    zes_device_properties_t* pProperties);
	
>>> props = zes_device_properties_t()
>>> props.stype = ZES_STRUCTURE_TYPE_DEVICE_PROPERTIES
>>> props.pNext = None
>>> pyzes.zesDeviceGetProperties(devices[i], byref(props))

```

- C structs are converted into Python classes.
```
// C Function and typedef struct

ze_result_t zesDeviceGetProperties(
    zes_device_handle_t hDevice,
    zes_device_properties_t* pProperties);

typedef struct _zes_device_properties_t
{
	zes_structure_type_t stype; 
	void* pNext;
	ze_device_properties_t core;
	uint32_t numSubdevices; 
	char serialNumber[ZES_STRING_PROPERTY_SIZE];
	char boardNumber[ZES_STRING_PROPERTY_SIZE]; 
	char brandName[ZES_STRING_PROPERTY_SIZE];   
	char modelName[ZES_STRING_PROPERTY_SIZE];   
	char vendorName[ZES_STRING_PROPERTY_SIZE];  
	char driverVersion[ZES_STRING_PROPERTY_SIZE]
} zes_device_properties_t;

>>>print(f"numSubdevices: {props.numSubdevices}")
>>>print(f"serialNumber:  {props.serialNumber}")
>>>print(f"boardNumber:   {props.boardNumber}")
>>>print(f"brandName: {props.brandName}")
>>>print(f"modelName: {props.modelName}")
>>>print(f"driverVersion: {props.driverVersion}")
>>>print(f"coreClockMHz: {props.core.coreClockRate}")
```

HOW TO USE STRUCTURE CHAINING
```
>>> props = zes_device_properties_t()
>>> props.stype = ZES_STRUCTURE_TYPE_DEVICE_PROPERTIES
>>> ext = zes_device_ext_properties_t()
>>> ext.stype = ZES_STRUCTURE_TYPE_DEVICE_EXT_PROPERTIES
>>> ext.pNext = None
>>> base.pNext = cast(pointer(ext), c_void_p)
>>> pyzes.zesDeviceGetProperties(devices[i], byref(props))
>>> print(f"Extension properties flags: {ext.flags}")
```

For more information see the Level-Zero-Driver documentation.

VARIABLES
---------
All meaningful constants and enums are exposed in Python module.

SUPPORTED APIs
--------------

| API Function | Module | Since Version | Limitations |
|--------------|--------|---------------|-------------|
| `zesInit` | Device | 0.1.0 | None |
| `zesDriverGet` | Device | 0.1.0 | None |
| `zesDeviceGet` | Device | 0.1.0 | None |
| `zesDeviceGetProperties` | Device | 0.1.0 | None |
| `zesDriverGetDeviceByUuidExp` | Device | 0.1.0 | Experimental API |
| `zesDeviceProcessesGetState` | Device | 0.1.0 | None |
| **Memory Management** |-|-|-|
| `zesDeviceEnumMemoryModules` | Memory | 0.1.0 | None |
| `zesMemoryGetProperties` | Memory | 0.1.0 | None |
| `zesMemoryGetState` | Memory | 0.1.0 | None |
| `zesMemoryGetBandwidth` | Memory | 0.1.0 | Linux: Requires superuser or read permissions for telem nodes |
| **Power Management** |-|-|-|
| `zesDeviceEnumPowerDomains` | Power | 0.1.0 | None |
| `zesPowerGetEnergyCounter` | Power | 0.1.0 | Linux: Requires superuser or read permissions for telem nodes |
| **Frequency Management** |-|-|-|
| `zesDeviceEnumFrequencyDomains` | Frequency | 0.1.0 | None |
| `zesFrequencyGetState` | Frequency | 0.1.0 | None |
| **Temperature Monitoring** |-|-|-|
| `zesDeviceEnumTemperatureSensors` | Temperature | 0.1.0 | None |
| `zesTemperatureGetProperties` | Temperature | 0.1.0 | None |
| `zesTemperatureGetConfig` | Temperature | 0.1.0 | None |
| `zesTemperatureGetState` | Temperature | 0.1.0 | Linux: Requires superuser or read permissions for telem nodes |
| **Engine Management** |-|-|-|
| `zesDeviceEnumEngineGroups` | Engine | 0.1.0 | Linux: Shows "no handles found" error when not in superuser mode |
| `zesEngineGetProperties` | Engine | 0.1.0 | None |
| `zesEngineGetActivity` | Engine | 0.1.0 | None |

RELEASE NOTES
-------------
Version 0.1.0 (Initial Release)
- Initial release of pyzes Python bindings for Intel Level-Zero Driver Library
- Added pyzes.py module with Python binding wrapper functions
- Added pyzes_example.py and pyzes_black_box_test.py as sample applications
- Supported API modules:
  - Device Management APIs
  - Memory Management APIs
  - Power Management APIs
  - Frequency Management APIs
  - Temperature Monitoring APIs
  - Engine Management APIs

Notes:
  Linux:
    zesPowerGetEnergyCounter
    zesTemperatureGetState
    zesMemoryGetBandwidth

    The above APIs needs user to be in superuser/root mode or have read permissions for telem nodes
    Telem Node Directory: /sys/class/intel_pmt/telem(1/2/3/4)/telem

    zesDeviceEnumEngineGroups shows no handles found error when not in super user mode.

# Contributing

See [CONTRIBUTING](CONTRIBUTING.md) for more information.

# License

Distributed under the MIT license. See [LICENSE](LICENSE) for more information.

# Security

See Intel's [Security Center](https://www.intel.com/content/www/us/en/security-center/default.html) for information on how to report a potential security issue or vulnerability.

See also [SECURITY](SECURITY.md).

