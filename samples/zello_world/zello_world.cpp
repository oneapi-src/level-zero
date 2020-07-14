/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include <stdlib.h>
#include <memory>

#include "zello_init.h"

//////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
    if( argparse( argc, argv, "-null", "--enable_null_driver" ) )
    {
        putenv( const_cast<char *>( "ZE_ENABLE_NULL_DRIVER=1" ) );
    }
    if( argparse( argc, argv, "-ldr", "--force_loader_intercepts" ) )
    {
        putenv( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
    }
    if( argparse( argc, argv, "-val", "--enable_validation_layer" ) )
    {
        putenv( const_cast<char *>( "ZE_ENABLE_VALIDATION_LAYER=1" ) );
        putenv( const_cast<char *>( "ZE_ENABLE_PARAMETER_VALIDATION=1" ) );
    }

    const ze::Device::type_t type = ze::Device::type_t::GPU;

    ze::Driver* pDriver = nullptr;
    ze::Device* pDevice = nullptr;
    if( init_ze() )
    {
        uint32_t driverCount = 0;
        ze::Driver::Get( &driverCount );

        std::vector<ze::Driver*> drivers( driverCount );
        ze::Driver::Get( &driverCount, drivers.data() );

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
        std::cout << "Did NOT find matching " << ze::to_string(type) <<" device!" << "\n";
        return -1;
    }

    try
    {
        // Create the context
        ze::Context::desc_t context_desc;
        auto pContext = std::shared_ptr<ze::Context>(
            ze::Context::Create(pDriver, &context_desc),
            []( ze::Context* p ) { ze::Context::Destroy( p ); } );

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

        // signal the event from the device and wait for completion
        pCommandList->AppendSignalEvent( pEvent.get() );
        pEvent->HostSynchronize( UINT32_MAX );
        std::cout << "Congratulations, the device completed execution!\n";
    }
    catch( const ze::exception_t& e )
    {
        std::cout << e.what();
        return -1;
    }

    return 0;
}