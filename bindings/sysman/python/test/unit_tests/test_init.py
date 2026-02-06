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
class TestInitFunctions(unittest.TestCase):

    def setUp(self):
        import pyzes

        self.pyzes = pyzes

    def test_GivenvalidPyzesModuleWhenCallingZesInitThenCallSucceeds(
        self, mock_get_func
    ):
        mock_func = MagicMock()
        mock_func.return_value = self.pyzes.ZE_RESULT_SUCCESS
        mock_get_func.return_value = mock_func

        result = self.pyzes.zesInit(0)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.assert_called_with("zesInit")
        mock_func.assert_called_once()

    def test_GivenValidPyzesMouleWhenCallingZesDriverGetThenCallSucceedsWithValidCount(
        self, mock_get_func
    ):
        mock_driver_count = 1

        def mock_driver_get(count_ptr, drivers_ptr):
            count_ptr._obj.value = mock_driver_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_driver_get)
        mock_get_func.return_value = mock_func

        count = c_uint32(0)

        result = self.pyzes.zesDriverGet(byref(count), None)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_driver_count)
        mock_get_func.assert_called_with("zesDriverGet")
        mock_func.assert_called_once()

    def test_GivenValidDriverHandleWhenCallingZesDriverGetDeviceByUuidExpThenCallSucceedsWithDeviceInfo(
        self, mock_get_func
    ):
        mock_device_handle = 0x12345678
        mock_on_subdevice = False
        mock_subdevice_id = 0

        def mock_get_device_by_uuid(
            driver_handle, uuid, device_handle_ptr, on_subdevice_ptr, subdevice_id_ptr
        ):
            device_handle_ptr._obj.value = mock_device_handle
            on_subdevice_ptr._obj.value = mock_on_subdevice
            subdevice_id_ptr._obj.value = mock_subdevice_id
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_device_by_uuid)
        mock_get_func.return_value = mock_func

        driver_handle = self.pyzes.zes_driver_handle_t()
        uuid = self.pyzes.zes_uuid_t()
        device_handle = self.pyzes.zes_device_handle_t()
        on_subdevice = self.pyzes.ze_bool_t()
        subdevice_id = c_uint32()

        result = self.pyzes.zesDriverGetDeviceByUuidExp(
            driver_handle,
            uuid,
            byref(device_handle),
            byref(on_subdevice),
            byref(subdevice_id),
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(device_handle.value, mock_device_handle)
        self.assertEqual(on_subdevice.value, mock_on_subdevice)
        self.assertEqual(subdevice_id.value, mock_subdevice_id)
        mock_get_func.assert_called_with("zesDriverGetDeviceByUuidExp")
        mock_func.assert_called_once()


class TestInitInfrastructure(unittest.TestCase):

    def setUp(self):
        import pyzes

        self.pyzes = pyzes

    def test_GivenLibraryAlreadyLoadedWhenCallingLoadZeLibraryThenReturnsEarly(self):
        # Test early return when library already loaded
        original_gpuLib = self.pyzes.gpuLib

        # Set gpuLib to non-None to trigger early return
        mock_lib = MagicMock()
        self.pyzes.gpuLib = mock_lib

        try:
            # This should return early without any library loading
            with patch("builtins.print") as mock_print:
                self.pyzes._LoadZeLibrary()
                # Should not print "Loading Linux library" because it returns early
                print_calls = [
                    call.args[0] for call in mock_print.call_args_list if call.args
                ]
                self.assertNotIn("Loading Linux library", print_calls)
        finally:
            # Restore original state
            self.pyzes.gpuLib = original_gpuLib

    @patch("pyzes.gpuLib", None)
    def test_GivenLibraryNotLoadedWhenCallingGetFunctionPointerListThenRaisesException(
        self,
    ):
        # Test error handling path when library not loaded
        with patch("pyzes.libLoadLock") as mock_lock:
            mock_acquire = MagicMock()
            mock_release = MagicMock()
            mock_lock.acquire = mock_acquire
            mock_lock.release = mock_release

            with self.assertRaises(Exception) as context:
                self.pyzes.getFunctionPointerList("zesInit")

            self.assertIn("Library not loaded", str(context.exception))
            mock_acquire.assert_called_once()
            mock_release.assert_called_once()

    def test_GivenFunctionPointerAlreadyCachedWhenCallingGetFunctionPointerListThenReturnsCachedVersion(
        self,
    ):
        # Test caching logic in getFunctionPointerList
        mock_func_ptr = MagicMock()

        # Pre-populate cache
        original_cache = self.pyzes._getFunctionPointerList.copy()
        self.pyzes._getFunctionPointerList["testFunction"] = mock_func_ptr

        try:
            # This should return cached version without library access
            result = self.pyzes.getFunctionPointerList("testFunction")
            self.assertEqual(result, mock_func_ptr)
        finally:
            # Restore original cache
            self.pyzes._getFunctionPointerList.clear()
            self.pyzes._getFunctionPointerList.update(original_cache)

    @patch("pyzes.gpuLib")
    @patch("pyzes.libLoadLock")
    def test_GivenValidLibraryWhenGettingNewFunctionPointerThenCachesAndReturnsFunction(
        self, mock_lock, mock_lib
    ):
        # Test function pointer retrieval and caching
        mock_acquire = MagicMock()
        mock_release = MagicMock()
        mock_lock.acquire = mock_acquire
        mock_lock.release = mock_release

        mock_function = MagicMock()
        mock_lib.testNewFunction = mock_function

        # Clear cache for this test
        original_cache = self.pyzes._getFunctionPointerList.copy()
        self.pyzes._getFunctionPointerList.clear()

        try:
            result = self.pyzes.getFunctionPointerList("testNewFunction")

            # Verify function was retrieved and cached
            self.assertEqual(result, mock_function)
            self.assertEqual(
                self.pyzes._getFunctionPointerList["testNewFunction"], mock_function
            )
            mock_acquire.assert_called_once()
            mock_release.assert_called_once()
        finally:
            # Restore original cache
            self.pyzes._getFunctionPointerList.clear()
            self.pyzes._getFunctionPointerList.update(original_cache)

    @patch("sys.platform", "win32")
    @patch("pyzes.gpuLib", None)
    @patch("builtins.print")
    @patch("os.path.exists")
    @patch("pyzes.CDLL")
    def test_GivenWindowsPlatformWhenLoadingLibraryThenLibraryIsLoaded(
        self, mock_cdll, mock_exists, mock_print
    ):
        # Test Windows library loading path with deterministic mocking
        mock_exists.return_value = True
        mock_lib = MagicMock()
        mock_cdll.return_value = mock_lib

        self.pyzes._LoadZeLibrary()

        # Verify Windows-specific print was called
        mock_print.assert_any_call("Loading Windows library")
        # Verify successful library loading
        mock_cdll.assert_called()


if __name__ == "__main__":
    unittest.main()
