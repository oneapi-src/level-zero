/*
 *
 * Copyright (C) 2019-2022 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_nullddi.cpp
 *
 */
#include "ze_null.h"

namespace driver
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesInit
    __zedlllocal ze_result_t ZE_APICALL
    zesInit(
        zes_init_flags_t flags                          ///< [in] initialization flags.
                                                        ///< currently unused, must be 0 (default).
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnInit = context.zesDdiTable.Global.pfnInit;
        if( nullptr != pfnInit )
        {
            result = pfnInit( flags );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.zesDdiTable.Driver.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( pCount, phDrivers );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phDrivers ) && ( i < *pCount ); ++i )
                phDrivers[ i ] = reinterpret_cast<zes_driver_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDriverGetExtensionProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesDriverGetExtensionProperties(
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetExtensionProperties = context.zesDdiTable.Driver.pfnGetExtensionProperties;
        if( nullptr != pfnGetExtensionProperties )
        {
            result = pfnGetExtensionProperties( hDriver, pCount, pExtensionProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDriverGetExtensionFunctionAddress
    __zedlllocal ze_result_t ZE_APICALL
    zesDriverGetExtensionFunctionAddress(
        zes_driver_handle_t hDriver,                    ///< [in] handle of the driver instance
        const char* name,                               ///< [in] extension function name
        void** ppFunctionAddress                        ///< [out] pointer to function pointer
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetExtensionFunctionAddress = context.zesDdiTable.Driver.pfnGetExtensionFunctionAddress;
        if( nullptr != pfnGetExtensionFunctionAddress )
        {
            result = pfnGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGet = context.zesDdiTable.Device.pfnGet;
        if( nullptr != pfnGet )
        {
            result = pfnGet( hDriver, pCount, phDevices );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phDevices ) && ( i < *pCount ); ++i )
                phDevices[ i ] = reinterpret_cast<zes_device_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGetProperties(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.Device.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hDevice, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGetState(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.Device.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hDevice, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReset = context.zesDdiTable.Device.pfnReset;
        if( nullptr != pfnReset )
        {
            result = pfnReset( hDevice, force );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceResetExt
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceResetExt(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
        zes_reset_properties_t* pProperties             ///< [in] Device reset properties to apply
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnResetExt = context.zesDdiTable.Device.pfnResetExt;
        if( nullptr != pfnResetExt )
        {
            result = pfnResetExt( hDevice, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnProcessesGetState = context.zesDdiTable.Device.pfnProcessesGetState;
        if( nullptr != pfnProcessesGetState )
        {
            result = pfnProcessesGetState( hDevice, pCount, pProcesses );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesDevicePciGetProperties(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetProperties = context.zesDdiTable.Device.pfnPciGetProperties;
        if( nullptr != pfnPciGetProperties )
        {
            result = pfnPciGetProperties( hDevice, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesDevicePciGetState(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetState = context.zesDdiTable.Device.pfnPciGetState;
        if( nullptr != pfnPciGetState )
        {
            result = pfnPciGetState( hDevice, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetBars = context.zesDdiTable.Device.pfnPciGetBars;
        if( nullptr != pfnPciGetBars )
        {
            result = pfnPciGetBars( hDevice, pCount, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetStats
    __zedlllocal ze_result_t ZE_APICALL
    zesDevicePciGetStats(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnPciGetStats = context.zesDdiTable.Device.pfnPciGetStats;
        if( nullptr != pfnPciGetStats )
        {
            result = pfnPciGetStats( hDevice, pStats );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceSetOverclockWaiver
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceSetOverclockWaiver(
        zes_device_handle_t hDevice                     ///< [in] Sysman handle of the device.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetOverclockWaiver = context.zesDdiTable.Device.pfnSetOverclockWaiver;
        if( nullptr != pfnSetOverclockWaiver )
        {
            result = pfnSetOverclockWaiver( hDevice );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetOverclockDomains = context.zesDdiTable.Device.pfnGetOverclockDomains;
        if( nullptr != pfnGetOverclockDomains )
        {
            result = pfnGetOverclockDomains( hDevice, pOverclockDomains );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetOverclockControls = context.zesDdiTable.Device.pfnGetOverclockControls;
        if( nullptr != pfnGetOverclockControls )
        {
            result = pfnGetOverclockControls( hDevice, domainType, pAvailableControls );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnResetOverclockSettings = context.zesDdiTable.Device.pfnResetOverclockSettings;
        if( nullptr != pfnResetOverclockSettings )
        {
            result = pfnResetOverclockSettings( hDevice, onShippedState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnReadOverclockState = context.zesDdiTable.Device.pfnReadOverclockState;
        if( nullptr != pfnReadOverclockState )
        {
            result = pfnReadOverclockState( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumOverclockDomains = context.zesDdiTable.Device.pfnEnumOverclockDomains;
        if( nullptr != pfnEnumOverclockDomains )
        {
            result = pfnEnumOverclockDomains( hDevice, pCount, phDomainHandle );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phDomainHandle ) && ( i < *pCount ); ++i )
                phDomainHandle[ i ] = reinterpret_cast<zes_overclock_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesOverclockGetDomainProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesOverclockGetDomainProperties(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_properties_t* pDomainProperties   ///< [in,out] The overclock properties for the specified domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetDomainProperties = context.zesDdiTable.Overclock.pfnGetDomainProperties;
        if( nullptr != pfnGetDomainProperties )
        {
            result = pfnGetDomainProperties( hDomainHandle, pDomainProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesOverclockGetDomainVFProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesOverclockGetDomainVFProperties(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_vf_property_t* pVFProperties                ///< [in,out] The VF min,max,step for a specified domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetDomainVFProperties = context.zesDdiTable.Overclock.pfnGetDomainVFProperties;
        if( nullptr != pfnGetDomainVFProperties )
        {
            result = pfnGetDomainVFProperties( hDomainHandle, pVFProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetDomainControlProperties = context.zesDdiTable.Overclock.pfnGetDomainControlProperties;
        if( nullptr != pfnGetDomainControlProperties )
        {
            result = pfnGetDomainControlProperties( hDomainHandle, DomainControl, pControlProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetControlCurrentValue = context.zesDdiTable.Overclock.pfnGetControlCurrentValue;
        if( nullptr != pfnGetControlCurrentValue )
        {
            result = pfnGetControlCurrentValue( hDomainHandle, DomainControl, pValue );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetControlPendingValue = context.zesDdiTable.Overclock.pfnGetControlPendingValue;
        if( nullptr != pfnGetControlPendingValue )
        {
            result = pfnGetControlPendingValue( hDomainHandle, DomainControl, pValue );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetControlUserValue = context.zesDdiTable.Overclock.pfnSetControlUserValue;
        if( nullptr != pfnSetControlUserValue )
        {
            result = pfnSetControlUserValue( hDomainHandle, DomainControl, pValue, pPendingAction );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetControlState = context.zesDdiTable.Overclock.pfnGetControlState;
        if( nullptr != pfnGetControlState )
        {
            result = pfnGetControlState( hDomainHandle, DomainControl, pControlState, pPendingAction );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetVFPointValues = context.zesDdiTable.Overclock.pfnGetVFPointValues;
        if( nullptr != pfnGetVFPointValues )
        {
            result = pfnGetVFPointValues( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetVFPointValues = context.zesDdiTable.Overclock.pfnSetVFPointValues;
        if( nullptr != pfnSetVFPointValues )
        {
            result = pfnSetVFPointValues( hDomainHandle, VFType, PointIndex, PointValue );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumDiagnosticTestSuites = context.zesDdiTable.Device.pfnEnumDiagnosticTestSuites;
        if( nullptr != pfnEnumDiagnosticTestSuites )
        {
            result = pfnEnumDiagnosticTestSuites( hDevice, pCount, phDiagnostics );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phDiagnostics ) && ( i < *pCount ); ++i )
                phDiagnostics[ i ] = reinterpret_cast<zes_diag_handle_t>( context.get() );

        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.Diagnostics.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hDiagnostics, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
                                                        ///< individual tests sorted by increasing value of the `index` member of ::zes_diag_test_t.
                                                        ///< if count is less than the number of tests that are available, then the
                                                        ///< driver shall only retrieve that number of tests.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetTests = context.zesDdiTable.Diagnostics.pfnGetTests;
        if( nullptr != pfnGetTests )
        {
            result = pfnGetTests( hDiagnostics, pCount, pTests );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnRunTests = context.zesDdiTable.Diagnostics.pfnRunTests;
        if( nullptr != pfnRunTests )
        {
            result = pfnRunTests( hDiagnostics, startIndex, endIndex, pResult );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEccAvailable
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEccAvailable(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        ze_bool_t* pAvailable                           ///< [out] ECC functionality is available (true)/unavailable (false).
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEccAvailable = context.zesDdiTable.Device.pfnEccAvailable;
        if( nullptr != pfnEccAvailable )
        {
            result = pfnEccAvailable( hDevice, pAvailable );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEccConfigurable
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEccConfigurable(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        ze_bool_t* pConfigurable                        ///< [out] ECC can be enabled/disabled (true)/enabled/disabled (false).
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEccConfigurable = context.zesDdiTable.Device.pfnEccConfigurable;
        if( nullptr != pfnEccConfigurable )
        {
            result = pfnEccConfigurable( hDevice, pConfigurable );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetEccState
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGetEccState(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        zes_device_ecc_properties_t* pState             ///< [out] ECC state, pending state, and pending action for state change.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetEccState = context.zesDdiTable.Device.pfnGetEccState;
        if( nullptr != pfnGetEccState )
        {
            result = pfnGetEccState( hDevice, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetEccState = context.zesDdiTable.Device.pfnSetEccState;
        if( nullptr != pfnSetEccState )
        {
            result = pfnSetEccState( hDevice, newState, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumEngineGroups = context.zesDdiTable.Device.pfnEnumEngineGroups;
        if( nullptr != pfnEnumEngineGroups )
        {
            result = pfnEnumEngineGroups( hDevice, pCount, phEngine );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phEngine ) && ( i < *pCount ); ++i )
                phEngine[ i ] = reinterpret_cast<zes_engine_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesEngineGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesEngineGetProperties(
        zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
        zes_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.Engine.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hEngine, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetActivity = context.zesDdiTable.Engine.pfnGetActivity;
        if( nullptr != pfnGetActivity )
        {
            result = pfnGetActivity( hEngine, pStats );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEventRegister
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEventRegister(
        zes_device_handle_t hDevice,                    ///< [in] The device handle.
        zes_event_type_flags_t events                   ///< [in] List of events to listen to.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEventRegister = context.zesDdiTable.Device.pfnEventRegister;
        if( nullptr != pfnEventRegister )
        {
            result = pfnEventRegister( hDevice, events );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDriverEventListen
    __zedlllocal ze_result_t ZE_APICALL
    zesDriverEventListen(
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEventListen = context.zesDdiTable.Driver.pfnEventListen;
        if( nullptr != pfnEventListen )
        {
            result = pfnEventListen( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDriverEventListenEx
    __zedlllocal ze_result_t ZE_APICALL
    zesDriverEventListenEx(
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEventListenEx = context.zesDdiTable.Driver.pfnEventListenEx;
        if( nullptr != pfnEventListenEx )
        {
            result = pfnEventListenEx( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumFabricPorts = context.zesDdiTable.Device.pfnEnumFabricPorts;
        if( nullptr != pfnEnumFabricPorts )
        {
            result = pfnEnumFabricPorts( hDevice, pCount, phPort );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phPort ) && ( i < *pCount ); ++i )
                phPort[ i ] = reinterpret_cast<zes_fabric_port_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetProperties(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.FabricPort.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hPort, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetLinkType = context.zesDdiTable.FabricPort.pfnGetLinkType;
        if( nullptr != pfnGetLinkType )
        {
            result = pfnGetLinkType( hPort, pLinkType );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetConfig(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zesDdiTable.FabricPort.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hPort, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortSetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortSetConfig(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        const zes_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetConfig = context.zesDdiTable.FabricPort.pfnSetConfig;
        if( nullptr != pfnSetConfig )
        {
            result = pfnSetConfig( hPort, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetState(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.FabricPort.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hPort, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetThroughput
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetThroughput(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetThroughput = context.zesDdiTable.FabricPort.pfnGetThroughput;
        if( nullptr != pfnGetThroughput )
        {
            result = pfnGetThroughput( hPort, pThroughput );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetFabricErrorCounters
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetFabricErrorCounters(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_error_counters_t* pErrors       ///< [in,out] Will contain the Fabric port Error counters.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetFabricErrorCounters = context.zesDdiTable.FabricPort.pfnGetFabricErrorCounters;
        if( nullptr != pfnGetFabricErrorCounters )
        {
            result = pfnGetFabricErrorCounters( hPort, pErrors );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetMultiPortThroughput
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetMultiPortThroughput(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t numPorts,                              ///< [in] Number of ports enumerated in function ::zesDeviceEnumFabricPorts
        zes_fabric_port_handle_t* phPort,               ///< [in][range(0, numPorts)] array of fabric port handles provided by user
                                                        ///< to gather throughput values. 
        zes_fabric_port_throughput_t** pThroughput      ///< [out][range(0, numPorts)] array of fabric port throughput counters
                                                        ///< from multiple ports of type ::zes_fabric_port_throughput_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMultiPortThroughput = context.zesDdiTable.FabricPort.pfnGetMultiPortThroughput;
        if( nullptr != pfnGetMultiPortThroughput )
        {
            result = pfnGetMultiPortThroughput( hDevice, numPorts, phPort, pThroughput );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumFans = context.zesDdiTable.Device.pfnEnumFans;
        if( nullptr != pfnEnumFans )
        {
            result = pfnEnumFans( hDevice, pCount, phFan );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phFan ) && ( i < *pCount ); ++i )
                phFan[ i ] = reinterpret_cast<zes_fan_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesFanGetProperties(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.Fan.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hFan, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanGetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesFanGetConfig(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zesDdiTable.Fan.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hFan, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanSetDefaultMode
    __zedlllocal ze_result_t ZE_APICALL
    zesFanSetDefaultMode(
        zes_fan_handle_t hFan                           ///< [in] Handle for the component.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetDefaultMode = context.zesDdiTable.Fan.pfnSetDefaultMode;
        if( nullptr != pfnSetDefaultMode )
        {
            result = pfnSetDefaultMode( hFan );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanSetFixedSpeedMode
    __zedlllocal ze_result_t ZE_APICALL
    zesFanSetFixedSpeedMode(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        const zes_fan_speed_t* speed                    ///< [in] The fixed fan speed setting
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetFixedSpeedMode = context.zesDdiTable.Fan.pfnSetFixedSpeedMode;
        if( nullptr != pfnSetFixedSpeedMode )
        {
            result = pfnSetFixedSpeedMode( hFan, speed );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanSetSpeedTableMode
    __zedlllocal ze_result_t ZE_APICALL
    zesFanSetSpeedTableMode(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        const zes_fan_speed_table_t* speedTable         ///< [in] A table containing temperature/speed pairs.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetSpeedTableMode = context.zesDdiTable.Fan.pfnSetSpeedTableMode;
        if( nullptr != pfnSetSpeedTableMode )
        {
            result = pfnSetSpeedTableMode( hFan, speedTable );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.Fan.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hFan, units, pSpeed );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumFirmwares = context.zesDdiTable.Device.pfnEnumFirmwares;
        if( nullptr != pfnEnumFirmwares )
        {
            result = pfnEnumFirmwares( hDevice, pCount, phFirmware );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phFirmware ) && ( i < *pCount ); ++i )
                phFirmware[ i ] = reinterpret_cast<zes_firmware_handle_t>( context.get() );

        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.Firmware.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hFirmware, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnFlash = context.zesDdiTable.Firmware.pfnFlash;
        if( nullptr != pfnFlash )
        {
            result = pfnFlash( hFirmware, pImage, size );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFirmwareGetFlashProgress
    __zedlllocal ze_result_t ZE_APICALL
    zesFirmwareGetFlashProgress(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        uint32_t* pCompletionPercent                    ///< [in,out] Pointer to the Completion Percentage of Firmware Update
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetFlashProgress = context.zesDdiTable.Firmware.pfnGetFlashProgress;
        if( nullptr != pfnGetFlashProgress )
        {
            result = pfnGetFlashProgress( hFirmware, pCompletionPercent );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumFrequencyDomains = context.zesDdiTable.Device.pfnEnumFrequencyDomains;
        if( nullptr != pfnEnumFrequencyDomains )
        {
            result = pfnEnumFrequencyDomains( hDevice, pCount, phFrequency );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phFrequency ) && ( i < *pCount ); ++i )
                phFrequency[ i ] = reinterpret_cast<zes_freq_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyGetProperties(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.Frequency.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hFrequency, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetAvailableClocks = context.zesDdiTable.Frequency.pfnGetAvailableClocks;
        if( nullptr != pfnGetAvailableClocks )
        {
            result = pfnGetAvailableClocks( hFrequency, pCount, phFrequency );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetRange = context.zesDdiTable.Frequency.pfnGetRange;
        if( nullptr != pfnGetRange )
        {
            result = pfnGetRange( hFrequency, pLimits );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetRange = context.zesDdiTable.Frequency.pfnSetRange;
        if( nullptr != pfnSetRange )
        {
            result = pfnSetRange( hFrequency, pLimits );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyGetState(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.Frequency.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hFrequency, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetThrottleTime = context.zesDdiTable.Frequency.pfnGetThrottleTime;
        if( nullptr != pfnGetThrottleTime )
        {
            result = pfnGetThrottleTime( hFrequency, pThrottleTime );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetCapabilities
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcGetCapabilities(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcGetCapabilities = context.zesDdiTable.Frequency.pfnOcGetCapabilities;
        if( nullptr != pfnOcGetCapabilities )
        {
            result = pfnOcGetCapabilities( hFrequency, pOcCapabilities );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetFrequencyTarget
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcGetFrequencyTarget(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pCurrentOcFrequency                     ///< [out] Overclocking Frequency in MHz, if extended moded is supported,
                                                        ///< will returned in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                        ///< cannot be greater than the `maxOcFrequency` member of
                                                        ///< ::zes_oc_capabilities_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcGetFrequencyTarget = context.zesDdiTable.Frequency.pfnOcGetFrequencyTarget;
        if( nullptr != pfnOcGetFrequencyTarget )
        {
            result = pfnOcGetFrequencyTarget( hFrequency, pCurrentOcFrequency );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetFrequencyTarget
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcSetFrequencyTarget(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double CurrentOcFrequency                       ///< [in] Overclocking Frequency in MHz, if extended moded is supported, it
                                                        ///< could be set in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                        ///< cannot be greater than the `maxOcFrequency` member of
                                                        ///< ::zes_oc_capabilities_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcSetFrequencyTarget = context.zesDdiTable.Frequency.pfnOcSetFrequencyTarget;
        if( nullptr != pfnOcSetFrequencyTarget )
        {
            result = pfnOcSetFrequencyTarget( hFrequency, CurrentOcFrequency );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetVoltageTarget
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcGetVoltageTarget(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pCurrentVoltageTarget,                  ///< [out] Overclock voltage in Volts. This cannot be greater than the
                                                        ///< `maxOcVoltage` member of ::zes_oc_capabilities_t.
        double* pCurrentVoltageOffset                   ///< [out] This voltage offset is applied to all points on the
                                                        ///< voltage/frequency curve, including the new overclock voltageTarget.
                                                        ///< Valid range is between the `minOcVoltageOffset` and
                                                        ///< `maxOcVoltageOffset` members of ::zes_oc_capabilities_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcGetVoltageTarget = context.zesDdiTable.Frequency.pfnOcGetVoltageTarget;
        if( nullptr != pfnOcGetVoltageTarget )
        {
            result = pfnOcGetVoltageTarget( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetVoltageTarget
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcSetVoltageTarget(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double CurrentVoltageTarget,                    ///< [in] Overclock voltage in Volts. This cannot be greater than the
                                                        ///< `maxOcVoltage` member of ::zes_oc_capabilities_t.
        double CurrentVoltageOffset                     ///< [in] This voltage offset is applied to all points on the
                                                        ///< voltage/frequency curve, include the new overclock voltageTarget.
                                                        ///< Valid range is between the `minOcVoltageOffset` and
                                                        ///< `maxOcVoltageOffset` members of ::zes_oc_capabilities_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcSetVoltageTarget = context.zesDdiTable.Frequency.pfnOcSetVoltageTarget;
        if( nullptr != pfnOcSetVoltageTarget )
        {
            result = pfnOcSetVoltageTarget( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetMode
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcSetMode(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_mode_t CurrentOcMode                     ///< [in] Current Overclocking Mode ::zes_oc_mode_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcSetMode = context.zesDdiTable.Frequency.pfnOcSetMode;
        if( nullptr != pfnOcSetMode )
        {
            result = pfnOcSetMode( hFrequency, CurrentOcMode );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetMode
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcGetMode(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_mode_t* pCurrentOcMode                   ///< [out] Current Overclocking Mode ::zes_oc_mode_t.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcGetMode = context.zesDdiTable.Frequency.pfnOcGetMode;
        if( nullptr != pfnOcGetMode )
        {
            result = pfnOcGetMode( hFrequency, pCurrentOcMode );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcGetIccMax = context.zesDdiTable.Frequency.pfnOcGetIccMax;
        if( nullptr != pfnOcGetIccMax )
        {
            result = pfnOcGetIccMax( hFrequency, pOcIccMax );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetIccMax
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcSetIccMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcSetIccMax = context.zesDdiTable.Frequency.pfnOcSetIccMax;
        if( nullptr != pfnOcSetIccMax )
        {
            result = pfnOcSetIccMax( hFrequency, ocIccMax );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcGetTjMax = context.zesDdiTable.Frequency.pfnOcGetTjMax;
        if( nullptr != pfnOcGetTjMax )
        {
            result = pfnOcGetTjMax( hFrequency, pOcTjMax );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetTjMax
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcSetTjMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnOcSetTjMax = context.zesDdiTable.Frequency.pfnOcSetTjMax;
        if( nullptr != pfnOcSetTjMax )
        {
            result = pfnOcSetTjMax( hFrequency, ocTjMax );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumLeds = context.zesDdiTable.Device.pfnEnumLeds;
        if( nullptr != pfnEnumLeds )
        {
            result = pfnEnumLeds( hDevice, pCount, phLed );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phLed ) && ( i < *pCount ); ++i )
                phLed[ i ] = reinterpret_cast<zes_led_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesLedGetProperties(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.Led.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hLed, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesLedGetState(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.Led.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hLed, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedSetState
    __zedlllocal ze_result_t ZE_APICALL
    zesLedSetState(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        ze_bool_t enable                                ///< [in] Set to TRUE to turn the LED on, FALSE to turn off.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetState = context.zesDdiTable.Led.pfnSetState;
        if( nullptr != pfnSetState )
        {
            result = pfnSetState( hLed, enable );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedSetColor
    __zedlllocal ze_result_t ZE_APICALL
    zesLedSetColor(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        const zes_led_color_t* pColor                   ///< [in] New color of the LED.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetColor = context.zesDdiTable.Led.pfnSetColor;
        if( nullptr != pfnSetColor )
        {
            result = pfnSetColor( hLed, pColor );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumMemoryModules = context.zesDdiTable.Device.pfnEnumMemoryModules;
        if( nullptr != pfnEnumMemoryModules )
        {
            result = pfnEnumMemoryModules( hDevice, pCount, phMemory );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phMemory ) && ( i < *pCount ); ++i )
                phMemory[ i ] = reinterpret_cast<zes_mem_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesMemoryGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesMemoryGetProperties(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.Memory.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hMemory, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesMemoryGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesMemoryGetState(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.Memory.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hMemory, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetBandwidth = context.zesDdiTable.Memory.pfnGetBandwidth;
        if( nullptr != pfnGetBandwidth )
        {
            result = pfnGetBandwidth( hMemory, pBandwidth );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumPerformanceFactorDomains = context.zesDdiTable.Device.pfnEnumPerformanceFactorDomains;
        if( nullptr != pfnEnumPerformanceFactorDomains )
        {
            result = pfnEnumPerformanceFactorDomains( hDevice, pCount, phPerf );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phPerf ) && ( i < *pCount ); ++i )
                phPerf[ i ] = reinterpret_cast<zes_perf_handle_t>( context.get() );

        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.PerformanceFactor.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hPerf, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zesDdiTable.PerformanceFactor.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hPerf, pFactor );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPerformanceFactorSetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesPerformanceFactorSetConfig(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        double factor                                   ///< [in] The new Performance Factor.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetConfig = context.zesDdiTable.PerformanceFactor.pfnSetConfig;
        if( nullptr != pfnSetConfig )
        {
            result = pfnSetConfig( hPerf, factor );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumPowerDomains = context.zesDdiTable.Device.pfnEnumPowerDomains;
        if( nullptr != pfnEnumPowerDomains )
        {
            result = pfnEnumPowerDomains( hDevice, pCount, phPower );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phPower ) && ( i < *pCount ); ++i )
                phPower[ i ] = reinterpret_cast<zes_pwr_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetCardPowerDomain
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGetCardPowerDomain(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pwr_handle_t* phPower                       ///< [in,out] power domain handle for the entire PCIe card.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetCardPowerDomain = context.zesDdiTable.Device.pfnGetCardPowerDomain;
        if( nullptr != pfnGetCardPowerDomain )
        {
            result = pfnGetCardPowerDomain( hDevice, phPower );
        }
        else
        {
            // generic implementation
            *phPower = reinterpret_cast<zes_pwr_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesPowerGetProperties(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.Power.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hPower, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetEnergyCounter = context.zesDdiTable.Power.pfnGetEnergyCounter;
        if( nullptr != pfnGetEnergyCounter )
        {
            result = pfnGetEnergyCounter( hPower, pEnergy );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetLimits = context.zesDdiTable.Power.pfnGetLimits;
        if( nullptr != pfnGetLimits )
        {
            result = pfnGetLimits( hPower, pSustained, pBurst, pPeak );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetLimits = context.zesDdiTable.Power.pfnSetLimits;
        if( nullptr != pfnSetLimits )
        {
            result = pfnSetLimits( hPower, pSustained, pBurst, pPeak );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetEnergyThreshold = context.zesDdiTable.Power.pfnGetEnergyThreshold;
        if( nullptr != pfnGetEnergyThreshold )
        {
            result = pfnGetEnergyThreshold( hPower, pThreshold );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerSetEnergyThreshold
    __zedlllocal ze_result_t ZE_APICALL
    zesPowerSetEnergyThreshold(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        double threshold                                ///< [in] The energy threshold to be set in joules.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetEnergyThreshold = context.zesDdiTable.Power.pfnSetEnergyThreshold;
        if( nullptr != pfnSetEnergyThreshold )
        {
            result = pfnSetEnergyThreshold( hPower, threshold );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumPsus = context.zesDdiTable.Device.pfnEnumPsus;
        if( nullptr != pfnEnumPsus )
        {
            result = pfnEnumPsus( hDevice, pCount, phPsu );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phPsu ) && ( i < *pCount ); ++i )
                phPsu[ i ] = reinterpret_cast<zes_psu_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPsuGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesPsuGetProperties(
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.Psu.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hPsu, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPsuGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesPsuGetState(
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.Psu.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hPsu, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumRasErrorSets = context.zesDdiTable.Device.pfnEnumRasErrorSets;
        if( nullptr != pfnEnumRasErrorSets )
        {
            result = pfnEnumRasErrorSets( hDevice, pCount, phRas );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phRas ) && ( i < *pCount ); ++i )
                phRas[ i ] = reinterpret_cast<zes_ras_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesRasGetProperties(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.Ras.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hRas, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zesDdiTable.Ras.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hRas, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasSetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesRasSetConfig(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        const zes_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetConfig = context.zesDdiTable.Ras.pfnSetConfig;
        if( nullptr != pfnSetConfig )
        {
            result = pfnSetConfig( hRas, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.Ras.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hRas, clear, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumSchedulers = context.zesDdiTable.Device.pfnEnumSchedulers;
        if( nullptr != pfnEnumSchedulers )
        {
            result = pfnEnumSchedulers( hDevice, pCount, phScheduler );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phScheduler ) && ( i < *pCount ); ++i )
                phScheduler[ i ] = reinterpret_cast<zes_sched_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesSchedulerGetProperties(
        zes_sched_handle_t hScheduler,                  ///< [in] Handle for the component.
        zes_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.Scheduler.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hScheduler, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerGetCurrentMode
    __zedlllocal ze_result_t ZE_APICALL
    zesSchedulerGetCurrentMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetCurrentMode = context.zesDdiTable.Scheduler.pfnGetCurrentMode;
        if( nullptr != pfnGetCurrentMode )
        {
            result = pfnGetCurrentMode( hScheduler, pMode );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetTimeoutModeProperties = context.zesDdiTable.Scheduler.pfnGetTimeoutModeProperties;
        if( nullptr != pfnGetTimeoutModeProperties )
        {
            result = pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetTimesliceModeProperties = context.zesDdiTable.Scheduler.pfnGetTimesliceModeProperties;
        if( nullptr != pfnGetTimesliceModeProperties )
        {
            result = pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetTimeoutMode = context.zesDdiTable.Scheduler.pfnSetTimeoutMode;
        if( nullptr != pfnSetTimeoutMode )
        {
            result = pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetTimesliceMode = context.zesDdiTable.Scheduler.pfnSetTimesliceMode;
        if( nullptr != pfnSetTimesliceMode )
        {
            result = pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetExclusiveMode = context.zesDdiTable.Scheduler.pfnSetExclusiveMode;
        if( nullptr != pfnSetExclusiveMode )
        {
            result = pfnSetExclusiveMode( hScheduler, pNeedReload );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetComputeUnitDebugMode = context.zesDdiTable.Scheduler.pfnSetComputeUnitDebugMode;
        if( nullptr != pfnSetComputeUnitDebugMode )
        {
            result = pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumStandbyDomains = context.zesDdiTable.Device.pfnEnumStandbyDomains;
        if( nullptr != pfnEnumStandbyDomains )
        {
            result = pfnEnumStandbyDomains( hDevice, pCount, phStandby );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phStandby ) && ( i < *pCount ); ++i )
                phStandby[ i ] = reinterpret_cast<zes_standby_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesStandbyGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesStandbyGetProperties(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.Standby.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hStandby, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesStandbyGetMode
    __zedlllocal ze_result_t ZE_APICALL
    zesStandbyGetMode(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetMode = context.zesDdiTable.Standby.pfnGetMode;
        if( nullptr != pfnGetMode )
        {
            result = pfnGetMode( hStandby, pMode );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesStandbySetMode
    __zedlllocal ze_result_t ZE_APICALL
    zesStandbySetMode(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t mode                   ///< [in] New standby mode.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetMode = context.zesDdiTable.Standby.pfnSetMode;
        if( nullptr != pfnSetMode )
        {
            result = pfnSetMode( hStandby, mode );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnEnumTemperatureSensors = context.zesDdiTable.Device.pfnEnumTemperatureSensors;
        if( nullptr != pfnEnumTemperatureSensors )
        {
            result = pfnEnumTemperatureSensors( hDevice, pCount, phTemperature );
        }
        else
        {
            // generic implementation
            for( size_t i = 0; ( nullptr != phTemperature ) && ( i < *pCount ); ++i )
                phTemperature[ i ] = reinterpret_cast<zes_temp_handle_t>( context.get() );

        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesTemperatureGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesTemperatureGetProperties(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetProperties = context.zesDdiTable.Temperature.pfnGetProperties;
        if( nullptr != pfnGetProperties )
        {
            result = pfnGetProperties( hTemperature, pProperties );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesTemperatureGetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesTemperatureGetConfig(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetConfig = context.zesDdiTable.Temperature.pfnGetConfig;
        if( nullptr != pfnGetConfig )
        {
            result = pfnGetConfig( hTemperature, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesTemperatureSetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesTemperatureSetConfig(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        const zes_temp_config_t* pConfig                ///< [in] New configuration.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetConfig = context.zesDdiTable.Temperature.pfnSetConfig;
        if( nullptr != pfnSetConfig )
        {
            result = pfnSetConfig( hTemperature, pConfig );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetState = context.zesDdiTable.Temperature.pfnGetState;
        if( nullptr != pfnGetState )
        {
            result = pfnGetState( hTemperature, pTemperature );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetLimitsExt = context.zesDdiTable.Power.pfnGetLimitsExt;
        if( nullptr != pfnGetLimitsExt )
        {
            result = pfnGetLimitsExt( hPower, pCount, pSustained );
        }
        else
        {
            // generic implementation
        }

        return result;
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnSetLimitsExt = context.zesDdiTable.Power.pfnSetLimitsExt;
        if( nullptr != pfnSetLimitsExt )
        {
            result = pfnSetLimitsExt( hPower, pCount, pSustained );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesEngineGetActivityExt
    __zedlllocal ze_result_t ZE_APICALL
    zesEngineGetActivityExt(
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetActivityExt = context.zesDdiTable.Engine.pfnGetActivityExt;
        if( nullptr != pfnGetActivityExt )
        {
            result = pfnGetActivityExt( hEngine, pCount, pStats );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasGetStateExp
    __zedlllocal ze_result_t ZE_APICALL
    zesRasGetStateExp(
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnGetStateExp = context.zesDdiTable.RasExp.pfnGetStateExp;
        if( nullptr != pfnGetStateExp )
        {
            result = pfnGetStateExp( hRas, pCount, pState );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasClearStateExp
    __zedlllocal ze_result_t ZE_APICALL
    zesRasClearStateExp(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_error_category_exp_t category           ///< [in] category for which error counter is to be cleared.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // if the driver has created a custom function, then call it instead of using the generic path
        auto pfnClearStateExp = context.zesDdiTable.RasExp.pfnClearStateExp;
        if( nullptr != pfnClearStateExp )
        {
            result = pfnClearStateExp( hRas, category );
        }
        else
        {
            // generic implementation
        }

        return result;
    }

} // namespace driver

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnInit                                   = driver::zesInit;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesDeviceGetProperties;

    pDdiTable->pfnGetState                               = driver::zesDeviceGetState;

    pDdiTable->pfnReset                                  = driver::zesDeviceReset;

    pDdiTable->pfnProcessesGetState                      = driver::zesDeviceProcessesGetState;

    pDdiTable->pfnPciGetProperties                       = driver::zesDevicePciGetProperties;

    pDdiTable->pfnPciGetState                            = driver::zesDevicePciGetState;

    pDdiTable->pfnPciGetBars                             = driver::zesDevicePciGetBars;

    pDdiTable->pfnPciGetStats                            = driver::zesDevicePciGetStats;

    pDdiTable->pfnEnumDiagnosticTestSuites               = driver::zesDeviceEnumDiagnosticTestSuites;

    pDdiTable->pfnEnumEngineGroups                       = driver::zesDeviceEnumEngineGroups;

    pDdiTable->pfnEventRegister                          = driver::zesDeviceEventRegister;

    pDdiTable->pfnEnumFabricPorts                        = driver::zesDeviceEnumFabricPorts;

    pDdiTable->pfnEnumFans                               = driver::zesDeviceEnumFans;

    pDdiTable->pfnEnumFirmwares                          = driver::zesDeviceEnumFirmwares;

    pDdiTable->pfnEnumFrequencyDomains                   = driver::zesDeviceEnumFrequencyDomains;

    pDdiTable->pfnEnumLeds                               = driver::zesDeviceEnumLeds;

    pDdiTable->pfnEnumMemoryModules                      = driver::zesDeviceEnumMemoryModules;

    pDdiTable->pfnEnumPerformanceFactorDomains           = driver::zesDeviceEnumPerformanceFactorDomains;

    pDdiTable->pfnEnumPowerDomains                       = driver::zesDeviceEnumPowerDomains;

    pDdiTable->pfnGetCardPowerDomain                     = driver::zesDeviceGetCardPowerDomain;

    pDdiTable->pfnEnumPsus                               = driver::zesDeviceEnumPsus;

    pDdiTable->pfnEnumRasErrorSets                       = driver::zesDeviceEnumRasErrorSets;

    pDdiTable->pfnEnumSchedulers                         = driver::zesDeviceEnumSchedulers;

    pDdiTable->pfnEnumStandbyDomains                     = driver::zesDeviceEnumStandbyDomains;

    pDdiTable->pfnEnumTemperatureSensors                 = driver::zesDeviceEnumTemperatureSensors;

    pDdiTable->pfnEccAvailable                           = driver::zesDeviceEccAvailable;

    pDdiTable->pfnEccConfigurable                        = driver::zesDeviceEccConfigurable;

    pDdiTable->pfnGetEccState                            = driver::zesDeviceGetEccState;

    pDdiTable->pfnSetEccState                            = driver::zesDeviceSetEccState;

    pDdiTable->pfnGet                                    = driver::zesDeviceGet;

    pDdiTable->pfnSetOverclockWaiver                     = driver::zesDeviceSetOverclockWaiver;

    pDdiTable->pfnGetOverclockDomains                    = driver::zesDeviceGetOverclockDomains;

    pDdiTable->pfnGetOverclockControls                   = driver::zesDeviceGetOverclockControls;

    pDdiTable->pfnResetOverclockSettings                 = driver::zesDeviceResetOverclockSettings;

    pDdiTable->pfnReadOverclockState                     = driver::zesDeviceReadOverclockState;

    pDdiTable->pfnEnumOverclockDomains                   = driver::zesDeviceEnumOverclockDomains;

    pDdiTable->pfnResetExt                               = driver::zesDeviceResetExt;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnEventListen                            = driver::zesDriverEventListen;

    pDdiTable->pfnEventListenEx                          = driver::zesDriverEventListenEx;

    pDdiTable->pfnGet                                    = driver::zesDriverGet;

    pDdiTable->pfnGetExtensionProperties                 = driver::zesDriverGetExtensionProperties;

    pDdiTable->pfnGetExtensionFunctionAddress            = driver::zesDriverGetExtensionFunctionAddress;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesDiagnosticsGetProperties;

    pDdiTable->pfnGetTests                               = driver::zesDiagnosticsGetTests;

    pDdiTable->pfnRunTests                               = driver::zesDiagnosticsRunTests;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesEngineGetProperties;

    pDdiTable->pfnGetActivity                            = driver::zesEngineGetActivity;

    pDdiTable->pfnGetActivityExt                         = driver::zesEngineGetActivityExt;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesFabricPortGetProperties;

    pDdiTable->pfnGetLinkType                            = driver::zesFabricPortGetLinkType;

    pDdiTable->pfnGetConfig                              = driver::zesFabricPortGetConfig;

    pDdiTable->pfnSetConfig                              = driver::zesFabricPortSetConfig;

    pDdiTable->pfnGetState                               = driver::zesFabricPortGetState;

    pDdiTable->pfnGetThroughput                          = driver::zesFabricPortGetThroughput;

    pDdiTable->pfnGetFabricErrorCounters                 = driver::zesFabricPortGetFabricErrorCounters;

    pDdiTable->pfnGetMultiPortThroughput                 = driver::zesFabricPortGetMultiPortThroughput;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesFanGetProperties;

    pDdiTable->pfnGetConfig                              = driver::zesFanGetConfig;

    pDdiTable->pfnSetDefaultMode                         = driver::zesFanSetDefaultMode;

    pDdiTable->pfnSetFixedSpeedMode                      = driver::zesFanSetFixedSpeedMode;

    pDdiTable->pfnSetSpeedTableMode                      = driver::zesFanSetSpeedTableMode;

    pDdiTable->pfnGetState                               = driver::zesFanGetState;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesFirmwareGetProperties;

    pDdiTable->pfnFlash                                  = driver::zesFirmwareFlash;

    pDdiTable->pfnGetFlashProgress                       = driver::zesFirmwareGetFlashProgress;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesFrequencyGetProperties;

    pDdiTable->pfnGetAvailableClocks                     = driver::zesFrequencyGetAvailableClocks;

    pDdiTable->pfnGetRange                               = driver::zesFrequencyGetRange;

    pDdiTable->pfnSetRange                               = driver::zesFrequencySetRange;

    pDdiTable->pfnGetState                               = driver::zesFrequencyGetState;

    pDdiTable->pfnGetThrottleTime                        = driver::zesFrequencyGetThrottleTime;

    pDdiTable->pfnOcGetCapabilities                      = driver::zesFrequencyOcGetCapabilities;

    pDdiTable->pfnOcGetFrequencyTarget                   = driver::zesFrequencyOcGetFrequencyTarget;

    pDdiTable->pfnOcSetFrequencyTarget                   = driver::zesFrequencyOcSetFrequencyTarget;

    pDdiTable->pfnOcGetVoltageTarget                     = driver::zesFrequencyOcGetVoltageTarget;

    pDdiTable->pfnOcSetVoltageTarget                     = driver::zesFrequencyOcSetVoltageTarget;

    pDdiTable->pfnOcSetMode                              = driver::zesFrequencyOcSetMode;

    pDdiTable->pfnOcGetMode                              = driver::zesFrequencyOcGetMode;

    pDdiTable->pfnOcGetIccMax                            = driver::zesFrequencyOcGetIccMax;

    pDdiTable->pfnOcSetIccMax                            = driver::zesFrequencyOcSetIccMax;

    pDdiTable->pfnOcGetTjMax                             = driver::zesFrequencyOcGetTjMax;

    pDdiTable->pfnOcSetTjMax                             = driver::zesFrequencyOcSetTjMax;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesLedGetProperties;

    pDdiTable->pfnGetState                               = driver::zesLedGetState;

    pDdiTable->pfnSetState                               = driver::zesLedSetState;

    pDdiTable->pfnSetColor                               = driver::zesLedSetColor;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesMemoryGetProperties;

    pDdiTable->pfnGetState                               = driver::zesMemoryGetState;

    pDdiTable->pfnGetBandwidth                           = driver::zesMemoryGetBandwidth;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetDomainProperties                    = driver::zesOverclockGetDomainProperties;

    pDdiTable->pfnGetDomainVFProperties                  = driver::zesOverclockGetDomainVFProperties;

    pDdiTable->pfnGetDomainControlProperties             = driver::zesOverclockGetDomainControlProperties;

    pDdiTable->pfnGetControlCurrentValue                 = driver::zesOverclockGetControlCurrentValue;

    pDdiTable->pfnGetControlPendingValue                 = driver::zesOverclockGetControlPendingValue;

    pDdiTable->pfnSetControlUserValue                    = driver::zesOverclockSetControlUserValue;

    pDdiTable->pfnGetControlState                        = driver::zesOverclockGetControlState;

    pDdiTable->pfnGetVFPointValues                       = driver::zesOverclockGetVFPointValues;

    pDdiTable->pfnSetVFPointValues                       = driver::zesOverclockSetVFPointValues;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesPerformanceFactorGetProperties;

    pDdiTable->pfnGetConfig                              = driver::zesPerformanceFactorGetConfig;

    pDdiTable->pfnSetConfig                              = driver::zesPerformanceFactorSetConfig;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesPowerGetProperties;

    pDdiTable->pfnGetEnergyCounter                       = driver::zesPowerGetEnergyCounter;

    pDdiTable->pfnGetLimits                              = driver::zesPowerGetLimits;

    pDdiTable->pfnSetLimits                              = driver::zesPowerSetLimits;

    pDdiTable->pfnGetEnergyThreshold                     = driver::zesPowerGetEnergyThreshold;

    pDdiTable->pfnSetEnergyThreshold                     = driver::zesPowerSetEnergyThreshold;

    pDdiTable->pfnGetLimitsExt                           = driver::zesPowerGetLimitsExt;

    pDdiTable->pfnSetLimitsExt                           = driver::zesPowerSetLimitsExt;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesPsuGetProperties;

    pDdiTable->pfnGetState                               = driver::zesPsuGetState;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesRasGetProperties;

    pDdiTable->pfnGetConfig                              = driver::zesRasGetConfig;

    pDdiTable->pfnSetConfig                              = driver::zesRasSetConfig;

    pDdiTable->pfnGetState                               = driver::zesRasGetState;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's RasExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetRasExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_ras_exp_dditable_t* pDdiTable               ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetStateExp                            = driver::zesRasGetStateExp;

    pDdiTable->pfnClearStateExp                          = driver::zesRasClearStateExp;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesSchedulerGetProperties;

    pDdiTable->pfnGetCurrentMode                         = driver::zesSchedulerGetCurrentMode;

    pDdiTable->pfnGetTimeoutModeProperties               = driver::zesSchedulerGetTimeoutModeProperties;

    pDdiTable->pfnGetTimesliceModeProperties             = driver::zesSchedulerGetTimesliceModeProperties;

    pDdiTable->pfnSetTimeoutMode                         = driver::zesSchedulerSetTimeoutMode;

    pDdiTable->pfnSetTimesliceMode                       = driver::zesSchedulerSetTimesliceMode;

    pDdiTable->pfnSetExclusiveMode                       = driver::zesSchedulerSetExclusiveMode;

    pDdiTable->pfnSetComputeUnitDebugMode                = driver::zesSchedulerSetComputeUnitDebugMode;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesStandbyGetProperties;

    pDdiTable->pfnGetMode                                = driver::zesStandbyGetMode;

    pDdiTable->pfnSetMode                                = driver::zesStandbySetMode;

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
    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( driver::context.version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    pDdiTable->pfnGetProperties                          = driver::zesTemperatureGetProperties;

    pDdiTable->pfnGetConfig                              = driver::zesTemperatureGetConfig;

    pDdiTable->pfnSetConfig                              = driver::zesTemperatureSetConfig;

    pDdiTable->pfnGetState                               = driver::zesTemperatureGetState;

    return result;
}

#if defined(__cplusplus)
};
#endif
