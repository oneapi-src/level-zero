/*
 * ***THIS FILE IS GENERATED. ***
 * See valddi.cpp.mako for modifications
 *
 * Copyright (C) 2019-2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_valddi.cpp
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
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesInit(
        ze_result_t result,
        zes_init_flags_t flags                          ///< [in] initialization flags.
                                                        ///< currently unused, must be 0 (default).
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesInit(";
        
        
        oss << "flags=";
        oss << loader::to_string(flags);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDriverGet(
        ze_result_t result,
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sysman driver instances.
                                                        ///< if count is zero, then the loader shall update the value with the
                                                        ///< total number of sysman drivers available.
                                                        ///< if count is greater than the number of sysman drivers available, then
                                                        ///< the loader shall update the value with the correct number of sysman
                                                        ///< drivers available.
        zes_driver_handle_t* phDrivers                  ///< [in,out][optional][range(0, *pCount)] array of sysman driver instance handles.
                                                        ///< if count is less than the number of sysman drivers available, then the
                                                        ///< loader shall only retrieve that number of sysman drivers.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDriverGet(";
        
        
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phDrivers=";
        oss << loader::to_string(phDrivers);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDriverGetExtensionProperties(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDriverGetExtensionProperties(";
        
        
        oss << "hDriver=";
        oss << loader::to_string(hDriver);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "pExtensionProperties=";
        oss << loader::to_string(pExtensionProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDriverGetExtensionFunctionAddress(
        ze_result_t result,
        zes_driver_handle_t hDriver,                    ///< [in] handle of the driver instance
        const char* name,                               ///< [in] extension function name
        void** ppFunctionAddress                        ///< [out] pointer to function pointer
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDriverGetExtensionFunctionAddress(";
        
        
        oss << "hDriver=";
        oss << loader::to_string(hDriver);
        
        oss << ", ";
        oss << "name=";
        oss << loader::to_string(name);
        
        oss << ", ";
        oss << "ppFunctionAddress=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && ppFunctionAddress != nullptr) {
            oss << loader::to_string(*ppFunctionAddress);
        } else {
            oss << loader::to_string(ppFunctionAddress);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceGet(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceGet(";
        
        
        oss << "hDriver=";
        oss << loader::to_string(hDriver);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phDevices=";
        oss << loader::to_string(phDevices);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceGetProperties(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_properties_t* pProperties            ///< [in,out] Structure that will contain information about the device.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceGetProperties(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceGetState(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_device_state_t* pState                      ///< [in,out] Structure that will contain information about the device.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceGetState(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pState=";
        oss << loader::to_string(pState);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceReset(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
        ze_bool_t force                                 ///< [in] If set to true, all applications that are currently using the
                                                        ///< device will be forcibly killed.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceReset(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "force=";
        oss << loader::to_string(force);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceResetExt(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle for the device
        zes_reset_properties_t* pProperties             ///< [in] Device reset properties to apply
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceResetExt(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceProcessesGetState(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceProcessesGetState(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "pProcesses=";
        oss << loader::to_string(pProcesses);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDevicePciGetProperties(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_properties_t* pProperties               ///< [in,out] Will contain the PCI properties.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDevicePciGetProperties(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDevicePciGetState(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_state_t* pState                         ///< [in,out] Will contain the PCI properties.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDevicePciGetState(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pState=";
        oss << loader::to_string(pState);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDevicePciGetBars(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDevicePciGetBars(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDevicePciGetStats(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pci_stats_t* pStats                         ///< [in,out] Will contain a snapshot of the latest stats.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDevicePciGetStats(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pStats=";
        oss << loader::to_string(pStats);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceSetOverclockWaiver(
        ze_result_t result,
        zes_device_handle_t hDevice                     ///< [in] Sysman handle of the device.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceSetOverclockWaiver(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceGetOverclockDomains(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t* pOverclockDomains                     ///< [in,out] Returns the overclock domains that are supported (a bit for
                                                        ///< each of enum ::zes_overclock_domain_t). If no bits are set, the device
                                                        ///< doesn't support overclocking.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceGetOverclockDomains(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pOverclockDomains=";
        oss << loader::to_string(pOverclockDomains);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceGetOverclockControls(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_overclock_domain_t domainType,              ///< [in] Domain type.
        uint32_t* pAvailableControls                    ///< [in,out] Returns the overclock controls that are supported for the
                                                        ///< specified overclock domain (a bit for each of enum
                                                        ///< ::zes_overclock_control_t).
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceGetOverclockControls(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "domainType=";
        oss << loader::to_string(domainType);
        
        oss << ", ";
        oss << "pAvailableControls=";
        oss << loader::to_string(pAvailableControls);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceResetOverclockSettings(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        ze_bool_t onShippedState                        ///< [in] True will reset to shipped state; false will reset to
                                                        ///< manufacturing state
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceResetOverclockSettings(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "onShippedState=";
        oss << loader::to_string(onShippedState);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceReadOverclockState(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_overclock_mode_t* pOverclockMode,           ///< [out] One of overclock mode.
        ze_bool_t* pWaiverSetting,                      ///< [out] Waiver setting: 0 = Waiver not set, 1 = waiver has been set.
        ze_bool_t* pOverclockState,                     ///< [out] Current settings 0 =manufacturing state, 1= shipped state)..
        zes_pending_action_t* pPendingAction,           ///< [out] This enum is returned when the driver attempts to set an
                                                        ///< overclock control or reset overclock settings.
        ze_bool_t* pPendingReset                        ///< [out] Pending reset 0 =manufacturing state, 1= shipped state)..
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceReadOverclockState(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pOverclockMode=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pOverclockMode != nullptr) {
            oss << loader::to_string(*pOverclockMode);
        } else {
            oss << loader::to_string(pOverclockMode);
        }
        
        oss << ", ";
        oss << "pWaiverSetting=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pWaiverSetting != nullptr) {
            oss << loader::to_string(*pWaiverSetting);
        } else {
            oss << loader::to_string(pWaiverSetting);
        }
        
        oss << ", ";
        oss << "pOverclockState=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pOverclockState != nullptr) {
            oss << loader::to_string(*pOverclockState);
        } else {
            oss << loader::to_string(pOverclockState);
        }
        
        oss << ", ";
        oss << "pPendingAction=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pPendingAction != nullptr) {
            oss << loader::to_string(*pPendingAction);
        } else {
            oss << loader::to_string(pPendingAction);
        }
        
        oss << ", ";
        oss << "pPendingReset=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pPendingReset != nullptr) {
            oss << loader::to_string(*pPendingReset);
        } else {
            oss << loader::to_string(pPendingReset);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumOverclockDomains(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumOverclockDomains(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phDomainHandle=";
        oss << loader::to_string(phDomainHandle);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesOverclockGetDomainProperties(
        ze_result_t result,
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_properties_t* pDomainProperties   ///< [in,out] The overclock properties for the specified domain.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesOverclockGetDomainProperties(";
        
        
        oss << "hDomainHandle=";
        oss << loader::to_string(hDomainHandle);
        
        oss << ", ";
        oss << "pDomainProperties=";
        oss << loader::to_string(pDomainProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesOverclockGetDomainVFProperties(
        ze_result_t result,
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_vf_property_t* pVFProperties                ///< [in,out] The VF min,max,step for a specified domain.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesOverclockGetDomainVFProperties(";
        
        
        oss << "hDomainHandle=";
        oss << loader::to_string(hDomainHandle);
        
        oss << ", ";
        oss << "pVFProperties=";
        oss << loader::to_string(pVFProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesOverclockGetDomainControlProperties(
        ze_result_t result,
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Handle for the component.
        zes_control_property_t* pControlProperties      ///< [in,out] overclock control values.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesOverclockGetDomainControlProperties(";
        
        
        oss << "hDomainHandle=";
        oss << loader::to_string(hDomainHandle);
        
        oss << ", ";
        oss << "DomainControl=";
        oss << loader::to_string(DomainControl);
        
        oss << ", ";
        oss << "pControlProperties=";
        oss << loader::to_string(pControlProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesOverclockGetControlCurrentValue(
        ze_result_t result,
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component.
        zes_overclock_control_t DomainControl,          ///< [in] Overclock Control.
        double* pValue                                  ///< [in,out] Getting overclock control value for the specified control.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesOverclockGetControlCurrentValue(";
        
        
        oss << "hDomainHandle=";
        oss << loader::to_string(hDomainHandle);
        
        oss << ", ";
        oss << "DomainControl=";
        oss << loader::to_string(DomainControl);
        
        oss << ", ";
        oss << "pValue=";
        oss << loader::to_string(pValue);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesOverclockGetControlPendingValue(
        ze_result_t result,
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Overclock Control.
        double* pValue                                  ///< [out] Returns the pending value for a given control. The units and
                                                        ///< format of the value depend on the control type.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesOverclockGetControlPendingValue(";
        
        
        oss << "hDomainHandle=";
        oss << loader::to_string(hDomainHandle);
        
        oss << ", ";
        oss << "DomainControl=";
        oss << loader::to_string(DomainControl);
        
        oss << ", ";
        oss << "pValue=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pValue != nullptr) {
            oss << loader::to_string(*pValue);
        } else {
            oss << loader::to_string(pValue);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesOverclockSetControlUserValue(
        ze_result_t result,
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Domain Control.
        double pValue,                                  ///< [in] The new value of the control. The units and format of the value
                                                        ///< depend on the control type.
        zes_pending_action_t* pPendingAction            ///< [out] Pending overclock setting.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesOverclockSetControlUserValue(";
        
        
        oss << "hDomainHandle=";
        oss << loader::to_string(hDomainHandle);
        
        oss << ", ";
        oss << "DomainControl=";
        oss << loader::to_string(DomainControl);
        
        oss << ", ";
        oss << "pValue=";
        oss << loader::to_string(pValue);
        
        oss << ", ";
        oss << "pPendingAction=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pPendingAction != nullptr) {
            oss << loader::to_string(*pPendingAction);
        } else {
            oss << loader::to_string(pPendingAction);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesOverclockGetControlState(
        ze_result_t result,
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_overclock_control_t DomainControl,          ///< [in] Domain Control.
        zes_control_state_t* pControlState,             ///< [out] Current overclock control state.
        zes_pending_action_t* pPendingAction            ///< [out] Pending overclock setting.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesOverclockGetControlState(";
        
        
        oss << "hDomainHandle=";
        oss << loader::to_string(hDomainHandle);
        
        oss << ", ";
        oss << "DomainControl=";
        oss << loader::to_string(DomainControl);
        
        oss << ", ";
        oss << "pControlState=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pControlState != nullptr) {
            oss << loader::to_string(*pControlState);
        } else {
            oss << loader::to_string(pControlState);
        }
        
        oss << ", ";
        oss << "pPendingAction=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pPendingAction != nullptr) {
            oss << loader::to_string(*pPendingAction);
        } else {
            oss << loader::to_string(pPendingAction);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesOverclockGetVFPointValues(
        ze_result_t result,
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_vf_type_t VFType,                           ///< [in] Voltage or Freqency point to read.
        zes_vf_array_type_t VFArrayType,                ///< [in] User,Default or Live VF array to read from
        uint32_t PointIndex,                            ///< [in] Point index - number between (0, max_num_points - 1).
        uint32_t* PointValue                            ///< [out] Returns the frequency in 1kHz units or voltage in millivolt
                                                        ///< units from the custom V-F curve at the specified zero-based index 
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesOverclockGetVFPointValues(";
        
        
        oss << "hDomainHandle=";
        oss << loader::to_string(hDomainHandle);
        
        oss << ", ";
        oss << "VFType=";
        oss << loader::to_string(VFType);
        
        oss << ", ";
        oss << "VFArrayType=";
        oss << loader::to_string(VFArrayType);
        
        oss << ", ";
        oss << "PointIndex=";
        oss << loader::to_string(PointIndex);
        
        oss << ", ";
        oss << "PointValue=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && PointValue != nullptr) {
            oss << loader::to_string(*PointValue);
        } else {
            oss << loader::to_string(PointValue);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesOverclockSetVFPointValues(
        ze_result_t result,
        zes_overclock_handle_t hDomainHandle,           ///< [in] Handle for the component domain.
        zes_vf_type_t VFType,                           ///< [in] Voltage or Freqency point to read.
        uint32_t PointIndex,                            ///< [in] Point index - number between (0, max_num_points - 1).
        uint32_t PointValue                             ///< [in] Writes frequency in 1kHz units or voltage in millivolt units to
                                                        ///< custom V-F curve at the specified zero-based index 
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesOverclockSetVFPointValues(";
        
        
        oss << "hDomainHandle=";
        oss << loader::to_string(hDomainHandle);
        
        oss << ", ";
        oss << "VFType=";
        oss << loader::to_string(VFType);
        
        oss << ", ";
        oss << "PointIndex=";
        oss << loader::to_string(PointIndex);
        
        oss << ", ";
        oss << "PointValue=";
        oss << loader::to_string(PointValue);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumDiagnosticTestSuites(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumDiagnosticTestSuites(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phDiagnostics=";
        oss << loader::to_string(phDiagnostics);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDiagnosticsGetProperties(
        ze_result_t result,
        zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
        zes_diag_properties_t* pProperties              ///< [in,out] Structure describing the properties of a diagnostics test
                                                        ///< suite
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDiagnosticsGetProperties(";
        
        
        oss << "hDiagnostics=";
        oss << loader::to_string(hDiagnostics);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDiagnosticsGetTests(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDiagnosticsGetTests(";
        
        
        oss << "hDiagnostics=";
        oss << loader::to_string(hDiagnostics);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "pTests=";
        oss << loader::to_string(pTests);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDiagnosticsRunTests(
        ze_result_t result,
        zes_diag_handle_t hDiagnostics,                 ///< [in] Handle for the component.
        uint32_t startIndex,                            ///< [in] The index of the first test to run. Set to
                                                        ///< ::ZES_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t endIndex,                              ///< [in] The index of the last test to run. Set to
                                                        ///< ::ZES_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        zes_diag_result_t* pResult                      ///< [in,out] The result of the diagnostics
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDiagnosticsRunTests(";
        
        
        oss << "hDiagnostics=";
        oss << loader::to_string(hDiagnostics);
        
        oss << ", ";
        oss << "startIndex=";
        oss << loader::to_string(startIndex);
        
        oss << ", ";
        oss << "endIndex=";
        oss << loader::to_string(endIndex);
        
        oss << ", ";
        oss << "pResult=";
        oss << loader::to_string(pResult);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEccAvailable(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        ze_bool_t* pAvailable                           ///< [out] ECC functionality is available (true)/unavailable (false).
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEccAvailable(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pAvailable=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pAvailable != nullptr) {
            oss << loader::to_string(*pAvailable);
        } else {
            oss << loader::to_string(pAvailable);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEccConfigurable(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        ze_bool_t* pConfigurable                        ///< [out] ECC can be enabled/disabled (true)/enabled/disabled (false).
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEccConfigurable(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pConfigurable=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pConfigurable != nullptr) {
            oss << loader::to_string(*pConfigurable);
        } else {
            oss << loader::to_string(pConfigurable);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceGetEccState(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        zes_device_ecc_properties_t* pState             ///< [out] ECC state, pending state, and pending action for state change.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceGetEccState(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pState=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pState != nullptr) {
            oss << loader::to_string(*pState);
        } else {
            oss << loader::to_string(pState);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceSetEccState(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Handle for the component.
        const zes_device_ecc_desc_t* newState,          ///< [in] Pointer to desired ECC state.
        zes_device_ecc_properties_t* pState             ///< [out] ECC state, pending state, and pending action for state change.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceSetEccState(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "newState=";
        oss << loader::to_string(newState);
        
        oss << ", ";
        oss << "pState=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pState != nullptr) {
            oss << loader::to_string(*pState);
        } else {
            oss << loader::to_string(pState);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumEngineGroups(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumEngineGroups(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phEngine=";
        oss << loader::to_string(phEngine);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesEngineGetProperties(
        ze_result_t result,
        zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
        zes_engine_properties_t* pProperties            ///< [in,out] The properties for the specified engine group.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesEngineGetProperties(";
        
        
        oss << "hEngine=";
        oss << loader::to_string(hEngine);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesEngineGetActivity(
        ze_result_t result,
        zes_engine_handle_t hEngine,                    ///< [in] Handle for the component.
        zes_engine_stats_t* pStats                      ///< [in,out] Will contain a snapshot of the engine group activity
                                                        ///< counters.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesEngineGetActivity(";
        
        
        oss << "hEngine=";
        oss << loader::to_string(hEngine);
        
        oss << ", ";
        oss << "pStats=";
        oss << loader::to_string(pStats);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEventRegister(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] The device handle.
        zes_event_type_flags_t events                   ///< [in] List of events to listen to.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEventRegister(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "events=";
        oss << loader::to_string(events);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDriverEventListen(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDriverEventListen(";
        
        
        oss << "hDriver=";
        oss << loader::to_string(hDriver);
        
        oss << ", ";
        oss << "timeout=";
        oss << loader::to_string(timeout);
        
        oss << ", ";
        oss << "count=";
        oss << loader::to_string(count);
        
        oss << ", ";
        oss << "phDevices=";
        oss << loader::to_string(phDevices);
        
        oss << ", ";
        oss << "pNumDeviceEvents=";
        oss << loader::to_string(pNumDeviceEvents);
        
        oss << ", ";
        oss << "pEvents=";
        oss << loader::to_string(pEvents);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDriverEventListenEx(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDriverEventListenEx(";
        
        
        oss << "hDriver=";
        oss << loader::to_string(hDriver);
        
        oss << ", ";
        oss << "timeout=";
        oss << loader::to_string(timeout);
        
        oss << ", ";
        oss << "count=";
        oss << loader::to_string(count);
        
        oss << ", ";
        oss << "phDevices=";
        oss << loader::to_string(phDevices);
        
        oss << ", ";
        oss << "pNumDeviceEvents=";
        oss << loader::to_string(pNumDeviceEvents);
        
        oss << ", ";
        oss << "pEvents=";
        oss << loader::to_string(pEvents);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumFabricPorts(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumFabricPorts(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phPort=";
        oss << loader::to_string(phPort);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFabricPortGetProperties(
        ze_result_t result,
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_properties_t* pProperties       ///< [in,out] Will contain properties of the Fabric Port.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFabricPortGetProperties(";
        
        
        oss << "hPort=";
        oss << loader::to_string(hPort);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFabricPortGetLinkType(
        ze_result_t result,
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_link_type_t* pLinkType               ///< [in,out] Will contain details about the link attached to the Fabric
                                                        ///< port.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFabricPortGetLinkType(";
        
        
        oss << "hPort=";
        oss << loader::to_string(hPort);
        
        oss << ", ";
        oss << "pLinkType=";
        oss << loader::to_string(pLinkType);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFabricPortGetConfig(
        ze_result_t result,
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_config_t* pConfig               ///< [in,out] Will contain configuration of the Fabric Port.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFabricPortGetConfig(";
        
        
        oss << "hPort=";
        oss << loader::to_string(hPort);
        
        oss << ", ";
        oss << "pConfig=";
        oss << loader::to_string(pConfig);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFabricPortSetConfig(
        ze_result_t result,
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        const zes_fabric_port_config_t* pConfig         ///< [in] Contains new configuration of the Fabric Port.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFabricPortSetConfig(";
        
        
        oss << "hPort=";
        oss << loader::to_string(hPort);
        
        oss << ", ";
        oss << "pConfig=";
        oss << loader::to_string(pConfig);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFabricPortGetState(
        ze_result_t result,
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_state_t* pState                 ///< [in,out] Will contain the current state of the Fabric Port
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFabricPortGetState(";
        
        
        oss << "hPort=";
        oss << loader::to_string(hPort);
        
        oss << ", ";
        oss << "pState=";
        oss << loader::to_string(pState);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFabricPortGetThroughput(
        ze_result_t result,
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_throughput_t* pThroughput       ///< [in,out] Will contain the Fabric port throughput counters.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFabricPortGetThroughput(";
        
        
        oss << "hPort=";
        oss << loader::to_string(hPort);
        
        oss << ", ";
        oss << "pThroughput=";
        oss << loader::to_string(pThroughput);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFabricPortGetFabricErrorCounters(
        ze_result_t result,
        zes_fabric_port_handle_t hPort,                 ///< [in] Handle for the component.
        zes_fabric_port_error_counters_t* pErrors       ///< [in,out] Will contain the Fabric port Error counters.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFabricPortGetFabricErrorCounters(";
        
        
        oss << "hPort=";
        oss << loader::to_string(hPort);
        
        oss << ", ";
        oss << "pErrors=";
        oss << loader::to_string(pErrors);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFabricPortGetMultiPortThroughput(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        uint32_t numPorts,                              ///< [in] Number of ports enumerated in function ::zesDeviceEnumFabricPorts
        zes_fabric_port_handle_t* phPort,               ///< [in][range(0, numPorts)] array of fabric port handles provided by user
                                                        ///< to gather throughput values. 
        zes_fabric_port_throughput_t** pThroughput      ///< [out][range(0, numPorts)] array of fabric port throughput counters
                                                        ///< from multiple ports of type ::zes_fabric_port_throughput_t.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFabricPortGetMultiPortThroughput(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "numPorts=";
        oss << loader::to_string(numPorts);
        
        oss << ", ";
        oss << "phPort=";
        oss << loader::to_string(phPort);
        
        oss << ", ";
        oss << "pThroughput=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pThroughput != nullptr) {
            oss << loader::to_string(*pThroughput);
        } else {
            oss << loader::to_string(pThroughput);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumFans(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumFans(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phFan=";
        oss << loader::to_string(phFan);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFanGetProperties(
        ze_result_t result,
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_properties_t* pProperties               ///< [in,out] Will contain the properties of the fan.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFanGetProperties(";
        
        
        oss << "hFan=";
        oss << loader::to_string(hFan);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFanGetConfig(
        ze_result_t result,
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_config_t* pConfig                       ///< [in,out] Will contain the current configuration of the fan.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFanGetConfig(";
        
        
        oss << "hFan=";
        oss << loader::to_string(hFan);
        
        oss << ", ";
        oss << "pConfig=";
        oss << loader::to_string(pConfig);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFanSetDefaultMode(
        ze_result_t result,
        zes_fan_handle_t hFan                           ///< [in] Handle for the component.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFanSetDefaultMode(";
        
        
        oss << "hFan=";
        oss << loader::to_string(hFan);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFanSetFixedSpeedMode(
        ze_result_t result,
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        const zes_fan_speed_t* speed                    ///< [in] The fixed fan speed setting
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFanSetFixedSpeedMode(";
        
        
        oss << "hFan=";
        oss << loader::to_string(hFan);
        
        oss << ", ";
        oss << "speed=";
        oss << loader::to_string(speed);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFanSetSpeedTableMode(
        ze_result_t result,
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        const zes_fan_speed_table_t* speedTable         ///< [in] A table containing temperature/speed pairs.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFanSetSpeedTableMode(";
        
        
        oss << "hFan=";
        oss << loader::to_string(hFan);
        
        oss << ", ";
        oss << "speedTable=";
        oss << loader::to_string(speedTable);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFanGetState(
        ze_result_t result,
        zes_fan_handle_t hFan,                          ///< [in] Handle for the component.
        zes_fan_speed_units_t units,                    ///< [in] The units in which the fan speed should be returned.
        int32_t* pSpeed                                 ///< [in,out] Will contain the current speed of the fan in the units
                                                        ///< requested. A value of -1 indicates that the fan speed cannot be
                                                        ///< measured.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFanGetState(";
        
        
        oss << "hFan=";
        oss << loader::to_string(hFan);
        
        oss << ", ";
        oss << "units=";
        oss << loader::to_string(units);
        
        oss << ", ";
        oss << "pSpeed=";
        oss << loader::to_string(pSpeed);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumFirmwares(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumFirmwares(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phFirmware=";
        oss << loader::to_string(phFirmware);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFirmwareGetProperties(
        ze_result_t result,
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        zes_firmware_properties_t* pProperties          ///< [in,out] Pointer to an array that will hold the properties of the
                                                        ///< firmware
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFirmwareGetProperties(";
        
        
        oss << "hFirmware=";
        oss << loader::to_string(hFirmware);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFirmwareFlash(
        ze_result_t result,
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFirmwareFlash(";
        
        
        oss << "hFirmware=";
        oss << loader::to_string(hFirmware);
        
        oss << ", ";
        oss << "pImage=";
        oss << loader::to_string(pImage);
        
        oss << ", ";
        oss << "size=";
        oss << loader::to_string(size);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFirmwareGetFlashProgress(
        ze_result_t result,
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        uint32_t* pCompletionPercent                    ///< [in,out] Pointer to the Completion Percentage of Firmware Update
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFirmwareGetFlashProgress(";
        
        
        oss << "hFirmware=";
        oss << loader::to_string(hFirmware);
        
        oss << ", ";
        oss << "pCompletionPercent=";
        oss << loader::to_string(pCompletionPercent);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFirmwareGetConsoleLogs(
        ze_result_t result,
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        size_t* pSize,                                  ///< [in,out] size of firmware log
        char* pFirmwareLog                              ///< [in,out][optional] pointer to null-terminated string of the log.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFirmwareGetConsoleLogs(";
        
        
        oss << "hFirmware=";
        oss << loader::to_string(hFirmware);
        
        oss << ", ";
        oss << "pSize=";
        oss << loader::to_string(pSize);
        
        oss << ", ";
        oss << "pFirmwareLog=";
        oss << loader::to_string(pFirmwareLog);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumFrequencyDomains(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumFrequencyDomains(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phFrequency=";
        oss << loader::to_string(phFrequency);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyGetProperties(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_properties_t* pProperties              ///< [in,out] The frequency properties for the specified domain.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyGetProperties(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyGetAvailableClocks(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyGetAvailableClocks(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phFrequency=";
        oss << loader::to_string(phFrequency);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyGetRange(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_range_t* pLimits                       ///< [in,out] The range between which the hardware can operate for the
                                                        ///< specified domain.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyGetRange(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "pLimits=";
        oss << loader::to_string(pLimits);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencySetRange(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        const zes_freq_range_t* pLimits                 ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencySetRange(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "pLimits=";
        oss << loader::to_string(pLimits);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyGetState(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_state_t* pState                        ///< [in,out] Frequency state for the specified domain.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyGetState(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "pState=";
        oss << loader::to_string(pState);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyGetThrottleTime(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_freq_throttle_time_t* pThrottleTime         ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyGetThrottleTime(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "pThrottleTime=";
        oss << loader::to_string(pThrottleTime);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyOcGetCapabilities(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_capabilities_t* pOcCapabilities          ///< [in,out] Pointer to the capabilities structure.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyOcGetCapabilities(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "pOcCapabilities=";
        oss << loader::to_string(pOcCapabilities);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyOcGetFrequencyTarget(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pCurrentOcFrequency                     ///< [out] Overclocking Frequency in MHz, if extended moded is supported,
                                                        ///< will returned in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                        ///< cannot be greater than the `maxOcFrequency` member of
                                                        ///< ::zes_oc_capabilities_t.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyOcGetFrequencyTarget(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "pCurrentOcFrequency=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pCurrentOcFrequency != nullptr) {
            oss << loader::to_string(*pCurrentOcFrequency);
        } else {
            oss << loader::to_string(pCurrentOcFrequency);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyOcSetFrequencyTarget(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double CurrentOcFrequency                       ///< [in] Overclocking Frequency in MHz, if extended moded is supported, it
                                                        ///< could be set in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                        ///< cannot be greater than the `maxOcFrequency` member of
                                                        ///< ::zes_oc_capabilities_t.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyOcSetFrequencyTarget(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "CurrentOcFrequency=";
        oss << loader::to_string(CurrentOcFrequency);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyOcGetVoltageTarget(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pCurrentVoltageTarget,                  ///< [out] Overclock voltage in Volts. This cannot be greater than the
                                                        ///< `maxOcVoltage` member of ::zes_oc_capabilities_t.
        double* pCurrentVoltageOffset                   ///< [out] This voltage offset is applied to all points on the
                                                        ///< voltage/frequency curve, including the new overclock voltageTarget.
                                                        ///< Valid range is between the `minOcVoltageOffset` and
                                                        ///< `maxOcVoltageOffset` members of ::zes_oc_capabilities_t.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyOcGetVoltageTarget(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "pCurrentVoltageTarget=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pCurrentVoltageTarget != nullptr) {
            oss << loader::to_string(*pCurrentVoltageTarget);
        } else {
            oss << loader::to_string(pCurrentVoltageTarget);
        }
        
        oss << ", ";
        oss << "pCurrentVoltageOffset=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pCurrentVoltageOffset != nullptr) {
            oss << loader::to_string(*pCurrentVoltageOffset);
        } else {
            oss << loader::to_string(pCurrentVoltageOffset);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyOcSetVoltageTarget(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double CurrentVoltageTarget,                    ///< [in] Overclock voltage in Volts. This cannot be greater than the
                                                        ///< `maxOcVoltage` member of ::zes_oc_capabilities_t.
        double CurrentVoltageOffset                     ///< [in] This voltage offset is applied to all points on the
                                                        ///< voltage/frequency curve, include the new overclock voltageTarget.
                                                        ///< Valid range is between the `minOcVoltageOffset` and
                                                        ///< `maxOcVoltageOffset` members of ::zes_oc_capabilities_t.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyOcSetVoltageTarget(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "CurrentVoltageTarget=";
        oss << loader::to_string(CurrentVoltageTarget);
        
        oss << ", ";
        oss << "CurrentVoltageOffset=";
        oss << loader::to_string(CurrentVoltageOffset);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyOcSetMode(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_mode_t CurrentOcMode                     ///< [in] Current Overclocking Mode ::zes_oc_mode_t.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyOcSetMode(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "CurrentOcMode=";
        oss << loader::to_string(CurrentOcMode);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyOcGetMode(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        zes_oc_mode_t* pCurrentOcMode                   ///< [out] Current Overclocking Mode ::zes_oc_mode_t.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyOcGetMode(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "pCurrentOcMode=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pCurrentOcMode != nullptr) {
            oss << loader::to_string(*pCurrentOcMode);
        } else {
            oss << loader::to_string(pCurrentOcMode);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyOcGetIccMax(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                        ///< successful return.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyOcGetIccMax(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "pOcIccMax=";
        oss << loader::to_string(pOcIccMax);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyOcSetIccMax(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyOcSetIccMax(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "ocIccMax=";
        oss << loader::to_string(ocIccMax);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyOcGetTjMax(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                        ///< on successful return.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyOcGetTjMax(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "pOcTjMax=";
        oss << loader::to_string(pOcTjMax);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFrequencyOcSetTjMax(
        ze_result_t result,
        zes_freq_handle_t hFrequency,                   ///< [in] Handle for the component.
        double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFrequencyOcSetTjMax(";
        
        
        oss << "hFrequency=";
        oss << loader::to_string(hFrequency);
        
        oss << ", ";
        oss << "ocTjMax=";
        oss << loader::to_string(ocTjMax);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumLeds(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumLeds(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phLed=";
        oss << loader::to_string(phLed);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesLedGetProperties(
        ze_result_t result,
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_properties_t* pProperties               ///< [in,out] Will contain the properties of the LED.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesLedGetProperties(";
        
        
        oss << "hLed=";
        oss << loader::to_string(hLed);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesLedGetState(
        ze_result_t result,
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        zes_led_state_t* pState                         ///< [in,out] Will contain the current state of the LED.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesLedGetState(";
        
        
        oss << "hLed=";
        oss << loader::to_string(hLed);
        
        oss << ", ";
        oss << "pState=";
        oss << loader::to_string(pState);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesLedSetState(
        ze_result_t result,
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        ze_bool_t enable                                ///< [in] Set to TRUE to turn the LED on, FALSE to turn off.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesLedSetState(";
        
        
        oss << "hLed=";
        oss << loader::to_string(hLed);
        
        oss << ", ";
        oss << "enable=";
        oss << loader::to_string(enable);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesLedSetColor(
        ze_result_t result,
        zes_led_handle_t hLed,                          ///< [in] Handle for the component.
        const zes_led_color_t* pColor                   ///< [in] New color of the LED.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesLedSetColor(";
        
        
        oss << "hLed=";
        oss << loader::to_string(hLed);
        
        oss << ", ";
        oss << "pColor=";
        oss << loader::to_string(pColor);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumMemoryModules(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumMemoryModules(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phMemory=";
        oss << loader::to_string(phMemory);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesMemoryGetProperties(
        ze_result_t result,
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_properties_t* pProperties               ///< [in,out] Will contain memory properties.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesMemoryGetProperties(";
        
        
        oss << "hMemory=";
        oss << loader::to_string(hMemory);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesMemoryGetState(
        ze_result_t result,
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_state_t* pState                         ///< [in,out] Will contain the current health and allocated memory.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesMemoryGetState(";
        
        
        oss << "hMemory=";
        oss << loader::to_string(hMemory);
        
        oss << ", ";
        oss << "pState=";
        oss << loader::to_string(pState);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesMemoryGetBandwidth(
        ze_result_t result,
        zes_mem_handle_t hMemory,                       ///< [in] Handle for the component.
        zes_mem_bandwidth_t* pBandwidth                 ///< [in,out] Will contain the total number of bytes read from and written
                                                        ///< to memory, as well as the current maximum bandwidth.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesMemoryGetBandwidth(";
        
        
        oss << "hMemory=";
        oss << loader::to_string(hMemory);
        
        oss << ", ";
        oss << "pBandwidth=";
        oss << loader::to_string(pBandwidth);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumPerformanceFactorDomains(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumPerformanceFactorDomains(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phPerf=";
        oss << loader::to_string(phPerf);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesPerformanceFactorGetProperties(
        ze_result_t result,
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        zes_perf_properties_t* pProperties              ///< [in,out] Will contain information about the specified Performance
                                                        ///< Factor domain.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesPerformanceFactorGetProperties(";
        
        
        oss << "hPerf=";
        oss << loader::to_string(hPerf);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesPerformanceFactorGetConfig(
        ze_result_t result,
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        double* pFactor                                 ///< [in,out] Will contain the actual Performance Factor being used by the
                                                        ///< hardware (may not be the same as the requested Performance Factor).
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesPerformanceFactorGetConfig(";
        
        
        oss << "hPerf=";
        oss << loader::to_string(hPerf);
        
        oss << ", ";
        oss << "pFactor=";
        oss << loader::to_string(pFactor);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesPerformanceFactorSetConfig(
        ze_result_t result,
        zes_perf_handle_t hPerf,                        ///< [in] Handle for the Performance Factor domain.
        double factor                                   ///< [in] The new Performance Factor.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesPerformanceFactorSetConfig(";
        
        
        oss << "hPerf=";
        oss << loader::to_string(hPerf);
        
        oss << ", ";
        oss << "factor=";
        oss << loader::to_string(factor);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumPowerDomains(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumPowerDomains(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phPower=";
        oss << loader::to_string(phPower);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceGetCardPowerDomain(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        zes_pwr_handle_t* phPower                       ///< [in,out] power domain handle for the entire PCIe card.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceGetCardPowerDomain(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "phPower=";
        oss << loader::to_string(phPower);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesPowerGetProperties(
        ze_result_t result,
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesPowerGetProperties(";
        
        
        oss << "hPower=";
        oss << loader::to_string(hPower);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesPowerGetEnergyCounter(
        ze_result_t result,
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_energy_counter_t* pEnergy             ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesPowerGetEnergyCounter(";
        
        
        oss << "hPower=";
        oss << loader::to_string(hPower);
        
        oss << ", ";
        oss << "pEnergy=";
        oss << loader::to_string(pEnergy);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesPowerGetLimits(
        ze_result_t result,
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_power_sustained_limit_t* pSustained,        ///< [in,out][optional] The sustained power limit. If this is null, the
                                                        ///< current sustained power limits will not be returned.
        zes_power_burst_limit_t* pBurst,                ///< [in,out][optional] The burst power limit. If this is null, the current
                                                        ///< peak power limits will not be returned.
        zes_power_peak_limit_t* pPeak                   ///< [in,out][optional] The peak power limit. If this is null, the peak
                                                        ///< power limits will not be returned.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesPowerGetLimits(";
        
        
        oss << "hPower=";
        oss << loader::to_string(hPower);
        
        oss << ", ";
        oss << "pSustained=";
        oss << loader::to_string(pSustained);
        
        oss << ", ";
        oss << "pBurst=";
        oss << loader::to_string(pBurst);
        
        oss << ", ";
        oss << "pPeak=";
        oss << loader::to_string(pPeak);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesPowerSetLimits(
        ze_result_t result,
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        const zes_power_sustained_limit_t* pSustained,  ///< [in][optional] The sustained power limit. If this is null, no changes
                                                        ///< will be made to the sustained power limits.
        const zes_power_burst_limit_t* pBurst,          ///< [in][optional] The burst power limit. If this is null, no changes will
                                                        ///< be made to the burst power limits.
        const zes_power_peak_limit_t* pPeak             ///< [in][optional] The peak power limit. If this is null, no changes will
                                                        ///< be made to the peak power limits.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesPowerSetLimits(";
        
        
        oss << "hPower=";
        oss << loader::to_string(hPower);
        
        oss << ", ";
        oss << "pSustained=";
        oss << loader::to_string(pSustained);
        
        oss << ", ";
        oss << "pBurst=";
        oss << loader::to_string(pBurst);
        
        oss << ", ";
        oss << "pPeak=";
        oss << loader::to_string(pPeak);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesPowerGetEnergyThreshold(
        ze_result_t result,
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        zes_energy_threshold_t* pThreshold              ///< [in,out] Returns information about the energy threshold setting -
                                                        ///< enabled/energy threshold/process ID.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesPowerGetEnergyThreshold(";
        
        
        oss << "hPower=";
        oss << loader::to_string(hPower);
        
        oss << ", ";
        oss << "pThreshold=";
        oss << loader::to_string(pThreshold);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesPowerSetEnergyThreshold(
        ze_result_t result,
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        double threshold                                ///< [in] The energy threshold to be set in joules.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesPowerSetEnergyThreshold(";
        
        
        oss << "hPower=";
        oss << loader::to_string(hPower);
        
        oss << ", ";
        oss << "threshold=";
        oss << loader::to_string(threshold);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumPsus(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumPsus(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phPsu=";
        oss << loader::to_string(phPsu);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesPsuGetProperties(
        ze_result_t result,
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_properties_t* pProperties               ///< [in,out] Will contain the properties of the power supply.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesPsuGetProperties(";
        
        
        oss << "hPsu=";
        oss << loader::to_string(hPsu);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesPsuGetState(
        ze_result_t result,
        zes_psu_handle_t hPsu,                          ///< [in] Handle for the component.
        zes_psu_state_t* pState                         ///< [in,out] Will contain the current state of the power supply.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesPsuGetState(";
        
        
        oss << "hPsu=";
        oss << loader::to_string(hPsu);
        
        oss << ", ";
        oss << "pState=";
        oss << loader::to_string(pState);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumRasErrorSets(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumRasErrorSets(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phRas=";
        oss << loader::to_string(phRas);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesRasGetProperties(
        ze_result_t result,
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_properties_t* pProperties               ///< [in,out] Structure describing RAS properties
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesRasGetProperties(";
        
        
        oss << "hRas=";
        oss << loader::to_string(hRas);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesRasGetConfig(
        ze_result_t result,
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_config_t* pConfig                       ///< [in,out] Will be populed with the current RAS configuration -
                                                        ///< thresholds used to trigger events
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesRasGetConfig(";
        
        
        oss << "hRas=";
        oss << loader::to_string(hRas);
        
        oss << ", ";
        oss << "pConfig=";
        oss << loader::to_string(pConfig);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesRasSetConfig(
        ze_result_t result,
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        const zes_ras_config_t* pConfig                 ///< [in] Change the RAS configuration - thresholds used to trigger events
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesRasSetConfig(";
        
        
        oss << "hRas=";
        oss << loader::to_string(hRas);
        
        oss << ", ";
        oss << "pConfig=";
        oss << loader::to_string(pConfig);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesRasGetState(
        ze_result_t result,
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        ze_bool_t clear,                                ///< [in] Set to 1 to clear the counters of this type
        zes_ras_state_t* pState                         ///< [in,out] Breakdown of where errors have occurred
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesRasGetState(";
        
        
        oss << "hRas=";
        oss << loader::to_string(hRas);
        
        oss << ", ";
        oss << "clear=";
        oss << loader::to_string(clear);
        
        oss << ", ";
        oss << "pState=";
        oss << loader::to_string(pState);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumSchedulers(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumSchedulers(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phScheduler=";
        oss << loader::to_string(phScheduler);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesSchedulerGetProperties(
        ze_result_t result,
        zes_sched_handle_t hScheduler,                  ///< [in] Handle for the component.
        zes_sched_properties_t* pProperties             ///< [in,out] Structure that will contain property data.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesSchedulerGetProperties(";
        
        
        oss << "hScheduler=";
        oss << loader::to_string(hScheduler);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesSchedulerGetCurrentMode(
        ze_result_t result,
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_mode_t* pMode                         ///< [in,out] Will contain the current scheduler mode.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesSchedulerGetCurrentMode(";
        
        
        oss << "hScheduler=";
        oss << loader::to_string(hScheduler);
        
        oss << ", ";
        oss << "pMode=";
        oss << loader::to_string(pMode);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesSchedulerGetTimeoutModeProperties(
        ze_result_t result,
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zes_sched_timeout_properties_t* pConfig         ///< [in,out] Will contain the current parameters for this mode.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesSchedulerGetTimeoutModeProperties(";
        
        
        oss << "hScheduler=";
        oss << loader::to_string(hScheduler);
        
        oss << ", ";
        oss << "getDefaults=";
        oss << loader::to_string(getDefaults);
        
        oss << ", ";
        oss << "pConfig=";
        oss << loader::to_string(pConfig);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesSchedulerGetTimesliceModeProperties(
        ze_result_t result,
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t getDefaults,                          ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        zes_sched_timeslice_properties_t* pConfig       ///< [in,out] Will contain the current parameters for this mode.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesSchedulerGetTimesliceModeProperties(";
        
        
        oss << "hScheduler=";
        oss << loader::to_string(hScheduler);
        
        oss << ", ";
        oss << "getDefaults=";
        oss << loader::to_string(getDefaults);
        
        oss << ", ";
        oss << "pConfig=";
        oss << loader::to_string(pConfig);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesSchedulerSetTimeoutMode(
        ze_result_t result,
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_timeout_properties_t* pProperties,    ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesSchedulerSetTimeoutMode(";
        
        
        oss << "hScheduler=";
        oss << loader::to_string(hScheduler);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        
        oss << ", ";
        oss << "pNeedReload=";
        oss << loader::to_string(pNeedReload);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesSchedulerSetTimesliceMode(
        ze_result_t result,
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        zes_sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesSchedulerSetTimesliceMode(";
        
        
        oss << "hScheduler=";
        oss << loader::to_string(hScheduler);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        
        oss << ", ";
        oss << "pNeedReload=";
        oss << loader::to_string(pNeedReload);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesSchedulerSetExclusiveMode(
        ze_result_t result,
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesSchedulerSetExclusiveMode(";
        
        
        oss << "hScheduler=";
        oss << loader::to_string(hScheduler);
        
        oss << ", ";
        oss << "pNeedReload=";
        oss << loader::to_string(pNeedReload);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesSchedulerSetComputeUnitDebugMode(
        ze_result_t result,
        zes_sched_handle_t hScheduler,                  ///< [in] Sysman handle for the component.
        ze_bool_t* pNeedReload                          ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesSchedulerSetComputeUnitDebugMode(";
        
        
        oss << "hScheduler=";
        oss << loader::to_string(hScheduler);
        
        oss << ", ";
        oss << "pNeedReload=";
        oss << loader::to_string(pNeedReload);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumStandbyDomains(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumStandbyDomains(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phStandby=";
        oss << loader::to_string(phStandby);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesStandbyGetProperties(
        ze_result_t result,
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_properties_t* pProperties           ///< [in,out] Will contain the standby hardware properties.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesStandbyGetProperties(";
        
        
        oss << "hStandby=";
        oss << loader::to_string(hStandby);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesStandbyGetMode(
        ze_result_t result,
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t* pMode                 ///< [in,out] Will contain the current standby mode.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesStandbyGetMode(";
        
        
        oss << "hStandby=";
        oss << loader::to_string(hStandby);
        
        oss << ", ";
        oss << "pMode=";
        oss << loader::to_string(pMode);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesStandbySetMode(
        ze_result_t result,
        zes_standby_handle_t hStandby,                  ///< [in] Handle for the component.
        zes_standby_promo_mode_t mode                   ///< [in] New standby mode.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesStandbySetMode(";
        
        
        oss << "hStandby=";
        oss << loader::to_string(hStandby);
        
        oss << ", ";
        oss << "mode=";
        oss << loader::to_string(mode);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumTemperatureSensors(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumTemperatureSensors(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phTemperature=";
        oss << loader::to_string(phTemperature);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesTemperatureGetProperties(
        ze_result_t result,
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_properties_t* pProperties              ///< [in,out] Will contain the temperature sensor properties.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesTemperatureGetProperties(";
        
        
        oss << "hTemperature=";
        oss << loader::to_string(hTemperature);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesTemperatureGetConfig(
        ze_result_t result,
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        zes_temp_config_t* pConfig                      ///< [in,out] Returns current configuration.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesTemperatureGetConfig(";
        
        
        oss << "hTemperature=";
        oss << loader::to_string(hTemperature);
        
        oss << ", ";
        oss << "pConfig=";
        oss << loader::to_string(pConfig);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesTemperatureSetConfig(
        ze_result_t result,
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        const zes_temp_config_t* pConfig                ///< [in] New configuration.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesTemperatureSetConfig(";
        
        
        oss << "hTemperature=";
        oss << loader::to_string(hTemperature);
        
        oss << ", ";
        oss << "pConfig=";
        oss << loader::to_string(pConfig);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesTemperatureGetState(
        ze_result_t result,
        zes_temp_handle_t hTemperature,                 ///< [in] Handle for the component.
        double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                        ///< in degrees Celsius.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesTemperatureGetState(";
        
        
        oss << "hTemperature=";
        oss << loader::to_string(hTemperature);
        
        oss << ", ";
        oss << "pTemperature=";
        oss << loader::to_string(pTemperature);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDevicePciLinkSpeedUpdateExt(
        ze_result_t result,
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        ze_bool_t shouldDowngrade,                      ///< [in] boolean value to decide whether to perform PCIe downgrade(true)
                                                        ///< or set to default speed(false)
        zes_device_action_t* pendingAction              ///< [out] Pending action
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDevicePciLinkSpeedUpdateExt(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "shouldDowngrade=";
        oss << loader::to_string(shouldDowngrade);
        
        oss << ", ";
        oss << "pendingAction=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && pendingAction != nullptr) {
            oss << loader::to_string(*pendingAction);
        } else {
            oss << loader::to_string(pendingAction);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesPowerGetLimitsExt(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesPowerGetLimitsExt(";
        
        
        oss << "hPower=";
        oss << loader::to_string(hPower);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "pSustained=";
        oss << loader::to_string(pSustained);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesPowerSetLimitsExt(
        ze_result_t result,
        zes_pwr_handle_t hPower,                        ///< [in] Handle for the component.
        uint32_t* pCount,                               ///< [in] Pointer to the number of power limit descriptors.
        zes_power_limit_ext_desc_t* pSustained          ///< [in][optional][range(0, *pCount)] Array of power limit descriptors.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesPowerSetLimitsExt(";
        
        
        oss << "hPower=";
        oss << loader::to_string(hPower);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "pSustained=";
        oss << loader::to_string(pSustained);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesEngineGetActivityExt(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesEngineGetActivityExt(";
        
        
        oss << "hEngine=";
        oss << loader::to_string(hEngine);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "pStats=";
        oss << loader::to_string(pStats);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesRasGetStateExp(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesRasGetStateExp(";
        
        
        oss << "hRas=";
        oss << loader::to_string(hRas);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "pState=";
        oss << loader::to_string(pState);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesRasClearStateExp(
        ze_result_t result,
        zes_ras_handle_t hRas,                          ///< [in] Handle for the component.
        zes_ras_error_category_exp_t category           ///< [in] category for which error counter is to be cleared.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesRasClearStateExp(";
        
        
        oss << "hRas=";
        oss << loader::to_string(hRas);
        
        oss << ", ";
        oss << "category=";
        oss << loader::to_string(category);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFirmwareGetSecurityVersionExp(
        ze_result_t result,
        zes_firmware_handle_t hFirmware,                ///< [in] Handle for the component.
        char* pVersion                                  ///< [in,out] NULL terminated string value. The string "unknown" will be
                                                        ///< returned if this property cannot be determined.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFirmwareGetSecurityVersionExp(";
        
        
        oss << "hFirmware=";
        oss << loader::to_string(hFirmware);
        
        oss << ", ";
        oss << "pVersion=";
        oss << loader::to_string(pVersion);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesFirmwareSetSecurityVersionExp(
        ze_result_t result,
        zes_firmware_handle_t hFirmware                 ///< [in] Handle for the component.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesFirmwareSetSecurityVersionExp(";
        
        
        oss << "hFirmware=";
        oss << loader::to_string(hFirmware);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceGetSubDevicePropertiesExp(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceGetSubDevicePropertiesExp(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "pSubdeviceProps=";
        oss << loader::to_string(pSubdeviceProps);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDriverGetDeviceByUuidExp(
        ze_result_t result,
        zes_driver_handle_t hDriver,                    ///< [in] handle of the sysman driver instance
        zes_uuid_t uuid,                                ///< [in] universal unique identifier.
        zes_device_handle_t* phDevice,                  ///< [out] Sysman handle of the device.
        ze_bool_t* onSubdevice,                         ///< [out] True if the UUID belongs to the sub-device; false means that
                                                        ///< UUID belongs to the root device.
        uint32_t* subdeviceId                           ///< [out] If onSubdevice is true, this gives the ID of the sub-device
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDriverGetDeviceByUuidExp(";
        
        
        oss << "hDriver=";
        oss << loader::to_string(hDriver);
        
        oss << ", ";
        oss << "uuid=";
        oss << loader::to_string(uuid);
        
        oss << ", ";
        oss << "phDevice=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && phDevice != nullptr) {
            oss << loader::to_string(*phDevice);
        } else {
            oss << loader::to_string(phDevice);
        }
        
        oss << ", ";
        oss << "onSubdevice=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && onSubdevice != nullptr) {
            oss << loader::to_string(*onSubdevice);
        } else {
            oss << loader::to_string(onSubdevice);
        }
        
        oss << ", ";
        oss << "subdeviceId=";
        // Dereference output parameter if not null and result is success
        if (result == ZE_RESULT_SUCCESS && subdeviceId != nullptr) {
            oss << loader::to_string(*subdeviceId);
        } else {
            oss << loader::to_string(subdeviceId);
        }
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumActiveVFExp(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumActiveVFExp(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phVFhandle=";
        oss << loader::to_string(phVFhandle);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesVFManagementGetVFPropertiesExp(
        ze_result_t result,
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
        zes_vf_exp_properties_t* pProperties            ///< [in,out] Will contain VF properties.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesVFManagementGetVFPropertiesExp(";
        
        
        oss << "hVFhandle=";
        oss << loader::to_string(hVFhandle);
        
        oss << ", ";
        oss << "pProperties=";
        oss << loader::to_string(pProperties);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesVFManagementGetVFMemoryUtilizationExp(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesVFManagementGetVFMemoryUtilizationExp(";
        
        
        oss << "hVFhandle=";
        oss << loader::to_string(hVFhandle);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "pMemUtil=";
        oss << loader::to_string(pMemUtil);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesVFManagementGetVFEngineUtilizationExp(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesVFManagementGetVFEngineUtilizationExp(";
        
        
        oss << "hVFhandle=";
        oss << loader::to_string(hVFhandle);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "pEngineUtil=";
        oss << loader::to_string(pEngineUtil);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesVFManagementSetVFTelemetryModeExp(
        ze_result_t result,
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
        zes_vf_info_util_exp_flags_t flags,             ///< [in] utilization flags to enable or disable. May be 0 or a valid
                                                        ///< combination of ::zes_vf_info_util_exp_flag_t.
        ze_bool_t enable                                ///< [in] Enable utilization telemetry.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesVFManagementSetVFTelemetryModeExp(";
        
        
        oss << "hVFhandle=";
        oss << loader::to_string(hVFhandle);
        
        oss << ", ";
        oss << "flags=";
        oss << loader::to_string(flags);
        
        oss << ", ";
        oss << "enable=";
        oss << loader::to_string(enable);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesVFManagementSetVFTelemetrySamplingIntervalExp(
        ze_result_t result,
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the component.
        zes_vf_info_util_exp_flags_t flag,              ///< [in] utilization flags to set sampling interval. May be 0 or a valid
                                                        ///< combination of ::zes_vf_info_util_exp_flag_t.
        uint64_t samplingInterval                       ///< [in] Sampling interval value.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesVFManagementSetVFTelemetrySamplingIntervalExp(";
        
        
        oss << "hVFhandle=";
        oss << loader::to_string(hVFhandle);
        
        oss << ", ";
        oss << "flag=";
        oss << loader::to_string(flag);
        
        oss << ", ";
        oss << "samplingInterval=";
        oss << loader::to_string(samplingInterval);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesDeviceEnumEnabledVFExp(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesDeviceEnumEnabledVFExp(";
        
        
        oss << "hDevice=";
        oss << loader::to_string(hDevice);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "phVFhandle=";
        oss << loader::to_string(phVFhandle);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesVFManagementGetVFCapabilitiesExp(
        ze_result_t result,
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
        zes_vf_exp_capabilities_t* pCapability          ///< [in,out] Will contain VF capability.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesVFManagementGetVFCapabilitiesExp(";
        
        
        oss << "hVFhandle=";
        oss << loader::to_string(hVFhandle);
        
        oss << ", ";
        oss << "pCapability=";
        oss << loader::to_string(pCapability);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesVFManagementGetVFMemoryUtilizationExp2(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesVFManagementGetVFMemoryUtilizationExp2(";
        
        
        oss << "hVFhandle=";
        oss << loader::to_string(hVFhandle);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "pMemUtil=";
        oss << loader::to_string(pMemUtil);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesVFManagementGetVFEngineUtilizationExp2(
        ze_result_t result,
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
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesVFManagementGetVFEngineUtilizationExp2(";
        
        
        oss << "hVFhandle=";
        oss << loader::to_string(hVFhandle);
        
        oss << ", ";
        oss << "pCount=";
        oss << loader::to_string(pCount);
        
        oss << ", ";
        oss << "pEngineUtil=";
        oss << loader::to_string(pEngineUtil);
        oss << ")";
        context.logger->log_trace(oss.str());
        return result;
    }
        VALIDATION_MAYBE_UNUSED static ze_result_t logAndPropagateResult_zesVFManagementGetVFCapabilitiesExp2(
        ze_result_t result,
        zes_vf_handle_t hVFhandle,                      ///< [in] Sysman handle for the VF component.
        zes_vf_exp2_capabilities_t* pCapability         ///< [in,out] Will contain VF capability.
) {
        std::string status = (result == ZE_RESULT_SUCCESS) ? "SUCCESS" : "ERROR";
        std::ostringstream oss;
        oss << status << " (" << loader::to_string(result) << ") in zesVFManagementGetVFCapabilitiesExp2(";
        
        
        oss << "hVFhandle=";
        oss << loader::to_string(hVFhandle);
        
        oss << ", ";
        oss << "pCapability=";
        oss << loader::to_string(pCapability);
        oss << ")";
        context.logger->log_trace(oss.str());
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
            return logAndPropagateResult_zesInit(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, flags);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesInitPrologue( flags );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesInit(result, flags);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesInitPrologue( flags );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesInit(result, flags);
        }

        auto driver_result = pfnInit( flags );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesInitEpilogue( flags ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesInit(result, flags);
        }

        return logAndPropagateResult_zesInit(driver_result, flags);
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
            return logAndPropagateResult_zesDriverGet(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, pCount, phDrivers);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetPrologue( pCount, phDrivers );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverGet(result, pCount, phDrivers);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverGetPrologue( pCount, phDrivers );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverGet(result, pCount, phDrivers);
        }

        auto driver_result = pfnGet( pCount, phDrivers );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetEpilogue( pCount, phDrivers ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverGet(result, pCount, phDrivers);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phDrivers) && (i < *pCount); ++i){
                if (phDrivers[i]){
                    context.handleLifetime->addHandle( phDrivers[i] );
                    context.handleLifetime->addDependent( pCount, phDrivers[i] );
                }
            }
        }
        return logAndPropagateResult_zesDriverGet(driver_result, pCount, phDrivers);
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
            return logAndPropagateResult_zesDriverGetExtensionProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDriver, pCount, pExtensionProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetExtensionPropertiesPrologue( hDriver, pCount, pExtensionProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverGetExtensionProperties(result, hDriver, pCount, pExtensionProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverGetExtensionPropertiesPrologue( hDriver, pCount, pExtensionProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverGetExtensionProperties(result, hDriver, pCount, pExtensionProperties);
        }

        auto driver_result = pfnGetExtensionProperties( hDriver, pCount, pExtensionProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetExtensionPropertiesEpilogue( hDriver, pCount, pExtensionProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverGetExtensionProperties(result, hDriver, pCount, pExtensionProperties);
        }

        return logAndPropagateResult_zesDriverGetExtensionProperties(driver_result, hDriver, pCount, pExtensionProperties);
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
            return logAndPropagateResult_zesDriverGetExtensionFunctionAddress(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDriver, name, ppFunctionAddress);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetExtensionFunctionAddressPrologue( hDriver, name, ppFunctionAddress );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverGetExtensionFunctionAddress(result, hDriver, name, ppFunctionAddress);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverGetExtensionFunctionAddressPrologue( hDriver, name, ppFunctionAddress );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverGetExtensionFunctionAddress(result, hDriver, name, ppFunctionAddress);
        }

        auto driver_result = pfnGetExtensionFunctionAddress( hDriver, name, ppFunctionAddress );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetExtensionFunctionAddressEpilogue( hDriver, name, ppFunctionAddress ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverGetExtensionFunctionAddress(result, hDriver, name, ppFunctionAddress);
        }

        return logAndPropagateResult_zesDriverGetExtensionFunctionAddress(driver_result, hDriver, name, ppFunctionAddress);
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
            return logAndPropagateResult_zesDeviceGet(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDriver, pCount, phDevices);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetPrologue( hDriver, pCount, phDevices );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGet(result, hDriver, pCount, phDevices);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetPrologue( hDriver, pCount, phDevices );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGet(result, hDriver, pCount, phDevices);
        }

        auto driver_result = pfnGet( hDriver, pCount, phDevices );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetEpilogue( hDriver, pCount, phDevices ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGet(result, hDriver, pCount, phDevices);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            for (size_t i = 0; ( nullptr != phDevices) && (i < *pCount); ++i){
                if (phDevices[i]){
                    context.handleLifetime->addHandle( phDevices[i] );
                    context.handleLifetime->addDependent( hDriver, phDevices[i] );
                }
            }
        }
        return logAndPropagateResult_zesDeviceGet(driver_result, hDriver, pCount, phDevices);
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
            return logAndPropagateResult_zesDeviceGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetPropertiesPrologue( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetProperties(result, hDevice, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetPropertiesPrologue( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetProperties(result, hDevice, pProperties);
        }

        auto driver_result = pfnGetProperties( hDevice, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetPropertiesEpilogue( hDevice, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetProperties(result, hDevice, pProperties);
        }

        return logAndPropagateResult_zesDeviceGetProperties(driver_result, hDevice, pProperties);
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
            return logAndPropagateResult_zesDeviceGetState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pState);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetStatePrologue( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetState(result, hDevice, pState);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetStatePrologue( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetState(result, hDevice, pState);
        }

        auto driver_result = pfnGetState( hDevice, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetStateEpilogue( hDevice, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetState(result, hDevice, pState);
        }

        return logAndPropagateResult_zesDeviceGetState(driver_result, hDevice, pState);
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
            return logAndPropagateResult_zesDeviceReset(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, force);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceResetPrologue( hDevice, force );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceReset(result, hDevice, force);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceResetPrologue( hDevice, force );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceReset(result, hDevice, force);
        }

        auto driver_result = pfnReset( hDevice, force );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceResetEpilogue( hDevice, force ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceReset(result, hDevice, force);
        }

        return logAndPropagateResult_zesDeviceReset(driver_result, hDevice, force);
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
            return logAndPropagateResult_zesDeviceResetExt(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceResetExtPrologue( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceResetExt(result, hDevice, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceResetExtPrologue( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceResetExt(result, hDevice, pProperties);
        }

        auto driver_result = pfnResetExt( hDevice, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceResetExtEpilogue( hDevice, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceResetExt(result, hDevice, pProperties);
        }

        return logAndPropagateResult_zesDeviceResetExt(driver_result, hDevice, pProperties);
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
            return logAndPropagateResult_zesDeviceProcessesGetState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, pProcesses);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceProcessesGetStatePrologue( hDevice, pCount, pProcesses );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceProcessesGetState(result, hDevice, pCount, pProcesses);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceProcessesGetStatePrologue( hDevice, pCount, pProcesses );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceProcessesGetState(result, hDevice, pCount, pProcesses);
        }

        auto driver_result = pfnProcessesGetState( hDevice, pCount, pProcesses );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceProcessesGetStateEpilogue( hDevice, pCount, pProcesses ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceProcessesGetState(result, hDevice, pCount, pProcesses);
        }

        return logAndPropagateResult_zesDeviceProcessesGetState(driver_result, hDevice, pCount, pProcesses);
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
            return logAndPropagateResult_zesDevicePciGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetPropertiesPrologue( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDevicePciGetProperties(result, hDevice, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDevicePciGetPropertiesPrologue( hDevice, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDevicePciGetProperties(result, hDevice, pProperties);
        }

        auto driver_result = pfnPciGetProperties( hDevice, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetPropertiesEpilogue( hDevice, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDevicePciGetProperties(result, hDevice, pProperties);
        }

        return logAndPropagateResult_zesDevicePciGetProperties(driver_result, hDevice, pProperties);
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
            return logAndPropagateResult_zesDevicePciGetState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pState);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetStatePrologue( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDevicePciGetState(result, hDevice, pState);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDevicePciGetStatePrologue( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDevicePciGetState(result, hDevice, pState);
        }

        auto driver_result = pfnPciGetState( hDevice, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetStateEpilogue( hDevice, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDevicePciGetState(result, hDevice, pState);
        }

        return logAndPropagateResult_zesDevicePciGetState(driver_result, hDevice, pState);
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
            return logAndPropagateResult_zesDevicePciGetBars(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetBarsPrologue( hDevice, pCount, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDevicePciGetBars(result, hDevice, pCount, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDevicePciGetBarsPrologue( hDevice, pCount, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDevicePciGetBars(result, hDevice, pCount, pProperties);
        }

        auto driver_result = pfnPciGetBars( hDevice, pCount, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetBarsEpilogue( hDevice, pCount, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDevicePciGetBars(result, hDevice, pCount, pProperties);
        }

        return logAndPropagateResult_zesDevicePciGetBars(driver_result, hDevice, pCount, pProperties);
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
            return logAndPropagateResult_zesDevicePciGetStats(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pStats);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetStatsPrologue( hDevice, pStats );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDevicePciGetStats(result, hDevice, pStats);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDevicePciGetStatsPrologue( hDevice, pStats );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDevicePciGetStats(result, hDevice, pStats);
        }

        auto driver_result = pfnPciGetStats( hDevice, pStats );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciGetStatsEpilogue( hDevice, pStats ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDevicePciGetStats(result, hDevice, pStats);
        }

        return logAndPropagateResult_zesDevicePciGetStats(driver_result, hDevice, pStats);
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
            return logAndPropagateResult_zesDeviceSetOverclockWaiver(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceSetOverclockWaiverPrologue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceSetOverclockWaiver(result, hDevice);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceSetOverclockWaiverPrologue( hDevice );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceSetOverclockWaiver(result, hDevice);
        }

        auto driver_result = pfnSetOverclockWaiver( hDevice );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceSetOverclockWaiverEpilogue( hDevice ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceSetOverclockWaiver(result, hDevice);
        }

        return logAndPropagateResult_zesDeviceSetOverclockWaiver(driver_result, hDevice);
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
            return logAndPropagateResult_zesDeviceGetOverclockDomains(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pOverclockDomains);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetOverclockDomainsPrologue( hDevice, pOverclockDomains );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetOverclockDomains(result, hDevice, pOverclockDomains);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetOverclockDomainsPrologue( hDevice, pOverclockDomains );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetOverclockDomains(result, hDevice, pOverclockDomains);
        }

        auto driver_result = pfnGetOverclockDomains( hDevice, pOverclockDomains );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetOverclockDomainsEpilogue( hDevice, pOverclockDomains ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetOverclockDomains(result, hDevice, pOverclockDomains);
        }

        return logAndPropagateResult_zesDeviceGetOverclockDomains(driver_result, hDevice, pOverclockDomains);
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
            return logAndPropagateResult_zesDeviceGetOverclockControls(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, domainType, pAvailableControls);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetOverclockControlsPrologue( hDevice, domainType, pAvailableControls );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetOverclockControls(result, hDevice, domainType, pAvailableControls);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetOverclockControlsPrologue( hDevice, domainType, pAvailableControls );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetOverclockControls(result, hDevice, domainType, pAvailableControls);
        }

        auto driver_result = pfnGetOverclockControls( hDevice, domainType, pAvailableControls );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetOverclockControlsEpilogue( hDevice, domainType, pAvailableControls ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetOverclockControls(result, hDevice, domainType, pAvailableControls);
        }

        return logAndPropagateResult_zesDeviceGetOverclockControls(driver_result, hDevice, domainType, pAvailableControls);
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
            return logAndPropagateResult_zesDeviceResetOverclockSettings(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, onShippedState);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceResetOverclockSettingsPrologue( hDevice, onShippedState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceResetOverclockSettings(result, hDevice, onShippedState);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceResetOverclockSettingsPrologue( hDevice, onShippedState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceResetOverclockSettings(result, hDevice, onShippedState);
        }

        auto driver_result = pfnResetOverclockSettings( hDevice, onShippedState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceResetOverclockSettingsEpilogue( hDevice, onShippedState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceResetOverclockSettings(result, hDevice, onShippedState);
        }

        return logAndPropagateResult_zesDeviceResetOverclockSettings(driver_result, hDevice, onShippedState);
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
            return logAndPropagateResult_zesDeviceReadOverclockState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceReadOverclockStatePrologue( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceReadOverclockState(result, hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceReadOverclockStatePrologue( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceReadOverclockState(result, hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset);
        }

        auto driver_result = pfnReadOverclockState( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceReadOverclockStateEpilogue( hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceReadOverclockState(result, hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset);
        }

        return logAndPropagateResult_zesDeviceReadOverclockState(driver_result, hDevice, pOverclockMode, pWaiverSetting, pOverclockState, pPendingAction, pPendingReset);
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
            return logAndPropagateResult_zesDeviceEnumOverclockDomains(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phDomainHandle);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumOverclockDomainsPrologue( hDevice, pCount, phDomainHandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumOverclockDomains(result, hDevice, pCount, phDomainHandle);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumOverclockDomainsPrologue( hDevice, pCount, phDomainHandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumOverclockDomains(result, hDevice, pCount, phDomainHandle);
        }

        auto driver_result = pfnEnumOverclockDomains( hDevice, pCount, phDomainHandle );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumOverclockDomainsEpilogue( hDevice, pCount, phDomainHandle ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumOverclockDomains(result, hDevice, pCount, phDomainHandle);
        }

        return logAndPropagateResult_zesDeviceEnumOverclockDomains(driver_result, hDevice, pCount, phDomainHandle);
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
            return logAndPropagateResult_zesOverclockGetDomainProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDomainHandle, pDomainProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetDomainPropertiesPrologue( hDomainHandle, pDomainProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetDomainProperties(result, hDomainHandle, pDomainProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetDomainPropertiesPrologue( hDomainHandle, pDomainProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetDomainProperties(result, hDomainHandle, pDomainProperties);
        }

        auto driver_result = pfnGetDomainProperties( hDomainHandle, pDomainProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetDomainPropertiesEpilogue( hDomainHandle, pDomainProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetDomainProperties(result, hDomainHandle, pDomainProperties);
        }

        return logAndPropagateResult_zesOverclockGetDomainProperties(driver_result, hDomainHandle, pDomainProperties);
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
            return logAndPropagateResult_zesOverclockGetDomainVFProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDomainHandle, pVFProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetDomainVFPropertiesPrologue( hDomainHandle, pVFProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetDomainVFProperties(result, hDomainHandle, pVFProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetDomainVFPropertiesPrologue( hDomainHandle, pVFProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetDomainVFProperties(result, hDomainHandle, pVFProperties);
        }

        auto driver_result = pfnGetDomainVFProperties( hDomainHandle, pVFProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetDomainVFPropertiesEpilogue( hDomainHandle, pVFProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetDomainVFProperties(result, hDomainHandle, pVFProperties);
        }

        return logAndPropagateResult_zesOverclockGetDomainVFProperties(driver_result, hDomainHandle, pVFProperties);
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
            return logAndPropagateResult_zesOverclockGetDomainControlProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDomainHandle, DomainControl, pControlProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetDomainControlPropertiesPrologue( hDomainHandle, DomainControl, pControlProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetDomainControlProperties(result, hDomainHandle, DomainControl, pControlProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetDomainControlPropertiesPrologue( hDomainHandle, DomainControl, pControlProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetDomainControlProperties(result, hDomainHandle, DomainControl, pControlProperties);
        }

        auto driver_result = pfnGetDomainControlProperties( hDomainHandle, DomainControl, pControlProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetDomainControlPropertiesEpilogue( hDomainHandle, DomainControl, pControlProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetDomainControlProperties(result, hDomainHandle, DomainControl, pControlProperties);
        }

        return logAndPropagateResult_zesOverclockGetDomainControlProperties(driver_result, hDomainHandle, DomainControl, pControlProperties);
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
            return logAndPropagateResult_zesOverclockGetControlCurrentValue(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDomainHandle, DomainControl, pValue);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetControlCurrentValuePrologue( hDomainHandle, DomainControl, pValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetControlCurrentValue(result, hDomainHandle, DomainControl, pValue);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetControlCurrentValuePrologue( hDomainHandle, DomainControl, pValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetControlCurrentValue(result, hDomainHandle, DomainControl, pValue);
        }

        auto driver_result = pfnGetControlCurrentValue( hDomainHandle, DomainControl, pValue );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetControlCurrentValueEpilogue( hDomainHandle, DomainControl, pValue ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetControlCurrentValue(result, hDomainHandle, DomainControl, pValue);
        }

        return logAndPropagateResult_zesOverclockGetControlCurrentValue(driver_result, hDomainHandle, DomainControl, pValue);
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
            return logAndPropagateResult_zesOverclockGetControlPendingValue(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDomainHandle, DomainControl, pValue);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetControlPendingValuePrologue( hDomainHandle, DomainControl, pValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetControlPendingValue(result, hDomainHandle, DomainControl, pValue);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetControlPendingValuePrologue( hDomainHandle, DomainControl, pValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetControlPendingValue(result, hDomainHandle, DomainControl, pValue);
        }

        auto driver_result = pfnGetControlPendingValue( hDomainHandle, DomainControl, pValue );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetControlPendingValueEpilogue( hDomainHandle, DomainControl, pValue ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetControlPendingValue(result, hDomainHandle, DomainControl, pValue);
        }

        return logAndPropagateResult_zesOverclockGetControlPendingValue(driver_result, hDomainHandle, DomainControl, pValue);
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
            return logAndPropagateResult_zesOverclockSetControlUserValue(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDomainHandle, DomainControl, pValue, pPendingAction);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockSetControlUserValuePrologue( hDomainHandle, DomainControl, pValue, pPendingAction );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockSetControlUserValue(result, hDomainHandle, DomainControl, pValue, pPendingAction);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockSetControlUserValuePrologue( hDomainHandle, DomainControl, pValue, pPendingAction );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockSetControlUserValue(result, hDomainHandle, DomainControl, pValue, pPendingAction);
        }

        auto driver_result = pfnSetControlUserValue( hDomainHandle, DomainControl, pValue, pPendingAction );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockSetControlUserValueEpilogue( hDomainHandle, DomainControl, pValue, pPendingAction ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockSetControlUserValue(result, hDomainHandle, DomainControl, pValue, pPendingAction);
        }

        return logAndPropagateResult_zesOverclockSetControlUserValue(driver_result, hDomainHandle, DomainControl, pValue, pPendingAction);
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
            return logAndPropagateResult_zesOverclockGetControlState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDomainHandle, DomainControl, pControlState, pPendingAction);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetControlStatePrologue( hDomainHandle, DomainControl, pControlState, pPendingAction );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetControlState(result, hDomainHandle, DomainControl, pControlState, pPendingAction);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetControlStatePrologue( hDomainHandle, DomainControl, pControlState, pPendingAction );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetControlState(result, hDomainHandle, DomainControl, pControlState, pPendingAction);
        }

        auto driver_result = pfnGetControlState( hDomainHandle, DomainControl, pControlState, pPendingAction );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetControlStateEpilogue( hDomainHandle, DomainControl, pControlState, pPendingAction ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetControlState(result, hDomainHandle, DomainControl, pControlState, pPendingAction);
        }

        return logAndPropagateResult_zesOverclockGetControlState(driver_result, hDomainHandle, DomainControl, pControlState, pPendingAction);
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
            return logAndPropagateResult_zesOverclockGetVFPointValues(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDomainHandle, VFType, VFArrayType, PointIndex, PointValue);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetVFPointValuesPrologue( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetVFPointValues(result, hDomainHandle, VFType, VFArrayType, PointIndex, PointValue);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockGetVFPointValuesPrologue( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetVFPointValues(result, hDomainHandle, VFType, VFArrayType, PointIndex, PointValue);
        }

        auto driver_result = pfnGetVFPointValues( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockGetVFPointValuesEpilogue( hDomainHandle, VFType, VFArrayType, PointIndex, PointValue ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockGetVFPointValues(result, hDomainHandle, VFType, VFArrayType, PointIndex, PointValue);
        }

        return logAndPropagateResult_zesOverclockGetVFPointValues(driver_result, hDomainHandle, VFType, VFArrayType, PointIndex, PointValue);
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
            return logAndPropagateResult_zesOverclockSetVFPointValues(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDomainHandle, VFType, PointIndex, PointValue);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockSetVFPointValuesPrologue( hDomainHandle, VFType, PointIndex, PointValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockSetVFPointValues(result, hDomainHandle, VFType, PointIndex, PointValue);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesOverclockSetVFPointValuesPrologue( hDomainHandle, VFType, PointIndex, PointValue );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockSetVFPointValues(result, hDomainHandle, VFType, PointIndex, PointValue);
        }

        auto driver_result = pfnSetVFPointValues( hDomainHandle, VFType, PointIndex, PointValue );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesOverclockSetVFPointValuesEpilogue( hDomainHandle, VFType, PointIndex, PointValue ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesOverclockSetVFPointValues(result, hDomainHandle, VFType, PointIndex, PointValue);
        }

        return logAndPropagateResult_zesOverclockSetVFPointValues(driver_result, hDomainHandle, VFType, PointIndex, PointValue);
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
            return logAndPropagateResult_zesDeviceEnumDiagnosticTestSuites(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phDiagnostics);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumDiagnosticTestSuitesPrologue( hDevice, pCount, phDiagnostics );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumDiagnosticTestSuites(result, hDevice, pCount, phDiagnostics);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumDiagnosticTestSuitesPrologue( hDevice, pCount, phDiagnostics );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumDiagnosticTestSuites(result, hDevice, pCount, phDiagnostics);
        }

        auto driver_result = pfnEnumDiagnosticTestSuites( hDevice, pCount, phDiagnostics );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumDiagnosticTestSuitesEpilogue( hDevice, pCount, phDiagnostics ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumDiagnosticTestSuites(result, hDevice, pCount, phDiagnostics);
        }

        return logAndPropagateResult_zesDeviceEnumDiagnosticTestSuites(driver_result, hDevice, pCount, phDiagnostics);
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
            return logAndPropagateResult_zesDiagnosticsGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDiagnostics, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDiagnosticsGetPropertiesPrologue( hDiagnostics, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDiagnosticsGetProperties(result, hDiagnostics, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDiagnosticsGetPropertiesPrologue( hDiagnostics, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDiagnosticsGetProperties(result, hDiagnostics, pProperties);
        }

        auto driver_result = pfnGetProperties( hDiagnostics, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDiagnosticsGetPropertiesEpilogue( hDiagnostics, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDiagnosticsGetProperties(result, hDiagnostics, pProperties);
        }

        return logAndPropagateResult_zesDiagnosticsGetProperties(driver_result, hDiagnostics, pProperties);
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
            return logAndPropagateResult_zesDiagnosticsGetTests(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDiagnostics, pCount, pTests);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDiagnosticsGetTestsPrologue( hDiagnostics, pCount, pTests );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDiagnosticsGetTests(result, hDiagnostics, pCount, pTests);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDiagnosticsGetTestsPrologue( hDiagnostics, pCount, pTests );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDiagnosticsGetTests(result, hDiagnostics, pCount, pTests);
        }

        auto driver_result = pfnGetTests( hDiagnostics, pCount, pTests );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDiagnosticsGetTestsEpilogue( hDiagnostics, pCount, pTests ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDiagnosticsGetTests(result, hDiagnostics, pCount, pTests);
        }

        return logAndPropagateResult_zesDiagnosticsGetTests(driver_result, hDiagnostics, pCount, pTests);
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
            return logAndPropagateResult_zesDiagnosticsRunTests(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDiagnostics, startIndex, endIndex, pResult);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDiagnosticsRunTestsPrologue( hDiagnostics, startIndex, endIndex, pResult );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDiagnosticsRunTests(result, hDiagnostics, startIndex, endIndex, pResult);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDiagnosticsRunTestsPrologue( hDiagnostics, startIndex, endIndex, pResult );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDiagnosticsRunTests(result, hDiagnostics, startIndex, endIndex, pResult);
        }

        auto driver_result = pfnRunTests( hDiagnostics, startIndex, endIndex, pResult );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDiagnosticsRunTestsEpilogue( hDiagnostics, startIndex, endIndex, pResult ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDiagnosticsRunTests(result, hDiagnostics, startIndex, endIndex, pResult);
        }

        return logAndPropagateResult_zesDiagnosticsRunTests(driver_result, hDiagnostics, startIndex, endIndex, pResult);
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
            return logAndPropagateResult_zesDeviceEccAvailable(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pAvailable);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEccAvailablePrologue( hDevice, pAvailable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEccAvailable(result, hDevice, pAvailable);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEccAvailablePrologue( hDevice, pAvailable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEccAvailable(result, hDevice, pAvailable);
        }

        auto driver_result = pfnEccAvailable( hDevice, pAvailable );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEccAvailableEpilogue( hDevice, pAvailable ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEccAvailable(result, hDevice, pAvailable);
        }

        return logAndPropagateResult_zesDeviceEccAvailable(driver_result, hDevice, pAvailable);
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
            return logAndPropagateResult_zesDeviceEccConfigurable(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pConfigurable);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEccConfigurablePrologue( hDevice, pConfigurable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEccConfigurable(result, hDevice, pConfigurable);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEccConfigurablePrologue( hDevice, pConfigurable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEccConfigurable(result, hDevice, pConfigurable);
        }

        auto driver_result = pfnEccConfigurable( hDevice, pConfigurable );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEccConfigurableEpilogue( hDevice, pConfigurable ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEccConfigurable(result, hDevice, pConfigurable);
        }

        return logAndPropagateResult_zesDeviceEccConfigurable(driver_result, hDevice, pConfigurable);
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
            return logAndPropagateResult_zesDeviceGetEccState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pState);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetEccStatePrologue( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetEccState(result, hDevice, pState);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetEccStatePrologue( hDevice, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetEccState(result, hDevice, pState);
        }

        auto driver_result = pfnGetEccState( hDevice, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetEccStateEpilogue( hDevice, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetEccState(result, hDevice, pState);
        }

        return logAndPropagateResult_zesDeviceGetEccState(driver_result, hDevice, pState);
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
            return logAndPropagateResult_zesDeviceSetEccState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, newState, pState);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceSetEccStatePrologue( hDevice, newState, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceSetEccState(result, hDevice, newState, pState);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceSetEccStatePrologue( hDevice, newState, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceSetEccState(result, hDevice, newState, pState);
        }

        auto driver_result = pfnSetEccState( hDevice, newState, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceSetEccStateEpilogue( hDevice, newState, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceSetEccState(result, hDevice, newState, pState);
        }

        return logAndPropagateResult_zesDeviceSetEccState(driver_result, hDevice, newState, pState);
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
            return logAndPropagateResult_zesDeviceEnumEngineGroups(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phEngine);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumEngineGroupsPrologue( hDevice, pCount, phEngine );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumEngineGroups(result, hDevice, pCount, phEngine);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumEngineGroupsPrologue( hDevice, pCount, phEngine );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumEngineGroups(result, hDevice, pCount, phEngine);
        }

        auto driver_result = pfnEnumEngineGroups( hDevice, pCount, phEngine );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumEngineGroupsEpilogue( hDevice, pCount, phEngine ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumEngineGroups(result, hDevice, pCount, phEngine);
        }

        return logAndPropagateResult_zesDeviceEnumEngineGroups(driver_result, hDevice, pCount, phEngine);
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
            return logAndPropagateResult_zesEngineGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hEngine, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesEngineGetPropertiesPrologue( hEngine, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesEngineGetProperties(result, hEngine, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesEngineGetPropertiesPrologue( hEngine, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesEngineGetProperties(result, hEngine, pProperties);
        }

        auto driver_result = pfnGetProperties( hEngine, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesEngineGetPropertiesEpilogue( hEngine, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesEngineGetProperties(result, hEngine, pProperties);
        }

        return logAndPropagateResult_zesEngineGetProperties(driver_result, hEngine, pProperties);
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
            return logAndPropagateResult_zesEngineGetActivity(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hEngine, pStats);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesEngineGetActivityPrologue( hEngine, pStats );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesEngineGetActivity(result, hEngine, pStats);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesEngineGetActivityPrologue( hEngine, pStats );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesEngineGetActivity(result, hEngine, pStats);
        }

        auto driver_result = pfnGetActivity( hEngine, pStats );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesEngineGetActivityEpilogue( hEngine, pStats ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesEngineGetActivity(result, hEngine, pStats);
        }

        return logAndPropagateResult_zesEngineGetActivity(driver_result, hEngine, pStats);
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
            return logAndPropagateResult_zesDeviceEventRegister(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, events);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEventRegisterPrologue( hDevice, events );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEventRegister(result, hDevice, events);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEventRegisterPrologue( hDevice, events );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEventRegister(result, hDevice, events);
        }

        auto driver_result = pfnEventRegister( hDevice, events );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEventRegisterEpilogue( hDevice, events ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEventRegister(result, hDevice, events);
        }

        return logAndPropagateResult_zesDeviceEventRegister(driver_result, hDevice, events);
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
            return logAndPropagateResult_zesDriverEventListen(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverEventListenPrologue( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverEventListen(result, hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverEventListenPrologue( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverEventListen(result, hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);
        }

        auto driver_result = pfnEventListen( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverEventListenEpilogue( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverEventListen(result, hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);
        }

        return logAndPropagateResult_zesDriverEventListen(driver_result, hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);
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
            return logAndPropagateResult_zesDriverEventListenEx(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverEventListenExPrologue( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverEventListenEx(result, hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverEventListenExPrologue( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverEventListenEx(result, hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);
        }

        auto driver_result = pfnEventListenEx( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverEventListenExEpilogue( hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverEventListenEx(result, hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);
        }

        return logAndPropagateResult_zesDriverEventListenEx(driver_result, hDriver, timeout, count, phDevices, pNumDeviceEvents, pEvents);
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
            return logAndPropagateResult_zesDeviceEnumFabricPorts(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phPort);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFabricPortsPrologue( hDevice, pCount, phPort );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumFabricPorts(result, hDevice, pCount, phPort);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumFabricPortsPrologue( hDevice, pCount, phPort );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumFabricPorts(result, hDevice, pCount, phPort);
        }

        auto driver_result = pfnEnumFabricPorts( hDevice, pCount, phPort );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFabricPortsEpilogue( hDevice, pCount, phPort ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumFabricPorts(result, hDevice, pCount, phPort);
        }

        return logAndPropagateResult_zesDeviceEnumFabricPorts(driver_result, hDevice, pCount, phPort);
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
            return logAndPropagateResult_zesFabricPortGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPort, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetPropertiesPrologue( hPort, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetProperties(result, hPort, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetPropertiesPrologue( hPort, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetProperties(result, hPort, pProperties);
        }

        auto driver_result = pfnGetProperties( hPort, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetPropertiesEpilogue( hPort, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetProperties(result, hPort, pProperties);
        }

        return logAndPropagateResult_zesFabricPortGetProperties(driver_result, hPort, pProperties);
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
            return logAndPropagateResult_zesFabricPortGetLinkType(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPort, pLinkType);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetLinkTypePrologue( hPort, pLinkType );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetLinkType(result, hPort, pLinkType);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetLinkTypePrologue( hPort, pLinkType );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetLinkType(result, hPort, pLinkType);
        }

        auto driver_result = pfnGetLinkType( hPort, pLinkType );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetLinkTypeEpilogue( hPort, pLinkType ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetLinkType(result, hPort, pLinkType);
        }

        return logAndPropagateResult_zesFabricPortGetLinkType(driver_result, hPort, pLinkType);
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
            return logAndPropagateResult_zesFabricPortGetConfig(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPort, pConfig);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetConfigPrologue( hPort, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetConfig(result, hPort, pConfig);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetConfigPrologue( hPort, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetConfig(result, hPort, pConfig);
        }

        auto driver_result = pfnGetConfig( hPort, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetConfigEpilogue( hPort, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetConfig(result, hPort, pConfig);
        }

        return logAndPropagateResult_zesFabricPortGetConfig(driver_result, hPort, pConfig);
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
            return logAndPropagateResult_zesFabricPortSetConfig(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPort, pConfig);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortSetConfigPrologue( hPort, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortSetConfig(result, hPort, pConfig);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortSetConfigPrologue( hPort, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortSetConfig(result, hPort, pConfig);
        }

        auto driver_result = pfnSetConfig( hPort, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortSetConfigEpilogue( hPort, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortSetConfig(result, hPort, pConfig);
        }

        return logAndPropagateResult_zesFabricPortSetConfig(driver_result, hPort, pConfig);
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
            return logAndPropagateResult_zesFabricPortGetState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPort, pState);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetStatePrologue( hPort, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetState(result, hPort, pState);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetStatePrologue( hPort, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetState(result, hPort, pState);
        }

        auto driver_result = pfnGetState( hPort, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetStateEpilogue( hPort, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetState(result, hPort, pState);
        }

        return logAndPropagateResult_zesFabricPortGetState(driver_result, hPort, pState);
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
            return logAndPropagateResult_zesFabricPortGetThroughput(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPort, pThroughput);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetThroughputPrologue( hPort, pThroughput );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetThroughput(result, hPort, pThroughput);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetThroughputPrologue( hPort, pThroughput );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetThroughput(result, hPort, pThroughput);
        }

        auto driver_result = pfnGetThroughput( hPort, pThroughput );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetThroughputEpilogue( hPort, pThroughput ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetThroughput(result, hPort, pThroughput);
        }

        return logAndPropagateResult_zesFabricPortGetThroughput(driver_result, hPort, pThroughput);
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
            return logAndPropagateResult_zesFabricPortGetFabricErrorCounters(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPort, pErrors);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetFabricErrorCountersPrologue( hPort, pErrors );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetFabricErrorCounters(result, hPort, pErrors);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetFabricErrorCountersPrologue( hPort, pErrors );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetFabricErrorCounters(result, hPort, pErrors);
        }

        auto driver_result = pfnGetFabricErrorCounters( hPort, pErrors );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetFabricErrorCountersEpilogue( hPort, pErrors ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetFabricErrorCounters(result, hPort, pErrors);
        }

        return logAndPropagateResult_zesFabricPortGetFabricErrorCounters(driver_result, hPort, pErrors);
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
            return logAndPropagateResult_zesFabricPortGetMultiPortThroughput(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, numPorts, phPort, pThroughput);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetMultiPortThroughputPrologue( hDevice, numPorts, phPort, pThroughput );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetMultiPortThroughput(result, hDevice, numPorts, phPort, pThroughput);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFabricPortGetMultiPortThroughputPrologue( hDevice, numPorts, phPort, pThroughput );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetMultiPortThroughput(result, hDevice, numPorts, phPort, pThroughput);
        }

        auto driver_result = pfnGetMultiPortThroughput( hDevice, numPorts, phPort, pThroughput );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFabricPortGetMultiPortThroughputEpilogue( hDevice, numPorts, phPort, pThroughput ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFabricPortGetMultiPortThroughput(result, hDevice, numPorts, phPort, pThroughput);
        }

        return logAndPropagateResult_zesFabricPortGetMultiPortThroughput(driver_result, hDevice, numPorts, phPort, pThroughput);
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
            return logAndPropagateResult_zesDeviceEnumFans(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phFan);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFansPrologue( hDevice, pCount, phFan );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumFans(result, hDevice, pCount, phFan);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumFansPrologue( hDevice, pCount, phFan );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumFans(result, hDevice, pCount, phFan);
        }

        auto driver_result = pfnEnumFans( hDevice, pCount, phFan );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFansEpilogue( hDevice, pCount, phFan ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumFans(result, hDevice, pCount, phFan);
        }

        return logAndPropagateResult_zesDeviceEnumFans(driver_result, hDevice, pCount, phFan);
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
            return logAndPropagateResult_zesFanGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFan, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanGetPropertiesPrologue( hFan, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanGetProperties(result, hFan, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanGetPropertiesPrologue( hFan, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanGetProperties(result, hFan, pProperties);
        }

        auto driver_result = pfnGetProperties( hFan, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanGetPropertiesEpilogue( hFan, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanGetProperties(result, hFan, pProperties);
        }

        return logAndPropagateResult_zesFanGetProperties(driver_result, hFan, pProperties);
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
            return logAndPropagateResult_zesFanGetConfig(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFan, pConfig);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanGetConfigPrologue( hFan, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanGetConfig(result, hFan, pConfig);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanGetConfigPrologue( hFan, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanGetConfig(result, hFan, pConfig);
        }

        auto driver_result = pfnGetConfig( hFan, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanGetConfigEpilogue( hFan, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanGetConfig(result, hFan, pConfig);
        }

        return logAndPropagateResult_zesFanGetConfig(driver_result, hFan, pConfig);
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
            return logAndPropagateResult_zesFanSetDefaultMode(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFan);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanSetDefaultModePrologue( hFan );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanSetDefaultMode(result, hFan);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanSetDefaultModePrologue( hFan );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanSetDefaultMode(result, hFan);
        }

        auto driver_result = pfnSetDefaultMode( hFan );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanSetDefaultModeEpilogue( hFan ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanSetDefaultMode(result, hFan);
        }

        return logAndPropagateResult_zesFanSetDefaultMode(driver_result, hFan);
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
            return logAndPropagateResult_zesFanSetFixedSpeedMode(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFan, speed);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanSetFixedSpeedModePrologue( hFan, speed );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanSetFixedSpeedMode(result, hFan, speed);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanSetFixedSpeedModePrologue( hFan, speed );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanSetFixedSpeedMode(result, hFan, speed);
        }

        auto driver_result = pfnSetFixedSpeedMode( hFan, speed );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanSetFixedSpeedModeEpilogue( hFan, speed ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanSetFixedSpeedMode(result, hFan, speed);
        }

        return logAndPropagateResult_zesFanSetFixedSpeedMode(driver_result, hFan, speed);
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
            return logAndPropagateResult_zesFanSetSpeedTableMode(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFan, speedTable);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanSetSpeedTableModePrologue( hFan, speedTable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanSetSpeedTableMode(result, hFan, speedTable);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanSetSpeedTableModePrologue( hFan, speedTable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanSetSpeedTableMode(result, hFan, speedTable);
        }

        auto driver_result = pfnSetSpeedTableMode( hFan, speedTable );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanSetSpeedTableModeEpilogue( hFan, speedTable ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanSetSpeedTableMode(result, hFan, speedTable);
        }

        return logAndPropagateResult_zesFanSetSpeedTableMode(driver_result, hFan, speedTable);
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
            return logAndPropagateResult_zesFanGetState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFan, units, pSpeed);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanGetStatePrologue( hFan, units, pSpeed );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanGetState(result, hFan, units, pSpeed);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFanGetStatePrologue( hFan, units, pSpeed );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanGetState(result, hFan, units, pSpeed);
        }

        auto driver_result = pfnGetState( hFan, units, pSpeed );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFanGetStateEpilogue( hFan, units, pSpeed ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFanGetState(result, hFan, units, pSpeed);
        }

        return logAndPropagateResult_zesFanGetState(driver_result, hFan, units, pSpeed);
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
            return logAndPropagateResult_zesDeviceEnumFirmwares(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phFirmware);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFirmwaresPrologue( hDevice, pCount, phFirmware );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumFirmwares(result, hDevice, pCount, phFirmware);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumFirmwaresPrologue( hDevice, pCount, phFirmware );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumFirmwares(result, hDevice, pCount, phFirmware);
        }

        auto driver_result = pfnEnumFirmwares( hDevice, pCount, phFirmware );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFirmwaresEpilogue( hDevice, pCount, phFirmware ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumFirmwares(result, hDevice, pCount, phFirmware);
        }

        return logAndPropagateResult_zesDeviceEnumFirmwares(driver_result, hDevice, pCount, phFirmware);
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
            return logAndPropagateResult_zesFirmwareGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFirmware, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetPropertiesPrologue( hFirmware, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareGetProperties(result, hFirmware, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFirmwareGetPropertiesPrologue( hFirmware, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareGetProperties(result, hFirmware, pProperties);
        }

        auto driver_result = pfnGetProperties( hFirmware, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetPropertiesEpilogue( hFirmware, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareGetProperties(result, hFirmware, pProperties);
        }

        return logAndPropagateResult_zesFirmwareGetProperties(driver_result, hFirmware, pProperties);
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
            return logAndPropagateResult_zesFirmwareFlash(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFirmware, pImage, size);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareFlashPrologue( hFirmware, pImage, size );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareFlash(result, hFirmware, pImage, size);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFirmwareFlashPrologue( hFirmware, pImage, size );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareFlash(result, hFirmware, pImage, size);
        }

        auto driver_result = pfnFlash( hFirmware, pImage, size );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareFlashEpilogue( hFirmware, pImage, size ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareFlash(result, hFirmware, pImage, size);
        }

        return logAndPropagateResult_zesFirmwareFlash(driver_result, hFirmware, pImage, size);
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
            return logAndPropagateResult_zesFirmwareGetFlashProgress(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFirmware, pCompletionPercent);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetFlashProgressPrologue( hFirmware, pCompletionPercent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareGetFlashProgress(result, hFirmware, pCompletionPercent);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFirmwareGetFlashProgressPrologue( hFirmware, pCompletionPercent );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareGetFlashProgress(result, hFirmware, pCompletionPercent);
        }

        auto driver_result = pfnGetFlashProgress( hFirmware, pCompletionPercent );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetFlashProgressEpilogue( hFirmware, pCompletionPercent ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareGetFlashProgress(result, hFirmware, pCompletionPercent);
        }

        return logAndPropagateResult_zesFirmwareGetFlashProgress(driver_result, hFirmware, pCompletionPercent);
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
            return logAndPropagateResult_zesFirmwareGetConsoleLogs(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFirmware, pSize, pFirmwareLog);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetConsoleLogsPrologue( hFirmware, pSize, pFirmwareLog );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareGetConsoleLogs(result, hFirmware, pSize, pFirmwareLog);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFirmwareGetConsoleLogsPrologue( hFirmware, pSize, pFirmwareLog );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareGetConsoleLogs(result, hFirmware, pSize, pFirmwareLog);
        }

        auto driver_result = pfnGetConsoleLogs( hFirmware, pSize, pFirmwareLog );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetConsoleLogsEpilogue( hFirmware, pSize, pFirmwareLog ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareGetConsoleLogs(result, hFirmware, pSize, pFirmwareLog);
        }

        return logAndPropagateResult_zesFirmwareGetConsoleLogs(driver_result, hFirmware, pSize, pFirmwareLog);
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
            return logAndPropagateResult_zesDeviceEnumFrequencyDomains(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phFrequency);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFrequencyDomainsPrologue( hDevice, pCount, phFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumFrequencyDomains(result, hDevice, pCount, phFrequency);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumFrequencyDomainsPrologue( hDevice, pCount, phFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumFrequencyDomains(result, hDevice, pCount, phFrequency);
        }

        auto driver_result = pfnEnumFrequencyDomains( hDevice, pCount, phFrequency );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumFrequencyDomainsEpilogue( hDevice, pCount, phFrequency ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumFrequencyDomains(result, hDevice, pCount, phFrequency);
        }

        return logAndPropagateResult_zesDeviceEnumFrequencyDomains(driver_result, hDevice, pCount, phFrequency);
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
            return logAndPropagateResult_zesFrequencyGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetPropertiesPrologue( hFrequency, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyGetProperties(result, hFrequency, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyGetPropertiesPrologue( hFrequency, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyGetProperties(result, hFrequency, pProperties);
        }

        auto driver_result = pfnGetProperties( hFrequency, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetPropertiesEpilogue( hFrequency, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyGetProperties(result, hFrequency, pProperties);
        }

        return logAndPropagateResult_zesFrequencyGetProperties(driver_result, hFrequency, pProperties);
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
            return logAndPropagateResult_zesFrequencyGetAvailableClocks(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, pCount, phFrequency);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetAvailableClocksPrologue( hFrequency, pCount, phFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyGetAvailableClocks(result, hFrequency, pCount, phFrequency);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyGetAvailableClocksPrologue( hFrequency, pCount, phFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyGetAvailableClocks(result, hFrequency, pCount, phFrequency);
        }

        auto driver_result = pfnGetAvailableClocks( hFrequency, pCount, phFrequency );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetAvailableClocksEpilogue( hFrequency, pCount, phFrequency ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyGetAvailableClocks(result, hFrequency, pCount, phFrequency);
        }

        return logAndPropagateResult_zesFrequencyGetAvailableClocks(driver_result, hFrequency, pCount, phFrequency);
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
            return logAndPropagateResult_zesFrequencyGetRange(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, pLimits);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetRangePrologue( hFrequency, pLimits );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyGetRange(result, hFrequency, pLimits);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyGetRangePrologue( hFrequency, pLimits );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyGetRange(result, hFrequency, pLimits);
        }

        auto driver_result = pfnGetRange( hFrequency, pLimits );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetRangeEpilogue( hFrequency, pLimits ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyGetRange(result, hFrequency, pLimits);
        }

        return logAndPropagateResult_zesFrequencyGetRange(driver_result, hFrequency, pLimits);
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
            return logAndPropagateResult_zesFrequencySetRange(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, pLimits);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencySetRangePrologue( hFrequency, pLimits );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencySetRange(result, hFrequency, pLimits);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencySetRangePrologue( hFrequency, pLimits );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencySetRange(result, hFrequency, pLimits);
        }

        auto driver_result = pfnSetRange( hFrequency, pLimits );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencySetRangeEpilogue( hFrequency, pLimits ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencySetRange(result, hFrequency, pLimits);
        }

        return logAndPropagateResult_zesFrequencySetRange(driver_result, hFrequency, pLimits);
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
            return logAndPropagateResult_zesFrequencyGetState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, pState);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetStatePrologue( hFrequency, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyGetState(result, hFrequency, pState);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyGetStatePrologue( hFrequency, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyGetState(result, hFrequency, pState);
        }

        auto driver_result = pfnGetState( hFrequency, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetStateEpilogue( hFrequency, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyGetState(result, hFrequency, pState);
        }

        return logAndPropagateResult_zesFrequencyGetState(driver_result, hFrequency, pState);
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
            return logAndPropagateResult_zesFrequencyGetThrottleTime(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, pThrottleTime);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetThrottleTimePrologue( hFrequency, pThrottleTime );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyGetThrottleTime(result, hFrequency, pThrottleTime);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyGetThrottleTimePrologue( hFrequency, pThrottleTime );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyGetThrottleTime(result, hFrequency, pThrottleTime);
        }

        auto driver_result = pfnGetThrottleTime( hFrequency, pThrottleTime );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyGetThrottleTimeEpilogue( hFrequency, pThrottleTime ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyGetThrottleTime(result, hFrequency, pThrottleTime);
        }

        return logAndPropagateResult_zesFrequencyGetThrottleTime(driver_result, hFrequency, pThrottleTime);
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
            return logAndPropagateResult_zesFrequencyOcGetCapabilities(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, pOcCapabilities);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetCapabilitiesPrologue( hFrequency, pOcCapabilities );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetCapabilities(result, hFrequency, pOcCapabilities);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetCapabilitiesPrologue( hFrequency, pOcCapabilities );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetCapabilities(result, hFrequency, pOcCapabilities);
        }

        auto driver_result = pfnOcGetCapabilities( hFrequency, pOcCapabilities );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetCapabilitiesEpilogue( hFrequency, pOcCapabilities ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetCapabilities(result, hFrequency, pOcCapabilities);
        }

        return logAndPropagateResult_zesFrequencyOcGetCapabilities(driver_result, hFrequency, pOcCapabilities);
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
            return logAndPropagateResult_zesFrequencyOcGetFrequencyTarget(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, pCurrentOcFrequency);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetFrequencyTargetPrologue( hFrequency, pCurrentOcFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetFrequencyTarget(result, hFrequency, pCurrentOcFrequency);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetFrequencyTargetPrologue( hFrequency, pCurrentOcFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetFrequencyTarget(result, hFrequency, pCurrentOcFrequency);
        }

        auto driver_result = pfnOcGetFrequencyTarget( hFrequency, pCurrentOcFrequency );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetFrequencyTargetEpilogue( hFrequency, pCurrentOcFrequency ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetFrequencyTarget(result, hFrequency, pCurrentOcFrequency);
        }

        return logAndPropagateResult_zesFrequencyOcGetFrequencyTarget(driver_result, hFrequency, pCurrentOcFrequency);
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
            return logAndPropagateResult_zesFrequencyOcSetFrequencyTarget(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, CurrentOcFrequency);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetFrequencyTargetPrologue( hFrequency, CurrentOcFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcSetFrequencyTarget(result, hFrequency, CurrentOcFrequency);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcSetFrequencyTargetPrologue( hFrequency, CurrentOcFrequency );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcSetFrequencyTarget(result, hFrequency, CurrentOcFrequency);
        }

        auto driver_result = pfnOcSetFrequencyTarget( hFrequency, CurrentOcFrequency );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetFrequencyTargetEpilogue( hFrequency, CurrentOcFrequency ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcSetFrequencyTarget(result, hFrequency, CurrentOcFrequency);
        }

        return logAndPropagateResult_zesFrequencyOcSetFrequencyTarget(driver_result, hFrequency, CurrentOcFrequency);
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
            return logAndPropagateResult_zesFrequencyOcGetVoltageTarget(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetVoltageTargetPrologue( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetVoltageTarget(result, hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetVoltageTargetPrologue( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetVoltageTarget(result, hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset);
        }

        auto driver_result = pfnOcGetVoltageTarget( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetVoltageTargetEpilogue( hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetVoltageTarget(result, hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset);
        }

        return logAndPropagateResult_zesFrequencyOcGetVoltageTarget(driver_result, hFrequency, pCurrentVoltageTarget, pCurrentVoltageOffset);
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
            return logAndPropagateResult_zesFrequencyOcSetVoltageTarget(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, CurrentVoltageTarget, CurrentVoltageOffset);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetVoltageTargetPrologue( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcSetVoltageTarget(result, hFrequency, CurrentVoltageTarget, CurrentVoltageOffset);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcSetVoltageTargetPrologue( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcSetVoltageTarget(result, hFrequency, CurrentVoltageTarget, CurrentVoltageOffset);
        }

        auto driver_result = pfnOcSetVoltageTarget( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetVoltageTargetEpilogue( hFrequency, CurrentVoltageTarget, CurrentVoltageOffset ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcSetVoltageTarget(result, hFrequency, CurrentVoltageTarget, CurrentVoltageOffset);
        }

        return logAndPropagateResult_zesFrequencyOcSetVoltageTarget(driver_result, hFrequency, CurrentVoltageTarget, CurrentVoltageOffset);
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
            return logAndPropagateResult_zesFrequencyOcSetMode(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, CurrentOcMode);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetModePrologue( hFrequency, CurrentOcMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcSetMode(result, hFrequency, CurrentOcMode);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcSetModePrologue( hFrequency, CurrentOcMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcSetMode(result, hFrequency, CurrentOcMode);
        }

        auto driver_result = pfnOcSetMode( hFrequency, CurrentOcMode );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetModeEpilogue( hFrequency, CurrentOcMode ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcSetMode(result, hFrequency, CurrentOcMode);
        }

        return logAndPropagateResult_zesFrequencyOcSetMode(driver_result, hFrequency, CurrentOcMode);
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
            return logAndPropagateResult_zesFrequencyOcGetMode(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, pCurrentOcMode);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetModePrologue( hFrequency, pCurrentOcMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetMode(result, hFrequency, pCurrentOcMode);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetModePrologue( hFrequency, pCurrentOcMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetMode(result, hFrequency, pCurrentOcMode);
        }

        auto driver_result = pfnOcGetMode( hFrequency, pCurrentOcMode );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetModeEpilogue( hFrequency, pCurrentOcMode ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetMode(result, hFrequency, pCurrentOcMode);
        }

        return logAndPropagateResult_zesFrequencyOcGetMode(driver_result, hFrequency, pCurrentOcMode);
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
            return logAndPropagateResult_zesFrequencyOcGetIccMax(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, pOcIccMax);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetIccMaxPrologue( hFrequency, pOcIccMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetIccMax(result, hFrequency, pOcIccMax);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetIccMaxPrologue( hFrequency, pOcIccMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetIccMax(result, hFrequency, pOcIccMax);
        }

        auto driver_result = pfnOcGetIccMax( hFrequency, pOcIccMax );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetIccMaxEpilogue( hFrequency, pOcIccMax ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetIccMax(result, hFrequency, pOcIccMax);
        }

        return logAndPropagateResult_zesFrequencyOcGetIccMax(driver_result, hFrequency, pOcIccMax);
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
            return logAndPropagateResult_zesFrequencyOcSetIccMax(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, ocIccMax);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetIccMaxPrologue( hFrequency, ocIccMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcSetIccMax(result, hFrequency, ocIccMax);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcSetIccMaxPrologue( hFrequency, ocIccMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcSetIccMax(result, hFrequency, ocIccMax);
        }

        auto driver_result = pfnOcSetIccMax( hFrequency, ocIccMax );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetIccMaxEpilogue( hFrequency, ocIccMax ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcSetIccMax(result, hFrequency, ocIccMax);
        }

        return logAndPropagateResult_zesFrequencyOcSetIccMax(driver_result, hFrequency, ocIccMax);
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
            return logAndPropagateResult_zesFrequencyOcGetTjMax(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, pOcTjMax);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetTjMaxPrologue( hFrequency, pOcTjMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetTjMax(result, hFrequency, pOcTjMax);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcGetTjMaxPrologue( hFrequency, pOcTjMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetTjMax(result, hFrequency, pOcTjMax);
        }

        auto driver_result = pfnOcGetTjMax( hFrequency, pOcTjMax );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcGetTjMaxEpilogue( hFrequency, pOcTjMax ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcGetTjMax(result, hFrequency, pOcTjMax);
        }

        return logAndPropagateResult_zesFrequencyOcGetTjMax(driver_result, hFrequency, pOcTjMax);
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
            return logAndPropagateResult_zesFrequencyOcSetTjMax(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFrequency, ocTjMax);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetTjMaxPrologue( hFrequency, ocTjMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcSetTjMax(result, hFrequency, ocTjMax);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFrequencyOcSetTjMaxPrologue( hFrequency, ocTjMax );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcSetTjMax(result, hFrequency, ocTjMax);
        }

        auto driver_result = pfnOcSetTjMax( hFrequency, ocTjMax );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFrequencyOcSetTjMaxEpilogue( hFrequency, ocTjMax ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFrequencyOcSetTjMax(result, hFrequency, ocTjMax);
        }

        return logAndPropagateResult_zesFrequencyOcSetTjMax(driver_result, hFrequency, ocTjMax);
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
            return logAndPropagateResult_zesDeviceEnumLeds(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phLed);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumLedsPrologue( hDevice, pCount, phLed );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumLeds(result, hDevice, pCount, phLed);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumLedsPrologue( hDevice, pCount, phLed );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumLeds(result, hDevice, pCount, phLed);
        }

        auto driver_result = pfnEnumLeds( hDevice, pCount, phLed );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumLedsEpilogue( hDevice, pCount, phLed ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumLeds(result, hDevice, pCount, phLed);
        }

        return logAndPropagateResult_zesDeviceEnumLeds(driver_result, hDevice, pCount, phLed);
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
            return logAndPropagateResult_zesLedGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hLed, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedGetPropertiesPrologue( hLed, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesLedGetProperties(result, hLed, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesLedGetPropertiesPrologue( hLed, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesLedGetProperties(result, hLed, pProperties);
        }

        auto driver_result = pfnGetProperties( hLed, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedGetPropertiesEpilogue( hLed, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesLedGetProperties(result, hLed, pProperties);
        }

        return logAndPropagateResult_zesLedGetProperties(driver_result, hLed, pProperties);
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
            return logAndPropagateResult_zesLedGetState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hLed, pState);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedGetStatePrologue( hLed, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesLedGetState(result, hLed, pState);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesLedGetStatePrologue( hLed, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesLedGetState(result, hLed, pState);
        }

        auto driver_result = pfnGetState( hLed, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedGetStateEpilogue( hLed, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesLedGetState(result, hLed, pState);
        }

        return logAndPropagateResult_zesLedGetState(driver_result, hLed, pState);
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
            return logAndPropagateResult_zesLedSetState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hLed, enable);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedSetStatePrologue( hLed, enable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesLedSetState(result, hLed, enable);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesLedSetStatePrologue( hLed, enable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesLedSetState(result, hLed, enable);
        }

        auto driver_result = pfnSetState( hLed, enable );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedSetStateEpilogue( hLed, enable ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesLedSetState(result, hLed, enable);
        }

        return logAndPropagateResult_zesLedSetState(driver_result, hLed, enable);
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
            return logAndPropagateResult_zesLedSetColor(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hLed, pColor);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedSetColorPrologue( hLed, pColor );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesLedSetColor(result, hLed, pColor);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesLedSetColorPrologue( hLed, pColor );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesLedSetColor(result, hLed, pColor);
        }

        auto driver_result = pfnSetColor( hLed, pColor );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesLedSetColorEpilogue( hLed, pColor ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesLedSetColor(result, hLed, pColor);
        }

        return logAndPropagateResult_zesLedSetColor(driver_result, hLed, pColor);
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
            return logAndPropagateResult_zesDeviceEnumMemoryModules(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phMemory);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumMemoryModulesPrologue( hDevice, pCount, phMemory );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumMemoryModules(result, hDevice, pCount, phMemory);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumMemoryModulesPrologue( hDevice, pCount, phMemory );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumMemoryModules(result, hDevice, pCount, phMemory);
        }

        auto driver_result = pfnEnumMemoryModules( hDevice, pCount, phMemory );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumMemoryModulesEpilogue( hDevice, pCount, phMemory ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumMemoryModules(result, hDevice, pCount, phMemory);
        }

        return logAndPropagateResult_zesDeviceEnumMemoryModules(driver_result, hDevice, pCount, phMemory);
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
            return logAndPropagateResult_zesMemoryGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMemory, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesMemoryGetPropertiesPrologue( hMemory, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesMemoryGetProperties(result, hMemory, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesMemoryGetPropertiesPrologue( hMemory, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesMemoryGetProperties(result, hMemory, pProperties);
        }

        auto driver_result = pfnGetProperties( hMemory, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesMemoryGetPropertiesEpilogue( hMemory, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesMemoryGetProperties(result, hMemory, pProperties);
        }

        return logAndPropagateResult_zesMemoryGetProperties(driver_result, hMemory, pProperties);
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
            return logAndPropagateResult_zesMemoryGetState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMemory, pState);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesMemoryGetStatePrologue( hMemory, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesMemoryGetState(result, hMemory, pState);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesMemoryGetStatePrologue( hMemory, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesMemoryGetState(result, hMemory, pState);
        }

        auto driver_result = pfnGetState( hMemory, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesMemoryGetStateEpilogue( hMemory, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesMemoryGetState(result, hMemory, pState);
        }

        return logAndPropagateResult_zesMemoryGetState(driver_result, hMemory, pState);
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
            return logAndPropagateResult_zesMemoryGetBandwidth(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hMemory, pBandwidth);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesMemoryGetBandwidthPrologue( hMemory, pBandwidth );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesMemoryGetBandwidth(result, hMemory, pBandwidth);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesMemoryGetBandwidthPrologue( hMemory, pBandwidth );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesMemoryGetBandwidth(result, hMemory, pBandwidth);
        }

        auto driver_result = pfnGetBandwidth( hMemory, pBandwidth );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesMemoryGetBandwidthEpilogue( hMemory, pBandwidth ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesMemoryGetBandwidth(result, hMemory, pBandwidth);
        }

        return logAndPropagateResult_zesMemoryGetBandwidth(driver_result, hMemory, pBandwidth);
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
            return logAndPropagateResult_zesDeviceEnumPerformanceFactorDomains(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phPerf);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumPerformanceFactorDomainsPrologue( hDevice, pCount, phPerf );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumPerformanceFactorDomains(result, hDevice, pCount, phPerf);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumPerformanceFactorDomainsPrologue( hDevice, pCount, phPerf );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumPerformanceFactorDomains(result, hDevice, pCount, phPerf);
        }

        auto driver_result = pfnEnumPerformanceFactorDomains( hDevice, pCount, phPerf );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumPerformanceFactorDomainsEpilogue( hDevice, pCount, phPerf ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumPerformanceFactorDomains(result, hDevice, pCount, phPerf);
        }

        return logAndPropagateResult_zesDeviceEnumPerformanceFactorDomains(driver_result, hDevice, pCount, phPerf);
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
            return logAndPropagateResult_zesPerformanceFactorGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPerf, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPerformanceFactorGetPropertiesPrologue( hPerf, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPerformanceFactorGetProperties(result, hPerf, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPerformanceFactorGetPropertiesPrologue( hPerf, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPerformanceFactorGetProperties(result, hPerf, pProperties);
        }

        auto driver_result = pfnGetProperties( hPerf, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPerformanceFactorGetPropertiesEpilogue( hPerf, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPerformanceFactorGetProperties(result, hPerf, pProperties);
        }

        return logAndPropagateResult_zesPerformanceFactorGetProperties(driver_result, hPerf, pProperties);
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
            return logAndPropagateResult_zesPerformanceFactorGetConfig(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPerf, pFactor);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPerformanceFactorGetConfigPrologue( hPerf, pFactor );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPerformanceFactorGetConfig(result, hPerf, pFactor);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPerformanceFactorGetConfigPrologue( hPerf, pFactor );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPerformanceFactorGetConfig(result, hPerf, pFactor);
        }

        auto driver_result = pfnGetConfig( hPerf, pFactor );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPerformanceFactorGetConfigEpilogue( hPerf, pFactor ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPerformanceFactorGetConfig(result, hPerf, pFactor);
        }

        return logAndPropagateResult_zesPerformanceFactorGetConfig(driver_result, hPerf, pFactor);
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
            return logAndPropagateResult_zesPerformanceFactorSetConfig(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPerf, factor);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPerformanceFactorSetConfigPrologue( hPerf, factor );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPerformanceFactorSetConfig(result, hPerf, factor);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPerformanceFactorSetConfigPrologue( hPerf, factor );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPerformanceFactorSetConfig(result, hPerf, factor);
        }

        auto driver_result = pfnSetConfig( hPerf, factor );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPerformanceFactorSetConfigEpilogue( hPerf, factor ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPerformanceFactorSetConfig(result, hPerf, factor);
        }

        return logAndPropagateResult_zesPerformanceFactorSetConfig(driver_result, hPerf, factor);
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
            return logAndPropagateResult_zesDeviceEnumPowerDomains(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phPower);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumPowerDomainsPrologue( hDevice, pCount, phPower );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumPowerDomains(result, hDevice, pCount, phPower);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumPowerDomainsPrologue( hDevice, pCount, phPower );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumPowerDomains(result, hDevice, pCount, phPower);
        }

        auto driver_result = pfnEnumPowerDomains( hDevice, pCount, phPower );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumPowerDomainsEpilogue( hDevice, pCount, phPower ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumPowerDomains(result, hDevice, pCount, phPower);
        }

        return logAndPropagateResult_zesDeviceEnumPowerDomains(driver_result, hDevice, pCount, phPower);
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
            return logAndPropagateResult_zesDeviceGetCardPowerDomain(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, phPower);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetCardPowerDomainPrologue( hDevice, phPower );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetCardPowerDomain(result, hDevice, phPower);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetCardPowerDomainPrologue( hDevice, phPower );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetCardPowerDomain(result, hDevice, phPower);
        }

        auto driver_result = pfnGetCardPowerDomain( hDevice, phPower );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetCardPowerDomainEpilogue( hDevice, phPower ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetCardPowerDomain(result, hDevice, phPower);
        }

        return logAndPropagateResult_zesDeviceGetCardPowerDomain(driver_result, hDevice, phPower);
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
            return logAndPropagateResult_zesPowerGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPower, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetPropertiesPrologue( hPower, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerGetProperties(result, hPower, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerGetPropertiesPrologue( hPower, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerGetProperties(result, hPower, pProperties);
        }

        auto driver_result = pfnGetProperties( hPower, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetPropertiesEpilogue( hPower, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerGetProperties(result, hPower, pProperties);
        }

        return logAndPropagateResult_zesPowerGetProperties(driver_result, hPower, pProperties);
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
            return logAndPropagateResult_zesPowerGetEnergyCounter(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPower, pEnergy);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetEnergyCounterPrologue( hPower, pEnergy );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerGetEnergyCounter(result, hPower, pEnergy);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerGetEnergyCounterPrologue( hPower, pEnergy );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerGetEnergyCounter(result, hPower, pEnergy);
        }

        auto driver_result = pfnGetEnergyCounter( hPower, pEnergy );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetEnergyCounterEpilogue( hPower, pEnergy ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerGetEnergyCounter(result, hPower, pEnergy);
        }

        return logAndPropagateResult_zesPowerGetEnergyCounter(driver_result, hPower, pEnergy);
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
            return logAndPropagateResult_zesPowerGetLimits(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPower, pSustained, pBurst, pPeak);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetLimitsPrologue( hPower, pSustained, pBurst, pPeak );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerGetLimits(result, hPower, pSustained, pBurst, pPeak);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerGetLimitsPrologue( hPower, pSustained, pBurst, pPeak );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerGetLimits(result, hPower, pSustained, pBurst, pPeak);
        }

        auto driver_result = pfnGetLimits( hPower, pSustained, pBurst, pPeak );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetLimitsEpilogue( hPower, pSustained, pBurst, pPeak ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerGetLimits(result, hPower, pSustained, pBurst, pPeak);
        }

        return logAndPropagateResult_zesPowerGetLimits(driver_result, hPower, pSustained, pBurst, pPeak);
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
            return logAndPropagateResult_zesPowerSetLimits(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPower, pSustained, pBurst, pPeak);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerSetLimitsPrologue( hPower, pSustained, pBurst, pPeak );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerSetLimits(result, hPower, pSustained, pBurst, pPeak);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerSetLimitsPrologue( hPower, pSustained, pBurst, pPeak );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerSetLimits(result, hPower, pSustained, pBurst, pPeak);
        }

        auto driver_result = pfnSetLimits( hPower, pSustained, pBurst, pPeak );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerSetLimitsEpilogue( hPower, pSustained, pBurst, pPeak ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerSetLimits(result, hPower, pSustained, pBurst, pPeak);
        }

        return logAndPropagateResult_zesPowerSetLimits(driver_result, hPower, pSustained, pBurst, pPeak);
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
            return logAndPropagateResult_zesPowerGetEnergyThreshold(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPower, pThreshold);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetEnergyThresholdPrologue( hPower, pThreshold );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerGetEnergyThreshold(result, hPower, pThreshold);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerGetEnergyThresholdPrologue( hPower, pThreshold );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerGetEnergyThreshold(result, hPower, pThreshold);
        }

        auto driver_result = pfnGetEnergyThreshold( hPower, pThreshold );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetEnergyThresholdEpilogue( hPower, pThreshold ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerGetEnergyThreshold(result, hPower, pThreshold);
        }

        return logAndPropagateResult_zesPowerGetEnergyThreshold(driver_result, hPower, pThreshold);
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
            return logAndPropagateResult_zesPowerSetEnergyThreshold(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPower, threshold);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerSetEnergyThresholdPrologue( hPower, threshold );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerSetEnergyThreshold(result, hPower, threshold);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerSetEnergyThresholdPrologue( hPower, threshold );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerSetEnergyThreshold(result, hPower, threshold);
        }

        auto driver_result = pfnSetEnergyThreshold( hPower, threshold );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerSetEnergyThresholdEpilogue( hPower, threshold ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerSetEnergyThreshold(result, hPower, threshold);
        }

        return logAndPropagateResult_zesPowerSetEnergyThreshold(driver_result, hPower, threshold);
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
            return logAndPropagateResult_zesDeviceEnumPsus(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phPsu);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumPsusPrologue( hDevice, pCount, phPsu );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumPsus(result, hDevice, pCount, phPsu);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumPsusPrologue( hDevice, pCount, phPsu );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumPsus(result, hDevice, pCount, phPsu);
        }

        auto driver_result = pfnEnumPsus( hDevice, pCount, phPsu );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumPsusEpilogue( hDevice, pCount, phPsu ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumPsus(result, hDevice, pCount, phPsu);
        }

        return logAndPropagateResult_zesDeviceEnumPsus(driver_result, hDevice, pCount, phPsu);
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
            return logAndPropagateResult_zesPsuGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPsu, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPsuGetPropertiesPrologue( hPsu, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPsuGetProperties(result, hPsu, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPsuGetPropertiesPrologue( hPsu, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPsuGetProperties(result, hPsu, pProperties);
        }

        auto driver_result = pfnGetProperties( hPsu, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPsuGetPropertiesEpilogue( hPsu, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPsuGetProperties(result, hPsu, pProperties);
        }

        return logAndPropagateResult_zesPsuGetProperties(driver_result, hPsu, pProperties);
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
            return logAndPropagateResult_zesPsuGetState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPsu, pState);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPsuGetStatePrologue( hPsu, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPsuGetState(result, hPsu, pState);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPsuGetStatePrologue( hPsu, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPsuGetState(result, hPsu, pState);
        }

        auto driver_result = pfnGetState( hPsu, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPsuGetStateEpilogue( hPsu, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPsuGetState(result, hPsu, pState);
        }

        return logAndPropagateResult_zesPsuGetState(driver_result, hPsu, pState);
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
            return logAndPropagateResult_zesDeviceEnumRasErrorSets(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phRas);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumRasErrorSetsPrologue( hDevice, pCount, phRas );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumRasErrorSets(result, hDevice, pCount, phRas);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumRasErrorSetsPrologue( hDevice, pCount, phRas );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumRasErrorSets(result, hDevice, pCount, phRas);
        }

        auto driver_result = pfnEnumRasErrorSets( hDevice, pCount, phRas );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumRasErrorSetsEpilogue( hDevice, pCount, phRas ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumRasErrorSets(result, hDevice, pCount, phRas);
        }

        return logAndPropagateResult_zesDeviceEnumRasErrorSets(driver_result, hDevice, pCount, phRas);
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
            return logAndPropagateResult_zesRasGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hRas, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetPropertiesPrologue( hRas, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasGetProperties(result, hRas, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasGetPropertiesPrologue( hRas, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasGetProperties(result, hRas, pProperties);
        }

        auto driver_result = pfnGetProperties( hRas, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetPropertiesEpilogue( hRas, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasGetProperties(result, hRas, pProperties);
        }

        return logAndPropagateResult_zesRasGetProperties(driver_result, hRas, pProperties);
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
            return logAndPropagateResult_zesRasGetConfig(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hRas, pConfig);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetConfigPrologue( hRas, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasGetConfig(result, hRas, pConfig);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasGetConfigPrologue( hRas, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasGetConfig(result, hRas, pConfig);
        }

        auto driver_result = pfnGetConfig( hRas, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetConfigEpilogue( hRas, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasGetConfig(result, hRas, pConfig);
        }

        return logAndPropagateResult_zesRasGetConfig(driver_result, hRas, pConfig);
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
            return logAndPropagateResult_zesRasSetConfig(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hRas, pConfig);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasSetConfigPrologue( hRas, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasSetConfig(result, hRas, pConfig);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasSetConfigPrologue( hRas, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasSetConfig(result, hRas, pConfig);
        }

        auto driver_result = pfnSetConfig( hRas, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasSetConfigEpilogue( hRas, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasSetConfig(result, hRas, pConfig);
        }

        return logAndPropagateResult_zesRasSetConfig(driver_result, hRas, pConfig);
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
            return logAndPropagateResult_zesRasGetState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hRas, clear, pState);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetStatePrologue( hRas, clear, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasGetState(result, hRas, clear, pState);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasGetStatePrologue( hRas, clear, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasGetState(result, hRas, clear, pState);
        }

        auto driver_result = pfnGetState( hRas, clear, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetStateEpilogue( hRas, clear, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasGetState(result, hRas, clear, pState);
        }

        return logAndPropagateResult_zesRasGetState(driver_result, hRas, clear, pState);
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
            return logAndPropagateResult_zesDeviceEnumSchedulers(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phScheduler);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumSchedulersPrologue( hDevice, pCount, phScheduler );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumSchedulers(result, hDevice, pCount, phScheduler);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumSchedulersPrologue( hDevice, pCount, phScheduler );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumSchedulers(result, hDevice, pCount, phScheduler);
        }

        auto driver_result = pfnEnumSchedulers( hDevice, pCount, phScheduler );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumSchedulersEpilogue( hDevice, pCount, phScheduler ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumSchedulers(result, hDevice, pCount, phScheduler);
        }

        return logAndPropagateResult_zesDeviceEnumSchedulers(driver_result, hDevice, pCount, phScheduler);
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
            return logAndPropagateResult_zesSchedulerGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hScheduler, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetPropertiesPrologue( hScheduler, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerGetProperties(result, hScheduler, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerGetPropertiesPrologue( hScheduler, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerGetProperties(result, hScheduler, pProperties);
        }

        auto driver_result = pfnGetProperties( hScheduler, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetPropertiesEpilogue( hScheduler, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerGetProperties(result, hScheduler, pProperties);
        }

        return logAndPropagateResult_zesSchedulerGetProperties(driver_result, hScheduler, pProperties);
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
            return logAndPropagateResult_zesSchedulerGetCurrentMode(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hScheduler, pMode);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetCurrentModePrologue( hScheduler, pMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerGetCurrentMode(result, hScheduler, pMode);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerGetCurrentModePrologue( hScheduler, pMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerGetCurrentMode(result, hScheduler, pMode);
        }

        auto driver_result = pfnGetCurrentMode( hScheduler, pMode );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetCurrentModeEpilogue( hScheduler, pMode ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerGetCurrentMode(result, hScheduler, pMode);
        }

        return logAndPropagateResult_zesSchedulerGetCurrentMode(driver_result, hScheduler, pMode);
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
            return logAndPropagateResult_zesSchedulerGetTimeoutModeProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hScheduler, getDefaults, pConfig);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetTimeoutModePropertiesPrologue( hScheduler, getDefaults, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerGetTimeoutModeProperties(result, hScheduler, getDefaults, pConfig);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerGetTimeoutModePropertiesPrologue( hScheduler, getDefaults, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerGetTimeoutModeProperties(result, hScheduler, getDefaults, pConfig);
        }

        auto driver_result = pfnGetTimeoutModeProperties( hScheduler, getDefaults, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetTimeoutModePropertiesEpilogue( hScheduler, getDefaults, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerGetTimeoutModeProperties(result, hScheduler, getDefaults, pConfig);
        }

        return logAndPropagateResult_zesSchedulerGetTimeoutModeProperties(driver_result, hScheduler, getDefaults, pConfig);
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
            return logAndPropagateResult_zesSchedulerGetTimesliceModeProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hScheduler, getDefaults, pConfig);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetTimesliceModePropertiesPrologue( hScheduler, getDefaults, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerGetTimesliceModeProperties(result, hScheduler, getDefaults, pConfig);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerGetTimesliceModePropertiesPrologue( hScheduler, getDefaults, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerGetTimesliceModeProperties(result, hScheduler, getDefaults, pConfig);
        }

        auto driver_result = pfnGetTimesliceModeProperties( hScheduler, getDefaults, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerGetTimesliceModePropertiesEpilogue( hScheduler, getDefaults, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerGetTimesliceModeProperties(result, hScheduler, getDefaults, pConfig);
        }

        return logAndPropagateResult_zesSchedulerGetTimesliceModeProperties(driver_result, hScheduler, getDefaults, pConfig);
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
            return logAndPropagateResult_zesSchedulerSetTimeoutMode(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hScheduler, pProperties, pNeedReload);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetTimeoutModePrologue( hScheduler, pProperties, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerSetTimeoutMode(result, hScheduler, pProperties, pNeedReload);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerSetTimeoutModePrologue( hScheduler, pProperties, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerSetTimeoutMode(result, hScheduler, pProperties, pNeedReload);
        }

        auto driver_result = pfnSetTimeoutMode( hScheduler, pProperties, pNeedReload );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetTimeoutModeEpilogue( hScheduler, pProperties, pNeedReload ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerSetTimeoutMode(result, hScheduler, pProperties, pNeedReload);
        }

        return logAndPropagateResult_zesSchedulerSetTimeoutMode(driver_result, hScheduler, pProperties, pNeedReload);
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
            return logAndPropagateResult_zesSchedulerSetTimesliceMode(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hScheduler, pProperties, pNeedReload);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetTimesliceModePrologue( hScheduler, pProperties, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerSetTimesliceMode(result, hScheduler, pProperties, pNeedReload);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerSetTimesliceModePrologue( hScheduler, pProperties, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerSetTimesliceMode(result, hScheduler, pProperties, pNeedReload);
        }

        auto driver_result = pfnSetTimesliceMode( hScheduler, pProperties, pNeedReload );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetTimesliceModeEpilogue( hScheduler, pProperties, pNeedReload ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerSetTimesliceMode(result, hScheduler, pProperties, pNeedReload);
        }

        return logAndPropagateResult_zesSchedulerSetTimesliceMode(driver_result, hScheduler, pProperties, pNeedReload);
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
            return logAndPropagateResult_zesSchedulerSetExclusiveMode(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hScheduler, pNeedReload);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetExclusiveModePrologue( hScheduler, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerSetExclusiveMode(result, hScheduler, pNeedReload);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerSetExclusiveModePrologue( hScheduler, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerSetExclusiveMode(result, hScheduler, pNeedReload);
        }

        auto driver_result = pfnSetExclusiveMode( hScheduler, pNeedReload );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetExclusiveModeEpilogue( hScheduler, pNeedReload ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerSetExclusiveMode(result, hScheduler, pNeedReload);
        }

        return logAndPropagateResult_zesSchedulerSetExclusiveMode(driver_result, hScheduler, pNeedReload);
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
            return logAndPropagateResult_zesSchedulerSetComputeUnitDebugMode(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hScheduler, pNeedReload);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetComputeUnitDebugModePrologue( hScheduler, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerSetComputeUnitDebugMode(result, hScheduler, pNeedReload);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesSchedulerSetComputeUnitDebugModePrologue( hScheduler, pNeedReload );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerSetComputeUnitDebugMode(result, hScheduler, pNeedReload);
        }

        auto driver_result = pfnSetComputeUnitDebugMode( hScheduler, pNeedReload );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesSchedulerSetComputeUnitDebugModeEpilogue( hScheduler, pNeedReload ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesSchedulerSetComputeUnitDebugMode(result, hScheduler, pNeedReload);
        }

        return logAndPropagateResult_zesSchedulerSetComputeUnitDebugMode(driver_result, hScheduler, pNeedReload);
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
            return logAndPropagateResult_zesDeviceEnumStandbyDomains(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phStandby);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumStandbyDomainsPrologue( hDevice, pCount, phStandby );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumStandbyDomains(result, hDevice, pCount, phStandby);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumStandbyDomainsPrologue( hDevice, pCount, phStandby );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumStandbyDomains(result, hDevice, pCount, phStandby);
        }

        auto driver_result = pfnEnumStandbyDomains( hDevice, pCount, phStandby );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumStandbyDomainsEpilogue( hDevice, pCount, phStandby ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumStandbyDomains(result, hDevice, pCount, phStandby);
        }

        return logAndPropagateResult_zesDeviceEnumStandbyDomains(driver_result, hDevice, pCount, phStandby);
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
            return logAndPropagateResult_zesStandbyGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hStandby, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesStandbyGetPropertiesPrologue( hStandby, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesStandbyGetProperties(result, hStandby, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesStandbyGetPropertiesPrologue( hStandby, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesStandbyGetProperties(result, hStandby, pProperties);
        }

        auto driver_result = pfnGetProperties( hStandby, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesStandbyGetPropertiesEpilogue( hStandby, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesStandbyGetProperties(result, hStandby, pProperties);
        }

        return logAndPropagateResult_zesStandbyGetProperties(driver_result, hStandby, pProperties);
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
            return logAndPropagateResult_zesStandbyGetMode(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hStandby, pMode);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesStandbyGetModePrologue( hStandby, pMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesStandbyGetMode(result, hStandby, pMode);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesStandbyGetModePrologue( hStandby, pMode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesStandbyGetMode(result, hStandby, pMode);
        }

        auto driver_result = pfnGetMode( hStandby, pMode );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesStandbyGetModeEpilogue( hStandby, pMode ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesStandbyGetMode(result, hStandby, pMode);
        }

        return logAndPropagateResult_zesStandbyGetMode(driver_result, hStandby, pMode);
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
            return logAndPropagateResult_zesStandbySetMode(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hStandby, mode);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesStandbySetModePrologue( hStandby, mode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesStandbySetMode(result, hStandby, mode);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesStandbySetModePrologue( hStandby, mode );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesStandbySetMode(result, hStandby, mode);
        }

        auto driver_result = pfnSetMode( hStandby, mode );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesStandbySetModeEpilogue( hStandby, mode ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesStandbySetMode(result, hStandby, mode);
        }

        return logAndPropagateResult_zesStandbySetMode(driver_result, hStandby, mode);
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
            return logAndPropagateResult_zesDeviceEnumTemperatureSensors(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phTemperature);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumTemperatureSensorsPrologue( hDevice, pCount, phTemperature );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumTemperatureSensors(result, hDevice, pCount, phTemperature);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumTemperatureSensorsPrologue( hDevice, pCount, phTemperature );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumTemperatureSensors(result, hDevice, pCount, phTemperature);
        }

        auto driver_result = pfnEnumTemperatureSensors( hDevice, pCount, phTemperature );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumTemperatureSensorsEpilogue( hDevice, pCount, phTemperature ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumTemperatureSensors(result, hDevice, pCount, phTemperature);
        }

        return logAndPropagateResult_zesDeviceEnumTemperatureSensors(driver_result, hDevice, pCount, phTemperature);
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
            return logAndPropagateResult_zesTemperatureGetProperties(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hTemperature, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureGetPropertiesPrologue( hTemperature, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesTemperatureGetProperties(result, hTemperature, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesTemperatureGetPropertiesPrologue( hTemperature, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesTemperatureGetProperties(result, hTemperature, pProperties);
        }

        auto driver_result = pfnGetProperties( hTemperature, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureGetPropertiesEpilogue( hTemperature, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesTemperatureGetProperties(result, hTemperature, pProperties);
        }

        return logAndPropagateResult_zesTemperatureGetProperties(driver_result, hTemperature, pProperties);
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
            return logAndPropagateResult_zesTemperatureGetConfig(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hTemperature, pConfig);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureGetConfigPrologue( hTemperature, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesTemperatureGetConfig(result, hTemperature, pConfig);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesTemperatureGetConfigPrologue( hTemperature, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesTemperatureGetConfig(result, hTemperature, pConfig);
        }

        auto driver_result = pfnGetConfig( hTemperature, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureGetConfigEpilogue( hTemperature, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesTemperatureGetConfig(result, hTemperature, pConfig);
        }

        return logAndPropagateResult_zesTemperatureGetConfig(driver_result, hTemperature, pConfig);
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
            return logAndPropagateResult_zesTemperatureSetConfig(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hTemperature, pConfig);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureSetConfigPrologue( hTemperature, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesTemperatureSetConfig(result, hTemperature, pConfig);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesTemperatureSetConfigPrologue( hTemperature, pConfig );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesTemperatureSetConfig(result, hTemperature, pConfig);
        }

        auto driver_result = pfnSetConfig( hTemperature, pConfig );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureSetConfigEpilogue( hTemperature, pConfig ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesTemperatureSetConfig(result, hTemperature, pConfig);
        }

        return logAndPropagateResult_zesTemperatureSetConfig(driver_result, hTemperature, pConfig);
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
            return logAndPropagateResult_zesTemperatureGetState(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hTemperature, pTemperature);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureGetStatePrologue( hTemperature, pTemperature );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesTemperatureGetState(result, hTemperature, pTemperature);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesTemperatureGetStatePrologue( hTemperature, pTemperature );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesTemperatureGetState(result, hTemperature, pTemperature);
        }

        auto driver_result = pfnGetState( hTemperature, pTemperature );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesTemperatureGetStateEpilogue( hTemperature, pTemperature ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesTemperatureGetState(result, hTemperature, pTemperature);
        }

        return logAndPropagateResult_zesTemperatureGetState(driver_result, hTemperature, pTemperature);
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Intercept function for zesDevicePciLinkSpeedUpdateExt
    __zedlllocal ze_result_t ZE_APICALL
    zesDevicePciLinkSpeedUpdateExt(
        zes_device_handle_t hDevice,                    ///< [in] Sysman handle of the device.
        ze_bool_t shouldDowngrade,                      ///< [in] boolean value to decide whether to perform PCIe downgrade(true)
                                                        ///< or set to default speed(false)
        zes_device_action_t* pendingAction              ///< [out] Pending action
        )
    {
        context.logger->log_trace("zesDevicePciLinkSpeedUpdateExt(hDevice, shouldDowngrade, pendingAction)");

        auto pfnPciLinkSpeedUpdateExt = context.zesDdiTable.Device.pfnPciLinkSpeedUpdateExt;

        if( nullptr == pfnPciLinkSpeedUpdateExt )
            return logAndPropagateResult_zesDevicePciLinkSpeedUpdateExt(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, shouldDowngrade, pendingAction);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciLinkSpeedUpdateExtPrologue( hDevice, shouldDowngrade, pendingAction );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDevicePciLinkSpeedUpdateExt(result, hDevice, shouldDowngrade, pendingAction);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDevicePciLinkSpeedUpdateExtPrologue( hDevice, shouldDowngrade, pendingAction );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDevicePciLinkSpeedUpdateExt(result, hDevice, shouldDowngrade, pendingAction);
        }

        auto driver_result = pfnPciLinkSpeedUpdateExt( hDevice, shouldDowngrade, pendingAction );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDevicePciLinkSpeedUpdateExtEpilogue( hDevice, shouldDowngrade, pendingAction ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDevicePciLinkSpeedUpdateExt(result, hDevice, shouldDowngrade, pendingAction);
        }

        return logAndPropagateResult_zesDevicePciLinkSpeedUpdateExt(driver_result, hDevice, shouldDowngrade, pendingAction);
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
            return logAndPropagateResult_zesPowerGetLimitsExt(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPower, pCount, pSustained);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetLimitsExtPrologue( hPower, pCount, pSustained );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerGetLimitsExt(result, hPower, pCount, pSustained);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerGetLimitsExtPrologue( hPower, pCount, pSustained );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerGetLimitsExt(result, hPower, pCount, pSustained);
        }

        auto driver_result = pfnGetLimitsExt( hPower, pCount, pSustained );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerGetLimitsExtEpilogue( hPower, pCount, pSustained ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerGetLimitsExt(result, hPower, pCount, pSustained);
        }

        return logAndPropagateResult_zesPowerGetLimitsExt(driver_result, hPower, pCount, pSustained);
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
            return logAndPropagateResult_zesPowerSetLimitsExt(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hPower, pCount, pSustained);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerSetLimitsExtPrologue( hPower, pCount, pSustained );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerSetLimitsExt(result, hPower, pCount, pSustained);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesPowerSetLimitsExtPrologue( hPower, pCount, pSustained );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerSetLimitsExt(result, hPower, pCount, pSustained);
        }

        auto driver_result = pfnSetLimitsExt( hPower, pCount, pSustained );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesPowerSetLimitsExtEpilogue( hPower, pCount, pSustained ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesPowerSetLimitsExt(result, hPower, pCount, pSustained);
        }

        return logAndPropagateResult_zesPowerSetLimitsExt(driver_result, hPower, pCount, pSustained);
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
            return logAndPropagateResult_zesEngineGetActivityExt(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hEngine, pCount, pStats);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesEngineGetActivityExtPrologue( hEngine, pCount, pStats );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesEngineGetActivityExt(result, hEngine, pCount, pStats);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesEngineGetActivityExtPrologue( hEngine, pCount, pStats );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesEngineGetActivityExt(result, hEngine, pCount, pStats);
        }

        auto driver_result = pfnGetActivityExt( hEngine, pCount, pStats );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesEngineGetActivityExtEpilogue( hEngine, pCount, pStats ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesEngineGetActivityExt(result, hEngine, pCount, pStats);
        }

        return logAndPropagateResult_zesEngineGetActivityExt(driver_result, hEngine, pCount, pStats);
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
            return logAndPropagateResult_zesRasGetStateExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hRas, pCount, pState);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetStateExpPrologue( hRas, pCount, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasGetStateExp(result, hRas, pCount, pState);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasGetStateExpPrologue( hRas, pCount, pState );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasGetStateExp(result, hRas, pCount, pState);
        }

        auto driver_result = pfnGetStateExp( hRas, pCount, pState );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasGetStateExpEpilogue( hRas, pCount, pState ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasGetStateExp(result, hRas, pCount, pState);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult_zesRasGetStateExp(driver_result, hRas, pCount, pState);
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
            return logAndPropagateResult_zesRasClearStateExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hRas, category);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasClearStateExpPrologue( hRas, category );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasClearStateExp(result, hRas, category);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesRasClearStateExpPrologue( hRas, category );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasClearStateExp(result, hRas, category);
        }

        auto driver_result = pfnClearStateExp( hRas, category );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesRasClearStateExpEpilogue( hRas, category ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesRasClearStateExp(result, hRas, category);
        }

        return logAndPropagateResult_zesRasClearStateExp(driver_result, hRas, category);
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
            return logAndPropagateResult_zesFirmwareGetSecurityVersionExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFirmware, pVersion);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetSecurityVersionExpPrologue( hFirmware, pVersion );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareGetSecurityVersionExp(result, hFirmware, pVersion);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFirmwareGetSecurityVersionExpPrologue( hFirmware, pVersion );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareGetSecurityVersionExp(result, hFirmware, pVersion);
        }

        auto driver_result = pfnGetSecurityVersionExp( hFirmware, pVersion );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareGetSecurityVersionExpEpilogue( hFirmware, pVersion ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareGetSecurityVersionExp(result, hFirmware, pVersion);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult_zesFirmwareGetSecurityVersionExp(driver_result, hFirmware, pVersion);
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
            return logAndPropagateResult_zesFirmwareSetSecurityVersionExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hFirmware);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareSetSecurityVersionExpPrologue( hFirmware );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareSetSecurityVersionExp(result, hFirmware);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesFirmwareSetSecurityVersionExpPrologue( hFirmware );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareSetSecurityVersionExp(result, hFirmware);
        }

        auto driver_result = pfnSetSecurityVersionExp( hFirmware );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesFirmwareSetSecurityVersionExpEpilogue( hFirmware ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesFirmwareSetSecurityVersionExp(result, hFirmware);
        }

        return logAndPropagateResult_zesFirmwareSetSecurityVersionExp(driver_result, hFirmware);
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
            return logAndPropagateResult_zesDeviceGetSubDevicePropertiesExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, pSubdeviceProps);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetSubDevicePropertiesExpPrologue( hDevice, pCount, pSubdeviceProps );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetSubDevicePropertiesExp(result, hDevice, pCount, pSubdeviceProps);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceGetSubDevicePropertiesExpPrologue( hDevice, pCount, pSubdeviceProps );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetSubDevicePropertiesExp(result, hDevice, pCount, pSubdeviceProps);
        }

        auto driver_result = pfnGetSubDevicePropertiesExp( hDevice, pCount, pSubdeviceProps );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceGetSubDevicePropertiesExpEpilogue( hDevice, pCount, pSubdeviceProps ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceGetSubDevicePropertiesExp(result, hDevice, pCount, pSubdeviceProps);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult_zesDeviceGetSubDevicePropertiesExp(driver_result, hDevice, pCount, pSubdeviceProps);
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
            return logAndPropagateResult_zesDriverGetDeviceByUuidExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDriver, uuid, phDevice, onSubdevice, subdeviceId);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetDeviceByUuidExpPrologue( hDriver, uuid, phDevice, onSubdevice, subdeviceId );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverGetDeviceByUuidExp(result, hDriver, uuid, phDevice, onSubdevice, subdeviceId);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDriverGetDeviceByUuidExpPrologue( hDriver, uuid, phDevice, onSubdevice, subdeviceId );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverGetDeviceByUuidExp(result, hDriver, uuid, phDevice, onSubdevice, subdeviceId);
        }

        auto driver_result = pfnGetDeviceByUuidExp( hDriver, uuid, phDevice, onSubdevice, subdeviceId );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDriverGetDeviceByUuidExpEpilogue( hDriver, uuid, phDevice, onSubdevice, subdeviceId ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDriverGetDeviceByUuidExp(result, hDriver, uuid, phDevice, onSubdevice, subdeviceId);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
            if (phDevice){
                context.handleLifetime->addHandle( *phDevice );
                context.handleLifetime->addDependent( hDriver, *phDevice );

            }
        }
        return logAndPropagateResult_zesDriverGetDeviceByUuidExp(driver_result, hDriver, uuid, phDevice, onSubdevice, subdeviceId);
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
            return logAndPropagateResult_zesDeviceEnumActiveVFExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phVFhandle);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumActiveVFExpPrologue( hDevice, pCount, phVFhandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumActiveVFExp(result, hDevice, pCount, phVFhandle);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumActiveVFExpPrologue( hDevice, pCount, phVFhandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumActiveVFExp(result, hDevice, pCount, phVFhandle);
        }

        auto driver_result = pfnEnumActiveVFExp( hDevice, pCount, phVFhandle );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumActiveVFExpEpilogue( hDevice, pCount, phVFhandle ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumActiveVFExp(result, hDevice, pCount, phVFhandle);
        }

        return logAndPropagateResult_zesDeviceEnumActiveVFExp(driver_result, hDevice, pCount, phVFhandle);
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
            return logAndPropagateResult_zesVFManagementGetVFPropertiesExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hVFhandle, pProperties);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFPropertiesExpPrologue( hVFhandle, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFPropertiesExp(result, hVFhandle, pProperties);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementGetVFPropertiesExpPrologue( hVFhandle, pProperties );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFPropertiesExp(result, hVFhandle, pProperties);
        }

        auto driver_result = pfnGetVFPropertiesExp( hVFhandle, pProperties );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFPropertiesExpEpilogue( hVFhandle, pProperties ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFPropertiesExp(result, hVFhandle, pProperties);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult_zesVFManagementGetVFPropertiesExp(driver_result, hVFhandle, pProperties);
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
            return logAndPropagateResult_zesVFManagementGetVFMemoryUtilizationExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hVFhandle, pCount, pMemUtil);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFMemoryUtilizationExpPrologue( hVFhandle, pCount, pMemUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFMemoryUtilizationExp(result, hVFhandle, pCount, pMemUtil);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementGetVFMemoryUtilizationExpPrologue( hVFhandle, pCount, pMemUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFMemoryUtilizationExp(result, hVFhandle, pCount, pMemUtil);
        }

        auto driver_result = pfnGetVFMemoryUtilizationExp( hVFhandle, pCount, pMemUtil );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFMemoryUtilizationExpEpilogue( hVFhandle, pCount, pMemUtil ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFMemoryUtilizationExp(result, hVFhandle, pCount, pMemUtil);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult_zesVFManagementGetVFMemoryUtilizationExp(driver_result, hVFhandle, pCount, pMemUtil);
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
            return logAndPropagateResult_zesVFManagementGetVFEngineUtilizationExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hVFhandle, pCount, pEngineUtil);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFEngineUtilizationExpPrologue( hVFhandle, pCount, pEngineUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFEngineUtilizationExp(result, hVFhandle, pCount, pEngineUtil);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementGetVFEngineUtilizationExpPrologue( hVFhandle, pCount, pEngineUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFEngineUtilizationExp(result, hVFhandle, pCount, pEngineUtil);
        }

        auto driver_result = pfnGetVFEngineUtilizationExp( hVFhandle, pCount, pEngineUtil );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFEngineUtilizationExpEpilogue( hVFhandle, pCount, pEngineUtil ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFEngineUtilizationExp(result, hVFhandle, pCount, pEngineUtil);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult_zesVFManagementGetVFEngineUtilizationExp(driver_result, hVFhandle, pCount, pEngineUtil);
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
            return logAndPropagateResult_zesVFManagementSetVFTelemetryModeExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hVFhandle, flags, enable);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementSetVFTelemetryModeExpPrologue( hVFhandle, flags, enable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementSetVFTelemetryModeExp(result, hVFhandle, flags, enable);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementSetVFTelemetryModeExpPrologue( hVFhandle, flags, enable );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementSetVFTelemetryModeExp(result, hVFhandle, flags, enable);
        }

        auto driver_result = pfnSetVFTelemetryModeExp( hVFhandle, flags, enable );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementSetVFTelemetryModeExpEpilogue( hVFhandle, flags, enable ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementSetVFTelemetryModeExp(result, hVFhandle, flags, enable);
        }

        return logAndPropagateResult_zesVFManagementSetVFTelemetryModeExp(driver_result, hVFhandle, flags, enable);
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
            return logAndPropagateResult_zesVFManagementSetVFTelemetrySamplingIntervalExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hVFhandle, flag, samplingInterval);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementSetVFTelemetrySamplingIntervalExpPrologue( hVFhandle, flag, samplingInterval );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementSetVFTelemetrySamplingIntervalExp(result, hVFhandle, flag, samplingInterval);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementSetVFTelemetrySamplingIntervalExpPrologue( hVFhandle, flag, samplingInterval );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementSetVFTelemetrySamplingIntervalExp(result, hVFhandle, flag, samplingInterval);
        }

        auto driver_result = pfnSetVFTelemetrySamplingIntervalExp( hVFhandle, flag, samplingInterval );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementSetVFTelemetrySamplingIntervalExpEpilogue( hVFhandle, flag, samplingInterval ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementSetVFTelemetrySamplingIntervalExp(result, hVFhandle, flag, samplingInterval);
        }

        return logAndPropagateResult_zesVFManagementSetVFTelemetrySamplingIntervalExp(driver_result, hVFhandle, flag, samplingInterval);
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
            return logAndPropagateResult_zesDeviceEnumEnabledVFExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hDevice, pCount, phVFhandle);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumEnabledVFExpPrologue( hDevice, pCount, phVFhandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumEnabledVFExp(result, hDevice, pCount, phVFhandle);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesDeviceEnumEnabledVFExpPrologue( hDevice, pCount, phVFhandle );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumEnabledVFExp(result, hDevice, pCount, phVFhandle);
        }

        auto driver_result = pfnEnumEnabledVFExp( hDevice, pCount, phVFhandle );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesDeviceEnumEnabledVFExpEpilogue( hDevice, pCount, phVFhandle ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesDeviceEnumEnabledVFExp(result, hDevice, pCount, phVFhandle);
        }

        return logAndPropagateResult_zesDeviceEnumEnabledVFExp(driver_result, hDevice, pCount, phVFhandle);
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
            return logAndPropagateResult_zesVFManagementGetVFCapabilitiesExp(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hVFhandle, pCapability);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFCapabilitiesExpPrologue( hVFhandle, pCapability );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFCapabilitiesExp(result, hVFhandle, pCapability);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementGetVFCapabilitiesExpPrologue( hVFhandle, pCapability );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFCapabilitiesExp(result, hVFhandle, pCapability);
        }

        auto driver_result = pfnGetVFCapabilitiesExp( hVFhandle, pCapability );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFCapabilitiesExpEpilogue( hVFhandle, pCapability ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFCapabilitiesExp(result, hVFhandle, pCapability);
        }


        if( driver_result == ZE_RESULT_SUCCESS && context.enableHandleLifetime ){
            
        }
        return logAndPropagateResult_zesVFManagementGetVFCapabilitiesExp(driver_result, hVFhandle, pCapability);
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
            return logAndPropagateResult_zesVFManagementGetVFMemoryUtilizationExp2(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hVFhandle, pCount, pMemUtil);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFMemoryUtilizationExp2Prologue( hVFhandle, pCount, pMemUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFMemoryUtilizationExp2(result, hVFhandle, pCount, pMemUtil);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementGetVFMemoryUtilizationExp2Prologue( hVFhandle, pCount, pMemUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFMemoryUtilizationExp2(result, hVFhandle, pCount, pMemUtil);
        }

        auto driver_result = pfnGetVFMemoryUtilizationExp2( hVFhandle, pCount, pMemUtil );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFMemoryUtilizationExp2Epilogue( hVFhandle, pCount, pMemUtil ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFMemoryUtilizationExp2(result, hVFhandle, pCount, pMemUtil);
        }

        return logAndPropagateResult_zesVFManagementGetVFMemoryUtilizationExp2(driver_result, hVFhandle, pCount, pMemUtil);
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
            return logAndPropagateResult_zesVFManagementGetVFEngineUtilizationExp2(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hVFhandle, pCount, pEngineUtil);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFEngineUtilizationExp2Prologue( hVFhandle, pCount, pEngineUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFEngineUtilizationExp2(result, hVFhandle, pCount, pEngineUtil);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementGetVFEngineUtilizationExp2Prologue( hVFhandle, pCount, pEngineUtil );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFEngineUtilizationExp2(result, hVFhandle, pCount, pEngineUtil);
        }

        auto driver_result = pfnGetVFEngineUtilizationExp2( hVFhandle, pCount, pEngineUtil );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFEngineUtilizationExp2Epilogue( hVFhandle, pCount, pEngineUtil ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFEngineUtilizationExp2(result, hVFhandle, pCount, pEngineUtil);
        }

        return logAndPropagateResult_zesVFManagementGetVFEngineUtilizationExp2(driver_result, hVFhandle, pCount, pEngineUtil);
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
            return logAndPropagateResult_zesVFManagementGetVFCapabilitiesExp2(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, hVFhandle, pCapability);

        auto numValHandlers = context.validationHandlers.size();
        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFCapabilitiesExp2Prologue( hVFhandle, pCapability );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFCapabilitiesExp2(result, hVFhandle, pCapability);
        }


        if( context.enableThreadingValidation ){ 
            //Unimplemented
        }

        
        if(context.enableHandleLifetime ){
            auto result = context.handleLifetime->zesHandleLifetime.zesVFManagementGetVFCapabilitiesExp2Prologue( hVFhandle, pCapability );
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFCapabilitiesExp2(result, hVFhandle, pCapability);
        }

        auto driver_result = pfnGetVFCapabilitiesExp2( hVFhandle, pCapability );

        for (size_t i = 0; i < numValHandlers; i++) {
            auto result = context.validationHandlers[i]->zesValidation->zesVFManagementGetVFCapabilitiesExp2Epilogue( hVFhandle, pCapability ,driver_result);
            if(result!=ZE_RESULT_SUCCESS) return logAndPropagateResult_zesVFManagementGetVFCapabilitiesExp2(result, hVFhandle, pCapability);
        }

        return logAndPropagateResult_zesVFManagementGetVFCapabilitiesExp2(driver_result, hVFhandle, pCapability);
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnInit                                     = pDdiTable->pfnInit;
        pDdiTable->pfnInit                                   = validation_layer::zesInit;
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
zesGetDeviceProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_device_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Device;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesDeviceGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetState                                 = pDdiTable->pfnGetState;
        pDdiTable->pfnGetState                               = validation_layer::zesDeviceGetState;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnReset                                    = pDdiTable->pfnReset;
        pDdiTable->pfnReset                                  = validation_layer::zesDeviceReset;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnProcessesGetState                        = pDdiTable->pfnProcessesGetState;
        pDdiTable->pfnProcessesGetState                      = validation_layer::zesDeviceProcessesGetState;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnPciGetProperties                         = pDdiTable->pfnPciGetProperties;
        pDdiTable->pfnPciGetProperties                       = validation_layer::zesDevicePciGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnPciGetState                              = pDdiTable->pfnPciGetState;
        pDdiTable->pfnPciGetState                            = validation_layer::zesDevicePciGetState;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnPciGetBars                               = pDdiTable->pfnPciGetBars;
        pDdiTable->pfnPciGetBars                             = validation_layer::zesDevicePciGetBars;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnPciGetStats                              = pDdiTable->pfnPciGetStats;
        pDdiTable->pfnPciGetStats                            = validation_layer::zesDevicePciGetStats;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEnumDiagnosticTestSuites                 = pDdiTable->pfnEnumDiagnosticTestSuites;
        pDdiTable->pfnEnumDiagnosticTestSuites               = validation_layer::zesDeviceEnumDiagnosticTestSuites;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEnumEngineGroups                         = pDdiTable->pfnEnumEngineGroups;
        pDdiTable->pfnEnumEngineGroups                       = validation_layer::zesDeviceEnumEngineGroups;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEventRegister                            = pDdiTable->pfnEventRegister;
        pDdiTable->pfnEventRegister                          = validation_layer::zesDeviceEventRegister;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEnumFabricPorts                          = pDdiTable->pfnEnumFabricPorts;
        pDdiTable->pfnEnumFabricPorts                        = validation_layer::zesDeviceEnumFabricPorts;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEnumFans                                 = pDdiTable->pfnEnumFans;
        pDdiTable->pfnEnumFans                               = validation_layer::zesDeviceEnumFans;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEnumFirmwares                            = pDdiTable->pfnEnumFirmwares;
        pDdiTable->pfnEnumFirmwares                          = validation_layer::zesDeviceEnumFirmwares;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEnumFrequencyDomains                     = pDdiTable->pfnEnumFrequencyDomains;
        pDdiTable->pfnEnumFrequencyDomains                   = validation_layer::zesDeviceEnumFrequencyDomains;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEnumLeds                                 = pDdiTable->pfnEnumLeds;
        pDdiTable->pfnEnumLeds                               = validation_layer::zesDeviceEnumLeds;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEnumMemoryModules                        = pDdiTable->pfnEnumMemoryModules;
        pDdiTable->pfnEnumMemoryModules                      = validation_layer::zesDeviceEnumMemoryModules;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEnumPerformanceFactorDomains             = pDdiTable->pfnEnumPerformanceFactorDomains;
        pDdiTable->pfnEnumPerformanceFactorDomains           = validation_layer::zesDeviceEnumPerformanceFactorDomains;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEnumPowerDomains                         = pDdiTable->pfnEnumPowerDomains;
        pDdiTable->pfnEnumPowerDomains                       = validation_layer::zesDeviceEnumPowerDomains;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetCardPowerDomain                       = pDdiTable->pfnGetCardPowerDomain;
        pDdiTable->pfnGetCardPowerDomain                     = validation_layer::zesDeviceGetCardPowerDomain;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEnumPsus                                 = pDdiTable->pfnEnumPsus;
        pDdiTable->pfnEnumPsus                               = validation_layer::zesDeviceEnumPsus;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEnumRasErrorSets                         = pDdiTable->pfnEnumRasErrorSets;
        pDdiTable->pfnEnumRasErrorSets                       = validation_layer::zesDeviceEnumRasErrorSets;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEnumSchedulers                           = pDdiTable->pfnEnumSchedulers;
        pDdiTable->pfnEnumSchedulers                         = validation_layer::zesDeviceEnumSchedulers;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEnumStandbyDomains                       = pDdiTable->pfnEnumStandbyDomains;
        pDdiTable->pfnEnumStandbyDomains                     = validation_layer::zesDeviceEnumStandbyDomains;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEnumTemperatureSensors                   = pDdiTable->pfnEnumTemperatureSensors;
        pDdiTable->pfnEnumTemperatureSensors                 = validation_layer::zesDeviceEnumTemperatureSensors;
    }
    if (version >= ZE_API_VERSION_1_15) {
        dditable.pfnPciLinkSpeedUpdateExt                    = pDdiTable->pfnPciLinkSpeedUpdateExt;
        pDdiTable->pfnPciLinkSpeedUpdateExt                  = validation_layer::zesDevicePciLinkSpeedUpdateExt;
    }
    if (version >= ZE_API_VERSION_1_4) {
        dditable.pfnEccAvailable                             = pDdiTable->pfnEccAvailable;
        pDdiTable->pfnEccAvailable                           = validation_layer::zesDeviceEccAvailable;
    }
    if (version >= ZE_API_VERSION_1_4) {
        dditable.pfnEccConfigurable                          = pDdiTable->pfnEccConfigurable;
        pDdiTable->pfnEccConfigurable                        = validation_layer::zesDeviceEccConfigurable;
    }
    if (version >= ZE_API_VERSION_1_4) {
        dditable.pfnGetEccState                              = pDdiTable->pfnGetEccState;
        pDdiTable->pfnGetEccState                            = validation_layer::zesDeviceGetEccState;
    }
    if (version >= ZE_API_VERSION_1_4) {
        dditable.pfnSetEccState                              = pDdiTable->pfnSetEccState;
        pDdiTable->pfnSetEccState                            = validation_layer::zesDeviceSetEccState;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnGet                                      = pDdiTable->pfnGet;
        pDdiTable->pfnGet                                    = validation_layer::zesDeviceGet;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnSetOverclockWaiver                       = pDdiTable->pfnSetOverclockWaiver;
        pDdiTable->pfnSetOverclockWaiver                     = validation_layer::zesDeviceSetOverclockWaiver;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnGetOverclockDomains                      = pDdiTable->pfnGetOverclockDomains;
        pDdiTable->pfnGetOverclockDomains                    = validation_layer::zesDeviceGetOverclockDomains;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnGetOverclockControls                     = pDdiTable->pfnGetOverclockControls;
        pDdiTable->pfnGetOverclockControls                   = validation_layer::zesDeviceGetOverclockControls;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnResetOverclockSettings                   = pDdiTable->pfnResetOverclockSettings;
        pDdiTable->pfnResetOverclockSettings                 = validation_layer::zesDeviceResetOverclockSettings;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnReadOverclockState                       = pDdiTable->pfnReadOverclockState;
        pDdiTable->pfnReadOverclockState                     = validation_layer::zesDeviceReadOverclockState;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnEnumOverclockDomains                     = pDdiTable->pfnEnumOverclockDomains;
        pDdiTable->pfnEnumOverclockDomains                   = validation_layer::zesDeviceEnumOverclockDomains;
    }
    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnResetExt                                 = pDdiTable->pfnResetExt;
        pDdiTable->pfnResetExt                               = validation_layer::zesDeviceResetExt;
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
zesGetDeviceExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_device_exp_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.DeviceExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnEnumEnabledVFExp                         = pDdiTable->pfnEnumEnabledVFExp;
        pDdiTable->pfnEnumEnabledVFExp                       = validation_layer::zesDeviceEnumEnabledVFExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetSubDevicePropertiesExp                = pDdiTable->pfnGetSubDevicePropertiesExp;
        pDdiTable->pfnGetSubDevicePropertiesExp              = validation_layer::zesDeviceGetSubDevicePropertiesExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnEnumActiveVFExp                          = pDdiTable->pfnEnumActiveVFExp;
        pDdiTable->pfnEnumActiveVFExp                        = validation_layer::zesDeviceEnumActiveVFExp;
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
zesGetDriverProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_driver_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.Driver;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnEventListen                              = pDdiTable->pfnEventListen;
        pDdiTable->pfnEventListen                            = validation_layer::zesDriverEventListen;
    }
    if (version >= ZE_API_VERSION_1_1) {
        dditable.pfnEventListenEx                            = pDdiTable->pfnEventListenEx;
        pDdiTable->pfnEventListenEx                          = validation_layer::zesDriverEventListenEx;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnGet                                      = pDdiTable->pfnGet;
        pDdiTable->pfnGet                                    = validation_layer::zesDriverGet;
    }
    if (version >= ZE_API_VERSION_1_8) {
        dditable.pfnGetExtensionProperties                   = pDdiTable->pfnGetExtensionProperties;
        pDdiTable->pfnGetExtensionProperties                 = validation_layer::zesDriverGetExtensionProperties;
    }
    if (version >= ZE_API_VERSION_1_8) {
        dditable.pfnGetExtensionFunctionAddress              = pDdiTable->pfnGetExtensionFunctionAddress;
        pDdiTable->pfnGetExtensionFunctionAddress            = validation_layer::zesDriverGetExtensionFunctionAddress;
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
zesGetDriverExpProcAddrTable(
    ze_api_version_t version,                       ///< [in] API version requested
    zes_driver_exp_dditable_t* pDdiTable            ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = validation_layer::context.zesDdiTable.DriverExp;

    if( nullptr == pDdiTable )
        return ZE_RESULT_ERROR_INVALID_NULL_POINTER;

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetDeviceByUuidExp                       = pDdiTable->pfnGetDeviceByUuidExp;
        pDdiTable->pfnGetDeviceByUuidExp                     = validation_layer::zesDriverGetDeviceByUuidExp;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesDiagnosticsGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetTests                                 = pDdiTable->pfnGetTests;
        pDdiTable->pfnGetTests                               = validation_layer::zesDiagnosticsGetTests;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnRunTests                                 = pDdiTable->pfnRunTests;
        pDdiTable->pfnRunTests                               = validation_layer::zesDiagnosticsRunTests;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesEngineGetProperties;
    }
    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnGetActivity                              = pDdiTable->pfnGetActivity;
        pDdiTable->pfnGetActivity                            = validation_layer::zesEngineGetActivity;
    }
    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnGetActivityExt                           = pDdiTable->pfnGetActivityExt;
        pDdiTable->pfnGetActivityExt                         = validation_layer::zesEngineGetActivityExt;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesFabricPortGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetLinkType                              = pDdiTable->pfnGetLinkType;
        pDdiTable->pfnGetLinkType                            = validation_layer::zesFabricPortGetLinkType;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
        pDdiTable->pfnGetConfig                              = validation_layer::zesFabricPortGetConfig;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
        pDdiTable->pfnSetConfig                              = validation_layer::zesFabricPortSetConfig;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetState                                 = pDdiTable->pfnGetState;
        pDdiTable->pfnGetState                               = validation_layer::zesFabricPortGetState;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetThroughput                            = pDdiTable->pfnGetThroughput;
        pDdiTable->pfnGetThroughput                          = validation_layer::zesFabricPortGetThroughput;
    }
    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnGetFabricErrorCounters                   = pDdiTable->pfnGetFabricErrorCounters;
        pDdiTable->pfnGetFabricErrorCounters                 = validation_layer::zesFabricPortGetFabricErrorCounters;
    }
    if (version >= ZE_API_VERSION_1_7) {
        dditable.pfnGetMultiPortThroughput                   = pDdiTable->pfnGetMultiPortThroughput;
        pDdiTable->pfnGetMultiPortThroughput                 = validation_layer::zesFabricPortGetMultiPortThroughput;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesFanGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
        pDdiTable->pfnGetConfig                              = validation_layer::zesFanGetConfig;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetDefaultMode                           = pDdiTable->pfnSetDefaultMode;
        pDdiTable->pfnSetDefaultMode                         = validation_layer::zesFanSetDefaultMode;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetFixedSpeedMode                        = pDdiTable->pfnSetFixedSpeedMode;
        pDdiTable->pfnSetFixedSpeedMode                      = validation_layer::zesFanSetFixedSpeedMode;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetSpeedTableMode                        = pDdiTable->pfnSetSpeedTableMode;
        pDdiTable->pfnSetSpeedTableMode                      = validation_layer::zesFanSetSpeedTableMode;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetState                                 = pDdiTable->pfnGetState;
        pDdiTable->pfnGetState                               = validation_layer::zesFanGetState;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesFirmwareGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnFlash                                    = pDdiTable->pfnFlash;
        pDdiTable->pfnFlash                                  = validation_layer::zesFirmwareFlash;
    }
    if (version >= ZE_API_VERSION_1_8) {
        dditable.pfnGetFlashProgress                         = pDdiTable->pfnGetFlashProgress;
        pDdiTable->pfnGetFlashProgress                       = validation_layer::zesFirmwareGetFlashProgress;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetConsoleLogs                           = pDdiTable->pfnGetConsoleLogs;
        pDdiTable->pfnGetConsoleLogs                         = validation_layer::zesFirmwareGetConsoleLogs;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetSecurityVersionExp                    = pDdiTable->pfnGetSecurityVersionExp;
        pDdiTable->pfnGetSecurityVersionExp                  = validation_layer::zesFirmwareGetSecurityVersionExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnSetSecurityVersionExp                    = pDdiTable->pfnSetSecurityVersionExp;
        pDdiTable->pfnSetSecurityVersionExp                  = validation_layer::zesFirmwareSetSecurityVersionExp;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesFrequencyGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetAvailableClocks                       = pDdiTable->pfnGetAvailableClocks;
        pDdiTable->pfnGetAvailableClocks                     = validation_layer::zesFrequencyGetAvailableClocks;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetRange                                 = pDdiTable->pfnGetRange;
        pDdiTable->pfnGetRange                               = validation_layer::zesFrequencyGetRange;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetRange                                 = pDdiTable->pfnSetRange;
        pDdiTable->pfnSetRange                               = validation_layer::zesFrequencySetRange;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetState                                 = pDdiTable->pfnGetState;
        pDdiTable->pfnGetState                               = validation_layer::zesFrequencyGetState;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetThrottleTime                          = pDdiTable->pfnGetThrottleTime;
        pDdiTable->pfnGetThrottleTime                        = validation_layer::zesFrequencyGetThrottleTime;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnOcGetCapabilities                        = pDdiTable->pfnOcGetCapabilities;
        pDdiTable->pfnOcGetCapabilities                      = validation_layer::zesFrequencyOcGetCapabilities;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnOcGetFrequencyTarget                     = pDdiTable->pfnOcGetFrequencyTarget;
        pDdiTable->pfnOcGetFrequencyTarget                   = validation_layer::zesFrequencyOcGetFrequencyTarget;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnOcSetFrequencyTarget                     = pDdiTable->pfnOcSetFrequencyTarget;
        pDdiTable->pfnOcSetFrequencyTarget                   = validation_layer::zesFrequencyOcSetFrequencyTarget;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnOcGetVoltageTarget                       = pDdiTable->pfnOcGetVoltageTarget;
        pDdiTable->pfnOcGetVoltageTarget                     = validation_layer::zesFrequencyOcGetVoltageTarget;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnOcSetVoltageTarget                       = pDdiTable->pfnOcSetVoltageTarget;
        pDdiTable->pfnOcSetVoltageTarget                     = validation_layer::zesFrequencyOcSetVoltageTarget;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnOcSetMode                                = pDdiTable->pfnOcSetMode;
        pDdiTable->pfnOcSetMode                              = validation_layer::zesFrequencyOcSetMode;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnOcGetMode                                = pDdiTable->pfnOcGetMode;
        pDdiTable->pfnOcGetMode                              = validation_layer::zesFrequencyOcGetMode;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnOcGetIccMax                              = pDdiTable->pfnOcGetIccMax;
        pDdiTable->pfnOcGetIccMax                            = validation_layer::zesFrequencyOcGetIccMax;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnOcSetIccMax                              = pDdiTable->pfnOcSetIccMax;
        pDdiTable->pfnOcSetIccMax                            = validation_layer::zesFrequencyOcSetIccMax;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnOcGetTjMax                               = pDdiTable->pfnOcGetTjMax;
        pDdiTable->pfnOcGetTjMax                             = validation_layer::zesFrequencyOcGetTjMax;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnOcSetTjMax                               = pDdiTable->pfnOcSetTjMax;
        pDdiTable->pfnOcSetTjMax                             = validation_layer::zesFrequencyOcSetTjMax;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesLedGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetState                                 = pDdiTable->pfnGetState;
        pDdiTable->pfnGetState                               = validation_layer::zesLedGetState;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetState                                 = pDdiTable->pfnSetState;
        pDdiTable->pfnSetState                               = validation_layer::zesLedSetState;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetColor                                 = pDdiTable->pfnSetColor;
        pDdiTable->pfnSetColor                               = validation_layer::zesLedSetColor;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesMemoryGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetState                                 = pDdiTable->pfnGetState;
        pDdiTable->pfnGetState                               = validation_layer::zesMemoryGetState;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetBandwidth                             = pDdiTable->pfnGetBandwidth;
        pDdiTable->pfnGetBandwidth                           = validation_layer::zesMemoryGetBandwidth;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnGetDomainProperties                      = pDdiTable->pfnGetDomainProperties;
        pDdiTable->pfnGetDomainProperties                    = validation_layer::zesOverclockGetDomainProperties;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnGetDomainVFProperties                    = pDdiTable->pfnGetDomainVFProperties;
        pDdiTable->pfnGetDomainVFProperties                  = validation_layer::zesOverclockGetDomainVFProperties;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnGetDomainControlProperties               = pDdiTable->pfnGetDomainControlProperties;
        pDdiTable->pfnGetDomainControlProperties             = validation_layer::zesOverclockGetDomainControlProperties;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnGetControlCurrentValue                   = pDdiTable->pfnGetControlCurrentValue;
        pDdiTable->pfnGetControlCurrentValue                 = validation_layer::zesOverclockGetControlCurrentValue;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnGetControlPendingValue                   = pDdiTable->pfnGetControlPendingValue;
        pDdiTable->pfnGetControlPendingValue                 = validation_layer::zesOverclockGetControlPendingValue;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnSetControlUserValue                      = pDdiTable->pfnSetControlUserValue;
        pDdiTable->pfnSetControlUserValue                    = validation_layer::zesOverclockSetControlUserValue;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnGetControlState                          = pDdiTable->pfnGetControlState;
        pDdiTable->pfnGetControlState                        = validation_layer::zesOverclockGetControlState;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnGetVFPointValues                         = pDdiTable->pfnGetVFPointValues;
        pDdiTable->pfnGetVFPointValues                       = validation_layer::zesOverclockGetVFPointValues;
    }
    if (version >= ZE_API_VERSION_1_5) {
        dditable.pfnSetVFPointValues                         = pDdiTable->pfnSetVFPointValues;
        pDdiTable->pfnSetVFPointValues                       = validation_layer::zesOverclockSetVFPointValues;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesPerformanceFactorGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
        pDdiTable->pfnGetConfig                              = validation_layer::zesPerformanceFactorGetConfig;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
        pDdiTable->pfnSetConfig                              = validation_layer::zesPerformanceFactorSetConfig;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesPowerGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetEnergyCounter                         = pDdiTable->pfnGetEnergyCounter;
        pDdiTable->pfnGetEnergyCounter                       = validation_layer::zesPowerGetEnergyCounter;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetLimits                                = pDdiTable->pfnGetLimits;
        pDdiTable->pfnGetLimits                              = validation_layer::zesPowerGetLimits;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetLimits                                = pDdiTable->pfnSetLimits;
        pDdiTable->pfnSetLimits                              = validation_layer::zesPowerSetLimits;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetEnergyThreshold                       = pDdiTable->pfnGetEnergyThreshold;
        pDdiTable->pfnGetEnergyThreshold                     = validation_layer::zesPowerGetEnergyThreshold;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetEnergyThreshold                       = pDdiTable->pfnSetEnergyThreshold;
        pDdiTable->pfnSetEnergyThreshold                     = validation_layer::zesPowerSetEnergyThreshold;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetLimitsExt                             = pDdiTable->pfnGetLimitsExt;
        pDdiTable->pfnGetLimitsExt                           = validation_layer::zesPowerGetLimitsExt;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetLimitsExt                             = pDdiTable->pfnSetLimitsExt;
        pDdiTable->pfnSetLimitsExt                           = validation_layer::zesPowerSetLimitsExt;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesPsuGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetState                                 = pDdiTable->pfnGetState;
        pDdiTable->pfnGetState                               = validation_layer::zesPsuGetState;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesRasGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
        pDdiTable->pfnGetConfig                              = validation_layer::zesRasGetConfig;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
        pDdiTable->pfnSetConfig                              = validation_layer::zesRasSetConfig;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetState                                 = pDdiTable->pfnGetState;
        pDdiTable->pfnGetState                               = validation_layer::zesRasGetState;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetStateExp                              = pDdiTable->pfnGetStateExp;
        pDdiTable->pfnGetStateExp                            = validation_layer::zesRasGetStateExp;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnClearStateExp                            = pDdiTable->pfnClearStateExp;
        pDdiTable->pfnClearStateExp                          = validation_layer::zesRasClearStateExp;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesSchedulerGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetCurrentMode                           = pDdiTable->pfnGetCurrentMode;
        pDdiTable->pfnGetCurrentMode                         = validation_layer::zesSchedulerGetCurrentMode;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetTimeoutModeProperties                 = pDdiTable->pfnGetTimeoutModeProperties;
        pDdiTable->pfnGetTimeoutModeProperties               = validation_layer::zesSchedulerGetTimeoutModeProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetTimesliceModeProperties               = pDdiTable->pfnGetTimesliceModeProperties;
        pDdiTable->pfnGetTimesliceModeProperties             = validation_layer::zesSchedulerGetTimesliceModeProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetTimeoutMode                           = pDdiTable->pfnSetTimeoutMode;
        pDdiTable->pfnSetTimeoutMode                         = validation_layer::zesSchedulerSetTimeoutMode;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetTimesliceMode                         = pDdiTable->pfnSetTimesliceMode;
        pDdiTable->pfnSetTimesliceMode                       = validation_layer::zesSchedulerSetTimesliceMode;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetExclusiveMode                         = pDdiTable->pfnSetExclusiveMode;
        pDdiTable->pfnSetExclusiveMode                       = validation_layer::zesSchedulerSetExclusiveMode;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetComputeUnitDebugMode                  = pDdiTable->pfnSetComputeUnitDebugMode;
        pDdiTable->pfnSetComputeUnitDebugMode                = validation_layer::zesSchedulerSetComputeUnitDebugMode;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesStandbyGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetMode                                  = pDdiTable->pfnGetMode;
        pDdiTable->pfnGetMode                                = validation_layer::zesStandbyGetMode;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetMode                                  = pDdiTable->pfnSetMode;
        pDdiTable->pfnSetMode                                = validation_layer::zesStandbySetMode;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
        pDdiTable->pfnGetProperties                          = validation_layer::zesTemperatureGetProperties;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetConfig                                = pDdiTable->pfnGetConfig;
        pDdiTable->pfnGetConfig                              = validation_layer::zesTemperatureGetConfig;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnSetConfig                                = pDdiTable->pfnSetConfig;
        pDdiTable->pfnSetConfig                              = validation_layer::zesTemperatureSetConfig;
    }
    if (version >= ZE_API_VERSION_1_0) {
        dditable.pfnGetState                                 = pDdiTable->pfnGetState;
        pDdiTable->pfnGetState                               = validation_layer::zesTemperatureGetState;
    }
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

    if (validation_layer::context.version < version)
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    ze_result_t result = ZE_RESULT_SUCCESS;

    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnGetVFCapabilitiesExp                     = pDdiTable->pfnGetVFCapabilitiesExp;
        pDdiTable->pfnGetVFCapabilitiesExp                   = validation_layer::zesVFManagementGetVFCapabilitiesExp;
    }
    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnGetVFMemoryUtilizationExp2               = pDdiTable->pfnGetVFMemoryUtilizationExp2;
        pDdiTable->pfnGetVFMemoryUtilizationExp2             = validation_layer::zesVFManagementGetVFMemoryUtilizationExp2;
    }
    if (version >= ZE_API_VERSION_1_10) {
        dditable.pfnGetVFEngineUtilizationExp2               = pDdiTable->pfnGetVFEngineUtilizationExp2;
        pDdiTable->pfnGetVFEngineUtilizationExp2             = validation_layer::zesVFManagementGetVFEngineUtilizationExp2;
    }
    if (version >= ZE_API_VERSION_1_12) {
        dditable.pfnGetVFCapabilitiesExp2                    = pDdiTable->pfnGetVFCapabilitiesExp2;
        pDdiTable->pfnGetVFCapabilitiesExp2                  = validation_layer::zesVFManagementGetVFCapabilitiesExp2;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetVFPropertiesExp                       = pDdiTable->pfnGetVFPropertiesExp;
        pDdiTable->pfnGetVFPropertiesExp                     = validation_layer::zesVFManagementGetVFPropertiesExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetVFMemoryUtilizationExp                = pDdiTable->pfnGetVFMemoryUtilizationExp;
        pDdiTable->pfnGetVFMemoryUtilizationExp              = validation_layer::zesVFManagementGetVFMemoryUtilizationExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnGetVFEngineUtilizationExp                = pDdiTable->pfnGetVFEngineUtilizationExp;
        pDdiTable->pfnGetVFEngineUtilizationExp              = validation_layer::zesVFManagementGetVFEngineUtilizationExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnSetVFTelemetryModeExp                    = pDdiTable->pfnSetVFTelemetryModeExp;
        pDdiTable->pfnSetVFTelemetryModeExp                  = validation_layer::zesVFManagementSetVFTelemetryModeExp;
    }
    if (version >= ZE_API_VERSION_1_9) {
        dditable.pfnSetVFTelemetrySamplingIntervalExp        = pDdiTable->pfnSetVFTelemetrySamplingIntervalExp;
        pDdiTable->pfnSetVFTelemetrySamplingIntervalExp      = validation_layer::zesVFManagementSetVFTelemetrySamplingIntervalExp;
    }
    return result;
}

#if defined(__cplusplus)
};
#endif
