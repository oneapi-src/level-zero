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
class TestMemoryFunctions(unittest.TestCase):

    def setUp(self):
        import pyzes

        self.pyzes = pyzes

    def test_GivenValidDeviceHandleWhenCallingZesDeviceEnumMemoryModulesThenCallSucceedsWithValidCount(
        self, mock_get_func
    ):
        mock_module_count = 3

        def mock_enum_memory_modules(device_handle, count_ptr, handles_ptr):
            count_ptr._obj.value = mock_module_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_enum_memory_modules)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        count = c_uint32(0)

        result = self.pyzes.zesDeviceEnumMemoryModules(
            device_handle, byref(count), None
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_module_count)
        mock_get_func.assert_called_with("zesDeviceEnumMemoryModules")
        mock_func.assert_called_once()

    def test_GivenValidMemoryHandleWhenCallingZesMemoryGetPropertiesThenCallSucceedsWithValidProperties(
        self, mock_get_func
    ):
        mock_type = self.pyzes.ZES_MEM_TYPE_GDDR6
        mock_on_subdevice = False
        mock_subdevice_id = 0
        mock_location = self.pyzes.ZES_MEM_LOC_DEVICE
        mock_physical_size = 8589934592  # 8GB
        mock_bus_width = 256
        mock_num_channels = 8

        def mock_get_properties(memory_handle, properties_ptr):
            properties_ptr._obj.type = mock_type
            properties_ptr._obj.onSubdevice = mock_on_subdevice
            properties_ptr._obj.subdeviceId = mock_subdevice_id
            properties_ptr._obj.location = mock_location
            properties_ptr._obj.physicalSize = mock_physical_size
            properties_ptr._obj.busWidth = mock_bus_width
            properties_ptr._obj.numChannels = mock_num_channels
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_properties)
        mock_get_func.return_value = mock_func

        memory_handle = self.pyzes.zes_mem_handle_t()
        mem_props = self.pyzes.zes_mem_properties_t()
        result = self.pyzes.zesMemoryGetProperties(memory_handle, byref(mem_props))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(mem_props.type, mock_type)
        self.assertEqual(mem_props.onSubdevice, mock_on_subdevice)
        self.assertEqual(mem_props.subdeviceId, mock_subdevice_id)
        self.assertEqual(mem_props.location, mock_location)
        self.assertEqual(mem_props.physicalSize, mock_physical_size)
        self.assertEqual(mem_props.busWidth, mock_bus_width)
        self.assertEqual(mem_props.numChannels, mock_num_channels)
        mock_get_func.assert_called_with("zesMemoryGetProperties")
        mock_func.assert_called_once()

    def test_GivenValidMemoryHandleWhenCallingZesMemoryGetStateThenCallSucceedsWithState(
        self, mock_get_func
    ):
        mock_health = self.pyzes.ZES_MEM_HEALTH_OK
        mock_free = 4294967296  # 4GB
        mock_size = 8589934592  # 8GB

        def mock_get_state(memory_handle, state_ptr):
            state_ptr._obj.health = mock_health
            state_ptr._obj.free = mock_free
            state_ptr._obj.size = mock_size
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_state)
        mock_get_func.return_value = mock_func

        memory_handle = self.pyzes.zes_mem_handle_t()
        mem_state = self.pyzes.zes_mem_state_t()
        result = self.pyzes.zesMemoryGetState(memory_handle, byref(mem_state))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(mem_state.health, mock_health)
        self.assertEqual(mem_state.free, mock_free)
        self.assertEqual(mem_state.size, mock_size)
        mock_get_func.assert_called_with("zesMemoryGetState")
        mock_func.assert_called_once()

    def test_GivenValidMemoryHandleWhenCallingZesMemoryGetBandwidthThenCallSucceedsWithBandwidth(
        self, mock_get_func
    ):
        mock_read_counter = 1073741824  # 1GB
        mock_write_counter = 536870912  # 512MB
        mock_max_bandwidth = 429496729600  # 400GB/s
        mock_timestamp = 123456789

        def mock_get_bandwidth(memory_handle, bandwidth_ptr):
            bandwidth_ptr._obj.readCounter = mock_read_counter
            bandwidth_ptr._obj.writeCounter = mock_write_counter
            bandwidth_ptr._obj.maxBandwidth = mock_max_bandwidth
            bandwidth_ptr._obj.timestamp = mock_timestamp
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_bandwidth)
        mock_get_func.return_value = mock_func

        memory_handle = self.pyzes.zes_mem_handle_t()
        mem_bandwidth = self.pyzes.zes_mem_bandwidth_t()
        result = self.pyzes.zesMemoryGetBandwidth(memory_handle, byref(mem_bandwidth))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(mem_bandwidth.readCounter, mock_read_counter)
        self.assertEqual(mem_bandwidth.writeCounter, mock_write_counter)
        self.assertEqual(mem_bandwidth.maxBandwidth, mock_max_bandwidth)
        self.assertEqual(mem_bandwidth.timestamp, mock_timestamp)
        mock_get_func.assert_called_with("zesMemoryGetBandwidth")
        mock_func.assert_called_once()


if __name__ == "__main__":
    unittest.main()
