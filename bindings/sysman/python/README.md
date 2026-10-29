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

EXAMPLES
--------
Example scripts are installed with the package under `pyzes.examples`:
```bash
python3 -m pyzes.examples.pyzes_example
python3 -m pyzes.examples.pyzes_black_box_test -h
```
See the [examples README](https://github.com/oneapi-src/level-zero/blob/master/bindings/sysman/python/source/pyzes/examples/README.md) for details.

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

The Linux Dependencies and Windows Dependencies columns list the external libraries that the Level Zero driver needs at runtime on that OS to support the API. Which of them is used depends on the platform.
- Linux:
  - `libigsc`: libigsc.so.1 or libigsc.so.0
  - `libudev`: libudev.so.1
  - `libnl-genl-3`: libnl-genl-3.so.200
  - `libtracefs`: libtracefs.so.1, version 1.8.0 or newer
- Windows:
  - `igsc.dll`

| API Function | Module | Since Version | Limitations | Linux Dependencies | Windows Dependencies |
|--------------|--------|---------------|-------------|--------------------|----------------------|
| `zesInit` | Device | 0.1.0 | None | None | None |
| `zesDriverGet` | Device | 0.1.0 | None | None | None |
| `zesDeviceGet` | Device | 0.1.0 | None | None | None |
| `zesDeviceGetProperties` | Device | 0.1.0 | None | None | None |
| `zesDriverGetDeviceByUuidExp` | Device | 0.1.0 | Experimental API | None | None |
| `zesDeviceGetSubDevicePropertiesExp` | Device | 0.1.0 | Experimental API | None | None |
| `zesDeviceProcessesGetState` | Device | 0.1.0 | None | None | None |
| **Driver Management** |-|-|-|-|-|
| `zesDriverGetProperties` | Driver | 0.1.4 | None | None | None |
| `zesDriverGetExtensionProperties` | Driver | 0.1.4 | None | None | None |
| `zesDriverGetExtensionFunctionAddress` | Driver | 0.1.4 | Returns a raw function address | None | None |
| `zesDriverEventListenEx` | Driver | 0.1.4 | Linux: Requires superuser | `libudev`, `libnl-genl-3` | None |
| `zesDriverEventRegisterExt` | Driver | 0.1.4 | None | None | None |
| `zesDriverEventListenExt` | Driver | 0.1.4 | Linux: Requires superuser | `libudev`, `libnl-genl-3`, `libtracefs` | None |
| `zesDeviceGetState` | Device | 0.1.4 | None | `libigsc` | None |
| `zesDeviceResetExt` | Device | 0.1.4 | Linux: Requires superuser; all device state is lost | None | None |
| `zesDeviceEventRegister` | Device | 0.1.4 | Linux: Requires superuser | None | None |
| `zesDeviceGetHealthStatusExt` | Device | 0.1.4 | None | None | None |
| `zesDeviceSetHealthStatusExt` | Device | 0.1.4 | Linux: Requires superuser; persisted to non-volatile memory | None | None |
| `zesDeviceEnumFirmwares` | Device | 0.1.4 | None | `libigsc` | `igsc.dll` |
| `zesFirmwareGetProperties` | Firmware | 0.1.4 | None | `libigsc` | `igsc.dll` |
| **Memory Management** |-|-|-|-|-|
| `zesDeviceEnumMemoryModules` | Memory | 0.1.0 | None | None | None |
| `zesMemoryGetProperties` | Memory | 0.1.0 | None | None | None |
| `zesMemoryGetState` | Memory | 0.1.0 | None | `libigsc` | None |
| `zesMemoryGetBandwidth` | Memory | 0.1.0 | Linux: Requires superuser or read permissions for telem nodes | None | None |
| **Power Management** |-|-|-|-|-|
| `zesDeviceEnumPowerDomains` | Power | 0.1.0 | None | None | None |
| `zesPowerGetEnergyCounter` | Power | 0.1.0 | Linux: Requires superuser or read permissions for telem nodes | None | None |
| `zesPowerGetProperties` | Power | 0.1.2 | None | None | None |
| `zesPowerGetLimitsExt` | Power | 0.1.2 | Extended power limits API | None | None |
| `zesPowerSetLimitsExt` | Power | 0.1.2 | Linux: Requires superuser or write permissions for telem nodes | None | None |
| `zesPowerGetUsage` | Power | 0.1.4 | Linux: Requires superuser or read permissions for telem nodes | None | None |
| `zesPowerGetLimitsExt2` | Power | 0.1.4 | None | None | None |
| `zesPowerSetLimitsExt2` | Power | 0.1.4 | Linux: Requires superuser | None | None |
| `zesPowerGetEnergyThreshold` | Power | 0.1.4 | None | None | None |
| `zesPowerSetEnergyThreshold` | Power | 0.1.4 | Linux: Requires superuser | None | None |
| **Frequency Management** |-|-|-|-|-|
| `zesDeviceEnumFrequencyDomains` | Frequency | 0.1.0 | None | None | None |
| `zesFrequencyGetState` | Frequency | 0.1.0 | None | None | None |
| `zesFrequencyGetProperties` | Frequency | 0.1.2 | None | None | None |
| `zesFrequencyGetAvailableClocks` | Frequency | 0.1.2 | None | None | None |
| `zesFrequencyGetRange` | Frequency | 0.1.2 | None | None | None |
| `zesFrequencySetRange` | Frequency | 0.1.2 | Linux: Requires superuser or write permissions for telem nodes | None | None |
| `zesFrequencyGetThrottleTime` | Frequency | 0.1.2 | None | None | None |
| **Temperature Monitoring** |-|-|-|-|-|
| `zesDeviceEnumTemperatureSensors` | Temperature | 0.1.0 | None | None | None |
| `zesTemperatureGetProperties` | Temperature | 0.1.0 | None | None | None |
| `zesTemperatureGetConfig` | Temperature | 0.1.0 | None | None | None |
| `zesTemperatureGetState` | Temperature | 0.1.0 | Linux: Requires superuser or read permissions for telem nodes | None | None |
| `zesTemperatureSetConfig` | Temperature | 0.1.4 | Linux: Requires superuser | None | None |
| **Engine Management** |-|-|-|-|-|
| `zesDeviceEnumEngineGroups` | Engine | 0.1.0 | Linux: Shows "no handles found" error when not in superuser mode | None | None |
| `zesEngineGetProperties` | Engine | 0.1.0 | None | None | None |
| `zesEngineGetActivity` | Engine | 0.1.0 | None | None | None |
| `zesEngineGetActivityExt` | Engine | 0.1.4 | None | None | None |
| **Standby Management** |-|-|-|-|-|
| `zesDeviceEnumStandbyDomains` | Standby | 0.1.4 | None | None | None |
| `zesStandbyGetProperties` | Standby | 0.1.4 | None | None | None |
| `zesStandbyGetMode` | Standby | 0.1.4 | None | None | None |
| `zesStandbySetMode` | Standby | 0.1.4 | Linux: Requires superuser | None | None |
| **Virtual Function (VF) Management** |-|-|-|-|-|
| `zesDeviceEnumEnabledVFExp` | VF Management | 0.1.4 | Experimental API | None | None |
| `zesVFManagementGetVFCapabilitiesExp2` | VF Management | 0.1.4 | Experimental API | None | None |
| `zesVFManagementGetVFEngineUtilizationExp2` | VF Management | 0.1.4 | Experimental API. Linux: Requires superuser | None | None |
| `zesVFManagementGetVFMemoryUtilizationExp2` | VF Management | 0.1.4 | Experimental API | None | None |
| **PCI Management** |-|-|-|-|-|
| `zesDevicePciGetProperties` | PCI | 0.1.2 | Linux: Requires superuser or read permissions for telem nodes | None | None |
| `zesDevicePciGetState` | PCI | 0.1.2 | Linux: Requires superuser or read permissions for telem nodes | None | None |
| `zesDevicePciGetStats` | PCI | 0.1.2 | Linux: Requires superuser or read permissions for telem nodes | None | None |
| **ECC (Error Correction Code) Management** |-|-|-|-|-|
| `zesDeviceEccAvailable` | ECC | 0.1.2 | None | `libigsc` | `igsc.dll` |
| `zesDeviceEccConfigurable` | ECC | 0.1.2 | None | `libigsc` | `igsc.dll` |
| `zesDeviceGetEccState` | ECC | 0.1.2 | None | `libigsc` | `igsc.dll` |
| `zesDeviceSetEccState` | ECC | 0.1.2 | None | `libigsc` | `igsc.dll` |
| **RAS (Reliability, Availability, Serviceability)** |-|-|-|-|-|
| `zesDeviceEnumRasErrorSets` | RAS | 0.1.4 | Linux: Requires superuser | `libnl-genl-3`, `libigsc` | None |
| `zesRasGetProperties` | RAS | 0.1.4 | None | `libnl-genl-3`, `libigsc` | None |
| `zesRasGetSupportedCategoriesExp` | RAS | 0.1.4 | Experimental API | `libnl-genl-3`, `libigsc` | None |
| `zesRasGetStateExp2` | RAS | 0.1.4 | Experimental API. Linux: Requires superuser | `libnl-genl-3`, `libigsc` | None |
| `zesRasGetConfigExp` | RAS | 0.1.4 | Experimental API. Linux: Requires superuser | `libnl-genl-3` | None |
| `zesRasSetConfigExp` | RAS | 0.1.4 | Experimental API. Linux: Requires superuser | `libnl-genl-3` | None |
| `zesRasClearStateExp` | RAS | 0.1.4 | Experimental API. Linux: Requires superuser | `libnl-genl-3`, `libigsc` | None |
| **Info Log Management** |-|-|-|-|-|
| `zesDriverEnumInfoLogsExt` | Info Log | 0.1.4 | Linux: Requires superuser | None | None |
| `zesInfoLogGetPropertiesExt` | Info Log | 0.1.4 | None | None | None |
| `zesInfoLogCreateInstanceExt` | Info Log | 0.1.4 | Linux: Requires superuser | `libtracefs` | None |
| `zesInfoLogInstanceReadWithMetadataExt` | Info Log | 0.1.4 | Records returned are consumed. Linux: Requires superuser | `libtracefs` | None |
| `zesInfoLogInstancePeekWithMetadataExt` | Info Log | 0.1.4 | Linux: Requires superuser | `libtracefs` | None |
| `zesInfoLogInstanceDeleteExt` | Info Log | 0.1.4 | Linux: Requires superuser | `libtracefs` | None |

RELEASE NOTES
-------------
Version 0.1.4
- **New API Functions:**
  - Driver: `zesDriverGetProperties`, `zesDriverGetExtensionProperties`, `zesDriverGetExtensionFunctionAddress`, `zesDriverEventListenEx`, `zesDriverEventRegisterExt`, `zesDriverEventListenExt`
  - Device: `zesDeviceGetState`, `zesDeviceResetExt`, `zesDeviceEventRegister`, `zesDeviceGetHealthStatusExt`, `zesDeviceSetHealthStatusExt`
  - Firmware: `zesDeviceEnumFirmwares`, `zesFirmwareGetProperties`
  - Power: `zesPowerGetUsage`, `zesPowerGetLimitsExt2`, `zesPowerSetLimitsExt2`, `zesPowerGetEnergyThreshold`, `zesPowerSetEnergyThreshold`
  - Temperature: `zesTemperatureSetConfig`
  - Engine: `zesEngineGetActivityExt`
  - Standby: `zesDeviceEnumStandbyDomains`, `zesStandbyGetProperties`, `zesStandbyGetMode`, `zesStandbySetMode`
  - VF Management (experimental): `zesDeviceEnumEnabledVFExp`, `zesVFManagementGetVFCapabilitiesExp2`, `zesVFManagementGetVFEngineUtilizationExp2`, `zesVFManagementGetVFMemoryUtilizationExp2`
  - RAS: `zesDeviceEnumRasErrorSets`, `zesRasGetProperties`, `zesRasGetSupportedCategoriesExp`, `zesRasGetStateExp2`, `zesRasGetConfigExp`, `zesRasSetConfigExp`, `zesRasClearStateExp`
  - Info Log: `zesDriverEnumInfoLogsExt`, `zesInfoLogGetPropertiesExt`, `zesInfoLogCreateInstanceExt`, `zesInfoLogInstanceReadWithMetadataExt`, `zesInfoLogInstancePeekWithMetadataExt`, `zesInfoLogInstanceDeleteExt`
- **Documentation:**
  - Added Linux Dependencies and Windows Dependencies columns to the SUPPORTED APIs table

Version 0.1.3
- **Packaging:**
  - `pyzes` is now a package (`pyzes/__init__.py`) instead of a single `pyzes.py` module. `import pyzes` and `from pyzes import *` are unchanged.
  - Example scripts moved from the top-level `examples` package to `pyzes.examples`, so installing pyzes no longer puts an `examples` package in `site-packages` that conflicts with other projects.
  - Run the examples with `python3 -m pyzes.examples.pyzes_example` and `python3 -m pyzes.examples.pyzes_black_box_test` (previously `python3 -m examples.<name>`).

Version 0.1.2
- **New API Functions:**
  - `zesDevicePciGetProperties`, `zesDevicePciGetStats`, `zesDevicePciGetState`
  - `zesDeviceEccAvailable`, `zesDeviceEccConfigurable`, `zesDeviceGetEccState`, `zesDeviceSetEccState`
  - `zesPowerGetProperties`, `zesPowerGetLimitsExt`, `zesPowerSetLimitsExt`
  - `zesFrequencyGetProperties`, `zesFrequencyGetAvailableClocks`, `zesFrequencyGetRange`, `zesFrequencySetRange`, `zesFrequencyGetThrottleTime`
- **Bug Fixes:**
  - Fixed ctypes structure definitions to correctly match L0 API specifications

Version 0.1.1
- Minor fixes: Removed unnecessary debug print statements

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

