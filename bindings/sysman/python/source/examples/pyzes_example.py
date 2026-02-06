#!/usr/bin/env python3
##
# Copyright (C) 2025 Intel Corporation
#
# SPDX-License-Identifier: MIT
#
##

"""
Run:
  python pyzes_example.py

If the Sysman APIs are not enabled you may need to export environment variables, e.g.:
  export ZES_ENABLE_SYSMAN=1
or just rely on calling zesInit(0) which initializes Sysman explicitly.

This script enumerates drivers, devices, prints basic properties, and tries the
experimental zesDriverGetDeviceByUuidExp mapping if exported by the runtime.
"""

import os
import sys
from ctypes import *

# Add the source directory to Python path so we can import pyzes
script_dir = os.path.dirname(os.path.abspath(__file__))
source_dir = os.path.join(script_dir, "..", "source")
source_dir = os.path.abspath(source_dir)
if source_dir not in sys.path:
    sys.path.insert(0, source_dir)

# Import the binding module (ensure its directory is on PYTHONPATH)
import pyzes
from pyzes import *

# Set environment variables to enable Sysman
os.environ["ZES_ENABLE_SYSMAN"] = "1"
os.environ["ZELLO_SYSMAN_USE_ZESINIT"] = "1"


#####################################################################################################################################
# Helper utilities ##
def zes_driver_get_device_by_uuid(hDriver, uuid_bytes: bytes):
    """Helper: given a 16-byte UUID (from core device properties), retrieve the corresponding Sysman device handle.
    Returns (result_code, device_handle, on_subdevice(bool), subdevice_id(int)).
    """
    if len(uuid_bytes) != ZES_MAX_UUID_SIZE:
        raise ValueError(
            f"uuid_bytes must be {ZES_MAX_UUID_SIZE} bytes, got {len(uuid_bytes)}"
        )
    uuid_struct = zes_uuid_t()
    for i, b in enumerate(uuid_bytes):
        uuid_struct.id[i] = b
    device_handle = zes_device_handle_t()
    on_sub = ze_bool_t(0)
    sub_id = c_uint32(0)
    rc = zesDriverGetDeviceByUuidExp(
        hDriver, uuid_struct, byref(device_handle), byref(on_sub), byref(sub_id)
    )
    return rc, device_handle, (on_sub.value != 0), sub_id.value


def allocate_device_properties():
    props = zes_device_properties_t()
    props.stype = ZES_STRUCTURE_TYPE_DEVICE_PROPERTIES
    props.pNext = None
    return props


def utf8(s):
    return (
        s.split(b"\0", 1)[0].decode("utf-8", "replace")
        if isinstance(s, (bytes, bytearray))
        else str(s)
    )


def format_device_properties(props: zes_device_properties_t) -> dict:
    return {
        "numSubdevices": props.numSubdevices,
        "serialNumber": utf8(props.serialNumber),
        "boardNumber": utf8(props.boardNumber),
        "brandName": utf8(props.brandName),
        "modelName": utf8(props.modelName),
        "vendorName": utf8(props.vendorName),
        "driverVersion": utf8(props.driverVersion),
        "coreName": utf8(props.core.name),
        "coreClockMHz": props.core.coreClockRate,
    }


def chain_device_properties_with_ext() -> (
    tuple[zes_device_properties_t, zes_device_ext_properties_t]
):
    """Allocate base Sysman device properties struct and chain an extension properties struct.
    Returns (base, ext). Caller must keep both alive until after the API call.
    Usage:
        base, ext = chain_device_properties_with_ext()
        rc = zesDeviceGetProperties(dev_handle, byref(base))
        if rc == ZE_RESULT_SUCCESS:
            print('Ext UUID:', bytes(ext.uuid.id))
    """
    base = allocate_device_properties()
    ext = zes_device_ext_properties_t()
    ext.stype = ZES_STRUCTURE_TYPE_DEVICE_EXT_PROPERTIES
    ext.pNext = None
    base.pNext = cast(pointer(ext), c_void_p)
    return base, ext


def handle_val(h):
    """Return integer value of a handle that may be ctypes or plain int."""
    return h.value if hasattr(h, "value") else h


def check_rc(label, rc):
    if rc != ZE_RESULT_SUCCESS:
        print(f"ERROR: {label} failed with ze_result_t={rc}")
        sys.exit(1)


# Shared initialization function - NO CODE DUPLICATION!
def initialize_sysman_and_get_devices():
    """Initialize Sysman and enumerate drivers/devices. Returns (hDriver, devices, dev_count)."""
    rc = pyzes.zesInit(0)
    check_rc("zesInit", rc)

    # -- Driver enumeration
    driver_count = c_uint32(0)
    rc = pyzes.zesDriverGet(byref(driver_count), None)
    check_rc("zesDriverGet(count)", rc)
    if driver_count.value == 0:
        print("No drivers found")
        return None, None, 0

    DriverArray = pyzes.zes_driver_handle_t * driver_count.value
    drivers = DriverArray()
    rc = pyzes.zesDriverGet(byref(driver_count), drivers)
    check_rc("zesDriverGet(handles)", rc)

    hDriver = drivers[0]
    # -- Device enumeration
    dev_count = c_uint32(0)
    rc = pyzes.zesDeviceGet(hDriver, byref(dev_count), None)
    check_rc("zesDeviceGet(count)", rc)
    if not hasattr(dev_count, "value"):
        print(f"WARNING: dev_count is plain int type={type(dev_count)}")
    if dev_count.value == 0:
        print("No devices found")
        return hDriver, None, 0

    DeviceArray = pyzes.zes_device_handle_t * dev_count.value
    devices = DeviceArray()
    rc = pyzes.zesDeviceGet(hDriver, byref(dev_count), devices)
    check_rc("zesDeviceGet(handles)", rc)
    if dev_count.value and not hasattr(devices[0], "value"):
        print(f"WARNING: Device handles are plain ints (type={type(devices[0])})")

    return hDriver, devices, dev_count.value


def enumerate_devices(hDriver, devices, dev_count):
    """Enumerate devices and show their properties."""
    if not devices or dev_count == 0:
        return

    print(f"Found {dev_count} device(s)\n")

    # -- Query properties for each device --
    for i in range(dev_count):
        # test for extension chaining
        props, ext = chain_device_properties_with_ext()
        rc = pyzes.zesDeviceGetProperties(devices[i], byref(props))
        check_rc(f"zesDeviceGetProperties(device {i})", rc)
        print(f"Extension properties flags: {ext.flags}")
        formatted = format_device_properties(props)
        print(f"Device {i}:")
        for k, v in formatted.items():
            print(f"  {k}: {v}")

        # Try experimental mapping API
        try:
            core_uuid_bytes = bytes(props.core.uuid.id)
            rc2, mapped_handle, on_sub, sub_id = zes_driver_get_device_by_uuid(
                hDriver, core_uuid_bytes
            )
            if rc2 == 0:
                same = handle_val(mapped_handle) == handle_val(devices[i])
                print(
                    f" zesDriverGetDeviceByUuidExp: SUCCESS same_handle={same} on_subdevice={on_sub} subdevice_id={sub_id}"
                )
            else:
                print(f" zesDriverGetDeviceByUuidExp: rc={rc2}")
        except NotImplementedError:
            print(" zesDriverGetDeviceByUuidExp not supported")
        print()


def demonstrate_memory_state(hDriver, devices, dev_count):
    print("=== Memory State ===")
    if not devices or dev_count == 0:
        return

    # For each device, enumerate memory modules and query their state
    for dev_idx in range(dev_count):
        print(f"\nDevice {dev_idx} Memory Modules:")
        hDevice = devices[dev_idx]

        # Step 1: Enumerate memory modules
        mem_count = c_uint32(0)
        rc = pyzes.zesDeviceEnumMemoryModules(hDevice, byref(mem_count), None)
        if rc != ZE_RESULT_SUCCESS:
            print(f"  Error enumerating memory modules: Return code {rc}")
            continue

        if mem_count.value == 0:
            print("  No memory modules found")
            continue

        # Allocate array for memory handles
        MemoryArray = pyzes.zes_mem_handle_t * mem_count.value
        memories = MemoryArray()
        rc = pyzes.zesDeviceEnumMemoryModules(hDevice, byref(mem_count), memories)
        check_rc(f"zesDeviceEnumMemoryModules(device {dev_idx})", rc)

        print(f"  Found {mem_count.value} memory module(s)")

        # Step 2: For each memory module, get properties and state
        for mem_idx in range(mem_count.value):
            hMemory = memories[mem_idx]
            print(f"\\n  Memory Module {mem_idx}:")

            try:
                # Get memory properties
                mem_props = zes_mem_properties_t()
                mem_props.stype = ZES_STRUCTURE_TYPE_MEM_PROPERTIES
                mem_props.pNext = None
                retVal = pyzes.zesMemoryGetProperties(hMemory, byref(mem_props))
                if retVal != ZE_RESULT_SUCCESS:
                    print(f"    Error getting memory properties: Return code {retVal}")
                    continue
                print(f"    Properties: {mem_props}")

                # Decode memory type
                mem_type_names = {
                    ZES_MEM_TYPE_HBM: "HBM",
                    ZES_MEM_TYPE_DDR: "DDR",
                    ZES_MEM_TYPE_DDR4: "DDR4",
                    ZES_MEM_TYPE_DDR5: "DDR5",
                    ZES_MEM_TYPE_GDDR6: "GDDR6",
                    ZES_MEM_TYPE_GDDR6X: "GDDR6X",
                    ZES_MEM_TYPE_GDDR7: "GDDR7",
                }
                type_name = mem_type_names.get(
                    mem_props.type, f"Unknown({mem_props.type})"
                )

                location_names = {
                    ZES_MEM_LOC_SYSTEM: "System",
                    ZES_MEM_LOC_DEVICE: "Device",
                }
                location_name = location_names.get(
                    mem_props.location, f"Unknown({mem_props.location})"
                )

                print(f"    Type: {type_name}")
                print(f"    Location: {location_name}")
                print(
                    f"    Physical Size: {mem_props.physicalSize:,} bytes ({mem_props.physicalSize / (1024**3):.2f} GB)"
                )
                if mem_props.busWidth != -1:
                    print(f"    Bus Width: {mem_props.busWidth} bits")
                if mem_props.numChannels != -1:
                    print(f"    Channels: {mem_props.numChannels}")

            except Exception as e:
                print(f"    Error getting memory properties: {e}")
                continue

            try:
                # Get memory state - this is the main function we're demonstrating
                mem_state = zes_mem_state_t()
                mem_state.stype = ZES_STRUCTURE_TYPE_MEM_STATE
                mem_state.pNext = None
                retVal = pyzes.zesMemoryGetState(hMemory, byref(mem_state))
                if retVal != ZE_RESULT_SUCCESS:
                    print(f"    Error getting memory state: Return code {retVal}")
                    continue
                print(f"    State: {mem_state}")

                # Decode health status
                health_names = {
                    ZES_MEM_HEALTH_UNKNOWN: "Unknown",
                    ZES_MEM_HEALTH_OK: "OK",
                    ZES_MEM_HEALTH_DEGRADED: "Degraded",
                    ZES_MEM_HEALTH_CRITICAL: "Critical",
                    ZES_MEM_HEALTH_REPLACE: "Replace",
                }
                health_name = health_names.get(
                    mem_state.health, f"Unknown({mem_state.health})"
                )

                print(f"    Health: {health_name}")
                print(
                    f"    Total Size: {mem_state.size:,} bytes ({mem_state.size / (1024**3):.2f} GB)"
                )
                print(
                    f"    Free: {mem_state.free:,} bytes ({mem_state.free / (1024**3):.2f} GB)"
                )

                if mem_state.size > 0:
                    used = mem_state.size - mem_state.free
                    used_percent = (used / mem_state.size) * 100
                    free_percent = (mem_state.free / mem_state.size) * 100
                    print(
                        f"    Used: {used:,} bytes ({used / (1024**3):.2f} GB, {used_percent:.1f}%)"
                    )
                    print(f"    Free: {free_percent:.1f}%")

            except Exception as e:
                print(f"    Error getting memory state: {e}")
                continue

            try:
                # Optionally get memory bandwidth if supported
                mem_bandwidth = zes_mem_bandwidth_t()
                retVal = pyzes.zesMemoryGetBandwidth(hMemory, byref(mem_bandwidth))
                if retVal != ZE_RESULT_SUCCESS:
                    print(f"    Error getting memory bandwidth: Return code {retVal}")
                    continue
                print(f"    Bandwidth: {mem_bandwidth}")
                print(
                    f"    Max Bandwidth: {mem_bandwidth.maxBandwidth:,} bytes/sec ({mem_bandwidth.maxBandwidth / (1024**3):.2f} GB/s)"
                )
                print(f"    Read Counter: {mem_bandwidth.readCounter:,} bytes")
                print(f"    Write Counter: {mem_bandwidth.writeCounter:,} bytes")

            except Exception as e:
                # Bandwidth might not be supported on all systems
                print(f"    Bandwidth info not available: {e}")


def demonstrate_memory_state_advanced(hDriver, devices, dev_count):
    """Advanced example showing manual struct initialization and error handling."""
    print("\n=== Advanced Memory State Example ===")

    if not devices or dev_count == 0:
        return

    mem_count = c_uint32(0)
    pyzes.zesDeviceEnumMemoryModules(devices[0], byref(mem_count), None)
    if mem_count.value == 0:
        print("No memory modules found")
        return

    MemoryArray = pyzes.zes_mem_handle_t * mem_count.value
    memories = MemoryArray()
    pyzes.zesDeviceEnumMemoryModules(devices[0], byref(mem_count), memories)

    print("\nManual struct initialization example:")
    mem_state = zes_mem_state_t()
    mem_state.stype = ZES_STRUCTURE_TYPE_MEM_STATE
    mem_state.pNext = None

    try:
        retVal = pyzes.zesMemoryGetState(memories[0], byref(mem_state))
        check_rc("zesMemoryGetState", retVal)
        print(f"Pre-initialized struct result: {mem_state}")
        print(f"Memory health: {mem_state.health}")
        print(f"Free memory: {mem_state.free} bytes")
        print(f"Total memory: {mem_state.size} bytes")
    except Exception as e:
        print(f"Error: {e}")


def demonstrate_power_energy(hDriver, devices, dev_count):
    """Demonstrate power energy counter functionality."""
    print("\n=== Power Energy Counter ===")
    if not devices or dev_count == 0:
        return

    # For each device, enumerate power domains and query their energy counters
    for dev_idx in range(dev_count):
        print(f"\nDevice {dev_idx} Power Domains:")
        hDevice = devices[dev_idx]

        # Step 1: Enumerate power domains
        power_count = c_uint32(0)
        rc = pyzes.zesDeviceEnumPowerDomains(hDevice, byref(power_count), None)
        if rc != ZE_RESULT_SUCCESS:
            print(f"  Error enumerating power domains: {rc}")
            continue

        if power_count.value == 0:
            print("  No power domains found")
            continue

        # Allocate array for power handles
        PowerArray = pyzes.zes_pwr_handle_t * power_count.value
        power_handles = PowerArray()
        rc = pyzes.zesDeviceEnumPowerDomains(hDevice, byref(power_count), power_handles)
        check_rc(f"zesDeviceEnumPowerDomains(device {dev_idx})", rc)

        print(f"  Found {power_count.value} power domain(s)")

        # Step 2: For each power domain, get energy counter
        for pwr_idx in range(power_count.value):
            hPower = power_handles[pwr_idx]
            print(f"\n  Power Domain {pwr_idx}:")

            try:
                # Get power energy counter
                energy_counter = zes_power_energy_counter_t()
                retVal = pyzes.zesPowerGetEnergyCounter(hPower, byref(energy_counter))
                if retVal != ZE_RESULT_SUCCESS:
                    print(f"    Error getting energy counter: {retVal}")
                    continue

                print(f"    Energy Counter: {energy_counter}")
                print(
                    f"    Energy: {energy_counter.energy} microjoules ({energy_counter.energy / 1000000.0:.6f} joules)"
                )
                print(f"    Timestamp: {energy_counter.timestamp} microseconds")

                # Convert timestamp to seconds for readability
                timestamp_seconds = energy_counter.timestamp / 1000000.0
                print(f"    Timestamp: {timestamp_seconds:.6f} seconds")

                # Try to get a second reading to show energy consumption
                import time

                print("    Waiting 1 second for energy measurement...")
                time.sleep(1)

                energy_counter2 = zes_power_energy_counter_t()
                retVal = pyzes.zesPowerGetEnergyCounter(hPower, byref(energy_counter2))
                if retVal == ZE_RESULT_SUCCESS:
                    energy_diff = energy_counter2.energy - energy_counter.energy
                    time_diff = (
                        energy_counter2.timestamp - energy_counter.timestamp
                    ) / 1000000.0

                    print(f"    Second reading:")
                    print(
                        f"      Energy: {energy_counter2.energy} microjoules ({energy_counter2.energy / 1000000.0:.6f} joules)"
                    )
                    print(
                        f"      Energy consumed: {energy_diff} microjoules ({energy_diff / 1000000.0:.6f} joules)"
                    )
                    if time_diff > 0:
                        avg_power = (energy_diff / 1000000.0) / time_diff  # Watts
                        print(
                            f"      Average power: {avg_power:.6f} watts over {time_diff:.6f} seconds"
                        )

            except Exception as e:
                print(f"    Error getting power energy counter: {e}")
                continue


def demonstrate_frequency_state(hDriver, devices, dev_count):
    """Demonstrate frequency domain enumeration and state functionality."""
    print("\n=== Frequency State ===")
    if not devices or dev_count == 0:
        return

    # For each device, enumerate frequency domains and query their state
    for dev_idx in range(dev_count):
        print(f"\nDevice {dev_idx} Frequency Domains:")
        hDevice = devices[dev_idx]

        # Step 1: Enumerate frequency domains
        freq_count = c_uint32(0)
        rc = pyzes.zesDeviceEnumFrequencyDomains(hDevice, byref(freq_count), None)
        if rc != ZE_RESULT_SUCCESS:
            print(f"  Error enumerating frequency domains: {rc}")
            continue

        if freq_count.value == 0:
            print("  No frequency domains found")
            continue

        # Allocate array for frequency handles
        FrequencyArray = pyzes.zes_freq_handle_t * freq_count.value
        freq_handles = FrequencyArray()
        rc = pyzes.zesDeviceEnumFrequencyDomains(
            hDevice, byref(freq_count), freq_handles
        )
        check_rc(f"zesDeviceEnumFrequencyDomains(device {dev_idx})", rc)

        print(f"  Found {freq_count.value} frequency domain(s)")

        # Step 2: For each frequency domain, get state
        for freq_idx in range(freq_count.value):
            hFrequency = freq_handles[freq_idx]
            print(f"\n  Frequency Domain {freq_idx}:")

            try:
                # Get frequency state - this is the main function we're demonstrating
                freq_state = zes_freq_state_t()
                freq_state.stype = ZES_STRUCTURE_TYPE_FREQ_STATE
                freq_state.pNext = None
                retVal = pyzes.zesFrequencyGetState(hFrequency, byref(freq_state))
                if retVal != ZE_RESULT_SUCCESS:
                    print(f"    Error getting frequency state: {retVal}")
                    continue
                print(f"    State: {freq_state}")

                # Display frequency state details
                print(
                    f"    Current Voltage: {freq_state.currentVoltage:.3f} V"
                    if freq_state.currentVoltage >= 0
                    else "    Current Voltage: Unknown"
                )
                print(
                    f"    Requested Frequency: {freq_state.request:.1f} MHz"
                    if freq_state.request >= 0
                    else "    Requested Frequency: Unknown"
                )
                print(
                    f"    TDP Frequency: {freq_state.tdp:.1f} MHz"
                    if freq_state.tdp >= 0
                    else "    TDP Frequency: Unknown"
                )
                print(
                    f"    Efficient Frequency: {freq_state.efficient:.1f} MHz"
                    if freq_state.efficient >= 0
                    else "    Efficient Frequency: Unknown"
                )
                print(
                    f"    Actual Frequency: {freq_state.actual:.1f} MHz"
                    if freq_state.actual >= 0
                    else "    Actual Frequency: Unknown"
                )

                # Decode throttle reasons
                if freq_state.throttleReasons != 0:
                    throttle_reasons = []
                    if (
                        freq_state.throttleReasons
                        & ZES_FREQ_THROTTLE_REASON_FLAG_AVE_PWR_CAP
                    ):
                        throttle_reasons.append("Average Power Cap (PL1)")
                    if (
                        freq_state.throttleReasons
                        & ZES_FREQ_THROTTLE_REASON_FLAG_BURST_PWR_CAP
                    ):
                        throttle_reasons.append("Burst Power Cap (PL2)")
                    if (
                        freq_state.throttleReasons
                        & ZES_FREQ_THROTTLE_REASON_FLAG_CURRENT_LIMIT
                    ):
                        throttle_reasons.append("Current Limit (PL4)")
                    if (
                        freq_state.throttleReasons
                        & ZES_FREQ_THROTTLE_REASON_FLAG_THERMAL_LIMIT
                    ):
                        throttle_reasons.append("Thermal Limit")
                    if (
                        freq_state.throttleReasons
                        & ZES_FREQ_THROTTLE_REASON_FLAG_PSU_ALERT
                    ):
                        throttle_reasons.append("PSU Alert")
                    if (
                        freq_state.throttleReasons
                        & ZES_FREQ_THROTTLE_REASON_FLAG_SW_RANGE
                    ):
                        throttle_reasons.append("Software Range")
                    if (
                        freq_state.throttleReasons
                        & ZES_FREQ_THROTTLE_REASON_FLAG_HW_RANGE
                    ):
                        throttle_reasons.append("Hardware Range")

                    print(f"    Throttle Reasons: {', '.join(throttle_reasons)}")
                else:
                    print("    Throttle Reasons: None (not throttled)")

            except Exception as e:
                print(f"    Error getting frequency state: {e}")
                continue


def demonstrate_temperature_state(hDriver, devices, dev_count):
    """Demonstrate temperature sensor enumeration and state functionality."""
    print("\n=== Temperature State ===")
    if not devices or dev_count == 0:
        return

    # For each device, enumerate temperature sensors and query their state
    for dev_idx in range(dev_count):
        print(f"\nDevice {dev_idx} Temperature Sensors:")
        hDevice = devices[dev_idx]

        # Step 1: Enumerate temperature sensors
        temp_count = c_uint32(0)
        rc = pyzes.zesDeviceEnumTemperatureSensors(hDevice, byref(temp_count), None)
        if rc != ZE_RESULT_SUCCESS:
            print(f"  Error enumerating temperature sensors: {rc}")
            continue

        if temp_count.value == 0:
            print("  No temperature sensors found")
            continue

        # Allocate array for temperature handles
        TemperatureArray = pyzes.zes_temp_handle_t * temp_count.value
        temp_handles = TemperatureArray()
        rc = pyzes.zesDeviceEnumTemperatureSensors(
            hDevice, byref(temp_count), temp_handles
        )
        check_rc(f"zesDeviceEnumTemperatureSensors(device {dev_idx})", rc)

        print(f"  Found {temp_count.value} temperature sensor(s)")

        # Step 2: For each temperature sensor, get properties and state
        for temp_idx in range(temp_count.value):
            hTemperature = temp_handles[temp_idx]
            print(f"\n  Temperature Sensor {temp_idx}:")

            try:
                # Get temperature properties first
                temp_props = zes_temp_properties_t()
                temp_props.stype = ZES_STRUCTURE_TYPE_TEMP_PROPERTIES
                temp_props.pNext = None
                retVal = pyzes.zesTemperatureGetProperties(
                    hTemperature, byref(temp_props)
                )
                if retVal != ZE_RESULT_SUCCESS:
                    print(f"    Error getting temperature properties: {retVal}")
                    continue
                print(f"    Properties: {temp_props}")

                # Decode sensor type
                sensor_type_names = {
                    ZES_TEMP_SENSORS_GLOBAL: "Global",
                    ZES_TEMP_SENSORS_GPU: "GPU Core",
                    ZES_TEMP_SENSORS_MEMORY: "Memory",
                    ZES_TEMP_SENSORS_GLOBAL_MIN: "Global Minimum",
                    ZES_TEMP_SENSORS_GPU_MIN: "GPU Minimum",
                    ZES_TEMP_SENSORS_MEMORY_MIN: "Memory Minimum",
                }
                type_name = sensor_type_names.get(
                    temp_props.type, f"Unknown({temp_props.type})"
                )

                print(f"    Type: {type_name}")
                print(f"    On Subdevice: {bool(temp_props.onSubdevice)}")
                if temp_props.onSubdevice:
                    print(f"    Subdevice ID: {temp_props.subdeviceId}")
                print(
                    f"    Max Temperature: {temp_props.maxTemperature:.1f} °C"
                    if temp_props.maxTemperature >= 0
                    else "    Max Temperature: Unknown"
                )
                print(
                    f"    Critical Temp Supported: {bool(temp_props.isCriticalTempSupported)}"
                )
                print(
                    f"    Threshold 1 Supported: {bool(temp_props.isThreshold1Supported)}"
                )
                print(
                    f"    Threshold 2 Supported: {bool(temp_props.isThreshold2Supported)}"
                )

            except Exception as e:
                print(f"    Error getting temperature properties: {e}")
                continue

            try:
                # Get temperature state - this is the main function we're demonstrating
                temperature = c_double(0.0)
                retVal = pyzes.zesTemperatureGetState(hTemperature, byref(temperature))
                if retVal != ZE_RESULT_SUCCESS:
                    print(f"    Error getting temperature state: {retVal}")
                    continue

                print(f"    Current Temperature: {temperature.value:.1f} °C")

                # Provide some context for the temperature reading
                if temperature.value > 0:
                    if temperature.value > 85:
                        temp_status = "Very Hot (consider cooling)"
                    elif temperature.value > 70:
                        temp_status = "Hot (normal under load)"
                    elif temperature.value > 50:
                        temp_status = "Warm (normal operation)"
                    elif temperature.value > 30:
                        temp_status = "Cool (idle/light load)"
                    else:
                        temp_status = "Cold (possibly just started)"
                    print(f"    Temperature Status: {temp_status}")

            except Exception as e:
                print(f"    Error getting temperature state: {e}")
                continue

            try:
                # Optionally get temperature configuration if supported
                temp_config = zes_temp_config_t()
                temp_config.stype = ZES_STRUCTURE_TYPE_TEMP_CONFIG
                temp_config.pNext = None
                retVal = pyzes.zesTemperatureGetConfig(hTemperature, byref(temp_config))
                if retVal == ZE_RESULT_SUCCESS:
                    print(f"    Configuration: {temp_config}")
                    print(
                        f"    Critical Events Enabled: {bool(temp_config.enableCritical)}"
                    )
                    print(
                        f"    Threshold 1: {temp_config.threshold1:.1f} °C"
                        if temp_config.threshold1 >= 0
                        else "    Threshold 1: Not set"
                    )
                    print(
                        f"    Threshold 2: {temp_config.threshold2:.1f} °C"
                        if temp_config.threshold2 >= 0
                        else "    Threshold 2: Not set"
                    )
                else:
                    print(f"    Configuration: Not available (rc={retVal})")

            except Exception as e:
                # Config might not be supported on all systems
                print(f"    Configuration info not available: {e}")


if __name__ == "__main__":
    try:
        # Initialize Sysman and get devices only once
        hDriver, devices, dev_count = initialize_sysman_and_get_devices()
        if not devices or dev_count == 0:
            print("No devices available for testing")
            sys.exit(0)

        # Pass the initialized data to all functions
        enumerate_devices(hDriver, devices, dev_count)
        demonstrate_memory_state(hDriver, devices, dev_count)
        demonstrate_memory_state_advanced(hDriver, devices, dev_count)
        demonstrate_power_energy(hDriver, devices, dev_count)
        demonstrate_frequency_state(hDriver, devices, dev_count)
        demonstrate_temperature_state(hDriver, devices, dev_count)
    except Exception as e:
        print(f"Unhandled exception: {e}")
        sys.exit(1)
