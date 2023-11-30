/*
 * ***THIS FILE IS GENERATED. ***
 * See valddi.cpp.mako for modifications
 *
 * Copyright (C) 2019-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_valddi.cpp
 *
 */
#include "ze_validation_layer.h"

namespace validation_layer
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetModuleGetDebugInfo
    __zedlllocal ze_result_t ZE_APICALL
    zetModuleGetDebugInfo(
        zet_module_handle_t hModule,                    ///< [in] handle of the module
        zet_module_debug_info_format_t format,          ///< [in] debug info format requested
        size_t* pSize,                                  ///< [in,out] size of debug info in bytes
        uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
        )
    {
        auto pfnGetDebugInfo = context.zetDdiTable.Module.pfnGetDebugInfo;

        if( nullptr == pfnGetDebugInfo )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetModuleGetDebugInfo( hModule, format, pSize, pDebugInfo );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetModuleGetDebugInfo( hModule, format, pSize, pDebugInfo );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDeviceGetDebugProperties
    __zedlllocal ze_result_t ZE_APICALL
    zetDeviceGetDebugProperties(
        zet_device_handle_t hDevice,                    ///< [in] device handle
        zet_device_debug_properties_t* pDebugProperties ///< [in,out] query result for debug properties
        )
    {
        auto pfnGetDebugProperties = context.zetDdiTable.Device.pfnGetDebugProperties;

        if( nullptr == pfnGetDebugProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetDeviceGetDebugProperties( hDevice, pDebugProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDeviceGetDebugProperties( hDevice, pDebugProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetDebugProperties( hDevice, pDebugProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugAttach
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugAttach(
        zet_device_handle_t hDevice,                    ///< [in] device handle
        const zet_debug_config_t* config,               ///< [in] the debug configuration
        zet_debug_session_handle_t* phDebug             ///< [out] debug session handle
        )
    {
        auto pfnAttach = context.zetDdiTable.Debug.pfnAttach;

        if( nullptr == pfnAttach )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetDebugAttach( hDevice, config, phDebug );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugAttach( hDevice, config, phDebug );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAttach( hDevice, config, phDebug );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugDetach
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugDetach(
        zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
        )
    {
        auto pfnDetach = context.zetDdiTable.Debug.pfnDetach;

        if( nullptr == pfnDetach )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetDebugDetach( hDebug );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugDetach( hDebug );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDetach( hDebug );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugReadEvent
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugReadEvent(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then immediately returns the status of the event;
                                                        ///< if `UINT64_MAX`, then function will not return until complete or
                                                        ///< device is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        zet_debug_event_t* event                        ///< [in,out] a pointer to a ::zet_debug_event_t.
        )
    {
        auto pfnReadEvent = context.zetDdiTable.Debug.pfnReadEvent;

        if( nullptr == pfnReadEvent )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetDebugReadEvent( hDebug, timeout, event );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugReadEvent( hDebug, timeout, event );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnReadEvent( hDebug, timeout, event );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugAcknowledgeEvent
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugAcknowledgeEvent(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        const zet_debug_event_t* event                  ///< [in] a pointer to a ::zet_debug_event_t.
        )
    {
        auto pfnAcknowledgeEvent = context.zetDdiTable.Debug.pfnAcknowledgeEvent;

        if( nullptr == pfnAcknowledgeEvent )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetDebugAcknowledgeEvent( hDebug, event );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugAcknowledgeEvent( hDebug, event );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAcknowledgeEvent( hDebug, event );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugInterrupt
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugInterrupt(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread                       ///< [in] the thread to interrupt
        )
    {
        auto pfnInterrupt = context.zetDdiTable.Debug.pfnInterrupt;

        if( nullptr == pfnInterrupt )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetDebugInterrupt( hDebug, thread );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugInterrupt( hDebug, thread );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnInterrupt( hDebug, thread );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugResume
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugResume(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread                       ///< [in] the thread to resume
        )
    {
        auto pfnResume = context.zetDdiTable.Debug.pfnResume;

        if( nullptr == pfnResume )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetDebugResume( hDebug, thread );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugResume( hDebug, thread );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnResume( hDebug, thread );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugReadMemory
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugReadMemory(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier.
        const zet_debug_memory_space_desc_t* desc,      ///< [in] memory space descriptor
        size_t size,                                    ///< [in] the number of bytes to read
        void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
        )
    {
        auto pfnReadMemory = context.zetDdiTable.Debug.pfnReadMemory;

        if( nullptr == pfnReadMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetDebugReadMemory( hDebug, thread, desc, size, buffer );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugReadMemory( hDebug, thread, desc, size, buffer );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnReadMemory( hDebug, thread, desc, size, buffer );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugWriteMemory
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugWriteMemory(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier.
        const zet_debug_memory_space_desc_t* desc,      ///< [in] memory space descriptor
        size_t size,                                    ///< [in] the number of bytes to write
        const void* buffer                              ///< [in] a buffer holding the pattern to write
        )
    {
        auto pfnWriteMemory = context.zetDdiTable.Debug.pfnWriteMemory;

        if( nullptr == pfnWriteMemory )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetDebugWriteMemory( hDebug, thread, desc, size, buffer );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugWriteMemory( hDebug, thread, desc, size, buffer );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnWriteMemory( hDebug, thread, desc, size, buffer );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugGetRegisterSetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugGetRegisterSetProperties(
        zet_device_handle_t hDevice,                    ///< [in] device handle
        uint32_t* pCount,                               ///< [in,out] pointer to the number of register set properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of register set properties available.
                                                        ///< if count is greater than the number of register set properties
                                                        ///< available, then the driver shall update the value with the correct
                                                        ///< number of registry set properties available.
        zet_debug_regset_properties_t* pRegisterSetProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< register set properties.
                                                        ///< if count is less than the number of register set properties available,
                                                        ///< then driver shall only retrieve that number of register set properties.
        )
    {
        auto pfnGetRegisterSetProperties = context.zetDdiTable.Debug.pfnGetRegisterSetProperties;

        if( nullptr == pfnGetRegisterSetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetDebugGetRegisterSetProperties( hDevice, pCount, pRegisterSetProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugGetRegisterSetProperties( hDevice, pCount, pRegisterSetProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetRegisterSetProperties( hDevice, pCount, pRegisterSetProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugGetThreadRegisterSetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugGetThreadRegisterSetProperties(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier specifying a single stopped thread
        uint32_t* pCount,                               ///< [in,out] pointer to the number of register set properties.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of register set properties available.
                                                        ///< if count is greater than the number of register set properties
                                                        ///< available, then the driver shall update the value with the correct
                                                        ///< number of registry set properties available.
        zet_debug_regset_properties_t* pRegisterSetProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< register set properties.
                                                        ///< if count is less than the number of register set properties available,
                                                        ///< then driver shall only retrieve that number of register set properties.
        )
    {
        auto pfnGetThreadRegisterSetProperties = context.zetDdiTable.Debug.pfnGetThreadRegisterSetProperties;

        if( nullptr == pfnGetThreadRegisterSetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetDebugGetThreadRegisterSetProperties( hDebug, thread, pCount, pRegisterSetProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugGetThreadRegisterSetProperties( hDebug, thread, pCount, pRegisterSetProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetThreadRegisterSetProperties( hDebug, thread, pCount, pRegisterSetProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugReadRegisters
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugReadRegisters(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier
        uint32_t type,                                  ///< [in] register set type
        uint32_t start,                                 ///< [in] the starting offset into the register state area; must be less
                                                        ///< than the `count` member of ::zet_debug_regset_properties_t for the
                                                        ///< type
        uint32_t count,                                 ///< [in] the number of registers to read; start+count must be less than or
                                                        ///< equal to the `count` member of ::zet_debug_register_group_properties_t
                                                        ///< for the type
        void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
        )
    {
        auto pfnReadRegisters = context.zetDdiTable.Debug.pfnReadRegisters;

        if( nullptr == pfnReadRegisters )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetDebugReadRegisters( hDebug, thread, type, start, count, pRegisterValues );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugReadRegisters( hDebug, thread, type, start, count, pRegisterValues );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnReadRegisters( hDebug, thread, type, start, count, pRegisterValues );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugWriteRegisters
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugWriteRegisters(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier
        uint32_t type,                                  ///< [in] register set type
        uint32_t start,                                 ///< [in] the starting offset into the register state area; must be less
                                                        ///< than the `count` member of ::zet_debug_regset_properties_t for the
                                                        ///< type
        uint32_t count,                                 ///< [in] the number of registers to write; start+count must be less than
                                                        ///< or equal to the `count` member of
                                                        ///< ::zet_debug_register_group_properties_t for the type
        void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
        )
    {
        auto pfnWriteRegisters = context.zetDdiTable.Debug.pfnWriteRegisters;

        if( nullptr == pfnWriteRegisters )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetDebugWriteRegisters( hDebug, thread, type, start, count, pRegisterValues );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugWriteRegisters( hDebug, thread, type, start, count, pRegisterValues );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnWriteRegisters( hDebug, thread, type, start, count, pRegisterValues );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGet
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupGet(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metric groups.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metric groups available.
                                                        ///< if count is greater than the number of metric groups available, then
                                                        ///< the driver shall update the value with the correct number of metric
                                                        ///< groups available.
        zet_metric_group_handle_t* phMetricGroups       ///< [in,out][optional][range(0, *pCount)] array of handle of metric groups.
                                                        ///< if count is less than the number of metric groups available, then
                                                        ///< driver shall only retrieve that number of metric groups.
        )
    {
        auto pfnGet = context.zetDdiTable.MetricGroup.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricGroupGet( hDevice, pCount, phMetricGroups );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupGet( hDevice, pCount, phMetricGroups );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGet( hDevice, pCount, phMetricGroups );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phMetricGroups) && (i < *pCount); ++i){
                if (phMetricGroups[i]){
                    context.handleLifetime->addHandle( phMetricGroups[i] );
                    context.handleLifetime->addDependent( hDevice, phMetricGroups[i] );
                }
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupGetProperties(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
        )
    {
        auto pfnGetProperties = context.zetDdiTable.MetricGroup.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricGroupGetProperties( hMetricGroup, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupGetProperties( hMetricGroup, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hMetricGroup, pProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupCalculateMetricValues
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupCalculateMetricValues(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_group_calculation_type_t type,       ///< [in] calculation type to be applied on raw data
        size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
        const uint8_t* pRawData,                        ///< [in][range(0, rawDataSize)] buffer of raw data to calculate
        uint32_t* pMetricValueCount,                    ///< [in,out] pointer to number of metric values calculated.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metric values to be calculated.
                                                        ///< if count is greater than the number available in the raw data buffer,
                                                        ///< then the driver shall update the value with the actual number of
                                                        ///< metric values to be calculated.
        zet_typed_value_t* pMetricValues                ///< [in,out][optional][range(0, *pMetricValueCount)] buffer of calculated metrics.
                                                        ///< if count is less than the number available in the raw data buffer,
                                                        ///< then driver shall only calculate that number of metric values.
        )
    {
        auto pfnCalculateMetricValues = context.zetDdiTable.MetricGroup.pfnCalculateMetricValues;

        if( nullptr == pfnCalculateMetricValues )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricGroupCalculateMetricValues( hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupCalculateMetricValues( hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCalculateMetricValues( hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGet
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGet(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metrics.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metrics available.
                                                        ///< if count is greater than the number of metrics available, then the
                                                        ///< driver shall update the value with the correct number of metrics available.
        zet_metric_handle_t* phMetrics                  ///< [in,out][optional][range(0, *pCount)] array of handle of metrics.
                                                        ///< if count is less than the number of metrics available, then driver
                                                        ///< shall only retrieve that number of metrics.
        )
    {
        auto pfnGet = context.zetDdiTable.Metric.pfnGet;

        if( nullptr == pfnGet )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricGet( hMetricGroup, pCount, phMetrics );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGet( hMetricGroup, pCount, phMetrics );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGet( hMetricGroup, pCount, phMetrics );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phMetrics) && (i < *pCount); ++i){
                if (phMetrics[i]){
                    context.handleLifetime->addHandle( phMetrics[i] );
                    context.handleLifetime->addDependent( hMetricGroup, phMetrics[i] );
                }
            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGetProperties(
        zet_metric_handle_t hMetric,                    ///< [in] handle of the metric
        zet_metric_properties_t* pProperties            ///< [in,out] metric properties
        )
    {
        auto pfnGetProperties = context.zetDdiTable.Metric.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricGetProperties( hMetric, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGetProperties( hMetric, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProperties( hMetric, pProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetContextActivateMetricGroups
    __zedlllocal ze_result_t ZE_APICALL
    zetContextActivateMetricGroups(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t count,                                 ///< [in] metric group count to activate; must be 0 if `nullptr ==
                                                        ///< phMetricGroups`
        zet_metric_group_handle_t* phMetricGroups       ///< [in][optional][range(0, count)] handles of the metric groups to activate.
                                                        ///< nullptr deactivates all previously used metric groups.
                                                        ///< all metrics groups must come from a different domains.
                                                        ///< metric query and metric stream must use activated metric groups.
        )
    {
        auto pfnActivateMetricGroups = context.zetDdiTable.Context.pfnActivateMetricGroups;

        if( nullptr == pfnActivateMetricGroups )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetContextActivateMetricGroups( hContext, hDevice, count, phMetricGroups );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetContextActivateMetricGroups( hContext, hDevice, count, phMetricGroups );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnActivateMetricGroups( hContext, hDevice, count, phMetricGroups );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricStreamerOpen
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricStreamerOpen(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_streamer_desc_t* desc,               ///< [in,out] metric streamer descriptor
        ze_event_handle_t hNotificationEvent,           ///< [in][optional] event used for report availability notification
        zet_metric_streamer_handle_t* phMetricStreamer  ///< [out] handle of metric streamer
        )
    {
        auto pfnOpen = context.zetDdiTable.MetricStreamer.pfnOpen;

        if( nullptr == pfnOpen )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricStreamerOpen( hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricStreamerOpen( hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnOpen( hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricStreamerMarker
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMetricStreamerMarker(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_streamer_handle_t hMetricStreamer,   ///< [in] handle of the metric streamer
        uint32_t value                                  ///< [in] streamer marker value
        )
    {
        auto pfnAppendMetricStreamerMarker = context.zetDdiTable.CommandList.pfnAppendMetricStreamerMarker;

        if( nullptr == pfnAppendMetricStreamerMarker )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetCommandListAppendMetricStreamerMarker( hCommandList, hMetricStreamer, value );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetCommandListAppendMetricStreamerMarker( hCommandList, hMetricStreamer, value );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendMetricStreamerMarker( hCommandList, hMetricStreamer, value );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricStreamerClose
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricStreamerClose(
        zet_metric_streamer_handle_t hMetricStreamer    ///< [in][release] handle of the metric streamer
        )
    {
        auto pfnClose = context.zetDdiTable.MetricStreamer.pfnClose;

        if( nullptr == pfnClose )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricStreamerClose( hMetricStreamer );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricStreamerClose( hMetricStreamer );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnClose( hMetricStreamer );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricStreamerReadData
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricStreamerReadData(
        zet_metric_streamer_handle_t hMetricStreamer,   ///< [in] handle of the metric streamer
        uint32_t maxReportCount,                        ///< [in] the maximum number of reports the application wants to receive.
                                                        ///< if `UINT32_MAX`, then function will retrieve all reports available
        size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                        ///< if size is zero, then the driver will update the value with the total
                                                        ///< size in bytes needed for all reports available.
                                                        ///< if size is non-zero, then driver will only retrieve the number of
                                                        ///< reports that fit into the buffer.
                                                        ///< if size is larger than size needed for all reports, then driver will
                                                        ///< update the value with the actual size needed.
        uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing streamer
                                                        ///< reports in raw format
        )
    {
        auto pfnReadData = context.zetDdiTable.MetricStreamer.pfnReadData;

        if( nullptr == pfnReadData )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricStreamerReadData( hMetricStreamer, maxReportCount, pRawDataSize, pRawData );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricStreamerReadData( hMetricStreamer, maxReportCount, pRawDataSize, pRawData );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnReadData( hMetricStreamer, maxReportCount, pRawDataSize, pRawData );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryPoolCreate
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryPoolCreate(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
        const zet_metric_query_pool_desc_t* desc,       ///< [in] metric query pool descriptor
        zet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
        )
    {
        auto pfnCreate = context.zetDdiTable.MetricQueryPool.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricQueryPoolCreate( hContext, hDevice, hMetricGroup, desc, phMetricQueryPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricQueryPoolCreate( hContext, hDevice, hMetricGroup, desc, phMetricQueryPool );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreate( hContext, hDevice, hMetricGroup, desc, phMetricQueryPool );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phMetricQueryPool){
                context.handleLifetime->addHandle( *phMetricQueryPool );
                context.handleLifetime->addDependent( hContext, *phMetricQueryPool );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryPoolDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryPoolDestroy(
        zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
        )
    {
        auto pfnDestroy = context.zetDdiTable.MetricQueryPool.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricQueryPoolDestroy( hMetricQueryPool );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricQueryPoolDestroy( hMetricQueryPool );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroy( hMetricQueryPool );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryCreate
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryCreate(
        zet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
        uint32_t index,                                 ///< [in] index of the query within the pool
        zet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
        )
    {
        auto pfnCreate = context.zetDdiTable.MetricQuery.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricQueryCreate( hMetricQueryPool, index, phMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricQueryCreate( hMetricQueryPool, index, phMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreate( hMetricQueryPool, index, phMetricQuery );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phMetricQuery){
                context.handleLifetime->addHandle( *phMetricQuery );
                context.handleLifetime->addDependent( hMetricQueryPool, *phMetricQuery );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryDestroy(
        zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
        )
    {
        auto pfnDestroy = context.zetDdiTable.MetricQuery.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricQueryDestroy( hMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricQueryDestroy( hMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroy( hMetricQuery );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryReset
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryReset(
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
        )
    {
        auto pfnReset = context.zetDdiTable.MetricQuery.pfnReset;

        if( nullptr == pfnReset )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricQueryReset( hMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricQueryReset( hMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnReset( hMetricQuery );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricQueryBegin
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMetricQueryBegin(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
        )
    {
        auto pfnAppendMetricQueryBegin = context.zetDdiTable.CommandList.pfnAppendMetricQueryBegin;

        if( nullptr == pfnAppendMetricQueryBegin )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetCommandListAppendMetricQueryBegin( hCommandList, hMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetCommandListAppendMetricQueryBegin( hCommandList, hMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricQueryEnd
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMetricQueryEnd(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in] must be zero
        ze_event_handle_t* phWaitEvents                 ///< [in][mbz] must be nullptr
        )
    {
        auto pfnAppendMetricQueryEnd = context.zetDdiTable.CommandList.pfnAppendMetricQueryEnd;

        if( nullptr == pfnAppendMetricQueryEnd )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetCommandListAppendMetricQueryEnd( hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetCommandListAppendMetricQueryEnd( hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricMemoryBarrier
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMetricMemoryBarrier(
        zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
        )
    {
        auto pfnAppendMetricMemoryBarrier = context.zetDdiTable.CommandList.pfnAppendMetricMemoryBarrier;

        if( nullptr == pfnAppendMetricMemoryBarrier )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetCommandListAppendMetricMemoryBarrier( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetCommandListAppendMetricMemoryBarrier( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnAppendMetricMemoryBarrier( hCommandList );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryGetData
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryGetData(
        zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                        ///< if size is zero, then the driver will update the value with the total
                                                        ///< size in bytes needed for all reports available.
                                                        ///< if size is non-zero, then driver will only retrieve the number of
                                                        ///< reports that fit into the buffer.
                                                        ///< if size is larger than size needed for all reports, then driver will
                                                        ///< update the value with the actual size needed.
        uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing query
                                                        ///< reports in raw format
        )
    {
        auto pfnGetData = context.zetDdiTable.MetricQuery.pfnGetData;

        if( nullptr == pfnGetData )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricQueryGetData( hMetricQuery, pRawDataSize, pRawData );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricQueryGetData( hMetricQuery, pRawDataSize, pRawData );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetData( hMetricQuery, pRawDataSize, pRawData );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetKernelGetProfileInfo
    __zedlllocal ze_result_t ZE_APICALL
    zetKernelGetProfileInfo(
        zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
        zet_profile_properties_t* pProfileProperties    ///< [out] pointer to profile properties
        )
    {
        auto pfnGetProfileInfo = context.zetDdiTable.Kernel.pfnGetProfileInfo;

        if( nullptr == pfnGetProfileInfo )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetKernelGetProfileInfo( hKernel, pProfileProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetKernelGetProfileInfo( hKernel, pProfileProperties );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetProfileInfo( hKernel, pProfileProperties );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerExpCreate
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpCreate(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        const zet_tracer_exp_desc_t* desc,              ///< [in] pointer to tracer descriptor
        zet_tracer_exp_handle_t* phTracer               ///< [out] pointer to handle of tracer object created
        )
    {
        auto pfnCreate = context.zetDdiTable.TracerExp.pfnCreate;

        if( nullptr == pfnCreate )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetTracerExpCreate( hContext, desc, phTracer );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetTracerExpCreate( hContext, desc, phTracer );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCreate( hContext, desc, phTracer );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phTracer){
                context.handleLifetime->addHandle( *phTracer );
                context.handleLifetime->addDependent( hContext, *phTracer );

            }
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerExpDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpDestroy(
        zet_tracer_exp_handle_t hTracer                 ///< [in][release] handle of tracer object to destroy
        )
    {
        auto pfnDestroy = context.zetDdiTable.TracerExp.pfnDestroy;

        if( nullptr == pfnDestroy )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetTracerExpDestroy( hTracer );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetTracerExpDestroy( hTracer );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnDestroy( hTracer );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerExpSetPrologues
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpSetPrologues(
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        auto pfnSetPrologues = context.zetDdiTable.TracerExp.pfnSetPrologues;

        if( nullptr == pfnSetPrologues )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetTracerExpSetPrologues( hTracer, pCoreCbs );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetTracerExpSetPrologues( hTracer, pCoreCbs );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetPrologues( hTracer, pCoreCbs );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerExpSetEpilogues
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpSetEpilogues(
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        auto pfnSetEpilogues = context.zetDdiTable.TracerExp.pfnSetEpilogues;

        if( nullptr == pfnSetEpilogues )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetTracerExpSetEpilogues( hTracer, pCoreCbs );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetTracerExpSetEpilogues( hTracer, pCoreCbs );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetEpilogues( hTracer, pCoreCbs );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerExpSetEnabled
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpSetEnabled(
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
        )
    {
        auto pfnSetEnabled = context.zetDdiTable.TracerExp.pfnSetEnabled;

        if( nullptr == pfnSetEnabled )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetTracerExpSetEnabled( hTracer, enable );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetTracerExpSetEnabled( hTracer, enable );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnSetEnabled( hTracer, enable );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupCalculateMultipleMetricValuesExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupCalculateMultipleMetricValuesExp(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_group_calculation_type_t type,       ///< [in] calculation type to be applied on raw data
        size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
        const uint8_t* pRawData,                        ///< [in][range(0, rawDataSize)] buffer of raw data to calculate
        uint32_t* pSetCount,                            ///< [in,out] pointer to number of metric sets.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metric sets to be calculated.
                                                        ///< if count is greater than the number available in the raw data buffer,
                                                        ///< then the driver shall update the value with the actual number of
                                                        ///< metric sets to be calculated.
        uint32_t* pTotalMetricValueCount,               ///< [in,out] pointer to number of the total number of metric values
                                                        ///< calculated, for all metric sets.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metric values to be calculated.
                                                        ///< if count is greater than the number available in the raw data buffer,
                                                        ///< then the driver shall update the value with the actual number of
                                                        ///< metric values to be calculated.
        uint32_t* pMetricCounts,                        ///< [in,out][optional][range(0, *pSetCount)] buffer of metric counts per
                                                        ///< metric set.
        zet_typed_value_t* pMetricValues                ///< [in,out][optional][range(0, *pTotalMetricValueCount)] buffer of
                                                        ///< calculated metrics.
                                                        ///< if count is less than the number available in the raw data buffer,
                                                        ///< then driver shall only calculate that number of metric values.
        )
    {
        auto pfnCalculateMultipleMetricValuesExp = context.zetDdiTable.MetricGroupExp.pfnCalculateMultipleMetricValuesExp;

        if( nullptr == pfnCalculateMultipleMetricValuesExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricGroupCalculateMultipleMetricValuesExp( hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupCalculateMultipleMetricValuesExp( hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCalculateMultipleMetricValuesExp( hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGetGlobalTimestampsExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupGetGlobalTimestampsExp(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        ze_bool_t synchronizedWithHost,                 ///< [in] Returns the timestamps synchronized to the host or the device.
        uint64_t* globalTimestamp,                      ///< [out] Device timestamp.
        uint64_t* metricTimestamp                       ///< [out] Metric timestamp.
        )
    {
        auto pfnGetGlobalTimestampsExp = context.zetDdiTable.MetricGroupExp.pfnGetGlobalTimestampsExp;

        if( nullptr == pfnGetGlobalTimestampsExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricGroupGetGlobalTimestampsExp( hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupGetGlobalTimestampsExp( hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetGlobalTimestampsExp( hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGetExportDataExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupGetExportDataExp(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        const uint8_t* pRawData,                        ///< [in] buffer of raw data
        size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
        size_t* pExportDataSize,                        ///< [in,out] size in bytes of export data buffer
                                                        ///< if size is zero, then the driver shall update the value with the
                                                        ///< number of bytes necessary to store the exported data.
                                                        ///< if size is greater than required, then the driver shall update the
                                                        ///< value with the actual number of bytes necessary to store the exported data.
        uint8_t * pExportData                           ///< [in,out][optional][range(0, *pExportDataSize)] buffer of exported data.
        )
    {
        auto pfnGetExportDataExp = context.zetDdiTable.MetricGroupExp.pfnGetExportDataExp;

        if( nullptr == pfnGetExportDataExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricGroupGetExportDataExp( hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupGetExportDataExp( hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnGetExportDataExp( hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData );

        if( result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupCalculateMetricExportDataExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupCalculateMetricExportDataExp(
        ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
        zet_metric_group_calculation_type_t type,       ///< [in] calculation type to be applied on raw data
        size_t exportDataSize,                          ///< [in] size in bytes of exported data buffer
        const uint8_t* pExportData,                     ///< [in][range(0, exportDataSize)] buffer of exported data to calculate
        zet_metric_calculate_exp_desc_t* pCalculateDescriptor,  ///< [in] descriptor specifying calculation specific parameters
        uint32_t* pSetCount,                            ///< [in,out] pointer to number of metric sets.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metric sets to be calculated.
                                                        ///< if count is greater than the number available in the raw data buffer,
                                                        ///< then the driver shall update the value with the actual number of
                                                        ///< metric sets to be calculated.
        uint32_t* pTotalMetricValueCount,               ///< [in,out] pointer to number of the total number of metric values
                                                        ///< calculated, for all metric sets.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metric values to be calculated.
                                                        ///< if count is greater than the number available in the raw data buffer,
                                                        ///< then the driver shall update the value with the actual number of
                                                        ///< metric values to be calculated.
        uint32_t* pMetricCounts,                        ///< [in,out][optional][range(0, *pSetCount)] buffer of metric counts per
                                                        ///< metric set.
        zet_typed_value_t* pMetricValues                ///< [in,out][optional][range(0, *pTotalMetricValueCount)] buffer of
                                                        ///< calculated metrics.
                                                        ///< if count is less than the number available in the raw data buffer,
                                                        ///< then driver shall only calculate that number of metric values.
        )
    {
        auto pfnCalculateMetricExportDataExp = context.zetDdiTable.MetricGroupExp.pfnCalculateMetricExportDataExp;

        if( nullptr == pfnCalculateMetricExportDataExp )
            return ZE_RESULT_ERROR_UNSUPPORTED_FEATURE;

        if( context.enableParameterValidation )
        {
            auto result = context.paramValidation->zetParamValidation.zetMetricGroupCalculateMetricExportDataExp( hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
            if(result!=ZE_RESULT_SUCCESS) return result;
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupCalculateMetricExportDataExp( hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
            if(result!=ZE_RESULT_SUCCESS) return result;    
        }

        auto result = pfnCalculateMetricExportDataExp( hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
        return result;
    }

} // namespace validation_layer

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.Device;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetDebugProperties                       = pDdiTable->pfnGetDebugProperties;
    pDdiTable->pfnGetDebugProperties                     = validation_layer::zetDeviceGetDebugProperties;

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
zetGetContextProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_context_dditable_t* pDdiTable               ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.Context;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnActivateMetricGroups                     = pDdiTable->pfnActivateMetricGroups;
    pDdiTable->pfnActivateMetricGroups                   = validation_layer::zetContextActivateMetricGroups;

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
zetGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.CommandList;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnAppendMetricStreamerMarker               = pDdiTable->pfnAppendMetricStreamerMarker;
    pDdiTable->pfnAppendMetricStreamerMarker             = validation_layer::zetCommandListAppendMetricStreamerMarker;

    dditable.pfnAppendMetricQueryBegin                   = pDdiTable->pfnAppendMetricQueryBegin;
    pDdiTable->pfnAppendMetricQueryBegin                 = validation_layer::zetCommandListAppendMetricQueryBegin;

    dditable.pfnAppendMetricQueryEnd                     = pDdiTable->pfnAppendMetricQueryEnd;
    pDdiTable->pfnAppendMetricQueryEnd                   = validation_layer::zetCommandListAppendMetricQueryEnd;

    dditable.pfnAppendMetricMemoryBarrier                = pDdiTable->pfnAppendMetricMemoryBarrier;
    pDdiTable->pfnAppendMetricMemoryBarrier              = validation_layer::zetCommandListAppendMetricMemoryBarrier;

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
zetGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_kernel_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.Kernel;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetProfileInfo                           = pDdiTable->pfnGetProfileInfo;
    pDdiTable->pfnGetProfileInfo                         = validation_layer::zetKernelGetProfileInfo;

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
zetGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_module_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.Module;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGetDebugInfo                             = pDdiTable->pfnGetDebugInfo;
    pDdiTable->pfnGetDebugInfo                           = validation_layer::zetModuleGetDebugInfo;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Debug table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetDebugProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_debug_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.Debug;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnAttach                                   = pDdiTable->pfnAttach;
    pDdiTable->pfnAttach                                 = validation_layer::zetDebugAttach;

    dditable.pfnDetach                                   = pDdiTable->pfnDetach;
    pDdiTable->pfnDetach                                 = validation_layer::zetDebugDetach;

    dditable.pfnReadEvent                                = pDdiTable->pfnReadEvent;
    pDdiTable->pfnReadEvent                              = validation_layer::zetDebugReadEvent;

    dditable.pfnAcknowledgeEvent                         = pDdiTable->pfnAcknowledgeEvent;
    pDdiTable->pfnAcknowledgeEvent                       = validation_layer::zetDebugAcknowledgeEvent;

    dditable.pfnInterrupt                                = pDdiTable->pfnInterrupt;
    pDdiTable->pfnInterrupt                              = validation_layer::zetDebugInterrupt;

    dditable.pfnResume                                   = pDdiTable->pfnResume;
    pDdiTable->pfnResume                                 = validation_layer::zetDebugResume;

    dditable.pfnReadMemory                               = pDdiTable->pfnReadMemory;
    pDdiTable->pfnReadMemory                             = validation_layer::zetDebugReadMemory;

    dditable.pfnWriteMemory                              = pDdiTable->pfnWriteMemory;
    pDdiTable->pfnWriteMemory                            = validation_layer::zetDebugWriteMemory;

    dditable.pfnGetRegisterSetProperties                 = pDdiTable->pfnGetRegisterSetProperties;
    pDdiTable->pfnGetRegisterSetProperties               = validation_layer::zetDebugGetRegisterSetProperties;

    dditable.pfnReadRegisters                            = pDdiTable->pfnReadRegisters;
    pDdiTable->pfnReadRegisters                          = validation_layer::zetDebugReadRegisters;

    dditable.pfnWriteRegisters                           = pDdiTable->pfnWriteRegisters;
    pDdiTable->pfnWriteRegisters                         = validation_layer::zetDebugWriteRegisters;

    dditable.pfnGetThreadRegisterSetProperties           = pDdiTable->pfnGetThreadRegisterSetProperties;
    pDdiTable->pfnGetThreadRegisterSetProperties         = validation_layer::zetDebugGetThreadRegisterSetProperties;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Metric table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.Metric;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = validation_layer::zetMetricGet;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zetMetricGetProperties;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricGroup table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricGroupProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_group_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.MetricGroup;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnGet                                      = pDdiTable->pfnGet;
    pDdiTable->pfnGet                                    = validation_layer::zetMetricGroupGet;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = validation_layer::zetMetricGroupGetProperties;

    dditable.pfnCalculateMetricValues                    = pDdiTable->pfnCalculateMetricValues;
    pDdiTable->pfnCalculateMetricValues                  = validation_layer::zetMetricGroupCalculateMetricValues;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricGroupExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricGroupExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_group_exp_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.MetricGroupExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCalculateMultipleMetricValuesExp         = pDdiTable->pfnCalculateMultipleMetricValuesExp;
    pDdiTable->pfnCalculateMultipleMetricValuesExp       = validation_layer::zetMetricGroupCalculateMultipleMetricValuesExp;

    dditable.pfnGetGlobalTimestampsExp                   = pDdiTable->pfnGetGlobalTimestampsExp;
    pDdiTable->pfnGetGlobalTimestampsExp                 = validation_layer::zetMetricGroupGetGlobalTimestampsExp;

    dditable.pfnGetExportDataExp                         = pDdiTable->pfnGetExportDataExp;
    pDdiTable->pfnGetExportDataExp                       = validation_layer::zetMetricGroupGetExportDataExp;

    dditable.pfnCalculateMetricExportDataExp             = pDdiTable->pfnCalculateMetricExportDataExp;
    pDdiTable->pfnCalculateMetricExportDataExp           = validation_layer::zetMetricGroupCalculateMetricExportDataExp;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQuery table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricQueryProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.MetricQuery;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zetMetricQueryCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zetMetricQueryDestroy;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = validation_layer::zetMetricQueryReset;

    dditable.pfnGetData                                  = pDdiTable->pfnGetData;
    pDdiTable->pfnGetData                                = validation_layer::zetMetricQueryGetData;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricQueryPool table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricQueryPoolProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_query_pool_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.MetricQueryPool;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zetMetricQueryPoolCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zetMetricQueryPoolDestroy;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricStreamer table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricStreamerProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_streamer_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.MetricStreamer;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnOpen                                     = pDdiTable->pfnOpen;
    pDdiTable->pfnOpen                                   = validation_layer::zetMetricStreamerOpen;

    dditable.pfnClose                                    = pDdiTable->pfnClose;
    pDdiTable->pfnClose                                  = validation_layer::zetMetricStreamerClose;

    dditable.pfnReadData                                 = pDdiTable->pfnReadData;
    pDdiTable->pfnReadData                               = validation_layer::zetMetricStreamerReadData;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's TracerExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetTracerExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_tracer_exp_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.TracerExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (ZE_MAJOR_VERSION(validation_layer::context.version) != ZE_MAJOR_VERSION(version) ||
        ZE_MINOR_VERSION(validation_layer::context.version) > ZE_MINOR_VERSION(version))
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = validation_layer::zetTracerExpCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = validation_layer::zetTracerExpDestroy;

    dditable.pfnSetPrologues                             = pDdiTable->pfnSetPrologues;
    pDdiTable->pfnSetPrologues                           = validation_layer::zetTracerExpSetPrologues;

    dditable.pfnSetEpilogues                             = pDdiTable->pfnSetEpilogues;
    pDdiTable->pfnSetEpilogues                           = validation_layer::zetTracerExpSetEpilogues;

    dditable.pfnSetEnabled                               = pDdiTable->pfnSetEnabled;
    pDdiTable->pfnSetEnabled                             = validation_layer::zetTracerExpSetEnabled;

    return result;
}

#if defined(__cplusplus)
};
#endif
