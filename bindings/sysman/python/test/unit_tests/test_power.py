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

    def test_GivenValidPowerHandleWhenCallingZesPowerGetUsageThenCallSucceedsWithUsageData(
        self, mock_get_func
    ):
        mock_instant_power = 42000
        mock_average_power = 38000

        def mock_get_usage(power_handle, instant_ptr, average_ptr):
            instant_ptr._obj.value = mock_instant_power
            average_ptr._obj.value = mock_average_power
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_usage)
        mock_get_func.return_value = mock_func

        power_handle = self.pyzes.zes_pwr_handle_t()
        instant_power = c_uint32(0)
        average_power = c_uint32(0)

        result = self.pyzes.zesPowerGetUsage(
            power_handle, byref(instant_power), byref(average_power)
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(instant_power.value, mock_instant_power)
        self.assertEqual(average_power.value, mock_average_power)
        mock_get_func.assert_called_with("zesPowerGetUsage")
        mock_func.assert_called_once()

    def test_GivenValidPowerHandleWhenCallingZesPowerGetPropertiesThenCallSucceedsWithProperties(
        self, mock_get_func
    ):
        mock_default_limit = 150000
        mock_min_limit = 100000
        mock_max_limit = 225000
        mock_domain = self.pyzes.ZES_POWER_DOMAIN_PACKAGE
        mock_ext_default_limit = 175000

        def mock_get_properties(power_handle, properties_ptr):
            properties_ptr._obj.onSubdevice = True
            properties_ptr._obj.subdeviceId = 1
            properties_ptr._obj.canControl = True
            properties_ptr._obj.isEnergyThresholdSupported = True
            properties_ptr._obj.defaultLimit = mock_default_limit
            properties_ptr._obj.minLimit = mock_min_limit
            properties_ptr._obj.maxLimit = mock_max_limit

            ext_properties_ptr = cast(
                properties_ptr._obj.pNext,
                POINTER(self.pyzes.zes_power_ext_properties_t),
            )
            ext_properties_ptr.contents.domain = mock_domain
            ext_properties_ptr.contents.defaultLimit.contents.limit = (
                mock_ext_default_limit
            )
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_properties)
        mock_get_func.return_value = mock_func

        power_handle = self.pyzes.zes_pwr_handle_t()
        properties = self.pyzes.zes_power_properties_t()
        ext_properties = self.pyzes.zes_power_ext_properties_t()
        ext_default_limit = self.pyzes.zes_power_limit_ext_desc_t()

        properties.stype = self.pyzes.ZES_STRUCTURE_TYPE_POWER_PROPERTIES
        properties.pNext = cast(byref(ext_properties), c_void_p)
        ext_properties.stype = self.pyzes.ZES_STRUCTURE_TYPE_POWER_EXT_PROPERTIES
        ext_properties.defaultLimit = pointer(ext_default_limit)

        result = self.pyzes.zesPowerGetProperties(power_handle, byref(properties))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(properties.onSubdevice, True)
        self.assertEqual(properties.subdeviceId, 1)
        self.assertEqual(properties.canControl, True)
        self.assertEqual(properties.isEnergyThresholdSupported, True)
        self.assertEqual(properties.defaultLimit, mock_default_limit)
        self.assertEqual(properties.minLimit, mock_min_limit)
        self.assertEqual(properties.maxLimit, mock_max_limit)
        self.assertEqual(ext_properties.stype, self.pyzes.ZES_STRUCTURE_TYPE_POWER_EXT_PROPERTIES)
        self.assertEqual(ext_properties.domain, mock_domain)
        self.assertEqual(ext_properties.defaultLimit.contents.limit, mock_ext_default_limit)
        mock_get_func.assert_called_with("zesPowerGetProperties")
        mock_func.assert_called_once()

if __name__ == "__main__":
    unittest.main()
