##
# Copyright (C) 2026 Intel Corporation
#
# SPDX-License-Identifier: MIT
#
##

import os
from ctypes import byref, c_uint32

import pytest


class TestPowerCts:
    """Pytest fixture class"""

    @pytest.fixture(autouse=True)
    def _set_up_fixture(self, pyzes_module, sysman_devices):
        self.pz = pyzes_module
        self.devices = sysman_devices

    def _get_power_handles(self, device):
        power_count = c_uint32(0)
        rc = self.pz.zesDeviceEnumPowerDomains(device, byref(power_count), None)
        assert (
            rc == self.pz.ZE_RESULT_SUCCESS
        ), f"zesDeviceEnumPowerDomains(count) failed with ze_result_t={rc}"

        if power_count.value == 0:
            return []

        PowerArray = self.pz.zes_pwr_handle_t * power_count.value
        power_handles = PowerArray()
        rc = self.pz.zesDeviceEnumPowerDomains(
            device, byref(power_count), power_handles
        )
        assert (
            rc == self.pz.ZE_RESULT_SUCCESS
        ), f"zesDeviceEnumPowerDomains(handles) failed with ze_result_t={rc}"

        return list(power_handles)

    def _get_power_properties(self, power_handle):
        default_limit = self.pz.zes_power_limit_ext_desc_t()
        ext_properties = self.pz.zes_power_ext_properties_t()
        ext_properties.stype = self.pz.ZES_STRUCTURE_TYPE_POWER_EXT_PROPERTIES
        ext_properties.pNext = None
        ext_properties.defaultLimit = self.pz.pointer(default_limit)

        properties = self.pz.zes_power_properties_t()
        properties.stype = self.pz.ZES_STRUCTURE_TYPE_POWER_PROPERTIES
        properties.pNext = self.pz.cast(
            self.pz.pointer(ext_properties), self.pz.c_void_p
        )

        rc = self.pz.zesPowerGetProperties(power_handle, byref(properties))
        assert (
            rc == self.pz.ZE_RESULT_SUCCESS
        ), f"zesPowerGetProperties failed with ze_result_t={rc}"

        return properties, ext_properties, default_limit

    def _copy_power_limit_descriptor(self, source_descriptor):
        copied_descriptor = self.pz.zes_power_limit_ext_desc_t()
        copied_descriptor.stype = self.pz.ZES_STRUCTURE_TYPE_POWER_LIMIT_EXT_DESC
        copied_descriptor.pNext = None
        copied_descriptor.level = source_descriptor.level
        copied_descriptor.source = source_descriptor.source
        copied_descriptor.limitUnit = source_descriptor.limitUnit
        copied_descriptor.enabledStateLocked = source_descriptor.enabledStateLocked
        copied_descriptor.enabled = source_descriptor.enabled
        copied_descriptor.intervalValueLocked = source_descriptor.intervalValueLocked
        copied_descriptor.interval = source_descriptor.interval
        copied_descriptor.limitValueLocked = source_descriptor.limitValueLocked
        copied_descriptor.limit = source_descriptor.limit
        return copied_descriptor

    def _get_power_limits_ext_descriptors(self, power_handle):
        limit_count = c_uint32(0)
        rc = self.pz.zesPowerGetLimitsExt(power_handle, byref(limit_count), None)
        if rc == self.pz.ZE_RESULT_ERROR_UNSUPPORTED_FEATURE:
            return None

        assert (
            rc == self.pz.ZE_RESULT_SUCCESS
        ), f"zesPowerGetLimitsExt(count) failed with ze_result_t={rc}"

        if limit_count.value == 0:
            return []

        LimitsArray = self.pz.zes_power_limit_ext_desc_t * limit_count.value
        limit_descriptors = LimitsArray()

        for index in range(limit_count.value):
            limit_descriptors[index].stype = (
                self.pz.ZES_STRUCTURE_TYPE_POWER_LIMIT_EXT_DESC
            )
            limit_descriptors[index].pNext = None

        rc = self.pz.zesPowerGetLimitsExt(
            power_handle, byref(limit_count), limit_descriptors
        )
        assert (
            rc == self.pz.ZE_RESULT_SUCCESS
        ), f"zesPowerGetLimitsExt(descriptors) failed with ze_result_t={rc}"

        return [
            self._copy_power_limit_descriptor(descriptor)
            for descriptor in limit_descriptors
        ]

    def _iter_supported_power_handles(self):
        found_power_support = False

        for device in self.devices:
            power_handles = self._get_power_handles(device)
            if power_handles:
                found_power_support = True
            for power_handle in power_handles:
                yield power_handle

        assert found_power_support, "No power handles found on any of the devices"

    def test_GivenValidDeviceWhenEnumeratingPowerHandlesThenNonZeroCountAndValidPowerHandlesAreReturned(
        self,
    ):
        found_power_support = False

        for device in self.devices:
            power_handles = self._get_power_handles(device)
            if not power_handles:
                continue

            found_power_support = True
            for power_handle in power_handles:
                assert power_handle.value is not None, "Expected a valid power handle"

        assert found_power_support, "No power handles found on any of the devices"

    def test_GivenValidDeviceWhenRetrievingPowerHandlesThenSimilarHandlesAreReturnedTwice(
        self,
    ):
        found_power_support = False

        for device in self.devices:
            initial_handles = self._get_power_handles(device)
            later_handles = self._get_power_handles(device)

            if not initial_handles:
                continue

            found_power_support = True
            assert initial_handles == later_handles

        assert found_power_support, "No power handles found on any of the devices"

    def test_GivenValidDeviceWhenRetrievingPowerHandlesThenActualHandleCountIsUpdatedAndIfRequestedHandlesAreLessThanActualHandleCountThenDesiredNumberOfHandlesAreReturned(
        self,
    ):
        found_power_support = False

        for device in self.devices:
            power_count = c_uint32(0)
            rc = self.pz.zesDeviceEnumPowerDomains(device, byref(power_count), None)
            assert (
                rc == self.pz.ZE_RESULT_SUCCESS
            ), f"zesDeviceEnumPowerDomains(count) failed with ze_result_t={rc}"

            if power_count.value == 0:
                continue

            found_power_support = True
            actual_count = power_count.value

            oversized_count = c_uint32(actual_count + 1)
            OversizedArray = self.pz.zes_pwr_handle_t * oversized_count.value
            oversized_handles = OversizedArray()
            rc = self.pz.zesDeviceEnumPowerDomains(
                device, byref(oversized_count), oversized_handles
            )
            assert (
                rc == self.pz.ZE_RESULT_SUCCESS
            ), f"zesDeviceEnumPowerDomains(oversized) failed with ze_result_t={rc}"
            assert oversized_count.value == actual_count

            if actual_count > 1:
                reduced_count = c_uint32(actual_count - 1)
                ReducedArray = self.pz.zes_pwr_handle_t * reduced_count.value
                reduced_handles = ReducedArray()
                rc = self.pz.zesDeviceEnumPowerDomains(
                    device, byref(reduced_count), reduced_handles
                )
                assert (
                    rc == self.pz.ZE_RESULT_SUCCESS
                ), f"zesDeviceEnumPowerDomains(reduced) failed with ze_result_t={rc}"
                assert len(reduced_handles) == reduced_count.value

        assert found_power_support, "No power handles found on any of the devices"

    def test_GivenSamePowerHandleWhenRequestingPowerPropertiesThenExpectSamePropertiesTwiceAndLimitsAreInRange(
        self,
    ):
        for power_handle in self._iter_supported_power_handles():
            initial_properties, initial_ext_properties, initial_default_limit = (
                self._get_power_properties(power_handle)
            )
            later_properties, later_ext_properties, later_default_limit = (
                self._get_power_properties(power_handle)
            )

            assert initial_properties.onSubdevice == later_properties.onSubdevice
            assert initial_properties.subdeviceId == later_properties.subdeviceId
            assert initial_properties.canControl == later_properties.canControl
            assert (
                initial_properties.isEnergyThresholdSupported
                == later_properties.isEnergyThresholdSupported
            )
            assert initial_properties.defaultLimit == later_properties.defaultLimit
            assert initial_properties.minLimit == later_properties.minLimit
            assert initial_properties.maxLimit == later_properties.maxLimit
            assert initial_ext_properties.domain == later_ext_properties.domain
            assert initial_default_limit.limit == later_default_limit.limit

            if initial_properties.maxLimit != -1:
                assert initial_properties.maxLimit > 0
                assert initial_properties.maxLimit >= initial_properties.minLimit
            if initial_properties.minLimit != -1:
                assert initial_properties.minLimit >= 0
            if initial_properties.defaultLimit != -1:
                assert initial_properties.defaultLimit > 0

    def test_GivenValidPowerHandleThenExpectZesPowerGetEnergyCounterToReturnSuccess(
        self,
    ):
        exercised_any = False

        for power_handle in self._iter_supported_power_handles():
            energy_initial = self.pz.zes_power_energy_counter_t()
            rc = self.pz.zesPowerGetEnergyCounter(power_handle, byref(energy_initial))
            if rc == self.pz.ZE_RESULT_ERROR_UNSUPPORTED_FEATURE:
                continue

            assert (
                rc == self.pz.ZE_RESULT_SUCCESS
            ), f"zesPowerGetEnergyCounter(first) failed with ze_result_t={rc}"

            energy_later = self.pz.zes_power_energy_counter_t()
            rc = self.pz.zesPowerGetEnergyCounter(power_handle, byref(energy_later))
            assert (
                rc == self.pz.ZE_RESULT_SUCCESS
            ), f"zesPowerGetEnergyCounter(second) failed with ze_result_t={rc}"

            exercised_any = True
            assert energy_later.energy >= energy_initial.energy
            assert energy_later.timestamp >= energy_initial.timestamp

        if not exercised_any:
            pytest.skip(
                "zesPowerGetEnergyCounter is unsupported on all available power handles"
            )

    def test_GivenValidRootDevicePowerHandleWhenRequestingPowerLimitsExtThenExpectSameValuesTwice(
        self,
    ):
        exercised_any = False

        for power_handle in self._iter_supported_power_handles():
            properties, _, _ = self._get_power_properties(power_handle)
            if properties.onSubdevice:
                continue

            first_descriptors = self._get_power_limits_ext_descriptors(power_handle)
            if first_descriptors is None:
                continue

            second_descriptors = self._get_power_limits_ext_descriptors(power_handle)
            exercised_any = True

            assert len(first_descriptors) == len(second_descriptors)
            for first_descriptor, second_descriptor in zip(
                first_descriptors, second_descriptors
            ):
                assert first_descriptor.level == second_descriptor.level
                assert first_descriptor.source == second_descriptor.source
                assert first_descriptor.limitUnit == second_descriptor.limitUnit
                assert (
                    first_descriptor.enabledStateLocked
                    == second_descriptor.enabledStateLocked
                )
                assert first_descriptor.enabled == second_descriptor.enabled
                assert (
                    first_descriptor.intervalValueLocked
                    == second_descriptor.intervalValueLocked
                )
                assert first_descriptor.interval == second_descriptor.interval
                assert (
                    first_descriptor.limitValueLocked
                    == second_descriptor.limitValueLocked
                )
                assert first_descriptor.limit == second_descriptor.limit

        if not exercised_any:
            pytest.skip(
                "zesPowerGetLimitsExt is unsupported or unavailable on all root-device power handles"
            )

    def test_GivenValidRootPowerHandleWhenSettingMutablePowerLimitDescriptorThenExpectZesPowerSetLimitsExtFollowedByZesPowerGetLimitsExtToMatch(
        self,
    ):
        if getattr(os, "geteuid", None) and os.geteuid() != 0:
            pytest.skip("zesPowerSetLimitsExt CTS validation requires root permissions")

        exercised_any = False

        for power_handle in self._iter_supported_power_handles():
            properties, _, _ = self._get_power_properties(power_handle)
            if properties.onSubdevice:
                continue

            initial_descriptors = self._get_power_limits_ext_descriptors(power_handle)
            if initial_descriptors is None or not initial_descriptors:
                continue

            mutable_index = None
            for index, descriptor in enumerate(initial_descriptors):
                if descriptor.limitValueLocked:
                    continue
                if descriptor.limit <= 0:
                    continue
                mutable_index = index
                break

            if mutable_index is None:
                continue

            modified_descriptors = [
                self._copy_power_limit_descriptor(descriptor)
                for descriptor in initial_descriptors
            ]
            original_descriptor = initial_descriptors[mutable_index]
            modified_descriptor = modified_descriptors[mutable_index]
            modified_descriptor.limit = max(0, original_descriptor.limit - 1000)

            if modified_descriptor.limit == original_descriptor.limit:
                continue

            limit_count = c_uint32(len(modified_descriptors))
            ModifiedArray = self.pz.zes_power_limit_ext_desc_t * len(
                modified_descriptors
            )
            modified_array = ModifiedArray(*modified_descriptors)
            rc = self.pz.zesPowerSetLimitsExt(
                power_handle, byref(limit_count), modified_array
            )
            if rc == self.pz.ZE_RESULT_ERROR_UNSUPPORTED_FEATURE:
                continue

            assert (
                rc == self.pz.ZE_RESULT_SUCCESS
            ), f"zesPowerSetLimitsExt(set) failed with ze_result_t={rc}"

            try:
                current_descriptors = self._get_power_limits_ext_descriptors(
                    power_handle
                )
                assert current_descriptors is not None
                assert (
                    current_descriptors[mutable_index].limit
                    == modified_descriptor.limit
                )
                exercised_any = True
            finally:
                restore_count = c_uint32(len(initial_descriptors))
                RestoreArray = self.pz.zes_power_limit_ext_desc_t * len(
                    initial_descriptors
                )
                restore_array = RestoreArray(*initial_descriptors)
                restore_rc = self.pz.zesPowerSetLimitsExt(
                    power_handle, byref(restore_count), restore_array
                )
                assert (
                    restore_rc == self.pz.ZE_RESULT_SUCCESS
                ), f"zesPowerSetLimitsExt(restore) failed with ze_result_t={restore_rc}"

        if not exercised_any:
            pytest.skip(
                "No mutable root-device power limit descriptors were available for zesPowerSetLimitsExt"
            )
