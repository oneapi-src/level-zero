/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include <stdlib.h>
#include <memory>

#include "zello_metrics.h"

//////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
    if( argparse( argc, argv, "-null", "--enable_null_driver" ) )
    {
        putenv( const_cast<char *>( "ZE_ENABLE_NULL_DRIVER=1" ) );
    }

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
                break;
            }
        }
    }
    if( !pDevice )
        return -1;

    // Find an event-based metric group
    auto pMetricGroup = findMetricGroup( pDevice, zet::MetricGroup::SAMPLING_TYPE_FLAG_EVENT_BASED );
    if( !pMetricGroup )
        return -1;

    try
    {
        // Create the context
        ze::Context::desc_t context_desc;
        auto pContext = std::shared_ptr<zet::Context>(
            reinterpret_cast<zet::Context*>( ze::Context::Create( pDriver, &context_desc ) ),
            []( zet::Context* p ){ ze::Context::Destroy( reinterpret_cast<ze::Context*>( p ) ); } );

        // Active the metric group on the device
        pContext->ActivateMetricGroups( pDevice, 1, &pMetricGroup );

        // Create an immediate command list for direct submission
        ze::CommandQueue::desc_t queue_desc;
        auto pCommandList = std::shared_ptr<zet::CommandList>(
            reinterpret_cast<zet::CommandList*>( ze::CommandList::CreateImmediate( pContext.get(), pDevice, &queue_desc ) ),
            []( zet::CommandList* p ){ ze::CommandList::Destroy( reinterpret_cast<ze::CommandList*>( p ) ); } );

        // Create an event to be signaled by the device
        uint32_t numSamples = 1;
        ze::EventPool::desc_t pool_desc;
        pool_desc.flags = ze::EventPool::FLAG_HOST_VISIBLE;
        pool_desc.count = numSamples;
        auto pEventPool = std::shared_ptr<ze::EventPool>(
            ze::EventPool::Create( pContext.get(), &pool_desc, 0, nullptr ),
            []( ze::EventPool* p ){ ze::EventPool::Destroy( p ); } );

        ze::Event::desc_t event_desc;
        event_desc.signal = ze::Event::SCOPE_FLAG_HOST;
        event_desc.index = 0;
        auto pEvent = std::shared_ptr<ze::Event>(
            ze::Event::Create( pEventPool.get(), &event_desc ),
            []( ze::Event* p ){ ze::Event::Destroy( p ); } );

        // Create metric query
        zet::MetricQueryPool::desc_t query_pool_desc;
        query_pool_desc.count = numSamples;
        auto pQueryPool = std::shared_ptr<zet::MetricQueryPool>(
            zet::MetricQueryPool::Create( pContext.get(), pDevice, pMetricGroup, &query_pool_desc ),
            []( zet::MetricQueryPool* p ){ zet::MetricQueryPool::Destroy( p ); } );

        auto pQuery = std::shared_ptr<zet::MetricQuery>(
            zet::MetricQuery::Create( pQueryPool.get(), 0 ),
            []( zet::MetricQuery* p ){ zet::MetricQuery::Destroy( p ); } );

        // Sample data from device and wait for completion
        pCommandList->AppendMetricQueryBegin( pQuery.get() );
        pCommandList->AppendMetricQueryEnd( pQuery.get(), pEvent.get() );
        pEvent->HostSynchronize( UINT32_MAX );

        calculateResults( pMetricGroup, pQuery.get() );
    }
    catch( const ze::exception_t& e )
    {
        std::cout << e.what();
        return -1;
    }

    return 0;
}