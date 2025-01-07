/*
 * ***THIS FILE IS GENERATED. ***
 * See valddi.cpp.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_parameter_validation.cpp
 *
 */
#include "ze_validation_layer.h"
#include "param_validation.h"

namespace validation_layer
{

    ze_result_t
    ZESParameterValidation::zesInitPrologue(
        zes_init_flags_t flags                          ///< [in] initialization flags.
                                                        ///< currently unused, must be 0 (default).
        )
    {
        if( 0x1 < flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDriverGetPrologue(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sysman driver instances.
                                                        ///< if count is zero, then the loader shall update the value with the
                                                        ///< total number of sysman drivers available.
                                                        ///< if count is greater than the number of sysman drivers available, then
                                                        ///< the loader shall update the value with the correct number of sysman
                                                        ///< drivers available.
        zes_driver_handle_t* phDrivers                  ///< [in,out][optional][range(0, *pCount)] array of sysman driver instance handles.
                                                        ///< if count is less than the number of sysman drivers available, then the
                                                        ///< loader shall only retrieve that number of sysman drivers.
        )
    {
        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDriverGetExtensionPropertiesPrologue(
        zes_driver_handle_t hDriver,                    ///< [in] handle of the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of extension properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of extension properties available.
                                                        ///< if count is greater than the number of extension properties available,
                                                        ///< then the driver shall update the value with the correct number of
                                                        ///< extension properties available.
        zes_driver_extension_properties_t* pExtensionProperties ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< extension properties.
                                                        ///< if count is less than the number of extension properties available,
                                                        ///< then driver shall only retrieve that number of extension properties.
        )
    {
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pExtensionProperties);
    }


    ze_result_t
    ZESParameterValidation::zesDriverGetExtensionFunctionAddressPrologue(
        zes_driver_handle_t hDriver,                    ///< [in] handle of the driver instance
        const char* name,                               ///< [in] extension function name
        void** ppFunctionAddress                        ///< [out] pointer to function pointer
        )
    {
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == name )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == ppFunctionAddress )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceGetPrologue(
        zes_driver_handle_t hDriver,                    ///< [in] handle of the sysman driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sysman devices.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of sysman devices available.
                                                        ///< if count is greater than the number of sysman devices available, then
                                                        ///< the driver shall update the value with the correct number of sysman
                                                        ///< devices available.
        zes_device_handle_t* phDevices                  ///< [in,out][optional][range(0, *pCount)] array of handle of sysman devices.
                                                        ///< if count is less than the number of sysman devices available, then
                                                        ///< driver shall only retrieve that number of sysman devices.
        )
    {
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceGetPropertiesPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesDeviceGetStatePrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pState )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pState);
    }


    ze_result_t
    ZESParameterValidation::zesDeviceResetPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
        ze_bool_t force                                 ///< [in] If set to true, all applications that are currently using the
                                                        ///< device will be forcibly killed.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceResetExtPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
        zes_reset_properties_t* pProperties             ///< [in] Device reset properties to apply
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesDeviceProcessesGetStatePrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of processes.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of processes currently attached to the device.
                                                        ///< if count is greater than the number of processes currently attached to
                                                        ///< the device, then the driver shall update the value with the correct
                                                        ///< number of processes.
        zes_process_state_t* pProcesses                 ///< [in,out][optional][range(0, *pCount)] array of process information.
                                                        ///< if count is less than the number of processes currently attached to
                                                        ///< the device, then the driver shall only retrieve information about that
                                                        ///< number of processes. In this case, the return code will ::ZE_RESULT_ERROR_INVALID_SIZE.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProcesses);
    }


    ze_result_t
    ZESParameterValidation::zesDevicePciGetPropertiesPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesDevicePciGetStatePrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pState )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pState);
    }


    ze_result_t
    ZESParameterValidation::zesDevicePciGetBarsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of PCI bars.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of PCI bars that are setup.
                                                        ///< if count is greater than the number of PCI bars that are setup, then
                                                        ///< the driver shall update the value with the correct number of PCI bars.
        zes_pci_bar_properties_t* pProperties           ///< [in,out][optional][range(0, *pCount)] array of information about setup
                                                        ///< PCI bars.
                                                        ///< if count is less than the number of PCI bars that are setup, then the
                                                        ///< driver shall only retrieve information about that number of PCI bars.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesDevicePciGetStatsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pStats )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceSetOverclockWaiverPrologue(
        zes_device_handle_t hDevice                     ///< [in] Sysman handle of the device.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceGetOverclockDomainsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pOverclockDomains                     ///< [in,out] Returns the overclock domains that are supported (a bit for
                                                        ///< each of enum ::zes_overclock_domain_t). If no bits are set, the device
                                                        ///< doesn't support overclocking.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pOverclockDomains )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceGetOverclockControlsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_overclock_domain_t domainType,              ///< [in] Domain type.
        uint32_t* pAvailableControls                    ///< [in,out] Returns the overclock controls that are supported for the
                                                        ///< specified overclock domain (a bit for each of enum
                                                        ///< ::zes_overclock_control_t).
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( ZES_OVERCLOCK_DOMAIN_ADM < domainType )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( nullptr == pAvailableControls )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceResetOverclockSettingsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        ze_bool_t onShippedState                        ///< [in] True will reset to shipped state; false will reset to
                                                        ///< manufacturing state
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceReadOverclockStatePrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_overclock_mode_t* pOverclockMode,           ///< [out] One of overclock mode.
        ze_bool_t* pWaiverSetting,                      ///< [out] Waiver setting: 0 = Waiver not set, 1 = waiver has been set.
        ze_bool_t* pOverclockState,                     ///< [out] Current settings 0 =manufacturing state, 1= shipped state)..
        zes_pending_action_t* pPendingAction,           ///< [out] This enum is returned when the driver attempts to set an
                                                        ///< overclock control or reset overclock settings.
        ze_bool_t* pPendingReset                        ///< [out] Pending reset 0 =manufacturing state, 1= shipped state)..
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pOverclockMode )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pWaiverSetting )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pOverclockState )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pPendingAction )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pPendingReset )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumOverclockDomainsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_overclock_handle_t* phDomainHandle          ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesOverclockGetDomainPropertiesPrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_properties_t* pDomainProperties   ///< [in,out] The overclock properties for the specified domain.
        )
    {
        if( nullptr == hDomainHandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pDomainProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pDomainProperties);
    }


    ze_result_t
    ZESParameterValidation::zesOverclockGetDomainVFPropertiesPrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_vf_property_t* pVFProperties                ///< [in,out] The VF min,max,step for a specified domain.
        )
    {
        if( nullptr == hDomainHandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pVFProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesOverclockGetDomainControlPropertiesPrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Handle for the component.
        zes_control_property_t* pControlProperties      ///< [in,out] overclock control values.
        )
    {
        if( nullptr == hDomainHandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( nullptr == pControlProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesOverclockGetControlCurrentValuePrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component.
        zes_overclock_control_t DomainControl,          ///< [in] Overclock Control.
        double* pValue                                  ///< [in,out] Getting overclock control value for the specified control.
        )
    {
        if( nullptr == hDomainHandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( nullptr == pValue )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesOverclockGetControlPendingValuePrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Overclock Control.
        double* pValue                                  ///< [out] Returns the pending value for a given control. The units and
                                                        ///< format of the value depend on the control type.
        )
    {
        if( nullptr == hDomainHandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( nullptr == pValue )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesOverclockSetControlUserValuePrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Domain Control.
        double pValue,                                  ///< [in] The new value of the control. The units and format of the value
                                                        ///< depend on the control type.
        zes_pending_action_t* pPendingAction            ///< [out] Pending overclock setting.
        )
    {
        if( nullptr == hDomainHandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( nullptr == pPendingAction )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesOverclockGetControlStatePrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Domain Control.
        zes_control_state_t* pControlState,             ///< [out] Current overclock control state.
        zes_pending_action_t* pPendingAction            ///< [out] Pending overclock setting.
        )
    {
        if( nullptr == hDomainHandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( nullptr == pControlState )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pPendingAction )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesOverclockGetVFPointValuesPrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_vf_type_t VFType,                           ///< [in] Voltage or Freqency point to read.
        zes_vf_array_type_t VFArrayType,                ///< [in] User,Default or Live VF array to read from
        uint32_t PointIndex,                            ///< [in] Point index - number between (0, max_num_points - 1).
        uint32_t* PointValue                            ///< [out] Returns the frequency in 1kHz units or voltage in millivolt
                                                        ///< units from the custom V-F curve at the specified zero-based index 
        )
    {
        if( nullptr == hDomainHandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( ZES_VF_TYPE_FREQ < VFType )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( ZES_VF_ARRAY_TYPE_LIVE_VF_ARRAY < VFArrayType )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( nullptr == PointValue )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesOverclockSetVFPointValuesPrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_vf_type_t VFType,                           ///< [in] Voltage or Freqency point to read.
        uint32_t PointIndex,                            ///< [in] Point index - number between (0, max_num_points - 1).
        uint32_t PointValue                             ///< [in] Writes frequency in 1kHz units or voltage in millivolt units to
                                                        ///< custom V-F curve at the specified zero-based index 
        )
    {
        if( nullptr == hDomainHandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( ZES_VF_TYPE_FREQ < VFType )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumDiagnosticTestSuitesPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_diag_handle_t* phDiagnostics                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDiagnosticsGetPropertiesPrologue(
        zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
        zes_diag_properties_t* pProperties              ///< [in,out] Structure describing the properties of a diagnostics test
                                                        ///< suite
        )
    {
        if( nullptr == hDiagnostics )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesDiagnosticsGetTestsPrologue(
        zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of tests.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of tests that are available.
                                                        ///< if count is greater than the number of tests that are available, then
                                                        ///< the driver shall update the value with the correct number of tests.
        zes_diag_test_t* pTests                         ///< [in,out][optional][range(0, *pCount)] array of information about
                                                        ///< individual tests sorted by increasing value of the `index` member of ::zes_diag_test_t.
                                                        ///< if count is less than the number of tests that are available, then the
                                                        ///< driver shall only retrieve that number of tests.
        )
    {
        if( nullptr == hDiagnostics )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDiagnosticsRunTestsPrologue(
        zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
        uint32_t startIndex,                            ///< [in] The index of the first test to run. Set to
                                                        ///< ::ZES_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t endIndex,                              ///< [in] The index of the last test to run. Set to
                                                        ///< ::ZES_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        zes_diag_result_t* pResult                      ///< [in,out] The result of the diagnostics
        )
    {
        if( nullptr == hDiagnostics )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pResult )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEccAvailablePrologue(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        ze_bool_t* pAvailable                           ///< [out] ECC functionality is available (true)/unavailable (false).
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pAvailable )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEccConfigurablePrologue(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        ze_bool_t* pConfigurable                        ///< [out] ECC can be enabled/disabled (true)/enabled/disabled (false).
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pConfigurable )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceGetEccStatePrologue(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        zes_device_ecc_properties_t* pState             ///< [out] ECC state, pending state, and pending action for state change.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pState )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pState);
    }


    ze_result_t
    ZESParameterValidation::zesDeviceSetEccStatePrologue(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        const zes_device_ecc_desc_t* newState,          ///< [in] Pointer to desired ECC state.
        zes_device_ecc_properties_t* pState             ///< [out] ECC state, pending state, and pending action for state change.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == newState )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pState )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( ZES_DEVICE_ECC_STATE_DISABLED < newState->state )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        auto retVal = ZE_RESULT_SUCCESS;
        retVal = ParameterValidation::validateExtensions(newState);
        if(retVal)
            return retVal;
        retVal = ParameterValidation::validateExtensions(pState);
        return retVal;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumEngineGroupsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_engine_handle_t* phEngine                   ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesEngineGetPropertiesPrologue(
        zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
        zes_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
        )
    {
        if( nullptr == hEngine )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesEngineGetActivityPrologue(
        zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
        zes_engine_stats_t* pStats                      ///< [in,out] Will contain a snapshot of the engine group activity
                                                        ///< counters.
        )
    {
        if( nullptr == hEngine )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pStats )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEventRegisterPrologue(
        zes_device_handle_t hDevice,                    ///< [in] The device handle.
        zes_event_type_flags_t events                   ///< [in] List of events to listen to.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( 0xffff < events )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDriverEventListenPrologue(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then will check status and return immediately;
                                                        ///< if `UINT32_MAX`, then function will not return until events arrive.
        uint32_t count,                                 ///< [in] Number of device handles in phDevices.
        zes_device_handle_t* phDevices,                 ///< [in][range(0, count)] Device handles to listen to for events. Only
                                                        ///< devices from the provided driver handle can be specified in this list.
        uint32_t* pNumDeviceEvents,                     ///< [in,out] Will contain the actual number of devices in phDevices that
                                                        ///< generated events. If non-zero, check pEvents to determine the devices
                                                        ///< and events that were received.
        zes_event_type_flags_t* pEvents                 ///< [in,out] An array that will continue the list of events for each
                                                        ///< device listened in phDevices.
                                                        ///< This array must be at least as big as count.
                                                        ///< For every device handle in phDevices, this will provide the events
                                                        ///< that occurred for that device at the same position in this array. If
                                                        ///< no event was received for a given device, the corresponding array
                                                        ///< entry will be zero.
        )
    {
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phDevices )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pNumDeviceEvents )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pEvents )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDriverEventListenExPrologue(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint64_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then will check status and return immediately;
                                                        ///< if `UINT64_MAX`, then function will not return until events arrive.
        uint32_t count,                                 ///< [in] Number of device handles in phDevices.
        zes_device_handle_t* phDevices,                 ///< [in][range(0, count)] Device handles to listen to for events. Only
                                                        ///< devices from the provided driver handle can be specified in this list.
        uint32_t* pNumDeviceEvents,                     ///< [in,out] Will contain the actual number of devices in phDevices that
                                                        ///< generated events. If non-zero, check pEvents to determine the devices
                                                        ///< and events that were received.
        zes_event_type_flags_t* pEvents                 ///< [in,out] An array that will continue the list of events for each
                                                        ///< device listened in phDevices.
                                                        ///< This array must be at least as big as count.
                                                        ///< For every device handle in phDevices, this will provide the events
                                                        ///< that occurred for that device at the same position in this array. If
                                                        ///< no event was received for a given device, the corresponding array
                                                        ///< entry will be zero.
        )
    {
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phDevices )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pNumDeviceEvents )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pEvents )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumFabricPortsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_fabric_port_handle_t* phPort                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFabricPortGetPropertiesPrologue(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
        )
    {
        if( nullptr == hPort )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesFabricPortGetLinkTypePrologue(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_link_type_t* pLinkType               ///< [in,out] Will contain details about the link attached to the Fabric
                                                        ///< port.
        )
    {
        if( nullptr == hPort )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pLinkType )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFabricPortGetConfigPrologue(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
        )
    {
        if( nullptr == hPort )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pConfig )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pConfig);
    }


    ze_result_t
    ZESParameterValidation::zesFabricPortSetConfigPrologue(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        const zes_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
        )
    {
        if( nullptr == hPort )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pConfig )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pConfig);
    }


    ze_result_t
    ZESParameterValidation::zesFabricPortGetStatePrologue(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
        )
    {
        if( nullptr == hPort )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pState )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pState);
    }


    ze_result_t
    ZESParameterValidation::zesFabricPortGetThroughputPrologue(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
        )
    {
        if( nullptr == hPort )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pThroughput )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFabricPortGetFabricErrorCountersPrologue(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_error_counters_t* pErrors       ///< [in,out] Will contain the Fabric port Error counters.
        )
    {
        if( nullptr == hPort )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pErrors )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pErrors);
    }


    ze_result_t
    ZESParameterValidation::zesFabricPortGetMultiPortThroughputPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t numPorts,                              ///< [in] Number of ports enumerated in function ::zesDeviceEnumFabricPorts
        zes_fabric_port_handle_t* phPort,               ///< [in][range(0, numPorts)] array of fabric port handles provided by user
                                                        ///< to gather throughput values. 
        zes_fabric_port_throughput_t** pThroughput      ///< [out][range(0, numPorts)] array of fabric port throughput counters
                                                        ///< from multiple ports of type ::zes_fabric_port_throughput_t.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phPort )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pThroughput )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumFansPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_fan_handle_t* phFan                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFanGetPropertiesPrologue(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
        )
    {
        if( nullptr == hFan )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesFanGetConfigPrologue(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
        )
    {
        if( nullptr == hFan )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pConfig )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pConfig);
    }


    ze_result_t
    ZESParameterValidation::zesFanSetDefaultModePrologue(
        zes_fan_handle_t hFan                           ///< [in] Handle for the component.
        )
    {
        if( nullptr == hFan )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFanSetFixedSpeedModePrologue(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        const zes_fan_speed_t* speed                    ///< [in] The fixed fan speed setting
        )
    {
        if( nullptr == hFan )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == speed )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFanSetSpeedTableModePrologue(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        const zes_fan_speed_table_t* speedTable         ///< [in] A table containing temperature/speed pairs.
        )
    {
        if( nullptr == hFan )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == speedTable )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFanGetStatePrologue(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
        int32_t* pSpeed                                 ///< [in,out] Will contain the current speed of the fan in the units
                                                        ///< requested. A value of -1 indicates that the fan speed cannot be
                                                        ///< measured.
        )
    {
        if( nullptr == hFan )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( ZES_FAN_SPEED_UNITS_PERCENT < units )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        if( nullptr == pSpeed )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumFirmwaresPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_firmware_handle_t* phFirmware               ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFirmwareGetPropertiesPrologue(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        zes_firmware_properties_t* pProperties          ///< [in,out] Pointer to an array that will hold the properties of the
                                                        ///< firmware
        )
    {
        if( nullptr == hFirmware )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesFirmwareFlashPrologue(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    {
        if( nullptr == hFirmware )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pImage )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFirmwareGetFlashProgressPrologue(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        uint32_t* pCompletionPercent                    ///< [in,out] Pointer to the Completion Percentage of Firmware Update
        )
    {
        if( nullptr == hFirmware )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCompletionPercent )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFirmwareGetConsoleLogsPrologue(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        size_t* pSize,                                  ///< [in,out] size of firmware log
        char* pFirmwareLog                              ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    {
        if( nullptr == hFirmware )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pSize )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumFrequencyDomainsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_freq_handle_t* phFrequency                  ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyGetPropertiesPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyGetAvailableClocksPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of frequencies.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of frequencies that are available.
                                                        ///< if count is greater than the number of frequencies that are available,
                                                        ///< then the driver shall update the value with the correct number of frequencies.
        double* phFrequency                             ///< [in,out][optional][range(0, *pCount)] array of frequencies in units of
                                                        ///< MHz and sorted from slowest to fastest.
                                                        ///< if count is less than the number of frequencies that are available,
                                                        ///< then the driver shall only retrieve that number of frequencies.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyGetRangePrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_range_t* pLimits                       ///< [in,out] The range between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pLimits )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFrequencySetRangePrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        const zes_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pLimits )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyGetStatePrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pState )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pState);
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyGetThrottleTimePrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_throttle_time_t* pThrottleTime         ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pThrottleTime )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyOcGetCapabilitiesPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pOcCapabilities )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pOcCapabilities);
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyOcGetFrequencyTargetPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pCurrentOcFrequency                     ///< [out] Overclocking Frequency in MHz, if extended moded is supported,
                                                        ///< will returned in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                        ///< cannot be greater than the `maxOcFrequency` member of
                                                        ///< ::zes_oc_capabilities_t.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCurrentOcFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyOcSetFrequencyTargetPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double CurrentOcFrequency                       ///< [in] Overclocking Frequency in MHz, if extended moded is supported, it
                                                        ///< could be set in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                        ///< cannot be greater than the `maxOcFrequency` member of
                                                        ///< ::zes_oc_capabilities_t.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyOcGetVoltageTargetPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pCurrentVoltageTarget,                  ///< [out] Overclock voltage in Volts. This cannot be greater than the
                                                        ///< `maxOcVoltage` member of ::zes_oc_capabilities_t.
        double* pCurrentVoltageOffset                   ///< [out] This voltage offset is applied to all points on the
                                                        ///< voltage/frequency curve, including the new overclock voltageTarget.
                                                        ///< Valid range is between the `minOcVoltageOffset` and
                                                        ///< `maxOcVoltageOffset` members of ::zes_oc_capabilities_t.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCurrentVoltageTarget )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pCurrentVoltageOffset )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyOcSetVoltageTargetPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double CurrentVoltageTarget,                    ///< [in] Overclock voltage in Volts. This cannot be greater than the
                                                        ///< `maxOcVoltage` member of ::zes_oc_capabilities_t.
        double CurrentVoltageOffset                     ///< [in] This voltage offset is applied to all points on the
                                                        ///< voltage/frequency curve, include the new overclock voltageTarget.
                                                        ///< Valid range is between the `minOcVoltageOffset` and
                                                        ///< `maxOcVoltageOffset` members of ::zes_oc_capabilities_t.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyOcSetModePrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_mode_t CurrentOcMode                     ///< [in] Current Overclocking Mode ::zes_oc_mode_t.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( ZES_OC_MODE_FIXED < CurrentOcMode )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyOcGetModePrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_mode_t* pCurrentOcMode                   ///< [out] Current Overclocking Mode ::zes_oc_mode_t.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCurrentOcMode )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyOcGetIccMaxPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                        ///< successful return.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pOcIccMax )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyOcSetIccMaxPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyOcGetTjMaxPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                        ///< on successful return.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pOcTjMax )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFrequencyOcSetTjMaxPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
        )
    {
        if( nullptr == hFrequency )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumLedsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_led_handle_t* phLed                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesLedGetPropertiesPrologue(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
        )
    {
        if( nullptr == hLed )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesLedGetStatePrologue(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
        )
    {
        if( nullptr == hLed )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pState )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pState);
    }


    ze_result_t
    ZESParameterValidation::zesLedSetStatePrologue(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        ze_bool_t enable                                ///< [in] Set to TRUE to turn the LED on, FALSE to turn off.
        )
    {
        if( nullptr == hLed )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesLedSetColorPrologue(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        const zes_led_color_t* pColor                   ///< [in] New color of the LED.
        )
    {
        if( nullptr == hLed )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pColor )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumMemoryModulesPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_mem_handle_t* phMemory                      ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesMemoryGetPropertiesPrologue(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
        )
    {
        if( nullptr == hMemory )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesMemoryGetStatePrologue(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
        )
    {
        if( nullptr == hMemory )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pState )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pState);
    }


    ze_result_t
    ZESParameterValidation::zesMemoryGetBandwidthPrologue(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_bandwidth_t* pBandwidth                 ///< [in,out] Will contain the total number of bytes read from and written
                                                        ///< to memory, as well as the current maximum bandwidth.
        )
    {
        if( nullptr == hMemory )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pBandwidth )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumPerformanceFactorDomainsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_perf_handle_t* phPerf                       ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesPerformanceFactorGetPropertiesPrologue(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        zes_perf_properties_t* pProperties              ///< [in,out] Will contain information about the specified Performance
                                                        ///< Factor domain.
        )
    {
        if( nullptr == hPerf )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesPerformanceFactorGetConfigPrologue(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        double* pFactor                                 ///< [in,out] Will contain the actual Performance Factor being used by the
                                                        ///< hardware (may not be the same as the requested Performance Factor).
        )
    {
        if( nullptr == hPerf )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pFactor )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesPerformanceFactorSetConfigPrologue(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        double factor                                   ///< [in] The new Performance Factor.
        )
    {
        if( nullptr == hPerf )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumPowerDomainsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_pwr_handle_t* phPower                       ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceGetCardPowerDomainPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pwr_handle_t* phPower                       ///< [in,out] power domain handle for the entire PCIe card.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phPower )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesPowerGetPropertiesPrologue(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        if( nullptr == hPower )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesPowerGetEnergyCounterPrologue(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_energy_counter_t* pEnergy             ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
        )
    {
        if( nullptr == hPower )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pEnergy )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesPowerGetLimitsPrologue(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_sustained_limit_t* pSustained,        ///< [in,out][optional] The sustained power limit. If this is null, the
                                                        ///< current sustained power limits will not be returned.
        zes_power_burst_limit_t* pBurst,                ///< [in,out][optional] The burst power limit. If this is null, the current
                                                        ///< peak power limits will not be returned.
        zes_power_peak_limit_t* pPeak                   ///< [in,out][optional] The peak power limit. If this is null, the peak
                                                        ///< power limits will not be returned.
        )
    {
        if( nullptr == hPower )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesPowerSetLimitsPrologue(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        const zes_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit. If this is null, no changes
                                                        ///< will be made to the sustained power limits.
        const zes_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit. If this is null, no changes will
                                                        ///< be made to the burst power limits.
        const zes_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit. If this is null, no changes will
                                                        ///< be made to the peak power limits.
        )
    {
        if( nullptr == hPower )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesPowerGetEnergyThresholdPrologue(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_energy_threshold_t* pThreshold              ///< [in,out] Returns information about the energy threshold setting -
                                                        ///< enabled/energy threshold/process ID.
        )
    {
        if( nullptr == hPower )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pThreshold )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesPowerSetEnergyThresholdPrologue(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        double threshold                                ///< [in] The energy threshold to be set in joules.
        )
    {
        if( nullptr == hPower )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumPsusPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_psu_handle_t* phPsu                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesPsuGetPropertiesPrologue(
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
        )
    {
        if( nullptr == hPsu )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesPsuGetStatePrologue(
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
        )
    {
        if( nullptr == hPsu )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pState )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pState);
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumRasErrorSetsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_ras_handle_t* phRas                         ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesRasGetPropertiesPrologue(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
        )
    {
        if( nullptr == hRas )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesRasGetConfigPrologue(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_config_t* pConfig                       ///< [in,out] Will be populed with the current RAS configuration -
                                                        ///< thresholds used to trigger events
        )
    {
        if( nullptr == hRas )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pConfig )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pConfig);
    }


    ze_result_t
    ZESParameterValidation::zesRasSetConfigPrologue(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        const zes_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
        )
    {
        if( nullptr == hRas )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pConfig )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pConfig);
    }


    ze_result_t
    ZESParameterValidation::zesRasGetStatePrologue(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
        zes_ras_state_t* pState                         ///< [in,out] Breakdown of where errors have occurred
        )
    {
        if( nullptr == hRas )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pState )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pState);
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumSchedulersPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_sched_handle_t* phScheduler                 ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesSchedulerGetPropertiesPrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Handle for the component.
        zes_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        if( nullptr == hScheduler )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesSchedulerGetCurrentModePrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
        )
    {
        if( nullptr == hScheduler )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pMode )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesSchedulerGetTimeoutModePropertiesPrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zes_sched_timeout_properties_t* pConfig         ///< [in,out] Will contain the current parameters for this mode.
        )
    {
        if( nullptr == hScheduler )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pConfig )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pConfig);
    }


    ze_result_t
    ZESParameterValidation::zesSchedulerGetTimesliceModePropertiesPrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zes_sched_timeslice_properties_t* pConfig       ///< [in,out] Will contain the current parameters for this mode.
        )
    {
        if( nullptr == hScheduler )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pConfig )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pConfig);
    }


    ze_result_t
    ZESParameterValidation::zesSchedulerSetTimeoutModePrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        if( nullptr == hScheduler )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pNeedReload )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesSchedulerSetTimesliceModePrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        if( nullptr == hScheduler )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == pNeedReload )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesSchedulerSetExclusiveModePrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        if( nullptr == hScheduler )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pNeedReload )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesSchedulerSetComputeUnitDebugModePrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        if( nullptr == hScheduler )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pNeedReload )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumStandbyDomainsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_standby_handle_t* phStandby                 ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesStandbyGetPropertiesPrologue(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
        )
    {
        if( nullptr == hStandby )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesStandbyGetModePrologue(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
        )
    {
        if( nullptr == hStandby )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pMode )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesStandbySetModePrologue(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t mode                   ///< [in] New standby mode.
        )
    {
        if( nullptr == hStandby )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( ZES_STANDBY_PROMO_MODE_NEVER < mode )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumTemperatureSensorsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_temp_handle_t* phTemperature                ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesTemperatureGetPropertiesPrologue(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
        )
    {
        if( nullptr == hTemperature )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesTemperatureGetConfigPrologue(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
        )
    {
        if( nullptr == hTemperature )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pConfig )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pConfig);
    }


    ze_result_t
    ZESParameterValidation::zesTemperatureSetConfigPrologue(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        const zes_temp_config_t* pConfig                ///< [in] New configuration.
        )
    {
        if( nullptr == hTemperature )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pConfig )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pConfig);
    }


    ze_result_t
    ZESParameterValidation::zesTemperatureGetStatePrologue(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                        ///< in degrees Celsius.
        )
    {
        if( nullptr == hTemperature )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pTemperature )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesPowerGetLimitsExtPrologue(
        zes_pwr_handle_t hPower,                        ///< [in] Power domain handle instance.
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of power limit descriptors. If count is
                                                        ///< zero, then the driver shall update the value with the total number of
                                                        ///< components of this type that are available. If count is greater than
                                                        ///< the number of components of this type that are available, then the
                                                        ///< driver shall update the value with the correct number of components.
        zes_power_limit_ext_desc_t* pSustained          ///< [in,out][optional][range(0, *pCount)] Array of query results for power
                                                        ///< limit descriptors. If count is less than the number of components of
                                                        ///< this type that are available, then the driver shall only retrieve that
                                                        ///< number of components.
        )
    {
        if( nullptr == hPower )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pSustained);
    }


    ze_result_t
    ZESParameterValidation::zesPowerSetLimitsExtPrologue(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        uint32_t* pCount,                               ///< [in] Pointer to the number of power limit descriptors.
        zes_power_limit_ext_desc_t* pSustained          ///< [in][optional][range(0, *pCount)] Array of power limit descriptors.
        )
    {
        if( nullptr == hPower )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pSustained);
    }


    ze_result_t
    ZESParameterValidation::zesEngineGetActivityExtPrologue(
        zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of VF engine stats descriptors.
                                                        ///<  - if count is zero, the driver shall update the value with the total
                                                        ///< number of engine stats available.
                                                        ///<  - if count is greater than the total number of engine stats
                                                        ///< available, the driver shall update the value with the correct number
                                                        ///< of engine stats available.
                                                        ///<  - The count returned is the sum of number of VF instances currently
                                                        ///< available and the PF instance.
        zes_engine_stats_t* pStats                      ///< [in,out][optional][range(0, *pCount)] array of engine group activity counters.
                                                        ///<  - if count is less than the total number of engine stats available,
                                                        ///< then driver shall only retrieve that number of stats.
                                                        ///<  - the implementation shall populate the vector with engine stat for
                                                        ///< PF at index 0 of the vector followed by user provided pCount-1 number
                                                        ///< of VF engine stats.
        )
    {
        if( nullptr == hEngine )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesRasGetStateExpPrologue(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of RAS state structures that can be retrieved.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of error categories for which state can be retrieved.
                                                        ///< if count is greater than the number of RAS states available, then the
                                                        ///< driver shall update the value with the correct number of RAS states available.
        zes_ras_state_exp_t* pState                     ///< [in,out][optional][range(0, *pCount)] array of query results for RAS
                                                        ///< error states for different categories.
                                                        ///< if count is less than the number of RAS states available, then driver
                                                        ///< shall only retrieve that number of RAS states.
        )
    {
        if( nullptr == hRas )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesRasClearStateExpPrologue(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_error_category_exp_t category           ///< [in] category for which error counter is to be cleared.
        )
    {
        if( nullptr == hRas )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( ZES_RAS_ERROR_CATEGORY_EXP_L3FABRIC_ERRORS < category )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFirmwareGetSecurityVersionExpPrologue(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        char* pVersion                                  ///< [in,out] NULL terminated string value. The string "unknown" will be
                                                        ///< returned if this property cannot be determined.
        )
    {
        if( nullptr == hFirmware )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pVersion )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesFirmwareSetSecurityVersionExpPrologue(
        zes_firmware_handle_t hFirmware                 ///< [in] Handle for the component.
        )
    {
        if( nullptr == hFirmware )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceGetSubDevicePropertiesExpPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sub devices.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of sub devices currently attached to the device.
                                                        ///< if count is greater than the number of sub devices currently attached
                                                        ///< to the device, then the driver shall update the value with the correct
                                                        ///< number of sub devices.
        zes_subdevice_exp_properties_t* pSubdeviceProps ///< [in,out][optional][range(0, *pCount)] array of sub device property structures.
                                                        ///< if count is less than the number of sysman sub devices available, then
                                                        ///< the driver shall only retrieve that number of sub device property structures.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pSubdeviceProps);
    }


    ze_result_t
    ZESParameterValidation::zesDriverGetDeviceByUuidExpPrologue(
        zes_driver_handle_t hDriver,                    ///< [in] handle of the sysman driver instance
        zes_uuid_t uuid,                                ///< [in] universal unique identifier.
        zes_device_handle_t* phDevice,                  ///< [out] Sysman handle of the device.
        ze_bool_t* onSubdevice,                         ///< [out] True if the UUID belongs to the sub-device; false means that
                                                        ///< UUID belongs to the root device.
        uint32_t* subdeviceId                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
        )
    {
        if( nullptr == hDriver )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == phDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == onSubdevice )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        if( nullptr == subdeviceId )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumActiveVFExpPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_vf_handle_t* phVFhandle                     ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesVFManagementGetVFPropertiesExpPrologue(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
        zes_vf_exp_properties_t* pProperties            ///< [in,out] Will contain VF properties.
        )
    {
        if( nullptr == hVFhandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pProperties )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pProperties);
    }


    ze_result_t
    ZESParameterValidation::zesVFManagementGetVFMemoryUtilizationExpPrologue(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of VF memory stats descriptors.
                                                        ///<  - if count is zero, the driver shall update the value with the total
                                                        ///< number of memory stats available.
                                                        ///<  - if count is greater than the total number of memory stats
                                                        ///< available, the driver shall update the value with the correct number
                                                        ///< of memory stats available.
                                                        ///<  - The count returned is the sum of number of VF instances currently
                                                        ///< available and the PF instance.
        zes_vf_util_mem_exp_t* pMemUtil                 ///< [in,out][optional][range(0, *pCount)] array of memory group activity counters.
                                                        ///<  - if count is less than the total number of memory stats available,
                                                        ///< then driver shall only retrieve that number of stats.
                                                        ///<  - the implementation shall populate the vector pCount-1 number of VF
                                                        ///< memory stats.
        )
    {
        if( nullptr == hVFhandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesVFManagementGetVFEngineUtilizationExpPrologue(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of VF engine stats descriptors.
                                                        ///<  - if count is zero, the driver shall update the value with the total
                                                        ///< number of engine stats available.
                                                        ///<  - if count is greater than the total number of engine stats
                                                        ///< available, the driver shall update the value with the correct number
                                                        ///< of engine stats available.
                                                        ///<  - The count returned is the sum of number of VF instances currently
                                                        ///< available and the PF instance.
        zes_vf_util_engine_exp_t* pEngineUtil           ///< [in,out][optional][range(0, *pCount)] array of engine group activity counters.
                                                        ///<  - if count is less than the total number of engine stats available,
                                                        ///< then driver shall only retrieve that number of stats.
                                                        ///<  - the implementation shall populate the vector pCount-1 number of VF
                                                        ///< engine stats.
        )
    {
        if( nullptr == hVFhandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesVFManagementSetVFTelemetryModeExpPrologue(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
        zes_vf_info_util_exp_flags_t flags,             ///< [in] utilization flags to enable or disable. May be 0 or a valid
                                                        ///< combination of ::zes_vf_info_util_exp_flag_t.
        ze_bool_t enable                                ///< [in] Enable utilization telemetry.
        )
    {
        if( nullptr == hVFhandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( 0xf < flags )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesVFManagementSetVFTelemetrySamplingIntervalExpPrologue(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
        zes_vf_info_util_exp_flags_t flag,              ///< [in] utilization flags to set sampling interval. May be 0 or a valid
                                                        ///< combination of ::zes_vf_info_util_exp_flag_t.
        uint64_t samplingInterval                       ///< [in] Sampling interval value.
        )
    {
        if( nullptr == hVFhandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( 0xf < flag )
            return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesDeviceEnumEnabledVFExpPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of components of this type that are available.
                                                        ///< if count is greater than the number of components of this type that
                                                        ///< are available, then the driver shall update the value with the correct
                                                        ///< number of components.
        zes_vf_handle_t* phVFhandle                     ///< [in,out][optional][range(0, *pCount)] array of handle of components of
                                                        ///< this type.
                                                        ///< if count is less than the number of components of this type that are
                                                        ///< available, then the driver shall only retrieve that number of
                                                        ///< component handles.
        )
    {
        if( nullptr == hDevice )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesVFManagementGetVFCapabilitiesExpPrologue(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
        zes_vf_exp_capabilities_t* pCapability          ///< [in,out] Will contain VF capability.
        )
    {
        if( nullptr == hVFhandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCapability )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pCapability);
    }


    ze_result_t
    ZESParameterValidation::zesVFManagementGetVFMemoryUtilizationExp2Prologue(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of VF memory stats descriptors.
                                                        ///<  - if count is zero, the driver shall update the value with the total
                                                        ///< number of memory stats available.
                                                        ///<  - if count is greater than the total number of memory stats
                                                        ///< available, the driver shall update the value with the correct number
                                                        ///< of memory stats available.
        zes_vf_util_mem_exp2_t* pMemUtil                ///< [in,out][optional][range(0, *pCount)] array of memory group activity counters.
                                                        ///<  - if count is less than the total number of memory stats available,
                                                        ///< then driver shall only retrieve that number of stats.
                                                        ///<  - the implementation shall populate the vector pCount-1 number of VF
                                                        ///< memory stats.
        )
    {
        if( nullptr == hVFhandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesVFManagementGetVFEngineUtilizationExp2Prologue(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
        uint32_t* pCount,                               ///< [in,out] Pointer to the number of VF engine stats descriptors.
                                                        ///<  - if count is zero, the driver shall update the value with the total
                                                        ///< number of engine stats available.
                                                        ///<  - if count is greater than the total number of engine stats
                                                        ///< available, the driver shall update the value with the correct number
                                                        ///< of engine stats available.
        zes_vf_util_engine_exp2_t* pEngineUtil          ///< [in,out][optional][range(0, *pCount)] array of engine group activity counters.
                                                        ///<  - if count is less than the total number of engine stats available,
                                                        ///< then driver shall only retrieve that number of stats.
                                                        ///<  - the implementation shall populate the vector pCount-1 number of VF
                                                        ///< engine stats.
        )
    {
        if( nullptr == hVFhandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCount )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ZE_RESULT_SUCCESS;
    }


    ze_result_t
    ZESParameterValidation::zesVFManagementGetVFCapabilitiesExp2Prologue(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
        zes_vf_exp2_capabilities_t* pCapability         ///< [in,out] Will contain VF capability.
        )
    {
        if( nullptr == hVFhandle )
            return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        if( nullptr == pCapability )
            return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        return ParameterValidation::validateExtensions(pCapability);
    }

}