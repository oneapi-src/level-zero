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
class TestPowerFunctions(unittest.TestCase):

    def setUp(self):
        import pyzes

        self.pyzes = pyzes

    def test_GivenValidDeviceHandleWhenCallingZesDeviceEnumPowerDomainsThenCallSucceedsWithValidCount(
        self, mock_get_func
    ):
        mock_count = 2

        def mock_enum_domains(device_handle, count_ptr, handles_ptr):
            count_ptr._obj.value = mock_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_enum_domains)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        count = c_uint32(0)

        result = self.pyzes.zesDeviceEnumPowerDomains(device_handle, byref(count), None)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_count)
        mock_get_func.assert_called_with("zesDeviceEnumPowerDomains")
        mock_func.assert_called_once()

    def test_GivenValidPowerHandleWhenCallingZesPowerGetEnergyCounterThenCallSucceedsWithEnergyData(
        self, mock_get_func
    ):
        mock_energy = 12345
        mock_timestamp = 67890

        def mock_get_energy(power_handle, energy_ptr):
            energy_ptr._obj.energy = mock_energy
            energy_ptr._obj.timestamp = mock_timestamp
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_energy)
        mock_get_func.return_value = mock_func

        power_handle = self.pyzes.zes_pwr_handle_t()
        energy = self.pyzes.zes_power_energy_counter_t()

        result = self.pyzes.zesPowerGetEnergyCounter(power_handle, byref(energy))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(energy.energy, mock_energy)
        self.assertEqual(energy.timestamp, mock_timestamp)
        mock_get_func.assert_called_with("zesPowerGetEnergyCounter")
        mock_func.assert_called_once()


if __name__ == "__main__":
    unittest.main()
