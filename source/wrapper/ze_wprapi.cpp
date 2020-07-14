/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_wprapi.cpp
 *
 * @brief C++ wrapper of ze
 *
 */
#include "ze_api.hpp"
#include "ze_singleton.h"

#define _ZE_STRING(s) #s
#define ZE_STRING(s) _ZE_STRING(s)

namespace ze
{
#pragma region common
    ///////////////////////////////////////////////////////////////////////////////
    std::string exception_t::formatted(
        const result_t result,
        const char* file,
        const char* line,
        const char* func )
    {
    #ifdef _DEBUG
        std::stringstream msg;
        msg << file << "(" << line << ") : exception : " << func << "(" << ze::to_string(result) << ")";
        return msg.str();
    #else
        return ze::to_string(result);
    #endif
    }

#pragma endregion
#pragma region driver
    ///////////////////////////////////////////////////////////////////////////////
    Driver::Driver( 
        driver_handle_t handle                          ///< [in] handle of the driver instance
        ) :
        m_handle( handle )
    {
    }

    static singleton_factory_t<Driver, driver_handle_t> g_DriverFactory;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initialize the 'oneAPI' driver(s)
    /// 
    /// @details
    ///     - This function must be called before any other API function.
    ///     - If this function is not called then all other functions will return
    ///       ::ZE_RESULT_ERROR_UNINITIALIZED.
    ///     - Only one instance of each driver will be initialized per process.
    ///     - This function is thread-safe for scenarios where multiple libraries
    ///       may initialize the driver(s) simultaneously.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Init(
        init_flags_t flags                              ///< [in] initialization flags.
                                                        ///< must be 0 (default) or a combination of ::ze_init_flag_t.
        )
    {
        auto result = static_cast<result_t>( ::zeInit(
            static_cast<ze_init_flags_t>( flags ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::::Init" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves driver instances
    /// 
    /// @details
    ///     - A driver represents a collection of physical devices.
    ///     - Multiple calls to this function will return identical driver handles,
    ///       in the same order.
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
    void ZE_APICALL
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
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::Get" );

        for( uint32_t i = 0; ( ppDrivers ) && ( i < *pCount ); ++i )
            ppDrivers[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppDrivers ) && ( i < *pCount ); ++i )
                ppDrivers[ i ] = g_DriverFactory.getInstance( reinterpret_cast<driver_handle_t>( hDrivers[ i ] ) );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Driver::Get" );
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
    Driver::api_version_t ZE_APICALL
    Driver::GetApiVersion(
        void
        )
    {
        ze_api_version_t version;

        auto result = static_cast<result_t>( ::zeDriverGetApiVersion(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            &version ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::GetApiVersion" );

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
    void ZE_APICALL
    Driver::GetProperties(
        properties_t* pDriverProperties                 ///< [in,out] query result for driver properties
        )
    {
        auto result = static_cast<result_t>( ::zeDriverGetProperties(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            reinterpret_cast<ze_driver_properties_t*>( pDriverProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::GetProperties" );
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
    Driver::ipc_properties_t ZE_APICALL
    Driver::GetIpcProperties(
        void
        )
    {
        ze_driver_ipc_properties_t ipcProperties;

        auto result = static_cast<result_t>( ::zeDriverGetIpcProperties(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            &ipcProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::GetIpcProperties" );

        return *reinterpret_cast<ipc_properties_t*>( &ipcProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves extension properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkEnumerateInstanceExtensionProperties**
    /// 
    /// @throws result_t
    void ZE_APICALL
    Driver::GetExtensionProperties(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of extension properties.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of extension properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< extension properties.
                                                        ///< if count is larger than the number of extension properties available,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< extension properties available.
        extension_properties_t* pExtensionProperties    ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< extension properties
        )
    {
        auto result = static_cast<result_t>( ::zeDriverGetExtensionProperties(
            reinterpret_cast<ze_driver_handle_t>( getHandle() ),
            pCount,
            reinterpret_cast<ze_driver_extension_properties_t*>( pExtensionProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Driver::GetExtensionProperties" );
    }

#pragma endregion
#pragma region device
    ///////////////////////////////////////////////////////////////////////////////
    Device::Device( 
        device_handle_t handle,                         ///< [in] handle of device object
        Driver* pDriver                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDriver( pDriver )
    {
    }

    static singleton_factory_t<Device, device_handle_t> g_DeviceFactory;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves devices within a driver
    /// 
    /// @details
    ///     - Multiple calls to this function will return identical device handles,
    ///       in the same order.
    ///     - The number and order of handles returned from this function is
    ///       affected by the ::ZE_AFFINITY_MASK and ::ZE_ENABLE_PCI_ID_DEVICE_ORDER
    ///       environment variables.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::Get(
        Driver* pDriver,                                ///< [in] pointer to the driver instance
        uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of devices available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of devices.
                                                        ///< if count is larger than the number of devices available, then the
                                                        ///< driver will update the value with the correct number of devices available.
        Device** ppDevices                              ///< [in,out][optional][range(0, *pCount)] array of pointer to devices
        )
    {
        thread_local std::vector<ze_device_handle_t> hDevices;
        hDevices.resize( ( ppDevices ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zeDeviceGet(
            reinterpret_cast<ze_driver_handle_t>( pDriver->getHandle() ),
            pCount,
            hDevices.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::Get" );

        for( uint32_t i = 0; ( ppDevices ) && ( i < *pCount ); ++i )
            ppDevices[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppDevices ) && ( i < *pCount ); ++i )
                ppDevices[ i ] = g_DeviceFactory.getInstance( reinterpret_cast<device_handle_t>( hDevices[ i ] ), pDriver );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Device::Get" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves a sub-device from a device
    /// 
    /// @details
    ///     - Multiple calls to this function will return identical device handles,
    ///       in the same order.
    ///     - The number of handles returned from this function is affected by the
    ///       ::ZE_AFFINITY_MASK environment variable.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clCreateSubDevices
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::GetSubDevices(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-devices.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of sub-devices available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of sub-devices.
                                                        ///< if count is larger than the number of sub-devices available, then the
                                                        ///< driver will update the value with the correct number of sub-devices available.
        Device** ppSubdevices                           ///< [in,out][optional][range(0, *pCount)] array of pointer to sub-devices
        )
    {
        thread_local std::vector<ze_device_handle_t> hSubdevices;
        hSubdevices.resize( ( ppSubdevices ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zeDeviceGetSubDevices(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            pCount,
            hSubdevices.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetSubDevices" );

        for( uint32_t i = 0; ( ppSubdevices ) && ( i < *pCount ); ++i )
            ppSubdevices[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppSubdevices ) && ( i < *pCount ); ++i )
                ppSubdevices[ i ] = g_DeviceFactory.getInstance( reinterpret_cast<device_handle_t>( hSubdevices[ i ] ), m_pDriver );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetSubDevices" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves properties of the device.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clGetDeviceInfo
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::GetProperties(
        properties_t* pDeviceProperties                 ///< [in,out] query result for device properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_properties_t*>( pDeviceProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves compute properties of the device.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clGetDeviceInfo
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::GetComputeProperties(
        compute_properties_t* pComputeProperties        ///< [in,out] query result for compute properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetComputeProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_compute_properties_t*>( pComputeProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetComputeProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves module properties of the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::GetModuleProperties(
        module_properties_t* pModuleProperties          ///< [in,out] query result for module properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetModuleProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_module_properties_t*>( pModuleProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetModuleProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves command queue group properties of the device.
    /// 
    /// @details
    ///     - Properties are reported for each physical command queue type supported
    ///       by the device.
    ///     - Multiple calls to this function will return properties in the same
    ///       order.
    ///     - The order in which the properties are returned defines the command
    ///       queue group's ordinal.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkGetPhysicalDeviceQueueFamilyProperties**
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::GetCommandQueueGroupProperties(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of command queue group properties.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of command queue group properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< command queue group properties.
                                                        ///< if count is larger than the number of command queue group properties
                                                        ///< available, then the driver will update the value with the correct
                                                        ///< number of command queue group properties available.
        command_queue_group_properties_t* pCommandQueueGroupProperties  ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< command queue group properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetCommandQueueGroupProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            pCount,
            reinterpret_cast<ze_command_queue_group_properties_t*>( pCommandQueueGroupProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetCommandQueueGroupProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves local memory properties of the device.
    /// 
    /// @details
    ///     - Properties are reported for each physical memory type supported by the
    ///       device.
    ///     - Multiple calls to this function will return properties in the same
    ///       order.
    ///     - The order in which the properties are returned defines the device's
    ///       local memory ordinal.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clGetDeviceInfo
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::GetMemoryProperties(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of memory properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< memory properties.
                                                        ///< if count is larger than the number of memory properties available,
                                                        ///< then the driver will update the value with the correct number of
                                                        ///< memory properties available.
        memory_properties_t* pMemProperties             ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                        ///< memory properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetMemoryProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            pCount,
            reinterpret_cast<ze_device_memory_properties_t*>( pMemProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetMemoryProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves memory access properties of the device.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clGetDeviceInfo
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::GetMemoryAccessProperties(
        memory_access_properties_t* pMemAccessProperties///< [in,out] query result for memory access properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetMemoryAccessProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_memory_access_properties_t*>( pMemAccessProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetMemoryAccessProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves cache properties of the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clGetDeviceInfo
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::GetCacheProperties(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of cache properties.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of cache properties available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of
                                                        ///< cache properties.
                                                        ///< if count is larger than the number of cache properties available, then
                                                        ///< the driver will update the value with the correct number of cache
                                                        ///< properties available.
        cache_properties_t* pCacheProperties            ///< [in,out][optional][range(0, *pCount)] array of query results for cache
                                                        ///< properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetCacheProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            pCount,
            reinterpret_cast<ze_device_cache_properties_t*>( pCacheProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetCacheProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves image properties of the device
    /// 
    /// @details
    ///     - See ::zeImageGetProperties for format-specific capabilities.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::GetImageProperties(
        image_properties_t* pImageProperties            ///< [in,out] query result for image properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetImageProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_image_properties_t*>( pImageProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetImageProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves external memory import and export of the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::GetExternalMemoryProperties(
        external_memory_properties_t* pExternalMemoryProperties ///< [in,out] query result for external memory properties
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetExternalMemoryProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_external_memory_properties_t*>( pExternalMemoryProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetExternalMemoryProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves peer-to-peer properties between one device and a peer
    ///        devices
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::GetP2PProperties(
        Device* pPeerDevice,                            ///< [in] pointer to the peer device with the allocation
        p2p_properties_t* pP2PProperties                ///< [in,out] Peer-to-Peer properties between source and peer device
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetP2PProperties(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pPeerDevice->getHandle() ),
            reinterpret_cast<ze_device_p2p_properties_t*>( pP2PProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetP2PProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Queries if one device can directly access peer device allocations
    /// 
    /// @details
    ///     - Any device can access any other device within a node through a
    ///       scale-up fabric.
    ///     - The following are conditions for CanAccessPeer query.
    ///         + If both device and peer device are the same then return true.
    ///         + If both sub-device and peer sub-device are the same then return
    ///           true.
    ///         + If both are sub-devices and share the same parent device then
    ///           return true.
    ///         + If both device and remote device are connected by a direct or
    ///           indirect scale-up fabric or over PCIe (same root complex or shared
    ///           PCIe switch) then true.
    ///         + If both sub-device and remote parent device (and vice-versa) are
    ///           connected by a direct or indirect scale-up fabric or over PCIe
    ///           (same root complex or shared PCIe switch) then true.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - bool_t: returned access capability
    /// 
    /// @throws result_t
    bool_t ZE_APICALL
    Device::CanAccessPeer(
        Device* pPeerDevice                             ///< [in] pointer to the peer device with the allocation
        )
    {
        ze_bool_t value;

        auto result = static_cast<result_t>( ::zeDeviceCanAccessPeer(
            reinterpret_cast<ze_device_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pPeerDevice->getHandle() ),
            &value ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::CanAccessPeer" );

        return *reinterpret_cast<bool_t*>( &value );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns current status of the device.
    /// 
    /// @details
    ///     - Once a device is reset, this call will update the OS handle attached
    ///       to the device handle.
    ///     - The application may call this function from simultaneous threads with
    ///       the same device handle.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::GetStatus(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeDeviceGetStatus(
            reinterpret_cast<ze_device_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Device::GetStatus" );
    }

#pragma endregion
#pragma region context
    ///////////////////////////////////////////////////////////////////////////////
    Context::Context( 
        context_handle_t handle,                        ///< [in] handle of context object
        Driver* pDriver                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDriver( pDriver )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a context for the driver.
    /// 
    /// @details
    ///     - The application must only use the context for the driver which was
    ///       provided during creation.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - Context*: pointer to handle of context object created
    /// 
    /// @throws result_t
    Context* ZE_APICALL
    Context::Create(
        Driver* pDriver,                                ///< [in] pointer to the driver object
        const desc_t* desc                              ///< [in] pointer to context descriptor
        )
    {
        ze_context_handle_t hContext;

        auto result = static_cast<result_t>( ::zeContextCreate(
            reinterpret_cast<ze_driver_handle_t>( pDriver->getHandle() ),
            reinterpret_cast<const ze_context_desc_t*>( desc ),
            &hContext ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Context::Create" );

        Context* pContext = nullptr;

        try
        {
            pContext = new Context( reinterpret_cast<context_handle_t>( hContext ), pDriver );
        }
        catch( std::bad_alloc& )
        {
            delete pContext;
            pContext = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Context::Create" );
        }

        return pContext;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a context.
    /// 
    /// @details
    ///     - The application must ensure the device is not currently referencing
    ///       the context before it is deleted.
    ///     - The implementation of this function may immediately free all Host and
    ///       Device allocations associated with this context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same context handle.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Context::Destroy(
        Context* pContext                               ///< [in][release] pointer to context object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeContextDestroy(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Context::Destroy" );

        delete pContext;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Returns current status of the context.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads with
    ///       the same context handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Context::GetStatus(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeContextGetStatus(
            reinterpret_cast<ze_context_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Context::GetStatus" );
    }

#pragma endregion
#pragma region cmdqueue
    ///////////////////////////////////////////////////////////////////////////////
    CommandQueue::CommandQueue( 
        command_queue_handle_t handle,                  ///< [in] handle of command queue object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the command queue object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a command queue on the context.
    /// 
    /// @details
    ///     - A command queue represents a logical input stream to the device, tied
    ///       to a physical input stream.
    ///     - The application must only use the command queue for the device, or its
    ///       sub-devices, which was provided during creation.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clCreateCommandQueue**
    /// 
    /// @returns
    ///     - CommandQueue*: pointer to handle of command queue object created
    /// 
    /// @throws result_t
    CommandQueue* ZE_APICALL
    CommandQueue::Create(
        Context* pContext,                              ///< [in] pointer to the context object
        Device* pDevice,                                ///< [in] pointer to the device object
        const desc_t* desc                              ///< [in] pointer to command queue descriptor
        )
    {
        ze_command_queue_handle_t hCommandQueue;

        auto result = static_cast<result_t>( ::zeCommandQueueCreate(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_command_queue_desc_t*>( desc ),
            &hCommandQueue ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandQueue::Create" );

        CommandQueue* pCommandQueue = nullptr;

        try
        {
            pCommandQueue = new CommandQueue( reinterpret_cast<command_queue_handle_t>( hCommandQueue ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandQueue;
            pCommandQueue = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::CommandQueue::Create" );
        }

        return pCommandQueue;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a command queue.
    /// 
    /// @details
    ///     - The application must destroy all fence handles created from the
    ///       command queue before destroying the command queue itself
    ///     - The application must ensure the device is not currently referencing
    ///       the command queue before it is deleted
    ///     - The implementation of this function may immediately free all Host and
    ///       Device allocations associated with this command queue
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command queue handle.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clReleaseCommandQueue**
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandQueue::Destroy(
        CommandQueue* pCommandQueue                     ///< [in][release] pointer to command queue object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeCommandQueueDestroy(
            reinterpret_cast<ze_command_queue_handle_t>( pCommandQueue->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandQueue::Destroy" );

        delete pCommandQueue;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Executes a command list in a command queue.
    /// 
    /// @details
    ///     - The application must ensure the command lists are accessible by the
    ///       device on which the command queue was created.
    ///     - The application must only execute command lists created with an
    ///       identical command queue group ordinal to the command queue.
    ///     - The application must use a fence created using the same command queue.
    ///     - The application must ensure the command queue, command list and fence
    ///       were created on the same context.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - vkQueueSubmit
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandQueue::ExecuteCommandLists(
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        CommandList** ppCommandLists,                   ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                        ///< to execute
        Fence* pFence                                   ///< [in][optional] pointer to the fence to signal on completion
        )
    {
        thread_local std::vector<ze_command_list_handle_t> hCommandLists;
        hCommandLists.resize( 0 );
        hCommandLists.reserve( numCommandLists );
        for( uint32_t i = 0; i < numCommandLists; ++i )
            hCommandLists.emplace_back( reinterpret_cast<ze_command_list_handle_t>( ppCommandLists[ i ]->getHandle() ) );

        auto result = static_cast<result_t>( ::zeCommandQueueExecuteCommandLists(
            reinterpret_cast<ze_command_queue_handle_t>( getHandle() ),
            numCommandLists,
            hCommandLists.data(),
            ( pFence ) ? reinterpret_cast<ze_fence_handle_t>( pFence->getHandle() ) : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandQueue::ExecuteCommandLists" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Synchronizes a command queue by waiting on the host.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t ZE_APICALL
    CommandQueue::Synchronize(
        uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then immediately returns the status of the command queue;
                                                        ///< if UINT64_MAX, then function will not return until complete or device
                                                        ///< is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        auto result = static_cast<result_t>( ::zeCommandQueueSynchronize(
            reinterpret_cast<ze_command_queue_handle_t>( getHandle() ),
            timeout ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandQueue::Synchronize" );
        return 1; // true
    }

#pragma endregion
#pragma region cmdlist
    ///////////////////////////////////////////////////////////////////////////////
    CommandList::CommandList( 
        command_list_handle_t handle,                   ///< [in] handle of command list object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the command list object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a command list on the context.
    /// 
    /// @details
    ///     - A command list represents a sequence of commands for execution on a
    ///       command queue.
    ///     - The command list is created in the 'open' state.
    ///     - The application must only use the command list for the device, or its
    ///       sub-devices, which was provided during creation.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - CommandList*: pointer to handle of command list object created
    /// 
    /// @throws result_t
    CommandList* ZE_APICALL
    CommandList::Create(
        Context* pContext,                              ///< [in] pointer to the context object
        Device* pDevice,                                ///< [in] pointer to the device object
        const desc_t* desc                              ///< [in] pointer to command list descriptor
        )
    {
        ze_command_list_handle_t hCommandList;

        auto result = static_cast<result_t>( ::zeCommandListCreate(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_command_list_desc_t*>( desc ),
            &hCommandList ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::Create" );

        CommandList* pCommandList = nullptr;

        try
        {
            pCommandList = new CommandList( reinterpret_cast<command_list_handle_t>( hCommandList ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandList;
            pCommandList = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::Create" );
        }

        return pCommandList;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates an immediate command list on the context.
    /// 
    /// @details
    ///     - An immediate command list is used for low-latency submission of
    ///       commands.
    ///     - An immediate command list creates an implicit command queue.
    ///     - The command list is created in the 'open' state and never needs to be
    ///       closed.
    ///     - The application must only use the command list for the device, or its
    ///       sub-devices, which was provided during creation.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - CommandList*: pointer to handle of command list object created
    /// 
    /// @throws result_t
    CommandList* ZE_APICALL
    CommandList::CreateImmediate(
        Context* pContext,                              ///< [in] pointer to the context object
        Device* pDevice,                                ///< [in] pointer to the device object
        const CommandQueue::desc_t* altdesc             ///< [in] pointer to command queue descriptor
        )
    {
        ze_command_list_handle_t hCommandList;

        auto result = static_cast<result_t>( ::zeCommandListCreateImmediate(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_command_queue_desc_t*>( altdesc ),
            &hCommandList ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::CreateImmediate" );

        CommandList* pCommandList = nullptr;

        try
        {
            pCommandList = new CommandList( reinterpret_cast<command_list_handle_t>( hCommandList ), pDevice, nullptr );
        }
        catch( std::bad_alloc& )
        {
            delete pCommandList;
            pCommandList = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::CreateImmediate" );
        }

        return pCommandList;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a command list.
    /// 
    /// @details
    ///     - The application must ensure the device is not currently referencing
    ///       the command list before it is deleted.
    ///     - The implementation of this function may immediately free all Host and
    ///       Device allocations associated with this command list.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::Destroy(
        CommandList* pCommandList                       ///< [in][release] pointer to command list object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListDestroy(
            reinterpret_cast<ze_command_list_handle_t>( pCommandList->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::Destroy" );

        delete pCommandList;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes a command list; ready to be executed by a command queue.
    /// 
    /// @details
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::Close(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListClose(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::Close" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset a command list to initial (empty) state; ready for appending
    ///        commands.
    /// 
    /// @details
    ///     - The application must ensure the device is not currently referencing
    ///       the command list before it is reset
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::Reset(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListReset(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::Reset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends a memory write of the device's global timestamp value into a
    ///        command list.
    /// 
    /// @details
    ///     - The application must ensure the events are accessible by the device on
    ///       which the command list was created.
    ///     - The timestamp frequency can be queried from
    ///       ::ze_device_properties_t.timerResolution.
    ///     - The number of valid bits in the timestamp value can be queried from
    ///       ::ze_device_properties_t.timestampValidBits.
    ///     - The application must ensure the memory pointed to by dstptr is
    ///       accessible by the device on which the command list was created.
    ///     - The application must ensure the command list and events were created,
    ///       and the memory was allocated, on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendWriteGlobalTimestamp(
        uint64_t* dstptr,                               ///< [in,out] pointer to memory where timestamp value will be written; must
                                                        ///< be 8byte-aligned.
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing query;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before executing query
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendWriteGlobalTimestamp(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            dstptr,
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendWriteGlobalTimestamp" );
    }

#pragma endregion
#pragma region barrier
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends an execution and global memory barrier into a command list.
    /// 
    /// @details
    ///     - The application must ensure the events are accessible by the device on
    ///       which the command list was created.
    ///     - If numWaitEvents is zero, then all previous commands are completed
    ///       prior to the execution of the barrier.
    ///     - If numWaitEvents is non-zero, then then all phWaitEvents must be
    ///       signaled prior to the execution of the barrier.
    ///     - This command blocks all following commands from beginning until the
    ///       execution of the barrier completes.
    ///     - The application must ensure the signal event was **not** created from
    ///       an event pool that was created using
    ///       ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkCmdPipelineBarrier**
    ///     - clEnqueueBarrierWithWaitList
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendBarrier(
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before executing barrier
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendBarrier(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendBarrier" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends a global memory ranges barrier into a command list.
    /// 
    /// @details
    ///     - The application must ensure the events are accessible by the device on
    ///       which the command list was created.
    ///     - If numWaitEvents is zero, then all previous commands are completed
    ///       prior to the execution of the barrier.
    ///     - If numWaitEvents is non-zero, then then all phWaitEvents must be
    ///       signaled prior to the execution of the barrier.
    ///     - This command blocks all following commands from beginning until the
    ///       execution of the barrier completes.
    ///     - The application must ensure the signal event was **not** created from
    ///       an event pool that was created using
    ///       ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendMemoryRangesBarrier(
        uint32_t numRanges,                             ///< [in] number of memory ranges
        const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
        const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before executing barrier
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryRangesBarrier(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            numRanges,
            pRangeSizes,
            pRanges,
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendMemoryRangesBarrier" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Ensures in-bound writes to the device are globally observable.
    /// 
    /// @details
    ///     - This is a special-case system level barrier that can be used to ensure
    ///       global observability of writes; 
    ///       typically needed after a producer (e.g., NIC) performs direct writes
    ///       to the device's memory (e.g., Direct RDMA writes).
    ///       This is typically required when the memory corresponding to the writes
    ///       is subsequently accessed from a remote device.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Context::SystemBarrier(
        Device* pDevice                                 ///< [in] pointer to the device
        )
    {
        auto result = static_cast<result_t>( ::zeContextSystemBarrier(
            reinterpret_cast<ze_context_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Context::SystemBarrier" );
    }

#pragma endregion
#pragma region copy
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies host, device, or shared memory.
    /// 
    /// @details
    ///     - The application must ensure the memory pointed to by dstptr and srcptr
    ///       is accessible by the device on which the command list was created.
    ///     - The implementation must not access the memory pointed to by dstptr and
    ///       srcptr as they are free to be modified by either the Host or device up
    ///       until execution.
    ///     - The application must ensure the events are accessible by the device on
    ///       which the command list was created.
    ///     - The application must ensure the signal event was **not** created from
    ///       an event pool that was created using
    ///       ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
    ///     - The application must ensure the command list and events were created,
    ///       and the memory was allocated, on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clEnqueueCopyBuffer**
    ///     - **clEnqueueReadBuffer**
    ///     - **clEnqueueWriteBuffer**
    ///     - **clEnqueueSVMMemcpy**
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendMemoryCopy(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryCopy(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            dstptr,
            srcptr,
            size,
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendMemoryCopy" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes host, device, or shared memory.
    /// 
    /// @details
    ///     - The application must ensure the memory pointed to by dstptr is
    ///       accessible by the device on which the command list was created.
    ///     - The implementation must not access the memory pointed to by dstptr as
    ///       it is free to be modified by either the Host or device up until
    ///       execution.
    ///     - The value to initialize memory to is described by the pattern and the
    ///       pattern size.
    ///     - The pattern size must be a power-of-two and less than
    ///       ::ze_command_queue_group_properties_t.maxMemoryFillPatternSize.
    ///     - The application must ensure the events are accessible by the device on
    ///       which the command list was created.
    ///     - The application must ensure the signal event was **not** created from
    ///       an event pool that was created using
    ///       ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
    ///     - The application must enusre the command list and events were created,
    ///       and the memory was allocated, on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clEnqueueFillBuffer**
    ///     - **clEnqueueSVMMemFill**
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendMemoryFill(
        void* ptr,                                      ///< [in] pointer to memory to initialize
        const void* pattern,                            ///< [in] pointer to value to initialize memory to
        size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
        size_t size,                                    ///< [in] size in bytes to initialize
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryFill(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            ptr,
            pattern,
            pattern_size,
            size,
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendMemoryFill" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies a region from a 2D or 3D array of host, device, or shared
    ///        memory.
    /// 
    /// @details
    ///     - The application must ensure the memory pointed to by dstptr and srcptr
    ///       is accessible by the device on which the command list was created.
    ///     - The implementation must not access the memory pointed to by dstptr and
    ///       srcptr as they are free to be modified by either the Host or device up
    ///       until execution.
    ///     - The region width, height, and depth for both src and dst must be same.
    ///       The origins can be different.
    ///     - The src and dst regions cannot be overlapping.
    ///     - The application must ensure the events are accessible by the device on
    ///       which the command list was created.
    ///     - The application must ensure the signal event was **not** created from
    ///       an event pool that was created using
    ///       ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
    ///     - The application must ensure the command list and events were created,
    ///       and the memory was allocated, on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendMemoryCopyRegion(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const copy_region_t* dstRegion,                 ///< [in] pointer to destination region to copy to
        uint32_t dstPitch,                              ///< [in] destination pitch in bytes
        uint32_t dstSlicePitch,                         ///< [in] destination slice pitch in bytes. This is required for 3D region
                                                        ///< copies where ::ze_copy_region_t.depth is not 0, otherwise it's
                                                        ///< ignored.
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const copy_region_t* srcRegion,                 ///< [in] pointer to source region to copy from
        uint32_t srcPitch,                              ///< [in] source pitch in bytes
        uint32_t srcSlicePitch,                         ///< [in] source slice pitch in bytes. This is required for 3D region
                                                        ///< copies where ::ze_copy_region_t.depth is not 0, otherwise it's
                                                        ///< ignored.
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryCopyRegion(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            dstptr,
            reinterpret_cast<const ze_copy_region_t*>( dstRegion ),
            dstPitch,
            dstSlicePitch,
            srcptr,
            reinterpret_cast<const ze_copy_region_t*>( srcRegion ),
            srcPitch,
            srcSlicePitch,
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendMemoryCopyRegion" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies host, device, or shared memory from another context.
    /// 
    /// @details
    ///     - The current active and source context must be from the same driver.
    ///     - The application must ensure the memory pointed to by dstptr and srcptr
    ///       is accessible by the device on which the command list was created.
    ///     - The implementation must not access the memory pointed to by dstptr and
    ///       srcptr as they are free to be modified by either the Host or device up
    ///       until execution.
    ///     - The application must ensure the events are accessible by the device on
    ///       which the command list was created.
    ///     - The application must ensure the signal event was **not** created from
    ///       an event pool that was created using
    ///       ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
    ///     - The application must ensure the command list and events were created,
    ///       and the memory was allocated, on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendMemoryCopyFromContext(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        Context* pContextSrc,                           ///< [in] pointer to source context object
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryCopyFromContext(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            dstptr,
            reinterpret_cast<ze_context_handle_t>( pContextSrc->getHandle() ),
            srcptr,
            size,
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendMemoryCopyFromContext" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies an image.
    /// 
    /// @details
    ///     - The application must ensure the image and events are accessible by the
    ///       device on which the command list was created.
    ///     - The application must ensure the image format descriptors for both
    ///       source and destination images are the same.
    ///     - The application must ensure the signal event was **not** created from
    ///       an event pool that was created using
    ///       ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
    ///     - The application must ensure the command list, images and events were
    ///       created on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clEnqueueCopyImage**
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendImageCopy(
        Image* pDstImage,                               ///< [in] pointer to destination image to copy to
        Image* pSrcImage,                               ///< [in] pointer to source image to copy from
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopy(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pDstImage->getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pSrcImage->getHandle() ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendImageCopy" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies a region of an image to another image.
    /// 
    /// @details
    ///     - The application must ensure the image and events are accessible by the
    ///       device on which the command list was created.
    ///     - The region width and height for both src and dst must be same. The
    ///       origins can be different.
    ///     - The src and dst regions cannot be overlapping.
    ///     - The application must ensure the image format descriptors for both
    ///       source and destination images are the same.
    ///     - The application must ensure the signal event was **not** created from
    ///       an event pool that was created using
    ///       ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
    ///     - The application must ensure the command list, images and events were
    ///       created, and the memory was allocated, on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendImageCopyRegion(
        Image* pDstImage,                               ///< [in] pointer to destination image to copy to
        Image* pSrcImage,                               ///< [in] pointer to source image to copy from
        const image_region_t* pDstRegion,               ///< [in][optional] destination region descriptor
        const image_region_t* pSrcRegion,               ///< [in][optional] source region descriptor
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopyRegion(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pDstImage->getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pSrcImage->getHandle() ),
            reinterpret_cast<const ze_image_region_t*>( pDstRegion ),
            reinterpret_cast<const ze_image_region_t*>( pSrcRegion ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendImageCopyRegion" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies from an image to device or shared memory.
    /// 
    /// @details
    ///     - The application must ensure the memory pointed to by dstptr is
    ///       accessible by the device on which the command list was created.
    ///     - The implementation must not access the memory pointed to by dstptr as
    ///       it is free to be modified by either the Host or device up until
    ///       execution.
    ///     - The application must ensure the image and events are accessible by the
    ///       device on which the command list was created.
    ///     - The application must ensure the image format descriptor for the source
    ///       image is not a media format.
    ///     - The application must ensure the signal event was **not** created from
    ///       an event pool that was created using
    ///       ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
    ///     - The application must ensure the command list, image and events were
    ///       created, and the memory was allocated, on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clEnqueueReadImage
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendImageCopyToMemory(
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        Image* pSrcImage,                               ///< [in] pointer to source image to copy from
        const image_region_t* pSrcRegion,               ///< [in][optional] source region descriptor
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopyToMemory(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            dstptr,
            reinterpret_cast<ze_image_handle_t>( pSrcImage->getHandle() ),
            reinterpret_cast<const ze_image_region_t*>( pSrcRegion ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendImageCopyToMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Copies to an image from device or shared memory.
    /// 
    /// @details
    ///     - The application must ensure the memory pointed to by srcptr is
    ///       accessible by the device on which the command list was created.
    ///     - The implementation must not access the memory pointed to by srcptr as
    ///       it is free to be modified by either the Host or device up until
    ///       execution.
    ///     - The application must ensure the image and events are accessible by the
    ///       device on which the command list was created.
    ///     - The application must ensure the image format descriptor for the
    ///       destination image is not a media format.
    ///     - The application must ensure the signal event was **not** created from
    ///       an event pool that was created using
    ///       ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
    ///     - The application must ensure the command list, image and events were
    ///       created, and the memory was allocated, on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clEnqueueWriteImage
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendImageCopyFromMemory(
        Image* pDstImage,                               ///< [in] pointer to destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        const image_region_t* pDstRegion,               ///< [in][optional] destination region descriptor
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendImageCopyFromMemory(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pDstImage->getHandle() ),
            srcptr,
            reinterpret_cast<const ze_image_region_t*>( pDstRegion ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendImageCopyFromMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Asynchronously prefetches shared memory to the device associated with
    ///        the specified command list
    /// 
    /// @details
    ///     - This is a hint to improve performance only and is not required for
    ///       correctness.
    ///     - Only prefetching to the device associated with the specified command
    ///       list is supported.
    ///       Prefetching to the host or to a peer device is not supported.
    ///     - Prefetching may not be supported for all allocation types for all devices.
    ///       If memory prefetching is not supported for the specified memory range
    ///       the prefetch hint may be ignored.
    ///     - Prefetching may only be supported at a device-specific granularity,
    ///       such as at a page boundary.
    ///       In this case, the memory range may be expanded such that the start and
    ///       end of the range satisfy granularity requirements.
    ///     - The application must ensure the memory pointed to by ptr is accessible
    ///       by the device on which the command list was created.
    ///     - The application must ensure the command list was created, and the
    ///       memory was allocated, on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clEnqueueSVMMigrateMem
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendMemoryPrefetch(
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t size                                     ///< [in] size in bytes of the memory range to prefetch
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemoryPrefetch(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            ptr,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendMemoryPrefetch" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Provides advice about the use of a shared memory range
    /// 
    /// @details
    ///     - Memory advice is a performance hint only and is not required for
    ///       functional correctness.
    ///     - Memory advice can be used to override driver heuristics to explicitly
    ///       control shared memory behavior.
    ///     - Not all memory advice hints may be supported for all allocation types
    ///       for all devices.
    ///       If a memory advice hint is not supported by the device it will be ignored.
    ///     - Memory advice may only be supported at a device-specific granularity,
    ///       such as at a page boundary.
    ///       In this case, the memory range may be expanded such that the start and
    ///       end of the range satisfy granularity requirements.
    ///     - The application must ensure the memory pointed to by ptr is accessible
    ///       by the device on which the command list was created.
    ///     - The application must ensure the command list was created, and memory
    ///       was allocated, on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle, and the memory was
    ///       allocated.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendMemAdvise(
        Device* pDevice,                                ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        memory_advice_t advice                          ///< [in] Memory advice for the memory range
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendMemAdvise(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            ptr,
            size,
            static_cast<ze_memory_advice_t>( advice ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendMemAdvise" );
    }

#pragma endregion
#pragma region event
    ///////////////////////////////////////////////////////////////////////////////
    EventPool::EventPool( 
        event_pool_handle_t handle,                     ///< [in] handle of event pool object
        Context* pContext,                              ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the event pool object
        ) :
        m_handle( handle ),
        m_pContext( pContext ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    Event::Event( 
        event_handle_t handle,                          ///< [in] handle of event object
        EventPool* pEventPool,                          ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the event object
        ) :
        m_handle( handle ),
        m_pEventPool( pEventPool ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a pool of events on the context.
    /// 
    /// @details
    ///     - The application must only use events within the pool for the
    ///       device(s), or their sub-devices, which were provided during creation.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - EventPool*: pointer handle of event pool object created
    /// 
    /// @throws result_t
    EventPool* ZE_APICALL
    EventPool::Create(
        Context* pContext,                              ///< [in] pointer to the context object
        const desc_t* desc,                             ///< [in] pointer to event pool descriptor
        uint32_t numDevices,                            ///< [in][optional] number of device handles; must be 0 if `nullptr ==
                                                        ///< phDevices`
        Device** ppDevices                              ///< [in][optional][range(0, numDevices)] array of device handles which
                                                        ///< have visibility to the event pool.
                                                        ///< if nullptr, then event pool is visible to all devices supported by the
                                                        ///< driver instance.
        )
    {
        thread_local std::vector<ze_device_handle_t> hDevices;
        hDevices.resize( 0 );
        hDevices.reserve( numDevices );
        for( uint32_t i = 0; i < numDevices; ++i )
            hDevices.emplace_back( ( ppDevices ) ? reinterpret_cast<ze_device_handle_t>( ppDevices[ i ]->getHandle() ) : nullptr );

        ze_event_pool_handle_t hEventPool;

        auto result = static_cast<result_t>( ::zeEventPoolCreate(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<const ze_event_pool_desc_t*>( desc ),
            numDevices,
            hDevices.data(),
            &hEventPool ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::EventPool::Create" );

        EventPool* pEventPool = nullptr;

        try
        {
            pEventPool = new EventPool( reinterpret_cast<event_pool_handle_t>( hEventPool ), pContext, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pEventPool;
            pEventPool = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::EventPool::Create" );
        }

        return pEventPool;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes an event pool object.
    /// 
    /// @details
    ///     - The application must destroy all event handles created from the pool
    ///       before destroying the pool itself.
    ///     - The application must ensure the device is not currently referencing
    ///       the any event within the pool before it is deleted.
    ///     - The implementation of this function may immediately free all Host and
    ///       Device allocations associated with this event pool.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same event pool handle.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @throws result_t
    void ZE_APICALL
    EventPool::Destroy(
        EventPool* pEventPool                           ///< [in][release] pointer to event pool object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeEventPoolDestroy(
            reinterpret_cast<ze_event_pool_handle_t>( pEventPool->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::EventPool::Destroy" );

        delete pEventPool;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates an event from the pool.
    /// 
    /// @details
    ///     - An event is used to communicate fine-grain host-to-device,
    ///       device-to-host or device-to-device dependencies have completed.
    ///     - The application must ensure multiple events do not use the same
    ///       location within the same pool.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same event pool handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clCreateUserEvent**
    ///     - vkCreateEvent
    /// 
    /// @returns
    ///     - Event*: pointer to handle of event object created
    /// 
    /// @throws result_t
    Event* ZE_APICALL
    Event::Create(
        EventPool* pEventPool,                          ///< [in] pointer to the event pool
        const desc_t* desc                              ///< [in] pointer to event descriptor
        )
    {
        ze_event_handle_t hEvent;

        auto result = static_cast<result_t>( ::zeEventCreate(
            reinterpret_cast<ze_event_pool_handle_t>( pEventPool->getHandle() ),
            reinterpret_cast<const ze_event_desc_t*>( desc ),
            &hEvent ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Event::Create" );

        Event* pEvent = nullptr;

        try
        {
            pEvent = new Event( reinterpret_cast<event_handle_t>( hEvent ), pEventPool, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pEvent;
            pEvent = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Event::Create" );
        }

        return pEvent;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes an event object.
    /// 
    /// @details
    ///     - The application must ensure the device is not currently referencing
    ///       the event before it is deleted.
    ///     - The implementation of this function may immediately free all Host and
    ///       Device allocations associated with this event.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same event handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clReleaseEvent**
    ///     - vkDestroyEvent
    /// 
    /// @throws result_t
    void ZE_APICALL
    Event::Destroy(
        Event* pEvent                                   ///< [in][release] pointer to event object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeEventDestroy(
            reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Event::Destroy" );

        delete pEvent;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Gets an IPC event pool handle for the specified event handle that can
    ///        be shared with another process.
    /// 
    /// @details
    ///     - Event pool must have been created with ::ZE_EVENT_POOL_FLAG_IPC.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - ipc_event_pool_handle_t: Returned IPC event handle
    /// 
    /// @throws result_t
    ipc_event_pool_handle_t ZE_APICALL
    EventPool::GetIpcHandle(
        void
        )
    {
        ze_ipc_event_pool_handle_t hIpc;

        auto result = static_cast<result_t>( ::zeEventPoolGetIpcHandle(
            reinterpret_cast<ze_event_pool_handle_t>( getHandle() ),
            &hIpc ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::EventPool::GetIpcHandle" );

        return *reinterpret_cast<ipc_event_pool_handle_t*>( &hIpc );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Opens an IPC event pool handle to retrieve an event pool handle from
    ///        another process.
    /// 
    /// @details
    ///     - Multiple calls to this function with the same IPC handle will return
    ///       unique event pool handles.
    ///     - The event handle in this process should not be freed with
    ///       ::zeEventPoolDestroy, but rather with ::zeEventPoolCloseIpcHandle.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - EventPool*: pointer handle of event pool object created
    /// 
    /// @throws result_t
    EventPool* ZE_APICALL
    EventPool::OpenIpcHandle(
        Context* pContext,                              ///< [in] pointer to the context object to associate with the IPC event
                                                        ///< pool handle
        ipc_event_pool_handle_t pIpc                    ///< [in] IPC event pool handle
        )
    {
        ze_event_pool_handle_t hEventPool;

        auto result = static_cast<result_t>( ::zeEventPoolOpenIpcHandle(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            *reinterpret_cast<ze_ipc_event_pool_handle_t*>( &pIpc ),
            &hEventPool ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::EventPool::OpenIpcHandle" );

        EventPool* pEventPool = nullptr;

        try
        {
            pEventPool = new EventPool( reinterpret_cast<event_pool_handle_t>( hEventPool ), pContext, nullptr );
        }
        catch( std::bad_alloc& )
        {
            delete pEventPool;
            pEventPool = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::EventPool::OpenIpcHandle" );
        }

        return pEventPool;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes an IPC event handle in the current process.
    /// 
    /// @details
    ///     - Closes an IPC event handle by destroying events that were opened in
    ///       this process using ::zeEventPoolOpenIpcHandle.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same event pool handle.
    /// 
    /// @throws result_t
    void ZE_APICALL
    EventPool::CloseIpcHandle(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventPoolCloseIpcHandle(
            reinterpret_cast<ze_event_pool_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::EventPool::CloseIpcHandle" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends a signal of the event from the device into a command list.
    /// 
    /// @details
    ///     - The application must ensure the events are accessible by the device on
    ///       which the command list was created.
    ///     - The application must ensure the signal event was **not** created from
    ///       an event pool that was created using
    ///       ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
    ///     - The application must ensure the command list and events were created
    ///       on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clSetUserEventStatus**
    ///     - vkCmdSetEvent
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendSignalEvent(
        Event* pEvent                                   ///< [in] pointer to the event
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendSignalEvent(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendSignalEvent" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends wait on event(s) on the device into a command list.
    /// 
    /// @details
    ///     - The application must ensure the events are accessible by the device on
    ///       which the command list was created.
    ///     - The application must ensure the command list and events were created
    ///       on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendWaitOnEvents(
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        Event** ppEvents                                ///< [in][range(0, numEvents)] handles of the events to wait on before
                                                        ///< continuing
        )
    {
        thread_local std::vector<ze_event_handle_t> hEvents;
        hEvents.resize( 0 );
        hEvents.reserve( numEvents );
        for( uint32_t i = 0; i < numEvents; ++i )
            hEvents.emplace_back( reinterpret_cast<ze_event_handle_t>( ppEvents[ i ]->getHandle() ) );

        auto result = static_cast<result_t>( ::zeCommandListAppendWaitOnEvents(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            numEvents,
            hEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendWaitOnEvents" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Signals a event from host.
    /// 
    /// @details
    ///     - The application must ensure the signal event was **not** created from
    ///       an event pool that was created using
    ///       ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clSetUserEventStatus
    /// 
    /// @throws result_t
    void ZE_APICALL
    Event::HostSignal(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventHostSignal(
            reinterpret_cast<ze_event_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Event::HostSignal" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief The current host thread waits on an event to be signaled.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clWaitForEvents
    /// 
    /// @returns
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t ZE_APICALL
    Event::HostSynchronize(
        uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeEventQueryStatus;
                                                        ///< if UINT64_MAX, then function will not return until complete or device
                                                        ///< is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        auto result = static_cast<result_t>( ::zeEventHostSynchronize(
            reinterpret_cast<ze_event_handle_t>( getHandle() ),
            timeout ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Event::HostSynchronize" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Queries an event object's status on the host.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clGetEventInfo**
    ///     - vkGetEventStatus
    /// 
    /// @returns
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t ZE_APICALL
    Event::QueryStatus(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventQueryStatus(
            reinterpret_cast<ze_event_handle_t>( getHandle() ) ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Event::QueryStatus" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends a reset of an event back to not signaled state into a command
    ///        list.
    /// 
    /// @details
    ///     - The application must ensure the events are accessible by the device on
    ///       which the command list was created.
    ///     - The application must ensure the command list and events were created
    ///       on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - vkResetEvent
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendEventReset(
        Event* pEvent                                   ///< [in] pointer to the event
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendEventReset(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendEventReset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief The current host thread resets an event back to not signaled state.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - vkResetEvent
    /// 
    /// @throws result_t
    void ZE_APICALL
    Event::HostReset(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventHostReset(
            reinterpret_cast<ze_event_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Event::HostReset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Queries an event's timestamp value on the host.
    /// 
    /// @details
    ///     - The application must ensure the event was created from an event pool
    ///       that was created using ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
    ///     - The destination memory will be unmodified if the event has not been
    ///       signaled.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t ZE_APICALL
    Event::QueryKernelTimestamp(
        kernel_timestamp_result_t* dstptr               ///< [in,out] pointer to memory for where timestamp result will be written.
        )
    {
        auto result = static_cast<result_t>( ::zeEventQueryKernelTimestamp(
            reinterpret_cast<ze_event_handle_t>( getHandle() ),
            reinterpret_cast<ze_kernel_timestamp_result_t*>( dstptr ) ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Event::QueryKernelTimestamp" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends a query of an events' timestamp value(s) into a command list.
    /// 
    /// @details
    ///     - The application must ensure the events are accessible by the device on
    ///       which the command list was created.
    ///     - The application must ensure the events were created from an event pool
    ///       that was created using ::ZE_EVENT_POOL_FLAG_KERNEL_TIMESTAMP flag.
    ///     - The application must ensure the memory pointed to by both dstptr and
    ///       pOffsets is accessible by the device on which the command list was
    ///       created.
    ///     - The value(s) written to the destination buffer are undefined if any
    ///       timestamp event has not been signaled.
    ///     - If pOffsets is nullptr, then multiple results will be appended
    ///       sequentially into memory in the same order as phEvents.
    ///     - The application must ensure the command list and events were created,
    ///       and the memory was allocated, on the same context.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendQueryKernelTimestamps(
        uint32_t numEvents,                             ///< [in] the number of timestamp events to query
        Event** ppEvents,                               ///< [in][range(0, numEvents)] handles of timestamp events to query
        void* dstptr,                                   ///< [in,out] pointer to memory where ::ze_kernel_timestamp_result_t will
                                                        ///< be written; must be size-aligned.
        const size_t* pOffsets,                         ///< [in][optional][range(0, numEvents)] offset, in bytes, to write
                                                        ///< results; address must be 4byte-aligned and offsets must be
                                                        ///< size-aligned.
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing query;
                                                        ///< must be 0 if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before executing query
        )
    {
        thread_local std::vector<ze_event_handle_t> hEvents;
        hEvents.resize( 0 );
        hEvents.reserve( numEvents );
        for( uint32_t i = 0; i < numEvents; ++i )
            hEvents.emplace_back( reinterpret_cast<ze_event_handle_t>( ppEvents[ i ]->getHandle() ) );

        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendQueryKernelTimestamps(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            numEvents,
            hEvents.data(),
            dstptr,
            pOffsets,
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendQueryKernelTimestamps" );
    }

#pragma endregion
#pragma region fence
    ///////////////////////////////////////////////////////////////////////////////
    Fence::Fence( 
        fence_handle_t handle,                          ///< [in] handle of fence object
        CommandQueue* pCommandQueue,                    ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the fence object
        ) :
        m_handle( handle ),
        m_pCommandQueue( pCommandQueue ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a fence for the command queue.
    /// 
    /// @details
    ///     - A fence is a heavyweight synchronization primitive used to communicate
    ///       to the host that command list execution has completed.
    ///     - The application must only use the fence for the command queue which
    ///       was provided during creation.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkCreateFence**
    /// 
    /// @returns
    ///     - Fence*: pointer to handle of fence object created
    /// 
    /// @throws result_t
    Fence* ZE_APICALL
    Fence::Create(
        CommandQueue* pCommandQueue,                    ///< [in] pointer to command queue
        const desc_t* desc                              ///< [in] pointer to fence descriptor
        )
    {
        ze_fence_handle_t hFence;

        auto result = static_cast<result_t>( ::zeFenceCreate(
            reinterpret_cast<ze_command_queue_handle_t>( pCommandQueue->getHandle() ),
            reinterpret_cast<const ze_fence_desc_t*>( desc ),
            &hFence ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Fence::Create" );

        Fence* pFence = nullptr;

        try
        {
            pFence = new Fence( reinterpret_cast<fence_handle_t>( hFence ), pCommandQueue, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pFence;
            pFence = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Fence::Create" );
        }

        return pFence;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes a fence object.
    /// 
    /// @details
    ///     - The application must ensure the device is not currently referencing
    ///       the fence before it is deleted.
    ///     - The implementation of this function may immediately free all Host and
    ///       Device allocations associated with this fence.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same fence handle.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkDestroyFence**
    /// 
    /// @throws result_t
    void ZE_APICALL
    Fence::Destroy(
        Fence* pFence                                   ///< [in][release] pointer to fence object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeFenceDestroy(
            reinterpret_cast<ze_fence_handle_t>( pFence->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Fence::Destroy" );

        delete pFence;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief The current host thread waits on a fence to be signaled.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkWaitForFences**
    /// 
    /// @returns
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t ZE_APICALL
    Fence::HostSynchronize(
        uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                        ///< if UINT64_MAX, then function will not return until complete or device
                                                        ///< is lost.
                                                        ///< Due to external dependencies, timeout may be rounded to the closest
                                                        ///< value allowed by the accuracy of those dependencies.
        )
    {
        auto result = static_cast<result_t>( ::zeFenceHostSynchronize(
            reinterpret_cast<ze_fence_handle_t>( getHandle() ),
            timeout ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Fence::HostSynchronize" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Queries a fence object's status.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkGetFenceStatus**
    /// 
    /// @returns
    ///     - bool_t:'0' when RESULT_NOT_READY
    /// @throws result_t
    bool_t ZE_APICALL
    Fence::QueryStatus(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeFenceQueryStatus(
            reinterpret_cast<ze_fence_handle_t>( getHandle() ) ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Fence::QueryStatus" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset a fence back to the not signaled state.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **vkResetFences**
    /// 
    /// @throws result_t
    void ZE_APICALL
    Fence::Reset(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeFenceReset(
            reinterpret_cast<ze_fence_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Fence::Reset" );
    }

#pragma endregion
#pragma region image
    ///////////////////////////////////////////////////////////////////////////////
    Image::Image( 
        image_handle_t handle,                          ///< [in] handle of image object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the image object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves supported properties of an image.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - properties_t: pointer to image properties
    /// 
    /// @throws result_t
    Image::properties_t ZE_APICALL
    Image::GetProperties(
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* desc                              ///< [in] pointer to image descriptor
        )
    {
        ze_image_properties_t imageProperties;

        auto result = static_cast<result_t>( ::zeImageGetProperties(
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_image_desc_t*>( desc ),
            &imageProperties ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Image::GetProperties" );

        return *reinterpret_cast<properties_t*>( &imageProperties );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates an image on the context.
    /// 
    /// @details
    ///     - The application must only use the image for the device, or its
    ///       sub-devices, which was provided during creation.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clCreateImage
    /// 
    /// @returns
    ///     - Image*: pointer to handle of image object created
    /// 
    /// @throws result_t
    Image* ZE_APICALL
    Image::Create(
        Context* pContext,                              ///< [in] pointer to the context object
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* desc                              ///< [in] pointer to image descriptor
        )
    {
        ze_image_handle_t hImage;

        auto result = static_cast<result_t>( ::zeImageCreate(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_image_desc_t*>( desc ),
            &hImage ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Image::Create" );

        Image* pImage = nullptr;

        try
        {
            pImage = new Image( reinterpret_cast<image_handle_t>( hImage ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pImage;
            pImage = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Image::Create" );
        }

        return pImage;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes an image object.
    /// 
    /// @details
    ///     - The application must ensure the device is not currently referencing
    ///       the image before it is deleted.
    ///     - The implementation of this function may immediately free all Host and
    ///       Device allocations associated with this image.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same image handle.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Image::Destroy(
        Image* pImage                                   ///< [in][release] pointer to image object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeImageDestroy(
            reinterpret_cast<ze_image_handle_t>( pImage->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Image::Destroy" );

        delete pImage;
    }

#pragma endregion
#pragma region memory
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allocates shared memory on the context.
    /// 
    /// @details
    ///     - Shared allocations share ownership between the host and one or more
    ///       devices.
    ///     - Shared allocations may optionally be associated with a device by
    ///       passing a handle to the device.
    ///     - Devices supporting only single-device shared access capabilities may
    ///       access shared memory associated with the device.
    ///       For these devices, ownership of the allocation is shared between the
    ///       host and the associated device only.
    ///     - Passing nullptr as the device handle does not associate the shared
    ///       allocation with any device.
    ///       For allocations with no associated device, ownership of the allocation
    ///       is shared between the host and all devices supporting cross-device
    ///       shared access capabilities.
    ///     - The application must only use the memory allocation for the context
    ///       and device, or its sub-devices, which was provided during allocation.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - void*: pointer to shared allocation
    /// 
    /// @throws result_t
    void* ZE_APICALL
    Mem::AllocShared(
        Context* pContext,                              ///< [in] pointer to the context object
        const device_alloc_desc_t* device_desc,         ///< [in] pointer to device memory allocation descriptor
        const host_alloc_desc_t* host_desc,             ///< [in] pointer to host memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less-than
                                                        ///< ::ze_device_properties_t.maxMemAllocSize.
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two.
        Device* pDevice                                 ///< [in][optional] device handle to associate with
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::zeMemAllocShared(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<const ze_device_mem_alloc_desc_t*>( device_desc ),
            reinterpret_cast<const ze_host_mem_alloc_desc_t*>( host_desc ),
            size,
            alignment,
            ( pDevice ) ? reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ) : nullptr,
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Mem::AllocShared" );

        return pptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allocates device memory on the context.
    /// 
    /// @details
    ///     - Device allocations are owned by a specific device.
    ///     - In general, a device allocation may only be accessed by the device
    ///       that owns it.
    ///     - The application must only use the memory allocation for the context
    ///       and device, or its sub-devices, which was provided during allocation.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - void*: pointer to device allocation
    /// 
    /// @throws result_t
    void* ZE_APICALL
    Mem::AllocDevice(
        Context* pContext,                              ///< [in] pointer to the context object
        const device_alloc_desc_t* device_desc,         ///< [in] pointer to device memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less-than
                                                        ///< ::ze_device_properties_t.maxMemAllocSize.
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two.
        Device* pDevice                                 ///< [in] pointer to the device
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::zeMemAllocDevice(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<const ze_device_mem_alloc_desc_t*>( device_desc ),
            size,
            alignment,
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Mem::AllocDevice" );

        return pptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allocates host memory on the context.
    /// 
    /// @details
    ///     - Host allocations are owned by the host process.
    ///     - Host allocations are accessible by the host and all devices within the
    ///       driver's context.
    ///     - Host allocations are frequently used as staging areas to transfer data
    ///       to or from devices.
    ///     - The application must only use the memory allocation for the context
    ///       which was provided during allocation.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - void*: pointer to host allocation
    /// 
    /// @throws result_t
    void* ZE_APICALL
    Mem::AllocHost(
        Context* pContext,                              ///< [in] pointer to the context object
        const host_alloc_desc_t* host_desc,             ///< [in] pointer to host memory allocation descriptor
        size_t size,                                    ///< [in] size in bytes to allocate; must be less-than
                                                        ///< ::ze_device_properties_t.maxMemAllocSize.
        size_t alignment                                ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                        ///< two.
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::zeMemAllocHost(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<const ze_host_mem_alloc_desc_t*>( host_desc ),
            size,
            alignment,
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Mem::AllocHost" );

        return pptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Frees allocated host memory, device memory, or shared memory on the
    ///        context.
    /// 
    /// @details
    ///     - The application must ensure the device is not currently referencing
    ///       the memory before it is freed
    ///     - The implementation of this function may immediately free all Host and
    ///       Device allocations associated with this memory
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same pointer.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Mem::Free(
        Context* pContext,                              ///< [in] pointer to the context object
        void* ptr                                       ///< [in][release] pointer to memory to free
        )
    {
        auto result = static_cast<result_t>( ::zeMemFree(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Mem::Free" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves attributes of a memory allocation
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The application may query attributes of a memory allocation unrelated
    ///       to the context.
    ///       When this occurs, the returned allocation type will be
    ///       ::ZE_MEMORY_TYPE_UNKNOWN, and the returned identifier and associated
    ///       device is unspecified.
    /// 
    /// @returns
    ///     - Device*: device associated with this allocation
    /// 
    /// @throws result_t
    void ZE_APICALL
    Mem::GetAllocProperties(
        Context* pContext,                              ///< [in] pointer to the context object
        const void* ptr,                                ///< [in] memory pointer to query
        memory_allocation_properties_t* pMemAllocProperties,///< [in,out] query result for memory allocation properties
        Device** ppDevice                               ///< [out][optional] device associated with this allocation
        )
    {
        ze_device_handle_t hDevice;

        auto result = static_cast<result_t>( ::zeMemGetAllocProperties(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            ptr,
            reinterpret_cast<ze_memory_allocation_properties_t*>( pMemAllocProperties ),
            ( ppDevice ) ? &hDevice : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Mem::GetAllocProperties" );

        if( ppDevice )
            *ppDevice =  nullptr;

        try
        {
            if( ppDevice )
                *ppDevice =  g_DeviceFactory.getInstance( reinterpret_cast<device_handle_t>( hDevice ), nullptr );
        }
        catch( std::bad_alloc& )
        {
            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Mem::GetAllocProperties" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves the base address and/or size of an allocation
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Mem::GetAddressRange(
        Context* pContext,                              ///< [in] pointer to the context object
        const void* ptr,                                ///< [in] memory pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
        )
    {
        auto result = static_cast<result_t>( ::zeMemGetAddressRange(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            ptr,
            pBase,
            pSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Mem::GetAddressRange" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates an IPC memory handle for the specified allocation
    /// 
    /// @details
    ///     - Takes a pointer to a device memory allocation and creates an IPC
    ///       memory handle for exporting it for use in another process.
    ///     - The pointer must be base pointer of the device memory allocation; i.e.
    ///       the value returned from ::zeMemAllocDevice.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - ipc_mem_handle_t: Returned IPC memory handle
    /// 
    /// @throws result_t
    ipc_mem_handle_t ZE_APICALL
    Mem::GetIpcHandle(
        Context* pContext,                              ///< [in] pointer to the context object
        const void* ptr                                 ///< [in] pointer to the device memory allocation
        )
    {
        ze_ipc_mem_handle_t ipcHandle;

        auto result = static_cast<result_t>( ::zeMemGetIpcHandle(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            ptr,
            &ipcHandle ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Mem::GetIpcHandle" );

        return *reinterpret_cast<ipc_mem_handle_t*>( &ipcHandle );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Opens an IPC memory handle to retrieve a device pointer on the
    ///        context.
    /// 
    /// @details
    ///     - Takes an IPC memory handle from a remote process and associates it
    ///       with a device pointer usable in this process.
    ///     - The device pointer in this process should not be freed with
    ///       ::zeMemFree, but rather with ::zeMemCloseIpcHandle.
    ///     - Multiple calls to this function with the same IPC handle will return
    ///       unique pointers.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - void*: pointer to device allocation in this process
    /// 
    /// @throws result_t
    void* ZE_APICALL
    Mem::OpenIpcHandle(
        Context* pContext,                              ///< [in] pointer to the context object
        Device* pDevice,                                ///< [in] pointer to the device to associate with the IPC memory handle
        ipc_mem_handle_t handle,                        ///< [in] IPC memory handle
        ipc_memory_flags_t flags                        ///< [in] flags controlling the operation.
                                                        ///< must be 0 (default) or a valid combination of ::ze_ipc_memory_flag_t.
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::zeMemOpenIpcHandle(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            *reinterpret_cast<ze_ipc_mem_handle_t*>( &handle ),
            static_cast<ze_ipc_memory_flags_t>( flags ),
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Mem::OpenIpcHandle" );

        return pptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes an IPC memory handle
    /// 
    /// @details
    ///     - Closes an IPC memory handle by unmapping memory that was opened in
    ///       this process using ::zeMemOpenIpcHandle.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same pointer.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Mem::CloseIpcHandle(
        Context* pContext,                              ///< [in] pointer to the context object
        const void* ptr                                 ///< [in][release] pointer to device allocation in this process
        )
    {
        auto result = static_cast<result_t>( ::zeMemCloseIpcHandle(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Mem::CloseIpcHandle" );
    }

#pragma endregion
#pragma region module
    ///////////////////////////////////////////////////////////////////////////////
    Module::Module( 
        module_handle_t handle,                         ///< [in] handle of module object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the module object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    ModuleBuildLog::ModuleBuildLog( 
        module_build_log_handle_t handle,               ///< [in] handle of the buildlog object
        Module* pModule                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pModule( pModule )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    Kernel::Kernel( 
        kernel_handle_t handle,                         ///< [in] handle of kernel object
        Module* pModule,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the kernel object
        ) :
        m_handle( handle ),
        m_pModule( pModule ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a module on the context.
    /// 
    /// @details
    ///     - Compiles the module for execution on the device.
    ///     - The application must only use the module for the device, or its
    ///       sub-devices, which was provided during creation.
    ///     - The module can be copied to other devices and contexts within the same
    ///       driver instance by using ::zeModuleGetNativeBinary.
    ///     - A build log can optionally be returned to the caller. The caller is
    ///       responsible for destroying build log using ::zeModuleBuildLogDestroy.
    ///     - The module descriptor constants are only supported for SPIR-V
    ///       specialization constants.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - Module*: pointer to handle of module object created
    ///     - ModuleBuildLog*: pointer to handle of module's build log.
    /// 
    /// @throws result_t
    Module* ZE_APICALL
    Module::Create(
        Context* pContext,                              ///< [in] pointer to the context object
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* desc,                             ///< [in] pointer to module descriptor
        ModuleBuildLog** ppBuildLog                     ///< [out][optional] pointer to pointer to module's build log.
        )
    {
        ze_module_handle_t hModule;

        ze_module_build_log_handle_t hBuildLog;

        auto result = static_cast<result_t>( ::zeModuleCreate(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_module_desc_t*>( desc ),
            &hModule,
            ( ppBuildLog ) ? &hBuildLog : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Module::Create" );

        Module* pModule = nullptr;

        try
        {
            pModule = new Module( reinterpret_cast<module_handle_t>( hModule ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pModule;
            pModule = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Module::Create" );
        }

        if( ppBuildLog )
            *ppBuildLog =  nullptr;

        try
        {
            if( ppBuildLog )
                *ppBuildLog =  new ModuleBuildLog( reinterpret_cast<module_build_log_handle_t>( hBuildLog ), pModule );
        }
        catch( std::bad_alloc& )
        {
            if( ppBuildLog )
            {
                delete *ppBuildLog;
                *ppBuildLog =  nullptr;
            }
            delete pModule;
            pModule = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Module::Create" );
        }

        return pModule;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys module
    /// 
    /// @details
    ///     - The application must destroy all kernel and build log handles created
    ///       from the module before destroying the module itself.
    ///     - The application must ensure the device is not currently referencing
    ///       the module before it is deleted.
    ///     - The implementation of this function may immediately free all Host and
    ///       Device allocations associated with this module.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same module handle.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Module::Destroy(
        Module* pModule                                 ///< [in][release] pointer to the module
        )
    {
        auto result = static_cast<result_t>( ::zeModuleDestroy(
            reinterpret_cast<ze_module_handle_t>( pModule->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Module::Destroy" );

        delete pModule;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Dynamically link modules together that share import/export linkage
    ///        dependencies.
    /// 
    /// @details
    ///     - Modules support import and export linkage for functions and global
    ///       variables.
    ///     - Modules that have imports can be dynamically linked to export modules
    ///       that satisfy those import requirements.
    ///     - Modules can have both import and export linkages.
    ///     - Modules that do not have any imports or exports do not need to be
    ///       linked.
    ///     - Modules cannot be partially linked. All modules needed to satisfy all
    ///       import dependencies for a module must be passed in or
    ///       ::ZE_RESULT_ERROR_MODULE_LINK_FAILURE will returned.
    ///     - Modules with imports need to be linked before kernel objects can be
    ///       created from them.
    ///     - Modules will only be linked once. A module can be used in multiple
    ///       link calls if it has exports but it's imports will not be re-linked.
    ///     - Ambiguous dependencies, where multiple modules satisfy the import
    ///       dependencies for another module, is not allowed.
    ///     - ModuleGetNativeBinary can be called on any module regardless of
    ///       whether it is linked or not.
    ///     - A link log can optionally be returned to the caller. The caller is
    ///       responsible for destroying build log using ::zeModuleBuildLogDestroy.
    ///     - See SPIR-V specification for linkage details.
    ///     - The application may call this function from simultaneous threads as
    ///       long as the import modules being linked are not the same.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - ModuleBuildLog*: pointer to handle of dynamic link log.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Module::DynamicLink(
        uint32_t numModules,                            ///< [in] number of modules to be linked pointed to by phModules.
        Module** ppModules,                             ///< [in][range(0, numModules)] pointer to an array of modules to
                                                        ///< dynamically link together.
        ModuleBuildLog** ppLinkLog                      ///< [out][optional] pointer to pointer to dynamic link log.
        )
    {
        thread_local std::vector<ze_module_handle_t> hModules;
        hModules.resize( 0 );
        hModules.reserve( numModules );
        for( uint32_t i = 0; i < numModules; ++i )
            hModules.emplace_back( reinterpret_cast<ze_module_handle_t>( ppModules[ i ]->getHandle() ) );

        ze_module_build_log_handle_t hLinkLog;

        auto result = static_cast<result_t>( ::zeModuleDynamicLink(
            numModules,
            hModules.data(),
            ( ppLinkLog ) ? &hLinkLog : nullptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Module::DynamicLink" );

        if( ppLinkLog )
            *ppLinkLog =  nullptr;

        try
        {
            if( ppLinkLog )
                *ppLinkLog =  new ModuleBuildLog( reinterpret_cast<module_build_log_handle_t>( hLinkLog ), nullptr );
        }
        catch( std::bad_alloc& )
        {
            if( ppLinkLog )
            {
                delete *ppLinkLog;
                *ppLinkLog =  nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Module::DynamicLink" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys module build log object
    /// 
    /// @details
    ///     - The implementation of this function may immediately free all Host
    ///       allocations associated with this object.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same build log handle.
    ///     - The implementation of this function should be lock-free.
    ///     - This function can be called before or after ::zeModuleDestroy for the
    ///       associated module.
    /// 
    /// @throws result_t
    void ZE_APICALL
    ModuleBuildLog::Destroy(
        ModuleBuildLog* pModuleBuildLog                 ///< [in][release] pointer to the module build log object.
        )
    {
        auto result = static_cast<result_t>( ::zeModuleBuildLogDestroy(
            reinterpret_cast<ze_module_build_log_handle_t>( pModuleBuildLog->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::ModuleBuildLog::Destroy" );

        delete pModuleBuildLog;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieves text string for build log.
    /// 
    /// @details
    ///     - The caller can pass nullptr for pBuildLog when querying only for size.
    ///     - The caller must provide memory for build log.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    ModuleBuildLog::GetString(
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
        )
    {
        auto result = static_cast<result_t>( ::zeModuleBuildLogGetString(
            reinterpret_cast<ze_module_build_log_handle_t>( getHandle() ),
            pSize,
            pBuildLog ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::ModuleBuildLog::GetString" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve native binary from Module.
    /// 
    /// @details
    ///     - The native binary output can be cached to disk and new modules can be
    ///       later constructed from the cached copy.
    ///     - The native binary will retain debugging information that is associated
    ///       with a module.
    ///     - The caller can pass nullptr for pModuleNativeBinary when querying only
    ///       for size.
    ///     - The implementation will copy the native binary into a buffer supplied
    ///       by the caller.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Module::GetNativeBinary(
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
        )
    {
        auto result = static_cast<result_t>( ::zeModuleGetNativeBinary(
            reinterpret_cast<ze_module_handle_t>( getHandle() ),
            pSize,
            pModuleNativeBinary ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Module::GetNativeBinary" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve global variable pointer from Module.
    /// 
    /// @details
    ///     - The application may query global pointer from any module that either
    ///       exports or imports it.
    ///     - The application must dynamically link a module that imports a global
    ///       before the global pointer can be queried from it.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Module::GetGlobalPointer(
        const char* pGlobalName,                        ///< [in] name of global variable in module
        size_t* pSize,                                  ///< [in,out][optional] size of global variable
        void** pptr                                     ///< [in,out][optional] device visible pointer
        )
    {
        auto result = static_cast<result_t>( ::zeModuleGetGlobalPointer(
            reinterpret_cast<ze_module_handle_t>( getHandle() ),
            pGlobalName,
            pSize,
            pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Module::GetGlobalPointer" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve all kernel names in the module.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Module::GetKernelNames(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of names available.
                                                        ///< if count is non-zero, then driver will only retrieve that number of names.
                                                        ///< if count is larger than the number of names available, then the driver
                                                        ///< will update the value with the correct number of names available.
        const char** pNames                             ///< [in,out][optional][range(0, *pCount)] array of names of functions
        )
    {
        auto result = static_cast<result_t>( ::zeModuleGetKernelNames(
            reinterpret_cast<ze_module_handle_t>( getHandle() ),
            pCount,
            pNames ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Module::GetKernelNames" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve module properties.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Module::GetProperties(
        properties_t* pModuleProperties                 ///< [in,out] query result for module properties.
        )
    {
        auto result = static_cast<result_t>( ::zeModuleGetProperties(
            reinterpret_cast<ze_module_handle_t>( getHandle() ),
            reinterpret_cast<ze_module_properties_t*>( pModuleProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Module::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Create a kernel from the module.
    /// 
    /// @details
    ///     - Modules that have unresolved imports need to be dynamically linked
    ///       before a kernel can be created from them. (See ::zeModuleDynamicLink)
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - Kernel*: handle of the Function object
    /// 
    /// @throws result_t
    Kernel* ZE_APICALL
    Kernel::Create(
        Module* pModule,                                ///< [in] pointer to the module
        const desc_t* desc                              ///< [in] pointer to kernel descriptor
        )
    {
        ze_kernel_handle_t hKernel;

        auto result = static_cast<result_t>( ::zeKernelCreate(
            reinterpret_cast<ze_module_handle_t>( pModule->getHandle() ),
            reinterpret_cast<const ze_kernel_desc_t*>( desc ),
            &hKernel ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::Create" );

        Kernel* pKernel = nullptr;

        try
        {
            pKernel = new Kernel( reinterpret_cast<kernel_handle_t>( hKernel ), pModule, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pKernel;
            pKernel = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::Create" );
        }

        return pKernel;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a kernel object
    /// 
    /// @details
    ///     - The application must ensure the device is not currently referencing
    ///       the kernel before it is deleted.
    ///     - The implementation of this function may immediately free all Host and
    ///       Device allocations associated with this kernel.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same kernel handle.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Kernel::Destroy(
        Kernel* pKernel                                 ///< [in][release] pointer to the kernel object
        )
    {
        auto result = static_cast<result_t>( ::zeKernelDestroy(
            reinterpret_cast<ze_kernel_handle_t>( pKernel->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::Destroy" );

        delete pKernel;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve a function pointer from a module by name
    /// 
    /// @details
    ///     - The function pointer is unique for the device on which the module was
    ///       created.
    ///     - The function pointer is no longer valid if module is destroyed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - void*: pointer to function.
    /// 
    /// @throws result_t
    void* ZE_APICALL
    Module::GetFunctionPointer(
        const char* pFunctionName                       ///< [in] Name of function to retrieve function pointer for.
        )
    {
        void* pfnFunction;

        auto result = static_cast<result_t>( ::zeModuleGetFunctionPointer(
            reinterpret_cast<ze_module_handle_t>( getHandle() ),
            pFunctionName,
            &pfnFunction ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Module::GetFunctionPointer" );

        return pfnFunction;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set group size for a kernel on the current Host thread.
    /// 
    /// @details
    ///     - The implementation will maintain the group size in thread-local
    ///       storage.
    ///     - The group size will be used when a ::zeCommandListAppendLaunchKernel
    ///       variant is called on the same Host thread.
    ///     - The application may call this function from simultaneous threads with
    ///       the same kernel handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Kernel::SetGroupSize(
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
        )
    {
        auto result = static_cast<result_t>( ::zeKernelSetGroupSize(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            groupSizeX,
            groupSizeY,
            groupSizeZ ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::SetGroupSize" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query a suggested group size for a kernel given a global size for each
    ///        dimension.
    /// 
    /// @details
    ///     - This function ignores the group size that is set using
    ///       ::zeKernelSetGroupSize.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - uint32_t: recommended size of group for X dimension
    ///     - uint32_t: recommended size of group for Y dimension
    ///     - uint32_t: recommended size of group for Z dimension
    /// 
    /// @throws result_t
    std::tuple<uint32_t, uint32_t, uint32_t> ZE_APICALL
    Kernel::SuggestGroupSize(
        uint32_t globalSizeX,                           ///< [in] global width for X dimension
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension
        uint32_t globalSizeZ                            ///< [in] global width for Z dimension
        )
    {
        uint32_t groupSizeX;

        uint32_t groupSizeY;

        uint32_t groupSizeZ;

        auto result = static_cast<result_t>( ::zeKernelSuggestGroupSize(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            globalSizeX,
            globalSizeY,
            globalSizeZ,
            &groupSizeX,
            &groupSizeY,
            &groupSizeZ ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::SuggestGroupSize" );

        return std::make_tuple( groupSizeX, groupSizeY, groupSizeZ );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query a suggested max group count for a cooperative kernel.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - uint32_t: recommended total group count.
    /// 
    /// @throws result_t
    uint32_t ZE_APICALL
    Kernel::SuggestMaxCooperativeGroupCount(
        void
        )
    {
        uint32_t totalGroupCount;

        auto result = static_cast<result_t>( ::zeKernelSuggestMaxCooperativeGroupCount(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            &totalGroupCount ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::SuggestMaxCooperativeGroupCount" );

        return totalGroupCount;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set kernel argument for a kernel on the current Host thread.
    /// 
    /// @details
    ///     - The implementation will maintain the argument values in thread-local
    ///       storage.
    ///     - The argument values will be used when a
    ///       ::zeCommandListAppendLaunchKernel variant is called on the same Host
    ///       thread.
    ///     - The application may call this function from simultaneous threads with
    ///       the same kernel handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Kernel::SetArgumentValue(
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
        )
    {
        auto result = static_cast<result_t>( ::zeKernelSetArgumentValue(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            argIndex,
            argSize,
            pArgValue ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::SetArgumentValue" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets kernel indirect access flags.
    /// 
    /// @details
    ///     - The application should specify which allocations will be indirectly
    ///       accessed by the kernel to allow driver to optimize which allocations
    ///       are made resident
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same Kernel handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Kernel::SetIndirectAccess(
        indirect_access_flags_t flags                   ///< [in] kernel indirect access flags
        )
    {
        auto result = static_cast<result_t>( ::zeKernelSetIndirectAccess(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            static_cast<ze_kernel_indirect_access_flags_t>( flags ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::SetIndirectAccess" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve kernel indirect access flags.
    /// 
    /// @details
    ///     - This function may be called from simultaneous threads with the same
    ///       Kernel handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - indirect_access_flags_t: query result for kernel indirect access flags.
    /// 
    /// @throws result_t
    Kernel::indirect_access_flags_t ZE_APICALL
    Kernel::GetIndirectAccess(
        void
        )
    {
        ze_kernel_indirect_access_flags_t flags;

        auto result = static_cast<result_t>( ::zeKernelGetIndirectAccess(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            &flags ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::GetIndirectAccess" );

        return *reinterpret_cast<indirect_access_flags_t*>( &flags );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve all declared kernel attributes (i.e. can be specified with
    ///        __attribute__ in runtime language).
    /// 
    /// @details
    ///     - This function may be called from simultaneous threads with the same
    ///       Kernel handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Kernel::GetSourceAttributes(
        uint32_t* pSize,                                ///< [in,out] pointer to size of string in bytes.
                                                        ///< if size is zero, then the driver will update string argument.
                                                        ///< if size is non-zero, then driver will only retrieve string size in bytes.
                                                        ///< if size is larger than source attributes string, then the driver will
                                                        ///< update the string.
        char** pString                                  ///< [in,out][optional] pointer to null-terminated string where kernel
                                                        ///< source attributes are separated by space.
        )
    {
        auto result = static_cast<result_t>( ::zeKernelGetSourceAttributes(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            pSize,
            pString ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::GetSourceAttributes" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sets the preferred cache configuration for a kernel on the current
    ///        Host thread.
    /// 
    /// @details
    ///     - The implementation will maintain the cache configuration in
    ///       thread-local storage.
    ///     - The cache configuration will be used when a
    ///       ::zeCommandListAppendLaunchKernel variant is called on the same Host
    ///       thread.
    ///     - The application may call this function from simultaneous threads with
    ///       the same kernel handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Kernel::SetCacheConfig(
        cache_config_flags_t flags                      ///< [in] cache configuration. 
                                                        ///< must be 0 (default configuration) or a valid combination of ::ze_cache_config_flag_t.
        )
    {
        auto result = static_cast<result_t>( ::zeKernelSetCacheConfig(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            static_cast<ze_cache_config_flags_t>( flags ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::SetCacheConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve kernel properties.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Kernel::GetProperties(
        properties_t* pKernelProperties                 ///< [in,out] query result for kernel properties.
        )
    {
        auto result = static_cast<result_t>( ::zeKernelGetProperties(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            reinterpret_cast<ze_kernel_properties_t*>( pKernelProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Retrieve kernel name from Kernel.
    /// 
    /// @details
    ///     - The caller can pass nullptr for pName when querying only for size.
    ///     - The implementation will copy the kernel name into a buffer supplied by
    ///       the caller.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Kernel::GetName(
        size_t* pSize,                                  ///< [in,out] size of kernel name string, including null terminator, in
                                                        ///< bytes.
        char* pName                                     ///< [in,out][optional] char pointer to kernel name.
        )
    {
        auto result = static_cast<result_t>( ::zeKernelGetName(
            reinterpret_cast<ze_kernel_handle_t>( getHandle() ),
            pSize,
            pName ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Kernel::GetName" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch kernel over one or more work groups.
    /// 
    /// @details
    ///     - The application must ensure the kernel and events are accessible by
    ///       the device on which the command list was created.
    ///     - This may **only** be called for a command list created with command
    ///       queue group ordinal that supports compute.
    ///     - The application must ensure the command list, kernel and events were
    ///       created on the same context.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendLaunchKernel(
        Kernel* pKernel,                                ///< [in] pointer to the kernel object
        const group_count_t* pLaunchFuncArgs,           ///< [in] thread group launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendLaunchKernel(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_kernel_handle_t>( pKernel->getHandle() ),
            reinterpret_cast<const ze_group_count_t*>( pLaunchFuncArgs ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendLaunchKernel" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch kernel cooperatively over one or more work groups.
    /// 
    /// @details
    ///     - The application must ensure the kernel and events are accessible by
    ///       the device on which the command list was created.
    ///     - This may **only** be called for a command list created with command
    ///       queue group ordinal that supports compute.
    ///     - This may only be used for a command list that are submitted to command
    ///       queue with cooperative flag set.
    ///     - The application must ensure the command list, kernel and events were
    ///       created on the same context.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    ///     - Use ::zeKernelSuggestMaxCooperativeGroupCount to recommend max group
    ///       count for device for cooperative functions that device supports.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendLaunchCooperativeKernel(
        Kernel* pKernel,                                ///< [in] pointer to the kernel object
        const group_count_t* pLaunchFuncArgs,           ///< [in] thread group launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendLaunchCooperativeKernel(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_kernel_handle_t>( pKernel->getHandle() ),
            reinterpret_cast<const ze_group_count_t*>( pLaunchFuncArgs ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendLaunchCooperativeKernel" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch kernel over one or more work groups using indirect arguments.
    /// 
    /// @details
    ///     - The application must ensure the kernel and events are accessible by
    ///       the device on which the command list was created.
    ///     - The application must ensure the launch arguments are visible to the
    ///       device on which the command list was created.
    ///     - The implementation must not access the contents of the launch
    ///       arguments as they are free to be modified by either the Host or device
    ///       up until execution.
    ///     - This may **only** be called for a command list created with command
    ///       queue group ordinal that supports compute.
    ///     - The application must ensure the command list, kernel and events were
    ///       created, and the memory was allocated, on the same context.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendLaunchKernelIndirect(
        Kernel* pKernel,                                ///< [in] pointer to the kernel object
        const group_count_t* pLaunchArgumentsBuffer,    ///< [in] pointer to device buffer that will contain thread group launch
                                                        ///< arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendLaunchKernelIndirect(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_kernel_handle_t>( pKernel->getHandle() ),
            reinterpret_cast<const ze_group_count_t*>( pLaunchArgumentsBuffer ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendLaunchKernelIndirect" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Launch multiple kernels over one or more work groups using an array of
    ///        indirect arguments.
    /// 
    /// @details
    ///     - The application must ensure the kernel and events are accessible by
    ///       the device on which the command list was created.
    ///     - The application must ensure the array of launch arguments and count
    ///       buffer are visible to the device on which the command list was
    ///       created.
    ///     - The implementation must not access the contents of the array of launch
    ///       arguments or count buffer as they are free to be modified by either
    ///       the Host or device up until execution.
    ///     - This may **only** be called for a command list created with command
    ///       queue group ordinal that supports compute.
    ///     - The application must enusre the command list, kernel and events were
    ///       created, and the memory was allocated, on the same context.
    ///     - This function may **not** be called from simultaneous threads with the
    ///       same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    CommandList::AppendLaunchMultipleKernelsIndirect(
        uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
        Kernel** ppKernels,                             ///< [in][range(0, numKernels)] handles of the kernel objects
        const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of kernels to launch; value must be less-than or equal-to
                                                        ///< numKernels
        const group_count_t* pLaunchArgumentsBuffer,    ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                        ///< a contiguous array of thread group launch arguments
        Event* pSignalEvent,                            ///< [in][optional] pointer to the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching; must be 0
                                                        ///< if `nullptr == phWaitEvents`
        Event** ppWaitEvents                            ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                        ///< on before launching
        )
    {
        thread_local std::vector<ze_kernel_handle_t> hKernels;
        hKernels.resize( 0 );
        hKernels.reserve( numKernels );
        for( uint32_t i = 0; i < numKernels; ++i )
            hKernels.emplace_back( reinterpret_cast<ze_kernel_handle_t>( ppKernels[ i ]->getHandle() ) );

        thread_local std::vector<ze_event_handle_t> hWaitEvents;
        hWaitEvents.resize( 0 );
        hWaitEvents.reserve( numWaitEvents );
        for( uint32_t i = 0; i < numWaitEvents; ++i )
            hWaitEvents.emplace_back( ( ppWaitEvents ) ? reinterpret_cast<ze_event_handle_t>( ppWaitEvents[ i ]->getHandle() ) : nullptr );

        auto result = static_cast<result_t>( ::zeCommandListAppendLaunchMultipleKernelsIndirect(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            numKernels,
            hKernels.data(),
            pCountBuffer,
            reinterpret_cast<const ze_group_count_t*>( pLaunchArgumentsBuffer ),
            ( pSignalEvent ) ? reinterpret_cast<ze_event_handle_t>( pSignalEvent->getHandle() ) : nullptr,
            numWaitEvents,
            hWaitEvents.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::CommandList::AppendLaunchMultipleKernelsIndirect" );
    }

#pragma endregion
#pragma region raytracing
#pragma endregion
#pragma region residency
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Makes memory resident for the device.
    /// 
    /// @details
    ///     - The application must ensure the memory is resident before being
    ///       referenced by the device
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Context::MakeMemoryResident(
        Device* pDevice,                                ///< [in] pointer to the device
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
        )
    {
        auto result = static_cast<result_t>( ::zeContextMakeMemoryResident(
            reinterpret_cast<ze_context_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            ptr,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Context::MakeMemoryResident" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allows memory to be evicted from the device.
    /// 
    /// @details
    ///     - The application must ensure the device is not currently referencing
    ///       the memory before it is evicted
    ///     - The application may free the memory without evicting; the memory is
    ///       implicitly evicted when freed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Context::EvictMemory(
        Device* pDevice,                                ///< [in] pointer to the device
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
        )
    {
        auto result = static_cast<result_t>( ::zeContextEvictMemory(
            reinterpret_cast<ze_context_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            ptr,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Context::EvictMemory" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Makes image resident for the device.
    /// 
    /// @details
    ///     - The application must ensure the image is resident before being
    ///       referenced by the device
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Context::MakeImageResident(
        Device* pDevice,                                ///< [in] pointer to the device
        Image* pImage                                   ///< [in] pointer to image to make resident
        )
    {
        auto result = static_cast<result_t>( ::zeContextMakeImageResident(
            reinterpret_cast<ze_context_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pImage->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Context::MakeImageResident" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Allows image to be evicted from the device.
    /// 
    /// @details
    ///     - The application must ensure the device is not currently referencing
    ///       the image before it is evicted
    ///     - The application may destroy the image without evicting; the image is
    ///       implicitly evicted when destroyed.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Context::EvictImage(
        Device* pDevice,                                ///< [in] pointer to the device
        Image* pImage                                   ///< [in] pointer to image to make evict
        )
    {
        auto result = static_cast<result_t>( ::zeContextEvictImage(
            reinterpret_cast<ze_context_handle_t>( getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<ze_image_handle_t>( pImage->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Context::EvictImage" );
    }

#pragma endregion
#pragma region sampler
    ///////////////////////////////////////////////////////////////////////////////
    Sampler::Sampler( 
        sampler_handle_t handle,                        ///< [in] handle of the sample object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] sampler descriptor
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates sampler on the context.
    /// 
    /// @details
    ///     - The application must only use the sampler for the device, or its
    ///       sub-devices, which was provided during creation.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - Sampler*: handle of the sampler
    /// 
    /// @throws result_t
    Sampler* ZE_APICALL
    Sampler::Create(
        Context* pContext,                              ///< [in] pointer to the context object
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* desc                              ///< [in] pointer to sampler descriptor
        )
    {
        ze_sampler_handle_t hSampler;

        auto result = static_cast<result_t>( ::zeSamplerCreate(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_sampler_desc_t*>( desc ),
            &hSampler ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Sampler::Create" );

        Sampler* pSampler = nullptr;

        try
        {
            pSampler = new Sampler( reinterpret_cast<sampler_handle_t>( hSampler ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pSampler;
            pSampler = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::Sampler::Create" );
        }

        return pSampler;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys sampler object
    /// 
    /// @details
    ///     - The application must ensure the device is not currently referencing
    ///       the sampler before it is deleted.
    ///     - The implementation of this function may immediately free all Host and
    ///       Device allocations associated with this sampler.
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same sampler handle.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Sampler::Destroy(
        Sampler* pSampler                               ///< [in][release] pointer to the sampler
        )
    {
        auto result = static_cast<result_t>( ::zeSamplerDestroy(
            reinterpret_cast<ze_sampler_handle_t>( pSampler->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::Sampler::Destroy" );

        delete pSampler;
    }

#pragma endregion
#pragma region virtual
    ///////////////////////////////////////////////////////////////////////////////
    PhysicalMem::PhysicalMem( 
        physical_mem_handle_t handle,                   ///< [in] handle of physical memory object
        Context* pContext,                              ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the physical memory object
        ) :
        m_handle( handle ),
        m_pContext( pContext ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reserves pages in virtual address space.
    /// 
    /// @details
    ///     - The application must only use the memory allocation on the context for
    ///       which it was created.
    ///     - The starting address and size must be page aligned. See
    ///       ::zeVirtualMemQueryPageSize.
    ///     - If pStart is not null then implementation will attempt to reserve
    ///       starting from that address. If not available then will find another
    ///       suitable starting address.
    ///     - The application may call this function from simultaneous threads.
    ///     - The access attributes will default to none to indicate reservation is
    ///       inaccessible.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - void*: pointer to virtual reservation.
    /// 
    /// @throws result_t
    void* ZE_APICALL
    VirtualMem::Reserve(
        Context* pContext,                              ///< [in] pointer to the context object
        const void* pStart,                             ///< [in] pointer to start of region to reserve. If nullptr then
                                                        ///< implementation will choose a start address.
        size_t size                                     ///< [in] size in bytes to reserve; must be page aligned.
        )
    {
        void* pptr;

        auto result = static_cast<result_t>( ::zeVirtualMemReserve(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            pStart,
            size,
            &pptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::VirtualMem::Reserve" );

        return pptr;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Free pages in a reserved virtual address range.
    /// 
    /// @details
    ///     - Any existing virtual mappings for the range will be unmapped.
    ///     - Physical allocations objects that were mapped to this range will not
    ///       be destroyed. These need to be destroyed explicitly.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @throws result_t
    void ZE_APICALL
    VirtualMem::Free(
        Context* pContext,                              ///< [in] pointer to the context object
        const void* ptr,                                ///< [in] pointer to start of region to free.
        size_t size                                     ///< [in] size in bytes to free; must be page aligned.
        )
    {
        auto result = static_cast<result_t>( ::zeVirtualMemFree(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            ptr,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::VirtualMem::Free" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Queries page size to use for aligning virtual memory reservations and
    ///        physical memory allocations.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - size_t: pointer to page size to use for start address and size alignments.
    /// 
    /// @throws result_t
    size_t ZE_APICALL
    VirtualMem::QueryPageSize(
        Context* pContext,                              ///< [in] pointer to the context object
        Device* pDevice,                                ///< [in] pointer to the device object
        size_t size                                     ///< [in] unaligned allocation size in bytes
        )
    {
        size_t pagesize;

        auto result = static_cast<result_t>( ::zeVirtualMemQueryPageSize(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            size,
            &pagesize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::VirtualMem::QueryPageSize" );

        return pagesize;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates a physical memory object for the context.
    /// 
    /// @details
    ///     - The application must only use the physical memory object on the
    ///       context for which it was created.
    ///     - The size must be page aligned. See ::zeVirtualMemQueryPageSize.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @returns
    ///     - PhysicalMem*: pointer to handle of physical memory object created
    /// 
    /// @throws result_t
    PhysicalMem* ZE_APICALL
    PhysicalMem::Create(
        Context* pContext,                              ///< [in] pointer to the context object
        Device* pDevice,                                ///< [in] pointer to the device object
        desc_t* desc                                    ///< [in] pointer to physical memory descriptor.
        )
    {
        ze_physical_mem_handle_t hPhysicalMemory;

        auto result = static_cast<result_t>( ::zePhysicalMemCreate(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<ze_physical_mem_desc_t*>( desc ),
            &hPhysicalMemory ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::PhysicalMem::Create" );

        PhysicalMem* pPhysicalMemory = nullptr;

        try
        {
            pPhysicalMemory = new PhysicalMem( reinterpret_cast<physical_mem_handle_t>( hPhysicalMemory ), pContext, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pPhysicalMemory;
            pPhysicalMemory = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "ze::PhysicalMem::Create" );
        }

        return pPhysicalMemory;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys a physical memory object.
    /// 
    /// @details
    ///     - The application must ensure the device is not currently referencing
    ///       the physical memory object before it is deleted
    ///     - The application must **not** call this function from simultaneous
    ///       threads with the same physical memory handle.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @throws result_t
    void ZE_APICALL
    PhysicalMem::Destroy(
        Context* pContext,                              ///< [in] pointer to the context object
        PhysicalMem* pPhysicalMemory                    ///< [in][release] pointer to physical memory object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zePhysicalMemDestroy(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            reinterpret_cast<ze_physical_mem_handle_t>( pPhysicalMemory->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::PhysicalMem::Destroy" );

        delete pPhysicalMemory;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Maps pages in virtual address space to pages from physical memory
    ///        object.
    /// 
    /// @details
    ///     - The virtual address range must have been reserved using
    ///       ::zeVirtualMemReserve.
    ///     - The application must only use the mapped memory allocation on the
    ///       context for which it was created.
    ///     - The virtual start address and size must be page aligned. See
    ///       ::zeVirtualMemQueryPageSize.
    ///     - The application should use, for the starting address and size, the
    ///       same size alignment used for the physical allocation.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @throws result_t
    void ZE_APICALL
    VirtualMem::Map(
        Context* pContext,                              ///< [in] pointer to the context object
        const void* ptr,                                ///< [in] pointer to start of virtual address range to map.
        size_t size,                                    ///< [in] size in bytes of virtual address range to map; must be page
                                                        ///< aligned.
        PhysicalMem* pPhysicalMemory,                   ///< [in] handle to physical memory object.
        size_t offset,                                  ///< [in] offset into physical memory allocation object; must be page
                                                        ///< aligned.
        memory_access_attribute_t access                ///< [in] specifies page access attributes to apply to the virtual address
                                                        ///< range.
        )
    {
        auto result = static_cast<result_t>( ::zeVirtualMemMap(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            ptr,
            size,
            reinterpret_cast<ze_physical_mem_handle_t>( pPhysicalMemory->getHandle() ),
            offset,
            static_cast<ze_memory_access_attribute_t>( access ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::VirtualMem::Map" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Unmaps pages in virtual address space from pages from a physical
    ///        memory object.
    /// 
    /// @details
    ///     - The page access attributes for virtual address range will revert back
    ///       to none.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function must be thread-safe.
    /// 
    /// @throws result_t
    void ZE_APICALL
    VirtualMem::Unmap(
        Context* pContext,                              ///< [in] pointer to the context object
        const void* ptr,                                ///< [in] pointer to start of region to unmap.
        size_t size                                     ///< [in] size in bytes to unmap; must be page aligned.
        )
    {
        auto result = static_cast<result_t>( ::zeVirtualMemUnmap(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            ptr,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::VirtualMem::Unmap" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set memory access attributes for a virtual address range.
    /// 
    /// @details
    ///     - This function may be called from simultaneous threads with the same
    ///       function handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    VirtualMem::SetAccessAttribute(
        Context* pContext,                              ///< [in] pointer to the context object
        const void* ptr,                                ///< [in] pointer to start of reserved virtual address region.
        size_t size,                                    ///< [in] size in bytes; must be page aligned.
        memory_access_attribute_t access                ///< [in] specifies page access attributes to apply to the virtual address
                                                        ///< range.
        )
    {
        auto result = static_cast<result_t>( ::zeVirtualMemSetAccessAttribute(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            ptr,
            size,
            static_cast<ze_memory_access_attribute_t>( access ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::VirtualMem::SetAccessAttribute" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get memory access attribute for a virtual address range.
    /// 
    /// @details
    ///     - If size and outSize are equal then the pages in the specified virtual
    ///       address range have the same access attributes.
    ///     - This function may be called from simultaneous threads with the same
    ///       function handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - memory_access_attribute_t: query result for page access attribute.
    ///     - size_t: query result for size of virtual address range, starting at ptr, that shares same access attribute.
    /// 
    /// @throws result_t
    std::tuple<VirtualMem::memory_access_attribute_t, size_t> ZE_APICALL
    VirtualMem::GetAccessAttribute(
        Context* pContext,                              ///< [in] pointer to the context object
        const void* ptr,                                ///< [in] pointer to start of virtual address region for query.
        size_t size                                     ///< [in] size in bytes; must be page aligned.
        )
    {
        ze_memory_access_attribute_t access;

        size_t outSize;

        auto result = static_cast<result_t>( ::zeVirtualMemGetAccessAttribute(
            reinterpret_cast<ze_context_handle_t>( pContext->getHandle() ),
            ptr,
            size,
            &access,
            &outSize ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "ze::VirtualMem::GetAccessAttribute" );

        return std::make_tuple( *reinterpret_cast<memory_access_attribute_t*>( &access ), outSize );
    }

#pragma endregion
} // namespace ze

namespace ze
{
#pragma region common
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ipc_mem_handle_t to std::string
    std::string to_string( const ipc_mem_handle_t val )
    {
        std::string str;
        
        str += "ipc_mem_handle_t::data : ";
        str += val.data;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ipc_event_pool_handle_t to std::string
    std::string to_string( const ipc_event_pool_handle_t val )
    {
        std::string str;
        
        str += "ipc_event_pool_handle_t::data : ";
        str += val.data;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts result_t to std::string
    std::string to_string( const result_t val )
    {
        std::string str;

        switch( val )
        {
        case result_t::SUCCESS:
            str = "result_t::SUCCESS";
            break;

        case result_t::NOT_READY:
            str = "result_t::NOT_READY";
            break;

        case result_t::ERROR_DEVICE_LOST:
            str = "result_t::ERROR_DEVICE_LOST";
            break;

        case result_t::ERROR_OUT_OF_HOST_MEMORY:
            str = "result_t::ERROR_OUT_OF_HOST_MEMORY";
            break;

        case result_t::ERROR_OUT_OF_DEVICE_MEMORY:
            str = "result_t::ERROR_OUT_OF_DEVICE_MEMORY";
            break;

        case result_t::ERROR_MODULE_BUILD_FAILURE:
            str = "result_t::ERROR_MODULE_BUILD_FAILURE";
            break;

        case result_t::ERROR_MODULE_LINK_FAILURE:
            str = "result_t::ERROR_MODULE_LINK_FAILURE";
            break;

        case result_t::ERROR_INSUFFICIENT_PERMISSIONS:
            str = "result_t::ERROR_INSUFFICIENT_PERMISSIONS";
            break;

        case result_t::ERROR_NOT_AVAILABLE:
            str = "result_t::ERROR_NOT_AVAILABLE";
            break;

        case result_t::ERROR_DEPENDENCY_UNAVAILABLE:
            str = "result_t::ERROR_DEPENDENCY_UNAVAILABLE";
            break;

        case result_t::ERROR_UNINITIALIZED:
            str = "result_t::ERROR_UNINITIALIZED";
            break;

        case result_t::ERROR_UNSUPPORTED_VERSION:
            str = "result_t::ERROR_UNSUPPORTED_VERSION";
            break;

        case result_t::ERROR_UNSUPPORTED_FEATURE:
            str = "result_t::ERROR_UNSUPPORTED_FEATURE";
            break;

        case result_t::ERROR_INVALID_ARGUMENT:
            str = "result_t::ERROR_INVALID_ARGUMENT";
            break;

        case result_t::ERROR_INVALID_NULL_HANDLE:
            str = "result_t::ERROR_INVALID_NULL_HANDLE";
            break;

        case result_t::ERROR_HANDLE_OBJECT_IN_USE:
            str = "result_t::ERROR_HANDLE_OBJECT_IN_USE";
            break;

        case result_t::ERROR_INVALID_NULL_POINTER:
            str = "result_t::ERROR_INVALID_NULL_POINTER";
            break;

        case result_t::ERROR_INVALID_SIZE:
            str = "result_t::ERROR_INVALID_SIZE";
            break;

        case result_t::ERROR_UNSUPPORTED_SIZE:
            str = "result_t::ERROR_UNSUPPORTED_SIZE";
            break;

        case result_t::ERROR_UNSUPPORTED_ALIGNMENT:
            str = "result_t::ERROR_UNSUPPORTED_ALIGNMENT";
            break;

        case result_t::ERROR_INVALID_SYNCHRONIZATION_OBJECT:
            str = "result_t::ERROR_INVALID_SYNCHRONIZATION_OBJECT";
            break;

        case result_t::ERROR_INVALID_ENUMERATION:
            str = "result_t::ERROR_INVALID_ENUMERATION";
            break;

        case result_t::ERROR_UNSUPPORTED_ENUMERATION:
            str = "result_t::ERROR_UNSUPPORTED_ENUMERATION";
            break;

        case result_t::ERROR_UNSUPPORTED_IMAGE_FORMAT:
            str = "result_t::ERROR_UNSUPPORTED_IMAGE_FORMAT";
            break;

        case result_t::ERROR_INVALID_NATIVE_BINARY:
            str = "result_t::ERROR_INVALID_NATIVE_BINARY";
            break;

        case result_t::ERROR_INVALID_GLOBAL_NAME:
            str = "result_t::ERROR_INVALID_GLOBAL_NAME";
            break;

        case result_t::ERROR_INVALID_KERNEL_NAME:
            str = "result_t::ERROR_INVALID_KERNEL_NAME";
            break;

        case result_t::ERROR_INVALID_FUNCTION_NAME:
            str = "result_t::ERROR_INVALID_FUNCTION_NAME";
            break;

        case result_t::ERROR_INVALID_GROUP_SIZE_DIMENSION:
            str = "result_t::ERROR_INVALID_GROUP_SIZE_DIMENSION";
            break;

        case result_t::ERROR_INVALID_GLOBAL_WIDTH_DIMENSION:
            str = "result_t::ERROR_INVALID_GLOBAL_WIDTH_DIMENSION";
            break;

        case result_t::ERROR_INVALID_KERNEL_ARGUMENT_INDEX:
            str = "result_t::ERROR_INVALID_KERNEL_ARGUMENT_INDEX";
            break;

        case result_t::ERROR_INVALID_KERNEL_ARGUMENT_SIZE:
            str = "result_t::ERROR_INVALID_KERNEL_ARGUMENT_SIZE";
            break;

        case result_t::ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE:
            str = "result_t::ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE";
            break;

        case result_t::ERROR_INVALID_MODULE_UNLINKED:
            str = "result_t::ERROR_INVALID_MODULE_UNLINKED";
            break;

        case result_t::ERROR_INVALID_COMMAND_LIST_TYPE:
            str = "result_t::ERROR_INVALID_COMMAND_LIST_TYPE";
            break;

        case result_t::ERROR_OVERLAPPING_REGIONS:
            str = "result_t::ERROR_OVERLAPPING_REGIONS";
            break;

        case result_t::ERROR_UNKNOWN:
            str = "result_t::ERROR_UNKNOWN";
            break;

        default:
            str = "result_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts structure_type_t to std::string
    std::string to_string( const structure_type_t val )
    {
        std::string str;

        switch( val )
        {
        case structure_type_t::DRIVER_PROPERTIES:
            str = "structure_type_t::DRIVER_PROPERTIES";
            break;

        case structure_type_t::DRIVER_IPC_PROPERTIES:
            str = "structure_type_t::DRIVER_IPC_PROPERTIES";
            break;

        case structure_type_t::DEVICE_PROPERTIES:
            str = "structure_type_t::DEVICE_PROPERTIES";
            break;

        case structure_type_t::DEVICE_COMPUTE_PROPERTIES:
            str = "structure_type_t::DEVICE_COMPUTE_PROPERTIES";
            break;

        case structure_type_t::DEVICE_MODULE_PROPERTIES:
            str = "structure_type_t::DEVICE_MODULE_PROPERTIES";
            break;

        case structure_type_t::COMMAND_QUEUE_GROUP_PROPERTIES:
            str = "structure_type_t::COMMAND_QUEUE_GROUP_PROPERTIES";
            break;

        case structure_type_t::DEVICE_MEMORY_PROPERTIES:
            str = "structure_type_t::DEVICE_MEMORY_PROPERTIES";
            break;

        case structure_type_t::DEVICE_MEMORY_ACCESS_PROPERTIES:
            str = "structure_type_t::DEVICE_MEMORY_ACCESS_PROPERTIES";
            break;

        case structure_type_t::DEVICE_CACHE_PROPERTIES:
            str = "structure_type_t::DEVICE_CACHE_PROPERTIES";
            break;

        case structure_type_t::DEVICE_IMAGE_PROPERTIES:
            str = "structure_type_t::DEVICE_IMAGE_PROPERTIES";
            break;

        case structure_type_t::DEVICE_P2P_PROPERTIES:
            str = "structure_type_t::DEVICE_P2P_PROPERTIES";
            break;

        case structure_type_t::DEVICE_EXTERNAL_MEMORY_PROPERTIES:
            str = "structure_type_t::DEVICE_EXTERNAL_MEMORY_PROPERTIES";
            break;

        case structure_type_t::CONTEXT_DESC:
            str = "structure_type_t::CONTEXT_DESC";
            break;

        case structure_type_t::COMMAND_QUEUE_DESC:
            str = "structure_type_t::COMMAND_QUEUE_DESC";
            break;

        case structure_type_t::COMMAND_LIST_DESC:
            str = "structure_type_t::COMMAND_LIST_DESC";
            break;

        case structure_type_t::EVENT_POOL_DESC:
            str = "structure_type_t::EVENT_POOL_DESC";
            break;

        case structure_type_t::EVENT_DESC:
            str = "structure_type_t::EVENT_DESC";
            break;

        case structure_type_t::FENCE_DESC:
            str = "structure_type_t::FENCE_DESC";
            break;

        case structure_type_t::IMAGE_DESC:
            str = "structure_type_t::IMAGE_DESC";
            break;

        case structure_type_t::IMAGE_PROPERTIES:
            str = "structure_type_t::IMAGE_PROPERTIES";
            break;

        case structure_type_t::DEVICE_MEM_ALLOC_DESC:
            str = "structure_type_t::DEVICE_MEM_ALLOC_DESC";
            break;

        case structure_type_t::HOST_MEM_ALLOC_DESC:
            str = "structure_type_t::HOST_MEM_ALLOC_DESC";
            break;

        case structure_type_t::MEMORY_ALLOCATION_PROPERTIES:
            str = "structure_type_t::MEMORY_ALLOCATION_PROPERTIES";
            break;

        case structure_type_t::EXTERNAL_MEMORY_EXPORT_DESC:
            str = "structure_type_t::EXTERNAL_MEMORY_EXPORT_DESC";
            break;

        case structure_type_t::EXTERNAL_MEMORY_IMPORT_FD:
            str = "structure_type_t::EXTERNAL_MEMORY_IMPORT_FD";
            break;

        case structure_type_t::EXTERNAL_MEMORY_EXPORT_FD:
            str = "structure_type_t::EXTERNAL_MEMORY_EXPORT_FD";
            break;

        case structure_type_t::MODULE_DESC:
            str = "structure_type_t::MODULE_DESC";
            break;

        case structure_type_t::MODULE_PROPERTIES:
            str = "structure_type_t::MODULE_PROPERTIES";
            break;

        case structure_type_t::KERNEL_DESC:
            str = "structure_type_t::KERNEL_DESC";
            break;

        case structure_type_t::KERNEL_PROPERTIES:
            str = "structure_type_t::KERNEL_PROPERTIES";
            break;

        case structure_type_t::SAMPLER_DESC:
            str = "structure_type_t::SAMPLER_DESC";
            break;

        case structure_type_t::PHYSICAL_MEM_DESC:
            str = "structure_type_t::PHYSICAL_MEM_DESC";
            break;

        case structure_type_t::RAYTRACING_MEM_ALLOC_EXT_DESC:
            str = "structure_type_t::RAYTRACING_MEM_ALLOC_EXT_DESC";
            break;

        default:
            str = "structure_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts external_memory_type_flags_t to std::string
    std::string to_string( const external_memory_type_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(EXTERNAL_MEMORY_TYPE_FLAG_OPAQUE_FD) & bits )
            str += "EXTERNAL_MEMORY_TYPE_FLAG_OPAQUE_FD | ";
        
        if( static_cast<uint32_t>(EXTERNAL_MEMORY_TYPE_FLAG_DMA_BUF) & bits )
            str += "EXTERNAL_MEMORY_TYPE_FLAG_DMA_BUF | ";

        return ( str.size() > 3 ) 
            ? "{ " + str.substr(0, str.size() - 3) + " }"
            : "{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts base_properties_t to std::string
    std::string to_string( const base_properties_t val )
    {
        std::string str;
        
        str += "base_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "base_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts base_desc_t to std::string
    std::string to_string( const base_desc_t val )
    {
        std::string str;
        
        str += "base_desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "base_desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

#pragma endregion
#pragma region driver
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts init_flags_t to std::string
    std::string to_string( const init_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(INIT_FLAG_GPU_ONLY) & bits )
            str += "INIT_FLAG_GPU_ONLY | ";

        return ( str.size() > 3 ) 
            ? "{ " + str.substr(0, str.size() - 3) + " }"
            : "{ ? }";
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
    /// @brief Converts Driver::ipc_property_flags_t to std::string
    std::string to_string( const Driver::ipc_property_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Driver::IPC_PROPERTY_FLAG_MEMORY) & bits )
            str += "IPC_PROPERTY_FLAG_MEMORY | ";
        
        if( static_cast<uint32_t>(Driver::IPC_PROPERTY_FLAG_EVENT_POOL) & bits )
            str += "IPC_PROPERTY_FLAG_EVENT_POOL | ";

        return ( str.size() > 3 ) 
            ? "Driver::{ " + str.substr(0, str.size() - 3) + " }"
            : "Driver::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::properties_t to std::string
    std::string to_string( const Driver::properties_t val )
    {
        std::string str;
        
        str += "Driver::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Driver::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
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
        
        str += "Driver::ipc_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Driver::ipc_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Driver::ipc_properties_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::extension_properties_t to std::string
    std::string to_string( const Driver::extension_properties_t val )
    {
        std::string str;
        
        str += "Driver::extension_properties_t::name : ";
        str += val.name;
        str += "\n";
        
        str += "Driver::extension_properties_t::version : ";
        str += std::to_string(val.version);
        str += "\n";

        return str;
    }

#pragma endregion
#pragma region device
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts device_uuid_t to std::string
    std::string to_string( const device_uuid_t val )
    {
        std::string str;
        
        str += "device_uuid_t::id : ";
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
    /// @brief Converts Device::type_t to std::string
    std::string to_string( const Device::type_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::type_t::GPU:
            str = "Device::type_t::GPU";
            break;

        case Device::type_t::CPU:
            str = "Device::type_t::CPU";
            break;

        case Device::type_t::FPGA:
            str = "Device::type_t::FPGA";
            break;

        case Device::type_t::MCA:
            str = "Device::type_t::MCA";
            break;

        default:
            str = "Device::type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::property_flags_t to std::string
    std::string to_string( const Device::property_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Device::PROPERTY_FLAG_INTEGRATED) & bits )
            str += "PROPERTY_FLAG_INTEGRATED | ";
        
        if( static_cast<uint32_t>(Device::PROPERTY_FLAG_SUBDEVICE) & bits )
            str += "PROPERTY_FLAG_SUBDEVICE | ";
        
        if( static_cast<uint32_t>(Device::PROPERTY_FLAG_ECC) & bits )
            str += "PROPERTY_FLAG_ECC | ";
        
        if( static_cast<uint32_t>(Device::PROPERTY_FLAG_ONDEMANDPAGING) & bits )
            str += "PROPERTY_FLAG_ONDEMANDPAGING | ";

        return ( str.size() > 3 ) 
            ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::module_flags_t to std::string
    std::string to_string( const Device::module_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Device::MODULE_FLAG_FP16) & bits )
            str += "MODULE_FLAG_FP16 | ";
        
        if( static_cast<uint32_t>(Device::MODULE_FLAG_FP64) & bits )
            str += "MODULE_FLAG_FP64 | ";
        
        if( static_cast<uint32_t>(Device::MODULE_FLAG_INT64_ATOMICS) & bits )
            str += "MODULE_FLAG_INT64_ATOMICS | ";
        
        if( static_cast<uint32_t>(Device::MODULE_FLAG_DP4A) & bits )
            str += "MODULE_FLAG_DP4A | ";

        return ( str.size() > 3 ) 
            ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::fp_flags_t to std::string
    std::string to_string( const Device::fp_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Device::FP_FLAG_DENORM) & bits )
            str += "FP_FLAG_DENORM | ";
        
        if( static_cast<uint32_t>(Device::FP_FLAG_INF_NAN) & bits )
            str += "FP_FLAG_INF_NAN | ";
        
        if( static_cast<uint32_t>(Device::FP_FLAG_ROUND_TO_NEAREST) & bits )
            str += "FP_FLAG_ROUND_TO_NEAREST | ";
        
        if( static_cast<uint32_t>(Device::FP_FLAG_ROUND_TO_ZERO) & bits )
            str += "FP_FLAG_ROUND_TO_ZERO | ";
        
        if( static_cast<uint32_t>(Device::FP_FLAG_ROUND_TO_INF) & bits )
            str += "FP_FLAG_ROUND_TO_INF | ";
        
        if( static_cast<uint32_t>(Device::FP_FLAG_FMA) & bits )
            str += "FP_FLAG_FMA | ";
        
        if( static_cast<uint32_t>(Device::FP_FLAG_ROUNDED_DIVIDE_SQRT) & bits )
            str += "FP_FLAG_ROUNDED_DIVIDE_SQRT | ";
        
        if( static_cast<uint32_t>(Device::FP_FLAG_SOFT_FLOAT) & bits )
            str += "FP_FLAG_SOFT_FLOAT | ";

        return ( str.size() > 3 ) 
            ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::command_queue_group_property_flags_t to std::string
    std::string to_string( const Device::command_queue_group_property_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Device::COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE) & bits )
            str += "COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE | ";
        
        if( static_cast<uint32_t>(Device::COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COPY) & bits )
            str += "COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COPY | ";
        
        if( static_cast<uint32_t>(Device::COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COOPERATIVE_KERNELS) & bits )
            str += "COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COOPERATIVE_KERNELS | ";
        
        if( static_cast<uint32_t>(Device::COMMAND_QUEUE_GROUP_PROPERTY_FLAG_METRICS) & bits )
            str += "COMMAND_QUEUE_GROUP_PROPERTY_FLAG_METRICS | ";

        return ( str.size() > 3 ) 
            ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_property_flags_t to std::string
    std::string to_string( const Device::memory_property_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Device::MEMORY_PROPERTY_FLAG_TBD) & bits )
            str += "MEMORY_PROPERTY_FLAG_TBD | ";

        return ( str.size() > 3 ) 
            ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_access_cap_flags_t to std::string
    std::string to_string( const Device::memory_access_cap_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Device::MEMORY_ACCESS_CAP_FLAG_RW) & bits )
            str += "MEMORY_ACCESS_CAP_FLAG_RW | ";
        
        if( static_cast<uint32_t>(Device::MEMORY_ACCESS_CAP_FLAG_ATOMIC) & bits )
            str += "MEMORY_ACCESS_CAP_FLAG_ATOMIC | ";
        
        if( static_cast<uint32_t>(Device::MEMORY_ACCESS_CAP_FLAG_CONCURRENT) & bits )
            str += "MEMORY_ACCESS_CAP_FLAG_CONCURRENT | ";
        
        if( static_cast<uint32_t>(Device::MEMORY_ACCESS_CAP_FLAG_CONCURRENT_ATOMIC) & bits )
            str += "MEMORY_ACCESS_CAP_FLAG_CONCURRENT_ATOMIC | ";

        return ( str.size() > 3 ) 
            ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::cache_property_flags_t to std::string
    std::string to_string( const Device::cache_property_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Device::CACHE_PROPERTY_FLAG_USER_CONTROL) & bits )
            str += "CACHE_PROPERTY_FLAG_USER_CONTROL | ";

        return ( str.size() > 3 ) 
            ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::p2p_property_flags_t to std::string
    std::string to_string( const Device::p2p_property_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Device::P2P_PROPERTY_FLAG_ACCESS) & bits )
            str += "P2P_PROPERTY_FLAG_ACCESS | ";
        
        if( static_cast<uint32_t>(Device::P2P_PROPERTY_FLAG_ATOMICS) & bits )
            str += "P2P_PROPERTY_FLAG_ATOMICS | ";

        return ( str.size() > 3 ) 
            ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::properties_t to std::string
    std::string to_string( const Device::properties_t val )
    {
        std::string str;
        
        str += "Device::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Device::properties_t::vendorId : ";
        str += std::to_string(val.vendorId);
        str += "\n";
        
        str += "Device::properties_t::deviceId : ";
        str += std::to_string(val.deviceId);
        str += "\n";
        
        str += "Device::properties_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Device::properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "Device::properties_t::coreClockRate : ";
        str += std::to_string(val.coreClockRate);
        str += "\n";
        
        str += "Device::properties_t::maxMemAllocSize : ";
        str += std::to_string(val.maxMemAllocSize);
        str += "\n";
        
        str += "Device::properties_t::maxHardwareContexts : ";
        str += std::to_string(val.maxHardwareContexts);
        str += "\n";
        
        str += "Device::properties_t::maxCommandQueuePriority : ";
        str += std::to_string(val.maxCommandQueuePriority);
        str += "\n";
        
        str += "Device::properties_t::numThreadsPerEU : ";
        str += std::to_string(val.numThreadsPerEU);
        str += "\n";
        
        str += "Device::properties_t::physicalEUSimdWidth : ";
        str += std::to_string(val.physicalEUSimdWidth);
        str += "\n";
        
        str += "Device::properties_t::numEUsPerSubslice : ";
        str += std::to_string(val.numEUsPerSubslice);
        str += "\n";
        
        str += "Device::properties_t::numSubslicesPerSlice : ";
        str += std::to_string(val.numSubslicesPerSlice);
        str += "\n";
        
        str += "Device::properties_t::numSlices : ";
        str += std::to_string(val.numSlices);
        str += "\n";
        
        str += "Device::properties_t::timerResolution : ";
        str += std::to_string(val.timerResolution);
        str += "\n";
        
        str += "Device::properties_t::timestampValidBits : ";
        str += std::to_string(val.timestampValidBits);
        str += "\n";
        
        str += "Device::properties_t::kernelTimestampValidBits : ";
        str += std::to_string(val.kernelTimestampValidBits);
        str += "\n";
        
        str += "Device::properties_t::uuid : ";
        str += to_string(val.uuid);
        str += "\n";
        
        str += "Device::properties_t::name : ";
        str += val.name;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::thread_t to std::string
    std::string to_string( const Device::thread_t val )
    {
        std::string str;
        
        str += "Device::thread_t::slice : ";
        str += std::to_string(val.slice);
        str += "\n";
        
        str += "Device::thread_t::subslice : ";
        str += std::to_string(val.subslice);
        str += "\n";
        
        str += "Device::thread_t::eu : ";
        str += std::to_string(val.eu);
        str += "\n";
        
        str += "Device::thread_t::thread : ";
        str += std::to_string(val.thread);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::compute_properties_t to std::string
    std::string to_string( const Device::compute_properties_t val )
    {
        std::string str;
        
        str += "Device::compute_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::compute_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::compute_properties_t::maxTotalGroupSize : ";
        str += std::to_string(val.maxTotalGroupSize);
        str += "\n";
        
        str += "Device::compute_properties_t::maxGroupSizeX : ";
        str += std::to_string(val.maxGroupSizeX);
        str += "\n";
        
        str += "Device::compute_properties_t::maxGroupSizeY : ";
        str += std::to_string(val.maxGroupSizeY);
        str += "\n";
        
        str += "Device::compute_properties_t::maxGroupSizeZ : ";
        str += std::to_string(val.maxGroupSizeZ);
        str += "\n";
        
        str += "Device::compute_properties_t::maxGroupCountX : ";
        str += std::to_string(val.maxGroupCountX);
        str += "\n";
        
        str += "Device::compute_properties_t::maxGroupCountY : ";
        str += std::to_string(val.maxGroupCountY);
        str += "\n";
        
        str += "Device::compute_properties_t::maxGroupCountZ : ";
        str += std::to_string(val.maxGroupCountZ);
        str += "\n";
        
        str += "Device::compute_properties_t::maxSharedLocalMemory : ";
        str += std::to_string(val.maxSharedLocalMemory);
        str += "\n";
        
        str += "Device::compute_properties_t::numSubGroupSizes : ";
        str += std::to_string(val.numSubGroupSizes);
        str += "\n";
        
        str += "Device::compute_properties_t::subGroupSizes : ";
        {
            std::string tmp;
            for( auto& entry : val.subGroupSizes )
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
    /// @brief Converts Device::native_kernel_uuid_t to std::string
    std::string to_string( const Device::native_kernel_uuid_t val )
    {
        std::string str;
        
        str += "Device::native_kernel_uuid_t::id : ";
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
    /// @brief Converts Device::module_properties_t to std::string
    std::string to_string( const Device::module_properties_t val )
    {
        std::string str;
        
        str += "Device::module_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::module_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::module_properties_t::spirvVersionSupported : ";
        str += std::to_string(val.spirvVersionSupported);
        str += "\n";
        
        str += "Device::module_properties_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Device::module_properties_t::fp16flags : ";
        str += to_string(val.fp16flags);
        str += "\n";
        
        str += "Device::module_properties_t::fp32flags : ";
        str += to_string(val.fp32flags);
        str += "\n";
        
        str += "Device::module_properties_t::fp64flags : ";
        str += to_string(val.fp64flags);
        str += "\n";
        
        str += "Device::module_properties_t::maxArgumentsSize : ";
        str += std::to_string(val.maxArgumentsSize);
        str += "\n";
        
        str += "Device::module_properties_t::printfBufferSize : ";
        str += std::to_string(val.printfBufferSize);
        str += "\n";
        
        str += "Device::module_properties_t::nativeKernelSupported : ";
        str += to_string(val.nativeKernelSupported);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::command_queue_group_properties_t to std::string
    std::string to_string( const Device::command_queue_group_properties_t val )
    {
        std::string str;
        
        str += "Device::command_queue_group_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::command_queue_group_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::command_queue_group_properties_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Device::command_queue_group_properties_t::maxMemoryFillPatternSize : ";
        str += std::to_string(val.maxMemoryFillPatternSize);
        str += "\n";
        
        str += "Device::command_queue_group_properties_t::numQueues : ";
        str += std::to_string(val.numQueues);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_properties_t to std::string
    std::string to_string( const Device::memory_properties_t val )
    {
        std::string str;
        
        str += "Device::memory_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::memory_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::memory_properties_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Device::memory_properties_t::maxClockRate : ";
        str += std::to_string(val.maxClockRate);
        str += "\n";
        
        str += "Device::memory_properties_t::maxBusWidth : ";
        str += std::to_string(val.maxBusWidth);
        str += "\n";
        
        str += "Device::memory_properties_t::totalSize : ";
        str += std::to_string(val.totalSize);
        str += "\n";
        
        str += "Device::memory_properties_t::name : ";
        str += val.name;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_access_properties_t to std::string
    std::string to_string( const Device::memory_access_properties_t val )
    {
        std::string str;
        
        str += "Device::memory_access_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::memory_access_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::memory_access_properties_t::hostAllocCapabilities : ";
        str += to_string(val.hostAllocCapabilities);
        str += "\n";
        
        str += "Device::memory_access_properties_t::deviceAllocCapabilities : ";
        str += to_string(val.deviceAllocCapabilities);
        str += "\n";
        
        str += "Device::memory_access_properties_t::sharedSingleDeviceAllocCapabilities : ";
        str += to_string(val.sharedSingleDeviceAllocCapabilities);
        str += "\n";
        
        str += "Device::memory_access_properties_t::sharedCrossDeviceAllocCapabilities : ";
        str += to_string(val.sharedCrossDeviceAllocCapabilities);
        str += "\n";
        
        str += "Device::memory_access_properties_t::sharedSystemAllocCapabilities : ";
        str += to_string(val.sharedSystemAllocCapabilities);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::cache_properties_t to std::string
    std::string to_string( const Device::cache_properties_t val )
    {
        std::string str;
        
        str += "Device::cache_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::cache_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::cache_properties_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Device::cache_properties_t::cacheSize : ";
        str += std::to_string(val.cacheSize);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::image_properties_t to std::string
    std::string to_string( const Device::image_properties_t val )
    {
        std::string str;
        
        str += "Device::image_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::image_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::image_properties_t::maxImageDims1D : ";
        str += std::to_string(val.maxImageDims1D);
        str += "\n";
        
        str += "Device::image_properties_t::maxImageDims2D : ";
        str += std::to_string(val.maxImageDims2D);
        str += "\n";
        
        str += "Device::image_properties_t::maxImageDims3D : ";
        str += std::to_string(val.maxImageDims3D);
        str += "\n";
        
        str += "Device::image_properties_t::maxImageBufferSize : ";
        str += std::to_string(val.maxImageBufferSize);
        str += "\n";
        
        str += "Device::image_properties_t::maxImageArraySlices : ";
        str += std::to_string(val.maxImageArraySlices);
        str += "\n";
        
        str += "Device::image_properties_t::maxSamplers : ";
        str += std::to_string(val.maxSamplers);
        str += "\n";
        
        str += "Device::image_properties_t::maxReadImageArgs : ";
        str += std::to_string(val.maxReadImageArgs);
        str += "\n";
        
        str += "Device::image_properties_t::maxWriteImageArgs : ";
        str += std::to_string(val.maxWriteImageArgs);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::external_memory_properties_t to std::string
    std::string to_string( const Device::external_memory_properties_t val )
    {
        std::string str;
        
        str += "Device::external_memory_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::external_memory_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::external_memory_properties_t::memoryAllocationImportTypes : ";
        str += to_string(val.memoryAllocationImportTypes);
        str += "\n";
        
        str += "Device::external_memory_properties_t::memoryAllocationExportTypes : ";
        str += to_string(val.memoryAllocationExportTypes);
        str += "\n";
        
        str += "Device::external_memory_properties_t::imageImportTypes : ";
        str += to_string(val.imageImportTypes);
        str += "\n";
        
        str += "Device::external_memory_properties_t::imageExportTypes : ";
        str += to_string(val.imageExportTypes);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::p2p_properties_t to std::string
    std::string to_string( const Device::p2p_properties_t val )
    {
        std::string str;
        
        str += "Device::p2p_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::p2p_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::p2p_properties_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

#pragma endregion
#pragma region context
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Context::flags_t to std::string
    std::string to_string( const Context::flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Context::FLAG_TBD) & bits )
            str += "FLAG_TBD | ";

        return ( str.size() > 3 ) 
            ? "Context::{ " + str.substr(0, str.size() - 3) + " }"
            : "Context::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Context::raytracing_mem_alloc_ext_flags_t to std::string
    std::string to_string( const Context::raytracing_mem_alloc_ext_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Context::RAYTRACING_MEM_ALLOC_EXT_FLAG_TBD) & bits )
            str += "RAYTRACING_MEM_ALLOC_EXT_FLAG_TBD | ";

        return ( str.size() > 3 ) 
            ? "Context::{ " + str.substr(0, str.size() - 3) + " }"
            : "Context::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Context::desc_t to std::string
    std::string to_string( const Context::desc_t val )
    {
        std::string str;
        
        str += "Context::desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Context::desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Context::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Context::raytracing_mem_alloc_ext_desc_t to std::string
    std::string to_string( const Context::raytracing_mem_alloc_ext_desc_t val )
    {
        std::string str;
        
        str += "Context::raytracing_mem_alloc_ext_desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Context::raytracing_mem_alloc_ext_desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Context::raytracing_mem_alloc_ext_desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

#pragma endregion
#pragma region cmdqueue
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::flags_t to std::string
    std::string to_string( const CommandQueue::flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(CommandQueue::FLAG_EXPLICIT_ONLY) & bits )
            str += "FLAG_EXPLICIT_ONLY | ";

        return ( str.size() > 3 ) 
            ? "CommandQueue::{ " + str.substr(0, str.size() - 3) + " }"
            : "CommandQueue::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::mode_t to std::string
    std::string to_string( const CommandQueue::mode_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandQueue::mode_t::DEFAULT:
            str = "CommandQueue::mode_t::DEFAULT";
            break;

        case CommandQueue::mode_t::SYNCHRONOUS:
            str = "CommandQueue::mode_t::SYNCHRONOUS";
            break;

        case CommandQueue::mode_t::ASYNCHRONOUS:
            str = "CommandQueue::mode_t::ASYNCHRONOUS";
            break;

        default:
            str = "CommandQueue::mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::priority_t to std::string
    std::string to_string( const CommandQueue::priority_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandQueue::priority_t::NORMAL:
            str = "CommandQueue::priority_t::NORMAL";
            break;

        case CommandQueue::priority_t::PRIORITY_LOW:
            str = "CommandQueue::priority_t::PRIORITY_LOW";
            break;

        case CommandQueue::priority_t::PRIORITY_HIGH:
            str = "CommandQueue::priority_t::PRIORITY_HIGH";
            break;

        default:
            str = "CommandQueue::priority_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::desc_t to std::string
    std::string to_string( const CommandQueue::desc_t val )
    {
        std::string str;
        
        str += "CommandQueue::desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "CommandQueue::desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "CommandQueue::desc_t::ordinal : ";
        str += std::to_string(val.ordinal);
        str += "\n";
        
        str += "CommandQueue::desc_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "CommandQueue::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "CommandQueue::desc_t::mode : ";
        str += to_string(val.mode);
        str += "\n";
        
        str += "CommandQueue::desc_t::priority : ";
        str += to_string(val.priority);
        str += "\n";

        return str;
    }

#pragma endregion
#pragma region cmdlist
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::flags_t to std::string
    std::string to_string( const CommandList::flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(CommandList::FLAG_RELAXED_ORDERING) & bits )
            str += "FLAG_RELAXED_ORDERING | ";
        
        if( static_cast<uint32_t>(CommandList::FLAG_MAXIMIZE_THROUGHPUT) & bits )
            str += "FLAG_MAXIMIZE_THROUGHPUT | ";
        
        if( static_cast<uint32_t>(CommandList::FLAG_EXPLICIT_ONLY) & bits )
            str += "FLAG_EXPLICIT_ONLY | ";

        return ( str.size() > 3 ) 
            ? "CommandList::{ " + str.substr(0, str.size() - 3) + " }"
            : "CommandList::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::memory_advice_t to std::string
    std::string to_string( const CommandList::memory_advice_t val )
    {
        std::string str;

        switch( val )
        {
        case CommandList::memory_advice_t::SET_READ_MOSTLY:
            str = "CommandList::memory_advice_t::SET_READ_MOSTLY";
            break;

        case CommandList::memory_advice_t::CLEAR_READ_MOSTLY:
            str = "CommandList::memory_advice_t::CLEAR_READ_MOSTLY";
            break;

        case CommandList::memory_advice_t::SET_PREFERRED_LOCATION:
            str = "CommandList::memory_advice_t::SET_PREFERRED_LOCATION";
            break;

        case CommandList::memory_advice_t::CLEAR_PREFERRED_LOCATION:
            str = "CommandList::memory_advice_t::CLEAR_PREFERRED_LOCATION";
            break;

        case CommandList::memory_advice_t::SET_NON_ATOMIC_MOSTLY:
            str = "CommandList::memory_advice_t::SET_NON_ATOMIC_MOSTLY";
            break;

        case CommandList::memory_advice_t::CLEAR_NON_ATOMIC_MOSTLY:
            str = "CommandList::memory_advice_t::CLEAR_NON_ATOMIC_MOSTLY";
            break;

        case CommandList::memory_advice_t::BIAS_CACHED:
            str = "CommandList::memory_advice_t::BIAS_CACHED";
            break;

        case CommandList::memory_advice_t::BIAS_UNCACHED:
            str = "CommandList::memory_advice_t::BIAS_UNCACHED";
            break;

        default:
            str = "CommandList::memory_advice_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::desc_t to std::string
    std::string to_string( const CommandList::desc_t val )
    {
        std::string str;
        
        str += "CommandList::desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "CommandList::desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "CommandList::desc_t::commandQueueGroupOrdinal : ";
        str += std::to_string(val.commandQueueGroupOrdinal);
        str += "\n";
        
        str += "CommandList::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::copy_region_t to std::string
    std::string to_string( const CommandList::copy_region_t val )
    {
        std::string str;
        
        str += "CommandList::copy_region_t::originX : ";
        str += std::to_string(val.originX);
        str += "\n";
        
        str += "CommandList::copy_region_t::originY : ";
        str += std::to_string(val.originY);
        str += "\n";
        
        str += "CommandList::copy_region_t::originZ : ";
        str += std::to_string(val.originZ);
        str += "\n";
        
        str += "CommandList::copy_region_t::width : ";
        str += std::to_string(val.width);
        str += "\n";
        
        str += "CommandList::copy_region_t::height : ";
        str += std::to_string(val.height);
        str += "\n";
        
        str += "CommandList::copy_region_t::depth : ";
        str += std::to_string(val.depth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::image_region_t to std::string
    std::string to_string( const CommandList::image_region_t val )
    {
        std::string str;
        
        str += "CommandList::image_region_t::originX : ";
        str += std::to_string(val.originX);
        str += "\n";
        
        str += "CommandList::image_region_t::originY : ";
        str += std::to_string(val.originY);
        str += "\n";
        
        str += "CommandList::image_region_t::originZ : ";
        str += std::to_string(val.originZ);
        str += "\n";
        
        str += "CommandList::image_region_t::width : ";
        str += std::to_string(val.width);
        str += "\n";
        
        str += "CommandList::image_region_t::height : ";
        str += std::to_string(val.height);
        str += "\n";
        
        str += "CommandList::image_region_t::depth : ";
        str += std::to_string(val.depth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::group_count_t to std::string
    std::string to_string( const CommandList::group_count_t val )
    {
        std::string str;
        
        str += "CommandList::group_count_t::groupCountX : ";
        str += std::to_string(val.groupCountX);
        str += "\n";
        
        str += "CommandList::group_count_t::groupCountY : ";
        str += std::to_string(val.groupCountY);
        str += "\n";
        
        str += "CommandList::group_count_t::groupCountZ : ";
        str += std::to_string(val.groupCountZ);
        str += "\n";

        return str;
    }

#pragma endregion
#pragma region barrier
#pragma endregion
#pragma region copy
#pragma endregion
#pragma region event
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::flags_t to std::string
    std::string to_string( const EventPool::flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(EventPool::FLAG_HOST_VISIBLE) & bits )
            str += "FLAG_HOST_VISIBLE | ";
        
        if( static_cast<uint32_t>(EventPool::FLAG_IPC) & bits )
            str += "FLAG_IPC | ";
        
        if( static_cast<uint32_t>(EventPool::FLAG_KERNEL_TIMESTAMP) & bits )
            str += "FLAG_KERNEL_TIMESTAMP | ";

        return ( str.size() > 3 ) 
            ? "EventPool::{ " + str.substr(0, str.size() - 3) + " }"
            : "EventPool::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::desc_t to std::string
    std::string to_string( const EventPool::desc_t val )
    {
        std::string str;
        
        str += "EventPool::desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "EventPool::desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "EventPool::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "EventPool::desc_t::count : ";
        str += std::to_string(val.count);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::scope_flags_t to std::string
    std::string to_string( const Event::scope_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Event::SCOPE_FLAG_SUBDEVICE) & bits )
            str += "SCOPE_FLAG_SUBDEVICE | ";
        
        if( static_cast<uint32_t>(Event::SCOPE_FLAG_DEVICE) & bits )
            str += "SCOPE_FLAG_DEVICE | ";
        
        if( static_cast<uint32_t>(Event::SCOPE_FLAG_HOST) & bits )
            str += "SCOPE_FLAG_HOST | ";

        return ( str.size() > 3 ) 
            ? "Event::{ " + str.substr(0, str.size() - 3) + " }"
            : "Event::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::desc_t to std::string
    std::string to_string( const Event::desc_t val )
    {
        std::string str;
        
        str += "Event::desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Event::desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Event::desc_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Event::desc_t::signal : ";
        str += to_string(val.signal);
        str += "\n";
        
        str += "Event::desc_t::wait : ";
        str += to_string(val.wait);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::kernel_timestamp_data_t to std::string
    std::string to_string( const Event::kernel_timestamp_data_t val )
    {
        std::string str;
        
        str += "Event::kernel_timestamp_data_t::kernelStart : ";
        str += std::to_string(val.kernelStart);
        str += "\n";
        
        str += "Event::kernel_timestamp_data_t::kernelEnd : ";
        str += std::to_string(val.kernelEnd);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::kernel_timestamp_result_t to std::string
    std::string to_string( const Event::kernel_timestamp_result_t val )
    {
        std::string str;
        
        str += "Event::kernel_timestamp_result_t::global : ";
        str += to_string(val.global);
        str += "\n";
        
        str += "Event::kernel_timestamp_result_t::context : ";
        str += to_string(val.context);
        str += "\n";

        return str;
    }

#pragma endregion
#pragma region fence
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::flags_t to std::string
    std::string to_string( const Fence::flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Fence::FLAG_SIGNALED) & bits )
            str += "FLAG_SIGNALED | ";

        return ( str.size() > 3 ) 
            ? "Fence::{ " + str.substr(0, str.size() - 3) + " }"
            : "Fence::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::desc_t to std::string
    std::string to_string( const Fence::desc_t val )
    {
        std::string str;
        
        str += "Fence::desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Fence::desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Fence::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

#pragma endregion
#pragma region image
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::flags_t to std::string
    std::string to_string( const Image::flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Image::FLAG_KERNEL_WRITE) & bits )
            str += "FLAG_KERNEL_WRITE | ";
        
        if( static_cast<uint32_t>(Image::FLAG_BIAS_UNCACHED) & bits )
            str += "FLAG_BIAS_UNCACHED | ";

        return ( str.size() > 3 ) 
            ? "Image::{ " + str.substr(0, str.size() - 3) + " }"
            : "Image::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::type_t to std::string
    std::string to_string( const Image::type_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::type_t::_1D:
            str = "Image::type_t::_1D";
            break;

        case Image::type_t::_1DARRAY:
            str = "Image::type_t::_1DARRAY";
            break;

        case Image::type_t::_2D:
            str = "Image::type_t::_2D";
            break;

        case Image::type_t::_2DARRAY:
            str = "Image::type_t::_2DARRAY";
            break;

        case Image::type_t::_3D:
            str = "Image::type_t::_3D";
            break;

        case Image::type_t::BUFFER:
            str = "Image::type_t::BUFFER";
            break;

        default:
            str = "Image::type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_layout_t to std::string
    std::string to_string( const Image::format_layout_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::format_layout_t::_8:
            str = "Image::format_layout_t::_8";
            break;

        case Image::format_layout_t::_16:
            str = "Image::format_layout_t::_16";
            break;

        case Image::format_layout_t::_32:
            str = "Image::format_layout_t::_32";
            break;

        case Image::format_layout_t::_8_8:
            str = "Image::format_layout_t::_8_8";
            break;

        case Image::format_layout_t::_8_8_8_8:
            str = "Image::format_layout_t::_8_8_8_8";
            break;

        case Image::format_layout_t::_16_16:
            str = "Image::format_layout_t::_16_16";
            break;

        case Image::format_layout_t::_16_16_16_16:
            str = "Image::format_layout_t::_16_16_16_16";
            break;

        case Image::format_layout_t::_32_32:
            str = "Image::format_layout_t::_32_32";
            break;

        case Image::format_layout_t::_32_32_32_32:
            str = "Image::format_layout_t::_32_32_32_32";
            break;

        case Image::format_layout_t::_10_10_10_2:
            str = "Image::format_layout_t::_10_10_10_2";
            break;

        case Image::format_layout_t::_11_11_10:
            str = "Image::format_layout_t::_11_11_10";
            break;

        case Image::format_layout_t::_5_6_5:
            str = "Image::format_layout_t::_5_6_5";
            break;

        case Image::format_layout_t::_5_5_5_1:
            str = "Image::format_layout_t::_5_5_5_1";
            break;

        case Image::format_layout_t::_4_4_4_4:
            str = "Image::format_layout_t::_4_4_4_4";
            break;

        case Image::format_layout_t::Y8:
            str = "Image::format_layout_t::Y8";
            break;

        case Image::format_layout_t::NV12:
            str = "Image::format_layout_t::NV12";
            break;

        case Image::format_layout_t::YUYV:
            str = "Image::format_layout_t::YUYV";
            break;

        case Image::format_layout_t::VYUY:
            str = "Image::format_layout_t::VYUY";
            break;

        case Image::format_layout_t::YVYU:
            str = "Image::format_layout_t::YVYU";
            break;

        case Image::format_layout_t::UYVY:
            str = "Image::format_layout_t::UYVY";
            break;

        case Image::format_layout_t::AYUV:
            str = "Image::format_layout_t::AYUV";
            break;

        case Image::format_layout_t::P010:
            str = "Image::format_layout_t::P010";
            break;

        case Image::format_layout_t::Y410:
            str = "Image::format_layout_t::Y410";
            break;

        case Image::format_layout_t::P012:
            str = "Image::format_layout_t::P012";
            break;

        case Image::format_layout_t::Y16:
            str = "Image::format_layout_t::Y16";
            break;

        case Image::format_layout_t::P016:
            str = "Image::format_layout_t::P016";
            break;

        case Image::format_layout_t::Y216:
            str = "Image::format_layout_t::Y216";
            break;

        case Image::format_layout_t::P216:
            str = "Image::format_layout_t::P216";
            break;

        default:
            str = "Image::format_layout_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_type_t to std::string
    std::string to_string( const Image::format_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::format_type_t::UINT:
            str = "Image::format_type_t::UINT";
            break;

        case Image::format_type_t::SINT:
            str = "Image::format_type_t::SINT";
            break;

        case Image::format_type_t::UNORM:
            str = "Image::format_type_t::UNORM";
            break;

        case Image::format_type_t::SNORM:
            str = "Image::format_type_t::SNORM";
            break;

        case Image::format_type_t::FLOAT:
            str = "Image::format_type_t::FLOAT";
            break;

        default:
            str = "Image::format_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_swizzle_t to std::string
    std::string to_string( const Image::format_swizzle_t val )
    {
        std::string str;

        switch( val )
        {
        case Image::format_swizzle_t::R:
            str = "Image::format_swizzle_t::R";
            break;

        case Image::format_swizzle_t::G:
            str = "Image::format_swizzle_t::G";
            break;

        case Image::format_swizzle_t::B:
            str = "Image::format_swizzle_t::B";
            break;

        case Image::format_swizzle_t::A:
            str = "Image::format_swizzle_t::A";
            break;

        case Image::format_swizzle_t::_0:
            str = "Image::format_swizzle_t::_0";
            break;

        case Image::format_swizzle_t::_1:
            str = "Image::format_swizzle_t::_1";
            break;

        case Image::format_swizzle_t::X:
            str = "Image::format_swizzle_t::X";
            break;

        default:
            str = "Image::format_swizzle_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::sampler_filter_flags_t to std::string
    std::string to_string( const Image::sampler_filter_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Image::SAMPLER_FILTER_FLAG_POINT) & bits )
            str += "SAMPLER_FILTER_FLAG_POINT | ";
        
        if( static_cast<uint32_t>(Image::SAMPLER_FILTER_FLAG_LINEAR) & bits )
            str += "SAMPLER_FILTER_FLAG_LINEAR | ";

        return ( str.size() > 3 ) 
            ? "Image::{ " + str.substr(0, str.size() - 3) + " }"
            : "Image::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_t to std::string
    std::string to_string( const Image::format_t val )
    {
        std::string str;
        
        str += "Image::format_t::layout : ";
        str += to_string(val.layout);
        str += "\n";
        
        str += "Image::format_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Image::format_t::x : ";
        str += to_string(val.x);
        str += "\n";
        
        str += "Image::format_t::y : ";
        str += to_string(val.y);
        str += "\n";
        
        str += "Image::format_t::z : ";
        str += to_string(val.z);
        str += "\n";
        
        str += "Image::format_t::w : ";
        str += to_string(val.w);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::desc_t to std::string
    std::string to_string( const Image::desc_t val )
    {
        std::string str;
        
        str += "Image::desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Image::desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Image::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Image::desc_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Image::desc_t::format : ";
        str += to_string(val.format);
        str += "\n";
        
        str += "Image::desc_t::width : ";
        str += std::to_string(val.width);
        str += "\n";
        
        str += "Image::desc_t::height : ";
        str += std::to_string(val.height);
        str += "\n";
        
        str += "Image::desc_t::depth : ";
        str += std::to_string(val.depth);
        str += "\n";
        
        str += "Image::desc_t::arraylevels : ";
        str += std::to_string(val.arraylevels);
        str += "\n";
        
        str += "Image::desc_t::miplevels : ";
        str += std::to_string(val.miplevels);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::properties_t to std::string
    std::string to_string( const Image::properties_t val )
    {
        std::string str;
        
        str += "Image::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Image::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Image::properties_t::samplerFilterFlags : ";
        str += to_string(val.samplerFilterFlags);
        str += "\n";

        return str;
    }

#pragma endregion
#pragma region memory
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::device_alloc_flags_t to std::string
    std::string to_string( const Mem::device_alloc_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Mem::DEVICE_ALLOC_FLAG_BIAS_CACHED) & bits )
            str += "DEVICE_ALLOC_FLAG_BIAS_CACHED | ";
        
        if( static_cast<uint32_t>(Mem::DEVICE_ALLOC_FLAG_BIAS_UNCACHED) & bits )
            str += "DEVICE_ALLOC_FLAG_BIAS_UNCACHED | ";

        return ( str.size() > 3 ) 
            ? "Mem::{ " + str.substr(0, str.size() - 3) + " }"
            : "Mem::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::host_alloc_flags_t to std::string
    std::string to_string( const Mem::host_alloc_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Mem::HOST_ALLOC_FLAG_BIAS_CACHED) & bits )
            str += "HOST_ALLOC_FLAG_BIAS_CACHED | ";
        
        if( static_cast<uint32_t>(Mem::HOST_ALLOC_FLAG_BIAS_UNCACHED) & bits )
            str += "HOST_ALLOC_FLAG_BIAS_UNCACHED | ";
        
        if( static_cast<uint32_t>(Mem::HOST_ALLOC_FLAG_BIAS_WRITE_COMBINED) & bits )
            str += "HOST_ALLOC_FLAG_BIAS_WRITE_COMBINED | ";

        return ( str.size() > 3 ) 
            ? "Mem::{ " + str.substr(0, str.size() - 3) + " }"
            : "Mem::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::memory_type_t to std::string
    std::string to_string( const Mem::memory_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Mem::memory_type_t::UNKNOWN:
            str = "Mem::memory_type_t::UNKNOWN";
            break;

        case Mem::memory_type_t::HOST:
            str = "Mem::memory_type_t::HOST";
            break;

        case Mem::memory_type_t::DEVICE:
            str = "Mem::memory_type_t::DEVICE";
            break;

        case Mem::memory_type_t::SHARED:
            str = "Mem::memory_type_t::SHARED";
            break;

        default:
            str = "Mem::memory_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::ipc_memory_flags_t to std::string
    std::string to_string( const Mem::ipc_memory_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Mem::IPC_MEMORY_FLAG_TBD) & bits )
            str += "IPC_MEMORY_FLAG_TBD | ";

        return ( str.size() > 3 ) 
            ? "Mem::{ " + str.substr(0, str.size() - 3) + " }"
            : "Mem::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::device_alloc_desc_t to std::string
    std::string to_string( const Mem::device_alloc_desc_t val )
    {
        std::string str;
        
        str += "Mem::device_alloc_desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Mem::device_alloc_desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Mem::device_alloc_desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Mem::device_alloc_desc_t::ordinal : ";
        str += std::to_string(val.ordinal);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::host_alloc_desc_t to std::string
    std::string to_string( const Mem::host_alloc_desc_t val )
    {
        std::string str;
        
        str += "Mem::host_alloc_desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Mem::host_alloc_desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Mem::host_alloc_desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::memory_allocation_properties_t to std::string
    std::string to_string( const Mem::memory_allocation_properties_t val )
    {
        std::string str;
        
        str += "Mem::memory_allocation_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Mem::memory_allocation_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Mem::memory_allocation_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Mem::memory_allocation_properties_t::id : ";
        str += std::to_string(val.id);
        str += "\n";
        
        str += "Mem::memory_allocation_properties_t::pageSize : ";
        str += std::to_string(val.pageSize);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::external_memory_export_desc_t to std::string
    std::string to_string( const Mem::external_memory_export_desc_t val )
    {
        std::string str;
        
        str += "Mem::external_memory_export_desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Mem::external_memory_export_desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Mem::external_memory_export_desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::external_memory_import_fd_t to std::string
    std::string to_string( const Mem::external_memory_import_fd_t val )
    {
        std::string str;
        
        str += "Mem::external_memory_import_fd_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Mem::external_memory_import_fd_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Mem::external_memory_import_fd_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Mem::external_memory_import_fd_t::fd : ";
        str += std::to_string(val.fd);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::external_memory_export_fd_t to std::string
    std::string to_string( const Mem::external_memory_export_fd_t val )
    {
        std::string str;
        
        str += "Mem::external_memory_export_fd_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Mem::external_memory_export_fd_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Mem::external_memory_export_fd_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Mem::external_memory_export_fd_t::fd : ";
        str += std::to_string(val.fd);
        str += "\n";

        return str;
    }

#pragma endregion
#pragma region module
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts kernel_uuid_t to std::string
    std::string to_string( const kernel_uuid_t val )
    {
        std::string str;
        
        str += "kernel_uuid_t::kid : ";
        {
            std::string tmp;
            for( auto& entry : val.kid )
            {
                tmp += std::to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";
        
        str += "kernel_uuid_t::mid : ";
        {
            std::string tmp;
            for( auto& entry : val.mid )
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
    /// @brief Converts Module::format_t to std::string
    std::string to_string( const Module::format_t val )
    {
        std::string str;

        switch( val )
        {
        case Module::format_t::IL_SPIRV:
            str = "Module::format_t::IL_SPIRV";
            break;

        case Module::format_t::NATIVE:
            str = "Module::format_t::NATIVE";
            break;

        default:
            str = "Module::format_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::property_flags_t to std::string
    std::string to_string( const Module::property_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Module::PROPERTY_FLAG_IMPORTS) & bits )
            str += "PROPERTY_FLAG_IMPORTS | ";

        return ( str.size() > 3 ) 
            ? "Module::{ " + str.substr(0, str.size() - 3) + " }"
            : "Module::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::constants_t to std::string
    std::string to_string( const Module::constants_t val )
    {
        std::string str;
        
        str += "Module::constants_t::numConstants : ";
        str += std::to_string(val.numConstants);
        str += "\n";
        
        str += "Module::constants_t::pConstantIds : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pConstantIds);
            str += ss.str();
        }
        str += "\n";
        
        str += "Module::constants_t::pConstantValues : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pConstantValues);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::desc_t to std::string
    std::string to_string( const Module::desc_t val )
    {
        std::string str;
        
        str += "Module::desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Module::desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Module::desc_t::format : ";
        str += to_string(val.format);
        str += "\n";
        
        str += "Module::desc_t::inputSize : ";
        str += std::to_string(val.inputSize);
        str += "\n";
        
        str += "Module::desc_t::pInputModule : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pInputModule);
            str += ss.str();
        }
        str += "\n";
        
        str += "Module::desc_t::pBuildFlags : ";
        str += val.pBuildFlags;
        str += "\n";
        
        str += "Module::desc_t::pConstants : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pConstants);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::properties_t to std::string
    std::string to_string( const Module::properties_t val )
    {
        std::string str;
        
        str += "Module::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Module::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Module::properties_t::flags : ";
        str += to_string(val.flags);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::flags_t to std::string
    std::string to_string( const Kernel::flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Kernel::FLAG_FORCE_RESIDENCY) & bits )
            str += "FLAG_FORCE_RESIDENCY | ";
        
        if( static_cast<uint32_t>(Kernel::FLAG_EXPLICIT_RESIDENCY) & bits )
            str += "FLAG_EXPLICIT_RESIDENCY | ";

        return ( str.size() > 3 ) 
            ? "Kernel::{ " + str.substr(0, str.size() - 3) + " }"
            : "Kernel::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::indirect_access_flags_t to std::string
    std::string to_string( const Kernel::indirect_access_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Kernel::INDIRECT_ACCESS_FLAG_HOST) & bits )
            str += "INDIRECT_ACCESS_FLAG_HOST | ";
        
        if( static_cast<uint32_t>(Kernel::INDIRECT_ACCESS_FLAG_DEVICE) & bits )
            str += "INDIRECT_ACCESS_FLAG_DEVICE | ";
        
        if( static_cast<uint32_t>(Kernel::INDIRECT_ACCESS_FLAG_SHARED) & bits )
            str += "INDIRECT_ACCESS_FLAG_SHARED | ";

        return ( str.size() > 3 ) 
            ? "Kernel::{ " + str.substr(0, str.size() - 3) + " }"
            : "Kernel::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::cache_config_flags_t to std::string
    std::string to_string( const Kernel::cache_config_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Kernel::CACHE_CONFIG_FLAG_LARGE_SLM) & bits )
            str += "CACHE_CONFIG_FLAG_LARGE_SLM | ";
        
        if( static_cast<uint32_t>(Kernel::CACHE_CONFIG_FLAG_LARGE_DATA) & bits )
            str += "CACHE_CONFIG_FLAG_LARGE_DATA | ";

        return ( str.size() > 3 ) 
            ? "Kernel::{ " + str.substr(0, str.size() - 3) + " }"
            : "Kernel::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::desc_t to std::string
    std::string to_string( const Kernel::desc_t val )
    {
        std::string str;
        
        str += "Kernel::desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Kernel::desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Kernel::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "Kernel::desc_t::pKernelName : ";
        str += val.pKernelName;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::properties_t to std::string
    std::string to_string( const Kernel::properties_t val )
    {
        std::string str;
        
        str += "Kernel::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Kernel::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Kernel::properties_t::numKernelArgs : ";
        str += std::to_string(val.numKernelArgs);
        str += "\n";
        
        str += "Kernel::properties_t::requiredGroupSizeX : ";
        str += std::to_string(val.requiredGroupSizeX);
        str += "\n";
        
        str += "Kernel::properties_t::requiredGroupSizeY : ";
        str += std::to_string(val.requiredGroupSizeY);
        str += "\n";
        
        str += "Kernel::properties_t::requiredGroupSizeZ : ";
        str += std::to_string(val.requiredGroupSizeZ);
        str += "\n";
        
        str += "Kernel::properties_t::requiredNumSubGroups : ";
        str += std::to_string(val.requiredNumSubGroups);
        str += "\n";
        
        str += "Kernel::properties_t::requiredSubgroupSize : ";
        str += std::to_string(val.requiredSubgroupSize);
        str += "\n";
        
        str += "Kernel::properties_t::maxSubgroupSize : ";
        str += std::to_string(val.maxSubgroupSize);
        str += "\n";
        
        str += "Kernel::properties_t::maxNumSubgroups : ";
        str += std::to_string(val.maxNumSubgroups);
        str += "\n";
        
        str += "Kernel::properties_t::localMemSize : ";
        str += std::to_string(val.localMemSize);
        str += "\n";
        
        str += "Kernel::properties_t::privateMemSize : ";
        str += std::to_string(val.privateMemSize);
        str += "\n";
        
        str += "Kernel::properties_t::spillMemSize : ";
        str += std::to_string(val.spillMemSize);
        str += "\n";
        
        str += "Kernel::properties_t::uuid : ";
        str += to_string(val.uuid);
        str += "\n";

        return str;
    }

#pragma endregion
#pragma region raytracing
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts raytracing_ext_version_t to std::string
    std::string to_string( const raytracing_ext_version_t val )
    {
        std::string str;

        switch( val )
        {
        case raytracing_ext_version_t::_1_0:
            str = "raytracing_ext_version_t::_1_0";
            break;

        default:
            str = "raytracing_ext_version_t::?";
            break;
        };

        return str;
    }

#pragma endregion
#pragma region residency
#pragma endregion
#pragma region sampler
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::address_mode_t to std::string
    std::string to_string( const Sampler::address_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Sampler::address_mode_t::NONE:
            str = "Sampler::address_mode_t::NONE";
            break;

        case Sampler::address_mode_t::REPEAT:
            str = "Sampler::address_mode_t::REPEAT";
            break;

        case Sampler::address_mode_t::CLAMP:
            str = "Sampler::address_mode_t::CLAMP";
            break;

        case Sampler::address_mode_t::CLAMP_TO_BORDER:
            str = "Sampler::address_mode_t::CLAMP_TO_BORDER";
            break;

        case Sampler::address_mode_t::MIRROR:
            str = "Sampler::address_mode_t::MIRROR";
            break;

        default:
            str = "Sampler::address_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::filter_mode_t to std::string
    std::string to_string( const Sampler::filter_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Sampler::filter_mode_t::NEAREST:
            str = "Sampler::filter_mode_t::NEAREST";
            break;

        case Sampler::filter_mode_t::LINEAR:
            str = "Sampler::filter_mode_t::LINEAR";
            break;

        default:
            str = "Sampler::filter_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::desc_t to std::string
    std::string to_string( const Sampler::desc_t val )
    {
        std::string str;
        
        str += "Sampler::desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Sampler::desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Sampler::desc_t::addressMode : ";
        str += to_string(val.addressMode);
        str += "\n";
        
        str += "Sampler::desc_t::filterMode : ";
        str += to_string(val.filterMode);
        str += "\n";
        
        str += "Sampler::desc_t::isNormalized : ";
        str += std::to_string(val.isNormalized);
        str += "\n";

        return str;
    }

#pragma endregion
#pragma region virtual
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts VirtualMem::memory_access_attribute_t to std::string
    std::string to_string( const VirtualMem::memory_access_attribute_t val )
    {
        std::string str;

        switch( val )
        {
        case VirtualMem::memory_access_attribute_t::NONE:
            str = "VirtualMem::memory_access_attribute_t::NONE";
            break;

        case VirtualMem::memory_access_attribute_t::READWRITE:
            str = "VirtualMem::memory_access_attribute_t::READWRITE";
            break;

        case VirtualMem::memory_access_attribute_t::READONLY:
            str = "VirtualMem::memory_access_attribute_t::READONLY";
            break;

        default:
            str = "VirtualMem::memory_access_attribute_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts PhysicalMem::flags_t to std::string
    std::string to_string( const PhysicalMem::flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(PhysicalMem::FLAG_TBD) & bits )
            str += "FLAG_TBD | ";

        return ( str.size() > 3 ) 
            ? "PhysicalMem::{ " + str.substr(0, str.size() - 3) + " }"
            : "PhysicalMem::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts PhysicalMem::desc_t to std::string
    std::string to_string( const PhysicalMem::desc_t val )
    {
        std::string str;
        
        str += "PhysicalMem::desc_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "PhysicalMem::desc_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "PhysicalMem::desc_t::flags : ";
        str += to_string(val.flags);
        str += "\n";
        
        str += "PhysicalMem::desc_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

#pragma endregion
} // namespace ze
