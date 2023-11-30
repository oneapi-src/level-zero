/*
 * ***THIS FILE IS GENERATED. ***
 * See valddi.cpp.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_valddi.cpp
 *
 */
#include "ze_validation_layer.h"

namespace validation_layer
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeInit
    __zedlllocal ze_result_t ZE_APICALL
    zeInit(
        ze_init_flags_t flags                           ///< [in] initialization flags.
                                                        ///< must be 0 (default) or a combination of ::ze_init_flag_t.
        )
    {
        auto pfnInit = context.zeDdiTable.Global.pfnInit;

        if( nullptr == pfnInit )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeInit( flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeInit( flags );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnInit( flags );
        return result;
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
        auto pfnGet = context.zeDdiTable.Driver.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverGet( pCount, phDrivers );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGet( pCount, phDrivers );
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
    /// @brief Intercept function for zeDriverGetApiVersion
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetApiVersion(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_api_version_t* version                       ///< [out] api version
        )
    {
        auto pfnGetApiVersion = context.zeDdiTable.Driver.pfnGetApiVersion;

        if( nullptr == pfnGetApiVersion )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverGetApiVersion( hDriver, version );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetApiVersion( hDriver, version );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetApiVersion( hDriver, version );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_properties_t* pDriverProperties       ///< [in,out] query result for driver properties
        )
    {
        auto pfnGetProperties = context.zeDdiTable.Driver.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverGetProperties( hDriver, pDriverProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetProperties( hDriver, pDriverProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hDriver, pDriverProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDriverGetIpcProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDriverGetIpcProperties(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        ze_driver_ipc_properties_t* pIpcProperties      ///< [in,out] query result for IPC properties
        )
    {
        auto pfnGetIpcProperties = context.zeDdiTable.Driver.pfnGetIpcProperties;

        if( nullptr == pfnGetIpcProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverGetIpcProperties( hDriver, pIpcProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetIpcProperties( hDriver, pIpcProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetIpcProperties( hDriver, pIpcProperties );
        return result;
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
        auto pfnGetExtensionProperties = context.zeDdiTable.Driver.pfnGetExtensionProperties;

        if( nullptr == pfnGetExtensionProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverGetExtensionProperties( hDriver, pCount, pExtensionProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetExtensionProperties( hDriver, pCount, pExtensionProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetExtensionProperties( hDriver, pCount, pExtensionProperties );
        return result;
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
        auto pfnGetExtensionFunctionAddress = context.zeDdiTable.Driver.pfnGetExtensionFunctionAddress;

        if( nullptr == pfnGetExtensionFunctionAddress )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );
        return result;
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
        auto pfnGetLastErrorDescription = context.zeDdiTable.Driver.pfnGetLastErrorDescription;

        if( nullptr == pfnGetLastErrorDescription )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverGetLastErrorDescription( hDriver, ppString );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverGetLastErrorDescription( hDriver, ppString );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetLastErrorDescription( hDriver, ppString );
        return result;
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
        auto pfnGet = context.zeDdiTable.Device.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGet( hDriver, pCount, phDevices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGet( hDriver, pCount, phDevices );
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
    /// @brief Intercept function for zeDeviceGetRootDevice
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetRootDevice(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        ze_device_handle_t* phRootDevice                ///< [in,out] parent root device.
        )
    {
        auto pfnGetRootDevice = context.zeDdiTable.Device.pfnGetRootDevice;

        if( nullptr == pfnGetRootDevice )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetRootDevice( hDevice, phRootDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetRootDevice( hDevice, phRootDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetRootDevice( hDevice, phRootDevice );
        return result;
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
        auto pfnGetSubDevices = context.zeDdiTable.Device.pfnGetSubDevices;

        if( nullptr == pfnGetSubDevices )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetSubDevices( hDevice, pCount, phSubdevices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetSubDevices( hDevice, pCount, phSubdevices );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetSubDevices( hDevice, pCount, phSubdevices );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phSubdevices) && (i < *pCount); ++i){
                if (phSubdevices[i]){
                    context.handleLifetime->addHandle( phSubdevices[i] );
                    context.handleLifetime->addDependent( hDevice, phSubdevices[i] );
                }
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_properties_t* pDeviceProperties       ///< [in,out] query result for device properties
        )
    {
        auto pfnGetProperties = context.zeDdiTable.Device.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetProperties( hDevice, pDeviceProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetProperties( hDevice, pDeviceProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hDevice, pDeviceProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetComputeProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetComputeProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_compute_properties_t* pComputeProperties  ///< [in,out] query result for compute properties
        )
    {
        auto pfnGetComputeProperties = context.zeDdiTable.Device.pfnGetComputeProperties;

        if( nullptr == pfnGetComputeProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetComputeProperties( hDevice, pComputeProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetComputeProperties( hDevice, pComputeProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetComputeProperties( hDevice, pComputeProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetModuleProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetModuleProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_module_properties_t* pModuleProperties///< [in,out] query result for module properties
        )
    {
        auto pfnGetModuleProperties = context.zeDdiTable.Device.pfnGetModuleProperties;

        if( nullptr == pfnGetModuleProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetModuleProperties( hDevice, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetModuleProperties( hDevice, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetModuleProperties( hDevice, pModuleProperties );
        return result;
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
        auto pfnGetCommandQueueGroupProperties = context.zeDdiTable.Device.pfnGetCommandQueueGroupProperties;

        if( nullptr == pfnGetCommandQueueGroupProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetCommandQueueGroupProperties( hDevice, pCount, pCommandQueueGroupProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetCommandQueueGroupProperties( hDevice, pCount, pCommandQueueGroupProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetCommandQueueGroupProperties( hDevice, pCount, pCommandQueueGroupProperties );
        return result;
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
        auto pfnGetMemoryProperties = context.zeDdiTable.Device.pfnGetMemoryProperties;

        if( nullptr == pfnGetMemoryProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetMemoryProperties( hDevice, pCount, pMemProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetMemoryProperties( hDevice, pCount, pMemProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetMemoryProperties( hDevice, pCount, pMemProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetMemoryAccessProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetMemoryAccessProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_memory_access_properties_t* pMemAccessProperties  ///< [in,out] query result for memory access properties
        )
    {
        auto pfnGetMemoryAccessProperties = context.zeDdiTable.Device.pfnGetMemoryAccessProperties;

        if( nullptr == pfnGetMemoryAccessProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetMemoryAccessProperties( hDevice, pMemAccessProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetMemoryAccessProperties( hDevice, pMemAccessProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetMemoryAccessProperties( hDevice, pMemAccessProperties );
        return result;
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
        auto pfnGetCacheProperties = context.zeDdiTable.Device.pfnGetCacheProperties;

        if( nullptr == pfnGetCacheProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetCacheProperties( hDevice, pCount, pCacheProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetCacheProperties( hDevice, pCount, pCacheProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetCacheProperties( hDevice, pCount, pCacheProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetImageProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetImageProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_image_properties_t* pImageProperties  ///< [in,out] query result for image properties
        )
    {
        auto pfnGetImageProperties = context.zeDdiTable.Device.pfnGetImageProperties;

        if( nullptr == pfnGetImageProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetImageProperties( hDevice, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetImageProperties( hDevice, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetImageProperties( hDevice, pImageProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetExternalMemoryProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetExternalMemoryProperties(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_device_external_memory_properties_t* pExternalMemoryProperties   ///< [in,out] query result for external memory properties
        )
    {
        auto pfnGetExternalMemoryProperties = context.zeDdiTable.Device.pfnGetExternalMemoryProperties;

        if( nullptr == pfnGetExternalMemoryProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetExternalMemoryProperties( hDevice, pExternalMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetExternalMemoryProperties( hDevice, pExternalMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetExternalMemoryProperties( hDevice, pExternalMemoryProperties );
        return result;
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
        auto pfnGetP2PProperties = context.zeDdiTable.Device.pfnGetP2PProperties;

        if( nullptr == pfnGetP2PProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
        return result;
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
        auto pfnCanAccessPeer = context.zeDdiTable.Device.pfnCanAccessPeer;

        if( nullptr == pfnCanAccessPeer )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceCanAccessPeer( hDevice, hPeerDevice, value );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceCanAccessPeer( hDevice, hPeerDevice, value );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCanAccessPeer( hDevice, hPeerDevice, value );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetStatus(
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        auto pfnGetStatus = context.zeDdiTable.Device.pfnGetStatus;

        if( nullptr == pfnGetStatus )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetStatus( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetStatus( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetStatus( hDevice );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetGlobalTimestamps
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetGlobalTimestamps(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        uint64_t* hostTimestamp,                        ///< [out] value of the Host's global timestamp that correlates with the
                                                        ///< Device's global timestamp value
        uint64_t* deviceTimestamp                       ///< [out] value of the Device's global timestamp that correlates with the
                                                        ///< Host's global timestamp value
        )
    {
        auto pfnGetGlobalTimestamps = context.zeDdiTable.Device.pfnGetGlobalTimestamps;

        if( nullptr == pfnGetGlobalTimestamps )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetGlobalTimestamps( hDevice, hostTimestamp, deviceTimestamp );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetGlobalTimestamps( hDevice, hostTimestamp, deviceTimestamp );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetGlobalTimestamps( hDevice, hostTimestamp, deviceTimestamp );
        return result;
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
        auto pfnCreate = context.zeDdiTable.Context.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextCreate( hDriver, desc, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextCreate( hDriver, desc, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreate( hDriver, desc, phContext );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phContext){
                context.handleLifetime->addHandle( *phContext );
                context.handleLifetime->addDependent( hDriver, *phContext );

            }
        }
        return result;
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
        auto pfnCreateEx = context.zeDdiTable.Context.pfnCreateEx;

        if( nullptr == pfnCreateEx )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextCreateEx( hDriver, desc, numDevices, phDevices, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextCreateEx( hDriver, desc, numDevices, phDevices, phContext );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreateEx( hDriver, desc, numDevices, phDevices, phContext );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phContext){
                context.handleLifetime->addHandle( *phContext );
                context.handleLifetime->addDependent( hDriver, *phContext );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeContextDestroy(
        ze_context_handle_t hContext                    ///< [in][release] handle of context object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.Context.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextDestroy( hContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextDestroy( hContext );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroy( hContext );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextGetStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeContextGetStatus(
        ze_context_handle_t hContext                    ///< [in] handle of context object
        )
    {
        auto pfnGetStatus = context.zeDdiTable.Context.pfnGetStatus;

        if( nullptr == pfnGetStatus )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextGetStatus( hContext );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextGetStatus( hContext );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetStatus( hContext );
        return result;
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
        auto pfnCreate = context.zeDdiTable.CommandQueue.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandQueueCreate( hContext, hDevice, desc, phCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueCreate( hContext, hDevice, desc, phCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreate( hContext, hDevice, desc, phCommandQueue );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phCommandQueue){
                context.handleLifetime->addHandle( *phCommandQueue );
                context.handleLifetime->addDependent( hContext, *phCommandQueue );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandQueueDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandQueueDestroy(
        ze_command_queue_handle_t hCommandQueue         ///< [in][release] handle of command queue object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.CommandQueue.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandQueueDestroy( hCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueDestroy( hCommandQueue );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroy( hCommandQueue );
        return result;
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
        auto pfnExecuteCommandLists = context.zeDdiTable.CommandQueue.pfnExecuteCommandLists;

        if( nullptr == pfnExecuteCommandLists )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandQueueExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
        return result;
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
        auto pfnSynchronize = context.zeDdiTable.CommandQueue.pfnSynchronize;

        if( nullptr == pfnSynchronize )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandQueueSynchronize( hCommandQueue, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandQueueSynchronize( hCommandQueue, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSynchronize( hCommandQueue, timeout );
        return result;
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
        auto pfnCreate = context.zeDdiTable.CommandList.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListCreate( hContext, hDevice, desc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListCreate( hContext, hDevice, desc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreate( hContext, hDevice, desc, phCommandList );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phCommandList){
                context.handleLifetime->addHandle( *phCommandList );
                context.handleLifetime->addDependent( hContext, *phCommandList );

            }
        }
        return result;
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
        auto pfnCreateImmediate = context.zeDdiTable.CommandList.pfnCreateImmediate;

        if( nullptr == pfnCreateImmediate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListCreateImmediate( hContext, hDevice, altdesc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListCreateImmediate( hContext, hDevice, altdesc, phCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreateImmediate( hContext, hDevice, altdesc, phCommandList );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phCommandList){
                context.handleLifetime->addHandle( *phCommandList , false);
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListDestroy(
        ze_command_list_handle_t hCommandList           ///< [in][release] handle of command list object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.CommandList.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListDestroy( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListDestroy( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroy( hCommandList );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListClose
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListClose(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
        )
    {
        auto pfnClose = context.zeDdiTable.CommandList.pfnClose;

        if( nullptr == pfnClose )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListClose( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListClose( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnClose( hCommandList );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListReset
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListReset(
        ze_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
        )
    {
        auto pfnReset = context.zeDdiTable.CommandList.pfnReset;

        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListReset( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListReset( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnReset( hCommandList );
        return result;
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
        auto pfnAppendWriteGlobalTimestamp = context.zeDdiTable.CommandList.pfnAppendWriteGlobalTimestamp;

        if( nullptr == pfnAppendWriteGlobalTimestamp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendWriteGlobalTimestamp( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendWriteGlobalTimestamp( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendWriteGlobalTimestamp( hCommandList, dstptr, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnHostSynchronize = context.zeDdiTable.CommandList.pfnHostSynchronize;

        if( nullptr == pfnHostSynchronize )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListHostSynchronize( hCommandList, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListHostSynchronize( hCommandList, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnHostSynchronize( hCommandList, timeout );
        return result;
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
        auto pfnAppendBarrier = context.zeDdiTable.CommandList.pfnAppendBarrier;

        if( nullptr == pfnAppendBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnAppendMemoryRangesBarrier = context.zeDdiTable.CommandList.pfnAppendMemoryRangesBarrier;

        if( nullptr == pfnAppendMemoryRangesBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeContextSystemBarrier
    __zedlllocal ze_result_t ZE_APICALL
    zeContextSystemBarrier(
        ze_context_handle_t hContext,                   ///< [in] handle of context object
        ze_device_handle_t hDevice                      ///< [in] handle of the device
        )
    {
        auto pfnSystemBarrier = context.zeDdiTable.Context.pfnSystemBarrier;

        if( nullptr == pfnSystemBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextSystemBarrier( hContext, hDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextSystemBarrier( hContext, hDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSystemBarrier( hContext, hDevice );
        return result;
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
        auto pfnAppendMemoryCopy = context.zeDdiTable.CommandList.pfnAppendMemoryCopy;

        if( nullptr == pfnAppendMemoryCopy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnAppendMemoryFill = context.zeDdiTable.CommandList.pfnAppendMemoryFill;

        if( nullptr == pfnAppendMemoryFill )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendMemoryFill( hCommandList, ptr, pattern, pattern_size, size, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnAppendMemoryCopyRegion = context.zeDdiTable.CommandList.pfnAppendMemoryCopyRegion;

        if( nullptr == pfnAppendMemoryCopyRegion )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, dstSlicePitch, srcptr, srcRegion, srcPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnAppendMemoryCopyFromContext = context.zeDdiTable.CommandList.pfnAppendMemoryCopyFromContext;

        if( nullptr == pfnAppendMemoryCopyFromContext )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendMemoryCopyFromContext( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryCopyFromContext( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendMemoryCopyFromContext( hCommandList, dstptr, hContextSrc, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnAppendImageCopy = context.zeDdiTable.CommandList.pfnAppendImageCopy;

        if( nullptr == pfnAppendImageCopy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendImageCopy( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopy( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnAppendImageCopyRegion = context.zeDdiTable.CommandList.pfnAppendImageCopyRegion;

        if( nullptr == pfnAppendImageCopyRegion )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnAppendImageCopyToMemory = context.zeDdiTable.CommandList.pfnAppendImageCopyToMemory;

        if( nullptr == pfnAppendImageCopyToMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnAppendImageCopyFromMemory = context.zeDdiTable.CommandList.pfnAppendImageCopyFromMemory;

        if( nullptr == pfnAppendImageCopyFromMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnAppendMemoryPrefetch = context.zeDdiTable.CommandList.pfnAppendMemoryPrefetch;

        if( nullptr == pfnAppendMemoryPrefetch )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendMemoryPrefetch( hCommandList, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemoryPrefetch( hCommandList, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendMemoryPrefetch( hCommandList, ptr, size );
        return result;
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
        auto pfnAppendMemAdvise = context.zeDdiTable.CommandList.pfnAppendMemAdvise;

        if( nullptr == pfnAppendMemAdvise )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
        return result;
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
        auto pfnCreate = context.zeDdiTable.EventPool.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventPoolCreate( hContext, desc, numDevices, phDevices, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolCreate( hContext, desc, numDevices, phDevices, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreate( hContext, desc, numDevices, phDevices, phEventPool );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phEventPool){
                context.handleLifetime->addHandle( *phEventPool );
                context.handleLifetime->addDependent( hContext, *phEventPool );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolDestroy(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.EventPool.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventPoolDestroy( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolDestroy( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroy( hEventPool );
        return result;
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
        auto pfnCreate = context.zeDdiTable.Event.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventCreate( hEventPool, desc, phEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventCreate( hEventPool, desc, phEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreate( hEventPool, desc, phEvent );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phEvent){
                context.handleLifetime->addHandle( *phEvent );
                context.handleLifetime->addDependent( hEventPool, *phEvent );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeEventDestroy(
        ze_event_handle_t hEvent                        ///< [in][release] handle of event object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.Event.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventDestroy( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventDestroy( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroy( hEvent );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolGetIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolGetIpcHandle(
        ze_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
        ze_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
        )
    {
        auto pfnGetIpcHandle = context.zeDdiTable.EventPool.pfnGetIpcHandle;

        if( nullptr == pfnGetIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventPoolGetIpcHandle( hEventPool, phIpc );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolGetIpcHandle( hEventPool, phIpc );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetIpcHandle( hEventPool, phIpc );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
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
        auto pfnPutIpcHandle = context.zeDdiTable.EventPool.pfnPutIpcHandle;

        if( nullptr == pfnPutIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventPoolPutIpcHandle( hContext, hIpc );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolPutIpcHandle( hContext, hIpc );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnPutIpcHandle( hContext, hIpc );
        return result;
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
        auto pfnOpenIpcHandle = context.zeDdiTable.EventPool.pfnOpenIpcHandle;

        if( nullptr == pfnOpenIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventPoolOpenIpcHandle( hContext, hIpc, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolOpenIpcHandle( hContext, hIpc, phEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnOpenIpcHandle( hContext, hIpc, phEventPool );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventPoolCloseIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeEventPoolCloseIpcHandle(
        ze_event_pool_handle_t hEventPool               ///< [in][release] handle of event pool object
        )
    {
        auto pfnCloseIpcHandle = context.zeDdiTable.EventPool.pfnCloseIpcHandle;

        if( nullptr == pfnCloseIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventPoolCloseIpcHandle( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventPoolCloseIpcHandle( hEventPool );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCloseIpcHandle( hEventPool );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendSignalEvent
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendSignalEvent(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnAppendSignalEvent = context.zeDdiTable.CommandList.pfnAppendSignalEvent;

        if( nullptr == pfnAppendSignalEvent )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendSignalEvent( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendSignalEvent( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendSignalEvent( hCommandList, hEvent );
        return result;
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
        auto pfnAppendWaitOnEvents = context.zeDdiTable.CommandList.pfnAppendWaitOnEvents;

        if( nullptr == pfnAppendWaitOnEvents )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendWaitOnEvents( hCommandList, numEvents, phEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendWaitOnEvents( hCommandList, numEvents, phEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostSignal
    __zedlllocal ze_result_t ZE_APICALL
    zeEventHostSignal(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnHostSignal = context.zeDdiTable.Event.pfnHostSignal;

        if( nullptr == pfnHostSignal )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventHostSignal( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventHostSignal( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnHostSignal( hEvent );
        return result;
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
        auto pfnHostSynchronize = context.zeDdiTable.Event.pfnHostSynchronize;

        if( nullptr == pfnHostSynchronize )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventHostSynchronize( hEvent, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventHostSynchronize( hEvent, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnHostSynchronize( hEvent, timeout );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryStatus(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnQueryStatus = context.zeDdiTable.Event.pfnQueryStatus;

        if( nullptr == pfnQueryStatus )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventQueryStatus( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventQueryStatus( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnQueryStatus( hEvent );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeCommandListAppendEventReset
    __zedlllocal ze_result_t ZE_APICALL
    zeCommandListAppendEventReset(
        ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnAppendEventReset = context.zeDdiTable.CommandList.pfnAppendEventReset;

        if( nullptr == pfnAppendEventReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendEventReset( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendEventReset( hCommandList, hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendEventReset( hCommandList, hEvent );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventHostReset
    __zedlllocal ze_result_t ZE_APICALL
    zeEventHostReset(
        ze_event_handle_t hEvent                        ///< [in] handle of the event
        )
    {
        auto pfnHostReset = context.zeDdiTable.Event.pfnHostReset;

        if( nullptr == pfnHostReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventHostReset( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventHostReset( hEvent );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnHostReset( hEvent );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeEventQueryKernelTimestamp
    __zedlllocal ze_result_t ZE_APICALL
    zeEventQueryKernelTimestamp(
        ze_event_handle_t hEvent,                       ///< [in] handle of the event
        ze_kernel_timestamp_result_t* dstptr            ///< [in,out] pointer to memory for where timestamp result will be written.
        )
    {
        auto pfnQueryKernelTimestamp = context.zeDdiTable.Event.pfnQueryKernelTimestamp;

        if( nullptr == pfnQueryKernelTimestamp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventQueryKernelTimestamp( hEvent, dstptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventQueryKernelTimestamp( hEvent, dstptr );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnQueryKernelTimestamp( hEvent, dstptr );
        return result;
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
        auto pfnAppendQueryKernelTimestamps = context.zeDdiTable.CommandList.pfnAppendQueryKernelTimestamps;

        if( nullptr == pfnAppendQueryKernelTimestamps )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendQueryKernelTimestamps( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendQueryKernelTimestamps( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendQueryKernelTimestamps( hCommandList, numEvents, phEvents, dstptr, pOffsets, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnCreate = context.zeDdiTable.Fence.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFenceCreate( hCommandQueue, desc, phFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFenceCreate( hCommandQueue, desc, phFence );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreate( hCommandQueue, desc, phFence );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phFence){
                context.handleLifetime->addHandle( *phFence );
                context.handleLifetime->addDependent( hCommandQueue, *phFence );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceDestroy(
        ze_fence_handle_t hFence                        ///< [in][release] handle of fence object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.Fence.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFenceDestroy( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFenceDestroy( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroy( hFence );
        return result;
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
        auto pfnHostSynchronize = context.zeDdiTable.Fence.pfnHostSynchronize;

        if( nullptr == pfnHostSynchronize )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFenceHostSynchronize( hFence, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFenceHostSynchronize( hFence, timeout );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnHostSynchronize( hFence, timeout );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceQueryStatus
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceQueryStatus(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        auto pfnQueryStatus = context.zeDdiTable.Fence.pfnQueryStatus;

        if( nullptr == pfnQueryStatus )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFenceQueryStatus( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFenceQueryStatus( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnQueryStatus( hFence );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFenceReset
    __zedlllocal ze_result_t ZE_APICALL
    zeFenceReset(
        ze_fence_handle_t hFence                        ///< [in] handle of the fence
        )
    {
        auto pfnReset = context.zeDdiTable.Fence.pfnReset;

        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFenceReset( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFenceReset( hFence );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnReset( hFence );
        return result;
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
        auto pfnGetProperties = context.zeDdiTable.Image.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeImageGetProperties( hDevice, desc, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageGetProperties( hDevice, desc, pImageProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hDevice, desc, pImageProperties );
        return result;
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
        auto pfnCreate = context.zeDdiTable.Image.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeImageCreate( hContext, hDevice, desc, phImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageCreate( hContext, hDevice, desc, phImage );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreate( hContext, hDevice, desc, phImage );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phImage){
                context.handleLifetime->addHandle( *phImage );
                context.handleLifetime->addDependent( hContext, *phImage );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeImageDestroy(
        ze_image_handle_t hImage                        ///< [in][release] handle of image object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.Image.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeImageDestroy( hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageDestroy( hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroy( hImage );
        return result;
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
        auto pfnAllocShared = context.zeDdiTable.Mem.pfnAllocShared;

        if( nullptr == pfnAllocShared )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemAllocShared( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemAllocShared( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAllocShared( hContext, device_desc, host_desc, size, alignment, hDevice, pptr );
        return result;
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
        auto pfnAllocDevice = context.zeDdiTable.Mem.pfnAllocDevice;

        if( nullptr == pfnAllocDevice )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemAllocDevice( hContext, device_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemAllocDevice( hContext, device_desc, size, alignment, hDevice, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAllocDevice( hContext, device_desc, size, alignment, hDevice, pptr );
        return result;
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
        auto pfnAllocHost = context.zeDdiTable.Mem.pfnAllocHost;

        if( nullptr == pfnAllocHost )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemAllocHost( hContext, host_desc, size, alignment, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemAllocHost( hContext, host_desc, size, alignment, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAllocHost( hContext, host_desc, size, alignment, pptr );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemFree
    __zedlllocal ze_result_t ZE_APICALL
    zeMemFree(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        auto pfnFree = context.zeDdiTable.Mem.pfnFree;

        if( nullptr == pfnFree )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemFree( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemFree( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnFree( hContext, ptr );
        return result;
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
        auto pfnGetAllocProperties = context.zeDdiTable.Mem.pfnGetAllocProperties;

        if( nullptr == pfnGetAllocProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemGetAllocProperties( hContext, ptr, pMemAllocProperties, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetAllocProperties( hContext, ptr, pMemAllocProperties, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetAllocProperties( hContext, ptr, pMemAllocProperties, phDevice );
        return result;
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
        auto pfnGetAddressRange = context.zeDdiTable.Mem.pfnGetAddressRange;

        if( nullptr == pfnGetAddressRange )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemGetAddressRange( hContext, ptr, pBase, pSize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetAddressRange( hContext, ptr, pBase, pSize );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetAddressRange( hContext, ptr, pBase, pSize );
        return result;
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
        auto pfnGetIpcHandle = context.zeDdiTable.Mem.pfnGetIpcHandle;

        if( nullptr == pfnGetIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemGetIpcHandle( hContext, ptr, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetIpcHandle( hContext, ptr, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetIpcHandle( hContext, ptr, pIpcHandle );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
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
        auto pfnGetIpcHandleFromFileDescriptorExp = context.zeDdiTable.MemExp.pfnGetIpcHandleFromFileDescriptorExp;

        if( nullptr == pfnGetIpcHandleFromFileDescriptorExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemGetIpcHandleFromFileDescriptorExp( hContext, handle, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetIpcHandleFromFileDescriptorExp( hContext, handle, pIpcHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetIpcHandleFromFileDescriptorExp( hContext, handle, pIpcHandle );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
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
        auto pfnGetFileDescriptorFromIpcHandleExp = context.zeDdiTable.MemExp.pfnGetFileDescriptorFromIpcHandleExp;

        if( nullptr == pfnGetFileDescriptorFromIpcHandleExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemGetFileDescriptorFromIpcHandleExp( hContext, ipcHandle, pHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetFileDescriptorFromIpcHandleExp( hContext, ipcHandle, pHandle );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetFileDescriptorFromIpcHandleExp( hContext, ipcHandle, pHandle );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemPutIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeMemPutIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_ipc_mem_handle_t handle                      ///< [in] IPC memory handle
        )
    {
        auto pfnPutIpcHandle = context.zeDdiTable.Mem.pfnPutIpcHandle;

        if( nullptr == pfnPutIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemPutIpcHandle( hContext, handle );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemPutIpcHandle( hContext, handle );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnPutIpcHandle( hContext, handle );
        return result;
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
        auto pfnOpenIpcHandle = context.zeDdiTable.Mem.pfnOpenIpcHandle;

        if( nullptr == pfnOpenIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemOpenIpcHandle( hContext, hDevice, handle, flags, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemOpenIpcHandle( hContext, hDevice, handle, flags, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnOpenIpcHandle( hContext, hDevice, handle, flags, pptr );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeMemCloseIpcHandle
    __zedlllocal ze_result_t ZE_APICALL
    zeMemCloseIpcHandle(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        auto pfnCloseIpcHandle = context.zeDdiTable.Mem.pfnCloseIpcHandle;

        if( nullptr == pfnCloseIpcHandle )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemCloseIpcHandle( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemCloseIpcHandle( hContext, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCloseIpcHandle( hContext, ptr );
        return result;
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
        auto pfnSetAtomicAccessAttributeExp = context.zeDdiTable.MemExp.pfnSetAtomicAccessAttributeExp;

        if( nullptr == pfnSetAtomicAccessAttributeExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemSetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, attr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemSetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, attr );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, attr );
        return result;
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
        auto pfnGetAtomicAccessAttributeExp = context.zeDdiTable.MemExp.pfnGetAtomicAccessAttributeExp;

        if( nullptr == pfnGetAtomicAccessAttributeExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemGetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, pAttr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemGetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, pAttr );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetAtomicAccessAttributeExp( hContext, hDevice, ptr, size, pAttr );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
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
        auto pfnCreate = context.zeDdiTable.Module.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleCreate( hContext, hDevice, desc, phModule, phBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleCreate( hContext, hDevice, desc, phModule, phBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreate( hContext, hDevice, desc, phModule, phBuildLog );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phModule){
                context.handleLifetime->addHandle( *phModule );
                context.handleLifetime->addDependent( hContext, *phModule );

            }
            if (phBuildLog){
                context.handleLifetime->addHandle( *phBuildLog );
                context.handleLifetime->addDependent( hContext, *phBuildLog );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleDestroy(
        ze_module_handle_t hModule                      ///< [in][release] handle of the module
        )
    {
        auto pfnDestroy = context.zeDdiTable.Module.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleDestroy( hModule );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleDestroy( hModule );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroy( hModule );
        return result;
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
        auto pfnDynamicLink = context.zeDdiTable.Module.pfnDynamicLink;

        if( nullptr == pfnDynamicLink )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleDynamicLink( numModules, phModules, phLinkLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleDynamicLink( numModules, phModules, phLinkLog );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDynamicLink( numModules, phModules, phLinkLog );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleBuildLogDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleBuildLogDestroy(
        ze_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
        )
    {
        auto pfnDestroy = context.zeDdiTable.ModuleBuildLog.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleBuildLogDestroy( hModuleBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleBuildLogDestroy( hModuleBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroy( hModuleBuildLog );
        return result;
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
        auto pfnGetString = context.zeDdiTable.ModuleBuildLog.pfnGetString;

        if( nullptr == pfnGetString )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleBuildLogGetString( hModuleBuildLog, pSize, pBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleBuildLogGetString( hModuleBuildLog, pSize, pBuildLog );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetString( hModuleBuildLog, pSize, pBuildLog );
        return result;
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
        auto pfnGetNativeBinary = context.zeDdiTable.Module.pfnGetNativeBinary;

        if( nullptr == pfnGetNativeBinary )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleGetNativeBinary( hModule, pSize, pModuleNativeBinary );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleGetNativeBinary( hModule, pSize, pModuleNativeBinary );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );
        return result;
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
        auto pfnGetGlobalPointer = context.zeDdiTable.Module.pfnGetGlobalPointer;

        if( nullptr == pfnGetGlobalPointer )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleGetGlobalPointer( hModule, pGlobalName, pSize, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleGetGlobalPointer( hModule, pGlobalName, pSize, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetGlobalPointer( hModule, pGlobalName, pSize, pptr );
        return result;
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
        auto pfnGetKernelNames = context.zeDdiTable.Module.pfnGetKernelNames;

        if( nullptr == pfnGetKernelNames )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleGetKernelNames( hModule, pCount, pNames );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleGetKernelNames( hModule, pCount, pNames );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetKernelNames( hModule, pCount, pNames );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeModuleGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeModuleGetProperties(
        ze_module_handle_t hModule,                     ///< [in] handle of the module
        ze_module_properties_t* pModuleProperties       ///< [in,out] query result for module properties.
        )
    {
        auto pfnGetProperties = context.zeDdiTable.Module.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleGetProperties( hModule, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleGetProperties( hModule, pModuleProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hModule, pModuleProperties );
        return result;
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
        auto pfnCreate = context.zeDdiTable.Kernel.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelCreate( hModule, desc, phKernel );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelCreate( hModule, desc, phKernel );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreate( hModule, desc, phKernel );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phKernel){
                context.handleLifetime->addHandle( *phKernel );
                context.handleLifetime->addDependent( hModule, *phKernel );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelDestroy(
        ze_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
        )
    {
        auto pfnDestroy = context.zeDdiTable.Kernel.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelDestroy( hKernel );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelDestroy( hKernel );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroy( hKernel );
        return result;
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
        auto pfnGetFunctionPointer = context.zeDdiTable.Module.pfnGetFunctionPointer;

        if( nullptr == pfnGetFunctionPointer )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleGetFunctionPointer( hModule, pFunctionName, pfnFunction );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleGetFunctionPointer( hModule, pFunctionName, pfnFunction );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );
        return result;
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
        auto pfnSetGroupSize = context.zeDdiTable.Kernel.pfnSetGroupSize;

        if( nullptr == pfnSetGroupSize )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetGroupSize( hKernel, groupSizeX, groupSizeY, groupSizeZ );
        return result;
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
        auto pfnSuggestGroupSize = context.zeDdiTable.Kernel.pfnSuggestGroupSize;

        if( nullptr == pfnSuggestGroupSize )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSuggestGroupSize( hKernel, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSuggestMaxCooperativeGroupCount
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSuggestMaxCooperativeGroupCount(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        uint32_t* totalGroupCount                       ///< [out] recommended total group count.
        )
    {
        auto pfnSuggestMaxCooperativeGroupCount = context.zeDdiTable.Kernel.pfnSuggestMaxCooperativeGroupCount;

        if( nullptr == pfnSuggestMaxCooperativeGroupCount )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSuggestMaxCooperativeGroupCount( hKernel, totalGroupCount );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSuggestMaxCooperativeGroupCount( hKernel, totalGroupCount );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSuggestMaxCooperativeGroupCount( hKernel, totalGroupCount );
        return result;
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
        auto pfnSetArgumentValue = context.zeDdiTable.Kernel.pfnSetArgumentValue;

        if( nullptr == pfnSetArgumentValue )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSetArgumentValue( hKernel, argIndex, argSize, pArgValue );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSetArgumentValue( hKernel, argIndex, argSize, pArgValue );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetArgumentValue( hKernel, argIndex, argSize, pArgValue );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSetIndirectAccess
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSetIndirectAccess(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_indirect_access_flags_t flags         ///< [in] kernel indirect access flags
        )
    {
        auto pfnSetIndirectAccess = context.zeDdiTable.Kernel.pfnSetIndirectAccess;

        if( nullptr == pfnSetIndirectAccess )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSetIndirectAccess( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSetIndirectAccess( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetIndirectAccess( hKernel, flags );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetIndirectAccess
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetIndirectAccess(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_indirect_access_flags_t* pFlags       ///< [out] query result for kernel indirect access flags.
        )
    {
        auto pfnGetIndirectAccess = context.zeDdiTable.Kernel.pfnGetIndirectAccess;

        if( nullptr == pfnGetIndirectAccess )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelGetIndirectAccess( hKernel, pFlags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelGetIndirectAccess( hKernel, pFlags );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetIndirectAccess( hKernel, pFlags );
        return result;
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
                                                        ///< a null-terminating character, is returned in pSize.
                                                        ///< Otherwise, pString must point to valid application memory that is
                                                        ///< greater than or equal to *pSize bytes in length, and on return the
                                                        ///< pointed-to string will contain a space-separated list of kernel source attributes.
        )
    {
        auto pfnGetSourceAttributes = context.zeDdiTable.Kernel.pfnGetSourceAttributes;

        if( nullptr == pfnGetSourceAttributes )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelGetSourceAttributes( hKernel, pSize, pString );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelGetSourceAttributes( hKernel, pSize, pString );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetSourceAttributes( hKernel, pSize, pString );
        return result;
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
        auto pfnSetCacheConfig = context.zeDdiTable.Kernel.pfnSetCacheConfig;

        if( nullptr == pfnSetCacheConfig )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSetCacheConfig( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSetCacheConfig( hKernel, flags );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetCacheConfig( hKernel, flags );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelGetProperties(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_kernel_properties_t* pKernelProperties       ///< [in,out] query result for kernel properties.
        )
    {
        auto pfnGetProperties = context.zeDdiTable.Kernel.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelGetProperties( hKernel, pKernelProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelGetProperties( hKernel, pKernelProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hKernel, pKernelProperties );
        return result;
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
        auto pfnGetName = context.zeDdiTable.Kernel.pfnGetName;

        if( nullptr == pfnGetName )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelGetName( hKernel, pSize, pName );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelGetName( hKernel, pSize, pName );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetName( hKernel, pSize, pName );
        return result;
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
        auto pfnAppendLaunchKernel = context.zeDdiTable.CommandList.pfnAppendLaunchKernel;

        if( nullptr == pfnAppendLaunchKernel )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendLaunchKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnAppendLaunchCooperativeKernel = context.zeDdiTable.CommandList.pfnAppendLaunchCooperativeKernel;

        if( nullptr == pfnAppendLaunchCooperativeKernel )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendLaunchCooperativeKernel( hCommandList, hKernel, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnAppendLaunchKernelIndirect = context.zeDdiTable.CommandList.pfnAppendLaunchKernelIndirect;

        if( nullptr == pfnAppendLaunchKernelIndirect )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendLaunchKernelIndirect( hCommandList, hKernel, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnAppendLaunchMultipleKernelsIndirect = context.zeDdiTable.CommandList.pfnAppendLaunchMultipleKernelsIndirect;

        if( nullptr == pfnAppendLaunchMultipleKernelsIndirect )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendLaunchMultipleKernelsIndirect( hCommandList, numKernels, phKernels, pCountBuffer, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnMakeMemoryResident = context.zeDdiTable.Context.pfnMakeMemoryResident;

        if( nullptr == pfnMakeMemoryResident )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextMakeMemoryResident( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextMakeMemoryResident( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnMakeMemoryResident( hContext, hDevice, ptr, size );
        return result;
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
        auto pfnEvictMemory = context.zeDdiTable.Context.pfnEvictMemory;

        if( nullptr == pfnEvictMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextEvictMemory( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextEvictMemory( hContext, hDevice, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEvictMemory( hContext, hDevice, ptr, size );
        return result;
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
        auto pfnMakeImageResident = context.zeDdiTable.Context.pfnMakeImageResident;

        if( nullptr == pfnMakeImageResident )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextMakeImageResident( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextMakeImageResident( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnMakeImageResident( hContext, hDevice, hImage );
        return result;
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
        auto pfnEvictImage = context.zeDdiTable.Context.pfnEvictImage;

        if( nullptr == pfnEvictImage )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeContextEvictImage( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeContextEvictImage( hContext, hDevice, hImage );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnEvictImage( hContext, hDevice, hImage );
        return result;
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
        auto pfnCreate = context.zeDdiTable.Sampler.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeSamplerCreate( hContext, hDevice, desc, phSampler );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeSamplerCreate( hContext, hDevice, desc, phSampler );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreate( hContext, hDevice, desc, phSampler );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phSampler){
                context.handleLifetime->addHandle( *phSampler );
                context.handleLifetime->addDependent( hContext, *phSampler );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeSamplerDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zeSamplerDestroy(
        ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
        )
    {
        auto pfnDestroy = context.zeDdiTable.Sampler.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeSamplerDestroy( hSampler );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeSamplerDestroy( hSampler );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroy( hSampler );
        return result;
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
        auto pfnReserve = context.zeDdiTable.VirtualMem.pfnReserve;

        if( nullptr == pfnReserve )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeVirtualMemReserve( hContext, pStart, size, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemReserve( hContext, pStart, size, pptr );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnReserve( hContext, pStart, size, pptr );
        return result;
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
        auto pfnFree = context.zeDdiTable.VirtualMem.pfnFree;

        if( nullptr == pfnFree )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeVirtualMemFree( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemFree( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnFree( hContext, ptr, size );
        return result;
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
        auto pfnQueryPageSize = context.zeDdiTable.VirtualMem.pfnQueryPageSize;

        if( nullptr == pfnQueryPageSize )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeVirtualMemQueryPageSize( hContext, hDevice, size, pagesize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemQueryPageSize( hContext, hDevice, size, pagesize );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnQueryPageSize( hContext, hDevice, size, pagesize );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zePhysicalMemCreate
    __zedlllocal ze_result_t ZE_APICALL
    zePhysicalMemCreate(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object
        ze_physical_mem_desc_t* desc,                   ///< [in] pointer to physical memory descriptor.
        ze_physical_mem_handle_t* phPhysicalMemory      ///< [out] pointer to handle of physical memory object created
        )
    {
        auto pfnCreate = context.zeDdiTable.PhysicalMem.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zePhysicalMemCreate( hContext, hDevice, desc, phPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zePhysicalMemCreate( hContext, hDevice, desc, phPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreate( hContext, hDevice, desc, phPhysicalMemory );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phPhysicalMemory){
                context.handleLifetime->addHandle( *phPhysicalMemory );
                context.handleLifetime->addDependent( hContext, *phPhysicalMemory );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zePhysicalMemDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zePhysicalMemDestroy(
        ze_context_handle_t hContext,                   ///< [in] handle of the context object
        ze_physical_mem_handle_t hPhysicalMemory        ///< [in][release] handle of physical memory object to destroy
        )
    {
        auto pfnDestroy = context.zeDdiTable.PhysicalMem.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zePhysicalMemDestroy( hContext, hPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zePhysicalMemDestroy( hContext, hPhysicalMemory );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroy( hContext, hPhysicalMemory );
        return result;
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
        auto pfnMap = context.zeDdiTable.VirtualMem.pfnMap;

        if( nullptr == pfnMap )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeVirtualMemMap( hContext, ptr, size, hPhysicalMemory, offset, access );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemMap( hContext, ptr, size, hPhysicalMemory, offset, access );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnMap( hContext, ptr, size, hPhysicalMemory, offset, access );
        return result;
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
        auto pfnUnmap = context.zeDdiTable.VirtualMem.pfnUnmap;

        if( nullptr == pfnUnmap )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeVirtualMemUnmap( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemUnmap( hContext, ptr, size );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnUnmap( hContext, ptr, size );
        return result;
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
        auto pfnSetAccessAttribute = context.zeDdiTable.VirtualMem.pfnSetAccessAttribute;

        if( nullptr == pfnSetAccessAttribute )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeVirtualMemSetAccessAttribute( hContext, ptr, size, access );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemSetAccessAttribute( hContext, ptr, size, access );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetAccessAttribute( hContext, ptr, size, access );
        return result;
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
        auto pfnGetAccessAttribute = context.zeDdiTable.VirtualMem.pfnGetAccessAttribute;

        if( nullptr == pfnGetAccessAttribute )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeVirtualMemGetAccessAttribute( hContext, ptr, size, access, outSize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeVirtualMemGetAccessAttribute( hContext, ptr, size, access, outSize );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetAccessAttribute( hContext, ptr, size, access, outSize );
        return result;
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
        auto pfnSetGlobalOffsetExp = context.zeDdiTable.KernelExp.pfnSetGlobalOffsetExp;

        if( nullptr == pfnSetGlobalOffsetExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSetGlobalOffsetExp( hKernel, offsetX, offsetY, offsetZ );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSetGlobalOffsetExp( hKernel, offsetX, offsetY, offsetZ );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetGlobalOffsetExp( hKernel, offsetX, offsetY, offsetZ );
        return result;
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
        auto pfnReserveCacheExt = context.zeDdiTable.Device.pfnReserveCacheExt;

        if( nullptr == pfnReserveCacheExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceReserveCacheExt( hDevice, cacheLevel, cacheReservationSize );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceReserveCacheExt( hDevice, cacheLevel, cacheReservationSize );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnReserveCacheExt( hDevice, cacheLevel, cacheReservationSize );
        return result;
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
        auto pfnSetCacheAdviceExt = context.zeDdiTable.Device.pfnSetCacheAdviceExt;

        if( nullptr == pfnSetCacheAdviceExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceSetCacheAdviceExt( hDevice, ptr, regionSize, cacheRegion );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceSetCacheAdviceExt( hDevice, ptr, regionSize, cacheRegion );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetCacheAdviceExt( hDevice, ptr, regionSize, cacheRegion );
        return result;
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
        auto pfnQueryTimestampsExp = context.zeDdiTable.EventExp.pfnQueryTimestampsExp;

        if( nullptr == pfnQueryTimestampsExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventQueryTimestampsExp( hEvent, hDevice, pCount, pTimestamps );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventQueryTimestampsExp( hEvent, hDevice, pCount, pTimestamps );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnQueryTimestampsExp( hEvent, hDevice, pCount, pTimestamps );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeImageGetMemoryPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeImageGetMemoryPropertiesExp(
        ze_image_handle_t hImage,                       ///< [in] handle of image object
        ze_image_memory_properties_exp_t* pMemoryProperties ///< [in,out] query result for image memory properties.
        )
    {
        auto pfnGetMemoryPropertiesExp = context.zeDdiTable.ImageExp.pfnGetMemoryPropertiesExp;

        if( nullptr == pfnGetMemoryPropertiesExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeImageGetMemoryPropertiesExp( hImage, pMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageGetMemoryPropertiesExp( hImage, pMemoryProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetMemoryPropertiesExp( hImage, pMemoryProperties );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
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
        auto pfnViewCreateExt = context.zeDdiTable.Image.pfnViewCreateExt;

        if( nullptr == pfnViewCreateExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeImageViewCreateExt( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageViewCreateExt( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnViewCreateExt( hContext, hDevice, desc, hImage, phImageView );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phImageView){
                context.handleLifetime->addHandle( *phImageView );
                context.handleLifetime->addDependent( hContext, *phImageView );

            }
        }
        return result;
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
        auto pfnViewCreateExp = context.zeDdiTable.ImageExp.pfnViewCreateExp;

        if( nullptr == pfnViewCreateExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeImageViewCreateExp( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageViewCreateExp( hContext, hDevice, desc, hImage, phImageView );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnViewCreateExp( hContext, hDevice, desc, hImage, phImageView );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phImageView){
                context.handleLifetime->addHandle( *phImageView );
                context.handleLifetime->addDependent( hContext, *phImageView );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeKernelSchedulingHintExp
    __zedlllocal ze_result_t ZE_APICALL
    zeKernelSchedulingHintExp(
        ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
        ze_scheduling_hint_exp_desc_t* pHint            ///< [in] pointer to kernel scheduling hint descriptor
        )
    {
        auto pfnSchedulingHintExp = context.zeDdiTable.KernelExp.pfnSchedulingHintExp;

        if( nullptr == pfnSchedulingHintExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeKernelSchedulingHintExp( hKernel, pHint );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeKernelSchedulingHintExp( hKernel, pHint );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSchedulingHintExp( hKernel, pHint );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDevicePciGetPropertiesExt
    __zedlllocal ze_result_t ZE_APICALL
    zeDevicePciGetPropertiesExt(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device object.
        ze_pci_ext_properties_t* pPciProperties         ///< [in,out] returns the PCI properties of the device.
        )
    {
        auto pfnPciGetPropertiesExt = context.zeDdiTable.Device.pfnPciGetPropertiesExt;

        if( nullptr == pfnPciGetPropertiesExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDevicePciGetPropertiesExt( hDevice, pPciProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDevicePciGetPropertiesExt( hDevice, pPciProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnPciGetPropertiesExt( hDevice, pPciProperties );
        return result;
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
        auto pfnAppendImageCopyToMemoryExt = context.zeDdiTable.CommandList.pfnAppendImageCopyToMemoryExt;

        if( nullptr == pfnAppendImageCopyToMemoryExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendImageCopyToMemoryExt( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyToMemoryExt( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendImageCopyToMemoryExt( hCommandList, dstptr, hSrcImage, pSrcRegion, destRowPitch, destSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnAppendImageCopyFromMemoryExt = context.zeDdiTable.CommandList.pfnAppendImageCopyFromMemoryExt;

        if( nullptr == pfnAppendImageCopyFromMemoryExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeCommandListAppendImageCopyFromMemoryExt( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeCommandListAppendImageCopyFromMemoryExt( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendImageCopyFromMemoryExt( hCommandList, hDstImage, srcptr, pDstRegion, srcRowPitch, srcSlicePitch, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
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
        auto pfnGetAllocPropertiesExt = context.zeDdiTable.Image.pfnGetAllocPropertiesExt;

        if( nullptr == pfnGetAllocPropertiesExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeImageGetAllocPropertiesExt( hContext, hImage, pImageAllocProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeImageGetAllocPropertiesExt( hContext, hImage, pImageAllocProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetAllocPropertiesExt( hContext, hImage, pImageAllocProperties );
        return result;
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
        auto pfnInspectLinkageExt = context.zeDdiTable.Module.pfnInspectLinkageExt;

        if( nullptr == pfnInspectLinkageExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeModuleInspectLinkageExt( pInspectDesc, numModules, phModules, phLog );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeModuleInspectLinkageExt( pInspectDesc, numModules, phModules, phLog );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnInspectLinkageExt( pInspectDesc, numModules, phModules, phLog );
        return result;
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
        auto pfnFreeExt = context.zeDdiTable.Mem.pfnFreeExt;

        if( nullptr == pfnFreeExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeMemFreeExt( hContext, pMemFreeDesc, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeMemFreeExt( hContext, pMemFreeDesc, ptr );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnFreeExt( hContext, pMemFreeDesc, ptr );
        return result;
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
        auto pfnGetExp = context.zeDdiTable.FabricVertexExp.pfnGetExp;

        if( nullptr == pfnGetExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFabricVertexGetExp( hDriver, pCount, phVertices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricVertexGetExp( hDriver, pCount, phVertices );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetExp( hDriver, pCount, phVertices );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phVertices) && (i < *pCount); ++i){
                if (phVertices[i]){
                    context.handleLifetime->addHandle( phVertices[i] );
                    context.handleLifetime->addDependent( hDriver, phVertices[i] );
                }
            }
        }
        return result;
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
        auto pfnGetSubVerticesExp = context.zeDdiTable.FabricVertexExp.pfnGetSubVerticesExp;

        if( nullptr == pfnGetSubVerticesExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFabricVertexGetSubVerticesExp( hVertex, pCount, phSubvertices );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricVertexGetSubVerticesExp( hVertex, pCount, phSubvertices );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetSubVerticesExp( hVertex, pCount, phSubvertices );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phSubvertices) && (i < *pCount); ++i){
                if (phSubvertices[i]){
                    context.handleLifetime->addHandle( phSubvertices[i] );
                    context.handleLifetime->addDependent( hVertex, phSubvertices[i] );
                }
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricVertexGetPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetPropertiesExp(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
        ze_fabric_vertex_exp_properties_t* pVertexProperties///< [in,out] query result for fabric vertex properties
        )
    {
        auto pfnGetPropertiesExp = context.zeDdiTable.FabricVertexExp.pfnGetPropertiesExp;

        if( nullptr == pfnGetPropertiesExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFabricVertexGetPropertiesExp( hVertex, pVertexProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricVertexGetPropertiesExp( hVertex, pVertexProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetPropertiesExp( hVertex, pVertexProperties );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricVertexGetDeviceExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricVertexGetDeviceExp(
        ze_fabric_vertex_handle_t hVertex,              ///< [in] handle of the fabric vertex
        ze_device_handle_t* phDevice                    ///< [out] device handle corresponding to fabric vertex
        )
    {
        auto pfnGetDeviceExp = context.zeDdiTable.FabricVertexExp.pfnGetDeviceExp;

        if( nullptr == pfnGetDeviceExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFabricVertexGetDeviceExp( hVertex, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricVertexGetDeviceExp( hVertex, phDevice );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetDeviceExp( hVertex, phDevice );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phDevice){
                context.handleLifetime->addHandle( *phDevice );
                context.handleLifetime->addDependent( hVertex, *phDevice );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeDeviceGetFabricVertexExp
    __zedlllocal ze_result_t ZE_APICALL
    zeDeviceGetFabricVertexExp(
        ze_device_handle_t hDevice,                     ///< [in] handle of the device
        ze_fabric_vertex_handle_t* phVertex             ///< [out] fabric vertex handle corresponding to device
        )
    {
        auto pfnGetFabricVertexExp = context.zeDdiTable.DeviceExp.pfnGetFabricVertexExp;

        if( nullptr == pfnGetFabricVertexExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDeviceGetFabricVertexExp( hDevice, phVertex );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDeviceGetFabricVertexExp( hDevice, phVertex );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetFabricVertexExp( hDevice, phVertex );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phVertex){
                context.handleLifetime->addHandle( *phVertex );
                context.handleLifetime->addDependent( hDevice, *phVertex );

            }
        }
        return result;
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
        auto pfnGetExp = context.zeDdiTable.FabricEdgeExp.pfnGetExp;

        if( nullptr == pfnGetExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFabricEdgeGetExp( hVertexA, hVertexB, pCount, phEdges );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricEdgeGetExp( hVertexA, hVertexB, pCount, phEdges );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetExp( hVertexA, hVertexB, pCount, phEdges );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phEdges) && (i < *pCount); ++i){
                if (phEdges[i]){
                    context.handleLifetime->addHandle( phEdges[i] );
                    context.handleLifetime->addDependent( hVertexA, phEdges[i] );
                }
            }
        }
        return result;
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
        auto pfnGetVerticesExp = context.zeDdiTable.FabricEdgeExp.pfnGetVerticesExp;

        if( nullptr == pfnGetVerticesExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFabricEdgeGetVerticesExp( hEdge, phVertexA, phVertexB );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricEdgeGetVerticesExp( hEdge, phVertexA, phVertexB );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetVerticesExp( hEdge, phVertexA, phVertexB );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phVertexA){
                context.handleLifetime->addHandle( *phVertexA );
                context.handleLifetime->addDependent( hEdge, *phVertexA );

            }
            if (phVertexB){
                context.handleLifetime->addHandle( *phVertexB );
                context.handleLifetime->addDependent( hEdge, *phVertexB );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeFabricEdgeGetPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeFabricEdgeGetPropertiesExp(
        ze_fabric_edge_handle_t hEdge,                  ///< [in] handle of the fabric edge
        ze_fabric_edge_exp_properties_t* pEdgeProperties///< [in,out] query result for fabric edge properties
        )
    {
        auto pfnGetPropertiesExp = context.zeDdiTable.FabricEdgeExp.pfnGetPropertiesExp;

        if( nullptr == pfnGetPropertiesExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeFabricEdgeGetPropertiesExp( hEdge, pEdgeProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeFabricEdgeGetPropertiesExp( hEdge, pEdgeProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetPropertiesExp( hEdge, pEdgeProperties );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
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
        auto pfnQueryKernelTimestampsExt = context.zeDdiTable.Event.pfnQueryKernelTimestampsExt;

        if( nullptr == pfnQueryKernelTimestampsExt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeEventQueryKernelTimestampsExt( hEvent, hDevice, pCount, pResults );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeEventQueryKernelTimestampsExt( hEvent, hDevice, pCount, pResults );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnQueryKernelTimestampsExt( hEvent, hDevice, pCount, pResults );
        return result;
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
        auto pfnCreateExp = context.zeDdiTable.RTASBuilderExp.pfnCreateExp;

        if( nullptr == pfnCreateExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASBuilderCreateExp( hDriver, pDescriptor, phBuilder );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderCreateExp( hDriver, pDescriptor, phBuilder );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreateExp( hDriver, pDescriptor, phBuilder );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phBuilder){
                context.handleLifetime->addHandle( *phBuilder );
                context.handleLifetime->addDependent( hDriver, *phBuilder );

            }
        }
        return result;
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
        auto pfnGetBuildPropertiesExp = context.zeDdiTable.RTASBuilderExp.pfnGetBuildPropertiesExp;

        if( nullptr == pfnGetBuildPropertiesExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASBuilderGetBuildPropertiesExp( hBuilder, pBuildOpDescriptor, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderGetBuildPropertiesExp( hBuilder, pBuildOpDescriptor, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetBuildPropertiesExp( hBuilder, pBuildOpDescriptor, pProperties );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
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
        auto pfnRTASFormatCompatibilityCheckExp = context.zeDdiTable.DriverExp.pfnRTASFormatCompatibilityCheckExp;

        if( nullptr == pfnRTASFormatCompatibilityCheckExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeDriverRTASFormatCompatibilityCheckExp( hDriver, rtasFormatA, rtasFormatB );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeDriverRTASFormatCompatibilityCheckExp( hDriver, rtasFormatA, rtasFormatB );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnRTASFormatCompatibilityCheckExp( hDriver, rtasFormatA, rtasFormatB );
        return result;
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
        auto pfnBuildExp = context.zeDdiTable.RTASBuilderExp.pfnBuildExp;

        if( nullptr == pfnBuildExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASBuilderBuildExp( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderBuildExp( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnBuildExp( hBuilder, pBuildOpDescriptor, pScratchBuffer, scratchBufferSizeBytes, pRtasBuffer, rtasBufferSizeBytes, hParallelOperation, pBuildUserPtr, pBounds, pRtasBufferSizeBytes );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASBuilderDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASBuilderDestroyExp(
        ze_rtas_builder_exp_handle_t hBuilder           ///< [in][release] handle of builder object to destroy
        )
    {
        auto pfnDestroyExp = context.zeDdiTable.RTASBuilderExp.pfnDestroyExp;

        if( nullptr == pfnDestroyExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASBuilderDestroyExp( hBuilder );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASBuilderDestroyExp( hBuilder );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroyExp( hBuilder );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationCreateExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationCreateExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of driver object
        ze_rtas_parallel_operation_exp_handle_t* phParallelOperation///< [out] handle of parallel operation object
        )
    {
        auto pfnCreateExp = context.zeDdiTable.RTASParallelOperationExp.pfnCreateExp;

        if( nullptr == pfnCreateExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASParallelOperationCreateExp( hDriver, phParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationCreateExp( hDriver, phParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreateExp( hDriver, phParallelOperation );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phParallelOperation){
                context.handleLifetime->addHandle( *phParallelOperation );
                context.handleLifetime->addDependent( hDriver, *phParallelOperation );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationGetPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationGetPropertiesExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation, ///< [in] handle of parallel operation object
        ze_rtas_parallel_operation_exp_properties_t* pProperties///< [in,out] query result for parallel operation properties
        )
    {
        auto pfnGetPropertiesExp = context.zeDdiTable.RTASParallelOperationExp.pfnGetPropertiesExp;

        if( nullptr == pfnGetPropertiesExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASParallelOperationGetPropertiesExp( hParallelOperation, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationGetPropertiesExp( hParallelOperation, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetPropertiesExp( hParallelOperation, pProperties );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationJoinExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationJoinExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in] handle of parallel operation object
        )
    {
        auto pfnJoinExp = context.zeDdiTable.RTASParallelOperationExp.pfnJoinExp;

        if( nullptr == pfnJoinExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASParallelOperationJoinExp( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationJoinExp( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnJoinExp( hParallelOperation );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zeRTASParallelOperationDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zeRTASParallelOperationDestroyExp(
        ze_rtas_parallel_operation_exp_handle_t hParallelOperation  ///< [in][release] handle of parallel operation object to destroy
        )
    {
        auto pfnDestroyExp = context.zeDdiTable.RTASParallelOperationExp.pfnDestroyExp;

        if( nullptr == pfnDestroyExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zeParamValidation.zeRTASParallelOperationDestroyExp( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zeHandleLifetime.zeRTASParallelOperationDestroyExp( hParallelOperation );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroyExp( hParallelOperation );
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
zeGetGlobalProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    ze_global_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zeDdiTable.Global;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnInit                                     = pDdiTable->pfnInit;
    pDdiTable->pfnInit                                   = validation_layer::zeInit;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreateExp                                = pDdiTable->pfnCreateExp;
    pDdiTable->pfnCreateExp                              = validation_layer::zeRTASBuilderCreateExp;

    dditable.pfnGetBuildPropertiesExp                    = pDdiTable->pfnGetBuildPropertiesExp;
    pDdiTable->pfnGetBuildPropertiesExp                  = validation_layer::zeRTASBuilderGetBuildPropertiesExp;

    dditable.pfnBuildExp                                 = pDdiTable->pfnBuildExp;
    pDdiTable->pfnBuildExp                               = validation_layer::zeRTASBuilderBuildExp;

    dditable.pfnDestroyExp                               = pDdiTable->pfnDestroyExp;
    pDdiTable->pfnDestroyExp                             = validation_layer::zeRTASBuilderDestroyExp;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreateExp                                = pDdiTable->pfnCreateExp;
    pDdiTable->pfnCreateExp                              = validation_layer::zeRTASParallelOperationCreateExp;

    dditable.pfnGetPropertiesExp                         = pDdiTable->pfnGetPropertiesExp;
    pDdiTable->pfnGetPropertiesExp                       = validation_layer::zeRTASParallelOperationGetPropertiesExp;

    dditable.pfnJoinExp                                  = pDdiTable->pfnJoinExp;
    pDdiTable->pfnJoinExp                                = validation_layer::zeRTASParallelOperationJoinExp;

    dditable.pfnDestroyExp                               = pDdiTable->pfnDestroyExp;
    pDdiTable->pfnDestroyExp                             = validation_layer::zeRTASParallelOperationDestroyExp;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = validation_layer::zeDriverGet;

    dditable.pfnGetApiVersion                            = pDdiTable->pfnGetApiVersion;
    pDdiTable->pfnGetApiVersion                          = validation_layer::zeDriverGetApiVersion;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zeDriverGetProperties;

    dditable.pfnGetIpcProperties                         = pDdiTable->pfnGetIpcProperties;
    pDdiTable->pfnGetIpcProperties                       = validation_layer::zeDriverGetIpcProperties;

    dditable.pfnGetExtensionProperties                   = pDdiTable->pfnGetExtensionProperties;
    pDdiTable->pfnGetExtensionProperties                 = validation_layer::zeDriverGetExtensionProperties;

    dditable.pfnGetExtensionFunctionAddress              = pDdiTable->pfnGetExtensionFunctionAddress;
    pDdiTable->pfnGetExtensionFunctionAddress            = validation_layer::zeDriverGetExtensionFunctionAddress;

    dditable.pfnGetLastErrorDescription                  = pDdiTable->pfnGetLastErrorDescription;
    pDdiTable->pfnGetLastErrorDescription                = validation_layer::zeDriverGetLastErrorDescription;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnRTASFormatCompatibilityCheckExp          = pDdiTable->pfnRTASFormatCompatibilityCheckExp;
    pDdiTable->pfnRTASFormatCompatibilityCheckExp        = validation_layer::zeDriverRTASFormatCompatibilityCheckExp;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = validation_layer::zeDeviceGet;

    dditable.pfnGetSubDevices                            = pDdiTable->pfnGetSubDevices;
    pDdiTable->pfnGetSubDevices                          = validation_layer::zeDeviceGetSubDevices;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zeDeviceGetProperties;

    dditable.pfnGetComputeProperties                     = pDdiTable->pfnGetComputeProperties;
    pDdiTable->pfnGetComputeProperties                   = validation_layer::zeDeviceGetComputeProperties;

    dditable.pfnGetModuleProperties                      = pDdiTable->pfnGetModuleProperties;
    pDdiTable->pfnGetModuleProperties                    = validation_layer::zeDeviceGetModuleProperties;

    dditable.pfnGetCommandQueueGroupProperties           = pDdiTable->pfnGetCommandQueueGroupProperties;
    pDdiTable->pfnGetCommandQueueGroupProperties         = validation_layer::zeDeviceGetCommandQueueGroupProperties;

    dditable.pfnGetMemoryProperties                      = pDdiTable->pfnGetMemoryProperties;
    pDdiTable->pfnGetMemoryProperties                    = validation_layer::zeDeviceGetMemoryProperties;

    dditable.pfnGetMemoryAccessProperties                = pDdiTable->pfnGetMemoryAccessProperties;
    pDdiTable->pfnGetMemoryAccessProperties              = validation_layer::zeDeviceGetMemoryAccessProperties;

    dditable.pfnGetCacheProperties                       = pDdiTable->pfnGetCacheProperties;
    pDdiTable->pfnGetCacheProperties                     = validation_layer::zeDeviceGetCacheProperties;

    dditable.pfnGetImageProperties                       = pDdiTable->pfnGetImageProperties;
    pDdiTable->pfnGetImageProperties                     = validation_layer::zeDeviceGetImageProperties;

    dditable.pfnGetExternalMemoryProperties              = pDdiTable->pfnGetExternalMemoryProperties;
    pDdiTable->pfnGetExternalMemoryProperties            = validation_layer::zeDeviceGetExternalMemoryProperties;

    dditable.pfnGetP2PProperties                         = pDdiTable->pfnGetP2PProperties;
    pDdiTable->pfnGetP2PProperties                       = validation_layer::zeDeviceGetP2PProperties;

    dditable.pfnCanAccessPeer                            = pDdiTable->pfnCanAccessPeer;
    pDdiTable->pfnCanAccessPeer                          = validation_layer::zeDeviceCanAccessPeer;

    dditable.pfnGetStatus                                = pDdiTable->pfnGetStatus;
    pDdiTable->pfnGetStatus                              = validation_layer::zeDeviceGetStatus;

    dditable.pfnGetGlobalTimestamps                      = pDdiTable->pfnGetGlobalTimestamps;
    pDdiTable->pfnGetGlobalTimestamps                    = validation_layer::zeDeviceGetGlobalTimestamps;

    dditable.pfnReserveCacheExt                          = pDdiTable->pfnReserveCacheExt;
    pDdiTable->pfnReserveCacheExt                        = validation_layer::zeDeviceReserveCacheExt;

    dditable.pfnSetCacheAdviceExt                        = pDdiTable->pfnSetCacheAdviceExt;
    pDdiTable->pfnSetCacheAdviceExt                      = validation_layer::zeDeviceSetCacheAdviceExt;

    dditable.pfnPciGetPropertiesExt                      = pDdiTable->pfnPciGetPropertiesExt;
    pDdiTable->pfnPciGetPropertiesExt                    = validation_layer::zeDevicePciGetPropertiesExt;

    dditable.pfnGetRootDevice                            = pDdiTable->pfnGetRootDevice;
    pDdiTable->pfnGetRootDevice                          = validation_layer::zeDeviceGetRootDevice;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetFabricVertexExp                       = pDdiTable->pfnGetFabricVertexExp;
    pDdiTable->pfnGetFabricVertexExp                     = validation_layer::zeDeviceGetFabricVertexExp;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeContextCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeContextDestroy;

    dditable.pfnGetStatus                                = pDdiTable->pfnGetStatus;
    pDdiTable->pfnGetStatus                              = validation_layer::zeContextGetStatus;

    dditable.pfnSystemBarrier                            = pDdiTable->pfnSystemBarrier;
    pDdiTable->pfnSystemBarrier                          = validation_layer::zeContextSystemBarrier;

    dditable.pfnMakeMemoryResident                       = pDdiTable->pfnMakeMemoryResident;
    pDdiTable->pfnMakeMemoryResident                     = validation_layer::zeContextMakeMemoryResident;

    dditable.pfnEvictMemory                              = pDdiTable->pfnEvictMemory;
    pDdiTable->pfnEvictMemory                            = validation_layer::zeContextEvictMemory;

    dditable.pfnMakeImageResident                        = pDdiTable->pfnMakeImageResident;
    pDdiTable->pfnMakeImageResident                      = validation_layer::zeContextMakeImageResident;

    dditable.pfnEvictImage                               = pDdiTable->pfnEvictImage;
    pDdiTable->pfnEvictImage                             = validation_layer::zeContextEvictImage;

    dditable.pfnCreateEx                                 = pDdiTable->pfnCreateEx;
    pDdiTable->pfnCreateEx                               = validation_layer::zeContextCreateEx;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeCommandQueueCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeCommandQueueDestroy;

    dditable.pfnExecuteCommandLists                      = pDdiTable->pfnExecuteCommandLists;
    pDdiTable->pfnExecuteCommandLists                    = validation_layer::zeCommandQueueExecuteCommandLists;

    dditable.pfnSynchronize                              = pDdiTable->pfnSynchronize;
    pDdiTable->pfnSynchronize                            = validation_layer::zeCommandQueueSynchronize;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeCommandListCreate;

    dditable.pfnCreateImmediate                          = pDdiTable->pfnCreateImmediate;
    pDdiTable->pfnCreateImmediate                        = validation_layer::zeCommandListCreateImmediate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeCommandListDestroy;

    dditable.pfnClose                                    = pDdiTable->pfnClose;
    pDdiTable->pfnClose                                  = validation_layer::zeCommandListClose;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = validation_layer::zeCommandListReset;

    dditable.pfnAppendWriteGlobalTimestamp               = pDdiTable->pfnAppendWriteGlobalTimestamp;
    pDdiTable->pfnAppendWriteGlobalTimestamp             = validation_layer::zeCommandListAppendWriteGlobalTimestamp;

    dditable.pfnAppendBarrier                            = pDdiTable->pfnAppendBarrier;
    pDdiTable->pfnAppendBarrier                          = validation_layer::zeCommandListAppendBarrier;

    dditable.pfnAppendMemoryRangesBarrier                = pDdiTable->pfnAppendMemoryRangesBarrier;
    pDdiTable->pfnAppendMemoryRangesBarrier              = validation_layer::zeCommandListAppendMemoryRangesBarrier;

    dditable.pfnAppendMemoryCopy                         = pDdiTable->pfnAppendMemoryCopy;
    pDdiTable->pfnAppendMemoryCopy                       = validation_layer::zeCommandListAppendMemoryCopy;

    dditable.pfnAppendMemoryFill                         = pDdiTable->pfnAppendMemoryFill;
    pDdiTable->pfnAppendMemoryFill                       = validation_layer::zeCommandListAppendMemoryFill;

    dditable.pfnAppendMemoryCopyRegion                   = pDdiTable->pfnAppendMemoryCopyRegion;
    pDdiTable->pfnAppendMemoryCopyRegion                 = validation_layer::zeCommandListAppendMemoryCopyRegion;

    dditable.pfnAppendMemoryCopyFromContext              = pDdiTable->pfnAppendMemoryCopyFromContext;
    pDdiTable->pfnAppendMemoryCopyFromContext            = validation_layer::zeCommandListAppendMemoryCopyFromContext;

    dditable.pfnAppendImageCopy                          = pDdiTable->pfnAppendImageCopy;
    pDdiTable->pfnAppendImageCopy                        = validation_layer::zeCommandListAppendImageCopy;

    dditable.pfnAppendImageCopyRegion                    = pDdiTable->pfnAppendImageCopyRegion;
    pDdiTable->pfnAppendImageCopyRegion                  = validation_layer::zeCommandListAppendImageCopyRegion;

    dditable.pfnAppendImageCopyToMemory                  = pDdiTable->pfnAppendImageCopyToMemory;
    pDdiTable->pfnAppendImageCopyToMemory                = validation_layer::zeCommandListAppendImageCopyToMemory;

    dditable.pfnAppendImageCopyFromMemory                = pDdiTable->pfnAppendImageCopyFromMemory;
    pDdiTable->pfnAppendImageCopyFromMemory              = validation_layer::zeCommandListAppendImageCopyFromMemory;

    dditable.pfnAppendMemoryPrefetch                     = pDdiTable->pfnAppendMemoryPrefetch;
    pDdiTable->pfnAppendMemoryPrefetch                   = validation_layer::zeCommandListAppendMemoryPrefetch;

    dditable.pfnAppendMemAdvise                          = pDdiTable->pfnAppendMemAdvise;
    pDdiTable->pfnAppendMemAdvise                        = validation_layer::zeCommandListAppendMemAdvise;

    dditable.pfnAppendSignalEvent                        = pDdiTable->pfnAppendSignalEvent;
    pDdiTable->pfnAppendSignalEvent                      = validation_layer::zeCommandListAppendSignalEvent;

    dditable.pfnAppendWaitOnEvents                       = pDdiTable->pfnAppendWaitOnEvents;
    pDdiTable->pfnAppendWaitOnEvents                     = validation_layer::zeCommandListAppendWaitOnEvents;

    dditable.pfnAppendEventReset                         = pDdiTable->pfnAppendEventReset;
    pDdiTable->pfnAppendEventReset                       = validation_layer::zeCommandListAppendEventReset;

    dditable.pfnAppendQueryKernelTimestamps              = pDdiTable->pfnAppendQueryKernelTimestamps;
    pDdiTable->pfnAppendQueryKernelTimestamps            = validation_layer::zeCommandListAppendQueryKernelTimestamps;

    dditable.pfnAppendLaunchKernel                       = pDdiTable->pfnAppendLaunchKernel;
    pDdiTable->pfnAppendLaunchKernel                     = validation_layer::zeCommandListAppendLaunchKernel;

    dditable.pfnAppendLaunchCooperativeKernel            = pDdiTable->pfnAppendLaunchCooperativeKernel;
    pDdiTable->pfnAppendLaunchCooperativeKernel          = validation_layer::zeCommandListAppendLaunchCooperativeKernel;

    dditable.pfnAppendLaunchKernelIndirect               = pDdiTable->pfnAppendLaunchKernelIndirect;
    pDdiTable->pfnAppendLaunchKernelIndirect             = validation_layer::zeCommandListAppendLaunchKernelIndirect;

    dditable.pfnAppendLaunchMultipleKernelsIndirect      = pDdiTable->pfnAppendLaunchMultipleKernelsIndirect;
    pDdiTable->pfnAppendLaunchMultipleKernelsIndirect    = validation_layer::zeCommandListAppendLaunchMultipleKernelsIndirect;

    dditable.pfnAppendImageCopyToMemoryExt               = pDdiTable->pfnAppendImageCopyToMemoryExt;
    pDdiTable->pfnAppendImageCopyToMemoryExt             = validation_layer::zeCommandListAppendImageCopyToMemoryExt;

    dditable.pfnAppendImageCopyFromMemoryExt             = pDdiTable->pfnAppendImageCopyFromMemoryExt;
    pDdiTable->pfnAppendImageCopyFromMemoryExt           = validation_layer::zeCommandListAppendImageCopyFromMemoryExt;

    dditable.pfnHostSynchronize                          = pDdiTable->pfnHostSynchronize;
    pDdiTable->pfnHostSynchronize                        = validation_layer::zeCommandListHostSynchronize;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeEventCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeEventDestroy;

    dditable.pfnHostSignal                               = pDdiTable->pfnHostSignal;
    pDdiTable->pfnHostSignal                             = validation_layer::zeEventHostSignal;

    dditable.pfnHostSynchronize                          = pDdiTable->pfnHostSynchronize;
    pDdiTable->pfnHostSynchronize                        = validation_layer::zeEventHostSynchronize;

    dditable.pfnQueryStatus                              = pDdiTable->pfnQueryStatus;
    pDdiTable->pfnQueryStatus                            = validation_layer::zeEventQueryStatus;

    dditable.pfnHostReset                                = pDdiTable->pfnHostReset;
    pDdiTable->pfnHostReset                              = validation_layer::zeEventHostReset;

    dditable.pfnQueryKernelTimestamp                     = pDdiTable->pfnQueryKernelTimestamp;
    pDdiTable->pfnQueryKernelTimestamp                   = validation_layer::zeEventQueryKernelTimestamp;

    dditable.pfnQueryKernelTimestampsExt                 = pDdiTable->pfnQueryKernelTimestampsExt;
    pDdiTable->pfnQueryKernelTimestampsExt               = validation_layer::zeEventQueryKernelTimestampsExt;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnQueryTimestampsExp                       = pDdiTable->pfnQueryTimestampsExp;
    pDdiTable->pfnQueryTimestampsExp                     = validation_layer::zeEventQueryTimestampsExp;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeEventPoolCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeEventPoolDestroy;

    dditable.pfnGetIpcHandle                             = pDdiTable->pfnGetIpcHandle;
    pDdiTable->pfnGetIpcHandle                           = validation_layer::zeEventPoolGetIpcHandle;

    dditable.pfnOpenIpcHandle                            = pDdiTable->pfnOpenIpcHandle;
    pDdiTable->pfnOpenIpcHandle                          = validation_layer::zeEventPoolOpenIpcHandle;

    dditable.pfnCloseIpcHandle                           = pDdiTable->pfnCloseIpcHandle;
    pDdiTable->pfnCloseIpcHandle                         = validation_layer::zeEventPoolCloseIpcHandle;

    dditable.pfnPutIpcHandle                             = pDdiTable->pfnPutIpcHandle;
    pDdiTable->pfnPutIpcHandle                           = validation_layer::zeEventPoolPutIpcHandle;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeFenceCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeFenceDestroy;

    dditable.pfnHostSynchronize                          = pDdiTable->pfnHostSynchronize;
    pDdiTable->pfnHostSynchronize                        = validation_layer::zeFenceHostSynchronize;

    dditable.pfnQueryStatus                              = pDdiTable->pfnQueryStatus;
    pDdiTable->pfnQueryStatus                            = validation_layer::zeFenceQueryStatus;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = validation_layer::zeFenceReset;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zeImageGetProperties;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeImageCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeImageDestroy;

    dditable.pfnGetAllocPropertiesExt                    = pDdiTable->pfnGetAllocPropertiesExt;
    pDdiTable->pfnGetAllocPropertiesExt                  = validation_layer::zeImageGetAllocPropertiesExt;

    dditable.pfnViewCreateExt                            = pDdiTable->pfnViewCreateExt;
    pDdiTable->pfnViewCreateExt                          = validation_layer::zeImageViewCreateExt;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetMemoryPropertiesExp                   = pDdiTable->pfnGetMemoryPropertiesExp;
    pDdiTable->pfnGetMemoryPropertiesExp                 = validation_layer::zeImageGetMemoryPropertiesExp;

    dditable.pfnViewCreateExp                            = pDdiTable->pfnViewCreateExp;
    pDdiTable->pfnViewCreateExp                          = validation_layer::zeImageViewCreateExp;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeKernelCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeKernelDestroy;

    dditable.pfnSetCacheConfig                           = pDdiTable->pfnSetCacheConfig;
    pDdiTable->pfnSetCacheConfig                         = validation_layer::zeKernelSetCacheConfig;

    dditable.pfnSetGroupSize                             = pDdiTable->pfnSetGroupSize;
    pDdiTable->pfnSetGroupSize                           = validation_layer::zeKernelSetGroupSize;

    dditable.pfnSuggestGroupSize                         = pDdiTable->pfnSuggestGroupSize;
    pDdiTable->pfnSuggestGroupSize                       = validation_layer::zeKernelSuggestGroupSize;

    dditable.pfnSuggestMaxCooperativeGroupCount          = pDdiTable->pfnSuggestMaxCooperativeGroupCount;
    pDdiTable->pfnSuggestMaxCooperativeGroupCount        = validation_layer::zeKernelSuggestMaxCooperativeGroupCount;

    dditable.pfnSetArgumentValue                         = pDdiTable->pfnSetArgumentValue;
    pDdiTable->pfnSetArgumentValue                       = validation_layer::zeKernelSetArgumentValue;

    dditable.pfnSetIndirectAccess                        = pDdiTable->pfnSetIndirectAccess;
    pDdiTable->pfnSetIndirectAccess                      = validation_layer::zeKernelSetIndirectAccess;

    dditable.pfnGetIndirectAccess                        = pDdiTable->pfnGetIndirectAccess;
    pDdiTable->pfnGetIndirectAccess                      = validation_layer::zeKernelGetIndirectAccess;

    dditable.pfnGetSourceAttributes                      = pDdiTable->pfnGetSourceAttributes;
    pDdiTable->pfnGetSourceAttributes                    = validation_layer::zeKernelGetSourceAttributes;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zeKernelGetProperties;

    dditable.pfnGetName                                  = pDdiTable->pfnGetName;
    pDdiTable->pfnGetName                                = validation_layer::zeKernelGetName;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnSetGlobalOffsetExp                       = pDdiTable->pfnSetGlobalOffsetExp;
    pDdiTable->pfnSetGlobalOffsetExp                     = validation_layer::zeKernelSetGlobalOffsetExp;

    dditable.pfnSchedulingHintExp                        = pDdiTable->pfnSchedulingHintExp;
    pDdiTable->pfnSchedulingHintExp                      = validation_layer::zeKernelSchedulingHintExp;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnAllocShared                              = pDdiTable->pfnAllocShared;
    pDdiTable->pfnAllocShared                            = validation_layer::zeMemAllocShared;

    dditable.pfnAllocDevice                              = pDdiTable->pfnAllocDevice;
    pDdiTable->pfnAllocDevice                            = validation_layer::zeMemAllocDevice;

    dditable.pfnAllocHost                                = pDdiTable->pfnAllocHost;
    pDdiTable->pfnAllocHost                              = validation_layer::zeMemAllocHost;

    dditable.pfnFree                                     = pDdiTable->pfnFree;
    pDdiTable->pfnFree                                   = validation_layer::zeMemFree;

    dditable.pfnGetAllocProperties                       = pDdiTable->pfnGetAllocProperties;
    pDdiTable->pfnGetAllocProperties                     = validation_layer::zeMemGetAllocProperties;

    dditable.pfnGetAddressRange                          = pDdiTable->pfnGetAddressRange;
    pDdiTable->pfnGetAddressRange                        = validation_layer::zeMemGetAddressRange;

    dditable.pfnGetIpcHandle                             = pDdiTable->pfnGetIpcHandle;
    pDdiTable->pfnGetIpcHandle                           = validation_layer::zeMemGetIpcHandle;

    dditable.pfnOpenIpcHandle                            = pDdiTable->pfnOpenIpcHandle;
    pDdiTable->pfnOpenIpcHandle                          = validation_layer::zeMemOpenIpcHandle;

    dditable.pfnCloseIpcHandle                           = pDdiTable->pfnCloseIpcHandle;
    pDdiTable->pfnCloseIpcHandle                         = validation_layer::zeMemCloseIpcHandle;

    dditable.pfnFreeExt                                  = pDdiTable->pfnFreeExt;
    pDdiTable->pfnFreeExt                                = validation_layer::zeMemFreeExt;

    dditable.pfnPutIpcHandle                             = pDdiTable->pfnPutIpcHandle;
    pDdiTable->pfnPutIpcHandle                           = validation_layer::zeMemPutIpcHandle;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetIpcHandleFromFileDescriptorExp        = pDdiTable->pfnGetIpcHandleFromFileDescriptorExp;
    pDdiTable->pfnGetIpcHandleFromFileDescriptorExp      = validation_layer::zeMemGetIpcHandleFromFileDescriptorExp;

    dditable.pfnGetFileDescriptorFromIpcHandleExp        = pDdiTable->pfnGetFileDescriptorFromIpcHandleExp;
    pDdiTable->pfnGetFileDescriptorFromIpcHandleExp      = validation_layer::zeMemGetFileDescriptorFromIpcHandleExp;

    dditable.pfnSetAtomicAccessAttributeExp              = pDdiTable->pfnSetAtomicAccessAttributeExp;
    pDdiTable->pfnSetAtomicAccessAttributeExp            = validation_layer::zeMemSetAtomicAccessAttributeExp;

    dditable.pfnGetAtomicAccessAttributeExp              = pDdiTable->pfnGetAtomicAccessAttributeExp;
    pDdiTable->pfnGetAtomicAccessAttributeExp            = validation_layer::zeMemGetAtomicAccessAttributeExp;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeModuleCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeModuleDestroy;

    dditable.pfnDynamicLink                              = pDdiTable->pfnDynamicLink;
    pDdiTable->pfnDynamicLink                            = validation_layer::zeModuleDynamicLink;

    dditable.pfnGetNativeBinary                          = pDdiTable->pfnGetNativeBinary;
    pDdiTable->pfnGetNativeBinary                        = validation_layer::zeModuleGetNativeBinary;

    dditable.pfnGetGlobalPointer                         = pDdiTable->pfnGetGlobalPointer;
    pDdiTable->pfnGetGlobalPointer                       = validation_layer::zeModuleGetGlobalPointer;

    dditable.pfnGetKernelNames                           = pDdiTable->pfnGetKernelNames;
    pDdiTable->pfnGetKernelNames                         = validation_layer::zeModuleGetKernelNames;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zeModuleGetProperties;

    dditable.pfnGetFunctionPointer                       = pDdiTable->pfnGetFunctionPointer;
    pDdiTable->pfnGetFunctionPointer                     = validation_layer::zeModuleGetFunctionPointer;

    dditable.pfnInspectLinkageExt                        = pDdiTable->pfnInspectLinkageExt;
    pDdiTable->pfnInspectLinkageExt                      = validation_layer::zeModuleInspectLinkageExt;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeModuleBuildLogDestroy;

    dditable.pfnGetString                                = pDdiTable->pfnGetString;
    pDdiTable->pfnGetString                              = validation_layer::zeModuleBuildLogGetString;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zePhysicalMemCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zePhysicalMemDestroy;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zeSamplerCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zeSamplerDestroy;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnReserve                                  = pDdiTable->pfnReserve;
    pDdiTable->pfnReserve                                = validation_layer::zeVirtualMemReserve;

    dditable.pfnFree                                     = pDdiTable->pfnFree;
    pDdiTable->pfnFree                                   = validation_layer::zeVirtualMemFree;

    dditable.pfnQueryPageSize                            = pDdiTable->pfnQueryPageSize;
    pDdiTable->pfnQueryPageSize                          = validation_layer::zeVirtualMemQueryPageSize;

    dditable.pfnMap                                      = pDdiTable->pfnMap;
    pDdiTable->pfnMap                                    = validation_layer::zeVirtualMemMap;

    dditable.pfnUnmap                                    = pDdiTable->pfnUnmap;
    pDdiTable->pfnUnmap                                  = validation_layer::zeVirtualMemUnmap;

    dditable.pfnSetAccessAttribute                       = pDdiTable->pfnSetAccessAttribute;
    pDdiTable->pfnSetAccessAttribute                     = validation_layer::zeVirtualMemSetAccessAttribute;

    dditable.pfnGetAccessAttribute                       = pDdiTable->pfnGetAccessAttribute;
    pDdiTable->pfnGetAccessAttribute                     = validation_layer::zeVirtualMemGetAccessAttribute;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetExp                                   = pDdiTable->pfnGetExp;
    pDdiTable->pfnGetExp                                 = validation_layer::zeFabricEdgeGetExp;

    dditable.pfnGetVerticesExp                           = pDdiTable->pfnGetVerticesExp;
    pDdiTable->pfnGetVerticesExp                         = validation_layer::zeFabricEdgeGetVerticesExp;

    dditable.pfnGetPropertiesExp                         = pDdiTable->pfnGetPropertiesExp;
    pDdiTable->pfnGetPropertiesExp                       = validation_layer::zeFabricEdgeGetPropertiesExp;

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

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetExp                                   = pDdiTable->pfnGetExp;
    pDdiTable->pfnGetExp                                 = validation_layer::zeFabricVertexGetExp;

    dditable.pfnGetSubVerticesExp                        = pDdiTable->pfnGetSubVerticesExp;
    pDdiTable->pfnGetSubVerticesExp                      = validation_layer::zeFabricVertexGetSubVerticesExp;

    dditable.pfnGetPropertiesExp                         = pDdiTable->pfnGetPropertiesExp;
    pDdiTable->pfnGetPropertiesExp                       = validation_layer::zeFabricVertexGetPropertiesExp;

    dditable.pfnGetDeviceExp                             = pDdiTable->pfnGetDeviceExp;
    pDdiTable->pfnGetDeviceExp                           = validation_layer::zeFabricVertexGetDeviceExp;

    return result;
}

#if defined(__cplusplus)
};
#endif
