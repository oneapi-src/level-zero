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
class TestVFManagementFunctions(unittest.TestCase):
    def setUp(self):
        import pyzes

        self.pyzes = pyzes

    def test_GivenValidDeviceHandleWhenCallingZesDeviceEnumEnabledVFExpThenCallSucceedsWithValidCount(
        self, mock_get_func
    ):
        mock_count = 2

        def mock_enum_vf(device_handle, count_ptr, handles_ptr):
            count_ptr._obj.value = mock_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_enum_vf)
        mock_get_func.return_value = mock_func

        device_handle = self.pyzes.zes_device_handle_t()
        count = c_uint32(0)

        result = self.pyzes.zesDeviceEnumEnabledVFExp(device_handle, byref(count), None)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_count)
        mock_get_func.assert_called_with("zesDeviceEnumEnabledVFExp")
        mock_func.assert_called_once()

    def test_GivenValidVFHandleWhenCallingZesVFManagementGetVFCapabilitiesExp2ThenCallSucceedsWithCapabilities(
        self, mock_get_func
    ):
        def mock_get_capabilities(vf_handle, capability_ptr):
            capability = capability_ptr._obj
            capability.address.domain = 0
            capability.address.bus = 0x3A
            capability.address.device = 0
            capability.address.function = 1
            capability.vfDeviceMemSize = 4 * 1024 * 1024 * 1024
            capability.vfID = 1
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_capabilities)
        mock_get_func.return_value = mock_func

        vf_handle = self.pyzes.zes_vf_handle_t()
        capability = self.pyzes.zes_vf_exp2_capabilities_t()
        capability.stype = self.pyzes.ZES_STRUCTURE_TYPE_VF_EXP2_CAPABILITIES

        result = self.pyzes.zesVFManagementGetVFCapabilitiesExp2(
            vf_handle, byref(capability)
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(capability.address.bus, 0x3A)
        self.assertEqual(capability.address.function, 1)
        self.assertEqual(capability.vfDeviceMemSize, 4 * 1024 * 1024 * 1024)
        self.assertEqual(capability.vfID, 1)
        mock_get_func.assert_called_with("zesVFManagementGetVFCapabilitiesExp2")
        mock_func.assert_called_once()

    def test_GivenValidVFHandleWhenCallingZesVFManagementGetVFEngineUtilizationExp2ThenCallSucceedsWithUtilization(
        self, mock_get_func
    ):
        mock_count = 2

        def mock_get_engine_util(vf_handle, count_ptr, util_ptr):
            count_ptr._obj.value = mock_count
            util_ptr[0].vfEngineType = self.pyzes.ZES_ENGINE_GROUP_COMPUTE_ALL
            util_ptr[0].activeCounterValue = 1200
            util_ptr[0].samplingCounterValue = 5000
            util_ptr[1].vfEngineType = self.pyzes.ZES_ENGINE_GROUP_COPY_ALL
            util_ptr[1].activeCounterValue = 300
            util_ptr[1].samplingCounterValue = 5000
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_engine_util)
        mock_get_func.return_value = mock_func

        vf_handle = self.pyzes.zes_vf_handle_t()
        count = c_uint32(mock_count)
        engine_util = (self.pyzes.zes_vf_util_engine_exp2_t * mock_count)()
        for i in range(mock_count):
            engine_util[i].stype = self.pyzes.ZES_STRUCTURE_TYPE_VF_UTIL_ENGINE_EXP2

        result = self.pyzes.zesVFManagementGetVFEngineUtilizationExp2(
            vf_handle, byref(count), engine_util
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_count)
        self.assertEqual(
            engine_util[0].vfEngineType, self.pyzes.ZES_ENGINE_GROUP_COMPUTE_ALL
        )
        self.assertEqual(engine_util[0].activeCounterValue, 1200)
        self.assertEqual(engine_util[0].samplingCounterValue, 5000)
        self.assertEqual(
            engine_util[1].vfEngineType, self.pyzes.ZES_ENGINE_GROUP_COPY_ALL
        )
        self.assertEqual(engine_util[1].activeCounterValue, 300)
        mock_get_func.assert_called_with("zesVFManagementGetVFEngineUtilizationExp2")
        mock_func.assert_called_once()

    def test_GivenValidVFHandleWhenCallingZesVFManagementGetVFMemoryUtilizationExp2ThenCallSucceedsWithUtilization(
        self, mock_get_func
    ):
        mock_count = 2

        def mock_get_mem_util(vf_handle, count_ptr, util_ptr):
            count_ptr._obj.value = mock_count
            util_ptr[0].vfMemLocation = self.pyzes.ZES_MEM_LOC_SYSTEM
            util_ptr[0].vfMemUtilized = 1024
            util_ptr[1].vfMemLocation = self.pyzes.ZES_MEM_LOC_DEVICE
            util_ptr[1].vfMemUtilized = 2048
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_mem_util)
        mock_get_func.return_value = mock_func

        vf_handle = self.pyzes.zes_vf_handle_t()
        count = c_uint32(mock_count)
        mem_util = (self.pyzes.zes_vf_util_mem_exp2_t * mock_count)()
        for i in range(mock_count):
            mem_util[i].stype = self.pyzes.ZES_STRUCTURE_TYPE_VF_UTIL_MEM_EXP2

        result = self.pyzes.zesVFManagementGetVFMemoryUtilizationExp2(
            vf_handle, byref(count), mem_util
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_count)
        self.assertEqual(mem_util[0].vfMemLocation, self.pyzes.ZES_MEM_LOC_SYSTEM)
        self.assertEqual(mem_util[0].vfMemUtilized, 1024)
        self.assertEqual(mem_util[1].vfMemLocation, self.pyzes.ZES_MEM_LOC_DEVICE)
        self.assertEqual(mem_util[1].vfMemUtilized, 2048)
        mock_get_func.assert_called_with("zesVFManagementGetVFMemoryUtilizationExp2")
        mock_func.assert_called_once()


if __name__ == "__main__":
    unittest.main()
