/*
 *
 * Copyright (C) 2019-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_valddi.cpp
 *
 */
#include "ze_validation_layer.h"

namespace validation_layer
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesInit
    __zedlllocal ze_result_t ZE_APICALL
    zesInit(
        zes_init_flags_t flags                          ///< [in] initialization flags.
                                                        ///< currently unused, must be 0 (default).
        )
    {
        auto pfnInit = context.zesDdiTable.Global.pfnInit;

        if( nullptr == pfnInit )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( 0x1 < flags )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnInit( flags );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDriverGet
    __zedlllocal ze_result_t ZE_APICALL
    zesDriverGet(
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
        auto pfnGet = context.zesDdiTable.Driver.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGet( pCount, phDrivers );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGet
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGet(
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
        auto pfnGet = context.zesDdiTable.Device.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGet( hDriver, pCount, phDevices );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGetProperties(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Device.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hDevice, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGetState(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
        )
    {
        auto pfnGetState = context.zesDdiTable.Device.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hDevice, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceReset
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceReset(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
        ze_bool_t force                                 ///< [in] If set to true, all applications that are currently using the
                                                        ///< device will be forcibly killed.
        )
    {
        auto pfnReset = context.zesDdiTable.Device.pfnReset;

        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnReset( hDevice, force );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceProcessesGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceProcessesGetState(
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
        auto pfnProcessesGetState = context.zesDdiTable.Device.pfnProcessesGetState;

        if( nullptr == pfnProcessesGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnProcessesGetState( hDevice, pCount, pProcesses );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesDevicePciGetProperties(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
        )
    {
        auto pfnPciGetProperties = context.zesDdiTable.Device.pfnPciGetProperties;

        if( nullptr == pfnPciGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetProperties( hDevice, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesDevicePciGetState(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
        )
    {
        auto pfnPciGetState = context.zesDdiTable.Device.pfnPciGetState;

        if( nullptr == pfnPciGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetState( hDevice, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetBars
    __zedlllocal ze_result_t ZE_APICALL
    zesDevicePciGetBars(
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
        auto pfnPciGetBars = context.zesDdiTable.Device.pfnPciGetBars;

        if( nullptr == pfnPciGetBars )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetBars( hDevice, pCount, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetStats
    __zedlllocal ze_result_t ZE_APICALL
    zesDevicePciGetStats(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
        )
    {
        auto pfnPciGetStats = context.zesDdiTable.Device.pfnPciGetStats;

        if( nullptr == pfnPciGetStats )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pStats )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnPciGetStats( hDevice, pStats );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceSetOverclockWaiver
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceSetOverclockWaiver(
        zes_device_handle_t hDevice                     ///< [in] Sysman handle of the device.
        )
    {
        auto pfnSetOverclockWaiver = context.zesDdiTable.Device.pfnSetOverclockWaiver;

        if( nullptr == pfnSetOverclockWaiver )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSetOverclockWaiver( hDevice );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetOverclockDomains
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGetOverclockDomains(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pOverclockDomains                     ///< [in,out] Returns the overclock domains that are supported (a bit for
                                                        ///< each of enum ::zes_overclock_domain_t). If no bits are set, the device
                                                        ///< doesn't support overclocking.
        )
    {
        auto pfnGetOverclockDomains = context.zesDdiTable.Device.pfnGetOverclockDomains;

        if( nullptr == pfnGetOverclockDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pOverclockDomains )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetOverclockDomains( hDevice, pOverclockDomains );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetOverclockControls
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGetOverclockControls(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_overclock_domain_t domainType,              ///< [in] Domain type.
        uint32_t* pAvailableControls                    ///< [in,out] Returns the overclock controls that are supported for the
                                                        ///< specified overclock domain (a bit for each of enum
                                                        ///< ::zes_overclock_control_t).
        )
    {
        auto pfnGetOverclockControls = context.zesDdiTable.Device.pfnGetOverclockControls;

        if( nullptr == pfnGetOverclockControls )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( ZES_OVERCLOCK_DOMAIN_ADM < domainType )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == pAvailableControls )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetOverclockControls( hDevice, domainType, pAvailableControls );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceResetOverclockSettings
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceResetOverclockSettings(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        ze_bool_t onShippedState                        ///< [in] True will reset to shipped state; false will reset to
                                                        ///< manufacturing state
        )
    {
        auto pfnResetOverclockSettings = context.zesDdiTable.Device.pfnResetOverclockSettings;

        if( nullptr == pfnResetOverclockSettings )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnResetOverclockSettings( hDevice, onShippedState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceReadOverclockState
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceReadOverclockState(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_overclock_mode_t* pOverclockMode,           ///< [out] One of overclock mode.
        ze_bool_t* pWaiverSetting,                      ///< [out] Waiver setting: 0 = Waiver not set, 1 = waiver has been set.
        ze_bool_t* pOverclockState,                     ///< [out] Current settings 0 =manufacturing state, 1= shipped state)..
        zes_pending_action_t* pPendingAction,           ///< [out] This enum is returned when the driver attempts to set an
                                                        ///< overclock control or reset overclock settings.
        ze_bool_t* pPendingReset                        ///< [out] Pending reset 0 =manufacturing state, 1= shipped state)..
        )
    {
        auto pfnReadOverclockState = context.zesDdiTable.Device.pfnReadOverclockState;

        if( nullptr == pfnReadOverclockState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
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

        }

        return pfnReadOverclockState( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumOverclockDomains
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumOverclockDomains(
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
        auto pfnEnumOverclockDomains = context.zesDdiTable.Device.pfnEnumOverclockDomains;

        if( nullptr == pfnEnumOverclockDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumOverclockDomains( hDevice, pCount, phDomainHandle );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesOverclockGetDomainProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesOverclockGetDomainProperties(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_properties_t* pDomainProperties   ///< [in,out] The overclock properties for the specified domain.
        )
    {
        auto pfnGetDomainProperties = context.zesDdiTable.Overclock.pfnGetDomainProperties;

        if( nullptr == pfnGetDomainProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDomainHandle )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pDomainProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetDomainProperties( hDomainHandle, pDomainProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesOverclockGetDomainVFProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesOverclockGetDomainVFProperties(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_vf_property_t* pVFProperties                ///< [in,out] The VF min,max,step for a specified domain.
        )
    {
        auto pfnGetDomainVFProperties = context.zesDdiTable.Overclock.pfnGetDomainVFProperties;

        if( nullptr == pfnGetDomainVFProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDomainHandle )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pVFProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetDomainVFProperties( hDomainHandle, pVFProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesOverclockGetDomainControlProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesOverclockGetDomainControlProperties(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Handle for the component.
        zes_control_property_t* pControlProperties      ///< [in,out] overclock control values.
        )
    {
        auto pfnGetDomainControlProperties = context.zesDdiTable.Overclock.pfnGetDomainControlProperties;

        if( nullptr == pfnGetDomainControlProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDomainHandle )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == pControlProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetDomainControlProperties( hDomainHandle, DomainControl, pControlProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesOverclockGetControlCurrentValue
    __zedlllocal ze_result_t ZE_APICALL
    zesOverclockGetControlCurrentValue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component.
        zes_overclock_control_t DomainControl,          ///< [in] Overclock Control.
        double* pValue                                  ///< [in,out] Getting overclock control value for the specified control.
        )
    {
        auto pfnGetControlCurrentValue = context.zesDdiTable.Overclock.pfnGetControlCurrentValue;

        if( nullptr == pfnGetControlCurrentValue )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDomainHandle )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == pValue )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetControlCurrentValue( hDomainHandle, DomainControl, pValue );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesOverclockGetControlPendingValue
    __zedlllocal ze_result_t ZE_APICALL
    zesOverclockGetControlPendingValue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Overclock Control.
        double* pValue                                  ///< [out] Returns the pending value for a given control. The units and
                                                        ///< format of the value depend on the control type.
        )
    {
        auto pfnGetControlPendingValue = context.zesDdiTable.Overclock.pfnGetControlPendingValue;

        if( nullptr == pfnGetControlPendingValue )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDomainHandle )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == pValue )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetControlPendingValue( hDomainHandle, DomainControl, pValue );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesOverclockSetControlUserValue
    __zedlllocal ze_result_t ZE_APICALL
    zesOverclockSetControlUserValue(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Domain Control.
        double pValue,                                  ///< [in] The new value of the control. The units and format of the value
                                                        ///< depend on the control type.
        zes_pending_action_t* pPendingAction            ///< [out] Pending overclock setting.
        )
    {
        auto pfnSetControlUserValue = context.zesDdiTable.Overclock.pfnSetControlUserValue;

        if( nullptr == pfnSetControlUserValue )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDomainHandle )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == pPendingAction )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetControlUserValue( hDomainHandle, DomainControl, pValue, pPendingAction );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesOverclockGetControlState
    __zedlllocal ze_result_t ZE_APICALL
    zesOverclockGetControlState(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Domain Control.
        zes_control_state_t* pControlState,             ///< [out] Current overclock control state.
        zes_pending_action_t* pPendingAction            ///< [out] Pending overclock setting.
        )
    {
        auto pfnGetControlState = context.zesDdiTable.Overclock.pfnGetControlState;

        if( nullptr == pfnGetControlState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDomainHandle )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( ZES_OVERCLOCK_CONTROL_ACM_DISABLE < DomainControl )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == pControlState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pPendingAction )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetControlState( hDomainHandle, DomainControl, pControlState, pPendingAction );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesOverclockGetVFPointValues
    __zedlllocal ze_result_t ZE_APICALL
    zesOverclockGetVFPointValues(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_vf_type_t VFType,                           ///< [in] Voltage or Freqency point to read.
        zes_vf_array_type_t VFArrayType,                ///< [in] User,Default or Live VF array to read from
        uint32_t PointIndex,                            ///< [in] Point index - number between (0, max_num_points - 1).
        uint32_t* PointValue                            ///< [out] Returns the frequency in 1kHz units or voltage in millivolt
                                                        ///< units from the custom V-F curve at the specified zero-based index 
        )
    {
        auto pfnGetVFPointValues = context.zesDdiTable.Overclock.pfnGetVFPointValues;

        if( nullptr == pfnGetVFPointValues )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDomainHandle )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( ZES_VF_TYPE_FREQ < VFType )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( ZES_VF_ARRAY_TYPE_LIVE_VF_ARRAY < VFArrayType )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == PointValue )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetVFPointValues( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesOverclockSetVFPointValues
    __zedlllocal ze_result_t ZE_APICALL
    zesOverclockSetVFPointValues(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_vf_type_t VFType,                           ///< [in] Voltage or Freqency point to read.
        uint32_t PointIndex,                            ///< [in] Point index - number between (0, max_num_points - 1).
        uint32_t PointValue                             ///< [in] Writes frequency in 1kHz units or voltage in millivolt units to
                                                        ///< custom V-F curve at the specified zero-based index 
        )
    {
        auto pfnSetVFPointValues = context.zesDdiTable.Overclock.pfnSetVFPointValues;

        if( nullptr == pfnSetVFPointValues )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDomainHandle )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( ZES_VF_TYPE_FREQ < VFType )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnSetVFPointValues( hDomainHandle, VFType, PointIndex, PointValue );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumDiagnosticTestSuites
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumDiagnosticTestSuites(
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
        auto pfnEnumDiagnosticTestSuites = context.zesDdiTable.Device.pfnEnumDiagnosticTestSuites;

        if( nullptr == pfnEnumDiagnosticTestSuites )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumDiagnosticTestSuites( hDevice, pCount, phDiagnostics );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDiagnosticsGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesDiagnosticsGetProperties(
        zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
        zes_diag_properties_t* pProperties              ///< [in,out] Structure describing the properties of a diagnostics test
                                                        ///< suite
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Diagnostics.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDiagnostics )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hDiagnostics, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDiagnosticsGetTests
    __zedlllocal ze_result_t ZE_APICALL
    zesDiagnosticsGetTests(
        zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
        uint32_t* pCount,                               ///< [in,out] pointer to the number of tests.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of tests that are available.
                                                        ///< if count is greater than the number of tests that are available, then
                                                        ///< the driver shall update the value with the correct number of tests.
        zes_diag_test_t* pTests                         ///< [in,out][optional][range(0, *pCount)] array of information about
                                                        ///< individual tests sorted by increasing value of ::zes_diag_test_t.index.
                                                        ///< if count is less than the number of tests that are available, then the
                                                        ///< driver shall only retrieve that number of tests.
        )
    {
        auto pfnGetTests = context.zesDdiTable.Diagnostics.pfnGetTests;

        if( nullptr == pfnGetTests )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDiagnostics )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetTests( hDiagnostics, pCount, pTests );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDiagnosticsRunTests
    __zedlllocal ze_result_t ZE_APICALL
    zesDiagnosticsRunTests(
        zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
        uint32_t startIndex,                            ///< [in] The index of the first test to run. Set to
                                                        ///< ::ZES_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t endIndex,                              ///< [in] The index of the last test to run. Set to
                                                        ///< ::ZES_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        zes_diag_result_t* pResult                      ///< [in,out] The result of the diagnostics
        )
    {
        auto pfnRunTests = context.zesDdiTable.Diagnostics.pfnRunTests;

        if( nullptr == pfnRunTests )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDiagnostics )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pResult )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnRunTests( hDiagnostics, startIndex, endIndex, pResult );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEccAvailable
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEccAvailable(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        ze_bool_t* pAvailable                           ///< [out] ECC functionality is available (true)/unavailable (false).
        )
    {
        auto pfnEccAvailable = context.zesDdiTable.Device.pfnEccAvailable;

        if( nullptr == pfnEccAvailable )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pAvailable )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEccAvailable( hDevice, pAvailable );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEccConfigurable
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEccConfigurable(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        ze_bool_t* pConfigurable                        ///< [out] ECC can be enabled/disabled (true)/enabled/disabled (false).
        )
    {
        auto pfnEccConfigurable = context.zesDdiTable.Device.pfnEccConfigurable;

        if( nullptr == pfnEccConfigurable )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfigurable )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEccConfigurable( hDevice, pConfigurable );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetEccState
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGetEccState(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        zes_device_ecc_properties_t* pState             ///< [out] ECC state, pending state, and pending action for state change.
        )
    {
        auto pfnGetEccState = context.zesDdiTable.Device.pfnGetEccState;

        if( nullptr == pfnGetEccState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetEccState( hDevice, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceSetEccState
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceSetEccState(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        const zes_device_ecc_desc_t* newState,          ///< [in] Pointer to desired ECC state.
        zes_device_ecc_properties_t* pState             ///< [out] ECC state, pending state, and pending action for state change.
        )
    {
        auto pfnSetEccState = context.zesDdiTable.Device.pfnSetEccState;

        if( nullptr == pfnSetEccState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == newState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( ZES_DEVICE_ECC_STATE_DISABLED < newState->state )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnSetEccState( hDevice, newState, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumEngineGroups
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumEngineGroups(
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
        auto pfnEnumEngineGroups = context.zesDdiTable.Device.pfnEnumEngineGroups;

        if( nullptr == pfnEnumEngineGroups )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumEngineGroups( hDevice, pCount, phEngine );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesEngineGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesEngineGetProperties(
        zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
        zes_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Engine.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEngine )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hEngine, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesEngineGetActivity
    __zedlllocal ze_result_t ZE_APICALL
    zesEngineGetActivity(
        zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
        zes_engine_stats_t* pStats                      ///< [in,out] Will contain a snapshot of the engine group activity
                                                        ///< counters.
        )
    {
        auto pfnGetActivity = context.zesDdiTable.Engine.pfnGetActivity;

        if( nullptr == pfnGetActivity )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hEngine )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pStats )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetActivity( hEngine, pStats );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEventRegister
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEventRegister(
        zes_device_handle_t hDevice,                    ///< [in] The device handle.
        zes_event_type_flags_t events                   ///< [in] List of events to listen to.
        )
    {
        auto pfnEventRegister = context.zesDdiTable.Device.pfnEventRegister;

        if( nullptr == pfnEventRegister )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( 0x7fff < events )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnEventRegister( hDevice, events );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDriverEventListen
    __zedlllocal ze_result_t ZE_APICALL
    zesDriverEventListen(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then will check status and return immediately;
                                                        ///< if UINT32_MAX, then function will not return until events arrive.
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
        auto pfnEventListen = context.zesDdiTable.Driver.pfnEventListen;

        if( nullptr == pfnEventListen )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phDevices )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pNumDeviceEvents )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pEvents )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEventListen( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDriverEventListenEx
    __zedlllocal ze_result_t ZE_APICALL
    zesDriverEventListenEx(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint64_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then will check status and return immediately;
                                                        ///< if UINT64_MAX, then function will not return until events arrive.
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
        auto pfnEventListenEx = context.zesDdiTable.Driver.pfnEventListenEx;

        if( nullptr == pfnEventListenEx )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDriver )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phDevices )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pNumDeviceEvents )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pEvents )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEventListenEx( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumFabricPorts
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumFabricPorts(
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
        auto pfnEnumFabricPorts = context.zesDdiTable.Device.pfnEnumFabricPorts;

        if( nullptr == pfnEnumFabricPorts )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumFabricPorts( hDevice, pCount, phPort );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetProperties(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.FabricPort.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hPort, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetLinkType
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetLinkType(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_link_type_t* pLinkType               ///< [in,out] Will contain details about the link attached to the Fabric
                                                        ///< port.
        )
    {
        auto pfnGetLinkType = context.zesDdiTable.FabricPort.pfnGetLinkType;

        if( nullptr == pfnGetLinkType )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pLinkType )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetLinkType( hPort, pLinkType );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetConfig(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
        )
    {
        auto pfnGetConfig = context.zesDdiTable.FabricPort.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hPort, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortSetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortSetConfig(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        const zes_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
        )
    {
        auto pfnSetConfig = context.zesDdiTable.FabricPort.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetConfig( hPort, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetState(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
        )
    {
        auto pfnGetState = context.zesDdiTable.FabricPort.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hPort, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetThroughput
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetThroughput(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
        )
    {
        auto pfnGetThroughput = context.zesDdiTable.FabricPort.pfnGetThroughput;

        if( nullptr == pfnGetThroughput )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pThroughput )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetThroughput( hPort, pThroughput );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetFabricErrorCounters
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetFabricErrorCounters(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_error_counters_t* pErrors       ///< [in,out] Will contain the Fabric port Error counters.
        )
    {
        auto pfnGetFabricErrorCounters = context.zesDdiTable.FabricPort.pfnGetFabricErrorCounters;

        if( nullptr == pfnGetFabricErrorCounters )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPort )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pErrors )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetFabricErrorCounters( hPort, pErrors );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumFans
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumFans(
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
        auto pfnEnumFans = context.zesDdiTable.Device.pfnEnumFans;

        if( nullptr == pfnEnumFans )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumFans( hDevice, pCount, phFan );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesFanGetProperties(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Fan.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hFan, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanGetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesFanGetConfig(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
        )
    {
        auto pfnGetConfig = context.zesDdiTable.Fan.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hFan, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanSetDefaultMode
    __zedlllocal ze_result_t ZE_APICALL
    zesFanSetDefaultMode(
        zes_fan_handle_t hFan                           ///< [in] Handle for the component.
        )
    {
        auto pfnSetDefaultMode = context.zesDdiTable.Fan.pfnSetDefaultMode;

        if( nullptr == pfnSetDefaultMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSetDefaultMode( hFan );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanSetFixedSpeedMode
    __zedlllocal ze_result_t ZE_APICALL
    zesFanSetFixedSpeedMode(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        const zes_fan_speed_t* speed                    ///< [in] The fixed fan speed setting
        )
    {
        auto pfnSetFixedSpeedMode = context.zesDdiTable.Fan.pfnSetFixedSpeedMode;

        if( nullptr == pfnSetFixedSpeedMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == speed )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetFixedSpeedMode( hFan, speed );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanSetSpeedTableMode
    __zedlllocal ze_result_t ZE_APICALL
    zesFanSetSpeedTableMode(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        const zes_fan_speed_table_t* speedTable         ///< [in] A table containing temperature/speed pairs.
        )
    {
        auto pfnSetSpeedTableMode = context.zesDdiTable.Fan.pfnSetSpeedTableMode;

        if( nullptr == pfnSetSpeedTableMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == speedTable )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetSpeedTableMode( hFan, speedTable );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesFanGetState(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
        int32_t* pSpeed                                 ///< [in,out] Will contain the current speed of the fan in the units
                                                        ///< requested. A value of -1 indicates that the fan speed cannot be
                                                        ///< measured.
        )
    {
        auto pfnGetState = context.zesDdiTable.Fan.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFan )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( ZES_FAN_SPEED_UNITS_PERCENT < units )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

            if( nullptr == pSpeed )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hFan, units, pSpeed );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumFirmwares
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumFirmwares(
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
        auto pfnEnumFirmwares = context.zesDdiTable.Device.pfnEnumFirmwares;

        if( nullptr == pfnEnumFirmwares )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumFirmwares( hDevice, pCount, phFirmware );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFirmwareGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesFirmwareGetProperties(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        zes_firmware_properties_t* pProperties          ///< [in,out] Pointer to an array that will hold the properties of the
                                                        ///< firmware
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Firmware.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFirmware )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hFirmware, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFirmwareFlash
    __zedlllocal ze_result_t ZE_APICALL
    zesFirmwareFlash(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    {
        auto pfnFlash = context.zesDdiTable.Firmware.pfnFlash;

        if( nullptr == pfnFlash )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFirmware )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pImage )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnFlash( hFirmware, pImage, size );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumFrequencyDomains
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumFrequencyDomains(
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
        auto pfnEnumFrequencyDomains = context.zesDdiTable.Device.pfnEnumFrequencyDomains;

        if( nullptr == pfnEnumFrequencyDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumFrequencyDomains( hDevice, pCount, phFrequency );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyGetProperties(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Frequency.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hFrequency, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyGetAvailableClocks
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyGetAvailableClocks(
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
        auto pfnGetAvailableClocks = context.zesDdiTable.Frequency.pfnGetAvailableClocks;

        if( nullptr == pfnGetAvailableClocks )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetAvailableClocks( hFrequency, pCount, phFrequency );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyGetRange
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyGetRange(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_range_t* pLimits                       ///< [in,out] The range between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto pfnGetRange = context.zesDdiTable.Frequency.pfnGetRange;

        if( nullptr == pfnGetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pLimits )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetRange( hFrequency, pLimits );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencySetRange
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencySetRange(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        const zes_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto pfnSetRange = context.zesDdiTable.Frequency.pfnSetRange;

        if( nullptr == pfnSetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pLimits )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetRange( hFrequency, pLimits );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyGetState(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
        )
    {
        auto pfnGetState = context.zesDdiTable.Frequency.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hFrequency, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyGetThrottleTime
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyGetThrottleTime(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_throttle_time_t* pThrottleTime         ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
        )
    {
        auto pfnGetThrottleTime = context.zesDdiTable.Frequency.pfnGetThrottleTime;

        if( nullptr == pfnGetThrottleTime )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pThrottleTime )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetThrottleTime( hFrequency, pThrottleTime );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetCapabilities
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcGetCapabilities(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure
                                                        ///< ::zes_oc_capabilities_t.
        )
    {
        auto pfnOcGetCapabilities = context.zesDdiTable.Frequency.pfnOcGetCapabilities;

        if( nullptr == pfnOcGetCapabilities )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pOcCapabilities )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcGetCapabilities( hFrequency, pOcCapabilities );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetFrequencyTarget
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcGetFrequencyTarget(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pCurrentOcFrequency                     ///< [out] Overclocking Frequency in MHz, if extended moded is supported,
                                                        ///< will returned in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                        ///< cannot be greater than ::zes_oc_capabilities_t.maxOcFrequency.
        )
    {
        auto pfnOcGetFrequencyTarget = context.zesDdiTable.Frequency.pfnOcGetFrequencyTarget;

        if( nullptr == pfnOcGetFrequencyTarget )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCurrentOcFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcGetFrequencyTarget( hFrequency, pCurrentOcFrequency );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetFrequencyTarget
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcSetFrequencyTarget(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double CurrentOcFrequency                       ///< [in] Overclocking Frequency in MHz, if extended moded is supported, it
                                                        ///< could be set in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                        ///< cannot be greater than ::zes_oc_capabilities_t.maxOcFrequency.
        )
    {
        auto pfnOcSetFrequencyTarget = context.zesDdiTable.Frequency.pfnOcSetFrequencyTarget;

        if( nullptr == pfnOcSetFrequencyTarget )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnOcSetFrequencyTarget( hFrequency, CurrentOcFrequency );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetVoltageTarget
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcGetVoltageTarget(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pCurrentVoltageTarget,                  ///< [out] Overclock voltage in Volts. This cannot be greater than
                                                        ///< ::zes_oc_capabilities_t.maxOcVoltage.
        double* pCurrentVoltageOffset                   ///< [out] This voltage offset is applied to all points on the
                                                        ///< voltage/frequency curve, include the new overclock voltageTarget. It
                                                        ///< can be in the range (::zes_oc_capabilities_t.minOcVoltageOffset,
                                                        ///< ::zes_oc_capabilities_t.maxOcVoltageOffset).
        )
    {
        auto pfnOcGetVoltageTarget = context.zesDdiTable.Frequency.pfnOcGetVoltageTarget;

        if( nullptr == pfnOcGetVoltageTarget )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCurrentVoltageTarget )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pCurrentVoltageOffset )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcGetVoltageTarget( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetVoltageTarget
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcSetVoltageTarget(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double CurrentVoltageTarget,                    ///< [in] Overclock voltage in Volts. This cannot be greater than
                                                        ///< ::zes_oc_capabilities_t.maxOcVoltage.
        double CurrentVoltageOffset                     ///< [in] This voltage offset is applied to all points on the
                                                        ///< voltage/frequency curve, include the new overclock voltageTarget. It
                                                        ///< can be in the range (::zes_oc_capabilities_t.minOcVoltageOffset,
                                                        ///< ::zes_oc_capabilities_t.maxOcVoltageOffset).
        )
    {
        auto pfnOcSetVoltageTarget = context.zesDdiTable.Frequency.pfnOcSetVoltageTarget;

        if( nullptr == pfnOcSetVoltageTarget )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnOcSetVoltageTarget( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetMode
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcSetMode(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_mode_t CurrentOcMode                     ///< [in] Current Overclocking Mode ::zes_oc_mode_t.
        )
    {
        auto pfnOcSetMode = context.zesDdiTable.Frequency.pfnOcSetMode;

        if( nullptr == pfnOcSetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( ZES_OC_MODE_FIXED < CurrentOcMode )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnOcSetMode( hFrequency, CurrentOcMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetMode
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcGetMode(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_mode_t* pCurrentOcMode                   ///< [out] Current Overclocking Mode ::zes_oc_mode_t.
        )
    {
        auto pfnOcGetMode = context.zesDdiTable.Frequency.pfnOcGetMode;

        if( nullptr == pfnOcGetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCurrentOcMode )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcGetMode( hFrequency, pCurrentOcMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetIccMax
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcGetIccMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                        ///< successful return.
        )
    {
        auto pfnOcGetIccMax = context.zesDdiTable.Frequency.pfnOcGetIccMax;

        if( nullptr == pfnOcGetIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pOcIccMax )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcGetIccMax( hFrequency, pOcIccMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetIccMax
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcSetIccMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
        )
    {
        auto pfnOcSetIccMax = context.zesDdiTable.Frequency.pfnOcSetIccMax;

        if( nullptr == pfnOcSetIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnOcSetIccMax( hFrequency, ocIccMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetTjMax
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcGetTjMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                        ///< on successful return.
        )
    {
        auto pfnOcGetTjMax = context.zesDdiTable.Frequency.pfnOcGetTjMax;

        if( nullptr == pfnOcGetTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pOcTjMax )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnOcGetTjMax( hFrequency, pOcTjMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetTjMax
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcSetTjMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
        )
    {
        auto pfnOcSetTjMax = context.zesDdiTable.Frequency.pfnOcSetTjMax;

        if( nullptr == pfnOcSetTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hFrequency )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnOcSetTjMax( hFrequency, ocTjMax );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumLeds
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumLeds(
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
        auto pfnEnumLeds = context.zesDdiTable.Device.pfnEnumLeds;

        if( nullptr == pfnEnumLeds )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumLeds( hDevice, pCount, phLed );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesLedGetProperties(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Led.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hLed, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesLedGetState(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
        )
    {
        auto pfnGetState = context.zesDdiTable.Led.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hLed, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedSetState
    __zedlllocal ze_result_t ZE_APICALL
    zesLedSetState(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        ze_bool_t enable                                ///< [in] Set to TRUE to turn the LED on, FALSE to turn off.
        )
    {
        auto pfnSetState = context.zesDdiTable.Led.pfnSetState;

        if( nullptr == pfnSetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSetState( hLed, enable );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedSetColor
    __zedlllocal ze_result_t ZE_APICALL
    zesLedSetColor(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        const zes_led_color_t* pColor                   ///< [in] New color of the LED.
        )
    {
        auto pfnSetColor = context.zesDdiTable.Led.pfnSetColor;

        if( nullptr == pfnSetColor )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hLed )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pColor )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetColor( hLed, pColor );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumMemoryModules
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumMemoryModules(
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
        auto pfnEnumMemoryModules = context.zesDdiTable.Device.pfnEnumMemoryModules;

        if( nullptr == pfnEnumMemoryModules )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumMemoryModules( hDevice, pCount, phMemory );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesMemoryGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesMemoryGetProperties(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Memory.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMemory )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hMemory, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesMemoryGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesMemoryGetState(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
        )
    {
        auto pfnGetState = context.zesDdiTable.Memory.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMemory )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hMemory, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesMemoryGetBandwidth
    __zedlllocal ze_result_t ZE_APICALL
    zesMemoryGetBandwidth(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_bandwidth_t* pBandwidth                 ///< [in,out] Will contain the total number of bytes read from and written
                                                        ///< to memory, as well as the current maximum bandwidth.
        )
    {
        auto pfnGetBandwidth = context.zesDdiTable.Memory.pfnGetBandwidth;

        if( nullptr == pfnGetBandwidth )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hMemory )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pBandwidth )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetBandwidth( hMemory, pBandwidth );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumPerformanceFactorDomains
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumPerformanceFactorDomains(
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
        auto pfnEnumPerformanceFactorDomains = context.zesDdiTable.Device.pfnEnumPerformanceFactorDomains;

        if( nullptr == pfnEnumPerformanceFactorDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumPerformanceFactorDomains( hDevice, pCount, phPerf );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPerformanceFactorGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesPerformanceFactorGetProperties(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        zes_perf_properties_t* pProperties              ///< [in,out] Will contain information about the specified Performance
                                                        ///< Factor domain.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.PerformanceFactor.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPerf )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hPerf, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPerformanceFactorGetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesPerformanceFactorGetConfig(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        double* pFactor                                 ///< [in,out] Will contain the actual Performance Factor being used by the
                                                        ///< hardware (may not be the same as the requested Performance Factor).
        )
    {
        auto pfnGetConfig = context.zesDdiTable.PerformanceFactor.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPerf )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pFactor )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hPerf, pFactor );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPerformanceFactorSetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesPerformanceFactorSetConfig(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        double factor                                   ///< [in] The new Performance Factor.
        )
    {
        auto pfnSetConfig = context.zesDdiTable.PerformanceFactor.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPerf )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSetConfig( hPerf, factor );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumPowerDomains
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumPowerDomains(
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
        auto pfnEnumPowerDomains = context.zesDdiTable.Device.pfnEnumPowerDomains;

        if( nullptr == pfnEnumPowerDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumPowerDomains( hDevice, pCount, phPower );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetCardPowerDomain
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGetCardPowerDomain(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pwr_handle_t* phPower                       ///< [in,out] power domain handle for the entire PCIe card.
        )
    {
        auto pfnGetCardPowerDomain = context.zesDdiTable.Device.pfnGetCardPowerDomain;

        if( nullptr == pfnGetCardPowerDomain )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == phPower )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetCardPowerDomain( hDevice, phPower );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesPowerGetProperties(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Power.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hPower, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerGetEnergyCounter
    __zedlllocal ze_result_t ZE_APICALL
    zesPowerGetEnergyCounter(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_energy_counter_t* pEnergy             ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
        )
    {
        auto pfnGetEnergyCounter = context.zesDdiTable.Power.pfnGetEnergyCounter;

        if( nullptr == pfnGetEnergyCounter )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pEnergy )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetEnergyCounter( hPower, pEnergy );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerGetLimits
    __zedlllocal ze_result_t ZE_APICALL
    zesPowerGetLimits(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_sustained_limit_t* pSustained,        ///< [in,out][optional] The sustained power limit. If this is null, the
                                                        ///< current sustained power limits will not be returned.
        zes_power_burst_limit_t* pBurst,                ///< [in,out][optional] The burst power limit. If this is null, the current
                                                        ///< peak power limits will not be returned.
        zes_power_peak_limit_t* pPeak                   ///< [in,out][optional] The peak power limit. If this is null, the peak
                                                        ///< power limits will not be returned.
        )
    {
        auto pfnGetLimits = context.zesDdiTable.Power.pfnGetLimits;

        if( nullptr == pfnGetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnGetLimits( hPower, pSustained, pBurst, pPeak );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerSetLimits
    __zedlllocal ze_result_t ZE_APICALL
    zesPowerSetLimits(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        const zes_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit. If this is null, no changes
                                                        ///< will be made to the sustained power limits.
        const zes_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit. If this is null, no changes will
                                                        ///< be made to the burst power limits.
        const zes_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit. If this is null, no changes will
                                                        ///< be made to the peak power limits.
        )
    {
        auto pfnSetLimits = context.zesDdiTable.Power.pfnSetLimits;

        if( nullptr == pfnSetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSetLimits( hPower, pSustained, pBurst, pPeak );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerGetEnergyThreshold
    __zedlllocal ze_result_t ZE_APICALL
    zesPowerGetEnergyThreshold(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_energy_threshold_t* pThreshold              ///< [in,out] Returns information about the energy threshold setting -
                                                        ///< enabled/energy threshold/process ID.
        )
    {
        auto pfnGetEnergyThreshold = context.zesDdiTable.Power.pfnGetEnergyThreshold;

        if( nullptr == pfnGetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pThreshold )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetEnergyThreshold( hPower, pThreshold );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerSetEnergyThreshold
    __zedlllocal ze_result_t ZE_APICALL
    zesPowerSetEnergyThreshold(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        double threshold                                ///< [in] The energy threshold to be set in joules.
        )
    {
        auto pfnSetEnergyThreshold = context.zesDdiTable.Power.pfnSetEnergyThreshold;

        if( nullptr == pfnSetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

        }

        return pfnSetEnergyThreshold( hPower, threshold );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumPsus
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumPsus(
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
        auto pfnEnumPsus = context.zesDdiTable.Device.pfnEnumPsus;

        if( nullptr == pfnEnumPsus )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumPsus( hDevice, pCount, phPsu );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPsuGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesPsuGetProperties(
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Psu.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPsu )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hPsu, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPsuGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesPsuGetState(
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
        )
    {
        auto pfnGetState = context.zesDdiTable.Psu.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPsu )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hPsu, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumRasErrorSets
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumRasErrorSets(
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
        auto pfnEnumRasErrorSets = context.zesDdiTable.Device.pfnEnumRasErrorSets;

        if( nullptr == pfnEnumRasErrorSets )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumRasErrorSets( hDevice, pCount, phRas );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesRasGetProperties(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Ras.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hRas, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasGetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesRasGetConfig(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_config_t* pConfig                       ///< [in,out] Will be populed with the current RAS configuration -
                                                        ///< thresholds used to trigger events
        )
    {
        auto pfnGetConfig = context.zesDdiTable.Ras.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hRas, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasSetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesRasSetConfig(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        const zes_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
        )
    {
        auto pfnSetConfig = context.zesDdiTable.Ras.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetConfig( hRas, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesRasGetState(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
        zes_ras_state_t* pState                         ///< [in,out] Breakdown of where errors have occurred
        )
    {
        auto pfnGetState = context.zesDdiTable.Ras.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hRas )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pState )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hRas, clear, pState );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumSchedulers
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumSchedulers(
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
        auto pfnEnumSchedulers = context.zesDdiTable.Device.pfnEnumSchedulers;

        if( nullptr == pfnEnumSchedulers )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumSchedulers( hDevice, pCount, phScheduler );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesSchedulerGetProperties(
        zes_sched_handle_t hScheduler,                  ///< [in] Handle for the component.
        zes_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Scheduler.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hScheduler, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerGetCurrentMode
    __zedlllocal ze_result_t ZE_APICALL
    zesSchedulerGetCurrentMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
        )
    {
        auto pfnGetCurrentMode = context.zesDdiTable.Scheduler.pfnGetCurrentMode;

        if( nullptr == pfnGetCurrentMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pMode )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetCurrentMode( hScheduler, pMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerGetTimeoutModeProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesSchedulerGetTimeoutModeProperties(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zes_sched_timeout_properties_t* pConfig         ///< [in,out] Will contain the current parameters for this mode.
        )
    {
        auto pfnGetTimeoutModeProperties = context.zesDdiTable.Scheduler.pfnGetTimeoutModeProperties;

        if( nullptr == pfnGetTimeoutModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerGetTimesliceModeProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesSchedulerGetTimesliceModeProperties(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zes_sched_timeslice_properties_t* pConfig       ///< [in,out] Will contain the current parameters for this mode.
        )
    {
        auto pfnGetTimesliceModeProperties = context.zesDdiTable.Scheduler.pfnGetTimesliceModeProperties;

        if( nullptr == pfnGetTimesliceModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerSetTimeoutMode
    __zedlllocal ze_result_t ZE_APICALL
    zesSchedulerSetTimeoutMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto pfnSetTimeoutMode = context.zesDdiTable.Scheduler.pfnSetTimeoutMode;

        if( nullptr == pfnSetTimeoutMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pNeedReload )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerSetTimesliceMode
    __zedlllocal ze_result_t ZE_APICALL
    zesSchedulerSetTimesliceMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto pfnSetTimesliceMode = context.zesDdiTable.Scheduler.pfnSetTimesliceMode;

        if( nullptr == pfnSetTimesliceMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

            if( nullptr == pNeedReload )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerSetExclusiveMode
    __zedlllocal ze_result_t ZE_APICALL
    zesSchedulerSetExclusiveMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto pfnSetExclusiveMode = context.zesDdiTable.Scheduler.pfnSetExclusiveMode;

        if( nullptr == pfnSetExclusiveMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pNeedReload )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetExclusiveMode( hScheduler, pNeedReload );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerSetComputeUnitDebugMode
    __zedlllocal ze_result_t ZE_APICALL
    zesSchedulerSetComputeUnitDebugMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto pfnSetComputeUnitDebugMode = context.zesDdiTable.Scheduler.pfnSetComputeUnitDebugMode;

        if( nullptr == pfnSetComputeUnitDebugMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hScheduler )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pNeedReload )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumStandbyDomains
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumStandbyDomains(
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
        auto pfnEnumStandbyDomains = context.zesDdiTable.Device.pfnEnumStandbyDomains;

        if( nullptr == pfnEnumStandbyDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumStandbyDomains( hDevice, pCount, phStandby );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesStandbyGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesStandbyGetProperties(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Standby.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hStandby )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hStandby, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesStandbyGetMode
    __zedlllocal ze_result_t ZE_APICALL
    zesStandbyGetMode(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
        )
    {
        auto pfnGetMode = context.zesDdiTable.Standby.pfnGetMode;

        if( nullptr == pfnGetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hStandby )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pMode )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetMode( hStandby, pMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesStandbySetMode
    __zedlllocal ze_result_t ZE_APICALL
    zesStandbySetMode(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t mode                   ///< [in] New standby mode.
        )
    {
        auto pfnSetMode = context.zesDdiTable.Standby.pfnSetMode;

        if( nullptr == pfnSetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hStandby )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( ZES_STANDBY_PROMO_MODE_NEVER < mode )
                return ZE_RESULT_ERROR_INVALID_ENUMERATION;

        }

        return pfnSetMode( hStandby, mode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumTemperatureSensors
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumTemperatureSensors(
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
        auto pfnEnumTemperatureSensors = context.zesDdiTable.Device.pfnEnumTemperatureSensors;

        if( nullptr == pfnEnumTemperatureSensors )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hDevice )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnEnumTemperatureSensors( hDevice, pCount, phTemperature );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesTemperatureGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesTemperatureGetProperties(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
        )
    {
        auto pfnGetProperties = context.zesDdiTable.Temperature.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pProperties )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetProperties( hTemperature, pProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesTemperatureGetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesTemperatureGetConfig(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
        )
    {
        auto pfnGetConfig = context.zesDdiTable.Temperature.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetConfig( hTemperature, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesTemperatureSetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesTemperatureSetConfig(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        const zes_temp_config_t* pConfig                ///< [in] New configuration.
        )
    {
        auto pfnSetConfig = context.zesDdiTable.Temperature.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pConfig )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetConfig( hTemperature, pConfig );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesTemperatureGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesTemperatureGetState(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                        ///< in degrees Celsius.
        )
    {
        auto pfnGetState = context.zesDdiTable.Temperature.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hTemperature )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pTemperature )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetState( hTemperature, pTemperature );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerGetLimitsExt
    __zedlllocal ze_result_t ZE_APICALL
    zesPowerGetLimitsExt(
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
        auto pfnGetLimitsExt = context.zesDdiTable.Power.pfnGetLimitsExt;

        if( nullptr == pfnGetLimitsExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnGetLimitsExt( hPower, pCount, pSustained );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerSetLimitsExt
    __zedlllocal ze_result_t ZE_APICALL
    zesPowerSetLimitsExt(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        uint32_t* pCount,                               ///< [in] Pointer to the number of power limit descriptors.
        zes_power_limit_ext_desc_t* pSustained          ///< [in][optional][range(0, *pCount)] Array of power limit descriptors.
        )
    {
        auto pfnSetLimitsExt = context.zesDdiTable.Power.pfnSetLimitsExt;

        if( nullptr == pfnSetLimitsExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            if( nullptr == hPower )
                return ZE_RESULT_ERROR_INVALID_NULL_HANDLE;

            if( nullptr == pCount )
                return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

        }

        return pfnSetLimitsExt( hPower, pCount, pSustained );
    }

} // namespace validation_layer

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_global_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Global;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnInit                                     = pDdiTable->pfnInit;
    pDdiTable->pfnInit                                   = validation_layer::zesInit;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Device;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesDeviceGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = validation_layer::zesDeviceGetState;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = validation_layer::zesDeviceReset;

    dditable.pfnProcessesGetState                        = pDdiTable->pfnProcessesGetState;
    pDdiTable->pfnProcessesGetState                      = validation_layer::zesDeviceProcessesGetState;

    dditable.pfnPciGetProperties                         = pDdiTable->pfnPciGetProperties;
    pDdiTable->pfnPciGetProperties                       = validation_layer::zesDevicePciGetProperties;

    dditable.pfnPciGetState                              = pDdiTable->pfnPciGetState;
    pDdiTable->pfnPciGetState                            = validation_layer::zesDevicePciGetState;

    dditable.pfnPciGetBars                               = pDdiTable->pfnPciGetBars;
    pDdiTable->pfnPciGetBars                             = validation_layer::zesDevicePciGetBars;

    dditable.pfnPciGetStats                              = pDdiTable->pfnPciGetStats;
    pDdiTable->pfnPciGetStats                            = validation_layer::zesDevicePciGetStats;

    dditable.pfnEnumDiagnosticTestSuites                 = pDdiTable->pfnEnumDiagnosticTestSuites;
    pDdiTable->pfnEnumDiagnosticTestSuites               = validation_layer::zesDeviceEnumDiagnosticTestSuites;

    dditable.pfnEnumEngineGroups                         = pDdiTable->pfnEnumEngineGroups;
    pDdiTable->pfnEnumEngineGroups                       = validation_layer::zesDeviceEnumEngineGroups;

    dditable.pfnEventRegister                            = pDdiTable->pfnEventRegister;
    pDdiTable->pfnEventRegister                          = validation_layer::zesDeviceEventRegister;

    dditable.pfnEnumFabricPorts                          = pDdiTable->pfnEnumFabricPorts;
    pDdiTable->pfnEnumFabricPorts                        = validation_layer::zesDeviceEnumFabricPorts;

    dditable.pfnEnumFans                                 = pDdiTable->pfnEnumFans;
    pDdiTable->pfnEnumFans                               = validation_layer::zesDeviceEnumFans;

    dditable.pfnEnumFirmwares                            = pDdiTable->pfnEnumFirmwares;
    pDdiTable->pfnEnumFirmwares                          = validation_layer::zesDeviceEnumFirmwares;

    dditable.pfnEnumFrequencyDomains                     = pDdiTable->pfnEnumFrequencyDomains;
    pDdiTable->pfnEnumFrequencyDomains                   = validation_layer::zesDeviceEnumFrequencyDomains;

    dditable.pfnEnumLeds                                 = pDdiTable->pfnEnumLeds;
    pDdiTable->pfnEnumLeds                               = validation_layer::zesDeviceEnumLeds;

    dditable.pfnEnumMemoryModules                        = pDdiTable->pfnEnumMemoryModules;
    pDdiTable->pfnEnumMemoryModules                      = validation_layer::zesDeviceEnumMemoryModules;

    dditable.pfnEnumPerformanceFactorDomains             = pDdiTable->pfnEnumPerformanceFactorDomains;
    pDdiTable->pfnEnumPerformanceFactorDomains           = validation_layer::zesDeviceEnumPerformanceFactorDomains;

    dditable.pfnEnumPowerDomains                         = pDdiTable->pfnEnumPowerDomains;
    pDdiTable->pfnEnumPowerDomains                       = validation_layer::zesDeviceEnumPowerDomains;

    dditable.pfnGetCardPowerDomain                       = pDdiTable->pfnGetCardPowerDomain;
    pDdiTable->pfnGetCardPowerDomain                     = validation_layer::zesDeviceGetCardPowerDomain;

    dditable.pfnEnumPsus                                 = pDdiTable->pfnEnumPsus;
    pDdiTable->pfnEnumPsus                               = validation_layer::zesDeviceEnumPsus;

    dditable.pfnEnumRasErrorSets                         = pDdiTable->pfnEnumRasErrorSets;
    pDdiTable->pfnEnumRasErrorSets                       = validation_layer::zesDeviceEnumRasErrorSets;

    dditable.pfnEnumSchedulers                           = pDdiTable->pfnEnumSchedulers;
    pDdiTable->pfnEnumSchedulers                         = validation_layer::zesDeviceEnumSchedulers;

    dditable.pfnEnumStandbyDomains                       = pDdiTable->pfnEnumStandbyDomains;
    pDdiTable->pfnEnumStandbyDomains                     = validation_layer::zesDeviceEnumStandbyDomains;

    dditable.pfnEnumTemperatureSensors                   = pDdiTable->pfnEnumTemperatureSensors;
    pDdiTable->pfnEnumTemperatureSensors                 = validation_layer::zesDeviceEnumTemperatureSensors;

    dditable.pfnEccAvailable                             = pDdiTable->pfnEccAvailable;
    pDdiTable->pfnEccAvailable                           = validation_layer::zesDeviceEccAvailable;

    dditable.pfnEccConfigurable                          = pDdiTable->pfnEccConfigurable;
    pDdiTable->pfnEccConfigurable                        = validation_layer::zesDeviceEccConfigurable;

    dditable.pfnGetEccState                              = pDdiTable->pfnGetEccState;
    pDdiTable->pfnGetEccState                            = validation_layer::zesDeviceGetEccState;

    dditable.pfnSetEccState                              = pDdiTable->pfnSetEccState;
    pDdiTable->pfnSetEccState                            = validation_layer::zesDeviceSetEccState;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = validation_layer::zesDeviceGet;

    dditable.pfnSetOverclockWaiver                       = pDdiTable->pfnSetOverclockWaiver;
    pDdiTable->pfnSetOverclockWaiver                     = validation_layer::zesDeviceSetOverclockWaiver;

    dditable.pfnGetOverclockDomains                      = pDdiTable->pfnGetOverclockDomains;
    pDdiTable->pfnGetOverclockDomains                    = validation_layer::zesDeviceGetOverclockDomains;

    dditable.pfnGetOverclockControls                     = pDdiTable->pfnGetOverclockControls;
    pDdiTable->pfnGetOverclockControls                   = validation_layer::zesDeviceGetOverclockControls;

    dditable.pfnResetOverclockSettings                   = pDdiTable->pfnResetOverclockSettings;
    pDdiTable->pfnResetOverclockSettings                 = validation_layer::zesDeviceResetOverclockSettings;

    dditable.pfnReadOverclockState                       = pDdiTable->pfnReadOverclockState;
    pDdiTable->pfnReadOverclockState                     = validation_layer::zesDeviceReadOverclockState;

    dditable.pfnEnumOverclockDomains                     = pDdiTable->pfnEnumOverclockDomains;
    pDdiTable->pfnEnumOverclockDomains                   = validation_layer::zesDeviceEnumOverclockDomains;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Driver table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetDriverProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_driver_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Driver;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnEventListen                              = pDdiTable->pfnEventListen;
    pDdiTable->pfnEventListen                            = validation_layer::zesDriverEventListen;

    dditable.pfnEventListenEx                            = pDdiTable->pfnEventListenEx;
    pDdiTable->pfnEventListenEx                          = validation_layer::zesDriverEventListenEx;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = validation_layer::zesDriverGet;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Diagnostics table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetDiagnosticsProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_diagnostics_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Diagnostics;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesDiagnosticsGetProperties;

    dditable.pfnGetTests                                 = pDdiTable->pfnGetTests;
    pDdiTable->pfnGetTests                               = validation_layer::zesDiagnosticsGetTests;

    dditable.pfnRunTests                                 = pDdiTable->pfnRunTests;
    pDdiTable->pfnRunTests                               = validation_layer::zesDiagnosticsRunTests;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Engine table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetEngineProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_engine_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Engine;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesEngineGetProperties;

    dditable.pfnGetActivity                              = pDdiTable->pfnGetActivity;
    pDdiTable->pfnGetActivity                            = validation_layer::zesEngineGetActivity;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FabricPort table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetFabricPortProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_fabric_port_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.FabricPort;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesFabricPortGetProperties;

    dditable.pfnGetLinkType                              = pDdiTable->pfnGetLinkType;
    pDdiTable->pfnGetLinkType                            = validation_layer::zesFabricPortGetLinkType;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = validation_layer::zesFabricPortGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = validation_layer::zesFabricPortSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = validation_layer::zesFabricPortGetState;

    dditable.pfnGetThroughput                            = pDdiTable->pfnGetThroughput;
    pDdiTable->pfnGetThroughput                          = validation_layer::zesFabricPortGetThroughput;

    dditable.pfnGetFabricErrorCounters                   = pDdiTable->pfnGetFabricErrorCounters;
    pDdiTable->pfnGetFabricErrorCounters                 = validation_layer::zesFabricPortGetFabricErrorCounters;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fan table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetFanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_fan_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Fan;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesFanGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = validation_layer::zesFanGetConfig;

    dditable.pfnSetDefaultMode                           = pDdiTable->pfnSetDefaultMode;
    pDdiTable->pfnSetDefaultMode                         = validation_layer::zesFanSetDefaultMode;

    dditable.pfnSetFixedSpeedMode                        = pDdiTable->pfnSetFixedSpeedMode;
    pDdiTable->pfnSetFixedSpeedMode                      = validation_layer::zesFanSetFixedSpeedMode;

    dditable.pfnSetSpeedTableMode                        = pDdiTable->pfnSetSpeedTableMode;
    pDdiTable->pfnSetSpeedTableMode                      = validation_layer::zesFanSetSpeedTableMode;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = validation_layer::zesFanGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Firmware table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetFirmwareProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_firmware_dditable_t* pDdiTable              ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Firmware;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesFirmwareGetProperties;

    dditable.pfnFlash                                    = pDdiTable->pfnFlash;
    pDdiTable->pfnFlash                                  = validation_layer::zesFirmwareFlash;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Frequency table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetFrequencyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_frequency_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Frequency;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesFrequencyGetProperties;

    dditable.pfnGetAvailableClocks                       = pDdiTable->pfnGetAvailableClocks;
    pDdiTable->pfnGetAvailableClocks                     = validation_layer::zesFrequencyGetAvailableClocks;

    dditable.pfnGetRange                                 = pDdiTable->pfnGetRange;
    pDdiTable->pfnGetRange                               = validation_layer::zesFrequencyGetRange;

    dditable.pfnSetRange                                 = pDdiTable->pfnSetRange;
    pDdiTable->pfnSetRange                               = validation_layer::zesFrequencySetRange;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = validation_layer::zesFrequencyGetState;

    dditable.pfnGetThrottleTime                          = pDdiTable->pfnGetThrottleTime;
    pDdiTable->pfnGetThrottleTime                        = validation_layer::zesFrequencyGetThrottleTime;

    dditable.pfnOcGetCapabilities                        = pDdiTable->pfnOcGetCapabilities;
    pDdiTable->pfnOcGetCapabilities                      = validation_layer::zesFrequencyOcGetCapabilities;

    dditable.pfnOcGetFrequencyTarget                     = pDdiTable->pfnOcGetFrequencyTarget;
    pDdiTable->pfnOcGetFrequencyTarget                   = validation_layer::zesFrequencyOcGetFrequencyTarget;

    dditable.pfnOcSetFrequencyTarget                     = pDdiTable->pfnOcSetFrequencyTarget;
    pDdiTable->pfnOcSetFrequencyTarget                   = validation_layer::zesFrequencyOcSetFrequencyTarget;

    dditable.pfnOcGetVoltageTarget                       = pDdiTable->pfnOcGetVoltageTarget;
    pDdiTable->pfnOcGetVoltageTarget                     = validation_layer::zesFrequencyOcGetVoltageTarget;

    dditable.pfnOcSetVoltageTarget                       = pDdiTable->pfnOcSetVoltageTarget;
    pDdiTable->pfnOcSetVoltageTarget                     = validation_layer::zesFrequencyOcSetVoltageTarget;

    dditable.pfnOcSetMode                                = pDdiTable->pfnOcSetMode;
    pDdiTable->pfnOcSetMode                              = validation_layer::zesFrequencyOcSetMode;

    dditable.pfnOcGetMode                                = pDdiTable->pfnOcGetMode;
    pDdiTable->pfnOcGetMode                              = validation_layer::zesFrequencyOcGetMode;

    dditable.pfnOcGetIccMax                              = pDdiTable->pfnOcGetIccMax;
    pDdiTable->pfnOcGetIccMax                            = validation_layer::zesFrequencyOcGetIccMax;

    dditable.pfnOcSetIccMax                              = pDdiTable->pfnOcSetIccMax;
    pDdiTable->pfnOcSetIccMax                            = validation_layer::zesFrequencyOcSetIccMax;

    dditable.pfnOcGetTjMax                               = pDdiTable->pfnOcGetTjMax;
    pDdiTable->pfnOcGetTjMax                             = validation_layer::zesFrequencyOcGetTjMax;

    dditable.pfnOcSetTjMax                               = pDdiTable->pfnOcSetTjMax;
    pDdiTable->pfnOcSetTjMax                             = validation_layer::zesFrequencyOcSetTjMax;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Led table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetLedProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_led_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Led;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesLedGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = validation_layer::zesLedGetState;

    dditable.pfnSetState                                 = pDdiTable->pfnSetState;
    pDdiTable->pfnSetState                               = validation_layer::zesLedSetState;

    dditable.pfnSetColor                                 = pDdiTable->pfnSetColor;
    pDdiTable->pfnSetColor                               = validation_layer::zesLedSetColor;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Memory table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetMemoryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_memory_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Memory;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesMemoryGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = validation_layer::zesMemoryGetState;

    dditable.pfnGetBandwidth                             = pDdiTable->pfnGetBandwidth;
    pDdiTable->pfnGetBandwidth                           = validation_layer::zesMemoryGetBandwidth;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Overclock table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetOverclockProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_overclock_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Overclock;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetDomainProperties                      = pDdiTable->pfnGetDomainProperties;
    pDdiTable->pfnGetDomainProperties                    = validation_layer::zesOverclockGetDomainProperties;

    dditable.pfnGetDomainVFProperties                    = pDdiTable->pfnGetDomainVFProperties;
    pDdiTable->pfnGetDomainVFProperties                  = validation_layer::zesOverclockGetDomainVFProperties;

    dditable.pfnGetDomainControlProperties               = pDdiTable->pfnGetDomainControlProperties;
    pDdiTable->pfnGetDomainControlProperties             = validation_layer::zesOverclockGetDomainControlProperties;

    dditable.pfnGetControlCurrentValue                   = pDdiTable->pfnGetControlCurrentValue;
    pDdiTable->pfnGetControlCurrentValue                 = validation_layer::zesOverclockGetControlCurrentValue;

    dditable.pfnGetControlPendingValue                   = pDdiTable->pfnGetControlPendingValue;
    pDdiTable->pfnGetControlPendingValue                 = validation_layer::zesOverclockGetControlPendingValue;

    dditable.pfnSetControlUserValue                      = pDdiTable->pfnSetControlUserValue;
    pDdiTable->pfnSetControlUserValue                    = validation_layer::zesOverclockSetControlUserValue;

    dditable.pfnGetControlState                          = pDdiTable->pfnGetControlState;
    pDdiTable->pfnGetControlState                        = validation_layer::zesOverclockGetControlState;

    dditable.pfnGetVFPointValues                         = pDdiTable->pfnGetVFPointValues;
    pDdiTable->pfnGetVFPointValues                       = validation_layer::zesOverclockGetVFPointValues;

    dditable.pfnSetVFPointValues                         = pDdiTable->pfnSetVFPointValues;
    pDdiTable->pfnSetVFPointValues                       = validation_layer::zesOverclockSetVFPointValues;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's PerformanceFactor table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetPerformanceFactorProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_performance_factor_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.PerformanceFactor;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesPerformanceFactorGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = validation_layer::zesPerformanceFactorGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = validation_layer::zesPerformanceFactorSetConfig;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Power table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetPowerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_power_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Power;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesPowerGetProperties;

    dditable.pfnGetEnergyCounter                         = pDdiTable->pfnGetEnergyCounter;
    pDdiTable->pfnGetEnergyCounter                       = validation_layer::zesPowerGetEnergyCounter;

    dditable.pfnGetLimits                                = pDdiTable->pfnGetLimits;
    pDdiTable->pfnGetLimits                              = validation_layer::zesPowerGetLimits;

    dditable.pfnSetLimits                                = pDdiTable->pfnSetLimits;
    pDdiTable->pfnSetLimits                              = validation_layer::zesPowerSetLimits;

    dditable.pfnGetEnergyThreshold                       = pDdiTable->pfnGetEnergyThreshold;
    pDdiTable->pfnGetEnergyThreshold                     = validation_layer::zesPowerGetEnergyThreshold;

    dditable.pfnSetEnergyThreshold                       = pDdiTable->pfnSetEnergyThreshold;
    pDdiTable->pfnSetEnergyThreshold                     = validation_layer::zesPowerSetEnergyThreshold;

    dditable.pfnGetLimitsExt                             = pDdiTable->pfnGetLimitsExt;
    pDdiTable->pfnGetLimitsExt                           = validation_layer::zesPowerGetLimitsExt;

    dditable.pfnSetLimitsExt                             = pDdiTable->pfnSetLimitsExt;
    pDdiTable->pfnSetLimitsExt                           = validation_layer::zesPowerSetLimitsExt;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Psu table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetPsuProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_psu_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Psu;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesPsuGetProperties;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = validation_layer::zesPsuGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Ras table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetRasProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_ras_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Ras;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesRasGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = validation_layer::zesRasGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = validation_layer::zesRasSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = validation_layer::zesRasGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Scheduler table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetSchedulerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_scheduler_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Scheduler;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesSchedulerGetProperties;

    dditable.pfnGetCurrentMode                           = pDdiTable->pfnGetCurrentMode;
    pDdiTable->pfnGetCurrentMode                         = validation_layer::zesSchedulerGetCurrentMode;

    dditable.pfnGetTimeoutModeProperties                 = pDdiTable->pfnGetTimeoutModeProperties;
    pDdiTable->pfnGetTimeoutModeProperties               = validation_layer::zesSchedulerGetTimeoutModeProperties;

    dditable.pfnGetTimesliceModeProperties               = pDdiTable->pfnGetTimesliceModeProperties;
    pDdiTable->pfnGetTimesliceModeProperties             = validation_layer::zesSchedulerGetTimesliceModeProperties;

    dditable.pfnSetTimeoutMode                           = pDdiTable->pfnSetTimeoutMode;
    pDdiTable->pfnSetTimeoutMode                         = validation_layer::zesSchedulerSetTimeoutMode;

    dditable.pfnSetTimesliceMode                         = pDdiTable->pfnSetTimesliceMode;
    pDdiTable->pfnSetTimesliceMode                       = validation_layer::zesSchedulerSetTimesliceMode;

    dditable.pfnSetExclusiveMode                         = pDdiTable->pfnSetExclusiveMode;
    pDdiTable->pfnSetExclusiveMode                       = validation_layer::zesSchedulerSetExclusiveMode;

    dditable.pfnSetComputeUnitDebugMode                  = pDdiTable->pfnSetComputeUnitDebugMode;
    pDdiTable->pfnSetComputeUnitDebugMode                = validation_layer::zesSchedulerSetComputeUnitDebugMode;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Standby table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetStandbyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_standby_dditable_t* pDdiTable               ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Standby;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesStandbyGetProperties;

    dditable.pfnGetMode                                  = pDdiTable->pfnGetMode;
    pDdiTable->pfnGetMode                                = validation_layer::zesStandbyGetMode;

    dditable.pfnSetMode                                  = pDdiTable->pfnSetMode;
    pDdiTable->pfnSetMode                                = validation_layer::zesStandbySetMode;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Temperature table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetTemperatureProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_temperature_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Temperature;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zesTemperatureGetProperties;

    dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
    pDdiTable->pfnGetConfig                              = validation_layer::zesTemperatureGetConfig;

    dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
    pDdiTable->pfnSetConfig                              = validation_layer::zesTemperatureSetConfig;

    dditable.pfnGetState                                 = pDdiTable->pfnGetState;
    pDdiTable->pfnGetState                               = validation_layer::zesTemperatureGetState;

    return result;
}

#if defined(__cplusplus)
};
#endif
