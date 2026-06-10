##
# Copyright (C) 2026 Intel Corporation
#
# SPDX-License-Identifier: MIT
#
##

import os
import sys
from ctypes import byref, c_uint32

import pytest


CTS_TESTS_DIR = os.path.dirname(os.path.abspath(__file__))
SOURCE_DIR = os.path.abspath(os.path.join(CTS_TESTS_DIR, ".."))

if SOURCE_DIR not in sys.path:
    sys.path.insert(0, SOURCE_DIR)


@pytest.fixture(scope="session")
def pyzes_module():
    try:
        import pyzes as pz
    except (ImportError, OSError) as exc:
        pytest.skip(f"pyzes is not available for CTS validation: {exc}")

    return pz


@pytest.fixture(scope="session")
def sysman_devices(pyzes_module):
    pz = pyzes_module

    rc = pz.zesInit(0)
    if rc != pz.ZE_RESULT_SUCCESS:
        pytest.skip(f"zesInit failed with ze_result_t={rc}")

    driver_count = c_uint32(0)
    rc = pz.zesDriverGet(byref(driver_count), None)
    if rc != pz.ZE_RESULT_SUCCESS:
        pytest.skip(f"zesDriverGet(count) failed with ze_result_t={rc}")

    if driver_count.value == 0:
        pytest.skip("No Sysman drivers available")

    DriverArray = pz.zes_driver_handle_t * driver_count.value
    drivers = DriverArray()
    rc = pz.zesDriverGet(byref(driver_count), drivers)
    if rc != pz.ZE_RESULT_SUCCESS:
        pytest.skip(f"zesDriverGet(handles) failed with ze_result_t={rc}")

    devices = []
    for driver in drivers:
        device_count = c_uint32(0)
        rc = pz.zesDeviceGet(driver, byref(device_count), None)
        if rc != pz.ZE_RESULT_SUCCESS:
            continue

        if device_count.value == 0:
            continue

        DeviceArray = pz.zes_device_handle_t * device_count.value
        driver_devices = DeviceArray()
        rc = pz.zesDeviceGet(driver, byref(device_count), driver_devices)
        if rc != pz.ZE_RESULT_SUCCESS:
            continue

        devices.extend(driver_devices)

    if not devices:
        pytest.skip("No Sysman devices available")

    return devices