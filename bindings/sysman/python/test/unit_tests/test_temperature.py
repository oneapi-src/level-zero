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
class TestTemperatureFunctions(unittest.TestCase):
    """Test temperature-related function wrappers."""

    def setUp(self):
        """Set up test fixtures before each test method."""
        import pyzes

        self.pyzes = pyzes

    def test_GivenValidDeviceHandleWhenCallingZesDeviceEnumTemperatureSensorsThenCallSucceedsWithValidCount(
        self, mock_get_func
    ):
        mock_sensor_count = 4

        def mock_enum_temperature_sensors(device_handle, count_ptr, handles_ptr):
            count_ptr._obj.value = mock_sensor_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_enum_temperature_sensors)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        count = c_uint32(0)

        result = self.pyzes.zesDeviceEnumTemperatureSensors(
            device_handle, byref(count), None
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_sensor_count)
        mock_get_func.assert_called_with("zesDeviceEnumTemperatureSensors")
        mock_func.assert_called_once()

    def test_GivenValidTemperatureHandleWhenCallingZesTemperatureGetPropertiesThenCallSucceedsWithValidProperties(
        self, mock_get_func
    ):
        mock_sensor_type = self.pyzes.ZES_TEMP_SENSORS_GPU
        mock_on_subdevice = False
        mock_subdevice_id = 0
        mock_max_temperature = 85.0
        mock_is_critical_temp_supported = True
        mock_is_threshold1_supported = False
        mock_is_threshold2_supported = True

        def mock_get_properties(temp_handle, properties_ptr):
            properties_ptr._obj.type = mock_sensor_type
            properties_ptr._obj.onSubdevice = mock_on_subdevice
            properties_ptr._obj.subdeviceId = mock_subdevice_id
            properties_ptr._obj.maxTemperature = mock_max_temperature
            properties_ptr._obj.isCriticalTempSupported = (
                mock_is_critical_temp_supported
            )
            properties_ptr._obj.isThreshold1Supported = mock_is_threshold1_supported
            properties_ptr._obj.isThreshold2Supported = mock_is_threshold2_supported
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_properties)
        mock_get_func.return_value = mock_func

        temp_handle = self.pyzes.zes_temp_handle_t()
        temp_props = self.pyzes.zes_temp_properties_t()
        result = self.pyzes.zesTemperatureGetProperties(temp_handle, byref(temp_props))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(temp_props.type, mock_sensor_type)
        self.assertEqual(temp_props.onSubdevice, mock_on_subdevice)
        self.assertEqual(temp_props.subdeviceId, mock_subdevice_id)
        self.assertEqual(temp_props.maxTemperature, mock_max_temperature)
        self.assertEqual(
            temp_props.isCriticalTempSupported, mock_is_critical_temp_supported
        )
        self.assertEqual(temp_props.isThreshold1Supported, mock_is_threshold1_supported)
        self.assertEqual(temp_props.isThreshold2Supported, mock_is_threshold2_supported)
        mock_get_func.assert_called_with("zesTemperatureGetProperties")
        mock_func.assert_called_once()

    def test_GivenValidTemperatureHandleWhenCallingZesTemperatureGetConfigThenCallSucceedsWithConfig(
        self, mock_get_func
    ):
        mock_enable_critical = True
        mock_threshold1 = 75.0
        mock_threshold2 = 80.0

        def mock_get_config(temp_handle, config_ptr):
            config_ptr._obj.enableCritical = mock_enable_critical
            config_ptr._obj.threshold1 = mock_threshold1
            config_ptr._obj.threshold2 = mock_threshold2
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_config)
        mock_get_func.return_value = mock_func

        temp_handle = self.pyzes.zes_temp_handle_t()
        temp_config = self.pyzes.zes_temp_config_t()
        result = self.pyzes.zesTemperatureGetConfig(temp_handle, byref(temp_config))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(temp_config.enableCritical, mock_enable_critical)
        self.assertEqual(temp_config.threshold1, mock_threshold1)
        self.assertEqual(temp_config.threshold2, mock_threshold2)
        mock_get_func.assert_called_with("zesTemperatureGetConfig")
        mock_func.assert_called_once()

    def test_GivenValidTemperatureHandleWhenCallingZesTemperatureGetStateThenCallSucceedsWithState(
        self, mock_get_func
    ):
        mock_temperature = 65.5  # Current temperature in Celsius

        def mock_get_state(temp_handle, temperature_ptr):
            temperature_ptr._obj.value = mock_temperature
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_state)
        mock_get_func.return_value = mock_func

        temp_handle = self.pyzes.zes_temp_handle_t()
        temperature = c_double()
        result = self.pyzes.zesTemperatureGetState(temp_handle, byref(temperature))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(temperature.value, mock_temperature)
        mock_get_func.assert_called_with("zesTemperatureGetState")
        mock_func.assert_called_once()


if __name__ == "__main__":
    unittest.main()
