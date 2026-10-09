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
class TestInfoLogFunctions(unittest.TestCase):
    def setUp(self):
        import pyzes

        self.pyzes = pyzes

    def test_GivenValidDriverHandleWhenCallingZesDriverEnumInfoLogsExtThenCallSucceedsWithValidCount(
        self, mock_get_func
    ):
        mock_count = 1

        def mock_enum_info_logs(driver_handle, count_ptr, handles_ptr):
            count_ptr._obj.value = mock_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_enum_info_logs)
        mock_get_func.return_value = mock_func

        driver_handle = self.pyzes.zes_driver_handle_t()
        count = c_uint32(0)

        result = self.pyzes.zesDriverEnumInfoLogsExt(driver_handle, byref(count), None)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_count)
        mock_get_func.assert_called_with("zesDriverEnumInfoLogsExt")
        mock_func.assert_called_once()

    def test_GivenValidInfoLogHandleWhenCallingZesInfoLogGetPropertiesExtThenCallSucceedsWithValidProperties(
        self, mock_get_func
    ):
        def mock_get_properties(info_log_handle, properties_ptr):
            properties = properties_ptr._obj
            properties.infoLogType = self.pyzes.ZES_INFO_LOG_TYPE_EXT_DEVICE
            properties.infoLogFormat = self.pyzes.ZES_INFO_LOG_FORMAT_EXT_CPER
            properties.isNamedInstanceSupported = 1
            properties.isPeekDataSupported = 1
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_properties)
        mock_get_func.return_value = mock_func

        info_log_handle = self.pyzes.zes_info_log_handle_t()
        properties = self.pyzes.zes_info_log_ext_properties_t()
        properties.stype = self.pyzes.ZES_STRUCTURE_TYPE_INFO_LOG_EXT_PROPERTIES

        result = self.pyzes.zesInfoLogGetPropertiesExt(
            info_log_handle, byref(properties)
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(
            properties.infoLogType, self.pyzes.ZES_INFO_LOG_TYPE_EXT_DEVICE
        )
        self.assertEqual(
            properties.infoLogFormat, self.pyzes.ZES_INFO_LOG_FORMAT_EXT_CPER
        )
        self.assertEqual(properties.isNamedInstanceSupported, 1)
        self.assertEqual(properties.isPeekDataSupported, 1)
        mock_get_func.assert_called_with("zesInfoLogGetPropertiesExt")
        mock_func.assert_called_once()

    def test_GivenValidInfoLogHandleWhenCallingZesInfoLogCreateInstanceExtThenCallSucceedsWithInstanceHandle(
        self, mock_get_func
    ):
        def mock_create_instance(info_log_handle, name, desc_ptr, instance_ptr):
            self.assertEqual(name, b"pyzes_instance")
            desc = desc_ptr._obj
            self.assertEqual(
                desc.stype, self.pyzes.ZES_STRUCTURE_TYPE_INFO_LOG_INSTANCE_EXT_DESC
            )
            # Driver reports the buffer size it actually applied
            desc.pBufferSizeInKb[0] = 64
            instance_ptr._obj.value = 0x1234
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_create_instance)
        mock_get_func.return_value = mock_func

        info_log_handle = self.pyzes.zes_info_log_handle_t()
        buffer_size_kb = c_uint32(0)
        desc = self.pyzes.zes_info_log_instance_ext_desc_t()
        desc.stype = self.pyzes.ZES_STRUCTURE_TYPE_INFO_LOG_INSTANCE_EXT_DESC
        desc.pBufferSizeInKb = pointer(buffer_size_kb)
        instance_handle = self.pyzes.zes_info_log_instance_handle_t()

        result = self.pyzes.zesInfoLogCreateInstanceExt(
            info_log_handle, b"pyzes_instance", byref(desc), byref(instance_handle)
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(buffer_size_kb.value, 64)
        self.assertEqual(instance_handle.value, 0x1234)
        mock_get_func.assert_called_with("zesInfoLogCreateInstanceExt")
        mock_func.assert_called_once()

    def test_GivenValidInstanceHandleWhenCallingZesInfoLogInstanceReadWithMetadataExtWithZeroSizeThenQueryReturnsSizeAndRecordCount(
        self, mock_get_func
    ):
        def mock_query(
            instance_handle,
            timeout,
            size_ptr,
            buffer,
            count_ptr,
            descriptors,
            status_ptr,
        ):
            self.assertEqual(timeout, 1000)
            self.assertIsNone(buffer)
            self.assertIsNone(descriptors)
            size_ptr._obj.value = 512
            count_ptr._obj.value = 2
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_query)
        mock_get_func.return_value = mock_func

        instance_handle = self.pyzes.zes_info_log_instance_handle_t()
        size = c_uint32(0)
        record_count = c_uint32(0)

        result = self.pyzes.zesInfoLogInstanceReadWithMetadataExt(
            instance_handle, 1000, byref(size), None, byref(record_count), None, None
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(size.value, 512)
        self.assertEqual(record_count.value, 2)
        mock_get_func.assert_called_with("zesInfoLogInstanceReadWithMetadataExt")
        mock_func.assert_called_once()

    def test_GivenValidInstanceHandleWhenCallingZesInfoLogInstanceReadWithMetadataExtWithBuffersThenRecordsAndStatusAreReturned(
        self, mock_get_func
    ):
        def mock_read(
            instance_handle,
            timeout,
            size_ptr,
            buffer,
            count_ptr,
            descriptors,
            status_ptr,
        ):
            buffer[0] = 0x43
            buffer[300] = 0x50
            descriptors[0].lengthOfData = 300
            descriptors[0].offset = 0
            descriptors[0].timestamp = 123456789
            descriptors[0].recordType = (
                self.pyzes.ZES_INFO_LOG_RECORD_TYPE_EXT_ERROR_CORRECTED
            )
            descriptors[0].address.bus = 0x3A
            descriptors[1].lengthOfData = 212
            descriptors[1].offset = 300
            descriptors[1].recordType = (
                self.pyzes.ZES_INFO_LOG_RECORD_TYPE_EXT_ERROR_FATAL
            )
            status = status_ptr._obj
            status.droppedRecordCount = 0
            status.consumedDataSize = 4096
            status.hasDataToRead = 0
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_read)
        mock_get_func.return_value = mock_func

        instance_handle = self.pyzes.zes_info_log_instance_handle_t()
        size = c_uint32(512)
        record_count = c_uint32(2)
        buffer = (c_uint8 * size.value)()
        descriptors = (self.pyzes.zes_info_log_metadata_ext_t * record_count.value)()
        for i in range(record_count.value):
            descriptors[i].stype = self.pyzes.ZES_STRUCTURE_TYPE_INFO_LOG_METADATA_EXT
        status = self.pyzes.zes_info_log_read_status_ext_t()
        status.stype = self.pyzes.ZES_STRUCTURE_TYPE_INFO_LOG_READ_STATUS_EXT

        result = self.pyzes.zesInfoLogInstanceReadWithMetadataExt(
            instance_handle,
            1000,
            byref(size),
            buffer,
            byref(record_count),
            descriptors,
            byref(status),
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(buffer[0], 0x43)
        self.assertEqual(buffer[300], 0x50)
        self.assertEqual(descriptors[0].lengthOfData, 300)
        self.assertEqual(descriptors[0].timestamp, 123456789)
        self.assertEqual(
            descriptors[0].recordType,
            self.pyzes.ZES_INFO_LOG_RECORD_TYPE_EXT_ERROR_CORRECTED,
        )
        self.assertEqual(descriptors[0].address.bus, 0x3A)
        self.assertEqual(descriptors[1].offset, 300)
        self.assertEqual(
            descriptors[1].recordType,
            self.pyzes.ZES_INFO_LOG_RECORD_TYPE_EXT_ERROR_FATAL,
        )
        self.assertEqual(status.droppedRecordCount, 0)
        self.assertEqual(status.consumedDataSize, 4096)
        self.assertEqual(status.hasDataToRead, 0)
        mock_get_func.assert_called_with("zesInfoLogInstanceReadWithMetadataExt")
        mock_func.assert_called_once()

    def test_GivenValidInstanceHandleWhenCallingZesInfoLogInstancePeekWithMetadataExtWithZeroSizeThenQueryReturnsSizeAndRecordCount(
        self, mock_get_func
    ):
        def mock_query(
            instance_handle,
            timeout,
            size_ptr,
            buffer,
            count_ptr,
            descriptors,
            status_ptr,
        ):
            self.assertEqual(timeout, 1000)
            self.assertIsNone(buffer)
            self.assertIsNone(descriptors)
            size_ptr._obj.value = 512
            count_ptr._obj.value = 2
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_query)
        mock_get_func.return_value = mock_func

        instance_handle = self.pyzes.zes_info_log_instance_handle_t()
        size = c_uint32(0)
        record_count = c_uint32(0)

        result = self.pyzes.zesInfoLogInstancePeekWithMetadataExt(
            instance_handle, 1000, byref(size), None, byref(record_count), None, None
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(size.value, 512)
        self.assertEqual(record_count.value, 2)
        mock_get_func.assert_called_with("zesInfoLogInstancePeekWithMetadataExt")
        mock_func.assert_called_once()

    def test_GivenValidInstanceHandleWhenCallingZesInfoLogInstancePeekWithMetadataExtWithBuffersThenRecordsAndStatusAreReturned(
        self, mock_get_func
    ):
        def mock_read(
            instance_handle,
            timeout,
            size_ptr,
            buffer,
            count_ptr,
            descriptors,
            status_ptr,
        ):
            buffer[0] = 0x43
            buffer[300] = 0x50
            descriptors[0].lengthOfData = 300
            descriptors[0].offset = 0
            descriptors[0].timestamp = 123456789
            descriptors[0].recordType = (
                self.pyzes.ZES_INFO_LOG_RECORD_TYPE_EXT_ERROR_CORRECTED
            )
            descriptors[0].address.bus = 0x3A
            descriptors[1].lengthOfData = 212
            descriptors[1].offset = 300
            descriptors[1].recordType = (
                self.pyzes.ZES_INFO_LOG_RECORD_TYPE_EXT_ERROR_FATAL
            )
            status = status_ptr._obj
            status.droppedRecordCount = 0
            status.consumedDataSize = 4096
            status.hasDataToRead = 0
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_read)
        mock_get_func.return_value = mock_func

        instance_handle = self.pyzes.zes_info_log_instance_handle_t()
        size = c_uint32(512)
        record_count = c_uint32(2)
        buffer = (c_uint8 * size.value)()
        descriptors = (self.pyzes.zes_info_log_metadata_ext_t * record_count.value)()
        for i in range(record_count.value):
            descriptors[i].stype = self.pyzes.ZES_STRUCTURE_TYPE_INFO_LOG_METADATA_EXT
        status = self.pyzes.zes_info_log_read_status_ext_t()
        status.stype = self.pyzes.ZES_STRUCTURE_TYPE_INFO_LOG_READ_STATUS_EXT

        result = self.pyzes.zesInfoLogInstancePeekWithMetadataExt(
            instance_handle,
            1000,
            byref(size),
            buffer,
            byref(record_count),
            descriptors,
            byref(status),
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(buffer[0], 0x43)
        self.assertEqual(buffer[300], 0x50)
        self.assertEqual(descriptors[0].lengthOfData, 300)
        self.assertEqual(descriptors[0].timestamp, 123456789)
        self.assertEqual(
            descriptors[0].recordType,
            self.pyzes.ZES_INFO_LOG_RECORD_TYPE_EXT_ERROR_CORRECTED,
        )
        self.assertEqual(descriptors[0].address.bus, 0x3A)
        self.assertEqual(descriptors[1].offset, 300)
        self.assertEqual(
            descriptors[1].recordType,
            self.pyzes.ZES_INFO_LOG_RECORD_TYPE_EXT_ERROR_FATAL,
        )
        self.assertEqual(status.droppedRecordCount, 0)
        self.assertEqual(status.consumedDataSize, 4096)
        self.assertEqual(status.hasDataToRead, 0)
        mock_get_func.assert_called_with("zesInfoLogInstancePeekWithMetadataExt")
        mock_func.assert_called_once()

    def test_GivenValidInstanceHandleWhenCallingZesInfoLogInstanceDeleteExtThenCallSucceeds(
        self, mock_get_func
    ):
        mock_func = MagicMock(return_value=self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.return_value = mock_func

        instance_handle = self.pyzes.zes_info_log_instance_handle_t(0x1234)

        result = self.pyzes.zesInfoLogInstanceDeleteExt(instance_handle)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.assert_called_with("zesInfoLogInstanceDeleteExt")
        mock_func.assert_called_once_with(instance_handle)


if __name__ == "__main__":
    unittest.main()
