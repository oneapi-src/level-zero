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
class TestEngineFunctions(unittest.TestCase):

    def setUp(self):
        import pyzes

        self.pyzes = pyzes

    def test_GivenValidDeviceHandleWhenCallingZesDeviceEnumEngineGroupsThenCallSucceedsWithValidCount(
        self, mock_get_func
    ):
        mock_engine_count = 4

        def mock_enum_engine_groups(device_handle, count_ptr, handles_ptr):
            count_ptr._obj.value = mock_engine_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_enum_engine_groups)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        count = c_uint32(0)

        result = self.pyzes.zesDeviceEnumEngineGroups(device_handle, byref(count), None)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_engine_count)
        mock_get_func.assert_called_with("zesDeviceEnumEngineGroups")
        mock_func.assert_called_once()

    def test_GivenValidEngineHandleWhenCallingZesEngineGetPropertiesThenCallSucceedsWithValidProperties(
        self, mock_get_func
    ):
        mock_type = self.pyzes.ZES_ENGINE_GROUP_COMPUTE_SINGLE
        mock_subdevice_id = 0
        mock_on_subdevice = False

        def mock_get_properties(engine_handle, properties_ptr):
            properties_ptr._obj.type = mock_type
            properties_ptr._obj.subdeviceId = mock_subdevice_id
            properties_ptr._obj.onSubdevice = mock_on_subdevice
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_properties)
        mock_get_func.return_value = mock_func

        engine_handle = self.pyzes.zes_engine_handle_t()
        engine_props = self.pyzes.zes_engine_properties_t()
        result = self.pyzes.zesEngineGetProperties(engine_handle, byref(engine_props))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(engine_props.type, mock_type)
        self.assertEqual(engine_props.subdeviceId, mock_subdevice_id)
        self.assertEqual(engine_props.onSubdevice, mock_on_subdevice)
        mock_get_func.assert_called_with("zesEngineGetProperties")
        mock_func.assert_called_once()

    def test_GivenValidEngineHandleWhenCallingZesEngineGetActivityThenCallSucceedsWithActivity(
        self, mock_get_func
    ):
        mock_active_time = 987654321
        mock_timestamp = 123456789

        def mock_get_activity(engine_handle, stats_ptr):
            stats_ptr._obj.activeTime = mock_active_time
            stats_ptr._obj.timestamp = mock_timestamp
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_activity)
        mock_get_func.return_value = mock_func

        engine_handle = self.pyzes.zes_engine_handle_t()
        engine_stats = self.pyzes.zes_engine_stats_t()
        result = self.pyzes.zesEngineGetActivity(engine_handle, byref(engine_stats))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(engine_stats.activeTime, mock_active_time)
        self.assertEqual(engine_stats.timestamp, mock_timestamp)
        mock_get_func.assert_called_with("zesEngineGetActivity")
        mock_func.assert_called_once()


if __name__ == "__main__":
    unittest.main()
