/*
 * ***THIS FILE IS GENERATED. ***
 * See valddi.cpp.mako for modifications
 *
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_valddi.cpp
 *
 */
#include "ze_validation_layer.h"

namespace validation_layer
{
    static ze_result_t logAndPropagateResult(const char* fname, ze_result_t result) {
        if (result != ZE_RESULT_SUCCESS) {
            context.logger->log_trace("Error (" + loader::to_string(result) + ") in " + std::string(fname));
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesInit
    __zedlllocal ze_result_t ZE_APICALL
    zesInit(
        zes_init_flags_t flags                          ///< [in] initialization flags.
                                                        ///< currently unused, must be 0 (default).
        )
    {
        context.logger->log_trace("zesInit(flags)");

        auto pfnInit = context.zesDdiTable.Global.pfnInit;

        if( nullptr == pfnInit )
            return logAndPropagateResult("zesInit", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesInitPrologue( flags );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesInit", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesInitPrologue( flags );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesInit", result);
        }

        auto driver_result = pfnInit( flags );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesInitEpilogue( flags ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesInit", result);
        }

        return logAndPropagateResult("zesInit", driver_result);
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
        context.logger->log_trace("zesDriverGet(pCount, phDrivers)");

        auto pfnGet = context.zesDdiTable.Driver.pfnGet;

        if( nullptr == pfnGet )
            return logAndPropagateResult("zesDriverGet", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetPrologue( pCount, phDrivers );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverGet", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverGetPrologue( pCount, phDrivers );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverGet", result);
        }

        auto driver_result = pfnGet( pCount, phDrivers );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetEpilogue( pCount, phDrivers ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverGet", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phDrivers) && (i < *pCount); ++i){
                if (phDrivers[i]){
                    context.handleLifetime->addHandle( phDrivers[i] );
                    context.handleLifetime->addDependent( pCount, phDrivers[i] );
                }
            }
        }
        return logAndPropagateResult("zesDriverGet", driver_result);
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
        context.logger->log_trace("zesDriverGetExtensionProperties(hDriver, pCount, pExtensionProperties)");

        auto pfnGetExtensionProperties = context.zesDdiTable.Driver.pfnGetExtensionProperties;

        if( nullptr == pfnGetExtensionProperties )
            return logAndPropagateResult("zesDriverGetExtensionProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetExtensionPropertiesPrologue( hDriver, pCount, pExtensionProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverGetExtensionProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverGetExtensionPropertiesPrologue( hDriver, pCount, pExtensionProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverGetExtensionProperties", result);
        }

        auto driver_result = pfnGetExtensionProperties( hDriver, pCount, pExtensionProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetExtensionPropertiesEpilogue( hDriver, pCount, pExtensionProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverGetExtensionProperties", result);
        }

        return logAndPropagateResult("zesDriverGetExtensionProperties", driver_result);
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
        context.logger->log_trace("zesDriverGetExtensionFunctionAddress(hDriver, name, ppFunctionAddress)");

        auto pfnGetExtensionFunctionAddress = context.zesDdiTable.Driver.pfnGetExtensionFunctionAddress;

        if( nullptr == pfnGetExtensionFunctionAddress )
            return logAndPropagateResult("zesDriverGetExtensionFunctionAddress", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetExtensionFunctionAddressPrologue( hDriver, name, ppFunctionAddress );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverGetExtensionFunctionAddress", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverGetExtensionFunctionAddressPrologue( hDriver, name, ppFunctionAddress );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverGetExtensionFunctionAddress", result);
        }

        auto driver_result = pfnGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetExtensionFunctionAddressEpilogue( hDriver, name, ppFunctionAddress ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverGetExtensionFunctionAddress", result);
        }

        return logAndPropagateResult("zesDriverGetExtensionFunctionAddress", driver_result);
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
        context.logger->log_trace("zesDeviceGet(hDriver, pCount, phDevices)");

        auto pfnGet = context.zesDdiTable.Device.pfnGet;

        if( nullptr == pfnGet )
            return logAndPropagateResult("zesDeviceGet", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetPrologue( hDriver, pCount, phDevices );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGet", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetPrologue( hDriver, pCount, phDevices );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGet", result);
        }

        auto driver_result = pfnGet( hDriver, pCount, phDevices );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetEpilogue( hDriver, pCount, phDevices ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGet", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phDevices) && (i < *pCount); ++i){
                if (phDevices[i]){
                    context.handleLifetime->addHandle( phDevices[i] );
                    context.handleLifetime->addDependent( hDriver, phDevices[i] );
                }
            }
        }
        return logAndPropagateResult("zesDeviceGet", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGetProperties(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
        )
    {
        context.logger->log_trace("zesDeviceGetProperties(hDevice, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.Device.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesDeviceGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetPropertiesPrologue( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetPropertiesPrologue( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hDevice, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetPropertiesEpilogue( hDevice, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetProperties", result);
        }

        return logAndPropagateResult("zesDeviceGetProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGetState(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
        )
    {
        context.logger->log_trace("zesDeviceGetState(hDevice, pState)");

        auto pfnGetState = context.zesDdiTable.Device.pfnGetState;

        if( nullptr == pfnGetState )
            return logAndPropagateResult("zesDeviceGetState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetStatePrologue( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetStatePrologue( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetState", result);
        }

        auto driver_result = pfnGetState( hDevice, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetStateEpilogue( hDevice, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetState", result);
        }

        return logAndPropagateResult("zesDeviceGetState", driver_result);
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
        context.logger->log_trace("zesDeviceReset(hDevice, force)");

        auto pfnReset = context.zesDdiTable.Device.pfnReset;

        if( nullptr == pfnReset )
            return logAndPropagateResult("zesDeviceReset", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceResetPrologue( hDevice, force );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceReset", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceResetPrologue( hDevice, force );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceReset", result);
        }

        auto driver_result = pfnReset( hDevice, force );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceResetEpilogue( hDevice, force ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceReset", result);
        }

        return logAndPropagateResult("zesDeviceReset", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceResetExt
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceResetExt(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
        zes_reset_properties_t* pProperties             ///< [in] Device reset properties to apply
        )
    {
        context.logger->log_trace("zesDeviceResetExt(hDevice, pProperties)");

        auto pfnResetExt = context.zesDdiTable.Device.pfnResetExt;

        if( nullptr == pfnResetExt )
            return logAndPropagateResult("zesDeviceResetExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceResetExtPrologue( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceResetExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceResetExtPrologue( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceResetExt", result);
        }

        auto driver_result = pfnResetExt( hDevice, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceResetExtEpilogue( hDevice, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceResetExt", result);
        }

        return logAndPropagateResult("zesDeviceResetExt", driver_result);
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
        context.logger->log_trace("zesDeviceProcessesGetState(hDevice, pCount, pProcesses)");

        auto pfnProcessesGetState = context.zesDdiTable.Device.pfnProcessesGetState;

        if( nullptr == pfnProcessesGetState )
            return logAndPropagateResult("zesDeviceProcessesGetState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceProcessesGetStatePrologue( hDevice, pCount, pProcesses );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceProcessesGetState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceProcessesGetStatePrologue( hDevice, pCount, pProcesses );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceProcessesGetState", result);
        }

        auto driver_result = pfnProcessesGetState( hDevice, pCount, pProcesses );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceProcessesGetStateEpilogue( hDevice, pCount, pProcesses ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceProcessesGetState", result);
        }

        return logAndPropagateResult("zesDeviceProcessesGetState", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesDevicePciGetProperties(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
        )
    {
        context.logger->log_trace("zesDevicePciGetProperties(hDevice, pProperties)");

        auto pfnPciGetProperties = context.zesDdiTable.Device.pfnPciGetProperties;

        if( nullptr == pfnPciGetProperties )
            return logAndPropagateResult("zesDevicePciGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetPropertiesPrologue( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDevicePciGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDevicePciGetPropertiesPrologue( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDevicePciGetProperties", result);
        }

        auto driver_result = pfnPciGetProperties( hDevice, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetPropertiesEpilogue( hDevice, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDevicePciGetProperties", result);
        }

        return logAndPropagateResult("zesDevicePciGetProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesDevicePciGetState(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
        )
    {
        context.logger->log_trace("zesDevicePciGetState(hDevice, pState)");

        auto pfnPciGetState = context.zesDdiTable.Device.pfnPciGetState;

        if( nullptr == pfnPciGetState )
            return logAndPropagateResult("zesDevicePciGetState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetStatePrologue( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDevicePciGetState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDevicePciGetStatePrologue( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDevicePciGetState", result);
        }

        auto driver_result = pfnPciGetState( hDevice, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetStateEpilogue( hDevice, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDevicePciGetState", result);
        }

        return logAndPropagateResult("zesDevicePciGetState", driver_result);
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
        context.logger->log_trace("zesDevicePciGetBars(hDevice, pCount, pProperties)");

        auto pfnPciGetBars = context.zesDdiTable.Device.pfnPciGetBars;

        if( nullptr == pfnPciGetBars )
            return logAndPropagateResult("zesDevicePciGetBars", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetBarsPrologue( hDevice, pCount, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDevicePciGetBars", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDevicePciGetBarsPrologue( hDevice, pCount, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDevicePciGetBars", result);
        }

        auto driver_result = pfnPciGetBars( hDevice, pCount, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetBarsEpilogue( hDevice, pCount, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDevicePciGetBars", result);
        }

        return logAndPropagateResult("zesDevicePciGetBars", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciGetStats
    __zedlllocal ze_result_t ZE_APICALL
    zesDevicePciGetStats(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
        )
    {
        context.logger->log_trace("zesDevicePciGetStats(hDevice, pStats)");

        auto pfnPciGetStats = context.zesDdiTable.Device.pfnPciGetStats;

        if( nullptr == pfnPciGetStats )
            return logAndPropagateResult("zesDevicePciGetStats", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetStatsPrologue( hDevice, pStats );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDevicePciGetStats", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDevicePciGetStatsPrologue( hDevice, pStats );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDevicePciGetStats", result);
        }

        auto driver_result = pfnPciGetStats( hDevice, pStats );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetStatsEpilogue( hDevice, pStats ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDevicePciGetStats", result);
        }

        return logAndPropagateResult("zesDevicePciGetStats", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceSetOverclockWaiver
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceSetOverclockWaiver(
        zes_device_handle_t hDevice                     ///< [in] Sysman handle of the device.
        )
    {
        context.logger->log_trace("zesDeviceSetOverclockWaiver(hDevice)");

        auto pfnSetOverclockWaiver = context.zesDdiTable.Device.pfnSetOverclockWaiver;

        if( nullptr == pfnSetOverclockWaiver )
            return logAndPropagateResult("zesDeviceSetOverclockWaiver", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceSetOverclockWaiverPrologue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceSetOverclockWaiver", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceSetOverclockWaiverPrologue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceSetOverclockWaiver", result);
        }

        auto driver_result = pfnSetOverclockWaiver( hDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceSetOverclockWaiverEpilogue( hDevice ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceSetOverclockWaiver", result);
        }

        return logAndPropagateResult("zesDeviceSetOverclockWaiver", driver_result);
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
        context.logger->log_trace("zesDeviceGetOverclockDomains(hDevice, pOverclockDomains)");

        auto pfnGetOverclockDomains = context.zesDdiTable.Device.pfnGetOverclockDomains;

        if( nullptr == pfnGetOverclockDomains )
            return logAndPropagateResult("zesDeviceGetOverclockDomains", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetOverclockDomainsPrologue( hDevice, pOverclockDomains );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetOverclockDomains", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetOverclockDomainsPrologue( hDevice, pOverclockDomains );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetOverclockDomains", result);
        }

        auto driver_result = pfnGetOverclockDomains( hDevice, pOverclockDomains );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetOverclockDomainsEpilogue( hDevice, pOverclockDomains ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetOverclockDomains", result);
        }

        return logAndPropagateResult("zesDeviceGetOverclockDomains", driver_result);
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
        context.logger->log_trace("zesDeviceGetOverclockControls(hDevice, domainType, pAvailableControls)");

        auto pfnGetOverclockControls = context.zesDdiTable.Device.pfnGetOverclockControls;

        if( nullptr == pfnGetOverclockControls )
            return logAndPropagateResult("zesDeviceGetOverclockControls", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetOverclockControlsPrologue( hDevice, domainType, pAvailableControls );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetOverclockControls", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetOverclockControlsPrologue( hDevice, domainType, pAvailableControls );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetOverclockControls", result);
        }

        auto driver_result = pfnGetOverclockControls( hDevice, domainType, pAvailableControls );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetOverclockControlsEpilogue( hDevice, domainType, pAvailableControls ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetOverclockControls", result);
        }

        return logAndPropagateResult("zesDeviceGetOverclockControls", driver_result);
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
        context.logger->log_trace("zesDeviceResetOverclockSettings(hDevice, onShippedState)");

        auto pfnResetOverclockSettings = context.zesDdiTable.Device.pfnResetOverclockSettings;

        if( nullptr == pfnResetOverclockSettings )
            return logAndPropagateResult("zesDeviceResetOverclockSettings", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceResetOverclockSettingsPrologue( hDevice, onShippedState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceResetOverclockSettings", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceResetOverclockSettingsPrologue( hDevice, onShippedState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceResetOverclockSettings", result);
        }

        auto driver_result = pfnResetOverclockSettings( hDevice, onShippedState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceResetOverclockSettingsEpilogue( hDevice, onShippedState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceResetOverclockSettings", result);
        }

        return logAndPropagateResult("zesDeviceResetOverclockSettings", driver_result);
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
        context.logger->log_trace("zesDeviceReadOverclockState(hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset)");

        auto pfnReadOverclockState = context.zesDdiTable.Device.pfnReadOverclockState;

        if( nullptr == pfnReadOverclockState )
            return logAndPropagateResult("zesDeviceReadOverclockState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceReadOverclockStatePrologue( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceReadOverclockState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceReadOverclockStatePrologue( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceReadOverclockState", result);
        }

        auto driver_result = pfnReadOverclockState( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceReadOverclockStateEpilogue( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceReadOverclockState", result);
        }

        return logAndPropagateResult("zesDeviceReadOverclockState", driver_result);
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
        context.logger->log_trace("zesDeviceEnumOverclockDomains(hDevice, pCount, phDomainHandle)");

        auto pfnEnumOverclockDomains = context.zesDdiTable.Device.pfnEnumOverclockDomains;

        if( nullptr == pfnEnumOverclockDomains )
            return logAndPropagateResult("zesDeviceEnumOverclockDomains", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumOverclockDomainsPrologue( hDevice, pCount, phDomainHandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumOverclockDomains", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumOverclockDomainsPrologue( hDevice, pCount, phDomainHandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumOverclockDomains", result);
        }

        auto driver_result = pfnEnumOverclockDomains( hDevice, pCount, phDomainHandle );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumOverclockDomainsEpilogue( hDevice, pCount, phDomainHandle ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumOverclockDomains", result);
        }

        return logAndPropagateResult("zesDeviceEnumOverclockDomains", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesOverclockGetDomainProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesOverclockGetDomainProperties(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_properties_t* pDomainProperties   ///< [in,out] The overclock properties for the specified domain.
        )
    {
        context.logger->log_trace("zesOverclockGetDomainProperties(hDomainHandle, pDomainProperties)");

        auto pfnGetDomainProperties = context.zesDdiTable.Overclock.pfnGetDomainProperties;

        if( nullptr == pfnGetDomainProperties )
            return logAndPropagateResult("zesOverclockGetDomainProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetDomainPropertiesPrologue( hDomainHandle, pDomainProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetDomainProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetDomainPropertiesPrologue( hDomainHandle, pDomainProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetDomainProperties", result);
        }

        auto driver_result = pfnGetDomainProperties( hDomainHandle, pDomainProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetDomainPropertiesEpilogue( hDomainHandle, pDomainProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetDomainProperties", result);
        }

        return logAndPropagateResult("zesOverclockGetDomainProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesOverclockGetDomainVFProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesOverclockGetDomainVFProperties(
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_vf_property_t* pVFProperties                ///< [in,out] The VF min,max,step for a specified domain.
        )
    {
        context.logger->log_trace("zesOverclockGetDomainVFProperties(hDomainHandle, pVFProperties)");

        auto pfnGetDomainVFProperties = context.zesDdiTable.Overclock.pfnGetDomainVFProperties;

        if( nullptr == pfnGetDomainVFProperties )
            return logAndPropagateResult("zesOverclockGetDomainVFProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetDomainVFPropertiesPrologue( hDomainHandle, pVFProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetDomainVFProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetDomainVFPropertiesPrologue( hDomainHandle, pVFProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetDomainVFProperties", result);
        }

        auto driver_result = pfnGetDomainVFProperties( hDomainHandle, pVFProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetDomainVFPropertiesEpilogue( hDomainHandle, pVFProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetDomainVFProperties", result);
        }

        return logAndPropagateResult("zesOverclockGetDomainVFProperties", driver_result);
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
        context.logger->log_trace("zesOverclockGetDomainControlProperties(hDomainHandle, DomainControl, pControlProperties)");

        auto pfnGetDomainControlProperties = context.zesDdiTable.Overclock.pfnGetDomainControlProperties;

        if( nullptr == pfnGetDomainControlProperties )
            return logAndPropagateResult("zesOverclockGetDomainControlProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetDomainControlPropertiesPrologue( hDomainHandle, DomainControl, pControlProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetDomainControlProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetDomainControlPropertiesPrologue( hDomainHandle, DomainControl, pControlProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetDomainControlProperties", result);
        }

        auto driver_result = pfnGetDomainControlProperties( hDomainHandle, DomainControl, pControlProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetDomainControlPropertiesEpilogue( hDomainHandle, DomainControl, pControlProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetDomainControlProperties", result);
        }

        return logAndPropagateResult("zesOverclockGetDomainControlProperties", driver_result);
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
        context.logger->log_trace("zesOverclockGetControlCurrentValue(hDomainHandle, DomainControl, pValue)");

        auto pfnGetControlCurrentValue = context.zesDdiTable.Overclock.pfnGetControlCurrentValue;

        if( nullptr == pfnGetControlCurrentValue )
            return logAndPropagateResult("zesOverclockGetControlCurrentValue", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetControlCurrentValuePrologue( hDomainHandle, DomainControl, pValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetControlCurrentValue", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetControlCurrentValuePrologue( hDomainHandle, DomainControl, pValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetControlCurrentValue", result);
        }

        auto driver_result = pfnGetControlCurrentValue( hDomainHandle, DomainControl, pValue );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetControlCurrentValueEpilogue( hDomainHandle, DomainControl, pValue ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetControlCurrentValue", result);
        }

        return logAndPropagateResult("zesOverclockGetControlCurrentValue", driver_result);
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
        context.logger->log_trace("zesOverclockGetControlPendingValue(hDomainHandle, DomainControl, pValue)");

        auto pfnGetControlPendingValue = context.zesDdiTable.Overclock.pfnGetControlPendingValue;

        if( nullptr == pfnGetControlPendingValue )
            return logAndPropagateResult("zesOverclockGetControlPendingValue", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetControlPendingValuePrologue( hDomainHandle, DomainControl, pValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetControlPendingValue", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetControlPendingValuePrologue( hDomainHandle, DomainControl, pValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetControlPendingValue", result);
        }

        auto driver_result = pfnGetControlPendingValue( hDomainHandle, DomainControl, pValue );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetControlPendingValueEpilogue( hDomainHandle, DomainControl, pValue ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetControlPendingValue", result);
        }

        return logAndPropagateResult("zesOverclockGetControlPendingValue", driver_result);
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
        context.logger->log_trace("zesOverclockSetControlUserValue(hDomainHandle, DomainControl, pValue, pPendingAction)");

        auto pfnSetControlUserValue = context.zesDdiTable.Overclock.pfnSetControlUserValue;

        if( nullptr == pfnSetControlUserValue )
            return logAndPropagateResult("zesOverclockSetControlUserValue", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockSetControlUserValuePrologue( hDomainHandle, DomainControl, pValue, pPendingAction );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockSetControlUserValue", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockSetControlUserValuePrologue( hDomainHandle, DomainControl, pValue, pPendingAction );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockSetControlUserValue", result);
        }

        auto driver_result = pfnSetControlUserValue( hDomainHandle, DomainControl, pValue, pPendingAction );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockSetControlUserValueEpilogue( hDomainHandle, DomainControl, pValue, pPendingAction ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockSetControlUserValue", result);
        }

        return logAndPropagateResult("zesOverclockSetControlUserValue", driver_result);
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
        context.logger->log_trace("zesOverclockGetControlState(hDomainHandle, DomainControl, pControlState, pPendingAction)");

        auto pfnGetControlState = context.zesDdiTable.Overclock.pfnGetControlState;

        if( nullptr == pfnGetControlState )
            return logAndPropagateResult("zesOverclockGetControlState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetControlStatePrologue( hDomainHandle, DomainControl, pControlState, pPendingAction );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetControlState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetControlStatePrologue( hDomainHandle, DomainControl, pControlState, pPendingAction );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetControlState", result);
        }

        auto driver_result = pfnGetControlState( hDomainHandle, DomainControl, pControlState, pPendingAction );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetControlStateEpilogue( hDomainHandle, DomainControl, pControlState, pPendingAction ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetControlState", result);
        }

        return logAndPropagateResult("zesOverclockGetControlState", driver_result);
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
        context.logger->log_trace("zesOverclockGetVFPointValues(hDomainHandle, VFType, VFArrayType, PointIndex, PointValue)");

        auto pfnGetVFPointValues = context.zesDdiTable.Overclock.pfnGetVFPointValues;

        if( nullptr == pfnGetVFPointValues )
            return logAndPropagateResult("zesOverclockGetVFPointValues", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetVFPointValuesPrologue( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetVFPointValues", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetVFPointValuesPrologue( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetVFPointValues", result);
        }

        auto driver_result = pfnGetVFPointValues( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetVFPointValuesEpilogue( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockGetVFPointValues", result);
        }

        return logAndPropagateResult("zesOverclockGetVFPointValues", driver_result);
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
        context.logger->log_trace("zesOverclockSetVFPointValues(hDomainHandle, VFType, PointIndex, PointValue)");

        auto pfnSetVFPointValues = context.zesDdiTable.Overclock.pfnSetVFPointValues;

        if( nullptr == pfnSetVFPointValues )
            return logAndPropagateResult("zesOverclockSetVFPointValues", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockSetVFPointValuesPrologue( hDomainHandle, VFType, PointIndex, PointValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockSetVFPointValues", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockSetVFPointValuesPrologue( hDomainHandle, VFType, PointIndex, PointValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockSetVFPointValues", result);
        }

        auto driver_result = pfnSetVFPointValues( hDomainHandle, VFType, PointIndex, PointValue );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockSetVFPointValuesEpilogue( hDomainHandle, VFType, PointIndex, PointValue ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesOverclockSetVFPointValues", result);
        }

        return logAndPropagateResult("zesOverclockSetVFPointValues", driver_result);
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
        context.logger->log_trace("zesDeviceEnumDiagnosticTestSuites(hDevice, pCount, phDiagnostics)");

        auto pfnEnumDiagnosticTestSuites = context.zesDdiTable.Device.pfnEnumDiagnosticTestSuites;

        if( nullptr == pfnEnumDiagnosticTestSuites )
            return logAndPropagateResult("zesDeviceEnumDiagnosticTestSuites", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumDiagnosticTestSuitesPrologue( hDevice, pCount, phDiagnostics );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumDiagnosticTestSuites", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumDiagnosticTestSuitesPrologue( hDevice, pCount, phDiagnostics );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumDiagnosticTestSuites", result);
        }

        auto driver_result = pfnEnumDiagnosticTestSuites( hDevice, pCount, phDiagnostics );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumDiagnosticTestSuitesEpilogue( hDevice, pCount, phDiagnostics ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumDiagnosticTestSuites", result);
        }

        return logAndPropagateResult("zesDeviceEnumDiagnosticTestSuites", driver_result);
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
        context.logger->log_trace("zesDiagnosticsGetProperties(hDiagnostics, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.Diagnostics.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesDiagnosticsGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDiagnosticsGetPropertiesPrologue( hDiagnostics, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDiagnosticsGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDiagnosticsGetPropertiesPrologue( hDiagnostics, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDiagnosticsGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hDiagnostics, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDiagnosticsGetPropertiesEpilogue( hDiagnostics, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDiagnosticsGetProperties", result);
        }

        return logAndPropagateResult("zesDiagnosticsGetProperties", driver_result);
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
        context.logger->log_trace("zesDiagnosticsGetTests(hDiagnostics, pCount, pTests)");

        auto pfnGetTests = context.zesDdiTable.Diagnostics.pfnGetTests;

        if( nullptr == pfnGetTests )
            return logAndPropagateResult("zesDiagnosticsGetTests", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDiagnosticsGetTestsPrologue( hDiagnostics, pCount, pTests );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDiagnosticsGetTests", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDiagnosticsGetTestsPrologue( hDiagnostics, pCount, pTests );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDiagnosticsGetTests", result);
        }

        auto driver_result = pfnGetTests( hDiagnostics, pCount, pTests );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDiagnosticsGetTestsEpilogue( hDiagnostics, pCount, pTests ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDiagnosticsGetTests", result);
        }

        return logAndPropagateResult("zesDiagnosticsGetTests", driver_result);
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
        context.logger->log_trace("zesDiagnosticsRunTests(hDiagnostics, startIndex, endIndex, pResult)");

        auto pfnRunTests = context.zesDdiTable.Diagnostics.pfnRunTests;

        if( nullptr == pfnRunTests )
            return logAndPropagateResult("zesDiagnosticsRunTests", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDiagnosticsRunTestsPrologue( hDiagnostics, startIndex, endIndex, pResult );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDiagnosticsRunTests", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDiagnosticsRunTestsPrologue( hDiagnostics, startIndex, endIndex, pResult );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDiagnosticsRunTests", result);
        }

        auto driver_result = pfnRunTests( hDiagnostics, startIndex, endIndex, pResult );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDiagnosticsRunTestsEpilogue( hDiagnostics, startIndex, endIndex, pResult ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDiagnosticsRunTests", result);
        }

        return logAndPropagateResult("zesDiagnosticsRunTests", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEccAvailable
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEccAvailable(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        ze_bool_t* pAvailable                           ///< [out] ECC functionality is available (true)/unavailable (false).
        )
    {
        context.logger->log_trace("zesDeviceEccAvailable(hDevice, pAvailable)");

        auto pfnEccAvailable = context.zesDdiTable.Device.pfnEccAvailable;

        if( nullptr == pfnEccAvailable )
            return logAndPropagateResult("zesDeviceEccAvailable", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEccAvailablePrologue( hDevice, pAvailable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEccAvailable", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEccAvailablePrologue( hDevice, pAvailable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEccAvailable", result);
        }

        auto driver_result = pfnEccAvailable( hDevice, pAvailable );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEccAvailableEpilogue( hDevice, pAvailable ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEccAvailable", result);
        }

        return logAndPropagateResult("zesDeviceEccAvailable", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEccConfigurable
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEccConfigurable(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        ze_bool_t* pConfigurable                        ///< [out] ECC can be enabled/disabled (true)/enabled/disabled (false).
        )
    {
        context.logger->log_trace("zesDeviceEccConfigurable(hDevice, pConfigurable)");

        auto pfnEccConfigurable = context.zesDdiTable.Device.pfnEccConfigurable;

        if( nullptr == pfnEccConfigurable )
            return logAndPropagateResult("zesDeviceEccConfigurable", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEccConfigurablePrologue( hDevice, pConfigurable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEccConfigurable", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEccConfigurablePrologue( hDevice, pConfigurable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEccConfigurable", result);
        }

        auto driver_result = pfnEccConfigurable( hDevice, pConfigurable );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEccConfigurableEpilogue( hDevice, pConfigurable ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEccConfigurable", result);
        }

        return logAndPropagateResult("zesDeviceEccConfigurable", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetEccState
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGetEccState(
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        zes_device_ecc_properties_t* pState             ///< [out] ECC state, pending state, and pending action for state change.
        )
    {
        context.logger->log_trace("zesDeviceGetEccState(hDevice, pState)");

        auto pfnGetEccState = context.zesDdiTable.Device.pfnGetEccState;

        if( nullptr == pfnGetEccState )
            return logAndPropagateResult("zesDeviceGetEccState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetEccStatePrologue( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetEccState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetEccStatePrologue( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetEccState", result);
        }

        auto driver_result = pfnGetEccState( hDevice, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetEccStateEpilogue( hDevice, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetEccState", result);
        }

        return logAndPropagateResult("zesDeviceGetEccState", driver_result);
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
        context.logger->log_trace("zesDeviceSetEccState(hDevice, newState, pState)");

        auto pfnSetEccState = context.zesDdiTable.Device.pfnSetEccState;

        if( nullptr == pfnSetEccState )
            return logAndPropagateResult("zesDeviceSetEccState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceSetEccStatePrologue( hDevice, newState, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceSetEccState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceSetEccStatePrologue( hDevice, newState, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceSetEccState", result);
        }

        auto driver_result = pfnSetEccState( hDevice, newState, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceSetEccStateEpilogue( hDevice, newState, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceSetEccState", result);
        }

        return logAndPropagateResult("zesDeviceSetEccState", driver_result);
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
        context.logger->log_trace("zesDeviceEnumEngineGroups(hDevice, pCount, phEngine)");

        auto pfnEnumEngineGroups = context.zesDdiTable.Device.pfnEnumEngineGroups;

        if( nullptr == pfnEnumEngineGroups )
            return logAndPropagateResult("zesDeviceEnumEngineGroups", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumEngineGroupsPrologue( hDevice, pCount, phEngine );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumEngineGroups", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumEngineGroupsPrologue( hDevice, pCount, phEngine );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumEngineGroups", result);
        }

        auto driver_result = pfnEnumEngineGroups( hDevice, pCount, phEngine );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumEngineGroupsEpilogue( hDevice, pCount, phEngine ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumEngineGroups", result);
        }

        return logAndPropagateResult("zesDeviceEnumEngineGroups", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesEngineGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesEngineGetProperties(
        zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
        zes_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
        )
    {
        context.logger->log_trace("zesEngineGetProperties(hEngine, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.Engine.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesEngineGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesEngineGetPropertiesPrologue( hEngine, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesEngineGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesEngineGetPropertiesPrologue( hEngine, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesEngineGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hEngine, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesEngineGetPropertiesEpilogue( hEngine, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesEngineGetProperties", result);
        }

        return logAndPropagateResult("zesEngineGetProperties", driver_result);
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
        context.logger->log_trace("zesEngineGetActivity(hEngine, pStats)");

        auto pfnGetActivity = context.zesDdiTable.Engine.pfnGetActivity;

        if( nullptr == pfnGetActivity )
            return logAndPropagateResult("zesEngineGetActivity", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesEngineGetActivityPrologue( hEngine, pStats );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesEngineGetActivity", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesEngineGetActivityPrologue( hEngine, pStats );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesEngineGetActivity", result);
        }

        auto driver_result = pfnGetActivity( hEngine, pStats );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesEngineGetActivityEpilogue( hEngine, pStats ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesEngineGetActivity", result);
        }

        return logAndPropagateResult("zesEngineGetActivity", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceEventRegister
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceEventRegister(
        zes_device_handle_t hDevice,                    ///< [in] The device handle.
        zes_event_type_flags_t events                   ///< [in] List of events to listen to.
        )
    {
        context.logger->log_trace("zesDeviceEventRegister(hDevice, events)");

        auto pfnEventRegister = context.zesDdiTable.Device.pfnEventRegister;

        if( nullptr == pfnEventRegister )
            return logAndPropagateResult("zesDeviceEventRegister", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEventRegisterPrologue( hDevice, events );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEventRegister", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEventRegisterPrologue( hDevice, events );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEventRegister", result);
        }

        auto driver_result = pfnEventRegister( hDevice, events );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEventRegisterEpilogue( hDevice, events ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEventRegister", result);
        }

        return logAndPropagateResult("zesDeviceEventRegister", driver_result);
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
        context.logger->log_trace("zesDriverEventListen(hDriver, timeout, count, phDevicesLocal, pNumDeviceEvents, pEvents)");

        auto pfnEventListen = context.zesDdiTable.Driver.pfnEventListen;

        if( nullptr == pfnEventListen )
            return logAndPropagateResult("zesDriverEventListen", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverEventListenPrologue( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverEventListen", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverEventListenPrologue( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverEventListen", result);
        }

        auto driver_result = pfnEventListen( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverEventListenEpilogue( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverEventListen", result);
        }

        return logAndPropagateResult("zesDriverEventListen", driver_result);
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
        context.logger->log_trace("zesDriverEventListenEx(hDriver, timeout, count, phDevicesLocal, pNumDeviceEvents, pEvents)");

        auto pfnEventListenEx = context.zesDdiTable.Driver.pfnEventListenEx;

        if( nullptr == pfnEventListenEx )
            return logAndPropagateResult("zesDriverEventListenEx", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverEventListenExPrologue( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverEventListenEx", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverEventListenExPrologue( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverEventListenEx", result);
        }

        auto driver_result = pfnEventListenEx( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverEventListenExEpilogue( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverEventListenEx", result);
        }

        return logAndPropagateResult("zesDriverEventListenEx", driver_result);
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
        context.logger->log_trace("zesDeviceEnumFabricPorts(hDevice, pCount, phPort)");

        auto pfnEnumFabricPorts = context.zesDdiTable.Device.pfnEnumFabricPorts;

        if( nullptr == pfnEnumFabricPorts )
            return logAndPropagateResult("zesDeviceEnumFabricPorts", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFabricPortsPrologue( hDevice, pCount, phPort );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumFabricPorts", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumFabricPortsPrologue( hDevice, pCount, phPort );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumFabricPorts", result);
        }

        auto driver_result = pfnEnumFabricPorts( hDevice, pCount, phPort );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFabricPortsEpilogue( hDevice, pCount, phPort ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumFabricPorts", result);
        }

        return logAndPropagateResult("zesDeviceEnumFabricPorts", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetProperties(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
        )
    {
        context.logger->log_trace("zesFabricPortGetProperties(hPort, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.FabricPort.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesFabricPortGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetPropertiesPrologue( hPort, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetPropertiesPrologue( hPort, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hPort, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetPropertiesEpilogue( hPort, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetProperties", result);
        }

        return logAndPropagateResult("zesFabricPortGetProperties", driver_result);
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
        context.logger->log_trace("zesFabricPortGetLinkType(hPort, pLinkType)");

        auto pfnGetLinkType = context.zesDdiTable.FabricPort.pfnGetLinkType;

        if( nullptr == pfnGetLinkType )
            return logAndPropagateResult("zesFabricPortGetLinkType", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetLinkTypePrologue( hPort, pLinkType );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetLinkType", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetLinkTypePrologue( hPort, pLinkType );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetLinkType", result);
        }

        auto driver_result = pfnGetLinkType( hPort, pLinkType );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetLinkTypeEpilogue( hPort, pLinkType ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetLinkType", result);
        }

        return logAndPropagateResult("zesFabricPortGetLinkType", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetConfig(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
        )
    {
        context.logger->log_trace("zesFabricPortGetConfig(hPort, pConfig)");

        auto pfnGetConfig = context.zesDdiTable.FabricPort.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return logAndPropagateResult("zesFabricPortGetConfig", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetConfigPrologue( hPort, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetConfig", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetConfigPrologue( hPort, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetConfig", result);
        }

        auto driver_result = pfnGetConfig( hPort, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetConfigEpilogue( hPort, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetConfig", result);
        }

        return logAndPropagateResult("zesFabricPortGetConfig", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortSetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortSetConfig(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        const zes_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
        )
    {
        context.logger->log_trace("zesFabricPortSetConfig(hPort, pConfig)");

        auto pfnSetConfig = context.zesDdiTable.FabricPort.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return logAndPropagateResult("zesFabricPortSetConfig", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortSetConfigPrologue( hPort, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortSetConfig", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortSetConfigPrologue( hPort, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortSetConfig", result);
        }

        auto driver_result = pfnSetConfig( hPort, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortSetConfigEpilogue( hPort, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortSetConfig", result);
        }

        return logAndPropagateResult("zesFabricPortSetConfig", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetState(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
        )
    {
        context.logger->log_trace("zesFabricPortGetState(hPort, pState)");

        auto pfnGetState = context.zesDdiTable.FabricPort.pfnGetState;

        if( nullptr == pfnGetState )
            return logAndPropagateResult("zesFabricPortGetState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetStatePrologue( hPort, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetStatePrologue( hPort, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetState", result);
        }

        auto driver_result = pfnGetState( hPort, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetStateEpilogue( hPort, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetState", result);
        }

        return logAndPropagateResult("zesFabricPortGetState", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetThroughput
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetThroughput(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
        )
    {
        context.logger->log_trace("zesFabricPortGetThroughput(hPort, pThroughput)");

        auto pfnGetThroughput = context.zesDdiTable.FabricPort.pfnGetThroughput;

        if( nullptr == pfnGetThroughput )
            return logAndPropagateResult("zesFabricPortGetThroughput", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetThroughputPrologue( hPort, pThroughput );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetThroughput", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetThroughputPrologue( hPort, pThroughput );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetThroughput", result);
        }

        auto driver_result = pfnGetThroughput( hPort, pThroughput );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetThroughputEpilogue( hPort, pThroughput ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetThroughput", result);
        }

        return logAndPropagateResult("zesFabricPortGetThroughput", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFabricPortGetFabricErrorCounters
    __zedlllocal ze_result_t ZE_APICALL
    zesFabricPortGetFabricErrorCounters(
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_error_counters_t* pErrors       ///< [in,out] Will contain the Fabric port Error counters.
        )
    {
        context.logger->log_trace("zesFabricPortGetFabricErrorCounters(hPort, pErrors)");

        auto pfnGetFabricErrorCounters = context.zesDdiTable.FabricPort.pfnGetFabricErrorCounters;

        if( nullptr == pfnGetFabricErrorCounters )
            return logAndPropagateResult("zesFabricPortGetFabricErrorCounters", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetFabricErrorCountersPrologue( hPort, pErrors );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetFabricErrorCounters", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetFabricErrorCountersPrologue( hPort, pErrors );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetFabricErrorCounters", result);
        }

        auto driver_result = pfnGetFabricErrorCounters( hPort, pErrors );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetFabricErrorCountersEpilogue( hPort, pErrors ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetFabricErrorCounters", result);
        }

        return logAndPropagateResult("zesFabricPortGetFabricErrorCounters", driver_result);
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
        context.logger->log_trace("zesFabricPortGetMultiPortThroughput(hDevice, numPorts, phPortLocal, pThroughput)");

        auto pfnGetMultiPortThroughput = context.zesDdiTable.FabricPort.pfnGetMultiPortThroughput;

        if( nullptr == pfnGetMultiPortThroughput )
            return logAndPropagateResult("zesFabricPortGetMultiPortThroughput", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetMultiPortThroughputPrologue( hDevice, numPorts, phPort, pThroughput );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetMultiPortThroughput", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetMultiPortThroughputPrologue( hDevice, numPorts, phPort, pThroughput );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetMultiPortThroughput", result);
        }

        auto driver_result = pfnGetMultiPortThroughput( hDevice, numPorts, phPort, pThroughput );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetMultiPortThroughputEpilogue( hDevice, numPorts, phPort, pThroughput ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFabricPortGetMultiPortThroughput", result);
        }

        return logAndPropagateResult("zesFabricPortGetMultiPortThroughput", driver_result);
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
        context.logger->log_trace("zesDeviceEnumFans(hDevice, pCount, phFan)");

        auto pfnEnumFans = context.zesDdiTable.Device.pfnEnumFans;

        if( nullptr == pfnEnumFans )
            return logAndPropagateResult("zesDeviceEnumFans", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFansPrologue( hDevice, pCount, phFan );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumFans", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumFansPrologue( hDevice, pCount, phFan );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumFans", result);
        }

        auto driver_result = pfnEnumFans( hDevice, pCount, phFan );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFansEpilogue( hDevice, pCount, phFan ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumFans", result);
        }

        return logAndPropagateResult("zesDeviceEnumFans", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesFanGetProperties(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
        )
    {
        context.logger->log_trace("zesFanGetProperties(hFan, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.Fan.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesFanGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanGetPropertiesPrologue( hFan, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanGetPropertiesPrologue( hFan, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hFan, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanGetPropertiesEpilogue( hFan, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanGetProperties", result);
        }

        return logAndPropagateResult("zesFanGetProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanGetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesFanGetConfig(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
        )
    {
        context.logger->log_trace("zesFanGetConfig(hFan, pConfig)");

        auto pfnGetConfig = context.zesDdiTable.Fan.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return logAndPropagateResult("zesFanGetConfig", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanGetConfigPrologue( hFan, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanGetConfig", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanGetConfigPrologue( hFan, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanGetConfig", result);
        }

        auto driver_result = pfnGetConfig( hFan, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanGetConfigEpilogue( hFan, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanGetConfig", result);
        }

        return logAndPropagateResult("zesFanGetConfig", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanSetDefaultMode
    __zedlllocal ze_result_t ZE_APICALL
    zesFanSetDefaultMode(
        zes_fan_handle_t hFan                           ///< [in] Handle for the component.
        )
    {
        context.logger->log_trace("zesFanSetDefaultMode(hFan)");

        auto pfnSetDefaultMode = context.zesDdiTable.Fan.pfnSetDefaultMode;

        if( nullptr == pfnSetDefaultMode )
            return logAndPropagateResult("zesFanSetDefaultMode", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanSetDefaultModePrologue( hFan );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanSetDefaultMode", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanSetDefaultModePrologue( hFan );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanSetDefaultMode", result);
        }

        auto driver_result = pfnSetDefaultMode( hFan );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanSetDefaultModeEpilogue( hFan ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanSetDefaultMode", result);
        }

        return logAndPropagateResult("zesFanSetDefaultMode", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanSetFixedSpeedMode
    __zedlllocal ze_result_t ZE_APICALL
    zesFanSetFixedSpeedMode(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        const zes_fan_speed_t* speed                    ///< [in] The fixed fan speed setting
        )
    {
        context.logger->log_trace("zesFanSetFixedSpeedMode(hFan, speed)");

        auto pfnSetFixedSpeedMode = context.zesDdiTable.Fan.pfnSetFixedSpeedMode;

        if( nullptr == pfnSetFixedSpeedMode )
            return logAndPropagateResult("zesFanSetFixedSpeedMode", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanSetFixedSpeedModePrologue( hFan, speed );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanSetFixedSpeedMode", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanSetFixedSpeedModePrologue( hFan, speed );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanSetFixedSpeedMode", result);
        }

        auto driver_result = pfnSetFixedSpeedMode( hFan, speed );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanSetFixedSpeedModeEpilogue( hFan, speed ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanSetFixedSpeedMode", result);
        }

        return logAndPropagateResult("zesFanSetFixedSpeedMode", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFanSetSpeedTableMode
    __zedlllocal ze_result_t ZE_APICALL
    zesFanSetSpeedTableMode(
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        const zes_fan_speed_table_t* speedTable         ///< [in] A table containing temperature/speed pairs.
        )
    {
        context.logger->log_trace("zesFanSetSpeedTableMode(hFan, speedTable)");

        auto pfnSetSpeedTableMode = context.zesDdiTable.Fan.pfnSetSpeedTableMode;

        if( nullptr == pfnSetSpeedTableMode )
            return logAndPropagateResult("zesFanSetSpeedTableMode", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanSetSpeedTableModePrologue( hFan, speedTable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanSetSpeedTableMode", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanSetSpeedTableModePrologue( hFan, speedTable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanSetSpeedTableMode", result);
        }

        auto driver_result = pfnSetSpeedTableMode( hFan, speedTable );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanSetSpeedTableModeEpilogue( hFan, speedTable ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanSetSpeedTableMode", result);
        }

        return logAndPropagateResult("zesFanSetSpeedTableMode", driver_result);
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
        context.logger->log_trace("zesFanGetState(hFan, units, pSpeed)");

        auto pfnGetState = context.zesDdiTable.Fan.pfnGetState;

        if( nullptr == pfnGetState )
            return logAndPropagateResult("zesFanGetState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanGetStatePrologue( hFan, units, pSpeed );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanGetState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanGetStatePrologue( hFan, units, pSpeed );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanGetState", result);
        }

        auto driver_result = pfnGetState( hFan, units, pSpeed );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanGetStateEpilogue( hFan, units, pSpeed ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFanGetState", result);
        }

        return logAndPropagateResult("zesFanGetState", driver_result);
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
        context.logger->log_trace("zesDeviceEnumFirmwares(hDevice, pCount, phFirmware)");

        auto pfnEnumFirmwares = context.zesDdiTable.Device.pfnEnumFirmwares;

        if( nullptr == pfnEnumFirmwares )
            return logAndPropagateResult("zesDeviceEnumFirmwares", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFirmwaresPrologue( hDevice, pCount, phFirmware );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumFirmwares", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumFirmwaresPrologue( hDevice, pCount, phFirmware );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumFirmwares", result);
        }

        auto driver_result = pfnEnumFirmwares( hDevice, pCount, phFirmware );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFirmwaresEpilogue( hDevice, pCount, phFirmware ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumFirmwares", result);
        }

        return logAndPropagateResult("zesDeviceEnumFirmwares", driver_result);
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
        context.logger->log_trace("zesFirmwareGetProperties(hFirmware, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.Firmware.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesFirmwareGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetPropertiesPrologue( hFirmware, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFirmwareGetPropertiesPrologue( hFirmware, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hFirmware, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetPropertiesEpilogue( hFirmware, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareGetProperties", result);
        }

        return logAndPropagateResult("zesFirmwareGetProperties", driver_result);
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
        context.logger->log_trace("zesFirmwareFlash(hFirmware, pImage, size)");

        auto pfnFlash = context.zesDdiTable.Firmware.pfnFlash;

        if( nullptr == pfnFlash )
            return logAndPropagateResult("zesFirmwareFlash", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareFlashPrologue( hFirmware, pImage, size );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareFlash", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFirmwareFlashPrologue( hFirmware, pImage, size );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareFlash", result);
        }

        auto driver_result = pfnFlash( hFirmware, pImage, size );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareFlashEpilogue( hFirmware, pImage, size ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareFlash", result);
        }

        return logAndPropagateResult("zesFirmwareFlash", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFirmwareGetFlashProgress
    __zedlllocal ze_result_t ZE_APICALL
    zesFirmwareGetFlashProgress(
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        uint32_t* pCompletionPercent                    ///< [in,out] Pointer to the Completion Percentage of Firmware Update
        )
    {
        context.logger->log_trace("zesFirmwareGetFlashProgress(hFirmware, pCompletionPercent)");

        auto pfnGetFlashProgress = context.zesDdiTable.Firmware.pfnGetFlashProgress;

        if( nullptr == pfnGetFlashProgress )
            return logAndPropagateResult("zesFirmwareGetFlashProgress", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetFlashProgressPrologue( hFirmware, pCompletionPercent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareGetFlashProgress", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFirmwareGetFlashProgressPrologue( hFirmware, pCompletionPercent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareGetFlashProgress", result);
        }

        auto driver_result = pfnGetFlashProgress( hFirmware, pCompletionPercent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetFlashProgressEpilogue( hFirmware, pCompletionPercent ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareGetFlashProgress", result);
        }

        return logAndPropagateResult("zesFirmwareGetFlashProgress", driver_result);
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
        context.logger->log_trace("zesFirmwareGetConsoleLogs(hFirmware, pSize, pFirmwareLog)");

        auto pfnGetConsoleLogs = context.zesDdiTable.Firmware.pfnGetConsoleLogs;

        if( nullptr == pfnGetConsoleLogs )
            return logAndPropagateResult("zesFirmwareGetConsoleLogs", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetConsoleLogsPrologue( hFirmware, pSize, pFirmwareLog );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareGetConsoleLogs", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFirmwareGetConsoleLogsPrologue( hFirmware, pSize, pFirmwareLog );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareGetConsoleLogs", result);
        }

        auto driver_result = pfnGetConsoleLogs( hFirmware, pSize, pFirmwareLog );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetConsoleLogsEpilogue( hFirmware, pSize, pFirmwareLog ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareGetConsoleLogs", result);
        }

        return logAndPropagateResult("zesFirmwareGetConsoleLogs", driver_result);
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
        context.logger->log_trace("zesDeviceEnumFrequencyDomains(hDevice, pCount, phFrequency)");

        auto pfnEnumFrequencyDomains = context.zesDdiTable.Device.pfnEnumFrequencyDomains;

        if( nullptr == pfnEnumFrequencyDomains )
            return logAndPropagateResult("zesDeviceEnumFrequencyDomains", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFrequencyDomainsPrologue( hDevice, pCount, phFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumFrequencyDomains", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumFrequencyDomainsPrologue( hDevice, pCount, phFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumFrequencyDomains", result);
        }

        auto driver_result = pfnEnumFrequencyDomains( hDevice, pCount, phFrequency );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFrequencyDomainsEpilogue( hDevice, pCount, phFrequency ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumFrequencyDomains", result);
        }

        return logAndPropagateResult("zesDeviceEnumFrequencyDomains", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyGetProperties(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
        )
    {
        context.logger->log_trace("zesFrequencyGetProperties(hFrequency, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.Frequency.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesFrequencyGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetPropertiesPrologue( hFrequency, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyGetPropertiesPrologue( hFrequency, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hFrequency, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetPropertiesEpilogue( hFrequency, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyGetProperties", result);
        }

        return logAndPropagateResult("zesFrequencyGetProperties", driver_result);
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
        context.logger->log_trace("zesFrequencyGetAvailableClocks(hFrequency, pCount, phFrequency)");

        auto pfnGetAvailableClocks = context.zesDdiTable.Frequency.pfnGetAvailableClocks;

        if( nullptr == pfnGetAvailableClocks )
            return logAndPropagateResult("zesFrequencyGetAvailableClocks", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetAvailableClocksPrologue( hFrequency, pCount, phFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyGetAvailableClocks", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyGetAvailableClocksPrologue( hFrequency, pCount, phFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyGetAvailableClocks", result);
        }

        auto driver_result = pfnGetAvailableClocks( hFrequency, pCount, phFrequency );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetAvailableClocksEpilogue( hFrequency, pCount, phFrequency ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyGetAvailableClocks", result);
        }

        return logAndPropagateResult("zesFrequencyGetAvailableClocks", driver_result);
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
        context.logger->log_trace("zesFrequencyGetRange(hFrequency, pLimits)");

        auto pfnGetRange = context.zesDdiTable.Frequency.pfnGetRange;

        if( nullptr == pfnGetRange )
            return logAndPropagateResult("zesFrequencyGetRange", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetRangePrologue( hFrequency, pLimits );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyGetRange", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyGetRangePrologue( hFrequency, pLimits );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyGetRange", result);
        }

        auto driver_result = pfnGetRange( hFrequency, pLimits );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetRangeEpilogue( hFrequency, pLimits ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyGetRange", result);
        }

        return logAndPropagateResult("zesFrequencyGetRange", driver_result);
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
        context.logger->log_trace("zesFrequencySetRange(hFrequency, pLimits)");

        auto pfnSetRange = context.zesDdiTable.Frequency.pfnSetRange;

        if( nullptr == pfnSetRange )
            return logAndPropagateResult("zesFrequencySetRange", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencySetRangePrologue( hFrequency, pLimits );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencySetRange", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencySetRangePrologue( hFrequency, pLimits );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencySetRange", result);
        }

        auto driver_result = pfnSetRange( hFrequency, pLimits );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencySetRangeEpilogue( hFrequency, pLimits ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencySetRange", result);
        }

        return logAndPropagateResult("zesFrequencySetRange", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyGetState(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
        )
    {
        context.logger->log_trace("zesFrequencyGetState(hFrequency, pState)");

        auto pfnGetState = context.zesDdiTable.Frequency.pfnGetState;

        if( nullptr == pfnGetState )
            return logAndPropagateResult("zesFrequencyGetState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetStatePrologue( hFrequency, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyGetState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyGetStatePrologue( hFrequency, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyGetState", result);
        }

        auto driver_result = pfnGetState( hFrequency, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetStateEpilogue( hFrequency, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyGetState", result);
        }

        return logAndPropagateResult("zesFrequencyGetState", driver_result);
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
        context.logger->log_trace("zesFrequencyGetThrottleTime(hFrequency, pThrottleTime)");

        auto pfnGetThrottleTime = context.zesDdiTable.Frequency.pfnGetThrottleTime;

        if( nullptr == pfnGetThrottleTime )
            return logAndPropagateResult("zesFrequencyGetThrottleTime", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetThrottleTimePrologue( hFrequency, pThrottleTime );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyGetThrottleTime", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyGetThrottleTimePrologue( hFrequency, pThrottleTime );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyGetThrottleTime", result);
        }

        auto driver_result = pfnGetThrottleTime( hFrequency, pThrottleTime );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetThrottleTimeEpilogue( hFrequency, pThrottleTime ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyGetThrottleTime", result);
        }

        return logAndPropagateResult("zesFrequencyGetThrottleTime", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetCapabilities
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcGetCapabilities(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure.
        )
    {
        context.logger->log_trace("zesFrequencyOcGetCapabilities(hFrequency, pOcCapabilities)");

        auto pfnOcGetCapabilities = context.zesDdiTable.Frequency.pfnOcGetCapabilities;

        if( nullptr == pfnOcGetCapabilities )
            return logAndPropagateResult("zesFrequencyOcGetCapabilities", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetCapabilitiesPrologue( hFrequency, pOcCapabilities );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetCapabilities", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetCapabilitiesPrologue( hFrequency, pOcCapabilities );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetCapabilities", result);
        }

        auto driver_result = pfnOcGetCapabilities( hFrequency, pOcCapabilities );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetCapabilitiesEpilogue( hFrequency, pOcCapabilities ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetCapabilities", result);
        }

        return logAndPropagateResult("zesFrequencyOcGetCapabilities", driver_result);
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
        context.logger->log_trace("zesFrequencyOcGetFrequencyTarget(hFrequency, pCurrentOcFrequency)");

        auto pfnOcGetFrequencyTarget = context.zesDdiTable.Frequency.pfnOcGetFrequencyTarget;

        if( nullptr == pfnOcGetFrequencyTarget )
            return logAndPropagateResult("zesFrequencyOcGetFrequencyTarget", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetFrequencyTargetPrologue( hFrequency, pCurrentOcFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetFrequencyTarget", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetFrequencyTargetPrologue( hFrequency, pCurrentOcFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetFrequencyTarget", result);
        }

        auto driver_result = pfnOcGetFrequencyTarget( hFrequency, pCurrentOcFrequency );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetFrequencyTargetEpilogue( hFrequency, pCurrentOcFrequency ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetFrequencyTarget", result);
        }

        return logAndPropagateResult("zesFrequencyOcGetFrequencyTarget", driver_result);
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
        context.logger->log_trace("zesFrequencyOcSetFrequencyTarget(hFrequency, CurrentOcFrequency)");

        auto pfnOcSetFrequencyTarget = context.zesDdiTable.Frequency.pfnOcSetFrequencyTarget;

        if( nullptr == pfnOcSetFrequencyTarget )
            return logAndPropagateResult("zesFrequencyOcSetFrequencyTarget", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetFrequencyTargetPrologue( hFrequency, CurrentOcFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcSetFrequencyTarget", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcSetFrequencyTargetPrologue( hFrequency, CurrentOcFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcSetFrequencyTarget", result);
        }

        auto driver_result = pfnOcSetFrequencyTarget( hFrequency, CurrentOcFrequency );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetFrequencyTargetEpilogue( hFrequency, CurrentOcFrequency ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcSetFrequencyTarget", result);
        }

        return logAndPropagateResult("zesFrequencyOcSetFrequencyTarget", driver_result);
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
        context.logger->log_trace("zesFrequencyOcGetVoltageTarget(hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset)");

        auto pfnOcGetVoltageTarget = context.zesDdiTable.Frequency.pfnOcGetVoltageTarget;

        if( nullptr == pfnOcGetVoltageTarget )
            return logAndPropagateResult("zesFrequencyOcGetVoltageTarget", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetVoltageTargetPrologue( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetVoltageTarget", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetVoltageTargetPrologue( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetVoltageTarget", result);
        }

        auto driver_result = pfnOcGetVoltageTarget( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetVoltageTargetEpilogue( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetVoltageTarget", result);
        }

        return logAndPropagateResult("zesFrequencyOcGetVoltageTarget", driver_result);
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
        context.logger->log_trace("zesFrequencyOcSetVoltageTarget(hFrequency, CurrentVoltageTarget, CurrentVoltageOffset)");

        auto pfnOcSetVoltageTarget = context.zesDdiTable.Frequency.pfnOcSetVoltageTarget;

        if( nullptr == pfnOcSetVoltageTarget )
            return logAndPropagateResult("zesFrequencyOcSetVoltageTarget", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetVoltageTargetPrologue( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcSetVoltageTarget", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcSetVoltageTargetPrologue( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcSetVoltageTarget", result);
        }

        auto driver_result = pfnOcSetVoltageTarget( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetVoltageTargetEpilogue( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcSetVoltageTarget", result);
        }

        return logAndPropagateResult("zesFrequencyOcSetVoltageTarget", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetMode
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcSetMode(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_mode_t CurrentOcMode                     ///< [in] Current Overclocking Mode ::zes_oc_mode_t.
        )
    {
        context.logger->log_trace("zesFrequencyOcSetMode(hFrequency, CurrentOcMode)");

        auto pfnOcSetMode = context.zesDdiTable.Frequency.pfnOcSetMode;

        if( nullptr == pfnOcSetMode )
            return logAndPropagateResult("zesFrequencyOcSetMode", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetModePrologue( hFrequency, CurrentOcMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcSetMode", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcSetModePrologue( hFrequency, CurrentOcMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcSetMode", result);
        }

        auto driver_result = pfnOcSetMode( hFrequency, CurrentOcMode );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetModeEpilogue( hFrequency, CurrentOcMode ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcSetMode", result);
        }

        return logAndPropagateResult("zesFrequencyOcSetMode", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcGetMode
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcGetMode(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_mode_t* pCurrentOcMode                   ///< [out] Current Overclocking Mode ::zes_oc_mode_t.
        )
    {
        context.logger->log_trace("zesFrequencyOcGetMode(hFrequency, pCurrentOcMode)");

        auto pfnOcGetMode = context.zesDdiTable.Frequency.pfnOcGetMode;

        if( nullptr == pfnOcGetMode )
            return logAndPropagateResult("zesFrequencyOcGetMode", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetModePrologue( hFrequency, pCurrentOcMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetMode", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetModePrologue( hFrequency, pCurrentOcMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetMode", result);
        }

        auto driver_result = pfnOcGetMode( hFrequency, pCurrentOcMode );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetModeEpilogue( hFrequency, pCurrentOcMode ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetMode", result);
        }

        return logAndPropagateResult("zesFrequencyOcGetMode", driver_result);
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
        context.logger->log_trace("zesFrequencyOcGetIccMax(hFrequency, pOcIccMax)");

        auto pfnOcGetIccMax = context.zesDdiTable.Frequency.pfnOcGetIccMax;

        if( nullptr == pfnOcGetIccMax )
            return logAndPropagateResult("zesFrequencyOcGetIccMax", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetIccMaxPrologue( hFrequency, pOcIccMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetIccMax", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetIccMaxPrologue( hFrequency, pOcIccMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetIccMax", result);
        }

        auto driver_result = pfnOcGetIccMax( hFrequency, pOcIccMax );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetIccMaxEpilogue( hFrequency, pOcIccMax ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetIccMax", result);
        }

        return logAndPropagateResult("zesFrequencyOcGetIccMax", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetIccMax
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcSetIccMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
        )
    {
        context.logger->log_trace("zesFrequencyOcSetIccMax(hFrequency, ocIccMax)");

        auto pfnOcSetIccMax = context.zesDdiTable.Frequency.pfnOcSetIccMax;

        if( nullptr == pfnOcSetIccMax )
            return logAndPropagateResult("zesFrequencyOcSetIccMax", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetIccMaxPrologue( hFrequency, ocIccMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcSetIccMax", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcSetIccMaxPrologue( hFrequency, ocIccMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcSetIccMax", result);
        }

        auto driver_result = pfnOcSetIccMax( hFrequency, ocIccMax );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetIccMaxEpilogue( hFrequency, ocIccMax ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcSetIccMax", result);
        }

        return logAndPropagateResult("zesFrequencyOcSetIccMax", driver_result);
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
        context.logger->log_trace("zesFrequencyOcGetTjMax(hFrequency, pOcTjMax)");

        auto pfnOcGetTjMax = context.zesDdiTable.Frequency.pfnOcGetTjMax;

        if( nullptr == pfnOcGetTjMax )
            return logAndPropagateResult("zesFrequencyOcGetTjMax", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetTjMaxPrologue( hFrequency, pOcTjMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetTjMax", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetTjMaxPrologue( hFrequency, pOcTjMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetTjMax", result);
        }

        auto driver_result = pfnOcGetTjMax( hFrequency, pOcTjMax );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetTjMaxEpilogue( hFrequency, pOcTjMax ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcGetTjMax", result);
        }

        return logAndPropagateResult("zesFrequencyOcGetTjMax", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFrequencyOcSetTjMax
    __zedlllocal ze_result_t ZE_APICALL
    zesFrequencyOcSetTjMax(
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
        )
    {
        context.logger->log_trace("zesFrequencyOcSetTjMax(hFrequency, ocTjMax)");

        auto pfnOcSetTjMax = context.zesDdiTable.Frequency.pfnOcSetTjMax;

        if( nullptr == pfnOcSetTjMax )
            return logAndPropagateResult("zesFrequencyOcSetTjMax", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetTjMaxPrologue( hFrequency, ocTjMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcSetTjMax", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcSetTjMaxPrologue( hFrequency, ocTjMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcSetTjMax", result);
        }

        auto driver_result = pfnOcSetTjMax( hFrequency, ocTjMax );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetTjMaxEpilogue( hFrequency, ocTjMax ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFrequencyOcSetTjMax", result);
        }

        return logAndPropagateResult("zesFrequencyOcSetTjMax", driver_result);
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
        context.logger->log_trace("zesDeviceEnumLeds(hDevice, pCount, phLed)");

        auto pfnEnumLeds = context.zesDdiTable.Device.pfnEnumLeds;

        if( nullptr == pfnEnumLeds )
            return logAndPropagateResult("zesDeviceEnumLeds", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumLedsPrologue( hDevice, pCount, phLed );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumLeds", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumLedsPrologue( hDevice, pCount, phLed );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumLeds", result);
        }

        auto driver_result = pfnEnumLeds( hDevice, pCount, phLed );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumLedsEpilogue( hDevice, pCount, phLed ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumLeds", result);
        }

        return logAndPropagateResult("zesDeviceEnumLeds", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesLedGetProperties(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
        )
    {
        context.logger->log_trace("zesLedGetProperties(hLed, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.Led.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesLedGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedGetPropertiesPrologue( hLed, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesLedGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesLedGetPropertiesPrologue( hLed, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesLedGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hLed, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedGetPropertiesEpilogue( hLed, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesLedGetProperties", result);
        }

        return logAndPropagateResult("zesLedGetProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesLedGetState(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
        )
    {
        context.logger->log_trace("zesLedGetState(hLed, pState)");

        auto pfnGetState = context.zesDdiTable.Led.pfnGetState;

        if( nullptr == pfnGetState )
            return logAndPropagateResult("zesLedGetState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedGetStatePrologue( hLed, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesLedGetState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesLedGetStatePrologue( hLed, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesLedGetState", result);
        }

        auto driver_result = pfnGetState( hLed, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedGetStateEpilogue( hLed, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesLedGetState", result);
        }

        return logAndPropagateResult("zesLedGetState", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedSetState
    __zedlllocal ze_result_t ZE_APICALL
    zesLedSetState(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        ze_bool_t enable                                ///< [in] Set to TRUE to turn the LED on, FALSE to turn off.
        )
    {
        context.logger->log_trace("zesLedSetState(hLed, enable)");

        auto pfnSetState = context.zesDdiTable.Led.pfnSetState;

        if( nullptr == pfnSetState )
            return logAndPropagateResult("zesLedSetState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedSetStatePrologue( hLed, enable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesLedSetState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesLedSetStatePrologue( hLed, enable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesLedSetState", result);
        }

        auto driver_result = pfnSetState( hLed, enable );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedSetStateEpilogue( hLed, enable ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesLedSetState", result);
        }

        return logAndPropagateResult("zesLedSetState", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesLedSetColor
    __zedlllocal ze_result_t ZE_APICALL
    zesLedSetColor(
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        const zes_led_color_t* pColor                   ///< [in] New color of the LED.
        )
    {
        context.logger->log_trace("zesLedSetColor(hLed, pColor)");

        auto pfnSetColor = context.zesDdiTable.Led.pfnSetColor;

        if( nullptr == pfnSetColor )
            return logAndPropagateResult("zesLedSetColor", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedSetColorPrologue( hLed, pColor );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesLedSetColor", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesLedSetColorPrologue( hLed, pColor );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesLedSetColor", result);
        }

        auto driver_result = pfnSetColor( hLed, pColor );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedSetColorEpilogue( hLed, pColor ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesLedSetColor", result);
        }

        return logAndPropagateResult("zesLedSetColor", driver_result);
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
        context.logger->log_trace("zesDeviceEnumMemoryModules(hDevice, pCount, phMemory)");

        auto pfnEnumMemoryModules = context.zesDdiTable.Device.pfnEnumMemoryModules;

        if( nullptr == pfnEnumMemoryModules )
            return logAndPropagateResult("zesDeviceEnumMemoryModules", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumMemoryModulesPrologue( hDevice, pCount, phMemory );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumMemoryModules", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumMemoryModulesPrologue( hDevice, pCount, phMemory );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumMemoryModules", result);
        }

        auto driver_result = pfnEnumMemoryModules( hDevice, pCount, phMemory );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumMemoryModulesEpilogue( hDevice, pCount, phMemory ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumMemoryModules", result);
        }

        return logAndPropagateResult("zesDeviceEnumMemoryModules", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesMemoryGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesMemoryGetProperties(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
        )
    {
        context.logger->log_trace("zesMemoryGetProperties(hMemory, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.Memory.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesMemoryGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesMemoryGetPropertiesPrologue( hMemory, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesMemoryGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesMemoryGetPropertiesPrologue( hMemory, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesMemoryGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hMemory, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesMemoryGetPropertiesEpilogue( hMemory, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesMemoryGetProperties", result);
        }

        return logAndPropagateResult("zesMemoryGetProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesMemoryGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesMemoryGetState(
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
        )
    {
        context.logger->log_trace("zesMemoryGetState(hMemory, pState)");

        auto pfnGetState = context.zesDdiTable.Memory.pfnGetState;

        if( nullptr == pfnGetState )
            return logAndPropagateResult("zesMemoryGetState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesMemoryGetStatePrologue( hMemory, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesMemoryGetState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesMemoryGetStatePrologue( hMemory, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesMemoryGetState", result);
        }

        auto driver_result = pfnGetState( hMemory, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesMemoryGetStateEpilogue( hMemory, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesMemoryGetState", result);
        }

        return logAndPropagateResult("zesMemoryGetState", driver_result);
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
        context.logger->log_trace("zesMemoryGetBandwidth(hMemory, pBandwidth)");

        auto pfnGetBandwidth = context.zesDdiTable.Memory.pfnGetBandwidth;

        if( nullptr == pfnGetBandwidth )
            return logAndPropagateResult("zesMemoryGetBandwidth", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesMemoryGetBandwidthPrologue( hMemory, pBandwidth );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesMemoryGetBandwidth", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesMemoryGetBandwidthPrologue( hMemory, pBandwidth );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesMemoryGetBandwidth", result);
        }

        auto driver_result = pfnGetBandwidth( hMemory, pBandwidth );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesMemoryGetBandwidthEpilogue( hMemory, pBandwidth ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesMemoryGetBandwidth", result);
        }

        return logAndPropagateResult("zesMemoryGetBandwidth", driver_result);
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
        context.logger->log_trace("zesDeviceEnumPerformanceFactorDomains(hDevice, pCount, phPerf)");

        auto pfnEnumPerformanceFactorDomains = context.zesDdiTable.Device.pfnEnumPerformanceFactorDomains;

        if( nullptr == pfnEnumPerformanceFactorDomains )
            return logAndPropagateResult("zesDeviceEnumPerformanceFactorDomains", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumPerformanceFactorDomainsPrologue( hDevice, pCount, phPerf );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumPerformanceFactorDomains", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumPerformanceFactorDomainsPrologue( hDevice, pCount, phPerf );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumPerformanceFactorDomains", result);
        }

        auto driver_result = pfnEnumPerformanceFactorDomains( hDevice, pCount, phPerf );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumPerformanceFactorDomainsEpilogue( hDevice, pCount, phPerf ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumPerformanceFactorDomains", result);
        }

        return logAndPropagateResult("zesDeviceEnumPerformanceFactorDomains", driver_result);
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
        context.logger->log_trace("zesPerformanceFactorGetProperties(hPerf, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.PerformanceFactor.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesPerformanceFactorGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPerformanceFactorGetPropertiesPrologue( hPerf, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPerformanceFactorGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPerformanceFactorGetPropertiesPrologue( hPerf, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPerformanceFactorGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hPerf, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPerformanceFactorGetPropertiesEpilogue( hPerf, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPerformanceFactorGetProperties", result);
        }

        return logAndPropagateResult("zesPerformanceFactorGetProperties", driver_result);
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
        context.logger->log_trace("zesPerformanceFactorGetConfig(hPerf, pFactor)");

        auto pfnGetConfig = context.zesDdiTable.PerformanceFactor.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return logAndPropagateResult("zesPerformanceFactorGetConfig", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPerformanceFactorGetConfigPrologue( hPerf, pFactor );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPerformanceFactorGetConfig", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPerformanceFactorGetConfigPrologue( hPerf, pFactor );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPerformanceFactorGetConfig", result);
        }

        auto driver_result = pfnGetConfig( hPerf, pFactor );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPerformanceFactorGetConfigEpilogue( hPerf, pFactor ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPerformanceFactorGetConfig", result);
        }

        return logAndPropagateResult("zesPerformanceFactorGetConfig", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPerformanceFactorSetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesPerformanceFactorSetConfig(
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        double factor                                   ///< [in] The new Performance Factor.
        )
    {
        context.logger->log_trace("zesPerformanceFactorSetConfig(hPerf, factor)");

        auto pfnSetConfig = context.zesDdiTable.PerformanceFactor.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return logAndPropagateResult("zesPerformanceFactorSetConfig", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPerformanceFactorSetConfigPrologue( hPerf, factor );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPerformanceFactorSetConfig", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPerformanceFactorSetConfigPrologue( hPerf, factor );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPerformanceFactorSetConfig", result);
        }

        auto driver_result = pfnSetConfig( hPerf, factor );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPerformanceFactorSetConfigEpilogue( hPerf, factor ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPerformanceFactorSetConfig", result);
        }

        return logAndPropagateResult("zesPerformanceFactorSetConfig", driver_result);
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
        context.logger->log_trace("zesDeviceEnumPowerDomains(hDevice, pCount, phPower)");

        auto pfnEnumPowerDomains = context.zesDdiTable.Device.pfnEnumPowerDomains;

        if( nullptr == pfnEnumPowerDomains )
            return logAndPropagateResult("zesDeviceEnumPowerDomains", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumPowerDomainsPrologue( hDevice, pCount, phPower );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumPowerDomains", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumPowerDomainsPrologue( hDevice, pCount, phPower );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumPowerDomains", result);
        }

        auto driver_result = pfnEnumPowerDomains( hDevice, pCount, phPower );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumPowerDomainsEpilogue( hDevice, pCount, phPower ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumPowerDomains", result);
        }

        return logAndPropagateResult("zesDeviceEnumPowerDomains", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDeviceGetCardPowerDomain
    __zedlllocal ze_result_t ZE_APICALL
    zesDeviceGetCardPowerDomain(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pwr_handle_t* phPower                       ///< [in,out] power domain handle for the entire PCIe card.
        )
    {
        context.logger->log_trace("zesDeviceGetCardPowerDomain(hDevice, phPower)");

        auto pfnGetCardPowerDomain = context.zesDdiTable.Device.pfnGetCardPowerDomain;

        if( nullptr == pfnGetCardPowerDomain )
            return logAndPropagateResult("zesDeviceGetCardPowerDomain", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetCardPowerDomainPrologue( hDevice, phPower );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetCardPowerDomain", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetCardPowerDomainPrologue( hDevice, phPower );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetCardPowerDomain", result);
        }

        auto driver_result = pfnGetCardPowerDomain( hDevice, phPower );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetCardPowerDomainEpilogue( hDevice, phPower ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetCardPowerDomain", result);
        }

        return logAndPropagateResult("zesDeviceGetCardPowerDomain", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesPowerGetProperties(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        context.logger->log_trace("zesPowerGetProperties(hPower, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.Power.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesPowerGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetPropertiesPrologue( hPower, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerGetPropertiesPrologue( hPower, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hPower, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetPropertiesEpilogue( hPower, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerGetProperties", result);
        }

        return logAndPropagateResult("zesPowerGetProperties", driver_result);
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
        context.logger->log_trace("zesPowerGetEnergyCounter(hPower, pEnergy)");

        auto pfnGetEnergyCounter = context.zesDdiTable.Power.pfnGetEnergyCounter;

        if( nullptr == pfnGetEnergyCounter )
            return logAndPropagateResult("zesPowerGetEnergyCounter", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetEnergyCounterPrologue( hPower, pEnergy );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerGetEnergyCounter", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerGetEnergyCounterPrologue( hPower, pEnergy );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerGetEnergyCounter", result);
        }

        auto driver_result = pfnGetEnergyCounter( hPower, pEnergy );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetEnergyCounterEpilogue( hPower, pEnergy ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerGetEnergyCounter", result);
        }

        return logAndPropagateResult("zesPowerGetEnergyCounter", driver_result);
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
        context.logger->log_trace("zesPowerGetLimits(hPower, pSustained, pBurst, pPeak)");

        auto pfnGetLimits = context.zesDdiTable.Power.pfnGetLimits;

        if( nullptr == pfnGetLimits )
            return logAndPropagateResult("zesPowerGetLimits", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetLimitsPrologue( hPower, pSustained, pBurst, pPeak );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerGetLimits", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerGetLimitsPrologue( hPower, pSustained, pBurst, pPeak );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerGetLimits", result);
        }

        auto driver_result = pfnGetLimits( hPower, pSustained, pBurst, pPeak );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetLimitsEpilogue( hPower, pSustained, pBurst, pPeak ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerGetLimits", result);
        }

        return logAndPropagateResult("zesPowerGetLimits", driver_result);
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
        context.logger->log_trace("zesPowerSetLimits(hPower, pSustained, pBurst, pPeak)");

        auto pfnSetLimits = context.zesDdiTable.Power.pfnSetLimits;

        if( nullptr == pfnSetLimits )
            return logAndPropagateResult("zesPowerSetLimits", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerSetLimitsPrologue( hPower, pSustained, pBurst, pPeak );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerSetLimits", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerSetLimitsPrologue( hPower, pSustained, pBurst, pPeak );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerSetLimits", result);
        }

        auto driver_result = pfnSetLimits( hPower, pSustained, pBurst, pPeak );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerSetLimitsEpilogue( hPower, pSustained, pBurst, pPeak ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerSetLimits", result);
        }

        return logAndPropagateResult("zesPowerSetLimits", driver_result);
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
        context.logger->log_trace("zesPowerGetEnergyThreshold(hPower, pThreshold)");

        auto pfnGetEnergyThreshold = context.zesDdiTable.Power.pfnGetEnergyThreshold;

        if( nullptr == pfnGetEnergyThreshold )
            return logAndPropagateResult("zesPowerGetEnergyThreshold", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetEnergyThresholdPrologue( hPower, pThreshold );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerGetEnergyThreshold", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerGetEnergyThresholdPrologue( hPower, pThreshold );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerGetEnergyThreshold", result);
        }

        auto driver_result = pfnGetEnergyThreshold( hPower, pThreshold );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetEnergyThresholdEpilogue( hPower, pThreshold ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerGetEnergyThreshold", result);
        }

        return logAndPropagateResult("zesPowerGetEnergyThreshold", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPowerSetEnergyThreshold
    __zedlllocal ze_result_t ZE_APICALL
    zesPowerSetEnergyThreshold(
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        double threshold                                ///< [in] The energy threshold to be set in joules.
        )
    {
        context.logger->log_trace("zesPowerSetEnergyThreshold(hPower, threshold)");

        auto pfnSetEnergyThreshold = context.zesDdiTable.Power.pfnSetEnergyThreshold;

        if( nullptr == pfnSetEnergyThreshold )
            return logAndPropagateResult("zesPowerSetEnergyThreshold", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerSetEnergyThresholdPrologue( hPower, threshold );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerSetEnergyThreshold", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerSetEnergyThresholdPrologue( hPower, threshold );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerSetEnergyThreshold", result);
        }

        auto driver_result = pfnSetEnergyThreshold( hPower, threshold );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerSetEnergyThresholdEpilogue( hPower, threshold ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerSetEnergyThreshold", result);
        }

        return logAndPropagateResult("zesPowerSetEnergyThreshold", driver_result);
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
        context.logger->log_trace("zesDeviceEnumPsus(hDevice, pCount, phPsu)");

        auto pfnEnumPsus = context.zesDdiTable.Device.pfnEnumPsus;

        if( nullptr == pfnEnumPsus )
            return logAndPropagateResult("zesDeviceEnumPsus", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumPsusPrologue( hDevice, pCount, phPsu );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumPsus", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumPsusPrologue( hDevice, pCount, phPsu );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumPsus", result);
        }

        auto driver_result = pfnEnumPsus( hDevice, pCount, phPsu );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumPsusEpilogue( hDevice, pCount, phPsu ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumPsus", result);
        }

        return logAndPropagateResult("zesDeviceEnumPsus", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPsuGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesPsuGetProperties(
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
        )
    {
        context.logger->log_trace("zesPsuGetProperties(hPsu, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.Psu.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesPsuGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPsuGetPropertiesPrologue( hPsu, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPsuGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPsuGetPropertiesPrologue( hPsu, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPsuGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hPsu, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPsuGetPropertiesEpilogue( hPsu, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPsuGetProperties", result);
        }

        return logAndPropagateResult("zesPsuGetProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesPsuGetState
    __zedlllocal ze_result_t ZE_APICALL
    zesPsuGetState(
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
        )
    {
        context.logger->log_trace("zesPsuGetState(hPsu, pState)");

        auto pfnGetState = context.zesDdiTable.Psu.pfnGetState;

        if( nullptr == pfnGetState )
            return logAndPropagateResult("zesPsuGetState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPsuGetStatePrologue( hPsu, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPsuGetState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPsuGetStatePrologue( hPsu, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPsuGetState", result);
        }

        auto driver_result = pfnGetState( hPsu, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPsuGetStateEpilogue( hPsu, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPsuGetState", result);
        }

        return logAndPropagateResult("zesPsuGetState", driver_result);
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
        context.logger->log_trace("zesDeviceEnumRasErrorSets(hDevice, pCount, phRas)");

        auto pfnEnumRasErrorSets = context.zesDdiTable.Device.pfnEnumRasErrorSets;

        if( nullptr == pfnEnumRasErrorSets )
            return logAndPropagateResult("zesDeviceEnumRasErrorSets", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumRasErrorSetsPrologue( hDevice, pCount, phRas );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumRasErrorSets", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumRasErrorSetsPrologue( hDevice, pCount, phRas );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumRasErrorSets", result);
        }

        auto driver_result = pfnEnumRasErrorSets( hDevice, pCount, phRas );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumRasErrorSetsEpilogue( hDevice, pCount, phRas ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumRasErrorSets", result);
        }

        return logAndPropagateResult("zesDeviceEnumRasErrorSets", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesRasGetProperties(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
        )
    {
        context.logger->log_trace("zesRasGetProperties(hRas, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.Ras.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesRasGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetPropertiesPrologue( hRas, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasGetPropertiesPrologue( hRas, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hRas, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetPropertiesEpilogue( hRas, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasGetProperties", result);
        }

        return logAndPropagateResult("zesRasGetProperties", driver_result);
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
        context.logger->log_trace("zesRasGetConfig(hRas, pConfig)");

        auto pfnGetConfig = context.zesDdiTable.Ras.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return logAndPropagateResult("zesRasGetConfig", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetConfigPrologue( hRas, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasGetConfig", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasGetConfigPrologue( hRas, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasGetConfig", result);
        }

        auto driver_result = pfnGetConfig( hRas, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetConfigEpilogue( hRas, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasGetConfig", result);
        }

        return logAndPropagateResult("zesRasGetConfig", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasSetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesRasSetConfig(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        const zes_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
        )
    {
        context.logger->log_trace("zesRasSetConfig(hRas, pConfig)");

        auto pfnSetConfig = context.zesDdiTable.Ras.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return logAndPropagateResult("zesRasSetConfig", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasSetConfigPrologue( hRas, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasSetConfig", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasSetConfigPrologue( hRas, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasSetConfig", result);
        }

        auto driver_result = pfnSetConfig( hRas, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasSetConfigEpilogue( hRas, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasSetConfig", result);
        }

        return logAndPropagateResult("zesRasSetConfig", driver_result);
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
        context.logger->log_trace("zesRasGetState(hRas, clear, pState)");

        auto pfnGetState = context.zesDdiTable.Ras.pfnGetState;

        if( nullptr == pfnGetState )
            return logAndPropagateResult("zesRasGetState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetStatePrologue( hRas, clear, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasGetState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasGetStatePrologue( hRas, clear, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasGetState", result);
        }

        auto driver_result = pfnGetState( hRas, clear, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetStateEpilogue( hRas, clear, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasGetState", result);
        }

        return logAndPropagateResult("zesRasGetState", driver_result);
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
        context.logger->log_trace("zesDeviceEnumSchedulers(hDevice, pCount, phScheduler)");

        auto pfnEnumSchedulers = context.zesDdiTable.Device.pfnEnumSchedulers;

        if( nullptr == pfnEnumSchedulers )
            return logAndPropagateResult("zesDeviceEnumSchedulers", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumSchedulersPrologue( hDevice, pCount, phScheduler );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumSchedulers", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumSchedulersPrologue( hDevice, pCount, phScheduler );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumSchedulers", result);
        }

        auto driver_result = pfnEnumSchedulers( hDevice, pCount, phScheduler );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumSchedulersEpilogue( hDevice, pCount, phScheduler ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumSchedulers", result);
        }

        return logAndPropagateResult("zesDeviceEnumSchedulers", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesSchedulerGetProperties(
        zes_sched_handle_t hScheduler,                  ///< [in] Handle for the component.
        zes_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
        )
    {
        context.logger->log_trace("zesSchedulerGetProperties(hScheduler, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.Scheduler.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesSchedulerGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetPropertiesPrologue( hScheduler, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerGetPropertiesPrologue( hScheduler, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hScheduler, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetPropertiesEpilogue( hScheduler, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerGetProperties", result);
        }

        return logAndPropagateResult("zesSchedulerGetProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesSchedulerGetCurrentMode
    __zedlllocal ze_result_t ZE_APICALL
    zesSchedulerGetCurrentMode(
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
        )
    {
        context.logger->log_trace("zesSchedulerGetCurrentMode(hScheduler, pMode)");

        auto pfnGetCurrentMode = context.zesDdiTable.Scheduler.pfnGetCurrentMode;

        if( nullptr == pfnGetCurrentMode )
            return logAndPropagateResult("zesSchedulerGetCurrentMode", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetCurrentModePrologue( hScheduler, pMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerGetCurrentMode", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerGetCurrentModePrologue( hScheduler, pMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerGetCurrentMode", result);
        }

        auto driver_result = pfnGetCurrentMode( hScheduler, pMode );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetCurrentModeEpilogue( hScheduler, pMode ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerGetCurrentMode", result);
        }

        return logAndPropagateResult("zesSchedulerGetCurrentMode", driver_result);
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
        context.logger->log_trace("zesSchedulerGetTimeoutModeProperties(hScheduler, getDefaults, pConfig)");

        auto pfnGetTimeoutModeProperties = context.zesDdiTable.Scheduler.pfnGetTimeoutModeProperties;

        if( nullptr == pfnGetTimeoutModeProperties )
            return logAndPropagateResult("zesSchedulerGetTimeoutModeProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetTimeoutModePropertiesPrologue( hScheduler, getDefaults, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerGetTimeoutModeProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerGetTimeoutModePropertiesPrologue( hScheduler, getDefaults, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerGetTimeoutModeProperties", result);
        }

        auto driver_result = pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetTimeoutModePropertiesEpilogue( hScheduler, getDefaults, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerGetTimeoutModeProperties", result);
        }

        return logAndPropagateResult("zesSchedulerGetTimeoutModeProperties", driver_result);
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
        context.logger->log_trace("zesSchedulerGetTimesliceModeProperties(hScheduler, getDefaults, pConfig)");

        auto pfnGetTimesliceModeProperties = context.zesDdiTable.Scheduler.pfnGetTimesliceModeProperties;

        if( nullptr == pfnGetTimesliceModeProperties )
            return logAndPropagateResult("zesSchedulerGetTimesliceModeProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetTimesliceModePropertiesPrologue( hScheduler, getDefaults, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerGetTimesliceModeProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerGetTimesliceModePropertiesPrologue( hScheduler, getDefaults, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerGetTimesliceModeProperties", result);
        }

        auto driver_result = pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetTimesliceModePropertiesEpilogue( hScheduler, getDefaults, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerGetTimesliceModeProperties", result);
        }

        return logAndPropagateResult("zesSchedulerGetTimesliceModeProperties", driver_result);
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
        context.logger->log_trace("zesSchedulerSetTimeoutMode(hScheduler, pProperties, pNeedReload)");

        auto pfnSetTimeoutMode = context.zesDdiTable.Scheduler.pfnSetTimeoutMode;

        if( nullptr == pfnSetTimeoutMode )
            return logAndPropagateResult("zesSchedulerSetTimeoutMode", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetTimeoutModePrologue( hScheduler, pProperties, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerSetTimeoutMode", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerSetTimeoutModePrologue( hScheduler, pProperties, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerSetTimeoutMode", result);
        }

        auto driver_result = pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetTimeoutModeEpilogue( hScheduler, pProperties, pNeedReload ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerSetTimeoutMode", result);
        }

        return logAndPropagateResult("zesSchedulerSetTimeoutMode", driver_result);
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
        context.logger->log_trace("zesSchedulerSetTimesliceMode(hScheduler, pProperties, pNeedReload)");

        auto pfnSetTimesliceMode = context.zesDdiTable.Scheduler.pfnSetTimesliceMode;

        if( nullptr == pfnSetTimesliceMode )
            return logAndPropagateResult("zesSchedulerSetTimesliceMode", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetTimesliceModePrologue( hScheduler, pProperties, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerSetTimesliceMode", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerSetTimesliceModePrologue( hScheduler, pProperties, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerSetTimesliceMode", result);
        }

        auto driver_result = pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetTimesliceModeEpilogue( hScheduler, pProperties, pNeedReload ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerSetTimesliceMode", result);
        }

        return logAndPropagateResult("zesSchedulerSetTimesliceMode", driver_result);
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
        context.logger->log_trace("zesSchedulerSetExclusiveMode(hScheduler, pNeedReload)");

        auto pfnSetExclusiveMode = context.zesDdiTable.Scheduler.pfnSetExclusiveMode;

        if( nullptr == pfnSetExclusiveMode )
            return logAndPropagateResult("zesSchedulerSetExclusiveMode", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetExclusiveModePrologue( hScheduler, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerSetExclusiveMode", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerSetExclusiveModePrologue( hScheduler, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerSetExclusiveMode", result);
        }

        auto driver_result = pfnSetExclusiveMode( hScheduler, pNeedReload );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetExclusiveModeEpilogue( hScheduler, pNeedReload ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerSetExclusiveMode", result);
        }

        return logAndPropagateResult("zesSchedulerSetExclusiveMode", driver_result);
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
        context.logger->log_trace("zesSchedulerSetComputeUnitDebugMode(hScheduler, pNeedReload)");

        auto pfnSetComputeUnitDebugMode = context.zesDdiTable.Scheduler.pfnSetComputeUnitDebugMode;

        if( nullptr == pfnSetComputeUnitDebugMode )
            return logAndPropagateResult("zesSchedulerSetComputeUnitDebugMode", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetComputeUnitDebugModePrologue( hScheduler, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerSetComputeUnitDebugMode", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerSetComputeUnitDebugModePrologue( hScheduler, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerSetComputeUnitDebugMode", result);
        }

        auto driver_result = pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetComputeUnitDebugModeEpilogue( hScheduler, pNeedReload ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesSchedulerSetComputeUnitDebugMode", result);
        }

        return logAndPropagateResult("zesSchedulerSetComputeUnitDebugMode", driver_result);
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
        context.logger->log_trace("zesDeviceEnumStandbyDomains(hDevice, pCount, phStandby)");

        auto pfnEnumStandbyDomains = context.zesDdiTable.Device.pfnEnumStandbyDomains;

        if( nullptr == pfnEnumStandbyDomains )
            return logAndPropagateResult("zesDeviceEnumStandbyDomains", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumStandbyDomainsPrologue( hDevice, pCount, phStandby );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumStandbyDomains", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumStandbyDomainsPrologue( hDevice, pCount, phStandby );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumStandbyDomains", result);
        }

        auto driver_result = pfnEnumStandbyDomains( hDevice, pCount, phStandby );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumStandbyDomainsEpilogue( hDevice, pCount, phStandby ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumStandbyDomains", result);
        }

        return logAndPropagateResult("zesDeviceEnumStandbyDomains", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesStandbyGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesStandbyGetProperties(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
        )
    {
        context.logger->log_trace("zesStandbyGetProperties(hStandby, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.Standby.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesStandbyGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesStandbyGetPropertiesPrologue( hStandby, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesStandbyGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesStandbyGetPropertiesPrologue( hStandby, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesStandbyGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hStandby, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesStandbyGetPropertiesEpilogue( hStandby, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesStandbyGetProperties", result);
        }

        return logAndPropagateResult("zesStandbyGetProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesStandbyGetMode
    __zedlllocal ze_result_t ZE_APICALL
    zesStandbyGetMode(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
        )
    {
        context.logger->log_trace("zesStandbyGetMode(hStandby, pMode)");

        auto pfnGetMode = context.zesDdiTable.Standby.pfnGetMode;

        if( nullptr == pfnGetMode )
            return logAndPropagateResult("zesStandbyGetMode", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesStandbyGetModePrologue( hStandby, pMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesStandbyGetMode", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesStandbyGetModePrologue( hStandby, pMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesStandbyGetMode", result);
        }

        auto driver_result = pfnGetMode( hStandby, pMode );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesStandbyGetModeEpilogue( hStandby, pMode ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesStandbyGetMode", result);
        }

        return logAndPropagateResult("zesStandbyGetMode", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesStandbySetMode
    __zedlllocal ze_result_t ZE_APICALL
    zesStandbySetMode(
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t mode                   ///< [in] New standby mode.
        )
    {
        context.logger->log_trace("zesStandbySetMode(hStandby, mode)");

        auto pfnSetMode = context.zesDdiTable.Standby.pfnSetMode;

        if( nullptr == pfnSetMode )
            return logAndPropagateResult("zesStandbySetMode", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesStandbySetModePrologue( hStandby, mode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesStandbySetMode", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesStandbySetModePrologue( hStandby, mode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesStandbySetMode", result);
        }

        auto driver_result = pfnSetMode( hStandby, mode );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesStandbySetModeEpilogue( hStandby, mode ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesStandbySetMode", result);
        }

        return logAndPropagateResult("zesStandbySetMode", driver_result);
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
        context.logger->log_trace("zesDeviceEnumTemperatureSensors(hDevice, pCount, phTemperature)");

        auto pfnEnumTemperatureSensors = context.zesDdiTable.Device.pfnEnumTemperatureSensors;

        if( nullptr == pfnEnumTemperatureSensors )
            return logAndPropagateResult("zesDeviceEnumTemperatureSensors", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumTemperatureSensorsPrologue( hDevice, pCount, phTemperature );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumTemperatureSensors", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumTemperatureSensorsPrologue( hDevice, pCount, phTemperature );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumTemperatureSensors", result);
        }

        auto driver_result = pfnEnumTemperatureSensors( hDevice, pCount, phTemperature );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumTemperatureSensorsEpilogue( hDevice, pCount, phTemperature ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumTemperatureSensors", result);
        }

        return logAndPropagateResult("zesDeviceEnumTemperatureSensors", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesTemperatureGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zesTemperatureGetProperties(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
        )
    {
        context.logger->log_trace("zesTemperatureGetProperties(hTemperature, pProperties)");

        auto pfnGetProperties = context.zesDdiTable.Temperature.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zesTemperatureGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureGetPropertiesPrologue( hTemperature, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesTemperatureGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesTemperatureGetPropertiesPrologue( hTemperature, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesTemperatureGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hTemperature, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureGetPropertiesEpilogue( hTemperature, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesTemperatureGetProperties", result);
        }

        return logAndPropagateResult("zesTemperatureGetProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesTemperatureGetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesTemperatureGetConfig(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
        )
    {
        context.logger->log_trace("zesTemperatureGetConfig(hTemperature, pConfig)");

        auto pfnGetConfig = context.zesDdiTable.Temperature.pfnGetConfig;

        if( nullptr == pfnGetConfig )
            return logAndPropagateResult("zesTemperatureGetConfig", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureGetConfigPrologue( hTemperature, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesTemperatureGetConfig", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesTemperatureGetConfigPrologue( hTemperature, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesTemperatureGetConfig", result);
        }

        auto driver_result = pfnGetConfig( hTemperature, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureGetConfigEpilogue( hTemperature, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesTemperatureGetConfig", result);
        }

        return logAndPropagateResult("zesTemperatureGetConfig", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesTemperatureSetConfig
    __zedlllocal ze_result_t ZE_APICALL
    zesTemperatureSetConfig(
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        const zes_temp_config_t* pConfig                ///< [in] New configuration.
        )
    {
        context.logger->log_trace("zesTemperatureSetConfig(hTemperature, pConfig)");

        auto pfnSetConfig = context.zesDdiTable.Temperature.pfnSetConfig;

        if( nullptr == pfnSetConfig )
            return logAndPropagateResult("zesTemperatureSetConfig", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureSetConfigPrologue( hTemperature, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesTemperatureSetConfig", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesTemperatureSetConfigPrologue( hTemperature, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesTemperatureSetConfig", result);
        }

        auto driver_result = pfnSetConfig( hTemperature, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureSetConfigEpilogue( hTemperature, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesTemperatureSetConfig", result);
        }

        return logAndPropagateResult("zesTemperatureSetConfig", driver_result);
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
        context.logger->log_trace("zesTemperatureGetState(hTemperature, pTemperature)");

        auto pfnGetState = context.zesDdiTable.Temperature.pfnGetState;

        if( nullptr == pfnGetState )
            return logAndPropagateResult("zesTemperatureGetState", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureGetStatePrologue( hTemperature, pTemperature );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesTemperatureGetState", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesTemperatureGetStatePrologue( hTemperature, pTemperature );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesTemperatureGetState", result);
        }

        auto driver_result = pfnGetState( hTemperature, pTemperature );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureGetStateEpilogue( hTemperature, pTemperature ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesTemperatureGetState", result);
        }

        return logAndPropagateResult("zesTemperatureGetState", driver_result);
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
        context.logger->log_trace("zesPowerGetLimitsExt(hPower, pCount, pSustained)");

        auto pfnGetLimitsExt = context.zesDdiTable.Power.pfnGetLimitsExt;

        if( nullptr == pfnGetLimitsExt )
            return logAndPropagateResult("zesPowerGetLimitsExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetLimitsExtPrologue( hPower, pCount, pSustained );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerGetLimitsExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerGetLimitsExtPrologue( hPower, pCount, pSustained );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerGetLimitsExt", result);
        }

        auto driver_result = pfnGetLimitsExt( hPower, pCount, pSustained );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetLimitsExtEpilogue( hPower, pCount, pSustained ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerGetLimitsExt", result);
        }

        return logAndPropagateResult("zesPowerGetLimitsExt", driver_result);
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
        context.logger->log_trace("zesPowerSetLimitsExt(hPower, pCount, pSustained)");

        auto pfnSetLimitsExt = context.zesDdiTable.Power.pfnSetLimitsExt;

        if( nullptr == pfnSetLimitsExt )
            return logAndPropagateResult("zesPowerSetLimitsExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerSetLimitsExtPrologue( hPower, pCount, pSustained );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerSetLimitsExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerSetLimitsExtPrologue( hPower, pCount, pSustained );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerSetLimitsExt", result);
        }

        auto driver_result = pfnSetLimitsExt( hPower, pCount, pSustained );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerSetLimitsExtEpilogue( hPower, pCount, pSustained ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesPowerSetLimitsExt", result);
        }

        return logAndPropagateResult("zesPowerSetLimitsExt", driver_result);
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
        context.logger->log_trace("zesEngineGetActivityExt(hEngine, pCount, pStats)");

        auto pfnGetActivityExt = context.zesDdiTable.Engine.pfnGetActivityExt;

        if( nullptr == pfnGetActivityExt )
            return logAndPropagateResult("zesEngineGetActivityExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesEngineGetActivityExtPrologue( hEngine, pCount, pStats );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesEngineGetActivityExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesEngineGetActivityExtPrologue( hEngine, pCount, pStats );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesEngineGetActivityExt", result);
        }

        auto driver_result = pfnGetActivityExt( hEngine, pCount, pStats );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesEngineGetActivityExtEpilogue( hEngine, pCount, pStats ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesEngineGetActivityExt", result);
        }

        return logAndPropagateResult("zesEngineGetActivityExt", driver_result);
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
        context.logger->log_trace("zesRasGetStateExp(hRas, pCount, pState)");

        auto pfnGetStateExp = context.zesDdiTable.RasExp.pfnGetStateExp;

        if( nullptr == pfnGetStateExp )
            return logAndPropagateResult("zesRasGetStateExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetStateExpPrologue( hRas, pCount, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasGetStateExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasGetStateExpPrologue( hRas, pCount, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasGetStateExp", result);
        }

        auto driver_result = pfnGetStateExp( hRas, pCount, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetStateExpEpilogue( hRas, pCount, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasGetStateExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zesRasGetStateExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesRasClearStateExp
    __zedlllocal ze_result_t ZE_APICALL
    zesRasClearStateExp(
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_error_category_exp_t category           ///< [in] category for which error counter is to be cleared.
        )
    {
        context.logger->log_trace("zesRasClearStateExp(hRas, category)");

        auto pfnClearStateExp = context.zesDdiTable.RasExp.pfnClearStateExp;

        if( nullptr == pfnClearStateExp )
            return logAndPropagateResult("zesRasClearStateExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasClearStateExpPrologue( hRas, category );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasClearStateExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasClearStateExpPrologue( hRas, category );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasClearStateExp", result);
        }

        auto driver_result = pfnClearStateExp( hRas, category );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasClearStateExpEpilogue( hRas, category ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesRasClearStateExp", result);
        }

        return logAndPropagateResult("zesRasClearStateExp", driver_result);
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
        context.logger->log_trace("zesFirmwareGetSecurityVersionExp(hFirmware, pVersion)");

        auto pfnGetSecurityVersionExp = context.zesDdiTable.FirmwareExp.pfnGetSecurityVersionExp;

        if( nullptr == pfnGetSecurityVersionExp )
            return logAndPropagateResult("zesFirmwareGetSecurityVersionExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetSecurityVersionExpPrologue( hFirmware, pVersion );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareGetSecurityVersionExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFirmwareGetSecurityVersionExpPrologue( hFirmware, pVersion );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareGetSecurityVersionExp", result);
        }

        auto driver_result = pfnGetSecurityVersionExp( hFirmware, pVersion );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetSecurityVersionExpEpilogue( hFirmware, pVersion ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareGetSecurityVersionExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zesFirmwareGetSecurityVersionExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesFirmwareSetSecurityVersionExp
    __zedlllocal ze_result_t ZE_APICALL
    zesFirmwareSetSecurityVersionExp(
        zes_firmware_handle_t hFirmware                 ///< [in] Handle for the component.
        )
    {
        context.logger->log_trace("zesFirmwareSetSecurityVersionExp(hFirmware)");

        auto pfnSetSecurityVersionExp = context.zesDdiTable.FirmwareExp.pfnSetSecurityVersionExp;

        if( nullptr == pfnSetSecurityVersionExp )
            return logAndPropagateResult("zesFirmwareSetSecurityVersionExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareSetSecurityVersionExpPrologue( hFirmware );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareSetSecurityVersionExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFirmwareSetSecurityVersionExpPrologue( hFirmware );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareSetSecurityVersionExp", result);
        }

        auto driver_result = pfnSetSecurityVersionExp( hFirmware );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareSetSecurityVersionExpEpilogue( hFirmware ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesFirmwareSetSecurityVersionExp", result);
        }

        return logAndPropagateResult("zesFirmwareSetSecurityVersionExp", driver_result);
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
        context.logger->log_trace("zesDeviceGetSubDevicePropertiesExp(hDevice, pCount, pSubdeviceProps)");

        auto pfnGetSubDevicePropertiesExp = context.zesDdiTable.DeviceExp.pfnGetSubDevicePropertiesExp;

        if( nullptr == pfnGetSubDevicePropertiesExp )
            return logAndPropagateResult("zesDeviceGetSubDevicePropertiesExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetSubDevicePropertiesExpPrologue( hDevice, pCount, pSubdeviceProps );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetSubDevicePropertiesExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetSubDevicePropertiesExpPrologue( hDevice, pCount, pSubdeviceProps );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetSubDevicePropertiesExp", result);
        }

        auto driver_result = pfnGetSubDevicePropertiesExp( hDevice, pCount, pSubdeviceProps );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetSubDevicePropertiesExpEpilogue( hDevice, pCount, pSubdeviceProps ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceGetSubDevicePropertiesExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zesDeviceGetSubDevicePropertiesExp", driver_result);
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
        context.logger->log_trace("zesDriverGetDeviceByUuidExp(hDriver, uuid, phDevice, onSubdevice, subdeviceId)");

        auto pfnGetDeviceByUuidExp = context.zesDdiTable.DriverExp.pfnGetDeviceByUuidExp;

        if( nullptr == pfnGetDeviceByUuidExp )
            return logAndPropagateResult("zesDriverGetDeviceByUuidExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetDeviceByUuidExpPrologue( hDriver, uuid, phDevice, onSubdevice, subdeviceId );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverGetDeviceByUuidExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverGetDeviceByUuidExpPrologue( hDriver, uuid, phDevice, onSubdevice, subdeviceId );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverGetDeviceByUuidExp", result);
        }

        auto driver_result = pfnGetDeviceByUuidExp( hDriver, uuid, phDevice, onSubdevice, subdeviceId );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetDeviceByUuidExpEpilogue( hDriver, uuid, phDevice, onSubdevice, subdeviceId ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDriverGetDeviceByUuidExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phDevice){
                context.handleLifetime->addHandle( *phDevice );
                context.handleLifetime->addDependent( hDriver, *phDevice );

            }
        }
        return logAndPropagateResult("zesDriverGetDeviceByUuidExp", driver_result);
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
        context.logger->log_trace("zesDeviceEnumActiveVFExp(hDevice, pCount, phVFhandle)");

        auto pfnEnumActiveVFExp = context.zesDdiTable.DeviceExp.pfnEnumActiveVFExp;

        if( nullptr == pfnEnumActiveVFExp )
            return logAndPropagateResult("zesDeviceEnumActiveVFExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumActiveVFExpPrologue( hDevice, pCount, phVFhandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumActiveVFExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumActiveVFExpPrologue( hDevice, pCount, phVFhandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumActiveVFExp", result);
        }

        auto driver_result = pfnEnumActiveVFExp( hDevice, pCount, phVFhandle );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumActiveVFExpEpilogue( hDevice, pCount, phVFhandle ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumActiveVFExp", result);
        }

        return logAndPropagateResult("zesDeviceEnumActiveVFExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesVFManagementGetVFPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zesVFManagementGetVFPropertiesExp(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
        zes_vf_exp_properties_t* pProperties            ///< [in,out] Will contain VF properties.
        )
    {
        context.logger->log_trace("zesVFManagementGetVFPropertiesExp(hVFhandle, pProperties)");

        auto pfnGetVFPropertiesExp = context.zesDdiTable.VFManagementExp.pfnGetVFPropertiesExp;

        if( nullptr == pfnGetVFPropertiesExp )
            return logAndPropagateResult("zesVFManagementGetVFPropertiesExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFPropertiesExpPrologue( hVFhandle, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFPropertiesExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementGetVFPropertiesExpPrologue( hVFhandle, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFPropertiesExp", result);
        }

        auto driver_result = pfnGetVFPropertiesExp( hVFhandle, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFPropertiesExpEpilogue( hVFhandle, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFPropertiesExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zesVFManagementGetVFPropertiesExp", driver_result);
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
        context.logger->log_trace("zesVFManagementGetVFMemoryUtilizationExp(hVFhandle, pCount, pMemUtil)");

        auto pfnGetVFMemoryUtilizationExp = context.zesDdiTable.VFManagementExp.pfnGetVFMemoryUtilizationExp;

        if( nullptr == pfnGetVFMemoryUtilizationExp )
            return logAndPropagateResult("zesVFManagementGetVFMemoryUtilizationExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFMemoryUtilizationExpPrologue( hVFhandle, pCount, pMemUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFMemoryUtilizationExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementGetVFMemoryUtilizationExpPrologue( hVFhandle, pCount, pMemUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFMemoryUtilizationExp", result);
        }

        auto driver_result = pfnGetVFMemoryUtilizationExp( hVFhandle, pCount, pMemUtil );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFMemoryUtilizationExpEpilogue( hVFhandle, pCount, pMemUtil ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFMemoryUtilizationExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zesVFManagementGetVFMemoryUtilizationExp", driver_result);
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
        context.logger->log_trace("zesVFManagementGetVFEngineUtilizationExp(hVFhandle, pCount, pEngineUtil)");

        auto pfnGetVFEngineUtilizationExp = context.zesDdiTable.VFManagementExp.pfnGetVFEngineUtilizationExp;

        if( nullptr == pfnGetVFEngineUtilizationExp )
            return logAndPropagateResult("zesVFManagementGetVFEngineUtilizationExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFEngineUtilizationExpPrologue( hVFhandle, pCount, pEngineUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFEngineUtilizationExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementGetVFEngineUtilizationExpPrologue( hVFhandle, pCount, pEngineUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFEngineUtilizationExp", result);
        }

        auto driver_result = pfnGetVFEngineUtilizationExp( hVFhandle, pCount, pEngineUtil );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFEngineUtilizationExpEpilogue( hVFhandle, pCount, pEngineUtil ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFEngineUtilizationExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zesVFManagementGetVFEngineUtilizationExp", driver_result);
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
        context.logger->log_trace("zesVFManagementSetVFTelemetryModeExp(hVFhandle, flags, enable)");

        auto pfnSetVFTelemetryModeExp = context.zesDdiTable.VFManagementExp.pfnSetVFTelemetryModeExp;

        if( nullptr == pfnSetVFTelemetryModeExp )
            return logAndPropagateResult("zesVFManagementSetVFTelemetryModeExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementSetVFTelemetryModeExpPrologue( hVFhandle, flags, enable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementSetVFTelemetryModeExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementSetVFTelemetryModeExpPrologue( hVFhandle, flags, enable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementSetVFTelemetryModeExp", result);
        }

        auto driver_result = pfnSetVFTelemetryModeExp( hVFhandle, flags, enable );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementSetVFTelemetryModeExpEpilogue( hVFhandle, flags, enable ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementSetVFTelemetryModeExp", result);
        }

        return logAndPropagateResult("zesVFManagementSetVFTelemetryModeExp", driver_result);
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
        context.logger->log_trace("zesVFManagementSetVFTelemetrySamplingIntervalExp(hVFhandle, flag, samplingInterval)");

        auto pfnSetVFTelemetrySamplingIntervalExp = context.zesDdiTable.VFManagementExp.pfnSetVFTelemetrySamplingIntervalExp;

        if( nullptr == pfnSetVFTelemetrySamplingIntervalExp )
            return logAndPropagateResult("zesVFManagementSetVFTelemetrySamplingIntervalExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementSetVFTelemetrySamplingIntervalExpPrologue( hVFhandle, flag, samplingInterval );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementSetVFTelemetrySamplingIntervalExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementSetVFTelemetrySamplingIntervalExpPrologue( hVFhandle, flag, samplingInterval );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementSetVFTelemetrySamplingIntervalExp", result);
        }

        auto driver_result = pfnSetVFTelemetrySamplingIntervalExp( hVFhandle, flag, samplingInterval );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementSetVFTelemetrySamplingIntervalExpEpilogue( hVFhandle, flag, samplingInterval ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementSetVFTelemetrySamplingIntervalExp", result);
        }

        return logAndPropagateResult("zesVFManagementSetVFTelemetrySamplingIntervalExp", driver_result);
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
        context.logger->log_trace("zesDeviceEnumEnabledVFExp(hDevice, pCount, phVFhandle)");

        auto pfnEnumEnabledVFExp = context.zesDdiTable.DeviceExp.pfnEnumEnabledVFExp;

        if( nullptr == pfnEnumEnabledVFExp )
            return logAndPropagateResult("zesDeviceEnumEnabledVFExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumEnabledVFExpPrologue( hDevice, pCount, phVFhandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumEnabledVFExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumEnabledVFExpPrologue( hDevice, pCount, phVFhandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumEnabledVFExp", result);
        }

        auto driver_result = pfnEnumEnabledVFExp( hDevice, pCount, phVFhandle );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumEnabledVFExpEpilogue( hDevice, pCount, phVFhandle ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesDeviceEnumEnabledVFExp", result);
        }

        return logAndPropagateResult("zesDeviceEnumEnabledVFExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesVFManagementGetVFCapabilitiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zesVFManagementGetVFCapabilitiesExp(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
        zes_vf_exp_capabilities_t* pCapability          ///< [in,out] Will contain VF capability.
        )
    {
        context.logger->log_trace("zesVFManagementGetVFCapabilitiesExp(hVFhandle, pCapability)");

        auto pfnGetVFCapabilitiesExp = context.zesDdiTable.VFManagementExp.pfnGetVFCapabilitiesExp;

        if( nullptr == pfnGetVFCapabilitiesExp )
            return logAndPropagateResult("zesVFManagementGetVFCapabilitiesExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFCapabilitiesExpPrologue( hVFhandle, pCapability );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFCapabilitiesExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementGetVFCapabilitiesExpPrologue( hVFhandle, pCapability );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFCapabilitiesExp", result);
        }

        auto driver_result = pfnGetVFCapabilitiesExp( hVFhandle, pCapability );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFCapabilitiesExpEpilogue( hVFhandle, pCapability ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFCapabilitiesExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zesVFManagementGetVFCapabilitiesExp", driver_result);
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
        context.logger->log_trace("zesVFManagementGetVFMemoryUtilizationExp2(hVFhandle, pCount, pMemUtil)");

        auto pfnGetVFMemoryUtilizationExp2 = context.zesDdiTable.VFManagementExp.pfnGetVFMemoryUtilizationExp2;

        if( nullptr == pfnGetVFMemoryUtilizationExp2 )
            return logAndPropagateResult("zesVFManagementGetVFMemoryUtilizationExp2", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFMemoryUtilizationExp2Prologue( hVFhandle, pCount, pMemUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFMemoryUtilizationExp2", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementGetVFMemoryUtilizationExp2Prologue( hVFhandle, pCount, pMemUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFMemoryUtilizationExp2", result);
        }

        auto driver_result = pfnGetVFMemoryUtilizationExp2( hVFhandle, pCount, pMemUtil );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFMemoryUtilizationExp2Epilogue( hVFhandle, pCount, pMemUtil ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFMemoryUtilizationExp2", result);
        }

        return logAndPropagateResult("zesVFManagementGetVFMemoryUtilizationExp2", driver_result);
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
        context.logger->log_trace("zesVFManagementGetVFEngineUtilizationExp2(hVFhandle, pCount, pEngineUtil)");

        auto pfnGetVFEngineUtilizationExp2 = context.zesDdiTable.VFManagementExp.pfnGetVFEngineUtilizationExp2;

        if( nullptr == pfnGetVFEngineUtilizationExp2 )
            return logAndPropagateResult("zesVFManagementGetVFEngineUtilizationExp2", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFEngineUtilizationExp2Prologue( hVFhandle, pCount, pEngineUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFEngineUtilizationExp2", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementGetVFEngineUtilizationExp2Prologue( hVFhandle, pCount, pEngineUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFEngineUtilizationExp2", result);
        }

        auto driver_result = pfnGetVFEngineUtilizationExp2( hVFhandle, pCount, pEngineUtil );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFEngineUtilizationExp2Epilogue( hVFhandle, pCount, pEngineUtil ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFEngineUtilizationExp2", result);
        }

        return logAndPropagateResult("zesVFManagementGetVFEngineUtilizationExp2", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesVFManagementGetVFCapabilitiesExp2
    __zedlllocal ze_result_t ZE_APICALL
    zesVFManagementGetVFCapabilitiesExp2(
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
        zes_vf_exp2_capabilities_t* pCapability         ///< [in,out] Will contain VF capability.
        )
    {
        context.logger->log_trace("zesVFManagementGetVFCapabilitiesExp2(hVFhandle, pCapability)");

        auto pfnGetVFCapabilitiesExp2 = context.zesDdiTable.VFManagementExp.pfnGetVFCapabilitiesExp2;

        if( nullptr == pfnGetVFCapabilitiesExp2 )
            return logAndPropagateResult("zesVFManagementGetVFCapabilitiesExp2", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFCapabilitiesExp2Prologue( hVFhandle, pCapability );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFCapabilitiesExp2", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementGetVFCapabilitiesExp2Prologue( hVFhandle, pCapability );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFCapabilitiesExp2", result);
        }

        auto driver_result = pfnGetVFCapabilitiesExp2( hVFhandle, pCapability );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFCapabilitiesExp2Epilogue( hVFhandle, pCapability ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zesVFManagementGetVFCapabilitiesExp2", result);
        }

        return logAndPropagateResult("zesVFManagementGetVFCapabilitiesExp2", driver_result);
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
/// @brief Exported function for filling application's DeviceExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetDeviceExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_device_exp_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.DeviceExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnEnumEnabledVFExp                         = pDdiTable->pfnEnumEnabledVFExp;
    pDdiTable->pfnEnumEnabledVFExp                       = validation_layer::zesDeviceEnumEnabledVFExp;

    dditable.pfnGetSubDevicePropertiesExp                = pDdiTable->pfnGetSubDevicePropertiesExp;
    pDdiTable->pfnGetSubDevicePropertiesExp              = validation_layer::zesDeviceGetSubDevicePropertiesExp;

    dditable.pfnEnumActiveVFExp                          = pDdiTable->pfnEnumActiveVFExp;
    pDdiTable->pfnEnumActiveVFExp                        = validation_layer::zesDeviceEnumActiveVFExp;

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
/// @brief Exported function for filling application's DriverExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetDriverExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_driver_exp_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.DriverExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetDeviceByUuidExp                       = pDdiTable->pfnGetDeviceByUuidExp;
    pDdiTable->pfnGetDeviceByUuidExp                     = validation_layer::zesDriverGetDeviceByUuidExp;

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

    dditable.pfnGetConsoleLogs                           = pDdiTable->pfnGetConsoleLogs;
    pDdiTable->pfnGetConsoleLogs                         = validation_layer::zesFirmwareGetConsoleLogs;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FirmwareExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetFirmwareExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_firmware_exp_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.FirmwareExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetSecurityVersionExp                    = pDdiTable->pfnGetSecurityVersionExp;
    pDdiTable->pfnGetSecurityVersionExp                  = validation_layer::zesFirmwareGetSecurityVersionExp;

    dditable.pfnSetSecurityVersionExp                    = pDdiTable->pfnSetSecurityVersionExp;
    pDdiTable->pfnSetSecurityVersionExp                  = validation_layer::zesFirmwareSetSecurityVersionExp;

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

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's VFManagementExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zesGetVFManagementExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_vf_management_exp_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.VFManagementExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetVFCapabilitiesExp                     = pDdiTable->pfnGetVFCapabilitiesExp;
    pDdiTable->pfnGetVFCapabilitiesExp                   = validation_layer::zesVFManagementGetVFCapabilitiesExp;

    dditable.pfnGetVFMemoryUtilizationExp2               = pDdiTable->pfnGetVFMemoryUtilizationExp2;
    pDdiTable->pfnGetVFMemoryUtilizationExp2             = validation_layer::zesVFManagementGetVFMemoryUtilizationExp2;

    dditable.pfnGetVFEngineUtilizationExp2               = pDdiTable->pfnGetVFEngineUtilizationExp2;
    pDdiTable->pfnGetVFEngineUtilizationExp2             = validation_layer::zesVFManagementGetVFEngineUtilizationExp2;

    dditable.pfnGetVFCapabilitiesExp2                    = pDdiTable->pfnGetVFCapabilitiesExp2;
    pDdiTable->pfnGetVFCapabilitiesExp2                  = validation_layer::zesVFManagementGetVFCapabilitiesExp2;

    dditable.pfnGetVFPropertiesExp                       = pDdiTable->pfnGetVFPropertiesExp;
    pDdiTable->pfnGetVFPropertiesExp                     = validation_layer::zesVFManagementGetVFPropertiesExp;

    dditable.pfnGetVFMemoryUtilizationExp                = pDdiTable->pfnGetVFMemoryUtilizationExp;
    pDdiTable->pfnGetVFMemoryUtilizationExp              = validation_layer::zesVFManagementGetVFMemoryUtilizationExp;

    dditable.pfnGetVFEngineUtilizationExp                = pDdiTable->pfnGetVFEngineUtilizationExp;
    pDdiTable->pfnGetVFEngineUtilizationExp              = validation_layer::zesVFManagementGetVFEngineUtilizationExp;

    dditable.pfnSetVFTelemetryModeExp                    = pDdiTable->pfnSetVFTelemetryModeExp;
    pDdiTable->pfnSetVFTelemetryModeExp                  = validation_layer::zesVFManagementSetVFTelemetryModeExp;

    dditable.pfnSetVFTelemetrySamplingIntervalExp        = pDdiTable->pfnSetVFTelemetrySamplingIntervalExp;
    pDdiTable->pfnSetVFTelemetrySamplingIntervalExp      = validation_layer::zesVFManagementSetVFTelemetrySamplingIntervalExp;

    return result;
}

#if defined(__cplusplus)
};
#endif
