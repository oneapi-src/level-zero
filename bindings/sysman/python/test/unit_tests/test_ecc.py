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
class TestEccFunctions(unittest.TestCase):
    def setUp(self):
        import pyzes

        self.pyzes = pyzes

    def test_GivenValidDeviceHandleWhenCallingZesDeviceEccAvailableThenCallSucceedsWithAvailability(
        self, mock_get_func
    ):
        mock_available = 1

        def mock_ecc_available(device_handle, available_ptr):
            available_ptr._obj.value = mock_available
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_ecc_available)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        available = self.pyzes.ze_bool_t(0)

        result = self.pyzes.zesDeviceEccAvailable(device_handle, byref(available))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(available.value, mock_available)
        mock_get_func.assert_called_with("zesDeviceEccAvailable")
        mock_func.assert_called_once()

    def test_GivenValidDeviceHandleWhenCallingZesDeviceEccConfigurableThenCallSucceedsWithConfigurability(
        self, mock_get_func
    ):
        mock_configurable = 1

        def mock_ecc_configurable(device_handle, configurable_ptr):
            configurable_ptr._obj.value = mock_configurable
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_ecc_configurable)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        configurable = self.pyzes.ze_bool_t(0)

        result = self.pyzes.zesDeviceEccConfigurable(device_handle, byref(configurable))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(configurable.value, mock_configurable)
        mock_get_func.assert_called_with("zesDeviceEccConfigurable")
        mock_func.assert_called_once()

    def test_GivenValidDeviceHandleWhenCallingZesDeviceGetEccStateThenCallSucceedsWithState(
        self, mock_get_func
    ):
        mock_current_state = self.pyzes.ZES_DEVICE_ECC_STATE_ENABLED
        mock_pending_state = self.pyzes.ZES_DEVICE_ECC_STATE_DISABLED
        mock_pending_action = self.pyzes.ZES_DEVICE_ACTION_WARM_CARD_RESET

        def mock_get_ecc_state(device_handle, state_ptr):
            state_ptr._obj.currentState = mock_current_state
            state_ptr._obj.pendingState = mock_pending_state
            state_ptr._obj.pendingAction = mock_pending_action
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_ecc_state)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        ecc_state = self.pyzes.zes_device_ecc_properties_t()

        result = self.pyzes.zesDeviceGetEccState(device_handle, byref(ecc_state))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(ecc_state.currentState, mock_current_state)
        self.assertEqual(ecc_state.pendingState, mock_pending_state)
        self.assertEqual(ecc_state.pendingAction, mock_pending_action)
        mock_get_func.assert_called_with("zesDeviceGetEccState")
        mock_func.assert_called_once()

    def test_GivenValidDeviceHandleWhenCallingZesDeviceSetEccStateThenCallSucceedsWithUpdatedState(
        self, mock_get_func
    ):
        requested_state = self.pyzes.ZES_DEVICE_ECC_STATE_ENABLED
        mock_current_state = self.pyzes.ZES_DEVICE_ECC_STATE_DISABLED
        mock_pending_state = self.pyzes.ZES_DEVICE_ECC_STATE_ENABLED
        mock_pending_action = self.pyzes.ZES_DEVICE_ACTION_COLD_CARD_RESET

        def mock_set_ecc_state(device_handle, new_state_ptr, state_ptr):
            self.assertEqual(new_state_ptr._obj.state, requested_state)
            state_ptr._obj.currentState = mock_current_state
            state_ptr._obj.pendingState = mock_pending_state
            state_ptr._obj.pendingAction = mock_pending_action
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_set_ecc_state)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        new_state = self.pyzes.zes_device_ecc_desc_t()
        new_state.stype = self.pyzes.ZES_STRUCTURE_TYPE_DEVICE_ECC_DESC
        new_state.state = requested_state
        ecc_state = self.pyzes.zes_device_ecc_properties_t()

        result = self.pyzes.zesDeviceSetEccState(
            device_handle, byref(new_state), byref(ecc_state)
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(ecc_state.currentState, mock_current_state)
        self.assertEqual(ecc_state.pendingState, mock_pending_state)
        self.assertEqual(ecc_state.pendingAction, mock_pending_action)
        mock_get_func.assert_called_with("zesDeviceSetEccState")
        mock_func.assert_called_once()


if __name__ == "__main__":
    unittest.main()
