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

    def test_GivenValidPowerHandleWhenCallingZesPowerGetPropertiesThenCallSucceedsWithDomainData(
        self, mock_get_func
    ):
        def mock_get_properties(power_handle, properties_ptr):
            properties = properties_ptr._obj
            properties.onSubdevice = 1
            properties.subdeviceId = 3
            properties.canControl = 1
            properties.isEnergyThresholdSupported = 1
            properties.defaultLimit = 250000
            properties.minLimit = 150000
            properties.maxLimit = 300000

            ext_properties_ptr = cast(
                properties.pNext, POINTER(self.pyzes.zes_power_ext_properties_t)
            )
            ext_properties_ptr.contents.domain = self.pyzes.ZES_POWER_DOMAIN_GPU
            ext_properties_ptr.contents.defaultLimit.contents.level = (
                self.pyzes.ZES_POWER_LEVEL_SUSTAINED
            )
            ext_properties_ptr.contents.defaultLimit.contents.limit = 250000
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_properties)
        mock_get_func.return_value = mock_func

        power_handle = self.pyzes.zes_pwr_handle_t()
        default_limit = self.pyzes.zes_power_limit_ext_desc_t()
        ext_properties = self.pyzes.zes_power_ext_properties_t()
        ext_properties.stype = self.pyzes.ZES_STRUCTURE_TYPE_POWER_EXT_PROPERTIES
        ext_properties.defaultLimit = pointer(default_limit)

        properties = self.pyzes.zes_power_properties_t()
        properties.stype = self.pyzes.ZES_STRUCTURE_TYPE_POWER_PROPERTIES
        properties.pNext = cast(pointer(ext_properties), c_void_p)

        result = self.pyzes.zesPowerGetProperties(power_handle, byref(properties))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(properties.onSubdevice, 1)
        self.assertEqual(properties.subdeviceId, 3)
        self.assertEqual(properties.canControl, 1)
        self.assertEqual(properties.isEnergyThresholdSupported, 1)
        self.assertEqual(properties.defaultLimit, 250000)
        self.assertEqual(properties.minLimit, 150000)
        self.assertEqual(properties.maxLimit, 300000)
        self.assertEqual(ext_properties.domain, self.pyzes.ZES_POWER_DOMAIN_GPU)
        self.assertEqual(
            ext_properties.defaultLimit.contents.level,
            self.pyzes.ZES_POWER_LEVEL_SUSTAINED,
        )
        self.assertEqual(ext_properties.defaultLimit.contents.limit, 250000)
        mock_get_func.assert_called_with("zesPowerGetProperties")
        mock_func.assert_called_once()

    def test_GivenValidPowerHandleWhenCallingZesPowerGetLimitsExtThenCallSucceedsWithDescriptors(
        self, mock_get_func
    ):
        mock_count = 2

        def mock_get_limits_ext(power_handle, count_ptr, limits_ptr):
            count_ptr._obj.value = mock_count
            limits_ptr[0].level = self.pyzes.ZES_POWER_LEVEL_SUSTAINED
            limits_ptr[0].source = self.pyzes.ZES_POWER_SOURCE_MAINS
            limits_ptr[0].limitUnit = self.pyzes.ZES_LIMIT_UNIT_POWER
            limits_ptr[0].enabled = 1
            limits_ptr[0].interval = 1000
            limits_ptr[0].limit = 250000
            limits_ptr[1].level = self.pyzes.ZES_POWER_LEVEL_BURST
            limits_ptr[1].source = self.pyzes.ZES_POWER_SOURCE_ANY
            limits_ptr[1].limitUnit = self.pyzes.ZES_LIMIT_UNIT_POWER
            limits_ptr[1].enabled = 0
            limits_ptr[1].interval = 0
            limits_ptr[1].limit = 300000
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_limits_ext)
        mock_get_func.return_value = mock_func

        power_handle = self.pyzes.zes_pwr_handle_t()
        count = c_uint32(mock_count)
        limits = (self.pyzes.zes_power_limit_ext_desc_t * mock_count)()

        result = self.pyzes.zesPowerGetLimitsExt(power_handle, byref(count), limits)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_count)
        self.assertEqual(limits[0].level, self.pyzes.ZES_POWER_LEVEL_SUSTAINED)
        self.assertEqual(limits[0].source, self.pyzes.ZES_POWER_SOURCE_MAINS)
        self.assertEqual(limits[0].limit, 250000)
        self.assertEqual(limits[1].level, self.pyzes.ZES_POWER_LEVEL_BURST)
        self.assertEqual(limits[1].enabled, 0)
        self.assertEqual(limits[1].limit, 300000)
        mock_get_func.assert_called_with("zesPowerGetLimitsExt")
        mock_func.assert_called_once()

    def test_GivenValidPowerHandleWhenCallingZesPowerSetLimitsExtThenCallSucceeds(
        self, mock_get_func
    ):
        def mock_set_limits_ext(power_handle, count_ptr, limits_ptr):
            self.assertEqual(count_ptr._obj.value, 1)
            self.assertEqual(limits_ptr[0].level, self.pyzes.ZES_POWER_LEVEL_SUSTAINED)
            self.assertEqual(limits_ptr[0].source, self.pyzes.ZES_POWER_SOURCE_MAINS)
            self.assertEqual(limits_ptr[0].limitUnit, self.pyzes.ZES_LIMIT_UNIT_POWER)
            self.assertEqual(limits_ptr[0].enabled, 1)
            self.assertEqual(limits_ptr[0].interval, 2000)
            self.assertEqual(limits_ptr[0].limit, 275000)
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_set_limits_ext)
        mock_get_func.return_value = mock_func

        power_handle = self.pyzes.zes_pwr_handle_t()
        count = c_uint32(1)
        limits = (self.pyzes.zes_power_limit_ext_desc_t * 1)()
        limits[0].stype = self.pyzes.ZES_STRUCTURE_TYPE_POWER_LIMIT_EXT_DESC
        limits[0].level = self.pyzes.ZES_POWER_LEVEL_SUSTAINED
        limits[0].source = self.pyzes.ZES_POWER_SOURCE_MAINS
        limits[0].limitUnit = self.pyzes.ZES_LIMIT_UNIT_POWER
        limits[0].enabled = 1
        limits[0].interval = 2000
        limits[0].limit = 275000

        result = self.pyzes.zesPowerSetLimitsExt(power_handle, byref(count), limits)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.assert_called_with("zesPowerSetLimitsExt")
        mock_func.assert_called_once()

    def test_GivenValidPowerHandleWhenCallingZesPowerGetUsageThenCallSucceedsWithUsageData(
        self, mock_get_func
    ):
        def mock_get_usage(power_handle, instant_ptr, average_ptr):
            instant_ptr._obj.value = 45000
            average_ptr._obj.value = 40000
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
        self.assertEqual(instant_power.value, 45000)
        self.assertEqual(average_power.value, 40000)
        mock_get_func.assert_called_with("zesPowerGetUsage")
        mock_func.assert_called_once()

    def test_GivenValidPowerHandleWhenCallingZesPowerGetUsageWithOnlyInstantPowerThenCallSucceeds(
        self, mock_get_func
    ):
        def mock_get_usage(power_handle, instant_ptr, average_ptr):
            self.assertIsNone(average_ptr)
            instant_ptr._obj.value = 45000
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_usage)
        mock_get_func.return_value = mock_func

        power_handle = self.pyzes.zes_pwr_handle_t()
        instant_power = c_uint32(0)

        result = self.pyzes.zesPowerGetUsage(power_handle, byref(instant_power), None)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(instant_power.value, 45000)
        mock_get_func.assert_called_with("zesPowerGetUsage")
        mock_func.assert_called_once()

    def test_GivenValidPowerHandleWhenCallingZesPowerGetLimitsExt2ThenCallSucceedsWithLimit(
        self, mock_get_func
    ):
        def mock_get_limits_ext2(power_handle, limit_ptr):
            limit_ptr._obj.value = 250000
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_limits_ext2)
        mock_get_func.return_value = mock_func

        power_handle = self.pyzes.zes_pwr_handle_t()
        limit = c_uint32(0)

        result = self.pyzes.zesPowerGetLimitsExt2(power_handle, byref(limit))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(limit.value, 250000)
        mock_get_func.assert_called_with("zesPowerGetLimitsExt2")
        mock_func.assert_called_once()

    def test_GivenValidPowerHandleWhenCallingZesPowerSetLimitsExt2ThenCallSucceeds(
        self, mock_get_func
    ):
        mock_func = MagicMock(return_value=self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.return_value = mock_func

        power_handle = self.pyzes.zes_pwr_handle_t()

        result = self.pyzes.zesPowerSetLimitsExt2(power_handle, 275000)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.assert_called_with("zesPowerSetLimitsExt2")
        mock_func.assert_called_once_with(power_handle, 275000)

    def test_GivenValidPowerHandleWhenCallingZesPowerGetEnergyThresholdThenCallSucceedsWithThresholdData(
        self, mock_get_func
    ):
        def mock_get_energy_threshold(power_handle, threshold_ptr):
            threshold_ptr._obj.enable = 1
            threshold_ptr._obj.threshold = 1500.5
            threshold_ptr._obj.processId = 4321
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_energy_threshold)
        mock_get_func.return_value = mock_func

        power_handle = self.pyzes.zes_pwr_handle_t()
        threshold = self.pyzes.zes_energy_threshold_t()

        result = self.pyzes.zesPowerGetEnergyThreshold(power_handle, byref(threshold))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(threshold.enable, 1)
        self.assertEqual(threshold.threshold, 1500.5)
        self.assertEqual(threshold.processId, 4321)
        mock_get_func.assert_called_with("zesPowerGetEnergyThreshold")
        mock_func.assert_called_once()

    def test_GivenValidPowerHandleWhenCallingZesPowerSetEnergyThresholdThenCallSucceeds(
        self, mock_get_func
    ):
        mock_func = MagicMock(return_value=self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.return_value = mock_func

        power_handle = self.pyzes.zes_pwr_handle_t()

        result = self.pyzes.zesPowerSetEnergyThreshold(power_handle, 1500.5)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.assert_called_with("zesPowerSetEnergyThreshold")
        mock_func.assert_called_once_with(power_handle, 1500.5)


if __name__ == "__main__":
    unittest.main()
