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
class TestFrequencyFunctions(unittest.TestCase):

    def setUp(self):
        import pyzes

        self.pyzes = pyzes

    def test_GivenValidDeviceHandleWhenCallingZesDeviceEnumFrequencyDomainsThenCallSucceedsWithValidCount(
        self, mock_get_func
    ):
        mock_frequency_count = 2

        def mock_enum_frequency_domains(device_handle, count_ptr, handles_ptr):
            count_ptr._obj.value = mock_frequency_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_enum_frequency_domains)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        count = c_uint32(0)

        result = self.pyzes.zesDeviceEnumFrequencyDomains(
            device_handle, byref(count), None
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_frequency_count)
        mock_get_func.assert_called_with("zesDeviceEnumFrequencyDomains")
        mock_func.assert_called_once()

    def test_GivenValidFrequencyHandleWhenCallingZesFrequencyGetStateThenCallSucceedsWithState(
        self, mock_get_func
    ):
        mock_current_voltage = 1.2  # 1.2V
        mock_request = 1500.0  # 1500 MHz
        mock_tdp = 1600.0  # 1600 MHz
        mock_efficient = 800.0  # 800 MHz
        mock_actual = 1450.0  # 1450 MHz
        mock_throttle_reasons = 0  # throttle reason flags

        def mock_get_state(frequency_handle, state_ptr):
            state_ptr._obj.currentVoltage = mock_current_voltage
            state_ptr._obj.request = mock_request
            state_ptr._obj.tdp = mock_tdp
            state_ptr._obj.efficient = mock_efficient
            state_ptr._obj.actual = mock_actual
            state_ptr._obj.throttleReasons = mock_throttle_reasons
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_state)
        mock_get_func.return_value = mock_func

        frequency_handle = self.pyzes.zes_freq_handle_t()
        freq_state = self.pyzes.zes_freq_state_t()
        result = self.pyzes.zesFrequencyGetState(frequency_handle, byref(freq_state))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(freq_state.currentVoltage, mock_current_voltage)
        self.assertEqual(freq_state.request, mock_request)
        self.assertEqual(freq_state.tdp, mock_tdp)
        self.assertEqual(freq_state.efficient, mock_efficient)
        self.assertEqual(freq_state.actual, mock_actual)
        self.assertEqual(freq_state.throttleReasons, mock_throttle_reasons)
        mock_get_func.assert_called_with("zesFrequencyGetState")
        mock_func.assert_called_once()


if __name__ == "__main__":
    unittest.main()
