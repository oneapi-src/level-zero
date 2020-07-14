/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include <stdlib.h>
#include <memory>

#include "zello_sysman.h"

//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "zes_api.h"

void PrintRasDetails(zes_ras_state_t* pDetails)
{
    fprintf(stdout, "        Number new resets:                %llu\n", (long long unsigned int)pDetails->category[ZES_RAS_ERROR_CAT_RESET]);
    fprintf(stdout, "        Number new programming errors:    %llu\n", (long long unsigned int)pDetails->category[ZES_RAS_ERROR_CAT_PROGRAMMING_ERRORS]);
    fprintf(stdout, "        Number new driver errors:         %llu\n", (long long unsigned int)pDetails->category[ZES_RAS_ERROR_CAT_DRIVER_ERRORS]);
    fprintf(stdout, "        Number new compute errors:        %llu\n", (long long unsigned int)pDetails->category[ZES_RAS_ERROR_CAT_COMPUTE_ERRORS]);
    fprintf(stdout, "        Number new non-compute errors:    %llu\n", (long long unsigned int)pDetails->category[ZES_RAS_ERROR_CAT_NON_COMPUTE_ERRORS]);
    fprintf(stdout, "        Number new cache errors:          %llu\n", (long long unsigned int)pDetails->category[ZES_RAS_ERROR_CAT_CACHE_ERRORS]);
    fprintf(stdout, "        Number new display errors:        %llu\n", (long long unsigned int)pDetails->category[ZES_RAS_ERROR_CAT_DISPLAY_ERRORS]);
}

void ShowRasErrors(zes_device_handle_t hSysmanDevice)
{
    uint32_t numRasErrorSets;
    zes_ras_handle_t* phRasErrorSets;
    if (zesDeviceEnumRasErrorSets(hSysmanDevice, &numRasErrorSets, NULL) != ZE_RESULT_SUCCESS)
    {
        return;
    }
    if (numRasErrorSets == 0)
    {
        fprintf(stdout, "No RAS error sets available/enabled on this device.\n");
        return;
    }
    phRasErrorSets =
        (zes_ras_handle_t*)malloc(numRasErrorSets * sizeof(zes_ras_handle_t));
    if (zesDeviceEnumRasErrorSets(hSysmanDevice, &numRasErrorSets, phRasErrorSets) == ZE_RESULT_SUCCESS)
    {
        for (uint32_t rasIndex = 0; rasIndex < numRasErrorSets; rasIndex++)
        {
            zes_ras_properties_t props;
            if (zesRasGetProperties(phRasErrorSets[rasIndex], &props) == ZE_RESULT_SUCCESS)
            {
                zes_ras_state_t errorDetails;
                const char* pErrorType;
                switch (props.type)
                {
                case ZES_RAS_ERROR_TYPE_CORRECTABLE:
                    pErrorType = "Correctable";
                    break;
                case ZES_RAS_ERROR_TYPE_UNCORRECTABLE:
                    pErrorType = "Uncorrectable";
                    break;
                default:
                    pErrorType = "Unknown";
                    break;
                }
                fprintf(stdout, "RAS %s errors\n", pErrorType);
                if (props.onSubdevice)
                {
                    fprintf(stdout, "    On sub-device: %u\n", props.subdeviceId);
                }
                if (zesRasGetState(phRasErrorSets[rasIndex], 1, &errorDetails)
                    == ZE_RESULT_SUCCESS)
                {
                    uint64_t numErrors = 0;
                    for (int i = 0; i < ZES_MAX_RAS_ERROR_CATEGORY_COUNT; i++)
                    {
                        numErrors += errorDetails.category[i];
                    }
                    fprintf(stdout, "    Number new errors: %llu\n", (long long unsigned int)numErrors);
                    if (numErrors)
                    {
                        PrintRasDetails(&errorDetails);
                    }
                }
            }
        }
    }
    free(phRasErrorSets);
}

void ListDiagnosticTests(zes_device_handle_t hSysmanDevice)
{
    uint32_t numTestSuites;
    if ((zesDeviceEnumDiagnosticTestSuites(hSysmanDevice, &numTestSuites, NULL) == ZE_RESULT_SUCCESS) && numTestSuites)
    {
        zes_diag_handle_t* phTestSuites =
            (zes_diag_handle_t*)malloc(numTestSuites * sizeof(zes_diag_handle_t));
        if (zesDeviceEnumDiagnosticTestSuites(hSysmanDevice, &numTestSuites, phTestSuites) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t suiteIndex = 0; suiteIndex < numTestSuites; suiteIndex++)
            {
                uint32_t numTests = 0;
                zes_diag_test_t* pTests;
                zes_diag_properties_t suiteProps;
                if (zesDiagnosticsGetProperties(phTestSuites[suiteIndex], &suiteProps) != ZE_RESULT_SUCCESS)
                {
                    continue;
                }
                fprintf(stdout, "Diagnostic test suite %s:\n", suiteProps.name);
                if (!suiteProps.haveTests)
                {
                    fprintf(stdout, "    There are no individual tests that can be selected.\n");
                    continue;
                }
                if (zesDiagnosticsGetTests(phTestSuites[suiteIndex], &numTests, NULL) != ZE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "    Problem getting list of individual tests.\n");
                    continue;
                }
                pTests = (zes_diag_test_t*)malloc(numTests * sizeof(zes_diag_test_t*));
                if (zesDiagnosticsGetTests(phTestSuites[suiteIndex], &numTests, pTests) != ZE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "    Problem getting list of individual tests.\n");
                    continue;
                }
                for (uint32_t i = 0; i < numTests; i++)
                {
                    fprintf(stdout, "    Test %u: %s\n", pTests[i].index, pTests[i].name);
                }
                free(pTests);
            }
        }
        free(phTestSuites);
    }
}

void WaitForExcessTemperatureEvent(zes_driver_handle_t hDriver, double tempLimit)
{
    uint32_t deviceCount = 0;
    uint32_t numListenDevices = 0;
    ze_device_handle_t* phDevices;
    zes_device_handle_t* phListenDevices;
    zes_event_type_flags_t* pDeviceEvents;
    uint32_t* pListenDeviceIndex;

    // Get list of all devices under this driver
    zeDeviceGet(hDriver, &deviceCount, nullptr);
    phDevices = (ze_device_handle_t*)malloc(deviceCount * sizeof(ze_device_handle_t));
    phListenDevices = (zes_device_handle_t*)malloc(deviceCount * sizeof(ze_device_handle_t));
    pDeviceEvents = (zes_event_type_flags_t*)malloc(deviceCount * sizeof(zes_event_type_flags_t));
    pListenDeviceIndex = (uint32_t*)malloc(deviceCount * sizeof(uint32_t));
    zeDeviceGet(hDriver, &deviceCount, phDevices);
    for(uint32_t d = 0; d < deviceCount; ++d)
    {
        // Get Sysman handle, event handle and list of temperature sensors in the device
        uint32_t numTempSensors = 0;
        uint32_t numConfiguredTempSensors = 0;
        zes_temp_handle_t* allTempSensors;
        zes_device_handle_t hSysmanDevice = phDevices[d];
        if (zesDeviceEnumTemperatureSensors(hSysmanDevice, &numTempSensors, NULL) != ZE_RESULT_SUCCESS)
        {
            continue;
        }
        allTempSensors = (zes_temp_handle_t*)malloc(numTempSensors * sizeof(zes_temp_handle_t));
        if (zesDeviceEnumTemperatureSensors(hSysmanDevice, &numTempSensors, allTempSensors) == ZE_RESULT_SUCCESS)
        {
            // Configure each temperature sensor to trigger a critical event and a threshold1 event
            bool configuredSensors = false;
            zes_temp_config_t config;
            for (uint32_t t = 0; t < numTempSensors; t++)
            {
                if (zesTemperatureGetConfig(allTempSensors[t], &config) != ZE_RESULT_SUCCESS)
                {
                    continue;
                }
                config.enableCritical = true;
                config.threshold1.enableHighToLow = false;
                config.threshold1.enableLowToHigh = true;
                config.threshold1.threshold = tempLimit;
                config.threshold2.enableHighToLow = false;
                config.threshold2.enableLowToHigh = false;
                if (zesTemperatureSetConfig(allTempSensors[t], &config) == ZE_RESULT_SUCCESS)
                {
                    numConfiguredTempSensors++;
                }
            }
        }
        if (numConfiguredTempSensors)
        {
            if (zesDeviceEventRegister(hSysmanDevice, ZES_EVENT_TYPE_FLAG_TEMP_CRITICAL | ZES_EVENT_TYPE_FLAG_TEMP_THRESHOLD1) == ZE_RESULT_SUCCESS)
            {
                phListenDevices[numListenDevices] = hSysmanDevice;
                pListenDeviceIndex[numListenDevices] = d;
                numListenDevices++;
            }
        }
        free(allTempSensors);
    }

    if (numListenDevices)
    {
        // Block until we receive events
        uint32_t numEvents;
        if (zesDriverEventListen(hDriver, UINT32_MAX, numListenDevices, phListenDevices, &numEvents, pDeviceEvents) == ZE_RESULT_SUCCESS)
        {
            if (numEvents)
            {
                for (uint32_t e = 0; e < numListenDevices; e++)
                {
                    if (pDeviceEvents[e] & ZES_EVENT_TYPE_FLAG_TEMP_CRITICAL)
                    {
                        fprintf(stdout, "Device %u: Went above the critical temperature.\n", pListenDeviceIndex[e]);
                    }
                    else if (pDeviceEvents[e] & ZES_EVENT_TYPE_FLAG_TEMP_THRESHOLD1)
                    {
                        fprintf(stdout, "Device %u: Went above the temperature threshold %f.\n", pListenDeviceIndex[e], tempLimit);
                    }
                }
            }
        }
    }

    free(phDevices);
    free(phListenDevices);
    free(pListenDeviceIndex);
    free(pDeviceEvents);
}

void ResetDevice(zes_device_handle_t hSysmanDevice)
{
    ze_result_t status = zesDeviceReset(hSysmanDevice, false);
    switch (status)
    {
        case ZE_RESULT_SUCCESS:
            fprintf(stdout, "Device reset completed successfully.\n");
            break;
        case ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS:
            fprintf(stdout, "Device reset completed successfully.\n");
            break;
        case ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE:
            fprintf(stdout, "Device cannot be reset because applications are using it.\n");
            break;
        case ZE_RESULT_ERROR_UNKNOWN:
            fprintf(stdout, "Device reset was initiated but did not complete successfully.\n");
            break;
        default:
            fprintf(stdout, "Other errors occurred that prevent initiating a device reset.\n");
            break;
    }
}

void ShowFabricPortInfo(zes_fabric_port_handle_t hPort)
{
    zes_fabric_port_properties_t props;
    if (zesFabricPortGetProperties(hPort, &props) == ZE_RESULT_SUCCESS)
    {
        zes_fabric_port_state_t state;
        if (zesFabricPortGetState(hPort, &state) == ZE_RESULT_SUCCESS)
        {
            zes_fabric_link_type_t link;
            if (zesFabricPortGetLinkType(hPort, &link) == ZE_RESULT_SUCCESS)
            {
                zes_fabric_port_config_t config;
                if (zesFabricPortGetConfig(hPort, &config) == ZE_RESULT_SUCCESS)
                {
                    fprintf(stdout,
                        "        Model:                 %s\n", props.model);
                    if (props.onSubdevice)
                    {
                        fprintf(stdout,
                            "        On sub-device:         %u\n", props.subdeviceId);
                    }
                    if (config.enabled)
                    {
                        const char* status;
                        fprintf(stdout,
                            "        Config:                UP\n");
                        switch (state.status)
                        {
                        case ZES_FABRIC_PORT_STATUS_HEALTHY:
                            status = "HEALTHY - The port is up and operating as expected";
                            break;
                        case ZES_FABRIC_PORT_STATUS_DEGRADED:
                            status = "DEGRADED - The port is up but has quality and/or bandwidth degradation";
                            break;
                        case ZES_FABRIC_PORT_STATUS_FAILED:
                            status = "FAILED - Port connection instabilities";
                            break;
                        case ZES_FABRIC_PORT_STATUS_DISABLED:
                            status = "DISABLED - The port is configured down";
                            break;
                        default:
                            status = "UNKNOWN";
                            break;
                        }
                        fprintf(stdout,
                            "        Status:                %s\n", status);
                        fprintf(stdout,
                            "        Link type:             %s\n", link.desc);
                        fprintf(stdout,
                            "        Max speed (rx/tx):     %llu/%llu bytes/sec\n",
                            ((long long unsigned int)props.maxRxSpeed.bitRate) * props.maxRxSpeed.width / 8,
                            ((long long unsigned int)props.maxTxSpeed.bitRate) * props.maxTxSpeed.width / 8);
                        fprintf(stdout,
                            "        Current speed (rx/tx): %llu/%llu bytes/sec\n",
                            ((long long unsigned int)state.rxSpeed.bitRate) * state.rxSpeed.width / 8,
                            ((long long unsigned int)state.txSpeed.bitRate) * state.txSpeed.width / 8);
                    }
                    else
                    {
                        fprintf(stdout,
                            "        Config:                DOWN\n");
                    }
                }
            }
        }
    }
}

void ShowFabricPorts(zes_device_handle_t hSysmanDevice)
{
    uint32_t numPorts;
    if ((zesDeviceEnumFabricPorts(hSysmanDevice, &numPorts, NULL) == ZE_RESULT_SUCCESS) && numPorts)
    {
        zes_fabric_port_handle_t* phPorts =
            (zes_fabric_port_handle_t*)malloc(numPorts * sizeof(zes_fabric_port_handle_t));
        if (zesDeviceEnumFabricPorts(hSysmanDevice, &numPorts, phPorts) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numPorts; index++)
            {
                fprintf(stdout, "    Port %u:\n", index);
                ShowFabricPortInfo(phPorts[index]);
            }
        }
        free(phPorts);
    }
}

void PrintOcErrors(ze_result_t status) 
{
    if (status == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE)
    {
        fprintf(stderr, "ERROR: Overclocking not supported.\n");
    }
    else if (status == ZE_RESULT_ERROR_NOT_AVAILABLE)
    {
        fprintf(stderr, "ERROR: Overclocking locked by the BIOS.\n");
    }
    else if (status == ZE_RESULT_ERROR_INVALID_ARGUMENT)
    {
        fprintf(stderr, "ERROR: The overclock frequency or voltage is too high.\n");
    }
    else if (status == ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS)
    {
        fprintf(stderr, "ERROR: You don't have permission to overclock.\n");
    }
    else
    {
        fprintf(stderr, "ERROR: Problem requesting overclock.\n");
    }
}

// Try to overclock frequency 5% above the factory default with 10% increase in voltage
bool SetOverclock(zes_freq_handle_t hFreqDomain)
{
    bool ret = false;
    zes_oc_capabilities_t oc_caps;
    if (zesFrequencyOcGetCapabilities(hFreqDomain, &oc_caps) == ZE_RESULT_SUCCESS)
    {
        double CurrentMaxFrequencyMhz = oc_caps.maxFactoryDefaultFrequency;
        CurrentMaxFrequencyMhz *= 1.05;
        if (CurrentMaxFrequencyMhz <= oc_caps.maxOcFrequency)
        {
            ze_result_t status;
            double frequency = CurrentMaxFrequencyMhz;
            double voltageTarget = oc_caps.maxFactoryDefaultVoltage * 1.1;
            double voltageOffset = 0.0;

            status = zesFrequencyOcSetMode(hFreqDomain, zes_oc_mode_t::ZES_OC_MODE_INTERPOLATIVE);

            if (status == ZE_RESULT_SUCCESS) 
            {
                fprintf(stdout, "Successfully changed mode\n");
            }
            else 
            {
                PrintOcErrors(status);
            }

            status = zesFrequencyOcSetVoltageTarget(hFreqDomain, voltageTarget, voltageOffset);

            if (status == ZE_RESULT_SUCCESS)
            {
                fprintf(stdout, "Successfully changed voltage to %.3f V\n", (voltageTarget+ voltageOffset));
            }
            else
            {
                PrintOcErrors(status);
            }

            status = zesFrequencyOcSetFrequencyTarget(hFreqDomain, CurrentMaxFrequencyMhz);

            if (status == ZE_RESULT_SUCCESS)
            {
                fprintf(stdout, "Successfully overclocked to %.3f Mhz\n", CurrentMaxFrequencyMhz);
                ret = true;
            }
            else
            {
                PrintOcErrors(status);
            }
        }
    }
    else
    {
        fprintf(stderr, "ERROR: Problem getting overclock capabilities.\n");
    }
    return ret;
}

void ShowOcCapabilities(zes_device_handle_t hSysmanDevice)
{
    uint32_t numFreqDomains;
    if ((zesDeviceEnumFrequencyDomains(hSysmanDevice, &numFreqDomains, NULL) == ZE_RESULT_SUCCESS) && numFreqDomains)
    {
        zes_freq_handle_t* pFreqHandles = (zes_freq_handle_t*)malloc(numFreqDomains * sizeof(zes_freq_handle_t));
        if (zesDeviceEnumFrequencyDomains(hSysmanDevice, &numFreqDomains, pFreqHandles) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numFreqDomains; index++)
            {
                zes_freq_properties_t props;
                zes_oc_capabilities_t oc_caps;
                if (zesFrequencyGetProperties(pFreqHandles[index], &props) != ZE_RESULT_SUCCESS)
                {
                    continue;
                }
                // Only control GPU frequency domains
                if (props.type != ZES_FREQ_DOMAIN_GPU)
                {
                    continue;
                }
                if (zesFrequencyOcGetCapabilities(pFreqHandles[index], &oc_caps) != ZE_RESULT_SUCCESS)
                {
                    continue;
                }
                fprintf(stdout, "GPU frequency domaion %u:\n", index);
                if (oc_caps.isOcSupported)
                {
                    fprintf(stdout, "    Overclocking supported with these capabilities:\n");
                    fprintf(stdout, "        Max overclock Frequency: %.3f MHz\n", oc_caps.maxOcFrequency);
                    fprintf(stdout, "        Max overclock Voltage: %.3f Volts\n", oc_caps.maxOcVoltage);
                    fprintf(stdout, "        Max factory default frequency: %.3f\n", oc_caps.maxFactoryDefaultFrequency);
                    fprintf(stdout, "        Max factory default voltage: %.3f\n", oc_caps.maxFactoryDefaultVoltage);
                    fprintf(stdout, "        Is high voltage capable: %s\n", oc_caps.isHighVoltModeCapable ? "yes" : "no");
                    fprintf(stdout, "        Is high voltage enabled: %s\n", oc_caps.isHighVoltModeEnabled ? "yes" : "no");
                    fprintf(stdout, "        Is TjMax Supported: %s\n", oc_caps.isTjMaxSupported ? "yes" : "no");
                    fprintf(stdout, "        Is IccMax Supported: %s\n", oc_caps.isIccMaxSupported ? "yes" : "no");

                    if (oc_caps.isIccMaxSupported)
                    {
                        double iccmax;
                        if (zesFrequencyOcGetIccMax(pFreqHandles[index], &iccmax) == ZE_RESULT_SUCCESS) 
                        {
                            fprintf(stdout, "    Icc Max: %.3f A\n", iccmax);
                        }
                    }

                    if (oc_caps.isTjMaxSupported)
                    {
                        double tjmax;
                        if (zesFrequencyOcGetTjMax(pFreqHandles[index], &tjmax) == ZE_RESULT_SUCCESS)
                        {
                            fprintf(stdout, "    TjMax: %.3f\n", tjmax);
                        }
                    }                                                 
                }
                else
                {
                    fprintf(stdout, "    Overclocking not supported\n");
                }
            }
        }
        free(pFreqHandles);
    }    
}

void FixGpuFrequency(zes_device_handle_t hSysmanDevice, double FreqMHz)
{
    uint32_t numFreqDomains;
    if ((zesDeviceEnumFrequencyDomains(hSysmanDevice, &numFreqDomains, NULL) == ZE_RESULT_SUCCESS) && numFreqDomains)
    {
        zes_freq_handle_t* pFreqHandles = (zes_freq_handle_t*)malloc(numFreqDomains * sizeof(zes_freq_handle_t));
        if (zesDeviceEnumFrequencyDomains(hSysmanDevice, &numFreqDomains, pFreqHandles) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numFreqDomains; index++)
            {
                zes_freq_properties_t props;
                if (zesFrequencyGetProperties(pFreqHandles[index], &props) == ZE_RESULT_SUCCESS)
                {
                    // Only control GPU frequency domains
                    if (props.type == ZES_FREQ_DOMAIN_GPU)
                    {
                        if (props.canControl)
                        {
                            zes_freq_range_t range;
                            range.min = FreqMHz;
                            range.max = FreqMHz;
                            if (zesFrequencySetRange(pFreqHandles[index], &range) != ZE_RESULT_SUCCESS)
                            {
                                fprintf(stderr, "ERROR: Problem setting the frequency range for domain with index %u.\n", index);
                            }
                        }
                        else
                        {
                            fprintf(stderr, "ERROR: Can't control GPU frequency domain with index %u.\n", index);
                        }
                    }
                }              
            }
        }
        free(pFreqHandles);
    }
}

void FixSubdeviceGpuFrequency(zes_device_handle_t hSysmanDevice, uint32_t subdeviceId, double FreqMHz)
{
    uint32_t numFreqDomains;
    if ((zesDeviceEnumFrequencyDomains(hSysmanDevice, &numFreqDomains, NULL) == ZE_RESULT_SUCCESS) && numFreqDomains)
    {
        zes_freq_handle_t* pFreqHandles = (zes_freq_handle_t*)malloc(numFreqDomains * sizeof(zes_freq_handle_t));
        if (zesDeviceEnumFrequencyDomains(hSysmanDevice, &numFreqDomains, pFreqHandles) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numFreqDomains; index++)
            {
                zes_freq_properties_t props;
                if (zesFrequencyGetProperties(pFreqHandles[index], &props) == ZE_RESULT_SUCCESS)
                {
                    // Only control GPU frequency domains
                    if (props.type == ZES_FREQ_DOMAIN_GPU)
                    {
                        // Only control the GPU frequency domain for a specific sub-device
                        if (props.onSubdevice && (props.subdeviceId == subdeviceId))
                        {
                            if (props.canControl)
                            {
                                zes_freq_range_t range;
                                range.min = FreqMHz;
                                range.max = FreqMHz;
                                if (zesFrequencySetRange(pFreqHandles[index], &range) != ZE_RESULT_SUCCESS)
                                {
                                    fprintf(stderr, "ERROR: Problem setting the frequency range for domain with index %u.\n", index);
                                }
                            }
                            else
                            {
                                fprintf(stderr, "ERROR: Can't control GPU frequency domain with index %u.\n", index);
                            }
                        }
                    }
                }
            }
        }
        free(pFreqHandles);
    }
}

void SetFanSpeed(zes_device_handle_t hSysmanDevice, uint32_t SpeedRpm)
{
    uint32_t numFans;
    if (zesDeviceEnumFans(hSysmanDevice, &numFans, NULL) == ZE_RESULT_SUCCESS)
    {
        zes_fan_handle_t* phFans =
            (zes_fan_handle_t*)malloc(numFans * sizeof(zes_fan_handle_t));
        if (zesDeviceEnumFans(hSysmanDevice, &numFans, phFans) == ZE_RESULT_SUCCESS)
        {
            zes_fan_speed_t speedRequest;
            speedRequest.speed = SpeedRpm;
            speedRequest.units = ZES_FAN_SPEED_UNITS_RPM;
            for (uint32_t fanIndex = 0; fanIndex < numFans; fanIndex++)
            {
                zes_fan_properties_t fanprops;
                if (zesFanGetProperties(phFans[fanIndex], &fanprops) == ZE_RESULT_SUCCESS)
                {
                    if (fanprops.canControl)
                    {
                        zesFanSetFixedSpeedMode(phFans[fanIndex], &speedRequest);
                    }
                    else
                    {
                        fprintf(stderr, "ERROR: Can't control fan %u.\n", fanIndex);
                    }
                }
            }
        }
        free(phFans);
    }
}

void ShowFans(zes_device_handle_t hSysmanDevice)
{
    uint32_t numFans;
    if (zesDeviceEnumFans(hSysmanDevice, &numFans, NULL) == ZE_RESULT_SUCCESS)
    {
        zes_fan_handle_t* phFans =
            (zes_fan_handle_t*)malloc(numFans * sizeof(zes_fan_handle_t));
        if (zesDeviceEnumFans(hSysmanDevice, &numFans, phFans) == ZE_RESULT_SUCCESS)
        {
            fprintf(stdout, "    Fans\n");
            for (uint32_t fanIndex = 0; fanIndex < numFans; fanIndex++)
            {
                int32_t speed;
                if (zesFanGetState(phFans[fanIndex], ZES_FAN_SPEED_UNITS_RPM, &speed)
                    == ZE_RESULT_SUCCESS)
                {
                    fprintf(stdout, "        Fan %u: %d RPM\n", fanIndex, speed);
                }
            }
        }
        free(phFans);
    }
}

void ShowAveragePower(zes_pwr_handle_t hPower, zes_power_energy_counter_t* pPrevEnergyCounter)
{
    zes_power_energy_counter_t newEnergyCounter;
    if (zesPowerGetEnergyCounter(hPower, &newEnergyCounter) == ZE_RESULT_SUCCESS)
    {
        uint64_t deltaTime = newEnergyCounter.timestamp - pPrevEnergyCounter->timestamp;
        if (deltaTime)
        {
            fprintf(stdout, "    Average power: %.3f W\n",
                ((double)(newEnergyCounter.energy - pPrevEnergyCounter->energy)) / ((double)deltaTime));
            *pPrevEnergyCounter = newEnergyCounter;
        }
    }
}

// Forward declarations
void ShowPowerLimits(zes_pwr_handle_t hPower);
void ShowEnergyThreshold(zes_pwr_handle_t hPower);

void ShowPowerDomains(zes_device_handle_t hSysmanDevice)
{
    uint32_t numPowerDomains;
    if (zesDeviceEnumPowerDomains(hSysmanDevice, &numPowerDomains, NULL) == ZE_RESULT_SUCCESS)
    {
        zes_pwr_handle_t* phPower =
            (zes_pwr_handle_t*)malloc(numPowerDomains * sizeof(zes_pwr_handle_t));
        if (zesDeviceEnumPowerDomains(hSysmanDevice, &numPowerDomains, phPower) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t pwrIndex = 0; pwrIndex < numPowerDomains; pwrIndex++)
            {
                zes_power_properties_t props;
                if (zesPowerGetProperties(phPower[pwrIndex], &props) == ZE_RESULT_SUCCESS)
                {
                    if (props.onSubdevice)
                    {
                        fprintf(stdout, "Sub-device %u power:\n", props.subdeviceId);
                        fprintf(stdout, "    Can control: %s\n", props.canControl ? "yes" : "no");
                        ShowPowerLimits(phPower[pwrIndex]);
                    }
                    else
                    {
                        fprintf(stdout, "Total package power:\n");
                        fprintf(stdout, "    Can control: %s\n", props.canControl ? "yes" : "no");
                        ShowPowerLimits(phPower[pwrIndex]);
                    }
                }

                ShowEnergyThreshold(phPower[pwrIndex]);
            }
        }
        free(phPower);
    }
}

void ShowPowerLimits(zes_pwr_handle_t hPower)
{
    zes_power_sustained_limit_t sustainedLimits;
    zes_power_burst_limit_t burstLimits;
    zes_power_peak_limit_t peakLimits;
    if (zesPowerGetLimits(hPower, &sustainedLimits, &burstLimits, &peakLimits) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Power limits\n");
        if (sustainedLimits.enabled)
        {
            fprintf(stdout, "        Sustained: %.3f W %.3f sec\n",
                ((double)sustainedLimits.power) / 1000, ((double)sustainedLimits.interval) / 1000);
        }
        else
        {
            fprintf(stdout, "        Sustained: Disabled\n");
        }
        if (burstLimits.enabled)
        {
            fprintf(stdout, "        Burst:     %.3f\n", ((double)burstLimits.power) / 1000);
        }
        else
        {
            fprintf(stdout, "        Burst:     Disabled\n");
        }
        fprintf(stdout, "        Peak AC:     %.3f\n", ((double)peakLimits.powerAC) / 1000);
        fprintf(stdout, "        Peak DC:     %.3f\n", ((double)peakLimits.powerDC) / 1000);
    }
}

void ShowEnergyThreshold(zes_pwr_handle_t hPower)
{
    zes_energy_threshold_t energyThreshold;
    if (zesPowerGetEnergyThreshold(hPower, &energyThreshold) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Energy Threshold: ");
        if (energyThreshold.enable)
        {
            fprintf(stdout, "Enabled, %0.3f Joules, Process ID %u\n", energyThreshold.threshold, energyThreshold.processId);
        }
        else
        {
            fprintf(stdout, "Disabled");
        }
        fprintf(stdout, "\n");
    }

}

void ShowDeviceInfo(zes_device_handle_t hSysmanDevice)
{
    zes_device_properties_t devProps;
    zes_device_state_t devState;
    if (zesDeviceGetProperties(hSysmanDevice, &devProps) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    UUID:           %s\n", devProps.core.uuid.id);
        fprintf(stdout, "    #subdevices:    %u\n", devProps.numSubdevices);
        fprintf(stdout, "    brand:          %s\n", devProps.brandName);
        fprintf(stdout, "    model:          %s\n", devProps.modelName);
        fprintf(stdout, "    driver timeout: disabled\n");
    }
    if (zesDeviceGetState(hSysmanDevice, &devState) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    Was repaired:   %s\n", (devState.repaired == ZES_REPAIR_STATUS_PERFORMED) ? "yes" : "no");
        if (devState.reset != 0)
        {
            fprintf(stdout, "DEVICE RESET REQUIRED:\n");
            if (devState.reset & ZES_RESET_REASON_FLAG_WEDGED)
            {
                fprintf(stdout, "- Hardware is wedged\n");
            }
            if (devState.reset & ZES_RESET_REASON_FLAG_REPAIR)
            {
                fprintf(stdout, "- Hardware needs to complete repairs\n");
            }
        }
    }
}

void DisableSchedulerQueueWatchdog(zes_sched_handle_t hScheduler)
{
    ze_result_t res;
    zes_sched_mode_t currentMode;
    res = zesSchedulerGetCurrentMode(hScheduler, &currentMode);
    if (res == ZE_RESULT_SUCCESS)
    {
        ze_bool_t requireReboot;
        zes_sched_timeout_properties_t props;
        props.watchdogTimeout = ZES_SCHED_WATCHDOG_DISABLE;
        res = zesSchedulerSetTimeoutMode(hScheduler, &props, &requireReboot);
        if (res == ZE_RESULT_SUCCESS)
        {
            if (requireReboot)
            {
                fprintf(stderr, "WARNING: Reboot required to complete desired configuration.\n");
            }
            else
            {
                fprintf(stdout, "Schedule mode changed successfully.\n");
            }
        }
        else if(res == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE )
        {
            fprintf(stderr, "ERROR: The timeout scheduler mode is not supported on this device.\n");
        }
        else if(res == ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS )
        {
            fprintf(stderr, "ERROR: Don't have permissions to change the scheduler mode.\n");
        }
        else
        {
            fprintf(stderr, "ERROR: Problem calling the API to change the scheduler mode.\n");
        }
    }
    else if(res == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE )
    {
        fprintf(stderr, "ERROR: Scheduler modes are not supported on this device.\n");
    }
    else
    {
        fprintf(stderr, "ERROR: Problem calling the API.\n");
    }
}

void DisableSchedulerQueueWatchdog(zes_device_handle_t hSysmanDevice)
{
    uint32_t numSchedulerQueues;
    if (zesDeviceEnumSchedulers(hSysmanDevice, &numSchedulerQueues, NULL) == ZE_RESULT_SUCCESS)
    {
        zes_sched_handle_t* phScheduler =
            (zes_sched_handle_t*)malloc(numSchedulerQueues * sizeof(zes_sched_handle_t));
        if (zesDeviceEnumSchedulers(hSysmanDevice, &numSchedulerQueues, phScheduler) == ZE_RESULT_SUCCESS)
        {
            for (uint32_t index = 0; index < numSchedulerQueues; index++)
            {
                DisableSchedulerQueueWatchdog(phScheduler[index]);
            }
        }
    }
}

void ShowPciInfo(zes_device_handle_t hSysmanDevice)
{
    zes_pci_properties_t pciProps;
    if (zesDevicePciGetProperties(hSysmanDevice, &pciProps) == ZE_RESULT_SUCCESS)
    {
        fprintf(stdout, "    PCI address:        %04u:%02u:%02u.%u\n", pciProps.address.domain, pciProps.address.bus, pciProps.address.device, pciProps.address.function);
    }
}

int gNumDevices = 0;    // Global

int main( int argc, char *argv[] )
{
    int ret = -1;
    if ( zeInit(0) != ZE_RESULT_SUCCESS )
    {
        fprintf(stderr, "Can't initialize the API.\n");
        ret = 1;
    }
    else
    {
        // Discover all the device groups and devices
        uint32_t driversCount = 0;
        zeDriverGet(&driversCount, nullptr);
        ze_driver_handle_t* allDrivers = (ze_driver_handle_t*)
            malloc(driversCount * sizeof(ze_driver_handle_t));
        zeDriverGet(&driversCount, allDrivers);

        // Find the first GPU device group
        ze_driver_handle_t hDriver = nullptr;
        for(uint32_t i = 0; i < driversCount; ++i)
        {
            uint32_t deviceCount = 0;
            zeDeviceGet(allDrivers[i], &deviceCount, nullptr);

            ze_device_handle_t* allDevices = (ze_device_handle_t*)
                malloc(deviceCount * sizeof(ze_device_handle_t));
            zeDeviceGet(allDrivers[i], &deviceCount, allDevices);

            for(uint32_t d = 0; d < deviceCount; ++d)
            {
                ze_device_properties_t device_properties;
                zeDeviceGetProperties(allDevices[d], &device_properties);
                if(ZE_DEVICE_TYPE_GPU == device_properties.type)
                {
                    gNumDevices++;
                    fprintf(stdout, "Device %d\n", gNumDevices);
                    ShowDeviceInfo(allDevices[d]);
                }
            }

            free(allDevices);
        }

        free(allDrivers);
    }

    if (gNumDevices == 0)
    {
        fprintf(stdout, "No managed devices found.\n");
    }

    return ret;
}
