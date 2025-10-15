/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_ldrddi_driver_ddi.cpp
 *
 */
#include "ze_loader_internal.h"

namespace loader_driver_ddi
{
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_8) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Driver == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetExtensionProperties = dditable->Driver->pfnGetExtensionProperties;
        if( nullptr == pfnGetExtensionProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetExtensionProperties( hDriver, pCount, pExtensionProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_8) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Driver == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetExtensionFunctionAddress = dditable->Driver->pfnGetExtensionFunctionAddress;
        if( nullptr == pfnGetExtensionFunctionAddress ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGet = dditable->Device->pfnGet;
        if( nullptr == pfnGet ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGet( hDriver, pCount, phDevices );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Device->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hDevice, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetState = dditable->Device->pfnGetState;
        if( nullptr == pfnGetState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetState( hDevice, pState );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnReset = dditable->Device->pfnReset;
        if( nullptr == pfnReset ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnReset( hDevice, force );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnResetExt = dditable->Device->pfnResetExt;
        if( nullptr == pfnResetExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnResetExt( hDevice, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnProcessesGetState = dditable->Device->pfnProcessesGetState;
        if( nullptr == pfnProcessesGetState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnProcessesGetState( hDevice, pCount, pProcesses );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnPciGetProperties = dditable->Device->pfnPciGetProperties;
        if( nullptr == pfnPciGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnPciGetProperties( hDevice, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnPciGetState = dditable->Device->pfnPciGetState;
        if( nullptr == pfnPciGetState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnPciGetState( hDevice, pState );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnPciGetBars = dditable->Device->pfnPciGetBars;
        if( nullptr == pfnPciGetBars ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnPciGetBars( hDevice, pCount, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnPciGetStats = dditable->Device->pfnPciGetStats;
        if( nullptr == pfnPciGetStats ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnPciGetStats( hDevice, pStats );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetOverclockWaiver = dditable->Device->pfnSetOverclockWaiver;
        if( nullptr == pfnSetOverclockWaiver ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetOverclockWaiver( hDevice );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetOverclockDomains = dditable->Device->pfnGetOverclockDomains;
        if( nullptr == pfnGetOverclockDomains ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetOverclockDomains( hDevice, pOverclockDomains );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetOverclockControls = dditable->Device->pfnGetOverclockControls;
        if( nullptr == pfnGetOverclockControls ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetOverclockControls( hDevice, domainType, pAvailableControls );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnResetOverclockSettings = dditable->Device->pfnResetOverclockSettings;
        if( nullptr == pfnResetOverclockSettings ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnResetOverclockSettings( hDevice, onShippedState );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnReadOverclockState = dditable->Device->pfnReadOverclockState;
        if( nullptr == pfnReadOverclockState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnReadOverclockState( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumOverclockDomains = dditable->Device->pfnEnumOverclockDomains;
        if( nullptr == pfnEnumOverclockDomains ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumOverclockDomains( hDevice, pCount, phDomainHandle );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDomainHandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Overclock == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetDomainProperties = dditable->Overclock->pfnGetDomainProperties;
        if( nullptr == pfnGetDomainProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetDomainProperties( hDomainHandle, pDomainProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDomainHandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Overclock == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetDomainVFProperties = dditable->Overclock->pfnGetDomainVFProperties;
        if( nullptr == pfnGetDomainVFProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetDomainVFProperties( hDomainHandle, pVFProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDomainHandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Overclock == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetDomainControlProperties = dditable->Overclock->pfnGetDomainControlProperties;
        if( nullptr == pfnGetDomainControlProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetDomainControlProperties( hDomainHandle, DomainControl, pControlProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDomainHandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Overclock == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetControlCurrentValue = dditable->Overclock->pfnGetControlCurrentValue;
        if( nullptr == pfnGetControlCurrentValue ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetControlCurrentValue( hDomainHandle, DomainControl, pValue );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDomainHandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Overclock == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetControlPendingValue = dditable->Overclock->pfnGetControlPendingValue;
        if( nullptr == pfnGetControlPendingValue ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetControlPendingValue( hDomainHandle, DomainControl, pValue );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDomainHandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Overclock == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetControlUserValue = dditable->Overclock->pfnSetControlUserValue;
        if( nullptr == pfnSetControlUserValue ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetControlUserValue( hDomainHandle, DomainControl, pValue, pPendingAction );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDomainHandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Overclock == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetControlState = dditable->Overclock->pfnGetControlState;
        if( nullptr == pfnGetControlState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetControlState( hDomainHandle, DomainControl, pControlState, pPendingAction );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDomainHandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Overclock == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetVFPointValues = dditable->Overclock->pfnGetVFPointValues;
        if( nullptr == pfnGetVFPointValues ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetVFPointValues( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDomainHandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_5) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Overclock == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetVFPointValues = dditable->Overclock->pfnSetVFPointValues;
        if( nullptr == pfnSetVFPointValues ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetVFPointValues( hDomainHandle, VFType, PointIndex, PointValue );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumDiagnosticTestSuites = dditable->Device->pfnEnumDiagnosticTestSuites;
        if( nullptr == pfnEnumDiagnosticTestSuites ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumDiagnosticTestSuites( hDevice, pCount, phDiagnostics );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDiagnostics )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Diagnostics == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Diagnostics->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hDiagnostics, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDiagnostics )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Diagnostics == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetTests = dditable->Diagnostics->pfnGetTests;
        if( nullptr == pfnGetTests ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetTests( hDiagnostics, pCount, pTests );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDiagnostics )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Diagnostics == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnRunTests = dditable->Diagnostics->pfnRunTests;
        if( nullptr == pfnRunTests ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnRunTests( hDiagnostics, startIndex, endIndex, pResult );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_4) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEccAvailable = dditable->Device->pfnEccAvailable;
        if( nullptr == pfnEccAvailable ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEccAvailable( hDevice, pAvailable );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_4) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEccConfigurable = dditable->Device->pfnEccConfigurable;
        if( nullptr == pfnEccConfigurable ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEccConfigurable( hDevice, pConfigurable );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_4) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetEccState = dditable->Device->pfnGetEccState;
        if( nullptr == pfnGetEccState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetEccState( hDevice, pState );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_4) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetEccState = dditable->Device->pfnSetEccState;
        if( nullptr == pfnSetEccState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetEccState( hDevice, newState, pState );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumEngineGroups = dditable->Device->pfnEnumEngineGroups;
        if( nullptr == pfnEnumEngineGroups ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumEngineGroups( hDevice, pCount, phEngine );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEngine )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Engine == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Engine->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hEngine, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEngine )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Engine == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetActivity = dditable->Engine->pfnGetActivity;
        if( nullptr == pfnGetActivity ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetActivity( hEngine, pStats );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEventRegister = dditable->Device->pfnEventRegister;
        if( nullptr == pfnEventRegister ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEventRegister( hDevice, events );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Driver == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEventListen = dditable->Driver->pfnEventListen;
        if( nullptr == pfnEventListen ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEventListen( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_1) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Driver == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEventListenEx = dditable->Driver->pfnEventListenEx;
        if( nullptr == pfnEventListenEx ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEventListenEx( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumFabricPorts = dditable->Device->pfnEnumFabricPorts;
        if( nullptr == pfnEnumFabricPorts ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumFabricPorts( hDevice, pCount, phPort );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPort )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FabricPort == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->FabricPort->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hPort, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPort )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FabricPort == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetLinkType = dditable->FabricPort->pfnGetLinkType;
        if( nullptr == pfnGetLinkType ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetLinkType( hPort, pLinkType );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPort )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FabricPort == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetConfig = dditable->FabricPort->pfnGetConfig;
        if( nullptr == pfnGetConfig ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetConfig( hPort, pConfig );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPort )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FabricPort == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetConfig = dditable->FabricPort->pfnSetConfig;
        if( nullptr == pfnSetConfig ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetConfig( hPort, pConfig );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPort )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FabricPort == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetState = dditable->FabricPort->pfnGetState;
        if( nullptr == pfnGetState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetState( hPort, pState );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPort )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FabricPort == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetThroughput = dditable->FabricPort->pfnGetThroughput;
        if( nullptr == pfnGetThroughput ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetThroughput( hPort, pThroughput );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPort )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FabricPort == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetFabricErrorCounters = dditable->FabricPort->pfnGetFabricErrorCounters;
        if( nullptr == pfnGetFabricErrorCounters ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetFabricErrorCounters( hPort, pErrors );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FabricPort == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetMultiPortThroughput = dditable->FabricPort->pfnGetMultiPortThroughput;
        if( nullptr == pfnGetMultiPortThroughput ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetMultiPortThroughput( hDevice, numPorts, phPort, pThroughput );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumFans = dditable->Device->pfnEnumFans;
        if( nullptr == pfnEnumFans ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumFans( hDevice, pCount, phFan );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFan )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Fan == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Fan->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hFan, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFan )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Fan == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetConfig = dditable->Fan->pfnGetConfig;
        if( nullptr == pfnGetConfig ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetConfig( hFan, pConfig );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFan )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Fan == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetDefaultMode = dditable->Fan->pfnSetDefaultMode;
        if( nullptr == pfnSetDefaultMode ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetDefaultMode( hFan );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFan )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Fan == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetFixedSpeedMode = dditable->Fan->pfnSetFixedSpeedMode;
        if( nullptr == pfnSetFixedSpeedMode ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetFixedSpeedMode( hFan, speed );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFan )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Fan == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetSpeedTableMode = dditable->Fan->pfnSetSpeedTableMode;
        if( nullptr == pfnSetSpeedTableMode ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetSpeedTableMode( hFan, speedTable );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFan )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Fan == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetState = dditable->Fan->pfnGetState;
        if( nullptr == pfnGetState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetState( hFan, units, pSpeed );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumFirmwares = dditable->Device->pfnEnumFirmwares;
        if( nullptr == pfnEnumFirmwares ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumFirmwares( hDevice, pCount, phFirmware );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFirmware )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Firmware == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Firmware->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hFirmware, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFirmware )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Firmware == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnFlash = dditable->Firmware->pfnFlash;
        if( nullptr == pfnFlash ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnFlash( hFirmware, pImage, size );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFirmware )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_8) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Firmware == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetFlashProgress = dditable->Firmware->pfnGetFlashProgress;
        if( nullptr == pfnGetFlashProgress ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetFlashProgress( hFirmware, pCompletionPercent );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFirmwareGetConsoleLogs
    __zedlllocal ze_result_t ZE_APICALL
    zesFirmwareGetConsoleLogs(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        size_t* pSize,                                  ///< [in,out] size of firmware log
        char* pFirmwareLog                              ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFirmware )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Firmware == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetConsoleLogs = dditable->Firmware->pfnGetConsoleLogs;
        if( nullptr == pfnGetConsoleLogs ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetConsoleLogs( hFirmware, pSize, pFirmwareLog );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumFrequencyDomains = dditable->Device->pfnEnumFrequencyDomains;
        if( nullptr == pfnEnumFrequencyDomains ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumFrequencyDomains( hDevice, pCount, phFrequency );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Frequency->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hFrequency, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetAvailableClocks = dditable->Frequency->pfnGetAvailableClocks;
        if( nullptr == pfnGetAvailableClocks ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetAvailableClocks( hFrequency, pCount, phFrequency );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetRange = dditable->Frequency->pfnGetRange;
        if( nullptr == pfnGetRange ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetRange( hFrequency, pLimits );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetRange = dditable->Frequency->pfnSetRange;
        if( nullptr == pfnSetRange ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetRange( hFrequency, pLimits );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetState = dditable->Frequency->pfnGetState;
        if( nullptr == pfnGetState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetState( hFrequency, pState );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetThrottleTime = dditable->Frequency->pfnGetThrottleTime;
        if( nullptr == pfnGetThrottleTime ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetThrottleTime( hFrequency, pThrottleTime );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnOcGetCapabilities = dditable->Frequency->pfnOcGetCapabilities;
        if( nullptr == pfnOcGetCapabilities ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnOcGetCapabilities( hFrequency, pOcCapabilities );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnOcGetFrequencyTarget = dditable->Frequency->pfnOcGetFrequencyTarget;
        if( nullptr == pfnOcGetFrequencyTarget ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnOcGetFrequencyTarget( hFrequency, pCurrentOcFrequency );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnOcSetFrequencyTarget = dditable->Frequency->pfnOcSetFrequencyTarget;
        if( nullptr == pfnOcSetFrequencyTarget ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnOcSetFrequencyTarget( hFrequency, CurrentOcFrequency );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnOcGetVoltageTarget = dditable->Frequency->pfnOcGetVoltageTarget;
        if( nullptr == pfnOcGetVoltageTarget ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnOcGetVoltageTarget( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnOcSetVoltageTarget = dditable->Frequency->pfnOcSetVoltageTarget;
        if( nullptr == pfnOcSetVoltageTarget ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnOcSetVoltageTarget( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnOcSetMode = dditable->Frequency->pfnOcSetMode;
        if( nullptr == pfnOcSetMode ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnOcSetMode( hFrequency, CurrentOcMode );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnOcGetMode = dditable->Frequency->pfnOcGetMode;
        if( nullptr == pfnOcGetMode ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnOcGetMode( hFrequency, pCurrentOcMode );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnOcGetIccMax = dditable->Frequency->pfnOcGetIccMax;
        if( nullptr == pfnOcGetIccMax ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnOcGetIccMax( hFrequency, pOcIccMax );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnOcSetIccMax = dditable->Frequency->pfnOcSetIccMax;
        if( nullptr == pfnOcSetIccMax ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnOcSetIccMax( hFrequency, ocIccMax );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnOcGetTjMax = dditable->Frequency->pfnOcGetTjMax;
        if( nullptr == pfnOcGetTjMax ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnOcGetTjMax( hFrequency, pOcTjMax );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFrequency )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Frequency == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnOcSetTjMax = dditable->Frequency->pfnOcSetTjMax;
        if( nullptr == pfnOcSetTjMax ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnOcSetTjMax( hFrequency, ocTjMax );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumLeds = dditable->Device->pfnEnumLeds;
        if( nullptr == pfnEnumLeds ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumLeds( hDevice, pCount, phLed );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hLed )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Led == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Led->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hLed, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hLed )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Led == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetState = dditable->Led->pfnGetState;
        if( nullptr == pfnGetState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetState( hLed, pState );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hLed )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Led == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetState = dditable->Led->pfnSetState;
        if( nullptr == pfnSetState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetState( hLed, enable );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hLed )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Led == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetColor = dditable->Led->pfnSetColor;
        if( nullptr == pfnSetColor ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetColor( hLed, pColor );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumMemoryModules = dditable->Device->pfnEnumMemoryModules;
        if( nullptr == pfnEnumMemoryModules ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumMemoryModules( hDevice, pCount, phMemory );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hMemory )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Memory == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Memory->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hMemory, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hMemory )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Memory == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetState = dditable->Memory->pfnGetState;
        if( nullptr == pfnGetState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetState( hMemory, pState );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hMemory )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Memory == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetBandwidth = dditable->Memory->pfnGetBandwidth;
        if( nullptr == pfnGetBandwidth ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetBandwidth( hMemory, pBandwidth );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumPerformanceFactorDomains = dditable->Device->pfnEnumPerformanceFactorDomains;
        if( nullptr == pfnEnumPerformanceFactorDomains ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumPerformanceFactorDomains( hDevice, pCount, phPerf );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPerf )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->PerformanceFactor == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->PerformanceFactor->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hPerf, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPerf )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->PerformanceFactor == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetConfig = dditable->PerformanceFactor->pfnGetConfig;
        if( nullptr == pfnGetConfig ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetConfig( hPerf, pFactor );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPerf )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->PerformanceFactor == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetConfig = dditable->PerformanceFactor->pfnSetConfig;
        if( nullptr == pfnSetConfig ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetConfig( hPerf, factor );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumPowerDomains = dditable->Device->pfnEnumPowerDomains;
        if( nullptr == pfnEnumPowerDomains ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumPowerDomains( hDevice, pCount, phPower );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetCardPowerDomain = dditable->Device->pfnGetCardPowerDomain;
        if( nullptr == pfnGetCardPowerDomain ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetCardPowerDomain( hDevice, phPower );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPower )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Power == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Power->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hPower, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPower )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Power == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetEnergyCounter = dditable->Power->pfnGetEnergyCounter;
        if( nullptr == pfnGetEnergyCounter ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetEnergyCounter( hPower, pEnergy );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPower )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Power == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetLimits = dditable->Power->pfnGetLimits;
        if( nullptr == pfnGetLimits ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetLimits( hPower, pSustained, pBurst, pPeak );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPower )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Power == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetLimits = dditable->Power->pfnSetLimits;
        if( nullptr == pfnSetLimits ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetLimits( hPower, pSustained, pBurst, pPeak );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPower )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Power == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetEnergyThreshold = dditable->Power->pfnGetEnergyThreshold;
        if( nullptr == pfnGetEnergyThreshold ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetEnergyThreshold( hPower, pThreshold );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPower )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Power == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetEnergyThreshold = dditable->Power->pfnSetEnergyThreshold;
        if( nullptr == pfnSetEnergyThreshold ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetEnergyThreshold( hPower, threshold );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumPsus = dditable->Device->pfnEnumPsus;
        if( nullptr == pfnEnumPsus ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumPsus( hDevice, pCount, phPsu );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPsu )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Psu == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Psu->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hPsu, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPsu )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Psu == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetState = dditable->Psu->pfnGetState;
        if( nullptr == pfnGetState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetState( hPsu, pState );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumRasErrorSets = dditable->Device->pfnEnumRasErrorSets;
        if( nullptr == pfnEnumRasErrorSets ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumRasErrorSets( hDevice, pCount, phRas );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hRas )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Ras == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Ras->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hRas, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hRas )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Ras == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetConfig = dditable->Ras->pfnGetConfig;
        if( nullptr == pfnGetConfig ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetConfig( hRas, pConfig );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hRas )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Ras == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetConfig = dditable->Ras->pfnSetConfig;
        if( nullptr == pfnSetConfig ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetConfig( hRas, pConfig );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hRas )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Ras == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetState = dditable->Ras->pfnGetState;
        if( nullptr == pfnGetState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetState( hRas, clear, pState );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumSchedulers = dditable->Device->pfnEnumSchedulers;
        if( nullptr == pfnEnumSchedulers ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumSchedulers( hDevice, pCount, phScheduler );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hScheduler )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Scheduler == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Scheduler->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hScheduler, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hScheduler )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Scheduler == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetCurrentMode = dditable->Scheduler->pfnGetCurrentMode;
        if( nullptr == pfnGetCurrentMode ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetCurrentMode( hScheduler, pMode );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hScheduler )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Scheduler == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetTimeoutModeProperties = dditable->Scheduler->pfnGetTimeoutModeProperties;
        if( nullptr == pfnGetTimeoutModeProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hScheduler )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Scheduler == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetTimesliceModeProperties = dditable->Scheduler->pfnGetTimesliceModeProperties;
        if( nullptr == pfnGetTimesliceModeProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hScheduler )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Scheduler == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetTimeoutMode = dditable->Scheduler->pfnSetTimeoutMode;
        if( nullptr == pfnSetTimeoutMode ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hScheduler )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Scheduler == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetTimesliceMode = dditable->Scheduler->pfnSetTimesliceMode;
        if( nullptr == pfnSetTimesliceMode ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hScheduler )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Scheduler == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetExclusiveMode = dditable->Scheduler->pfnSetExclusiveMode;
        if( nullptr == pfnSetExclusiveMode ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetExclusiveMode( hScheduler, pNeedReload );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hScheduler )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Scheduler == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetComputeUnitDebugMode = dditable->Scheduler->pfnSetComputeUnitDebugMode;
        if( nullptr == pfnSetComputeUnitDebugMode ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumStandbyDomains = dditable->Device->pfnEnumStandbyDomains;
        if( nullptr == pfnEnumStandbyDomains ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumStandbyDomains( hDevice, pCount, phStandby );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hStandby )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Standby == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Standby->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hStandby, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hStandby )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Standby == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetMode = dditable->Standby->pfnGetMode;
        if( nullptr == pfnGetMode ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetMode( hStandby, pMode );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hStandby )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Standby == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetMode = dditable->Standby->pfnSetMode;
        if( nullptr == pfnSetMode ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetMode( hStandby, mode );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Device == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumTemperatureSensors = dditable->Device->pfnEnumTemperatureSensors;
        if( nullptr == pfnEnumTemperatureSensors ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumTemperatureSensors( hDevice, pCount, phTemperature );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hTemperature )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Temperature == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetProperties = dditable->Temperature->pfnGetProperties;
        if( nullptr == pfnGetProperties ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetProperties( hTemperature, pProperties );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hTemperature )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Temperature == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetConfig = dditable->Temperature->pfnGetConfig;
        if( nullptr == pfnGetConfig ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetConfig( hTemperature, pConfig );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hTemperature )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Temperature == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetConfig = dditable->Temperature->pfnSetConfig;
        if( nullptr == pfnSetConfig ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetConfig( hTemperature, pConfig );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hTemperature )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Temperature == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetState = dditable->Temperature->pfnGetState;
        if( nullptr == pfnGetState ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetState( hTemperature, pTemperature );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPower )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Power == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetLimitsExt = dditable->Power->pfnGetLimitsExt;
        if( nullptr == pfnGetLimitsExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetLimitsExt( hPower, pCount, pSustained );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hPower )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Power == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetLimitsExt = dditable->Power->pfnSetLimitsExt;
        if( nullptr == pfnSetLimitsExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetLimitsExt( hPower, pCount, pSustained );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hEngine )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_7) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->Engine == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetActivityExt = dditable->Engine->pfnGetActivityExt;
        if( nullptr == pfnGetActivityExt ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetActivityExt( hEngine, pCount, pStats );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hRas )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RasExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetStateExp = dditable->RasExp->pfnGetStateExp;
        if( nullptr == pfnGetStateExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetStateExp( hRas, pCount, pState );
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

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hRas )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_0) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->RasExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnClearStateExp = dditable->RasExp->pfnClearStateExp;
        if( nullptr == pfnClearStateExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnClearStateExp( hRas, category );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFirmwareGetSecurityVersionExp
    __zedlllocal ze_result_t ZE_APICALL
    zesFirmwareGetSecurityVersionExp(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        char* pVersion                                  ///< [in,out] NULL terminated string value. The string "unknown" will be
                                                        ///< returned if this property cannot be determined.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFirmware )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FirmwareExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetSecurityVersionExp = dditable->FirmwareExp->pfnGetSecurityVersionExp;
        if( nullptr == pfnGetSecurityVersionExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetSecurityVersionExp( hFirmware, pVersion );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFirmwareSetSecurityVersionExp
    __zedlllocal ze_result_t ZE_APICALL
    zesFirmwareSetSecurityVersionExp(
        zes_firmware_handle_t hFirmware                 ///< [in] Handle for the component.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hFirmware )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->FirmwareExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetSecurityVersionExp = dditable->FirmwareExp->pfnSetSecurityVersionExp;
        if( nullptr == pfnSetSecurityVersionExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetSecurityVersionExp( hFirmware );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetSubDevicePropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGetSubDevicePropertiesExp(
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->DeviceExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetSubDevicePropertiesExp = dditable->DeviceExp->pfnGetSubDevicePropertiesExp;
        if( nullptr == pfnGetSubDevicePropertiesExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetSubDevicePropertiesExp( hDevice, pCount, pSubdeviceProps );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDriverGetDeviceByUuidExp
    __zedlllocal ze_result_t ZE_APICALL
    zesDriverGetDeviceByUuidExp(
        zes_driver_handle_t hDriver,                    ///< [in] handle of the sysman driver instance
        zes_uuid_t uuid,                                ///< [in] universal unique identifier.
        zes_device_handle_t* phDevice,                  ///< [out] Sysman handle of the device.
        ze_bool_t* onSubdevice,                         ///< [out] True if the UUID belongs to the sub-device; false means that
                                                        ///< UUID belongs to the root device.
        uint32_t* subdeviceId                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDriver )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->DriverExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetDeviceByUuidExp = dditable->DriverExp->pfnGetDeviceByUuidExp;
        if( nullptr == pfnGetDeviceByUuidExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetDeviceByUuidExp( hDriver, uuid, phDevice, onSubdevice, subdeviceId );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumActiveVFExp
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumActiveVFExp(
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->DeviceExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumActiveVFExp = dditable->DeviceExp->pfnEnumActiveVFExp;
        if( nullptr == pfnEnumActiveVFExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumActiveVFExp( hDevice, pCount, phVFhandle );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesVFManagementGetVFPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zesVFManagementGetVFPropertiesExp(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
        zes_vf_exp_properties_t* pProperties            ///< [in,out] Will contain VF properties.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hVFhandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VFManagementExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetVFPropertiesExp = dditable->VFManagementExp->pfnGetVFPropertiesExp;
        if( nullptr == pfnGetVFPropertiesExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetVFPropertiesExp( hVFhandle, pProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesVFManagementGetVFMemoryUtilizationExp
    __zedlllocal ze_result_t ZE_APICALL
    zesVFManagementGetVFMemoryUtilizationExp(
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hVFhandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VFManagementExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetVFMemoryUtilizationExp = dditable->VFManagementExp->pfnGetVFMemoryUtilizationExp;
        if( nullptr == pfnGetVFMemoryUtilizationExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetVFMemoryUtilizationExp( hVFhandle, pCount, pMemUtil );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesVFManagementGetVFEngineUtilizationExp
    __zedlllocal ze_result_t ZE_APICALL
    zesVFManagementGetVFEngineUtilizationExp(
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hVFhandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VFManagementExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetVFEngineUtilizationExp = dditable->VFManagementExp->pfnGetVFEngineUtilizationExp;
        if( nullptr == pfnGetVFEngineUtilizationExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetVFEngineUtilizationExp( hVFhandle, pCount, pEngineUtil );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesVFManagementSetVFTelemetryModeExp
    __zedlllocal ze_result_t ZE_APICALL
    zesVFManagementSetVFTelemetryModeExp(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
        zes_vf_info_util_exp_flags_t flags,             ///< [in] utilization flags to enable or disable. May be 0 or a valid
                                                        ///< combination of ::zes_vf_info_util_exp_flag_t.
        ze_bool_t enable                                ///< [in] Enable utilization telemetry.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hVFhandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VFManagementExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetVFTelemetryModeExp = dditable->VFManagementExp->pfnSetVFTelemetryModeExp;
        if( nullptr == pfnSetVFTelemetryModeExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetVFTelemetryModeExp( hVFhandle, flags, enable );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesVFManagementSetVFTelemetrySamplingIntervalExp
    __zedlllocal ze_result_t ZE_APICALL
    zesVFManagementSetVFTelemetrySamplingIntervalExp(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
        zes_vf_info_util_exp_flags_t flag,              ///< [in] utilization flags to set sampling interval. May be 0 or a valid
                                                        ///< combination of ::zes_vf_info_util_exp_flag_t.
        uint64_t samplingInterval                       ///< [in] Sampling interval value.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hVFhandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_9) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VFManagementExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnSetVFTelemetrySamplingIntervalExp = dditable->VFManagementExp->pfnSetVFTelemetrySamplingIntervalExp;
        if( nullptr == pfnSetVFTelemetrySamplingIntervalExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnSetVFTelemetrySamplingIntervalExp( hVFhandle, flag, samplingInterval );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEnumEnabledVFExp
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEnumEnabledVFExp(
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hDevice )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_10) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->DeviceExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnEnumEnabledVFExp = dditable->DeviceExp->pfnEnumEnabledVFExp;
        if( nullptr == pfnEnumEnabledVFExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnEnumEnabledVFExp( hDevice, pCount, phVFhandle );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesVFManagementGetVFCapabilitiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zesVFManagementGetVFCapabilitiesExp(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
        zes_vf_exp_capabilities_t* pCapability          ///< [in,out] Will contain VF capability.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hVFhandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_10) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VFManagementExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetVFCapabilitiesExp = dditable->VFManagementExp->pfnGetVFCapabilitiesExp;
        if( nullptr == pfnGetVFCapabilitiesExp ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetVFCapabilitiesExp( hVFhandle, pCapability );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesVFManagementGetVFMemoryUtilizationExp2
    __zedlllocal ze_result_t ZE_APICALL
    zesVFManagementGetVFMemoryUtilizationExp2(
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hVFhandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_10) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VFManagementExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetVFMemoryUtilizationExp2 = dditable->VFManagementExp->pfnGetVFMemoryUtilizationExp2;
        if( nullptr == pfnGetVFMemoryUtilizationExp2 ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetVFMemoryUtilizationExp2( hVFhandle, pCount, pMemUtil );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesVFManagementGetVFEngineUtilizationExp2
    __zedlllocal ze_result_t ZE_APICALL
    zesVFManagementGetVFEngineUtilizationExp2(
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
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hVFhandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_10) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VFManagementExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetVFEngineUtilizationExp2 = dditable->VFManagementExp->pfnGetVFEngineUtilizationExp2;
        if( nullptr == pfnGetVFEngineUtilizationExp2 ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetVFEngineUtilizationExp2( hVFhandle, pCount, pEngineUtil );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesVFManagementGetVFCapabilitiesExp2
    __zedlllocal ze_result_t ZE_APICALL
    zesVFManagementGetVFCapabilitiesExp2(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
        zes_vf_exp2_capabilities_t* pCapability         ///< [in,out] Will contain VF capability.
        )
    {
        ze_result_t result = ZE_RESULT_SUCCESS;

        // extract handle's function pointer table
        auto dditable = reinterpret_cast<ze_handle_t*>( hVFhandle )->pSysman;
        if (dditable->isValidFlag == 0)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        // Check that api version in the driver is supported by this version of the API
        if (dditable->version < ZE_API_VERSION_1_12) {
            return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;
        }
        // Check that the driver has the function pointer table init
        if (dditable->VFManagementExp == nullptr) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        auto pfnGetVFCapabilitiesExp2 = dditable->VFManagementExp->pfnGetVFCapabilitiesExp2;
        if( nullptr == pfnGetVFCapabilitiesExp2 ) {
            return ZE_RESULT_ERROR_UNINITIALIZED;
        }
        // forward to device-driver
        result = pfnGetVFCapabilitiesExp2( hVFhandle, pCapability );
        return result;
    }


    ///////////////////////////////////////////////////////////////////////////////
    /// @brief function for removing the ddi driver tables for zes
    __zedlllocal void ZE_APICALL
    zesDestroyDDiDriverTables(zes_dditable_driver_t* pDdiTable)
    {
        // Delete ddi tables
        delete pDdiTable->Global;
        delete pDdiTable->Device;
        delete pDdiTable->DeviceExp;
        delete pDdiTable->Driver;
        delete pDdiTable->DriverExp;
        delete pDdiTable->Diagnostics;
        delete pDdiTable->Engine;
        delete pDdiTable->FabricPort;
        delete pDdiTable->Fan;
        delete pDdiTable->Firmware;
        delete pDdiTable->FirmwareExp;
        delete pDdiTable->Frequency;
        delete pDdiTable->Led;
        delete pDdiTable->Memory;
        delete pDdiTable->Overclock;
        delete pDdiTable->PerformanceFactor;
        delete pDdiTable->Power;
        delete pDdiTable->Psu;
        delete pDdiTable->Ras;
        delete pDdiTable->RasExp;
        delete pDdiTable->Scheduler;
        delete pDdiTable->Standby;
        delete pDdiTable->Temperature;
        delete pDdiTable->VFManagementExp;
        delete pDdiTable;
    }

} // namespace loader_driver_ddi