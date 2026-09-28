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
class TestStandbyFunctions(unittest.TestCase):
    def setUp(self):
        import pyzes

        self.pyzes = pyzes

    def test_GivenValidDeviceHandleWhenCallingZesDeviceEnumStandbyDomainsThenCallSucceedsWithValidCount(
        self, mock_get_func
    ):
        mock_count = 1

        def mock_enum_standby(device_handle, count_ptr, handles_ptr):
            count_ptr._obj.value = mock_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_enum_standby)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        count = c_uint32(0)

        result = self.pyzes.zesDeviceEnumStandbyDomains(
            device_handle, byref(count), None
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_count)
        mock_get_func.assert_called_with("zesDeviceEnumStandbyDomains")
        mock_func.assert_called_once()

    def test_GivenValidStandbyHandleWhenCallingZesStandbyGetPropertiesThenCallSucceedsWithValidProperties(
        self, mock_get_func
    ):
        def mock_get_properties(standby_handle, properties_ptr):
            properties = properties_ptr._obj
            properties.type = self.pyzes.ZES_STANDBY_TYPE_GLOBAL
            properties.onSubdevice = 1
            properties.subdeviceId = 1
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_properties)
        mock_get_func.return_value = mock_func

        standby_handle = self.pyzes.zes_standby_handle_t()
        properties = self.pyzes.zes_standby_properties_t()
        properties.stype = self.pyzes.ZES_STRUCTURE_TYPE_STANDBY_PROPERTIES

        result = self.pyzes.zesStandbyGetProperties(standby_handle, byref(properties))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(properties.type, self.pyzes.ZES_STANDBY_TYPE_GLOBAL)
        self.assertEqual(properties.onSubdevice, 1)
        self.assertEqual(properties.subdeviceId, 1)
        mock_get_func.assert_called_with("zesStandbyGetProperties")
        mock_func.assert_called_once()

    def test_GivenValidStandbyHandleWhenCallingZesStandbyGetModeThenCallSucceedsWithMode(
        self, mock_get_func
    ):
        def mock_get_mode(standby_handle, mode_ptr):
            mode_ptr._obj.value = self.pyzes.ZES_STANDBY_PROMO_MODE_NEVER
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_mode)
        mock_get_func.return_value = mock_func

        standby_handle = self.pyzes.zes_standby_handle_t()
        mode = self.pyzes.zes_standby_promo_mode_t(0)

        result = self.pyzes.zesStandbyGetMode(standby_handle, byref(mode))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(mode.value, self.pyzes.ZES_STANDBY_PROMO_MODE_NEVER)
        mock_get_func.assert_called_with("zesStandbyGetMode")
        mock_func.assert_called_once()

    def test_GivenValidStandbyHandleWhenCallingZesStandbySetModeThenCallSucceeds(
        self, mock_get_func
    ):
        mock_func = MagicMock(return_value=self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.return_value = mock_func

        standby_handle = self.pyzes.zes_standby_handle_t()

        result = self.pyzes.zesStandbySetMode(
            standby_handle, self.pyzes.ZES_STANDBY_PROMO_MODE_DEFAULT
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.assert_called_with("zesStandbySetMode")
        mock_func.assert_called_once_with(
            standby_handle, self.pyzes.ZES_STANDBY_PROMO_MODE_DEFAULT
        )


if __name__ == "__main__":
    unittest.main()
