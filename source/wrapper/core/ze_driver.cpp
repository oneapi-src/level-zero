/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_driver.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs
 *
 */
#include "ze_api.hpp"
#include "ze_singleton.h"

#define _STRING(s) #s
#define STRING(s) _STRING(s)

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    Driver::Driver( 
        driver_handle_t handle                          ///< [in] handle of the driver instance
        ) :
        m_handle( handle )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initialize the 'One API' driver and must be called before any other
    ///        API function
    /// 
    /// @details
    ///     - If this function is not called then all other functions will return
    ///       ::ZE_RESULT_ERROR_UNINITIALIZED.
    ///     - Only one instance of a driver per process will be initialized.
    ///     - This function is thread-safe for scenarios where multiple libraries
    ///       may initialize the driver simultaneously.
    /// 
    /// @throws result_t
    void __zecall
    Init(
        init_flag_t flags                               ///< [in] initialization flags
        )
    {
        auto result = static_cast<result_t>( ::zeInit(
            static_cast<ze_init_flag_t>( flags ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::::Init" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves driver instances
    /// 
    /// @details
    ///     - A driver represents a collection of physical devices.
    ///     - The application may pass nullptr for pDrivers when only querying the
    ///       number of drivers.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clGetPlatformIDs
    /// 
    /// @throws result_t
    void __zecall
    Driver::Get(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                        ///< if count is zero, then the loader will update the value with the total
                                                        ///< number of drivers available.
                                                        ///< if count is non-zero, then the loader will only retrieve that number
                                                        ///< of drivers.
                                                        ///< if count is larger than the number of drivers available, then the
                                                        ///< loader will update the value with the correct number of drivers available.
        Driver** ppDrivers                              ///< [in,out][optional][range(0, *pCount)] array of driver instance handles
        )
    {
        thread_local std::vector<ze_driver_handle_t> hDrivers;
        hDrivers.resize( ( ppDrivers ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zeDriverGet(
            pCount,
            hDrivers.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::Get" );

        for( uint32_t i = 0; ( ppDrivers ) && ( i < *pCount ); ++i )
            ppDrivers[ i ] = nullptr;

        try
        {
            static singleton_factory_t<Driver, driver_handle_t> driverFactory;

            for( uint32_t i = 0; ( ppDrivers ) && ( i < *pCount ); ++i )
                ppDrivers[ i ] = driverFactory.getInstance( reinterpret_cast<driver_handle_t>( hDrivers[ i ] ) );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::Driver::Get" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns the API version supported by the specified driver
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - api_version_t: api version
    /// 
    /// @throws result_t
    Driver::api_version_t __zecall
    Driver::GetApiVersion(
        void
        )
    {
        ze_api_version_t version;

        auto result = static_cast<result_t>( ::zeDriverGetApiVersion(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            &version ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::GetApiVersion" );

        return *reinterpret_cast<api_version_t*>( &version );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves properties of the driver.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clGetPlatformInfo**
    /// 
    /// @throws result_t
    void __zecall
    Driver::GetProperties(
        properties_t* pDriverProperties                 ///< [in,out] query result for driver properties
        )
    {
        auto result = static_cast<result_t>( ::zeDriverGetProperties(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            reinterpret_cast<ze_driver_properties_t*>( pDriverProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves IPC attributes of the driver
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - ipc_properties_t: query result for IPC properties
    /// 
    /// @throws result_t
    Driver::ipc_properties_t __zecall
    Driver::GetIPCProperties(
        void
        )
    {
        ze_driver_ipc_properties_t iPCProperties;

        auto result = static_cast<result_t>( ::zeDriverGetIPCProperties(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            &iPCProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::GetIPCProperties" );

        return *reinterpret_cast<ipc_properties_t*>( &iPCProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves an extension function for the specified driver
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clGetExtensionFunctionAddressForPlatform**
    /// 
    /// @returns
    ///     - void*: pointer to extension function
    /// 
    /// @throws result_t
    void* __zecall
    Driver::GetExtensionFunctionAddress(
        const char* pFuncName                           ///< [in] name of the extension function
        )
    {
        void* pfunc;

        auto result = static_cast<result_t>( ::zeDriverGetExtensionFunctionAddress(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            pFuncName,
            &pfunc ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Driver::GetExtensionFunctionAddress" );

        return pfunc;
    }

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts init_flag_t to std::string
    std::string to_string( const init_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(init_flag_t::GPU_ONLY) & bits )
            str += "GPU_ONLY | ";

        return ( str.size() > 3 ) 
            ? "init_flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "init_flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts driver_uuid_t to std::string
    std::string to_string( const driver_uuid_t val )
    {
        std::string str;
        
        str += "driver_uuid_t::id : ";
        {
            std::string tmp;
            for( auto& entry : val.id )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::api_version_t to std::string
    std::string to_string( const Driver::api_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::api_version_t::_1_0:
            str = "Driver::api_version_t::_1_0";
            break;

        default:
            str = "Driver::api_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::properties_version_t to std::string
    std::string to_string( const Driver::properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::properties_version_t::CURRENT:
            str = "Driver::properties_version_t::CURRENT";
            break;

        default:
            str = "Driver::properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::ipc_properties_version_t to std::string
    std::string to_string( const Driver::ipc_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::ipc_properties_version_t::CURRENT:
            str = "Driver::ipc_properties_version_t::CURRENT";
            break;

        default:
            str = "Driver::ipc_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::device_mem_alloc_desc_version_t to std::string
    std::string to_string( const Driver::device_mem_alloc_desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::device_mem_alloc_desc_version_t::CURRENT:
            str = "Driver::device_mem_alloc_desc_version_t::CURRENT";
            break;

        default:
            str = "Driver::device_mem_alloc_desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::device_mem_alloc_flag_t to std::string
    std::string to_string( const Driver::device_mem_alloc_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "DEFAULT   ";
        
        if( static_cast<uint32_t>(Driver::device_mem_alloc_flag_t::BIAS_CACHED) & bits )
            str += "BIAS_CACHED | ";
        
        if( static_cast<uint32_t>(Driver::device_mem_alloc_flag_t::BIAS_UNCACHED) & bits )
            str += "BIAS_UNCACHED | ";

        return ( str.size() > 3 ) 
            ? "Driver::device_mem_alloc_flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Driver::device_mem_alloc_flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::host_mem_alloc_desc_version_t to std::string
    std::string to_string( const Driver::host_mem_alloc_desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::host_mem_alloc_desc_version_t::CURRENT:
            str = "Driver::host_mem_alloc_desc_version_t::CURRENT";
            break;

        default:
            str = "Driver::host_mem_alloc_desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::host_mem_alloc_flag_t to std::string
    std::string to_string( const Driver::host_mem_alloc_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "DEFAULT   ";
        
        if( static_cast<uint32_t>(Driver::host_mem_alloc_flag_t::BIAS_CACHED) & bits )
            str += "BIAS_CACHED | ";
        
        if( static_cast<uint32_t>(Driver::host_mem_alloc_flag_t::BIAS_UNCACHED) & bits )
            str += "BIAS_UNCACHED | ";
        
        if( static_cast<uint32_t>(Driver::host_mem_alloc_flag_t::BIAS_WRITE_COMBINED) & bits )
            str += "BIAS_WRITE_COMBINED | ";

        return ( str.size() > 3 ) 
            ? "Driver::host_mem_alloc_flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Driver::host_mem_alloc_flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::memory_allocation_properties_version_t to std::string
    std::string to_string( const Driver::memory_allocation_properties_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::memory_allocation_properties_version_t::CURRENT:
            str = "Driver::memory_allocation_properties_version_t::CURRENT";
            break;

        default:
            str = "Driver::memory_allocation_properties_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::memory_type_t to std::string
    std::string to_string( const Driver::memory_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::memory_type_t::UNKNOWN:
            str = "Driver::memory_type_t::UNKNOWN";
            break;

        case Driver::memory_type_t::HOST:
            str = "Driver::memory_type_t::HOST";
            break;

        case Driver::memory_type_t::DEVICE:
            str = "Driver::memory_type_t::DEVICE";
            break;

        case Driver::memory_type_t::SHARED:
            str = "Driver::memory_type_t::SHARED";
            break;

        default:
            str = "Driver::memory_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::ipc_memory_flag_t to std::string
    std::string to_string( const Driver::ipc_memory_flag_t val )
    {
        std::string str;

        switch( val )
        {
        case Driver::ipc_memory_flag_t::NONE:
            str = "Driver::ipc_memory_flag_t::NONE";
            break;

        default:
            str = "Driver::ipc_memory_flag_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::properties_t to std::string
    std::string to_string( const Driver::properties_t val )
    {
        std::string str;
        
        str += "Driver::properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Driver::properties_t::uuid : ";
        str += to_string(val.uuid);
        str += "\n";
        
        str += "Driver::properties_t::driverVersion : ";
        str += std::to_string(val.driverVersion);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::ipc_properties_t to std::string
    std::string to_string( const Driver::ipc_properties_t val )
    {
        std::string str;
        
        str += "Driver::ipc_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Driver::ipc_properties_t::memsSupported : ";
        str += std::to_string(val.memsSupported);
        str += "\n";
        
        str += "Driver::ipc_properties_t::eventsSupported : ";
        str += std::to_string(val.eventsSupported);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::device_mem_alloc_desc_t to std::string
    std::string to_string( const Driver::device_mem_alloc_desc_t val )
    {
        std::string str;
        
        str += "Driver::device_mem_alloc_desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Driver::device_mem_alloc_desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Driver::device_mem_alloc_desc_t::ordinal : ";
        str += std::to_string(val.ordinal);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::host_mem_alloc_desc_t to std::string
    std::string to_string( const Driver::host_mem_alloc_desc_t val )
    {
        std::string str;
        
        str += "Driver::host_mem_alloc_desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Driver::host_mem_alloc_desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::memory_allocation_properties_t to std::string
    std::string to_string( const Driver::memory_allocation_properties_t val )
    {
        std::string str;
        
        str += "Driver::memory_allocation_properties_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Driver::memory_allocation_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Driver::memory_allocation_properties_t::id : ";
        str += std::to_string(val.id);
        str += "\n";

        return str;
    }

} // namespace ze
