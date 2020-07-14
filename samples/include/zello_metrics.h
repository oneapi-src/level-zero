/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#include "zello_init.h"

//////////////////////////////////////////////////////////////////////////
inline zet::MetricGroup* findMetricGroup(
    zet::Device* pDevice,
    const zet::MetricGroup::sampling_type_flags_t type,
    const char* name = "" )
{
    uint32_t groupCount = 0;
    zet::MetricGroup::Get( pDevice, &groupCount );

    std::vector< zet::MetricGroup*> metricGroups( groupCount );
    zet::MetricGroup::Get( pDevice, &groupCount, metricGroups.data() );

    zet::MetricGroup* found = nullptr;

    // for each device group, find the first one matching the type
    for( uint32_t grp = 0; grp < groupCount; ++grp )
    {
        auto pMetricGroup = metricGroups[ grp ];
        zet::MetricGroup::properties_t metric_group_properties;
        pMetricGroup->GetProperties( &metric_group_properties );

        if( 0 != ( static_cast<uint32_t>(type) & static_cast<uint32_t>(metric_group_properties.samplingType) ) )
        {
            if( ( 0 == strlen(name) ) || ( 0 == strcmp( name, metric_group_properties.name ) ) )
            {
                found = pMetricGroup;

                std::cout << "Found " << zet::to_string( type ) << " metric group..." << "\n";
                std::cout << zet::to_string( metric_group_properties ) << "\n";
            }
        }
    }
    if( !found )
    {
        std::cout << "Did NOT find matching " << zet::to_string( type ) << " device group!" << "\n";
    }

    return found;
}

//////////////////////////////////////////////////////////////////////////
inline void calculateResults( zet::MetricGroup* pMetricGroup, zet::MetricQuery* pQuery )
{
    // Read raw data from query
    size_t rawDataSize = 0;
    pQuery->GetData( &rawDataSize, nullptr );
    std::vector<uint8_t> rawData( rawDataSize );
    pQuery->GetData( &rawDataSize, rawData.data() );

    // Calculate results
    uint32_t numMetricValues = 0;
    zet::MetricGroup::CalculateMetricValues( pMetricGroup, zet::MetricGroup::calculation_type_t::METRIC_VALUES, rawDataSize, rawData.data(), &numMetricValues );
    std::vector<zet::typed_value_t> metricValues( numMetricValues );
    zet::MetricGroup::CalculateMetricValues( pMetricGroup, zet::MetricGroup::calculation_type_t::METRIC_VALUES, rawDataSize, rawData.data(), &numMetricValues, metricValues.data() );

    // get metric info
    uint32_t metricCount = 0;
    zet::Metric::Get( pMetricGroup, &metricCount, nullptr );
    std::vector< zet::Metric* > metrics( metricCount );
    zet::Metric::Get( pMetricGroup, &metricCount, metrics.data() );

    // Report results
    std::cout << "Compute Basic results:\n";
    uint32_t numReports = numMetricValues / metricCount;
    for( uint32_t report = 0; report < numReports; ++report )
    {
        for( uint32_t metric = 0; metric < metricCount; ++metric )
        {
            zet::Metric::properties_t metric_properties;
            metrics[ metric ]->GetProperties( &metric_properties );

            auto& result = metricValues[ report * metricCount + metric ];
            std::cout << metric_properties.name << " (" << metric_properties.resultUnits << ") :\n";
            std::cout << zet::to_string( result ) << "\n";
        }
    }
}
