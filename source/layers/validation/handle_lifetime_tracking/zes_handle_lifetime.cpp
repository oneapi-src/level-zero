/*
 * ***THIS FILE IS GENERATED. ***
 * See handle_lifetime.cpp.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_handle_lifetime.cpp
 *
 */
#include "ze_validation_layer.h"
#include "ze_handle_lifetime.h"

namespace validation_layer
{
    ze_result_t
    ZESHandleLifetimeValidation::zesDriverGetExtensionPropertiesPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDriverGetExtensionFunctionAddressPrologue(
        zes_driver_handle_t hDriver,                    ///< [in] handle of the driver instance
        const char* name,                               ///< [in] extension function name
        void** ppFunctionAddress                        ///< [out] pointer to function pointer
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceGetPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceGetPropertiesPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceGetStatePrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceResetPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
        ze_bool_t force                                 ///< [in] If set to true, all applications that are currently using the
                                                        ///< device will be forcibly killed.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceResetExtPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
        zes_reset_properties_t* pProperties             ///< [in] Device reset properties to apply
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceProcessesGetStatePrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDevicePciGetPropertiesPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDevicePciGetStatePrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDevicePciGetBarsPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDevicePciGetStatsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceSetOverclockWaiverPrologue(
        zes_device_handle_t hDevice                     ///< [in] Sysman handle of the device.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceGetOverclockDomainsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pOverclockDomains                     ///< [in,out] Returns the overclock domains that are supported (a bit for
                                                        ///< each of enum ::zes_overclock_domain_t). If no bits are set, the device
                                                        ///< doesn't support overclocking.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceGetOverclockControlsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_overclock_domain_t domainType,              ///< [in] Domain type.
        uint32_t* pAvailableControls                    ///< [in,out] Returns the overclock controls that are supported for the
                                                        ///< specified overclock domain (a bit for each of enum
                                                        ///< ::zes_overclock_control_t).
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceResetOverclockSettingsPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        ze_bool_t onShippedState                        ///< [in] True will reset to shipped state; false will reset to
                                                        ///< manufacturing state
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceReadOverclockStatePrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_overclock_mode_t* pOverclockMode,           ///< [out] One of overclock mode.
        ze_bool_t* pWaiverSetting,                      ///< [out] Waiver setting: 0 = Waiver not set, 1 = waiver has been set.
        ze_bool_t* pOverclockState,                     ///< [out] Current settings 0 =manufacturing state, 1= shipped state)..
        zes_pending_action_t* pPendingAction,           ///< [out] This enum is returned when the driver attempts to set an
                                                        ///< overclock control or reset overclock settings.
        ze_bool_t* pPendingReset                        ///< [out] Pending reset 0 =manufacturing state, 1= shipped state)..
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumOverclockDomainsPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesOverclockGetDomainPropertiesPrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_properties_t* pDomainProperties   ///< [in,out] The overclock properties for the specified domain.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDomainHandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesOverclockGetDomainVFPropertiesPrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_vf_property_t* pVFProperties                ///< [in,out] The VF min,max,step for a specified domain.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDomainHandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesOverclockGetDomainControlPropertiesPrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Handle for the component.
        zes_control_property_t* pControlProperties      ///< [in,out] overclock control values.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDomainHandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesOverclockGetControlCurrentValuePrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component.
        zes_overclock_control_t DomainControl,          ///< [in] Overclock Control.
        double* pValue                                  ///< [in,out] Getting overclock control value for the specified control.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDomainHandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesOverclockGetControlPendingValuePrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Overclock Control.
        double* pValue                                  ///< [out] Returns the pending value for a given control. The units and
                                                        ///< format of the value depend on the control type.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDomainHandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesOverclockSetControlUserValuePrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Domain Control.
        double pValue,                                  ///< [in] The new value of the control. The units and format of the value
                                                        ///< depend on the control type.
        zes_pending_action_t* pPendingAction            ///< [out] Pending overclock setting.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDomainHandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesOverclockGetControlStatePrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Domain Control.
        zes_control_state_t* pControlState,             ///< [out] Current overclock control state.
        zes_pending_action_t* pPendingAction            ///< [out] Pending overclock setting.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDomainHandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesOverclockGetVFPointValuesPrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_vf_type_t VFType,                           ///< [in] Voltage or Freqency point to read.
        zes_vf_array_type_t VFArrayType,                ///< [in] User,Default or Live VF array to read from
        uint32_t PointIndex,                            ///< [in] Point index - number between (0, max_num_points - 1).
        uint32_t* PointValue                            ///< [out] Returns the frequency in 1kHz units or voltage in millivolt
                                                        ///< units from the custom V-F curve at the specified zero-based index 
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDomainHandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesOverclockSetVFPointValuesPrologue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_vf_type_t VFType,                           ///< [in] Voltage or Freqency point to read.
        uint32_t PointIndex,                            ///< [in] Point index - number between (0, max_num_points - 1).
        uint32_t PointValue                             ///< [in] Writes frequency in 1kHz units or voltage in millivolt units to
                                                        ///< custom V-F curve at the specified zero-based index 
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDomainHandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumDiagnosticTestSuitesPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDiagnosticsGetPropertiesPrologue(
        zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
        zes_diag_properties_t* pProperties              ///< [in,out] Structure describing the properties of a diagnostics test
                                                        ///< suite
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDiagnostics )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDiagnosticsGetTestsPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDiagnostics )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDiagnosticsRunTestsPrologue(
        zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
        uint32_t startIndex,                            ///< [in] The index of the first test to run. Set to
                                                        ///< ::ZES_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t endIndex,                              ///< [in] The index of the last test to run. Set to
                                                        ///< ::ZES_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        zes_diag_result_t* pResult                      ///< [in,out] The result of the diagnostics
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDiagnostics )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEccAvailablePrologue(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        ze_bool_t* pAvailable                           ///< [out] ECC functionality is available (true)/unavailable (false).
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEccConfigurablePrologue(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        ze_bool_t* pConfigurable                        ///< [out] ECC can be enabled/disabled (true)/enabled/disabled (false).
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceGetEccStatePrologue(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        zes_device_ecc_properties_t* pState             ///< [out] ECC state, pending state, and pending action for state change.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceSetEccStatePrologue(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        const zes_device_ecc_desc_t* newState,          ///< [in] Pointer to desired ECC state.
        zes_device_ecc_properties_t* pState             ///< [out] ECC state, pending state, and pending action for state change.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumEngineGroupsPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesEngineGetPropertiesPrologue(
        zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
        zes_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEngine )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesEngineGetActivityPrologue(
        zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
        zes_engine_stats_t* pStats                      ///< [in,out] Will contain a snapshot of the engine group activity
                                                        ///< counters.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hEngine )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEventRegisterPrologue(
        zes_device_handle_t hDevice,                    ///< [in] The device handle.
        zes_event_type_flags_t events                   ///< [in] List of events to listen to.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDriverEventListenPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phDevices) && (i < count); ++i){
            if (!context.handleLifetime->isHandleValid( phDevices[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDriverEventListenExPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phDevices) && (i < count); ++i){
            if (!context.handleLifetime->isHandleValid( phDevices[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumFabricPortsPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFabricPortGetPropertiesPrologue(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPort )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFabricPortGetLinkTypePrologue(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_link_type_t* pLinkType               ///< [in,out] Will contain details about the link attached to the Fabric
                                                        ///< port.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPort )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFabricPortGetConfigPrologue(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPort )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFabricPortSetConfigPrologue(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        const zes_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPort )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFabricPortGetStatePrologue(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPort )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFabricPortGetThroughputPrologue(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPort )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFabricPortGetFabricErrorCountersPrologue(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_error_counters_t* pErrors       ///< [in,out] Will contain the Fabric port Error counters.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPort )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFabricPortGetMultiPortThroughputPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t numPorts,                              ///< [in] Number of ports enumerated in function ::zesDeviceEnumFabricPorts
        zes_fabric_port_handle_t* phPort,               ///< [in][range(0, numPorts)] array of fabric port handles provided by user
                                                        ///< to gather throughput values. 
        zes_fabric_port_throughput_t** pThroughput      ///< [out][range(0, numPorts)] array of fabric port throughput counters
                                                        ///< from multiple ports of type ::zes_fabric_port_throughput_t.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        for (size_t i = 0; ( nullptr != phPort) && (i < numPorts); ++i){
            if (!context.handleLifetime->isHandleValid( phPort[i] )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
            }
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumFansPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFanGetPropertiesPrologue(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFan )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFanGetConfigPrologue(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFan )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFanSetDefaultModePrologue(
        zes_fan_handle_t hFan                           ///< [in] Handle for the component.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFan )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFanSetFixedSpeedModePrologue(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        const zes_fan_speed_t* speed                    ///< [in] The fixed fan speed setting
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFan )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFanSetSpeedTableModePrologue(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        const zes_fan_speed_table_t* speedTable         ///< [in] A table containing temperature/speed pairs.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFan )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFanGetStatePrologue(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
        int32_t* pSpeed                                 ///< [in,out] Will contain the current speed of the fan in the units
                                                        ///< requested. A value of -1 indicates that the fan speed cannot be
                                                        ///< measured.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFan )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumFirmwaresPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFirmwareGetPropertiesPrologue(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        zes_firmware_properties_t* pProperties          ///< [in,out] Pointer to an array that will hold the properties of the
                                                        ///< firmware
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFirmware )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFirmwareFlashPrologue(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFirmware )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFirmwareGetFlashProgressPrologue(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        uint32_t* pCompletionPercent                    ///< [in,out] Pointer to the Completion Percentage of Firmware Update
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFirmware )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFirmwareGetConsoleLogsPrologue(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        size_t* pSize,                                  ///< [in,out] size of firmware log
        char* pFirmwareLog                              ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFirmware )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumFrequencyDomainsPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyGetPropertiesPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyGetAvailableClocksPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyGetRangePrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_range_t* pLimits                       ///< [in,out] The range between which the hardware can operate for the
                                                        ///< specified domain.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencySetRangePrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        const zes_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyGetStatePrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyGetThrottleTimePrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_throttle_time_t* pThrottleTime         ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyOcGetCapabilitiesPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyOcGetFrequencyTargetPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pCurrentOcFrequency                     ///< [out] Overclocking Frequency in MHz, if extended moded is supported,
                                                        ///< will returned in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                        ///< cannot be greater than the `maxOcFrequency` member of
                                                        ///< ::zes_oc_capabilities_t.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyOcSetFrequencyTargetPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double CurrentOcFrequency                       ///< [in] Overclocking Frequency in MHz, if extended moded is supported, it
                                                        ///< could be set in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                        ///< cannot be greater than the `maxOcFrequency` member of
                                                        ///< ::zes_oc_capabilities_t.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyOcGetVoltageTargetPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pCurrentVoltageTarget,                  ///< [out] Overclock voltage in Volts. This cannot be greater than the
                                                        ///< `maxOcVoltage` member of ::zes_oc_capabilities_t.
        double* pCurrentVoltageOffset                   ///< [out] This voltage offset is applied to all points on the
                                                        ///< voltage/frequency curve, including the new overclock voltageTarget.
                                                        ///< Valid range is between the `minOcVoltageOffset` and
                                                        ///< `maxOcVoltageOffset` members of ::zes_oc_capabilities_t.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyOcSetVoltageTargetPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double CurrentVoltageTarget,                    ///< [in] Overclock voltage in Volts. This cannot be greater than the
                                                        ///< `maxOcVoltage` member of ::zes_oc_capabilities_t.
        double CurrentVoltageOffset                     ///< [in] This voltage offset is applied to all points on the
                                                        ///< voltage/frequency curve, include the new overclock voltageTarget.
                                                        ///< Valid range is between the `minOcVoltageOffset` and
                                                        ///< `maxOcVoltageOffset` members of ::zes_oc_capabilities_t.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyOcSetModePrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_mode_t CurrentOcMode                     ///< [in] Current Overclocking Mode ::zes_oc_mode_t.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyOcGetModePrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_mode_t* pCurrentOcMode                   ///< [out] Current Overclocking Mode ::zes_oc_mode_t.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyOcGetIccMaxPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                        ///< successful return.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyOcSetIccMaxPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyOcGetTjMaxPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                        ///< on successful return.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFrequencyOcSetTjMaxPrologue(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFrequency )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumLedsPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesLedGetPropertiesPrologue(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hLed )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesLedGetStatePrologue(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hLed )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesLedSetStatePrologue(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        ze_bool_t enable                                ///< [in] Set to TRUE to turn the LED on, FALSE to turn off.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hLed )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesLedSetColorPrologue(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        const zes_led_color_t* pColor                   ///< [in] New color of the LED.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hLed )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumMemoryModulesPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesMemoryGetPropertiesPrologue(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hMemory )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesMemoryGetStatePrologue(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hMemory )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesMemoryGetBandwidthPrologue(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_bandwidth_t* pBandwidth                 ///< [in,out] Will contain the total number of bytes read from and written
                                                        ///< to memory, as well as the current maximum bandwidth.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hMemory )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumPerformanceFactorDomainsPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesPerformanceFactorGetPropertiesPrologue(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        zes_perf_properties_t* pProperties              ///< [in,out] Will contain information about the specified Performance
                                                        ///< Factor domain.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPerf )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesPerformanceFactorGetConfigPrologue(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        double* pFactor                                 ///< [in,out] Will contain the actual Performance Factor being used by the
                                                        ///< hardware (may not be the same as the requested Performance Factor).
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPerf )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesPerformanceFactorSetConfigPrologue(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        double factor                                   ///< [in] The new Performance Factor.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPerf )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumPowerDomainsPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceGetCardPowerDomainPrologue(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pwr_handle_t* phPower                       ///< [in,out] power domain handle for the entire PCIe card.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesPowerGetPropertiesPrologue(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPower )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesPowerGetEnergyCounterPrologue(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_energy_counter_t* pEnergy             ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPower )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesPowerGetLimitsPrologue(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_sustained_limit_t* pSustained,        ///< [in,out][optional] The sustained power limit. If this is null, the
                                                        ///< current sustained power limits will not be returned.
        zes_power_burst_limit_t* pBurst,                ///< [in,out][optional] The burst power limit. If this is null, the current
                                                        ///< peak power limits will not be returned.
        zes_power_peak_limit_t* pPeak                   ///< [in,out][optional] The peak power limit. If this is null, the peak
                                                        ///< power limits will not be returned.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPower )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesPowerSetLimitsPrologue(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        const zes_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit. If this is null, no changes
                                                        ///< will be made to the sustained power limits.
        const zes_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit. If this is null, no changes will
                                                        ///< be made to the burst power limits.
        const zes_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit. If this is null, no changes will
                                                        ///< be made to the peak power limits.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPower )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesPowerGetEnergyThresholdPrologue(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_energy_threshold_t* pThreshold              ///< [in,out] Returns information about the energy threshold setting -
                                                        ///< enabled/energy threshold/process ID.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPower )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesPowerSetEnergyThresholdPrologue(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        double threshold                                ///< [in] The energy threshold to be set in joules.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPower )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumPsusPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesPsuGetPropertiesPrologue(
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPsu )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesPsuGetStatePrologue(
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPsu )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumRasErrorSetsPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesRasGetPropertiesPrologue(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hRas )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesRasGetConfigPrologue(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_config_t* pConfig                       ///< [in,out] Will be populed with the current RAS configuration -
                                                        ///< thresholds used to trigger events
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hRas )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesRasSetConfigPrologue(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        const zes_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hRas )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesRasGetStatePrologue(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
        zes_ras_state_t* pState                         ///< [in,out] Breakdown of where errors have occurred
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hRas )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumSchedulersPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesSchedulerGetPropertiesPrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Handle for the component.
        zes_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hScheduler )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesSchedulerGetCurrentModePrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hScheduler )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesSchedulerGetTimeoutModePropertiesPrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zes_sched_timeout_properties_t* pConfig         ///< [in,out] Will contain the current parameters for this mode.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hScheduler )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesSchedulerGetTimesliceModePropertiesPrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zes_sched_timeslice_properties_t* pConfig       ///< [in,out] Will contain the current parameters for this mode.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hScheduler )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesSchedulerSetTimeoutModePrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hScheduler )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesSchedulerSetTimesliceModePrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hScheduler )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesSchedulerSetExclusiveModePrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hScheduler )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesSchedulerSetComputeUnitDebugModePrologue(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hScheduler )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumStandbyDomainsPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesStandbyGetPropertiesPrologue(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hStandby )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesStandbyGetModePrologue(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hStandby )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesStandbySetModePrologue(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t mode                   ///< [in] New standby mode.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hStandby )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumTemperatureSensorsPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesTemperatureGetPropertiesPrologue(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hTemperature )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesTemperatureGetConfigPrologue(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hTemperature )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesTemperatureSetConfigPrologue(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        const zes_temp_config_t* pConfig                ///< [in] New configuration.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hTemperature )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesTemperatureGetStatePrologue(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                        ///< in degrees Celsius.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hTemperature )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesPowerGetLimitsExtPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hPower )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesPowerSetLimitsExtPrologue(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        uint32_t* pCount,                               ///< [in] Pointer to the number of power limit descriptors.
        zes_power_limit_ext_desc_t* pSustained          ///< [in][optional][range(0, *pCount)] Array of power limit descriptors.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hPower )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesEngineGetActivityExtPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hEngine )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesRasGetStateExpPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hRas )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesRasClearStateExpPrologue(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_error_category_exp_t category           ///< [in] category for which error counter is to be cleared.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hRas )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFirmwareGetSecurityVersionExpPrologue(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        char* pVersion                                  ///< [in,out] NULL terminated string value. The string "unknown" will be
                                                        ///< returned if this property cannot be determined.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFirmware )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesFirmwareSetSecurityVersionExpPrologue(
        zes_firmware_handle_t hFirmware                 ///< [in] Handle for the component.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hFirmware )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceGetSubDevicePropertiesExpPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDriverGetDeviceByUuidExpPrologue(
        zes_driver_handle_t hDriver,                    ///< [in] handle of the sysman driver instance
        zes_uuid_t uuid,                                ///< [in] universal unique identifier.
        zes_device_handle_t* phDevice,                  ///< [out] Sysman handle of the device.
        ze_bool_t* onSubdevice,                         ///< [out] True if the UUID belongs to the sub-device; false means that
                                                        ///< UUID belongs to the root device.
        uint32_t* subdeviceId                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hDriver )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumActiveVFExpPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesVFManagementGetVFPropertiesExpPrologue(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
        zes_vf_exp_properties_t* pProperties            ///< [in,out] Will contain VF properties.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hVFhandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesVFManagementGetVFMemoryUtilizationExpPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hVFhandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesVFManagementGetVFEngineUtilizationExpPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hVFhandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesVFManagementSetVFTelemetryModeExpPrologue(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
        zes_vf_info_util_exp_flags_t flags,             ///< [in] utilization flags to enable or disable. May be 0 or a valid
                                                        ///< combination of ::zes_vf_info_util_exp_flag_t.
        ze_bool_t enable                                ///< [in] Enable utilization telemetry.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hVFhandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesVFManagementSetVFTelemetrySamplingIntervalExpPrologue(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
        zes_vf_info_util_exp_flags_t flag,              ///< [in] utilization flags to set sampling interval. May be 0 or a valid
                                                        ///< combination of ::zes_vf_info_util_exp_flag_t.
        uint64_t samplingInterval                       ///< [in] Sampling interval value.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hVFhandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesDeviceEnumEnabledVFExpPrologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hDevice )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesVFManagementGetVFCapabilitiesExpPrologue(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
        zes_vf_exp_capabilities_t* pCapability          ///< [in,out] Will contain VF capability.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hVFhandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesVFManagementGetVFMemoryUtilizationExp2Prologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hVFhandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesVFManagementGetVFEngineUtilizationExp2Prologue(
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
        
        if ( !context.handleLifetime->isHandleValid( hVFhandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
    ze_result_t
    ZESHandleLifetimeValidation::zesVFManagementGetVFCapabilitiesExp2Prologue(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
        zes_vf_exp2_capabilities_t* pCapability         ///< [in,out] Will contain VF capability.
        )
    { 
        
        if ( !context.handleLifetime->isHandleValid( hVFhandle )){
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;
        }
        return ZE_RESULT_SUCCESS;
    }
}