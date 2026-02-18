/*
 * ***THIS FILE IS GENERATED. ***
 * See valddi.cpp.mako for modifications
 *
 * Copyright (C) 2019-2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zet_valddi.cpp
 *
 */
#include "ze_validation_layer.h"
#include <sstream>

// Define a macro for marking potentially unused functions
#if defined(_MSC_VER)
    // MSVC doesn't support __attribute__((unused)), just omit the marking
    #define VALIDATION_MAYBE_UNUSED
#elif defined(__GNUC__) || defined(__clang__)
    // GCC and Clang support __attribute__((unused))
    #define VALIDATION_MAYBE_UNUSED __attribute__((unused))
#else
    #define VALIDATION_MAYBE_UNUSED
#endif

namespace validation_layer
{
    // Generate specific logAndPropagateResult functions for each API function
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetModuleGetDebugInfo(
        ze_result_t result,
        zet_module_handle_t hModule,                    ///< [in] handle of the module
        zet_module_debug_info_format_t format,          ///< [in] debug info format requested
        size_t* pSize,                                  ///< [in,out] size of debug info in bytes
        uint8_t* pDebugInfo                             ///< [in,out][optional] byte pointer to debug info
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetModuleGetDebugInfo(";
        
        
        oss << "hModule=";
        oss << loader::to_string(hModule);
        
        oss << ", ";
        oss << "format=";
        oss << loader::to_string(format);
        
        oss << ", ";
        oss << "pSize=";
        oss << loader::to_string(pSize);
        
        oss << ", ";
        oss << "pDebugInfo=";
        oss << loader::to_string(pDebugInfo);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDeviceGetDebugProperties(
        ze_result_t result,
        zet_device_handle_t hDevice,                    ///< [in] device handle
        zet_device_debug_properties_t* pDebugProperties ///< [in,out] query result for debug properties
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDeviceGetDebugProperties(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pDebugProperties=";
        oss << loader::to_string(pDebugProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDebugAttach(
        ze_result_t result,
        zet_device_handle_t hDevice,                    ///< [in] device handle
        const zet_debug_config_t* config,               ///< [in] the debug configuration
        zet_debug_session_handle_t* phDebug             ///< [out] debug session handle
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDebugAttach(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "config=";
        oss << loader::to_string(config);
        
        oss << ", ";
        oss << "phDebug=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && phDebug != nullptr) {
            oss << loader::to_string(*phDebug);
        } else {
            oss << loader::to_string(phDebug);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDebugDetach(
        ze_result_t result,
        zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDebugDetach(";
        
        
        oss << "hDebug=";
        oss << loader::to_string(hDebug);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDebugReadEvent(
        ze_result_t result,
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        uint64_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then immediately returns the status of the event;
                                                        ///< if `UINT64_MAX`, then function will not return until complete or
                                                        ///< device is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        zet_debug_event_t* event                        ///< [in,out] a pointer to a ::zet_debug_event_t.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDebugReadEvent(";
        
        
        oss << "hDebug=";
        oss << loader::to_string(hDebug);
        
        oss << ", ";
        oss << "timeout=";
        oss << loader::to_string(timeout);
        
        oss << ", ";
        oss << "event=";
        oss << loader::to_string(event);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDebugAcknowledgeEvent(
        ze_result_t result,
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        const zet_debug_event_t* event                  ///< [in] a pointer to a ::zet_debug_event_t.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDebugAcknowledgeEvent(";
        
        
        oss << "hDebug=";
        oss << loader::to_string(hDebug);
        
        oss << ", ";
        oss << "event=";
        oss << loader::to_string(event);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDebugInterrupt(
        ze_result_t result,
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread                       ///< [in] the thread to interrupt
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDebugInterrupt(";
        
        
        oss << "hDebug=";
        oss << loader::to_string(hDebug);
        
        oss << ", ";
        oss << "thread=";
        oss << loader::to_string(thread);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDebugResume(
        ze_result_t result,
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread                       ///< [in] the thread to resume
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDebugResume(";
        
        
        oss << "hDebug=";
        oss << loader::to_string(hDebug);
        
        oss << ", ";
        oss << "thread=";
        oss << loader::to_string(thread);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDebugReadMemory(
        ze_result_t result,
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier.
        const zet_debug_memory_space_desc_t* desc,      ///< [in] memory space descriptor
        size_t size,                                    ///< [in] the number of bytes to read
        void* buffer                                    ///< [in,out] a buffer to hold a copy of the memory
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDebugReadMemory(";
        
        
        oss << "hDebug=";
        oss << loader::to_string(hDebug);
        
        oss << ", ";
        oss << "thread=";
        oss << loader::to_string(thread);
        
        oss << ", ";
        oss << "desc=";
        oss << loader::to_string(desc);
        
        oss << ", ";
        oss << "size=";
        oss << loader::to_string(size);
        
        oss << ", ";
        oss << "buffer=";
        oss << loader::to_string(buffer);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDebugWriteMemory(
        ze_result_t result,
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier.
        const zet_debug_memory_space_desc_t* desc,      ///< [in] memory space descriptor
        size_t size,                                    ///< [in] the number of bytes to write
        const void* buffer                              ///< [in] a buffer holding the pattern to write
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDebugWriteMemory(";
        
        
        oss << "hDebug=";
        oss << loader::to_string(hDebug);
        
        oss << ", ";
        oss << "thread=";
        oss << loader::to_string(thread);
        
        oss << ", ";
        oss << "desc=";
        oss << loader::to_string(desc);
        
        oss << ", ";
        oss << "size=";
        oss << loader::to_string(size);
        
        oss << ", ";
        oss << "buffer=";
        oss << loader::to_string(buffer);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDebugGetRegisterSetProperties(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDebugGetRegisterSetProperties(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "pRegisterSetProperties=";
        oss << loader::to_string(pRegisterSetProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDebugGetThreadRegisterSetProperties(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDebugGetThreadRegisterSetProperties(";
        
        
        oss << "hDebug=";
        oss << loader::to_string(hDebug);
        
        oss << ", ";
        oss << "thread=";
        oss << loader::to_string(thread);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "pRegisterSetProperties=";
        oss << loader::to_string(pRegisterSetProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDebugReadRegisters(
        ze_result_t result,
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier
        uint32_t type,                                  ///< [in] register set type
        uint32_t start,                                 ///< [in] the starting offset into the register state area; must be less
                                                        ///< than the `count` member of ::zet_debug_regset_properties_t for the
                                                        ///< type
        uint32_t count,                                 ///< [in] the number of registers to read; start+count must be less than or
                                                        ///< equal to the `count` member of ::zet_debug_regset_properties_t for the
                                                        ///< type
        void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDebugReadRegisters(";
        
        
        oss << "hDebug=";
        oss << loader::to_string(hDebug);
        
        oss << ", ";
        oss << "thread=";
        oss << loader::to_string(thread);
        
        oss << ", ";
        oss << "type=";
        oss << loader::to_string(type);
        
        oss << ", ";
        oss << "start=";
        oss << loader::to_string(start);
        
        oss << ", ";
        oss << "count=";
        oss << loader::to_string(count);
        
        oss << ", ";
        oss << "pRegisterValues=";
        oss << loader::to_string(pRegisterValues);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDebugWriteRegisters(
        ze_result_t result,
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread,                      ///< [in] the thread identifier
        uint32_t type,                                  ///< [in] register set type
        uint32_t start,                                 ///< [in] the starting offset into the register state area; must be less
                                                        ///< than the `count` member of ::zet_debug_regset_properties_t for the
                                                        ///< type
        uint32_t count,                                 ///< [in] the number of registers to write; start+count must be less than
                                                        ///< or equal to the `count` member of ::zet_debug_regset_properties_t for
                                                        ///< the type
        void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDebugWriteRegisters(";
        
        
        oss << "hDebug=";
        oss << loader::to_string(hDebug);
        
        oss << ", ";
        oss << "thread=";
        oss << loader::to_string(thread);
        
        oss << ", ";
        oss << "type=";
        oss << loader::to_string(type);
        
        oss << ", ";
        oss << "start=";
        oss << loader::to_string(start);
        
        oss << ", ";
        oss << "count=";
        oss << loader::to_string(count);
        
        oss << ", ";
        oss << "pRegisterValues=";
        oss << loader::to_string(pRegisterValues);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricGroupGet(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricGroupGet(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phMetricGroups=";
        oss << loader::to_string(phMetricGroups);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricGroupGetProperties(
        ze_result_t result,
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricGroupGetProperties(";
        
        
        oss << "hMetricGroup=";
        oss << loader::to_string(hMetricGroup);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricGroupCalculateMetricValues(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricGroupCalculateMetricValues(";
        
        
        oss << "hMetricGroup=";
        oss << loader::to_string(hMetricGroup);
        
        oss << ", ";
        oss << "type=";
        oss << loader::to_string(type);
        
        oss << ", ";
        oss << "rawDataSize=";
        oss << loader::to_string(rawDataSize);
        
        oss << ", ";
        oss << "pRawData=";
        oss << loader::to_string(pRawData);
        
        oss << ", ";
        oss << "pMetricValueCount=";
        oss << loader::to_string(pMetricValueCount);
        
        oss << ", ";
        oss << "pMetricValues=";
        oss << loader::to_string(pMetricValues);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricGet(
        ze_result_t result,
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metrics.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metrics available.
                                                        ///< if count is greater than the number of metrics available, then the
                                                        ///< driver shall update the value with the correct number of metrics available.
        zet_metric_handle_t* phMetrics                  ///< [in,out][optional][range(0, *pCount)] array of handle of metrics.
                                                        ///< if count is less than the number of metrics available, then driver
                                                        ///< shall only retrieve that number of metrics.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricGet(";
        
        
        oss << "hMetricGroup=";
        oss << loader::to_string(hMetricGroup);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phMetrics=";
        oss << loader::to_string(phMetrics);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricGetProperties(
        ze_result_t result,
        zet_metric_handle_t hMetric,                    ///< [in] handle of the metric
        zet_metric_properties_t* pProperties            ///< [in,out] metric properties
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricGetProperties(";
        
        
        oss << "hMetric=";
        oss << loader::to_string(hMetric);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetContextActivateMetricGroups(
        ze_result_t result,
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t count,                                 ///< [in] metric group count to activate; must be 0 if `nullptr ==
                                                        ///< phMetricGroups`
        zet_metric_group_handle_t* phMetricGroups       ///< [in][optional][range(0, count)] handles of the metric groups to activate.
                                                        ///< nullptr deactivates all previously used metric groups.
                                                        ///< all metrics groups must come from a different domains.
                                                        ///< metric query and metric stream must use activated metric groups.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetContextActivateMetricGroups(";
        
        
        oss << "hContext=";
        oss << loader::to_string(hContext);
        
        oss << ", ";
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "count=";
        oss << loader::to_string(count);
        
        oss << ", ";
        oss << "phMetricGroups=";
        oss << loader::to_string(phMetricGroups);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricStreamerOpen(
        ze_result_t result,
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_streamer_desc_t* desc,               ///< [in,out] metric streamer descriptor
        ze_event_handle_t hNotificationEvent,           ///< [in][optional] event used for report availability notification
        zet_metric_streamer_handle_t* phMetricStreamer  ///< [out] handle of metric streamer
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricStreamerOpen(";
        
        
        oss << "hContext=";
        oss << loader::to_string(hContext);
        
        oss << ", ";
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "hMetricGroup=";
        oss << loader::to_string(hMetricGroup);
        
        oss << ", ";
        oss << "desc=";
        oss << loader::to_string(desc);
        
        oss << ", ";
        oss << "hNotificationEvent=";
        oss << loader::to_string(hNotificationEvent);
        
        oss << ", ";
        oss << "phMetricStreamer=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && phMetricStreamer != nullptr) {
            oss << loader::to_string(*phMetricStreamer);
        } else {
            oss << loader::to_string(phMetricStreamer);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetCommandListAppendMetricStreamerMarker(
        ze_result_t result,
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_streamer_handle_t hMetricStreamer,   ///< [in] handle of the metric streamer
        uint32_t value                                  ///< [in] streamer marker value
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetCommandListAppendMetricStreamerMarker(";
        
        
        oss << "hCommandList=";
        oss << loader::to_string(hCommandList);
        
        oss << ", ";
        oss << "hMetricStreamer=";
        oss << loader::to_string(hMetricStreamer);
        
        oss << ", ";
        oss << "value=";
        oss << loader::to_string(value);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricStreamerClose(
        ze_result_t result,
        zet_metric_streamer_handle_t hMetricStreamer    ///< [in][release] handle of the metric streamer
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricStreamerClose(";
        
        
        oss << "hMetricStreamer=";
        oss << loader::to_string(hMetricStreamer);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricStreamerReadData(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricStreamerReadData(";
        
        
        oss << "hMetricStreamer=";
        oss << loader::to_string(hMetricStreamer);
        
        oss << ", ";
        oss << "maxReportCount=";
        oss << loader::to_string(maxReportCount);
        
        oss << ", ";
        oss << "pRawDataSize=";
        oss << loader::to_string(pRawDataSize);
        
        oss << ", ";
        oss << "pRawData=";
        oss << loader::to_string(pRawData);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricQueryPoolCreate(
        ze_result_t result,
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        zet_metric_group_handle_t hMetricGroup,         ///< [in] metric group associated with the query object.
        const zet_metric_query_pool_desc_t* desc,       ///< [in] metric query pool descriptor
        zet_metric_query_pool_handle_t* phMetricQueryPool   ///< [out] handle of metric query pool
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricQueryPoolCreate(";
        
        
        oss << "hContext=";
        oss << loader::to_string(hContext);
        
        oss << ", ";
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "hMetricGroup=";
        oss << loader::to_string(hMetricGroup);
        
        oss << ", ";
        oss << "desc=";
        oss << loader::to_string(desc);
        
        oss << ", ";
        oss << "phMetricQueryPool=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && phMetricQueryPool != nullptr) {
            oss << loader::to_string(*phMetricQueryPool);
        } else {
            oss << loader::to_string(phMetricQueryPool);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricQueryPoolDestroy(
        ze_result_t result,
        zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricQueryPoolDestroy(";
        
        
        oss << "hMetricQueryPool=";
        oss << loader::to_string(hMetricQueryPool);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricQueryCreate(
        ze_result_t result,
        zet_metric_query_pool_handle_t hMetricQueryPool,///< [in] handle of the metric query pool
        uint32_t index,                                 ///< [in] index of the query within the pool
        zet_metric_query_handle_t* phMetricQuery        ///< [out] handle of metric query
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricQueryCreate(";
        
        
        oss << "hMetricQueryPool=";
        oss << loader::to_string(hMetricQueryPool);
        
        oss << ", ";
        oss << "index=";
        oss << loader::to_string(index);
        
        oss << ", ";
        oss << "phMetricQuery=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && phMetricQuery != nullptr) {
            oss << loader::to_string(*phMetricQuery);
        } else {
            oss << loader::to_string(phMetricQuery);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricQueryDestroy(
        ze_result_t result,
        zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricQueryDestroy(";
        
        
        oss << "hMetricQuery=";
        oss << loader::to_string(hMetricQuery);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricQueryReset(
        ze_result_t result,
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricQueryReset(";
        
        
        oss << "hMetricQuery=";
        oss << loader::to_string(hMetricQuery);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetCommandListAppendMetricQueryBegin(
        ze_result_t result,
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetCommandListAppendMetricQueryBegin(";
        
        
        oss << "hCommandList=";
        oss << loader::to_string(hCommandList);
        
        oss << ", ";
        oss << "hMetricQuery=";
        oss << loader::to_string(hMetricQuery);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetCommandListAppendMetricQueryEnd(
        ze_result_t result,
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery,         ///< [in] handle of the metric query
        ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in] must be zero
        ze_event_handle_t* phWaitEvents                 ///< [in][mbz] must be nullptr
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetCommandListAppendMetricQueryEnd(";
        
        
        oss << "hCommandList=";
        oss << loader::to_string(hCommandList);
        
        oss << ", ";
        oss << "hMetricQuery=";
        oss << loader::to_string(hMetricQuery);
        
        oss << ", ";
        oss << "hSignalEvent=";
        oss << loader::to_string(hSignalEvent);
        
        oss << ", ";
        oss << "numWaitEvents=";
        oss << loader::to_string(numWaitEvents);
        
        oss << ", ";
        oss << "phWaitEvents=";
        oss << loader::to_string(phWaitEvents);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetCommandListAppendMetricMemoryBarrier(
        ze_result_t result,
        zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetCommandListAppendMetricMemoryBarrier(";
        
        
        oss << "hCommandList=";
        oss << loader::to_string(hCommandList);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricQueryGetData(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricQueryGetData(";
        
        
        oss << "hMetricQuery=";
        oss << loader::to_string(hMetricQuery);
        
        oss << ", ";
        oss << "pRawDataSize=";
        oss << loader::to_string(pRawDataSize);
        
        oss << ", ";
        oss << "pRawData=";
        oss << loader::to_string(pRawData);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetKernelGetProfileInfo(
        ze_result_t result,
        zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
        zet_profile_properties_t* pProfileProperties    ///< [out] pointer to profile properties
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetKernelGetProfileInfo(";
        
        
        oss << "hKernel=";
        oss << loader::to_string(hKernel);
        
        oss << ", ";
        oss << "pProfileProperties=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pProfileProperties != nullptr) {
            oss << loader::to_string(*pProfileProperties);
        } else {
            oss << loader::to_string(pProfileProperties);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetTracerExpCreate(
        ze_result_t result,
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        const zet_tracer_exp_desc_t* desc,              ///< [in] pointer to tracer descriptor
        zet_tracer_exp_handle_t* phTracer               ///< [out] pointer to handle of tracer object created
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetTracerExpCreate(";
        
        
        oss << "hContext=";
        oss << loader::to_string(hContext);
        
        oss << ", ";
        oss << "desc=";
        oss << loader::to_string(desc);
        
        oss << ", ";
        oss << "phTracer=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && phTracer != nullptr) {
            oss << loader::to_string(*phTracer);
        } else {
            oss << loader::to_string(phTracer);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetTracerExpDestroy(
        ze_result_t result,
        zet_tracer_exp_handle_t hTracer                 ///< [in][release] handle of tracer object to destroy
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetTracerExpDestroy(";
        
        
        oss << "hTracer=";
        oss << loader::to_string(hTracer);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetTracerExpSetPrologues(
        ze_result_t result,
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetTracerExpSetPrologues(";
        
        
        oss << "hTracer=";
        oss << loader::to_string(hTracer);
        
        oss << ", ";
        oss << "pCoreCbs=";
        oss << loader::to_string(pCoreCbs);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetTracerExpSetEpilogues(
        ze_result_t result,
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetTracerExpSetEpilogues(";
        
        
        oss << "hTracer=";
        oss << loader::to_string(hTracer);
        
        oss << ", ";
        oss << "pCoreCbs=";
        oss << loader::to_string(pCoreCbs);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetTracerExpSetEnabled(
        ze_result_t result,
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetTracerExpSetEnabled(";
        
        
        oss << "hTracer=";
        oss << loader::to_string(hTracer);
        
        oss << ", ";
        oss << "enable=";
        oss << loader::to_string(enable);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDeviceGetConcurrentMetricGroupsExp(
        ze_result_t result,
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t metricGroupCount,                      ///< [in] metric group count
        zet_metric_group_handle_t * phMetricGroups,     ///< [in,out] metrics groups to be re-arranged to be sets of concurrent
                                                        ///< groups
        uint32_t * pMetricGroupsCountPerConcurrentGroup,///< [in,out][optional][*pConcurrentGroupCount] count of metric groups per
                                                        ///< concurrent group.
        uint32_t * pConcurrentGroupCount                ///< [out] number of concurrent groups.
                                                        ///< The value of this parameter could be used to determine the number of
                                                        ///< replays necessary.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDeviceGetConcurrentMetricGroupsExp(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "metricGroupCount=";
        oss << loader::to_string(metricGroupCount);
        
        oss << ", ";
        oss << "phMetricGroups=";
        oss << loader::to_string(phMetricGroups);
        
        oss << ", ";
        oss << "pMetricGroupsCountPerConcurrentGroup=";
        oss << loader::to_string(pMetricGroupsCountPerConcurrentGroup);
        
        oss << ", ";
        oss << "pConcurrentGroupCount=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pConcurrentGroupCount != nullptr) {
            oss << loader::to_string(*pConcurrentGroupCount);
        } else {
            oss << loader::to_string(pConcurrentGroupCount);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricTracerCreateExp(
        ze_result_t result,
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t metricGroupCount,                      ///< [in] metric group count
        zet_metric_group_handle_t* phMetricGroups,      ///< [in][range(0, metricGroupCount )] handles of the metric groups to
                                                        ///< trace
        zet_metric_tracer_exp_desc_t* desc,             ///< [in,out] metric tracer descriptor
        ze_event_handle_t hNotificationEvent,           ///< [in][optional] event used for report availability notification. Note:
                                                        ///< If buffer is not drained when the event it flagged, there is a risk of
                                                        ///< HW event buffer being overrun
        zet_metric_tracer_exp_handle_t* phMetricTracer  ///< [out] handle of the metric tracer
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricTracerCreateExp(";
        
        
        oss << "hContext=";
        oss << loader::to_string(hContext);
        
        oss << ", ";
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "metricGroupCount=";
        oss << loader::to_string(metricGroupCount);
        
        oss << ", ";
        oss << "phMetricGroups=";
        oss << loader::to_string(phMetricGroups);
        
        oss << ", ";
        oss << "desc=";
        oss << loader::to_string(desc);
        
        oss << ", ";
        oss << "hNotificationEvent=";
        oss << loader::to_string(hNotificationEvent);
        
        oss << ", ";
        oss << "phMetricTracer=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && phMetricTracer != nullptr) {
            oss << loader::to_string(*phMetricTracer);
        } else {
            oss << loader::to_string(phMetricTracer);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricTracerDestroyExp(
        ze_result_t result,
        zet_metric_tracer_exp_handle_t hMetricTracer    ///< [in] handle of the metric tracer
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricTracerDestroyExp(";
        
        
        oss << "hMetricTracer=";
        oss << loader::to_string(hMetricTracer);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricTracerEnableExp(
        ze_result_t result,
        zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
        ze_bool_t synchronous                           ///< [in] request synchronous behavior. Confirmation of successful
                                                        ///< asynchronous operation is done by calling ::zetMetricTracerReadDataExp()
                                                        ///< and checking the return status: ::ZE_RESULT_NOT_READY will be returned
                                                        ///< when the tracer is inactive. ::ZE_RESULT_SUCCESS will be returned 
                                                        ///< when the tracer is active.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricTracerEnableExp(";
        
        
        oss << "hMetricTracer=";
        oss << loader::to_string(hMetricTracer);
        
        oss << ", ";
        oss << "synchronous=";
        oss << loader::to_string(synchronous);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricTracerDisableExp(
        ze_result_t result,
        zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
        ze_bool_t synchronous                           ///< [in] request synchronous behavior. Confirmation of successful
                                                        ///< asynchronous operation is done by calling ::zetMetricTracerReadDataExp()
                                                        ///< and checking the return status: ::ZE_RESULT_SUCCESS will be returned
                                                        ///< when the tracer is active or when it is inactive but still has data. 
                                                        ///< ::ZE_RESULT_NOT_READY will be returned when the tracer is inactive and
                                                        ///< has no more data to be retrieved.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricTracerDisableExp(";
        
        
        oss << "hMetricTracer=";
        oss << loader::to_string(hMetricTracer);
        
        oss << ", ";
        oss << "synchronous=";
        oss << loader::to_string(synchronous);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricTracerReadDataExp(
        ze_result_t result,
        zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
        size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                        ///< if size is zero, then the driver will update the value with the total
                                                        ///< size in bytes needed for all data available.
                                                        ///< if size is non-zero, then driver will only retrieve that amount of
                                                        ///< data. 
                                                        ///< if size is larger than size needed for all data, then driver will
                                                        ///< update the value with the actual size needed.
        uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing tracer
                                                        ///< data in raw format
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricTracerReadDataExp(";
        
        
        oss << "hMetricTracer=";
        oss << loader::to_string(hMetricTracer);
        
        oss << ", ";
        oss << "pRawDataSize=";
        oss << loader::to_string(pRawDataSize);
        
        oss << ", ";
        oss << "pRawData=";
        oss << loader::to_string(pRawData);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricDecoderCreateExp(
        ze_result_t result,
        zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
        zet_metric_decoder_exp_handle_t* phMetricDecoder///< [out] handle of the metric decoder object
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricDecoderCreateExp(";
        
        
        oss << "hMetricTracer=";
        oss << loader::to_string(hMetricTracer);
        
        oss << ", ";
        oss << "phMetricDecoder=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && phMetricDecoder != nullptr) {
            oss << loader::to_string(*phMetricDecoder);
        } else {
            oss << loader::to_string(phMetricDecoder);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricDecoderDestroyExp(
        ze_result_t result,
        zet_metric_decoder_exp_handle_t phMetricDecoder ///< [in] handle of the metric decoder object
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricDecoderDestroyExp(";
        
        
        oss << "phMetricDecoder=";
        oss << loader::to_string(phMetricDecoder);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricDecoderGetDecodableMetricsExp(
        ze_result_t result,
        zet_metric_decoder_exp_handle_t hMetricDecoder, ///< [in] handle of the metric decoder object
        uint32_t* pCount,                               ///< [in,out] pointer to number of decodable metric in the hMetricDecoder
                                                        ///< handle. If count is zero, then the driver shall 
                                                        ///< update the value with the total number of decodable metrics available
                                                        ///< in the decoder. if count is greater than zero 
                                                        ///< but less than the total number of decodable metrics available in the
                                                        ///< decoder, then only that number will be returned. 
                                                        ///< if count is greater than the number of decodable metrics available in
                                                        ///< the decoder, then the driver shall update the 
                                                        ///< value with the actual number of decodable metrics available. 
        zet_metric_handle_t* phMetrics                  ///< [in,out] [range(0, *pCount)] array of handles of decodable metrics in
                                                        ///< the hMetricDecoder handle provided.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricDecoderGetDecodableMetricsExp(";
        
        
        oss << "hMetricDecoder=";
        oss << loader::to_string(hMetricDecoder);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phMetrics=";
        oss << loader::to_string(phMetrics);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricTracerDecodeExp(
        ze_result_t result,
        zet_metric_decoder_exp_handle_t phMetricDecoder,///< [in] handle of the metric decoder object
        size_t* pRawDataSize,                           ///< [in,out] size in bytes of raw data buffer. If pMetricEntriesCount is
                                                        ///< greater than zero but less than total number of 
                                                        ///< decodable metrics available in the raw data buffer, then driver shall
                                                        ///< update this value with actual number of raw 
                                                        ///< data bytes processed.
        uint8_t* pRawData,                              ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing tracer
                                                        ///< data in raw format
        uint32_t metricsCount,                          ///< [in] number of decodable metrics in the tracer for which the
                                                        ///< hMetricDecoder handle was provided. See 
                                                        ///< ::zetMetricDecoderGetDecodableMetricsExp(). If metricCount is greater
                                                        ///< than zero but less than the number decodable 
                                                        ///< metrics available in the raw data buffer, then driver shall only
                                                        ///< decode those.
        zet_metric_handle_t* phMetrics,                 ///< [in] [range(0, metricsCount)] array of handles of decodable metrics in
                                                        ///< the decoder for which the hMetricDecoder handle was 
                                                        ///< provided. Metrics handles are expected to be for decodable metrics,
                                                        ///< see ::zetMetricDecoderGetDecodableMetricsExp() 
        uint32_t* pSetCount,                            ///< [in,out] pointer to number of metric sets. If count is zero, then the
                                                        ///< driver shall update the value with the total
                                                        ///< number of metric sets to be decoded. If count is greater than the
                                                        ///< number available in the raw data buffer, then the
                                                        ///< driver shall update the value with the actual number of metric sets to
                                                        ///< be decoded. There is a 1:1 relation between
                                                        ///< the number of sets and sub-devices returned in the decoded entries.
        uint32_t* pMetricEntriesCountPerSet,            ///< [in,out][optional][range(0, *pSetCount)] buffer of metric entries
                                                        ///< counts per metric set, one value per set.
        uint32_t* pMetricEntriesCount,                  ///< [in,out]  pointer to the total number of metric entries decoded, for
                                                        ///< all metric sets. If count is zero, then the
                                                        ///< driver shall update the value with the total number of metric entries
                                                        ///< to be decoded. If count is greater than zero
                                                        ///< but less than the total number of metric entries available in the raw
                                                        ///< data, then user provided number will be decoded.
                                                        ///< If count is greater than the number available in the raw data buffer,
                                                        ///< then the driver shall update the value with
                                                        ///< the actual number of decodable metric entries decoded. If set to null,
                                                        ///< then driver will only update the value of
                                                        ///< pSetCount.
        zet_metric_entry_exp_t* pMetricEntries          ///< [in,out][optional][range(0, *pMetricEntriesCount)] buffer containing
                                                        ///< decoded metric entries
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricTracerDecodeExp(";
        
        
        oss << "phMetricDecoder=";
        oss << loader::to_string(phMetricDecoder);
        
        oss << ", ";
        oss << "pRawDataSize=";
        oss << loader::to_string(pRawDataSize);
        
        oss << ", ";
        oss << "pRawData=";
        oss << loader::to_string(pRawData);
        
        oss << ", ";
        oss << "metricsCount=";
        oss << loader::to_string(metricsCount);
        
        oss << ", ";
        oss << "phMetrics=";
        oss << loader::to_string(phMetrics);
        
        oss << ", ";
        oss << "pSetCount=";
        oss << loader::to_string(pSetCount);
        
        oss << ", ";
        oss << "pMetricEntriesCountPerSet=";
        oss << loader::to_string(pMetricEntriesCountPerSet);
        
        oss << ", ";
        oss << "pMetricEntriesCount=";
        oss << loader::to_string(pMetricEntriesCount);
        
        oss << ", ";
        oss << "pMetricEntries=";
        oss << loader::to_string(pMetricEntries);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetCommandListAppendMarkerExp(
        ze_result_t result,
        zet_command_list_handle_t hCommandList,         ///< [in] handle to the command list
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle to the marker metric group.
                                                        ///< ::zet_metric_group_type_exp_flags_t could be used to check whether
                                                        ///< marker is supoported by the metric group.
        uint32_t value                                  ///< [in] marker value
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetCommandListAppendMarkerExp(";
        
        
        oss << "hCommandList=";
        oss << loader::to_string(hCommandList);
        
        oss << ", ";
        oss << "hMetricGroup=";
        oss << loader::to_string(hMetricGroup);
        
        oss << ", ";
        oss << "value=";
        oss << loader::to_string(value);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDeviceEnableMetricsExp(
        ze_result_t result,
        zet_device_handle_t hDevice                     ///< [in] handle of the device where metrics collection has to be enabled.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDeviceEnableMetricsExp(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDeviceDisableMetricsExp(
        ze_result_t result,
        zet_device_handle_t hDevice                     ///< [in] handle of the device where metrics collection has to be disabled
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDeviceDisableMetricsExp(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricGroupCalculateMultipleMetricValuesExp(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricGroupCalculateMultipleMetricValuesExp(";
        
        
        oss << "hMetricGroup=";
        oss << loader::to_string(hMetricGroup);
        
        oss << ", ";
        oss << "type=";
        oss << loader::to_string(type);
        
        oss << ", ";
        oss << "rawDataSize=";
        oss << loader::to_string(rawDataSize);
        
        oss << ", ";
        oss << "pRawData=";
        oss << loader::to_string(pRawData);
        
        oss << ", ";
        oss << "pSetCount=";
        oss << loader::to_string(pSetCount);
        
        oss << ", ";
        oss << "pTotalMetricValueCount=";
        oss << loader::to_string(pTotalMetricValueCount);
        
        oss << ", ";
        oss << "pMetricCounts=";
        oss << loader::to_string(pMetricCounts);
        
        oss << ", ";
        oss << "pMetricValues=";
        oss << loader::to_string(pMetricValues);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricGroupGetGlobalTimestampsExp(
        ze_result_t result,
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        ze_bool_t synchronizedWithHost,                 ///< [in] Returns the timestamps synchronized to the host or the device.
        uint64_t* globalTimestamp,                      ///< [out] Device timestamp.
        uint64_t* metricTimestamp                       ///< [out] Metric timestamp.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricGroupGetGlobalTimestampsExp(";
        
        
        oss << "hMetricGroup=";
        oss << loader::to_string(hMetricGroup);
        
        oss << ", ";
        oss << "synchronizedWithHost=";
        oss << loader::to_string(synchronizedWithHost);
        
        oss << ", ";
        oss << "globalTimestamp=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && globalTimestamp != nullptr) {
            oss << loader::to_string(*globalTimestamp);
        } else {
            oss << loader::to_string(globalTimestamp);
        }
        
        oss << ", ";
        oss << "metricTimestamp=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && metricTimestamp != nullptr) {
            oss << loader::to_string(*metricTimestamp);
        } else {
            oss << loader::to_string(metricTimestamp);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricGroupGetExportDataExp(
        ze_result_t result,
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        const uint8_t* pRawData,                        ///< [in] buffer of raw data
        size_t rawDataSize,                             ///< [in] size in bytes of raw data buffer
        size_t* pExportDataSize,                        ///< [in,out] size in bytes of export data buffer
                                                        ///< if size is zero, then the driver shall update the value with the
                                                        ///< number of bytes necessary to store the exported data.
                                                        ///< if size is greater than required, then the driver shall update the
                                                        ///< value with the actual number of bytes necessary to store the exported data.
        uint8_t * pExportData                           ///< [in,out][optional][range(0, *pExportDataSize)] buffer of exported data.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricGroupGetExportDataExp(";
        
        
        oss << "hMetricGroup=";
        oss << loader::to_string(hMetricGroup);
        
        oss << ", ";
        oss << "pRawData=";
        oss << loader::to_string(pRawData);
        
        oss << ", ";
        oss << "rawDataSize=";
        oss << loader::to_string(rawDataSize);
        
        oss << ", ";
        oss << "pExportDataSize=";
        oss << loader::to_string(pExportDataSize);
        
        oss << ", ";
        oss << "pExportData=";
        oss << loader::to_string(pExportData);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricGroupCalculateMetricExportDataExp(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricGroupCalculateMetricExportDataExp(";
        
        
        oss << "hDriver=";
        oss << loader::to_string(hDriver);
        
        oss << ", ";
        oss << "type=";
        oss << loader::to_string(type);
        
        oss << ", ";
        oss << "exportDataSize=";
        oss << loader::to_string(exportDataSize);
        
        oss << ", ";
        oss << "pExportData=";
        oss << loader::to_string(pExportData);
        
        oss << ", ";
        oss << "pCalculateDescriptor=";
        oss << loader::to_string(pCalculateDescriptor);
        
        oss << ", ";
        oss << "pSetCount=";
        oss << loader::to_string(pSetCount);
        
        oss << ", ";
        oss << "pTotalMetricValueCount=";
        oss << loader::to_string(pTotalMetricValueCount);
        
        oss << ", ";
        oss << "pMetricCounts=";
        oss << loader::to_string(pMetricCounts);
        
        oss << ", ";
        oss << "pMetricValues=";
        oss << loader::to_string(pMetricValues);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricProgrammableGetExp(
        ze_result_t result,
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metric programmable handles.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metric programmable handles available.
                                                        ///< if count is greater than the number of metric programmable handles
                                                        ///< available, then the driver shall update the value with the correct
                                                        ///< number of metric programmable handles available.
        zet_metric_programmable_exp_handle_t* phMetricProgrammables ///< [in,out][optional][range(0, *pCount)] array of handle of metric programmables.
                                                        ///< if count is less than the number of metric programmables available,
                                                        ///< then driver shall only retrieve that number of metric programmables.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricProgrammableGetExp(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phMetricProgrammables=";
        oss << loader::to_string(phMetricProgrammables);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricProgrammableGetPropertiesExp(
        ze_result_t result,
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        zet_metric_programmable_exp_properties_t* pProperties   ///< [in,out] properties of the metric programmable
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricProgrammableGetPropertiesExp(";
        
        
        oss << "hMetricProgrammable=";
        oss << loader::to_string(hMetricProgrammable);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricProgrammableGetParamInfoExp(
        ze_result_t result,
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        uint32_t* pParameterCount,                      ///< [in,out] count of the parameters to retrieve parameter info.
                                                        ///< if value pParameterCount is greater than count of parameters
                                                        ///< available, then pParameterCount will be updated with count of
                                                        ///< parameters available.
                                                        ///< The count of parameters available can be queried using ::zetMetricProgrammableGetPropertiesExp.
        zet_metric_programmable_param_info_exp_t* pParameterInfo///< [in,out][range(1, *pParameterCount)] array of parameter info.
                                                        ///< if parameterCount is less than the number of parameters available,
                                                        ///< then driver shall only retrieve that number of parameter info.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricProgrammableGetParamInfoExp(";
        
        
        oss << "hMetricProgrammable=";
        oss << loader::to_string(hMetricProgrammable);
        
        oss << ", ";
        oss << "pParameterCount=";
        oss << loader::to_string(pParameterCount);
        
        oss << ", ";
        oss << "pParameterInfo=";
        oss << loader::to_string(pParameterInfo);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricProgrammableGetParamValueInfoExp(
        ze_result_t result,
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        uint32_t parameterOrdinal,                      ///< [in] ordinal of the parameter in the metric programmable
        uint32_t* pValueInfoCount,                      ///< [in,out] count of parameter value information to retrieve.
                                                        ///< if value at pValueInfoCount is greater than count of value info
                                                        ///< available, then pValueInfoCount will be updated with count of value
                                                        ///< info available.
                                                        ///< The count of parameter value info available can be queried using ::zetMetricProgrammableGetParamInfoExp.
        zet_metric_programmable_param_value_info_exp_t* pValueInfo  ///< [in,out][range(1, *pValueInfoCount)] array of parameter value info.
                                                        ///< if pValueInfoCount is less than the number of value info available,
                                                        ///< then driver shall only retrieve that number of value info.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricProgrammableGetParamValueInfoExp(";
        
        
        oss << "hMetricProgrammable=";
        oss << loader::to_string(hMetricProgrammable);
        
        oss << ", ";
        oss << "parameterOrdinal=";
        oss << loader::to_string(parameterOrdinal);
        
        oss << ", ";
        oss << "pValueInfoCount=";
        oss << loader::to_string(pValueInfoCount);
        
        oss << ", ";
        oss << "pValueInfo=";
        oss << loader::to_string(pValueInfo);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricCreateFromProgrammableExp2(
        ze_result_t result,
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        uint32_t parameterCount,                        ///< [in] Count of parameters to set.
        zet_metric_programmable_param_value_exp_t* pParameterValues,///< [in] list of parameter values to be set.
        const char* pName,                              ///< [in] pointer to metric name to be used. Must point to a
                                                        ///< null-terminated character array no longer than ::ZET_MAX_METRIC_NAME.
        const char* pDescription,                       ///< [in] pointer to metric description to be used. Must point to a
                                                        ///< null-terminated character array no longer than
                                                        ///< ::ZET_MAX_METRIC_DESCRIPTION.
        uint32_t* pMetricHandleCount,                   ///< [in,out] Pointer to the number of metric handles.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< number of metric handles available for this programmable.
                                                        ///< if count is greater than the number of metric handles available, then
                                                        ///< the driver shall update the value with the correct number of metric
                                                        ///< handles available.
        zet_metric_handle_t* phMetricHandles            ///< [in,out][optional][range(0,*pMetricHandleCount)] array of handle of metrics.
                                                        ///< if count is less than the number of metrics available, then driver
                                                        ///< shall only retrieve that number of metric handles.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricCreateFromProgrammableExp2(";
        
        
        oss << "hMetricProgrammable=";
        oss << loader::to_string(hMetricProgrammable);
        
        oss << ", ";
        oss << "parameterCount=";
        oss << loader::to_string(parameterCount);
        
        oss << ", ";
        oss << "pParameterValues=";
        oss << loader::to_string(pParameterValues);
        
        oss << ", ";
        oss << "pName=";
        oss << loader::to_string(pName);
        
        oss << ", ";
        oss << "pDescription=";
        oss << loader::to_string(pDescription);
        
        oss << ", ";
        oss << "pMetricHandleCount=";
        oss << loader::to_string(pMetricHandleCount);
        
        oss << ", ";
        oss << "phMetricHandles=";
        oss << loader::to_string(phMetricHandles);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricCreateFromProgrammableExp(
        ze_result_t result,
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        zet_metric_programmable_param_value_exp_t* pParameterValues,///< [in] list of parameter values to be set.
        uint32_t parameterCount,                        ///< [in] Count of parameters to set.
        const char* pName,                              ///< [in] pointer to metric name to be used. Must point to a
                                                        ///< null-terminated character array no longer than ::ZET_MAX_METRIC_NAME.
        const char* pDescription,                       ///< [in] pointer to metric description to be used. Must point to a
                                                        ///< null-terminated character array no longer than
                                                        ///< ::ZET_MAX_METRIC_DESCRIPTION.
        uint32_t* pMetricHandleCount,                   ///< [in,out] Pointer to the number of metric handles.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< number of metric handles available for this programmable.
                                                        ///< if count is greater than the number of metric handles available, then
                                                        ///< the driver shall update the value with the correct number of metric
                                                        ///< handles available.
        zet_metric_handle_t* phMetricHandles            ///< [in,out][optional][range(0,*pMetricHandleCount)] array of handle of metrics.
                                                        ///< if count is less than the number of metrics available, then driver
                                                        ///< shall only retrieve that number of metric handles.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricCreateFromProgrammableExp(";
        
        
        oss << "hMetricProgrammable=";
        oss << loader::to_string(hMetricProgrammable);
        
        oss << ", ";
        oss << "pParameterValues=";
        oss << loader::to_string(pParameterValues);
        
        oss << ", ";
        oss << "parameterCount=";
        oss << loader::to_string(parameterCount);
        
        oss << ", ";
        oss << "pName=";
        oss << loader::to_string(pName);
        
        oss << ", ";
        oss << "pDescription=";
        oss << loader::to_string(pDescription);
        
        oss << ", ";
        oss << "pMetricHandleCount=";
        oss << loader::to_string(pMetricHandleCount);
        
        oss << ", ";
        oss << "phMetricHandles=";
        oss << loader::to_string(phMetricHandles);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetDeviceCreateMetricGroupsFromMetricsExp(
        ze_result_t result,
        zet_device_handle_t hDevice,                    ///< [in] handle of the device.
        uint32_t metricCount,                           ///< [in] number of metric handles.
        zet_metric_handle_t * phMetrics,                ///< [in] metric handles to be added to the metric groups.
        const char * pMetricGroupNamePrefix,            ///< [in] prefix to the name created for the metric groups. Must point to a
                                                        ///< null-terminated character array no longer than
                                                        ///< ::ZET_MAX_METRIC_GROUP_NAME_PREFIX_EXP.
        const char * pDescription,                      ///< [in] pointer to description of the metric groups. Must point to a
                                                        ///< null-terminated character array no longer than
                                                        ///< ::ZET_MAX_METRIC_GROUP_DESCRIPTION.
        uint32_t * pMetricGroupCount,                   ///< [in,out] pointer to the number of metric group handles to be created.
                                                        ///< if pMetricGroupCount is zero, then the driver shall update the value
                                                        ///< with the maximum possible number of metric group handles that could be created.
                                                        ///< if pMetricGroupCount is greater than the number of metric group
                                                        ///< handles that could be created, then the driver shall update the value
                                                        ///< with the correct number of metric group handles generated.
                                                        ///< if pMetricGroupCount is lesser than the number of metric group handles
                                                        ///< that could be created, then ::ZE_RESULT_ERROR_INVALID_ARGUMENT is returned.
        zet_metric_group_handle_t* phMetricGroup        ///< [in,out][optional][range(0, *pMetricGroupCount)] array of handle of
                                                        ///< metric group handles.
                                                        ///< Created Metric group handles.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetDeviceCreateMetricGroupsFromMetricsExp(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "metricCount=";
        oss << loader::to_string(metricCount);
        
        oss << ", ";
        oss << "phMetrics=";
        oss << loader::to_string(phMetrics);
        
        oss << ", ";
        oss << "pMetricGroupNamePrefix=";
        oss << loader::to_string(pMetricGroupNamePrefix);
        
        oss << ", ";
        oss << "pDescription=";
        oss << loader::to_string(pDescription);
        
        oss << ", ";
        oss << "pMetricGroupCount=";
        oss << loader::to_string(pMetricGroupCount);
        
        oss << ", ";
        oss << "phMetricGroup=";
        oss << loader::to_string(phMetricGroup);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricGroupCreateExp(
        ze_result_t result,
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        const char* pName,                              ///< [in] pointer to metric group name. Must point to a null-terminated
                                                        ///< character array no longer than ::ZET_MAX_METRIC_GROUP_NAME.
        const char* pDescription,                       ///< [in] pointer to metric group description. Must point to a
                                                        ///< null-terminated character array no longer than
                                                        ///< ::ZET_MAX_METRIC_GROUP_DESCRIPTION.
        zet_metric_group_sampling_type_flags_t samplingType,///< [in] Sampling type for the metric group.
        zet_metric_group_handle_t* phMetricGroup        ///< [in,out] Created Metric group handle
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricGroupCreateExp(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pName=";
        oss << loader::to_string(pName);
        
        oss << ", ";
        oss << "pDescription=";
        oss << loader::to_string(pDescription);
        
        oss << ", ";
        oss << "samplingType=";
        oss << loader::to_string(samplingType);
        
        oss << ", ";
        oss << "phMetricGroup=";
        oss << loader::to_string(phMetricGroup);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricGroupAddMetricExp(
        ze_result_t result,
        zet_metric_group_handle_t hMetricGroup,         ///< [in] Handle of the metric group
        zet_metric_handle_t hMetric,                    ///< [in] Metric to be added to the group.
        size_t * pErrorStringSize,                      ///< [in,out][optional] Size of the error string to query, if an error was
                                                        ///< reported during adding the metric handle.
                                                        ///< if *pErrorStringSize is zero, then the driver shall update the value
                                                        ///< with the size of the error string in bytes.
        char* pErrorString                              ///< [in,out][optional][range(0, *pErrorStringSize)] Error string.
                                                        ///< if *pErrorStringSize is less than the length of the error string
                                                        ///< available, then driver shall only retrieve that length of error string.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricGroupAddMetricExp(";
        
        
        oss << "hMetricGroup=";
        oss << loader::to_string(hMetricGroup);
        
        oss << ", ";
        oss << "hMetric=";
        oss << loader::to_string(hMetric);
        
        oss << ", ";
        oss << "pErrorStringSize=";
        oss << loader::to_string(pErrorStringSize);
        
        oss << ", ";
        oss << "pErrorString=";
        oss << loader::to_string(pErrorString);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricGroupRemoveMetricExp(
        ze_result_t result,
        zet_metric_group_handle_t hMetricGroup,         ///< [in] Handle of the metric group
        zet_metric_handle_t hMetric                     ///< [in] Metric handle to be removed from the metric group.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricGroupRemoveMetricExp(";
        
        
        oss << "hMetricGroup=";
        oss << loader::to_string(hMetricGroup);
        
        oss << ", ";
        oss << "hMetric=";
        oss << loader::to_string(hMetric);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricGroupCloseExp(
        ze_result_t result,
        zet_metric_group_handle_t hMetricGroup          ///< [in] Handle of the metric group
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricGroupCloseExp(";
        
        
        oss << "hMetricGroup=";
        oss << loader::to_string(hMetricGroup);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricGroupDestroyExp(
        ze_result_t result,
        zet_metric_group_handle_t hMetricGroup          ///< [in] Handle of the metric group to destroy
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricGroupDestroyExp(";
        
        
        oss << "hMetricGroup=";
        oss << loader::to_string(hMetricGroup);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zetMetricDestroyExp(
        ze_result_t result,
        zet_metric_handle_t hMetric                     ///< [in] Handle of the metric to destroy
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zetMetricDestroyExp(";
        
        
        oss << "hMetric=";
        oss << loader::to_string(hMetric);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }

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
        context.logger->log_trace("zetModuleGetDebugInfo(hModule, format, pSize, pDebugInfo)");

        auto pfnGetDebugInfo = context.zetDdiTable.Module.pfnGetDebugInfo;

        if( nullptr == pfnGetDebugInfo )
            return logAndPropagateResult_zetModuleGetDebugInfo(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hModule, format, pSize, pDebugInfo);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetModuleGetDebugInfoPrologue( hModule, format, pSize, pDebugInfo );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetModuleGetDebugInfo(result, hModule, format, pSize, pDebugInfo);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetModuleGetDebugInfoPrologue( hModule, format, pSize, pDebugInfo );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetModuleGetDebugInfo(result, hModule, format, pSize, pDebugInfo);
        }

        auto driver_result = pfnGetDebugInfo( hModule, format, pSize, pDebugInfo );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetModuleGetDebugInfoEpilogue( hModule, format, pSize, pDebugInfo ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetModuleGetDebugInfo(result, hModule, format, pSize, pDebugInfo);
        }

        return logAndPropagateResult_zetModuleGetDebugInfo(driver_result, hModule, format, pSize, pDebugInfo);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDeviceGetDebugProperties
    __zedlllocal ze_result_t ZE_APICALL
    zetDeviceGetDebugProperties(
        zet_device_handle_t hDevice,                    ///< [in] device handle
        zet_device_debug_properties_t* pDebugProperties ///< [in,out] query result for debug properties
        )
    {
        context.logger->log_trace("zetDeviceGetDebugProperties(hDevice, pDebugProperties)");

        auto pfnGetDebugProperties = context.zetDdiTable.Device.pfnGetDebugProperties;

        if( nullptr == pfnGetDebugProperties )
            return logAndPropagateResult_zetDeviceGetDebugProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pDebugProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDeviceGetDebugPropertiesPrologue( hDevice, pDebugProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDeviceGetDebugProperties(result, hDevice, pDebugProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDeviceGetDebugPropertiesPrologue( hDevice, pDebugProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDeviceGetDebugProperties(result, hDevice, pDebugProperties);
        }

        auto driver_result = pfnGetDebugProperties( hDevice, pDebugProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDeviceGetDebugPropertiesEpilogue( hDevice, pDebugProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDeviceGetDebugProperties(result, hDevice, pDebugProperties);
        }

        return logAndPropagateResult_zetDeviceGetDebugProperties(driver_result, hDevice, pDebugProperties);
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
        context.logger->log_trace("zetDebugAttach(hDevice, config, phDebug)");

        auto pfnAttach = context.zetDdiTable.Debug.pfnAttach;

        if( nullptr == pfnAttach )
            return logAndPropagateResult_zetDebugAttach(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, config, phDebug);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugAttachPrologue( hDevice, config, phDebug );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugAttach(result, hDevice, config, phDebug);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugAttachPrologue( hDevice, config, phDebug );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugAttach(result, hDevice, config, phDebug);
        }

        auto driver_result = pfnAttach( hDevice, config, phDebug );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugAttachEpilogue( hDevice, config, phDebug ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugAttach(result, hDevice, config, phDebug);
        }

        return logAndPropagateResult_zetDebugAttach(driver_result, hDevice, config, phDebug);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugDetach
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugDetach(
        zet_debug_session_handle_t hDebug               ///< [in][release] debug session handle
        )
    {
        context.logger->log_trace("zetDebugDetach(hDebug)");

        auto pfnDetach = context.zetDdiTable.Debug.pfnDetach;

        if( nullptr == pfnDetach )
            return logAndPropagateResult_zetDebugDetach(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDebug);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugDetachPrologue( hDebug );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugDetach(result, hDebug);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugDetachPrologue( hDebug );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugDetach(result, hDebug);
        }

        auto driver_result = pfnDetach( hDebug );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugDetachEpilogue( hDebug ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugDetach(result, hDebug);
        }

        return logAndPropagateResult_zetDebugDetach(driver_result, hDebug);
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
        context.logger->log_trace("zetDebugReadEvent(hDebug, timeout, event)");

        auto pfnReadEvent = context.zetDdiTable.Debug.pfnReadEvent;

        if( nullptr == pfnReadEvent )
            return logAndPropagateResult_zetDebugReadEvent(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDebug, timeout, event);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugReadEventPrologue( hDebug, timeout, event );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugReadEvent(result, hDebug, timeout, event);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugReadEventPrologue( hDebug, timeout, event );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugReadEvent(result, hDebug, timeout, event);
        }

        auto driver_result = pfnReadEvent( hDebug, timeout, event );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugReadEventEpilogue( hDebug, timeout, event ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugReadEvent(result, hDebug, timeout, event);
        }

        return logAndPropagateResult_zetDebugReadEvent(driver_result, hDebug, timeout, event);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugAcknowledgeEvent
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugAcknowledgeEvent(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        const zet_debug_event_t* event                  ///< [in] a pointer to a ::zet_debug_event_t.
        )
    {
        context.logger->log_trace("zetDebugAcknowledgeEvent(hDebug, event)");

        auto pfnAcknowledgeEvent = context.zetDdiTable.Debug.pfnAcknowledgeEvent;

        if( nullptr == pfnAcknowledgeEvent )
            return logAndPropagateResult_zetDebugAcknowledgeEvent(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDebug, event);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugAcknowledgeEventPrologue( hDebug, event );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugAcknowledgeEvent(result, hDebug, event);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugAcknowledgeEventPrologue( hDebug, event );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugAcknowledgeEvent(result, hDebug, event);
        }

        auto driver_result = pfnAcknowledgeEvent( hDebug, event );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugAcknowledgeEventEpilogue( hDebug, event ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugAcknowledgeEvent(result, hDebug, event);
        }

        return logAndPropagateResult_zetDebugAcknowledgeEvent(driver_result, hDebug, event);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugInterrupt
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugInterrupt(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread                       ///< [in] the thread to interrupt
        )
    {
        context.logger->log_trace("zetDebugInterrupt(hDebug, thread)");

        auto pfnInterrupt = context.zetDdiTable.Debug.pfnInterrupt;

        if( nullptr == pfnInterrupt )
            return logAndPropagateResult_zetDebugInterrupt(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDebug, thread);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugInterruptPrologue( hDebug, thread );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugInterrupt(result, hDebug, thread);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugInterruptPrologue( hDebug, thread );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugInterrupt(result, hDebug, thread);
        }

        auto driver_result = pfnInterrupt( hDebug, thread );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugInterruptEpilogue( hDebug, thread ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugInterrupt(result, hDebug, thread);
        }

        return logAndPropagateResult_zetDebugInterrupt(driver_result, hDebug, thread);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDebugResume
    __zedlllocal ze_result_t ZE_APICALL
    zetDebugResume(
        zet_debug_session_handle_t hDebug,              ///< [in] debug session handle
        ze_device_thread_t thread                       ///< [in] the thread to resume
        )
    {
        context.logger->log_trace("zetDebugResume(hDebug, thread)");

        auto pfnResume = context.zetDdiTable.Debug.pfnResume;

        if( nullptr == pfnResume )
            return logAndPropagateResult_zetDebugResume(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDebug, thread);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugResumePrologue( hDebug, thread );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugResume(result, hDebug, thread);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugResumePrologue( hDebug, thread );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugResume(result, hDebug, thread);
        }

        auto driver_result = pfnResume( hDebug, thread );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugResumeEpilogue( hDebug, thread ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugResume(result, hDebug, thread);
        }

        return logAndPropagateResult_zetDebugResume(driver_result, hDebug, thread);
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
        context.logger->log_trace("zetDebugReadMemory(hDebug, thread, desc, size, buffer)");

        auto pfnReadMemory = context.zetDdiTable.Debug.pfnReadMemory;

        if( nullptr == pfnReadMemory )
            return logAndPropagateResult_zetDebugReadMemory(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDebug, thread, desc, size, buffer);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugReadMemoryPrologue( hDebug, thread, desc, size, buffer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugReadMemory(result, hDebug, thread, desc, size, buffer);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugReadMemoryPrologue( hDebug, thread, desc, size, buffer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugReadMemory(result, hDebug, thread, desc, size, buffer);
        }

        auto driver_result = pfnReadMemory( hDebug, thread, desc, size, buffer );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugReadMemoryEpilogue( hDebug, thread, desc, size, buffer ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugReadMemory(result, hDebug, thread, desc, size, buffer);
        }

        return logAndPropagateResult_zetDebugReadMemory(driver_result, hDebug, thread, desc, size, buffer);
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
        context.logger->log_trace("zetDebugWriteMemory(hDebug, thread, desc, size, buffer)");

        auto pfnWriteMemory = context.zetDdiTable.Debug.pfnWriteMemory;

        if( nullptr == pfnWriteMemory )
            return logAndPropagateResult_zetDebugWriteMemory(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDebug, thread, desc, size, buffer);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugWriteMemoryPrologue( hDebug, thread, desc, size, buffer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugWriteMemory(result, hDebug, thread, desc, size, buffer);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugWriteMemoryPrologue( hDebug, thread, desc, size, buffer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugWriteMemory(result, hDebug, thread, desc, size, buffer);
        }

        auto driver_result = pfnWriteMemory( hDebug, thread, desc, size, buffer );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugWriteMemoryEpilogue( hDebug, thread, desc, size, buffer ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugWriteMemory(result, hDebug, thread, desc, size, buffer);
        }

        return logAndPropagateResult_zetDebugWriteMemory(driver_result, hDebug, thread, desc, size, buffer);
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
        context.logger->log_trace("zetDebugGetRegisterSetProperties(hDevice, pCount, pRegisterSetProperties)");

        auto pfnGetRegisterSetProperties = context.zetDdiTable.Debug.pfnGetRegisterSetProperties;

        if( nullptr == pfnGetRegisterSetProperties )
            return logAndPropagateResult_zetDebugGetRegisterSetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, pRegisterSetProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugGetRegisterSetPropertiesPrologue( hDevice, pCount, pRegisterSetProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugGetRegisterSetProperties(result, hDevice, pCount, pRegisterSetProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugGetRegisterSetPropertiesPrologue( hDevice, pCount, pRegisterSetProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugGetRegisterSetProperties(result, hDevice, pCount, pRegisterSetProperties);
        }

        auto driver_result = pfnGetRegisterSetProperties( hDevice, pCount, pRegisterSetProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugGetRegisterSetPropertiesEpilogue( hDevice, pCount, pRegisterSetProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugGetRegisterSetProperties(result, hDevice, pCount, pRegisterSetProperties);
        }

        return logAndPropagateResult_zetDebugGetRegisterSetProperties(driver_result, hDevice, pCount, pRegisterSetProperties);
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
        context.logger->log_trace("zetDebugGetThreadRegisterSetProperties(hDebug, thread, pCount, pRegisterSetProperties)");

        auto pfnGetThreadRegisterSetProperties = context.zetDdiTable.Debug.pfnGetThreadRegisterSetProperties;

        if( nullptr == pfnGetThreadRegisterSetProperties )
            return logAndPropagateResult_zetDebugGetThreadRegisterSetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDebug, thread, pCount, pRegisterSetProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugGetThreadRegisterSetPropertiesPrologue( hDebug, thread, pCount, pRegisterSetProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugGetThreadRegisterSetProperties(result, hDebug, thread, pCount, pRegisterSetProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugGetThreadRegisterSetPropertiesPrologue( hDebug, thread, pCount, pRegisterSetProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugGetThreadRegisterSetProperties(result, hDebug, thread, pCount, pRegisterSetProperties);
        }

        auto driver_result = pfnGetThreadRegisterSetProperties( hDebug, thread, pCount, pRegisterSetProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugGetThreadRegisterSetPropertiesEpilogue( hDebug, thread, pCount, pRegisterSetProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugGetThreadRegisterSetProperties(result, hDebug, thread, pCount, pRegisterSetProperties);
        }

        return logAndPropagateResult_zetDebugGetThreadRegisterSetProperties(driver_result, hDebug, thread, pCount, pRegisterSetProperties);
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
                                                        ///< equal to the `count` member of ::zet_debug_regset_properties_t for the
                                                        ///< type
        void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
        )
    {
        context.logger->log_trace("zetDebugReadRegisters(hDebug, thread, type, start, count, pRegisterValues)");

        auto pfnReadRegisters = context.zetDdiTable.Debug.pfnReadRegisters;

        if( nullptr == pfnReadRegisters )
            return logAndPropagateResult_zetDebugReadRegisters(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDebug, thread, type, start, count, pRegisterValues);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugReadRegistersPrologue( hDebug, thread, type, start, count, pRegisterValues );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugReadRegisters(result, hDebug, thread, type, start, count, pRegisterValues);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugReadRegistersPrologue( hDebug, thread, type, start, count, pRegisterValues );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugReadRegisters(result, hDebug, thread, type, start, count, pRegisterValues);
        }

        auto driver_result = pfnReadRegisters( hDebug, thread, type, start, count, pRegisterValues );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugReadRegistersEpilogue( hDebug, thread, type, start, count, pRegisterValues ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugReadRegisters(result, hDebug, thread, type, start, count, pRegisterValues);
        }

        return logAndPropagateResult_zetDebugReadRegisters(driver_result, hDebug, thread, type, start, count, pRegisterValues);
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
                                                        ///< or equal to the `count` member of ::zet_debug_regset_properties_t for
                                                        ///< the type
        void* pRegisterValues                           ///< [in,out][optional][range(0, count)] buffer of register values
        )
    {
        context.logger->log_trace("zetDebugWriteRegisters(hDebug, thread, type, start, count, pRegisterValues)");

        auto pfnWriteRegisters = context.zetDdiTable.Debug.pfnWriteRegisters;

        if( nullptr == pfnWriteRegisters )
            return logAndPropagateResult_zetDebugWriteRegisters(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDebug, thread, type, start, count, pRegisterValues);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugWriteRegistersPrologue( hDebug, thread, type, start, count, pRegisterValues );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugWriteRegisters(result, hDebug, thread, type, start, count, pRegisterValues);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDebugWriteRegistersPrologue( hDebug, thread, type, start, count, pRegisterValues );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugWriteRegisters(result, hDebug, thread, type, start, count, pRegisterValues);
        }

        auto driver_result = pfnWriteRegisters( hDebug, thread, type, start, count, pRegisterValues );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDebugWriteRegistersEpilogue( hDebug, thread, type, start, count, pRegisterValues ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDebugWriteRegisters(result, hDebug, thread, type, start, count, pRegisterValues);
        }

        return logAndPropagateResult_zetDebugWriteRegisters(driver_result, hDebug, thread, type, start, count, pRegisterValues);
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
        context.logger->log_trace("zetMetricGroupGet(hDevice, pCount, phMetricGroups)");

        auto pfnGet = context.zetDdiTable.MetricGroup.pfnGet;

        if( nullptr == pfnGet )
            return logAndPropagateResult_zetMetricGroupGet(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phMetricGroups);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupGetPrologue( hDevice, pCount, phMetricGroups );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupGet(result, hDevice, pCount, phMetricGroups);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupGetPrologue( hDevice, pCount, phMetricGroups );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupGet(result, hDevice, pCount, phMetricGroups);
        }

        auto driver_result = pfnGet( hDevice, pCount, phMetricGroups );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupGetEpilogue( hDevice, pCount, phMetricGroups ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupGet(result, hDevice, pCount, phMetricGroups);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phMetricGroups) && (i < *pCount); ++i){
                if (phMetricGroups[i]){
                    context.handleLifetime->addHandle( phMetricGroups[i] );
                    context.handleLifetime->addDependent( hDevice, phMetricGroups[i] );
                }
            }
        }
        return logAndPropagateResult_zetMetricGroupGet(driver_result, hDevice, pCount, phMetricGroups);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupGetProperties(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle of the metric group
        zet_metric_group_properties_t* pProperties      ///< [in,out] metric group properties
        )
    {
        context.logger->log_trace("zetMetricGroupGetProperties(hMetricGroup, pProperties)");

        auto pfnGetProperties = context.zetDdiTable.MetricGroup.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult_zetMetricGroupGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricGroup, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupGetPropertiesPrologue( hMetricGroup, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupGetProperties(result, hMetricGroup, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupGetPropertiesPrologue( hMetricGroup, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupGetProperties(result, hMetricGroup, pProperties);
        }

        auto driver_result = pfnGetProperties( hMetricGroup, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupGetPropertiesEpilogue( hMetricGroup, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupGetProperties(result, hMetricGroup, pProperties);
        }

        return logAndPropagateResult_zetMetricGroupGetProperties(driver_result, hMetricGroup, pProperties);
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
        context.logger->log_trace("zetMetricGroupCalculateMetricValues(hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues)");

        auto pfnCalculateMetricValues = context.zetDdiTable.MetricGroup.pfnCalculateMetricValues;

        if( nullptr == pfnCalculateMetricValues )
            return logAndPropagateResult_zetMetricGroupCalculateMetricValues(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupCalculateMetricValuesPrologue( hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupCalculateMetricValues(result, hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupCalculateMetricValuesPrologue( hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupCalculateMetricValues(result, hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues);
        }

        auto driver_result = pfnCalculateMetricValues( hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupCalculateMetricValuesEpilogue( hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupCalculateMetricValues(result, hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues);
        }

        return logAndPropagateResult_zetMetricGroupCalculateMetricValues(driver_result, hMetricGroup, type, rawDataSize, pRawData, pMetricValueCount, pMetricValues);
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
        context.logger->log_trace("zetMetricGet(hMetricGroup, pCount, phMetrics)");

        auto pfnGet = context.zetDdiTable.Metric.pfnGet;

        if( nullptr == pfnGet )
            return logAndPropagateResult_zetMetricGet(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricGroup, pCount, phMetrics);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGetPrologue( hMetricGroup, pCount, phMetrics );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGet(result, hMetricGroup, pCount, phMetrics);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGetPrologue( hMetricGroup, pCount, phMetrics );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGet(result, hMetricGroup, pCount, phMetrics);
        }

        auto driver_result = pfnGet( hMetricGroup, pCount, phMetrics );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGetEpilogue( hMetricGroup, pCount, phMetrics ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGet(result, hMetricGroup, pCount, phMetrics);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phMetrics) && (i < *pCount); ++i){
                if (phMetrics[i]){
                    context.handleLifetime->addHandle( phMetrics[i] );
                    context.handleLifetime->addDependent( hMetricGroup, phMetrics[i] );
                }
            }
        }
        return logAndPropagateResult_zetMetricGet(driver_result, hMetricGroup, pCount, phMetrics);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGetProperties
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGetProperties(
        zet_metric_handle_t hMetric,                    ///< [in] handle of the metric
        zet_metric_properties_t* pProperties            ///< [in,out] metric properties
        )
    {
        context.logger->log_trace("zetMetricGetProperties(hMetric, pProperties)");

        auto pfnGetProperties = context.zetDdiTable.Metric.pfnGetProperties;

        if( nullptr == pfnGetProperties )
            return logAndPropagateResult_zetMetricGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetric, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGetPropertiesPrologue( hMetric, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGetProperties(result, hMetric, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGetPropertiesPrologue( hMetric, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGetProperties(result, hMetric, pProperties);
        }

        auto driver_result = pfnGetProperties( hMetric, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGetPropertiesEpilogue( hMetric, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGetProperties(result, hMetric, pProperties);
        }

        return logAndPropagateResult_zetMetricGetProperties(driver_result, hMetric, pProperties);
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
        context.logger->log_trace("zetContextActivateMetricGroups(hContext, hDevice, count, phMetricGroupsLocal)");

        auto pfnActivateMetricGroups = context.zetDdiTable.Context.pfnActivateMetricGroups;

        if( nullptr == pfnActivateMetricGroups )
            return logAndPropagateResult_zetContextActivateMetricGroups(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hContext, hDevice, count, phMetricGroups);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetContextActivateMetricGroupsPrologue( hContext, hDevice, count, phMetricGroups );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetContextActivateMetricGroups(result, hContext, hDevice, count, phMetricGroups);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetContextActivateMetricGroupsPrologue( hContext, hDevice, count, phMetricGroups );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetContextActivateMetricGroups(result, hContext, hDevice, count, phMetricGroups);
        }

        auto driver_result = pfnActivateMetricGroups( hContext, hDevice, count, phMetricGroups );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetContextActivateMetricGroupsEpilogue( hContext, hDevice, count, phMetricGroups ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetContextActivateMetricGroups(result, hContext, hDevice, count, phMetricGroups);
        }

        return logAndPropagateResult_zetContextActivateMetricGroups(driver_result, hContext, hDevice, count, phMetricGroups);
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
        context.logger->log_trace("zetMetricStreamerOpen(hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer)");

        auto pfnOpen = context.zetDdiTable.MetricStreamer.pfnOpen;

        if( nullptr == pfnOpen )
            return logAndPropagateResult_zetMetricStreamerOpen(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricStreamerOpenPrologue( hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricStreamerOpen(result, hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricStreamerOpenPrologue( hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricStreamerOpen(result, hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer);
        }

        auto driver_result = pfnOpen( hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricStreamerOpenEpilogue( hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricStreamerOpen(result, hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer);
        }

        return logAndPropagateResult_zetMetricStreamerOpen(driver_result, hContext, hDevice, hMetricGroup, desc, hNotificationEvent, phMetricStreamer);
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
        context.logger->log_trace("zetCommandListAppendMetricStreamerMarker(hCommandList, hMetricStreamer, value)");

        auto pfnAppendMetricStreamerMarker = context.zetDdiTable.CommandList.pfnAppendMetricStreamerMarker;

        if( nullptr == pfnAppendMetricStreamerMarker )
            return logAndPropagateResult_zetCommandListAppendMetricStreamerMarker(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hCommandList, hMetricStreamer, value);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetCommandListAppendMetricStreamerMarkerPrologue( hCommandList, hMetricStreamer, value );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetCommandListAppendMetricStreamerMarker(result, hCommandList, hMetricStreamer, value);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetCommandListAppendMetricStreamerMarkerPrologue( hCommandList, hMetricStreamer, value );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetCommandListAppendMetricStreamerMarker(result, hCommandList, hMetricStreamer, value);
        }

        auto driver_result = pfnAppendMetricStreamerMarker( hCommandList, hMetricStreamer, value );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetCommandListAppendMetricStreamerMarkerEpilogue( hCommandList, hMetricStreamer, value ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetCommandListAppendMetricStreamerMarker(result, hCommandList, hMetricStreamer, value);
        }

        return logAndPropagateResult_zetCommandListAppendMetricStreamerMarker(driver_result, hCommandList, hMetricStreamer, value);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricStreamerClose
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricStreamerClose(
        zet_metric_streamer_handle_t hMetricStreamer    ///< [in][release] handle of the metric streamer
        )
    {
        context.logger->log_trace("zetMetricStreamerClose(hMetricStreamer)");

        auto pfnClose = context.zetDdiTable.MetricStreamer.pfnClose;

        if( nullptr == pfnClose )
            return logAndPropagateResult_zetMetricStreamerClose(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricStreamer);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricStreamerClosePrologue( hMetricStreamer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricStreamerClose(result, hMetricStreamer);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricStreamerClosePrologue( hMetricStreamer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricStreamerClose(result, hMetricStreamer);
        }

        auto driver_result = pfnClose( hMetricStreamer );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricStreamerCloseEpilogue( hMetricStreamer ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricStreamerClose(result, hMetricStreamer);
        }

        return logAndPropagateResult_zetMetricStreamerClose(driver_result, hMetricStreamer);
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
        context.logger->log_trace("zetMetricStreamerReadData(hMetricStreamer, maxReportCount, pRawDataSize, pRawData)");

        auto pfnReadData = context.zetDdiTable.MetricStreamer.pfnReadData;

        if( nullptr == pfnReadData )
            return logAndPropagateResult_zetMetricStreamerReadData(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricStreamer, maxReportCount, pRawDataSize, pRawData);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricStreamerReadDataPrologue( hMetricStreamer, maxReportCount, pRawDataSize, pRawData );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricStreamerReadData(result, hMetricStreamer, maxReportCount, pRawDataSize, pRawData);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricStreamerReadDataPrologue( hMetricStreamer, maxReportCount, pRawDataSize, pRawData );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricStreamerReadData(result, hMetricStreamer, maxReportCount, pRawDataSize, pRawData);
        }

        auto driver_result = pfnReadData( hMetricStreamer, maxReportCount, pRawDataSize, pRawData );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricStreamerReadDataEpilogue( hMetricStreamer, maxReportCount, pRawDataSize, pRawData ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricStreamerReadData(result, hMetricStreamer, maxReportCount, pRawDataSize, pRawData);
        }

        return logAndPropagateResult_zetMetricStreamerReadData(driver_result, hMetricStreamer, maxReportCount, pRawDataSize, pRawData);
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
        context.logger->log_trace("zetMetricQueryPoolCreate(hContext, hDevice, hMetricGroup, desc, phMetricQueryPool)");

        auto pfnCreate = context.zetDdiTable.MetricQueryPool.pfnCreate;

        if( nullptr == pfnCreate )
            return logAndPropagateResult_zetMetricQueryPoolCreate(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hContext, hDevice, hMetricGroup, desc, phMetricQueryPool);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricQueryPoolCreatePrologue( hContext, hDevice, hMetricGroup, desc, phMetricQueryPool );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryPoolCreate(result, hContext, hDevice, hMetricGroup, desc, phMetricQueryPool);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricQueryPoolCreatePrologue( hContext, hDevice, hMetricGroup, desc, phMetricQueryPool );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryPoolCreate(result, hContext, hDevice, hMetricGroup, desc, phMetricQueryPool);
        }

        auto driver_result = pfnCreate( hContext, hDevice, hMetricGroup, desc, phMetricQueryPool );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricQueryPoolCreateEpilogue( hContext, hDevice, hMetricGroup, desc, phMetricQueryPool ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryPoolCreate(result, hContext, hDevice, hMetricGroup, desc, phMetricQueryPool);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phMetricQueryPool){
                context.handleLifetime->addHandle( *phMetricQueryPool );
                context.handleLifetime->addDependent( hContext, *phMetricQueryPool );

            }
        }
        return logAndPropagateResult_zetMetricQueryPoolCreate(driver_result, hContext, hDevice, hMetricGroup, desc, phMetricQueryPool);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryPoolDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryPoolDestroy(
        zet_metric_query_pool_handle_t hMetricQueryPool ///< [in][release] handle of the metric query pool
        )
    {
        context.logger->log_trace("zetMetricQueryPoolDestroy(hMetricQueryPool)");

        auto pfnDestroy = context.zetDdiTable.MetricQueryPool.pfnDestroy;

        if( nullptr == pfnDestroy )
            return logAndPropagateResult_zetMetricQueryPoolDestroy(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricQueryPool);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricQueryPoolDestroyPrologue( hMetricQueryPool );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryPoolDestroy(result, hMetricQueryPool);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricQueryPoolDestroyPrologue( hMetricQueryPool );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryPoolDestroy(result, hMetricQueryPool);
        }

        auto driver_result = pfnDestroy( hMetricQueryPool );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricQueryPoolDestroyEpilogue( hMetricQueryPool ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryPoolDestroy(result, hMetricQueryPool);
        }

        return logAndPropagateResult_zetMetricQueryPoolDestroy(driver_result, hMetricQueryPool);
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
        context.logger->log_trace("zetMetricQueryCreate(hMetricQueryPool, index, phMetricQuery)");

        auto pfnCreate = context.zetDdiTable.MetricQuery.pfnCreate;

        if( nullptr == pfnCreate )
            return logAndPropagateResult_zetMetricQueryCreate(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricQueryPool, index, phMetricQuery);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricQueryCreatePrologue( hMetricQueryPool, index, phMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryCreate(result, hMetricQueryPool, index, phMetricQuery);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricQueryCreatePrologue( hMetricQueryPool, index, phMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryCreate(result, hMetricQueryPool, index, phMetricQuery);
        }

        auto driver_result = pfnCreate( hMetricQueryPool, index, phMetricQuery );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricQueryCreateEpilogue( hMetricQueryPool, index, phMetricQuery ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryCreate(result, hMetricQueryPool, index, phMetricQuery);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phMetricQuery){
                context.handleLifetime->addHandle( *phMetricQuery );
                context.handleLifetime->addDependent( hMetricQueryPool, *phMetricQuery );

            }
        }
        return logAndPropagateResult_zetMetricQueryCreate(driver_result, hMetricQueryPool, index, phMetricQuery);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryDestroy(
        zet_metric_query_handle_t hMetricQuery          ///< [in][release] handle of metric query
        )
    {
        context.logger->log_trace("zetMetricQueryDestroy(hMetricQuery)");

        auto pfnDestroy = context.zetDdiTable.MetricQuery.pfnDestroy;

        if( nullptr == pfnDestroy )
            return logAndPropagateResult_zetMetricQueryDestroy(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricQuery);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricQueryDestroyPrologue( hMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryDestroy(result, hMetricQuery);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricQueryDestroyPrologue( hMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryDestroy(result, hMetricQuery);
        }

        auto driver_result = pfnDestroy( hMetricQuery );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricQueryDestroyEpilogue( hMetricQuery ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryDestroy(result, hMetricQuery);
        }

        return logAndPropagateResult_zetMetricQueryDestroy(driver_result, hMetricQuery);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricQueryReset
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricQueryReset(
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of metric query
        )
    {
        context.logger->log_trace("zetMetricQueryReset(hMetricQuery)");

        auto pfnReset = context.zetDdiTable.MetricQuery.pfnReset;

        if( nullptr == pfnReset )
            return logAndPropagateResult_zetMetricQueryReset(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricQuery);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricQueryResetPrologue( hMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryReset(result, hMetricQuery);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricQueryResetPrologue( hMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryReset(result, hMetricQuery);
        }

        auto driver_result = pfnReset( hMetricQuery );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricQueryResetEpilogue( hMetricQuery ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryReset(result, hMetricQuery);
        }

        return logAndPropagateResult_zetMetricQueryReset(driver_result, hMetricQuery);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricQueryBegin
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMetricQueryBegin(
        zet_command_list_handle_t hCommandList,         ///< [in] handle of the command list
        zet_metric_query_handle_t hMetricQuery          ///< [in] handle of the metric query
        )
    {
        context.logger->log_trace("zetCommandListAppendMetricQueryBegin(hCommandList, hMetricQuery)");

        auto pfnAppendMetricQueryBegin = context.zetDdiTable.CommandList.pfnAppendMetricQueryBegin;

        if( nullptr == pfnAppendMetricQueryBegin )
            return logAndPropagateResult_zetCommandListAppendMetricQueryBegin(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hCommandList, hMetricQuery);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetCommandListAppendMetricQueryBeginPrologue( hCommandList, hMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetCommandListAppendMetricQueryBegin(result, hCommandList, hMetricQuery);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetCommandListAppendMetricQueryBeginPrologue( hCommandList, hMetricQuery );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetCommandListAppendMetricQueryBegin(result, hCommandList, hMetricQuery);
        }

        auto driver_result = pfnAppendMetricQueryBegin( hCommandList, hMetricQuery );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetCommandListAppendMetricQueryBeginEpilogue( hCommandList, hMetricQuery ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetCommandListAppendMetricQueryBegin(result, hCommandList, hMetricQuery);
        }

        return logAndPropagateResult_zetCommandListAppendMetricQueryBegin(driver_result, hCommandList, hMetricQuery);
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
        context.logger->log_trace("zetCommandListAppendMetricQueryEnd(hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEventsLocal)");

        auto pfnAppendMetricQueryEnd = context.zetDdiTable.CommandList.pfnAppendMetricQueryEnd;

        if( nullptr == pfnAppendMetricQueryEnd )
            return logAndPropagateResult_zetCommandListAppendMetricQueryEnd(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetCommandListAppendMetricQueryEndPrologue( hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetCommandListAppendMetricQueryEnd(result, hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetCommandListAppendMetricQueryEndPrologue( hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetCommandListAppendMetricQueryEnd(result, hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents);
        }

        auto driver_result = pfnAppendMetricQueryEnd( hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetCommandListAppendMetricQueryEndEpilogue( hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetCommandListAppendMetricQueryEnd(result, hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents);
        }

        return logAndPropagateResult_zetCommandListAppendMetricQueryEnd(driver_result, hCommandList, hMetricQuery, hSignalEvent, numWaitEvents, phWaitEvents);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMetricMemoryBarrier
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMetricMemoryBarrier(
        zet_command_list_handle_t hCommandList          ///< [in] handle of the command list
        )
    {
        context.logger->log_trace("zetCommandListAppendMetricMemoryBarrier(hCommandList)");

        auto pfnAppendMetricMemoryBarrier = context.zetDdiTable.CommandList.pfnAppendMetricMemoryBarrier;

        if( nullptr == pfnAppendMetricMemoryBarrier )
            return logAndPropagateResult_zetCommandListAppendMetricMemoryBarrier(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hCommandList);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetCommandListAppendMetricMemoryBarrierPrologue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetCommandListAppendMetricMemoryBarrier(result, hCommandList);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetCommandListAppendMetricMemoryBarrierPrologue( hCommandList );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetCommandListAppendMetricMemoryBarrier(result, hCommandList);
        }

        auto driver_result = pfnAppendMetricMemoryBarrier( hCommandList );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetCommandListAppendMetricMemoryBarrierEpilogue( hCommandList ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetCommandListAppendMetricMemoryBarrier(result, hCommandList);
        }

        return logAndPropagateResult_zetCommandListAppendMetricMemoryBarrier(driver_result, hCommandList);
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
        context.logger->log_trace("zetMetricQueryGetData(hMetricQuery, pRawDataSize, pRawData)");

        auto pfnGetData = context.zetDdiTable.MetricQuery.pfnGetData;

        if( nullptr == pfnGetData )
            return logAndPropagateResult_zetMetricQueryGetData(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricQuery, pRawDataSize, pRawData);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricQueryGetDataPrologue( hMetricQuery, pRawDataSize, pRawData );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryGetData(result, hMetricQuery, pRawDataSize, pRawData);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricQueryGetDataPrologue( hMetricQuery, pRawDataSize, pRawData );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryGetData(result, hMetricQuery, pRawDataSize, pRawData);
        }

        auto driver_result = pfnGetData( hMetricQuery, pRawDataSize, pRawData );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricQueryGetDataEpilogue( hMetricQuery, pRawDataSize, pRawData ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricQueryGetData(result, hMetricQuery, pRawDataSize, pRawData);
        }

        return logAndPropagateResult_zetMetricQueryGetData(driver_result, hMetricQuery, pRawDataSize, pRawData);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetKernelGetProfileInfo
    __zedlllocal ze_result_t ZE_APICALL
    zetKernelGetProfileInfo(
        zet_kernel_handle_t hKernel,                    ///< [in] handle to kernel
        zet_profile_properties_t* pProfileProperties    ///< [out] pointer to profile properties
        )
    {
        context.logger->log_trace("zetKernelGetProfileInfo(hKernel, pProfileProperties)");

        auto pfnGetProfileInfo = context.zetDdiTable.Kernel.pfnGetProfileInfo;

        if( nullptr == pfnGetProfileInfo )
            return logAndPropagateResult_zetKernelGetProfileInfo(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hKernel, pProfileProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetKernelGetProfileInfoPrologue( hKernel, pProfileProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetKernelGetProfileInfo(result, hKernel, pProfileProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetKernelGetProfileInfoPrologue( hKernel, pProfileProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetKernelGetProfileInfo(result, hKernel, pProfileProperties);
        }

        auto driver_result = pfnGetProfileInfo( hKernel, pProfileProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetKernelGetProfileInfoEpilogue( hKernel, pProfileProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetKernelGetProfileInfo(result, hKernel, pProfileProperties);
        }

        return logAndPropagateResult_zetKernelGetProfileInfo(driver_result, hKernel, pProfileProperties);
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
        context.logger->log_trace("zetTracerExpCreate(hContext, desc, phTracer)");

        auto pfnCreate = context.zetDdiTable.TracerExp.pfnCreate;

        if( nullptr == pfnCreate )
            return logAndPropagateResult_zetTracerExpCreate(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hContext, desc, phTracer);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetTracerExpCreatePrologue( hContext, desc, phTracer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetTracerExpCreate(result, hContext, desc, phTracer);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetTracerExpCreatePrologue( hContext, desc, phTracer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetTracerExpCreate(result, hContext, desc, phTracer);
        }

        auto driver_result = pfnCreate( hContext, desc, phTracer );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetTracerExpCreateEpilogue( hContext, desc, phTracer ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetTracerExpCreate(result, hContext, desc, phTracer);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phTracer){
                context.handleLifetime->addHandle( *phTracer );
                context.handleLifetime->addDependent( hContext, *phTracer );

            }
        }
        return logAndPropagateResult_zetTracerExpCreate(driver_result, hContext, desc, phTracer);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerExpDestroy
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpDestroy(
        zet_tracer_exp_handle_t hTracer                 ///< [in][release] handle of tracer object to destroy
        )
    {
        context.logger->log_trace("zetTracerExpDestroy(hTracer)");

        auto pfnDestroy = context.zetDdiTable.TracerExp.pfnDestroy;

        if( nullptr == pfnDestroy )
            return logAndPropagateResult_zetTracerExpDestroy(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hTracer);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetTracerExpDestroyPrologue( hTracer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetTracerExpDestroy(result, hTracer);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetTracerExpDestroyPrologue( hTracer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetTracerExpDestroy(result, hTracer);
        }

        auto driver_result = pfnDestroy( hTracer );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetTracerExpDestroyEpilogue( hTracer ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetTracerExpDestroy(result, hTracer);
        }

        return logAndPropagateResult_zetTracerExpDestroy(driver_result, hTracer);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerExpSetPrologues
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpSetPrologues(
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        context.logger->log_trace("zetTracerExpSetPrologues(hTracer, pCoreCbs)");

        auto pfnSetPrologues = context.zetDdiTable.TracerExp.pfnSetPrologues;

        if( nullptr == pfnSetPrologues )
            return logAndPropagateResult_zetTracerExpSetPrologues(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hTracer, pCoreCbs);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetTracerExpSetProloguesPrologue( hTracer, pCoreCbs );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetTracerExpSetPrologues(result, hTracer, pCoreCbs);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetTracerExpSetProloguesPrologue( hTracer, pCoreCbs );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetTracerExpSetPrologues(result, hTracer, pCoreCbs);
        }

        auto driver_result = pfnSetPrologues( hTracer, pCoreCbs );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetTracerExpSetProloguesEpilogue( hTracer, pCoreCbs ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetTracerExpSetPrologues(result, hTracer, pCoreCbs);
        }

        return logAndPropagateResult_zetTracerExpSetPrologues(driver_result, hTracer, pCoreCbs);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerExpSetEpilogues
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpSetEpilogues(
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        zet_core_callbacks_t* pCoreCbs                  ///< [in] pointer to table of 'core' callback function pointers
        )
    {
        context.logger->log_trace("zetTracerExpSetEpilogues(hTracer, pCoreCbs)");

        auto pfnSetEpilogues = context.zetDdiTable.TracerExp.pfnSetEpilogues;

        if( nullptr == pfnSetEpilogues )
            return logAndPropagateResult_zetTracerExpSetEpilogues(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hTracer, pCoreCbs);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetTracerExpSetEpiloguesPrologue( hTracer, pCoreCbs );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetTracerExpSetEpilogues(result, hTracer, pCoreCbs);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetTracerExpSetEpiloguesPrologue( hTracer, pCoreCbs );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetTracerExpSetEpilogues(result, hTracer, pCoreCbs);
        }

        auto driver_result = pfnSetEpilogues( hTracer, pCoreCbs );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetTracerExpSetEpiloguesEpilogue( hTracer, pCoreCbs ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetTracerExpSetEpilogues(result, hTracer, pCoreCbs);
        }

        return logAndPropagateResult_zetTracerExpSetEpilogues(driver_result, hTracer, pCoreCbs);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetTracerExpSetEnabled
    __zedlllocal ze_result_t ZE_APICALL
    zetTracerExpSetEnabled(
        zet_tracer_exp_handle_t hTracer,                ///< [in] handle of the tracer
        ze_bool_t enable                                ///< [in] enable the tracer if true; disable if false
        )
    {
        context.logger->log_trace("zetTracerExpSetEnabled(hTracer, enable)");

        auto pfnSetEnabled = context.zetDdiTable.TracerExp.pfnSetEnabled;

        if( nullptr == pfnSetEnabled )
            return logAndPropagateResult_zetTracerExpSetEnabled(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hTracer, enable);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetTracerExpSetEnabledPrologue( hTracer, enable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetTracerExpSetEnabled(result, hTracer, enable);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetTracerExpSetEnabledPrologue( hTracer, enable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetTracerExpSetEnabled(result, hTracer, enable);
        }

        auto driver_result = pfnSetEnabled( hTracer, enable );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetTracerExpSetEnabledEpilogue( hTracer, enable ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetTracerExpSetEnabled(result, hTracer, enable);
        }

        return logAndPropagateResult_zetTracerExpSetEnabled(driver_result, hTracer, enable);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDeviceGetConcurrentMetricGroupsExp
    __zedlllocal ze_result_t ZE_APICALL
    zetDeviceGetConcurrentMetricGroupsExp(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t metricGroupCount,                      ///< [in] metric group count
        zet_metric_group_handle_t * phMetricGroups,     ///< [in,out] metrics groups to be re-arranged to be sets of concurrent
                                                        ///< groups
        uint32_t * pMetricGroupsCountPerConcurrentGroup,///< [in,out][optional][*pConcurrentGroupCount] count of metric groups per
                                                        ///< concurrent group.
        uint32_t * pConcurrentGroupCount                ///< [out] number of concurrent groups.
                                                        ///< The value of this parameter could be used to determine the number of
                                                        ///< replays necessary.
        )
    {
        context.logger->log_trace("zetDeviceGetConcurrentMetricGroupsExp(hDevice, metricGroupCount, phMetricGroups, pMetricGroupsCountPerConcurrentGroup, pConcurrentGroupCount)");

        auto pfnGetConcurrentMetricGroupsExp = context.zetDdiTable.DeviceExp.pfnGetConcurrentMetricGroupsExp;

        if( nullptr == pfnGetConcurrentMetricGroupsExp )
            return logAndPropagateResult_zetDeviceGetConcurrentMetricGroupsExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, metricGroupCount, phMetricGroups, pMetricGroupsCountPerConcurrentGroup, pConcurrentGroupCount);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDeviceGetConcurrentMetricGroupsExpPrologue( hDevice, metricGroupCount, phMetricGroups, pMetricGroupsCountPerConcurrentGroup, pConcurrentGroupCount );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDeviceGetConcurrentMetricGroupsExp(result, hDevice, metricGroupCount, phMetricGroups, pMetricGroupsCountPerConcurrentGroup, pConcurrentGroupCount);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDeviceGetConcurrentMetricGroupsExpPrologue( hDevice, metricGroupCount, phMetricGroups, pMetricGroupsCountPerConcurrentGroup, pConcurrentGroupCount );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDeviceGetConcurrentMetricGroupsExp(result, hDevice, metricGroupCount, phMetricGroups, pMetricGroupsCountPerConcurrentGroup, pConcurrentGroupCount);
        }

        auto driver_result = pfnGetConcurrentMetricGroupsExp( hDevice, metricGroupCount, phMetricGroups, pMetricGroupsCountPerConcurrentGroup, pConcurrentGroupCount );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDeviceGetConcurrentMetricGroupsExpEpilogue( hDevice, metricGroupCount, phMetricGroups, pMetricGroupsCountPerConcurrentGroup, pConcurrentGroupCount ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDeviceGetConcurrentMetricGroupsExp(result, hDevice, metricGroupCount, phMetricGroups, pMetricGroupsCountPerConcurrentGroup, pConcurrentGroupCount);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult_zetDeviceGetConcurrentMetricGroupsExp(driver_result, hDevice, metricGroupCount, phMetricGroups, pMetricGroupsCountPerConcurrentGroup, pConcurrentGroupCount);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerCreateExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricTracerCreateExp(
        zet_context_handle_t hContext,                  ///< [in] handle of the context object
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t metricGroupCount,                      ///< [in] metric group count
        zet_metric_group_handle_t* phMetricGroups,      ///< [in][range(0, metricGroupCount )] handles of the metric groups to
                                                        ///< trace
        zet_metric_tracer_exp_desc_t* desc,             ///< [in,out] metric tracer descriptor
        ze_event_handle_t hNotificationEvent,           ///< [in][optional] event used for report availability notification. Note:
                                                        ///< If buffer is not drained when the event it flagged, there is a risk of
                                                        ///< HW event buffer being overrun
        zet_metric_tracer_exp_handle_t* phMetricTracer  ///< [out] handle of the metric tracer
        )
    {
        context.logger->log_trace("zetMetricTracerCreateExp(hContext, hDevice, metricGroupCount, phMetricGroupsLocal, desc, hNotificationEvent, phMetricTracer)");

        auto pfnCreateExp = context.zetDdiTable.MetricTracerExp.pfnCreateExp;

        if( nullptr == pfnCreateExp )
            return logAndPropagateResult_zetMetricTracerCreateExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hContext, hDevice, metricGroupCount, phMetricGroups, desc, hNotificationEvent, phMetricTracer);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricTracerCreateExpPrologue( hContext, hDevice, metricGroupCount, phMetricGroups, desc, hNotificationEvent, phMetricTracer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerCreateExp(result, hContext, hDevice, metricGroupCount, phMetricGroups, desc, hNotificationEvent, phMetricTracer);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricTracerCreateExpPrologue( hContext, hDevice, metricGroupCount, phMetricGroups, desc, hNotificationEvent, phMetricTracer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerCreateExp(result, hContext, hDevice, metricGroupCount, phMetricGroups, desc, hNotificationEvent, phMetricTracer);
        }

        auto driver_result = pfnCreateExp( hContext, hDevice, metricGroupCount, phMetricGroups, desc, hNotificationEvent, phMetricTracer );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricTracerCreateExpEpilogue( hContext, hDevice, metricGroupCount, phMetricGroups, desc, hNotificationEvent, phMetricTracer ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerCreateExp(result, hContext, hDevice, metricGroupCount, phMetricGroups, desc, hNotificationEvent, phMetricTracer);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phMetricTracer){
                context.handleLifetime->addHandle( *phMetricTracer );
                context.handleLifetime->addDependent( hContext, *phMetricTracer );

            }
        }
        return logAndPropagateResult_zetMetricTracerCreateExp(driver_result, hContext, hDevice, metricGroupCount, phMetricGroups, desc, hNotificationEvent, phMetricTracer);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricTracerDestroyExp(
        zet_metric_tracer_exp_handle_t hMetricTracer    ///< [in] handle of the metric tracer
        )
    {
        context.logger->log_trace("zetMetricTracerDestroyExp(hMetricTracer)");

        auto pfnDestroyExp = context.zetDdiTable.MetricTracerExp.pfnDestroyExp;

        if( nullptr == pfnDestroyExp )
            return logAndPropagateResult_zetMetricTracerDestroyExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricTracer);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricTracerDestroyExpPrologue( hMetricTracer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerDestroyExp(result, hMetricTracer);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricTracerDestroyExpPrologue( hMetricTracer );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerDestroyExp(result, hMetricTracer);
        }

        auto driver_result = pfnDestroyExp( hMetricTracer );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricTracerDestroyExpEpilogue( hMetricTracer ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerDestroyExp(result, hMetricTracer);
        }

        return logAndPropagateResult_zetMetricTracerDestroyExp(driver_result, hMetricTracer);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerEnableExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricTracerEnableExp(
        zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
        ze_bool_t synchronous                           ///< [in] request synchronous behavior. Confirmation of successful
                                                        ///< asynchronous operation is done by calling ::zetMetricTracerReadDataExp()
                                                        ///< and checking the return status: ::ZE_RESULT_NOT_READY will be returned
                                                        ///< when the tracer is inactive. ::ZE_RESULT_SUCCESS will be returned 
                                                        ///< when the tracer is active.
        )
    {
        context.logger->log_trace("zetMetricTracerEnableExp(hMetricTracer, synchronous)");

        auto pfnEnableExp = context.zetDdiTable.MetricTracerExp.pfnEnableExp;

        if( nullptr == pfnEnableExp )
            return logAndPropagateResult_zetMetricTracerEnableExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricTracer, synchronous);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricTracerEnableExpPrologue( hMetricTracer, synchronous );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerEnableExp(result, hMetricTracer, synchronous);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricTracerEnableExpPrologue( hMetricTracer, synchronous );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerEnableExp(result, hMetricTracer, synchronous);
        }

        auto driver_result = pfnEnableExp( hMetricTracer, synchronous );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricTracerEnableExpEpilogue( hMetricTracer, synchronous ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerEnableExp(result, hMetricTracer, synchronous);
        }

        return logAndPropagateResult_zetMetricTracerEnableExp(driver_result, hMetricTracer, synchronous);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerDisableExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricTracerDisableExp(
        zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
        ze_bool_t synchronous                           ///< [in] request synchronous behavior. Confirmation of successful
                                                        ///< asynchronous operation is done by calling ::zetMetricTracerReadDataExp()
                                                        ///< and checking the return status: ::ZE_RESULT_SUCCESS will be returned
                                                        ///< when the tracer is active or when it is inactive but still has data. 
                                                        ///< ::ZE_RESULT_NOT_READY will be returned when the tracer is inactive and
                                                        ///< has no more data to be retrieved.
        )
    {
        context.logger->log_trace("zetMetricTracerDisableExp(hMetricTracer, synchronous)");

        auto pfnDisableExp = context.zetDdiTable.MetricTracerExp.pfnDisableExp;

        if( nullptr == pfnDisableExp )
            return logAndPropagateResult_zetMetricTracerDisableExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricTracer, synchronous);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricTracerDisableExpPrologue( hMetricTracer, synchronous );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerDisableExp(result, hMetricTracer, synchronous);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricTracerDisableExpPrologue( hMetricTracer, synchronous );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerDisableExp(result, hMetricTracer, synchronous);
        }

        auto driver_result = pfnDisableExp( hMetricTracer, synchronous );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricTracerDisableExpEpilogue( hMetricTracer, synchronous ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerDisableExp(result, hMetricTracer, synchronous);
        }

        return logAndPropagateResult_zetMetricTracerDisableExp(driver_result, hMetricTracer, synchronous);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerReadDataExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricTracerReadDataExp(
        zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
        size_t* pRawDataSize,                           ///< [in,out] pointer to size in bytes of raw data requested to read.
                                                        ///< if size is zero, then the driver will update the value with the total
                                                        ///< size in bytes needed for all data available.
                                                        ///< if size is non-zero, then driver will only retrieve that amount of
                                                        ///< data. 
                                                        ///< if size is larger than size needed for all data, then driver will
                                                        ///< update the value with the actual size needed.
        uint8_t* pRawData                               ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing tracer
                                                        ///< data in raw format
        )
    {
        context.logger->log_trace("zetMetricTracerReadDataExp(hMetricTracer, pRawDataSize, pRawData)");

        auto pfnReadDataExp = context.zetDdiTable.MetricTracerExp.pfnReadDataExp;

        if( nullptr == pfnReadDataExp )
            return logAndPropagateResult_zetMetricTracerReadDataExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricTracer, pRawDataSize, pRawData);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricTracerReadDataExpPrologue( hMetricTracer, pRawDataSize, pRawData );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerReadDataExp(result, hMetricTracer, pRawDataSize, pRawData);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricTracerReadDataExpPrologue( hMetricTracer, pRawDataSize, pRawData );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerReadDataExp(result, hMetricTracer, pRawDataSize, pRawData);
        }

        auto driver_result = pfnReadDataExp( hMetricTracer, pRawDataSize, pRawData );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricTracerReadDataExpEpilogue( hMetricTracer, pRawDataSize, pRawData ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerReadDataExp(result, hMetricTracer, pRawDataSize, pRawData);
        }

        return logAndPropagateResult_zetMetricTracerReadDataExp(driver_result, hMetricTracer, pRawDataSize, pRawData);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricDecoderCreateExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricDecoderCreateExp(
        zet_metric_tracer_exp_handle_t hMetricTracer,   ///< [in] handle of the metric tracer
        zet_metric_decoder_exp_handle_t* phMetricDecoder///< [out] handle of the metric decoder object
        )
    {
        context.logger->log_trace("zetMetricDecoderCreateExp(hMetricTracer, phMetricDecoder)");

        auto pfnCreateExp = context.zetDdiTable.MetricDecoderExp.pfnCreateExp;

        if( nullptr == pfnCreateExp )
            return logAndPropagateResult_zetMetricDecoderCreateExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricTracer, phMetricDecoder);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricDecoderCreateExpPrologue( hMetricTracer, phMetricDecoder );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricDecoderCreateExp(result, hMetricTracer, phMetricDecoder);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricDecoderCreateExpPrologue( hMetricTracer, phMetricDecoder );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricDecoderCreateExp(result, hMetricTracer, phMetricDecoder);
        }

        auto driver_result = pfnCreateExp( hMetricTracer, phMetricDecoder );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricDecoderCreateExpEpilogue( hMetricTracer, phMetricDecoder ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricDecoderCreateExp(result, hMetricTracer, phMetricDecoder);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phMetricDecoder){
                context.handleLifetime->addHandle( *phMetricDecoder );
                context.handleLifetime->addDependent( hMetricTracer, *phMetricDecoder );

            }
        }
        return logAndPropagateResult_zetMetricDecoderCreateExp(driver_result, hMetricTracer, phMetricDecoder);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricDecoderDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricDecoderDestroyExp(
        zet_metric_decoder_exp_handle_t phMetricDecoder ///< [in] handle of the metric decoder object
        )
    {
        context.logger->log_trace("zetMetricDecoderDestroyExp(phMetricDecoder)");

        auto pfnDestroyExp = context.zetDdiTable.MetricDecoderExp.pfnDestroyExp;

        if( nullptr == pfnDestroyExp )
            return logAndPropagateResult_zetMetricDecoderDestroyExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, phMetricDecoder);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricDecoderDestroyExpPrologue( phMetricDecoder );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricDecoderDestroyExp(result, phMetricDecoder);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricDecoderDestroyExpPrologue( phMetricDecoder );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricDecoderDestroyExp(result, phMetricDecoder);
        }

        auto driver_result = pfnDestroyExp( phMetricDecoder );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricDecoderDestroyExpEpilogue( phMetricDecoder ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricDecoderDestroyExp(result, phMetricDecoder);
        }

        return logAndPropagateResult_zetMetricDecoderDestroyExp(driver_result, phMetricDecoder);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricDecoderGetDecodableMetricsExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricDecoderGetDecodableMetricsExp(
        zet_metric_decoder_exp_handle_t hMetricDecoder, ///< [in] handle of the metric decoder object
        uint32_t* pCount,                               ///< [in,out] pointer to number of decodable metric in the hMetricDecoder
                                                        ///< handle. If count is zero, then the driver shall 
                                                        ///< update the value with the total number of decodable metrics available
                                                        ///< in the decoder. if count is greater than zero 
                                                        ///< but less than the total number of decodable metrics available in the
                                                        ///< decoder, then only that number will be returned. 
                                                        ///< if count is greater than the number of decodable metrics available in
                                                        ///< the decoder, then the driver shall update the 
                                                        ///< value with the actual number of decodable metrics available. 
        zet_metric_handle_t* phMetrics                  ///< [in,out] [range(0, *pCount)] array of handles of decodable metrics in
                                                        ///< the hMetricDecoder handle provided.
        )
    {
        context.logger->log_trace("zetMetricDecoderGetDecodableMetricsExp(hMetricDecoder, pCount, phMetrics)");

        auto pfnGetDecodableMetricsExp = context.zetDdiTable.MetricDecoderExp.pfnGetDecodableMetricsExp;

        if( nullptr == pfnGetDecodableMetricsExp )
            return logAndPropagateResult_zetMetricDecoderGetDecodableMetricsExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricDecoder, pCount, phMetrics);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricDecoderGetDecodableMetricsExpPrologue( hMetricDecoder, pCount, phMetrics );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricDecoderGetDecodableMetricsExp(result, hMetricDecoder, pCount, phMetrics);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricDecoderGetDecodableMetricsExpPrologue( hMetricDecoder, pCount, phMetrics );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricDecoderGetDecodableMetricsExp(result, hMetricDecoder, pCount, phMetrics);
        }

        auto driver_result = pfnGetDecodableMetricsExp( hMetricDecoder, pCount, phMetrics );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricDecoderGetDecodableMetricsExpEpilogue( hMetricDecoder, pCount, phMetrics ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricDecoderGetDecodableMetricsExp(result, hMetricDecoder, pCount, phMetrics);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phMetrics) && (i < *pCount); ++i){
                if (phMetrics[i]){
                    context.handleLifetime->addHandle( phMetrics[i] );
                    context.handleLifetime->addDependent( hMetricDecoder, phMetrics[i] );
                }
            }
        }
        return logAndPropagateResult_zetMetricDecoderGetDecodableMetricsExp(driver_result, hMetricDecoder, pCount, phMetrics);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricTracerDecodeExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricTracerDecodeExp(
        zet_metric_decoder_exp_handle_t phMetricDecoder,///< [in] handle of the metric decoder object
        size_t* pRawDataSize,                           ///< [in,out] size in bytes of raw data buffer. If pMetricEntriesCount is
                                                        ///< greater than zero but less than total number of 
                                                        ///< decodable metrics available in the raw data buffer, then driver shall
                                                        ///< update this value with actual number of raw 
                                                        ///< data bytes processed.
        uint8_t* pRawData,                              ///< [in,out][optional][range(0, *pRawDataSize)] buffer containing tracer
                                                        ///< data in raw format
        uint32_t metricsCount,                          ///< [in] number of decodable metrics in the tracer for which the
                                                        ///< hMetricDecoder handle was provided. See 
                                                        ///< ::zetMetricDecoderGetDecodableMetricsExp(). If metricCount is greater
                                                        ///< than zero but less than the number decodable 
                                                        ///< metrics available in the raw data buffer, then driver shall only
                                                        ///< decode those.
        zet_metric_handle_t* phMetrics,                 ///< [in] [range(0, metricsCount)] array of handles of decodable metrics in
                                                        ///< the decoder for which the hMetricDecoder handle was 
                                                        ///< provided. Metrics handles are expected to be for decodable metrics,
                                                        ///< see ::zetMetricDecoderGetDecodableMetricsExp() 
        uint32_t* pSetCount,                            ///< [in,out] pointer to number of metric sets. If count is zero, then the
                                                        ///< driver shall update the value with the total
                                                        ///< number of metric sets to be decoded. If count is greater than the
                                                        ///< number available in the raw data buffer, then the
                                                        ///< driver shall update the value with the actual number of metric sets to
                                                        ///< be decoded. There is a 1:1 relation between
                                                        ///< the number of sets and sub-devices returned in the decoded entries.
        uint32_t* pMetricEntriesCountPerSet,            ///< [in,out][optional][range(0, *pSetCount)] buffer of metric entries
                                                        ///< counts per metric set, one value per set.
        uint32_t* pMetricEntriesCount,                  ///< [in,out]  pointer to the total number of metric entries decoded, for
                                                        ///< all metric sets. If count is zero, then the
                                                        ///< driver shall update the value with the total number of metric entries
                                                        ///< to be decoded. If count is greater than zero
                                                        ///< but less than the total number of metric entries available in the raw
                                                        ///< data, then user provided number will be decoded.
                                                        ///< If count is greater than the number available in the raw data buffer,
                                                        ///< then the driver shall update the value with
                                                        ///< the actual number of decodable metric entries decoded. If set to null,
                                                        ///< then driver will only update the value of
                                                        ///< pSetCount.
        zet_metric_entry_exp_t* pMetricEntries          ///< [in,out][optional][range(0, *pMetricEntriesCount)] buffer containing
                                                        ///< decoded metric entries
        )
    {
        context.logger->log_trace("zetMetricTracerDecodeExp(phMetricDecoder, pRawDataSize, pRawData, metricsCount, phMetricsLocal, pSetCount, pMetricEntriesCountPerSet, pMetricEntriesCount, pMetricEntries)");

        auto pfnDecodeExp = context.zetDdiTable.MetricTracerExp.pfnDecodeExp;

        if( nullptr == pfnDecodeExp )
            return logAndPropagateResult_zetMetricTracerDecodeExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, phMetricDecoder, pRawDataSize, pRawData, metricsCount, phMetrics, pSetCount, pMetricEntriesCountPerSet, pMetricEntriesCount, pMetricEntries);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricTracerDecodeExpPrologue( phMetricDecoder, pRawDataSize, pRawData, metricsCount, phMetrics, pSetCount, pMetricEntriesCountPerSet, pMetricEntriesCount, pMetricEntries );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerDecodeExp(result, phMetricDecoder, pRawDataSize, pRawData, metricsCount, phMetrics, pSetCount, pMetricEntriesCountPerSet, pMetricEntriesCount, pMetricEntries);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricTracerDecodeExpPrologue( phMetricDecoder, pRawDataSize, pRawData, metricsCount, phMetrics, pSetCount, pMetricEntriesCountPerSet, pMetricEntriesCount, pMetricEntries );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerDecodeExp(result, phMetricDecoder, pRawDataSize, pRawData, metricsCount, phMetrics, pSetCount, pMetricEntriesCountPerSet, pMetricEntriesCount, pMetricEntries);
        }

        auto driver_result = pfnDecodeExp( phMetricDecoder, pRawDataSize, pRawData, metricsCount, phMetrics, pSetCount, pMetricEntriesCountPerSet, pMetricEntriesCount, pMetricEntries );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricTracerDecodeExpEpilogue( phMetricDecoder, pRawDataSize, pRawData, metricsCount, phMetrics, pSetCount, pMetricEntriesCountPerSet, pMetricEntriesCount, pMetricEntries ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricTracerDecodeExp(result, phMetricDecoder, pRawDataSize, pRawData, metricsCount, phMetrics, pSetCount, pMetricEntriesCountPerSet, pMetricEntriesCount, pMetricEntries);
        }

        return logAndPropagateResult_zetMetricTracerDecodeExp(driver_result, phMetricDecoder, pRawDataSize, pRawData, metricsCount, phMetrics, pSetCount, pMetricEntriesCountPerSet, pMetricEntriesCount, pMetricEntries);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetCommandListAppendMarkerExp
    __zedlllocal ze_result_t ZE_APICALL
    zetCommandListAppendMarkerExp(
        zet_command_list_handle_t hCommandList,         ///< [in] handle to the command list
        zet_metric_group_handle_t hMetricGroup,         ///< [in] handle to the marker metric group.
                                                        ///< ::zet_metric_group_type_exp_flags_t could be used to check whether
                                                        ///< marker is supoported by the metric group.
        uint32_t value                                  ///< [in] marker value
        )
    {
        context.logger->log_trace("zetCommandListAppendMarkerExp(hCommandList, hMetricGroup, value)");

        auto pfnAppendMarkerExp = context.zetDdiTable.CommandListExp.pfnAppendMarkerExp;

        if( nullptr == pfnAppendMarkerExp )
            return logAndPropagateResult_zetCommandListAppendMarkerExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hCommandList, hMetricGroup, value);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetCommandListAppendMarkerExpPrologue( hCommandList, hMetricGroup, value );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetCommandListAppendMarkerExp(result, hCommandList, hMetricGroup, value);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetCommandListAppendMarkerExpPrologue( hCommandList, hMetricGroup, value );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetCommandListAppendMarkerExp(result, hCommandList, hMetricGroup, value);
        }

        auto driver_result = pfnAppendMarkerExp( hCommandList, hMetricGroup, value );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetCommandListAppendMarkerExpEpilogue( hCommandList, hMetricGroup, value ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetCommandListAppendMarkerExp(result, hCommandList, hMetricGroup, value);
        }

        return logAndPropagateResult_zetCommandListAppendMarkerExp(driver_result, hCommandList, hMetricGroup, value);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDeviceEnableMetricsExp
    __zedlllocal ze_result_t ZE_APICALL
    zetDeviceEnableMetricsExp(
        zet_device_handle_t hDevice                     ///< [in] handle of the device where metrics collection has to be enabled.
        )
    {
        context.logger->log_trace("zetDeviceEnableMetricsExp(hDevice)");

        auto pfnEnableMetricsExp = context.zetDdiTable.DeviceExp.pfnEnableMetricsExp;

        if( nullptr == pfnEnableMetricsExp )
            return logAndPropagateResult_zetDeviceEnableMetricsExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDeviceEnableMetricsExpPrologue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDeviceEnableMetricsExp(result, hDevice);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDeviceEnableMetricsExpPrologue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDeviceEnableMetricsExp(result, hDevice);
        }

        auto driver_result = pfnEnableMetricsExp( hDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDeviceEnableMetricsExpEpilogue( hDevice ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDeviceEnableMetricsExp(result, hDevice);
        }

        return logAndPropagateResult_zetDeviceEnableMetricsExp(driver_result, hDevice);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDeviceDisableMetricsExp
    __zedlllocal ze_result_t ZE_APICALL
    zetDeviceDisableMetricsExp(
        zet_device_handle_t hDevice                     ///< [in] handle of the device where metrics collection has to be disabled
        )
    {
        context.logger->log_trace("zetDeviceDisableMetricsExp(hDevice)");

        auto pfnDisableMetricsExp = context.zetDdiTable.DeviceExp.pfnDisableMetricsExp;

        if( nullptr == pfnDisableMetricsExp )
            return logAndPropagateResult_zetDeviceDisableMetricsExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDeviceDisableMetricsExpPrologue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDeviceDisableMetricsExp(result, hDevice);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDeviceDisableMetricsExpPrologue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDeviceDisableMetricsExp(result, hDevice);
        }

        auto driver_result = pfnDisableMetricsExp( hDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDeviceDisableMetricsExpEpilogue( hDevice ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDeviceDisableMetricsExp(result, hDevice);
        }

        return logAndPropagateResult_zetDeviceDisableMetricsExp(driver_result, hDevice);
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
        context.logger->log_trace("zetMetricGroupCalculateMultipleMetricValuesExp(hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues)");

        auto pfnCalculateMultipleMetricValuesExp = context.zetDdiTable.MetricGroupExp.pfnCalculateMultipleMetricValuesExp;

        if( nullptr == pfnCalculateMultipleMetricValuesExp )
            return logAndPropagateResult_zetMetricGroupCalculateMultipleMetricValuesExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupCalculateMultipleMetricValuesExpPrologue( hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupCalculateMultipleMetricValuesExp(result, hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupCalculateMultipleMetricValuesExpPrologue( hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupCalculateMultipleMetricValuesExp(result, hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues);
        }

        auto driver_result = pfnCalculateMultipleMetricValuesExp( hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupCalculateMultipleMetricValuesExpEpilogue( hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupCalculateMultipleMetricValuesExp(result, hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues);
        }

        return logAndPropagateResult_zetMetricGroupCalculateMultipleMetricValuesExp(driver_result, hMetricGroup, type, rawDataSize, pRawData, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues);
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
        context.logger->log_trace("zetMetricGroupGetGlobalTimestampsExp(hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp)");

        auto pfnGetGlobalTimestampsExp = context.zetDdiTable.MetricGroupExp.pfnGetGlobalTimestampsExp;

        if( nullptr == pfnGetGlobalTimestampsExp )
            return logAndPropagateResult_zetMetricGroupGetGlobalTimestampsExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupGetGlobalTimestampsExpPrologue( hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupGetGlobalTimestampsExp(result, hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupGetGlobalTimestampsExpPrologue( hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupGetGlobalTimestampsExp(result, hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp);
        }

        auto driver_result = pfnGetGlobalTimestampsExp( hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupGetGlobalTimestampsExpEpilogue( hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupGetGlobalTimestampsExp(result, hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult_zetMetricGroupGetGlobalTimestampsExp(driver_result, hMetricGroup, synchronizedWithHost, globalTimestamp, metricTimestamp);
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
        context.logger->log_trace("zetMetricGroupGetExportDataExp(hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData)");

        auto pfnGetExportDataExp = context.zetDdiTable.MetricGroupExp.pfnGetExportDataExp;

        if( nullptr == pfnGetExportDataExp )
            return logAndPropagateResult_zetMetricGroupGetExportDataExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupGetExportDataExpPrologue( hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupGetExportDataExp(result, hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupGetExportDataExpPrologue( hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupGetExportDataExp(result, hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData);
        }

        auto driver_result = pfnGetExportDataExp( hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupGetExportDataExpEpilogue( hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupGetExportDataExp(result, hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult_zetMetricGroupGetExportDataExp(driver_result, hMetricGroup, pRawData, rawDataSize, pExportDataSize, pExportData);
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
        context.logger->log_trace("zetMetricGroupCalculateMetricExportDataExp(hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues)");

        auto pfnCalculateMetricExportDataExp = context.zetDdiTable.MetricGroupExp.pfnCalculateMetricExportDataExp;

        if( nullptr == pfnCalculateMetricExportDataExp )
            return logAndPropagateResult_zetMetricGroupCalculateMetricExportDataExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupCalculateMetricExportDataExpPrologue( hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupCalculateMetricExportDataExp(result, hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupCalculateMetricExportDataExpPrologue( hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupCalculateMetricExportDataExp(result, hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues);
        }

        auto driver_result = pfnCalculateMetricExportDataExp( hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupCalculateMetricExportDataExpEpilogue( hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupCalculateMetricExportDataExp(result, hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues);
        }

        return logAndPropagateResult_zetMetricGroupCalculateMetricExportDataExp(driver_result, hDriver, type, exportDataSize, pExportData, pCalculateDescriptor, pSetCount, pTotalMetricValueCount, pMetricCounts, pMetricValues);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricProgrammableGetExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricProgrammableGetExp(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        uint32_t* pCount,                               ///< [in,out] pointer to the number of metric programmable handles.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< total number of metric programmable handles available.
                                                        ///< if count is greater than the number of metric programmable handles
                                                        ///< available, then the driver shall update the value with the correct
                                                        ///< number of metric programmable handles available.
        zet_metric_programmable_exp_handle_t* phMetricProgrammables ///< [in,out][optional][range(0, *pCount)] array of handle of metric programmables.
                                                        ///< if count is less than the number of metric programmables available,
                                                        ///< then driver shall only retrieve that number of metric programmables.
        )
    {
        context.logger->log_trace("zetMetricProgrammableGetExp(hDevice, pCount, phMetricProgrammables)");

        auto pfnGetExp = context.zetDdiTable.MetricProgrammableExp.pfnGetExp;

        if( nullptr == pfnGetExp )
            return logAndPropagateResult_zetMetricProgrammableGetExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phMetricProgrammables);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricProgrammableGetExpPrologue( hDevice, pCount, phMetricProgrammables );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricProgrammableGetExp(result, hDevice, pCount, phMetricProgrammables);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricProgrammableGetExpPrologue( hDevice, pCount, phMetricProgrammables );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricProgrammableGetExp(result, hDevice, pCount, phMetricProgrammables);
        }

        auto driver_result = pfnGetExp( hDevice, pCount, phMetricProgrammables );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricProgrammableGetExpEpilogue( hDevice, pCount, phMetricProgrammables ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricProgrammableGetExp(result, hDevice, pCount, phMetricProgrammables);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phMetricProgrammables) && (i < *pCount); ++i){
                if (phMetricProgrammables[i]){
                    context.handleLifetime->addHandle( phMetricProgrammables[i] );
                    context.handleLifetime->addDependent( hDevice, phMetricProgrammables[i] );
                }
            }
        }
        return logAndPropagateResult_zetMetricProgrammableGetExp(driver_result, hDevice, pCount, phMetricProgrammables);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricProgrammableGetPropertiesExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricProgrammableGetPropertiesExp(
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        zet_metric_programmable_exp_properties_t* pProperties   ///< [in,out] properties of the metric programmable
        )
    {
        context.logger->log_trace("zetMetricProgrammableGetPropertiesExp(hMetricProgrammable, pProperties)");

        auto pfnGetPropertiesExp = context.zetDdiTable.MetricProgrammableExp.pfnGetPropertiesExp;

        if( nullptr == pfnGetPropertiesExp )
            return logAndPropagateResult_zetMetricProgrammableGetPropertiesExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricProgrammable, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricProgrammableGetPropertiesExpPrologue( hMetricProgrammable, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricProgrammableGetPropertiesExp(result, hMetricProgrammable, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricProgrammableGetPropertiesExpPrologue( hMetricProgrammable, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricProgrammableGetPropertiesExp(result, hMetricProgrammable, pProperties);
        }

        auto driver_result = pfnGetPropertiesExp( hMetricProgrammable, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricProgrammableGetPropertiesExpEpilogue( hMetricProgrammable, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricProgrammableGetPropertiesExp(result, hMetricProgrammable, pProperties);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult_zetMetricProgrammableGetPropertiesExp(driver_result, hMetricProgrammable, pProperties);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricProgrammableGetParamInfoExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricProgrammableGetParamInfoExp(
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        uint32_t* pParameterCount,                      ///< [in,out] count of the parameters to retrieve parameter info.
                                                        ///< if value pParameterCount is greater than count of parameters
                                                        ///< available, then pParameterCount will be updated with count of
                                                        ///< parameters available.
                                                        ///< The count of parameters available can be queried using ::zetMetricProgrammableGetPropertiesExp.
        zet_metric_programmable_param_info_exp_t* pParameterInfo///< [in,out][range(1, *pParameterCount)] array of parameter info.
                                                        ///< if parameterCount is less than the number of parameters available,
                                                        ///< then driver shall only retrieve that number of parameter info.
        )
    {
        context.logger->log_trace("zetMetricProgrammableGetParamInfoExp(hMetricProgrammable, pParameterCount, pParameterInfo)");

        auto pfnGetParamInfoExp = context.zetDdiTable.MetricProgrammableExp.pfnGetParamInfoExp;

        if( nullptr == pfnGetParamInfoExp )
            return logAndPropagateResult_zetMetricProgrammableGetParamInfoExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricProgrammable, pParameterCount, pParameterInfo);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricProgrammableGetParamInfoExpPrologue( hMetricProgrammable, pParameterCount, pParameterInfo );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricProgrammableGetParamInfoExp(result, hMetricProgrammable, pParameterCount, pParameterInfo);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricProgrammableGetParamInfoExpPrologue( hMetricProgrammable, pParameterCount, pParameterInfo );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricProgrammableGetParamInfoExp(result, hMetricProgrammable, pParameterCount, pParameterInfo);
        }

        auto driver_result = pfnGetParamInfoExp( hMetricProgrammable, pParameterCount, pParameterInfo );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricProgrammableGetParamInfoExpEpilogue( hMetricProgrammable, pParameterCount, pParameterInfo ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricProgrammableGetParamInfoExp(result, hMetricProgrammable, pParameterCount, pParameterInfo);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult_zetMetricProgrammableGetParamInfoExp(driver_result, hMetricProgrammable, pParameterCount, pParameterInfo);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricProgrammableGetParamValueInfoExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricProgrammableGetParamValueInfoExp(
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        uint32_t parameterOrdinal,                      ///< [in] ordinal of the parameter in the metric programmable
        uint32_t* pValueInfoCount,                      ///< [in,out] count of parameter value information to retrieve.
                                                        ///< if value at pValueInfoCount is greater than count of value info
                                                        ///< available, then pValueInfoCount will be updated with count of value
                                                        ///< info available.
                                                        ///< The count of parameter value info available can be queried using ::zetMetricProgrammableGetParamInfoExp.
        zet_metric_programmable_param_value_info_exp_t* pValueInfo  ///< [in,out][range(1, *pValueInfoCount)] array of parameter value info.
                                                        ///< if pValueInfoCount is less than the number of value info available,
                                                        ///< then driver shall only retrieve that number of value info.
        )
    {
        context.logger->log_trace("zetMetricProgrammableGetParamValueInfoExp(hMetricProgrammable, parameterOrdinal, pValueInfoCount, pValueInfo)");

        auto pfnGetParamValueInfoExp = context.zetDdiTable.MetricProgrammableExp.pfnGetParamValueInfoExp;

        if( nullptr == pfnGetParamValueInfoExp )
            return logAndPropagateResult_zetMetricProgrammableGetParamValueInfoExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricProgrammable, parameterOrdinal, pValueInfoCount, pValueInfo);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricProgrammableGetParamValueInfoExpPrologue( hMetricProgrammable, parameterOrdinal, pValueInfoCount, pValueInfo );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricProgrammableGetParamValueInfoExp(result, hMetricProgrammable, parameterOrdinal, pValueInfoCount, pValueInfo);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricProgrammableGetParamValueInfoExpPrologue( hMetricProgrammable, parameterOrdinal, pValueInfoCount, pValueInfo );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricProgrammableGetParamValueInfoExp(result, hMetricProgrammable, parameterOrdinal, pValueInfoCount, pValueInfo);
        }

        auto driver_result = pfnGetParamValueInfoExp( hMetricProgrammable, parameterOrdinal, pValueInfoCount, pValueInfo );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricProgrammableGetParamValueInfoExpEpilogue( hMetricProgrammable, parameterOrdinal, pValueInfoCount, pValueInfo ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricProgrammableGetParamValueInfoExp(result, hMetricProgrammable, parameterOrdinal, pValueInfoCount, pValueInfo);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult_zetMetricProgrammableGetParamValueInfoExp(driver_result, hMetricProgrammable, parameterOrdinal, pValueInfoCount, pValueInfo);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricCreateFromProgrammableExp2
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricCreateFromProgrammableExp2(
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        uint32_t parameterCount,                        ///< [in] Count of parameters to set.
        zet_metric_programmable_param_value_exp_t* pParameterValues,///< [in] list of parameter values to be set.
        const char* pName,                              ///< [in] pointer to metric name to be used. Must point to a
                                                        ///< null-terminated character array no longer than ::ZET_MAX_METRIC_NAME.
        const char* pDescription,                       ///< [in] pointer to metric description to be used. Must point to a
                                                        ///< null-terminated character array no longer than
                                                        ///< ::ZET_MAX_METRIC_DESCRIPTION.
        uint32_t* pMetricHandleCount,                   ///< [in,out] Pointer to the number of metric handles.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< number of metric handles available for this programmable.
                                                        ///< if count is greater than the number of metric handles available, then
                                                        ///< the driver shall update the value with the correct number of metric
                                                        ///< handles available.
        zet_metric_handle_t* phMetricHandles            ///< [in,out][optional][range(0,*pMetricHandleCount)] array of handle of metrics.
                                                        ///< if count is less than the number of metrics available, then driver
                                                        ///< shall only retrieve that number of metric handles.
        )
    {
        context.logger->log_trace("zetMetricCreateFromProgrammableExp2(hMetricProgrammable, parameterCount, pParameterValues, pName, pDescription, pMetricHandleCount, phMetricHandles)");

        auto pfnCreateFromProgrammableExp2 = context.zetDdiTable.MetricExp.pfnCreateFromProgrammableExp2;

        if( nullptr == pfnCreateFromProgrammableExp2 )
            return logAndPropagateResult_zetMetricCreateFromProgrammableExp2(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricProgrammable, parameterCount, pParameterValues, pName, pDescription, pMetricHandleCount, phMetricHandles);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricCreateFromProgrammableExp2Prologue( hMetricProgrammable, parameterCount, pParameterValues, pName, pDescription, pMetricHandleCount, phMetricHandles );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricCreateFromProgrammableExp2(result, hMetricProgrammable, parameterCount, pParameterValues, pName, pDescription, pMetricHandleCount, phMetricHandles);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricCreateFromProgrammableExp2Prologue( hMetricProgrammable, parameterCount, pParameterValues, pName, pDescription, pMetricHandleCount, phMetricHandles );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricCreateFromProgrammableExp2(result, hMetricProgrammable, parameterCount, pParameterValues, pName, pDescription, pMetricHandleCount, phMetricHandles);
        }

        auto driver_result = pfnCreateFromProgrammableExp2( hMetricProgrammable, parameterCount, pParameterValues, pName, pDescription, pMetricHandleCount, phMetricHandles );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricCreateFromProgrammableExp2Epilogue( hMetricProgrammable, parameterCount, pParameterValues, pName, pDescription, pMetricHandleCount, phMetricHandles ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricCreateFromProgrammableExp2(result, hMetricProgrammable, parameterCount, pParameterValues, pName, pDescription, pMetricHandleCount, phMetricHandles);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phMetricHandles) && (i < *pMetricHandleCount); ++i){
                if (phMetricHandles[i]){
                    context.handleLifetime->addHandle( phMetricHandles[i] );
                    context.handleLifetime->addDependent( hMetricProgrammable, phMetricHandles[i] );
                }
            }
        }
        return logAndPropagateResult_zetMetricCreateFromProgrammableExp2(driver_result, hMetricProgrammable, parameterCount, pParameterValues, pName, pDescription, pMetricHandleCount, phMetricHandles);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricCreateFromProgrammableExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricCreateFromProgrammableExp(
        zet_metric_programmable_exp_handle_t hMetricProgrammable,   ///< [in] handle of the metric programmable
        zet_metric_programmable_param_value_exp_t* pParameterValues,///< [in] list of parameter values to be set.
        uint32_t parameterCount,                        ///< [in] Count of parameters to set.
        const char* pName,                              ///< [in] pointer to metric name to be used. Must point to a
                                                        ///< null-terminated character array no longer than ::ZET_MAX_METRIC_NAME.
        const char* pDescription,                       ///< [in] pointer to metric description to be used. Must point to a
                                                        ///< null-terminated character array no longer than
                                                        ///< ::ZET_MAX_METRIC_DESCRIPTION.
        uint32_t* pMetricHandleCount,                   ///< [in,out] Pointer to the number of metric handles.
                                                        ///< if count is zero, then the driver shall update the value with the
                                                        ///< number of metric handles available for this programmable.
                                                        ///< if count is greater than the number of metric handles available, then
                                                        ///< the driver shall update the value with the correct number of metric
                                                        ///< handles available.
        zet_metric_handle_t* phMetricHandles            ///< [in,out][optional][range(0,*pMetricHandleCount)] array of handle of metrics.
                                                        ///< if count is less than the number of metrics available, then driver
                                                        ///< shall only retrieve that number of metric handles.
        )
    {
        context.logger->log_trace("zetMetricCreateFromProgrammableExp(hMetricProgrammable, pParameterValues, parameterCount, pName, pDescription, pMetricHandleCount, phMetricHandles)");

        auto pfnCreateFromProgrammableExp = context.zetDdiTable.MetricExp.pfnCreateFromProgrammableExp;

        if( nullptr == pfnCreateFromProgrammableExp )
            return logAndPropagateResult_zetMetricCreateFromProgrammableExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricProgrammable, pParameterValues, parameterCount, pName, pDescription, pMetricHandleCount, phMetricHandles);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricCreateFromProgrammableExpPrologue( hMetricProgrammable, pParameterValues, parameterCount, pName, pDescription, pMetricHandleCount, phMetricHandles );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricCreateFromProgrammableExp(result, hMetricProgrammable, pParameterValues, parameterCount, pName, pDescription, pMetricHandleCount, phMetricHandles);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricCreateFromProgrammableExpPrologue( hMetricProgrammable, pParameterValues, parameterCount, pName, pDescription, pMetricHandleCount, phMetricHandles );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricCreateFromProgrammableExp(result, hMetricProgrammable, pParameterValues, parameterCount, pName, pDescription, pMetricHandleCount, phMetricHandles);
        }

        auto driver_result = pfnCreateFromProgrammableExp( hMetricProgrammable, pParameterValues, parameterCount, pName, pDescription, pMetricHandleCount, phMetricHandles );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricCreateFromProgrammableExpEpilogue( hMetricProgrammable, pParameterValues, parameterCount, pName, pDescription, pMetricHandleCount, phMetricHandles ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricCreateFromProgrammableExp(result, hMetricProgrammable, pParameterValues, parameterCount, pName, pDescription, pMetricHandleCount, phMetricHandles);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phMetricHandles) && (i < *pMetricHandleCount); ++i){
                if (phMetricHandles[i]){
                    context.handleLifetime->addHandle( phMetricHandles[i] );
                    context.handleLifetime->addDependent( hMetricProgrammable, phMetricHandles[i] );
                }
            }
        }
        return logAndPropagateResult_zetMetricCreateFromProgrammableExp(driver_result, hMetricProgrammable, pParameterValues, parameterCount, pName, pDescription, pMetricHandleCount, phMetricHandles);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetDeviceCreateMetricGroupsFromMetricsExp
    __zedlllocal ze_result_t ZE_APICALL
    zetDeviceCreateMetricGroupsFromMetricsExp(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device.
        uint32_t metricCount,                           ///< [in] number of metric handles.
        zet_metric_handle_t * phMetrics,                ///< [in] metric handles to be added to the metric groups.
        const char * pMetricGroupNamePrefix,            ///< [in] prefix to the name created for the metric groups. Must point to a
                                                        ///< null-terminated character array no longer than
                                                        ///< ::ZET_MAX_METRIC_GROUP_NAME_PREFIX_EXP.
        const char * pDescription,                      ///< [in] pointer to description of the metric groups. Must point to a
                                                        ///< null-terminated character array no longer than
                                                        ///< ::ZET_MAX_METRIC_GROUP_DESCRIPTION.
        uint32_t * pMetricGroupCount,                   ///< [in,out] pointer to the number of metric group handles to be created.
                                                        ///< if pMetricGroupCount is zero, then the driver shall update the value
                                                        ///< with the maximum possible number of metric group handles that could be created.
                                                        ///< if pMetricGroupCount is greater than the number of metric group
                                                        ///< handles that could be created, then the driver shall update the value
                                                        ///< with the correct number of metric group handles generated.
                                                        ///< if pMetricGroupCount is lesser than the number of metric group handles
                                                        ///< that could be created, then ::ZE_RESULT_ERROR_INVALID_ARGUMENT is returned.
        zet_metric_group_handle_t* phMetricGroup        ///< [in,out][optional][range(0, *pMetricGroupCount)] array of handle of
                                                        ///< metric group handles.
                                                        ///< Created Metric group handles.
        )
    {
        context.logger->log_trace("zetDeviceCreateMetricGroupsFromMetricsExp(hDevice, metricCount, phMetrics, pMetricGroupNamePrefix, pDescription, pMetricGroupCount, phMetricGroup)");

        auto pfnCreateMetricGroupsFromMetricsExp = context.zetDdiTable.DeviceExp.pfnCreateMetricGroupsFromMetricsExp;

        if( nullptr == pfnCreateMetricGroupsFromMetricsExp )
            return logAndPropagateResult_zetDeviceCreateMetricGroupsFromMetricsExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, metricCount, phMetrics, pMetricGroupNamePrefix, pDescription, pMetricGroupCount, phMetricGroup);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDeviceCreateMetricGroupsFromMetricsExpPrologue( hDevice, metricCount, phMetrics, pMetricGroupNamePrefix, pDescription, pMetricGroupCount, phMetricGroup );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDeviceCreateMetricGroupsFromMetricsExp(result, hDevice, metricCount, phMetrics, pMetricGroupNamePrefix, pDescription, pMetricGroupCount, phMetricGroup);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetDeviceCreateMetricGroupsFromMetricsExpPrologue( hDevice, metricCount, phMetrics, pMetricGroupNamePrefix, pDescription, pMetricGroupCount, phMetricGroup );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDeviceCreateMetricGroupsFromMetricsExp(result, hDevice, metricCount, phMetrics, pMetricGroupNamePrefix, pDescription, pMetricGroupCount, phMetricGroup);
        }

        auto driver_result = pfnCreateMetricGroupsFromMetricsExp( hDevice, metricCount, phMetrics, pMetricGroupNamePrefix, pDescription, pMetricGroupCount, phMetricGroup );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetDeviceCreateMetricGroupsFromMetricsExpEpilogue( hDevice, metricCount, phMetrics, pMetricGroupNamePrefix, pDescription, pMetricGroupCount, phMetricGroup ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetDeviceCreateMetricGroupsFromMetricsExp(result, hDevice, metricCount, phMetrics, pMetricGroupNamePrefix, pDescription, pMetricGroupCount, phMetricGroup);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phMetricGroup) && (i < *pMetricGroupCount); ++i){
                if (phMetricGroup[i]){
                    context.handleLifetime->addHandle( phMetricGroup[i] );
                    context.handleLifetime->addDependent( hDevice, phMetricGroup[i] );
                }
            }
        }
        return logAndPropagateResult_zetDeviceCreateMetricGroupsFromMetricsExp(driver_result, hDevice, metricCount, phMetrics, pMetricGroupNamePrefix, pDescription, pMetricGroupCount, phMetricGroup);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupCreateExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupCreateExp(
        zet_device_handle_t hDevice,                    ///< [in] handle of the device
        const char* pName,                              ///< [in] pointer to metric group name. Must point to a null-terminated
                                                        ///< character array no longer than ::ZET_MAX_METRIC_GROUP_NAME.
        const char* pDescription,                       ///< [in] pointer to metric group description. Must point to a
                                                        ///< null-terminated character array no longer than
                                                        ///< ::ZET_MAX_METRIC_GROUP_DESCRIPTION.
        zet_metric_group_sampling_type_flags_t samplingType,///< [in] Sampling type for the metric group.
        zet_metric_group_handle_t* phMetricGroup        ///< [in,out] Created Metric group handle
        )
    {
        context.logger->log_trace("zetMetricGroupCreateExp(hDevice, pName, pDescription, samplingType, phMetricGroup)");

        auto pfnCreateExp = context.zetDdiTable.MetricGroupExp.pfnCreateExp;

        if( nullptr == pfnCreateExp )
            return logAndPropagateResult_zetMetricGroupCreateExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pName, pDescription, samplingType, phMetricGroup);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupCreateExpPrologue( hDevice, pName, pDescription, samplingType, phMetricGroup );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupCreateExp(result, hDevice, pName, pDescription, samplingType, phMetricGroup);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupCreateExpPrologue( hDevice, pName, pDescription, samplingType, phMetricGroup );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupCreateExp(result, hDevice, pName, pDescription, samplingType, phMetricGroup);
        }

        auto driver_result = pfnCreateExp( hDevice, pName, pDescription, samplingType, phMetricGroup );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupCreateExpEpilogue( hDevice, pName, pDescription, samplingType, phMetricGroup ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupCreateExp(result, hDevice, pName, pDescription, samplingType, phMetricGroup);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phMetricGroup){
                context.handleLifetime->addHandle( *phMetricGroup );
                context.handleLifetime->addDependent( hDevice, *phMetricGroup );

            }
        }
        return logAndPropagateResult_zetMetricGroupCreateExp(driver_result, hDevice, pName, pDescription, samplingType, phMetricGroup);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupAddMetricExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupAddMetricExp(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] Handle of the metric group
        zet_metric_handle_t hMetric,                    ///< [in] Metric to be added to the group.
        size_t * pErrorStringSize,                      ///< [in,out][optional] Size of the error string to query, if an error was
                                                        ///< reported during adding the metric handle.
                                                        ///< if *pErrorStringSize is zero, then the driver shall update the value
                                                        ///< with the size of the error string in bytes.
        char* pErrorString                              ///< [in,out][optional][range(0, *pErrorStringSize)] Error string.
                                                        ///< if *pErrorStringSize is less than the length of the error string
                                                        ///< available, then driver shall only retrieve that length of error string.
        )
    {
        context.logger->log_trace("zetMetricGroupAddMetricExp(hMetricGroup, hMetric, pErrorStringSize, pErrorString)");

        auto pfnAddMetricExp = context.zetDdiTable.MetricGroupExp.pfnAddMetricExp;

        if( nullptr == pfnAddMetricExp )
            return logAndPropagateResult_zetMetricGroupAddMetricExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricGroup, hMetric, pErrorStringSize, pErrorString);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupAddMetricExpPrologue( hMetricGroup, hMetric, pErrorStringSize, pErrorString );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupAddMetricExp(result, hMetricGroup, hMetric, pErrorStringSize, pErrorString);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupAddMetricExpPrologue( hMetricGroup, hMetric, pErrorStringSize, pErrorString );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupAddMetricExp(result, hMetricGroup, hMetric, pErrorStringSize, pErrorString);
        }

        auto driver_result = pfnAddMetricExp( hMetricGroup, hMetric, pErrorStringSize, pErrorString );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupAddMetricExpEpilogue( hMetricGroup, hMetric, pErrorStringSize, pErrorString ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupAddMetricExp(result, hMetricGroup, hMetric, pErrorStringSize, pErrorString);
        }

        return logAndPropagateResult_zetMetricGroupAddMetricExp(driver_result, hMetricGroup, hMetric, pErrorStringSize, pErrorString);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupRemoveMetricExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupRemoveMetricExp(
        zet_metric_group_handle_t hMetricGroup,         ///< [in] Handle of the metric group
        zet_metric_handle_t hMetric                     ///< [in] Metric handle to be removed from the metric group.
        )
    {
        context.logger->log_trace("zetMetricGroupRemoveMetricExp(hMetricGroup, hMetric)");

        auto pfnRemoveMetricExp = context.zetDdiTable.MetricGroupExp.pfnRemoveMetricExp;

        if( nullptr == pfnRemoveMetricExp )
            return logAndPropagateResult_zetMetricGroupRemoveMetricExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricGroup, hMetric);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupRemoveMetricExpPrologue( hMetricGroup, hMetric );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupRemoveMetricExp(result, hMetricGroup, hMetric);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupRemoveMetricExpPrologue( hMetricGroup, hMetric );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupRemoveMetricExp(result, hMetricGroup, hMetric);
        }

        auto driver_result = pfnRemoveMetricExp( hMetricGroup, hMetric );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupRemoveMetricExpEpilogue( hMetricGroup, hMetric ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupRemoveMetricExp(result, hMetricGroup, hMetric);
        }

        return logAndPropagateResult_zetMetricGroupRemoveMetricExp(driver_result, hMetricGroup, hMetric);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupCloseExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupCloseExp(
        zet_metric_group_handle_t hMetricGroup          ///< [in] Handle of the metric group
        )
    {
        context.logger->log_trace("zetMetricGroupCloseExp(hMetricGroup)");

        auto pfnCloseExp = context.zetDdiTable.MetricGroupExp.pfnCloseExp;

        if( nullptr == pfnCloseExp )
            return logAndPropagateResult_zetMetricGroupCloseExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricGroup);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupCloseExpPrologue( hMetricGroup );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupCloseExp(result, hMetricGroup);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupCloseExpPrologue( hMetricGroup );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupCloseExp(result, hMetricGroup);
        }

        auto driver_result = pfnCloseExp( hMetricGroup );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupCloseExpEpilogue( hMetricGroup ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupCloseExp(result, hMetricGroup);
        }

        return logAndPropagateResult_zetMetricGroupCloseExp(driver_result, hMetricGroup);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricGroupDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricGroupDestroyExp(
        zet_metric_group_handle_t hMetricGroup          ///< [in] Handle of the metric group to destroy
        )
    {
        context.logger->log_trace("zetMetricGroupDestroyExp(hMetricGroup)");

        auto pfnDestroyExp = context.zetDdiTable.MetricGroupExp.pfnDestroyExp;

        if( nullptr == pfnDestroyExp )
            return logAndPropagateResult_zetMetricGroupDestroyExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetricGroup);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupDestroyExpPrologue( hMetricGroup );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupDestroyExp(result, hMetricGroup);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricGroupDestroyExpPrologue( hMetricGroup );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupDestroyExp(result, hMetricGroup);
        }

        auto driver_result = pfnDestroyExp( hMetricGroup );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricGroupDestroyExpEpilogue( hMetricGroup ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricGroupDestroyExp(result, hMetricGroup);
        }

        return logAndPropagateResult_zetMetricGroupDestroyExp(driver_result, hMetricGroup);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zetMetricDestroyExp
    __zedlllocal ze_result_t ZE_APICALL
    zetMetricDestroyExp(
        zet_metric_handle_t hMetric                     ///< [in] Handle of the metric to destroy
        )
    {
        context.logger->log_trace("zetMetricDestroyExp(hMetric)");

        auto pfnDestroyExp = context.zetDdiTable.MetricExp.pfnDestroyExp;

        if( nullptr == pfnDestroyExp )
            return logAndPropagateResult_zetMetricDestroyExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMetric);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricDestroyExpPrologue( hMetric );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricDestroyExp(result, hMetric);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zetHandleLifetime.zetMetricDestroyExpPrologue( hMetric );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricDestroyExp(result, hMetric);
        }

        auto driver_result = pfnDestroyExp( hMetric );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zetValidation->zetMetricDestroyExpEpilogue( hMetric ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zetMetricDestroyExp(result, hMetric);
        }

        return logAndPropagateResult_zetMetricDestroyExp(driver_result, hMetric);
    }

} // namespace validation_layer

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricDecoderExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricDecoderExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_decoder_exp_dditable_t* pDdiTable    ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.MetricDecoderExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnCreateExp                                = pDdiTable->pfnCreateExp;
        pDdiTable->pfnCreateExp                              = validation_layer::zetMetricDecoderCreateExp;
    }
    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnDestroyExp                               = pDdiTable->pfnDestroyExp;
        pDdiTable->pfnDestroyExp                             = validation_layer::zetMetricDecoderDestroyExp;
    }
    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnGetDecodableMetricsExp                   = pDdiTable->pfnGetDecodableMetricsExp;
        pDdiTable->pfnGetDecodableMetricsExp                 = validation_layer::zetMetricDecoderGetDecodableMetricsExp;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricProgrammableExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricProgrammableExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_programmable_exp_dditable_t* pDdiTable   ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.MetricProgrammableExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetExp                                   = pDdiTable->pfnGetExp;
        pDdiTable->pfnGetExp                                 = validation_layer::zetMetricProgrammableGetExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetPropertiesExp                         = pDdiTable->pfnGetPropertiesExp;
        pDdiTable->pfnGetPropertiesExp                       = validation_layer::zetMetricProgrammableGetPropertiesExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetParamInfoExp                          = pDdiTable->pfnGetParamInfoExp;
        pDdiTable->pfnGetParamInfoExp                        = validation_layer::zetMetricProgrammableGetParamInfoExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetParamValueInfoExp                     = pDdiTable->pfnGetParamValueInfoExp;
        pDdiTable->pfnGetParamValueInfoExp                   = validation_layer::zetMetricProgrammableGetParamValueInfoExp;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricTracerExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricTracerExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_tracer_exp_dditable_t* pDdiTable     ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.MetricTracerExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnCreateExp                                = pDdiTable->pfnCreateExp;
        pDdiTable->pfnCreateExp                              = validation_layer::zetMetricTracerCreateExp;
    }
    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnDestroyExp                               = pDdiTable->pfnDestroyExp;
        pDdiTable->pfnDestroyExp                             = validation_layer::zetMetricTracerDestroyExp;
    }
    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnEnableExp                                = pDdiTable->pfnEnableExp;
        pDdiTable->pfnEnableExp                              = validation_layer::zetMetricTracerEnableExp;
    }
    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnDisableExp                               = pDdiTable->pfnDisableExp;
        pDdiTable->pfnDisableExp                             = validation_layer::zetMetricTracerDisableExp;
    }
    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnReadDataExp                              = pDdiTable->pfnReadDataExp;
        pDdiTable->pfnReadDataExp                            = validation_layer::zetMetricTracerReadDataExp;
    }
    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnDecodeExp                                = pDdiTable->pfnDecodeExp;
        pDdiTable->pfnDecodeExp                              = validation_layer::zetMetricTracerDecodeExp;
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
zetGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.Device;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetDebugProperties                       = pDdiTable->pfnGetDebugProperties;
        pDdiTable->pfnGetDebugProperties                     = validation_layer::zetDeviceGetDebugProperties;
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
zetGetDeviceExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_device_exp_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.DeviceExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnGetConcurrentMetricGroupsExp             = pDdiTable->pfnGetConcurrentMetricGroupsExp;
        pDdiTable->pfnGetConcurrentMetricGroupsExp           = validation_layer::zetDeviceGetConcurrentMetricGroupsExp;
    }
    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnCreateMetricGroupsFromMetricsExp         = pDdiTable->pfnCreateMetricGroupsFromMetricsExp;
        pDdiTable->pfnCreateMetricGroupsFromMetricsExp       = validation_layer::zetDeviceCreateMetricGroupsFromMetricsExp;
    }
    if (version >= ZE_API_VERSION_1_13) {
        dditable.pfnEnableMetricsExp                         = pDdiTable->pfnEnableMetricsExp;
        pDdiTable->pfnEnableMetricsExp                       = validation_layer::zetDeviceEnableMetricsExp;
    }
    if (version >= ZE_API_VERSION_1_13) {
        dditable.pfnDisableMetricsExp                        = pDdiTable->pfnDisableMetricsExp;
        pDdiTable->pfnDisableMetricsExp                      = validation_layer::zetDeviceDisableMetricsExp;
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
zetGetContextProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_context_dditable_t* pDdiTable               ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.Context;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnActivateMetricGroups                     = pDdiTable->pfnActivateMetricGroups;
        pDdiTable->pfnActivateMetricGroups                   = validation_layer::zetContextActivateMetricGroups;
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
zetGetCommandListProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_command_list_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.CommandList;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendMetricStreamerMarker               = pDdiTable->pfnAppendMetricStreamerMarker;
        pDdiTable->pfnAppendMetricStreamerMarker             = validation_layer::zetCommandListAppendMetricStreamerMarker;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendMetricQueryBegin                   = pDdiTable->pfnAppendMetricQueryBegin;
        pDdiTable->pfnAppendMetricQueryBegin                 = validation_layer::zetCommandListAppendMetricQueryBegin;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendMetricQueryEnd                     = pDdiTable->pfnAppendMetricQueryEnd;
        pDdiTable->pfnAppendMetricQueryEnd                   = validation_layer::zetCommandListAppendMetricQueryEnd;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAppendMetricMemoryBarrier                = pDdiTable->pfnAppendMetricMemoryBarrier;
        pDdiTable->pfnAppendMetricMemoryBarrier              = validation_layer::zetCommandListAppendMetricMemoryBarrier;
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
zetGetCommandListExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_command_list_exp_dditable_t* pDdiTable      ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.CommandListExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_13) {
        dditable.pfnAppendMarkerExp                          = pDdiTable->pfnAppendMarkerExp;
        pDdiTable->pfnAppendMarkerExp                        = validation_layer::zetCommandListAppendMarkerExp;
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
zetGetKernelProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_kernel_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.Kernel;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProfileInfo                           = pDdiTable->pfnGetProfileInfo;
        pDdiTable->pfnGetProfileInfo                         = validation_layer::zetKernelGetProfileInfo;
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
zetGetModuleProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_module_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.Module;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetDebugInfo                             = pDdiTable->pfnGetDebugInfo;
        pDdiTable->pfnGetDebugInfo                           = validation_layer::zetModuleGetDebugInfo;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAttach                                   = pDdiTable->pfnAttach;
        pDdiTable->pfnAttach                                 = validation_layer::zetDebugAttach;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDetach                                   = pDdiTable->pfnDetach;
        pDdiTable->pfnDetach                                 = validation_layer::zetDebugDetach;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnReadEvent                                = pDdiTable->pfnReadEvent;
        pDdiTable->pfnReadEvent                              = validation_layer::zetDebugReadEvent;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnAcknowledgeEvent                         = pDdiTable->pfnAcknowledgeEvent;
        pDdiTable->pfnAcknowledgeEvent                       = validation_layer::zetDebugAcknowledgeEvent;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnInterrupt                                = pDdiTable->pfnInterrupt;
        pDdiTable->pfnInterrupt                              = validation_layer::zetDebugInterrupt;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnResume                                   = pDdiTable->pfnResume;
        pDdiTable->pfnResume                                 = validation_layer::zetDebugResume;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnReadMemory                               = pDdiTable->pfnReadMemory;
        pDdiTable->pfnReadMemory                             = validation_layer::zetDebugReadMemory;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnWriteMemory                              = pDdiTable->pfnWriteMemory;
        pDdiTable->pfnWriteMemory                            = validation_layer::zetDebugWriteMemory;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetRegisterSetProperties                 = pDdiTable->pfnGetRegisterSetProperties;
        pDdiTable->pfnGetRegisterSetProperties               = validation_layer::zetDebugGetRegisterSetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnReadRegisters                            = pDdiTable->pfnReadRegisters;
        pDdiTable->pfnReadRegisters                          = validation_layer::zetDebugReadRegisters;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnWriteRegisters                           = pDdiTable->pfnWriteRegisters;
        pDdiTable->pfnWriteRegisters                         = validation_layer::zetDebugWriteRegisters;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnGetThreadRegisterSetProperties           = pDdiTable->pfnGetThreadRegisterSetProperties;
        pDdiTable->pfnGetThreadRegisterSetProperties         = validation_layer::zetDebugGetThreadRegisterSetProperties;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGet                                      = pDdiTable->pfnGet;
        pDdiTable->pfnGet                                    = validation_layer::zetMetricGet;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zetMetricGetProperties;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's MetricExp table
///        with current process' addresses
///
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
ZE_DLLEXPORT ze_result_t ZE_APICALL
zetGetMetricExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zet_metric_exp_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zetDdiTable.MetricExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_11) {
        dditable.pfnCreateFromProgrammableExp2               = pDdiTable->pfnCreateFromProgrammableExp2;
        pDdiTable->pfnCreateFromProgrammableExp2             = validation_layer::zetMetricCreateFromProgrammableExp2;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnCreateFromProgrammableExp                = pDdiTable->pfnCreateFromProgrammableExp;
        pDdiTable->pfnCreateFromProgrammableExp              = validation_layer::zetMetricCreateFromProgrammableExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnDestroyExp                               = pDdiTable->pfnDestroyExp;
        pDdiTable->pfnDestroyExp                             = validation_layer::zetMetricDestroyExp;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGet                                      = pDdiTable->pfnGet;
        pDdiTable->pfnGet                                    = validation_layer::zetMetricGroupGet;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zetMetricGroupGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCalculateMetricValues                    = pDdiTable->pfnCalculateMetricValues;
        pDdiTable->pfnCalculateMetricValues                  = validation_layer::zetMetricGroupCalculateMetricValues;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_2) {
        dditable.pfnCalculateMultipleMetricValuesExp         = pDdiTable->pfnCalculateMultipleMetricValuesExp;
        pDdiTable->pfnCalculateMultipleMetricValuesExp       = validation_layer::zetMetricGroupCalculateMultipleMetricValuesExp;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnGetGlobalTimestampsExp                   = pDdiTable->pfnGetGlobalTimestampsExp;
        pDdiTable->pfnGetGlobalTimestampsExp                 = validation_layer::zetMetricGroupGetGlobalTimestampsExp;
    }
    if (version >= ZE_API_VERSION_1_6) {
        dditable.pfnGetExportDataExp                         = pDdiTable->pfnGetExportDataExp;
        pDdiTable->pfnGetExportDataExp                       = validation_layer::zetMetricGroupGetExportDataExp;
    }
    if (version >= ZE_API_VERSION_1_6) {
        dditable.pfnCalculateMetricExportDataExp             = pDdiTable->pfnCalculateMetricExportDataExp;
        pDdiTable->pfnCalculateMetricExportDataExp           = validation_layer::zetMetricGroupCalculateMetricExportDataExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnCreateExp                                = pDdiTable->pfnCreateExp;
        pDdiTable->pfnCreateExp                              = validation_layer::zetMetricGroupCreateExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnAddMetricExp                             = pDdiTable->pfnAddMetricExp;
        pDdiTable->pfnAddMetricExp                           = validation_layer::zetMetricGroupAddMetricExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnRemoveMetricExp                          = pDdiTable->pfnRemoveMetricExp;
        pDdiTable->pfnRemoveMetricExp                        = validation_layer::zetMetricGroupRemoveMetricExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnCloseExp                                 = pDdiTable->pfnCloseExp;
        pDdiTable->pfnCloseExp                               = validation_layer::zetMetricGroupCloseExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnDestroyExp                               = pDdiTable->pfnDestroyExp;
        pDdiTable->pfnDestroyExp                             = validation_layer::zetMetricGroupDestroyExp;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCreate                                   = pDdiTable->pfnCreate;
        pDdiTable->pfnCreate                                 = validation_layer::zetMetricQueryCreate;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
        pDdiTable->pfnDestroy                                = validation_layer::zetMetricQueryDestroy;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnReset                                    = pDdiTable->pfnReset;
        pDdiTable->pfnReset                                  = validation_layer::zetMetricQueryReset;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetData                                  = pDdiTable->pfnGetData;
        pDdiTable->pfnGetData                                = validation_layer::zetMetricQueryGetData;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCreate                                   = pDdiTable->pfnCreate;
        pDdiTable->pfnCreate                                 = validation_layer::zetMetricQueryPoolCreate;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
        pDdiTable->pfnDestroy                                = validation_layer::zetMetricQueryPoolDestroy;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnOpen                                     = pDdiTable->pfnOpen;
        pDdiTable->pfnOpen                                   = validation_layer::zetMetricStreamerOpen;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnClose                                    = pDdiTable->pfnClose;
        pDdiTable->pfnClose                                  = validation_layer::zetMetricStreamerClose;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnReadData                                 = pDdiTable->pfnReadData;
        pDdiTable->pfnReadData                               = validation_layer::zetMetricStreamerReadData;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnCreate                                   = pDdiTable->pfnCreate;
        pDdiTable->pfnCreate                                 = validation_layer::zetTracerExpCreate;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
        pDdiTable->pfnDestroy                                = validation_layer::zetTracerExpDestroy;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetPrologues                             = pDdiTable->pfnSetPrologues;
        pDdiTable->pfnSetPrologues                           = validation_layer::zetTracerExpSetPrologues;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetEpilogues                             = pDdiTable->pfnSetEpilogues;
        pDdiTable->pfnSetEpilogues                           = validation_layer::zetTracerExpSetEpilogues;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetEnabled                               = pDdiTable->pfnSetEnabled;
        pDdiTable->pfnSetEnabled                             = validation_layer::zetTracerExpSetEnabled;
    }
    return result;
}

#if defined(__cplusplus)
};
#endif
