##
# Copyright (C) 2026 Intel Corporation
#
# SPDX-License-Identifier: MIT
#
##

##
# Python bindings for the libze_intel_gpu.so / ze_intel_gpu.dll library
##

import sys
import threading
from ctypes import *
from typing import Any, Dict

libLoadLock = threading.Lock()
gpuLib = None


class _PrintableStructure(Structure):
    """
    Abstract class that produces nicer __str__ output than ctypes.Structure.
    e.g. instead of:
      >>> print str(obj)
      <class_name object at 0x7fdf82fef9e0>
    this class will print
      class_name(field_name: formatted_value, field_name: formatted_value)

    _fmt_ dictionary of <str _field_ name> -> <str format>
    e.g. class that has _field_ 'hex_value', c_uint could be formatted with
      _fmt_ = {"hex_value" : "%08X"}
    to produce nicer output.
    Default fomratting string for all fields can be set with key "<default>" like:
      _fmt_ = {"<default>" : "%d MHz"} # e.g all values are numbers in MHz.
    If not set it's assumed to be just "%s"

    Exact format of returned str from this class is subject to change in the future.
    """

    _fmt_: Dict[str, str] = {}

    def __str__(self):
        result = []
        for x in self._fields_:
            key = x[0]
            value = getattr(self, key)
            fmt = "%s"
            if key in self._fmt_:
                fmt = self._fmt_[key]
            elif "<default>" in self._fmt_:
                fmt = self._fmt_["<default>"]
            result.append(("%s: " + fmt) % (key, value))
        return self.__class__.__name__ + "(" + ", ".join(result) + ")"


def _LoadZeLibrary():
    global gpuLib
    if gpuLib is not None:
        return

    libLoadLock.acquire()
    try:
        # ensure library was loaded
        if gpuLib is not None:
            return
        # load the library
        libName = "ze_loader"
        if sys.platform.startswith("linux"):
            print("Loading Linux library")
            libName = "/usr/lib/x86_64-linux-gnu/lib" + libName + ".so.1"
        else:
            print("Loading Windows library")
            # Try multiple common locations for Windows Intel GPU drivers
            import os

            possible_paths = [
                # Try system PATH first
                libName + "64.dll",
                # Common Intel GPU driver locations
                r"C:\Windows\System32\DriverStore\FileRepository\iigd_dch.inf_amd64_*\ze_intel_gpu64.dll",
                r"C:\Windows\System32\DriverStore\FileRepository\igdlh64.inf_amd64_*\ze_intel_gpu64.dll",
                # Try current directory
                "ze_intel_gpu64.dll",
            ]

            library_loaded = False
            for path in possible_paths:
                try:
                    if "*" in path:
                        # Handle wildcard paths for driver store
                        import glob

                        matching_paths = glob.glob(path)
                        for match_path in matching_paths:
                            try:
                                print(f"Trying: {match_path}")
                                gpuLib = CDLL(match_path)
                                library_loaded = True
                                print(f"Successfully loaded: {match_path}")
                                break
                            except Exception as e:
                                print(f"Failed to load {match_path}: {e}")
                                continue
                    else:
                        if os.path.exists(path):
                            print(f"Trying: {path}")
                            gpuLib = CDLL(path)
                            library_loaded = True
                            print(f"Successfully loaded: {path}")
                            break
                        else:
                            print(f"Trying: {path}")
                            gpuLib = CDLL(path)
                            library_loaded = True
                            print(f"Successfully loaded: {path}")
                            break
                except Exception as e:
                    print(f"Failed to load {path}: {e}")
                    continue

                if library_loaded:
                    break

            if not library_loaded:
                raise Exception(
                    f"Failed to load Intel GPU library. Tried paths: {possible_paths}"
                )

        if sys.platform.startswith("linux"):
            gpuLib = CDLL(libName)

        if gpuLib is None:
            raise Exception("Failed to load library: " + str(libName))
    finally:
        # lock is always freed
        libLoadLock.release()


_LoadZeLibrary()


class zes_driver_handle_t(c_void_p):
    pass


class zes_device_handle_t(c_void_p):
    pass


class zes_mem_handle_t(c_void_p):
    pass


class zes_pwr_handle_t(c_void_p):
    pass


class zes_freq_handle_t(c_void_p):
    pass


class zes_temp_handle_t(c_void_p):
    pass


class zes_engine_handle_t(c_void_p):
    pass


##

ze_bool_t = c_uint32
ze_device_property_flags_t = c_uint32
zes_engine_type_flags_t = c_uint32
zes_device_property_flags_t = c_uint32

ze_device_type_t = c_int32
ZE_DEVICE_TYPE_GPU = 1
ZE_DEVICE_TYPE_CPU = 2
ZE_DEVICE_TYPE_FPGA = 3
ZE_DEVICE_TYPE_MCA = 4
ZE_DEVICE_TYPE_VPU = 5
ZE_DEVICE_TYPE_FORCE_UINT32 = 0x7FFFFFFF

# Sysman device type enumeration (same values as ze_device_type_t)
zes_device_type_t = c_int32
ZES_DEVICE_TYPE_GPU = 1
ZES_DEVICE_TYPE_CPU = 2
ZES_DEVICE_TYPE_FPGA = 3
ZES_DEVICE_TYPE_MCA = 4
ZES_DEVICE_TYPE_VPU = 5
ZES_DEVICE_TYPE_FORCE_UINT32 = 0x7FFFFFFF

# Memory type enumeration
zes_mem_type_t = c_int32
ZES_MEM_TYPE_HBM = 0
ZES_MEM_TYPE_DDR = 1
ZES_MEM_TYPE_DDR3 = 2
ZES_MEM_TYPE_DDR4 = 3
ZES_MEM_TYPE_DDR5 = 4
ZES_MEM_TYPE_LPDDR = 5
ZES_MEM_TYPE_LPDDR3 = 6
ZES_MEM_TYPE_LPDDR4 = 7
ZES_MEM_TYPE_LPDDR5 = 8
ZES_MEM_TYPE_SRAM = 9
ZES_MEM_TYPE_L1 = 10
ZES_MEM_TYPE_L3 = 11
ZES_MEM_TYPE_GRF = 12
ZES_MEM_TYPE_SLM = 13
ZES_MEM_TYPE_GDDR4 = 14
ZES_MEM_TYPE_GDDR5 = 15
ZES_MEM_TYPE_GDDR5X = 16
ZES_MEM_TYPE_GDDR6 = 17
ZES_MEM_TYPE_GDDR6X = 18
ZES_MEM_TYPE_GDDR7 = 19
ZES_MEM_TYPE_FORCE_UINT32 = 0x7FFFFFFF

# Memory location enumeration
zes_mem_loc_t = c_int32
ZES_MEM_LOC_SYSTEM = 0
ZES_MEM_LOC_DEVICE = 1
ZES_MEM_LOC_FORCE_UINT32 = 0x7FFFFFFF

# Memory health enumeration
zes_mem_health_t = c_int32
ZES_MEM_HEALTH_UNKNOWN = 0
ZES_MEM_HEALTH_OK = 1
ZES_MEM_HEALTH_DEGRADED = 2
ZES_MEM_HEALTH_CRITICAL = 3
ZES_MEM_HEALTH_REPLACE = 4
ZES_MEM_HEALTH_FORCE_UINT32 = 0x7FFFFFFF

# Power domain enumeration
zes_power_domain_t = c_int32
ZES_POWER_DOMAIN_UNKNOWN = 0
ZES_POWER_DOMAIN_CARD = 1
ZES_POWER_DOMAIN_PACKAGE = 2
ZES_POWER_DOMAIN_STACK = 3
ZES_POWER_DOMAIN_MEMORY = 4
ZES_POWER_DOMAIN_GPU = 5
ZES_POWER_DOMAIN_FORCE_UINT32 = 0x7FFFFFFF

## Frequency domain enums ##
zes_freq_domain_t = c_int32
ZES_FREQ_DOMAIN_GPU = 0
ZES_FREQ_DOMAIN_MEMORY = 1
ZES_FREQ_DOMAIN_MEDIA = 2
ZES_FREQ_DOMAIN_FORCE_UINT32 = 0x7FFFFFFF

## Frequency throttle reason flags ##
zes_freq_throttle_reason_flags_t = c_uint32
ZES_FREQ_THROTTLE_REASON_FLAG_AVE_PWR_CAP = 1 << 0
ZES_FREQ_THROTTLE_REASON_FLAG_BURST_PWR_CAP = 1 << 1
ZES_FREQ_THROTTLE_REASON_FLAG_CURRENT_LIMIT = 1 << 2
ZES_FREQ_THROTTLE_REASON_FLAG_THERMAL_LIMIT = 1 << 3
ZES_FREQ_THROTTLE_REASON_FLAG_PSU_ALERT = 1 << 4
ZES_FREQ_THROTTLE_REASON_FLAG_SW_RANGE = 1 << 5
ZES_FREQ_THROTTLE_REASON_FLAG_HW_RANGE = 1 << 6
ZES_FREQ_THROTTLE_REASON_FLAG_FORCE_UINT32 = 0x7FFFFFFF

## Temperature sensor enums ##
zes_temp_sensors_t = c_int32
ZES_TEMP_SENSORS_GLOBAL = 0
ZES_TEMP_SENSORS_GPU = 1
ZES_TEMP_SENSORS_MEMORY = 2
ZES_TEMP_SENSORS_GLOBAL_MIN = 3
ZES_TEMP_SENSORS_GPU_MIN = 4
ZES_TEMP_SENSORS_MEMORY_MIN = 5
ZES_TEMP_SENSORS_FORCE_UINT32 = 0x7FFFFFFF

## Engine type enums ##
zes_engine_group_t = c_uint32
ZES_ENGINE_GROUP_ALL = 0
ZES_ENGINE_GROUP_COMPUTE_ALL = 1
ZES_ENGINE_GROUP_MEDIA_ALL = 2
ZES_ENGINE_GROUP_COPY_ALL = 3
ZES_ENGINE_GROUP_COMPUTE_SINGLE = 4
ZES_ENGINE_GROUP_RENDER_SINGLE = 5
ZES_ENGINE_GROUP_MEDIA_DECODE_SINGLE = 6
ZES_ENGINE_GROUP_MEDIA_ENCODE_SINGLE = 7
ZES_ENGINE_GROUP_COPY_SINGLE = 8
ZES_ENGINE_GROUP_MEDIA_ENHANCEMENT_SINGLE = 9
ZES_ENGINE_GROUP_3D_SINGLE = 10
ZES_ENGINE_GROUP_3D_RENDER_COMPUTE_ALL = 11
ZES_ENGINE_GROUP_RENDER_ALL = 12
ZES_ENGINE_GROUP_3D_ALL = 13
ZES_ENGINE_GROUP_MEDIA_CODEC_SINGLE = 14
ZES_ENGINE_GROUP_FORCE_UINT32 = 0x7FFFFFFF

ze_result_t = c_int32
ZE_RESULT_SUCCESS = 0
ZE_RESULT_NOT_READY = 1
ZE_RESULT_ERROR_DEVICE_LOST = 0x70000001
ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY = 0x70000002
ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY = 0x70000003
ZE_RESULT_ERROR_MODULE_BUILD_FAILURE = 0x70000004
ZE_RESULT_ERROR_MODULE_LINK_FAILURE = 0x70000005
ZE_RESULT_ERROR_DEVICE_REQUIRES_RESET = 0x70000006
ZE_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE = 0x70000007
ZE_RESULT_EXP_ERROR_DEVICE_IS_NOT_VERTEX = 0x7FF00001
ZE_RESULT_EXP_ERROR_VERTEX_IS_NOT_DEVICE = 0x7FF00002
ZE_RESULT_EXP_ERROR_REMOTE_DEVICE = 0x7FF00003
ZE_RESULT_EXP_ERROR_OPERANDS_INCOMPATIBLE = 0x7FF00004
ZE_RESULT_EXP_RTAS_BUILD_RETRY = 0x7FF00005
ZE_RESULT_EXP_RTAS_BUILD_DEFERRED = 0x7FF00006
ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS = 0x70010000
ZE_RESULT_ERROR_NOT_AVAILABLE = 0x70010001
ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE = 0x70020000
ZE_RESULT_WARNING_DROPPED_DATA = 0x70020001
ZE_RESULT_ERROR_UNINITIALIZED = 0x78000001
ZE_RESULT_ERROR_UNSUPPORTED_VERSION = 0x78000002
ZE_RESULT_ERROR_UNSUPPORTED_FEATURE = 0x78000003
ZE_RESULT_ERROR_INVALID_ARGUMENT = 0x78000004
ZE_RESULT_ERROR_INVALID_NULL_HANDLE = 0x78000005
ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE = 0x78000006
ZE_RESULT_ERROR_INVALID_NULL_POINTER = 0x78000007
ZE_RESULT_ERROR_INVALID_SIZE = 0x78000008
ZE_RESULT_ERROR_UNSUPPORTED_SIZE = 0x78000009
ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT = 0x7800000A
ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT = 0x7800000B
ZE_RESULT_ERROR_INVALID_ENUMERATION = 0x7800000C
ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION = 0x7800000D
ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT = 0x7800000E
ZE_RESULT_ERROR_INVALID_NATIVE_BINARY = 0x7800000F
ZE_RESULT_ERROR_INVALID_GLOBAL_NAME = 0x78000010
ZE_RESULT_ERROR_INVALID_KERNEL_NAME = 0x78000011
ZE_RESULT_ERROR_INVALID_FUNCTION_NAME = 0x78000012
ZE_RESULT_ERROR_INVALID_GROUP_SIZE_DIMENSION = 0x78000013
ZE_RESULT_ERROR_INVALID_GLOBAL_WIDTH_DIMENSION = 0x78000014
ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_INDEX = 0x78000015
ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_SIZE = 0x78000016
ZE_RESULT_ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE = 0x78000017
ZE_RESULT_ERROR_INVALID_MODULE_UNLINKED = 0x78000018
ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE = 0x78000019
ZE_RESULT_ERROR_OVERLAPPING_REGIONS = 0x7800001A
ZE_RESULT_WARNING_ACTION_REQUIRED = 0x7800001B
ZE_RESULT_ERROR_INVALID_KERNEL_HANDLE = 0x7800001C
ZE_RESULT_EXT_RTAS_BUILD_RETRY = 0x7800001D
ZE_RESULT_EXT_RTAS_BUILD_DEFERRED = 0x7800001E
ZE_RESULT_EXT_ERROR_OPERANDS_INCOMPATIBLE = 0x7800001F
ZE_RESULT_ERROR_SURVIVABILITY_MODE_DETECTED = 0x78000020
ZE_RESULT_ERROR_UNKNOWN = 0x7FFFFFFE
ZE_RESULT_FORCE_UINT32 = 0x7FFFFFFF

## Constants (subset) ##
ZE_MAX_DEVICE_UUID_SIZE = 16
ZES_STRING_PROPERTY_SIZE = 64  # from zes_api.h
ZE_MAX_DEVICE_NAME = 256  # from ze_api.h
ZES_MAX_UUID_SIZE = 16  # from zes_api.h (uuid size for zes_uuid_t)

# Structure type enum values
ZES_STRUCTURE_TYPE_DEVICE_PROPERTIES = 0x1
ZES_STRUCTURE_TYPE_DEVICE_EXT_PROPERTIES = 0x2D  # from zes_structure_type_t
ZES_STRUCTURE_TYPE_SUBDEVICE_EXP_PROPERTIES = 0x2E  # Experimental subdevice properties
ZES_STRUCTURE_TYPE_MEM_PROPERTIES = 0xB
ZES_STRUCTURE_TYPE_MEM_STATE = 0x1E
ZES_STRUCTURE_TYPE_FREQ_PROPERTIES = 0x9
ZES_STRUCTURE_TYPE_FREQ_STATE = 0x1B
ZES_STRUCTURE_TYPE_TEMP_PROPERTIES = 0xA
ZES_STRUCTURE_TYPE_TEMP_CONFIG = 0x1C
ZES_STRUCTURE_TYPE_ENGINE_PROPERTIES = 0x5


## Core ze_device UUID struct ##
class ze_device_uuid_t(_PrintableStructure):
    _fields_ = [("id", c_ubyte * ZE_MAX_DEVICE_UUID_SIZE)]


## Core ze_device_properties_t ##
class ze_device_properties_t(_PrintableStructure):
    _fields_ = [
        ("stype", c_int32),
        ("pNext", c_void_p),
        ("type", ze_device_type_t),
        ("vendorId", c_uint32),
        ("deviceId", c_uint32),
        ("flags", ze_device_property_flags_t),
        ("subdeviceId", c_uint32),
        ("coreClockRate", c_uint32),
        ("maxMemAllocSize", c_uint64),
        ("maxHardwareContexts", c_uint32),
        ("maxCommandQueuePriority", c_uint32),
        ("numThreadsPerEU", c_uint32),
        ("physicalEUSimdWidth", c_uint32),
        ("numEUsPerSubslice", c_uint32),
        ("numSubslicesPerSlice", c_uint32),
        ("numSlices", c_uint32),
        ("timerResolution", c_uint64),
        ("timestampValidBits", c_uint32),
        ("kernelTimestampValidBits", c_uint32),
        ("uuid", ze_device_uuid_t),
        ("name", c_char * ZE_MAX_DEVICE_NAME),
    ]


## Sysman zes_device_properties_t ##
class zes_device_properties_t(_PrintableStructure):
    _fields_ = [
        ("stype", c_int32),
        ("pNext", c_void_p),
        ("core", ze_device_properties_t),
        ("numSubdevices", c_uint32),
        ("serialNumber", c_char * ZES_STRING_PROPERTY_SIZE),
        ("boardNumber", c_char * ZES_STRING_PROPERTY_SIZE),
        ("brandName", c_char * ZES_STRING_PROPERTY_SIZE),
        ("modelName", c_char * ZES_STRING_PROPERTY_SIZE),
        ("vendorName", c_char * ZES_STRING_PROPERTY_SIZE),
        ("driverVersion", c_char * ZES_STRING_PROPERTY_SIZE),
    ]


## Sysman zes_process_state_t ##
class zes_process_state_t(_PrintableStructure):
    _fields_ = [
        ("pid", c_uint32),
        ("command", c_char * ZES_STRING_PROPERTY_SIZE),
        ("memSize", c_uint64),  # in bytes
        ("sharedMemSize", c_uint64),  # in bytes
        ("engineType", zes_engine_type_flags_t),
        ("subdeviceId", c_uint32),
    ]
    _fmt_ = {"memSize": "%d bytes", "sharedMemSize": "%d bytes"}


## Sysman zes_uuid_t ##
class zes_uuid_t(_PrintableStructure):
    _fields_ = [("id", c_ubyte * ZES_MAX_UUID_SIZE)]


## Sysman zes_device_ext_properties_t (extension) ##
class zes_device_ext_properties_t(_PrintableStructure):
    _fields_ = [
        ("stype", c_int32),  # ZES_STRUCTURE_TYPE_DEVICE_EXT_PROPERTIES
        ("pNext", c_void_p),  # optional chain
        ("uuid", zes_uuid_t),  # same as core/sysman device UUID
        ("type", zes_device_type_t),  # zes_device_type_t (enum)
        ("flags", zes_device_property_flags_t),  # zes_device_property_flags_t
    ]


## Sysman zes_subdevice_exp_properties_t (experimental extension) ##
class zes_subdevice_exp_properties_t(_PrintableStructure):
    _fields_ = [
        ("stype", c_int32),  # ZES_STRUCTURE_TYPE_SUBDEVICE_EXP_PROPERTIES
        ("pNext", c_void_p),  # optional chain
        ("subdeviceId", c_uint32),  # Sub-device ID
        ("uuid", zes_uuid_t),  # Sub-device UUID
    ]


## Memory structures ##
class zes_mem_properties_t(_PrintableStructure):
    _fields_ = [
        ("stype", c_int32),  # ZES_STRUCTURE_TYPE_MEM_PROPERTIES
        ("pNext", c_void_p),  # optional chain
        ("type", zes_mem_type_t),  # memory type
        ("onSubdevice", ze_bool_t),  # is on subdevice
        ("subdeviceId", c_uint32),  # subdevice ID
        ("location", zes_mem_loc_t),  # memory location
        ("physicalSize", c_uint64),  # physical memory size in bytes
        ("busWidth", c_int32),  # memory bus width (-1 if unknown)
        ("numChannels", c_int32),  # number of memory channels (-1 if unknown)
    ]
    _fmt_ = {
        "physicalSize": "%d bytes",
        "busWidth": "%d bits",
        "numChannels": "%d channels",
    }


class zes_mem_state_t(_PrintableStructure):
    _fields_ = [
        ("stype", c_int32),  # ZES_STRUCTURE_TYPE_MEM_STATE
        ("pNext", c_void_p),  # optional chain (const void*)
        ("health", zes_mem_health_t),  # memory health status
        ("free", c_uint64),  # free memory in bytes
        ("size", c_uint64),  # total allocatable memory in bytes
    ]
    _fmt_ = {"free": "%d bytes", "size": "%d bytes"}


class zes_mem_bandwidth_t(_PrintableStructure):
    _fields_ = [
        ("readCounter", c_uint64),  # total bytes read from memory
        ("writeCounter", c_uint64),  # total bytes written to memory
        ("maxBandwidth", c_uint64),  # current maximum bandwidth in bytes/sec
        ("timestamp", c_uint64),  # timestamp in microseconds
    ]
    _fmt_ = {
        "readCounter": "%d bytes",
        "writeCounter": "%d bytes",
        "maxBandwidth": "%d bytes/sec",
    }


## Power structures ##
class zes_power_energy_counter_t(_PrintableStructure):
    _fields_ = [
        ("energy", c_uint64),  # monotonic energy counter in microjoules
        ("timestamp", c_uint64),  # microsecond timestamp when energy was captured
    ]
    _fmt_ = {"energy": "%d", "timestamp": "%d microseconds"}


## Frequency structures ##
class zes_freq_state_t(_PrintableStructure):
    _fields_ = [
        ("stype", c_int32),  # ZES_STRUCTURE_TYPE_FREQ_STATE
        ("pNext", c_void_p),
        ("currentVoltage", c_double),  # current voltage in Volts
        ("request", c_double),  # current frequency request in MHz
        ("tdp", c_double),  # max frequency under current TDP in MHz
        ("efficient", c_double),  # efficient minimum frequency in MHz
        ("actual", c_double),  # resolved frequency in MHz
        ("throttleReasons", zes_freq_throttle_reason_flags_t),  # throttle reasons
    ]
    _fmt_ = {
        "currentVoltage": "%.3f V",
        "request": "%.1f MHz",
        "tdp": "%.1f MHz",
        "efficient": "%.1f MHz",
        "actual": "%.1f MHz",
        "throttleReasons": "0x%08X",
    }


## Temperature structures ##
class zes_temp_properties_t(_PrintableStructure):
    _fields_ = [
        ("stype", c_int32),  # ZES_STRUCTURE_TYPE_TEMP_PROPERTIES
        ("pNext", c_void_p),
        ("type", zes_temp_sensors_t),  # temperature sensor type
        ("onSubdevice", ze_bool_t),  # is on subdevice
        ("subdeviceId", c_uint32),  # subdevice ID
        ("maxTemperature", c_double),  # maximum temperature in degrees Celsius
        ("isCriticalTempSupported", ze_bool_t),  # is critical temperature supported
        ("isThreshold1Supported", ze_bool_t),  # is threshold 1 supported
        ("isThreshold2Supported", ze_bool_t),  # is threshold 2 supported
    ]
    _fmt_ = {"maxTemperature": "%.1f °C"}


class zes_temp_config_t(_PrintableStructure):
    _fields_ = [
        ("stype", c_int32),  # ZES_STRUCTURE_TYPE_TEMP_CONFIG
        ("pNext", c_void_p),
        ("enableCritical", ze_bool_t),  # enable critical temperature event
        ("threshold1", c_double),  # threshold 1 in degrees Celsius
        ("threshold2", c_double),  # threshold 2 in degrees Celsius
    ]
    _fmt_ = {"threshold1": "%.1f °C", "threshold2": "%.1f °C"}


## Engine structures ##


class zes_engine_properties_t(_PrintableStructure):
    _fields_ = [
        ("stype", c_int32),  # ZES_STRUCTURE_TYPE_ENGINE_PROPERTIES
        ("pNext", c_void_p),
        ("type", zes_engine_group_t),  # engine type
        ("onSubdevice", ze_bool_t),  # is on subdevice
        ("subdeviceId", c_uint32),  # subdevice ID
    ]
    _fmt_ = {"type": "0x%08X"}


class zes_engine_stats_t(_PrintableStructure):
    _fields_ = [
        ("activeTime", c_uint64),  # active time
        ("timestamp", c_uint64),  # timestamp
    ]
    _fmt_ = {"activeTime": "%d", "timestamp": "%d"}


## Function access ##
_getFunctionPointerList: Dict[str, Any] = dict()


def getFunctionPointerList(name):
    if name in _getFunctionPointerList:
        return _getFunctionPointerList[name]

    libLoadLock.acquire()
    try:
        # ensure library was loaded
        if gpuLib is None:
            raise Exception("Library not loaded")
        else:
            _getFunctionPointerList[name] = getattr(gpuLib, name)
            return _getFunctionPointerList[name]
    finally:
        # lock is always freed
        libLoadLock.release()


## function wrappers ##
def zesInit(flags: int):
    funcPtr = getFunctionPointerList("zesInit")
    funcPtr.argtypes = [c_uint32]
    funcPtr.restype = ze_result_t
    retVal = funcPtr(flags)
    return retVal


def zesDriverGet(pCount, phDrivers):
    """Wraps:
    ze_result_t zesDriverGet(uint32_t* pCount, zes_driver_handle_t* phDrivers)
    pCount: POINTER(c_uint32)
    phDrivers: POINTER(zes_driver_handle_t) or None
    """
    funcPtr = getFunctionPointerList("zesDriverGet")
    funcPtr.argtypes = [POINTER(c_uint32), POINTER(zes_driver_handle_t)]
    funcPtr.restype = ze_result_t
    retVal = funcPtr(pCount, phDrivers)
    return retVal


def zesDeviceGet(hDriver, pCount, phDevices):
    """Wraps:
    ze_result_t zesDeviceGet(zes_driver_handle_t hDriver, uint32_t* pCount, zes_device_handle_t* phDevices)
    hDriver: driver handle (void*)
    pCount: POINTER(c_uint32)
    phDevices: POINTER(zes_device_handle_t) or None
    """
    funcPtr = getFunctionPointerList("zesDeviceGet")
    funcPtr.argtypes = [
        zes_driver_handle_t,
        POINTER(c_uint32),
        POINTER(zes_device_handle_t),
    ]
    funcPtr.restype = ze_result_t
    retVal = funcPtr(hDriver, pCount, phDevices)
    return retVal


def zesDeviceGetProperties(hDevice, pProperties):
    """Wraps API:
    ze_result_t zesDeviceGetProperties(zes_device_handle_t hDevice, zes_device_properties_t* pProperties)

    Parameters:
      hDevice: device handle
      pProperties: POINTER(zes_device_properties_t) - properties structure to fill
    Returns:
      ze_result_t - return code only, properties are filled into pProperties
    """
    funcPtr = getFunctionPointerList("zesDeviceGetProperties")
    funcPtr.argtypes = [zes_device_handle_t, POINTER(zes_device_properties_t)]
    funcPtr.restype = ze_result_t
    retVal = funcPtr(hDevice, pProperties)
    return retVal


def zesDeviceGetSubDevicePropertiesExp(hDevice, pCount, pSubdeviceProps):
    """Wraps API:
    ze_result_t zesDeviceGetSubDevicePropertiesExp(
        zes_device_handle_t hDevice,
        uint32_t* pCount,
        zes_subdevice_exp_properties_t* pSubdeviceProps)

    Parameters:
      hDevice: device handle
      pCount: POINTER(c_uint32) - pointer to count of subdevices
      pSubdeviceProps: POINTER(zes_subdevice_exp_properties_t) or None - array of subdevice properties
    Returns:
      ze_result_t - return code only, subdevice properties are filled into pSubdeviceProps
    """
    funcPtr = getFunctionPointerList("zesDeviceGetSubDevicePropertiesExp")
    funcPtr.argtypes = [
        zes_device_handle_t,
        POINTER(c_uint32),
        POINTER(zes_subdevice_exp_properties_t),
    ]
    funcPtr.restype = ze_result_t
    retVal = funcPtr(hDevice, pCount, pSubdeviceProps)
    return retVal


def zesDriverGetDeviceByUuidExp(
    hDriver, uuid: "zes_uuid_t", phDevice, onSubdevice, subdeviceId
):
    """Wraps API:
    ze_result_t zesDriverGetDeviceByUuidExp(
        zes_driver_handle_t hDriver,
        zes_uuid_t uuid,
        zes_device_handle_t *phDevice,
        ze_bool_t *onSubdevice,
        uint32_t *subdeviceId)

    Parameters:
      hDriver: driver handle
      uuid: instance of zes_uuid_t passed by value
      phDevice: POINTER(zes_device_handle_t)
      onSubdevice: POINTER(ze_bool_t)
      subdeviceId: POINTER(c_uint32)
    """
    funcPtr = getFunctionPointerList("zesDriverGetDeviceByUuidExp")
    funcPtr.argtypes = [
        zes_driver_handle_t,
        zes_uuid_t,
        POINTER(zes_device_handle_t),
        POINTER(ze_bool_t),
        POINTER(c_uint32),
    ]
    funcPtr.restype = ze_result_t
    retVal = funcPtr(hDriver, uuid, phDevice, onSubdevice, subdeviceId)
    return retVal


def zesDeviceProcessesGetState(hDevice, pCount, pProcesses):
    """Wraps API:
    ze_result_t zesDeviceProcessesGetState(
        zes_device_handle_t hDevice,
        uint32_t* pCount,
        zes_process_state_t* pProcesses)

    Parameters:
      hDevice: device handle
      pCount: POINTER(c_uint32)
      pProcesses: POINTER(zes_process_state_t) or None
    """
    funcPtr = getFunctionPointerList("zesDeviceProcessesGetState")
    funcPtr.argtypes = [
        zes_device_handle_t,
        POINTER(c_uint32),
        POINTER(zes_process_state_t),
    ]
    funcPtr.restype = ze_result_t
    retVal = funcPtr(hDevice, pCount, pProcesses)
    return retVal


## Memory management functions ##
def zesDeviceEnumMemoryModules(hDevice, pCount, phMemory):
    """Wraps API:
    ze_result_t zesDeviceEnumMemoryModules(
        zes_device_handle_t hDevice,
        uint32_t* pCount,
        zes_mem_handle_t* phMemory)

    Parameters:
      hDevice: device handle
      pCount: POINTER(c_uint32)
      phMemory: POINTER(zes_mem_handle_t) or None
    """
    funcPtr = getFunctionPointerList("zesDeviceEnumMemoryModules")
    funcPtr.argtypes = [
        zes_device_handle_t,
        POINTER(c_uint32),
        POINTER(zes_mem_handle_t),
    ]
    funcPtr.restype = ze_result_t
    retVal = funcPtr(hDevice, pCount, phMemory)
    return retVal


def zesMemoryGetProperties(hMemory, pProperties):
    """Wraps API:
    ze_result_t zesMemoryGetProperties(
        zes_mem_handle_t hMemory,
        zes_mem_properties_t* pProperties)

    Parameters:
      hMemory: memory handle
      pProperties: POINTER(zes_mem_properties_t) - properties structure to fill
    Returns:
      ze_result_t - return code only, properties are filled into pProperties
    """
    funcPtr = getFunctionPointerList("zesMemoryGetProperties")
    funcPtr.argtypes = [zes_mem_handle_t, POINTER(zes_mem_properties_t)]
    funcPtr.restype = ze_result_t
    retVal = funcPtr(hMemory, pProperties)
    return retVal


def zesMemoryGetState(hMemory, pState):
    """Wraps API:
    ze_result_t zesMemoryGetState(
        zes_mem_handle_t hMemory,
        zes_mem_state_t* pState)

    Parameters:
      hMemory: memory handle
      pState: POINTER(zes_mem_state_t) - state structure to fill
    Returns:
      ze_result_t - return code only, state is filled into pState
    """
    funcPtr = getFunctionPointerList("zesMemoryGetState")
    funcPtr.argtypes = [zes_mem_handle_t, POINTER(zes_mem_state_t)]
    funcPtr.restype = ze_result_t
    retVal = funcPtr(hMemory, pState)
    return retVal


def zesMemoryGetBandwidth(hMemory, pBandwidth):
    """Wraps API:
    ze_result_t zesMemoryGetBandwidth(
        zes_mem_handle_t hMemory,
        zes_mem_bandwidth_t* pBandwidth)

    Parameters:
      hMemory: memory handle
      pBandwidth: POINTER(zes_mem_bandwidth_t) - bandwidth structure to fill
    Returns:
      ze_result_t - return code only, bandwidth is filled into pBandwidth
    """
    funcPtr = getFunctionPointerList("zesMemoryGetBandwidth")
    funcPtr.argtypes = [zes_mem_handle_t, POINTER(zes_mem_bandwidth_t)]
    funcPtr.restype = ze_result_t
    retVal = funcPtr(hMemory, pBandwidth)
    return retVal


## Power management functions ##
def zesDeviceEnumPowerDomains(hDevice, pCount, phPower):
    """Wraps API:
    ze_result_t zesDeviceEnumPowerDomains(
        zes_device_handle_t hDevice,
        uint32_t* pCount,
        zes_pwr_handle_t* phPower)

    Parameters:
      hDevice: device handle
      pCount: POINTER(c_uint32)
      phPower: POINTER(zes_pwr_handle_t) or None
    """
    funcPtr = getFunctionPointerList("zesDeviceEnumPowerDomains")
    funcPtr.argtypes = [
        zes_device_handle_t,
        POINTER(c_uint32),
        POINTER(zes_pwr_handle_t),
    ]
    funcPtr.restype = ze_result_t
    retVal = funcPtr(hDevice, pCount, phPower)
    return retVal


def zesPowerGetEnergyCounter(hPower, pEnergy):
    """Wraps API:
    ze_result_t zesPowerGetEnergyCounter(
        zes_pwr_handle_t hPower,
        zes_power_energy_counter_t* pEnergy)

    Parameters:
      hPower: power handle
      pEnergy: POINTER(zes_power_energy_counter_t) - energy counter structure to fill
    Returns:
      ze_result_t - return code only, energy counter is filled into pEnergy
    """
    funcPtr = getFunctionPointerList("zesPowerGetEnergyCounter")
    funcPtr.argtypes = [zes_pwr_handle_t, POINTER(zes_power_energy_counter_t)]
    funcPtr.restype = ze_result_t

    retVal = funcPtr(hPower, pEnergy)
    return retVal


## Frequency module functions ##
def zesDeviceEnumFrequencyDomains(hDevice, pCount, phFrequency):
    """Wraps API:
    ze_result_t zesDeviceEnumFrequencyDomains(
        zes_device_handle_t hDevice,
        uint32_t* pCount,
        zes_freq_handle_t* phFrequency)

    Parameters:
      hDevice: device handle
      pCount: POINTER(c_uint32)
      phFrequency: POINTER(zes_freq_handle_t) or None
    """
    funcPtr = getFunctionPointerList("zesDeviceEnumFrequencyDomains")
    funcPtr.argtypes = [
        zes_device_handle_t,
        POINTER(c_uint32),
        POINTER(zes_freq_handle_t),
    ]
    funcPtr.restype = ze_result_t
    retVal = funcPtr(hDevice, pCount, phFrequency)
    return retVal


def zesFrequencyGetState(hFrequency, pState):
    """Wraps API:
    ze_result_t zesFrequencyGetState(
        zes_freq_handle_t hFrequency,
        zes_freq_state_t* pState)

    Parameters:
      hFrequency: frequency handle
      pState: POINTER(zes_freq_state_t) - state structure to fill
    Returns:
      ze_result_t - return code only, state is filled into pState
    """
    funcPtr = getFunctionPointerList("zesFrequencyGetState")
    funcPtr.argtypes = [zes_freq_handle_t, POINTER(zes_freq_state_t)]
    funcPtr.restype = ze_result_t

    retVal = funcPtr(hFrequency, pState)
    return retVal


## Temperature sensor functions ##
def zesDeviceEnumTemperatureSensors(hDevice, pCount, phTemperature):
    """Wraps API:
    ze_result_t zesDeviceEnumTemperatureSensors(
        zes_device_handle_t hDevice,
        uint32_t* pCount,
        zes_temp_handle_t* phTemperature)

    Parameters:
      hDevice: device handle
      pCount: POINTER(c_uint32)
      phTemperature: POINTER(zes_temp_handle_t) or None
    """
    funcPtr = getFunctionPointerList("zesDeviceEnumTemperatureSensors")
    funcPtr.argtypes = [
        zes_device_handle_t,
        POINTER(c_uint32),
        POINTER(zes_temp_handle_t),
    ]
    funcPtr.restype = ze_result_t
    retVal = funcPtr(hDevice, pCount, phTemperature)
    return retVal


def zesTemperatureGetProperties(hTemperature, pProperties):
    """Wraps API:
    ze_result_t zesTemperatureGetProperties(
        zes_temp_handle_t hTemperature,
        zes_temp_properties_t* pProperties)

    Parameters:
      hTemperature: temperature handle
      pProperties: POINTER(zes_temp_properties_t) - properties structure to fill
    Returns:
      ze_result_t - return code only, properties are filled into pProperties
    """
    funcPtr = getFunctionPointerList("zesTemperatureGetProperties")
    funcPtr.argtypes = [zes_temp_handle_t, POINTER(zes_temp_properties_t)]
    funcPtr.restype = ze_result_t

    retVal = funcPtr(hTemperature, pProperties)
    return retVal


def zesTemperatureGetConfig(hTemperature, pConfig):
    """Wraps API:
    ze_result_t zesTemperatureGetConfig(
        zes_temp_handle_t hTemperature,
        zes_temp_config_t* pConfig)

    Parameters:
      hTemperature: temperature handle
      pConfig: POINTER(zes_temp_config_t) - config structure to fill
    Returns:
      ze_result_t - return code only, config is filled into pConfig
    """
    funcPtr = getFunctionPointerList("zesTemperatureGetConfig")
    funcPtr.argtypes = [zes_temp_handle_t, POINTER(zes_temp_config_t)]
    funcPtr.restype = ze_result_t

    retVal = funcPtr(hTemperature, pConfig)
    return retVal


def zesTemperatureGetState(hTemperature, pTemperature):
    """Wraps API:
    ze_result_t zesTemperatureGetState(
        zes_temp_handle_t hTemperature,
        double* pTemperature)

    Parameters:
      hTemperature: temperature handle
      pTemperature: POINTER(c_double) - temperature value to fill in degrees Celsius
    Returns:
      ze_result_t - return code only, temperature is filled into pTemperature
    """
    funcPtr = getFunctionPointerList("zesTemperatureGetState")
    funcPtr.argtypes = [zes_temp_handle_t, POINTER(c_double)]
    funcPtr.restype = ze_result_t

    retVal = funcPtr(hTemperature, pTemperature)
    return retVal


## Engine functions ##


def zesDeviceEnumEngineGroups(hDevice, pCount, phEngine):
    """Wraps API:
    ze_result_t zesDeviceEnumEngineGroups(
        zes_device_handle_t hDevice,
        uint32_t* pCount,
        zes_engine_handle_t* phEngine)

    Parameters:
      hDevice: device handle
      pCount: POINTER(c_uint32)
      phEngine: POINTER(zes_engine_handle_t) or None
    """
    funcPtr = getFunctionPointerList("zesDeviceEnumEngineGroups")
    funcPtr.argtypes = [
        zes_device_handle_t,
        POINTER(c_uint32),
        POINTER(zes_engine_handle_t),
    ]
    funcPtr.restype = ze_result_t
    retVal = funcPtr(hDevice, pCount, phEngine)
    return retVal


def zesEngineGetProperties(hEngine, pProperties):
    """Wraps API:
    ze_result_t zesEngineGetProperties(
        zes_engine_handle_t hEngine,
        zes_engine_properties_t* pProperties)

    Parameters:
      hEngine: engine handle
      pProperties: POINTER(zes_engine_properties_t) - properties structure to fill
    Returns:
      ze_result_t - return code only, properties are filled into pProperties
    """
    funcPtr = getFunctionPointerList("zesEngineGetProperties")
    funcPtr.argtypes = [zes_engine_handle_t, POINTER(zes_engine_properties_t)]
    funcPtr.restype = ze_result_t

    retVal = funcPtr(hEngine, pProperties)
    return retVal


def zesEngineGetActivity(hEngine, pStats):
    """Wraps API:
    ze_result_t zesEngineGetActivity(
        zes_engine_handle_t hEngine,
        zes_engine_stats_t* pStats)

    Parameters:
      hEngine: engine handle
      pStats: POINTER(zes_engine_stats_t) - stats structure to fill
    Returns:
      ze_result_t - return code only, stats are filled into pStats
    """
    funcPtr = getFunctionPointerList("zesEngineGetActivity")
    funcPtr.argtypes = [zes_engine_handle_t, POINTER(zes_engine_stats_t)]
    funcPtr.restype = ze_result_t

    retVal = funcPtr(hEngine, pStats)
    return retVal
