/*
 *
 * Copyright (C) 2020-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#pragma once
#include <vector>
#include <iostream>
#include <string.h> 
#include "ze_api.h"
#include "zet_api.h"
#include "loader/ze_loader.h"
#include "zello_log.h"

//////////////////////////////////////////////////////////////////////////
inline bool argparse( int argc, char *argv[],
    const char *shortName, const char *longName )
{
    char **arg = &argv[ 1 ];
    char **argE = &argv[ argc ];

    for( ; arg != argE; ++arg )
        if( ( 0 == strcmp( *arg, shortName ) ) || ( 0 == strcmp( *arg, longName ) ) )
            return true;

    return false;
}

//////////////////////////////////////////////////////////////////////////
inline bool init_ze( void )
{
    ze_result_t result;
        // Initialize the driver
    result = zeInit(0);
    if(result != ZE_RESULT_SUCCESS) {
        std::cout << "Driver not initialized: " << to_string(result) << std::endl;
        return false;
    }
    std::cout << "Driver initialized.\n";
    return true;
}
//////////////////////////////////////////////////////////////////////////
inline ze_device_handle_t findDevice(
    ze_driver_handle_t pDriver,
    ze_device_type_t type)
{
    // get all devices
    uint32_t deviceCount = 0;
    zeDeviceGet(pDriver, &deviceCount, nullptr);

    std::vector<ze_device_handle_t> devices(deviceCount);
    zeDeviceGet(pDriver, &deviceCount, devices.data());

    ze_device_handle_t found = nullptr;

    // for each device, find the first one matching the type
    for(uint32_t device = 0; device < deviceCount; ++device)
    {
        auto phDevice = devices[device];

        ze_device_properties_t device_properties = {};
        device_properties.stype = ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES;
        zeDeviceGetProperties(phDevice, &device_properties);

        if(type == device_properties.type)
        {
            found = phDevice;

            ze_driver_properties_t driver_properties = {};
            driver_properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
            zeDriverGetProperties(pDriver, &driver_properties);

            std::cout << "Found "<< to_string(type) << " device..." << "\n";
            std::cout << "Driver version: " << driver_properties.driverVersion << "\n";

            ze_api_version_t version = {};
            zeDriverGetApiVersion(pDriver, &version);
            std::cout << "API version: " << to_string(version) << "\n";

            std::cout << to_string(device_properties) << "\n";

            ze_device_compute_properties_t compute_properties = {};
            compute_properties.stype = ZE_STRUCTURE_TYPE_DEVICE_COMPUTE_PROPERTIES;
            zeDeviceGetComputeProperties(phDevice, &compute_properties);
            std::cout << to_string(compute_properties) << "\n";

            uint32_t memoryCount = 0;
            zeDeviceGetMemoryProperties(phDevice, &memoryCount, nullptr);
            auto pMemoryProperties = new ze_device_memory_properties_t[memoryCount];
            for( uint32_t mem = 0; mem < memoryCount; ++mem )
            {
                pMemoryProperties[mem].stype = ZE_STRUCTURE_TYPE_DEVICE_MEMORY_PROPERTIES;
                pMemoryProperties[mem].pNext = nullptr;
            }
            zeDeviceGetMemoryProperties(phDevice, &memoryCount, pMemoryProperties);
            for( uint32_t mem = 0; mem < memoryCount; ++mem )
            {
                std::cout << to_string( pMemoryProperties[ mem ] ) << "\n";
            }
            delete[] pMemoryProperties;

            ze_device_memory_access_properties_t memory_access_properties = {};
            memory_access_properties.stype = ZE_STRUCTURE_TYPE_DEVICE_MEMORY_ACCESS_PROPERTIES;
            zeDeviceGetMemoryAccessProperties(phDevice, &memory_access_properties);
            std::cout << to_string( memory_access_properties ) << "\n";

            uint32_t cacheCount = 0;
            zeDeviceGetCacheProperties(phDevice, &cacheCount, nullptr );
            auto pCacheProperties = new ze_device_cache_properties_t[cacheCount];
            for( uint32_t cache = 0; cache < cacheCount; ++cache )
            {
                pCacheProperties[cache].stype = ZE_STRUCTURE_TYPE_DEVICE_CACHE_PROPERTIES;
                pCacheProperties[cache].pNext = nullptr;
            }
            zeDeviceGetCacheProperties(phDevice, &cacheCount, pCacheProperties);
            for( uint32_t cache = 0; cache < cacheCount; ++cache )
            {
                std::cout << to_string( pCacheProperties[ cache ] ) << "\n";
            }
            delete[] pCacheProperties;

            ze_device_image_properties_t image_properties = {};
            image_properties.stype = ZE_STRUCTURE_TYPE_DEVICE_IMAGE_PROPERTIES;
            zeDeviceGetImageProperties(phDevice, &image_properties);
            std::cout << to_string( image_properties ) << "\n";

            break;
        }
    }

    return found;
}
