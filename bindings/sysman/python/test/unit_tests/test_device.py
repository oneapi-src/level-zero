##
# Copyright (C) 2026 Intel Corporation
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
class TestDeviceFunctions(unittest.TestCase):
    def setUp(self):
        import pyzes

        self.pyzes = pyzes

    def test_GivenValidDeviceHandleWhenCallingZesDeviceGetStateThenCallSucceedsWithValidState(
        self, mock_get_func
    ):
        def mock_get_state(device_handle, state_ptr):
            state = state_ptr._obj
            state.reset = (
                self.pyzes.ZES_RESET_REASON_FLAG_WEDGED
                | self.pyzes.ZES_RESET_REASON_FLAG_REPAIR
            )
            state.repaired = self.pyzes.ZES_REPAIR_STATUS_PERFORMED
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_state)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        state = self.pyzes.zes_device_state_t()
        state.stype = self.pyzes.ZES_STRUCTURE_TYPE_DEVICE_STATE

        result = self.pyzes.zesDeviceGetState(device_handle, byref(state))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(
            state.reset,
            self.pyzes.ZES_RESET_REASON_FLAG_WEDGED
            | self.pyzes.ZES_RESET_REASON_FLAG_REPAIR,
        )
        self.assertEqual(state.repaired, self.pyzes.ZES_REPAIR_STATUS_PERFORMED)
        mock_get_func.assert_called_with("zesDeviceGetState")
        mock_func.assert_called_once()

    def test_GivenValidDeviceHandleWhenCallingZesDeviceResetExtThenCallSucceedsWithRequestedProperties(
        self, mock_get_func
    ):
        def mock_reset_ext(device_handle, properties_ptr):
            properties = properties_ptr._obj
            self.assertEqual(
                properties.stype, self.pyzes.ZES_STRUCTURE_TYPE_RESET_PROPERTIES
            )
            self.assertEqual(properties.force, 0)
            self.assertEqual(properties.resetType, self.pyzes.ZES_RESET_TYPE_FLR)
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_reset_ext)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        properties = self.pyzes.zes_reset_properties_t()
        properties.stype = self.pyzes.ZES_STRUCTURE_TYPE_RESET_PROPERTIES
        properties.force = 0
        properties.resetType = self.pyzes.ZES_RESET_TYPE_FLR

        result = self.pyzes.zesDeviceResetExt(device_handle, byref(properties))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.assert_called_with("zesDeviceResetExt")
        mock_func.assert_called_once()

    def test_GivenValidDeviceHandleWhenCallingZesDeviceEventRegisterThenCallSucceeds(
        self, mock_get_func
    ):
        mock_func = MagicMock(return_value=self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        events = (
            self.pyzes.ZES_EVENT_TYPE_FLAG_DEVICE_RESET_REQUIRED
            | self.pyzes.ZES_EVENT_TYPE_FLAG_TEMP_CRITICAL
        )

        result = self.pyzes.zesDeviceEventRegister(device_handle, events)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.assert_called_with("zesDeviceEventRegister")
        mock_func.assert_called_once_with(device_handle, events)

    def test_GivenValidDeviceHandleWhenCallingZesDeviceGetHealthStatusExtThenCallSucceedsWithHealthStatus(
        self, mock_get_func
    ):
        def mock_get_health(device_handle, health_ptr):
            health_ptr._obj.value = self.pyzes.ZES_DEVICE_HEALTH_STATUS_EXT_WARNING
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_health)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        health = self.pyzes.zes_device_health_status_ext_t(0)

        result = self.pyzes.zesDeviceGetHealthStatusExt(device_handle, byref(health))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(health.value, self.pyzes.ZES_DEVICE_HEALTH_STATUS_EXT_WARNING)
        mock_get_func.assert_called_with("zesDeviceGetHealthStatusExt")
        mock_func.assert_called_once()

    def test_GivenValidDeviceHandleWhenCallingZesDeviceSetHealthStatusExtThenCallSucceeds(
        self, mock_get_func
    ):
        mock_func = MagicMock(return_value=self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()

        result = self.pyzes.zesDeviceSetHealthStatusExt(
            device_handle, self.pyzes.ZES_DEVICE_HEALTH_STATUS_EXT_OK
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.assert_called_with("zesDeviceSetHealthStatusExt")
        mock_func.assert_called_once_with(
            device_handle, self.pyzes.ZES_DEVICE_HEALTH_STATUS_EXT_OK
        )

    def test_GivenValidDeviceHandleWhenCallingZesDeviceEnumFirmwaresThenCallSucceedsWithValidCount(
        self, mock_get_func
    ):
        mock_count = 3

        def mock_enum_firmwares(device_handle, count_ptr, handles_ptr):
            count_ptr._obj.value = mock_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_enum_firmwares)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        count = c_uint32(0)

        result = self.pyzes.zesDeviceEnumFirmwares(device_handle, byref(count), None)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_count)
        mock_get_func.assert_called_with("zesDeviceEnumFirmwares")
        mock_func.assert_called_once()

    def test_GivenValidDeviceHandleWhenCallingZesDeviceEnumFirmwaresWithArrayThenCallSucceedsWithHandles(
        self, mock_get_func
    ):
        mock_count = 2

        def mock_enum_firmwares(device_handle, count_ptr, handles_ptr):
            count_ptr._obj.value = mock_count
            handles_ptr[0] = self.pyzes.zes_firmware_handle_t(0x1000)
            handles_ptr[1] = self.pyzes.zes_firmware_handle_t(0x2000)
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_enum_firmwares)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        count = c_uint32(mock_count)
        handles = (self.pyzes.zes_firmware_handle_t * mock_count)()

        result = self.pyzes.zesDeviceEnumFirmwares(device_handle, byref(count), handles)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_count)
        self.assertEqual(handles[0].value, 0x1000)
        self.assertEqual(handles[1].value, 0x2000)
        mock_get_func.assert_called_with("zesDeviceEnumFirmwares")
        mock_func.assert_called_once()


if __name__ == "__main__":
    unittest.main()
