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
class TestRasFunctions(unittest.TestCase):
    def setUp(self):
        import pyzes

        self.pyzes = pyzes

    def test_GivenValidDeviceHandleWhenCallingZesDeviceEnumRasErrorSetsThenCallSucceedsWithValidCount(
        self, mock_get_func
    ):
        mock_count = 2

        def mock_enum_ras(device_handle, count_ptr, handles_ptr):
            count_ptr._obj.value = mock_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_enum_ras)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        count = c_uint32(0)

        result = self.pyzes.zesDeviceEnumRasErrorSets(device_handle, byref(count), None)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_count)
        mock_get_func.assert_called_with("zesDeviceEnumRasErrorSets")
        mock_func.assert_called_once()

    def test_GivenValidRasHandleWhenCallingZesRasGetPropertiesThenCallSucceedsWithValidProperties(
        self, mock_get_func
    ):
        def mock_get_properties(ras_handle, properties_ptr):
            properties = properties_ptr._obj
            properties.type = self.pyzes.ZES_RAS_ERROR_TYPE_UNCORRECTABLE
            properties.onSubdevice = 1
            properties.subdeviceId = 1
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_properties)
        mock_get_func.return_value = mock_func

        ras_handle = self.pyzes.zes_ras_handle_t()
        properties = self.pyzes.zes_ras_properties_t()
        properties.stype = self.pyzes.ZES_STRUCTURE_TYPE_RAS_PROPERTIES

        result = self.pyzes.zesRasGetProperties(ras_handle, byref(properties))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(properties.type, self.pyzes.ZES_RAS_ERROR_TYPE_UNCORRECTABLE)
        self.assertEqual(properties.onSubdevice, 1)
        self.assertEqual(properties.subdeviceId, 1)
        mock_get_func.assert_called_with("zesRasGetProperties")
        mock_func.assert_called_once()

    def test_GivenValidRasHandleWhenCallingZesRasGetSupportedCategoriesExpThenCallSucceedsWithCategories(
        self, mock_get_func
    ):
        mock_count = 3

        def mock_get_categories(ras_handle, count_ptr, categories_ptr):
            count_ptr._obj.value = mock_count
            categories_ptr[0] = self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_RESET
            categories_ptr[1] = self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_CACHE_ERRORS
            categories_ptr[2] = self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_MEMORY_ERRORS
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_categories)
        mock_get_func.return_value = mock_func

        ras_handle = self.pyzes.zes_ras_handle_t()
        count = c_uint32(mock_count)
        categories = (self.pyzes.zes_ras_error_category_exp_t * mock_count)()

        result = self.pyzes.zesRasGetSupportedCategoriesExp(
            ras_handle, byref(count), categories
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_count)
        self.assertEqual(categories[0], self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_RESET)
        self.assertEqual(
            categories[1], self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_CACHE_ERRORS
        )
        self.assertEqual(
            categories[2], self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_MEMORY_ERRORS
        )
        mock_get_func.assert_called_with("zesRasGetSupportedCategoriesExp")
        mock_func.assert_called_once()

    def test_GivenValidRasHandleWhenCallingZesRasGetStateExp2ThenCallSucceedsWithErrorCounters(
        self, mock_get_func
    ):
        mock_count = 2

        def mock_get_state(ras_handle, count, categories_ptr, state_ptr):
            self.assertEqual(count, mock_count)
            self.assertEqual(
                categories_ptr[0], self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_RESET
            )
            self.assertEqual(
                categories_ptr[1], self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_PCIE_ERRORS
            )
            state_ptr[0].errorCounter = 5
            state_ptr[1].errorCounter = 12
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_state)
        mock_get_func.return_value = mock_func

        ras_handle = self.pyzes.zes_ras_handle_t()
        categories = (self.pyzes.zes_ras_error_category_exp_t * mock_count)(
            self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_RESET,
            self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_PCIE_ERRORS,
        )
        states = (self.pyzes.zes_ras_state_exp2_t * mock_count)()
        for i in range(mock_count):
            states[i].stype = self.pyzes.ZES_STRUCTURE_TYPE_RAS_STATE_EXP2
            states[i].pNext = None

        result = self.pyzes.zesRasGetStateExp2(
            ras_handle, mock_count, categories, states
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(states[0].errorCounter, 5)
        self.assertEqual(states[1].errorCounter, 12)
        mock_get_func.assert_called_with("zesRasGetStateExp2")
        mock_func.assert_called_once()

    def test_GivenValidRasHandleWhenCallingZesRasGetConfigExpThenCallSucceedsWithThresholds(
        self, mock_get_func
    ):
        mock_count = 2

        def mock_get_config(ras_handle, count, config_ptr):
            self.assertEqual(count, mock_count)
            self.assertEqual(
                config_ptr[0].category,
                self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_COMPUTE_ERRORS,
            )
            self.assertEqual(
                config_ptr[1].category,
                self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_FABRIC_ERRORS,
            )
            config_ptr[0].threshold = 100
            config_ptr[1].threshold = 0
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_config)
        mock_get_func.return_value = mock_func

        ras_handle = self.pyzes.zes_ras_handle_t()
        configs = (self.pyzes.zes_ras_config_exp_t * mock_count)()
        configs[0].stype = self.pyzes.ZES_STRUCTURE_TYPE_RAS_CONFIG_EXP
        configs[0].category = self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_COMPUTE_ERRORS
        configs[1].stype = self.pyzes.ZES_STRUCTURE_TYPE_RAS_CONFIG_EXP
        configs[1].category = self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_FABRIC_ERRORS

        result = self.pyzes.zesRasGetConfigExp(ras_handle, mock_count, configs)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(configs[0].threshold, 100)
        self.assertEqual(configs[1].threshold, 0)
        mock_get_func.assert_called_with("zesRasGetConfigExp")
        mock_func.assert_called_once()

    def test_GivenValidRasHandleWhenCallingZesRasSetConfigExpThenCallSucceeds(
        self, mock_get_func
    ):
        def mock_set_config(ras_handle, count, config_ptr):
            self.assertEqual(count, 1)
            self.assertEqual(
                config_ptr[0].stype, self.pyzes.ZES_STRUCTURE_TYPE_RAS_CONFIG_EXP
            )
            self.assertEqual(
                config_ptr[0].category,
                self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_CACHE_ERRORS,
            )
            self.assertEqual(config_ptr[0].threshold, 50)
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_set_config)
        mock_get_func.return_value = mock_func

        ras_handle = self.pyzes.zes_ras_handle_t()
        configs = (self.pyzes.zes_ras_config_exp_t * 1)()
        configs[0].stype = self.pyzes.ZES_STRUCTURE_TYPE_RAS_CONFIG_EXP
        configs[0].category = self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_CACHE_ERRORS
        configs[0].threshold = 50

        result = self.pyzes.zesRasSetConfigExp(ras_handle, 1, configs)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.assert_called_with("zesRasSetConfigExp")
        mock_func.assert_called_once()

    def test_GivenValidRasHandleWhenCallingZesRasClearStateExpThenCallSucceeds(
        self, mock_get_func
    ):
        mock_func = MagicMock(return_value=self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.return_value = mock_func

        ras_handle = self.pyzes.zes_ras_handle_t()

        result = self.pyzes.zesRasClearStateExp(
            ras_handle, self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_RESET
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.assert_called_with("zesRasClearStateExp")
        mock_func.assert_called_once_with(
            ras_handle, self.pyzes.ZES_RAS_ERROR_CATEGORY_EXP_RESET
        )


if __name__ == "__main__":
    unittest.main()
