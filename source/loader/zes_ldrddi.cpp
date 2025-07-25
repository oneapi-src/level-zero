/*
 *
 * Copyright (C) 2019-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_ldrddi.cpp
 *
 */
#include "ze_loader_internal.h"

using namespace loader_driver_ddi;

namespace loader
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

        bool atLeastOneDriverValid = false;
        for( auto& drv : *loader::context->sysmanInstanceDrivers )
        {
            if(drv.initStatus != ZE_RESULT_SUCCESS || drv.initSysManStatus != ZE_RESULT_SUCCESS)
                continue;
            if (!drv.dditable.zes.Global.pfnInit) {
                drv.initSysManStatus = ZE_RESULT_ERROR_UNINITIALIZED;
                continue;
            }
            drv.initSysManStatus = drv.dditable.zes.Global.pfnInit( flags );
            if(drv.initSysManStatus == ZE_RESULT_SUCCESS)
                atLeastOneDriverValid = true;
        }

        if(!atLeastOneDriverValid)
            result=ZE_RESULT_ERROR_UNINITIALIZED;

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

        uint32_t total_driver_handle_count = 0;

        {
            std::lock_guard<std::mutex> lock(loader::context->sortMutex);
            if (!loader::context->sortingInProgress.exchange(true) && !loader::context->instrumentationEnabled) {
                std::call_once(loader::context->sysmanDriverSortOnce, []() {
                    loader::context->driverSorting(loader::context->sysmanInstanceDrivers, nullptr, true);
                });
                loader::context->sortingInProgress.store(false);
            }
        }

        for( auto& drv : *loader::context->sysmanInstanceDrivers )
        {
            if(drv.initStatus != ZE_RESULT_SUCCESS || drv.initSysManStatus != ZE_RESULT_SUCCESS)
                continue;

            if( ( 0 < *pCount ) && ( *pCount == total_driver_handle_count))
                break;

            uint32_t library_driver_handle_count = 0;

            result = drv.dditable.zes.Driver.pfnGet( &library_driver_handle_count, nullptr );
            if( ZE_RESULT_SUCCESS != result ) {
                // If Get Drivers fails with Uninitialized, then update the driver init status to prevent reporting this driver in the next get call.
                if (ZE_RESULT_ERROR_UNINITIALIZED == result) {
                    drv.initStatus = result;
                }
                continue;
            }

            if( nullptr != phDrivers && *pCount !=0)
            {
                if( total_driver_handle_count + library_driver_handle_count > *pCount) {
                    library_driver_handle_count = *pCount - total_driver_handle_count;
                }
                result = drv.dditable.zes.Driver.pfnGet( &library_driver_handle_count, &phDrivers[ total_driver_handle_count ] );
                if( ZE_RESULT_SUCCESS != result ) break;

                drv.driverInuse = true;

                try
                {
                    for( uint32_t i = 0; i < library_driver_handle_count; ++i ) {
                        uint32_t driver_index = total_driver_handle_count + i;
                        phDrivers[ driver_index ] = reinterpret_cast<zes_driver_handle_t>(
                            context->zes_driver_factory.getInstance( phDrivers[ driver_index ], &drv.dditable ) );
                    }
                }
                catch( std::bad_alloc& )
                {
                    result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
                }
            }

            total_driver_handle_count += library_driver_handle_count;
        }

        // If the last driver get failed, but at least one driver succeeded, then return success with total count.
        if( ZE_RESULT_SUCCESS == result || total_driver_handle_count > 0)
            *pCount = total_driver_handle_count;
        if (total_driver_handle_count > 0) {
            result = ZE_RESULT_SUCCESS;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_driver_object_t*>( hDriver )->dditable;
        auto pfnGetExtensionProperties = dditable->zes.Driver.pfnGetExtensionProperties;
        if( nullptr == pfnGetExtensionProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<zes_driver_object_t*>( hDriver )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_driver_object_t*>( hDriver )->dditable;
        auto pfnGetExtensionFunctionAddress = dditable->zes.Driver.pfnGetExtensionFunctionAddress;
        if( nullptr == pfnGetExtensionFunctionAddress )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<zes_driver_object_t*>( hDriver )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_driver_object_t*>( hDriver )->dditable;
        auto pfnGet = dditable->zes.Device.pfnGet;
        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<zes_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnGet( hDriver, pCount, phDevices );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phDevices ) && ( i < *pCount ); ++i )
                phDevices[ i ] = reinterpret_cast<zes_device_handle_t>(
                    context->zes_device_factory.getInstance( phDevices[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnGetProperties = dditable->zes.Device.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnGetState = dditable->zes.Device.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnReset = dditable->zes.Device.pfnReset;
        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnResetExt = dditable->zes.Device.pfnResetExt;
        if( nullptr == pfnResetExt )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnProcessesGetState = dditable->zes.Device.pfnProcessesGetState;
        if( nullptr == pfnProcessesGetState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnPciGetProperties = dditable->zes.Device.pfnPciGetProperties;
        if( nullptr == pfnPciGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnPciGetState = dditable->zes.Device.pfnPciGetState;
        if( nullptr == pfnPciGetState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnPciGetBars = dditable->zes.Device.pfnPciGetBars;
        if( nullptr == pfnPciGetBars )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnPciGetStats = dditable->zes.Device.pfnPciGetStats;
        if( nullptr == pfnPciGetStats )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnSetOverclockWaiver = dditable->zes.Device.pfnSetOverclockWaiver;
        if( nullptr == pfnSetOverclockWaiver )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnGetOverclockDomains = dditable->zes.Device.pfnGetOverclockDomains;
        if( nullptr == pfnGetOverclockDomains )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnGetOverclockControls = dditable->zes.Device.pfnGetOverclockControls;
        if( nullptr == pfnGetOverclockControls )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnResetOverclockSettings = dditable->zes.Device.pfnResetOverclockSettings;
        if( nullptr == pfnResetOverclockSettings )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnReadOverclockState = dditable->zes.Device.pfnReadOverclockState;
        if( nullptr == pfnReadOverclockState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumOverclockDomains = dditable->zes.Device.pfnEnumOverclockDomains;
        if( nullptr == pfnEnumOverclockDomains )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumOverclockDomains( hDevice, pCount, phDomainHandle );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phDomainHandle ) && ( i < *pCount ); ++i )
                phDomainHandle[ i ] = reinterpret_cast<zes_overclock_handle_t>(
                    context->zes_overclock_factory.getInstance( phDomainHandle[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->dditable;
        auto pfnGetDomainProperties = dditable->zes.Overclock.pfnGetDomainProperties;
        if( nullptr == pfnGetDomainProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDomainHandle = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->dditable;
        auto pfnGetDomainVFProperties = dditable->zes.Overclock.pfnGetDomainVFProperties;
        if( nullptr == pfnGetDomainVFProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDomainHandle = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->dditable;
        auto pfnGetDomainControlProperties = dditable->zes.Overclock.pfnGetDomainControlProperties;
        if( nullptr == pfnGetDomainControlProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDomainHandle = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->dditable;
        auto pfnGetControlCurrentValue = dditable->zes.Overclock.pfnGetControlCurrentValue;
        if( nullptr == pfnGetControlCurrentValue )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDomainHandle = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->dditable;
        auto pfnGetControlPendingValue = dditable->zes.Overclock.pfnGetControlPendingValue;
        if( nullptr == pfnGetControlPendingValue )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDomainHandle = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->dditable;
        auto pfnSetControlUserValue = dditable->zes.Overclock.pfnSetControlUserValue;
        if( nullptr == pfnSetControlUserValue )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDomainHandle = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->dditable;
        auto pfnGetControlState = dditable->zes.Overclock.pfnGetControlState;
        if( nullptr == pfnGetControlState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDomainHandle = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->dditable;
        auto pfnGetVFPointValues = dditable->zes.Overclock.pfnGetVFPointValues;
        if( nullptr == pfnGetVFPointValues )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDomainHandle = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->dditable;
        auto pfnSetVFPointValues = dditable->zes.Overclock.pfnSetVFPointValues;
        if( nullptr == pfnSetVFPointValues )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDomainHandle = reinterpret_cast<zes_overclock_object_t*>( hDomainHandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumDiagnosticTestSuites = dditable->zes.Device.pfnEnumDiagnosticTestSuites;
        if( nullptr == pfnEnumDiagnosticTestSuites )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumDiagnosticTestSuites( hDevice, pCount, phDiagnostics );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phDiagnostics ) && ( i < *pCount ); ++i )
                phDiagnostics[ i ] = reinterpret_cast<zes_diag_handle_t>(
                    context->zes_diag_factory.getInstance( phDiagnostics[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_diag_object_t*>( hDiagnostics )->dditable;
        auto pfnGetProperties = dditable->zes.Diagnostics.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDiagnostics = reinterpret_cast<zes_diag_object_t*>( hDiagnostics )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_diag_object_t*>( hDiagnostics )->dditable;
        auto pfnGetTests = dditable->zes.Diagnostics.pfnGetTests;
        if( nullptr == pfnGetTests )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDiagnostics = reinterpret_cast<zes_diag_object_t*>( hDiagnostics )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_diag_object_t*>( hDiagnostics )->dditable;
        auto pfnRunTests = dditable->zes.Diagnostics.pfnRunTests;
        if( nullptr == pfnRunTests )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDiagnostics = reinterpret_cast<zes_diag_object_t*>( hDiagnostics )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEccAvailable = dditable->zes.Device.pfnEccAvailable;
        if( nullptr == pfnEccAvailable )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEccConfigurable = dditable->zes.Device.pfnEccConfigurable;
        if( nullptr == pfnEccConfigurable )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnGetEccState = dditable->zes.Device.pfnGetEccState;
        if( nullptr == pfnGetEccState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnSetEccState = dditable->zes.Device.pfnSetEccState;
        if( nullptr == pfnSetEccState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumEngineGroups = dditable->zes.Device.pfnEnumEngineGroups;
        if( nullptr == pfnEnumEngineGroups )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumEngineGroups( hDevice, pCount, phEngine );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phEngine ) && ( i < *pCount ); ++i )
                phEngine[ i ] = reinterpret_cast<zes_engine_handle_t>(
                    context->zes_engine_factory.getInstance( phEngine[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_engine_object_t*>( hEngine )->dditable;
        auto pfnGetProperties = dditable->zes.Engine.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEngine = reinterpret_cast<zes_engine_object_t*>( hEngine )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_engine_object_t*>( hEngine )->dditable;
        auto pfnGetActivity = dditable->zes.Engine.pfnGetActivity;
        if( nullptr == pfnGetActivity )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEngine = reinterpret_cast<zes_engine_object_t*>( hEngine )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEventRegister = dditable->zes.Device.pfnEventRegister;
        if( nullptr == pfnEventRegister )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnEventListen = dditable->zes.Driver.pfnEventListen;
        if( nullptr == pfnEventListen )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // convert loader handles to driver handles
        auto phDevicesLocal = new zes_device_handle_t [count];
        for( size_t i = 0; ( nullptr != phDevices ) && ( i < count ); ++i )
            phDevicesLocal[ i ] = reinterpret_cast<zes_device_object_t*>( phDevices[ i ] )->handle;

        // forward to device-driver
        result = pfnEventListen( hDriver, timeout, count, phDevicesLocal, pNumDeviceEvents, pEvents );
        delete []phDevicesLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<ze_driver_object_t*>( hDriver )->dditable;
        auto pfnEventListenEx = dditable->zes.Driver.pfnEventListenEx;
        if( nullptr == pfnEventListenEx )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<ze_driver_object_t*>( hDriver )->handle;

        // convert loader handles to driver handles
        auto phDevicesLocal = new zes_device_handle_t [count];
        for( size_t i = 0; ( nullptr != phDevices ) && ( i < count ); ++i )
            phDevicesLocal[ i ] = reinterpret_cast<zes_device_object_t*>( phDevices[ i ] )->handle;

        // forward to device-driver
        result = pfnEventListenEx( hDriver, timeout, count, phDevicesLocal, pNumDeviceEvents, pEvents );
        delete []phDevicesLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumFabricPorts = dditable->zes.Device.pfnEnumFabricPorts;
        if( nullptr == pfnEnumFabricPorts )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumFabricPorts( hDevice, pCount, phPort );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPort ) && ( i < *pCount ); ++i )
                phPort[ i ] = reinterpret_cast<zes_fabric_port_handle_t>(
                    context->zes_fabric_port_factory.getInstance( phPort[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetProperties = dditable->zes.FabricPort.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetLinkType = dditable->zes.FabricPort.pfnGetLinkType;
        if( nullptr == pfnGetLinkType )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetConfig = dditable->zes.FabricPort.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->dditable;
        auto pfnSetConfig = dditable->zes.FabricPort.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetState = dditable->zes.FabricPort.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetThroughput = dditable->zes.FabricPort.pfnGetThroughput;
        if( nullptr == pfnGetThroughput )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->dditable;
        auto pfnGetFabricErrorCounters = dditable->zes.FabricPort.pfnGetFabricErrorCounters;
        if( nullptr == pfnGetFabricErrorCounters )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPort = reinterpret_cast<zes_fabric_port_object_t*>( hPort )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnGetMultiPortThroughput = dditable->zes.FabricPort.pfnGetMultiPortThroughput;
        if( nullptr == pfnGetMultiPortThroughput )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // convert loader handles to driver handles
        auto phPortLocal = new zes_fabric_port_handle_t [numPorts];
        for( size_t i = 0; ( nullptr != phPort ) && ( i < numPorts ); ++i )
            phPortLocal[ i ] = reinterpret_cast<zes_fabric_port_object_t*>( phPort[ i ] )->handle;

        // forward to device-driver
        result = pfnGetMultiPortThroughput( hDevice, numPorts, phPortLocal, pThroughput );
        delete []phPortLocal;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumFans = dditable->zes.Device.pfnEnumFans;
        if( nullptr == pfnEnumFans )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumFans( hDevice, pCount, phFan );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFan ) && ( i < *pCount ); ++i )
                phFan[ i ] = reinterpret_cast<zes_fan_handle_t>(
                    context->zes_fan_factory.getInstance( phFan[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fan_object_t*>( hFan )->dditable;
        auto pfnGetProperties = dditable->zes.Fan.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zes_fan_object_t*>( hFan )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fan_object_t*>( hFan )->dditable;
        auto pfnGetConfig = dditable->zes.Fan.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zes_fan_object_t*>( hFan )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fan_object_t*>( hFan )->dditable;
        auto pfnSetDefaultMode = dditable->zes.Fan.pfnSetDefaultMode;
        if( nullptr == pfnSetDefaultMode )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zes_fan_object_t*>( hFan )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fan_object_t*>( hFan )->dditable;
        auto pfnSetFixedSpeedMode = dditable->zes.Fan.pfnSetFixedSpeedMode;
        if( nullptr == pfnSetFixedSpeedMode )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zes_fan_object_t*>( hFan )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fan_object_t*>( hFan )->dditable;
        auto pfnSetSpeedTableMode = dditable->zes.Fan.pfnSetSpeedTableMode;
        if( nullptr == pfnSetSpeedTableMode )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zes_fan_object_t*>( hFan )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_fan_object_t*>( hFan )->dditable;
        auto pfnGetState = dditable->zes.Fan.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFan = reinterpret_cast<zes_fan_object_t*>( hFan )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumFirmwares = dditable->zes.Device.pfnEnumFirmwares;
        if( nullptr == pfnEnumFirmwares )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumFirmwares( hDevice, pCount, phFirmware );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFirmware ) && ( i < *pCount ); ++i )
                phFirmware[ i ] = reinterpret_cast<zes_firmware_handle_t>(
                    context->zes_firmware_factory.getInstance( phFirmware[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->dditable;
        auto pfnGetProperties = dditable->zes.Firmware.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->dditable;
        auto pfnFlash = dditable->zes.Firmware.pfnFlash;
        if( nullptr == pfnFlash )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->dditable;
        auto pfnGetFlashProgress = dditable->zes.Firmware.pfnGetFlashProgress;
        if( nullptr == pfnGetFlashProgress )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->dditable;
        auto pfnGetConsoleLogs = dditable->zes.Firmware.pfnGetConsoleLogs;
        if( nullptr == pfnGetConsoleLogs )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumFrequencyDomains = dditable->zes.Device.pfnEnumFrequencyDomains;
        if( nullptr == pfnEnumFrequencyDomains )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumFrequencyDomains( hDevice, pCount, phFrequency );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phFrequency ) && ( i < *pCount ); ++i )
                phFrequency[ i ] = reinterpret_cast<zes_freq_handle_t>(
                    context->zes_freq_factory.getInstance( phFrequency[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetProperties = dditable->zes.Frequency.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetAvailableClocks = dditable->zes.Frequency.pfnGetAvailableClocks;
        if( nullptr == pfnGetAvailableClocks )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetRange = dditable->zes.Frequency.pfnGetRange;
        if( nullptr == pfnGetRange )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnSetRange = dditable->zes.Frequency.pfnSetRange;
        if( nullptr == pfnSetRange )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetState = dditable->zes.Frequency.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnGetThrottleTime = dditable->zes.Frequency.pfnGetThrottleTime;
        if( nullptr == pfnGetThrottleTime )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetCapabilities = dditable->zes.Frequency.pfnOcGetCapabilities;
        if( nullptr == pfnOcGetCapabilities )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetFrequencyTarget = dditable->zes.Frequency.pfnOcGetFrequencyTarget;
        if( nullptr == pfnOcGetFrequencyTarget )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcSetFrequencyTarget = dditable->zes.Frequency.pfnOcSetFrequencyTarget;
        if( nullptr == pfnOcSetFrequencyTarget )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetVoltageTarget = dditable->zes.Frequency.pfnOcGetVoltageTarget;
        if( nullptr == pfnOcGetVoltageTarget )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcSetVoltageTarget = dditable->zes.Frequency.pfnOcSetVoltageTarget;
        if( nullptr == pfnOcSetVoltageTarget )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcSetMode = dditable->zes.Frequency.pfnOcSetMode;
        if( nullptr == pfnOcSetMode )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetMode = dditable->zes.Frequency.pfnOcGetMode;
        if( nullptr == pfnOcGetMode )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetIccMax = dditable->zes.Frequency.pfnOcGetIccMax;
        if( nullptr == pfnOcGetIccMax )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcSetIccMax = dditable->zes.Frequency.pfnOcSetIccMax;
        if( nullptr == pfnOcSetIccMax )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcGetTjMax = dditable->zes.Frequency.pfnOcGetTjMax;
        if( nullptr == pfnOcGetTjMax )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_freq_object_t*>( hFrequency )->dditable;
        auto pfnOcSetTjMax = dditable->zes.Frequency.pfnOcSetTjMax;
        if( nullptr == pfnOcSetTjMax )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFrequency = reinterpret_cast<zes_freq_object_t*>( hFrequency )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumLeds = dditable->zes.Device.pfnEnumLeds;
        if( nullptr == pfnEnumLeds )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumLeds( hDevice, pCount, phLed );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phLed ) && ( i < *pCount ); ++i )
                phLed[ i ] = reinterpret_cast<zes_led_handle_t>(
                    context->zes_led_factory.getInstance( phLed[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_led_object_t*>( hLed )->dditable;
        auto pfnGetProperties = dditable->zes.Led.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<zes_led_object_t*>( hLed )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_led_object_t*>( hLed )->dditable;
        auto pfnGetState = dditable->zes.Led.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<zes_led_object_t*>( hLed )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_led_object_t*>( hLed )->dditable;
        auto pfnSetState = dditable->zes.Led.pfnSetState;
        if( nullptr == pfnSetState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<zes_led_object_t*>( hLed )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_led_object_t*>( hLed )->dditable;
        auto pfnSetColor = dditable->zes.Led.pfnSetColor;
        if( nullptr == pfnSetColor )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hLed = reinterpret_cast<zes_led_object_t*>( hLed )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumMemoryModules = dditable->zes.Device.pfnEnumMemoryModules;
        if( nullptr == pfnEnumMemoryModules )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumMemoryModules( hDevice, pCount, phMemory );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phMemory ) && ( i < *pCount ); ++i )
                phMemory[ i ] = reinterpret_cast<zes_mem_handle_t>(
                    context->zes_mem_factory.getInstance( phMemory[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_mem_object_t*>( hMemory )->dditable;
        auto pfnGetProperties = dditable->zes.Memory.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMemory = reinterpret_cast<zes_mem_object_t*>( hMemory )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_mem_object_t*>( hMemory )->dditable;
        auto pfnGetState = dditable->zes.Memory.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMemory = reinterpret_cast<zes_mem_object_t*>( hMemory )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_mem_object_t*>( hMemory )->dditable;
        auto pfnGetBandwidth = dditable->zes.Memory.pfnGetBandwidth;
        if( nullptr == pfnGetBandwidth )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hMemory = reinterpret_cast<zes_mem_object_t*>( hMemory )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumPerformanceFactorDomains = dditable->zes.Device.pfnEnumPerformanceFactorDomains;
        if( nullptr == pfnEnumPerformanceFactorDomains )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumPerformanceFactorDomains( hDevice, pCount, phPerf );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPerf ) && ( i < *pCount ); ++i )
                phPerf[ i ] = reinterpret_cast<zes_perf_handle_t>(
                    context->zes_perf_factory.getInstance( phPerf[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_perf_object_t*>( hPerf )->dditable;
        auto pfnGetProperties = dditable->zes.PerformanceFactor.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPerf = reinterpret_cast<zes_perf_object_t*>( hPerf )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_perf_object_t*>( hPerf )->dditable;
        auto pfnGetConfig = dditable->zes.PerformanceFactor.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPerf = reinterpret_cast<zes_perf_object_t*>( hPerf )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_perf_object_t*>( hPerf )->dditable;
        auto pfnSetConfig = dditable->zes.PerformanceFactor.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPerf = reinterpret_cast<zes_perf_object_t*>( hPerf )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumPowerDomains = dditable->zes.Device.pfnEnumPowerDomains;
        if( nullptr == pfnEnumPowerDomains )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumPowerDomains( hDevice, pCount, phPower );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPower ) && ( i < *pCount ); ++i )
                phPower[ i ] = reinterpret_cast<zes_pwr_handle_t>(
                    context->zes_pwr_factory.getInstance( phPower[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnGetCardPowerDomain = dditable->zes.Device.pfnGetCardPowerDomain;
        if( nullptr == pfnGetCardPowerDomain )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnGetCardPowerDomain( hDevice, phPower );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phPower = reinterpret_cast<zes_pwr_handle_t>(
                context->zes_pwr_factory.getInstance( *phPower, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_pwr_object_t*>( hPower )->dditable;
        auto pfnGetProperties = dditable->zes.Power.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_pwr_object_t*>( hPower )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_pwr_object_t*>( hPower )->dditable;
        auto pfnGetEnergyCounter = dditable->zes.Power.pfnGetEnergyCounter;
        if( nullptr == pfnGetEnergyCounter )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_pwr_object_t*>( hPower )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_pwr_object_t*>( hPower )->dditable;
        auto pfnGetLimits = dditable->zes.Power.pfnGetLimits;
        if( nullptr == pfnGetLimits )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_pwr_object_t*>( hPower )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_pwr_object_t*>( hPower )->dditable;
        auto pfnSetLimits = dditable->zes.Power.pfnSetLimits;
        if( nullptr == pfnSetLimits )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_pwr_object_t*>( hPower )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_pwr_object_t*>( hPower )->dditable;
        auto pfnGetEnergyThreshold = dditable->zes.Power.pfnGetEnergyThreshold;
        if( nullptr == pfnGetEnergyThreshold )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_pwr_object_t*>( hPower )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_pwr_object_t*>( hPower )->dditable;
        auto pfnSetEnergyThreshold = dditable->zes.Power.pfnSetEnergyThreshold;
        if( nullptr == pfnSetEnergyThreshold )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_pwr_object_t*>( hPower )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumPsus = dditable->zes.Device.pfnEnumPsus;
        if( nullptr == pfnEnumPsus )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumPsus( hDevice, pCount, phPsu );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phPsu ) && ( i < *pCount ); ++i )
                phPsu[ i ] = reinterpret_cast<zes_psu_handle_t>(
                    context->zes_psu_factory.getInstance( phPsu[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_psu_object_t*>( hPsu )->dditable;
        auto pfnGetProperties = dditable->zes.Psu.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPsu = reinterpret_cast<zes_psu_object_t*>( hPsu )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_psu_object_t*>( hPsu )->dditable;
        auto pfnGetState = dditable->zes.Psu.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPsu = reinterpret_cast<zes_psu_object_t*>( hPsu )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumRasErrorSets = dditable->zes.Device.pfnEnumRasErrorSets;
        if( nullptr == pfnEnumRasErrorSets )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumRasErrorSets( hDevice, pCount, phRas );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phRas ) && ( i < *pCount ); ++i )
                phRas[ i ] = reinterpret_cast<zes_ras_handle_t>(
                    context->zes_ras_factory.getInstance( phRas[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_ras_object_t*>( hRas )->dditable;
        auto pfnGetProperties = dditable->zes.Ras.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zes_ras_object_t*>( hRas )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_ras_object_t*>( hRas )->dditable;
        auto pfnGetConfig = dditable->zes.Ras.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zes_ras_object_t*>( hRas )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_ras_object_t*>( hRas )->dditable;
        auto pfnSetConfig = dditable->zes.Ras.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zes_ras_object_t*>( hRas )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_ras_object_t*>( hRas )->dditable;
        auto pfnGetState = dditable->zes.Ras.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zes_ras_object_t*>( hRas )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumSchedulers = dditable->zes.Device.pfnEnumSchedulers;
        if( nullptr == pfnEnumSchedulers )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumSchedulers( hDevice, pCount, phScheduler );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phScheduler ) && ( i < *pCount ); ++i )
                phScheduler[ i ] = reinterpret_cast<zes_sched_handle_t>(
                    context->zes_sched_factory.getInstance( phScheduler[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnGetProperties = dditable->zes.Scheduler.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnGetCurrentMode = dditable->zes.Scheduler.pfnGetCurrentMode;
        if( nullptr == pfnGetCurrentMode )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnGetTimeoutModeProperties = dditable->zes.Scheduler.pfnGetTimeoutModeProperties;
        if( nullptr == pfnGetTimeoutModeProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnGetTimesliceModeProperties = dditable->zes.Scheduler.pfnGetTimesliceModeProperties;
        if( nullptr == pfnGetTimesliceModeProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnSetTimeoutMode = dditable->zes.Scheduler.pfnSetTimeoutMode;
        if( nullptr == pfnSetTimeoutMode )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnSetTimesliceMode = dditable->zes.Scheduler.pfnSetTimesliceMode;
        if( nullptr == pfnSetTimesliceMode )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnSetExclusiveMode = dditable->zes.Scheduler.pfnSetExclusiveMode;
        if( nullptr == pfnSetExclusiveMode )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_sched_object_t*>( hScheduler )->dditable;
        auto pfnSetComputeUnitDebugMode = dditable->zes.Scheduler.pfnSetComputeUnitDebugMode;
        if( nullptr == pfnSetComputeUnitDebugMode )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hScheduler = reinterpret_cast<zes_sched_object_t*>( hScheduler )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumStandbyDomains = dditable->zes.Device.pfnEnumStandbyDomains;
        if( nullptr == pfnEnumStandbyDomains )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumStandbyDomains( hDevice, pCount, phStandby );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phStandby ) && ( i < *pCount ); ++i )
                phStandby[ i ] = reinterpret_cast<zes_standby_handle_t>(
                    context->zes_standby_factory.getInstance( phStandby[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_standby_object_t*>( hStandby )->dditable;
        auto pfnGetProperties = dditable->zes.Standby.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hStandby = reinterpret_cast<zes_standby_object_t*>( hStandby )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_standby_object_t*>( hStandby )->dditable;
        auto pfnGetMode = dditable->zes.Standby.pfnGetMode;
        if( nullptr == pfnGetMode )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hStandby = reinterpret_cast<zes_standby_object_t*>( hStandby )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_standby_object_t*>( hStandby )->dditable;
        auto pfnSetMode = dditable->zes.Standby.pfnSetMode;
        if( nullptr == pfnSetMode )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hStandby = reinterpret_cast<zes_standby_object_t*>( hStandby )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumTemperatureSensors = dditable->zes.Device.pfnEnumTemperatureSensors;
        if( nullptr == pfnEnumTemperatureSensors )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumTemperatureSensors( hDevice, pCount, phTemperature );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phTemperature ) && ( i < *pCount ); ++i )
                phTemperature[ i ] = reinterpret_cast<zes_temp_handle_t>(
                    context->zes_temp_factory.getInstance( phTemperature[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_temp_object_t*>( hTemperature )->dditable;
        auto pfnGetProperties = dditable->zes.Temperature.pfnGetProperties;
        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zes_temp_object_t*>( hTemperature )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_temp_object_t*>( hTemperature )->dditable;
        auto pfnGetConfig = dditable->zes.Temperature.pfnGetConfig;
        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zes_temp_object_t*>( hTemperature )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_temp_object_t*>( hTemperature )->dditable;
        auto pfnSetConfig = dditable->zes.Temperature.pfnSetConfig;
        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zes_temp_object_t*>( hTemperature )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_temp_object_t*>( hTemperature )->dditable;
        auto pfnGetState = dditable->zes.Temperature.pfnGetState;
        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hTemperature = reinterpret_cast<zes_temp_object_t*>( hTemperature )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_pwr_object_t*>( hPower )->dditable;
        auto pfnGetLimitsExt = dditable->zes.Power.pfnGetLimitsExt;
        if( nullptr == pfnGetLimitsExt )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_pwr_object_t*>( hPower )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_pwr_object_t*>( hPower )->dditable;
        auto pfnSetLimitsExt = dditable->zes.Power.pfnSetLimitsExt;
        if( nullptr == pfnSetLimitsExt )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hPower = reinterpret_cast<zes_pwr_object_t*>( hPower )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_engine_object_t*>( hEngine )->dditable;
        auto pfnGetActivityExt = dditable->zes.Engine.pfnGetActivityExt;
        if( nullptr == pfnGetActivityExt )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hEngine = reinterpret_cast<zes_engine_object_t*>( hEngine )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_ras_object_t*>( hRas )->dditable;
        auto pfnGetStateExp = dditable->zes.RasExp.pfnGetStateExp;
        if( nullptr == pfnGetStateExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zes_ras_object_t*>( hRas )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_ras_object_t*>( hRas )->dditable;
        auto pfnClearStateExp = dditable->zes.RasExp.pfnClearStateExp;
        if( nullptr == pfnClearStateExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hRas = reinterpret_cast<zes_ras_object_t*>( hRas )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->dditable;
        auto pfnGetSecurityVersionExp = dditable->zes.FirmwareExp.pfnGetSecurityVersionExp;
        if( nullptr == pfnGetSecurityVersionExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->dditable;
        auto pfnSetSecurityVersionExp = dditable->zes.FirmwareExp.pfnSetSecurityVersionExp;
        if( nullptr == pfnSetSecurityVersionExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hFirmware = reinterpret_cast<zes_firmware_object_t*>( hFirmware )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnGetSubDevicePropertiesExp = dditable->zes.DeviceExp.pfnGetSubDevicePropertiesExp;
        if( nullptr == pfnGetSubDevicePropertiesExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_driver_object_t*>( hDriver )->dditable;
        auto pfnGetDeviceByUuidExp = dditable->zes.DriverExp.pfnGetDeviceByUuidExp;
        if( nullptr == pfnGetDeviceByUuidExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDriver = reinterpret_cast<zes_driver_object_t*>( hDriver )->handle;

        // forward to device-driver
        result = pfnGetDeviceByUuidExp( hDriver, uuid, phDevice, onSubdevice, subdeviceId );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handle to loader handle
            *phDevice = reinterpret_cast<zes_device_handle_t>(
                context->zes_device_factory.getInstance( *phDevice, dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumActiveVFExp = dditable->zes.DeviceExp.pfnEnumActiveVFExp;
        if( nullptr == pfnEnumActiveVFExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumActiveVFExp( hDevice, pCount, phVFhandle );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phVFhandle ) && ( i < *pCount ); ++i )
                phVFhandle[ i ] = reinterpret_cast<zes_vf_handle_t>(
                    context->zes_vf_factory.getInstance( phVFhandle[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->dditable;
        auto pfnGetVFPropertiesExp = dditable->zes.VFManagementExp.pfnGetVFPropertiesExp;
        if( nullptr == pfnGetVFPropertiesExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hVFhandle = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->dditable;
        auto pfnGetVFMemoryUtilizationExp = dditable->zes.VFManagementExp.pfnGetVFMemoryUtilizationExp;
        if( nullptr == pfnGetVFMemoryUtilizationExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hVFhandle = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->dditable;
        auto pfnGetVFEngineUtilizationExp = dditable->zes.VFManagementExp.pfnGetVFEngineUtilizationExp;
        if( nullptr == pfnGetVFEngineUtilizationExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hVFhandle = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->dditable;
        auto pfnSetVFTelemetryModeExp = dditable->zes.VFManagementExp.pfnSetVFTelemetryModeExp;
        if( nullptr == pfnSetVFTelemetryModeExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hVFhandle = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->dditable;
        auto pfnSetVFTelemetrySamplingIntervalExp = dditable->zes.VFManagementExp.pfnSetVFTelemetrySamplingIntervalExp;
        if( nullptr == pfnSetVFTelemetrySamplingIntervalExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hVFhandle = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_device_object_t*>( hDevice )->dditable;
        auto pfnEnumEnabledVFExp = dditable->zes.DeviceExp.pfnEnumEnabledVFExp;
        if( nullptr == pfnEnumEnabledVFExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hDevice = reinterpret_cast<zes_device_object_t*>( hDevice )->handle;

        // forward to device-driver
        result = pfnEnumEnabledVFExp( hDevice, pCount, phVFhandle );

        if( ZE_RESULT_SUCCESS != result )
            return result;

        try
        {
            // convert driver handles to loader handles
            for( size_t i = 0; ( nullptr != phVFhandle ) && ( i < *pCount ); ++i )
                phVFhandle[ i ] = reinterpret_cast<zes_vf_handle_t>(
                    context->zes_vf_factory.getInstance( phVFhandle[ i ], dditable ) );
        }
        catch( std::bad_alloc& )
        {
            result = ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY;
        }

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->dditable;
        auto pfnGetVFCapabilitiesExp = dditable->zes.VFManagementExp.pfnGetVFCapabilitiesExp;
        if( nullptr == pfnGetVFCapabilitiesExp )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hVFhandle = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->dditable;
        auto pfnGetVFMemoryUtilizationExp2 = dditable->zes.VFManagementExp.pfnGetVFMemoryUtilizationExp2;
        if( nullptr == pfnGetVFMemoryUtilizationExp2 )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hVFhandle = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->dditable;
        auto pfnGetVFEngineUtilizationExp2 = dditable->zes.VFManagementExp.pfnGetVFEngineUtilizationExp2;
        if( nullptr == pfnGetVFEngineUtilizationExp2 )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hVFhandle = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->handle;

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

        // extract driver's function pointer table
        auto dditable = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->dditable;
        auto pfnGetVFCapabilitiesExp2 = dditable->zes.VFManagementExp.pfnGetVFCapabilitiesExp2;
        if( nullptr == pfnGetVFCapabilitiesExp2 )
            return ZE_RESULT_ERROR_UNINITIALIZED;

        // convert loader handle to driver handle
        hVFhandle = reinterpret_cast<zes_vf_object_t*>( hVFhandle )->handle;

        // forward to device-driver
        result = pfnGetVFCapabilitiesExp2( hVFhandle, pCapability );

        return result;
    }

} // namespace loader

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Global table
__zedlllocal void ZE_APICALL
zesGetGlobalProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Global->pfnInit                                     = loader::zesInit;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Device table
__zedlllocal void ZE_APICALL
zesGetDeviceProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Device->pfnGetProperties                            = loader::zesDeviceGetProperties;
    loader::loaderDispatch->pSysman->Device->pfnGetState                                 = loader::zesDeviceGetState;
    loader::loaderDispatch->pSysman->Device->pfnReset                                    = loader::zesDeviceReset;
    loader::loaderDispatch->pSysman->Device->pfnProcessesGetState                        = loader::zesDeviceProcessesGetState;
    loader::loaderDispatch->pSysman->Device->pfnPciGetProperties                         = loader::zesDevicePciGetProperties;
    loader::loaderDispatch->pSysman->Device->pfnPciGetState                              = loader::zesDevicePciGetState;
    loader::loaderDispatch->pSysman->Device->pfnPciGetBars                               = loader::zesDevicePciGetBars;
    loader::loaderDispatch->pSysman->Device->pfnPciGetStats                              = loader::zesDevicePciGetStats;
    loader::loaderDispatch->pSysman->Device->pfnEnumDiagnosticTestSuites                 = loader::zesDeviceEnumDiagnosticTestSuites;
    loader::loaderDispatch->pSysman->Device->pfnEnumEngineGroups                         = loader::zesDeviceEnumEngineGroups;
    loader::loaderDispatch->pSysman->Device->pfnEventRegister                            = loader::zesDeviceEventRegister;
    loader::loaderDispatch->pSysman->Device->pfnEnumFabricPorts                          = loader::zesDeviceEnumFabricPorts;
    loader::loaderDispatch->pSysman->Device->pfnEnumFans                                 = loader::zesDeviceEnumFans;
    loader::loaderDispatch->pSysman->Device->pfnEnumFirmwares                            = loader::zesDeviceEnumFirmwares;
    loader::loaderDispatch->pSysman->Device->pfnEnumFrequencyDomains                     = loader::zesDeviceEnumFrequencyDomains;
    loader::loaderDispatch->pSysman->Device->pfnEnumLeds                                 = loader::zesDeviceEnumLeds;
    loader::loaderDispatch->pSysman->Device->pfnEnumMemoryModules                        = loader::zesDeviceEnumMemoryModules;
    loader::loaderDispatch->pSysman->Device->pfnEnumPerformanceFactorDomains             = loader::zesDeviceEnumPerformanceFactorDomains;
    loader::loaderDispatch->pSysman->Device->pfnEnumPowerDomains                         = loader::zesDeviceEnumPowerDomains;
    loader::loaderDispatch->pSysman->Device->pfnGetCardPowerDomain                       = loader::zesDeviceGetCardPowerDomain;
    loader::loaderDispatch->pSysman->Device->pfnEnumPsus                                 = loader::zesDeviceEnumPsus;
    loader::loaderDispatch->pSysman->Device->pfnEnumRasErrorSets                         = loader::zesDeviceEnumRasErrorSets;
    loader::loaderDispatch->pSysman->Device->pfnEnumSchedulers                           = loader::zesDeviceEnumSchedulers;
    loader::loaderDispatch->pSysman->Device->pfnEnumStandbyDomains                       = loader::zesDeviceEnumStandbyDomains;
    loader::loaderDispatch->pSysman->Device->pfnEnumTemperatureSensors                   = loader::zesDeviceEnumTemperatureSensors;
    loader::loaderDispatch->pSysman->Device->pfnEccAvailable                             = loader::zesDeviceEccAvailable;
    loader::loaderDispatch->pSysman->Device->pfnEccConfigurable                          = loader::zesDeviceEccConfigurable;
    loader::loaderDispatch->pSysman->Device->pfnGetEccState                              = loader::zesDeviceGetEccState;
    loader::loaderDispatch->pSysman->Device->pfnSetEccState                              = loader::zesDeviceSetEccState;
    loader::loaderDispatch->pSysman->Device->pfnGet                                      = loader::zesDeviceGet;
    loader::loaderDispatch->pSysman->Device->pfnSetOverclockWaiver                       = loader::zesDeviceSetOverclockWaiver;
    loader::loaderDispatch->pSysman->Device->pfnGetOverclockDomains                      = loader::zesDeviceGetOverclockDomains;
    loader::loaderDispatch->pSysman->Device->pfnGetOverclockControls                     = loader::zesDeviceGetOverclockControls;
    loader::loaderDispatch->pSysman->Device->pfnResetOverclockSettings                   = loader::zesDeviceResetOverclockSettings;
    loader::loaderDispatch->pSysman->Device->pfnReadOverclockState                       = loader::zesDeviceReadOverclockState;
    loader::loaderDispatch->pSysman->Device->pfnEnumOverclockDomains                     = loader::zesDeviceEnumOverclockDomains;
    loader::loaderDispatch->pSysman->Device->pfnResetExt                                 = loader::zesDeviceResetExt;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for DeviceExp table
__zedlllocal void ZE_APICALL
zesGetDeviceExpProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->DeviceExp->pfnEnumEnabledVFExp                         = loader::zesDeviceEnumEnabledVFExp;
    loader::loaderDispatch->pSysman->DeviceExp->pfnGetSubDevicePropertiesExp                = loader::zesDeviceGetSubDevicePropertiesExp;
    loader::loaderDispatch->pSysman->DeviceExp->pfnEnumActiveVFExp                          = loader::zesDeviceEnumActiveVFExp;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Driver table
__zedlllocal void ZE_APICALL
zesGetDriverProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Driver->pfnEventListen                              = loader::zesDriverEventListen;
    loader::loaderDispatch->pSysman->Driver->pfnEventListenEx                            = loader::zesDriverEventListenEx;
    loader::loaderDispatch->pSysman->Driver->pfnGet                                      = loader::zesDriverGet;
    loader::loaderDispatch->pSysman->Driver->pfnGetExtensionProperties                   = loader::zesDriverGetExtensionProperties;
    loader::loaderDispatch->pSysman->Driver->pfnGetExtensionFunctionAddress              = loader::zesDriverGetExtensionFunctionAddress;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for DriverExp table
__zedlllocal void ZE_APICALL
zesGetDriverExpProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->DriverExp->pfnGetDeviceByUuidExp                       = loader::zesDriverGetDeviceByUuidExp;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Diagnostics table
__zedlllocal void ZE_APICALL
zesGetDiagnosticsProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Diagnostics->pfnGetProperties                            = loader::zesDiagnosticsGetProperties;
    loader::loaderDispatch->pSysman->Diagnostics->pfnGetTests                                 = loader::zesDiagnosticsGetTests;
    loader::loaderDispatch->pSysman->Diagnostics->pfnRunTests                                 = loader::zesDiagnosticsRunTests;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Engine table
__zedlllocal void ZE_APICALL
zesGetEngineProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Engine->pfnGetProperties                            = loader::zesEngineGetProperties;
    loader::loaderDispatch->pSysman->Engine->pfnGetActivity                              = loader::zesEngineGetActivity;
    loader::loaderDispatch->pSysman->Engine->pfnGetActivityExt                           = loader::zesEngineGetActivityExt;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for FabricPort table
__zedlllocal void ZE_APICALL
zesGetFabricPortProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->FabricPort->pfnGetProperties                            = loader::zesFabricPortGetProperties;
    loader::loaderDispatch->pSysman->FabricPort->pfnGetLinkType                              = loader::zesFabricPortGetLinkType;
    loader::loaderDispatch->pSysman->FabricPort->pfnGetConfig                                = loader::zesFabricPortGetConfig;
    loader::loaderDispatch->pSysman->FabricPort->pfnSetConfig                                = loader::zesFabricPortSetConfig;
    loader::loaderDispatch->pSysman->FabricPort->pfnGetState                                 = loader::zesFabricPortGetState;
    loader::loaderDispatch->pSysman->FabricPort->pfnGetThroughput                            = loader::zesFabricPortGetThroughput;
    loader::loaderDispatch->pSysman->FabricPort->pfnGetFabricErrorCounters                   = loader::zesFabricPortGetFabricErrorCounters;
    loader::loaderDispatch->pSysman->FabricPort->pfnGetMultiPortThroughput                   = loader::zesFabricPortGetMultiPortThroughput;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Fan table
__zedlllocal void ZE_APICALL
zesGetFanProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Fan->pfnGetProperties                            = loader::zesFanGetProperties;
    loader::loaderDispatch->pSysman->Fan->pfnGetConfig                                = loader::zesFanGetConfig;
    loader::loaderDispatch->pSysman->Fan->pfnSetDefaultMode                           = loader::zesFanSetDefaultMode;
    loader::loaderDispatch->pSysman->Fan->pfnSetFixedSpeedMode                        = loader::zesFanSetFixedSpeedMode;
    loader::loaderDispatch->pSysman->Fan->pfnSetSpeedTableMode                        = loader::zesFanSetSpeedTableMode;
    loader::loaderDispatch->pSysman->Fan->pfnGetState                                 = loader::zesFanGetState;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Firmware table
__zedlllocal void ZE_APICALL
zesGetFirmwareProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Firmware->pfnGetProperties                            = loader::zesFirmwareGetProperties;
    loader::loaderDispatch->pSysman->Firmware->pfnFlash                                    = loader::zesFirmwareFlash;
    loader::loaderDispatch->pSysman->Firmware->pfnGetFlashProgress                         = loader::zesFirmwareGetFlashProgress;
    loader::loaderDispatch->pSysman->Firmware->pfnGetConsoleLogs                           = loader::zesFirmwareGetConsoleLogs;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for FirmwareExp table
__zedlllocal void ZE_APICALL
zesGetFirmwareExpProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->FirmwareExp->pfnGetSecurityVersionExp                    = loader::zesFirmwareGetSecurityVersionExp;
    loader::loaderDispatch->pSysman->FirmwareExp->pfnSetSecurityVersionExp                    = loader::zesFirmwareSetSecurityVersionExp;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Frequency table
__zedlllocal void ZE_APICALL
zesGetFrequencyProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Frequency->pfnGetProperties                            = loader::zesFrequencyGetProperties;
    loader::loaderDispatch->pSysman->Frequency->pfnGetAvailableClocks                       = loader::zesFrequencyGetAvailableClocks;
    loader::loaderDispatch->pSysman->Frequency->pfnGetRange                                 = loader::zesFrequencyGetRange;
    loader::loaderDispatch->pSysman->Frequency->pfnSetRange                                 = loader::zesFrequencySetRange;
    loader::loaderDispatch->pSysman->Frequency->pfnGetState                                 = loader::zesFrequencyGetState;
    loader::loaderDispatch->pSysman->Frequency->pfnGetThrottleTime                          = loader::zesFrequencyGetThrottleTime;
    loader::loaderDispatch->pSysman->Frequency->pfnOcGetCapabilities                        = loader::zesFrequencyOcGetCapabilities;
    loader::loaderDispatch->pSysman->Frequency->pfnOcGetFrequencyTarget                     = loader::zesFrequencyOcGetFrequencyTarget;
    loader::loaderDispatch->pSysman->Frequency->pfnOcSetFrequencyTarget                     = loader::zesFrequencyOcSetFrequencyTarget;
    loader::loaderDispatch->pSysman->Frequency->pfnOcGetVoltageTarget                       = loader::zesFrequencyOcGetVoltageTarget;
    loader::loaderDispatch->pSysman->Frequency->pfnOcSetVoltageTarget                       = loader::zesFrequencyOcSetVoltageTarget;
    loader::loaderDispatch->pSysman->Frequency->pfnOcSetMode                                = loader::zesFrequencyOcSetMode;
    loader::loaderDispatch->pSysman->Frequency->pfnOcGetMode                                = loader::zesFrequencyOcGetMode;
    loader::loaderDispatch->pSysman->Frequency->pfnOcGetIccMax                              = loader::zesFrequencyOcGetIccMax;
    loader::loaderDispatch->pSysman->Frequency->pfnOcSetIccMax                              = loader::zesFrequencyOcSetIccMax;
    loader::loaderDispatch->pSysman->Frequency->pfnOcGetTjMax                               = loader::zesFrequencyOcGetTjMax;
    loader::loaderDispatch->pSysman->Frequency->pfnOcSetTjMax                               = loader::zesFrequencyOcSetTjMax;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Led table
__zedlllocal void ZE_APICALL
zesGetLedProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Led->pfnGetProperties                            = loader::zesLedGetProperties;
    loader::loaderDispatch->pSysman->Led->pfnGetState                                 = loader::zesLedGetState;
    loader::loaderDispatch->pSysman->Led->pfnSetState                                 = loader::zesLedSetState;
    loader::loaderDispatch->pSysman->Led->pfnSetColor                                 = loader::zesLedSetColor;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Memory table
__zedlllocal void ZE_APICALL
zesGetMemoryProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Memory->pfnGetProperties                            = loader::zesMemoryGetProperties;
    loader::loaderDispatch->pSysman->Memory->pfnGetState                                 = loader::zesMemoryGetState;
    loader::loaderDispatch->pSysman->Memory->pfnGetBandwidth                             = loader::zesMemoryGetBandwidth;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Overclock table
__zedlllocal void ZE_APICALL
zesGetOverclockProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Overclock->pfnGetDomainProperties                      = loader::zesOverclockGetDomainProperties;
    loader::loaderDispatch->pSysman->Overclock->pfnGetDomainVFProperties                    = loader::zesOverclockGetDomainVFProperties;
    loader::loaderDispatch->pSysman->Overclock->pfnGetDomainControlProperties               = loader::zesOverclockGetDomainControlProperties;
    loader::loaderDispatch->pSysman->Overclock->pfnGetControlCurrentValue                   = loader::zesOverclockGetControlCurrentValue;
    loader::loaderDispatch->pSysman->Overclock->pfnGetControlPendingValue                   = loader::zesOverclockGetControlPendingValue;
    loader::loaderDispatch->pSysman->Overclock->pfnSetControlUserValue                      = loader::zesOverclockSetControlUserValue;
    loader::loaderDispatch->pSysman->Overclock->pfnGetControlState                          = loader::zesOverclockGetControlState;
    loader::loaderDispatch->pSysman->Overclock->pfnGetVFPointValues                         = loader::zesOverclockGetVFPointValues;
    loader::loaderDispatch->pSysman->Overclock->pfnSetVFPointValues                         = loader::zesOverclockSetVFPointValues;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for PerformanceFactor table
__zedlllocal void ZE_APICALL
zesGetPerformanceFactorProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->PerformanceFactor->pfnGetProperties                            = loader::zesPerformanceFactorGetProperties;
    loader::loaderDispatch->pSysman->PerformanceFactor->pfnGetConfig                                = loader::zesPerformanceFactorGetConfig;
    loader::loaderDispatch->pSysman->PerformanceFactor->pfnSetConfig                                = loader::zesPerformanceFactorSetConfig;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Power table
__zedlllocal void ZE_APICALL
zesGetPowerProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Power->pfnGetProperties                            = loader::zesPowerGetProperties;
    loader::loaderDispatch->pSysman->Power->pfnGetEnergyCounter                         = loader::zesPowerGetEnergyCounter;
    loader::loaderDispatch->pSysman->Power->pfnGetLimits                                = loader::zesPowerGetLimits;
    loader::loaderDispatch->pSysman->Power->pfnSetLimits                                = loader::zesPowerSetLimits;
    loader::loaderDispatch->pSysman->Power->pfnGetEnergyThreshold                       = loader::zesPowerGetEnergyThreshold;
    loader::loaderDispatch->pSysman->Power->pfnSetEnergyThreshold                       = loader::zesPowerSetEnergyThreshold;
    loader::loaderDispatch->pSysman->Power->pfnGetLimitsExt                             = loader::zesPowerGetLimitsExt;
    loader::loaderDispatch->pSysman->Power->pfnSetLimitsExt                             = loader::zesPowerSetLimitsExt;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Psu table
__zedlllocal void ZE_APICALL
zesGetPsuProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Psu->pfnGetProperties                            = loader::zesPsuGetProperties;
    loader::loaderDispatch->pSysman->Psu->pfnGetState                                 = loader::zesPsuGetState;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Ras table
__zedlllocal void ZE_APICALL
zesGetRasProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Ras->pfnGetProperties                            = loader::zesRasGetProperties;
    loader::loaderDispatch->pSysman->Ras->pfnGetConfig                                = loader::zesRasGetConfig;
    loader::loaderDispatch->pSysman->Ras->pfnSetConfig                                = loader::zesRasSetConfig;
    loader::loaderDispatch->pSysman->Ras->pfnGetState                                 = loader::zesRasGetState;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for RasExp table
__zedlllocal void ZE_APICALL
zesGetRasExpProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->RasExp->pfnGetStateExp                              = loader::zesRasGetStateExp;
    loader::loaderDispatch->pSysman->RasExp->pfnClearStateExp                            = loader::zesRasClearStateExp;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Scheduler table
__zedlllocal void ZE_APICALL
zesGetSchedulerProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Scheduler->pfnGetProperties                            = loader::zesSchedulerGetProperties;
    loader::loaderDispatch->pSysman->Scheduler->pfnGetCurrentMode                           = loader::zesSchedulerGetCurrentMode;
    loader::loaderDispatch->pSysman->Scheduler->pfnGetTimeoutModeProperties                 = loader::zesSchedulerGetTimeoutModeProperties;
    loader::loaderDispatch->pSysman->Scheduler->pfnGetTimesliceModeProperties               = loader::zesSchedulerGetTimesliceModeProperties;
    loader::loaderDispatch->pSysman->Scheduler->pfnSetTimeoutMode                           = loader::zesSchedulerSetTimeoutMode;
    loader::loaderDispatch->pSysman->Scheduler->pfnSetTimesliceMode                         = loader::zesSchedulerSetTimesliceMode;
    loader::loaderDispatch->pSysman->Scheduler->pfnSetExclusiveMode                         = loader::zesSchedulerSetExclusiveMode;
    loader::loaderDispatch->pSysman->Scheduler->pfnSetComputeUnitDebugMode                  = loader::zesSchedulerSetComputeUnitDebugMode;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Standby table
__zedlllocal void ZE_APICALL
zesGetStandbyProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Standby->pfnGetProperties                            = loader::zesStandbyGetProperties;
    loader::loaderDispatch->pSysman->Standby->pfnGetMode                                  = loader::zesStandbyGetMode;
    loader::loaderDispatch->pSysman->Standby->pfnSetMode                                  = loader::zesStandbySetMode;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for Temperature table
__zedlllocal void ZE_APICALL
zesGetTemperatureProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->Temperature->pfnGetProperties                            = loader::zesTemperatureGetProperties;
    loader::loaderDispatch->pSysman->Temperature->pfnGetConfig                                = loader::zesTemperatureGetConfig;
    loader::loaderDispatch->pSysman->Temperature->pfnSetConfig                                = loader::zesTemperatureSetConfig;
    loader::loaderDispatch->pSysman->Temperature->pfnGetState                                 = loader::zesTemperatureGetState;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief function for filling the legacy api pointers for VFManagementExp table
__zedlllocal void ZE_APICALL
zesGetVFManagementExpProcAddrTableLegacy()
{
    // return pointers to the Loader's Functions.
    loader::loaderDispatch->pSysman->VFManagementExp->pfnGetVFCapabilitiesExp                     = loader::zesVFManagementGetVFCapabilitiesExp;
    loader::loaderDispatch->pSysman->VFManagementExp->pfnGetVFMemoryUtilizationExp2               = loader::zesVFManagementGetVFMemoryUtilizationExp2;
    loader::loaderDispatch->pSysman->VFManagementExp->pfnGetVFEngineUtilizationExp2               = loader::zesVFManagementGetVFEngineUtilizationExp2;
    loader::loaderDispatch->pSysman->VFManagementExp->pfnGetVFCapabilitiesExp2                    = loader::zesVFManagementGetVFCapabilitiesExp2;
    loader::loaderDispatch->pSysman->VFManagementExp->pfnGetVFPropertiesExp                       = loader::zesVFManagementGetVFPropertiesExp;
    loader::loaderDispatch->pSysman->VFManagementExp->pfnGetVFMemoryUtilizationExp                = loader::zesVFManagementGetVFMemoryUtilizationExp;
    loader::loaderDispatch->pSysman->VFManagementExp->pfnGetVFEngineUtilizationExp                = loader::zesVFManagementGetVFEngineUtilizationExp;
    loader::loaderDispatch->pSysman->VFManagementExp->pfnSetVFTelemetryModeExp                    = loader::zesVFManagementSetVFTelemetryModeExp;
    loader::loaderDispatch->pSysman->VFManagementExp->pfnSetVFTelemetrySamplingIntervalExp        = loader::zesVFManagementSetVFTelemetrySamplingIntervalExp;
}


///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_global_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetGlobalProcAddrTable") );
        if(!getTable) 
        {
            atLeastOneDriverValid = true;
            //It is valid to not have this proc addr table
            continue; 
        }
        auto getTableResult = getTable( version, &drv.dditable.zes.Global);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Global = new zes_global_dditable_t;
            if (version >= ZE_API_VERSION_1_5) {
            pDdiTable->pfnInit                                     = loader::zesInit;
            }
            zesGetGlobalProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Global;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetGlobalProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetDeviceProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.Device);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Device = new zes_device_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesDeviceGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesDeviceGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetState                                 = loader_driver_ddi::zesDeviceGetState;
            } else {
                pDdiTable->pfnGetState                                 = loader::zesDeviceGetState;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnReset                                    = loader_driver_ddi::zesDeviceReset;
            } else {
                pDdiTable->pfnReset                                    = loader::zesDeviceReset;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnProcessesGetState                        = loader_driver_ddi::zesDeviceProcessesGetState;
            } else {
                pDdiTable->pfnProcessesGetState                        = loader::zesDeviceProcessesGetState;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnPciGetProperties                         = loader_driver_ddi::zesDevicePciGetProperties;
            } else {
                pDdiTable->pfnPciGetProperties                         = loader::zesDevicePciGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnPciGetState                              = loader_driver_ddi::zesDevicePciGetState;
            } else {
                pDdiTable->pfnPciGetState                              = loader::zesDevicePciGetState;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnPciGetBars                               = loader_driver_ddi::zesDevicePciGetBars;
            } else {
                pDdiTable->pfnPciGetBars                               = loader::zesDevicePciGetBars;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnPciGetStats                              = loader_driver_ddi::zesDevicePciGetStats;
            } else {
                pDdiTable->pfnPciGetStats                              = loader::zesDevicePciGetStats;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumDiagnosticTestSuites                 = loader_driver_ddi::zesDeviceEnumDiagnosticTestSuites;
            } else {
                pDdiTable->pfnEnumDiagnosticTestSuites                 = loader::zesDeviceEnumDiagnosticTestSuites;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumEngineGroups                         = loader_driver_ddi::zesDeviceEnumEngineGroups;
            } else {
                pDdiTable->pfnEnumEngineGroups                         = loader::zesDeviceEnumEngineGroups;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEventRegister                            = loader_driver_ddi::zesDeviceEventRegister;
            } else {
                pDdiTable->pfnEventRegister                            = loader::zesDeviceEventRegister;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumFabricPorts                          = loader_driver_ddi::zesDeviceEnumFabricPorts;
            } else {
                pDdiTable->pfnEnumFabricPorts                          = loader::zesDeviceEnumFabricPorts;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumFans                                 = loader_driver_ddi::zesDeviceEnumFans;
            } else {
                pDdiTable->pfnEnumFans                                 = loader::zesDeviceEnumFans;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumFirmwares                            = loader_driver_ddi::zesDeviceEnumFirmwares;
            } else {
                pDdiTable->pfnEnumFirmwares                            = loader::zesDeviceEnumFirmwares;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumFrequencyDomains                     = loader_driver_ddi::zesDeviceEnumFrequencyDomains;
            } else {
                pDdiTable->pfnEnumFrequencyDomains                     = loader::zesDeviceEnumFrequencyDomains;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumLeds                                 = loader_driver_ddi::zesDeviceEnumLeds;
            } else {
                pDdiTable->pfnEnumLeds                                 = loader::zesDeviceEnumLeds;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumMemoryModules                        = loader_driver_ddi::zesDeviceEnumMemoryModules;
            } else {
                pDdiTable->pfnEnumMemoryModules                        = loader::zesDeviceEnumMemoryModules;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumPerformanceFactorDomains             = loader_driver_ddi::zesDeviceEnumPerformanceFactorDomains;
            } else {
                pDdiTable->pfnEnumPerformanceFactorDomains             = loader::zesDeviceEnumPerformanceFactorDomains;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumPowerDomains                         = loader_driver_ddi::zesDeviceEnumPowerDomains;
            } else {
                pDdiTable->pfnEnumPowerDomains                         = loader::zesDeviceEnumPowerDomains;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetCardPowerDomain                       = loader_driver_ddi::zesDeviceGetCardPowerDomain;
            } else {
                pDdiTable->pfnGetCardPowerDomain                       = loader::zesDeviceGetCardPowerDomain;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumPsus                                 = loader_driver_ddi::zesDeviceEnumPsus;
            } else {
                pDdiTable->pfnEnumPsus                                 = loader::zesDeviceEnumPsus;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumRasErrorSets                         = loader_driver_ddi::zesDeviceEnumRasErrorSets;
            } else {
                pDdiTable->pfnEnumRasErrorSets                         = loader::zesDeviceEnumRasErrorSets;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumSchedulers                           = loader_driver_ddi::zesDeviceEnumSchedulers;
            } else {
                pDdiTable->pfnEnumSchedulers                           = loader::zesDeviceEnumSchedulers;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumStandbyDomains                       = loader_driver_ddi::zesDeviceEnumStandbyDomains;
            } else {
                pDdiTable->pfnEnumStandbyDomains                       = loader::zesDeviceEnumStandbyDomains;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumTemperatureSensors                   = loader_driver_ddi::zesDeviceEnumTemperatureSensors;
            } else {
                pDdiTable->pfnEnumTemperatureSensors                   = loader::zesDeviceEnumTemperatureSensors;
            }
            }
            if (version >= ZE_API_VERSION_1_4) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEccAvailable                             = loader_driver_ddi::zesDeviceEccAvailable;
            } else {
                pDdiTable->pfnEccAvailable                             = loader::zesDeviceEccAvailable;
            }
            }
            if (version >= ZE_API_VERSION_1_4) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEccConfigurable                          = loader_driver_ddi::zesDeviceEccConfigurable;
            } else {
                pDdiTable->pfnEccConfigurable                          = loader::zesDeviceEccConfigurable;
            }
            }
            if (version >= ZE_API_VERSION_1_4) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetEccState                              = loader_driver_ddi::zesDeviceGetEccState;
            } else {
                pDdiTable->pfnGetEccState                              = loader::zesDeviceGetEccState;
            }
            }
            if (version >= ZE_API_VERSION_1_4) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetEccState                              = loader_driver_ddi::zesDeviceSetEccState;
            } else {
                pDdiTable->pfnSetEccState                              = loader::zesDeviceSetEccState;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGet                                      = loader_driver_ddi::zesDeviceGet;
            } else {
                pDdiTable->pfnGet                                      = loader::zesDeviceGet;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetOverclockWaiver                       = loader_driver_ddi::zesDeviceSetOverclockWaiver;
            } else {
                pDdiTable->pfnSetOverclockWaiver                       = loader::zesDeviceSetOverclockWaiver;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetOverclockDomains                      = loader_driver_ddi::zesDeviceGetOverclockDomains;
            } else {
                pDdiTable->pfnGetOverclockDomains                      = loader::zesDeviceGetOverclockDomains;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetOverclockControls                     = loader_driver_ddi::zesDeviceGetOverclockControls;
            } else {
                pDdiTable->pfnGetOverclockControls                     = loader::zesDeviceGetOverclockControls;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnResetOverclockSettings                   = loader_driver_ddi::zesDeviceResetOverclockSettings;
            } else {
                pDdiTable->pfnResetOverclockSettings                   = loader::zesDeviceResetOverclockSettings;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnReadOverclockState                       = loader_driver_ddi::zesDeviceReadOverclockState;
            } else {
                pDdiTable->pfnReadOverclockState                       = loader::zesDeviceReadOverclockState;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumOverclockDomains                     = loader_driver_ddi::zesDeviceEnumOverclockDomains;
            } else {
                pDdiTable->pfnEnumOverclockDomains                     = loader::zesDeviceEnumOverclockDomains;
            }
            }
            if (version >= ZE_API_VERSION_1_7) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnResetExt                                 = loader_driver_ddi::zesDeviceResetExt;
            } else {
                pDdiTable->pfnResetExt                                 = loader::zesDeviceResetExt;
            }
            }
            zesGetDeviceProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Device;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetDeviceProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetDeviceProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's DeviceExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetDeviceExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_device_exp_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetDeviceExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetDeviceExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.zes.DeviceExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->DeviceExp = new zes_device_exp_dditable_t;
            if (version >= ZE_API_VERSION_1_10) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumEnabledVFExp                         = loader_driver_ddi::zesDeviceEnumEnabledVFExp;
            } else {
                pDdiTable->pfnEnumEnabledVFExp                         = loader::zesDeviceEnumEnabledVFExp;
            }
            }
            if (version >= ZE_API_VERSION_1_9) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetSubDevicePropertiesExp                = loader_driver_ddi::zesDeviceGetSubDevicePropertiesExp;
            } else {
                pDdiTable->pfnGetSubDevicePropertiesExp                = loader::zesDeviceGetSubDevicePropertiesExp;
            }
            }
            if (version >= ZE_API_VERSION_1_9) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEnumActiveVFExp                          = loader_driver_ddi::zesDeviceEnumActiveVFExp;
            } else {
                pDdiTable->pfnEnumActiveVFExp                          = loader::zesDeviceEnumActiveVFExp;
            }
            }
            zesGetDeviceExpProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.DeviceExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetDeviceExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetDeviceExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Driver table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetDriverProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_driver_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetDriverProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetDriverProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.Driver);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Driver = new zes_driver_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEventListen                              = loader_driver_ddi::zesDriverEventListen;
            } else {
                pDdiTable->pfnEventListen                              = loader::zesDriverEventListen;
            }
            }
            if (version >= ZE_API_VERSION_1_1) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnEventListenEx                            = loader_driver_ddi::zesDriverEventListenEx;
            } else {
                pDdiTable->pfnEventListenEx                            = loader::zesDriverEventListenEx;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            pDdiTable->pfnGet                                      = loader::zesDriverGet;
            }
            if (version >= ZE_API_VERSION_1_8) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetExtensionProperties                   = loader_driver_ddi::zesDriverGetExtensionProperties;
            } else {
                pDdiTable->pfnGetExtensionProperties                   = loader::zesDriverGetExtensionProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_8) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetExtensionFunctionAddress              = loader_driver_ddi::zesDriverGetExtensionFunctionAddress;
            } else {
                pDdiTable->pfnGetExtensionFunctionAddress              = loader::zesDriverGetExtensionFunctionAddress;
            }
            }
            zesGetDriverProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Driver;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetDriverProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetDriverProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's DriverExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetDriverExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_driver_exp_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetDriverExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetDriverExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.zes.DriverExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->DriverExp = new zes_driver_exp_dditable_t;
            if (version >= ZE_API_VERSION_1_9) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetDeviceByUuidExp                       = loader_driver_ddi::zesDriverGetDeviceByUuidExp;
            } else {
                pDdiTable->pfnGetDeviceByUuidExp                       = loader::zesDriverGetDeviceByUuidExp;
            }
            }
            zesGetDriverExpProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.DriverExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetDriverExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetDriverExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Diagnostics table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetDiagnosticsProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_diagnostics_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetDiagnosticsProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetDiagnosticsProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.Diagnostics);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Diagnostics = new zes_diagnostics_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesDiagnosticsGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesDiagnosticsGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetTests                                 = loader_driver_ddi::zesDiagnosticsGetTests;
            } else {
                pDdiTable->pfnGetTests                                 = loader::zesDiagnosticsGetTests;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnRunTests                                 = loader_driver_ddi::zesDiagnosticsRunTests;
            } else {
                pDdiTable->pfnRunTests                                 = loader::zesDiagnosticsRunTests;
            }
            }
            zesGetDiagnosticsProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Diagnostics;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetDiagnosticsProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetDiagnosticsProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Engine table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetEngineProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_engine_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetEngineProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetEngineProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.Engine);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Engine = new zes_engine_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesEngineGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesEngineGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_7) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetActivity                              = loader_driver_ddi::zesEngineGetActivity;
            } else {
                pDdiTable->pfnGetActivity                              = loader::zesEngineGetActivity;
            }
            }
            if (version >= ZE_API_VERSION_1_7) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetActivityExt                           = loader_driver_ddi::zesEngineGetActivityExt;
            } else {
                pDdiTable->pfnGetActivityExt                           = loader::zesEngineGetActivityExt;
            }
            }
            zesGetEngineProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Engine;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetEngineProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetEngineProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FabricPort table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetFabricPortProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_fabric_port_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetFabricPortProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetFabricPortProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.FabricPort);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->FabricPort = new zes_fabric_port_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesFabricPortGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesFabricPortGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetLinkType                              = loader_driver_ddi::zesFabricPortGetLinkType;
            } else {
                pDdiTable->pfnGetLinkType                              = loader::zesFabricPortGetLinkType;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetConfig                                = loader_driver_ddi::zesFabricPortGetConfig;
            } else {
                pDdiTable->pfnGetConfig                                = loader::zesFabricPortGetConfig;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetConfig                                = loader_driver_ddi::zesFabricPortSetConfig;
            } else {
                pDdiTable->pfnSetConfig                                = loader::zesFabricPortSetConfig;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetState                                 = loader_driver_ddi::zesFabricPortGetState;
            } else {
                pDdiTable->pfnGetState                                 = loader::zesFabricPortGetState;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetThroughput                            = loader_driver_ddi::zesFabricPortGetThroughput;
            } else {
                pDdiTable->pfnGetThroughput                            = loader::zesFabricPortGetThroughput;
            }
            }
            if (version >= ZE_API_VERSION_1_7) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetFabricErrorCounters                   = loader_driver_ddi::zesFabricPortGetFabricErrorCounters;
            } else {
                pDdiTable->pfnGetFabricErrorCounters                   = loader::zesFabricPortGetFabricErrorCounters;
            }
            }
            if (version >= ZE_API_VERSION_1_7) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetMultiPortThroughput                   = loader_driver_ddi::zesFabricPortGetMultiPortThroughput;
            } else {
                pDdiTable->pfnGetMultiPortThroughput                   = loader::zesFabricPortGetMultiPortThroughput;
            }
            }
            zesGetFabricPortProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.FabricPort;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetFabricPortProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetFabricPortProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fan table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetFanProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_fan_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetFanProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetFanProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.Fan);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Fan = new zes_fan_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesFanGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesFanGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetConfig                                = loader_driver_ddi::zesFanGetConfig;
            } else {
                pDdiTable->pfnGetConfig                                = loader::zesFanGetConfig;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetDefaultMode                           = loader_driver_ddi::zesFanSetDefaultMode;
            } else {
                pDdiTable->pfnSetDefaultMode                           = loader::zesFanSetDefaultMode;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetFixedSpeedMode                        = loader_driver_ddi::zesFanSetFixedSpeedMode;
            } else {
                pDdiTable->pfnSetFixedSpeedMode                        = loader::zesFanSetFixedSpeedMode;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetSpeedTableMode                        = loader_driver_ddi::zesFanSetSpeedTableMode;
            } else {
                pDdiTable->pfnSetSpeedTableMode                        = loader::zesFanSetSpeedTableMode;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetState                                 = loader_driver_ddi::zesFanGetState;
            } else {
                pDdiTable->pfnGetState                                 = loader::zesFanGetState;
            }
            }
            zesGetFanProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Fan;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetFanProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetFanProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Firmware table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetFirmwareProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_firmware_dditable_t* pDdiTable              ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetFirmwareProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetFirmwareProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.Firmware);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Firmware = new zes_firmware_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesFirmwareGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesFirmwareGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnFlash                                    = loader_driver_ddi::zesFirmwareFlash;
            } else {
                pDdiTable->pfnFlash                                    = loader::zesFirmwareFlash;
            }
            }
            if (version >= ZE_API_VERSION_1_8) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetFlashProgress                         = loader_driver_ddi::zesFirmwareGetFlashProgress;
            } else {
                pDdiTable->pfnGetFlashProgress                         = loader::zesFirmwareGetFlashProgress;
            }
            }
            if (version >= ZE_API_VERSION_1_9) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetConsoleLogs                           = loader_driver_ddi::zesFirmwareGetConsoleLogs;
            } else {
                pDdiTable->pfnGetConsoleLogs                           = loader::zesFirmwareGetConsoleLogs;
            }
            }
            zesGetFirmwareProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Firmware;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetFirmwareProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetFirmwareProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FirmwareExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetFirmwareExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_firmware_exp_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetFirmwareExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetFirmwareExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.zes.FirmwareExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->FirmwareExp = new zes_firmware_exp_dditable_t;
            if (version >= ZE_API_VERSION_1_9) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetSecurityVersionExp                    = loader_driver_ddi::zesFirmwareGetSecurityVersionExp;
            } else {
                pDdiTable->pfnGetSecurityVersionExp                    = loader::zesFirmwareGetSecurityVersionExp;
            }
            }
            if (version >= ZE_API_VERSION_1_9) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetSecurityVersionExp                    = loader_driver_ddi::zesFirmwareSetSecurityVersionExp;
            } else {
                pDdiTable->pfnSetSecurityVersionExp                    = loader::zesFirmwareSetSecurityVersionExp;
            }
            }
            zesGetFirmwareExpProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.FirmwareExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetFirmwareExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetFirmwareExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Frequency table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetFrequencyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_frequency_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetFrequencyProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetFrequencyProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.Frequency);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Frequency = new zes_frequency_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesFrequencyGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesFrequencyGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetAvailableClocks                       = loader_driver_ddi::zesFrequencyGetAvailableClocks;
            } else {
                pDdiTable->pfnGetAvailableClocks                       = loader::zesFrequencyGetAvailableClocks;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetRange                                 = loader_driver_ddi::zesFrequencyGetRange;
            } else {
                pDdiTable->pfnGetRange                                 = loader::zesFrequencyGetRange;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetRange                                 = loader_driver_ddi::zesFrequencySetRange;
            } else {
                pDdiTable->pfnSetRange                                 = loader::zesFrequencySetRange;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetState                                 = loader_driver_ddi::zesFrequencyGetState;
            } else {
                pDdiTable->pfnGetState                                 = loader::zesFrequencyGetState;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetThrottleTime                          = loader_driver_ddi::zesFrequencyGetThrottleTime;
            } else {
                pDdiTable->pfnGetThrottleTime                          = loader::zesFrequencyGetThrottleTime;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnOcGetCapabilities                        = loader_driver_ddi::zesFrequencyOcGetCapabilities;
            } else {
                pDdiTable->pfnOcGetCapabilities                        = loader::zesFrequencyOcGetCapabilities;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnOcGetFrequencyTarget                     = loader_driver_ddi::zesFrequencyOcGetFrequencyTarget;
            } else {
                pDdiTable->pfnOcGetFrequencyTarget                     = loader::zesFrequencyOcGetFrequencyTarget;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnOcSetFrequencyTarget                     = loader_driver_ddi::zesFrequencyOcSetFrequencyTarget;
            } else {
                pDdiTable->pfnOcSetFrequencyTarget                     = loader::zesFrequencyOcSetFrequencyTarget;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnOcGetVoltageTarget                       = loader_driver_ddi::zesFrequencyOcGetVoltageTarget;
            } else {
                pDdiTable->pfnOcGetVoltageTarget                       = loader::zesFrequencyOcGetVoltageTarget;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnOcSetVoltageTarget                       = loader_driver_ddi::zesFrequencyOcSetVoltageTarget;
            } else {
                pDdiTable->pfnOcSetVoltageTarget                       = loader::zesFrequencyOcSetVoltageTarget;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnOcSetMode                                = loader_driver_ddi::zesFrequencyOcSetMode;
            } else {
                pDdiTable->pfnOcSetMode                                = loader::zesFrequencyOcSetMode;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnOcGetMode                                = loader_driver_ddi::zesFrequencyOcGetMode;
            } else {
                pDdiTable->pfnOcGetMode                                = loader::zesFrequencyOcGetMode;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnOcGetIccMax                              = loader_driver_ddi::zesFrequencyOcGetIccMax;
            } else {
                pDdiTable->pfnOcGetIccMax                              = loader::zesFrequencyOcGetIccMax;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnOcSetIccMax                              = loader_driver_ddi::zesFrequencyOcSetIccMax;
            } else {
                pDdiTable->pfnOcSetIccMax                              = loader::zesFrequencyOcSetIccMax;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnOcGetTjMax                               = loader_driver_ddi::zesFrequencyOcGetTjMax;
            } else {
                pDdiTable->pfnOcGetTjMax                               = loader::zesFrequencyOcGetTjMax;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnOcSetTjMax                               = loader_driver_ddi::zesFrequencyOcSetTjMax;
            } else {
                pDdiTable->pfnOcSetTjMax                               = loader::zesFrequencyOcSetTjMax;
            }
            }
            zesGetFrequencyProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Frequency;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetFrequencyProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetFrequencyProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Led table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetLedProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_led_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetLedProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetLedProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.Led);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Led = new zes_led_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesLedGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesLedGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetState                                 = loader_driver_ddi::zesLedGetState;
            } else {
                pDdiTable->pfnGetState                                 = loader::zesLedGetState;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetState                                 = loader_driver_ddi::zesLedSetState;
            } else {
                pDdiTable->pfnSetState                                 = loader::zesLedSetState;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetColor                                 = loader_driver_ddi::zesLedSetColor;
            } else {
                pDdiTable->pfnSetColor                                 = loader::zesLedSetColor;
            }
            }
            zesGetLedProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Led;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetLedProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetLedProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Memory table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetMemoryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_memory_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetMemoryProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetMemoryProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.Memory);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Memory = new zes_memory_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesMemoryGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesMemoryGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetState                                 = loader_driver_ddi::zesMemoryGetState;
            } else {
                pDdiTable->pfnGetState                                 = loader::zesMemoryGetState;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetBandwidth                             = loader_driver_ddi::zesMemoryGetBandwidth;
            } else {
                pDdiTable->pfnGetBandwidth                             = loader::zesMemoryGetBandwidth;
            }
            }
            zesGetMemoryProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Memory;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetMemoryProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetMemoryProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Overclock table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetOverclockProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_overclock_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetOverclockProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetOverclockProcAddrTable") );
        if(!getTable) 
        {
            atLeastOneDriverValid = true;
            //It is valid to not have this proc addr table
            continue; 
        }
        auto getTableResult = getTable( version, &drv.dditable.zes.Overclock);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Overclock = new zes_overclock_dditable_t;
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetDomainProperties                      = loader_driver_ddi::zesOverclockGetDomainProperties;
            } else {
                pDdiTable->pfnGetDomainProperties                      = loader::zesOverclockGetDomainProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetDomainVFProperties                    = loader_driver_ddi::zesOverclockGetDomainVFProperties;
            } else {
                pDdiTable->pfnGetDomainVFProperties                    = loader::zesOverclockGetDomainVFProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetDomainControlProperties               = loader_driver_ddi::zesOverclockGetDomainControlProperties;
            } else {
                pDdiTable->pfnGetDomainControlProperties               = loader::zesOverclockGetDomainControlProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetControlCurrentValue                   = loader_driver_ddi::zesOverclockGetControlCurrentValue;
            } else {
                pDdiTable->pfnGetControlCurrentValue                   = loader::zesOverclockGetControlCurrentValue;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetControlPendingValue                   = loader_driver_ddi::zesOverclockGetControlPendingValue;
            } else {
                pDdiTable->pfnGetControlPendingValue                   = loader::zesOverclockGetControlPendingValue;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetControlUserValue                      = loader_driver_ddi::zesOverclockSetControlUserValue;
            } else {
                pDdiTable->pfnSetControlUserValue                      = loader::zesOverclockSetControlUserValue;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetControlState                          = loader_driver_ddi::zesOverclockGetControlState;
            } else {
                pDdiTable->pfnGetControlState                          = loader::zesOverclockGetControlState;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetVFPointValues                         = loader_driver_ddi::zesOverclockGetVFPointValues;
            } else {
                pDdiTable->pfnGetVFPointValues                         = loader::zesOverclockGetVFPointValues;
            }
            }
            if (version >= ZE_API_VERSION_1_5) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetVFPointValues                         = loader_driver_ddi::zesOverclockSetVFPointValues;
            } else {
                pDdiTable->pfnSetVFPointValues                         = loader::zesOverclockSetVFPointValues;
            }
            }
            zesGetOverclockProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Overclock;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetOverclockProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetOverclockProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's PerformanceFactor table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetPerformanceFactorProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_performance_factor_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetPerformanceFactorProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetPerformanceFactorProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.PerformanceFactor);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->PerformanceFactor = new zes_performance_factor_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesPerformanceFactorGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesPerformanceFactorGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetConfig                                = loader_driver_ddi::zesPerformanceFactorGetConfig;
            } else {
                pDdiTable->pfnGetConfig                                = loader::zesPerformanceFactorGetConfig;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetConfig                                = loader_driver_ddi::zesPerformanceFactorSetConfig;
            } else {
                pDdiTable->pfnSetConfig                                = loader::zesPerformanceFactorSetConfig;
            }
            }
            zesGetPerformanceFactorProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.PerformanceFactor;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetPerformanceFactorProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetPerformanceFactorProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Power table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetPowerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_power_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetPowerProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetPowerProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.Power);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Power = new zes_power_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesPowerGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesPowerGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetEnergyCounter                         = loader_driver_ddi::zesPowerGetEnergyCounter;
            } else {
                pDdiTable->pfnGetEnergyCounter                         = loader::zesPowerGetEnergyCounter;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetLimits                                = loader_driver_ddi::zesPowerGetLimits;
            } else {
                pDdiTable->pfnGetLimits                                = loader::zesPowerGetLimits;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetLimits                                = loader_driver_ddi::zesPowerSetLimits;
            } else {
                pDdiTable->pfnSetLimits                                = loader::zesPowerSetLimits;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetEnergyThreshold                       = loader_driver_ddi::zesPowerGetEnergyThreshold;
            } else {
                pDdiTable->pfnGetEnergyThreshold                       = loader::zesPowerGetEnergyThreshold;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetEnergyThreshold                       = loader_driver_ddi::zesPowerSetEnergyThreshold;
            } else {
                pDdiTable->pfnSetEnergyThreshold                       = loader::zesPowerSetEnergyThreshold;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetLimitsExt                             = loader_driver_ddi::zesPowerGetLimitsExt;
            } else {
                pDdiTable->pfnGetLimitsExt                             = loader::zesPowerGetLimitsExt;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetLimitsExt                             = loader_driver_ddi::zesPowerSetLimitsExt;
            } else {
                pDdiTable->pfnSetLimitsExt                             = loader::zesPowerSetLimitsExt;
            }
            }
            zesGetPowerProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Power;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetPowerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetPowerProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Psu table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetPsuProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_psu_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetPsuProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetPsuProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.Psu);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Psu = new zes_psu_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesPsuGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesPsuGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetState                                 = loader_driver_ddi::zesPsuGetState;
            } else {
                pDdiTable->pfnGetState                                 = loader::zesPsuGetState;
            }
            }
            zesGetPsuProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Psu;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetPsuProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetPsuProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Ras table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetRasProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_ras_dditable_t* pDdiTable                   ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetRasProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetRasProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.Ras);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Ras = new zes_ras_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesRasGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesRasGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetConfig                                = loader_driver_ddi::zesRasGetConfig;
            } else {
                pDdiTable->pfnGetConfig                                = loader::zesRasGetConfig;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetConfig                                = loader_driver_ddi::zesRasSetConfig;
            } else {
                pDdiTable->pfnSetConfig                                = loader::zesRasSetConfig;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetState                                 = loader_driver_ddi::zesRasGetState;
            } else {
                pDdiTable->pfnGetState                                 = loader::zesRasGetState;
            }
            }
            zesGetRasProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Ras;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetRasProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetRasProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's RasExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetRasExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_ras_exp_dditable_t* pDdiTable               ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetRasExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetRasExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.zes.RasExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->RasExp = new zes_ras_exp_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetStateExp                              = loader_driver_ddi::zesRasGetStateExp;
            } else {
                pDdiTable->pfnGetStateExp                              = loader::zesRasGetStateExp;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnClearStateExp                            = loader_driver_ddi::zesRasClearStateExp;
            } else {
                pDdiTable->pfnClearStateExp                            = loader::zesRasClearStateExp;
            }
            }
            zesGetRasExpProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.RasExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetRasExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetRasExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Scheduler table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetSchedulerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_scheduler_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetSchedulerProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetSchedulerProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.Scheduler);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Scheduler = new zes_scheduler_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesSchedulerGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesSchedulerGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetCurrentMode                           = loader_driver_ddi::zesSchedulerGetCurrentMode;
            } else {
                pDdiTable->pfnGetCurrentMode                           = loader::zesSchedulerGetCurrentMode;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetTimeoutModeProperties                 = loader_driver_ddi::zesSchedulerGetTimeoutModeProperties;
            } else {
                pDdiTable->pfnGetTimeoutModeProperties                 = loader::zesSchedulerGetTimeoutModeProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetTimesliceModeProperties               = loader_driver_ddi::zesSchedulerGetTimesliceModeProperties;
            } else {
                pDdiTable->pfnGetTimesliceModeProperties               = loader::zesSchedulerGetTimesliceModeProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetTimeoutMode                           = loader_driver_ddi::zesSchedulerSetTimeoutMode;
            } else {
                pDdiTable->pfnSetTimeoutMode                           = loader::zesSchedulerSetTimeoutMode;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetTimesliceMode                         = loader_driver_ddi::zesSchedulerSetTimesliceMode;
            } else {
                pDdiTable->pfnSetTimesliceMode                         = loader::zesSchedulerSetTimesliceMode;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetExclusiveMode                         = loader_driver_ddi::zesSchedulerSetExclusiveMode;
            } else {
                pDdiTable->pfnSetExclusiveMode                         = loader::zesSchedulerSetExclusiveMode;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetComputeUnitDebugMode                  = loader_driver_ddi::zesSchedulerSetComputeUnitDebugMode;
            } else {
                pDdiTable->pfnSetComputeUnitDebugMode                  = loader::zesSchedulerSetComputeUnitDebugMode;
            }
            }
            zesGetSchedulerProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Scheduler;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetSchedulerProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetSchedulerProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Standby table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetStandbyProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_standby_dditable_t* pDdiTable               ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetStandbyProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetStandbyProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.Standby);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Standby = new zes_standby_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesStandbyGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesStandbyGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetMode                                  = loader_driver_ddi::zesStandbyGetMode;
            } else {
                pDdiTable->pfnGetMode                                  = loader::zesStandbyGetMode;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetMode                                  = loader_driver_ddi::zesStandbySetMode;
            } else {
                pDdiTable->pfnSetMode                                  = loader::zesStandbySetMode;
            }
            }
            zesGetStandbyProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Standby;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetStandbyProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetStandbyProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Temperature table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetTemperatureProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_temperature_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    bool atLeastOneDriverValid = false;
    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetTemperatureProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetTemperatureProcAddrTable") );
        if(!getTable) 
            continue; 
        auto getTableResult = getTable( version, &drv.dditable.zes.Temperature);
        if(getTableResult == ZE_RESULT_SUCCESS) {
            atLeastOneDriverValid = true;
            loader::context->configured_version = version;
        } else
            drv.initStatus = getTableResult;
    }

    if(!atLeastOneDriverValid)
        result = ZE_RESULT_ERROR_UNINITIALIZED;
    else
        result = ZE_RESULT_SUCCESS;

    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->Temperature = new zes_temperature_dditable_t;
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetProperties                            = loader_driver_ddi::zesTemperatureGetProperties;
            } else {
                pDdiTable->pfnGetProperties                            = loader::zesTemperatureGetProperties;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetConfig                                = loader_driver_ddi::zesTemperatureGetConfig;
            } else {
                pDdiTable->pfnGetConfig                                = loader::zesTemperatureGetConfig;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetConfig                                = loader_driver_ddi::zesTemperatureSetConfig;
            } else {
                pDdiTable->pfnSetConfig                                = loader::zesTemperatureSetConfig;
            }
            }
            if (version >= ZE_API_VERSION_1_0) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetState                                 = loader_driver_ddi::zesTemperatureGetState;
            } else {
                pDdiTable->pfnGetState                                 = loader::zesTemperatureGetState;
            }
            }
            zesGetTemperatureProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.Temperature;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetTemperatureProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetTemperatureProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's VFManagementExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetVFManagementExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_vf_management_exp_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    )
{
    if( loader::context->sysmanInstanceDrivers->size() < 1 ) {
        return ZE_RESULT_ERROR_UNINITIALIZED;
    }

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if( loader::context->version < version )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    // Load the device-driver DDI tables
    for( auto& drv : *loader::context->sysmanInstanceDrivers )
    {
        if(drv.initStatus != ZE_RESULT_SUCCESS)
            continue;
        auto getTable = reinterpret_cast<zes_pfnGetVFManagementExpProcAddrTable_t>(
            GET_FUNCTION_PTR( drv.handle, "zesGetVFManagementExpProcAddrTable") );
        if(!getTable) 
            continue; 
        result = getTable( version, &drv.dditable.zes.VFManagementExp);
    }


    if( ZE_RESULT_SUCCESS == result )
    {
        if( ( loader::context->sysmanInstanceDrivers->size() > 1 ) || loader::context->forceIntercept )
        {
            // return pointers to loader's DDIs
            loader::loaderDispatch->pSysman->VFManagementExp = new zes_vf_management_exp_dditable_t;
            if (version >= ZE_API_VERSION_1_10) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetVFCapabilitiesExp                     = loader_driver_ddi::zesVFManagementGetVFCapabilitiesExp;
            } else {
                pDdiTable->pfnGetVFCapabilitiesExp                     = loader::zesVFManagementGetVFCapabilitiesExp;
            }
            }
            if (version >= ZE_API_VERSION_1_10) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetVFMemoryUtilizationExp2               = loader_driver_ddi::zesVFManagementGetVFMemoryUtilizationExp2;
            } else {
                pDdiTable->pfnGetVFMemoryUtilizationExp2               = loader::zesVFManagementGetVFMemoryUtilizationExp2;
            }
            }
            if (version >= ZE_API_VERSION_1_10) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetVFEngineUtilizationExp2               = loader_driver_ddi::zesVFManagementGetVFEngineUtilizationExp2;
            } else {
                pDdiTable->pfnGetVFEngineUtilizationExp2               = loader::zesVFManagementGetVFEngineUtilizationExp2;
            }
            }
            if (version >= ZE_API_VERSION_1_12) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetVFCapabilitiesExp2                    = loader_driver_ddi::zesVFManagementGetVFCapabilitiesExp2;
            } else {
                pDdiTable->pfnGetVFCapabilitiesExp2                    = loader::zesVFManagementGetVFCapabilitiesExp2;
            }
            }
            if (version >= ZE_API_VERSION_1_9) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetVFPropertiesExp                       = loader_driver_ddi::zesVFManagementGetVFPropertiesExp;
            } else {
                pDdiTable->pfnGetVFPropertiesExp                       = loader::zesVFManagementGetVFPropertiesExp;
            }
            }
            if (version >= ZE_API_VERSION_1_9) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetVFMemoryUtilizationExp                = loader_driver_ddi::zesVFManagementGetVFMemoryUtilizationExp;
            } else {
                pDdiTable->pfnGetVFMemoryUtilizationExp                = loader::zesVFManagementGetVFMemoryUtilizationExp;
            }
            }
            if (version >= ZE_API_VERSION_1_9) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnGetVFEngineUtilizationExp                = loader_driver_ddi::zesVFManagementGetVFEngineUtilizationExp;
            } else {
                pDdiTable->pfnGetVFEngineUtilizationExp                = loader::zesVFManagementGetVFEngineUtilizationExp;
            }
            }
            if (version >= ZE_API_VERSION_1_9) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetVFTelemetryModeExp                    = loader_driver_ddi::zesVFManagementSetVFTelemetryModeExp;
            } else {
                pDdiTable->pfnSetVFTelemetryModeExp                    = loader::zesVFManagementSetVFTelemetryModeExp;
            }
            }
            if (version >= ZE_API_VERSION_1_9) {
            if (loader::context->driverDDIPathDefault) {
                pDdiTable->pfnSetVFTelemetrySamplingIntervalExp        = loader_driver_ddi::zesVFManagementSetVFTelemetrySamplingIntervalExp;
            } else {
                pDdiTable->pfnSetVFTelemetrySamplingIntervalExp        = loader::zesVFManagementSetVFTelemetrySamplingIntervalExp;
            }
            }
            zesGetVFManagementExpProcAddrTableLegacy();
        }
        else
        {
            // return pointers directly to driver's DDIs
            *pDdiTable = loader::context->sysmanInstanceDrivers->front().dditable.zes.VFManagementExp;
        }
    }

    // If the validation layer is enabled, then intercept the loader's DDIs
    if(( ZE_RESULT_SUCCESS == result ) && ( nullptr != loader::context->validationLayer ))
    {
        auto getTable = reinterpret_cast<zes_pfnGetVFManagementExpProcAddrTable_t>(
            GET_FUNCTION_PTR(loader::context->validationLayer, "zesGetVFManagementExpProcAddrTable") );
        if(!getTable)
            return ZE_RESULT_ERROR_UNINITIALIZED;
        result = getTable( version, pDdiTable );
    }

    return result;
}


#if defined(__cplusplus)
};
#endif