#!/usr/bin/env python3
##
# Copyright (C) 2025 Intel Corporation
#
# SPDX-License-Identifier: MIT
#
##

##
# Python Black Box Test for pyzes.py - Level Zero Sysman Python Bindings
##

import argparse
import os
import sys
from ctypes import *

# Add the source directory to Python path so we can import pyzes
script_dir = os.path.dirname(os.path.abspath(__file__))
source_dir = os.path.join(script_dir, "..", "source")
source_dir = os.path.abspath(source_dir)
if source_dir not in sys.path:
    sys.path.insert(0, source_dir)

# Import the pyzes module
try:
    import pyzes as pz
except ImportError as e:
    print("Error: Could not import pyzes module")
    print(f"Import error: {e}")
    print(f"Make sure pyzes.py is in the source directory: {source_dir}")
    print(f"Current working directory: {os.getcwd()}")
    print(f"Script directory: {script_dir}")
    print(f"Source directory: {source_dir}")
    sys.exit(1)


# Setup environment and path for pyzes module
def setup_environment():
    """Setup Python path and environment for pyzes module"""
    # Get the directory where this script is located
    script_dir = os.path.dirname(os.path.abspath(__file__))

    # Add script directory to Python path if not already there
    if script_dir not in sys.path:
        sys.path.insert(0, script_dir)
        print(f"Added {script_dir} to Python path")

    # Set PYTHONPATH environment variable for completeness
    current_pythonpath = os.environ.get("PYTHONPATH", "")
    if script_dir not in current_pythonpath:
        if current_pythonpath:
            os.environ["PYTHONPATH"] = f"{script_dir}{os.pathsep}{current_pythonpath}"
        else:
            os.environ["PYTHONPATH"] = script_dir


setup_environment()

verbose = True


def check_rc(label, rc):
    """Check return code and exit on error"""
    if rc != pz.ZE_RESULT_SUCCESS:
        print(f"ERROR: {label} failed with ze_result_t={rc}")
        return False
    return True


def print_error(func_name, error_msg):
    """Print error message in a consistent format"""
    print(f"ERROR: {func_name}: {error_msg}")


def print_verbose(message):
    """Print message only if verbose mode is enabled"""
    if verbose:
        print(message)


def get_memory_type_string(mem_type):
    """Convert memory type enum to string"""
    type_map = {
        pz.ZES_MEM_TYPE_HBM: "ZES_MEM_TYPE_HBM",
        pz.ZES_MEM_TYPE_DDR: "ZES_MEM_TYPE_DDR",
        pz.ZES_MEM_TYPE_DDR3: "ZES_MEM_TYPE_DDR3",
        pz.ZES_MEM_TYPE_DDR4: "ZES_MEM_TYPE_DDR4",
        pz.ZES_MEM_TYPE_DDR5: "ZES_MEM_TYPE_DDR5",
        pz.ZES_MEM_TYPE_LPDDR: "ZES_MEM_TYPE_LPDDR",
        pz.ZES_MEM_TYPE_LPDDR3: "ZES_MEM_TYPE_LPDDR3",
        pz.ZES_MEM_TYPE_LPDDR4: "ZES_MEM_TYPE_LPDDR4",
        pz.ZES_MEM_TYPE_LPDDR5: "ZES_MEM_TYPE_LPDDR5",
        pz.ZES_MEM_TYPE_SRAM: "ZES_MEM_TYPE_SRAM",
        pz.ZES_MEM_TYPE_L1: "ZES_MEM_TYPE_L1",
        pz.ZES_MEM_TYPE_L3: "ZES_MEM_TYPE_L3",
        pz.ZES_MEM_TYPE_GRF: "ZES_MEM_TYPE_GRF",
        pz.ZES_MEM_TYPE_SLM: "ZES_MEM_TYPE_SLM",
        pz.ZES_MEM_TYPE_GDDR4: "ZES_MEM_TYPE_GDDR4",
        pz.ZES_MEM_TYPE_GDDR5: "ZES_MEM_TYPE_GDDR5",
        pz.ZES_MEM_TYPE_GDDR5X: "ZES_MEM_TYPE_GDDR5X",
        pz.ZES_MEM_TYPE_GDDR6: "ZES_MEM_TYPE_GDDR6",
        pz.ZES_MEM_TYPE_GDDR6X: "ZES_MEM_TYPE_GDDR6X",
        pz.ZES_MEM_TYPE_GDDR7: "ZES_MEM_TYPE_GDDR7",
    }
    return type_map.get(mem_type, f"UNKNOWN_TYPE_{mem_type}")


def get_memory_location_string(mem_loc):
    """Convert memory location enum to string"""
    loc_map = {
        pz.ZES_MEM_LOC_SYSTEM: "ZES_MEM_LOC_SYSTEM",
        pz.ZES_MEM_LOC_DEVICE: "ZES_MEM_LOC_DEVICE",
    }
    return loc_map.get(mem_loc, f"UNKNOWN_LOCATION_{mem_loc}")


def get_memory_health_string(mem_health):
    """Convert memory health enum to string"""
    health_map = {
        pz.ZES_MEM_HEALTH_UNKNOWN: "ZES_MEM_HEALTH_UNKNOWN",
        pz.ZES_MEM_HEALTH_OK: "ZES_MEM_HEALTH_OK",
        pz.ZES_MEM_HEALTH_DEGRADED: "ZES_MEM_HEALTH_DEGRADED",
        pz.ZES_MEM_HEALTH_CRITICAL: "ZES_MEM_HEALTH_CRITICAL",
        pz.ZES_MEM_HEALTH_REPLACE: "ZES_MEM_HEALTH_REPLACE",
    }
    return health_map.get(mem_health, f"UNKNOWN_HEALTH_{mem_health}")


def get_device_type_string(device_type):
    """Convert device type enum to string"""
    type_map = {
        pz.ZES_DEVICE_TYPE_GPU: "ZES_DEVICE_TYPE_GPU",
        pz.ZES_DEVICE_TYPE_CPU: "ZES_DEVICE_TYPE_CPU",
        pz.ZES_DEVICE_TYPE_FPGA: "ZES_DEVICE_TYPE_FPGA",
        pz.ZES_DEVICE_TYPE_MCA: "ZES_DEVICE_TYPE_MCA",
        pz.ZES_DEVICE_TYPE_VPU: "ZES_DEVICE_TYPE_VPU",
    }
    return type_map.get(device_type, f"UNKNOWN_DEVICE_TYPE_{device_type}")


def get_frequency_domain_string(freq_domain):
    """Convert frequency domain enum to string"""
    domain_map = {
        pz.ZES_FREQ_DOMAIN_GPU: "ZES_FREQ_DOMAIN_GPU",
        pz.ZES_FREQ_DOMAIN_MEMORY: "ZES_FREQ_DOMAIN_MEMORY",
        pz.ZES_FREQ_DOMAIN_MEDIA: "ZES_FREQ_DOMAIN_MEDIA",
    }
    return domain_map.get(freq_domain, f"UNKNOWN_FREQ_DOMAIN_{freq_domain}")


def get_throttle_reasons_string(throttle_reasons):
    """Convert throttle reason flags to human-readable string"""
    if throttle_reasons == 0:
        return "None (not throttled)"

    reasons = []
    if throttle_reasons & pz.ZES_FREQ_THROTTLE_REASON_FLAG_AVE_PWR_CAP:
        reasons.append("AVE_PWR_CAP")
    if throttle_reasons & pz.ZES_FREQ_THROTTLE_REASON_FLAG_BURST_PWR_CAP:
        reasons.append("BURST_PWR_CAP")
    if throttle_reasons & pz.ZES_FREQ_THROTTLE_REASON_FLAG_CURRENT_LIMIT:
        reasons.append("CURRENT_LIMIT")
    if throttle_reasons & pz.ZES_FREQ_THROTTLE_REASON_FLAG_THERMAL_LIMIT:
        reasons.append("THERMAL_LIMIT")
    if throttle_reasons & pz.ZES_FREQ_THROTTLE_REASON_FLAG_PSU_ALERT:
        reasons.append("PSU_ALERT")
    if throttle_reasons & pz.ZES_FREQ_THROTTLE_REASON_FLAG_SW_RANGE:
        reasons.append("SW_RANGE")
    if throttle_reasons & pz.ZES_FREQ_THROTTLE_REASON_FLAG_HW_RANGE:
        reasons.append("HW_RANGE")

    return " | ".join(reasons)


def get_temperature_sensor_string(temp_sensor):
    """Convert temperature sensor enum to string"""
    sensor_map = {
        pz.ZES_TEMP_SENSORS_GLOBAL: "ZES_TEMP_SENSORS_GLOBAL",
        pz.ZES_TEMP_SENSORS_GPU: "ZES_TEMP_SENSORS_GPU",
        pz.ZES_TEMP_SENSORS_MEMORY: "ZES_TEMP_SENSORS_MEMORY",
        pz.ZES_TEMP_SENSORS_GLOBAL_MIN: "ZES_TEMP_SENSORS_GLOBAL_MIN",
        pz.ZES_TEMP_SENSORS_GPU_MIN: "ZES_TEMP_SENSORS_GPU_MIN",
        pz.ZES_TEMP_SENSORS_MEMORY_MIN: "ZES_TEMP_SENSORS_MEMORY_MIN",
    }
    return sensor_map.get(temp_sensor, f"UNKNOWN_TEMP_SENSOR_{temp_sensor}")


def get_engine_type_string(engine_type):
    """Convert engine type enum to string"""
    type_map = {
        pz.ZES_ENGINE_GROUP_ALL: "ZES_ENGINE_GROUP_ALL",
        pz.ZES_ENGINE_GROUP_COMPUTE_ALL: "ZES_ENGINE_GROUP_COMPUTE_ALL",
        pz.ZES_ENGINE_GROUP_MEDIA_ALL: "ZES_ENGINE_GROUP_MEDIA_ALL",
        pz.ZES_ENGINE_GROUP_COPY_ALL: "ZES_ENGINE_GROUP_COPY_ALL",
        pz.ZES_ENGINE_GROUP_COMPUTE_SINGLE: "ZES_ENGINE_GROUP_COMPUTE_SINGLE",
        pz.ZES_ENGINE_GROUP_RENDER_SINGLE: "ZES_ENGINE_GROUP_RENDER_SINGLE",
        pz.ZES_ENGINE_GROUP_MEDIA_DECODE_SINGLE: "ZES_ENGINE_GROUP_MEDIA_DECODE_SINGLE",
        pz.ZES_ENGINE_GROUP_MEDIA_ENCODE_SINGLE: "ZES_ENGINE_GROUP_MEDIA_ENCODE_SINGLE",
        pz.ZES_ENGINE_GROUP_COPY_SINGLE: "ZES_ENGINE_GROUP_COPY_SINGLE",
        pz.ZES_ENGINE_GROUP_MEDIA_ENHANCEMENT_SINGLE: "ZES_ENGINE_GROUP_MEDIA_ENHANCEMENT_SINGLE",
        pz.ZES_ENGINE_GROUP_3D_SINGLE: "ZES_ENGINE_GROUP_3D_SINGLE",
        pz.ZES_ENGINE_GROUP_3D_RENDER_COMPUTE_ALL: "ZES_ENGINE_GROUP_3D_RENDER_COMPUTE_ALL",
        pz.ZES_ENGINE_GROUP_RENDER_ALL: "ZES_ENGINE_GROUP_RENDER_ALL",
        pz.ZES_ENGINE_GROUP_3D_ALL: "ZES_ENGINE_GROUP_3D_ALL",
        pz.ZES_ENGINE_GROUP_MEDIA_CODEC_SINGLE: "ZES_ENGINE_GROUP_MEDIA_CODEC_SINGLE",
    }
    return type_map.get(engine_type, f"UNKNOWN_ENGINE_TYPE_{engine_type}")


def initialize_sysman_and_get_devices():
    """Initialize Sysman and enumerate drivers/devices. Returns (drivers, driver_count, devices, device_count)."""
    if not initialize_sysman():
        return None, 0, None, 0

    # Get drivers
    driver_info = get_drivers()
    if driver_info is None:
        return None, 0, None, 0

    drivers, driver_count = driver_info

    if driver_count == 0:
        return drivers, driver_count, None, 0

    # Get devices for the first driver
    device_info = get_devices(drivers[0])
    if device_info is None:
        return drivers, driver_count, None, 0

    devices, device_count = device_info
    return drivers, driver_count, devices, device_count


def initialize_sysman():
    """Initialize the Sysman interface"""
    print_verbose("Initializing Sysman...")
    rc = pz.zesInit(0)
    if not check_rc("zesInit", rc):
        return False
    print_verbose("Sysman initialization successful")
    return True


def get_drivers():
    """Get all available drivers"""
    print_verbose("Getting driver count...")
    driver_count = c_uint32(0)
    rc = pz.zesDriverGet(byref(driver_count), None)
    if not check_rc("zesDriverGet(count)", rc):
        return None

    if driver_count.value == 0:
        print("No drivers found")
        return None

    print_verbose(f"Found {driver_count.value} driver(s)")

    # Allocate array for driver handles
    DriverArray = pz.zes_driver_handle_t * driver_count.value
    drivers = DriverArray()

    rc = pz.zesDriverGet(byref(driver_count), drivers)
    if not check_rc("zesDriverGet(handles)", rc):
        return None

    return drivers, driver_count.value


def get_devices(driver_handle):
    """Get all devices for a given driver"""
    print_verbose("Getting device count...")
    device_count = c_uint32(0)
    rc = pz.zesDeviceGet(driver_handle, byref(device_count), None)
    if not check_rc("zesDeviceGet(count)", rc):
        return None

    if device_count.value == 0:
        print("No devices found")
        return None

    print_verbose(f"Found {device_count.value} device(s)")

    # Allocate array for device handles
    DeviceArray = pz.zes_device_handle_t * device_count.value
    devices = DeviceArray()

    rc = pz.zesDeviceGet(driver_handle, byref(device_count), devices)
    if not check_rc("zesDeviceGet(handles)", rc):
        return None

    return devices, device_count.value


def test_global_operation(driver_handle, device_handle, device_index):
    """Test global device operations: properties retrieval, UUID mapping, and device processes state"""
    print(f"\n---- Device {device_index} Global Operations Test ----")

    # Test Device Properties
    print_verbose("=== Device Properties Test ===")

    # Initialize properties structure
    properties = pz.zes_device_properties_t()
    properties.stype = pz.ZES_STRUCTURE_TYPE_DEVICE_PROPERTIES
    properties.pNext = None

    rc = pz.zesDeviceGetProperties(device_handle, byref(properties))
    if not check_rc(f"zesDeviceGetProperties(device {device_index})", rc):
        return False

    print_verbose("Device Properties:")
    print_verbose(
        f"  Serial Number: {properties.serialNumber.decode('utf-8', errors='ignore')}"
    )
    print_verbose(
        f"  Board Number: {properties.boardNumber.decode('utf-8', errors='ignore')}"
    )
    print_verbose(
        f"  Brand Name: {properties.brandName.decode('utf-8', errors='ignore')}"
    )
    print_verbose(
        f"  Model Name: {properties.modelName.decode('utf-8', errors='ignore')}"
    )
    print_verbose(
        f"  Vendor Name: {properties.vendorName.decode('utf-8', errors='ignore')}"
    )
    print_verbose(
        f"  Driver Version: {properties.driverVersion.decode('utf-8', errors='ignore')}"
    )
    print_verbose(f"  Number of Subdevices: {properties.numSubdevices}")
    print_verbose(
        f"  Core Device Name: {properties.core.name.decode('utf-8', errors='ignore')}"
    )
    print_verbose(f"  Core Device Type: {get_device_type_string(properties.core.type)}")
    print_verbose(
        f"  Core UUID: {'-'.join(f'{properties.core.uuid.id[i]:02x}' for i in range(16))}"
    )
    print_verbose(f"  Vendor ID: 0x{properties.core.vendorId:04X}")
    print_verbose(f"  Device ID: 0x{properties.core.deviceId:04X}")

    # Test Subdevice Properties (Experimental API)
    print_verbose("\n=== Subdevice Properties Test (Experimental) ===")
    if properties.numSubdevices > 0:
        # First call to get count
        subdevice_count = c_uint32(0)
        rc = pz.zesDeviceGetSubDevicePropertiesExp(
            device_handle, byref(subdevice_count), None
        )
        if check_rc(
            f"zesDeviceGetSubDevicePropertiesExp(device {device_index}, count)", rc
        ):
            print_verbose(f"Number of subdevices: {subdevice_count.value}")

            if subdevice_count.value > 0:
                # Allocate array for subdevice properties
                SubdevicePropsArray = (
                    pz.zes_subdevice_exp_properties_t * subdevice_count.value
                )
                subdevice_props = SubdevicePropsArray()

                # Initialize each structure
                for i in range(subdevice_count.value):
                    subdevice_props[i].stype = (
                        pz.ZES_STRUCTURE_TYPE_SUBDEVICE_EXP_PROPERTIES
                    )
                    subdevice_props[i].pNext = None

                # Second call to get properties
                rc = pz.zesDeviceGetSubDevicePropertiesExp(
                    device_handle, byref(subdevice_count), subdevice_props
                )
                if check_rc(
                    f"zesDeviceGetSubDevicePropertiesExp(device {device_index}, properties)",
                    rc,
                ):
                    for i in range(subdevice_count.value):
                        prop = subdevice_props[i]
                        print_verbose(f"  Subdevice {i}:")
                        print_verbose(f"    Subdevice ID: {prop.subdeviceId}")
                        print_verbose(
                            f"    UUID: {'-'.join(f'{prop.uuid.id[j]:02x}' for j in range(16))}"
                        )
        else:
            print_verbose("Subdevice properties API not supported or failed")
    else:
        print_verbose("No subdevices present on this device")

    # Test UUID mapping using the properties we just retrieved
    print_verbose("\nUUID Mapping Test:")
    try:
        # Convert core UUID to zes_uuid_t
        core_uuid = pz.zes_uuid_t()
        for i in range(min(len(properties.core.uuid.id), len(core_uuid.id))):
            core_uuid.id[i] = properties.core.uuid.id[i]

        # Test UUID mapping
        mapped_device = pz.zes_device_handle_t()
        on_subdevice = pz.ze_bool_t()
        subdevice_id = c_uint32()

        ret = pz.zesDriverGetDeviceByUuidExp(
            driver_handle,
            core_uuid,
            byref(mapped_device),
            byref(on_subdevice),
            byref(subdevice_id),
        )

        if ret == pz.ZE_RESULT_SUCCESS:
            print_verbose("  UUID mapping successful")
            print_verbose(
                f"  Same handle: {mapped_device.value == device_handle.value}"
            )
            print_verbose(f"  On subdevice: {bool(on_subdevice.value)}")
            print_verbose(f"  Subdevice ID: {subdevice_id.value}")
        else:
            print_verbose(f"  UUID mapping failed with return code: {ret}")

    except Exception:
        print_verbose("  UUID mapping test failed with exception")

    # Test Device Processes
    print_verbose("\n=== Device Processes Test ===")

    process_count = c_uint32(0)
    rc = pz.zesDeviceProcessesGetState(device_handle, byref(process_count), None)
    if not check_rc(f"zesDeviceProcessesGetState(device {device_index}, count)", rc):
        return False

    if process_count.value == 0:
        print_verbose("No active processes found on this device")
    else:
        print_verbose(f"Found {process_count.value} active process(es)")

        # Allocate array for process states
        ProcessArray = pz.zes_process_state_t * process_count.value
        processes = ProcessArray()

        rc = pz.zesDeviceProcessesGetState(
            device_handle, byref(process_count), processes
        )
        if not check_rc(
            f"zesDeviceProcessesGetState(device {device_index}, handles)", rc
        ):
            return False

        for i in range(process_count.value):
            process = processes[i]
            print_verbose(f"  Process {i}:")
            print_verbose(f"    PID: {process.pid}")
            print_verbose(f"    Memory Size: {process.memSize} bytes")
            print_verbose(f"    Shared Memory Size: {process.sharedMemSize} bytes")
            print_verbose(f"    Engine Type Flags: 0x{process.engineType:08X}")
            print_verbose(f"    Subdevice ID: {process.subdeviceId}")

    return True


def test_device_processes(device_handle, device_index):
    """Test device processes state"""
    print(f"\n---- Device {device_index} Processes Test ----")

    process_count = c_uint32(0)
    rc = pz.zesDeviceProcessesGetState(device_handle, byref(process_count), None)
    if not check_rc(f"zesDeviceProcessesGetState(device {device_index}, count)", rc):
        return False

    if process_count.value == 0:
        print_verbose("No active processes found on this device")
        return True

    print_verbose(f"Found {process_count.value} active process(es)")

    # Allocate array for process states
    ProcessArray = pz.zes_process_state_t * process_count.value
    processes = ProcessArray()

    rc = pz.zesDeviceProcessesGetState(device_handle, byref(process_count), processes)
    if not check_rc(f"zesDeviceProcessesGetState(device {device_index}, handles)", rc):
        return False

    for i in range(process_count.value):
        process = processes[i]
        print_verbose(f"  Process {i}:")
        print_verbose(f"    PID: {process.pid}")
        print_verbose(f"    Memory Size: {process.memSize} bytes")
        print_verbose(f"    Shared Memory Size: {process.sharedMemSize} bytes")
        print_verbose(f"    Engine Type Flags: 0x{process.engineType:08X}")
        print_verbose(f"    Subdevice ID: {process.subdeviceId}")

    return True


def test_engine_modules(device_handle, device_index):
    """Test engine module enumeration and operations"""
    print(f"\n---- Device {device_index} Engine Modules Test ----")

    # Get engine module count
    engine_count = c_uint32(0)
    rc = pz.zesDeviceEnumEngineGroups(device_handle, byref(engine_count), None)
    if not check_rc(f"zesDeviceEnumEngineGroups(device {device_index}, count)", rc):
        return False

    if engine_count.value == 0:
        print_verbose("No engine modules found on this device")
        return True

    print_verbose(f"Found {engine_count.value} engine module(s)")

    # Allocate array for engine handles
    EngineArray = pz.zes_engine_handle_t * engine_count.value
    engine_handles = EngineArray()

    rc = pz.zesDeviceEnumEngineGroups(
        device_handle, byref(engine_count), engine_handles
    )
    if not check_rc(f"zesDeviceEnumEngineGroups(device {device_index}, handles)", rc):
        return False

    for iteration in range(10):
        print(f"  Iteration {iteration}")
        # Test each engine module
        for i in range(engine_count.value):
            print_verbose(f"\n  Engine Module {i}:")

            # Test engine properties
            props = pz.zes_engine_properties_t()
            props.stype = pz.ZES_STRUCTURE_TYPE_ENGINE_PROPERTIES
            props.pNext = None

            rc = pz.zesEngineGetProperties(engine_handles[i], byref(props))
            if not check_rc(f"zesEngineGetProperties(engine {i})", rc):
                continue

            print_verbose(f"      Type: {get_engine_type_string(props.type)}")
            if props.onSubdevice:
                print_verbose(f"      Subdevice ID: {props.subdeviceId}")

            engineStats = pz.zes_engine_stats_t()
            rc = pz.zesEngineGetActivity(engine_handles[i], byref(engineStats))
            if not check_rc(f"zesEngineGetActivity(engine {i})", rc):
                continue

            print_verbose("      Activity:")
            print_verbose(f"        Active Time: {engineStats.activeTime}")
            print_verbose(f"        Timestamp: {engineStats.timestamp}")

    return True


def test_memory_modules(device_handle, device_index):
    """Test memory module enumeration and operations"""
    print(f"\n---- Device {device_index} Memory Modules Test ----")

    # Get memory module count
    mem_count = c_uint32(0)
    rc = pz.zesDeviceEnumMemoryModules(device_handle, byref(mem_count), None)
    if not check_rc(f"zesDeviceEnumMemoryModules(device {device_index}, count)", rc):
        return False

    if mem_count.value == 0:
        print_verbose("No memory modules found on this device")
        return True

    print_verbose(f"Found {mem_count.value} memory module(s)")

    # Allocate array for memory handles
    MemoryArray = pz.zes_mem_handle_t * mem_count.value
    mem_handles = MemoryArray()

    rc = pz.zesDeviceEnumMemoryModules(device_handle, byref(mem_count), mem_handles)
    if not check_rc(f"zesDeviceEnumMemoryModules(device {device_index}, handles)", rc):
        return False

    # Test each memory module
    for i in range(mem_count.value):
        print_verbose(f"\n  Memory Module {i}:")

        # Test memory properties
        props = pz.zes_mem_properties_t()
        props.stype = pz.ZES_STRUCTURE_TYPE_MEM_PROPERTIES
        props.pNext = None

        rc = pz.zesMemoryGetProperties(mem_handles[i], byref(props))
        if not check_rc(f"zesMemoryGetProperties(memory {i})", rc):
            continue

        print_verbose("    Properties:")
        print_verbose(f"      Type: {get_memory_type_string(props.type)}")
        print_verbose(f"      Location: {get_memory_location_string(props.location)}")
        print_verbose(f"      Physical Size: {props.physicalSize} bytes")
        print_verbose(
            f"      Bus Width: {props.busWidth} bits"
            if props.busWidth != -1
            else "      Bus Width: Unknown"
        )
        print_verbose(
            f"      Num Channels: {props.numChannels}"
            if props.numChannels != -1
            else "      Num Channels: Unknown"
        )
        print_verbose(f"      On Subdevice: {bool(props.onSubdevice)}")
        if props.onSubdevice:
            print_verbose(f"      Subdevice ID: {props.subdeviceId}")

        # Test memory state
        state = pz.zes_mem_state_t()
        state.stype = pz.ZES_STRUCTURE_TYPE_MEM_STATE
        state.pNext = None

        rc = pz.zesMemoryGetState(mem_handles[i], byref(state))
        if not check_rc(f"zesMemoryGetState(memory {i})", rc):
            continue

        print_verbose("    State:")
        print_verbose(f"      Health: {get_memory_health_string(state.health)}")
        print_verbose(f"      Free: {state.free} bytes")
        print_verbose(f"      Size: {state.size} bytes")
        print_verbose(f"      Used: {state.size - state.free} bytes")
        if state.size > 0:
            usage_percent = ((state.size - state.free) / state.size) * 100
            print_verbose(f"      Usage: {usage_percent:.1f}%")

        # Test memory bandwidth
        bandwidth = pz.zes_mem_bandwidth_t()

        rc = pz.zesMemoryGetBandwidth(mem_handles[i], byref(bandwidth))
        if not check_rc(f"zesMemoryGetBandwidth(memory {i})", rc):
            continue

        print_verbose("    Bandwidth:")
        print_verbose(f"      Read Counter: {bandwidth.readCounter} bytes")
        print_verbose(f"      Write Counter: {bandwidth.writeCounter} bytes")
        print_verbose(f"      Max Bandwidth: {bandwidth.maxBandwidth} bytes/sec")
        print_verbose(f"      Timestamp: {bandwidth.timestamp} microseconds")

    return True


def test_power_module(device_handle, device_index):
    """Test power domain enumeration and energy counter operations"""
    print(f"\n---- Device {device_index} Power Domains Test ----")

    # Get power domain count
    power_count = c_uint32(0)
    rc = pz.zesDeviceEnumPowerDomains(device_handle, byref(power_count), None)
    if not check_rc(f"zesDeviceEnumPowerDomains(device {device_index}, count)", rc):
        return False

    if power_count.value == 0:
        print_verbose("No power domains found on this device")
        return True

    print_verbose(f"Found {power_count.value} power domain(s)")

    # Allocate array for power handles
    PowerArray = pz.zes_pwr_handle_t * power_count.value
    power_handles = PowerArray()

    rc = pz.zesDeviceEnumPowerDomains(device_handle, byref(power_count), power_handles)
    if not check_rc(f"zesDeviceEnumPowerDomains(device {device_index}, handles)", rc):
        return False

    # Test each power domain
    for i in range(power_count.value):
        print_verbose(f"\n  Power Domain {i}:")

        # Test power energy counter
        energy_counter = pz.zes_power_energy_counter_t()

        rc = pz.zesPowerGetEnergyCounter(power_handles[i], byref(energy_counter))
        if not check_rc(f"zesPowerGetEnergyCounter(power {i})", rc):
            continue

        print_verbose("    Energy Counter:")
        print_verbose(f"      Energy: {energy_counter.energy}")
        print_verbose(f"      Timestamp: {energy_counter.timestamp} microseconds")

        # Take a second reading after a small delay
        import time

        time.sleep(0.01)  # 10ms delay

        energy_counter2 = pz.zes_power_energy_counter_t()
        ret2 = pz.zesPowerGetEnergyCounter(power_handles[i], byref(energy_counter2))
        if ret2 == pz.ZE_RESULT_SUCCESS:
            energy_delta = energy_counter2.energy - energy_counter.energy
            time_delta = energy_counter2.timestamp - energy_counter.timestamp
            if time_delta > 0:
                print_verbose(
                    f"    Energy Delta: {energy_delta} over {time_delta} microseconds"
                )

    return True


def test_frequency_domains(device_handle, device_index):
    """Test frequency domain enumeration and state operations"""
    print(f"\n---- Device {device_index} Frequency Domains Test ----")

    # Get frequency domain count
    freq_count = c_uint32(0)
    rc = pz.zesDeviceEnumFrequencyDomains(device_handle, byref(freq_count), None)
    if not check_rc(f"zesDeviceEnumFrequencyDomains(device {device_index}, count)", rc):
        return False

    if freq_count.value == 0:
        print_verbose("No frequency domains found on this device")
        return True

    print_verbose(f"Found {freq_count.value} frequency domain(s)")

    # Allocate array for frequency handles
    FrequencyArray = pz.zes_freq_handle_t * freq_count.value
    freq_handles = FrequencyArray()

    rc = pz.zesDeviceEnumFrequencyDomains(
        device_handle, byref(freq_count), freq_handles
    )
    if not check_rc(
        f"zesDeviceEnumFrequencyDomains(device {device_index}, handles)", rc
    ):
        return False

    # Test each frequency domain
    for i in range(freq_count.value):
        print_verbose(f"\n  Frequency Domain {i}:")

        # Test frequency state
        freq_state = pz.zes_freq_state_t()
        freq_state.stype = pz.ZES_STRUCTURE_TYPE_FREQ_STATE
        freq_state.pNext = None

        rc = pz.zesFrequencyGetState(freq_handles[i], byref(freq_state))
        if not check_rc(f"zesFrequencyGetState(frequency {i})", rc):
            continue

        print_verbose("    Frequency State:")
        print_verbose(
            f"      Current Voltage: {freq_state.currentVoltage:.3f} V"
            if freq_state.currentVoltage >= 0
            else "      Current Voltage: Unknown"
        )
        print_verbose(
            f"      Requested Frequency: {freq_state.request:.1f} MHz"
            if freq_state.request >= 0
            else "      Requested Frequency: Unknown"
        )
        print_verbose(
            f"      TDP Frequency: {freq_state.tdp:.1f} MHz"
            if freq_state.tdp >= 0
            else "      TDP Frequency: Unknown"
        )
        print_verbose(
            f"      Efficient Frequency: {freq_state.efficient:.1f} MHz"
            if freq_state.efficient >= 0
            else "      Efficient Frequency: Unknown"
        )
        print_verbose(
            f"      Actual Frequency: {freq_state.actual:.1f} MHz"
            if freq_state.actual >= 0
            else "      Actual Frequency: Unknown"
        )
        print_verbose(
            f"      Throttle Reasons: {get_throttle_reasons_string(freq_state.throttleReasons)}"
        )

    return True


def test_temperature_sensors(device_handle, device_index):
    """Test temperature sensor enumeration and state operations"""
    print(f"\n---- Device {device_index} Temperature Sensors Test ----")

    # Get temperature sensor count
    temp_count = c_uint32(0)
    rc = pz.zesDeviceEnumTemperatureSensors(device_handle, byref(temp_count), None)
    if not check_rc(
        f"zesDeviceEnumTemperatureSensors(device {device_index}, count)", rc
    ):
        return False

    if temp_count.value == 0:
        print_verbose("No temperature sensors found on this device")
        return True

    print_verbose(f"Found {temp_count.value} temperature sensor(s)")

    # Allocate array for temperature handles
    TemperatureArray = pz.zes_temp_handle_t * temp_count.value
    temp_handles = TemperatureArray()

    rc = pz.zesDeviceEnumTemperatureSensors(
        device_handle, byref(temp_count), temp_handles
    )
    if not check_rc(
        f"zesDeviceEnumTemperatureSensors(device {device_index}, handles)", rc
    ):
        return False

    # Test each temperature sensor
    for i in range(temp_count.value):
        print_verbose(f"\n  Temperature Sensor {i}:")

        # Test temperature properties
        temp_props = pz.zes_temp_properties_t()
        temp_props.stype = pz.ZES_STRUCTURE_TYPE_TEMP_PROPERTIES
        temp_props.pNext = None

        rc = pz.zesTemperatureGetProperties(temp_handles[i], byref(temp_props))
        if not check_rc(f"zesTemperatureGetProperties(temperature {i})", rc):
            continue

        print_verbose("    Temperature Properties:")
        print_verbose(f"      Type: {get_temperature_sensor_string(temp_props.type)}")
        print_verbose(f"      On Subdevice: {bool(temp_props.onSubdevice)}")
        if temp_props.onSubdevice:
            print_verbose(f"      Subdevice ID: {temp_props.subdeviceId}")
        print_verbose(
            f"      Max Temperature: {temp_props.maxTemperature:.1f} °C"
            if temp_props.maxTemperature >= 0
            else "      Max Temperature: Unknown"
        )
        print_verbose(
            f"      Critical Temp Supported: {bool(temp_props.isCriticalTempSupported)}"
        )
        print_verbose(
            f"      Threshold 1 Supported: {bool(temp_props.isThreshold1Supported)}"
        )
        print_verbose(
            f"      Threshold 2 Supported: {bool(temp_props.isThreshold2Supported)}"
        )

        # Test temperature state - this is the main function we're demonstrating
        temperature = c_double(0.0)
        rc = pz.zesTemperatureGetState(temp_handles[i], byref(temperature))
        if not check_rc(f"zesTemperatureGetState(temperature {i})", rc):
            continue

        print_verbose(f"    Current Temperature: {temperature.value:.1f} °C")

        # Test temperature configuration if supported
        temp_config = pz.zes_temp_config_t()
        temp_config.stype = pz.ZES_STRUCTURE_TYPE_TEMP_CONFIG
        temp_config.pNext = None

        rc = pz.zesTemperatureGetConfig(temp_handles[i], byref(temp_config))
        if rc == pz.ZE_RESULT_SUCCESS:
            print_verbose("    Temperature Config:")
            print_verbose(f"      Critical Enabled: {bool(temp_config.enableCritical)}")
            print_verbose(
                f"      Threshold 1: {temp_config.threshold1:.1f} °C"
                if temp_config.threshold1 >= 0
                else "      Threshold 1: Not set"
            )
            print_verbose(
                f"      Threshold 2: {temp_config.threshold2:.1f} °C"
                if temp_config.threshold2 >= 0
                else "      Threshold 2: Not set"
            )
        else:
            print_verbose(f"    Temperature Config: Not available (rc={rc})")

    return True


def run_all_tests():
    """Run all black box tests"""
    print("=== Python Level Zero Sysman Black Box Test ===")

    # Get drivers
    driver_info = get_drivers()
    if driver_info is None:
        return False

    drivers, driver_count = driver_info

    # Test each driver
    for driver_idx in range(driver_count):
        print(f"\n=== Driver {driver_idx} Tests ===")

        # Get devices for this driver
        device_info = get_devices(drivers[driver_idx])
        if device_info is None:
            print(f"No devices found for driver {driver_idx}")
            continue

        devices, device_count = device_info

        # Test each device
        for device_idx in range(device_count):
            print(f"\n--- Device {device_idx} ---")

            # Test global device operations (properties and processes)
            test_global_operation(drivers[driver_idx], devices[device_idx], device_idx)

            # Test memory modules
            test_memory_modules(devices[device_idx], device_idx)

            # Test power domains
            test_power_module(devices[device_idx], device_idx)

            # Test frequency domains
            test_frequency_domains(devices[device_idx], device_idx)

            # Test temperature sensors
            test_temperature_sensors(devices[device_idx], device_idx)

            # Test engine modules
            test_engine_modules(devices[device_idx], device_idx)

    print("\n=== Test Completed ===")
    return True


def main():
    """Main function"""
    parser = argparse.ArgumentParser(
        description="Python Level Zero Sysman Black Box Test",
        epilog="""Examples:
  %(prog)s -a                 # Run all tests
  %(prog)s -m                 # Memory tests only
  %(prog)s -g                 # Global operations (device properties and processes) only
  %(prog)s -p                 # Power tests only
  %(prog)s -f                 # Frequency tests only
  %(prog)s -t                 # Temperature tests only
  %(prog)s -e                 # Engine tests only
  %(prog)s -h                 # Show help message""",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )

    parser.add_argument("-a", "--all", action="store_true", help="Run all tests")
    parser.add_argument(
        "-m", "--memory", action="store_true", help="Run only memory-related tests"
    )
    parser.add_argument(
        "-g",
        "--global",
        action="store_true",
        help="Run only global operations (device properties and processes)",
    )
    parser.add_argument(
        "-p", "--power", action="store_true", help="Run only power-related tests"
    )
    parser.add_argument(
        "-f",
        "--frequency",
        action="store_true",
        help="Run only frequency-related tests",
    )
    parser.add_argument(
        "-t",
        "--temperature",
        action="store_true",
        help="Run only temperature sensor tests",
    )
    parser.add_argument(
        "--version",
        action="version",
        version="Python Level Zero Sysman Black Box Test v1.0",
    )
    parser.add_argument("-e", "--engine", action="store_true", help="Run engine tests ")

    args = parser.parse_args()

    # Check if any specific test is requested
    specific_test = (
        args.memory
        or getattr(args, "global", False)
        or args.power
        or args.frequency
        or args.temperature
        or args.engine
        or args.all
    )

    # If no arguments provided, show help and exit
    if not specific_test:
        parser.print_help()
        return 0

    # Initialize Sysman and get devices
    drivers, driver_count, devices, device_count = initialize_sysman_and_get_devices()
    try:
        if args.all:
            # Run all tests
            success = run_all_tests()
        else:
            # Run specific tests
            print("=== Python Level Zero Sysman Selective Black Box Test ===")

            if not drivers or driver_count == 0:
                print("No drivers available for testing")
                return 1

            if not devices or device_count == 0:
                print("No devices available for testing")
                return 1

            # Run selected tests on all devices
            for device_idx in range(device_count):
                if getattr(args, "global", False):
                    test_global_operation(drivers[0], devices[device_idx], device_idx)

                if args.memory:
                    test_memory_modules(devices[device_idx], device_idx)

                if args.engine:
                    test_engine_modules(devices[device_idx], device_idx)

                if args.power:
                    test_power_module(devices[device_idx], device_idx)

                if args.frequency:
                    test_frequency_domains(devices[device_idx], device_idx)

                if args.temperature:
                    test_temperature_sensors(devices[device_idx], device_idx)

            success = True

        return 0 if success else 1

    except Exception as e:
        print(f"Unhandled exception: {e}")
        return 1


if __name__ == "__main__":
    sys.exit(main())
