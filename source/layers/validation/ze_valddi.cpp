/*
 * ***THIS FILE IS GENERATED. ***
 * See valddi.cpp.mako for modifications
 *
 * Copyright (C) 2019-2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_valddi.cpp
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
    /// @brief Intercept function for zeInit
    __zedlllocal ze_result_t ZE_APICALL
    zeInit(
        ze_init_flags_t flags                           ///< [in] initialization flags.
                                                        ///< must be 0 (default) or a combination of ::ze_init_flag_t.
        )
    {
        context.logger->log_trace("zeInit(flags)");

        auto pfnInit = context.zeDdiTable.Global.pfnInit;

        if( nullptr == pfnInit )
            return logAndPropagateResult("zeInit", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeInitPrologue( flags );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeInit", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeInitPrologue( flags );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeInit", result);
        }

        auto driver_result = pfnInit( flags );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeInitEpilogue( flags ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeInit", result);
        }

        return logAndPropagateResult("zeInit", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGet
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGet(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                        ///< if count is zero, then the loader shall update the value with the
                                                        ///< total number of drivers available.
                                                        ///< if count is greater than the number of drivers available, then the
                                                        ///< loader shall update the value with the correct number of drivers available.
        ze_driver_handle_t* phDrivers                   ///< [in,out][optional][range(0, *pCount)] array of driver instance handles.
                                                        ///< if count is less than the number of drivers available, then the loader
                                                        ///< shall only retrieve that number of drivers.
        )
    {
        context.logger->log_trace("zeDriverGet(pCount, phDrivers)");

        auto pfnGet = context.zeDdiTable.Driver.pfnGet;

        if( nullptr == pfnGet )
            return logAndPropagateResult("zeDriverGet", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverGetPrologue( pCount, phDrivers );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGet", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetPrologue( pCount, phDrivers );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGet", result);
        }

        auto driver_result = pfnGet( pCount, phDrivers );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverGetEpilogue( pCount, phDrivers ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGet", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phDrivers) && (i < *pCount); ++i){
                if (phDrivers[i]){
                    context.handleLifetime->addHandle( phDrivers[i] );
                    context.handleLifetime->addDependent( pCount, phDrivers[i] );
                }
            }
        }
        return logAndPropagateResult("zeDriverGet", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeInitDrivers
    __zedlllocal ze_result_t ZE_APICALL
    zeInitDrivers(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                        ///< if count is zero, then the loader shall update the value with the
                                                        ///< total number of drivers available.
                                                        ///< if count is greater than the number of drivers available, then the
                                                        ///< loader shall update the value with the correct number of drivers available.
        ze_driver_handle_t* phDrivers,                  ///< [in,out][optional][range(0, *pCount)] array of driver instance handles.
                                                        ///< if count is less than the number of drivers available, then the loader
                                                        ///< shall only retrieve that number of drivers.
        ze_init_driver_type_desc_t* desc                ///< [in] descriptor containing the driver type initialization details
                                                        ///< including ::ze_init_driver_type_flag_t combinations.
        )
    {
        context.logger->log_trace("zeInitDrivers(pCount, phDrivers, desc)");

        auto pfnInitDrivers = context.zeDdiTable.Global.pfnInitDrivers;

        if( nullptr == pfnInitDrivers )
            return logAndPropagateResult("zeInitDrivers", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeInitDriversPrologue( pCount, phDrivers, desc );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeInitDrivers", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeInitDriversPrologue( pCount, phDrivers, desc );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeInitDrivers", result);
        }

        auto driver_result = pfnInitDrivers( pCount, phDrivers, desc );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeInitDriversEpilogue( pCount, phDrivers, desc ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeInitDrivers", result);
        }

        return logAndPropagateResult("zeInitDrivers", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetApiVersion
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetApiVersion(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_api_version_t* version                       ///< [out] api version
        )
    {
        context.logger->log_trace("zeDriverGetApiVersion(hDriver, version)");

        auto pfnGetApiVersion = context.zeDdiTable.Driver.pfnGetApiVersion;

        if( nullptr == pfnGetApiVersion )
            return logAndPropagateResult("zeDriverGetApiVersion", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverGetApiVersionPrologue( hDriver, version );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetApiVersion", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetApiVersionPrologue( hDriver, version );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetApiVersion", result);
        }

        auto driver_result = pfnGetApiVersion( hDriver, version );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverGetApiVersionEpilogue( hDriver, version ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetApiVersion", result);
        }

        return logAndPropagateResult("zeDriverGetApiVersion", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_properties_t* pDriverProperties       ///< [in,out] query result for driver properties
        )
    {
        context.logger->log_trace("zeDriverGetProperties(hDriver, pDriverProperties)");

        auto pfnGetProperties = context.zeDdiTable.Driver.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zeDriverGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverGetPropertiesPrologue( hDriver, pDriverProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetPropertiesPrologue( hDriver, pDriverProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hDriver, pDriverProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverGetPropertiesEpilogue( hDriver, pDriverProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetProperties", result);
        }

        return logAndPropagateResult("zeDriverGetProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetIpcProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetIpcProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_ipc_properties_t* pIpcProperties      ///< [in,out] query result for IPC properties
        )
    {
        context.logger->log_trace("zeDriverGetIpcProperties(hDriver, pIpcProperties)");

        auto pfnGetIpcProperties = context.zeDdiTable.Driver.pfnGetIpcProperties;

        if( nullptr == pfnGetIpcProperties )
            return logAndPropagateResult("zeDriverGetIpcProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverGetIpcPropertiesPrologue( hDriver, pIpcProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetIpcProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetIpcPropertiesPrologue( hDriver, pIpcProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetIpcProperties", result);
        }

        auto driver_result = pfnGetIpcProperties( hDriver, pIpcProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverGetIpcPropertiesEpilogue( hDriver, pIpcProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetIpcProperties", result);
        }

        return logAndPropagateResult("zeDriverGetIpcProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetExtensionProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetExtensionProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of extension properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of extension properties available.
                                                        ///< if count is greater than the number of extension properties available,
                                                        ///< then the driver shall update the value with the correct number of
                                                        ///< extension properties available.
        ze_driver_extension_properties_t* pExtensionProperties  ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< extension properties.
                                                        ///< if count is less than the number of extension properties available,
                                                        ///< then driver shall only retrieve that number of extension properties.
        )
    {
        context.logger->log_trace("zeDriverGetExtensionProperties(hDriver, pCount, pExtensionProperties)");

        auto pfnGetExtensionProperties = context.zeDdiTable.Driver.pfnGetExtensionProperties;

        if( nullptr == pfnGetExtensionProperties )
            return logAndPropagateResult("zeDriverGetExtensionProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverGetExtensionPropertiesPrologue( hDriver, pCount, pExtensionProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetExtensionProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetExtensionPropertiesPrologue( hDriver, pCount, pExtensionProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetExtensionProperties", result);
        }

        auto driver_result = pfnGetExtensionProperties( hDriver, pCount, pExtensionProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverGetExtensionPropertiesEpilogue( hDriver, pCount, pExtensionProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetExtensionProperties", result);
        }

        return logAndPropagateResult("zeDriverGetExtensionProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetExtensionFunctionAddress
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetExtensionFunctionAddress(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const char* name,                               ///< [in] extension function name
        void** ppFunctionAddress                        ///< [out] pointer to function pointer
        )
    {
        context.logger->log_trace("zeDriverGetExtensionFunctionAddress(hDriver, name, ppFunctionAddress)");

        auto pfnGetExtensionFunctionAddress = context.zeDdiTable.Driver.pfnGetExtensionFunctionAddress;

        if( nullptr == pfnGetExtensionFunctionAddress )
            return logAndPropagateResult("zeDriverGetExtensionFunctionAddress", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverGetExtensionFunctionAddressPrologue( hDriver, name, ppFunctionAddress );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetExtensionFunctionAddress", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetExtensionFunctionAddressPrologue( hDriver, name, ppFunctionAddress );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetExtensionFunctionAddress", result);
        }

        auto driver_result = pfnGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverGetExtensionFunctionAddressEpilogue( hDriver, name, ppFunctionAddress ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetExtensionFunctionAddress", result);
        }

        return logAndPropagateResult("zeDriverGetExtensionFunctionAddress", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetLastErrorDescription
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetLastErrorDescription(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        const char** ppString                           ///< [in,out] pointer to a null-terminated array of characters describing
                                                        ///< cause of error.
        )
    {
        context.logger->log_trace("zeDriverGetLastErrorDescription(hDriver, ppString)");

        auto pfnGetLastErrorDescription = context.zeDdiTable.Driver.pfnGetLastErrorDescription;

        if( nullptr == pfnGetLastErrorDescription )
            return logAndPropagateResult("zeDriverGetLastErrorDescription", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverGetLastErrorDescriptionPrologue( hDriver, ppString );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetLastErrorDescription", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetLastErrorDescriptionPrologue( hDriver, ppString );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetLastErrorDescription", result);
        }

        auto driver_result = pfnGetLastErrorDescription( hDriver, ppString );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverGetLastErrorDescriptionEpilogue( hDriver, ppString ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverGetLastErrorDescription", result);
        }

        return logAndPropagateResult("zeDriverGetLastErrorDescription", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGet
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGet(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of devices available.
                                                        ///< if count is greater than the number of devices available, then the
                                                        ///< driver shall update the value with the correct number of devices available.
        ze_device_handle_t* phDevices                   ///< [in,out][optional][range(0, *pCount)] array of handle of devices.
                                                        ///< if count is less than the number of devices available, then driver
                                                        ///< shall only retrieve that number of devices.
        )
    {
        context.logger->log_trace("zeDeviceGet(hDriver, pCount, phDevices)");

        auto pfnGet = context.zeDdiTable.Device.pfnGet;

        if( nullptr == pfnGet )
            return logAndPropagateResult("zeDeviceGet", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetPrologue( hDriver, pCount, phDevices );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGet", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetPrologue( hDriver, pCount, phDevices );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGet", result);
        }

        auto driver_result = pfnGet( hDriver, pCount, phDevices );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetEpilogue( hDriver, pCount, phDevices ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGet", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phDevices) && (i < *pCount); ++i){
                if (phDevices[i]){
                    context.handleLifetime->addHandle( phDevices[i] );
                    context.handleLifetime->addDependent( hDriver, phDevices[i] );
                }
            }
        }
        return logAndPropagateResult("zeDeviceGet", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetRootDevice
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetRootDevice(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        ze_device_handle_t* phRootDevice                ///< [in,out] parent root device.
        )
    {
        context.logger->log_trace("zeDeviceGetRootDevice(hDevice, phRootDevice)");

        auto pfnGetRootDevice = context.zeDdiTable.Device.pfnGetRootDevice;

        if( nullptr == pfnGetRootDevice )
            return logAndPropagateResult("zeDeviceGetRootDevice", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetRootDevicePrologue( hDevice, phRootDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetRootDevice", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetRootDevicePrologue( hDevice, phRootDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetRootDevice", result);
        }

        auto driver_result = pfnGetRootDevice( hDevice, phRootDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetRootDeviceEpilogue( hDevice, phRootDevice ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetRootDevice", result);
        }

        return logAndPropagateResult("zeDeviceGetRootDevice", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetSubDevices
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetSubDevices(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-devices.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of sub-devices available.
                                                        ///< if count is greater than the number of sub-devices available, then the
                                                        ///< driver shall update the value with the correct number of sub-devices available.
        ze_device_handle_t* phSubdevices                ///< [in,out][optional][range(0, *pCount)] array of handle of sub-devices.
                                                        ///< if count is less than the number of sub-devices available, then driver
                                                        ///< shall only retrieve that number of sub-devices.
        )
    {
        context.logger->log_trace("zeDeviceGetSubDevices(hDevice, pCount, phSubdevices)");

        auto pfnGetSubDevices = context.zeDdiTable.Device.pfnGetSubDevices;

        if( nullptr == pfnGetSubDevices )
            return logAndPropagateResult("zeDeviceGetSubDevices", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetSubDevicesPrologue( hDevice, pCount, phSubdevices );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetSubDevices", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetSubDevicesPrologue( hDevice, pCount, phSubdevices );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetSubDevices", result);
        }

        auto driver_result = pfnGetSubDevices( hDevice, pCount, phSubdevices );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetSubDevicesEpilogue( hDevice, pCount, phSubdevices ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetSubDevices", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phSubdevices) && (i < *pCount); ++i){
                if (phSubdevices[i]){
                    context.handleLifetime->addHandle( phSubdevices[i] );
                    context.handleLifetime->addDependent( hDevice, phSubdevices[i] );
                }
            }
        }
        return logAndPropagateResult("zeDeviceGetSubDevices", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_properties_t* pDeviceProperties       ///< [in,out] query result for device properties
        )
    {
        context.logger->log_trace("zeDeviceGetProperties(hDevice, pDeviceProperties)");

        auto pfnGetProperties = context.zeDdiTable.Device.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zeDeviceGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetPropertiesPrologue( hDevice, pDeviceProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetPropertiesPrologue( hDevice, pDeviceProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hDevice, pDeviceProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetPropertiesEpilogue( hDevice, pDeviceProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetProperties", result);
        }

        return logAndPropagateResult("zeDeviceGetProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetComputeProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetComputeProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_compute_properties_t* pComputeProperties  ///< [in,out] query result for compute properties
        )
    {
        context.logger->log_trace("zeDeviceGetComputeProperties(hDevice, pComputeProperties)");

        auto pfnGetComputeProperties = context.zeDdiTable.Device.pfnGetComputeProperties;

        if( nullptr == pfnGetComputeProperties )
            return logAndPropagateResult("zeDeviceGetComputeProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetComputePropertiesPrologue( hDevice, pComputeProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetComputeProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetComputePropertiesPrologue( hDevice, pComputeProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetComputeProperties", result);
        }

        auto driver_result = pfnGetComputeProperties( hDevice, pComputeProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetComputePropertiesEpilogue( hDevice, pComputeProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetComputeProperties", result);
        }

        return logAndPropagateResult("zeDeviceGetComputeProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetModuleProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetModuleProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_module_properties_t* pModuleProperties///< [in,out] query result for module properties
        )
    {
        context.logger->log_trace("zeDeviceGetModuleProperties(hDevice, pModuleProperties)");

        auto pfnGetModuleProperties = context.zeDdiTable.Device.pfnGetModuleProperties;

        if( nullptr == pfnGetModuleProperties )
            return logAndPropagateResult("zeDeviceGetModuleProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetModulePropertiesPrologue( hDevice, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetModuleProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetModulePropertiesPrologue( hDevice, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetModuleProperties", result);
        }

        auto driver_result = pfnGetModuleProperties( hDevice, pModuleProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetModulePropertiesEpilogue( hDevice, pModuleProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetModuleProperties", result);
        }

        return logAndPropagateResult("zeDeviceGetModuleProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetCommandQueueGroupProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetCommandQueueGroupProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of command queue group properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of command queue group properties available.
                                                        ///< if count is greater than the number of command queue group properties
                                                        ///< available, then the driver shall update the value with the correct
                                                        ///< number of command queue group properties available.
        ze_command_queue_group_properties_t* pCommandQueueGroupProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< command queue group properties.
                                                        ///< if count is less than the number of command queue group properties
                                                        ///< available, then driver shall only retrieve that number of command
                                                        ///< queue group properties.
        )
    {
        context.logger->log_trace("zeDeviceGetCommandQueueGroupProperties(hDevice, pCount, pCommandQueueGroupProperties)");

        auto pfnGetCommandQueueGroupProperties = context.zeDdiTable.Device.pfnGetCommandQueueGroupProperties;

        if( nullptr == pfnGetCommandQueueGroupProperties )
            return logAndPropagateResult("zeDeviceGetCommandQueueGroupProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetCommandQueueGroupPropertiesPrologue( hDevice, pCount, pCommandQueueGroupProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetCommandQueueGroupProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetCommandQueueGroupPropertiesPrologue( hDevice, pCount, pCommandQueueGroupProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetCommandQueueGroupProperties", result);
        }

        auto driver_result = pfnGetCommandQueueGroupProperties( hDevice, pCount, pCommandQueueGroupProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetCommandQueueGroupPropertiesEpilogue( hDevice, pCount, pCommandQueueGroupProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetCommandQueueGroupProperties", result);
        }

        return logAndPropagateResult("zeDeviceGetCommandQueueGroupProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetMemoryProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetMemoryProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of memory properties available.
                                                        ///< if count is greater than the number of memory properties available,
                                                        ///< then the driver shall update the value with the correct number of
                                                        ///< memory properties available.
        ze_device_memory_properties_t* pMemProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< memory properties.
                                                        ///< if count is less than the number of memory properties available, then
                                                        ///< driver shall only retrieve that number of memory properties.
        )
    {
        context.logger->log_trace("zeDeviceGetMemoryProperties(hDevice, pCount, pMemProperties)");

        auto pfnGetMemoryProperties = context.zeDdiTable.Device.pfnGetMemoryProperties;

        if( nullptr == pfnGetMemoryProperties )
            return logAndPropagateResult("zeDeviceGetMemoryProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetMemoryPropertiesPrologue( hDevice, pCount, pMemProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetMemoryProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetMemoryPropertiesPrologue( hDevice, pCount, pMemProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetMemoryProperties", result);
        }

        auto driver_result = pfnGetMemoryProperties( hDevice, pCount, pMemProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetMemoryPropertiesEpilogue( hDevice, pCount, pMemProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetMemoryProperties", result);
        }

        return logAndPropagateResult("zeDeviceGetMemoryProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetMemoryAccessProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetMemoryAccessProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_memory_access_properties_t* pMemAccessProperties  ///< [in,out] query result for memory access properties
        )
    {
        context.logger->log_trace("zeDeviceGetMemoryAccessProperties(hDevice, pMemAccessProperties)");

        auto pfnGetMemoryAccessProperties = context.zeDdiTable.Device.pfnGetMemoryAccessProperties;

        if( nullptr == pfnGetMemoryAccessProperties )
            return logAndPropagateResult("zeDeviceGetMemoryAccessProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetMemoryAccessPropertiesPrologue( hDevice, pMemAccessProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetMemoryAccessProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetMemoryAccessPropertiesPrologue( hDevice, pMemAccessProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetMemoryAccessProperties", result);
        }

        auto driver_result = pfnGetMemoryAccessProperties( hDevice, pMemAccessProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetMemoryAccessPropertiesEpilogue( hDevice, pMemAccessProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetMemoryAccessProperties", result);
        }

        return logAndPropagateResult("zeDeviceGetMemoryAccessProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetCacheProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetCacheProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of cache properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of cache properties available.
                                                        ///< if count is greater than the number of cache properties available,
                                                        ///< then the driver shall update the value with the correct number of
                                                        ///< cache properties available.
        ze_device_cache_properties_t* pCacheProperties  ///< [in,out][optional][range(0, *pCount)] array of query results for cache properties.
                                                        ///< if count is less than the number of cache properties available, then
                                                        ///< driver shall only retrieve that number of cache properties.
        )
    {
        context.logger->log_trace("zeDeviceGetCacheProperties(hDevice, pCount, pCacheProperties)");

        auto pfnGetCacheProperties = context.zeDdiTable.Device.pfnGetCacheProperties;

        if( nullptr == pfnGetCacheProperties )
            return logAndPropagateResult("zeDeviceGetCacheProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetCachePropertiesPrologue( hDevice, pCount, pCacheProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetCacheProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetCachePropertiesPrologue( hDevice, pCount, pCacheProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetCacheProperties", result);
        }

        auto driver_result = pfnGetCacheProperties( hDevice, pCount, pCacheProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetCachePropertiesEpilogue( hDevice, pCount, pCacheProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetCacheProperties", result);
        }

        return logAndPropagateResult("zeDeviceGetCacheProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetImageProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetImageProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_image_properties_t* pImageProperties  ///< [in,out] query result for image properties
        )
    {
        context.logger->log_trace("zeDeviceGetImageProperties(hDevice, pImageProperties)");

        auto pfnGetImageProperties = context.zeDdiTable.Device.pfnGetImageProperties;

        if( nullptr == pfnGetImageProperties )
            return logAndPropagateResult("zeDeviceGetImageProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetImagePropertiesPrologue( hDevice, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetImageProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetImagePropertiesPrologue( hDevice, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetImageProperties", result);
        }

        auto driver_result = pfnGetImageProperties( hDevice, pImageProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetImagePropertiesEpilogue( hDevice, pImageProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetImageProperties", result);
        }

        return logAndPropagateResult("zeDeviceGetImageProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetExternalMemoryProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetExternalMemoryProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_external_memory_properties_t* pExternalMemoryProperties   ///< [in,out] query result for external memory properties
        )
    {
        context.logger->log_trace("zeDeviceGetExternalMemoryProperties(hDevice, pExternalMemoryProperties)");

        auto pfnGetExternalMemoryProperties = context.zeDdiTable.Device.pfnGetExternalMemoryProperties;

        if( nullptr == pfnGetExternalMemoryProperties )
            return logAndPropagateResult("zeDeviceGetExternalMemoryProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetExternalMemoryPropertiesPrologue( hDevice, pExternalMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetExternalMemoryProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetExternalMemoryPropertiesPrologue( hDevice, pExternalMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetExternalMemoryProperties", result);
        }

        auto driver_result = pfnGetExternalMemoryProperties( hDevice, pExternalMemoryProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetExternalMemoryPropertiesEpilogue( hDevice, pExternalMemoryProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetExternalMemoryProperties", result);
        }

        return logAndPropagateResult("zeDeviceGetExternalMemoryProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetP2PProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetP2PProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_device_p2p_properties_t* pP2PProperties      ///< [in,out] Peer-to-Peer properties between source and peer device
        )
    {
        context.logger->log_trace("zeDeviceGetP2PProperties(hDevice, hPeerDevice, pP2PProperties)");

        auto pfnGetP2PProperties = context.zeDdiTable.Device.pfnGetP2PProperties;

        if( nullptr == pfnGetP2PProperties )
            return logAndPropagateResult("zeDeviceGetP2PProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetP2PPropertiesPrologue( hDevice, hPeerDevice, pP2PProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetP2PProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetP2PPropertiesPrologue( hDevice, hPeerDevice, pP2PProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetP2PProperties", result);
        }

        auto driver_result = pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetP2PPropertiesEpilogue( hDevice, hPeerDevice, pP2PProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetP2PProperties", result);
        }

        return logAndPropagateResult("zeDeviceGetP2PProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceCanAccessPeer
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceCanAccessPeer(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        ze_bool_t* value                                ///< [out] returned access capability
        )
    {
        context.logger->log_trace("zeDeviceCanAccessPeer(hDevice, hPeerDevice, value)");

        auto pfnCanAccessPeer = context.zeDdiTable.Device.pfnCanAccessPeer;

        if( nullptr == pfnCanAccessPeer )
            return logAndPropagateResult("zeDeviceCanAccessPeer", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceCanAccessPeerPrologue( hDevice, hPeerDevice, value );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceCanAccessPeer", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceCanAccessPeerPrologue( hDevice, hPeerDevice, value );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceCanAccessPeer", result);
        }

        auto driver_result = pfnCanAccessPeer( hDevice, hPeerDevice, value );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceCanAccessPeerEpilogue( hDevice, hPeerDevice, value ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceCanAccessPeer", result);
        }

        return logAndPropagateResult("zeDeviceCanAccessPeer", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetStatus(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        context.logger->log_trace("zeDeviceGetStatus(hDevice)");

        auto pfnGetStatus = context.zeDdiTable.Device.pfnGetStatus;

        if( nullptr == pfnGetStatus )
            return logAndPropagateResult("zeDeviceGetStatus", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetStatusPrologue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetStatus", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetStatusPrologue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetStatus", result);
        }

        auto driver_result = pfnGetStatus( hDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetStatusEpilogue( hDevice ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetStatus", result);
        }

        return logAndPropagateResult("zeDeviceGetStatus", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetGlobalTimestamps
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetGlobalTimestamps(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint64_t* hostTimestamp,                        ///< [out] value of the Host's global timestamp that correlates with the
                                                        ///< Device's global timestamp value.
        uint64_t* deviceTimestamp                       ///< [out] value of the Device's global timestamp that correlates with the
                                                        ///< Host's global timestamp value.
        )
    {
        context.logger->log_trace("zeDeviceGetGlobalTimestamps(hDevice, hostTimestamp, deviceTimestamp)");

        auto pfnGetGlobalTimestamps = context.zeDdiTable.Device.pfnGetGlobalTimestamps;

        if( nullptr == pfnGetGlobalTimestamps )
            return logAndPropagateResult("zeDeviceGetGlobalTimestamps", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetGlobalTimestampsPrologue( hDevice, hostTimestamp, deviceTimestamp );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetGlobalTimestamps", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetGlobalTimestampsPrologue( hDevice, hostTimestamp, deviceTimestamp );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetGlobalTimestamps", result);
        }

        auto driver_result = pfnGetGlobalTimestamps( hDevice, hostTimestamp, deviceTimestamp );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetGlobalTimestampsEpilogue( hDevice, hostTimestamp, deviceTimestamp ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetGlobalTimestamps", result);
        }

        return logAndPropagateResult("zeDeviceGetGlobalTimestamps", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeContextCreate(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver object
        const ze_context_desc_t* desc,                  ///< [in] pointer to context descriptor
        ze_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
        )
    {
        context.logger->log_trace("zeContextCreate(hDriver, desc, phContext)");

        auto pfnCreate = context.zeDdiTable.Context.pfnCreate;

        if( nullptr == pfnCreate )
            return logAndPropagateResult("zeContextCreate", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextCreatePrologue( hDriver, desc, phContext );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextCreate", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextCreatePrologue( hDriver, desc, phContext );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextCreate", result);
        }

        auto driver_result = pfnCreate( hDriver, desc, phContext );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextCreateEpilogue( hDriver, desc, phContext ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextCreate", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phContext){
                context.handleLifetime->addHandle( *phContext );
                context.handleLifetime->addDependent( hDriver, *phContext );

            }
        }
        return logAndPropagateResult("zeContextCreate", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextCreateEx
    __zedlllocal ze_result_t ZE_APICALL
    zeContextCreateEx(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver object
        const ze_context_desc_t* desc,                  ///< [in] pointer to context descriptor
        uint32_t numDevices,                            ///< [in][optional] number of device handles; must be 0 if `nullptr ==
                                                        ///< phDevices`
        ze_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                        ///< context has visibility.
                                                        ///< if nullptr, then all devices and any sub-devices supported by the
                                                        ///< driver instance are
                                                        ///< visible to the context.
                                                        ///< otherwise, the context only has visibility to the devices and any
                                                        ///< sub-devices of the
                                                        ///< devices in this array.
        ze_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
        )
    {
        context.logger->log_trace("zeContextCreateEx(hDriver, desc, numDevices, phDevicesLocal, phContext)");

        auto pfnCreateEx = context.zeDdiTable.Context.pfnCreateEx;

        if( nullptr == pfnCreateEx )
            return logAndPropagateResult("zeContextCreateEx", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextCreateExPrologue( hDriver, desc, numDevices, phDevices, phContext );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextCreateEx", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextCreateExPrologue( hDriver, desc, numDevices, phDevices, phContext );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextCreateEx", result);
        }

        auto driver_result = pfnCreateEx( hDriver, desc, numDevices, phDevices, phContext );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextCreateExEpilogue( hDriver, desc, numDevices, phDevices, phContext ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextCreateEx", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phContext){
                context.handleLifetime->addHandle( *phContext );
                context.handleLifetime->addDependent( hDriver, *phContext );

            }
        }
        return logAndPropagateResult("zeContextCreateEx", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeContextDestroy(
        ze_context_handle_t hContext                    ///< [in][release] handle of context object to destroy
        )
    {
        context.logger->log_trace("zeContextDestroy(hContext)");

        auto pfnDestroy = context.zeDdiTable.Context.pfnDestroy;

        if( nullptr == pfnDestroy )
            return logAndPropagateResult("zeContextDestroy", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextDestroyPrologue( hContext );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextDestroy", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextDestroyPrologue( hContext );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextDestroy", result);
        }

        auto driver_result = pfnDestroy( hContext );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextDestroyEpilogue( hContext ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextDestroy", result);
        }

        return logAndPropagateResult("zeContextDestroy", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextGetStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeContextGetStatus(
        ze_context_handle_t hContext                    ///< [in] handle of context object
        )
    {
        context.logger->log_trace("zeContextGetStatus(hContext)");

        auto pfnGetStatus = context.zeDdiTable.Context.pfnGetStatus;

        if( nullptr == pfnGetStatus )
            return logAndPropagateResult("zeContextGetStatus", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextGetStatusPrologue( hContext );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextGetStatus", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextGetStatusPrologue( hContext );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextGetStatus", result);
        }

        auto driver_result = pfnGetStatus( hContext );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextGetStatusEpilogue( hContext ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextGetStatus", result);
        }

        return logAndPropagateResult("zeContextGetStatus", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        ze_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
        )
    {
        context.logger->log_trace("zeCommandQueueCreate(hContext, hDevice, desc, phCommandQueue)");

        auto pfnCreate = context.zeDdiTable.CommandQueue.pfnCreate;

        if( nullptr == pfnCreate )
            return logAndPropagateResult("zeCommandQueueCreate", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandQueueCreatePrologue( hContext, hDevice, desc, phCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueCreate", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueCreatePrologue( hContext, hDevice, desc, phCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueCreate", result);
        }

        auto driver_result = pfnCreate( hContext, hDevice, desc, phCommandQueue );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandQueueCreateEpilogue( hContext, hDevice, desc, phCommandQueue ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueCreate", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phCommandQueue){
                context.handleLifetime->addHandle( *phCommandQueue );
                context.handleLifetime->addDependent( hContext, *phCommandQueue );

            }
        }
        return logAndPropagateResult("zeCommandQueueCreate", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueDestroy(
        ze_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
        )
    {
        context.logger->log_trace("zeCommandQueueDestroy(hCommandQueue)");

        auto pfnDestroy = context.zeDdiTable.CommandQueue.pfnDestroy;

        if( nullptr == pfnDestroy )
            return logAndPropagateResult("zeCommandQueueDestroy", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandQueueDestroyPrologue( hCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueDestroy", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueDestroyPrologue( hCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueDestroy", result);
        }

        auto driver_result = pfnDestroy( hCommandQueue );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandQueueDestroyEpilogue( hCommandQueue ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueDestroy", result);
        }

        return logAndPropagateResult("zeCommandQueueDestroy", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueExecuteCommandLists
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueExecuteCommandLists(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                        ///< to execute
        ze_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
        )
    {
        context.logger->log_trace("zeCommandQueueExecuteCommandLists(hCommandQueue, numCommandLists, phCommandListsLocal, hFence)");

        auto pfnExecuteCommandLists = context.zeDdiTable.CommandQueue.pfnExecuteCommandLists;

        if( nullptr == pfnExecuteCommandLists )
            return logAndPropagateResult("zeCommandQueueExecuteCommandLists", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandQueueExecuteCommandListsPrologue( hCommandQueue, numCommandLists, phCommandLists, hFence );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueExecuteCommandLists", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueExecuteCommandListsPrologue( hCommandQueue, numCommandLists, phCommandLists, hFence );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueExecuteCommandLists", result);
        }

        auto driver_result = pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandQueueExecuteCommandListsEpilogue( hCommandQueue, numCommandLists, phCommandLists, hFence ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueExecuteCommandLists", result);
        }

        return logAndPropagateResult("zeCommandQueueExecuteCommandLists", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueSynchronize
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueSynchronize(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then immediately returns the status of the command queue;
                                                        ///< if `UINT64_MAX`, then function will not return until complete or
                                                        ///< device is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        context.logger->log_trace("zeCommandQueueSynchronize(hCommandQueue, timeout)");

        auto pfnSynchronize = context.zeDdiTable.CommandQueue.pfnSynchronize;

        if( nullptr == pfnSynchronize )
            return logAndPropagateResult("zeCommandQueueSynchronize", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandQueueSynchronizePrologue( hCommandQueue, timeout );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueSynchronize", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueSynchronizePrologue( hCommandQueue, timeout );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueSynchronize", result);
        }

        auto driver_result = pfnSynchronize( hCommandQueue, timeout );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandQueueSynchronizeEpilogue( hCommandQueue, timeout ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueSynchronize", result);
        }

        return logAndPropagateResult("zeCommandQueueSynchronize", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueGetOrdinal
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueGetOrdinal(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t* pOrdinal                              ///< [out] command queue group ordinal
        )
    {
        context.logger->log_trace("zeCommandQueueGetOrdinal(hCommandQueue, pOrdinal)");

        auto pfnGetOrdinal = context.zeDdiTable.CommandQueue.pfnGetOrdinal;

        if( nullptr == pfnGetOrdinal )
            return logAndPropagateResult("zeCommandQueueGetOrdinal", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandQueueGetOrdinalPrologue( hCommandQueue, pOrdinal );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueGetOrdinal", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueGetOrdinalPrologue( hCommandQueue, pOrdinal );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueGetOrdinal", result);
        }

        auto driver_result = pfnGetOrdinal( hCommandQueue, pOrdinal );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandQueueGetOrdinalEpilogue( hCommandQueue, pOrdinal ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueGetOrdinal", result);
        }

        return logAndPropagateResult("zeCommandQueueGetOrdinal", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueGetIndex
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueGetIndex(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t* pIndex                                ///< [out] command queue index within the group
        )
    {
        context.logger->log_trace("zeCommandQueueGetIndex(hCommandQueue, pIndex)");

        auto pfnGetIndex = context.zeDdiTable.CommandQueue.pfnGetIndex;

        if( nullptr == pfnGetIndex )
            return logAndPropagateResult("zeCommandQueueGetIndex", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandQueueGetIndexPrologue( hCommandQueue, pIndex );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueGetIndex", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueGetIndexPrologue( hCommandQueue, pIndex );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueGetIndex", result);
        }

        auto driver_result = pfnGetIndex( hCommandQueue, pIndex );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandQueueGetIndexEpilogue( hCommandQueue, pIndex ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandQueueGetIndex", result);
        }

        return logAndPropagateResult("zeCommandQueueGetIndex", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        context.logger->log_trace("zeCommandListCreate(hContext, hDevice, desc, phCommandList)");

        auto pfnCreate = context.zeDdiTable.CommandList.pfnCreate;

        if( nullptr == pfnCreate )
            return logAndPropagateResult("zeCommandListCreate", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListCreatePrologue( hContext, hDevice, desc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListCreate", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListCreatePrologue( hContext, hDevice, desc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListCreate", result);
        }

        auto driver_result = pfnCreate( hContext, hDevice, desc, phCommandList );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListCreateEpilogue( hContext, hDevice, desc, phCommandList ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListCreate", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phCommandList){
                context.handleLifetime->addHandle( *phCommandList );
                context.handleLifetime->addDependent( hContext, *phCommandList );

            }
        }
        return logAndPropagateResult("zeCommandListCreate", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListCreateImmediate
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListCreateImmediate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        const ze_command_queue_desc_t* altdesc,         ///< [in] pointer to command queue descriptor
        ze_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
        )
    {
        context.logger->log_trace("zeCommandListCreateImmediate(hContext, hDevice, altdesc, phCommandList)");

        auto pfnCreateImmediate = context.zeDdiTable.CommandList.pfnCreateImmediate;

        if( nullptr == pfnCreateImmediate )
            return logAndPropagateResult("zeCommandListCreateImmediate", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListCreateImmediatePrologue( hContext, hDevice, altdesc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListCreateImmediate", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListCreateImmediatePrologue( hContext, hDevice, altdesc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListCreateImmediate", result);
        }

        auto driver_result = pfnCreateImmediate( hContext, hDevice, altdesc, phCommandList );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListCreateImmediateEpilogue( hContext, hDevice, altdesc, phCommandList ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListCreateImmediate", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phCommandList){
                context.handleLifetime->addHandle( *phCommandList , false);
            }
        }
        return logAndPropagateResult("zeCommandListCreateImmediate", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListDestroy(
        ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
        )
    {
        context.logger->log_trace("zeCommandListDestroy(hCommandList)");

        auto pfnDestroy = context.zeDdiTable.CommandList.pfnDestroy;

        if( nullptr == pfnDestroy )
            return logAndPropagateResult("zeCommandListDestroy", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListDestroyPrologue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListDestroy", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListDestroyPrologue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListDestroy", result);
        }

        auto driver_result = pfnDestroy( hCommandList );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListDestroyEpilogue( hCommandList ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListDestroy", result);
        }

        return logAndPropagateResult("zeCommandListDestroy", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListClose
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListClose(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
        )
    {
        context.logger->log_trace("zeCommandListClose(hCommandList)");

        auto pfnClose = context.zeDdiTable.CommandList.pfnClose;

        if( nullptr == pfnClose )
            return logAndPropagateResult("zeCommandListClose", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListClosePrologue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListClose", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListClosePrologue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListClose", result);
        }

        auto driver_result = pfnClose( hCommandList );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListCloseEpilogue( hCommandList ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListClose", result);
        }

        return logAndPropagateResult("zeCommandListClose", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListReset
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListReset(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
        )
    {
        context.logger->log_trace("zeCommandListReset(hCommandList)");

        auto pfnReset = context.zeDdiTable.CommandList.pfnReset;

        if( nullptr == pfnReset )
            return logAndPropagateResult("zeCommandListReset", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListResetPrologue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListReset", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListResetPrologue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListReset", result);
        }

        auto driver_result = pfnReset( hCommandList );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListResetEpilogue( hCommandList ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListReset", result);
        }

        return logAndPropagateResult("zeCommandListReset", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendWriteGlobalTimestamp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendWriteGlobalTimestamp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint64_t* dstptr,                               ///< [in,out] pointer to memory where timestamp value will be written; must
                                                        ///< be 8byte-aligned.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing query;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing query
        )
    {
        context.logger->log_trace("zeCommandListAppendWriteGlobalTimestamp(hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendWriteGlobalTimestamp = context.zeDdiTable.CommandList.pfnAppendWriteGlobalTimestamp;

        if( nullptr == pfnAppendWriteGlobalTimestamp )
            return logAndPropagateResult("zeCommandListAppendWriteGlobalTimestamp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendWriteGlobalTimestampPrologue( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendWriteGlobalTimestamp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendWriteGlobalTimestampPrologue( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendWriteGlobalTimestamp", result);
        }

        auto driver_result = pfnAppendWriteGlobalTimestamp( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendWriteGlobalTimestampEpilogue( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendWriteGlobalTimestamp", result);
        }

        return logAndPropagateResult("zeCommandListAppendWriteGlobalTimestamp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListHostSynchronize
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListHostSynchronize(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the immediate command list
        uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then immediately returns the status of the immediate command list;
                                                        ///< if `UINT64_MAX`, then function will not return until complete or
                                                        ///< device is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        context.logger->log_trace("zeCommandListHostSynchronize(hCommandList, timeout)");

        auto pfnHostSynchronize = context.zeDdiTable.CommandList.pfnHostSynchronize;

        if( nullptr == pfnHostSynchronize )
            return logAndPropagateResult("zeCommandListHostSynchronize", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListHostSynchronizePrologue( hCommandList, timeout );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListHostSynchronize", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListHostSynchronizePrologue( hCommandList, timeout );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListHostSynchronize", result);
        }

        auto driver_result = pfnHostSynchronize( hCommandList, timeout );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListHostSynchronizeEpilogue( hCommandList, timeout ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListHostSynchronize", result);
        }

        return logAndPropagateResult("zeCommandListHostSynchronize", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListGetDeviceHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetDeviceHandle(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_device_handle_t* phDevice                    ///< [out] handle of the device on which the command list was created
        )
    {
        context.logger->log_trace("zeCommandListGetDeviceHandle(hCommandList, phDevice)");

        auto pfnGetDeviceHandle = context.zeDdiTable.CommandList.pfnGetDeviceHandle;

        if( nullptr == pfnGetDeviceHandle )
            return logAndPropagateResult("zeCommandListGetDeviceHandle", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListGetDeviceHandlePrologue( hCommandList, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListGetDeviceHandle", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListGetDeviceHandlePrologue( hCommandList, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListGetDeviceHandle", result);
        }

        auto driver_result = pfnGetDeviceHandle( hCommandList, phDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListGetDeviceHandleEpilogue( hCommandList, phDevice ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListGetDeviceHandle", result);
        }

        return logAndPropagateResult("zeCommandListGetDeviceHandle", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListGetContextHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetContextHandle(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_context_handle_t* phContext                  ///< [out] handle of the context on which the command list was created
        )
    {
        context.logger->log_trace("zeCommandListGetContextHandle(hCommandList, phContext)");

        auto pfnGetContextHandle = context.zeDdiTable.CommandList.pfnGetContextHandle;

        if( nullptr == pfnGetContextHandle )
            return logAndPropagateResult("zeCommandListGetContextHandle", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListGetContextHandlePrologue( hCommandList, phContext );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListGetContextHandle", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListGetContextHandlePrologue( hCommandList, phContext );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListGetContextHandle", result);
        }

        auto driver_result = pfnGetContextHandle( hCommandList, phContext );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListGetContextHandleEpilogue( hCommandList, phContext ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListGetContextHandle", result);
        }

        return logAndPropagateResult("zeCommandListGetContextHandle", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListGetOrdinal
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetOrdinal(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t* pOrdinal                              ///< [out] command queue group ordinal to which command list is submitted
        )
    {
        context.logger->log_trace("zeCommandListGetOrdinal(hCommandList, pOrdinal)");

        auto pfnGetOrdinal = context.zeDdiTable.CommandList.pfnGetOrdinal;

        if( nullptr == pfnGetOrdinal )
            return logAndPropagateResult("zeCommandListGetOrdinal", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListGetOrdinalPrologue( hCommandList, pOrdinal );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListGetOrdinal", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListGetOrdinalPrologue( hCommandList, pOrdinal );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListGetOrdinal", result);
        }

        auto driver_result = pfnGetOrdinal( hCommandList, pOrdinal );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListGetOrdinalEpilogue( hCommandList, pOrdinal ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListGetOrdinal", result);
        }

        return logAndPropagateResult("zeCommandListGetOrdinal", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListImmediateGetIndex
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListImmediateGetIndex(
        ze_command_list_handle_t hCommandListImmediate, ///< [in] handle of the immediate command list
        uint32_t* pIndex                                ///< [out] command queue index within the group to which the immediate
                                                        ///< command list is submitted
        )
    {
        context.logger->log_trace("zeCommandListImmediateGetIndex(hCommandListImmediate, pIndex)");

        auto pfnImmediateGetIndex = context.zeDdiTable.CommandList.pfnImmediateGetIndex;

        if( nullptr == pfnImmediateGetIndex )
            return logAndPropagateResult("zeCommandListImmediateGetIndex", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListImmediateGetIndexPrologue( hCommandListImmediate, pIndex );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListImmediateGetIndex", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListImmediateGetIndexPrologue( hCommandListImmediate, pIndex );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListImmediateGetIndex", result);
        }

        auto driver_result = pfnImmediateGetIndex( hCommandListImmediate, pIndex );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListImmediateGetIndexEpilogue( hCommandListImmediate, pIndex ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListImmediateGetIndex", result);
        }

        return logAndPropagateResult("zeCommandListImmediateGetIndex", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListIsImmediate
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListIsImmediate(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_bool_t* pIsImmediate                         ///< [out] Boolean indicating whether the command list is an immediate
                                                        ///< command list (true) or not (false)
        )
    {
        context.logger->log_trace("zeCommandListIsImmediate(hCommandList, pIsImmediate)");

        auto pfnIsImmediate = context.zeDdiTable.CommandList.pfnIsImmediate;

        if( nullptr == pfnIsImmediate )
            return logAndPropagateResult("zeCommandListIsImmediate", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListIsImmediatePrologue( hCommandList, pIsImmediate );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListIsImmediate", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListIsImmediatePrologue( hCommandList, pIsImmediate );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListIsImmediate", result);
        }

        auto driver_result = pfnIsImmediate( hCommandList, pIsImmediate );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListIsImmediateEpilogue( hCommandList, pIsImmediate ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListIsImmediate", result);
        }

        return logAndPropagateResult("zeCommandListIsImmediate", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendBarrier
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendBarrier(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        )
    {
        context.logger->log_trace("zeCommandListAppendBarrier(hCommandList, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendBarrier = context.zeDdiTable.CommandList.pfnAppendBarrier;

        if( nullptr == pfnAppendBarrier )
            return logAndPropagateResult("zeCommandListAppendBarrier", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendBarrierPrologue( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendBarrier", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendBarrierPrologue( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendBarrier", result);
        }

        auto driver_result = pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendBarrierEpilogue( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendBarrier", result);
        }

        return logAndPropagateResult("zeCommandListAppendBarrier", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryRangesBarrier
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryRangesBarrier(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numRanges,                             ///< [in] number of memory ranges
        const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
        const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing barrier
        )
    {
        context.logger->log_trace("zeCommandListAppendMemoryRangesBarrier(hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendMemoryRangesBarrier = context.zeDdiTable.CommandList.pfnAppendMemoryRangesBarrier;

        if( nullptr == pfnAppendMemoryRangesBarrier )
            return logAndPropagateResult("zeCommandListAppendMemoryRangesBarrier", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendMemoryRangesBarrierPrologue( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryRangesBarrier", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryRangesBarrierPrologue( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryRangesBarrier", result);
        }

        auto driver_result = pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendMemoryRangesBarrierEpilogue( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryRangesBarrier", result);
        }

        return logAndPropagateResult("zeCommandListAppendMemoryRangesBarrier", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextSystemBarrier
    __zedlllocal ze_result_t ZE_APICALL
    zeContextSystemBarrier(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        context.logger->log_trace("zeContextSystemBarrier(hContext, hDevice)");

        auto pfnSystemBarrier = context.zeDdiTable.Context.pfnSystemBarrier;

        if( nullptr == pfnSystemBarrier )
            return logAndPropagateResult("zeContextSystemBarrier", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextSystemBarrierPrologue( hContext, hDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextSystemBarrier", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextSystemBarrierPrologue( hContext, hDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextSystemBarrier", result);
        }

        auto driver_result = pfnSystemBarrier( hContext, hDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextSystemBarrierEpilogue( hContext, hDevice ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextSystemBarrier", result);
        }

        return logAndPropagateResult("zeContextSystemBarrier", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryCopy
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryCopy(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendMemoryCopy(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendMemoryCopy = context.zeDdiTable.CommandList.pfnAppendMemoryCopy;

        if( nullptr == pfnAppendMemoryCopy )
            return logAndPropagateResult("zeCommandListAppendMemoryCopy", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendMemoryCopyPrologue( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryCopy", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryCopyPrologue( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryCopy", result);
        }

        auto driver_result = pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendMemoryCopyEpilogue( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryCopy", result);
        }

        return logAndPropagateResult("zeCommandListAppendMemoryCopy", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryFill
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryFill(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* ptr,                                      ///< [in] pointer to memory to initialize
        const void* pattern,                            ///< [in] pointer to value to initialize memory to
        size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
        size_t size,                                    ///< [in] size in bytes to initialize
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendMemoryFill(hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendMemoryFill = context.zeDdiTable.CommandList.pfnAppendMemoryFill;

        if( nullptr == pfnAppendMemoryFill )
            return logAndPropagateResult("zeCommandListAppendMemoryFill", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendMemoryFillPrologue( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryFill", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryFillPrologue( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryFill", result);
        }

        auto driver_result = pfnAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendMemoryFillEpilogue( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryFill", result);
        }

        return logAndPropagateResult("zeCommandListAppendMemoryFill", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryCopyRegion
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryCopyRegion(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const ze_copy_region_t* dstRegion,              ///< [in] pointer to destination region to copy to
        uint32_t dstPitch,                              ///< [in] destination pitch in bytes
        uint32_t dstSlicePitch,                         ///< [in] destination slice pitch in bytes. This is required for 3D region
                                                        ///< copies where the `depth` member of ::ze_copy_region_t is not 0,
                                                        ///< otherwise it's ignored.
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_copy_region_t* srcRegion,              ///< [in] pointer to source region to copy from
        uint32_t srcPitch,                              ///< [in] source pitch in bytes
        uint32_t srcSlicePitch,                         ///< [in] source slice pitch in bytes. This is required for 3D region
                                                        ///< copies where the `depth` member of ::ze_copy_region_t is not 0,
                                                        ///< otherwise it's ignored.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendMemoryCopyRegion(hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendMemoryCopyRegion = context.zeDdiTable.CommandList.pfnAppendMemoryCopyRegion;

        if( nullptr == pfnAppendMemoryCopyRegion )
            return logAndPropagateResult("zeCommandListAppendMemoryCopyRegion", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendMemoryCopyRegionPrologue( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryCopyRegion", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryCopyRegionPrologue( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryCopyRegion", result);
        }

        auto driver_result = pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendMemoryCopyRegionEpilogue( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryCopyRegion", result);
        }

        return logAndPropagateResult("zeCommandListAppendMemoryCopyRegion", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryCopyFromContext
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryCopyFromContext(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        ze_context_handle_t hContextSrc,                ///< [in] handle of source context object
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendMemoryCopyFromContext(hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendMemoryCopyFromContext = context.zeDdiTable.CommandList.pfnAppendMemoryCopyFromContext;

        if( nullptr == pfnAppendMemoryCopyFromContext )
            return logAndPropagateResult("zeCommandListAppendMemoryCopyFromContext", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendMemoryCopyFromContextPrologue( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryCopyFromContext", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryCopyFromContextPrologue( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryCopyFromContext", result);
        }

        auto driver_result = pfnAppendMemoryCopyFromContext( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendMemoryCopyFromContextEpilogue( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryCopyFromContext", result);
        }

        return logAndPropagateResult("zeCommandListAppendMemoryCopyFromContext", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopy
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopy(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendImageCopy(hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendImageCopy = context.zeDdiTable.CommandList.pfnAppendImageCopy;

        if( nullptr == pfnAppendImageCopy )
            return logAndPropagateResult("zeCommandListAppendImageCopy", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendImageCopyPrologue( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopy", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyPrologue( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopy", result);
        }

        auto driver_result = pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendImageCopyEpilogue( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopy", result);
        }

        return logAndPropagateResult("zeCommandListAppendImageCopy", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyRegion
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopyRegion(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendImageCopyRegion(hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendImageCopyRegion = context.zeDdiTable.CommandList.pfnAppendImageCopyRegion;

        if( nullptr == pfnAppendImageCopyRegion )
            return logAndPropagateResult("zeCommandListAppendImageCopyRegion", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendImageCopyRegionPrologue( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopyRegion", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyRegionPrologue( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopyRegion", result);
        }

        auto driver_result = pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendImageCopyRegionEpilogue( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopyRegion", result);
        }

        return logAndPropagateResult("zeCommandListAppendImageCopyRegion", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyToMemory
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopyToMemory(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendImageCopyToMemory(hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendImageCopyToMemory = context.zeDdiTable.CommandList.pfnAppendImageCopyToMemory;

        if( nullptr == pfnAppendImageCopyToMemory )
            return logAndPropagateResult("zeCommandListAppendImageCopyToMemory", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendImageCopyToMemoryPrologue( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopyToMemory", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyToMemoryPrologue( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopyToMemory", result);
        }

        auto driver_result = pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendImageCopyToMemoryEpilogue( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopyToMemory", result);
        }

        return logAndPropagateResult("zeCommandListAppendImageCopyToMemory", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyFromMemory
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopyFromMemory(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendImageCopyFromMemory(hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendImageCopyFromMemory = context.zeDdiTable.CommandList.pfnAppendImageCopyFromMemory;

        if( nullptr == pfnAppendImageCopyFromMemory )
            return logAndPropagateResult("zeCommandListAppendImageCopyFromMemory", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendImageCopyFromMemoryPrologue( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopyFromMemory", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyFromMemoryPrologue( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopyFromMemory", result);
        }

        auto driver_result = pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendImageCopyFromMemoryEpilogue( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopyFromMemory", result);
        }

        return logAndPropagateResult("zeCommandListAppendImageCopyFromMemory", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemoryPrefetch
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemoryPrefetch(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t size                                     ///< [in] size in bytes of the memory range to prefetch
        )
    {
        context.logger->log_trace("zeCommandListAppendMemoryPrefetch(hCommandList, ptr, size)");

        auto pfnAppendMemoryPrefetch = context.zeDdiTable.CommandList.pfnAppendMemoryPrefetch;

        if( nullptr == pfnAppendMemoryPrefetch )
            return logAndPropagateResult("zeCommandListAppendMemoryPrefetch", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendMemoryPrefetchPrologue( hCommandList, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryPrefetch", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryPrefetchPrologue( hCommandList, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryPrefetch", result);
        }

        auto driver_result = pfnAppendMemoryPrefetch( hCommandList, ptr, size );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendMemoryPrefetchEpilogue( hCommandList, ptr, size ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemoryPrefetch", result);
        }

        return logAndPropagateResult("zeCommandListAppendMemoryPrefetch", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendMemAdvise
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendMemAdvise(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_advice_t advice                       ///< [in] Memory advice for the memory range
        )
    {
        context.logger->log_trace("zeCommandListAppendMemAdvise(hCommandList, hDevice, ptr, size, advice)");

        auto pfnAppendMemAdvise = context.zeDdiTable.CommandList.pfnAppendMemAdvise;

        if( nullptr == pfnAppendMemAdvise )
            return logAndPropagateResult("zeCommandListAppendMemAdvise", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendMemAdvisePrologue( hCommandList, hDevice, ptr, size, advice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemAdvise", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemAdvisePrologue( hCommandList, hDevice, ptr, size, advice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemAdvise", result);
        }

        auto driver_result = pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendMemAdviseEpilogue( hCommandList, hDevice, ptr, size, advice ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendMemAdvise", result);
        }

        return logAndPropagateResult("zeCommandListAppendMemAdvise", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
        uint32_t numDevices,                            ///< [in][optional] number of device handles; must be 0 if `nullptr ==
                                                        ///< phDevices`
        ze_device_handle_t* phDevices,                  ///< [in][optional][range(0, numDevices)] array of device handles which
                                                        ///< have visibility to the event pool.
                                                        ///< if nullptr, then event pool is visible to all devices supported by the
                                                        ///< driver instance.
        ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        context.logger->log_trace("zeEventPoolCreate(hContext, desc, numDevices, phDevicesLocal, phEventPool)");

        auto pfnCreate = context.zeDdiTable.EventPool.pfnCreate;

        if( nullptr == pfnCreate )
            return logAndPropagateResult("zeEventPoolCreate", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolCreatePrologue( hContext, desc, numDevices, phDevices, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolCreate", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolCreatePrologue( hContext, desc, numDevices, phDevices, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolCreate", result);
        }

        auto driver_result = pfnCreate( hContext, desc, numDevices, phDevices, phEventPool );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolCreateEpilogue( hContext, desc, numDevices, phDevices, phEventPool ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolCreate", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phEventPool){
                context.handleLifetime->addHandle( *phEventPool );
                context.handleLifetime->addDependent( hContext, *phEventPool );

            }
        }
        return logAndPropagateResult("zeEventPoolCreate", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolDestroy(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
        )
    {
        context.logger->log_trace("zeEventPoolDestroy(hEventPool)");

        auto pfnDestroy = context.zeDdiTable.EventPool.pfnDestroy;

        if( nullptr == pfnDestroy )
            return logAndPropagateResult("zeEventPoolDestroy", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolDestroyPrologue( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolDestroy", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolDestroyPrologue( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolDestroy", result);
        }

        auto driver_result = pfnDestroy( hEventPool );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolDestroyEpilogue( hEventPool ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolDestroy", result);
        }

        return logAndPropagateResult("zeEventPoolDestroy", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeEventCreate(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        const ze_event_desc_t* desc,                    ///< [in] pointer to event descriptor
        ze_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
        )
    {
        context.logger->log_trace("zeEventCreate(hEventPool, desc, phEvent)");

        auto pfnCreate = context.zeDdiTable.Event.pfnCreate;

        if( nullptr == pfnCreate )
            return logAndPropagateResult("zeEventCreate", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventCreatePrologue( hEventPool, desc, phEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventCreate", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventCreatePrologue( hEventPool, desc, phEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventCreate", result);
        }

        auto driver_result = pfnCreate( hEventPool, desc, phEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventCreateEpilogue( hEventPool, desc, phEvent ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventCreate", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phEvent){
                context.handleLifetime->addHandle( *phEvent );
                context.handleLifetime->addDependent( hEventPool, *phEvent );

            }
        }
        return logAndPropagateResult("zeEventCreate", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeEventDestroy(
        ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
        )
    {
        context.logger->log_trace("zeEventDestroy(hEvent)");

        auto pfnDestroy = context.zeDdiTable.Event.pfnDestroy;

        if( nullptr == pfnDestroy )
            return logAndPropagateResult("zeEventDestroy", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventDestroyPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventDestroy", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventDestroyPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventDestroy", result);
        }

        auto driver_result = pfnDestroy( hEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventDestroyEpilogue( hEvent ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventDestroy", result);
        }

        return logAndPropagateResult("zeEventDestroy", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolGetIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolGetIpcHandle(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
        ze_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
        )
    {
        context.logger->log_trace("zeEventPoolGetIpcHandle(hEventPool, phIpc)");

        auto pfnGetIpcHandle = context.zeDdiTable.EventPool.pfnGetIpcHandle;

        if( nullptr == pfnGetIpcHandle )
            return logAndPropagateResult("zeEventPoolGetIpcHandle", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolGetIpcHandlePrologue( hEventPool, phIpc );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolGetIpcHandle", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolGetIpcHandlePrologue( hEventPool, phIpc );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolGetIpcHandle", result);
        }

        auto driver_result = pfnGetIpcHandle( hEventPool, phIpc );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolGetIpcHandleEpilogue( hEventPool, phIpc ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolGetIpcHandle", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zeEventPoolGetIpcHandle", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolPutIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolPutIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object associated with the IPC event pool
                                                        ///< handle
        ze_ipc_event_pool_handle_t hIpc                 ///< [in] IPC event pool handle
        )
    {
        context.logger->log_trace("zeEventPoolPutIpcHandle(hContext, hIpc)");

        auto pfnPutIpcHandle = context.zeDdiTable.EventPool.pfnPutIpcHandle;

        if( nullptr == pfnPutIpcHandle )
            return logAndPropagateResult("zeEventPoolPutIpcHandle", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolPutIpcHandlePrologue( hContext, hIpc );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolPutIpcHandle", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolPutIpcHandlePrologue( hContext, hIpc );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolPutIpcHandle", result);
        }

        auto driver_result = pfnPutIpcHandle( hContext, hIpc );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolPutIpcHandleEpilogue( hContext, hIpc ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolPutIpcHandle", result);
        }

        return logAndPropagateResult("zeEventPoolPutIpcHandle", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolOpenIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolOpenIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object to associate with the IPC event pool
                                                        ///< handle
        ze_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event pool handle
        ze_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
        )
    {
        context.logger->log_trace("zeEventPoolOpenIpcHandle(hContext, hIpc, phEventPool)");

        auto pfnOpenIpcHandle = context.zeDdiTable.EventPool.pfnOpenIpcHandle;

        if( nullptr == pfnOpenIpcHandle )
            return logAndPropagateResult("zeEventPoolOpenIpcHandle", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolOpenIpcHandlePrologue( hContext, hIpc, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolOpenIpcHandle", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolOpenIpcHandlePrologue( hContext, hIpc, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolOpenIpcHandle", result);
        }

        auto driver_result = pfnOpenIpcHandle( hContext, hIpc, phEventPool );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolOpenIpcHandleEpilogue( hContext, hIpc, phEventPool ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolOpenIpcHandle", result);
        }

        return logAndPropagateResult("zeEventPoolOpenIpcHandle", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolCloseIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolCloseIpcHandle(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
        )
    {
        context.logger->log_trace("zeEventPoolCloseIpcHandle(hEventPool)");

        auto pfnCloseIpcHandle = context.zeDdiTable.EventPool.pfnCloseIpcHandle;

        if( nullptr == pfnCloseIpcHandle )
            return logAndPropagateResult("zeEventPoolCloseIpcHandle", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolCloseIpcHandlePrologue( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolCloseIpcHandle", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolCloseIpcHandlePrologue( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolCloseIpcHandle", result);
        }

        auto driver_result = pfnCloseIpcHandle( hEventPool );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolCloseIpcHandleEpilogue( hEventPool ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolCloseIpcHandle", result);
        }

        return logAndPropagateResult("zeEventPoolCloseIpcHandle", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendSignalEvent
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendSignalEvent(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        context.logger->log_trace("zeCommandListAppendSignalEvent(hCommandList, hEvent)");

        auto pfnAppendSignalEvent = context.zeDdiTable.CommandList.pfnAppendSignalEvent;

        if( nullptr == pfnAppendSignalEvent )
            return logAndPropagateResult("zeCommandListAppendSignalEvent", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendSignalEventPrologue( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendSignalEvent", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendSignalEventPrologue( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendSignalEvent", result);
        }

        auto driver_result = pfnAppendSignalEvent( hCommandList, hEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendSignalEventEpilogue( hCommandList, hEvent ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendSignalEvent", result);
        }

        return logAndPropagateResult("zeCommandListAppendSignalEvent", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendWaitOnEvents
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendWaitOnEvents(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        ze_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handles of the events to wait on before
                                                        ///< continuing
        )
    {
        context.logger->log_trace("zeCommandListAppendWaitOnEvents(hCommandList, numEvents, phEventsLocal)");

        auto pfnAppendWaitOnEvents = context.zeDdiTable.CommandList.pfnAppendWaitOnEvents;

        if( nullptr == pfnAppendWaitOnEvents )
            return logAndPropagateResult("zeCommandListAppendWaitOnEvents", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendWaitOnEventsPrologue( hCommandList, numEvents, phEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendWaitOnEvents", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendWaitOnEventsPrologue( hCommandList, numEvents, phEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendWaitOnEvents", result);
        }

        auto driver_result = pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendWaitOnEventsEpilogue( hCommandList, numEvents, phEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendWaitOnEvents", result);
        }

        return logAndPropagateResult("zeCommandListAppendWaitOnEvents", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostSignal
    __zedlllocal ze_result_t ZE_APICALL
    zeEventHostSignal(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        context.logger->log_trace("zeEventHostSignal(hEvent)");

        auto pfnHostSignal = context.zeDdiTable.Event.pfnHostSignal;

        if( nullptr == pfnHostSignal )
            return logAndPropagateResult("zeEventHostSignal", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventHostSignalPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventHostSignal", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventHostSignalPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventHostSignal", result);
        }

        auto driver_result = pfnHostSignal( hEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventHostSignalEpilogue( hEvent ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventHostSignal", result);
        }

        return logAndPropagateResult("zeEventHostSignal", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostSynchronize
    __zedlllocal ze_result_t ZE_APICALL
    zeEventHostSynchronize(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeEventQueryStatus;
                                                        ///< if `UINT64_MAX`, then function will not return until complete or
                                                        ///< device is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        context.logger->log_trace("zeEventHostSynchronize(hEvent, timeout)");

        auto pfnHostSynchronize = context.zeDdiTable.Event.pfnHostSynchronize;

        if( nullptr == pfnHostSynchronize )
            return logAndPropagateResult("zeEventHostSynchronize", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventHostSynchronizePrologue( hEvent, timeout );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventHostSynchronize", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventHostSynchronizePrologue( hEvent, timeout );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventHostSynchronize", result);
        }

        auto driver_result = pfnHostSynchronize( hEvent, timeout );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventHostSynchronizeEpilogue( hEvent, timeout ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventHostSynchronize", result);
        }

        return logAndPropagateResult("zeEventHostSynchronize", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryStatus(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        context.logger->log_trace("zeEventQueryStatus(hEvent)");

        auto pfnQueryStatus = context.zeDdiTable.Event.pfnQueryStatus;

        if( nullptr == pfnQueryStatus )
            return logAndPropagateResult("zeEventQueryStatus", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventQueryStatusPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventQueryStatus", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventQueryStatusPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventQueryStatus", result);
        }

        auto driver_result = pfnQueryStatus( hEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventQueryStatusEpilogue( hEvent ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventQueryStatus", result);
        }

        return logAndPropagateResult("zeEventQueryStatus", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendEventReset
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendEventReset(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        context.logger->log_trace("zeCommandListAppendEventReset(hCommandList, hEvent)");

        auto pfnAppendEventReset = context.zeDdiTable.CommandList.pfnAppendEventReset;

        if( nullptr == pfnAppendEventReset )
            return logAndPropagateResult("zeCommandListAppendEventReset", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendEventResetPrologue( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendEventReset", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendEventResetPrologue( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendEventReset", result);
        }

        auto driver_result = pfnAppendEventReset( hCommandList, hEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendEventResetEpilogue( hCommandList, hEvent ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendEventReset", result);
        }

        return logAndPropagateResult("zeCommandListAppendEventReset", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostReset
    __zedlllocal ze_result_t ZE_APICALL
    zeEventHostReset(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        context.logger->log_trace("zeEventHostReset(hEvent)");

        auto pfnHostReset = context.zeDdiTable.Event.pfnHostReset;

        if( nullptr == pfnHostReset )
            return logAndPropagateResult("zeEventHostReset", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventHostResetPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventHostReset", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventHostResetPrologue( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventHostReset", result);
        }

        auto driver_result = pfnHostReset( hEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventHostResetEpilogue( hEvent ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventHostReset", result);
        }

        return logAndPropagateResult("zeEventHostReset", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryKernelTimestamp
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryKernelTimestamp(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_kernel_timestamp_result_t* dstptr            ///< [in,out] pointer to memory for where timestamp result will be written.
        )
    {
        context.logger->log_trace("zeEventQueryKernelTimestamp(hEvent, dstptr)");

        auto pfnQueryKernelTimestamp = context.zeDdiTable.Event.pfnQueryKernelTimestamp;

        if( nullptr == pfnQueryKernelTimestamp )
            return logAndPropagateResult("zeEventQueryKernelTimestamp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventQueryKernelTimestampPrologue( hEvent, dstptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventQueryKernelTimestamp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventQueryKernelTimestampPrologue( hEvent, dstptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventQueryKernelTimestamp", result);
        }

        auto driver_result = pfnQueryKernelTimestamp( hEvent, dstptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventQueryKernelTimestampEpilogue( hEvent, dstptr ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventQueryKernelTimestamp", result);
        }

        return logAndPropagateResult("zeEventQueryKernelTimestamp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendQueryKernelTimestamps
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendQueryKernelTimestamps(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] the number of timestamp events to query
        ze_event_handle_t* phEvents,                    ///< [in][range(0, numEvents)] handles of timestamp events to query
        void* dstptr,                                   ///< [in,out] pointer to memory where ::ze_kernel_timestamp_result_t will
                                                        ///< be written; must be size-aligned.
        const size_t* pOffsets,                         ///< [in][optional][range(0, numEvents)] offset, in bytes, to write
                                                        ///< results; address must be 4byte-aligned and offsets must be
                                                        ///< size-aligned.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing query;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing query
        )
    {
        context.logger->log_trace("zeCommandListAppendQueryKernelTimestamps(hCommandList, numEvents, phEventsLocal, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendQueryKernelTimestamps = context.zeDdiTable.CommandList.pfnAppendQueryKernelTimestamps;

        if( nullptr == pfnAppendQueryKernelTimestamps )
            return logAndPropagateResult("zeCommandListAppendQueryKernelTimestamps", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendQueryKernelTimestampsPrologue( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendQueryKernelTimestamps", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendQueryKernelTimestampsPrologue( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendQueryKernelTimestamps", result);
        }

        auto driver_result = pfnAppendQueryKernelTimestamps( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendQueryKernelTimestampsEpilogue( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendQueryKernelTimestamps", result);
        }

        return logAndPropagateResult("zeCommandListAppendQueryKernelTimestamps", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventGetEventPool
    __zedlllocal ze_result_t ZE_APICALL
    zeEventGetEventPool(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_pool_handle_t* phEventPool             ///< [out] handle of the event pool for the event
        )
    {
        context.logger->log_trace("zeEventGetEventPool(hEvent, phEventPool)");

        auto pfnGetEventPool = context.zeDdiTable.Event.pfnGetEventPool;

        if( nullptr == pfnGetEventPool )
            return logAndPropagateResult("zeEventGetEventPool", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventGetEventPoolPrologue( hEvent, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventGetEventPool", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventGetEventPoolPrologue( hEvent, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventGetEventPool", result);
        }

        auto driver_result = pfnGetEventPool( hEvent, phEventPool );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventGetEventPoolEpilogue( hEvent, phEventPool ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventGetEventPool", result);
        }

        return logAndPropagateResult("zeEventGetEventPool", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventGetSignalScope
    __zedlllocal ze_result_t ZE_APICALL
    zeEventGetSignalScope(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_scope_flags_t* pSignalScope            ///< [out] signal event scope. This is the scope of relevant cache
                                                        ///< hierarchies that are flushed on a signal action before the event is
                                                        ///< triggered. May be 0 or a valid combination of ::ze_event_scope_flag_t.
        )
    {
        context.logger->log_trace("zeEventGetSignalScope(hEvent, pSignalScope)");

        auto pfnGetSignalScope = context.zeDdiTable.Event.pfnGetSignalScope;

        if( nullptr == pfnGetSignalScope )
            return logAndPropagateResult("zeEventGetSignalScope", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventGetSignalScopePrologue( hEvent, pSignalScope );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventGetSignalScope", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventGetSignalScopePrologue( hEvent, pSignalScope );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventGetSignalScope", result);
        }

        auto driver_result = pfnGetSignalScope( hEvent, pSignalScope );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventGetSignalScopeEpilogue( hEvent, pSignalScope ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventGetSignalScope", result);
        }

        return logAndPropagateResult("zeEventGetSignalScope", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventGetWaitScope
    __zedlllocal ze_result_t ZE_APICALL
    zeEventGetWaitScope(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_event_scope_flags_t* pWaitScope              ///< [out] wait event scope. This is the scope of relevant cache
                                                        ///< hierarchies invalidated on a wait action after the event is complete.
                                                        ///< May be 0 or a valid combination of ::ze_event_scope_flag_t.
        )
    {
        context.logger->log_trace("zeEventGetWaitScope(hEvent, pWaitScope)");

        auto pfnGetWaitScope = context.zeDdiTable.Event.pfnGetWaitScope;

        if( nullptr == pfnGetWaitScope )
            return logAndPropagateResult("zeEventGetWaitScope", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventGetWaitScopePrologue( hEvent, pWaitScope );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventGetWaitScope", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventGetWaitScopePrologue( hEvent, pWaitScope );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventGetWaitScope", result);
        }

        auto driver_result = pfnGetWaitScope( hEvent, pWaitScope );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventGetWaitScopeEpilogue( hEvent, pWaitScope ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventGetWaitScope", result);
        }

        return logAndPropagateResult("zeEventGetWaitScope", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolGetContextHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolGetContextHandle(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        ze_context_handle_t* phContext                  ///< [out] handle of the context on which the event pool was created
        )
    {
        context.logger->log_trace("zeEventPoolGetContextHandle(hEventPool, phContext)");

        auto pfnGetContextHandle = context.zeDdiTable.EventPool.pfnGetContextHandle;

        if( nullptr == pfnGetContextHandle )
            return logAndPropagateResult("zeEventPoolGetContextHandle", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolGetContextHandlePrologue( hEventPool, phContext );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolGetContextHandle", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolGetContextHandlePrologue( hEventPool, phContext );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolGetContextHandle", result);
        }

        auto driver_result = pfnGetContextHandle( hEventPool, phContext );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolGetContextHandleEpilogue( hEventPool, phContext ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolGetContextHandle", result);
        }

        return logAndPropagateResult("zeEventPoolGetContextHandle", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolGetFlags
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolGetFlags(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        ze_event_pool_flags_t* pFlags                   ///< [out] creation flags used to create the event pool; may be 0 or a
                                                        ///< valid combination of ::ze_event_pool_flag_t
        )
    {
        context.logger->log_trace("zeEventPoolGetFlags(hEventPool, pFlags)");

        auto pfnGetFlags = context.zeDdiTable.EventPool.pfnGetFlags;

        if( nullptr == pfnGetFlags )
            return logAndPropagateResult("zeEventPoolGetFlags", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolGetFlagsPrologue( hEventPool, pFlags );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolGetFlags", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolGetFlagsPrologue( hEventPool, pFlags );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolGetFlags", result);
        }

        auto driver_result = pfnGetFlags( hEventPool, pFlags );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventPoolGetFlagsEpilogue( hEventPool, pFlags ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventPoolGetFlags", result);
        }

        return logAndPropagateResult("zeEventPoolGetFlags", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceCreate(
        ze_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
        const ze_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
        ze_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
        )
    {
        context.logger->log_trace("zeFenceCreate(hCommandQueue, desc, phFence)");

        auto pfnCreate = context.zeDdiTable.Fence.pfnCreate;

        if( nullptr == pfnCreate )
            return logAndPropagateResult("zeFenceCreate", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFenceCreatePrologue( hCommandQueue, desc, phFence );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFenceCreate", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFenceCreatePrologue( hCommandQueue, desc, phFence );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFenceCreate", result);
        }

        auto driver_result = pfnCreate( hCommandQueue, desc, phFence );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFenceCreateEpilogue( hCommandQueue, desc, phFence ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFenceCreate", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phFence){
                context.handleLifetime->addHandle( *phFence );
                context.handleLifetime->addDependent( hCommandQueue, *phFence );

            }
        }
        return logAndPropagateResult("zeFenceCreate", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceDestroy(
        ze_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
        )
    {
        context.logger->log_trace("zeFenceDestroy(hFence)");

        auto pfnDestroy = context.zeDdiTable.Fence.pfnDestroy;

        if( nullptr == pfnDestroy )
            return logAndPropagateResult("zeFenceDestroy", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFenceDestroyPrologue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFenceDestroy", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFenceDestroyPrologue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFenceDestroy", result);
        }

        auto driver_result = pfnDestroy( hFence );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFenceDestroyEpilogue( hFence ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFenceDestroy", result);
        }

        return logAndPropagateResult("zeFenceDestroy", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceHostSynchronize
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceHostSynchronize(
        ze_fence_handle_t hFence,                       ///< [in] handle of the fence
        uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                        ///< if `UINT64_MAX`, then function will not return until complete or
                                                        ///< device is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        context.logger->log_trace("zeFenceHostSynchronize(hFence, timeout)");

        auto pfnHostSynchronize = context.zeDdiTable.Fence.pfnHostSynchronize;

        if( nullptr == pfnHostSynchronize )
            return logAndPropagateResult("zeFenceHostSynchronize", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFenceHostSynchronizePrologue( hFence, timeout );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFenceHostSynchronize", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFenceHostSynchronizePrologue( hFence, timeout );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFenceHostSynchronize", result);
        }

        auto driver_result = pfnHostSynchronize( hFence, timeout );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFenceHostSynchronizeEpilogue( hFence, timeout ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFenceHostSynchronize", result);
        }

        return logAndPropagateResult("zeFenceHostSynchronize", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceQueryStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceQueryStatus(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        context.logger->log_trace("zeFenceQueryStatus(hFence)");

        auto pfnQueryStatus = context.zeDdiTable.Fence.pfnQueryStatus;

        if( nullptr == pfnQueryStatus )
            return logAndPropagateResult("zeFenceQueryStatus", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFenceQueryStatusPrologue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFenceQueryStatus", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFenceQueryStatusPrologue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFenceQueryStatus", result);
        }

        auto driver_result = pfnQueryStatus( hFence );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFenceQueryStatusEpilogue( hFence ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFenceQueryStatus", result);
        }

        return logAndPropagateResult("zeFenceQueryStatus", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceReset
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceReset(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        context.logger->log_trace("zeFenceReset(hFence)");

        auto pfnReset = context.zeDdiTable.Fence.pfnReset;

        if( nullptr == pfnReset )
            return logAndPropagateResult("zeFenceReset", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFenceResetPrologue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFenceReset", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFenceResetPrologue( hFence );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFenceReset", result);
        }

        auto driver_result = pfnReset( hFence );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFenceResetEpilogue( hFence ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFenceReset", result);
        }

        return logAndPropagateResult("zeFenceReset", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_properties_t* pImageProperties         ///< [out] pointer to image properties
        )
    {
        context.logger->log_trace("zeImageGetProperties(hDevice, desc, pImageProperties)");

        auto pfnGetProperties = context.zeDdiTable.Image.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zeImageGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageGetPropertiesPrologue( hDevice, desc, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageGetPropertiesPrologue( hDevice, desc, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hDevice, desc, pImageProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageGetPropertiesEpilogue( hDevice, desc, pImageProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageGetProperties", result);
        }

        return logAndPropagateResult("zeImageGetProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeImageCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
        )
    {
        context.logger->log_trace("zeImageCreate(hContext, hDevice, desc, phImage)");

        auto pfnCreate = context.zeDdiTable.Image.pfnCreate;

        if( nullptr == pfnCreate )
            return logAndPropagateResult("zeImageCreate", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageCreatePrologue( hContext, hDevice, desc, phImage );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageCreate", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageCreatePrologue( hContext, hDevice, desc, phImage );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageCreate", result);
        }

        auto driver_result = pfnCreate( hContext, hDevice, desc, phImage );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageCreateEpilogue( hContext, hDevice, desc, phImage ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageCreate", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phImage){
                context.handleLifetime->addHandle( *phImage );
                context.handleLifetime->addDependent( hContext, *phImage );

            }
        }
        return logAndPropagateResult("zeImageCreate", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeImageDestroy(
        ze_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
        )
    {
        context.logger->log_trace("zeImageDestroy(hImage)");

        auto pfnDestroy = context.zeDdiTable.Image.pfnDestroy;

        if( nullptr == pfnDestroy )
            return logAndPropagateResult("zeImageDestroy", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageDestroyPrologue( hImage );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageDestroy", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageDestroyPrologue( hImage );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageDestroy", result);
        }

        auto driver_result = pfnDestroy( hImage );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageDestroyEpilogue( hImage ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageDestroy", result);
        }

        return logAndPropagateResult("zeImageDestroy", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemAllocShared
    __zedlllocal ze_result_t ZE_APICALL
    zeMemAllocShared(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device memory allocation descriptor
        const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less than or equal to the
                                                        ///< `maxMemAllocSize` member of ::ze_device_properties_t
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two
        ze_device_handle_t hDevice,                     ///< [in][optional] device handle to associate with
        void** pptr                                     ///< [out] pointer to shared allocation
        )
    {
        context.logger->log_trace("zeMemAllocShared(hContext, device_desc, host_desc, size, alignment, hDevice, pptr)");

        auto pfnAllocShared = context.zeDdiTable.Mem.pfnAllocShared;

        if( nullptr == pfnAllocShared )
            return logAndPropagateResult("zeMemAllocShared", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemAllocSharedPrologue( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemAllocShared", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemAllocSharedPrologue( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemAllocShared", result);
        }

        auto driver_result = pfnAllocShared( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemAllocSharedEpilogue( hContext, device_desc, host_desc, size, alignment, hDevice, pptr ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemAllocShared", result);
        }

        return logAndPropagateResult("zeMemAllocShared", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemAllocDevice
    __zedlllocal ze_result_t ZE_APICALL
    zeMemAllocDevice(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_device_mem_alloc_desc_t* device_desc,  ///< [in] pointer to device memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less than or equal to the
                                                        ///< `maxMemAllocSize` member of ::ze_device_properties_t
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void** pptr                                     ///< [out] pointer to device allocation
        )
    {
        context.logger->log_trace("zeMemAllocDevice(hContext, device_desc, size, alignment, hDevice, pptr)");

        auto pfnAllocDevice = context.zeDdiTable.Mem.pfnAllocDevice;

        if( nullptr == pfnAllocDevice )
            return logAndPropagateResult("zeMemAllocDevice", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemAllocDevicePrologue( hContext, device_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemAllocDevice", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemAllocDevicePrologue( hContext, device_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemAllocDevice", result);
        }

        auto driver_result = pfnAllocDevice( hContext, device_desc, size, alignment, hDevice, pptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemAllocDeviceEpilogue( hContext, device_desc, size, alignment, hDevice, pptr ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemAllocDevice", result);
        }

        return logAndPropagateResult("zeMemAllocDevice", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemAllocHost
    __zedlllocal ze_result_t ZE_APICALL
    zeMemAllocHost(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_host_mem_alloc_desc_t* host_desc,      ///< [in] pointer to host memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less than or equal to the
                                                        ///< `maxMemAllocSize` member of ::ze_device_properties_t
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two
        void** pptr                                     ///< [out] pointer to host allocation
        )
    {
        context.logger->log_trace("zeMemAllocHost(hContext, host_desc, size, alignment, pptr)");

        auto pfnAllocHost = context.zeDdiTable.Mem.pfnAllocHost;

        if( nullptr == pfnAllocHost )
            return logAndPropagateResult("zeMemAllocHost", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemAllocHostPrologue( hContext, host_desc, size, alignment, pptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemAllocHost", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemAllocHostPrologue( hContext, host_desc, size, alignment, pptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemAllocHost", result);
        }

        auto driver_result = pfnAllocHost( hContext, host_desc, size, alignment, pptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemAllocHostEpilogue( hContext, host_desc, size, alignment, pptr ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemAllocHost", result);
        }

        return logAndPropagateResult("zeMemAllocHost", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemFree
    __zedlllocal ze_result_t ZE_APICALL
    zeMemFree(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        context.logger->log_trace("zeMemFree(hContext, ptr)");

        auto pfnFree = context.zeDdiTable.Mem.pfnFree;

        if( nullptr == pfnFree )
            return logAndPropagateResult("zeMemFree", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemFreePrologue( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemFree", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemFreePrologue( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemFree", result);
        }

        auto driver_result = pfnFree( hContext, ptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemFreeEpilogue( hContext, ptr ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemFree", result);
        }

        return logAndPropagateResult("zeMemFree", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetAllocProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetAllocProperties(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] memory pointer to query
        ze_memory_allocation_properties_t* pMemAllocProperties, ///< [in,out] query result for memory allocation properties
        ze_device_handle_t* phDevice                    ///< [out][optional] device associated with this allocation
        )
    {
        context.logger->log_trace("zeMemGetAllocProperties(hContext, ptr, pMemAllocProperties, phDevice)");

        auto pfnGetAllocProperties = context.zeDdiTable.Mem.pfnGetAllocProperties;

        if( nullptr == pfnGetAllocProperties )
            return logAndPropagateResult("zeMemGetAllocProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemGetAllocPropertiesPrologue( hContext, ptr, pMemAllocProperties, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetAllocProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetAllocPropertiesPrologue( hContext, ptr, pMemAllocProperties, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetAllocProperties", result);
        }

        auto driver_result = pfnGetAllocProperties( hContext, ptr, pMemAllocProperties, phDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemGetAllocPropertiesEpilogue( hContext, ptr, pMemAllocProperties, phDevice ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetAllocProperties", result);
        }

        return logAndPropagateResult("zeMemGetAllocProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetAddressRange
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetAddressRange(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        context.logger->log_trace("zeMemGetAddressRange(hContext, ptr, pBase, pSize)");

        auto pfnGetAddressRange = context.zeDdiTable.Mem.pfnGetAddressRange;

        if( nullptr == pfnGetAddressRange )
            return logAndPropagateResult("zeMemGetAddressRange", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemGetAddressRangePrologue( hContext, ptr, pBase, pSize );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetAddressRange", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetAddressRangePrologue( hContext, ptr, pBase, pSize );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetAddressRange", result);
        }

        auto driver_result = pfnGetAddressRange( hContext, ptr, pBase, pSize );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemGetAddressRangeEpilogue( hContext, ptr, pBase, pSize ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetAddressRange", result);
        }

        return logAndPropagateResult("zeMemGetAddressRange", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to the device memory allocation
        ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    {
        context.logger->log_trace("zeMemGetIpcHandle(hContext, ptr, pIpcHandle)");

        auto pfnGetIpcHandle = context.zeDdiTable.Mem.pfnGetIpcHandle;

        if( nullptr == pfnGetIpcHandle )
            return logAndPropagateResult("zeMemGetIpcHandle", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemGetIpcHandlePrologue( hContext, ptr, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetIpcHandle", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetIpcHandlePrologue( hContext, ptr, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetIpcHandle", result);
        }

        auto driver_result = pfnGetIpcHandle( hContext, ptr, pIpcHandle );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemGetIpcHandleEpilogue( hContext, ptr, pIpcHandle ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetIpcHandle", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zeMemGetIpcHandle", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetIpcHandleFromFileDescriptorExp
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetIpcHandleFromFileDescriptorExp(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        uint64_t handle,                                ///< [in] file descriptor
        ze_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
        )
    {
        context.logger->log_trace("zeMemGetIpcHandleFromFileDescriptorExp(hContext, handle, pIpcHandle)");

        auto pfnGetIpcHandleFromFileDescriptorExp = context.zeDdiTable.MemExp.pfnGetIpcHandleFromFileDescriptorExp;

        if( nullptr == pfnGetIpcHandleFromFileDescriptorExp )
            return logAndPropagateResult("zeMemGetIpcHandleFromFileDescriptorExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemGetIpcHandleFromFileDescriptorExpPrologue( hContext, handle, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetIpcHandleFromFileDescriptorExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetIpcHandleFromFileDescriptorExpPrologue( hContext, handle, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetIpcHandleFromFileDescriptorExp", result);
        }

        auto driver_result = pfnGetIpcHandleFromFileDescriptorExp( hContext, handle, pIpcHandle );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemGetIpcHandleFromFileDescriptorExpEpilogue( hContext, handle, pIpcHandle ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetIpcHandleFromFileDescriptorExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zeMemGetIpcHandleFromFileDescriptorExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetFileDescriptorFromIpcHandleExp
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetFileDescriptorFromIpcHandleExp(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_ipc_mem_handle_t ipcHandle,                  ///< [in] IPC memory handle
        uint64_t* pHandle                               ///< [out] Returned file descriptor
        )
    {
        context.logger->log_trace("zeMemGetFileDescriptorFromIpcHandleExp(hContext, ipcHandle, pHandle)");

        auto pfnGetFileDescriptorFromIpcHandleExp = context.zeDdiTable.MemExp.pfnGetFileDescriptorFromIpcHandleExp;

        if( nullptr == pfnGetFileDescriptorFromIpcHandleExp )
            return logAndPropagateResult("zeMemGetFileDescriptorFromIpcHandleExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemGetFileDescriptorFromIpcHandleExpPrologue( hContext, ipcHandle, pHandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetFileDescriptorFromIpcHandleExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetFileDescriptorFromIpcHandleExpPrologue( hContext, ipcHandle, pHandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetFileDescriptorFromIpcHandleExp", result);
        }

        auto driver_result = pfnGetFileDescriptorFromIpcHandleExp( hContext, ipcHandle, pHandle );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemGetFileDescriptorFromIpcHandleExpEpilogue( hContext, ipcHandle, pHandle ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetFileDescriptorFromIpcHandleExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zeMemGetFileDescriptorFromIpcHandleExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemPutIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeMemPutIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_ipc_mem_handle_t handle                      ///< [in] IPC memory handle
        )
    {
        context.logger->log_trace("zeMemPutIpcHandle(hContext, handle)");

        auto pfnPutIpcHandle = context.zeDdiTable.Mem.pfnPutIpcHandle;

        if( nullptr == pfnPutIpcHandle )
            return logAndPropagateResult("zeMemPutIpcHandle", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemPutIpcHandlePrologue( hContext, handle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemPutIpcHandle", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemPutIpcHandlePrologue( hContext, handle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemPutIpcHandle", result);
        }

        auto driver_result = pfnPutIpcHandle( hContext, handle );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemPutIpcHandleEpilogue( hContext, handle ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemPutIpcHandle", result);
        }

        return logAndPropagateResult("zeMemPutIpcHandle", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemOpenIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeMemOpenIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        ze_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        ze_ipc_memory_flags_t flags,                    ///< [in] flags controlling the operation.
                                                        ///< must be 0 (default) or a valid combination of ::ze_ipc_memory_flag_t.
        void** pptr                                     ///< [out] pointer to device allocation in this process
        )
    {
        context.logger->log_trace("zeMemOpenIpcHandle(hContext, hDevice, handle, flags, pptr)");

        auto pfnOpenIpcHandle = context.zeDdiTable.Mem.pfnOpenIpcHandle;

        if( nullptr == pfnOpenIpcHandle )
            return logAndPropagateResult("zeMemOpenIpcHandle", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemOpenIpcHandlePrologue( hContext, hDevice, handle, flags, pptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemOpenIpcHandle", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemOpenIpcHandlePrologue( hContext, hDevice, handle, flags, pptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemOpenIpcHandle", result);
        }

        auto driver_result = pfnOpenIpcHandle( hContext, hDevice, handle, flags, pptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemOpenIpcHandleEpilogue( hContext, hDevice, handle, flags, pptr ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemOpenIpcHandle", result);
        }

        return logAndPropagateResult("zeMemOpenIpcHandle", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemCloseIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeMemCloseIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        context.logger->log_trace("zeMemCloseIpcHandle(hContext, ptr)");

        auto pfnCloseIpcHandle = context.zeDdiTable.Mem.pfnCloseIpcHandle;

        if( nullptr == pfnCloseIpcHandle )
            return logAndPropagateResult("zeMemCloseIpcHandle", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemCloseIpcHandlePrologue( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemCloseIpcHandle", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemCloseIpcHandlePrologue( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemCloseIpcHandle", result);
        }

        auto driver_result = pfnCloseIpcHandle( hContext, ptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemCloseIpcHandleEpilogue( hContext, ptr ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemCloseIpcHandle", result);
        }

        return logAndPropagateResult("zeMemCloseIpcHandle", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemSetAtomicAccessAttributeExp
    __zedlllocal ze_result_t ZE_APICALL
    zeMemSetAtomicAccessAttributeExp(
        ze_context_handle_t hContext,                   ///< [in] handle of context
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_atomic_attr_exp_flags_t attr          ///< [in] Atomic access attributes to set for the specified range.
                                                        ///< Must be 0 (default) or a valid combination of ::ze_memory_atomic_attr_exp_flag_t.
        )
    {
        context.logger->log_trace("zeMemSetAtomicAccessAttributeExp(hContext, hDevice, ptr, size, attr)");

        auto pfnSetAtomicAccessAttributeExp = context.zeDdiTable.MemExp.pfnSetAtomicAccessAttributeExp;

        if( nullptr == pfnSetAtomicAccessAttributeExp )
            return logAndPropagateResult("zeMemSetAtomicAccessAttributeExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemSetAtomicAccessAttributeExpPrologue( hContext, hDevice, ptr, size, attr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemSetAtomicAccessAttributeExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemSetAtomicAccessAttributeExpPrologue( hContext, hDevice, ptr, size, attr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemSetAtomicAccessAttributeExp", result);
        }

        auto driver_result = pfnSetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, attr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemSetAtomicAccessAttributeExpEpilogue( hContext, hDevice, ptr, size, attr ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemSetAtomicAccessAttributeExp", result);
        }

        return logAndPropagateResult("zeMemSetAtomicAccessAttributeExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetAtomicAccessAttributeExp
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetAtomicAccessAttributeExp(
        ze_context_handle_t hContext,                   ///< [in] handle of context
        ze_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        ze_memory_atomic_attr_exp_flags_t* pAttr        ///< [out] Atomic access attributes for the specified range
        )
    {
        context.logger->log_trace("zeMemGetAtomicAccessAttributeExp(hContext, hDevice, ptr, size, pAttr)");

        auto pfnGetAtomicAccessAttributeExp = context.zeDdiTable.MemExp.pfnGetAtomicAccessAttributeExp;

        if( nullptr == pfnGetAtomicAccessAttributeExp )
            return logAndPropagateResult("zeMemGetAtomicAccessAttributeExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemGetAtomicAccessAttributeExpPrologue( hContext, hDevice, ptr, size, pAttr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetAtomicAccessAttributeExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetAtomicAccessAttributeExpPrologue( hContext, hDevice, ptr, size, pAttr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetAtomicAccessAttributeExp", result);
        }

        auto driver_result = pfnGetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, pAttr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemGetAtomicAccessAttributeExpEpilogue( hContext, hDevice, ptr, size, pAttr ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetAtomicAccessAttributeExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zeMemGetAtomicAccessAttributeExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_module_desc_t* desc,                   ///< [in] pointer to module descriptor
        ze_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
        ze_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
        )
    {
        context.logger->log_trace("zeModuleCreate(hContext, hDevice, desc, phModule, phBuildLog)");

        auto pfnCreate = context.zeDdiTable.Module.pfnCreate;

        if( nullptr == pfnCreate )
            return logAndPropagateResult("zeModuleCreate", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleCreatePrologue( hContext, hDevice, desc, phModule, phBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleCreate", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleCreatePrologue( hContext, hDevice, desc, phModule, phBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleCreate", result);
        }

        auto driver_result = pfnCreate( hContext, hDevice, desc, phModule, phBuildLog );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleCreateEpilogue( hContext, hDevice, desc, phModule, phBuildLog ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleCreate", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phModule){
                context.handleLifetime->addHandle( *phModule );
                context.handleLifetime->addDependent( hContext, *phModule );

            }
            if (phBuildLog){
                context.handleLifetime->addHandle( *phBuildLog );
                context.handleLifetime->addDependent( hContext, *phBuildLog );

            }
        }
        return logAndPropagateResult("zeModuleCreate", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleDestroy(
        ze_module_handle_t hModule                      ///< [in][release] handle of the module
        )
    {
        context.logger->log_trace("zeModuleDestroy(hModule)");

        auto pfnDestroy = context.zeDdiTable.Module.pfnDestroy;

        if( nullptr == pfnDestroy )
            return logAndPropagateResult("zeModuleDestroy", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleDestroyPrologue( hModule );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleDestroy", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleDestroyPrologue( hModule );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleDestroy", result);
        }

        auto driver_result = pfnDestroy( hModule );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleDestroyEpilogue( hModule ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleDestroy", result);
        }

        return logAndPropagateResult("zeModuleDestroy", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleDynamicLink
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleDynamicLink(
        uint32_t numModules,                            ///< [in] number of modules to be linked pointed to by phModules.
        ze_module_handle_t* phModules,                  ///< [in][range(0, numModules)] pointer to an array of modules to
                                                        ///< dynamically link together.
        ze_module_build_log_handle_t* phLinkLog         ///< [out][optional] pointer to handle of dynamic link log.
        )
    {
        context.logger->log_trace("zeModuleDynamicLink(numModules, phModulesLocal, phLinkLog)");

        auto pfnDynamicLink = context.zeDdiTable.Module.pfnDynamicLink;

        if( nullptr == pfnDynamicLink )
            return logAndPropagateResult("zeModuleDynamicLink", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleDynamicLinkPrologue( numModules, phModules, phLinkLog );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleDynamicLink", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleDynamicLinkPrologue( numModules, phModules, phLinkLog );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleDynamicLink", result);
        }

        auto driver_result = pfnDynamicLink( numModules, phModules, phLinkLog );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleDynamicLinkEpilogue( numModules, phModules, phLinkLog ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleDynamicLink", result);
        }

        return logAndPropagateResult("zeModuleDynamicLink", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleBuildLogDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleBuildLogDestroy(
        ze_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
        )
    {
        context.logger->log_trace("zeModuleBuildLogDestroy(hModuleBuildLog)");

        auto pfnDestroy = context.zeDdiTable.ModuleBuildLog.pfnDestroy;

        if( nullptr == pfnDestroy )
            return logAndPropagateResult("zeModuleBuildLogDestroy", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleBuildLogDestroyPrologue( hModuleBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleBuildLogDestroy", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleBuildLogDestroyPrologue( hModuleBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleBuildLogDestroy", result);
        }

        auto driver_result = pfnDestroy( hModuleBuildLog );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleBuildLogDestroyEpilogue( hModuleBuildLog ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleBuildLogDestroy", result);
        }

        return logAndPropagateResult("zeModuleBuildLogDestroy", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleBuildLogGetString
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleBuildLogGetString(
        ze_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    {
        context.logger->log_trace("zeModuleBuildLogGetString(hModuleBuildLog, pSize, pBuildLog)");

        auto pfnGetString = context.zeDdiTable.ModuleBuildLog.pfnGetString;

        if( nullptr == pfnGetString )
            return logAndPropagateResult("zeModuleBuildLogGetString", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleBuildLogGetStringPrologue( hModuleBuildLog, pSize, pBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleBuildLogGetString", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleBuildLogGetStringPrologue( hModuleBuildLog, pSize, pBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleBuildLogGetString", result);
        }

        auto driver_result = pfnGetString( hModuleBuildLog, pSize, pBuildLog );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleBuildLogGetStringEpilogue( hModuleBuildLog, pSize, pBuildLog ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleBuildLogGetString", result);
        }

        return logAndPropagateResult("zeModuleBuildLogGetString", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetNativeBinary
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetNativeBinary(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    {
        context.logger->log_trace("zeModuleGetNativeBinary(hModule, pSize, pModuleNativeBinary)");

        auto pfnGetNativeBinary = context.zeDdiTable.Module.pfnGetNativeBinary;

        if( nullptr == pfnGetNativeBinary )
            return logAndPropagateResult("zeModuleGetNativeBinary", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleGetNativeBinaryPrologue( hModule, pSize, pModuleNativeBinary );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleGetNativeBinary", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleGetNativeBinaryPrologue( hModule, pSize, pModuleNativeBinary );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleGetNativeBinary", result);
        }

        auto driver_result = pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleGetNativeBinaryEpilogue( hModule, pSize, pModuleNativeBinary ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleGetNativeBinary", result);
        }

        return logAndPropagateResult("zeModuleGetNativeBinary", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetGlobalPointer
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetGlobalPointer(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pGlobalName,                        ///< [in] name of global variable in module
        size_t* pSize,                                  ///< [in,out][optional] size of global variable
        void** pptr                                     ///< [in,out][optional] device visible pointer
        )
    {
        context.logger->log_trace("zeModuleGetGlobalPointer(hModule, pGlobalName, pSize, pptr)");

        auto pfnGetGlobalPointer = context.zeDdiTable.Module.pfnGetGlobalPointer;

        if( nullptr == pfnGetGlobalPointer )
            return logAndPropagateResult("zeModuleGetGlobalPointer", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleGetGlobalPointerPrologue( hModule, pGlobalName, pSize, pptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleGetGlobalPointer", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleGetGlobalPointerPrologue( hModule, pGlobalName, pSize, pptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleGetGlobalPointer", result);
        }

        auto driver_result = pfnGetGlobalPointer( hModule, pGlobalName, pSize, pptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleGetGlobalPointerEpilogue( hModule, pGlobalName, pSize, pptr ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleGetGlobalPointer", result);
        }

        return logAndPropagateResult("zeModuleGetGlobalPointer", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetKernelNames
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetKernelNames(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of names available.
                                                        ///< if count is greater than the number of names available, then the
                                                        ///< driver shall update the value with the correct number of names available.
        const char** pNames                             ///< [in,out][optional][range(0, *pCount)] array of names of functions.
                                                        ///< if count is less than the number of names available, then driver shall
                                                        ///< only retrieve that number of names.
        )
    {
        context.logger->log_trace("zeModuleGetKernelNames(hModule, pCount, pNames)");

        auto pfnGetKernelNames = context.zeDdiTable.Module.pfnGetKernelNames;

        if( nullptr == pfnGetKernelNames )
            return logAndPropagateResult("zeModuleGetKernelNames", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleGetKernelNamesPrologue( hModule, pCount, pNames );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleGetKernelNames", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleGetKernelNamesPrologue( hModule, pCount, pNames );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleGetKernelNames", result);
        }

        auto driver_result = pfnGetKernelNames( hModule, pCount, pNames );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleGetKernelNamesEpilogue( hModule, pCount, pNames ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleGetKernelNames", result);
        }

        return logAndPropagateResult("zeModuleGetKernelNames", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetProperties(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        ze_module_properties_t* pModuleProperties       ///< [in,out] query result for module properties.
        )
    {
        context.logger->log_trace("zeModuleGetProperties(hModule, pModuleProperties)");

        auto pfnGetProperties = context.zeDdiTable.Module.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zeModuleGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleGetPropertiesPrologue( hModule, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleGetPropertiesPrologue( hModule, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hModule, pModuleProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleGetPropertiesEpilogue( hModule, pModuleProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleGetProperties", result);
        }

        return logAndPropagateResult("zeModuleGetProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelCreate(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const ze_kernel_desc_t* desc,                   ///< [in] pointer to kernel descriptor
        ze_kernel_handle_t* phKernel                    ///< [out] handle of the Function object
        )
    {
        context.logger->log_trace("zeKernelCreate(hModule, desc, phKernel)");

        auto pfnCreate = context.zeDdiTable.Kernel.pfnCreate;

        if( nullptr == pfnCreate )
            return logAndPropagateResult("zeKernelCreate", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelCreatePrologue( hModule, desc, phKernel );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelCreate", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelCreatePrologue( hModule, desc, phKernel );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelCreate", result);
        }

        auto driver_result = pfnCreate( hModule, desc, phKernel );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelCreateEpilogue( hModule, desc, phKernel ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelCreate", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phKernel){
                context.handleLifetime->addHandle( *phKernel );
                context.handleLifetime->addDependent( hModule, *phKernel );

            }
        }
        return logAndPropagateResult("zeKernelCreate", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelDestroy(
        ze_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
        )
    {
        context.logger->log_trace("zeKernelDestroy(hKernel)");

        auto pfnDestroy = context.zeDdiTable.Kernel.pfnDestroy;

        if( nullptr == pfnDestroy )
            return logAndPropagateResult("zeKernelDestroy", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelDestroyPrologue( hKernel );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelDestroy", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelDestroyPrologue( hKernel );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelDestroy", result);
        }

        auto driver_result = pfnDestroy( hKernel );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelDestroyEpilogue( hKernel ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelDestroy", result);
        }

        return logAndPropagateResult("zeKernelDestroy", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetFunctionPointer
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetFunctionPointer(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
        void** pfnFunction                              ///< [out] pointer to function.
        )
    {
        context.logger->log_trace("zeModuleGetFunctionPointer(hModule, pFunctionName, pfnFunction)");

        auto pfnGetFunctionPointer = context.zeDdiTable.Module.pfnGetFunctionPointer;

        if( nullptr == pfnGetFunctionPointer )
            return logAndPropagateResult("zeModuleGetFunctionPointer", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleGetFunctionPointerPrologue( hModule, pFunctionName, pfnFunction );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleGetFunctionPointer", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleGetFunctionPointerPrologue( hModule, pFunctionName, pfnFunction );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleGetFunctionPointer", result);
        }

        auto driver_result = pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleGetFunctionPointerEpilogue( hModule, pFunctionName, pfnFunction ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleGetFunctionPointer", result);
        }

        return logAndPropagateResult("zeModuleGetFunctionPointer", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetGroupSize
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetGroupSize(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
        )
    {
        context.logger->log_trace("zeKernelSetGroupSize(hKernel, groupSizeX, groupSizeY, groupSizeZ)");

        auto pfnSetGroupSize = context.zeDdiTable.Kernel.pfnSetGroupSize;

        if( nullptr == pfnSetGroupSize )
            return logAndPropagateResult("zeKernelSetGroupSize", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSetGroupSizePrologue( hKernel, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSetGroupSize", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSetGroupSizePrologue( hKernel, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSetGroupSize", result);
        }

        auto driver_result = pfnSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSetGroupSizeEpilogue( hKernel, groupSizeX, groupSizeY, groupSizeZ ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSetGroupSize", result);
        }

        return logAndPropagateResult("zeKernelSetGroupSize", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSuggestGroupSize
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSuggestGroupSize(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t globalSizeX,                           ///< [in] global width for X dimension
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension
        uint32_t globalSizeZ,                           ///< [in] global width for Z dimension
        uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension
        uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension
        uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension
        )
    {
        context.logger->log_trace("zeKernelSuggestGroupSize(hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ)");

        auto pfnSuggestGroupSize = context.zeDdiTable.Kernel.pfnSuggestGroupSize;

        if( nullptr == pfnSuggestGroupSize )
            return logAndPropagateResult("zeKernelSuggestGroupSize", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSuggestGroupSizePrologue( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSuggestGroupSize", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSuggestGroupSizePrologue( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSuggestGroupSize", result);
        }

        auto driver_result = pfnSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSuggestGroupSizeEpilogue( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSuggestGroupSize", result);
        }

        return logAndPropagateResult("zeKernelSuggestGroupSize", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSuggestMaxCooperativeGroupCount
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSuggestMaxCooperativeGroupCount(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t* totalGroupCount                       ///< [out] recommended total group count.
        )
    {
        context.logger->log_trace("zeKernelSuggestMaxCooperativeGroupCount(hKernel, totalGroupCount)");

        auto pfnSuggestMaxCooperativeGroupCount = context.zeDdiTable.Kernel.pfnSuggestMaxCooperativeGroupCount;

        if( nullptr == pfnSuggestMaxCooperativeGroupCount )
            return logAndPropagateResult("zeKernelSuggestMaxCooperativeGroupCount", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSuggestMaxCooperativeGroupCountPrologue( hKernel, totalGroupCount );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSuggestMaxCooperativeGroupCount", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSuggestMaxCooperativeGroupCountPrologue( hKernel, totalGroupCount );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSuggestMaxCooperativeGroupCount", result);
        }

        auto driver_result = pfnSuggestMaxCooperativeGroupCount( hKernel, totalGroupCount );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSuggestMaxCooperativeGroupCountEpilogue( hKernel, totalGroupCount ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSuggestMaxCooperativeGroupCount", result);
        }

        return logAndPropagateResult("zeKernelSuggestMaxCooperativeGroupCount", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetArgumentValue
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetArgumentValue(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
        )
    {
        context.logger->log_trace("zeKernelSetArgumentValue(hKernel, argIndex, argSize, pArgValue)");

        auto pfnSetArgumentValue = context.zeDdiTable.Kernel.pfnSetArgumentValue;

        if( nullptr == pfnSetArgumentValue )
            return logAndPropagateResult("zeKernelSetArgumentValue", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSetArgumentValuePrologue( hKernel, argIndex, argSize, pArgValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSetArgumentValue", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSetArgumentValuePrologue( hKernel, argIndex, argSize, pArgValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSetArgumentValue", result);
        }

        auto driver_result = pfnSetArgumentValue( hKernel, argIndex, argSize, pArgValue );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSetArgumentValueEpilogue( hKernel, argIndex, argSize, pArgValue ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSetArgumentValue", result);
        }

        return logAndPropagateResult("zeKernelSetArgumentValue", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetIndirectAccess
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetIndirectAccess(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_indirect_access_flags_t flags         ///< [in] kernel indirect access flags
        )
    {
        context.logger->log_trace("zeKernelSetIndirectAccess(hKernel, flags)");

        auto pfnSetIndirectAccess = context.zeDdiTable.Kernel.pfnSetIndirectAccess;

        if( nullptr == pfnSetIndirectAccess )
            return logAndPropagateResult("zeKernelSetIndirectAccess", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSetIndirectAccessPrologue( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSetIndirectAccess", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSetIndirectAccessPrologue( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSetIndirectAccess", result);
        }

        auto driver_result = pfnSetIndirectAccess( hKernel, flags );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSetIndirectAccessEpilogue( hKernel, flags ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSetIndirectAccess", result);
        }

        return logAndPropagateResult("zeKernelSetIndirectAccess", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetIndirectAccess
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetIndirectAccess(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_indirect_access_flags_t* pFlags       ///< [out] query result for kernel indirect access flags.
        )
    {
        context.logger->log_trace("zeKernelGetIndirectAccess(hKernel, pFlags)");

        auto pfnGetIndirectAccess = context.zeDdiTable.Kernel.pfnGetIndirectAccess;

        if( nullptr == pfnGetIndirectAccess )
            return logAndPropagateResult("zeKernelGetIndirectAccess", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelGetIndirectAccessPrologue( hKernel, pFlags );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelGetIndirectAccess", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelGetIndirectAccessPrologue( hKernel, pFlags );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelGetIndirectAccess", result);
        }

        auto driver_result = pfnGetIndirectAccess( hKernel, pFlags );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelGetIndirectAccessEpilogue( hKernel, pFlags ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelGetIndirectAccess", result);
        }

        return logAndPropagateResult("zeKernelGetIndirectAccess", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetSourceAttributes
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetSourceAttributes(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t* pSize,                                ///< [in,out] pointer to size of string in bytes, including
                                                        ///< null-terminating character.
        char** pString                                  ///< [in,out][optional] pointer to application-managed character array
                                                        ///< (string data).
                                                        ///< If NULL, the string length of the kernel source attributes, including
                                                        ///< a null-terminating character, is returned in pSize. Otherwise, pString
                                                        ///< must point to valid application memory that is greater than or equal
                                                        ///< to *pSize bytes in length, and on return the pointed-to string will
                                                        ///< contain a space-separated list of kernel source attributes. Note: This
                                                        ///< API was originally intended to ship with a char *pString, however this
                                                        ///< typo was introduced. Thus the API has to stay this way for backwards
                                                        ///< compatible reasons. It can be corrected in v2.0. Suggestion is to
                                                        ///< create your own char *pString and then pass to this API with &pString.
        )
    {
        context.logger->log_trace("zeKernelGetSourceAttributes(hKernel, pSize, pString)");

        auto pfnGetSourceAttributes = context.zeDdiTable.Kernel.pfnGetSourceAttributes;

        if( nullptr == pfnGetSourceAttributes )
            return logAndPropagateResult("zeKernelGetSourceAttributes", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelGetSourceAttributesPrologue( hKernel, pSize, pString );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelGetSourceAttributes", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelGetSourceAttributesPrologue( hKernel, pSize, pString );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelGetSourceAttributes", result);
        }

        auto driver_result = pfnGetSourceAttributes( hKernel, pSize, pString );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelGetSourceAttributesEpilogue( hKernel, pSize, pString ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelGetSourceAttributes", result);
        }

        return logAndPropagateResult("zeKernelGetSourceAttributes", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetCacheConfig
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetCacheConfig(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_cache_config_flags_t flags                   ///< [in] cache configuration.
                                                        ///< must be 0 (default configuration) or a valid combination of ::ze_cache_config_flag_t.
        )
    {
        context.logger->log_trace("zeKernelSetCacheConfig(hKernel, flags)");

        auto pfnSetCacheConfig = context.zeDdiTable.Kernel.pfnSetCacheConfig;

        if( nullptr == pfnSetCacheConfig )
            return logAndPropagateResult("zeKernelSetCacheConfig", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSetCacheConfigPrologue( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSetCacheConfig", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSetCacheConfigPrologue( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSetCacheConfig", result);
        }

        auto driver_result = pfnSetCacheConfig( hKernel, flags );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSetCacheConfigEpilogue( hKernel, flags ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSetCacheConfig", result);
        }

        return logAndPropagateResult("zeKernelSetCacheConfig", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetProperties(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_properties_t* pKernelProperties       ///< [in,out] query result for kernel properties.
        )
    {
        context.logger->log_trace("zeKernelGetProperties(hKernel, pKernelProperties)");

        auto pfnGetProperties = context.zeDdiTable.Kernel.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult("zeKernelGetProperties", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelGetPropertiesPrologue( hKernel, pKernelProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelGetProperties", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelGetPropertiesPrologue( hKernel, pKernelProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelGetProperties", result);
        }

        auto driver_result = pfnGetProperties( hKernel, pKernelProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelGetPropertiesEpilogue( hKernel, pKernelProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelGetProperties", result);
        }

        return logAndPropagateResult("zeKernelGetProperties", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetName
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetName(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        size_t* pSize,                                  ///< [in,out] size of kernel name string, including null terminator, in
                                                        ///< bytes.
        char* pName                                     ///< [in,out][optional] char pointer to kernel name.
        )
    {
        context.logger->log_trace("zeKernelGetName(hKernel, pSize, pName)");

        auto pfnGetName = context.zeDdiTable.Kernel.pfnGetName;

        if( nullptr == pfnGetName )
            return logAndPropagateResult("zeKernelGetName", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelGetNamePrologue( hKernel, pSize, pName );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelGetName", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelGetNamePrologue( hKernel, pSize, pName );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelGetName", result);
        }

        auto driver_result = pfnGetName( hKernel, pSize, pName );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelGetNameEpilogue( hKernel, pSize, pName ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelGetName", result);
        }

        return logAndPropagateResult("zeKernelGetName", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchKernel
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendLaunchKernel(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendLaunchKernel(hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendLaunchKernel = context.zeDdiTable.CommandList.pfnAppendLaunchKernel;

        if( nullptr == pfnAppendLaunchKernel )
            return logAndPropagateResult("zeCommandListAppendLaunchKernel", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendLaunchKernelPrologue( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendLaunchKernel", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendLaunchKernelPrologue( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendLaunchKernel", result);
        }

        auto driver_result = pfnAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendLaunchKernelEpilogue( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendLaunchKernel", result);
        }

        return logAndPropagateResult("zeCommandListAppendLaunchKernel", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchCooperativeKernel
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendLaunchCooperativeKernel(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchFuncArgs,        ///< [in] thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendLaunchCooperativeKernel(hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendLaunchCooperativeKernel = context.zeDdiTable.CommandList.pfnAppendLaunchCooperativeKernel;

        if( nullptr == pfnAppendLaunchCooperativeKernel )
            return logAndPropagateResult("zeCommandListAppendLaunchCooperativeKernel", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendLaunchCooperativeKernelPrologue( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendLaunchCooperativeKernel", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendLaunchCooperativeKernelPrologue( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendLaunchCooperativeKernel", result);
        }

        auto driver_result = pfnAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendLaunchCooperativeKernelEpilogue( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendLaunchCooperativeKernel", result);
        }

        return logAndPropagateResult("zeCommandListAppendLaunchCooperativeKernel", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchKernelIndirect
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendLaunchKernelIndirect(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain thread group launch
                                                        ///< arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendLaunchKernelIndirect(hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendLaunchKernelIndirect = context.zeDdiTable.CommandList.pfnAppendLaunchKernelIndirect;

        if( nullptr == pfnAppendLaunchKernelIndirect )
            return logAndPropagateResult("zeCommandListAppendLaunchKernelIndirect", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendLaunchKernelIndirectPrologue( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendLaunchKernelIndirect", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendLaunchKernelIndirectPrologue( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendLaunchKernelIndirect", result);
        }

        auto driver_result = pfnAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendLaunchKernelIndirectEpilogue( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendLaunchKernelIndirect", result);
        }

        return logAndPropagateResult("zeCommandListAppendLaunchKernelIndirect", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendLaunchMultipleKernelsIndirect
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendLaunchMultipleKernelsIndirect(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
        ze_kernel_handle_t* phKernels,                  ///< [in][range(0, numKernels)] handles of the kernel objects
        const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of kernels to launch; value must be less than or equal to
                                                        ///< numKernels
        const ze_group_count_t* pLaunchArgumentsBuffer, ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                        ///< a contiguous array of thread group launch arguments
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendLaunchMultipleKernelsIndirect(hCommandList, numKernels, phKernelsLocal, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendLaunchMultipleKernelsIndirect = context.zeDdiTable.CommandList.pfnAppendLaunchMultipleKernelsIndirect;

        if( nullptr == pfnAppendLaunchMultipleKernelsIndirect )
            return logAndPropagateResult("zeCommandListAppendLaunchMultipleKernelsIndirect", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendLaunchMultipleKernelsIndirectPrologue( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendLaunchMultipleKernelsIndirect", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendLaunchMultipleKernelsIndirectPrologue( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendLaunchMultipleKernelsIndirect", result);
        }

        auto driver_result = pfnAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendLaunchMultipleKernelsIndirectEpilogue( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendLaunchMultipleKernelsIndirect", result);
        }

        return logAndPropagateResult("zeCommandListAppendLaunchMultipleKernelsIndirect", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextMakeMemoryResident
    __zedlllocal ze_result_t ZE_APICALL
    zeContextMakeMemoryResident(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        )
    {
        context.logger->log_trace("zeContextMakeMemoryResident(hContext, hDevice, ptr, size)");

        auto pfnMakeMemoryResident = context.zeDdiTable.Context.pfnMakeMemoryResident;

        if( nullptr == pfnMakeMemoryResident )
            return logAndPropagateResult("zeContextMakeMemoryResident", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextMakeMemoryResidentPrologue( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextMakeMemoryResident", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextMakeMemoryResidentPrologue( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextMakeMemoryResident", result);
        }

        auto driver_result = pfnMakeMemoryResident( hContext, hDevice, ptr, size );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextMakeMemoryResidentEpilogue( hContext, hDevice, ptr, size ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextMakeMemoryResident", result);
        }

        return logAndPropagateResult("zeContextMakeMemoryResident", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextEvictMemory
    __zedlllocal ze_result_t ZE_APICALL
    zeContextEvictMemory(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        )
    {
        context.logger->log_trace("zeContextEvictMemory(hContext, hDevice, ptr, size)");

        auto pfnEvictMemory = context.zeDdiTable.Context.pfnEvictMemory;

        if( nullptr == pfnEvictMemory )
            return logAndPropagateResult("zeContextEvictMemory", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextEvictMemoryPrologue( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextEvictMemory", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextEvictMemoryPrologue( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextEvictMemory", result);
        }

        auto driver_result = pfnEvictMemory( hContext, hDevice, ptr, size );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextEvictMemoryEpilogue( hContext, hDevice, ptr, size ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextEvictMemory", result);
        }

        return logAndPropagateResult("zeContextEvictMemory", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextMakeImageResident
    __zedlllocal ze_result_t ZE_APICALL
    zeContextMakeImageResident(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make resident
        )
    {
        context.logger->log_trace("zeContextMakeImageResident(hContext, hDevice, hImage)");

        auto pfnMakeImageResident = context.zeDdiTable.Context.pfnMakeImageResident;

        if( nullptr == pfnMakeImageResident )
            return logAndPropagateResult("zeContextMakeImageResident", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextMakeImageResidentPrologue( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextMakeImageResident", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextMakeImageResidentPrologue( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextMakeImageResident", result);
        }

        auto driver_result = pfnMakeImageResident( hContext, hDevice, hImage );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextMakeImageResidentEpilogue( hContext, hDevice, hImage ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextMakeImageResident", result);
        }

        return logAndPropagateResult("zeContextMakeImageResident", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextEvictImage
    __zedlllocal ze_result_t ZE_APICALL
    zeContextEvictImage(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_image_handle_t hImage                        ///< [in] handle of image to make evict
        )
    {
        context.logger->log_trace("zeContextEvictImage(hContext, hDevice, hImage)");

        auto pfnEvictImage = context.zeDdiTable.Context.pfnEvictImage;

        if( nullptr == pfnEvictImage )
            return logAndPropagateResult("zeContextEvictImage", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextEvictImagePrologue( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextEvictImage", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextEvictImagePrologue( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextEvictImage", result);
        }

        auto driver_result = pfnEvictImage( hContext, hDevice, hImage );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeContextEvictImageEpilogue( hContext, hDevice, hImage ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeContextEvictImage", result);
        }

        return logAndPropagateResult("zeContextEvictImage", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeSamplerCreate
    __zedlllocal ze_result_t ZE_APICALL
    zeSamplerCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_sampler_desc_t* desc,                  ///< [in] pointer to sampler descriptor
        ze_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
        )
    {
        context.logger->log_trace("zeSamplerCreate(hContext, hDevice, desc, phSampler)");

        auto pfnCreate = context.zeDdiTable.Sampler.pfnCreate;

        if( nullptr == pfnCreate )
            return logAndPropagateResult("zeSamplerCreate", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeSamplerCreatePrologue( hContext, hDevice, desc, phSampler );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeSamplerCreate", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeSamplerCreatePrologue( hContext, hDevice, desc, phSampler );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeSamplerCreate", result);
        }

        auto driver_result = pfnCreate( hContext, hDevice, desc, phSampler );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeSamplerCreateEpilogue( hContext, hDevice, desc, phSampler ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeSamplerCreate", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phSampler){
                context.handleLifetime->addHandle( *phSampler );
                context.handleLifetime->addDependent( hContext, *phSampler );

            }
        }
        return logAndPropagateResult("zeSamplerCreate", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeSamplerDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeSamplerDestroy(
        ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
        )
    {
        context.logger->log_trace("zeSamplerDestroy(hSampler)");

        auto pfnDestroy = context.zeDdiTable.Sampler.pfnDestroy;

        if( nullptr == pfnDestroy )
            return logAndPropagateResult("zeSamplerDestroy", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeSamplerDestroyPrologue( hSampler );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeSamplerDestroy", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeSamplerDestroyPrologue( hSampler );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeSamplerDestroy", result);
        }

        auto driver_result = pfnDestroy( hSampler );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeSamplerDestroyEpilogue( hSampler ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeSamplerDestroy", result);
        }

        return logAndPropagateResult("zeSamplerDestroy", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemReserve
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemReserve(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* pStart,                             ///< [in][optional] pointer to start of region to reserve. If nullptr then
                                                        ///< implementation will choose a start address.
        size_t size,                                    ///< [in] size in bytes to reserve; must be page aligned.
        void** pptr                                     ///< [out] pointer to virtual reservation.
        )
    {
        context.logger->log_trace("zeVirtualMemReserve(hContext, pStart, size, pptr)");

        auto pfnReserve = context.zeDdiTable.VirtualMem.pfnReserve;

        if( nullptr == pfnReserve )
            return logAndPropagateResult("zeVirtualMemReserve", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeVirtualMemReservePrologue( hContext, pStart, size, pptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemReserve", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemReservePrologue( hContext, pStart, size, pptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemReserve", result);
        }

        auto driver_result = pfnReserve( hContext, pStart, size, pptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeVirtualMemReserveEpilogue( hContext, pStart, size, pptr ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemReserve", result);
        }

        return logAndPropagateResult("zeVirtualMemReserve", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemFree
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemFree(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of region to free.
        size_t size                                     ///< [in] size in bytes to free; must be page aligned.
        )
    {
        context.logger->log_trace("zeVirtualMemFree(hContext, ptr, size)");

        auto pfnFree = context.zeDdiTable.VirtualMem.pfnFree;

        if( nullptr == pfnFree )
            return logAndPropagateResult("zeVirtualMemFree", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeVirtualMemFreePrologue( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemFree", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemFreePrologue( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemFree", result);
        }

        auto driver_result = pfnFree( hContext, ptr, size );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeVirtualMemFreeEpilogue( hContext, ptr, size ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemFree", result);
        }

        return logAndPropagateResult("zeVirtualMemFree", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemQueryPageSize
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemQueryPageSize(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        size_t size,                                    ///< [in] unaligned allocation size in bytes
        size_t* pagesize                                ///< [out] pointer to page size to use for start address and size
                                                        ///< alignments.
        )
    {
        context.logger->log_trace("zeVirtualMemQueryPageSize(hContext, hDevice, size, pagesize)");

        auto pfnQueryPageSize = context.zeDdiTable.VirtualMem.pfnQueryPageSize;

        if( nullptr == pfnQueryPageSize )
            return logAndPropagateResult("zeVirtualMemQueryPageSize", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeVirtualMemQueryPageSizePrologue( hContext, hDevice, size, pagesize );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemQueryPageSize", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemQueryPageSizePrologue( hContext, hDevice, size, pagesize );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemQueryPageSize", result);
        }

        auto driver_result = pfnQueryPageSize( hContext, hDevice, size, pagesize );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeVirtualMemQueryPageSizeEpilogue( hContext, hDevice, size, pagesize ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemQueryPageSize", result);
        }

        return logAndPropagateResult("zeVirtualMemQueryPageSize", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zePhysicalMemCreate
    __zedlllocal ze_result_t ZE_APICALL
    zePhysicalMemCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object, can be `nullptr` if creating
                                                        ///< physical host memory.
        ze_physical_mem_desc_t* desc,                   ///< [in] pointer to physical memory descriptor.
        ze_physical_mem_handle_t* phPhysicalMemory      ///< [out] pointer to handle of physical memory object created
        )
    {
        context.logger->log_trace("zePhysicalMemCreate(hContext, hDevice, desc, phPhysicalMemory)");

        auto pfnCreate = context.zeDdiTable.PhysicalMem.pfnCreate;

        if( nullptr == pfnCreate )
            return logAndPropagateResult("zePhysicalMemCreate", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zePhysicalMemCreatePrologue( hContext, hDevice, desc, phPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zePhysicalMemCreate", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zePhysicalMemCreatePrologue( hContext, hDevice, desc, phPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zePhysicalMemCreate", result);
        }

        auto driver_result = pfnCreate( hContext, hDevice, desc, phPhysicalMemory );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zePhysicalMemCreateEpilogue( hContext, hDevice, desc, phPhysicalMemory ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zePhysicalMemCreate", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phPhysicalMemory){
                context.handleLifetime->addHandle( *phPhysicalMemory );
                context.handleLifetime->addDependent( hContext, *phPhysicalMemory );

            }
        }
        return logAndPropagateResult("zePhysicalMemCreate", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zePhysicalMemDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zePhysicalMemDestroy(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_physical_mem_handle_t hPhysicalMemory        ///< [in][release] handle of physical memory object to destroy
        )
    {
        context.logger->log_trace("zePhysicalMemDestroy(hContext, hPhysicalMemory)");

        auto pfnDestroy = context.zeDdiTable.PhysicalMem.pfnDestroy;

        if( nullptr == pfnDestroy )
            return logAndPropagateResult("zePhysicalMemDestroy", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zePhysicalMemDestroyPrologue( hContext, hPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zePhysicalMemDestroy", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zePhysicalMemDestroyPrologue( hContext, hPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zePhysicalMemDestroy", result);
        }

        auto driver_result = pfnDestroy( hContext, hPhysicalMemory );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zePhysicalMemDestroyEpilogue( hContext, hPhysicalMemory ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zePhysicalMemDestroy", result);
        }

        return logAndPropagateResult("zePhysicalMemDestroy", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemMap
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemMap(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of virtual address range to map.
        size_t size,                                    ///< [in] size in bytes of virtual address range to map; must be page
                                                        ///< aligned.
        ze_physical_mem_handle_t hPhysicalMemory,       ///< [in] handle to physical memory object.
        size_t offset,                                  ///< [in] offset into physical memory allocation object; must be page
                                                        ///< aligned.
        ze_memory_access_attribute_t access             ///< [in] specifies page access attributes to apply to the virtual address
                                                        ///< range.
        )
    {
        context.logger->log_trace("zeVirtualMemMap(hContext, ptr, size, hPhysicalMemory, offset, access)");

        auto pfnMap = context.zeDdiTable.VirtualMem.pfnMap;

        if( nullptr == pfnMap )
            return logAndPropagateResult("zeVirtualMemMap", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeVirtualMemMapPrologue( hContext, ptr, size, hPhysicalMemory, offset, access );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemMap", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemMapPrologue( hContext, ptr, size, hPhysicalMemory, offset, access );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemMap", result);
        }

        auto driver_result = pfnMap( hContext, ptr, size, hPhysicalMemory, offset, access );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeVirtualMemMapEpilogue( hContext, ptr, size, hPhysicalMemory, offset, access ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemMap", result);
        }

        return logAndPropagateResult("zeVirtualMemMap", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemUnmap
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemUnmap(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of region to unmap.
        size_t size                                     ///< [in] size in bytes to unmap; must be page aligned.
        )
    {
        context.logger->log_trace("zeVirtualMemUnmap(hContext, ptr, size)");

        auto pfnUnmap = context.zeDdiTable.VirtualMem.pfnUnmap;

        if( nullptr == pfnUnmap )
            return logAndPropagateResult("zeVirtualMemUnmap", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeVirtualMemUnmapPrologue( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemUnmap", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemUnmapPrologue( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemUnmap", result);
        }

        auto driver_result = pfnUnmap( hContext, ptr, size );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeVirtualMemUnmapEpilogue( hContext, ptr, size ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemUnmap", result);
        }

        return logAndPropagateResult("zeVirtualMemUnmap", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemSetAccessAttribute
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemSetAccessAttribute(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of reserved virtual address region.
        size_t size,                                    ///< [in] size in bytes; must be page aligned.
        ze_memory_access_attribute_t access             ///< [in] specifies page access attributes to apply to the virtual address
                                                        ///< range.
        )
    {
        context.logger->log_trace("zeVirtualMemSetAccessAttribute(hContext, ptr, size, access)");

        auto pfnSetAccessAttribute = context.zeDdiTable.VirtualMem.pfnSetAccessAttribute;

        if( nullptr == pfnSetAccessAttribute )
            return logAndPropagateResult("zeVirtualMemSetAccessAttribute", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeVirtualMemSetAccessAttributePrologue( hContext, ptr, size, access );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemSetAccessAttribute", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemSetAccessAttributePrologue( hContext, ptr, size, access );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemSetAccessAttribute", result);
        }

        auto driver_result = pfnSetAccessAttribute( hContext, ptr, size, access );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeVirtualMemSetAccessAttributeEpilogue( hContext, ptr, size, access ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemSetAccessAttribute", result);
        }

        return logAndPropagateResult("zeVirtualMemSetAccessAttribute", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeVirtualMemGetAccessAttribute
    __zedlllocal ze_result_t ZE_APICALL
    zeVirtualMemGetAccessAttribute(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr,                                ///< [in] pointer to start of virtual address region for query.
        size_t size,                                    ///< [in] size in bytes; must be page aligned.
        ze_memory_access_attribute_t* access,           ///< [out] query result for page access attribute.
        size_t* outSize                                 ///< [out] query result for size of virtual address range, starting at ptr,
                                                        ///< that shares same access attribute.
        )
    {
        context.logger->log_trace("zeVirtualMemGetAccessAttribute(hContext, ptr, size, access, outSize)");

        auto pfnGetAccessAttribute = context.zeDdiTable.VirtualMem.pfnGetAccessAttribute;

        if( nullptr == pfnGetAccessAttribute )
            return logAndPropagateResult("zeVirtualMemGetAccessAttribute", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeVirtualMemGetAccessAttributePrologue( hContext, ptr, size, access, outSize );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemGetAccessAttribute", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemGetAccessAttributePrologue( hContext, ptr, size, access, outSize );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemGetAccessAttribute", result);
        }

        auto driver_result = pfnGetAccessAttribute( hContext, ptr, size, access, outSize );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeVirtualMemGetAccessAttributeEpilogue( hContext, ptr, size, access, outSize ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeVirtualMemGetAccessAttribute", result);
        }

        return logAndPropagateResult("zeVirtualMemGetAccessAttribute", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetGlobalOffsetExp
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetGlobalOffsetExp(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t offsetX,                               ///< [in] global offset for X dimension to use for this kernel
        uint32_t offsetY,                               ///< [in] global offset for Y dimension to use for this kernel
        uint32_t offsetZ                                ///< [in] global offset for Z dimension to use for this kernel
        )
    {
        context.logger->log_trace("zeKernelSetGlobalOffsetExp(hKernel, offsetX, offsetY, offsetZ)");

        auto pfnSetGlobalOffsetExp = context.zeDdiTable.KernelExp.pfnSetGlobalOffsetExp;

        if( nullptr == pfnSetGlobalOffsetExp )
            return logAndPropagateResult("zeKernelSetGlobalOffsetExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSetGlobalOffsetExpPrologue( hKernel, offsetX, offsetY, offsetZ );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSetGlobalOffsetExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSetGlobalOffsetExpPrologue( hKernel, offsetX, offsetY, offsetZ );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSetGlobalOffsetExp", result);
        }

        auto driver_result = pfnSetGlobalOffsetExp( hKernel, offsetX, offsetY, offsetZ );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSetGlobalOffsetExpEpilogue( hKernel, offsetX, offsetY, offsetZ ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSetGlobalOffsetExp", result);
        }

        return logAndPropagateResult("zeKernelSetGlobalOffsetExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetBinaryExp
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetBinaryExp(
        ze_kernel_handle_t hKernel,                     ///< [in] Kernel handle.
        size_t* pSize,                                  ///< [in,out] pointer to variable with size of GEN ISA binary.
        uint8_t* pKernelBinary                          ///< [in,out] pointer to storage area for GEN ISA binary function.
        )
    {
        context.logger->log_trace("zeKernelGetBinaryExp(hKernel, pSize, pKernelBinary)");

        auto pfnGetBinaryExp = context.zeDdiTable.KernelExp.pfnGetBinaryExp;

        if( nullptr == pfnGetBinaryExp )
            return logAndPropagateResult("zeKernelGetBinaryExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelGetBinaryExpPrologue( hKernel, pSize, pKernelBinary );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelGetBinaryExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelGetBinaryExpPrologue( hKernel, pSize, pKernelBinary );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelGetBinaryExp", result);
        }

        auto driver_result = pfnGetBinaryExp( hKernel, pSize, pKernelBinary );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelGetBinaryExpEpilogue( hKernel, pSize, pKernelBinary ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelGetBinaryExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zeKernelGetBinaryExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceImportExternalSemaphoreExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceImportExternalSemaphoreExt(
        ze_device_handle_t hDevice,                     ///< [in] The device handle.
        const ze_external_semaphore_ext_desc_t* desc,   ///< [in] The pointer to external semaphore descriptor.
        ze_external_semaphore_ext_handle_t* phSemaphore ///< [out] The handle of the external semaphore imported.
        )
    {
        context.logger->log_trace("zeDeviceImportExternalSemaphoreExt(hDevice, desc, phSemaphore)");

        auto pfnImportExternalSemaphoreExt = context.zeDdiTable.Device.pfnImportExternalSemaphoreExt;

        if( nullptr == pfnImportExternalSemaphoreExt )
            return logAndPropagateResult("zeDeviceImportExternalSemaphoreExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceImportExternalSemaphoreExtPrologue( hDevice, desc, phSemaphore );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceImportExternalSemaphoreExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceImportExternalSemaphoreExtPrologue( hDevice, desc, phSemaphore );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceImportExternalSemaphoreExt", result);
        }

        auto driver_result = pfnImportExternalSemaphoreExt( hDevice, desc, phSemaphore );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceImportExternalSemaphoreExtEpilogue( hDevice, desc, phSemaphore ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceImportExternalSemaphoreExt", result);
        }

        return logAndPropagateResult("zeDeviceImportExternalSemaphoreExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceReleaseExternalSemaphoreExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceReleaseExternalSemaphoreExt(
        ze_external_semaphore_ext_handle_t hSemaphore   ///< [in] The handle of the external semaphore.
        )
    {
        context.logger->log_trace("zeDeviceReleaseExternalSemaphoreExt(hSemaphore)");

        auto pfnReleaseExternalSemaphoreExt = context.zeDdiTable.Device.pfnReleaseExternalSemaphoreExt;

        if( nullptr == pfnReleaseExternalSemaphoreExt )
            return logAndPropagateResult("zeDeviceReleaseExternalSemaphoreExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceReleaseExternalSemaphoreExtPrologue( hSemaphore );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceReleaseExternalSemaphoreExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceReleaseExternalSemaphoreExtPrologue( hSemaphore );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceReleaseExternalSemaphoreExt", result);
        }

        auto driver_result = pfnReleaseExternalSemaphoreExt( hSemaphore );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceReleaseExternalSemaphoreExtEpilogue( hSemaphore ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceReleaseExternalSemaphoreExt", result);
        }

        return logAndPropagateResult("zeDeviceReleaseExternalSemaphoreExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendSignalExternalSemaphoreExt
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendSignalExternalSemaphoreExt(
        ze_command_list_handle_t hCommandList,          ///< [in] The command list handle.
        uint32_t numSemaphores,                         ///< [in] The number of external semaphores.
        ze_external_semaphore_ext_handle_t* phSemaphores,   ///< [in][range(0, numSemaphores)] The vector of external semaphore handles
                                                        ///< to be appended into command list.
        ze_external_semaphore_signal_params_ext_t* signalParams,///< [in] Signal parameters.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendSignalExternalSemaphoreExt(hCommandList, numSemaphores, phSemaphoresLocal, signalParams, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendSignalExternalSemaphoreExt = context.zeDdiTable.CommandList.pfnAppendSignalExternalSemaphoreExt;

        if( nullptr == pfnAppendSignalExternalSemaphoreExt )
            return logAndPropagateResult("zeCommandListAppendSignalExternalSemaphoreExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendSignalExternalSemaphoreExtPrologue( hCommandList, numSemaphores, phSemaphores, signalParams, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendSignalExternalSemaphoreExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendSignalExternalSemaphoreExtPrologue( hCommandList, numSemaphores, phSemaphores, signalParams, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendSignalExternalSemaphoreExt", result);
        }

        auto driver_result = pfnAppendSignalExternalSemaphoreExt( hCommandList, numSemaphores, phSemaphores, signalParams, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendSignalExternalSemaphoreExtEpilogue( hCommandList, numSemaphores, phSemaphores, signalParams, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendSignalExternalSemaphoreExt", result);
        }

        return logAndPropagateResult("zeCommandListAppendSignalExternalSemaphoreExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendWaitExternalSemaphoreExt
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendWaitExternalSemaphoreExt(
        ze_command_list_handle_t hCommandList,          ///< [in] The command list handle.
        uint32_t numSemaphores,                         ///< [in] The number of external semaphores.
        ze_external_semaphore_ext_handle_t* phSemaphores,   ///< [in] [range(0,numSemaphores)] The vector of external semaphore handles
                                                        ///< to append into command list.
        ze_external_semaphore_wait_params_ext_t* waitParams,///< [in] Wait parameters.
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendWaitExternalSemaphoreExt(hCommandList, numSemaphores, phSemaphoresLocal, waitParams, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendWaitExternalSemaphoreExt = context.zeDdiTable.CommandList.pfnAppendWaitExternalSemaphoreExt;

        if( nullptr == pfnAppendWaitExternalSemaphoreExt )
            return logAndPropagateResult("zeCommandListAppendWaitExternalSemaphoreExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendWaitExternalSemaphoreExtPrologue( hCommandList, numSemaphores, phSemaphores, waitParams, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendWaitExternalSemaphoreExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendWaitExternalSemaphoreExtPrologue( hCommandList, numSemaphores, phSemaphores, waitParams, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendWaitExternalSemaphoreExt", result);
        }

        auto driver_result = pfnAppendWaitExternalSemaphoreExt( hCommandList, numSemaphores, phSemaphores, waitParams, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendWaitExternalSemaphoreExtEpilogue( hCommandList, numSemaphores, phSemaphores, waitParams, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendWaitExternalSemaphoreExt", result);
        }

        return logAndPropagateResult("zeCommandListAppendWaitExternalSemaphoreExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderCreateExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderCreateExt(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        const ze_rtas_builder_ext_desc_t* pDescriptor,  ///< [in] pointer to builder descriptor
        ze_rtas_builder_ext_handle_t* phBuilder         ///< [out] handle of builder object
        )
    {
        context.logger->log_trace("zeRTASBuilderCreateExt(hDriver, pDescriptor, phBuilder)");

        auto pfnCreateExt = context.zeDdiTable.RTASBuilder.pfnCreateExt;

        if( nullptr == pfnCreateExt )
            return logAndPropagateResult("zeRTASBuilderCreateExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderCreateExtPrologue( hDriver, pDescriptor, phBuilder );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderCreateExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderCreateExtPrologue( hDriver, pDescriptor, phBuilder );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderCreateExt", result);
        }

        auto driver_result = pfnCreateExt( hDriver, pDescriptor, phBuilder );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderCreateExtEpilogue( hDriver, pDescriptor, phBuilder ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderCreateExt", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phBuilder){
                context.handleLifetime->addHandle( *phBuilder );
                context.handleLifetime->addDependent( hDriver, *phBuilder );

            }
        }
        return logAndPropagateResult("zeRTASBuilderCreateExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderGetBuildPropertiesExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderGetBuildPropertiesExt(
        ze_rtas_builder_ext_handle_t hBuilder,          ///< [in] handle of builder object
        const ze_rtas_builder_build_op_ext_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
        ze_rtas_builder_ext_properties_t* pProperties   ///< [in,out] query result for builder properties
        )
    {
        context.logger->log_trace("zeRTASBuilderGetBuildPropertiesExt(hBuilder, pBuildOpDescriptor, pProperties)");

        auto pfnGetBuildPropertiesExt = context.zeDdiTable.RTASBuilder.pfnGetBuildPropertiesExt;

        if( nullptr == pfnGetBuildPropertiesExt )
            return logAndPropagateResult("zeRTASBuilderGetBuildPropertiesExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderGetBuildPropertiesExtPrologue( hBuilder, pBuildOpDescriptor, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderGetBuildPropertiesExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderGetBuildPropertiesExtPrologue( hBuilder, pBuildOpDescriptor, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderGetBuildPropertiesExt", result);
        }

        auto driver_result = pfnGetBuildPropertiesExt( hBuilder, pBuildOpDescriptor, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderGetBuildPropertiesExtEpilogue( hBuilder, pBuildOpDescriptor, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderGetBuildPropertiesExt", result);
        }

        return logAndPropagateResult("zeRTASBuilderGetBuildPropertiesExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverRTASFormatCompatibilityCheckExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverRTASFormatCompatibilityCheckExt(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_format_ext_t rtasFormatA,               ///< [in] operand A
        ze_rtas_format_ext_t rtasFormatB                ///< [in] operand B
        )
    {
        context.logger->log_trace("zeDriverRTASFormatCompatibilityCheckExt(hDriver, rtasFormatA, rtasFormatB)");

        auto pfnRTASFormatCompatibilityCheckExt = context.zeDdiTable.Driver.pfnRTASFormatCompatibilityCheckExt;

        if( nullptr == pfnRTASFormatCompatibilityCheckExt )
            return logAndPropagateResult("zeDriverRTASFormatCompatibilityCheckExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverRTASFormatCompatibilityCheckExtPrologue( hDriver, rtasFormatA, rtasFormatB );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverRTASFormatCompatibilityCheckExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverRTASFormatCompatibilityCheckExtPrologue( hDriver, rtasFormatA, rtasFormatB );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverRTASFormatCompatibilityCheckExt", result);
        }

        auto driver_result = pfnRTASFormatCompatibilityCheckExt( hDriver, rtasFormatA, rtasFormatB );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverRTASFormatCompatibilityCheckExtEpilogue( hDriver, rtasFormatA, rtasFormatB ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverRTASFormatCompatibilityCheckExt", result);
        }

        return logAndPropagateResult("zeDriverRTASFormatCompatibilityCheckExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderBuildExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderBuildExt(
        ze_rtas_builder_ext_handle_t hBuilder,          ///< [in] handle of builder object
        const ze_rtas_builder_build_op_ext_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
        void* pScratchBuffer,                           ///< [in][range(0, `scratchBufferSizeBytes`)] scratch buffer to be used
                                                        ///< during acceleration structure construction
        size_t scratchBufferSizeBytes,                  ///< [in] size of scratch buffer, in bytes
        void* pRtasBuffer,                              ///< [in] pointer to destination buffer
        size_t rtasBufferSizeBytes,                     ///< [in] destination buffer size, in bytes
        ze_rtas_parallel_operation_ext_handle_t hParallelOperation, ///< [in][optional] handle to parallel operation object
        void* pBuildUserPtr,                            ///< [in][optional] pointer passed to callbacks
        ze_rtas_aabb_ext_t* pBounds,                    ///< [in,out][optional] pointer to destination address for acceleration
                                                        ///< structure bounds
        size_t* pRtasBufferSizeBytes                    ///< [out][optional] updated acceleration structure size requirement, in
                                                        ///< bytes
        )
    {
        context.logger->log_trace("zeRTASBuilderBuildExt(hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes)");

        auto pfnBuildExt = context.zeDdiTable.RTASBuilder.pfnBuildExt;

        if( nullptr == pfnBuildExt )
            return logAndPropagateResult("zeRTASBuilderBuildExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderBuildExtPrologue( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderBuildExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderBuildExtPrologue( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderBuildExt", result);
        }

        auto driver_result = pfnBuildExt( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderBuildExtEpilogue( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderBuildExt", result);
        }

        return logAndPropagateResult("zeRTASBuilderBuildExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderCommandListAppendCopyExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderCommandListAppendCopyExt(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination in device memory to copy the ray tracing
                                                        ///< acceleration structure to
        const void* srcptr,                             ///< [in] pointer to a valid source ray tracing acceleration structure in
                                                        ///< host memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeRTASBuilderCommandListAppendCopyExt(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnCommandListAppendCopyExt = context.zeDdiTable.RTASBuilder.pfnCommandListAppendCopyExt;

        if( nullptr == pfnCommandListAppendCopyExt )
            return logAndPropagateResult("zeRTASBuilderCommandListAppendCopyExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderCommandListAppendCopyExtPrologue( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderCommandListAppendCopyExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderCommandListAppendCopyExtPrologue( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderCommandListAppendCopyExt", result);
        }

        auto driver_result = pfnCommandListAppendCopyExt( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderCommandListAppendCopyExtEpilogue( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderCommandListAppendCopyExt", result);
        }

        return logAndPropagateResult("zeRTASBuilderCommandListAppendCopyExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderDestroyExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderDestroyExt(
        ze_rtas_builder_ext_handle_t hBuilder           ///< [in][release] handle of builder object to destroy
        )
    {
        context.logger->log_trace("zeRTASBuilderDestroyExt(hBuilder)");

        auto pfnDestroyExt = context.zeDdiTable.RTASBuilder.pfnDestroyExt;

        if( nullptr == pfnDestroyExt )
            return logAndPropagateResult("zeRTASBuilderDestroyExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderDestroyExtPrologue( hBuilder );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderDestroyExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderDestroyExtPrologue( hBuilder );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderDestroyExt", result);
        }

        auto driver_result = pfnDestroyExt( hBuilder );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderDestroyExtEpilogue( hBuilder ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderDestroyExt", result);
        }

        return logAndPropagateResult("zeRTASBuilderDestroyExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationCreateExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationCreateExt(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_parallel_operation_ext_handle_t* phParallelOperation///< [out] handle of parallel operation object
        )
    {
        context.logger->log_trace("zeRTASParallelOperationCreateExt(hDriver, phParallelOperation)");

        auto pfnCreateExt = context.zeDdiTable.RTASParallelOperation.pfnCreateExt;

        if( nullptr == pfnCreateExt )
            return logAndPropagateResult("zeRTASParallelOperationCreateExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationCreateExtPrologue( hDriver, phParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationCreateExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationCreateExtPrologue( hDriver, phParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationCreateExt", result);
        }

        auto driver_result = pfnCreateExt( hDriver, phParallelOperation );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationCreateExtEpilogue( hDriver, phParallelOperation ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationCreateExt", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phParallelOperation){
                context.handleLifetime->addHandle( *phParallelOperation );
                context.handleLifetime->addDependent( hDriver, *phParallelOperation );

            }
        }
        return logAndPropagateResult("zeRTASParallelOperationCreateExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationGetPropertiesExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationGetPropertiesExt(
        ze_rtas_parallel_operation_ext_handle_t hParallelOperation, ///< [in] handle of parallel operation object
        ze_rtas_parallel_operation_ext_properties_t* pProperties///< [in,out] query result for parallel operation properties
        )
    {
        context.logger->log_trace("zeRTASParallelOperationGetPropertiesExt(hParallelOperation, pProperties)");

        auto pfnGetPropertiesExt = context.zeDdiTable.RTASParallelOperation.pfnGetPropertiesExt;

        if( nullptr == pfnGetPropertiesExt )
            return logAndPropagateResult("zeRTASParallelOperationGetPropertiesExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationGetPropertiesExtPrologue( hParallelOperation, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationGetPropertiesExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationGetPropertiesExtPrologue( hParallelOperation, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationGetPropertiesExt", result);
        }

        auto driver_result = pfnGetPropertiesExt( hParallelOperation, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationGetPropertiesExtEpilogue( hParallelOperation, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationGetPropertiesExt", result);
        }

        return logAndPropagateResult("zeRTASParallelOperationGetPropertiesExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationJoinExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationJoinExt(
        ze_rtas_parallel_operation_ext_handle_t hParallelOperation  ///< [in] handle of parallel operation object
        )
    {
        context.logger->log_trace("zeRTASParallelOperationJoinExt(hParallelOperation)");

        auto pfnJoinExt = context.zeDdiTable.RTASParallelOperation.pfnJoinExt;

        if( nullptr == pfnJoinExt )
            return logAndPropagateResult("zeRTASParallelOperationJoinExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationJoinExtPrologue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationJoinExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationJoinExtPrologue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationJoinExt", result);
        }

        auto driver_result = pfnJoinExt( hParallelOperation );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationJoinExtEpilogue( hParallelOperation ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationJoinExt", result);
        }

        return logAndPropagateResult("zeRTASParallelOperationJoinExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationDestroyExt
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationDestroyExt(
        ze_rtas_parallel_operation_ext_handle_t hParallelOperation  ///< [in][release] handle of parallel operation object to destroy
        )
    {
        context.logger->log_trace("zeRTASParallelOperationDestroyExt(hParallelOperation)");

        auto pfnDestroyExt = context.zeDdiTable.RTASParallelOperation.pfnDestroyExt;

        if( nullptr == pfnDestroyExt )
            return logAndPropagateResult("zeRTASParallelOperationDestroyExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationDestroyExtPrologue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationDestroyExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationDestroyExtPrologue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationDestroyExt", result);
        }

        auto driver_result = pfnDestroyExt( hParallelOperation );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationDestroyExtEpilogue( hParallelOperation ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationDestroyExt", result);
        }

        return logAndPropagateResult("zeRTASParallelOperationDestroyExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetVectorWidthPropertiesExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetVectorWidthPropertiesExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of vector width properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of vector width properties available.
                                                        ///< if count is greater than the number of vector width properties
                                                        ///< available, then the driver shall update the value with the correct
                                                        ///< number of vector width properties available.
        ze_device_vector_width_properties_ext_t* pVectorWidthProperties ///< [in,out][optional][range(0, *pCount)] array of vector width properties.
                                                        ///< if count is less than the number of properties available, then the
                                                        ///< driver will return only the number requested.
        )
    {
        context.logger->log_trace("zeDeviceGetVectorWidthPropertiesExt(hDevice, pCount, pVectorWidthProperties)");

        auto pfnGetVectorWidthPropertiesExt = context.zeDdiTable.Device.pfnGetVectorWidthPropertiesExt;

        if( nullptr == pfnGetVectorWidthPropertiesExt )
            return logAndPropagateResult("zeDeviceGetVectorWidthPropertiesExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetVectorWidthPropertiesExtPrologue( hDevice, pCount, pVectorWidthProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetVectorWidthPropertiesExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetVectorWidthPropertiesExtPrologue( hDevice, pCount, pVectorWidthProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetVectorWidthPropertiesExt", result);
        }

        auto driver_result = pfnGetVectorWidthPropertiesExt( hDevice, pCount, pVectorWidthProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetVectorWidthPropertiesExtEpilogue( hDevice, pCount, pVectorWidthProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetVectorWidthPropertiesExt", result);
        }

        return logAndPropagateResult("zeDeviceGetVectorWidthPropertiesExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceReserveCacheExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceReserveCacheExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        size_t cacheLevel,                              ///< [in] cache level where application want to reserve. If zero, then the
                                                        ///< driver shall default to last level of cache and attempt to reserve in
                                                        ///< that cache.
        size_t cacheReservationSize                     ///< [in] value for reserving size, in bytes. If zero, then the driver
                                                        ///< shall remove prior reservation
        )
    {
        context.logger->log_trace("zeDeviceReserveCacheExt(hDevice, cacheLevel, cacheReservationSize)");

        auto pfnReserveCacheExt = context.zeDdiTable.Device.pfnReserveCacheExt;

        if( nullptr == pfnReserveCacheExt )
            return logAndPropagateResult("zeDeviceReserveCacheExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceReserveCacheExtPrologue( hDevice, cacheLevel, cacheReservationSize );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceReserveCacheExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceReserveCacheExtPrologue( hDevice, cacheLevel, cacheReservationSize );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceReserveCacheExt", result);
        }

        auto driver_result = pfnReserveCacheExt( hDevice, cacheLevel, cacheReservationSize );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceReserveCacheExtEpilogue( hDevice, cacheLevel, cacheReservationSize ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceReserveCacheExt", result);
        }

        return logAndPropagateResult("zeDeviceReserveCacheExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceSetCacheAdviceExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceSetCacheAdviceExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        void* ptr,                                      ///< [in] memory pointer to query
        size_t regionSize,                              ///< [in] region size, in pages
        ze_cache_ext_region_t cacheRegion               ///< [in] reservation region
        )
    {
        context.logger->log_trace("zeDeviceSetCacheAdviceExt(hDevice, ptr, regionSize, cacheRegion)");

        auto pfnSetCacheAdviceExt = context.zeDdiTable.Device.pfnSetCacheAdviceExt;

        if( nullptr == pfnSetCacheAdviceExt )
            return logAndPropagateResult("zeDeviceSetCacheAdviceExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceSetCacheAdviceExtPrologue( hDevice, ptr, regionSize, cacheRegion );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceSetCacheAdviceExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceSetCacheAdviceExtPrologue( hDevice, ptr, regionSize, cacheRegion );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceSetCacheAdviceExt", result);
        }

        auto driver_result = pfnSetCacheAdviceExt( hDevice, ptr, regionSize, cacheRegion );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceSetCacheAdviceExtEpilogue( hDevice, ptr, regionSize, cacheRegion ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceSetCacheAdviceExt", result);
        }

        return logAndPropagateResult("zeDeviceSetCacheAdviceExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryTimestampsExp
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryTimestampsExp(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_device_handle_t hDevice,                     ///< [in] handle of the device to query
        uint32_t* pCount,                               ///< [in,out] pointer to the number of timestamp results.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of timestamps available.
                                                        ///< if count is greater than the number of timestamps available, then the
                                                        ///< driver shall update the value with the correct number of timestamps available.
        ze_kernel_timestamp_result_t* pTimestamps       ///< [in,out][optional][range(0, *pCount)] array of timestamp results.
                                                        ///< if count is less than the number of timestamps available, then driver
                                                        ///< shall only retrieve that number of timestamps.
        )
    {
        context.logger->log_trace("zeEventQueryTimestampsExp(hEvent, hDevice, pCount, pTimestamps)");

        auto pfnQueryTimestampsExp = context.zeDdiTable.EventExp.pfnQueryTimestampsExp;

        if( nullptr == pfnQueryTimestampsExp )
            return logAndPropagateResult("zeEventQueryTimestampsExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventQueryTimestampsExpPrologue( hEvent, hDevice, pCount, pTimestamps );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventQueryTimestampsExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventQueryTimestampsExpPrologue( hEvent, hDevice, pCount, pTimestamps );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventQueryTimestampsExp", result);
        }

        auto driver_result = pfnQueryTimestampsExp( hEvent, hDevice, pCount, pTimestamps );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventQueryTimestampsExpEpilogue( hEvent, hDevice, pCount, pTimestamps ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventQueryTimestampsExp", result);
        }

        return logAndPropagateResult("zeEventQueryTimestampsExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageGetMemoryPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetMemoryPropertiesExp(
        ze_image_handle_t hImage,                       ///< [in] handle of image object
        ze_image_memory_properties_exp_t* pMemoryProperties ///< [in,out] query result for image memory properties.
        )
    {
        context.logger->log_trace("zeImageGetMemoryPropertiesExp(hImage, pMemoryProperties)");

        auto pfnGetMemoryPropertiesExp = context.zeDdiTable.ImageExp.pfnGetMemoryPropertiesExp;

        if( nullptr == pfnGetMemoryPropertiesExp )
            return logAndPropagateResult("zeImageGetMemoryPropertiesExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageGetMemoryPropertiesExpPrologue( hImage, pMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageGetMemoryPropertiesExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageGetMemoryPropertiesExpPrologue( hImage, pMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageGetMemoryPropertiesExp", result);
        }

        auto driver_result = pfnGetMemoryPropertiesExp( hImage, pMemoryProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageGetMemoryPropertiesExpEpilogue( hImage, pMemoryProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageGetMemoryPropertiesExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zeImageGetMemoryPropertiesExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageViewCreateExt
    __zedlllocal ze_result_t ZE_APICALL
    zeImageViewCreateExt(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t hImage,                       ///< [in] handle of image object to create view from
        ze_image_handle_t* phImageView                  ///< [out] pointer to handle of image object created for view
        )
    {
        context.logger->log_trace("zeImageViewCreateExt(hContext, hDevice, desc, hImage, phImageView)");

        auto pfnViewCreateExt = context.zeDdiTable.Image.pfnViewCreateExt;

        if( nullptr == pfnViewCreateExt )
            return logAndPropagateResult("zeImageViewCreateExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageViewCreateExtPrologue( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageViewCreateExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageViewCreateExtPrologue( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageViewCreateExt", result);
        }

        auto driver_result = pfnViewCreateExt( hContext, hDevice, desc, hImage, phImageView );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageViewCreateExtEpilogue( hContext, hDevice, desc, hImage, phImageView ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageViewCreateExt", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phImageView){
                context.handleLifetime->addHandle( *phImageView );
                context.handleLifetime->addDependent( hContext, *phImageView );

            }
        }
        return logAndPropagateResult("zeImageViewCreateExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageViewCreateExp
    __zedlllocal ze_result_t ZE_APICALL
    zeImageViewCreateExp(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        const ze_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        ze_image_handle_t hImage,                       ///< [in] handle of image object to create view from
        ze_image_handle_t* phImageView                  ///< [out] pointer to handle of image object created for view
        )
    {
        context.logger->log_trace("zeImageViewCreateExp(hContext, hDevice, desc, hImage, phImageView)");

        auto pfnViewCreateExp = context.zeDdiTable.ImageExp.pfnViewCreateExp;

        if( nullptr == pfnViewCreateExp )
            return logAndPropagateResult("zeImageViewCreateExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageViewCreateExpPrologue( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageViewCreateExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageViewCreateExpPrologue( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageViewCreateExp", result);
        }

        auto driver_result = pfnViewCreateExp( hContext, hDevice, desc, hImage, phImageView );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageViewCreateExpEpilogue( hContext, hDevice, desc, hImage, phImageView ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageViewCreateExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phImageView){
                context.handleLifetime->addHandle( *phImageView );
                context.handleLifetime->addDependent( hContext, *phImageView );

            }
        }
        return logAndPropagateResult("zeImageViewCreateExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSchedulingHintExp
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSchedulingHintExp(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_scheduling_hint_exp_desc_t* pHint            ///< [in] pointer to kernel scheduling hint descriptor
        )
    {
        context.logger->log_trace("zeKernelSchedulingHintExp(hKernel, pHint)");

        auto pfnSchedulingHintExp = context.zeDdiTable.KernelExp.pfnSchedulingHintExp;

        if( nullptr == pfnSchedulingHintExp )
            return logAndPropagateResult("zeKernelSchedulingHintExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSchedulingHintExpPrologue( hKernel, pHint );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSchedulingHintExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSchedulingHintExpPrologue( hKernel, pHint );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSchedulingHintExp", result);
        }

        auto driver_result = pfnSchedulingHintExp( hKernel, pHint );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeKernelSchedulingHintExpEpilogue( hKernel, pHint ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeKernelSchedulingHintExp", result);
        }

        return logAndPropagateResult("zeKernelSchedulingHintExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDevicePciGetPropertiesExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDevicePciGetPropertiesExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object.
        ze_pci_ext_properties_t* pPciProperties         ///< [in,out] returns the PCI properties of the device.
        )
    {
        context.logger->log_trace("zeDevicePciGetPropertiesExt(hDevice, pPciProperties)");

        auto pfnPciGetPropertiesExt = context.zeDdiTable.Device.pfnPciGetPropertiesExt;

        if( nullptr == pfnPciGetPropertiesExt )
            return logAndPropagateResult("zeDevicePciGetPropertiesExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDevicePciGetPropertiesExtPrologue( hDevice, pPciProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDevicePciGetPropertiesExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDevicePciGetPropertiesExtPrologue( hDevice, pPciProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDevicePciGetPropertiesExt", result);
        }

        auto driver_result = pfnPciGetPropertiesExt( hDevice, pPciProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDevicePciGetPropertiesExtEpilogue( hDevice, pPciProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDevicePciGetPropertiesExt", result);
        }

        return logAndPropagateResult("zeDevicePciGetPropertiesExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyToMemoryExt
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopyToMemoryExt(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        ze_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        const ze_image_region_t* pSrcRegion,            ///< [in][optional] source region descriptor
        uint32_t destRowPitch,                          ///< [in] size in bytes of the 1D slice of the 2D region of a 2D or 3D
                                                        ///< image or each image of a 1D or 2D image array being written
        uint32_t destSlicePitch,                        ///< [in] size in bytes of the 2D slice of the 3D region of a 3D image or
                                                        ///< each image of a 1D or 2D image array being written
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendImageCopyToMemoryExt(hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendImageCopyToMemoryExt = context.zeDdiTable.CommandList.pfnAppendImageCopyToMemoryExt;

        if( nullptr == pfnAppendImageCopyToMemoryExt )
            return logAndPropagateResult("zeCommandListAppendImageCopyToMemoryExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendImageCopyToMemoryExtPrologue( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopyToMemoryExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyToMemoryExtPrologue( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopyToMemoryExt", result);
        }

        auto driver_result = pfnAppendImageCopyToMemoryExt( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendImageCopyToMemoryExtEpilogue( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopyToMemoryExt", result);
        }

        return logAndPropagateResult("zeCommandListAppendImageCopyToMemoryExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendImageCopyFromMemoryExt
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendImageCopyFromMemoryExt(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of command list
        ze_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const ze_image_region_t* pDstRegion,            ///< [in][optional] destination region descriptor
        uint32_t srcRowPitch,                           ///< [in] size in bytes of the 1D slice of the 2D region of a 2D or 3D
                                                        ///< image or each image of a 1D or 2D image array being read
        uint32_t srcSlicePitch,                         ///< [in] size in bytes of the 2D slice of the 3D region of a 3D image or
                                                        ///< each image of a 1D or 2D image array being read
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListAppendImageCopyFromMemoryExt(hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendImageCopyFromMemoryExt = context.zeDdiTable.CommandList.pfnAppendImageCopyFromMemoryExt;

        if( nullptr == pfnAppendImageCopyFromMemoryExt )
            return logAndPropagateResult("zeCommandListAppendImageCopyFromMemoryExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendImageCopyFromMemoryExtPrologue( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopyFromMemoryExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyFromMemoryExtPrologue( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopyFromMemoryExt", result);
        }

        auto driver_result = pfnAppendImageCopyFromMemoryExt( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListAppendImageCopyFromMemoryExtEpilogue( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListAppendImageCopyFromMemoryExt", result);
        }

        return logAndPropagateResult("zeCommandListAppendImageCopyFromMemoryExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageGetAllocPropertiesExt
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetAllocPropertiesExt(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_image_handle_t hImage,                       ///< [in] handle of image object to query
        ze_image_allocation_ext_properties_t* pImageAllocProperties ///< [in,out] query result for image allocation properties
        )
    {
        context.logger->log_trace("zeImageGetAllocPropertiesExt(hContext, hImage, pImageAllocProperties)");

        auto pfnGetAllocPropertiesExt = context.zeDdiTable.Image.pfnGetAllocPropertiesExt;

        if( nullptr == pfnGetAllocPropertiesExt )
            return logAndPropagateResult("zeImageGetAllocPropertiesExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageGetAllocPropertiesExtPrologue( hContext, hImage, pImageAllocProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageGetAllocPropertiesExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageGetAllocPropertiesExtPrologue( hContext, hImage, pImageAllocProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageGetAllocPropertiesExt", result);
        }

        auto driver_result = pfnGetAllocPropertiesExt( hContext, hImage, pImageAllocProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageGetAllocPropertiesExtEpilogue( hContext, hImage, pImageAllocProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageGetAllocPropertiesExt", result);
        }

        return logAndPropagateResult("zeImageGetAllocPropertiesExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleInspectLinkageExt
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleInspectLinkageExt(
        ze_linkage_inspection_ext_desc_t* pInspectDesc, ///< [in] pointer to linkage inspection descriptor structure.
        uint32_t numModules,                            ///< [in] number of modules to be inspected pointed to by phModules.
        ze_module_handle_t* phModules,                  ///< [in][range(0, numModules)] pointer to an array of modules to be
                                                        ///< inspected for import dependencies.
        ze_module_build_log_handle_t* phLog             ///< [out] pointer to handle of linkage inspection log. Log object will
                                                        ///< contain separate lists of imports, un-resolvable imports, and exports.
        )
    {
        context.logger->log_trace("zeModuleInspectLinkageExt(pInspectDesc, numModules, phModulesLocal, phLog)");

        auto pfnInspectLinkageExt = context.zeDdiTable.Module.pfnInspectLinkageExt;

        if( nullptr == pfnInspectLinkageExt )
            return logAndPropagateResult("zeModuleInspectLinkageExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleInspectLinkageExtPrologue( pInspectDesc, numModules, phModules, phLog );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleInspectLinkageExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleInspectLinkageExtPrologue( pInspectDesc, numModules, phModules, phLog );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleInspectLinkageExt", result);
        }

        auto driver_result = pfnInspectLinkageExt( pInspectDesc, numModules, phModules, phLog );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeModuleInspectLinkageExtEpilogue( pInspectDesc, numModules, phModules, phLog ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeModuleInspectLinkageExt", result);
        }

        return logAndPropagateResult("zeModuleInspectLinkageExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemFreeExt
    __zedlllocal ze_result_t ZE_APICALL
    zeMemFreeExt(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const ze_memory_free_ext_desc_t* pMemFreeDesc,  ///< [in] pointer to memory free descriptor
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        context.logger->log_trace("zeMemFreeExt(hContext, pMemFreeDesc, ptr)");

        auto pfnFreeExt = context.zeDdiTable.Mem.pfnFreeExt;

        if( nullptr == pfnFreeExt )
            return logAndPropagateResult("zeMemFreeExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemFreeExtPrologue( hContext, pMemFreeDesc, ptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemFreeExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemFreeExtPrologue( hContext, pMemFreeDesc, ptr );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemFreeExt", result);
        }

        auto driver_result = pfnFreeExt( hContext, pMemFreeDesc, ptr );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemFreeExtEpilogue( hContext, pMemFreeDesc, ptr ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemFreeExt", result);
        }

        return logAndPropagateResult("zeMemFreeExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricVertexGetExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of fabric vertices.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of fabric vertices available.
                                                        ///< if count is greater than the number of fabric vertices available, then
                                                        ///< the driver shall update the value with the correct number of fabric
                                                        ///< vertices available.
        ze_fabric_vertex_handle_t* phVertices           ///< [in,out][optional][range(0, *pCount)] array of handle of fabric vertices.
                                                        ///< if count is less than the number of fabric vertices available, then
                                                        ///< driver shall only retrieve that number of fabric vertices.
        )
    {
        context.logger->log_trace("zeFabricVertexGetExp(hDriver, pCount, phVertices)");

        auto pfnGetExp = context.zeDdiTable.FabricVertexExp.pfnGetExp;

        if( nullptr == pfnGetExp )
            return logAndPropagateResult("zeFabricVertexGetExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFabricVertexGetExpPrologue( hDriver, pCount, phVertices );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricVertexGetExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricVertexGetExpPrologue( hDriver, pCount, phVertices );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricVertexGetExp", result);
        }

        auto driver_result = pfnGetExp( hDriver, pCount, phVertices );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFabricVertexGetExpEpilogue( hDriver, pCount, phVertices ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricVertexGetExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phVertices) && (i < *pCount); ++i){
                if (phVertices[i]){
                    context.handleLifetime->addHandle( phVertices[i] );
                    context.handleLifetime->addDependent( hDriver, phVertices[i] );
                }
            }
        }
        return logAndPropagateResult("zeFabricVertexGetExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricVertexGetSubVerticesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetSubVerticesExp(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex object
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-vertices.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of sub-vertices available.
                                                        ///< if count is greater than the number of sub-vertices available, then
                                                        ///< the driver shall update the value with the correct number of
                                                        ///< sub-vertices available.
        ze_fabric_vertex_handle_t* phSubvertices        ///< [in,out][optional][range(0, *pCount)] array of handle of sub-vertices.
                                                        ///< if count is less than the number of sub-vertices available, then
                                                        ///< driver shall only retrieve that number of sub-vertices.
        )
    {
        context.logger->log_trace("zeFabricVertexGetSubVerticesExp(hVertex, pCount, phSubvertices)");

        auto pfnGetSubVerticesExp = context.zeDdiTable.FabricVertexExp.pfnGetSubVerticesExp;

        if( nullptr == pfnGetSubVerticesExp )
            return logAndPropagateResult("zeFabricVertexGetSubVerticesExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFabricVertexGetSubVerticesExpPrologue( hVertex, pCount, phSubvertices );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricVertexGetSubVerticesExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricVertexGetSubVerticesExpPrologue( hVertex, pCount, phSubvertices );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricVertexGetSubVerticesExp", result);
        }

        auto driver_result = pfnGetSubVerticesExp( hVertex, pCount, phSubvertices );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFabricVertexGetSubVerticesExpEpilogue( hVertex, pCount, phSubvertices ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricVertexGetSubVerticesExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phSubvertices) && (i < *pCount); ++i){
                if (phSubvertices[i]){
                    context.handleLifetime->addHandle( phSubvertices[i] );
                    context.handleLifetime->addDependent( hVertex, phSubvertices[i] );
                }
            }
        }
        return logAndPropagateResult("zeFabricVertexGetSubVerticesExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricVertexGetPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetPropertiesExp(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
        ze_fabric_vertex_exp_properties_t* pVertexProperties///< [in,out] query result for fabric vertex properties
        )
    {
        context.logger->log_trace("zeFabricVertexGetPropertiesExp(hVertex, pVertexProperties)");

        auto pfnGetPropertiesExp = context.zeDdiTable.FabricVertexExp.pfnGetPropertiesExp;

        if( nullptr == pfnGetPropertiesExp )
            return logAndPropagateResult("zeFabricVertexGetPropertiesExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFabricVertexGetPropertiesExpPrologue( hVertex, pVertexProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricVertexGetPropertiesExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricVertexGetPropertiesExpPrologue( hVertex, pVertexProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricVertexGetPropertiesExp", result);
        }

        auto driver_result = pfnGetPropertiesExp( hVertex, pVertexProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFabricVertexGetPropertiesExpEpilogue( hVertex, pVertexProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricVertexGetPropertiesExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zeFabricVertexGetPropertiesExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricVertexGetDeviceExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetDeviceExp(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
        ze_device_handle_t* phDevice                    ///< [out] device handle corresponding to fabric vertex
        )
    {
        context.logger->log_trace("zeFabricVertexGetDeviceExp(hVertex, phDevice)");

        auto pfnGetDeviceExp = context.zeDdiTable.FabricVertexExp.pfnGetDeviceExp;

        if( nullptr == pfnGetDeviceExp )
            return logAndPropagateResult("zeFabricVertexGetDeviceExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFabricVertexGetDeviceExpPrologue( hVertex, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricVertexGetDeviceExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricVertexGetDeviceExpPrologue( hVertex, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricVertexGetDeviceExp", result);
        }

        auto driver_result = pfnGetDeviceExp( hVertex, phDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFabricVertexGetDeviceExpEpilogue( hVertex, phDevice ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricVertexGetDeviceExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phDevice){
                context.handleLifetime->addHandle( *phDevice );
                context.handleLifetime->addDependent( hVertex, *phDevice );

            }
        }
        return logAndPropagateResult("zeFabricVertexGetDeviceExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetFabricVertexExp
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetFabricVertexExp(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_fabric_vertex_handle_t* phVertex             ///< [out] fabric vertex handle corresponding to device
        )
    {
        context.logger->log_trace("zeDeviceGetFabricVertexExp(hDevice, phVertex)");

        auto pfnGetFabricVertexExp = context.zeDdiTable.DeviceExp.pfnGetFabricVertexExp;

        if( nullptr == pfnGetFabricVertexExp )
            return logAndPropagateResult("zeDeviceGetFabricVertexExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetFabricVertexExpPrologue( hDevice, phVertex );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetFabricVertexExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetFabricVertexExpPrologue( hDevice, phVertex );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetFabricVertexExp", result);
        }

        auto driver_result = pfnGetFabricVertexExp( hDevice, phVertex );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDeviceGetFabricVertexExpEpilogue( hDevice, phVertex ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDeviceGetFabricVertexExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phVertex){
                context.handleLifetime->addHandle( *phVertex );
                context.handleLifetime->addDependent( hDevice, *phVertex );

            }
        }
        return logAndPropagateResult("zeDeviceGetFabricVertexExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricEdgeGetExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricEdgeGetExp(
        ze_fabric_vertex_handle_t hVertexA,             ///< [in] handle of first fabric vertex instance
        ze_fabric_vertex_handle_t hVertexB,             ///< [in] handle of second fabric vertex instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of fabric edges.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of fabric edges available.
                                                        ///< if count is greater than the number of fabric edges available, then
                                                        ///< the driver shall update the value with the correct number of fabric
                                                        ///< edges available.
        ze_fabric_edge_handle_t* phEdges                ///< [in,out][optional][range(0, *pCount)] array of handle of fabric edges.
                                                        ///< if count is less than the number of fabric edges available, then
                                                        ///< driver shall only retrieve that number of fabric edges.
        )
    {
        context.logger->log_trace("zeFabricEdgeGetExp(hVertexA, hVertexB, pCount, phEdges)");

        auto pfnGetExp = context.zeDdiTable.FabricEdgeExp.pfnGetExp;

        if( nullptr == pfnGetExp )
            return logAndPropagateResult("zeFabricEdgeGetExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFabricEdgeGetExpPrologue( hVertexA, hVertexB, pCount, phEdges );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricEdgeGetExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricEdgeGetExpPrologue( hVertexA, hVertexB, pCount, phEdges );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricEdgeGetExp", result);
        }

        auto driver_result = pfnGetExp( hVertexA, hVertexB, pCount, phEdges );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFabricEdgeGetExpEpilogue( hVertexA, hVertexB, pCount, phEdges ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricEdgeGetExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phEdges) && (i < *pCount); ++i){
                if (phEdges[i]){
                    context.handleLifetime->addHandle( phEdges[i] );
                    context.handleLifetime->addDependent( hVertexA, phEdges[i] );
                }
            }
        }
        return logAndPropagateResult("zeFabricEdgeGetExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricEdgeGetVerticesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricEdgeGetVerticesExp(
        ze_fabric_edge_handle_t hEdge,                  ///< [in] handle of the fabric edge instance
        ze_fabric_vertex_handle_t* phVertexA,           ///< [out] fabric vertex connected to one end of the given fabric edge.
        ze_fabric_vertex_handle_t* phVertexB            ///< [out] fabric vertex connected to other end of the given fabric edge.
        )
    {
        context.logger->log_trace("zeFabricEdgeGetVerticesExp(hEdge, phVertexA, phVertexB)");

        auto pfnGetVerticesExp = context.zeDdiTable.FabricEdgeExp.pfnGetVerticesExp;

        if( nullptr == pfnGetVerticesExp )
            return logAndPropagateResult("zeFabricEdgeGetVerticesExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFabricEdgeGetVerticesExpPrologue( hEdge, phVertexA, phVertexB );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricEdgeGetVerticesExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricEdgeGetVerticesExpPrologue( hEdge, phVertexA, phVertexB );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricEdgeGetVerticesExp", result);
        }

        auto driver_result = pfnGetVerticesExp( hEdge, phVertexA, phVertexB );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFabricEdgeGetVerticesExpEpilogue( hEdge, phVertexA, phVertexB ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricEdgeGetVerticesExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phVertexA){
                context.handleLifetime->addHandle( *phVertexA );
                context.handleLifetime->addDependent( hEdge, *phVertexA );

            }
            if (phVertexB){
                context.handleLifetime->addHandle( *phVertexB );
                context.handleLifetime->addDependent( hEdge, *phVertexB );

            }
        }
        return logAndPropagateResult("zeFabricEdgeGetVerticesExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricEdgeGetPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricEdgeGetPropertiesExp(
        ze_fabric_edge_handle_t hEdge,                  ///< [in] handle of the fabric edge
        ze_fabric_edge_exp_properties_t* pEdgeProperties///< [in,out] query result for fabric edge properties
        )
    {
        context.logger->log_trace("zeFabricEdgeGetPropertiesExp(hEdge, pEdgeProperties)");

        auto pfnGetPropertiesExp = context.zeDdiTable.FabricEdgeExp.pfnGetPropertiesExp;

        if( nullptr == pfnGetPropertiesExp )
            return logAndPropagateResult("zeFabricEdgeGetPropertiesExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFabricEdgeGetPropertiesExpPrologue( hEdge, pEdgeProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricEdgeGetPropertiesExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricEdgeGetPropertiesExpPrologue( hEdge, pEdgeProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricEdgeGetPropertiesExp", result);
        }

        auto driver_result = pfnGetPropertiesExp( hEdge, pEdgeProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeFabricEdgeGetPropertiesExpEpilogue( hEdge, pEdgeProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeFabricEdgeGetPropertiesExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zeFabricEdgeGetPropertiesExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryKernelTimestampsExt
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryKernelTimestampsExt(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_device_handle_t hDevice,                     ///< [in] handle of the device to query
        uint32_t* pCount,                               ///< [in,out] pointer to the number of event packets available.
                                                        ///<    - This value is implementation specific.
                                                        ///<    - if `*pCount` is zero, then the driver shall update the value with
                                                        ///< the total number of event packets available.
                                                        ///<    - if `*pCount` is greater than the number of event packets
                                                        ///< available, the driver shall update the value with the correct value.
                                                        ///<    - Buffer(s) for query results must be sized by the application to
                                                        ///< accommodate a minimum of `*pCount` elements.
        ze_event_query_kernel_timestamps_results_ext_properties_t* pResults ///< [in,out][optional][range(0, *pCount)] pointer to event query
                                                        ///< properties structure(s).
                                                        ///<    - This parameter may be null when `*pCount` is zero.
                                                        ///<    - if `*pCount` is less than the number of event packets available,
                                                        ///< the driver may only update `*pCount` elements, starting at element zero.
                                                        ///<    - if `*pCount` is greater than the number of event packets
                                                        ///< available, the driver may only update the valid elements.
        )
    {
        context.logger->log_trace("zeEventQueryKernelTimestampsExt(hEvent, hDevice, pCount, pResults)");

        auto pfnQueryKernelTimestampsExt = context.zeDdiTable.Event.pfnQueryKernelTimestampsExt;

        if( nullptr == pfnQueryKernelTimestampsExt )
            return logAndPropagateResult("zeEventQueryKernelTimestampsExt", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventQueryKernelTimestampsExtPrologue( hEvent, hDevice, pCount, pResults );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventQueryKernelTimestampsExt", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventQueryKernelTimestampsExtPrologue( hEvent, hDevice, pCount, pResults );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventQueryKernelTimestampsExt", result);
        }

        auto driver_result = pfnQueryKernelTimestampsExt( hEvent, hDevice, pCount, pResults );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeEventQueryKernelTimestampsExtEpilogue( hEvent, hDevice, pCount, pResults ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeEventQueryKernelTimestampsExt", result);
        }

        return logAndPropagateResult("zeEventQueryKernelTimestampsExt", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderCreateExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderCreateExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        const ze_rtas_builder_exp_desc_t* pDescriptor,  ///< [in] pointer to builder descriptor
        ze_rtas_builder_exp_handle_t* phBuilder         ///< [out] handle of builder object
        )
    {
        context.logger->log_trace("zeRTASBuilderCreateExp(hDriver, pDescriptor, phBuilder)");

        auto pfnCreateExp = context.zeDdiTable.RTASBuilderExp.pfnCreateExp;

        if( nullptr == pfnCreateExp )
            return logAndPropagateResult("zeRTASBuilderCreateExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderCreateExpPrologue( hDriver, pDescriptor, phBuilder );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderCreateExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderCreateExpPrologue( hDriver, pDescriptor, phBuilder );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderCreateExp", result);
        }

        auto driver_result = pfnCreateExp( hDriver, pDescriptor, phBuilder );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderCreateExpEpilogue( hDriver, pDescriptor, phBuilder ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderCreateExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phBuilder){
                context.handleLifetime->addHandle( *phBuilder );
                context.handleLifetime->addDependent( hDriver, *phBuilder );

            }
        }
        return logAndPropagateResult("zeRTASBuilderCreateExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderGetBuildPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderGetBuildPropertiesExp(
        ze_rtas_builder_exp_handle_t hBuilder,          ///< [in] handle of builder object
        const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
        ze_rtas_builder_exp_properties_t* pProperties   ///< [in,out] query result for builder properties
        )
    {
        context.logger->log_trace("zeRTASBuilderGetBuildPropertiesExp(hBuilder, pBuildOpDescriptor, pProperties)");

        auto pfnGetBuildPropertiesExp = context.zeDdiTable.RTASBuilderExp.pfnGetBuildPropertiesExp;

        if( nullptr == pfnGetBuildPropertiesExp )
            return logAndPropagateResult("zeRTASBuilderGetBuildPropertiesExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderGetBuildPropertiesExpPrologue( hBuilder, pBuildOpDescriptor, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderGetBuildPropertiesExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderGetBuildPropertiesExpPrologue( hBuilder, pBuildOpDescriptor, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderGetBuildPropertiesExp", result);
        }

        auto driver_result = pfnGetBuildPropertiesExp( hBuilder, pBuildOpDescriptor, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderGetBuildPropertiesExpEpilogue( hBuilder, pBuildOpDescriptor, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderGetBuildPropertiesExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zeRTASBuilderGetBuildPropertiesExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverRTASFormatCompatibilityCheckExp
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverRTASFormatCompatibilityCheckExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_format_exp_t rtasFormatA,               ///< [in] operand A
        ze_rtas_format_exp_t rtasFormatB                ///< [in] operand B
        )
    {
        context.logger->log_trace("zeDriverRTASFormatCompatibilityCheckExp(hDriver, rtasFormatA, rtasFormatB)");

        auto pfnRTASFormatCompatibilityCheckExp = context.zeDdiTable.DriverExp.pfnRTASFormatCompatibilityCheckExp;

        if( nullptr == pfnRTASFormatCompatibilityCheckExp )
            return logAndPropagateResult("zeDriverRTASFormatCompatibilityCheckExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverRTASFormatCompatibilityCheckExpPrologue( hDriver, rtasFormatA, rtasFormatB );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverRTASFormatCompatibilityCheckExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverRTASFormatCompatibilityCheckExpPrologue( hDriver, rtasFormatA, rtasFormatB );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverRTASFormatCompatibilityCheckExp", result);
        }

        auto driver_result = pfnRTASFormatCompatibilityCheckExp( hDriver, rtasFormatA, rtasFormatB );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeDriverRTASFormatCompatibilityCheckExpEpilogue( hDriver, rtasFormatA, rtasFormatB ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeDriverRTASFormatCompatibilityCheckExp", result);
        }

        return logAndPropagateResult("zeDriverRTASFormatCompatibilityCheckExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderBuildExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderBuildExp(
        ze_rtas_builder_exp_handle_t hBuilder,          ///< [in] handle of builder object
        const ze_rtas_builder_build_op_exp_desc_t* pBuildOpDescriptor,  ///< [in] pointer to build operation descriptor
        void* pScratchBuffer,                           ///< [in][range(0, `scratchBufferSizeBytes`)] scratch buffer to be used
                                                        ///< during acceleration structure construction
        size_t scratchBufferSizeBytes,                  ///< [in] size of scratch buffer, in bytes
        void* pRtasBuffer,                              ///< [in] pointer to destination buffer
        size_t rtasBufferSizeBytes,                     ///< [in] destination buffer size, in bytes
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ///< [in][optional] handle to parallel operation object
        void* pBuildUserPtr,                            ///< [in][optional] pointer passed to callbacks
        ze_rtas_aabb_exp_t* pBounds,                    ///< [in,out][optional] pointer to destination address for acceleration
                                                        ///< structure bounds
        size_t* pRtasBufferSizeBytes                    ///< [out][optional] updated acceleration structure size requirement, in
                                                        ///< bytes
        )
    {
        context.logger->log_trace("zeRTASBuilderBuildExp(hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes)");

        auto pfnBuildExp = context.zeDdiTable.RTASBuilderExp.pfnBuildExp;

        if( nullptr == pfnBuildExp )
            return logAndPropagateResult("zeRTASBuilderBuildExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderBuildExpPrologue( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderBuildExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderBuildExpPrologue( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderBuildExp", result);
        }

        auto driver_result = pfnBuildExp( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderBuildExpEpilogue( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderBuildExp", result);
        }

        return logAndPropagateResult("zeRTASBuilderBuildExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderDestroyExp(
        ze_rtas_builder_exp_handle_t hBuilder           ///< [in][release] handle of builder object to destroy
        )
    {
        context.logger->log_trace("zeRTASBuilderDestroyExp(hBuilder)");

        auto pfnDestroyExp = context.zeDdiTable.RTASBuilderExp.pfnDestroyExp;

        if( nullptr == pfnDestroyExp )
            return logAndPropagateResult("zeRTASBuilderDestroyExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderDestroyExpPrologue( hBuilder );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderDestroyExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderDestroyExpPrologue( hBuilder );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderDestroyExp", result);
        }

        auto driver_result = pfnDestroyExp( hBuilder );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASBuilderDestroyExpEpilogue( hBuilder ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASBuilderDestroyExp", result);
        }

        return logAndPropagateResult("zeRTASBuilderDestroyExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationCreateExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationCreateExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_parallel_operation_exp_handle_t* phParallelOperation///< [out] handle of parallel operation object
        )
    {
        context.logger->log_trace("zeRTASParallelOperationCreateExp(hDriver, phParallelOperation)");

        auto pfnCreateExp = context.zeDdiTable.RTASParallelOperationExp.pfnCreateExp;

        if( nullptr == pfnCreateExp )
            return logAndPropagateResult("zeRTASParallelOperationCreateExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationCreateExpPrologue( hDriver, phParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationCreateExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationCreateExpPrologue( hDriver, phParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationCreateExp", result);
        }

        auto driver_result = pfnCreateExp( hDriver, phParallelOperation );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationCreateExpEpilogue( hDriver, phParallelOperation ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationCreateExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phParallelOperation){
                context.handleLifetime->addHandle( *phParallelOperation );
                context.handleLifetime->addDependent( hDriver, *phParallelOperation );

            }
        }
        return logAndPropagateResult("zeRTASParallelOperationCreateExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationGetPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationGetPropertiesExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ///< [in] handle of parallel operation object
        ze_rtas_parallel_operation_exp_properties_t* pProperties///< [in,out] query result for parallel operation properties
        )
    {
        context.logger->log_trace("zeRTASParallelOperationGetPropertiesExp(hParallelOperation, pProperties)");

        auto pfnGetPropertiesExp = context.zeDdiTable.RTASParallelOperationExp.pfnGetPropertiesExp;

        if( nullptr == pfnGetPropertiesExp )
            return logAndPropagateResult("zeRTASParallelOperationGetPropertiesExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationGetPropertiesExpPrologue( hParallelOperation, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationGetPropertiesExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationGetPropertiesExpPrologue( hParallelOperation, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationGetPropertiesExp", result);
        }

        auto driver_result = pfnGetPropertiesExp( hParallelOperation, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationGetPropertiesExpEpilogue( hParallelOperation, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationGetPropertiesExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zeRTASParallelOperationGetPropertiesExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationJoinExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationJoinExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in] handle of parallel operation object
        )
    {
        context.logger->log_trace("zeRTASParallelOperationJoinExp(hParallelOperation)");

        auto pfnJoinExp = context.zeDdiTable.RTASParallelOperationExp.pfnJoinExp;

        if( nullptr == pfnJoinExp )
            return logAndPropagateResult("zeRTASParallelOperationJoinExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationJoinExpPrologue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationJoinExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationJoinExpPrologue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationJoinExp", result);
        }

        auto driver_result = pfnJoinExp( hParallelOperation );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationJoinExpEpilogue( hParallelOperation ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationJoinExp", result);
        }

        return logAndPropagateResult("zeRTASParallelOperationJoinExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationDestroyExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in][release] handle of parallel operation object to destroy
        )
    {
        context.logger->log_trace("zeRTASParallelOperationDestroyExp(hParallelOperation)");

        auto pfnDestroyExp = context.zeDdiTable.RTASParallelOperationExp.pfnDestroyExp;

        if( nullptr == pfnDestroyExp )
            return logAndPropagateResult("zeRTASParallelOperationDestroyExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationDestroyExpPrologue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationDestroyExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationDestroyExpPrologue( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationDestroyExp", result);
        }

        auto driver_result = pfnDestroyExp( hParallelOperation );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeRTASParallelOperationDestroyExpEpilogue( hParallelOperation ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeRTASParallelOperationDestroyExp", result);
        }

        return logAndPropagateResult("zeRTASParallelOperationDestroyExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemGetPitchFor2dImage
    __zedlllocal ze_result_t ZE_APICALL
    zeMemGetPitchFor2dImage(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        size_t imageWidth,                              ///< [in] imageWidth
        size_t imageHeight,                             ///< [in] imageHeight
        unsigned int elementSizeInBytes,                ///< [in] Element size in bytes
        size_t * rowPitch                               ///< [out] rowPitch
        )
    {
        context.logger->log_trace("zeMemGetPitchFor2dImage(hContext, hDevice, imageWidth, imageHeight, elementSizeInBytes, rowPitch)");

        auto pfnGetPitchFor2dImage = context.zeDdiTable.Mem.pfnGetPitchFor2dImage;

        if( nullptr == pfnGetPitchFor2dImage )
            return logAndPropagateResult("zeMemGetPitchFor2dImage", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemGetPitchFor2dImagePrologue( hContext, hDevice, imageWidth, imageHeight, elementSizeInBytes, rowPitch );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetPitchFor2dImage", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetPitchFor2dImagePrologue( hContext, hDevice, imageWidth, imageHeight, elementSizeInBytes, rowPitch );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetPitchFor2dImage", result);
        }

        auto driver_result = pfnGetPitchFor2dImage( hContext, hDevice, imageWidth, imageHeight, elementSizeInBytes, rowPitch );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeMemGetPitchFor2dImageEpilogue( hContext, hDevice, imageWidth, imageHeight, elementSizeInBytes, rowPitch ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeMemGetPitchFor2dImage", result);
        }

        return logAndPropagateResult("zeMemGetPitchFor2dImage", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageGetDeviceOffsetExp
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetDeviceOffsetExp(
        ze_image_handle_t hImage,                       ///< [in] handle of the image
        uint64_t* pDeviceOffset                         ///< [out] bindless device offset for image
        )
    {
        context.logger->log_trace("zeImageGetDeviceOffsetExp(hImage, pDeviceOffset)");

        auto pfnGetDeviceOffsetExp = context.zeDdiTable.ImageExp.pfnGetDeviceOffsetExp;

        if( nullptr == pfnGetDeviceOffsetExp )
            return logAndPropagateResult("zeImageGetDeviceOffsetExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageGetDeviceOffsetExpPrologue( hImage, pDeviceOffset );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageGetDeviceOffsetExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageGetDeviceOffsetExpPrologue( hImage, pDeviceOffset );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageGetDeviceOffsetExp", result);
        }

        auto driver_result = pfnGetDeviceOffsetExp( hImage, pDeviceOffset );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeImageGetDeviceOffsetExpEpilogue( hImage, pDeviceOffset ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeImageGetDeviceOffsetExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zeImageGetDeviceOffsetExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListCreateCloneExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListCreateCloneExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle to source command list (the command list to clone)
        ze_command_list_handle_t* phClonedCommandList   ///< [out] pointer to handle of the cloned command list
        )
    {
        context.logger->log_trace("zeCommandListCreateCloneExp(hCommandList, phClonedCommandList)");

        auto pfnCreateCloneExp = context.zeDdiTable.CommandListExp.pfnCreateCloneExp;

        if( nullptr == pfnCreateCloneExp )
            return logAndPropagateResult("zeCommandListCreateCloneExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListCreateCloneExpPrologue( hCommandList, phClonedCommandList );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListCreateCloneExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListCreateCloneExpPrologue( hCommandList, phClonedCommandList );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListCreateCloneExp", result);
        }

        auto driver_result = pfnCreateCloneExp( hCommandList, phClonedCommandList );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListCreateCloneExpEpilogue( hCommandList, phClonedCommandList ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListCreateCloneExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phClonedCommandList){
                context.handleLifetime->addHandle( *phClonedCommandList );
                context.handleLifetime->addDependent( hCommandList, *phClonedCommandList );

            }
        }
        return logAndPropagateResult("zeCommandListCreateCloneExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListImmediateAppendCommandListsExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListImmediateAppendCommandListsExp(
        ze_command_list_handle_t hCommandListImmediate, ///< [in] handle of the immediate command list
        uint32_t numCommandLists,                       ///< [in] number of command lists
        ze_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] handles of command lists
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
                                                        ///<    - if not null, this event is signaled after the completion of all
                                                        ///< appended command lists
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing appended
                                                        ///< command lists; must be 0 if nullptr == phWaitEvents
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before executing appended command lists.
                                                        ///<    - if not null, all wait events must be satisfied prior to the start
                                                        ///< of any appended command list(s)
        )
    {
        context.logger->log_trace("zeCommandListImmediateAppendCommandListsExp(hCommandListImmediate, numCommandLists, phCommandListsLocal, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnImmediateAppendCommandListsExp = context.zeDdiTable.CommandListExp.pfnImmediateAppendCommandListsExp;

        if( nullptr == pfnImmediateAppendCommandListsExp )
            return logAndPropagateResult("zeCommandListImmediateAppendCommandListsExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListImmediateAppendCommandListsExpPrologue( hCommandListImmediate, numCommandLists, phCommandLists, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListImmediateAppendCommandListsExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListImmediateAppendCommandListsExpPrologue( hCommandListImmediate, numCommandLists, phCommandLists, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListImmediateAppendCommandListsExp", result);
        }

        auto driver_result = pfnImmediateAppendCommandListsExp( hCommandListImmediate, numCommandLists, phCommandLists, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListImmediateAppendCommandListsExpEpilogue( hCommandListImmediate, numCommandLists, phCommandLists, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListImmediateAppendCommandListsExp", result);
        }

        return logAndPropagateResult("zeCommandListImmediateAppendCommandListsExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListGetNextCommandIdExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetNextCommandIdExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        const ze_mutable_command_id_exp_desc_t* desc,   ///< [in] pointer to mutable command identifier descriptor
        uint64_t* pCommandId                            ///< [out] pointer to mutable command identifier to be written
        )
    {
        context.logger->log_trace("zeCommandListGetNextCommandIdExp(hCommandList, desc, pCommandId)");

        auto pfnGetNextCommandIdExp = context.zeDdiTable.CommandListExp.pfnGetNextCommandIdExp;

        if( nullptr == pfnGetNextCommandIdExp )
            return logAndPropagateResult("zeCommandListGetNextCommandIdExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListGetNextCommandIdExpPrologue( hCommandList, desc, pCommandId );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListGetNextCommandIdExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListGetNextCommandIdExpPrologue( hCommandList, desc, pCommandId );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListGetNextCommandIdExp", result);
        }

        auto driver_result = pfnGetNextCommandIdExp( hCommandList, desc, pCommandId );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListGetNextCommandIdExpEpilogue( hCommandList, desc, pCommandId ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListGetNextCommandIdExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zeCommandListGetNextCommandIdExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListGetNextCommandIdWithKernelsExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListGetNextCommandIdWithKernelsExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        const ze_mutable_command_id_exp_desc_t* desc,   ///< [in][out] pointer to mutable command identifier descriptor
        uint32_t numKernels,                            ///< [in][optional] number of entries on phKernels list
        ze_kernel_handle_t* phKernels,                  ///< [in][optional][range(0, numKernels)] list of kernels that user can
                                                        ///< switch between using ::zeCommandListUpdateMutableCommandKernelsExp
                                                        ///< call
        uint64_t* pCommandId                            ///< [out] pointer to mutable command identifier to be written
        )
    {
        context.logger->log_trace("zeCommandListGetNextCommandIdWithKernelsExp(hCommandList, desc, numKernels, phKernelsLocal, pCommandId)");

        auto pfnGetNextCommandIdWithKernelsExp = context.zeDdiTable.CommandListExp.pfnGetNextCommandIdWithKernelsExp;

        if( nullptr == pfnGetNextCommandIdWithKernelsExp )
            return logAndPropagateResult("zeCommandListGetNextCommandIdWithKernelsExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListGetNextCommandIdWithKernelsExpPrologue( hCommandList, desc, numKernels, phKernels, pCommandId );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListGetNextCommandIdWithKernelsExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListGetNextCommandIdWithKernelsExpPrologue( hCommandList, desc, numKernels, phKernels, pCommandId );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListGetNextCommandIdWithKernelsExp", result);
        }

        auto driver_result = pfnGetNextCommandIdWithKernelsExp( hCommandList, desc, numKernels, phKernels, pCommandId );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListGetNextCommandIdWithKernelsExpEpilogue( hCommandList, desc, numKernels, phKernels, pCommandId ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListGetNextCommandIdWithKernelsExp", result);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult("zeCommandListGetNextCommandIdWithKernelsExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListUpdateMutableCommandsExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListUpdateMutableCommandsExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        const ze_mutable_commands_exp_desc_t* desc      ///< [in] pointer to mutable commands descriptor; multiple descriptors may
                                                        ///< be chained via `pNext` member
        )
    {
        context.logger->log_trace("zeCommandListUpdateMutableCommandsExp(hCommandList, desc)");

        auto pfnUpdateMutableCommandsExp = context.zeDdiTable.CommandListExp.pfnUpdateMutableCommandsExp;

        if( nullptr == pfnUpdateMutableCommandsExp )
            return logAndPropagateResult("zeCommandListUpdateMutableCommandsExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListUpdateMutableCommandsExpPrologue( hCommandList, desc );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListUpdateMutableCommandsExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListUpdateMutableCommandsExpPrologue( hCommandList, desc );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListUpdateMutableCommandsExp", result);
        }

        auto driver_result = pfnUpdateMutableCommandsExp( hCommandList, desc );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListUpdateMutableCommandsExpEpilogue( hCommandList, desc ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListUpdateMutableCommandsExp", result);
        }

        return logAndPropagateResult("zeCommandListUpdateMutableCommandsExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListUpdateMutableCommandSignalEventExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListUpdateMutableCommandSignalEventExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint64_t commandId,                             ///< [in] command identifier
        ze_event_handle_t hSignalEvent                  ///< [in][optional] handle of the event to signal on completion
        )
    {
        context.logger->log_trace("zeCommandListUpdateMutableCommandSignalEventExp(hCommandList, commandId, hSignalEvent)");

        auto pfnUpdateMutableCommandSignalEventExp = context.zeDdiTable.CommandListExp.pfnUpdateMutableCommandSignalEventExp;

        if( nullptr == pfnUpdateMutableCommandSignalEventExp )
            return logAndPropagateResult("zeCommandListUpdateMutableCommandSignalEventExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListUpdateMutableCommandSignalEventExpPrologue( hCommandList, commandId, hSignalEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListUpdateMutableCommandSignalEventExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListUpdateMutableCommandSignalEventExpPrologue( hCommandList, commandId, hSignalEvent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListUpdateMutableCommandSignalEventExp", result);
        }

        auto driver_result = pfnUpdateMutableCommandSignalEventExp( hCommandList, commandId, hSignalEvent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListUpdateMutableCommandSignalEventExpEpilogue( hCommandList, commandId, hSignalEvent ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListUpdateMutableCommandSignalEventExp", result);
        }

        return logAndPropagateResult("zeCommandListUpdateMutableCommandSignalEventExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListUpdateMutableCommandWaitEventsExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListUpdateMutableCommandWaitEventsExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint64_t commandId,                             ///< [in] command identifier
        uint32_t numWaitEvents,                         ///< [in][optional] the number of wait events
        ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                        ///< on before launching
        )
    {
        context.logger->log_trace("zeCommandListUpdateMutableCommandWaitEventsExp(hCommandList, commandId, numWaitEvents, phWaitEventsLocal)");

        auto pfnUpdateMutableCommandWaitEventsExp = context.zeDdiTable.CommandListExp.pfnUpdateMutableCommandWaitEventsExp;

        if( nullptr == pfnUpdateMutableCommandWaitEventsExp )
            return logAndPropagateResult("zeCommandListUpdateMutableCommandWaitEventsExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListUpdateMutableCommandWaitEventsExpPrologue( hCommandList, commandId, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListUpdateMutableCommandWaitEventsExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListUpdateMutableCommandWaitEventsExpPrologue( hCommandList, commandId, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListUpdateMutableCommandWaitEventsExp", result);
        }

        auto driver_result = pfnUpdateMutableCommandWaitEventsExp( hCommandList, commandId, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListUpdateMutableCommandWaitEventsExpEpilogue( hCommandList, commandId, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListUpdateMutableCommandWaitEventsExp", result);
        }

        return logAndPropagateResult("zeCommandListUpdateMutableCommandWaitEventsExp", driver_result);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListUpdateMutableCommandKernelsExp
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListUpdateMutableCommandKernelsExp(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numKernels,                            ///< [in] the number of kernels to update
        uint64_t* pCommandId,                           ///< [in][range(0, numKernels)] command identifier
        ze_kernel_handle_t* phKernels                   ///< [in][range(0, numKernels)] handle of the kernel for a command
                                                        ///< identifier to switch to
        )
    {
        context.logger->log_trace("zeCommandListUpdateMutableCommandKernelsExp(hCommandList, numKernels, pCommandId, phKernelsLocal)");

        auto pfnUpdateMutableCommandKernelsExp = context.zeDdiTable.CommandListExp.pfnUpdateMutableCommandKernelsExp;

        if( nullptr == pfnUpdateMutableCommandKernelsExp )
            return logAndPropagateResult("zeCommandListUpdateMutableCommandKernelsExp", ZE_RESULT_ERROR_UNSUPPORTED_FEATURE);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListUpdateMutableCommandKernelsExpPrologue( hCommandList, numKernels, pCommandId, phKernels );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListUpdateMutableCommandKernelsExp", result);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListUpdateMutableCommandKernelsExpPrologue( hCommandList, numKernels, pCommandId, phKernels );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListUpdateMutableCommandKernelsExp", result);
        }

        auto driver_result = pfnUpdateMutableCommandKernelsExp( hCommandList, numKernels, pCommandId, phKernels );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zeValidation->zeCommandListUpdateMutableCommandKernelsExpEpilogue( hCommandList, numKernels, pCommandId, phKernels ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult("zeCommandListUpdateMutableCommandKernelsExp", result);
        }

        return logAndPropagateResult("zeCommandListUpdateMutableCommandKernelsExp", driver_result);
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
zeGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_global_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Global;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnInit                                     = pDdiTable->pfnInit;
        pDdiTable->pfnInit                                   = validation_layer::zeInit;
    }
    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnInitDrivers                              = pDdiTable->pfnInitDrivers;
        pDdiTable->pfnInitDrivers                            = validation_layer::zeInitDrivers;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's RTASBuilder table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetRTASBuilderProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_rtas_builder_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.RTASBuilder;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_13) {
        dditable.pfnCreateExt                                = pDdiTable->pfnCreateExt;
        pDdiTable->pfnCreateExt                              = validation_layer::zeRTASBuilderCreateExt;
    }
    if (version >= ZE_API_VERSION_1_13) {
        dditable.pfnGetBuildPropertiesExt                    = pDdiTable->pfnGetBuildPropertiesExt;
        pDdiTable->pfnGetBuildPropertiesExt                  = validation_layer::zeRTASBuilderGetBuildPropertiesExt;
    }
    if (version >= ZE_API_VERSION_1_13) {
        dditable.pfnBuildExt                                 = pDdiTable->pfnBuildExt;
        pDdiTable->pfnBuildExt                               = validation_layer::zeRTASBuilderBuildExt;
    }
    if (version >= ZE_API_VERSION_1_13) {
        dditable.pfnCommandListAppendCopyExt                 = pDdiTable->pfnCommandListAppendCopyExt;
        pDdiTable->pfnCommandListAppendCopyExt               = validation_layer::zeRTASBuilderCommandListAppendCopyExt;
    }
    if (version >= ZE_API_VERSION_1_13) {
        dditable.pfnDestroyExt                               = pDdiTable->pfnDestroyExt;
        pDdiTable->pfnDestroyExt                             = validation_layer::zeRTASBuilderDestroyExt;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's RTASBuilderExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetRTASBuilderExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_rtas_builder_exp_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.RTASBuilderExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnCreateExp                                = pDdiTable->pfnCreateExp;
        pDdiTable->pfnCreateExp                              = validation_layer::zeRTASBuilderCreateExp;
    }
    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnGetBuildPropertiesExp                    = pDdiTable->pfnGetBuildPropertiesExp;
        pDdiTable->pfnGetBuildPropertiesExp                  = validation_layer::zeRTASBuilderGetBuildPropertiesExp;
    }
    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnBuildExp                                 = pDdiTable->pfnBuildExp;
        pDdiTable->pfnBuildExp                               = validation_layer::zeRTASBuilderBuildExp;
    }
    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnDestroyExp                               = pDdiTable->pfnDestroyExp;
        pDdiTable->pfnDestroyExp                             = validation_layer::zeRTASBuilderDestroyExp;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's RTASParallelOperation table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetRTASParallelOperationProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_rtas_parallel_operation_dditable_t* pDdiTable///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.RTASParallelOperation;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_13) {
        dditable.pfnCreateExt                                = pDdiTable->pfnCreateExt;
        pDdiTable->pfnCreateExt                              = validation_layer::zeRTASParallelOperationCreateExt;
    }
    if (version >= ZE_API_VERSION_1_13) {
        dditable.pfnGetPropertiesExt                         = pDdiTable->pfnGetPropertiesExt;
        pDdiTable->pfnGetPropertiesExt                       = validation_layer::zeRTASParallelOperationGetPropertiesExt;
    }
    if (version >= ZE_API_VERSION_1_13) {
        dditable.pfnJoinExt                                  = pDdiTable->pfnJoinExt;
        pDdiTable->pfnJoinExt                                = validation_layer::zeRTASParallelOperationJoinExt;
    }
    if (version >= ZE_API_VERSION_1_13) {
        dditable.pfnDestroyExt                               = pDdiTable->pfnDestroyExt;
        pDdiTable->pfnDestroyExt                             = validation_layer::zeRTASParallelOperationDestroyExt;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's RTASParallelOperationExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetRTASParallelOperationExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_rtas_parallel_operation_exp_dditable_t* pDdiTable///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.RTASParallelOperationExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnCreateExp                                = pDdiTable->pfnCreateExp;
        pDdiTable->pfnCreateExp                              = validation_layer::zeRTASParallelOperationCreateExp;
    }
    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnGetPropertiesExp                         = pDdiTable->pfnGetPropertiesExp;
        pDdiTable->pfnGetPropertiesExp                       = validation_layer::zeRTASParallelOperationGetPropertiesExp;
    }
    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnJoinExp                                  = pDdiTable->pfnJoinExp;
        pDdiTable->pfnJoinExp                                = validation_layer::zeRTASParallelOperationJoinExp;
    }
    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnDestroyExp                               = pDdiTable->pfnDestroyExp;
        pDdiTable->pfnDestroyExp                             = validation_layer::zeRTASParallelOperationDestroyExp;
    }
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
zeGetDriverProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_driver_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Driver;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGet                                      = pDdiTable->pfnGet;
        pDdiTable->pfnGet                                    = validation_layer::zeDriverGet;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetApiVersion                            = pDdiTable->pfnGetApiVersion;
        pDdiTable->pfnGetApiVersion                          = validation_layer::zeDriverGetApiVersion;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zeDriverGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetIpcProperties                         = pDdiTable->pfnGetIpcProperties;
        pDdiTable->pfnGetIpcProperties                       = validation_layer::zeDriverGetIpcProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetExtensionProperties                   = pDdiTable->pfnGetExtensionProperties;
        pDdiTable->pfnGetExtensionProperties                 = validation_layer::zeDriverGetExtensionProperties;
    }
    if (version >= ZE_API_VERSION_1_1) {
        dditable.pfnGetExtensionFunctionAddress              = pDdiTable->pfnGetExtensionFunctionAddress;
        pDdiTable->pfnGetExtensionFunctionAddress            = validation_layer::zeDriverGetExtensionFunctionAddress;
    }
    if (version >= ZE_API_VERSION_1_13) {
        dditable.pfnRTASFormatCompatibilityCheckExt          = pDdiTable->pfnRTASFormatCompatibilityCheckExt;
        pDdiTable->pfnRTASFormatCompatibilityCheckExt        = validation_layer::zeDriverRTASFormatCompatibilityCheckExt;
    }
    if (version >= ZE_API_VERSION_1_6) {
        dditable.pfnGetLastErrorDescription                  = pDdiTable->pfnGetLastErrorDescription;
        pDdiTable->pfnGetLastErrorDescription                = validation_layer::zeDriverGetLastErrorDescription;
    }
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
zeGetDriverExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_driver_exp_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.DriverExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnRTASFormatCompatibilityCheckExp          = pDdiTable->pfnRTASFormatCompatibilityCheckExp;
        pDdiTable->pfnRTASFormatCompatibilityCheckExp        = validation_layer::zeDriverRTASFormatCompatibilityCheckExp;
    }
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
zeGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_device_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Device;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGet                                      = pDdiTable->pfnGet;
        pDdiTable->pfnGet                                    = validation_layer::zeDeviceGet;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetSubDevices                            = pDdiTable->pfnGetSubDevices;
        pDdiTable->pfnGetSubDevices                          = validation_layer::zeDeviceGetSubDevices;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zeDeviceGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetComputeProperties                     = pDdiTable->pfnGetComputeProperties;
        pDdiTable->pfnGetComputeProperties                   = validation_layer::zeDeviceGetComputeProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetModuleProperties                      = pDdiTable->pfnGetModuleProperties;
        pDdiTable->pfnGetModuleProperties                    = validation_layer::zeDeviceGetModuleProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetCommandQueueGroupProperties           = pDdiTable->pfnGetCommandQueueGroupProperties;
        pDdiTable->pfnGetCommandQueueGroupProperties         = validation_layer::zeDeviceGetCommandQueueGroupProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetMemoryProperties                      = pDdiTable->pfnGetMemoryProperties;
        pDdiTable->pfnGetMemoryProperties                    = validation_layer::zeDeviceGetMemoryProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetMemoryAccessProperties                = pDdiTable->pfnGetMemoryAccessProperties;
        pDdiTable->pfnGetMemoryAccessProperties              = validation_layer::zeDeviceGetMemoryAccessProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetCacheProperties                       = pDdiTable->pfnGetCacheProperties;
        pDdiTable->pfnGetCacheProperties                     = validation_layer::zeDeviceGetCacheProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetImageProperties                       = pDdiTable->pfnGetImageProperties;
        pDdiTable->pfnGetImageProperties                     = validation_layer::zeDeviceGetImageProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetExternalMemoryProperties              = pDdiTable->pfnGetExternalMemoryProperties;
        pDdiTable->pfnGetExternalMemoryProperties            = validation_layer::zeDeviceGetExternalMemoryProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetP2PProperties                         = pDdiTable->pfnGetP2PProperties;
        pDdiTable->pfnGetP2PProperties                       = validation_layer::zeDeviceGetP2PProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCanAccessPeer                            = pDdiTable->pfnCanAccessPeer;
        pDdiTable->pfnCanAccessPeer                          = validation_layer::zeDeviceCanAccessPeer;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetStatus                                = pDdiTable->pfnGetStatus;
        pDdiTable->pfnGetStatus                              = validation_layer::zeDeviceGetStatus;
    }
    if (version >= ZE_API_VERSION_1_1) {
        dditable.pfnGetGlobalTimestamps                      = pDdiTable->pfnGetGlobalTimestamps;
        pDdiTable->pfnGetGlobalTimestamps                    = validation_layer::zeDeviceGetGlobalTimestamps;
    }
    if (version >= ZE_API_VERSION_1_12) {
        dditable.pfnImportExternalSemaphoreExt               = pDdiTable->pfnImportExternalSemaphoreExt;
        pDdiTable->pfnImportExternalSemaphoreExt             = validation_layer::zeDeviceImportExternalSemaphoreExt;
    }
    if (version >= ZE_API_VERSION_1_12) {
        dditable.pfnReleaseExternalSemaphoreExt              = pDdiTable->pfnReleaseExternalSemaphoreExt;
        pDdiTable->pfnReleaseExternalSemaphoreExt            = validation_layer::zeDeviceReleaseExternalSemaphoreExt;
    }
    if (version >= ZE_API_VERSION_1_13) {
        dditable.pfnGetVectorWidthPropertiesExt              = pDdiTable->pfnGetVectorWidthPropertiesExt;
        pDdiTable->pfnGetVectorWidthPropertiesExt            = validation_layer::zeDeviceGetVectorWidthPropertiesExt;
    }
    if (version >= ZE_API_VERSION_1_2) {
        dditable.pfnReserveCacheExt                          = pDdiTable->pfnReserveCacheExt;
        pDdiTable->pfnReserveCacheExt                        = validation_layer::zeDeviceReserveCacheExt;
    }
    if (version >= ZE_API_VERSION_1_2) {
        dditable.pfnSetCacheAdviceExt                        = pDdiTable->pfnSetCacheAdviceExt;
        pDdiTable->pfnSetCacheAdviceExt                      = validation_layer::zeDeviceSetCacheAdviceExt;
    }
    if (version >= ZE_API_VERSION_1_3) {
        dditable.pfnPciGetPropertiesExt                      = pDdiTable->pfnPciGetPropertiesExt;
        pDdiTable->pfnPciGetPropertiesExt                    = validation_layer::zeDevicePciGetPropertiesExt;
    }
    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnGetRootDevice                            = pDdiTable->pfnGetRootDevice;
        pDdiTable->pfnGetRootDevice                          = validation_layer::zeDeviceGetRootDevice;
    }
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
zeGetDeviceExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_device_exp_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.DeviceExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_4) {
        dditable.pfnGetFabricVertexExp                       = pDdiTable->pfnGetFabricVertexExp;
        pDdiTable->pfnGetFabricVertexExp                     = validation_layer::zeDeviceGetFabricVertexExp;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Context table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetContextProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_context_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Context;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCreate                                   = pDdiTable->pfnCreate;
        pDdiTable->pfnCreate                                 = validation_layer::zeContextCreate;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
        pDdiTable->pfnDestroy                                = validation_layer::zeContextDestroy;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetStatus                                = pDdiTable->pfnGetStatus;
        pDdiTable->pfnGetStatus                              = validation_layer::zeContextGetStatus;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSystemBarrier                            = pDdiTable->pfnSystemBarrier;
        pDdiTable->pfnSystemBarrier                          = validation_layer::zeContextSystemBarrier;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnMakeMemoryResident                       = pDdiTable->pfnMakeMemoryResident;
        pDdiTable->pfnMakeMemoryResident                     = validation_layer::zeContextMakeMemoryResident;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEvictMemory                              = pDdiTable->pfnEvictMemory;
        pDdiTable->pfnEvictMemory                            = validation_layer::zeContextEvictMemory;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnMakeImageResident                        = pDdiTable->pfnMakeImageResident;
        pDdiTable->pfnMakeImageResident                      = validation_layer::zeContextMakeImageResident;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEvictImage                               = pDdiTable->pfnEvictImage;
        pDdiTable->pfnEvictImage                             = validation_layer::zeContextEvictImage;
    }
    if (version >= ZE_API_VERSION_1_1) {
        dditable.pfnCreateEx                                 = pDdiTable->pfnCreateEx;
        pDdiTable->pfnCreateEx                               = validation_layer::zeContextCreateEx;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandQueue table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetCommandQueueProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_queue_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.CommandQueue;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCreate                                   = pDdiTable->pfnCreate;
        pDdiTable->pfnCreate                                 = validation_layer::zeCommandQueueCreate;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
        pDdiTable->pfnDestroy                                = validation_layer::zeCommandQueueDestroy;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnExecuteCommandLists                      = pDdiTable->pfnExecuteCommandLists;
        pDdiTable->pfnExecuteCommandLists                    = validation_layer::zeCommandQueueExecuteCommandLists;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSynchronize                              = pDdiTable->pfnSynchronize;
        pDdiTable->pfnSynchronize                            = validation_layer::zeCommandQueueSynchronize;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetOrdinal                               = pDdiTable->pfnGetOrdinal;
        pDdiTable->pfnGetOrdinal                             = validation_layer::zeCommandQueueGetOrdinal;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetIndex                                 = pDdiTable->pfnGetIndex;
        pDdiTable->pfnGetIndex                               = validation_layer::zeCommandQueueGetIndex;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_list_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.CommandList;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCreate                                   = pDdiTable->pfnCreate;
        pDdiTable->pfnCreate                                 = validation_layer::zeCommandListCreate;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCreateImmediate                          = pDdiTable->pfnCreateImmediate;
        pDdiTable->pfnCreateImmediate                        = validation_layer::zeCommandListCreateImmediate;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
        pDdiTable->pfnDestroy                                = validation_layer::zeCommandListDestroy;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnClose                                    = pDdiTable->pfnClose;
        pDdiTable->pfnClose                                  = validation_layer::zeCommandListClose;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnReset                                    = pDdiTable->pfnReset;
        pDdiTable->pfnReset                                  = validation_layer::zeCommandListReset;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendWriteGlobalTimestamp               = pDdiTable->pfnAppendWriteGlobalTimestamp;
        pDdiTable->pfnAppendWriteGlobalTimestamp             = validation_layer::zeCommandListAppendWriteGlobalTimestamp;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendBarrier                            = pDdiTable->pfnAppendBarrier;
        pDdiTable->pfnAppendBarrier                          = validation_layer::zeCommandListAppendBarrier;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendMemoryRangesBarrier                = pDdiTable->pfnAppendMemoryRangesBarrier;
        pDdiTable->pfnAppendMemoryRangesBarrier              = validation_layer::zeCommandListAppendMemoryRangesBarrier;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendMemoryCopy                         = pDdiTable->pfnAppendMemoryCopy;
        pDdiTable->pfnAppendMemoryCopy                       = validation_layer::zeCommandListAppendMemoryCopy;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendMemoryFill                         = pDdiTable->pfnAppendMemoryFill;
        pDdiTable->pfnAppendMemoryFill                       = validation_layer::zeCommandListAppendMemoryFill;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendMemoryCopyRegion                   = pDdiTable->pfnAppendMemoryCopyRegion;
        pDdiTable->pfnAppendMemoryCopyRegion                 = validation_layer::zeCommandListAppendMemoryCopyRegion;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendMemoryCopyFromContext              = pDdiTable->pfnAppendMemoryCopyFromContext;
        pDdiTable->pfnAppendMemoryCopyFromContext            = validation_layer::zeCommandListAppendMemoryCopyFromContext;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendImageCopy                          = pDdiTable->pfnAppendImageCopy;
        pDdiTable->pfnAppendImageCopy                        = validation_layer::zeCommandListAppendImageCopy;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendImageCopyRegion                    = pDdiTable->pfnAppendImageCopyRegion;
        pDdiTable->pfnAppendImageCopyRegion                  = validation_layer::zeCommandListAppendImageCopyRegion;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendImageCopyToMemory                  = pDdiTable->pfnAppendImageCopyToMemory;
        pDdiTable->pfnAppendImageCopyToMemory                = validation_layer::zeCommandListAppendImageCopyToMemory;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendImageCopyFromMemory                = pDdiTable->pfnAppendImageCopyFromMemory;
        pDdiTable->pfnAppendImageCopyFromMemory              = validation_layer::zeCommandListAppendImageCopyFromMemory;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendMemoryPrefetch                     = pDdiTable->pfnAppendMemoryPrefetch;
        pDdiTable->pfnAppendMemoryPrefetch                   = validation_layer::zeCommandListAppendMemoryPrefetch;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendMemAdvise                          = pDdiTable->pfnAppendMemAdvise;
        pDdiTable->pfnAppendMemAdvise                        = validation_layer::zeCommandListAppendMemAdvise;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendSignalEvent                        = pDdiTable->pfnAppendSignalEvent;
        pDdiTable->pfnAppendSignalEvent                      = validation_layer::zeCommandListAppendSignalEvent;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendWaitOnEvents                       = pDdiTable->pfnAppendWaitOnEvents;
        pDdiTable->pfnAppendWaitOnEvents                     = validation_layer::zeCommandListAppendWaitOnEvents;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendEventReset                         = pDdiTable->pfnAppendEventReset;
        pDdiTable->pfnAppendEventReset                       = validation_layer::zeCommandListAppendEventReset;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendQueryKernelTimestamps              = pDdiTable->pfnAppendQueryKernelTimestamps;
        pDdiTable->pfnAppendQueryKernelTimestamps            = validation_layer::zeCommandListAppendQueryKernelTimestamps;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendLaunchKernel                       = pDdiTable->pfnAppendLaunchKernel;
        pDdiTable->pfnAppendLaunchKernel                     = validation_layer::zeCommandListAppendLaunchKernel;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendLaunchCooperativeKernel            = pDdiTable->pfnAppendLaunchCooperativeKernel;
        pDdiTable->pfnAppendLaunchCooperativeKernel          = validation_layer::zeCommandListAppendLaunchCooperativeKernel;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendLaunchKernelIndirect               = pDdiTable->pfnAppendLaunchKernelIndirect;
        pDdiTable->pfnAppendLaunchKernelIndirect             = validation_layer::zeCommandListAppendLaunchKernelIndirect;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendLaunchMultipleKernelsIndirect      = pDdiTable->pfnAppendLaunchMultipleKernelsIndirect;
        pDdiTable->pfnAppendLaunchMultipleKernelsIndirect    = validation_layer::zeCommandListAppendLaunchMultipleKernelsIndirect;
    }
    if (version >= ZE_API_VERSION_1_12) {
        dditable.pfnAppendSignalExternalSemaphoreExt         = pDdiTable->pfnAppendSignalExternalSemaphoreExt;
        pDdiTable->pfnAppendSignalExternalSemaphoreExt       = validation_layer::zeCommandListAppendSignalExternalSemaphoreExt;
    }
    if (version >= ZE_API_VERSION_1_12) {
        dditable.pfnAppendWaitExternalSemaphoreExt           = pDdiTable->pfnAppendWaitExternalSemaphoreExt;
        pDdiTable->pfnAppendWaitExternalSemaphoreExt         = validation_layer::zeCommandListAppendWaitExternalSemaphoreExt;
    }
    if (version >= ZE_API_VERSION_1_3) {
        dditable.pfnAppendImageCopyToMemoryExt               = pDdiTable->pfnAppendImageCopyToMemoryExt;
        pDdiTable->pfnAppendImageCopyToMemoryExt             = validation_layer::zeCommandListAppendImageCopyToMemoryExt;
    }
    if (version >= ZE_API_VERSION_1_3) {
        dditable.pfnAppendImageCopyFromMemoryExt             = pDdiTable->pfnAppendImageCopyFromMemoryExt;
        pDdiTable->pfnAppendImageCopyFromMemoryExt           = validation_layer::zeCommandListAppendImageCopyFromMemoryExt;
    }
    if (version >= ZE_API_VERSION_1_6) {
        dditable.pfnHostSynchronize                          = pDdiTable->pfnHostSynchronize;
        pDdiTable->pfnHostSynchronize                        = validation_layer::zeCommandListHostSynchronize;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetDeviceHandle                          = pDdiTable->pfnGetDeviceHandle;
        pDdiTable->pfnGetDeviceHandle                        = validation_layer::zeCommandListGetDeviceHandle;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetContextHandle                         = pDdiTable->pfnGetContextHandle;
        pDdiTable->pfnGetContextHandle                       = validation_layer::zeCommandListGetContextHandle;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetOrdinal                               = pDdiTable->pfnGetOrdinal;
        pDdiTable->pfnGetOrdinal                             = validation_layer::zeCommandListGetOrdinal;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnImmediateGetIndex                        = pDdiTable->pfnImmediateGetIndex;
        pDdiTable->pfnImmediateGetIndex                      = validation_layer::zeCommandListImmediateGetIndex;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnIsImmediate                              = pDdiTable->pfnIsImmediate;
        pDdiTable->pfnIsImmediate                            = validation_layer::zeCommandListIsImmediate;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandListExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetCommandListExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_command_list_exp_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.CommandListExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnGetNextCommandIdWithKernelsExp           = pDdiTable->pfnGetNextCommandIdWithKernelsExp;
        pDdiTable->pfnGetNextCommandIdWithKernelsExp         = validation_layer::zeCommandListGetNextCommandIdWithKernelsExp;
    }
    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnUpdateMutableCommandKernelsExp           = pDdiTable->pfnUpdateMutableCommandKernelsExp;
        pDdiTable->pfnUpdateMutableCommandKernelsExp         = validation_layer::zeCommandListUpdateMutableCommandKernelsExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnCreateCloneExp                           = pDdiTable->pfnCreateCloneExp;
        pDdiTable->pfnCreateCloneExp                         = validation_layer::zeCommandListCreateCloneExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnImmediateAppendCommandListsExp           = pDdiTable->pfnImmediateAppendCommandListsExp;
        pDdiTable->pfnImmediateAppendCommandListsExp         = validation_layer::zeCommandListImmediateAppendCommandListsExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetNextCommandIdExp                      = pDdiTable->pfnGetNextCommandIdExp;
        pDdiTable->pfnGetNextCommandIdExp                    = validation_layer::zeCommandListGetNextCommandIdExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnUpdateMutableCommandsExp                 = pDdiTable->pfnUpdateMutableCommandsExp;
        pDdiTable->pfnUpdateMutableCommandsExp               = validation_layer::zeCommandListUpdateMutableCommandsExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnUpdateMutableCommandSignalEventExp       = pDdiTable->pfnUpdateMutableCommandSignalEventExp;
        pDdiTable->pfnUpdateMutableCommandSignalEventExp     = validation_layer::zeCommandListUpdateMutableCommandSignalEventExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnUpdateMutableCommandWaitEventsExp        = pDdiTable->pfnUpdateMutableCommandWaitEventsExp;
        pDdiTable->pfnUpdateMutableCommandWaitEventsExp      = validation_layer::zeCommandListUpdateMutableCommandWaitEventsExp;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Event table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetEventProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Event;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCreate                                   = pDdiTable->pfnCreate;
        pDdiTable->pfnCreate                                 = validation_layer::zeEventCreate;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
        pDdiTable->pfnDestroy                                = validation_layer::zeEventDestroy;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnHostSignal                               = pDdiTable->pfnHostSignal;
        pDdiTable->pfnHostSignal                             = validation_layer::zeEventHostSignal;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnHostSynchronize                          = pDdiTable->pfnHostSynchronize;
        pDdiTable->pfnHostSynchronize                        = validation_layer::zeEventHostSynchronize;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnQueryStatus                              = pDdiTable->pfnQueryStatus;
        pDdiTable->pfnQueryStatus                            = validation_layer::zeEventQueryStatus;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnHostReset                                = pDdiTable->pfnHostReset;
        pDdiTable->pfnHostReset                              = validation_layer::zeEventHostReset;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnQueryKernelTimestamp                     = pDdiTable->pfnQueryKernelTimestamp;
        pDdiTable->pfnQueryKernelTimestamp                   = validation_layer::zeEventQueryKernelTimestamp;
    }
    if (version >= ZE_API_VERSION_1_6) {
        dditable.pfnQueryKernelTimestampsExt                 = pDdiTable->pfnQueryKernelTimestampsExt;
        pDdiTable->pfnQueryKernelTimestampsExt               = validation_layer::zeEventQueryKernelTimestampsExt;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetEventPool                             = pDdiTable->pfnGetEventPool;
        pDdiTable->pfnGetEventPool                           = validation_layer::zeEventGetEventPool;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetSignalScope                           = pDdiTable->pfnGetSignalScope;
        pDdiTable->pfnGetSignalScope                         = validation_layer::zeEventGetSignalScope;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetWaitScope                             = pDdiTable->pfnGetWaitScope;
        pDdiTable->pfnGetWaitScope                           = validation_layer::zeEventGetWaitScope;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetEventExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_exp_dditable_t* pDdiTable              ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.EventExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_2) {
        dditable.pfnQueryTimestampsExp                       = pDdiTable->pfnQueryTimestampsExp;
        pDdiTable->pfnQueryTimestampsExp                     = validation_layer::zeEventQueryTimestampsExp;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventPool table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetEventPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_event_pool_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.EventPool;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCreate                                   = pDdiTable->pfnCreate;
        pDdiTable->pfnCreate                                 = validation_layer::zeEventPoolCreate;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
        pDdiTable->pfnDestroy                                = validation_layer::zeEventPoolDestroy;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetIpcHandle                             = pDdiTable->pfnGetIpcHandle;
        pDdiTable->pfnGetIpcHandle                           = validation_layer::zeEventPoolGetIpcHandle;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnOpenIpcHandle                            = pDdiTable->pfnOpenIpcHandle;
        pDdiTable->pfnOpenIpcHandle                          = validation_layer::zeEventPoolOpenIpcHandle;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCloseIpcHandle                           = pDdiTable->pfnCloseIpcHandle;
        pDdiTable->pfnCloseIpcHandle                         = validation_layer::zeEventPoolCloseIpcHandle;
    }
    if (version >= ZE_API_VERSION_1_6) {
        dditable.pfnPutIpcHandle                             = pDdiTable->pfnPutIpcHandle;
        pDdiTable->pfnPutIpcHandle                           = validation_layer::zeEventPoolPutIpcHandle;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetContextHandle                         = pDdiTable->pfnGetContextHandle;
        pDdiTable->pfnGetContextHandle                       = validation_layer::zeEventPoolGetContextHandle;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetFlags                                 = pDdiTable->pfnGetFlags;
        pDdiTable->pfnGetFlags                               = validation_layer::zeEventPoolGetFlags;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fence table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetFenceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_fence_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Fence;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCreate                                   = pDdiTable->pfnCreate;
        pDdiTable->pfnCreate                                 = validation_layer::zeFenceCreate;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
        pDdiTable->pfnDestroy                                = validation_layer::zeFenceDestroy;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnHostSynchronize                          = pDdiTable->pfnHostSynchronize;
        pDdiTable->pfnHostSynchronize                        = validation_layer::zeFenceHostSynchronize;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnQueryStatus                              = pDdiTable->pfnQueryStatus;
        pDdiTable->pfnQueryStatus                            = validation_layer::zeFenceQueryStatus;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnReset                                    = pDdiTable->pfnReset;
        pDdiTable->pfnReset                                  = validation_layer::zeFenceReset;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Image table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetImageProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_image_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Image;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zeImageGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCreate                                   = pDdiTable->pfnCreate;
        pDdiTable->pfnCreate                                 = validation_layer::zeImageCreate;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
        pDdiTable->pfnDestroy                                = validation_layer::zeImageDestroy;
    }
    if (version >= ZE_API_VERSION_1_3) {
        dditable.pfnGetAllocPropertiesExt                    = pDdiTable->pfnGetAllocPropertiesExt;
        pDdiTable->pfnGetAllocPropertiesExt                  = validation_layer::zeImageGetAllocPropertiesExt;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnViewCreateExt                            = pDdiTable->pfnViewCreateExt;
        pDdiTable->pfnViewCreateExt                          = validation_layer::zeImageViewCreateExt;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ImageExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetImageExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_image_exp_dditable_t* pDdiTable              ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.ImageExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_2) {
        dditable.pfnGetMemoryPropertiesExp                   = pDdiTable->pfnGetMemoryPropertiesExp;
        pDdiTable->pfnGetMemoryPropertiesExp                 = validation_layer::zeImageGetMemoryPropertiesExp;
    }
    if (version >= ZE_API_VERSION_1_2) {
        dditable.pfnViewCreateExp                            = pDdiTable->pfnViewCreateExp;
        pDdiTable->pfnViewCreateExp                          = validation_layer::zeImageViewCreateExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetDeviceOffsetExp                       = pDdiTable->pfnGetDeviceOffsetExp;
        pDdiTable->pfnGetDeviceOffsetExp                     = validation_layer::zeImageGetDeviceOffsetExp;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Kernel table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_kernel_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Kernel;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCreate                                   = pDdiTable->pfnCreate;
        pDdiTable->pfnCreate                                 = validation_layer::zeKernelCreate;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
        pDdiTable->pfnDestroy                                = validation_layer::zeKernelDestroy;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetCacheConfig                           = pDdiTable->pfnSetCacheConfig;
        pDdiTable->pfnSetCacheConfig                         = validation_layer::zeKernelSetCacheConfig;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetGroupSize                             = pDdiTable->pfnSetGroupSize;
        pDdiTable->pfnSetGroupSize                           = validation_layer::zeKernelSetGroupSize;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSuggestGroupSize                         = pDdiTable->pfnSuggestGroupSize;
        pDdiTable->pfnSuggestGroupSize                       = validation_layer::zeKernelSuggestGroupSize;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSuggestMaxCooperativeGroupCount          = pDdiTable->pfnSuggestMaxCooperativeGroupCount;
        pDdiTable->pfnSuggestMaxCooperativeGroupCount        = validation_layer::zeKernelSuggestMaxCooperativeGroupCount;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetArgumentValue                         = pDdiTable->pfnSetArgumentValue;
        pDdiTable->pfnSetArgumentValue                       = validation_layer::zeKernelSetArgumentValue;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetIndirectAccess                        = pDdiTable->pfnSetIndirectAccess;
        pDdiTable->pfnSetIndirectAccess                      = validation_layer::zeKernelSetIndirectAccess;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetIndirectAccess                        = pDdiTable->pfnGetIndirectAccess;
        pDdiTable->pfnGetIndirectAccess                      = validation_layer::zeKernelGetIndirectAccess;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetSourceAttributes                      = pDdiTable->pfnGetSourceAttributes;
        pDdiTable->pfnGetSourceAttributes                    = validation_layer::zeKernelGetSourceAttributes;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zeKernelGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetName                                  = pDdiTable->pfnGetName;
        pDdiTable->pfnGetName                                = validation_layer::zeKernelGetName;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's KernelExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetKernelExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_kernel_exp_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.KernelExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_1) {
        dditable.pfnSetGlobalOffsetExp                       = pDdiTable->pfnSetGlobalOffsetExp;
        pDdiTable->pfnSetGlobalOffsetExp                     = validation_layer::zeKernelSetGlobalOffsetExp;
    }
    if (version >= ZE_API_VERSION_1_11) {
        dditable.pfnGetBinaryExp                             = pDdiTable->pfnGetBinaryExp;
        pDdiTable->pfnGetBinaryExp                           = validation_layer::zeKernelGetBinaryExp;
    }
    if (version >= ZE_API_VERSION_1_2) {
        dditable.pfnSchedulingHintExp                        = pDdiTable->pfnSchedulingHintExp;
        pDdiTable->pfnSchedulingHintExp                      = validation_layer::zeKernelSchedulingHintExp;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Mem table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetMemProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_mem_dditable_t* pDdiTable                    ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Mem;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAllocShared                              = pDdiTable->pfnAllocShared;
        pDdiTable->pfnAllocShared                            = validation_layer::zeMemAllocShared;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAllocDevice                              = pDdiTable->pfnAllocDevice;
        pDdiTable->pfnAllocDevice                            = validation_layer::zeMemAllocDevice;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAllocHost                                = pDdiTable->pfnAllocHost;
        pDdiTable->pfnAllocHost                              = validation_layer::zeMemAllocHost;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnFree                                     = pDdiTable->pfnFree;
        pDdiTable->pfnFree                                   = validation_layer::zeMemFree;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetAllocProperties                       = pDdiTable->pfnGetAllocProperties;
        pDdiTable->pfnGetAllocProperties                     = validation_layer::zeMemGetAllocProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetAddressRange                          = pDdiTable->pfnGetAddressRange;
        pDdiTable->pfnGetAddressRange                        = validation_layer::zeMemGetAddressRange;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetIpcHandle                             = pDdiTable->pfnGetIpcHandle;
        pDdiTable->pfnGetIpcHandle                           = validation_layer::zeMemGetIpcHandle;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnOpenIpcHandle                            = pDdiTable->pfnOpenIpcHandle;
        pDdiTable->pfnOpenIpcHandle                          = validation_layer::zeMemOpenIpcHandle;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCloseIpcHandle                           = pDdiTable->pfnCloseIpcHandle;
        pDdiTable->pfnCloseIpcHandle                         = validation_layer::zeMemCloseIpcHandle;
    }
    if (version >= ZE_API_VERSION_1_3) {
        dditable.pfnFreeExt                                  = pDdiTable->pfnFreeExt;
        pDdiTable->pfnFreeExt                                = validation_layer::zeMemFreeExt;
    }
    if (version >= ZE_API_VERSION_1_6) {
        dditable.pfnPutIpcHandle                             = pDdiTable->pfnPutIpcHandle;
        pDdiTable->pfnPutIpcHandle                           = validation_layer::zeMemPutIpcHandle;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetPitchFor2dImage                       = pDdiTable->pfnGetPitchFor2dImage;
        pDdiTable->pfnGetPitchFor2dImage                     = validation_layer::zeMemGetPitchFor2dImage;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MemExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetMemExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_mem_exp_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.MemExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_6) {
        dditable.pfnGetIpcHandleFromFileDescriptorExp        = pDdiTable->pfnGetIpcHandleFromFileDescriptorExp;
        pDdiTable->pfnGetIpcHandleFromFileDescriptorExp      = validation_layer::zeMemGetIpcHandleFromFileDescriptorExp;
    }
    if (version >= ZE_API_VERSION_1_6) {
        dditable.pfnGetFileDescriptorFromIpcHandleExp        = pDdiTable->pfnGetFileDescriptorFromIpcHandleExp;
        pDdiTable->pfnGetFileDescriptorFromIpcHandleExp      = validation_layer::zeMemGetFileDescriptorFromIpcHandleExp;
    }
    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnSetAtomicAccessAttributeExp              = pDdiTable->pfnSetAtomicAccessAttributeExp;
        pDdiTable->pfnSetAtomicAccessAttributeExp            = validation_layer::zeMemSetAtomicAccessAttributeExp;
    }
    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnGetAtomicAccessAttributeExp              = pDdiTable->pfnGetAtomicAccessAttributeExp;
        pDdiTable->pfnGetAtomicAccessAttributeExp            = validation_layer::zeMemGetAtomicAccessAttributeExp;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Module;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCreate                                   = pDdiTable->pfnCreate;
        pDdiTable->pfnCreate                                 = validation_layer::zeModuleCreate;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
        pDdiTable->pfnDestroy                                = validation_layer::zeModuleDestroy;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDynamicLink                              = pDdiTable->pfnDynamicLink;
        pDdiTable->pfnDynamicLink                            = validation_layer::zeModuleDynamicLink;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetNativeBinary                          = pDdiTable->pfnGetNativeBinary;
        pDdiTable->pfnGetNativeBinary                        = validation_layer::zeModuleGetNativeBinary;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetGlobalPointer                         = pDdiTable->pfnGetGlobalPointer;
        pDdiTable->pfnGetGlobalPointer                       = validation_layer::zeModuleGetGlobalPointer;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetKernelNames                           = pDdiTable->pfnGetKernelNames;
        pDdiTable->pfnGetKernelNames                         = validation_layer::zeModuleGetKernelNames;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zeModuleGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetFunctionPointer                       = pDdiTable->pfnGetFunctionPointer;
        pDdiTable->pfnGetFunctionPointer                     = validation_layer::zeModuleGetFunctionPointer;
    }
    if (version >= ZE_API_VERSION_1_3) {
        dditable.pfnInspectLinkageExt                        = pDdiTable->pfnInspectLinkageExt;
        pDdiTable->pfnInspectLinkageExt                      = validation_layer::zeModuleInspectLinkageExt;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ModuleBuildLog table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetModuleBuildLogProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_module_build_log_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.ModuleBuildLog;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
        pDdiTable->pfnDestroy                                = validation_layer::zeModuleBuildLogDestroy;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetString                                = pDdiTable->pfnGetString;
        pDdiTable->pfnGetString                              = validation_layer::zeModuleBuildLogGetString;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's PhysicalMem table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetPhysicalMemProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_physical_mem_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.PhysicalMem;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCreate                                   = pDdiTable->pfnCreate;
        pDdiTable->pfnCreate                                 = validation_layer::zePhysicalMemCreate;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
        pDdiTable->pfnDestroy                                = validation_layer::zePhysicalMemDestroy;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sampler table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetSamplerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_sampler_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Sampler;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCreate                                   = pDdiTable->pfnCreate;
        pDdiTable->pfnCreate                                 = validation_layer::zeSamplerCreate;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
        pDdiTable->pfnDestroy                                = validation_layer::zeSamplerDestroy;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's VirtualMem table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetVirtualMemProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_virtual_mem_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.VirtualMem;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnReserve                                  = pDdiTable->pfnReserve;
        pDdiTable->pfnReserve                                = validation_layer::zeVirtualMemReserve;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnFree                                     = pDdiTable->pfnFree;
        pDdiTable->pfnFree                                   = validation_layer::zeVirtualMemFree;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnQueryPageSize                            = pDdiTable->pfnQueryPageSize;
        pDdiTable->pfnQueryPageSize                          = validation_layer::zeVirtualMemQueryPageSize;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnMap                                      = pDdiTable->pfnMap;
        pDdiTable->pfnMap                                    = validation_layer::zeVirtualMemMap;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnUnmap                                    = pDdiTable->pfnUnmap;
        pDdiTable->pfnUnmap                                  = validation_layer::zeVirtualMemUnmap;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetAccessAttribute                       = pDdiTable->pfnSetAccessAttribute;
        pDdiTable->pfnSetAccessAttribute                     = validation_layer::zeVirtualMemSetAccessAttribute;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetAccessAttribute                       = pDdiTable->pfnGetAccessAttribute;
        pDdiTable->pfnGetAccessAttribute                     = validation_layer::zeVirtualMemGetAccessAttribute;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FabricEdgeExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetFabricEdgeExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_fabric_edge_exp_dditable_t* pDdiTable        ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.FabricEdgeExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_4) {
        dditable.pfnGetExp                                   = pDdiTable->pfnGetExp;
        pDdiTable->pfnGetExp                                 = validation_layer::zeFabricEdgeGetExp;
    }
    if (version >= ZE_API_VERSION_1_4) {
        dditable.pfnGetVerticesExp                           = pDdiTable->pfnGetVerticesExp;
        pDdiTable->pfnGetVerticesExp                         = validation_layer::zeFabricEdgeGetVerticesExp;
    }
    if (version >= ZE_API_VERSION_1_4) {
        dditable.pfnGetPropertiesExp                         = pDdiTable->pfnGetPropertiesExp;
        pDdiTable->pfnGetPropertiesExp                       = validation_layer::zeFabricEdgeGetPropertiesExp;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's FabricVertexExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zeGetFabricVertexExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_fabric_vertex_exp_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.FabricVertexExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_4) {
        dditable.pfnGetExp                                   = pDdiTable->pfnGetExp;
        pDdiTable->pfnGetExp                                 = validation_layer::zeFabricVertexGetExp;
    }
    if (version >= ZE_API_VERSION_1_4) {
        dditable.pfnGetSubVerticesExp                        = pDdiTable->pfnGetSubVerticesExp;
        pDdiTable->pfnGetSubVerticesExp                      = validation_layer::zeFabricVertexGetSubVerticesExp;
    }
    if (version >= ZE_API_VERSION_1_4) {
        dditable.pfnGetPropertiesExp                         = pDdiTable->pfnGetPropertiesExp;
        pDdiTable->pfnGetPropertiesExp                       = validation_layer::zeFabricVertexGetPropertiesExp;
    }
    if (version >= ZE_API_VERSION_1_4) {
        dditable.pfnGetDeviceExp                             = pDdiTable->pfnGetDeviceExp;
        pDdiTable->pfnGetDeviceExp                           = validation_layer::zeFabricVertexGetDeviceExp;
    }
    return result;
}

#if defined(__cplusplus)
};
#endif
