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

script_dir = os.path.dirname(os.path.abspath(__file__))
source_dir = os.path.join(script_dir, "..", "..", "source")
source_dir = os.path.abspath(source_dir)
if source_dir not in sys.path:
    sys.path.insert(0, source_dir)


@patch("pyzes.getFunctionPointerList")
class TestDriverFunctions(unittest.TestCase):
    def setUp(self):
        import pyzes

        self.pyzes = pyzes

    def test_GivenValidDriverHandleWhenCallingZesDriverGetPropertiesThenCallSucceedsWithValidProperties(
        self, mock_get_func
    ):
        def mock_get_properties(driver_handle, properties_ptr):
            properties = properties_ptr._obj
            properties.uuid.id[0] = 0xAB
            properties.uuid.id[15] = 0xCD
            properties.driverVersion = 0x10002
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_properties)
        mock_get_func.return_value = mock_func

        driver_handle = self.pyzes.zes_driver_handle_t()
        properties = self.pyzes.zes_driver_properties_t()
        properties.stype = self.pyzes.ZES_STRUCTURE_TYPE_DRIVER_PROPERTIES

        result = self.pyzes.zesDriverGetProperties(driver_handle, byref(properties))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(properties.uuid.id[0], 0xAB)
        self.assertEqual(properties.uuid.id[15], 0xCD)
        self.assertEqual(properties.driverVersion, 0x10002)
        mock_get_func.assert_called_with("zesDriverGetProperties")
        mock_func.assert_called_once()

    def test_GivenValidDriverHandleWhenCallingZesDriverGetExtensionPropertiesThenCallSucceedsWithValidCount(
        self, mock_get_func
    ):
        mock_count = 3

        def mock_get_extension_properties(driver_handle, count_ptr, properties_ptr):
            count_ptr._obj.value = mock_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_extension_properties)
        mock_get_func.return_value = mock_func

        driver_handle = self.pyzes.zes_driver_handle_t()
        count = c_uint32(0)

        result = self.pyzes.zesDriverGetExtensionProperties(
            driver_handle, byref(count), None
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_count)
        mock_get_func.assert_called_with("zesDriverGetExtensionProperties")
        mock_func.assert_called_once()

    def test_GivenValidDriverHandleWhenCallingZesDriverGetExtensionPropertiesWithArrayThenCallSucceedsWithProperties(
        self, mock_get_func
    ):
        mock_count = 2

        def mock_get_extension_properties(driver_handle, count_ptr, properties_ptr):
            count_ptr._obj.value = mock_count
            properties_ptr[0].name = b"ZES_extension_info_logs"
            properties_ptr[0].version = 0x10000
            properties_ptr[1].name = b"ZES_extension_power_limits"
            properties_ptr[1].version = 0x10000
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_extension_properties)
        mock_get_func.return_value = mock_func

        driver_handle = self.pyzes.zes_driver_handle_t()
        count = c_uint32(mock_count)
        properties = (self.pyzes.zes_driver_extension_properties_t * mock_count)()

        result = self.pyzes.zesDriverGetExtensionProperties(
            driver_handle, byref(count), properties
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_count)
        self.assertEqual(properties[0].name, b"ZES_extension_info_logs")
        self.assertEqual(properties[0].version, 0x10000)
        self.assertEqual(properties[1].name, b"ZES_extension_power_limits")
        mock_get_func.assert_called_with("zesDriverGetExtensionProperties")
        mock_func.assert_called_once()

    def test_GivenValidDriverHandleWhenCallingZesDriverGetExtensionFunctionAddressThenCallSucceedsWithAddress(
        self, mock_get_func
    ):
        def mock_get_function_address(driver_handle, name, address_ptr):
            self.assertEqual(name, b"zesDriverGetDeviceByUuidExp")
            address_ptr._obj.value = 0xDEADBEEF
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_function_address)
        mock_get_func.return_value = mock_func

        driver_handle = self.pyzes.zes_driver_handle_t()
        address = c_void_p()

        result = self.pyzes.zesDriverGetExtensionFunctionAddress(
            driver_handle, b"zesDriverGetDeviceByUuidExp", byref(address)
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(address.value, 0xDEADBEEF)
        mock_get_func.assert_called_with("zesDriverGetExtensionFunctionAddress")
        mock_func.assert_called_once()

    def test_GivenValidDriverHandleWhenCallingZesDriverEventListenExThenCallSucceedsWithDeviceEvents(
        self, mock_get_func
    ):
        device_count = 2

        def mock_listen_ex(
            driver_handle, timeout, count, devices, num_events_ptr, events
        ):
            self.assertEqual(timeout, 0)
            self.assertEqual(count, device_count)
            num_events_ptr._obj.value = 1
            events[0] = 0
            events[1] = self.pyzes.ZES_EVENT_TYPE_FLAG_TEMP_CRITICAL
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_listen_ex)
        mock_get_func.return_value = mock_func

        driver_handle = self.pyzes.zes_driver_handle_t()
        devices = (self.pyzes.zes_device_handle_t * device_count)()
        num_device_events = c_uint32(0)
        events = (self.pyzes.zes_event_type_flags_t * device_count)()

        result = self.pyzes.zesDriverEventListenEx(
            driver_handle, 0, device_count, devices, byref(num_device_events), events
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(num_device_events.value, 1)
        self.assertEqual(events[0], 0)
        self.assertEqual(events[1], self.pyzes.ZES_EVENT_TYPE_FLAG_TEMP_CRITICAL)
        mock_get_func.assert_called_with("zesDriverEventListenEx")
        mock_func.assert_called_once()

    def test_GivenValidDriverHandleWhenCallingZesDriverEventRegisterExtThenCallSucceeds(
        self, mock_get_func
    ):
        mock_func = MagicMock(return_value=self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.return_value = mock_func

        driver_handle = self.pyzes.zes_driver_handle_t()
        events = self.pyzes.ZES_EVENT_TYPE_FLAG_INFO_LOG_CPER_DATA_AVAILABLE_EXT

        result = self.pyzes.zesDriverEventRegisterExt(driver_handle, events)

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        mock_get_func.assert_called_with("zesDriverEventRegisterExt")
        mock_func.assert_called_once_with(driver_handle, events)

    def test_GivenValidDriverHandleWhenCallingZesDriverEventListenExtThenCallSucceedsWithDriverEvents(
        self, mock_get_func
    ):
        device_count = 1

        def mock_listen_ext(
            driver_handle,
            timeout,
            count,
            devices,
            num_events_ptr,
            events,
            driver_events_ptr,
        ):
            self.assertEqual(timeout, 0)
            self.assertEqual(count, device_count)
            num_events_ptr._obj.value = 0
            events[0] = 0
            driver_events_ptr._obj.value = (
                self.pyzes.ZES_EVENT_TYPE_FLAG_INFO_LOG_CPER_DATA_AVAILABLE_EXT
            )
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_listen_ext)
        mock_get_func.return_value = mock_func

        driver_handle = self.pyzes.zes_driver_handle_t()
        devices = (self.pyzes.zes_device_handle_t * device_count)()
        num_device_events = c_uint32(0)
        events = (self.pyzes.zes_event_type_flags_t * device_count)()
        driver_events = self.pyzes.zes_event_type_flags_t(0)

        result = self.pyzes.zesDriverEventListenExt(
            driver_handle,
            0,
            device_count,
            devices,
            byref(num_device_events),
            events,
            byref(driver_events),
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(num_device_events.value, 0)
        self.assertEqual(events[0], 0)
        self.assertEqual(
            driver_events.value,
            self.pyzes.ZES_EVENT_TYPE_FLAG_INFO_LOG_CPER_DATA_AVAILABLE_EXT,
        )
        mock_get_func.assert_called_with("zesDriverEventListenExt")
        mock_func.assert_called_once()

    def test_GivenValidDriverHandleWhenCallingZesDriverGetApiVersionThenCallSucceedsWithVersion(
        self, mock_get_func
    ):
        def mock_get_api_version(driver_handle, version_ptr):
            version_ptr._obj.value = self.pyzes.ZES_API_VERSION_1_21
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_api_version)
        mock_get_func.return_value = mock_func

        driver_handle = self.pyzes.zes_driver_handle_t()
        version = self.pyzes.zes_api_version_t()

        result = self.pyzes.zesDriverGetApiVersion(driver_handle, byref(version))

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(version.value, self.pyzes.ZES_API_VERSION_1_21)
        self.assertEqual(self.pyzes.ZES_MAJOR_VERSION(version.value), 1)
        self.assertEqual(self.pyzes.ZES_MINOR_VERSION(version.value), 21)
        mock_get_func.assert_called_with("zesDriverGetApiVersion")
        mock_func.assert_called_once()

    def test_GivenApiVersionMacrosWhenComputingVersionsThenValuesMatchCHeader(
        self, mock_get_func
    ):
        self.assertEqual(self.pyzes.ZES_MAKE_VERSION(1, 21), 0x00010015)
        self.assertEqual(self.pyzes.ZES_API_VERSION_1_0, 0x00010000)        
        self.assertEqual(self.pyzes.ZES_MAJOR_VERSION(0x00020003), 2)
        self.assertEqual(self.pyzes.ZES_MINOR_VERSION(0x00020003), 3)

    def test_GivenValidDriverHandleWhenCallingZesDriverGetPciDevicePropertiesThenCallSucceedsWithValidCount(
        self, mock_get_func
    ):
        mock_count = 2

        def mock_get_pci_device_properties(driver_handle, count_ptr, properties_ptr):
            self.assertFalse(bool(properties_ptr))
            count_ptr._obj.value = mock_count
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_pci_device_properties)
        mock_get_func.return_value = mock_func

        driver_handle = self.pyzes.zes_driver_handle_t()
        count = c_uint32(0)

        result = self.pyzes.zesDriverGetPciDeviceProperties(
            driver_handle, byref(count), None
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_count)
        mock_get_func.assert_called_with("zesDriverGetPciDeviceProperties")
        mock_func.assert_called_once()

    def test_GivenValidDriverHandleWhenCallingZesDriverGetPciDevicePropertiesWithArrayThenCallSucceedsWithProperties(
        self, mock_get_func
    ):
        mock_count = 2

        def mock_get_pci_device_properties(driver_handle, count_ptr, properties_ptr):
            count_ptr._obj.value = mock_count
            for i in range(mock_count):
                props = properties_ptr[i]
                props.address.domain = 0
                props.address.bus = 0x03 + i
                props.address.device = 0
                props.address.function = 0
                props.maxSpeed.gen = -1
                props.maxSpeed.width = -1
                props.maxSpeed.maxBandwidth = -1
                props.status = self.pyzes.ZES_PCI_LINK_STATUS_GOOD
                props.configProperties.stype = (
                    self.pyzes.ZES_STRUCTURE_TYPE_PCI_CONFIG_PROPERTIES
                )
                props.configProperties.vendorId = 0x8086
                props.configProperties.deviceId = 0x674C
                props.configProperties.subsystemVendorId = 0x8086
                props.configProperties.subsystemDeviceId = 0x1234
                props.configProperties.supportedLinkSpeeds = (
                    self.pyzes.ZES_PCI_LINK_SPEED_FLAG_GEN1
                    | self.pyzes.ZES_PCI_LINK_SPEED_FLAG_GEN5
                )
            # second device has a revision of 0xFF (device fell off the bus)
            properties_ptr[0].configProperties.revision = 0x01
            properties_ptr[1].configProperties.revision = 0xFF
            return self.pyzes.ZE_RESULT_SUCCESS

        mock_func = MagicMock(side_effect=mock_get_pci_device_properties)
        mock_get_func.return_value = mock_func

        driver_handle = self.pyzes.zes_driver_handle_t()
        count = c_uint32(mock_count)
        properties = (self.pyzes.zes_driver_pci_device_properties_t * mock_count)()
        for i in range(mock_count):
            properties[i].stype = (
                self.pyzes.ZES_STRUCTURE_TYPE_DRIVER_PCI_DEVICE_PROPERTIES
            )
            properties[i].pNext = None

        result = self.pyzes.zesDriverGetPciDeviceProperties(
            driver_handle, byref(count), properties
        )

        self.assertEqual(result, self.pyzes.ZE_RESULT_SUCCESS)
        self.assertEqual(count.value, mock_count)
        self.assertEqual(properties[0].address.bus, 0x03)
        self.assertEqual(properties[1].address.bus, 0x04)
        self.assertEqual(properties[0].maxSpeed.gen, -1)
        self.assertEqual(properties[0].status, self.pyzes.ZES_PCI_LINK_STATUS_GOOD)
        self.assertEqual(properties[0].configProperties.vendorId, 0x8086)
        self.assertEqual(properties[0].configProperties.deviceId, 0x674C)
        self.assertEqual(properties[0].configProperties.subsystemDeviceId, 0x1234)
        self.assertEqual(properties[0].configProperties.supportedLinkSpeeds, 0x11)
        self.assertEqual(properties[0].configProperties.revision, 0x01)
        self.assertEqual(properties[1].configProperties.revision, 0xFF)
        mock_get_func.assert_called_with("zesDriverGetPciDeviceProperties")
        mock_func.assert_called_once()

    def test_GivenPciConfigPropertiesStructWhenCheckingLayoutThenSizeMatchesCStruct(
        self, mock_get_func
    ):
        # stype(4) + pad(4) + pNext(8) + 4*uint16(8) + 2*uint32(8) + uint8(1) + pad(7)
        self.assertEqual(sizeof(self.pyzes.zes_pci_config_properties_t), 40)
        self.assertEqual(
            self.pyzes.ZES_STRUCTURE_TYPE_PCI_CONFIG_PROPERTIES, 0x00020024
        )
        self.assertEqual(
            self.pyzes.ZES_STRUCTURE_TYPE_DRIVER_PCI_DEVICE_PROPERTIES, 0x00020025
        )


if __name__ == "__main__":
    unittest.main()
