/*
 * ***THIS FILE IS GENERATED. ***
 * See valddi.cpp.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
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
            auto result = context.paramValidation->zesParamValidation.zesInit( flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesInit( flags );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnInit( flags );
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
        auto pfnGet = context.zesDdiTable.Driver.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDriverGet( pCount, phDrivers );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverGet( pCount, phDrivers );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGet( pCount, phDrivers );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phDrivers) && (i < *pCount); ++i){
                if (phDrivers[i]){
                    context.handleLifetime->addHandle( phDrivers[i] );
                    context.handleLifetime->addDependent( pCount, phDrivers[i] );
                }
            }
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
        auto pfnGetExtensionProperties = context.zesDdiTable.Driver.pfnGetExtensionProperties;

        if( nullptr == pfnGetExtensionProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDriverGetExtensionProperties( hDriver, pCount, pExtensionProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverGetExtensionProperties( hDriver, pCount, pExtensionProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetExtensionProperties( hDriver, pCount, pExtensionProperties );
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
        auto pfnGetExtensionFunctionAddress = context.zesDdiTable.Driver.pfnGetExtensionFunctionAddress;

        if( nullptr == pfnGetExtensionFunctionAddress )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDriverGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );
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
        auto pfnGet = context.zesDdiTable.Device.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceGet( hDriver, pCount, phDevices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGet( hDriver, pCount, phDevices );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGet( hDriver, pCount, phDevices );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phDevices) && (i < *pCount); ++i){
                if (phDevices[i]){
                    context.handleLifetime->addHandle( phDevices[i] );
                    context.handleLifetime->addDependent( hDriver, phDevices[i] );
                }
            }
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
        auto pfnGetProperties = context.zesDdiTable.Device.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceGetProperties( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetProperties( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hDevice, pProperties );
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
        auto pfnGetState = context.zesDdiTable.Device.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceGetState( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetState( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetState( hDevice, pState );
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
        auto pfnReset = context.zesDdiTable.Device.pfnReset;

        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceReset( hDevice, force );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceReset( hDevice, force );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnReset( hDevice, force );
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
        auto pfnResetExt = context.zesDdiTable.Device.pfnResetExt;

        if( nullptr == pfnResetExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceResetExt( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceResetExt( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnResetExt( hDevice, pProperties );
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
        auto pfnProcessesGetState = context.zesDdiTable.Device.pfnProcessesGetState;

        if( nullptr == pfnProcessesGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceProcessesGetState( hDevice, pCount, pProcesses );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceProcessesGetState( hDevice, pCount, pProcesses );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnProcessesGetState( hDevice, pCount, pProcesses );
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
        auto pfnPciGetProperties = context.zesDdiTable.Device.pfnPciGetProperties;

        if( nullptr == pfnPciGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDevicePciGetProperties( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDevicePciGetProperties( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnPciGetProperties( hDevice, pProperties );
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
        auto pfnPciGetState = context.zesDdiTable.Device.pfnPciGetState;

        if( nullptr == pfnPciGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDevicePciGetState( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDevicePciGetState( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnPciGetState( hDevice, pState );
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
        auto pfnPciGetBars = context.zesDdiTable.Device.pfnPciGetBars;

        if( nullptr == pfnPciGetBars )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDevicePciGetBars( hDevice, pCount, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDevicePciGetBars( hDevice, pCount, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnPciGetBars( hDevice, pCount, pProperties );
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
        auto pfnPciGetStats = context.zesDdiTable.Device.pfnPciGetStats;

        if( nullptr == pfnPciGetStats )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDevicePciGetStats( hDevice, pStats );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDevicePciGetStats( hDevice, pStats );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnPciGetStats( hDevice, pStats );
        return result;
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
            auto result = context.paramValidation->zesParamValidation.zesDeviceSetOverclockWaiver( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceSetOverclockWaiver( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetOverclockWaiver( hDevice );
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
        auto pfnGetOverclockDomains = context.zesDdiTable.Device.pfnGetOverclockDomains;

        if( nullptr == pfnGetOverclockDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceGetOverclockDomains( hDevice, pOverclockDomains );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetOverclockDomains( hDevice, pOverclockDomains );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetOverclockDomains( hDevice, pOverclockDomains );
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
        auto pfnGetOverclockControls = context.zesDdiTable.Device.pfnGetOverclockControls;

        if( nullptr == pfnGetOverclockControls )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceGetOverclockControls( hDevice, domainType, pAvailableControls );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetOverclockControls( hDevice, domainType, pAvailableControls );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetOverclockControls( hDevice, domainType, pAvailableControls );
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
        auto pfnResetOverclockSettings = context.zesDdiTable.Device.pfnResetOverclockSettings;

        if( nullptr == pfnResetOverclockSettings )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceResetOverclockSettings( hDevice, onShippedState );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceResetOverclockSettings( hDevice, onShippedState );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnResetOverclockSettings( hDevice, onShippedState );
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
        auto pfnReadOverclockState = context.zesDdiTable.Device.pfnReadOverclockState;

        if( nullptr == pfnReadOverclockState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceReadOverclockState( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceReadOverclockState( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnReadOverclockState( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset );
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
        auto pfnEnumOverclockDomains = context.zesDdiTable.Device.pfnEnumOverclockDomains;

        if( nullptr == pfnEnumOverclockDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumOverclockDomains( hDevice, pCount, phDomainHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumOverclockDomains( hDevice, pCount, phDomainHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumOverclockDomains( hDevice, pCount, phDomainHandle );
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
        auto pfnGetDomainProperties = context.zesDdiTable.Overclock.pfnGetDomainProperties;

        if( nullptr == pfnGetDomainProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesOverclockGetDomainProperties( hDomainHandle, pDomainProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetDomainProperties( hDomainHandle, pDomainProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetDomainProperties( hDomainHandle, pDomainProperties );
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
        auto pfnGetDomainVFProperties = context.zesDdiTable.Overclock.pfnGetDomainVFProperties;

        if( nullptr == pfnGetDomainVFProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesOverclockGetDomainVFProperties( hDomainHandle, pVFProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetDomainVFProperties( hDomainHandle, pVFProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetDomainVFProperties( hDomainHandle, pVFProperties );
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
        auto pfnGetDomainControlProperties = context.zesDdiTable.Overclock.pfnGetDomainControlProperties;

        if( nullptr == pfnGetDomainControlProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesOverclockGetDomainControlProperties( hDomainHandle, DomainControl, pControlProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetDomainControlProperties( hDomainHandle, DomainControl, pControlProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetDomainControlProperties( hDomainHandle, DomainControl, pControlProperties );
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
        auto pfnGetControlCurrentValue = context.zesDdiTable.Overclock.pfnGetControlCurrentValue;

        if( nullptr == pfnGetControlCurrentValue )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesOverclockGetControlCurrentValue( hDomainHandle, DomainControl, pValue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetControlCurrentValue( hDomainHandle, DomainControl, pValue );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetControlCurrentValue( hDomainHandle, DomainControl, pValue );
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
        auto pfnGetControlPendingValue = context.zesDdiTable.Overclock.pfnGetControlPendingValue;

        if( nullptr == pfnGetControlPendingValue )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesOverclockGetControlPendingValue( hDomainHandle, DomainControl, pValue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetControlPendingValue( hDomainHandle, DomainControl, pValue );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetControlPendingValue( hDomainHandle, DomainControl, pValue );
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
        auto pfnSetControlUserValue = context.zesDdiTable.Overclock.pfnSetControlUserValue;

        if( nullptr == pfnSetControlUserValue )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesOverclockSetControlUserValue( hDomainHandle, DomainControl, pValue, pPendingAction );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockSetControlUserValue( hDomainHandle, DomainControl, pValue, pPendingAction );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetControlUserValue( hDomainHandle, DomainControl, pValue, pPendingAction );
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
        auto pfnGetControlState = context.zesDdiTable.Overclock.pfnGetControlState;

        if( nullptr == pfnGetControlState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesOverclockGetControlState( hDomainHandle, DomainControl, pControlState, pPendingAction );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetControlState( hDomainHandle, DomainControl, pControlState, pPendingAction );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetControlState( hDomainHandle, DomainControl, pControlState, pPendingAction );
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
        auto pfnGetVFPointValues = context.zesDdiTable.Overclock.pfnGetVFPointValues;

        if( nullptr == pfnGetVFPointValues )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesOverclockGetVFPointValues( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetVFPointValues( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetVFPointValues( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue );
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
        auto pfnSetVFPointValues = context.zesDdiTable.Overclock.pfnSetVFPointValues;

        if( nullptr == pfnSetVFPointValues )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesOverclockSetVFPointValues( hDomainHandle, VFType, PointIndex, PointValue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockSetVFPointValues( hDomainHandle, VFType, PointIndex, PointValue );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetVFPointValues( hDomainHandle, VFType, PointIndex, PointValue );
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
        auto pfnEnumDiagnosticTestSuites = context.zesDdiTable.Device.pfnEnumDiagnosticTestSuites;

        if( nullptr == pfnEnumDiagnosticTestSuites )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumDiagnosticTestSuites( hDevice, pCount, phDiagnostics );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumDiagnosticTestSuites( hDevice, pCount, phDiagnostics );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumDiagnosticTestSuites( hDevice, pCount, phDiagnostics );
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
        auto pfnGetProperties = context.zesDdiTable.Diagnostics.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDiagnosticsGetProperties( hDiagnostics, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDiagnosticsGetProperties( hDiagnostics, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hDiagnostics, pProperties );
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
        auto pfnGetTests = context.zesDdiTable.Diagnostics.pfnGetTests;

        if( nullptr == pfnGetTests )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDiagnosticsGetTests( hDiagnostics, pCount, pTests );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDiagnosticsGetTests( hDiagnostics, pCount, pTests );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetTests( hDiagnostics, pCount, pTests );
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
        auto pfnRunTests = context.zesDdiTable.Diagnostics.pfnRunTests;

        if( nullptr == pfnRunTests )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDiagnosticsRunTests( hDiagnostics, startIndex, endIndex, pResult );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDiagnosticsRunTests( hDiagnostics, startIndex, endIndex, pResult );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnRunTests( hDiagnostics, startIndex, endIndex, pResult );
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
        auto pfnEccAvailable = context.zesDdiTable.Device.pfnEccAvailable;

        if( nullptr == pfnEccAvailable )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEccAvailable( hDevice, pAvailable );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEccAvailable( hDevice, pAvailable );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEccAvailable( hDevice, pAvailable );
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
        auto pfnEccConfigurable = context.zesDdiTable.Device.pfnEccConfigurable;

        if( nullptr == pfnEccConfigurable )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEccConfigurable( hDevice, pConfigurable );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEccConfigurable( hDevice, pConfigurable );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEccConfigurable( hDevice, pConfigurable );
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
        auto pfnGetEccState = context.zesDdiTable.Device.pfnGetEccState;

        if( nullptr == pfnGetEccState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceGetEccState( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetEccState( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetEccState( hDevice, pState );
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
        auto pfnSetEccState = context.zesDdiTable.Device.pfnSetEccState;

        if( nullptr == pfnSetEccState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceSetEccState( hDevice, newState, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceSetEccState( hDevice, newState, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetEccState( hDevice, newState, pState );
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
        auto pfnEnumEngineGroups = context.zesDdiTable.Device.pfnEnumEngineGroups;

        if( nullptr == pfnEnumEngineGroups )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumEngineGroups( hDevice, pCount, phEngine );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumEngineGroups( hDevice, pCount, phEngine );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumEngineGroups( hDevice, pCount, phEngine );
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
        auto pfnGetProperties = context.zesDdiTable.Engine.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesEngineGetProperties( hEngine, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesEngineGetProperties( hEngine, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hEngine, pProperties );
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
        auto pfnGetActivity = context.zesDdiTable.Engine.pfnGetActivity;

        if( nullptr == pfnGetActivity )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesEngineGetActivity( hEngine, pStats );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesEngineGetActivity( hEngine, pStats );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetActivity( hEngine, pStats );
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
        auto pfnEventRegister = context.zesDdiTable.Device.pfnEventRegister;

        if( nullptr == pfnEventRegister )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEventRegister( hDevice, events );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEventRegister( hDevice, events );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEventRegister( hDevice, events );
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
        auto pfnEventListen = context.zesDdiTable.Driver.pfnEventListen;

        if( nullptr == pfnEventListen )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDriverEventListen( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverEventListen( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEventListen( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
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
        auto pfnEventListenEx = context.zesDdiTable.Driver.pfnEventListenEx;

        if( nullptr == pfnEventListenEx )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDriverEventListenEx( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverEventListenEx( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEventListenEx( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
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
        auto pfnEnumFabricPorts = context.zesDdiTable.Device.pfnEnumFabricPorts;

        if( nullptr == pfnEnumFabricPorts )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumFabricPorts( hDevice, pCount, phPort );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumFabricPorts( hDevice, pCount, phPort );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumFabricPorts( hDevice, pCount, phPort );
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
        auto pfnGetProperties = context.zesDdiTable.FabricPort.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFabricPortGetProperties( hPort, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetProperties( hPort, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hPort, pProperties );
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
        auto pfnGetLinkType = context.zesDdiTable.FabricPort.pfnGetLinkType;

        if( nullptr == pfnGetLinkType )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFabricPortGetLinkType( hPort, pLinkType );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetLinkType( hPort, pLinkType );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetLinkType( hPort, pLinkType );
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
        auto pfnGetConfig = context.zesDdiTable.FabricPort.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFabricPortGetConfig( hPort, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetConfig( hPort, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetConfig( hPort, pConfig );
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
        auto pfnSetConfig = context.zesDdiTable.FabricPort.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFabricPortSetConfig( hPort, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortSetConfig( hPort, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetConfig( hPort, pConfig );
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
        auto pfnGetState = context.zesDdiTable.FabricPort.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFabricPortGetState( hPort, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetState( hPort, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetState( hPort, pState );
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
        auto pfnGetThroughput = context.zesDdiTable.FabricPort.pfnGetThroughput;

        if( nullptr == pfnGetThroughput )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFabricPortGetThroughput( hPort, pThroughput );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetThroughput( hPort, pThroughput );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetThroughput( hPort, pThroughput );
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
        auto pfnGetFabricErrorCounters = context.zesDdiTable.FabricPort.pfnGetFabricErrorCounters;

        if( nullptr == pfnGetFabricErrorCounters )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFabricPortGetFabricErrorCounters( hPort, pErrors );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetFabricErrorCounters( hPort, pErrors );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetFabricErrorCounters( hPort, pErrors );
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
        auto pfnGetMultiPortThroughput = context.zesDdiTable.FabricPort.pfnGetMultiPortThroughput;

        if( nullptr == pfnGetMultiPortThroughput )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFabricPortGetMultiPortThroughput( hDevice, numPorts, phPort, pThroughput );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetMultiPortThroughput( hDevice, numPorts, phPort, pThroughput );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetMultiPortThroughput( hDevice, numPorts, phPort, pThroughput );
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
        auto pfnEnumFans = context.zesDdiTable.Device.pfnEnumFans;

        if( nullptr == pfnEnumFans )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumFans( hDevice, pCount, phFan );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumFans( hDevice, pCount, phFan );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumFans( hDevice, pCount, phFan );
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
        auto pfnGetProperties = context.zesDdiTable.Fan.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFanGetProperties( hFan, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanGetProperties( hFan, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hFan, pProperties );
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
        auto pfnGetConfig = context.zesDdiTable.Fan.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFanGetConfig( hFan, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanGetConfig( hFan, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetConfig( hFan, pConfig );
        return result;
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
            auto result = context.paramValidation->zesParamValidation.zesFanSetDefaultMode( hFan );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanSetDefaultMode( hFan );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetDefaultMode( hFan );
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
        auto pfnSetFixedSpeedMode = context.zesDdiTable.Fan.pfnSetFixedSpeedMode;

        if( nullptr == pfnSetFixedSpeedMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFanSetFixedSpeedMode( hFan, speed );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanSetFixedSpeedMode( hFan, speed );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetFixedSpeedMode( hFan, speed );
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
        auto pfnSetSpeedTableMode = context.zesDdiTable.Fan.pfnSetSpeedTableMode;

        if( nullptr == pfnSetSpeedTableMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFanSetSpeedTableMode( hFan, speedTable );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanSetSpeedTableMode( hFan, speedTable );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetSpeedTableMode( hFan, speedTable );
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
        auto pfnGetState = context.zesDdiTable.Fan.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFanGetState( hFan, units, pSpeed );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanGetState( hFan, units, pSpeed );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetState( hFan, units, pSpeed );
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
        auto pfnEnumFirmwares = context.zesDdiTable.Device.pfnEnumFirmwares;

        if( nullptr == pfnEnumFirmwares )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumFirmwares( hDevice, pCount, phFirmware );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumFirmwares( hDevice, pCount, phFirmware );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumFirmwares( hDevice, pCount, phFirmware );
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
        auto pfnGetProperties = context.zesDdiTable.Firmware.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFirmwareGetProperties( hFirmware, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFirmwareGetProperties( hFirmware, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hFirmware, pProperties );
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
        auto pfnFlash = context.zesDdiTable.Firmware.pfnFlash;

        if( nullptr == pfnFlash )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFirmwareFlash( hFirmware, pImage, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFirmwareFlash( hFirmware, pImage, size );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnFlash( hFirmware, pImage, size );
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
        auto pfnGetFlashProgress = context.zesDdiTable.Firmware.pfnGetFlashProgress;

        if( nullptr == pfnGetFlashProgress )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFirmwareGetFlashProgress( hFirmware, pCompletionPercent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFirmwareGetFlashProgress( hFirmware, pCompletionPercent );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetFlashProgress( hFirmware, pCompletionPercent );
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
        auto pfnEnumFrequencyDomains = context.zesDdiTable.Device.pfnEnumFrequencyDomains;

        if( nullptr == pfnEnumFrequencyDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumFrequencyDomains( hDevice, pCount, phFrequency );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumFrequencyDomains( hDevice, pCount, phFrequency );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumFrequencyDomains( hDevice, pCount, phFrequency );
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
        auto pfnGetProperties = context.zesDdiTable.Frequency.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyGetProperties( hFrequency, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyGetProperties( hFrequency, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hFrequency, pProperties );
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
        auto pfnGetAvailableClocks = context.zesDdiTable.Frequency.pfnGetAvailableClocks;

        if( nullptr == pfnGetAvailableClocks )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyGetAvailableClocks( hFrequency, pCount, phFrequency );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyGetAvailableClocks( hFrequency, pCount, phFrequency );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetAvailableClocks( hFrequency, pCount, phFrequency );
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
        auto pfnGetRange = context.zesDdiTable.Frequency.pfnGetRange;

        if( nullptr == pfnGetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyGetRange( hFrequency, pLimits );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyGetRange( hFrequency, pLimits );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetRange( hFrequency, pLimits );
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
        auto pfnSetRange = context.zesDdiTable.Frequency.pfnSetRange;

        if( nullptr == pfnSetRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencySetRange( hFrequency, pLimits );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencySetRange( hFrequency, pLimits );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetRange( hFrequency, pLimits );
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
        auto pfnGetState = context.zesDdiTable.Frequency.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyGetState( hFrequency, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyGetState( hFrequency, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetState( hFrequency, pState );
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
        auto pfnGetThrottleTime = context.zesDdiTable.Frequency.pfnGetThrottleTime;

        if( nullptr == pfnGetThrottleTime )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyGetThrottleTime( hFrequency, pThrottleTime );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyGetThrottleTime( hFrequency, pThrottleTime );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetThrottleTime( hFrequency, pThrottleTime );
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
        auto pfnOcGetCapabilities = context.zesDdiTable.Frequency.pfnOcGetCapabilities;

        if( nullptr == pfnOcGetCapabilities )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyOcGetCapabilities( hFrequency, pOcCapabilities );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetCapabilities( hFrequency, pOcCapabilities );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnOcGetCapabilities( hFrequency, pOcCapabilities );
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
        auto pfnOcGetFrequencyTarget = context.zesDdiTable.Frequency.pfnOcGetFrequencyTarget;

        if( nullptr == pfnOcGetFrequencyTarget )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyOcGetFrequencyTarget( hFrequency, pCurrentOcFrequency );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetFrequencyTarget( hFrequency, pCurrentOcFrequency );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnOcGetFrequencyTarget( hFrequency, pCurrentOcFrequency );
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
        auto pfnOcSetFrequencyTarget = context.zesDdiTable.Frequency.pfnOcSetFrequencyTarget;

        if( nullptr == pfnOcSetFrequencyTarget )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyOcSetFrequencyTarget( hFrequency, CurrentOcFrequency );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcSetFrequencyTarget( hFrequency, CurrentOcFrequency );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnOcSetFrequencyTarget( hFrequency, CurrentOcFrequency );
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
        auto pfnOcGetVoltageTarget = context.zesDdiTable.Frequency.pfnOcGetVoltageTarget;

        if( nullptr == pfnOcGetVoltageTarget )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyOcGetVoltageTarget( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetVoltageTarget( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnOcGetVoltageTarget( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );
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
        auto pfnOcSetVoltageTarget = context.zesDdiTable.Frequency.pfnOcSetVoltageTarget;

        if( nullptr == pfnOcSetVoltageTarget )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyOcSetVoltageTarget( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcSetVoltageTarget( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnOcSetVoltageTarget( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );
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
        auto pfnOcSetMode = context.zesDdiTable.Frequency.pfnOcSetMode;

        if( nullptr == pfnOcSetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyOcSetMode( hFrequency, CurrentOcMode );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcSetMode( hFrequency, CurrentOcMode );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnOcSetMode( hFrequency, CurrentOcMode );
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
        auto pfnOcGetMode = context.zesDdiTable.Frequency.pfnOcGetMode;

        if( nullptr == pfnOcGetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyOcGetMode( hFrequency, pCurrentOcMode );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetMode( hFrequency, pCurrentOcMode );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnOcGetMode( hFrequency, pCurrentOcMode );
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
        auto pfnOcGetIccMax = context.zesDdiTable.Frequency.pfnOcGetIccMax;

        if( nullptr == pfnOcGetIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyOcGetIccMax( hFrequency, pOcIccMax );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetIccMax( hFrequency, pOcIccMax );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnOcGetIccMax( hFrequency, pOcIccMax );
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
        auto pfnOcSetIccMax = context.zesDdiTable.Frequency.pfnOcSetIccMax;

        if( nullptr == pfnOcSetIccMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyOcSetIccMax( hFrequency, ocIccMax );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcSetIccMax( hFrequency, ocIccMax );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnOcSetIccMax( hFrequency, ocIccMax );
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
        auto pfnOcGetTjMax = context.zesDdiTable.Frequency.pfnOcGetTjMax;

        if( nullptr == pfnOcGetTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyOcGetTjMax( hFrequency, pOcTjMax );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetTjMax( hFrequency, pOcTjMax );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnOcGetTjMax( hFrequency, pOcTjMax );
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
        auto pfnOcSetTjMax = context.zesDdiTable.Frequency.pfnOcSetTjMax;

        if( nullptr == pfnOcSetTjMax )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesFrequencyOcSetTjMax( hFrequency, ocTjMax );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcSetTjMax( hFrequency, ocTjMax );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnOcSetTjMax( hFrequency, ocTjMax );
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
        auto pfnEnumLeds = context.zesDdiTable.Device.pfnEnumLeds;

        if( nullptr == pfnEnumLeds )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumLeds( hDevice, pCount, phLed );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumLeds( hDevice, pCount, phLed );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumLeds( hDevice, pCount, phLed );
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
        auto pfnGetProperties = context.zesDdiTable.Led.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesLedGetProperties( hLed, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesLedGetProperties( hLed, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hLed, pProperties );
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
        auto pfnGetState = context.zesDdiTable.Led.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesLedGetState( hLed, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesLedGetState( hLed, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetState( hLed, pState );
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
        auto pfnSetState = context.zesDdiTable.Led.pfnSetState;

        if( nullptr == pfnSetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesLedSetState( hLed, enable );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesLedSetState( hLed, enable );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetState( hLed, enable );
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
        auto pfnSetColor = context.zesDdiTable.Led.pfnSetColor;

        if( nullptr == pfnSetColor )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesLedSetColor( hLed, pColor );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesLedSetColor( hLed, pColor );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetColor( hLed, pColor );
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
        auto pfnEnumMemoryModules = context.zesDdiTable.Device.pfnEnumMemoryModules;

        if( nullptr == pfnEnumMemoryModules )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumMemoryModules( hDevice, pCount, phMemory );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumMemoryModules( hDevice, pCount, phMemory );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumMemoryModules( hDevice, pCount, phMemory );
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
        auto pfnGetProperties = context.zesDdiTable.Memory.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesMemoryGetProperties( hMemory, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesMemoryGetProperties( hMemory, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hMemory, pProperties );
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
        auto pfnGetState = context.zesDdiTable.Memory.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesMemoryGetState( hMemory, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesMemoryGetState( hMemory, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetState( hMemory, pState );
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
        auto pfnGetBandwidth = context.zesDdiTable.Memory.pfnGetBandwidth;

        if( nullptr == pfnGetBandwidth )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesMemoryGetBandwidth( hMemory, pBandwidth );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesMemoryGetBandwidth( hMemory, pBandwidth );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetBandwidth( hMemory, pBandwidth );
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
        auto pfnEnumPerformanceFactorDomains = context.zesDdiTable.Device.pfnEnumPerformanceFactorDomains;

        if( nullptr == pfnEnumPerformanceFactorDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumPerformanceFactorDomains( hDevice, pCount, phPerf );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumPerformanceFactorDomains( hDevice, pCount, phPerf );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumPerformanceFactorDomains( hDevice, pCount, phPerf );
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
        auto pfnGetProperties = context.zesDdiTable.PerformanceFactor.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesPerformanceFactorGetProperties( hPerf, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPerformanceFactorGetProperties( hPerf, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hPerf, pProperties );
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
        auto pfnGetConfig = context.zesDdiTable.PerformanceFactor.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesPerformanceFactorGetConfig( hPerf, pFactor );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPerformanceFactorGetConfig( hPerf, pFactor );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetConfig( hPerf, pFactor );
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
        auto pfnSetConfig = context.zesDdiTable.PerformanceFactor.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesPerformanceFactorSetConfig( hPerf, factor );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPerformanceFactorSetConfig( hPerf, factor );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetConfig( hPerf, factor );
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
        auto pfnEnumPowerDomains = context.zesDdiTable.Device.pfnEnumPowerDomains;

        if( nullptr == pfnEnumPowerDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumPowerDomains( hDevice, pCount, phPower );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumPowerDomains( hDevice, pCount, phPower );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumPowerDomains( hDevice, pCount, phPower );
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
        auto pfnGetCardPowerDomain = context.zesDdiTable.Device.pfnGetCardPowerDomain;

        if( nullptr == pfnGetCardPowerDomain )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceGetCardPowerDomain( hDevice, phPower );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetCardPowerDomain( hDevice, phPower );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetCardPowerDomain( hDevice, phPower );
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
        auto pfnGetProperties = context.zesDdiTable.Power.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesPowerGetProperties( hPower, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerGetProperties( hPower, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hPower, pProperties );
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
        auto pfnGetEnergyCounter = context.zesDdiTable.Power.pfnGetEnergyCounter;

        if( nullptr == pfnGetEnergyCounter )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesPowerGetEnergyCounter( hPower, pEnergy );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerGetEnergyCounter( hPower, pEnergy );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetEnergyCounter( hPower, pEnergy );
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
        auto pfnGetLimits = context.zesDdiTable.Power.pfnGetLimits;

        if( nullptr == pfnGetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesPowerGetLimits( hPower, pSustained, pBurst, pPeak );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerGetLimits( hPower, pSustained, pBurst, pPeak );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetLimits( hPower, pSustained, pBurst, pPeak );
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
        auto pfnSetLimits = context.zesDdiTable.Power.pfnSetLimits;

        if( nullptr == pfnSetLimits )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesPowerSetLimits( hPower, pSustained, pBurst, pPeak );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerSetLimits( hPower, pSustained, pBurst, pPeak );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetLimits( hPower, pSustained, pBurst, pPeak );
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
        auto pfnGetEnergyThreshold = context.zesDdiTable.Power.pfnGetEnergyThreshold;

        if( nullptr == pfnGetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesPowerGetEnergyThreshold( hPower, pThreshold );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerGetEnergyThreshold( hPower, pThreshold );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetEnergyThreshold( hPower, pThreshold );
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
        auto pfnSetEnergyThreshold = context.zesDdiTable.Power.pfnSetEnergyThreshold;

        if( nullptr == pfnSetEnergyThreshold )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesPowerSetEnergyThreshold( hPower, threshold );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerSetEnergyThreshold( hPower, threshold );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetEnergyThreshold( hPower, threshold );
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
        auto pfnEnumPsus = context.zesDdiTable.Device.pfnEnumPsus;

        if( nullptr == pfnEnumPsus )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumPsus( hDevice, pCount, phPsu );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumPsus( hDevice, pCount, phPsu );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumPsus( hDevice, pCount, phPsu );
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
        auto pfnGetProperties = context.zesDdiTable.Psu.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesPsuGetProperties( hPsu, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPsuGetProperties( hPsu, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hPsu, pProperties );
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
        auto pfnGetState = context.zesDdiTable.Psu.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesPsuGetState( hPsu, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPsuGetState( hPsu, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetState( hPsu, pState );
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
        auto pfnEnumRasErrorSets = context.zesDdiTable.Device.pfnEnumRasErrorSets;

        if( nullptr == pfnEnumRasErrorSets )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumRasErrorSets( hDevice, pCount, phRas );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumRasErrorSets( hDevice, pCount, phRas );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumRasErrorSets( hDevice, pCount, phRas );
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
        auto pfnGetProperties = context.zesDdiTable.Ras.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesRasGetProperties( hRas, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasGetProperties( hRas, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hRas, pProperties );
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
        auto pfnGetConfig = context.zesDdiTable.Ras.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesRasGetConfig( hRas, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasGetConfig( hRas, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetConfig( hRas, pConfig );
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
        auto pfnSetConfig = context.zesDdiTable.Ras.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesRasSetConfig( hRas, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasSetConfig( hRas, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetConfig( hRas, pConfig );
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
        auto pfnGetState = context.zesDdiTable.Ras.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesRasGetState( hRas, clear, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasGetState( hRas, clear, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetState( hRas, clear, pState );
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
        auto pfnEnumSchedulers = context.zesDdiTable.Device.pfnEnumSchedulers;

        if( nullptr == pfnEnumSchedulers )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumSchedulers( hDevice, pCount, phScheduler );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumSchedulers( hDevice, pCount, phScheduler );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumSchedulers( hDevice, pCount, phScheduler );
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
        auto pfnGetProperties = context.zesDdiTable.Scheduler.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesSchedulerGetProperties( hScheduler, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerGetProperties( hScheduler, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hScheduler, pProperties );
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
        auto pfnGetCurrentMode = context.zesDdiTable.Scheduler.pfnGetCurrentMode;

        if( nullptr == pfnGetCurrentMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesSchedulerGetCurrentMode( hScheduler, pMode );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerGetCurrentMode( hScheduler, pMode );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetCurrentMode( hScheduler, pMode );
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
        auto pfnGetTimeoutModeProperties = context.zesDdiTable.Scheduler.pfnGetTimeoutModeProperties;

        if( nullptr == pfnGetTimeoutModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesSchedulerGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );
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
        auto pfnGetTimesliceModeProperties = context.zesDdiTable.Scheduler.pfnGetTimesliceModeProperties;

        if( nullptr == pfnGetTimesliceModeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesSchedulerGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );
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
        auto pfnSetTimeoutMode = context.zesDdiTable.Scheduler.pfnSetTimeoutMode;

        if( nullptr == pfnSetTimeoutMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesSchedulerSetTimeoutMode( hScheduler, pProperties, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerSetTimeoutMode( hScheduler, pProperties, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );
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
        auto pfnSetTimesliceMode = context.zesDdiTable.Scheduler.pfnSetTimesliceMode;

        if( nullptr == pfnSetTimesliceMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesSchedulerSetTimesliceMode( hScheduler, pProperties, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerSetTimesliceMode( hScheduler, pProperties, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );
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
        auto pfnSetExclusiveMode = context.zesDdiTable.Scheduler.pfnSetExclusiveMode;

        if( nullptr == pfnSetExclusiveMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesSchedulerSetExclusiveMode( hScheduler, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerSetExclusiveMode( hScheduler, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetExclusiveMode( hScheduler, pNeedReload );
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
        auto pfnSetComputeUnitDebugMode = context.zesDdiTable.Scheduler.pfnSetComputeUnitDebugMode;

        if( nullptr == pfnSetComputeUnitDebugMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesSchedulerSetComputeUnitDebugMode( hScheduler, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerSetComputeUnitDebugMode( hScheduler, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );
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
        auto pfnEnumStandbyDomains = context.zesDdiTable.Device.pfnEnumStandbyDomains;

        if( nullptr == pfnEnumStandbyDomains )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumStandbyDomains( hDevice, pCount, phStandby );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumStandbyDomains( hDevice, pCount, phStandby );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumStandbyDomains( hDevice, pCount, phStandby );
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
        auto pfnGetProperties = context.zesDdiTable.Standby.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesStandbyGetProperties( hStandby, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesStandbyGetProperties( hStandby, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hStandby, pProperties );
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
        auto pfnGetMode = context.zesDdiTable.Standby.pfnGetMode;

        if( nullptr == pfnGetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesStandbyGetMode( hStandby, pMode );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesStandbyGetMode( hStandby, pMode );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetMode( hStandby, pMode );
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
        auto pfnSetMode = context.zesDdiTable.Standby.pfnSetMode;

        if( nullptr == pfnSetMode )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesStandbySetMode( hStandby, mode );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesStandbySetMode( hStandby, mode );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetMode( hStandby, mode );
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
        auto pfnEnumTemperatureSensors = context.zesDdiTable.Device.pfnEnumTemperatureSensors;

        if( nullptr == pfnEnumTemperatureSensors )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesDeviceEnumTemperatureSensors( hDevice, pCount, phTemperature );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumTemperatureSensors( hDevice, pCount, phTemperature );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEnumTemperatureSensors( hDevice, pCount, phTemperature );
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
        auto pfnGetProperties = context.zesDdiTable.Temperature.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesTemperatureGetProperties( hTemperature, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesTemperatureGetProperties( hTemperature, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hTemperature, pProperties );
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
        auto pfnGetConfig = context.zesDdiTable.Temperature.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesTemperatureGetConfig( hTemperature, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesTemperatureGetConfig( hTemperature, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetConfig( hTemperature, pConfig );
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
        auto pfnSetConfig = context.zesDdiTable.Temperature.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesTemperatureSetConfig( hTemperature, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesTemperatureSetConfig( hTemperature, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetConfig( hTemperature, pConfig );
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
        auto pfnGetState = context.zesDdiTable.Temperature.pfnGetState;

        if( nullptr == pfnGetState )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesTemperatureGetState( hTemperature, pTemperature );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesTemperatureGetState( hTemperature, pTemperature );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetState( hTemperature, pTemperature );
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
        auto pfnGetLimitsExt = context.zesDdiTable.Power.pfnGetLimitsExt;

        if( nullptr == pfnGetLimitsExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesPowerGetLimitsExt( hPower, pCount, pSustained );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerGetLimitsExt( hPower, pCount, pSustained );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetLimitsExt( hPower, pCount, pSustained );
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
        auto pfnSetLimitsExt = context.zesDdiTable.Power.pfnSetLimitsExt;

        if( nullptr == pfnSetLimitsExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesPowerSetLimitsExt( hPower, pCount, pSustained );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerSetLimitsExt( hPower, pCount, pSustained );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetLimitsExt( hPower, pCount, pSustained );
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
        auto pfnGetActivityExt = context.zesDdiTable.Engine.pfnGetActivityExt;

        if( nullptr == pfnGetActivityExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesEngineGetActivityExt( hEngine, pCount, pStats );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesEngineGetActivityExt( hEngine, pCount, pStats );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetActivityExt( hEngine, pCount, pStats );
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
        auto pfnGetStateExp = context.zesDdiTable.RasExp.pfnGetStateExp;

        if( nullptr == pfnGetStateExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesRasGetStateExp( hRas, pCount, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasGetStateExp( hRas, pCount, pState );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetStateExp( hRas, pCount, pState );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
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
        auto pfnClearStateExp = context.zesDdiTable.RasExp.pfnClearStateExp;

        if( nullptr == pfnClearStateExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zesParamValidation.zesRasClearStateExp( hRas, category );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasClearStateExp( hRas, category );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnClearStateExp( hRas, category );
        return result;
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

    dditable.pfnResetExt                                 = pDdiTable->pfnResetExt;
    pDdiTable->pfnResetExt                               = validation_layer::zesDeviceResetExt;

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

    dditable.pfnGetExtensionProperties                   = pDdiTable->pfnGetExtensionProperties;
    pDdiTable->pfnGetExtensionProperties                 = validation_layer::zesDriverGetExtensionProperties;

    dditable.pfnGetExtensionFunctionAddress              = pDdiTable->pfnGetExtensionFunctionAddress;
    pDdiTable->pfnGetExtensionFunctionAddress            = validation_layer::zesDriverGetExtensionFunctionAddress;

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

    dditable.pfnGetActivityExt                           = pDdiTable->pfnGetActivityExt;
    pDdiTable->pfnGetActivityExt                         = validation_layer::zesEngineGetActivityExt;

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

    dditable.pfnGetMultiPortThroughput                   = pDdiTable->pfnGetMultiPortThroughput;
    pDdiTable->pfnGetMultiPortThroughput                 = validation_layer::zesFabricPortGetMultiPortThroughput;

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

    dditable.pfnGetFlashProgress                         = pDdiTable->pfnGetFlashProgress;
    pDdiTable->pfnGetFlashProgress                       = validation_layer::zesFirmwareGetFlashProgress;

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
    auto& dditable = validation_layer::context.zesDdiTable.RasExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetStateExp                              = pDdiTable->pfnGetStateExp;
    pDdiTable->pfnGetStateExp                            = validation_layer::zesRasGetStateExp;

    dditable.pfnClearStateExp                            = pDdiTable->pfnClearStateExp;
    pDdiTable->pfnClearStateExp                          = validation_layer::zesRasClearStateExp;

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
