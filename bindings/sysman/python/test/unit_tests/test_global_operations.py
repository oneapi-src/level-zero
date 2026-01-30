#!/usr/bin/env python3
##
# Copyright (C) 2025 Intel Corporation
#
# SPDX-License-Identifier: MIT
#
##

import os
import sys
import unittest
from ctypes import *
from unittest.mock import MagicMock, patch

# Add the source directory to Python path so we can import pyzes
script_dir = os.path.dirname(os.path.abspath(__file__))
source_dir = os.path.join(script_dir, "..", "..", "source")
source_dir = os.path.abspath(source_dir)
if source_dir not in sys.path:
    sys.path.insert(0, source_dir)


@patch("pyzes.getFunctionPointerList")
class TestGlobalOperations(unittest.TestCase):

    def setUp(self):
        import pyzes

        self.pyzes = pyzes

    def test_GivenValidDriverHandleWhenCallingZesDeviceGetThenCallSucceedsWithValidCount(
        self, mock_get_func
    ):
        mock_device_count = 2

        def mock_device_get(driver_handle, count_ptr, devices_ptr):
            count_ptr._obj.value = mock_device_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_device_get)
        mock_get_func.return_value = mock_func

        driver_handle = self.pyzes.zes_driver_handle_t()
        count = c_uint32(0)

        result = self.pyzes.zesDeviceGet(driver_handle, byref(count), None)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_device_count)
        mock_get_func.assert_called_with("zesDeviceGet")
        mock_func.assert_called_once()

    def test_GivenValidDeviceHandleWhenCallingZesDeviceGetPropertiesThenCallSucceedsWithValidProperties(
        self, mock_get_func
    ):
        mock_num_subdevices = 4
        mock_vendor_id = 0x8086  # Intel
        mock_device_id = 0x1234
        mock_core_clock_rate = 1500  # MHz
        mock_max_mem_alloc_size = 4294967296  # 4GB
        mock_num_slices = 8
        mock_max_hardware_contexts = 512
        mock_num_threads_per_eu = 8

        def mock_get_properties(device_handle, properties_ptr):
            # Set zes_device_properties_t fields
            properties_ptr._obj.numSubdevices = mock_num_subdevices

            # Set ze_device_properties_t core fields
            properties_ptr._obj.core.vendorId = mock_vendor_id
            properties_ptr._obj.core.deviceId = mock_device_id
            properties_ptr._obj.core.coreClockRate = mock_core_clock_rate
            properties_ptr._obj.core.maxMemAllocSize = mock_max_mem_alloc_size
            properties_ptr._obj.core.numSlices = mock_num_slices
            properties_ptr._obj.core.maxHardwareContexts = mock_max_hardware_contexts
            properties_ptr._obj.core.numThreadsPerEU = mock_num_threads_per_eu

            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_properties)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        device_props = self.pyzes.zes_device_properties_t()
        result = self.pyzes.zesDeviceGetProperties(device_handle, byref(device_props))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)

        # Validate zes_device_properties_t fields
        self.assertEqual(device_props.numSubdevices, mock_num_subdevices)

        # Validate ze_device_properties_t core fields
        self.assertEqual(device_props.core.vendorId, mock_vendor_id)
        self.assertEqual(device_props.core.deviceId, mock_device_id)
        self.assertEqual(device_props.core.coreClockRate, mock_core_clock_rate)
        self.assertEqual(device_props.core.maxMemAllocSize, mock_max_mem_alloc_size)
        self.assertEqual(device_props.core.numSlices, mock_num_slices)
        self.assertEqual(
            device_props.core.maxHardwareContexts, mock_max_hardware_contexts
        )
        self.assertEqual(device_props.core.numThreadsPerEU, mock_num_threads_per_eu)

        mock_get_func.assert_called_with("zesDeviceGetProperties")
        mock_func.assert_called_once()

    def test_GivenValidDeviceHandleWhenCallingZesDeviceProcessesGetStateThenCallSucceedsWithProcessCount(
        self, mock_get_func
    ):
        mock_process_count = 3

        def mock_get_processes_state(device_handle, count_ptr, processes_ptr):
            count_ptr._obj.value = mock_process_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_processes_state)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        count = c_uint32(0)

        result = self.pyzes.zesDeviceProcessesGetState(
            device_handle, byref(count), None
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_process_count)
        mock_get_func.assert_called_with("zesDeviceProcessesGetState")
        mock_func.assert_called_once()

    def test_GivenValidDeviceHandleWhenCallingZesDeviceProcessesGetStateWithArrayThenCallSucceedsWithProcessData(
        self, mock_get_func
    ):
        mock_process_count = 2
        mock_pid_1 = 1234
        mock_pid_2 = 5678
        mock_mem_size_1 = 1073741824  # 1GB
        mock_mem_size_2 = 2147483648  # 2GB
        mock_shared_mem_size_1 = 536870912  # 512MB
        mock_shared_mem_size_2 = 1073741824  # 1GB
        mock_subdevice_id_1 = 0
        mock_subdevice_id_2 = 1

        def mock_get_processes_state_with_data(device_handle, count_ptr, processes_ptr):
            if processes_ptr:
                # Fill in process data for first process
                processes_ptr[0].pid = mock_pid_1
                processes_ptr[0].memSize = mock_mem_size_1
                processes_ptr[0].sharedMemSize = mock_shared_mem_size_1
                processes_ptr[0].subdeviceId = mock_subdevice_id_1

                # Fill in process data for second process
                processes_ptr[1].pid = mock_pid_2
                processes_ptr[1].memSize = mock_mem_size_2
                processes_ptr[1].sharedMemSize = mock_shared_mem_size_2
                processes_ptr[1].subdeviceId = mock_subdevice_id_2
            else:
                count_ptr._obj.value = mock_process_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_processes_state_with_data)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        count = c_uint32(mock_process_count)

        # Create array for process states
        process_array = (self.pyzes.zes_process_state_t * mock_process_count)()

        result = self.pyzes.zesDeviceProcessesGetState(
            device_handle, byref(count), process_array
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)

        # Validate first process data
        self.assertEqual(process_array[0].pid, mock_pid_1)
        self.assertEqual(process_array[0].memSize, mock_mem_size_1)
        self.assertEqual(process_array[0].sharedMemSize, mock_shared_mem_size_1)
        self.assertEqual(process_array[0].subdeviceId, mock_subdevice_id_1)

        # Validate second process data
        self.assertEqual(process_array[1].pid, mock_pid_2)
        self.assertEqual(process_array[1].memSize, mock_mem_size_2)
        self.assertEqual(process_array[1].sharedMemSize, mock_shared_mem_size_2)
        self.assertEqual(process_array[1].subdeviceId, mock_subdevice_id_2)

        mock_get_func.assert_called_with("zesDeviceProcessesGetState")
        mock_func.assert_called_once()

    def test_GivenValidDeviceHandleWhenCallingZesDeviceGetSubDevicePropertiesExpThenCallSucceedsWithSubdeviceCount(
        self, mock_get_func
    ):
        mock_subdevice_count = 2

        def mock_get_subdevice_props(device_handle, count_ptr, props_ptr):
            count_ptr._obj.value = mock_subdevice_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_subdevice_props)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        count = c_uint32(0)

        result = self.pyzes.zesDeviceGetSubDevicePropertiesExp(
            device_handle, byref(count), None
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_subdevice_count)
        mock_get_func.assert_called_with("zesDeviceGetSubDevicePropertiesExp")
        mock_func.assert_called_once()

    def test_GivenValidDeviceHandleWhenCallingZesDeviceGetSubDevicePropertiesExpWithArrayThenCallSucceedsWithSubdeviceData(
        self, mock_get_func
    ):
        mock_subdevice_count = 2
        mock_subdevice_id_0 = 0
        mock_subdevice_id_1 = 1
        # Mock UUIDs as predefined byte arrays
        mock_uuid_0 = [
            0x01,
            0x23,
            0x45,
            0x67,
            0x89,
            0xAB,
            0xCD,
            0xEF,
            0xFE,
            0xDC,
            0xBA,
            0x98,
            0x76,
            0x54,
            0x32,
            0x10,
        ]
        mock_uuid_1 = [
            0x11,
            0x22,
            0x33,
            0x44,
            0x55,
            0x66,
            0x77,
            0x88,
            0x99,
            0xAA,
            0xBB,
            0xCC,
            0xDD,
            0xEE,
            0xFF,
            0x00,
        ]

        def mock_get_subdevice_props_with_data(device_handle, count_ptr, props_ptr):
            if props_ptr:
                # Fill in first subdevice properties
                props_ptr[0].subdeviceId = mock_subdevice_id_0
                # Set UUID for first subdevice
                for i in range(16):
                    props_ptr[0].uuid.id[i] = mock_uuid_0[i]

                # Fill in second subdevice properties
                props_ptr[1].subdeviceId = mock_subdevice_id_1
                # Set UUID for second subdevice
                for i in range(16):
                    props_ptr[1].uuid.id[i] = mock_uuid_1[i]
            else:
                count_ptr._obj.value = mock_subdevice_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_subdevice_props_with_data)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        count = c_uint32(mock_subdevice_count)

        # Create array for subdevice properties
        subdevice_props_array = (
            self.pyzes.zes_subdevice_exp_properties_t * mock_subdevice_count
        )()

        result = self.pyzes.zesDeviceGetSubDevicePropertiesExp(
            device_handle, byref(count), subdevice_props_array
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)

        # Validate first subdevice properties
        self.assertEqual(subdevice_props_array[0].subdeviceId, mock_subdevice_id_0)
        for i in range(16):
            self.assertEqual(subdevice_props_array[0].uuid.id[i], mock_uuid_0[i])

        # Validate second subdevice properties
        self.assertEqual(subdevice_props_array[1].subdeviceId, mock_subdevice_id_1)
        for i in range(16):
            self.assertEqual(subdevice_props_array[1].uuid.id[i], mock_uuid_1[i])

        mock_get_func.assert_called_with("zesDeviceGetSubDevicePropertiesExp")
        mock_func.assert_called_once()


if __name__ == "__main__":
    unittest.main()
