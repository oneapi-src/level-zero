/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include <stdlib.h>
#include <memory>
#include <chrono>

#include "zello_init.h"

//////////////////////////////////////////////////////////////////////////
struct my_tracer_data_t
{
    uint32_t instance = 0;
};

using time_point_t = std::chrono::time_point<std::chrono::high_resolution_clock>;

struct my_instance_data_t
{
    time_point_t start;
};


//////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
    if( argparse( argc, argv, "-null", "--enable_null_driver" ) )
        putenv( const_cast<char *>( "ZE_ENABLE_NULL_DRIVER=1" ) );

    putenv( const_cast<char *>( "ZE_ENABLE_API_TRACING=1" ) );

    const ze::Device::type_t type = ze::Device::type_t::GPU;

    zet::Driver* pDriver = nullptr;
    zet::Device* pDevice = nullptr;
    if( init_ze() )
    {
        uint32_t driverCount = 0;
        ze::Driver::Get( &driverCount );

        std::vector<ze::Driver*> drivers( driverCount );
        ze::Driver::Get( &driverCount, drivers.data() );

        for( uint32_t driver = 0; driver < driverCount; ++driver )
        {
            pDriver = reinterpret_cast<zet::Driver*>( drivers[driver] );
            pDevice = reinterpret_cast<zet::Device*>( findDevice( pDriver, type ) );
            if( pDevice )
            {
                uint32_t extensionCount = 0;
                pDriver->GetExtensionProperties( &extensionCount );
                std::vector<ze::Driver::extension_properties_t> extensions( extensionCount );
                pDriver->GetExtensionProperties( &extensionCount, extensions.data() );

                bool apiTracingSupported = false;
                for( auto& extn : extensions )
                    if( strcmp( extn.name, ZET_API_TRACING_EXP_NAME ) )
                    {
                        apiTracingSupported = true;
                        break;
                    }

                if( apiTracingSupported )
                    break;
            }
        }
    }
    if( !pDevice )
        return -1;

    try
    {
        // Create the context
        ze::Context::desc_t context_desc;
        auto pContext = std::shared_ptr<zet::Context>(
            reinterpret_cast<zet::Context*>( ze::Context::Create( pDriver, &context_desc ) ),
            []( zet::Context* p ) { ze::Context::Destroy( reinterpret_cast<ze::Context*>( p ) ); } );

        // Create an immediate command list for direct submission
        ze::CommandQueue::desc_t queue_desc;
        auto pCommandList = std::shared_ptr<ze::CommandList>(
            ze::CommandList::CreateImmediate( pContext.get(), pDevice, &queue_desc ),
            []( ze::CommandList* p ){ ze::CommandList::Destroy( p ); } );

        // Create an event to be signaled by the device
        ze::EventPool::desc_t pool_desc;
        pool_desc.flags = ze::EventPool::FLAG_HOST_VISIBLE;
        pool_desc.count = 1;
        auto pEventPool = std::shared_ptr<ze::EventPool>(
            ze::EventPool::Create( pContext.get(), &pool_desc, 0, nullptr ),
            []( ze::EventPool* p ){ ze::EventPool::Destroy( p ); } );

        ze::Event::desc_t event_desc;
        event_desc.signal = ze::Event::SCOPE_FLAG_HOST;
        event_desc.index = 0;
        auto pEvent = std::shared_ptr<ze::Event>(
            ze::Event::Create( pEventPool.get(), &event_desc ),
            []( ze::Event* p ){ ze::Event::Destroy( p ); } );

        // Create a tracer for the event call
        my_tracer_data_t gbl;
        zet::TracerExp::desc_t tracer_desc;
        tracer_desc.pUserData = &gbl;
        auto pTracer = std::shared_ptr<zet::TracerExp>(
            zet::TracerExp::Create( pContext.get(), &tracer_desc ),
            []( zet::TracerExp* p ){ zet::TracerExp::Destroy( p ); } );

        // Set the callbacks
        zet::TracerExp::core_callbacks_t prologCbs = {};
        prologCbs.CommandList.pfnAppendSignalEventCb = [](
            ze_command_list_append_signal_event_params_t*, ze_result_t,
            void* pTracerUserData,
            void** ppTracerInstanceUserData )
        {
            my_instance_data_t* instance_data = new my_instance_data_t;
            *ppTracerInstanceUserData = instance_data;

            instance_data->start = std::chrono::high_resolution_clock::now();
        };
        pTracer->SetPrologues( &prologCbs );

        zet::TracerExp::core_callbacks_t epilogCbs = {};
        epilogCbs.CommandList.pfnAppendSignalEventCb = [](
            ze_command_list_append_signal_event_params_t*, ze_result_t,
            void* pTracerUserData,
            void** ppTracerInstanceUserData )
        {
            auto end = std::chrono::high_resolution_clock::now();

            my_tracer_data_t* tracer_data = reinterpret_cast<my_tracer_data_t*>( pTracerUserData );
            my_instance_data_t* instance_data = *reinterpret_cast<my_instance_data_t**>( ppTracerInstanceUserData );

            std::chrono::duration<double, std::micro> diff = end - instance_data->start;
            std::cout << "AppendSignalEvent #" << tracer_data->instance++ << " took : " << diff.count() << " us\n";

            delete instance_data;
        };
        pTracer->SetEpilogues( &epilogCbs );

        // enable the tracer
        pTracer->SetEnabled( true );

        // signal the event(s) from the device and wait for completion
        pCommandList->AppendSignalEvent( pEvent.get() );
        pEvent->HostSynchronize( UINT32_MAX );
        pEvent->HostReset();

        pCommandList->AppendSignalEvent( pEvent.get() );
        pEvent->HostSynchronize( UINT32_MAX );
        pEvent->HostReset();

    }
    catch( const ze::exception_t& e )
    {
        std::cout << e.what();
        return -1;
    }

    return 0;
}