/*
 *
 * Copyright (C) 2020-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include <stdlib.h>
#include <memory>

#include "zello_init.h"

void print_loader_versions(){

    zel_component_version_t *versions;
    size_t size = 0;
    zelLoaderGetVersions(&size, nullptr);
    std::cout << "zelLoaderGetVersions number of components found: " << size << std::endl;
    versions = new zel_component_version_t[size];
    zelLoaderGetVersions(&size, versions);

    for(size_t i = 0; i < size; i++){
        std::cout << "Version " << i << std::endl;
        std::cout << "Name: " << versions[i].component_name << std::endl;
        std::cout << "Major: " << versions[i].component_lib_version.major << std::endl;
        std::cout << "Minor: " << versions[i].component_lib_version.minor << std::endl;
        std::cout << "Patch: " << versions[i].component_lib_version.patch << std::endl;
    }

    delete[] versions;
}

#if defined(_WIN32)
    #define putenv_safe _putenv
#else
    #define putenv_safe putenv
#endif

//////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
    bool tracing_runtime_enabled = false;
    bool legacy_init = false;
    if( argparse( argc, argv, "-null", "--enable_null_driver" ) )
    {
        putenv_safe( const_cast<char *>( "ZE_ENABLE_NULL_DRIVER=1" ) );
    }
    if( argparse( argc, argv, "-ldr", "--force_loader_intercepts" ) )
    {
        putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
    }
    if( argparse( argc, argv, "-val", "--enable_validation_layer" ) )
    {
        putenv_safe( const_cast<char *>( "ZE_ENABLE_VALIDATION_LAYER=1" ) );
        putenv_safe( const_cast<char *>( "ZE_ENABLE_PARAMETER_VALIDATION=1" ) );
    }
    if( argparse( argc, argv, "-trace", "--enable_tracing_layer" ) )
    {
        putenv_safe( const_cast<char *>( "ZE_ENABLE_TRACING_LAYER=1" ) );
    }
    if( argparse( argc, argv, "-tracerun", "--enable_tracing_layer_runtime" ) )
    {
        tracing_runtime_enabled = true;
    }
    if( argparse( argc, argv, "-legacy_init", "--enable_legacy_init" ) )
    {
        legacy_init = true;
    }

    ze_result_t status;
    const ze_device_type_t type = ZE_DEVICE_TYPE_GPU;

    ze_init_driver_type_desc_t driverTypeDesc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    driverTypeDesc.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU;
    driverTypeDesc.pNext = nullptr;

    ze_driver_handle_t pDriver = nullptr;
    ze_device_handle_t pDevice = nullptr;
    uint32_t driverCount = 0;
    if( init_ze(legacy_init, driverCount, driverTypeDesc) )
    {

        print_loader_versions();

        if (tracing_runtime_enabled) {
            std::cout << "Enabling Tracing Layer after init" << std::endl;
            status = zelEnableTracingLayer();
            if(status != ZE_RESULT_SUCCESS) {
                std::cout << "zelEnableTracingLayer Failed with return code: " << to_string(status) << std::endl;
                exit(1);
            }
        }

        std::vector<ze_driver_handle_t> drivers;
        if (legacy_init) {
            status = zeDriverGet(&driverCount, nullptr);
            if(status != ZE_RESULT_SUCCESS) {
                std::cout << "zeDriverGet Failed with return code: " << to_string(status) << std::endl;
                exit(1);
            }

            drivers.resize(driverCount);
            status = zeDriverGet( &driverCount, drivers.data() );
            if(status != ZE_RESULT_SUCCESS) {
                std::cout << "zeDriverGet Failed with return code: " << to_string(status) << std::endl;
                exit(1);
            }
        } else {
            drivers.resize(driverCount);
            status = zeInitDrivers( &driverCount, drivers.data(), &driverTypeDesc);
            if(status != ZE_RESULT_SUCCESS) {
                std::cout << "zeInitDrivers Failed with return code: " << to_string(status) << std::endl;
                exit(1);
            }
        }

        for( uint32_t driver = 0; driver < driverCount; ++driver )
        {
            pDriver = drivers[driver];
            pDevice = findDevice( pDriver, type );
            if( pDevice )
            {
                break;
            }
        }
    }

    if( !pDevice )
    {
        std::cout << "Did NOT find matching " << to_string(type) <<" device!" << "\n";
        return -1;
    }


    // Create the context
    ze_context_handle_t context;
    ze_context_desc_t context_desc = {};
    context_desc.stype = ZE_STRUCTURE_TYPE_CONTEXT_DESC;
    status = zeContextCreate(pDriver, &context_desc, &context);
    if(status != ZE_RESULT_SUCCESS) {
        std::cout << "zeContextCreate Failed with return code: " << to_string(status) << std::endl;
        exit(1);
    }

    // Create an immediate command list for direct submission
    ze_command_queue_desc_t altdesc = {};
    altdesc.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC;
    ze_command_list_handle_t command_list = {};
    status = zeCommandListCreateImmediate(context, pDevice, &altdesc, &command_list);
    if(status != ZE_RESULT_SUCCESS) {
        std::cout << "zeCommandListCreateImmediate Failed with return code: " << to_string(status) << std::endl;
        exit(1);
    }

    // Create an event to be signaled by the device
    ze_event_pool_desc_t ep_desc = {};
    ep_desc.stype = ZE_STRUCTURE_TYPE_EVENT_POOL_DESC;
    ep_desc.count = 1;
    ep_desc.flags = ZE_EVENT_POOL_FLAG_HOST_VISIBLE;
    ze_event_desc_t ev_desc = {};
    ev_desc.stype = ZE_STRUCTURE_TYPE_EVENT_DESC;
    ev_desc.signal = ZE_EVENT_SCOPE_FLAG_HOST;
    ev_desc.wait = ZE_EVENT_SCOPE_FLAG_HOST;
    ze_event_handle_t event;
    ze_event_pool_handle_t event_pool;

    status = zeEventPoolCreate(context, &ep_desc, 1, &pDevice, &event_pool);
    if(status != ZE_RESULT_SUCCESS) {
        std::cout << "zeEventPoolCreate Failed with return code: " << to_string(status) << std::endl;
        exit(1);
    }

    status = zeEventCreate(event_pool, &ev_desc, &event);
    if(status != ZE_RESULT_SUCCESS) {
        std::cout << "zeEventCreate Failed with return code: " << to_string(status) << std::endl;
        exit(1);
    }

    // signal the event from the device and wait for completion
    zeCommandListAppendSignalEvent(command_list, event);
    zeEventHostSynchronize(event, UINT64_MAX );
    std::cout << "Congratulations, the device completed execution!\n";

    zeContextDestroy(context);
    zeCommandListDestroy(command_list);
    zeEventDestroy(event);
    zeEventPoolDestroy(event_pool);

    if (tracing_runtime_enabled) {
        std::cout << "Disable Tracing Layer after init" << std::endl;
        status = zelDisableTracingLayer();
        if(status != ZE_RESULT_SUCCESS) {
            std::cout << "zelDisableTracingLayer Failed with return code: " << to_string(status) << std::endl;
            exit(1);
        }
    }

    return 0;
}