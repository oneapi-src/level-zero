/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file zes_wprapi.cpp
 * @version v1.0-r1.0.4.8
 *
 * @brief C++ wrapper of zes
 *
 */
#include "zes_api.hpp"
#include "ze_singleton.h"

#define _ZE_STRING(s) #s
#define ZE_STRING(s) _ZE_STRING(s)

namespace zes
{
#if !defined(__GNUC__)
#pragma region common
#endif
#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region device
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get properties about the device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::GetProperties(
        properties_t* pProperties                       ///< [in,out] Structure that will contain information about the device.
        )
    {
        auto result = static_cast<result_t>( ::zesDeviceGetProperties(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            reinterpret_cast<zes_device_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get information about the state of the device - if a reset is
    ///        required, reasons for the reset and if the device has been repaired
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::GetState(
        state_t* pState                                 ///< [in,out] Structure that will contain information about the device.
        )
    {
        auto result = static_cast<result_t>( ::zesDeviceGetState(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            reinterpret_cast<zes_device_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset device
    /// 
    /// @details
    ///     - Performs a PCI bus reset of the device. This will result in all
    ///       current device state being lost.
    ///     - All applications using the device should be stopped before calling
    ///       this function.
    ///     - If the force argument is specified, all applications using the device
    ///       will be forcibly killed.
    ///     - The function will block until the device has restarted or a timeout
    ///       occurred waiting for the reset to complete.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::Reset(
        ze::bool_t force                                ///< [in] If set to true, all applications that are currently using the
                                                        ///< device will be forcibly killed.
        )
    {
        auto result = static_cast<result_t>( ::zesDeviceReset(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( force ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::Reset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get information about host processes using the device
    /// 
    /// @details
    ///     - The number of processes connected to the device is dynamic. This means
    ///       that between a call to determine the value of pCount and the
    ///       subsequent call, the number of processes may have increased or
    ///       decreased. It is recommended that a large array be passed in so as to
    ///       avoid receiving the error ::ZE_RESULT_ERROR_INVALID_SIZE. Also, always
    ///       check the returned value in pCount since it may be less than the
    ///       earlier call to get the required array size.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::ProcessesGetState(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of processes.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of processes currently using the device.
                                                        ///< if count is non-zero but less than the number of processes, the driver
                                                        ///< will set to the number of processes currently using the device and
                                                        ///< return the error ::ZE_RESULT_ERROR_INVALID_SIZE.
                                                        ///< if count is larger than the number of processes, then the driver will
                                                        ///< update the value with the correct number of processes that are returned.
        process_state_t* pProcesses                     ///< [in,out][optional][range(0, *pCount)] array of process information,
                                                        ///< one for each process currently using the device
        )
    {
        auto result = static_cast<result_t>( ::zesDeviceProcessesGetState(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            reinterpret_cast<zes_process_state_t*>( pProcesses ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::ProcessesGetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get PCI properties - address, max speed
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::PciGetProperties(
        pci_properties_t* pProperties                   ///< [in,out] Will contain the PCI properties.
        )
    {
        auto result = static_cast<result_t>( ::zesDevicePciGetProperties(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            reinterpret_cast<zes_pci_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::PciGetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current PCI state - current speed
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::PciGetState(
        pci_state_t* pState                             ///< [in,out] Will contain the PCI properties.
        )
    {
        auto result = static_cast<result_t>( ::zesDevicePciGetState(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            reinterpret_cast<zes_pci_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::PciGetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get information about each configured bar
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::PciGetBars(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of PCI bars.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of bars.
                                                        ///< if count is non-zero, then driver will only retrieve that number of bars.
                                                        ///< if count is larger than the number of bar, then the driver will update
                                                        ///< the value with the correct number of bars that are returned.
        pci_bar_properties_t* pProperties               ///< [in,out][optional][range(0, *pCount)] array of bar properties
        )
    {
        auto result = static_cast<result_t>( ::zesDevicePciGetBars(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            reinterpret_cast<zes_pci_bar_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::PciGetBars" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get PCI stats - bandwidth, number of packets, number of replays
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::PciGetStats(
        pci_stats_t* pStats                             ///< [in,out] Will contain a snapshot of the latest stats.
        )
    {
        auto result = static_cast<result_t>( ::zesDevicePciGetStats(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            reinterpret_cast<zes_pci_stats_t*>( pStats ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::PciGetStats" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region diagnostics
#endif
    ///////////////////////////////////////////////////////////////////////////////
    Diagnostics::Diagnostics( 
        diag_handle_t handle,                           ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of diagnostics test suites
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EnumDiagnosticTestSuites(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        Diagnostics** ppDiagnostics                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zes_diag_handle_t> hDiagnostics;
        hDiagnostics.resize( ( ppDiagnostics ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zesDeviceEnumDiagnosticTestSuites(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            hDiagnostics.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumDiagnosticTestSuites" );

        for( uint32_t i = 0; ( ppDiagnostics ) && ( i < *pCount ); ++i )
            ppDiagnostics[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppDiagnostics ) && ( i < *pCount ); ++i )
                ppDiagnostics[ i ] = new Diagnostics( reinterpret_cast<diag_handle_t>( hDiagnostics[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppDiagnostics ) && ( i < *pCount ); ++i )
            {
                delete ppDiagnostics[ i ];
                ppDiagnostics[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumDiagnosticTestSuites" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get properties of a diagnostics test suite
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Diagnostics::GetProperties(
        diag_properties_t* pProperties                  ///< [in,out] Structure describing the properties of a diagnostics test
                                                        ///< suite
        )
    {
        auto result = static_cast<result_t>( ::zesDiagnosticsGetProperties(
            reinterpret_cast<zes_diag_handle_t>( getHandle() ),
            reinterpret_cast<zes_diag_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Diagnostics::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get individual tests that can be run separately. Not all test suites
    ///        permit running individual tests - check
    ///        ::zes_diag_properties_t.haveTests
    /// 
    /// @details
    ///     - The list of available tests is returned in order of increasing test
    ///       index ::zes_diag_test_t.index.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Diagnostics::GetTests(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of tests.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of tests available.
                                                        ///< If count is non-zero, then driver will only retrieve that number of tests.
                                                        ///< If count is larger than the number of tests available, then the driver
                                                        ///< will update the value with the correct number of tests available.
        diag_test_t* pTests                             ///< [in,out][optional][range(0, *pCount)] Array of tests sorted by
                                                        ///< increasing value of ::zes_diag_test_t.index
        )
    {
        auto result = static_cast<result_t>( ::zesDiagnosticsGetTests(
            reinterpret_cast<zes_diag_handle_t>( getHandle() ),
            pCount,
            reinterpret_cast<zes_diag_test_t*>( pTests ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Diagnostics::GetTests" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Run a diagnostics test suite, either all tests or a subset of tests.
    /// 
    /// @details
    ///     - WARNING: Performancing diagnostics may destroy current device state
    ///       information. Gracefully close any running workloads before initiating.
    ///     - To run all tests in a test suite, set start =
    ///       ::ZES_DIAG_FIRST_TEST_INDEX and end = ::ZES_DIAG_LAST_TEST_INDEX.
    ///     - If the test suite permits running individual tests,
    ///       ::zes_diag_properties_t.haveTests will be true. In this case, the
    ///       function ::zesDiagnosticsGetTests() can be called to get the list of
    ///       tests and corresponding indices that can be supplied to the arguments
    ///       start and end in this function.
    ///     - This function will block until the diagnostics have completed.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Diagnostics::RunTests(
        uint32_t start,                                 ///< [in] The index of the first test to run. Set to
                                                        ///< ::ZES_DIAG_FIRST_TEST_INDEX to start from the beginning.
        uint32_t end,                                   ///< [in] The index of the last test to run. Set to
                                                        ///< ::ZES_DIAG_LAST_TEST_INDEX to complete all tests after the start test.
        diag_result_t* pResult                          ///< [in,out] The result of the diagnostics
        )
    {
        auto result = static_cast<result_t>( ::zesDiagnosticsRunTests(
            reinterpret_cast<zes_diag_handle_t>( getHandle() ),
            start,
            end,
            reinterpret_cast<zes_diag_result_t*>( pResult ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Diagnostics::RunTests" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region engine
#endif
    ///////////////////////////////////////////////////////////////////////////////
    Engine::Engine( 
        engine_handle_t handle,                         ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of engine groups
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EnumEngineGroups(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        Engine** ppEngine                               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zes_engine_handle_t> hEngine;
        hEngine.resize( ( ppEngine ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zesDeviceEnumEngineGroups(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            hEngine.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumEngineGroups" );

        for( uint32_t i = 0; ( ppEngine ) && ( i < *pCount ); ++i )
            ppEngine[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppEngine ) && ( i < *pCount ); ++i )
                ppEngine[ i ] = new Engine( reinterpret_cast<engine_handle_t>( hEngine[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppEngine ) && ( i < *pCount ); ++i )
            {
                delete ppEngine[ i ];
                ppEngine[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumEngineGroups" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get engine group properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Engine::GetProperties(
        properties_t* pProperties                       ///< [in,out] The properties for the specified engine group.
        )
    {
        auto result = static_cast<result_t>( ::zesEngineGetProperties(
            reinterpret_cast<zes_engine_handle_t>( getHandle() ),
            reinterpret_cast<zes_engine_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Engine::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the activity stats for an engine group
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Engine::GetActivity(
        stats_t* pStats                                 ///< [in,out] Will contain a snapshot of the engine group activity
                                                        ///< counters.
        )
    {
        auto result = static_cast<result_t>( ::zesEngineGetActivity(
            reinterpret_cast<zes_engine_handle_t>( getHandle() ),
            reinterpret_cast<zes_engine_stats_t*>( pStats ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Engine::GetActivity" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region events
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Specify the list of events to listen to for a given device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EventRegister(
        Driver::event_type_flags_t events               ///< [in] List of events to listen to.
        )
    {
        auto result = static_cast<result_t>( ::zesDeviceEventRegister(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            static_cast<zes_event_type_flags_t>( events ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EventRegister" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Wait for events to be received from a one or more devices.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Driver::EventListen(
        ze::Driver* pDriver,                            ///< [in] pointer to the driver instance
        uint32_t timeout,                               ///< [in] if non-zero, then indicates the maximum time (in milliseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then will check status and return immediately;
                                                        ///< if UINT32_MAX, then function will not return until events arrive.
        uint32_t count,                                 ///< [in] Number of device handles in phDevices.
        Device** ppDevices,                             ///< [in][range(0, count)] Device handles to listen to for events. Only
                                                        ///< devices from the provided driver handle can be specified in this list.
        uint32_t* pNumDeviceEvents,                     ///< [in,out] Will contain the actual number of devices in phDevices that
                                                        ///< generated events. If non-zero, check pEvents to determine the devices
                                                        ///< and events that were received.
        event_type_flags_t* pEvents                     ///< [in,out] An array that will continue the list of events for each
                                                        ///< device listened in phDevices.
                                                        ///< This array must be at least as big as count.
                                                        ///< For every device handle in phDevices, this will provide the events
                                                        ///< that occurred for that device at the same position in this array. If
                                                        ///< no event was received for a given device, the corresponding array
                                                        ///< entry will be zero.
        )
    {
        thread_local std::vector<zes_device_handle_t> hDevices;
        hDevices.resize( 0 );
        hDevices.reserve( count );
        for( uint32_t i = 0; i < count; ++i )
            hDevices.emplace_back( reinterpret_cast<zes_device_handle_t>( ppDevices[ i ]->getHandle() ) );

        auto result = static_cast<result_t>( ::zesDriverEventListen(
            reinterpret_cast<ze_driver_handle_t>( pDriver->getHandle() ),
            timeout,
            count,
            hDevices.data(),
            pNumDeviceEvents,
            reinterpret_cast<zes_event_type_flags_t*>( pEvents ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Driver::EventListen" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region fabric
#endif
    ///////////////////////////////////////////////////////////////////////////////
    FabricPort::FabricPort( 
        fabric_port_handle_t handle,                    ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of Fabric ports in a device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EnumFabricPorts(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        FabricPort** ppPort                             ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zes_fabric_port_handle_t> hPort;
        hPort.resize( ( ppPort ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zesDeviceEnumFabricPorts(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            hPort.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumFabricPorts" );

        for( uint32_t i = 0; ( ppPort ) && ( i < *pCount ); ++i )
            ppPort[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppPort ) && ( i < *pCount ); ++i )
                ppPort[ i ] = new FabricPort( reinterpret_cast<fabric_port_handle_t>( hPort[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppPort ) && ( i < *pCount ); ++i )
            {
                delete ppPort[ i ];
                ppPort[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumFabricPorts" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get Fabric port properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    FabricPort::GetProperties(
        properties_t* pProperties                       ///< [in,out] Will contain properties of the Fabric Port.
        )
    {
        auto result = static_cast<result_t>( ::zesFabricPortGetProperties(
            reinterpret_cast<zes_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<zes_fabric_port_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::FabricPort::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get Fabric port link type
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    FabricPort::GetLinkType(
        fabric_link_type_t* pLinkType                   ///< [in,out] Will contain details about the link attached to the Fabric
                                                        ///< port.
        )
    {
        auto result = static_cast<result_t>( ::zesFabricPortGetLinkType(
            reinterpret_cast<zes_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<zes_fabric_link_type_t*>( pLinkType ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::FabricPort::GetLinkType" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get Fabric port configuration
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    FabricPort::GetConfig(
        config_t* pConfig                               ///< [in,out] Will contain configuration of the Fabric Port.
        )
    {
        auto result = static_cast<result_t>( ::zesFabricPortGetConfig(
            reinterpret_cast<zes_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<zes_fabric_port_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::FabricPort::GetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set Fabric port configuration
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    FabricPort::SetConfig(
        const config_t* pConfig                         ///< [in] Contains new configuration of the Fabric Port.
        )
    {
        auto result = static_cast<result_t>( ::zesFabricPortSetConfig(
            reinterpret_cast<zes_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<const zes_fabric_port_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::FabricPort::SetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get Fabric port state - status (health/degraded/failed/disabled),
    ///        reasons for link degradation or instability, current rx/tx speed
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    FabricPort::GetState(
        state_t* pState                                 ///< [in,out] Will contain the current state of the Fabric Port
        )
    {
        auto result = static_cast<result_t>( ::zesFabricPortGetState(
            reinterpret_cast<zes_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<zes_fabric_port_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::FabricPort::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get Fabric port throughput
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    FabricPort::GetThroughput(
        throughput_t* pThroughput                       ///< [in,out] Will contain the Fabric port throughput counters.
        )
    {
        auto result = static_cast<result_t>( ::zesFabricPortGetThroughput(
            reinterpret_cast<zes_fabric_port_handle_t>( getHandle() ),
            reinterpret_cast<zes_fabric_port_throughput_t*>( pThroughput ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::FabricPort::GetThroughput" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region fan
#endif
    ///////////////////////////////////////////////////////////////////////////////
    Fan::Fan( 
        fan_handle_t handle,                            ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of fans
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EnumFans(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        Fan** ppFan                                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zes_fan_handle_t> hFan;
        hFan.resize( ( ppFan ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zesDeviceEnumFans(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            hFan.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumFans" );

        for( uint32_t i = 0; ( ppFan ) && ( i < *pCount ); ++i )
            ppFan[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppFan ) && ( i < *pCount ); ++i )
                ppFan[ i ] = new Fan( reinterpret_cast<fan_handle_t>( hFan[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppFan ) && ( i < *pCount ); ++i )
            {
                delete ppFan[ i ];
                ppFan[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumFans" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get fan properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Fan::GetProperties(
        properties_t* pProperties                       ///< [in,out] Will contain the properties of the fan.
        )
    {
        auto result = static_cast<result_t>( ::zesFanGetProperties(
            reinterpret_cast<zes_fan_handle_t>( getHandle() ),
            reinterpret_cast<zes_fan_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Fan::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get fan configurations and the current fan speed mode (default, fixed,
    ///        temp-speed table)
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Fan::GetConfig(
        config_t* pConfig                               ///< [in,out] Will contain the current configuration of the fan.
        )
    {
        auto result = static_cast<result_t>( ::zesFanGetConfig(
            reinterpret_cast<zes_fan_handle_t>( getHandle() ),
            reinterpret_cast<zes_fan_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Fan::GetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Configure the fan to run with hardware factory settings (set mode to
    ///        ::ZES_FAN_SPEED_MODE_DEFAULT)
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Fan::SetDefaultMode(
        void
        )
    {
        auto result = static_cast<result_t>( ::zesFanSetDefaultMode(
            reinterpret_cast<zes_fan_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Fan::SetDefaultMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Configure the fan to rotate at a fixed speed (set mode to
    ///        ::ZES_FAN_SPEED_MODE_FIXED)
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Fan::SetFixedSpeedMode(
        const speed_t* speed                            ///< [in] The fixed fan speed setting
        )
    {
        auto result = static_cast<result_t>( ::zesFanSetFixedSpeedMode(
            reinterpret_cast<zes_fan_handle_t>( getHandle() ),
            reinterpret_cast<const zes_fan_speed_t*>( speed ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Fan::SetFixedSpeedMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Configure the fan to adjust speed based on a temperature/speed table
    ///        (set mode to ::ZES_FAN_SPEED_MODE_TABLE)
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Fan::SetSpeedTableMode(
        const speed_table_t* speedTable                 ///< [in] A table containing temperature/speed pairs.
        )
    {
        auto result = static_cast<result_t>( ::zesFanSetSpeedTableMode(
            reinterpret_cast<zes_fan_handle_t>( getHandle() ),
            reinterpret_cast<const zes_fan_speed_table_t*>( speedTable ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Fan::SetSpeedTableMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current state of a fan - current mode and speed
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Fan::GetState(
        speed_units_t units,                            ///< [in] The units in which the fan speed should be returned.
        int32_t* pSpeed                                 ///< [in,out] Will contain the current speed of the fan in the units
                                                        ///< requested. A value of -1 indicates that the fan speed cannot be
                                                        ///< measured.
        )
    {
        auto result = static_cast<result_t>( ::zesFanGetState(
            reinterpret_cast<zes_fan_handle_t>( getHandle() ),
            static_cast<zes_fan_speed_units_t>( units ),
            pSpeed ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Fan::GetState" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region firmware
#endif
    ///////////////////////////////////////////////////////////////////////////////
    Firmware::Firmware( 
        firmware_handle_t handle,                       ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of firmwares
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EnumFirmwares(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        Firmware** ppFirmware                           ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zes_firmware_handle_t> hFirmware;
        hFirmware.resize( ( ppFirmware ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zesDeviceEnumFirmwares(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            hFirmware.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumFirmwares" );

        for( uint32_t i = 0; ( ppFirmware ) && ( i < *pCount ); ++i )
            ppFirmware[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppFirmware ) && ( i < *pCount ); ++i )
                ppFirmware[ i ] = new Firmware( reinterpret_cast<firmware_handle_t>( hFirmware[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppFirmware ) && ( i < *pCount ); ++i )
            {
                delete ppFirmware[ i ];
                ppFirmware[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumFirmwares" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get firmware properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Firmware::GetProperties(
        properties_t* pProperties                       ///< [in,out] Pointer to an array that will hold the properties of the
                                                        ///< firmware
        )
    {
        auto result = static_cast<result_t>( ::zesFirmwareGetProperties(
            reinterpret_cast<zes_firmware_handle_t>( getHandle() ),
            reinterpret_cast<zes_firmware_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Firmware::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Flash a new firmware image
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Firmware::Flash(
        void* pImage,                                   ///< [in] Image of the new firmware to flash.
        uint32_t size                                   ///< [in] Size of the flash image.
        )
    {
        auto result = static_cast<result_t>( ::zesFirmwareFlash(
            reinterpret_cast<zes_firmware_handle_t>( getHandle() ),
            pImage,
            size ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Firmware::Flash" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region frequency
#endif
    ///////////////////////////////////////////////////////////////////////////////
    Frequency::Frequency( 
        freq_handle_t handle,                           ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of frequency domains
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EnumFrequencyDomains(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        Frequency** ppFrequency                         ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zes_freq_handle_t> hFrequency;
        hFrequency.resize( ( ppFrequency ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zesDeviceEnumFrequencyDomains(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            hFrequency.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumFrequencyDomains" );

        for( uint32_t i = 0; ( ppFrequency ) && ( i < *pCount ); ++i )
            ppFrequency[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppFrequency ) && ( i < *pCount ); ++i )
                ppFrequency[ i ] = new Frequency( reinterpret_cast<freq_handle_t>( hFrequency[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppFrequency ) && ( i < *pCount ); ++i )
            {
                delete ppFrequency[ i ];
                ppFrequency[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumFrequencyDomains" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get frequency properties - available frequencies
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Frequency::GetProperties(
        freq_properties_t* pProperties                  ///< [in,out] The frequency properties for the specified domain.
        )
    {
        auto result = static_cast<result_t>( ::zesFrequencyGetProperties(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            reinterpret_cast<zes_freq_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get available non-overclocked hardware clock frequencies for the
    ///        frequency domain
    /// 
    /// @details
    ///     - The list of available frequencies is returned in order of slowest to
    ///       fastest.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Frequency::GetAvailableClocks(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of frequencies.
                                                        ///< If count is zero, then the driver will update the value with the total
                                                        ///< number of frequencies available.
                                                        ///< If count is non-zero, then driver will only retrieve that number of frequencies.
                                                        ///< If count is larger than the number of frequencies available, then the
                                                        ///< driver will update the value with the correct number of frequencies available.
        double* phFrequency                             ///< [in,out][optional][range(0, *pCount)] array of frequencies in units of
                                                        ///< MHz and sorted from slowest to fastest
        )
    {
        auto result = static_cast<result_t>( ::zesFrequencyGetAvailableClocks(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            pCount,
            phFrequency ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::GetAvailableClocks" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current frequency limits
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Frequency::GetRange(
        freq_range_t* pLimits                           ///< [in,out] The range between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto result = static_cast<result_t>( ::zesFrequencyGetRange(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            reinterpret_cast<zes_freq_range_t*>( pLimits ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::GetRange" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set frequency range between which the hardware can operate.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Frequency::SetRange(
        const freq_range_t* pLimits                     ///< [in] The limits between which the hardware can operate for the
                                                        ///< specified domain.
        )
    {
        auto result = static_cast<result_t>( ::zesFrequencySetRange(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            reinterpret_cast<const zes_freq_range_t*>( pLimits ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::SetRange" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current frequency state - frequency request, actual frequency, TDP
    ///        limits
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Frequency::GetState(
        freq_state_t* pState                            ///< [in,out] Frequency state for the specified domain.
        )
    {
        auto result = static_cast<result_t>( ::zesFrequencyGetState(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            reinterpret_cast<zes_freq_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get frequency throttle time
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Frequency::GetThrottleTime(
        freq_throttle_time_t* pThrottleTime             ///< [in,out] Will contain a snapshot of the throttle time counters for the
                                                        ///< specified domain.
        )
    {
        auto result = static_cast<result_t>( ::zesFrequencyGetThrottleTime(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            reinterpret_cast<zes_freq_throttle_time_t*>( pThrottleTime ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::GetThrottleTime" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the overclocking capabilities.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Frequency::OcGetCapabilities(
        oc_capabilities_t* pOcCapabilities              ///< [in,out] Pointer to the capabilities structure
                                                        ///< ::zes_oc_capabilities_t.
        )
    {
        auto result = static_cast<result_t>( ::zesFrequencyOcGetCapabilities(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            reinterpret_cast<zes_oc_capabilities_t*>( pOcCapabilities ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::OcGetCapabilities" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the current overclocking frequency target, if extended moded is
    ///        supported, will returned in 1 Mhz granularity.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - double: Overclocking Frequency in MHz, if extended moded is supported, will returned in 1 Mhz granularity, else, in multiples of 50 Mhz. This cannot be greater than ::zes_oc_capabilities_t.maxOcFrequency.
    /// 
    /// @throws result_t
    double ZE_APICALL
    Frequency::OcGetFrequencyTarget(
        void
        )
    {
        double currentOcFrequency;

        auto result = static_cast<result_t>( ::zesFrequencyOcGetFrequencyTarget(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            &currentOcFrequency ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::OcGetFrequencyTarget" );

        return currentOcFrequency;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the current overclocking frequency target, if extended moded is
    ///        supported, can be set in 1 Mhz granularity.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Frequency::OcSetFrequencyTarget(
        double CurrentOcFrequency                       ///< [in] Overclocking Frequency in MHz, if extended moded is supported, it
                                                        ///< could be set in 1 Mhz granularity, else, in multiples of 50 Mhz. This
                                                        ///< cannot be greater than ::zes_oc_capabilities_t.maxOcFrequency.
        )
    {
        auto result = static_cast<result_t>( ::zesFrequencyOcSetFrequencyTarget(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            CurrentOcFrequency ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::OcSetFrequencyTarget" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the current overclocking voltage settings.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - double: Overclock voltage in Volts. This cannot be greater than ::zes_oc_capabilities_t.maxOcVoltage.
    ///     - double: This voltage offset is applied to all points on the voltage/frequency curve, include the new overclock voltageTarget. It can be in the range (::zes_oc_capabilities_t.minOcVoltageOffset, ::zes_oc_capabilities_t.maxOcVoltageOffset).
    /// 
    /// @throws result_t
    std::tuple<double, double> ZE_APICALL
    Frequency::OcGetVoltageTarget(
        void
        )
    {
        double currentVoltageTarget;

        double currentVoltageOffset;

        auto result = static_cast<result_t>( ::zesFrequencyOcGetVoltageTarget(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            &currentVoltageTarget,
            &currentVoltageOffset ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::OcGetVoltageTarget" );

        return std::make_tuple( currentVoltageTarget, currentVoltageOffset );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the current overclocking voltage settings.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Frequency::OcSetVoltageTarget(
        double CurrentVoltageTarget,                    ///< [in] Overclock voltage in Volts. This cannot be greater than
                                                        ///< ::zes_oc_capabilities_t.maxOcVoltage.
        double CurrentVoltageOffset                     ///< [in] This voltage offset is applied to all points on the
                                                        ///< voltage/frequency curve, include the new overclock voltageTarget. It
                                                        ///< can be in the range (::zes_oc_capabilities_t.minOcVoltageOffset,
                                                        ///< ::zes_oc_capabilities_t.maxOcVoltageOffset).
        )
    {
        auto result = static_cast<result_t>( ::zesFrequencyOcSetVoltageTarget(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            CurrentVoltageTarget,
            CurrentVoltageOffset ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::OcSetVoltageTarget" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the current overclocking mode.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Frequency::OcSetMode(
        oc_mode_t CurrentOcMode                         ///< [in] Current Overclocking Mode ::zes_oc_mode_t.
        )
    {
        auto result = static_cast<result_t>( ::zesFrequencyOcSetMode(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            static_cast<zes_oc_mode_t>( CurrentOcMode ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::OcSetMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the current overclocking mode.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - oc_mode_t: Current Overclocking Mode ::zes_oc_mode_t.
    /// 
    /// @throws result_t
    Frequency::oc_mode_t ZE_APICALL
    Frequency::OcGetMode(
        void
        )
    {
        zes_oc_mode_t currentOcMode;

        auto result = static_cast<result_t>( ::zesFrequencyOcGetMode(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            &currentOcMode ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::OcGetMode" );

        return *reinterpret_cast<oc_mode_t*>( &currentOcMode );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the maximum current limit setting.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Frequency::OcGetIccMax(
        double* pOcIccMax                               ///< [in,out] Will contain the maximum current limit in Amperes on
                                                        ///< successful return.
        )
    {
        auto result = static_cast<result_t>( ::zesFrequencyOcGetIccMax(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            pOcIccMax ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::OcGetIccMax" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Change the maximum current limit setting.
    /// 
    /// @details
    ///     - Setting ocIccMax to 0.0 will return the value to the factory default.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Frequency::OcSetIccMax(
        double ocIccMax                                 ///< [in] The new maximum current limit in Amperes.
        )
    {
        auto result = static_cast<result_t>( ::zesFrequencyOcSetIccMax(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            ocIccMax ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::OcSetIccMax" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the maximum temperature limit setting.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Frequency::OcGetTjMax(
        double* pOcTjMax                                ///< [in,out] Will contain the maximum temperature limit in degrees Celsius
                                                        ///< on successful return.
        )
    {
        auto result = static_cast<result_t>( ::zesFrequencyOcGetTjMax(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            pOcTjMax ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::OcGetTjMax" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Change the maximum temperature limit setting.
    /// 
    /// @details
    ///     - Setting ocTjMax to 0.0 will return the value to the factory default.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Frequency::OcSetTjMax(
        double ocTjMax                                  ///< [in] The new maximum temperature limit in degrees Celsius.
        )
    {
        auto result = static_cast<result_t>( ::zesFrequencyOcSetTjMax(
            reinterpret_cast<zes_freq_handle_t>( getHandle() ),
            ocTjMax ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Frequency::OcSetTjMax" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region led
#endif
    ///////////////////////////////////////////////////////////////////////////////
    Led::Led( 
        led_handle_t handle,                            ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of LEDs
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EnumLeds(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        Led** ppLed                                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zes_led_handle_t> hLed;
        hLed.resize( ( ppLed ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zesDeviceEnumLeds(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            hLed.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumLeds" );

        for( uint32_t i = 0; ( ppLed ) && ( i < *pCount ); ++i )
            ppLed[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppLed ) && ( i < *pCount ); ++i )
                ppLed[ i ] = new Led( reinterpret_cast<led_handle_t>( hLed[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppLed ) && ( i < *pCount ); ++i )
            {
                delete ppLed[ i ];
                ppLed[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumLeds" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get LED properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Led::GetProperties(
        properties_t* pProperties                       ///< [in,out] Will contain the properties of the LED.
        )
    {
        auto result = static_cast<result_t>( ::zesLedGetProperties(
            reinterpret_cast<zes_led_handle_t>( getHandle() ),
            reinterpret_cast<zes_led_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Led::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current state of a LED - on/off, color
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Led::GetState(
        state_t* pState                                 ///< [in,out] Will contain the current state of the LED.
        )
    {
        auto result = static_cast<result_t>( ::zesLedGetState(
            reinterpret_cast<zes_led_handle_t>( getHandle() ),
            reinterpret_cast<zes_led_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Led::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Turn the LED on/off
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Led::SetState(
        ze::bool_t enable                               ///< [in] Set to TRUE to turn the LED on, FALSE to turn off.
        )
    {
        auto result = static_cast<result_t>( ::zesLedSetState(
            reinterpret_cast<zes_led_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( enable ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Led::SetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the color of the LED
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Led::SetColor(
        const color_t* pColor                           ///< [in] New color of the LED.
        )
    {
        auto result = static_cast<result_t>( ::zesLedSetColor(
            reinterpret_cast<zes_led_handle_t>( getHandle() ),
            reinterpret_cast<const zes_led_color_t*>( pColor ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Led::SetColor" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region memory
#endif
    ///////////////////////////////////////////////////////////////////////////////
    Memory::Memory( 
        mem_handle_t handle,                            ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of memory modules
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EnumMemoryModules(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        Memory** ppMemory                               ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zes_mem_handle_t> hMemory;
        hMemory.resize( ( ppMemory ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zesDeviceEnumMemoryModules(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            hMemory.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumMemoryModules" );

        for( uint32_t i = 0; ( ppMemory ) && ( i < *pCount ); ++i )
            ppMemory[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppMemory ) && ( i < *pCount ); ++i )
                ppMemory[ i ] = new Memory( reinterpret_cast<mem_handle_t>( hMemory[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppMemory ) && ( i < *pCount ); ++i )
            {
                delete ppMemory[ i ];
                ppMemory[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumMemoryModules" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get memory properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Memory::GetProperties(
        mem_properties_t* pProperties                   ///< [in,out] Will contain memory properties.
        )
    {
        auto result = static_cast<result_t>( ::zesMemoryGetProperties(
            reinterpret_cast<zes_mem_handle_t>( getHandle() ),
            reinterpret_cast<zes_mem_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Memory::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get memory state - health, allocated
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Memory::GetState(
        mem_state_t* pState                             ///< [in,out] Will contain the current health and allocated memory.
        )
    {
        auto result = static_cast<result_t>( ::zesMemoryGetState(
            reinterpret_cast<zes_mem_handle_t>( getHandle() ),
            reinterpret_cast<zes_mem_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Memory::GetState" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get memory bandwidth
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Memory::GetBandwidth(
        mem_bandwidth_t* pBandwidth                     ///< [in,out] Will contain the current health, free memory, total memory
                                                        ///< size.
        )
    {
        auto result = static_cast<result_t>( ::zesMemoryGetBandwidth(
            reinterpret_cast<zes_mem_handle_t>( getHandle() ),
            reinterpret_cast<zes_mem_bandwidth_t*>( pBandwidth ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Memory::GetBandwidth" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region performance
#endif
    ///////////////////////////////////////////////////////////////////////////////
    PerformanceFactor::PerformanceFactor( 
        perf_handle_t handle,                           ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handles to accelerator domains whose performance can be optimized
    ///        via a Performance Factor
    /// 
    /// @details
    ///     - A Performance Factor should be tuned for each workload.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EnumPerformanceFactorDomains(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        PerformanceFactor** ppPerf                      ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zes_perf_handle_t> hPerf;
        hPerf.resize( ( ppPerf ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zesDeviceEnumPerformanceFactorDomains(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            hPerf.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumPerformanceFactorDomains" );

        for( uint32_t i = 0; ( ppPerf ) && ( i < *pCount ); ++i )
            ppPerf[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppPerf ) && ( i < *pCount ); ++i )
                ppPerf[ i ] = new PerformanceFactor( reinterpret_cast<perf_handle_t>( hPerf[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppPerf ) && ( i < *pCount ); ++i )
            {
                delete ppPerf[ i ];
                ppPerf[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumPerformanceFactorDomains" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get properties about a Performance Factor domain
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    PerformanceFactor::GetProperties(
        perf_properties_t* pProperties                  ///< [in,out] Will contain information about the specified Performance
                                                        ///< Factor domain.
        )
    {
        auto result = static_cast<result_t>( ::zesPerformanceFactorGetProperties(
            reinterpret_cast<zes_perf_handle_t>( getHandle() ),
            reinterpret_cast<zes_perf_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::PerformanceFactor::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current Performance Factor for a given domain
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    PerformanceFactor::GetConfig(
        double* pFactor                                 ///< [in,out] Will contain the actual Performance Factor being used by the
                                                        ///< hardware (may not be the same as the requested Performance Factor).
        )
    {
        auto result = static_cast<result_t>( ::zesPerformanceFactorGetConfig(
            reinterpret_cast<zes_perf_handle_t>( getHandle() ),
            pFactor ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::PerformanceFactor::GetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Change the performance factor for a domain
    /// 
    /// @details
    ///     - The Performance Factor is a number between 0 and 100.
    ///     - A Performance Factor is a hint to the hardware. Depending on the
    ///       hardware, the request may not be granted. Follow up this function with
    ///       a call to ::zesPerformanceFactorGetConfig() to determine the actual
    ///       factor being used by the hardware.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    PerformanceFactor::SetConfig(
        double factor                                   ///< [in] The new Performance Factor.
        )
    {
        auto result = static_cast<result_t>( ::zesPerformanceFactorSetConfig(
            reinterpret_cast<zes_perf_handle_t>( getHandle() ),
            factor ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::PerformanceFactor::SetConfig" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region power
#endif
    ///////////////////////////////////////////////////////////////////////////////
    Power::Power( 
        pwr_handle_t handle,                            ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of power domains
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EnumPowerDomains(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        Power** ppPower                                 ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zes_pwr_handle_t> hPower;
        hPower.resize( ( ppPower ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zesDeviceEnumPowerDomains(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            hPower.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumPowerDomains" );

        for( uint32_t i = 0; ( ppPower ) && ( i < *pCount ); ++i )
            ppPower[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppPower ) && ( i < *pCount ); ++i )
                ppPower[ i ] = new Power( reinterpret_cast<pwr_handle_t>( hPower[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppPower ) && ( i < *pCount ); ++i )
            {
                delete ppPower[ i ];
                ppPower[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumPowerDomains" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get properties related to a power domain
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Power::GetProperties(
        properties_t* pProperties                       ///< [in,out] Structure that will contain property data.
        )
    {
        auto result = static_cast<result_t>( ::zesPowerGetProperties(
            reinterpret_cast<zes_pwr_handle_t>( getHandle() ),
            reinterpret_cast<zes_power_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Power::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get energy counter
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Power::GetEnergyCounter(
        energy_counter_t* pEnergy                       ///< [in,out] Will contain the latest snapshot of the energy counter and
                                                        ///< timestamp when the last counter value was measured.
        )
    {
        auto result = static_cast<result_t>( ::zesPowerGetEnergyCounter(
            reinterpret_cast<zes_pwr_handle_t>( getHandle() ),
            reinterpret_cast<zes_power_energy_counter_t*>( pEnergy ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Power::GetEnergyCounter" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get power limits
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Power::GetLimits(
        sustained_limit_t* pSustained,                  ///< [in,out][optional] The sustained power limit. If this is null, the
                                                        ///< current sustained power limits will not be returned.
        burst_limit_t* pBurst,                          ///< [in,out][optional] The burst power limit. If this is null, the current
                                                        ///< peak power limits will not be returned.
        peak_limit_t* pPeak                             ///< [in,out][optional] The peak power limit. If this is null, the peak
                                                        ///< power limits will not be returned.
        )
    {
        auto result = static_cast<result_t>( ::zesPowerGetLimits(
            reinterpret_cast<zes_pwr_handle_t>( getHandle() ),
            reinterpret_cast<zes_power_sustained_limit_t*>( pSustained ),
            reinterpret_cast<zes_power_burst_limit_t*>( pBurst ),
            reinterpret_cast<zes_power_peak_limit_t*>( pPeak ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Power::GetLimits" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set power limits
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Power::SetLimits(
        const sustained_limit_t* pSustained,            ///< [in][optional] The sustained power limit. If this is null, no changes
                                                        ///< will be made to the sustained power limits.
        const burst_limit_t* pBurst,                    ///< [in][optional] The burst power limit. If this is null, no changes will
                                                        ///< be made to the burst power limits.
        const peak_limit_t* pPeak                       ///< [in][optional] The peak power limit. If this is null, no changes will
                                                        ///< be made to the peak power limits.
        )
    {
        auto result = static_cast<result_t>( ::zesPowerSetLimits(
            reinterpret_cast<zes_pwr_handle_t>( getHandle() ),
            reinterpret_cast<const zes_power_sustained_limit_t*>( pSustained ),
            reinterpret_cast<const zes_power_burst_limit_t*>( pBurst ),
            reinterpret_cast<const zes_power_peak_limit_t*>( pPeak ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Power::SetLimits" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get energy threshold
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Power::GetEnergyThreshold(
        energy_threshold_t* pThreshold                  ///< [in,out] Returns information about the energy threshold setting -
                                                        ///< enabled/energy threshold/process ID.
        )
    {
        auto result = static_cast<result_t>( ::zesPowerGetEnergyThreshold(
            reinterpret_cast<zes_pwr_handle_t>( getHandle() ),
            reinterpret_cast<zes_energy_threshold_t*>( pThreshold ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Power::GetEnergyThreshold" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set energy threshold
    /// 
    /// @details
    ///     - An event ::ZES_EVENT_TYPE_FLAG_ENERGY_THRESHOLD_CROSSED will be
    ///       generated when the delta energy consumed starting from this call
    ///       exceeds the specified threshold. Use the function
    ///       ::zesDeviceEventRegister() to start receiving the event.
    ///     - Only one running process can control the energy threshold at a given
    ///       time. If another process attempts to change the energy threshold, the
    ///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
    ///       ::zesPowerGetEnergyThreshold() to determine the process ID currently
    ///       controlling this setting.
    ///     - Calling this function will remove any pending energy thresholds and
    ///       start counting from the time of this call.
    ///     - Once the energy threshold has been reached and the event generated,
    ///       the threshold is automatically removed. It is up to the application to
    ///       request a new threshold.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Power::SetEnergyThreshold(
        double threshold                                ///< [in] The energy threshold to be set in joules.
        )
    {
        auto result = static_cast<result_t>( ::zesPowerSetEnergyThreshold(
            reinterpret_cast<zes_pwr_handle_t>( getHandle() ),
            threshold ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Power::SetEnergyThreshold" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region psu
#endif
    ///////////////////////////////////////////////////////////////////////////////
    Psu::Psu( 
        psu_handle_t handle,                            ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of power supplies
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EnumPsus(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        Psu** ppPsu                                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zes_psu_handle_t> hPsu;
        hPsu.resize( ( ppPsu ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zesDeviceEnumPsus(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            hPsu.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumPsus" );

        for( uint32_t i = 0; ( ppPsu ) && ( i < *pCount ); ++i )
            ppPsu[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppPsu ) && ( i < *pCount ); ++i )
                ppPsu[ i ] = new Psu( reinterpret_cast<psu_handle_t>( hPsu[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppPsu ) && ( i < *pCount ); ++i )
            {
                delete ppPsu[ i ];
                ppPsu[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumPsus" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get power supply properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Psu::GetProperties(
        properties_t* pProperties                       ///< [in,out] Will contain the properties of the power supply.
        )
    {
        auto result = static_cast<result_t>( ::zesPsuGetProperties(
            reinterpret_cast<zes_psu_handle_t>( getHandle() ),
            reinterpret_cast<zes_psu_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Psu::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current power supply state
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Psu::GetState(
        state_t* pState                                 ///< [in,out] Will contain the current state of the power supply.
        )
    {
        auto result = static_cast<result_t>( ::zesPsuGetState(
            reinterpret_cast<zes_psu_handle_t>( getHandle() ),
            reinterpret_cast<zes_psu_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Psu::GetState" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region ras
#endif
    ///////////////////////////////////////////////////////////////////////////////
    Ras::Ras( 
        ras_handle_t handle,                            ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of all RAS error sets on a device
    /// 
    /// @details
    ///     - A RAS error set is a collection of RAS error counters of a given type
    ///       (correctable/uncorrectable) from hardware blocks contained within a
    ///       sub-device or within the device.
    ///     - A device without sub-devices will typically return two handles, one
    ///       for correctable errors sets and one for uncorrectable error sets.
    ///     - A device with sub-devices will return RAS error sets for each
    ///       sub-device and possibly RAS error sets for hardware blocks outside the
    ///       sub-devices.
    ///     - If the function completes successfully but pCount is set to 0, RAS
    ///       features are not available/enabled on this device.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EnumRasErrorSets(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        Ras** ppRas                                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zes_ras_handle_t> hRas;
        hRas.resize( ( ppRas ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zesDeviceEnumRasErrorSets(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            hRas.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumRasErrorSets" );

        for( uint32_t i = 0; ( ppRas ) && ( i < *pCount ); ++i )
            ppRas[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppRas ) && ( i < *pCount ); ++i )
                ppRas[ i ] = new Ras( reinterpret_cast<ras_handle_t>( hRas[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppRas ) && ( i < *pCount ); ++i )
            {
                delete ppRas[ i ];
                ppRas[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumRasErrorSets" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get RAS properties of a given RAS error set - this enables discovery
    ///        of the type of RAS error set (correctable/uncorrectable) and if
    ///        located on a sub-device
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Ras::GetProperties(
        properties_t* pProperties                       ///< [in,out] Structure describing RAS properties
        )
    {
        auto result = static_cast<result_t>( ::zesRasGetProperties(
            reinterpret_cast<zes_ras_handle_t>( getHandle() ),
            reinterpret_cast<zes_ras_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Ras::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get RAS error thresholds that control when RAS events are generated
    /// 
    /// @details
    ///     - The driver maintains counters for all RAS error sets and error
    ///       categories. Events are generated when errors occur. The configuration
    ///       enables setting thresholds to limit when events are sent.
    ///     - When a particular RAS correctable error counter exceeds the configured
    ///       threshold, the event ::ZES_EVENT_TYPE_FLAG_RAS_CORRECTABLE_ERRORS will
    ///       be triggered.
    ///     - When a particular RAS uncorrectable error counter exceeds the
    ///       configured threshold, the event
    ///       ::ZES_EVENT_TYPE_FLAG_RAS_UNCORRECTABLE_ERRORS will be triggered.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Ras::GetConfig(
        config_t* pConfig                               ///< [in,out] Will be populed with the current RAS configuration -
                                                        ///< thresholds used to trigger events
        )
    {
        auto result = static_cast<result_t>( ::zesRasGetConfig(
            reinterpret_cast<zes_ras_handle_t>( getHandle() ),
            reinterpret_cast<zes_ras_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Ras::GetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set RAS error thresholds that control when RAS events are generated
    /// 
    /// @details
    ///     - The driver maintains counters for all RAS error sets and error
    ///       categories. Events are generated when errors occur. The configuration
    ///       enables setting thresholds to limit when events are sent.
    ///     - When a particular RAS correctable error counter exceeds the specified
    ///       threshold, the event ::ZES_EVENT_TYPE_FLAG_RAS_CORRECTABLE_ERRORS will
    ///       be generated.
    ///     - When a particular RAS uncorrectable error counter exceeds the
    ///       specified threshold, the event
    ///       ::ZES_EVENT_TYPE_FLAG_RAS_UNCORRECTABLE_ERRORS will be generated.
    ///     - Call ::zesRasGetState() and set the clear flag to true to restart
    ///       event generation once counters have exceeded thresholds.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Ras::SetConfig(
        const config_t* pConfig                         ///< [in] Change the RAS configuration - thresholds used to trigger events
        )
    {
        auto result = static_cast<result_t>( ::zesRasSetConfig(
            reinterpret_cast<zes_ras_handle_t>( getHandle() ),
            reinterpret_cast<const zes_ras_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Ras::SetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the current value of RAS error counters for a particular error set
    /// 
    /// @details
    ///     - Clearing errors will affect other threads/applications - the counter
    ///       values will start from zero.
    ///     - Clearing errors requires write permissions.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Ras::GetState(
        ze::bool_t clear,                               ///< [in] Set to 1 to clear the counters of this type
        state_t* pState                                 ///< [in,out] Breakdown of where errors have occurred
        )
    {
        auto result = static_cast<result_t>( ::zesRasGetState(
            reinterpret_cast<zes_ras_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( clear ),
            reinterpret_cast<zes_ras_state_t*>( pState ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Ras::GetState" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region scheduler
#endif
    ///////////////////////////////////////////////////////////////////////////////
    Scheduler::Scheduler( 
        sched_handle_t handle,                          ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle to a scheduler component
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EnumSchedulers(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        Scheduler** ppScheduler                         ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zes_sched_handle_t> hScheduler;
        hScheduler.resize( ( ppScheduler ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zesDeviceEnumSchedulers(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            hScheduler.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumSchedulers" );

        for( uint32_t i = 0; ( ppScheduler ) && ( i < *pCount ); ++i )
            ppScheduler[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppScheduler ) && ( i < *pCount ); ++i )
                ppScheduler[ i ] = new Scheduler( reinterpret_cast<sched_handle_t>( hScheduler[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppScheduler ) && ( i < *pCount ); ++i )
            {
                delete ppScheduler[ i ];
                ppScheduler[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumSchedulers" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get properties related to a scheduler component
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Scheduler::GetProperties(
        sched_properties_t* pProperties                 ///< [in,out] Structure that will contain property data.
        )
    {
        auto result = static_cast<result_t>( ::zesSchedulerGetProperties(
            reinterpret_cast<zes_sched_handle_t>( getHandle() ),
            reinterpret_cast<zes_sched_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Scheduler::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get current scheduling mode in effect on a scheduler component.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Scheduler::GetCurrentMode(
        Device::sched_mode_t* pMode                     ///< [in,out] Will contain the current scheduler mode.
        )
    {
        auto result = static_cast<result_t>( ::zesSchedulerGetCurrentMode(
            reinterpret_cast<zes_sched_handle_t>( getHandle() ),
            reinterpret_cast<zes_sched_mode_t*>( pMode ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Scheduler::GetCurrentMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get scheduler config for mode ::ZES_SCHED_MODE_TIMEOUT
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Scheduler::GetTimeoutModeProperties(
        ze::bool_t getDefaults,                         ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        Device::sched_timeout_properties_t* pConfig     ///< [in,out] Will contain the current parameters for this mode.
        )
    {
        auto result = static_cast<result_t>( ::zesSchedulerGetTimeoutModeProperties(
            reinterpret_cast<zes_sched_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( getDefaults ),
            reinterpret_cast<zes_sched_timeout_properties_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Scheduler::GetTimeoutModeProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get scheduler config for mode ::ZES_SCHED_MODE_TIMESLICE
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Scheduler::GetTimesliceModeProperties(
        ze::bool_t getDefaults,                         ///< [in] If TRUE, the driver will return the system default properties for
                                                        ///< this mode, otherwise it will return the current properties.
        Device::sched_timeslice_properties_t* pConfig   ///< [in,out] Will contain the current parameters for this mode.
        )
    {
        auto result = static_cast<result_t>( ::zesSchedulerGetTimesliceModeProperties(
            reinterpret_cast<zes_sched_handle_t>( getHandle() ),
            static_cast<ze_bool_t>( getDefaults ),
            reinterpret_cast<zes_sched_timeslice_properties_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Scheduler::GetTimesliceModeProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Change scheduler mode to ::ZES_SCHED_MODE_TIMEOUT or update scheduler
    ///        mode parameters if already running in this mode.
    /// 
    /// @details
    ///     - This mode is optimized for multiple applications or contexts
    ///       submitting work to the hardware. When higher priority work arrives,
    ///       the scheduler attempts to pause the current executing work within some
    ///       timeout interval, then submits the other work.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Scheduler::SetTimeoutMode(
        Device::sched_timeout_properties_t* pProperties,///< [in] The properties to use when configurating this mode.
        ze::bool_t* pNeedReload                         ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto result = static_cast<result_t>( ::zesSchedulerSetTimeoutMode(
            reinterpret_cast<zes_sched_handle_t>( getHandle() ),
            reinterpret_cast<zes_sched_timeout_properties_t*>( pProperties ),
            reinterpret_cast<ze_bool_t*>( pNeedReload ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Scheduler::SetTimeoutMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Change scheduler mode to ::ZES_SCHED_MODE_TIMESLICE or update
    ///        scheduler mode parameters if already running in this mode.
    /// 
    /// @details
    ///     - This mode is optimized to provide fair sharing of hardware execution
    ///       time between multiple contexts submitting work to the hardware
    ///       concurrently.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Scheduler::SetTimesliceMode(
        Device::sched_timeslice_properties_t* pProperties,  ///< [in] The properties to use when configurating this mode.
        ze::bool_t* pNeedReload                         ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto result = static_cast<result_t>( ::zesSchedulerSetTimesliceMode(
            reinterpret_cast<zes_sched_handle_t>( getHandle() ),
            reinterpret_cast<zes_sched_timeslice_properties_t*>( pProperties ),
            reinterpret_cast<ze_bool_t*>( pNeedReload ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Scheduler::SetTimesliceMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Change scheduler mode to ::ZES_SCHED_MODE_EXCLUSIVE
    /// 
    /// @details
    ///     - This mode is optimized for single application/context use-cases. It
    ///       permits a context to run indefinitely on the hardware without being
    ///       preempted or terminated. All pending work for other contexts must wait
    ///       until the running context completes with no further submitted work.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Scheduler::SetExclusiveMode(
        ze::bool_t* pNeedReload                         ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto result = static_cast<result_t>( ::zesSchedulerSetExclusiveMode(
            reinterpret_cast<zes_sched_handle_t>( getHandle() ),
            reinterpret_cast<ze_bool_t*>( pNeedReload ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Scheduler::SetExclusiveMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Change scheduler mode to ::ZES_SCHED_MODE_COMPUTE_UNIT_DEBUG
    /// 
    /// @details
    ///     - This is a special mode that must ben enabled when debugging an
    ///       application that uses this device e.g. using the Level0 Debug API.
    ///     - It ensures that only one command queue can execute work on the
    ///       hardware at a given time. Work is permitted to run as long as needed
    ///       without enforcing any scheduler fairness policies.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Scheduler::SetComputeUnitDebugMode(
        ze::bool_t* pNeedReload                         ///< [in,out] Will be set to TRUE if a device driver reload is needed to
                                                        ///< apply the new scheduler mode.
        )
    {
        auto result = static_cast<result_t>( ::zesSchedulerSetComputeUnitDebugMode(
            reinterpret_cast<zes_sched_handle_t>( getHandle() ),
            reinterpret_cast<ze_bool_t*>( pNeedReload ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Scheduler::SetComputeUnitDebugMode" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region standby
#endif
    ///////////////////////////////////////////////////////////////////////////////
    Standby::Standby( 
        standby_handle_t handle,                        ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of standby controls
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EnumStandbyDomains(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        Standby** ppStandby                             ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zes_standby_handle_t> hStandby;
        hStandby.resize( ( ppStandby ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zesDeviceEnumStandbyDomains(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            hStandby.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumStandbyDomains" );

        for( uint32_t i = 0; ( ppStandby ) && ( i < *pCount ); ++i )
            ppStandby[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppStandby ) && ( i < *pCount ); ++i )
                ppStandby[ i ] = new Standby( reinterpret_cast<standby_handle_t>( hStandby[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppStandby ) && ( i < *pCount ); ++i )
            {
                delete ppStandby[ i ];
                ppStandby[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumStandbyDomains" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get standby hardware component properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Standby::GetProperties(
        properties_t* pProperties                       ///< [in,out] Will contain the standby hardware properties.
        )
    {
        auto result = static_cast<result_t>( ::zesStandbyGetProperties(
            reinterpret_cast<zes_standby_handle_t>( getHandle() ),
            reinterpret_cast<zes_standby_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Standby::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the current standby promotion mode
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Standby::GetMode(
        promo_mode_t* pMode                             ///< [in,out] Will contain the current standby mode.
        )
    {
        auto result = static_cast<result_t>( ::zesStandbyGetMode(
            reinterpret_cast<zes_standby_handle_t>( getHandle() ),
            reinterpret_cast<zes_standby_promo_mode_t*>( pMode ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Standby::GetMode" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set standby promotion mode
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Standby::SetMode(
        promo_mode_t mode                               ///< [in] New standby mode.
        )
    {
        auto result = static_cast<result_t>( ::zesStandbySetMode(
            reinterpret_cast<zes_standby_handle_t>( getHandle() ),
            static_cast<zes_standby_promo_mode_t>( mode ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Standby::SetMode" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region temperature
#endif
    ///////////////////////////////////////////////////////////////////////////////
    Temperature::Temperature( 
        temp_handle_t handle,                           ///< [in] handle of Sysman object
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_handle( handle ),
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get handle of temperature sensors
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Device::EnumTemperatureSensors(
        uint32_t* pCount,                               ///< [in,out] pointer to the number of components of this type.
                                                        ///< if count is zero, then the driver will update the value with the total
                                                        ///< number of components of this type.
                                                        ///< if count is non-zero, then driver will only retrieve that number of components.
                                                        ///< if count is larger than the number of components available, then the
                                                        ///< driver will update the value with the correct number of components
                                                        ///< that are returned.
        Temperature** ppTemperature                     ///< [in,out][optional][range(0, *pCount)] array of pointer to components
                                                        ///< of this type
        )
    {
        thread_local std::vector<zes_temp_handle_t> hTemperature;
        hTemperature.resize( ( ppTemperature ) ? *pCount : 0 );

        auto result = static_cast<result_t>( ::zesDeviceEnumTemperatureSensors(
            reinterpret_cast<zes_device_handle_t>( getHandle() ),
            pCount,
            hTemperature.data() ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumTemperatureSensors" );

        for( uint32_t i = 0; ( ppTemperature ) && ( i < *pCount ); ++i )
            ppTemperature[ i ] = nullptr;

        try
        {
            for( uint32_t i = 0; ( ppTemperature ) && ( i < *pCount ); ++i )
                ppTemperature[ i ] = new Temperature( reinterpret_cast<temp_handle_t>( hTemperature[ i ] ), this );
        }
        catch( std::bad_alloc& )
        {
            for( uint32_t i = 0; ( ppTemperature ) && ( i < *pCount ); ++i )
            {
                delete ppTemperature[ i ];
                ppTemperature[ i ] = nullptr;
            }

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, ZE_STRING(__LINE__), "zes::Device::EnumTemperatureSensors" );
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get temperature sensor properties
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Temperature::GetProperties(
        temp_properties_t* pProperties                  ///< [in,out] Will contain the temperature sensor properties.
        )
    {
        auto result = static_cast<result_t>( ::zesTemperatureGetProperties(
            reinterpret_cast<zes_temp_handle_t>( getHandle() ),
            reinterpret_cast<zes_temp_properties_t*>( pProperties ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Temperature::GetProperties" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get temperature configuration for this sensor - which events are
    ///        triggered and the trigger conditions
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Temperature::GetConfig(
        temp_config_t* pConfig                          ///< [in,out] Returns current configuration.
        )
    {
        auto result = static_cast<result_t>( ::zesTemperatureGetConfig(
            reinterpret_cast<zes_temp_handle_t>( getHandle() ),
            reinterpret_cast<zes_temp_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Temperature::GetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set temperature configuration for this sensor - indicates which events
    ///        are triggered and the trigger conditions
    /// 
    /// @details
    ///     - Events ::ZES_EVENT_TYPE_FLAG_TEMP_CRITICAL will be triggered when
    ///       temperature reaches the critical range. Use the function
    ///       ::zesDeviceEventRegister() to start receiving this event.
    ///     - Events ::ZES_EVENT_TYPE_FLAG_TEMP_THRESHOLD1 and
    ///       ::ZES_EVENT_TYPE_FLAG_TEMP_THRESHOLD2 will be generated when
    ///       temperature cross the thresholds set using this function. Use the
    ///       function ::zesDeviceEventRegister() to start receiving these events.
    ///     - Only one running process can set the temperature configuration at a
    ///       time. If another process attempts to change the configuration, the
    ///       error ::ZE_RESULT_ERROR_NOT_AVAILABLE will be returned. The function
    ///       ::zesTemperatureGetConfig() will return the process ID currently
    ///       controlling these settings.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Temperature::SetConfig(
        const temp_config_t* pConfig                    ///< [in] New configuration.
        )
    {
        auto result = static_cast<result_t>( ::zesTemperatureSetConfig(
            reinterpret_cast<zes_temp_handle_t>( getHandle() ),
            reinterpret_cast<const zes_temp_config_t*>( pConfig ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Temperature::SetConfig" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the temperature from a specified sensor
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void ZE_APICALL
    Temperature::GetState(
        double* pTemperature                            ///< [in,out] Will contain the temperature read from the specified sensor
                                                        ///< in degrees Celsius.
        )
    {
        auto result = static_cast<result_t>( ::zesTemperatureGetState(
            reinterpret_cast<zes_temp_handle_t>( getHandle() ),
            pTemperature ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, ZE_STRING(__LINE__), "zes::Temperature::GetState" );
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
} // namespace zes

namespace zes
{
#if !defined(__GNUC__)
#pragma region common
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts structure_type_t to std::string
    std::string to_string( const structure_type_t val )
    {
        std::string str;

        switch( val )
        {
        case structure_type_t::DEVICE_PROPERTIES:
            str = "structure_type_t::DEVICE_PROPERTIES";
            break;

        case structure_type_t::PCI_PROPERTIES:
            str = "structure_type_t::PCI_PROPERTIES";
            break;

        case structure_type_t::PCI_BAR_PROPERTIES:
            str = "structure_type_t::PCI_BAR_PROPERTIES";
            break;

        case structure_type_t::DIAG_PROPERTIES:
            str = "structure_type_t::DIAG_PROPERTIES";
            break;

        case structure_type_t::ENGINE_PROPERTIES:
            str = "structure_type_t::ENGINE_PROPERTIES";
            break;

        case structure_type_t::FABRIC_PORT_PROPERTIES:
            str = "structure_type_t::FABRIC_PORT_PROPERTIES";
            break;

        case structure_type_t::FAN_PROPERTIES:
            str = "structure_type_t::FAN_PROPERTIES";
            break;

        case structure_type_t::FIRMWARE_PROPERTIES:
            str = "structure_type_t::FIRMWARE_PROPERTIES";
            break;

        case structure_type_t::FREQ_PROPERTIES:
            str = "structure_type_t::FREQ_PROPERTIES";
            break;

        case structure_type_t::LED_PROPERTIES:
            str = "structure_type_t::LED_PROPERTIES";
            break;

        case structure_type_t::MEM_PROPERTIES:
            str = "structure_type_t::MEM_PROPERTIES";
            break;

        case structure_type_t::PERF_PROPERTIES:
            str = "structure_type_t::PERF_PROPERTIES";
            break;

        case structure_type_t::POWER_PROPERTIES:
            str = "structure_type_t::POWER_PROPERTIES";
            break;

        case structure_type_t::PSU_PROPERTIES:
            str = "structure_type_t::PSU_PROPERTIES";
            break;

        case structure_type_t::RAS_PROPERTIES:
            str = "structure_type_t::RAS_PROPERTIES";
            break;

        case structure_type_t::SCHED_PROPERTIES:
            str = "structure_type_t::SCHED_PROPERTIES";
            break;

        case structure_type_t::SCHED_TIMEOUT_PROPERTIES:
            str = "structure_type_t::SCHED_TIMEOUT_PROPERTIES";
            break;

        case structure_type_t::SCHED_TIMESLICE_PROPERTIES:
            str = "structure_type_t::SCHED_TIMESLICE_PROPERTIES";
            break;

        case structure_type_t::STANDBY_PROPERTIES:
            str = "structure_type_t::STANDBY_PROPERTIES";
            break;

        case structure_type_t::TEMP_PROPERTIES:
            str = "structure_type_t::TEMP_PROPERTIES";
            break;

        case structure_type_t::DEVICE_STATE:
            str = "structure_type_t::DEVICE_STATE";
            break;

        case structure_type_t::PROCESS_STATE:
            str = "structure_type_t::PROCESS_STATE";
            break;

        case structure_type_t::PCI_STATE:
            str = "structure_type_t::PCI_STATE";
            break;

        case structure_type_t::FABRIC_PORT_CONFIG:
            str = "structure_type_t::FABRIC_PORT_CONFIG";
            break;

        case structure_type_t::FABRIC_PORT_STATE:
            str = "structure_type_t::FABRIC_PORT_STATE";
            break;

        case structure_type_t::FAN_CONFIG:
            str = "structure_type_t::FAN_CONFIG";
            break;

        case structure_type_t::FREQ_STATE:
            str = "structure_type_t::FREQ_STATE";
            break;

        case structure_type_t::OC_CAPABILITIES:
            str = "structure_type_t::OC_CAPABILITIES";
            break;

        case structure_type_t::LED_STATE:
            str = "structure_type_t::LED_STATE";
            break;

        case structure_type_t::MEM_STATE:
            str = "structure_type_t::MEM_STATE";
            break;

        case structure_type_t::PSU_STATE:
            str = "structure_type_t::PSU_STATE";
            break;

        case structure_type_t::BASE_STATE:
            str = "structure_type_t::BASE_STATE";
            break;

        case structure_type_t::RAS_CONFIG:
            str = "structure_type_t::RAS_CONFIG";
            break;

        case structure_type_t::RAS_STATE:
            str = "structure_type_t::RAS_STATE";
            break;

        case structure_type_t::TEMP_CONFIG:
            str = "structure_type_t::TEMP_CONFIG";
            break;

        default:
            str = "structure_type_t::?";
            break;
        };

        return str;
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

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts base_state_t to std::string
    std::string to_string( const base_state_t val )
    {
        std::string str;
        
        str += "base_state_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "base_state_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts base_config_t to std::string
    std::string to_string( const base_config_t val )
    {
        std::string str;
        
        str += "base_config_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "base_config_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts base_capability_t to std::string
    std::string to_string( const base_capability_t val )
    {
        std::string str;
        
        str += "base_capability_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "base_capability_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region device
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::event_type_flags_t to std::string
    std::string to_string( const Driver::event_type_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Driver::EVENT_TYPE_FLAG_DEVICE_DETACH) & bits )
            str += "EVENT_TYPE_FLAG_DEVICE_DETACH | ";
        
        if( static_cast<uint32_t>(Driver::EVENT_TYPE_FLAG_DEVICE_ATTACH) & bits )
            str += "EVENT_TYPE_FLAG_DEVICE_ATTACH | ";
        
        if( static_cast<uint32_t>(Driver::EVENT_TYPE_FLAG_DEVICE_SLEEP_STATE_ENTER) & bits )
            str += "EVENT_TYPE_FLAG_DEVICE_SLEEP_STATE_ENTER | ";
        
        if( static_cast<uint32_t>(Driver::EVENT_TYPE_FLAG_DEVICE_SLEEP_STATE_EXIT) & bits )
            str += "EVENT_TYPE_FLAG_DEVICE_SLEEP_STATE_EXIT | ";
        
        if( static_cast<uint32_t>(Driver::EVENT_TYPE_FLAG_FREQ_THROTTLED) & bits )
            str += "EVENT_TYPE_FLAG_FREQ_THROTTLED | ";
        
        if( static_cast<uint32_t>(Driver::EVENT_TYPE_FLAG_ENERGY_THRESHOLD_CROSSED) & bits )
            str += "EVENT_TYPE_FLAG_ENERGY_THRESHOLD_CROSSED | ";
        
        if( static_cast<uint32_t>(Driver::EVENT_TYPE_FLAG_TEMP_CRITICAL) & bits )
            str += "EVENT_TYPE_FLAG_TEMP_CRITICAL | ";
        
        if( static_cast<uint32_t>(Driver::EVENT_TYPE_FLAG_TEMP_THRESHOLD1) & bits )
            str += "EVENT_TYPE_FLAG_TEMP_THRESHOLD1 | ";
        
        if( static_cast<uint32_t>(Driver::EVENT_TYPE_FLAG_TEMP_THRESHOLD2) & bits )
            str += "EVENT_TYPE_FLAG_TEMP_THRESHOLD2 | ";
        
        if( static_cast<uint32_t>(Driver::EVENT_TYPE_FLAG_MEM_HEALTH) & bits )
            str += "EVENT_TYPE_FLAG_MEM_HEALTH | ";
        
        if( static_cast<uint32_t>(Driver::EVENT_TYPE_FLAG_FABRIC_PORT_HEALTH) & bits )
            str += "EVENT_TYPE_FLAG_FABRIC_PORT_HEALTH | ";
        
        if( static_cast<uint32_t>(Driver::EVENT_TYPE_FLAG_PCI_LINK_HEALTH) & bits )
            str += "EVENT_TYPE_FLAG_PCI_LINK_HEALTH | ";
        
        if( static_cast<uint32_t>(Driver::EVENT_TYPE_FLAG_RAS_CORRECTABLE_ERRORS) & bits )
            str += "EVENT_TYPE_FLAG_RAS_CORRECTABLE_ERRORS | ";
        
        if( static_cast<uint32_t>(Driver::EVENT_TYPE_FLAG_RAS_UNCORRECTABLE_ERRORS) & bits )
            str += "EVENT_TYPE_FLAG_RAS_UNCORRECTABLE_ERRORS | ";
        
        if( static_cast<uint32_t>(Driver::EVENT_TYPE_FLAG_DEVICE_RESET_REQUIRED) & bits )
            str += "EVENT_TYPE_FLAG_DEVICE_RESET_REQUIRED | ";

        return ( str.size() > 3 ) 
            ? "Driver::{ " + str.substr(0, str.size() - 3) + " }"
            : "Driver::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::engine_type_flags_t to std::string
    std::string to_string( const Device::engine_type_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Device::ENGINE_TYPE_FLAG_OTHER) & bits )
            str += "ENGINE_TYPE_FLAG_OTHER | ";
        
        if( static_cast<uint32_t>(Device::ENGINE_TYPE_FLAG_COMPUTE) & bits )
            str += "ENGINE_TYPE_FLAG_COMPUTE | ";
        
        if( static_cast<uint32_t>(Device::ENGINE_TYPE_FLAG_3D) & bits )
            str += "ENGINE_TYPE_FLAG_3D | ";
        
        if( static_cast<uint32_t>(Device::ENGINE_TYPE_FLAG_MEDIA) & bits )
            str += "ENGINE_TYPE_FLAG_MEDIA | ";
        
        if( static_cast<uint32_t>(Device::ENGINE_TYPE_FLAG_DMA) & bits )
            str += "ENGINE_TYPE_FLAG_DMA | ";

        return ( str.size() > 3 ) 
            ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::repair_status_t to std::string
    std::string to_string( const Device::repair_status_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::repair_status_t::UNSUPPORTED:
            str = "Device::repair_status_t::UNSUPPORTED";
            break;

        case Device::repair_status_t::NOT_PERFORMED:
            str = "Device::repair_status_t::NOT_PERFORMED";
            break;

        case Device::repair_status_t::PERFORMED:
            str = "Device::repair_status_t::PERFORMED";
            break;

        default:
            str = "Device::repair_status_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::reset_reason_flags_t to std::string
    std::string to_string( const Device::reset_reason_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Device::RESET_REASON_FLAG_WEDGED) & bits )
            str += "RESET_REASON_FLAG_WEDGED | ";
        
        if( static_cast<uint32_t>(Device::RESET_REASON_FLAG_REPAIR) & bits )
            str += "RESET_REASON_FLAG_REPAIR | ";

        return ( str.size() > 3 ) 
            ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::pci_link_status_t to std::string
    std::string to_string( const Device::pci_link_status_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::pci_link_status_t::UNKNOWN:
            str = "Device::pci_link_status_t::UNKNOWN";
            break;

        case Device::pci_link_status_t::GOOD:
            str = "Device::pci_link_status_t::GOOD";
            break;

        case Device::pci_link_status_t::QUALITY_ISSUES:
            str = "Device::pci_link_status_t::QUALITY_ISSUES";
            break;

        case Device::pci_link_status_t::STABILITY_ISSUES:
            str = "Device::pci_link_status_t::STABILITY_ISSUES";
            break;

        default:
            str = "Device::pci_link_status_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::pci_link_qual_issue_flags_t to std::string
    std::string to_string( const Device::pci_link_qual_issue_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Device::PCI_LINK_QUAL_ISSUE_FLAG_REPLAYS) & bits )
            str += "PCI_LINK_QUAL_ISSUE_FLAG_REPLAYS | ";
        
        if( static_cast<uint32_t>(Device::PCI_LINK_QUAL_ISSUE_FLAG_SPEED) & bits )
            str += "PCI_LINK_QUAL_ISSUE_FLAG_SPEED | ";

        return ( str.size() > 3 ) 
            ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::pci_link_stab_issue_flags_t to std::string
    std::string to_string( const Device::pci_link_stab_issue_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Device::PCI_LINK_STAB_ISSUE_FLAG_RETRAINING) & bits )
            str += "PCI_LINK_STAB_ISSUE_FLAG_RETRAINING | ";

        return ( str.size() > 3 ) 
            ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
            : "Device::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::pci_bar_type_t to std::string
    std::string to_string( const Device::pci_bar_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::pci_bar_type_t::MMIO:
            str = "Device::pci_bar_type_t::MMIO";
            break;

        case Device::pci_bar_type_t::ROM:
            str = "Device::pci_bar_type_t::ROM";
            break;

        case Device::pci_bar_type_t::MEM:
            str = "Device::pci_bar_type_t::MEM";
            break;

        default:
            str = "Device::pci_bar_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::freq_domain_t to std::string
    std::string to_string( const Device::freq_domain_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::freq_domain_t::GPU:
            str = "Device::freq_domain_t::GPU";
            break;

        case Device::freq_domain_t::MEMORY:
            str = "Device::freq_domain_t::MEMORY";
            break;

        default:
            str = "Device::freq_domain_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::sched_mode_t to std::string
    std::string to_string( const Device::sched_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Device::sched_mode_t::TIMEOUT:
            str = "Device::sched_mode_t::TIMEOUT";
            break;

        case Device::sched_mode_t::TIMESLICE:
            str = "Device::sched_mode_t::TIMESLICE";
            break;

        case Device::sched_mode_t::EXCLUSIVE:
            str = "Device::sched_mode_t::EXCLUSIVE";
            break;

        case Device::sched_mode_t::COMPUTE_UNIT_DEBUG:
            str = "Device::sched_mode_t::COMPUTE_UNIT_DEBUG";
            break;

        default:
            str = "Device::sched_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::state_t to std::string
    std::string to_string( const Device::state_t val )
    {
        std::string str;
        
        str += "Device::state_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::state_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::state_t::reset : ";
        str += to_string(val.reset);
        str += "\n";
        
        str += "Device::state_t::repaired : ";
        str += to_string(val.repaired);
        str += "\n";

        return str;
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
        
        str += "Device::properties_t::core : ";
        str += to_string(val.core);
        str += "\n";
        
        str += "Device::properties_t::numSubdevices : ";
        str += std::to_string(val.numSubdevices);
        str += "\n";
        
        str += "Device::properties_t::serialNumber : ";
        str += val.serialNumber;
        str += "\n";
        
        str += "Device::properties_t::boardNumber : ";
        str += val.boardNumber;
        str += "\n";
        
        str += "Device::properties_t::brandName : ";
        str += val.brandName;
        str += "\n";
        
        str += "Device::properties_t::modelName : ";
        str += val.modelName;
        str += "\n";
        
        str += "Device::properties_t::vendorName : ";
        str += val.vendorName;
        str += "\n";
        
        str += "Device::properties_t::driverVersion : ";
        str += val.driverVersion;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::process_state_t to std::string
    std::string to_string( const Device::process_state_t val )
    {
        std::string str;
        
        str += "Device::process_state_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::process_state_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::process_state_t::processId : ";
        str += std::to_string(val.processId);
        str += "\n";
        
        str += "Device::process_state_t::memSize : ";
        str += std::to_string(val.memSize);
        str += "\n";
        
        str += "Device::process_state_t::sharedSize : ";
        str += std::to_string(val.sharedSize);
        str += "\n";
        
        str += "Device::process_state_t::engines : ";
        str += to_string(val.engines);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::pci_address_t to std::string
    std::string to_string( const Device::pci_address_t val )
    {
        std::string str;
        
        str += "Device::pci_address_t::domain : ";
        str += std::to_string(val.domain);
        str += "\n";
        
        str += "Device::pci_address_t::bus : ";
        str += std::to_string(val.bus);
        str += "\n";
        
        str += "Device::pci_address_t::device : ";
        str += std::to_string(val.device);
        str += "\n";
        
        str += "Device::pci_address_t::function : ";
        str += std::to_string(val.function);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::pci_speed_t to std::string
    std::string to_string( const Device::pci_speed_t val )
    {
        std::string str;
        
        str += "Device::pci_speed_t::gen : ";
        str += std::to_string(val.gen);
        str += "\n";
        
        str += "Device::pci_speed_t::width : ";
        str += std::to_string(val.width);
        str += "\n";
        
        str += "Device::pci_speed_t::maxBandwidth : ";
        str += std::to_string(val.maxBandwidth);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::pci_properties_t to std::string
    std::string to_string( const Device::pci_properties_t val )
    {
        std::string str;
        
        str += "Device::pci_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::pci_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::pci_properties_t::address : ";
        str += to_string(val.address);
        str += "\n";
        
        str += "Device::pci_properties_t::maxSpeed : ";
        str += to_string(val.maxSpeed);
        str += "\n";
        
        str += "Device::pci_properties_t::haveBandwidthCounters : ";
        str += std::to_string(val.haveBandwidthCounters);
        str += "\n";
        
        str += "Device::pci_properties_t::havePacketCounters : ";
        str += std::to_string(val.havePacketCounters);
        str += "\n";
        
        str += "Device::pci_properties_t::haveReplayCounters : ";
        str += std::to_string(val.haveReplayCounters);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::pci_state_t to std::string
    std::string to_string( const Device::pci_state_t val )
    {
        std::string str;
        
        str += "Device::pci_state_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::pci_state_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::pci_state_t::status : ";
        str += to_string(val.status);
        str += "\n";
        
        str += "Device::pci_state_t::qualityIssues : ";
        str += to_string(val.qualityIssues);
        str += "\n";
        
        str += "Device::pci_state_t::stabilityIssues : ";
        str += to_string(val.stabilityIssues);
        str += "\n";
        
        str += "Device::pci_state_t::speed : ";
        str += to_string(val.speed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::pci_bar_properties_t to std::string
    std::string to_string( const Device::pci_bar_properties_t val )
    {
        std::string str;
        
        str += "Device::pci_bar_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::pci_bar_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::pci_bar_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Device::pci_bar_properties_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Device::pci_bar_properties_t::base : ";
        str += std::to_string(val.base);
        str += "\n";
        
        str += "Device::pci_bar_properties_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::pci_stats_t to std::string
    std::string to_string( const Device::pci_stats_t val )
    {
        std::string str;
        
        str += "Device::pci_stats_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";
        
        str += "Device::pci_stats_t::replayCounter : ";
        str += std::to_string(val.replayCounter);
        str += "\n";
        
        str += "Device::pci_stats_t::packetCounter : ";
        str += std::to_string(val.packetCounter);
        str += "\n";
        
        str += "Device::pci_stats_t::rxCounter : ";
        str += std::to_string(val.rxCounter);
        str += "\n";
        
        str += "Device::pci_stats_t::txCounter : ";
        str += std::to_string(val.txCounter);
        str += "\n";
        
        str += "Device::pci_stats_t::speed : ";
        str += to_string(val.speed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::sched_timeout_properties_t to std::string
    std::string to_string( const Device::sched_timeout_properties_t val )
    {
        std::string str;
        
        str += "Device::sched_timeout_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::sched_timeout_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::sched_timeout_properties_t::watchdogTimeout : ";
        str += std::to_string(val.watchdogTimeout);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::sched_timeslice_properties_t to std::string
    std::string to_string( const Device::sched_timeslice_properties_t val )
    {
        std::string str;
        
        str += "Device::sched_timeslice_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Device::sched_timeslice_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Device::sched_timeslice_properties_t::interval : ";
        str += std::to_string(val.interval);
        str += "\n";
        
        str += "Device::sched_timeslice_properties_t::yieldTimeout : ";
        str += std::to_string(val.yieldTimeout);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region diagnostics
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Diagnostics::diag_result_t to std::string
    std::string to_string( const Diagnostics::diag_result_t val )
    {
        std::string str;

        switch( val )
        {
        case Diagnostics::diag_result_t::NO_ERRORS:
            str = "Diagnostics::diag_result_t::NO_ERRORS";
            break;

        case Diagnostics::diag_result_t::ABORT:
            str = "Diagnostics::diag_result_t::ABORT";
            break;

        case Diagnostics::diag_result_t::FAIL_CANT_REPAIR:
            str = "Diagnostics::diag_result_t::FAIL_CANT_REPAIR";
            break;

        case Diagnostics::diag_result_t::REBOOT_FOR_REPAIR:
            str = "Diagnostics::diag_result_t::REBOOT_FOR_REPAIR";
            break;

        default:
            str = "Diagnostics::diag_result_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Diagnostics::diag_test_t to std::string
    std::string to_string( const Diagnostics::diag_test_t val )
    {
        std::string str;
        
        str += "Diagnostics::diag_test_t::index : ";
        str += std::to_string(val.index);
        str += "\n";
        
        str += "Diagnostics::diag_test_t::name : ";
        str += val.name;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Diagnostics::diag_properties_t to std::string
    std::string to_string( const Diagnostics::diag_properties_t val )
    {
        std::string str;
        
        str += "Diagnostics::diag_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Diagnostics::diag_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Diagnostics::diag_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "Diagnostics::diag_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "Diagnostics::diag_properties_t::name : ";
        str += val.name;
        str += "\n";
        
        str += "Diagnostics::diag_properties_t::haveTests : ";
        str += std::to_string(val.haveTests);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region engine
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Engine::group_t to std::string
    std::string to_string( const Engine::group_t val )
    {
        std::string str;

        switch( val )
        {
        case Engine::group_t::ALL:
            str = "Engine::group_t::ALL";
            break;

        case Engine::group_t::COMPUTE_ALL:
            str = "Engine::group_t::COMPUTE_ALL";
            break;

        case Engine::group_t::MEDIA_ALL:
            str = "Engine::group_t::MEDIA_ALL";
            break;

        case Engine::group_t::COPY_ALL:
            str = "Engine::group_t::COPY_ALL";
            break;

        case Engine::group_t::COMPUTE_SINGLE:
            str = "Engine::group_t::COMPUTE_SINGLE";
            break;

        case Engine::group_t::RENDER_SINGLE:
            str = "Engine::group_t::RENDER_SINGLE";
            break;

        case Engine::group_t::MEDIA_DECODE_SINGLE:
            str = "Engine::group_t::MEDIA_DECODE_SINGLE";
            break;

        case Engine::group_t::MEDIA_ENCODE_SINGLE:
            str = "Engine::group_t::MEDIA_ENCODE_SINGLE";
            break;

        case Engine::group_t::COPY_SINGLE:
            str = "Engine::group_t::COPY_SINGLE";
            break;

        default:
            str = "Engine::group_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Engine::properties_t to std::string
    std::string to_string( const Engine::properties_t val )
    {
        std::string str;
        
        str += "Engine::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Engine::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Engine::properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Engine::properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "Engine::properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Engine::stats_t to std::string
    std::string to_string( const Engine::stats_t val )
    {
        std::string str;
        
        str += "Engine::stats_t::activeTime : ";
        str += std::to_string(val.activeTime);
        str += "\n";
        
        str += "Engine::stats_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region events
#endif
#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region fabric
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FabricPort::status_t to std::string
    std::string to_string( const FabricPort::status_t val )
    {
        std::string str;

        switch( val )
        {
        case FabricPort::status_t::UNKNOWN:
            str = "FabricPort::status_t::UNKNOWN";
            break;

        case FabricPort::status_t::HEALTHY:
            str = "FabricPort::status_t::HEALTHY";
            break;

        case FabricPort::status_t::DEGRADED:
            str = "FabricPort::status_t::DEGRADED";
            break;

        case FabricPort::status_t::FAILED:
            str = "FabricPort::status_t::FAILED";
            break;

        case FabricPort::status_t::DISABLED:
            str = "FabricPort::status_t::DISABLED";
            break;

        default:
            str = "FabricPort::status_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FabricPort::qual_issue_flags_t to std::string
    std::string to_string( const FabricPort::qual_issue_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(FabricPort::QUAL_ISSUE_FLAG_LINK_ERRORS) & bits )
            str += "QUAL_ISSUE_FLAG_LINK_ERRORS | ";
        
        if( static_cast<uint32_t>(FabricPort::QUAL_ISSUE_FLAG_SPEED) & bits )
            str += "QUAL_ISSUE_FLAG_SPEED | ";

        return ( str.size() > 3 ) 
            ? "FabricPort::{ " + str.substr(0, str.size() - 3) + " }"
            : "FabricPort::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FabricPort::failure_flags_t to std::string
    std::string to_string( const FabricPort::failure_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(FabricPort::FAILURE_FLAG_FAILED) & bits )
            str += "FAILURE_FLAG_FAILED | ";
        
        if( static_cast<uint32_t>(FabricPort::FAILURE_FLAG_TRAINING_TIMEOUT) & bits )
            str += "FAILURE_FLAG_TRAINING_TIMEOUT | ";
        
        if( static_cast<uint32_t>(FabricPort::FAILURE_FLAG_FLAPPING) & bits )
            str += "FAILURE_FLAG_FLAPPING | ";

        return ( str.size() > 3 ) 
            ? "FabricPort::{ " + str.substr(0, str.size() - 3) + " }"
            : "FabricPort::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FabricPort::id_t to std::string
    std::string to_string( const FabricPort::id_t val )
    {
        std::string str;
        
        str += "FabricPort::id_t::fabricId : ";
        str += std::to_string(val.fabricId);
        str += "\n";
        
        str += "FabricPort::id_t::attachId : ";
        str += std::to_string(val.attachId);
        str += "\n";
        
        str += "FabricPort::id_t::portNumber : ";
        str += std::to_string(val.portNumber);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FabricPort::speed_t to std::string
    std::string to_string( const FabricPort::speed_t val )
    {
        std::string str;
        
        str += "FabricPort::speed_t::bitRate : ";
        str += std::to_string(val.bitRate);
        str += "\n";
        
        str += "FabricPort::speed_t::width : ";
        str += std::to_string(val.width);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FabricPort::properties_t to std::string
    std::string to_string( const FabricPort::properties_t val )
    {
        std::string str;
        
        str += "FabricPort::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "FabricPort::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "FabricPort::properties_t::model : ";
        str += val.model;
        str += "\n";
        
        str += "FabricPort::properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "FabricPort::properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "FabricPort::properties_t::portId : ";
        str += to_string(val.portId);
        str += "\n";
        
        str += "FabricPort::properties_t::maxRxSpeed : ";
        str += to_string(val.maxRxSpeed);
        str += "\n";
        
        str += "FabricPort::properties_t::maxTxSpeed : ";
        str += to_string(val.maxTxSpeed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FabricPort::fabric_link_type_t to std::string
    std::string to_string( const FabricPort::fabric_link_type_t val )
    {
        std::string str;
        
        str += "FabricPort::fabric_link_type_t::desc : ";
        str += val.desc;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FabricPort::config_t to std::string
    std::string to_string( const FabricPort::config_t val )
    {
        std::string str;
        
        str += "FabricPort::config_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "FabricPort::config_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "FabricPort::config_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "FabricPort::config_t::beaconing : ";
        str += std::to_string(val.beaconing);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FabricPort::state_t to std::string
    std::string to_string( const FabricPort::state_t val )
    {
        std::string str;
        
        str += "FabricPort::state_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "FabricPort::state_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "FabricPort::state_t::status : ";
        str += to_string(val.status);
        str += "\n";
        
        str += "FabricPort::state_t::qualityIssues : ";
        str += to_string(val.qualityIssues);
        str += "\n";
        
        str += "FabricPort::state_t::failureReasons : ";
        str += to_string(val.failureReasons);
        str += "\n";
        
        str += "FabricPort::state_t::remotePortId : ";
        str += to_string(val.remotePortId);
        str += "\n";
        
        str += "FabricPort::state_t::rxSpeed : ";
        str += to_string(val.rxSpeed);
        str += "\n";
        
        str += "FabricPort::state_t::txSpeed : ";
        str += to_string(val.txSpeed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts FabricPort::throughput_t to std::string
    std::string to_string( const FabricPort::throughput_t val )
    {
        std::string str;
        
        str += "FabricPort::throughput_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";
        
        str += "FabricPort::throughput_t::rxCounter : ";
        str += std::to_string(val.rxCounter);
        str += "\n";
        
        str += "FabricPort::throughput_t::txCounter : ";
        str += std::to_string(val.txCounter);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region fan
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fan::speed_mode_t to std::string
    std::string to_string( const Fan::speed_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Fan::speed_mode_t::DEFAULT:
            str = "Fan::speed_mode_t::DEFAULT";
            break;

        case Fan::speed_mode_t::FIXED:
            str = "Fan::speed_mode_t::FIXED";
            break;

        case Fan::speed_mode_t::TABLE:
            str = "Fan::speed_mode_t::TABLE";
            break;

        default:
            str = "Fan::speed_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fan::speed_units_t to std::string
    std::string to_string( const Fan::speed_units_t val )
    {
        std::string str;

        switch( val )
        {
        case Fan::speed_units_t::RPM:
            str = "Fan::speed_units_t::RPM";
            break;

        case Fan::speed_units_t::PERCENT:
            str = "Fan::speed_units_t::PERCENT";
            break;

        default:
            str = "Fan::speed_units_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fan::speed_t to std::string
    std::string to_string( const Fan::speed_t val )
    {
        std::string str;
        
        str += "Fan::speed_t::speed : ";
        str += std::to_string(val.speed);
        str += "\n";
        
        str += "Fan::speed_t::units : ";
        str += to_string(val.units);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fan::temp_speed_t to std::string
    std::string to_string( const Fan::temp_speed_t val )
    {
        std::string str;
        
        str += "Fan::temp_speed_t::temperature : ";
        str += std::to_string(val.temperature);
        str += "\n";
        
        str += "Fan::temp_speed_t::speed : ";
        str += to_string(val.speed);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fan::speed_table_t to std::string
    std::string to_string( const Fan::speed_table_t val )
    {
        std::string str;
        
        str += "Fan::speed_table_t::numPoints : ";
        str += std::to_string(val.numPoints);
        str += "\n";
        
        str += "Fan::speed_table_t::table : ";
        {
            std::string tmp;
            for( auto& entry : val.table )
            {
                tmp += to_string( entry );
                tmp += ", ";
            }
            str += "[ " + tmp.substr( 0, tmp.size() - 2 ) + " ]";;
        }
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fan::properties_t to std::string
    std::string to_string( const Fan::properties_t val )
    {
        std::string str;
        
        str += "Fan::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Fan::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Fan::properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "Fan::properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "Fan::properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "Fan::properties_t::supportedModes : ";
        str += std::to_string(val.supportedModes);
        str += "\n";
        
        str += "Fan::properties_t::supportedUnits : ";
        str += std::to_string(val.supportedUnits);
        str += "\n";
        
        str += "Fan::properties_t::maxRPM : ";
        str += std::to_string(val.maxRPM);
        str += "\n";
        
        str += "Fan::properties_t::maxPoints : ";
        str += std::to_string(val.maxPoints);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fan::config_t to std::string
    std::string to_string( const Fan::config_t val )
    {
        std::string str;
        
        str += "Fan::config_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Fan::config_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Fan::config_t::mode : ";
        str += to_string(val.mode);
        str += "\n";
        
        str += "Fan::config_t::speedFixed : ";
        str += to_string(val.speedFixed);
        str += "\n";
        
        str += "Fan::config_t::speedTable : ";
        str += to_string(val.speedTable);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region firmware
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Firmware::properties_t to std::string
    std::string to_string( const Firmware::properties_t val )
    {
        std::string str;
        
        str += "Firmware::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Firmware::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Firmware::properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "Firmware::properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "Firmware::properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "Firmware::properties_t::name : ";
        str += val.name;
        str += "\n";
        
        str += "Firmware::properties_t::version : ";
        str += val.version;
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region frequency
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Frequency::freq_throttle_reason_flags_t to std::string
    std::string to_string( const Frequency::freq_throttle_reason_flags_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;

        if( 0 == bits )
            str += "0 | ";
        
        if( static_cast<uint32_t>(Frequency::FREQ_THROTTLE_REASON_FLAG_AVE_PWR_CAP) & bits )
            str += "FREQ_THROTTLE_REASON_FLAG_AVE_PWR_CAP | ";
        
        if( static_cast<uint32_t>(Frequency::FREQ_THROTTLE_REASON_FLAG_BURST_PWR_CAP) & bits )
            str += "FREQ_THROTTLE_REASON_FLAG_BURST_PWR_CAP | ";
        
        if( static_cast<uint32_t>(Frequency::FREQ_THROTTLE_REASON_FLAG_CURRENT_LIMIT) & bits )
            str += "FREQ_THROTTLE_REASON_FLAG_CURRENT_LIMIT | ";
        
        if( static_cast<uint32_t>(Frequency::FREQ_THROTTLE_REASON_FLAG_THERMAL_LIMIT) & bits )
            str += "FREQ_THROTTLE_REASON_FLAG_THERMAL_LIMIT | ";
        
        if( static_cast<uint32_t>(Frequency::FREQ_THROTTLE_REASON_FLAG_PSU_ALERT) & bits )
            str += "FREQ_THROTTLE_REASON_FLAG_PSU_ALERT | ";
        
        if( static_cast<uint32_t>(Frequency::FREQ_THROTTLE_REASON_FLAG_SW_RANGE) & bits )
            str += "FREQ_THROTTLE_REASON_FLAG_SW_RANGE | ";
        
        if( static_cast<uint32_t>(Frequency::FREQ_THROTTLE_REASON_FLAG_HW_RANGE) & bits )
            str += "FREQ_THROTTLE_REASON_FLAG_HW_RANGE | ";

        return ( str.size() > 3 ) 
            ? "Frequency::{ " + str.substr(0, str.size() - 3) + " }"
            : "Frequency::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Frequency::oc_mode_t to std::string
    std::string to_string( const Frequency::oc_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Frequency::oc_mode_t::OFF:
            str = "Frequency::oc_mode_t::OFF";
            break;

        case Frequency::oc_mode_t::OVERRIDE:
            str = "Frequency::oc_mode_t::OVERRIDE";
            break;

        case Frequency::oc_mode_t::INTERPOLATIVE:
            str = "Frequency::oc_mode_t::INTERPOLATIVE";
            break;

        case Frequency::oc_mode_t::FIXED:
            str = "Frequency::oc_mode_t::FIXED";
            break;

        default:
            str = "Frequency::oc_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Frequency::freq_properties_t to std::string
    std::string to_string( const Frequency::freq_properties_t val )
    {
        std::string str;
        
        str += "Frequency::freq_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Frequency::freq_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Frequency::freq_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Frequency::freq_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "Frequency::freq_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "Frequency::freq_properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "Frequency::freq_properties_t::isThrottleEventSupported : ";
        str += std::to_string(val.isThrottleEventSupported);
        str += "\n";
        
        str += "Frequency::freq_properties_t::min : ";
        str += std::to_string(val.min);
        str += "\n";
        
        str += "Frequency::freq_properties_t::max : ";
        str += std::to_string(val.max);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Frequency::freq_range_t to std::string
    std::string to_string( const Frequency::freq_range_t val )
    {
        std::string str;
        
        str += "Frequency::freq_range_t::min : ";
        str += std::to_string(val.min);
        str += "\n";
        
        str += "Frequency::freq_range_t::max : ";
        str += std::to_string(val.max);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Frequency::freq_state_t to std::string
    std::string to_string( const Frequency::freq_state_t val )
    {
        std::string str;
        
        str += "Frequency::freq_state_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Frequency::freq_state_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Frequency::freq_state_t::currentVoltage : ";
        str += std::to_string(val.currentVoltage);
        str += "\n";
        
        str += "Frequency::freq_state_t::request : ";
        str += std::to_string(val.request);
        str += "\n";
        
        str += "Frequency::freq_state_t::tdp : ";
        str += std::to_string(val.tdp);
        str += "\n";
        
        str += "Frequency::freq_state_t::efficient : ";
        str += std::to_string(val.efficient);
        str += "\n";
        
        str += "Frequency::freq_state_t::actual : ";
        str += std::to_string(val.actual);
        str += "\n";
        
        str += "Frequency::freq_state_t::throttleReasons : ";
        str += to_string(val.throttleReasons);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Frequency::freq_throttle_time_t to std::string
    std::string to_string( const Frequency::freq_throttle_time_t val )
    {
        std::string str;
        
        str += "Frequency::freq_throttle_time_t::throttleTime : ";
        str += std::to_string(val.throttleTime);
        str += "\n";
        
        str += "Frequency::freq_throttle_time_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Frequency::oc_capabilities_t to std::string
    std::string to_string( const Frequency::oc_capabilities_t val )
    {
        std::string str;
        
        str += "Frequency::oc_capabilities_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Frequency::oc_capabilities_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Frequency::oc_capabilities_t::isOcSupported : ";
        str += std::to_string(val.isOcSupported);
        str += "\n";
        
        str += "Frequency::oc_capabilities_t::maxFactoryDefaultFrequency : ";
        str += std::to_string(val.maxFactoryDefaultFrequency);
        str += "\n";
        
        str += "Frequency::oc_capabilities_t::maxFactoryDefaultVoltage : ";
        str += std::to_string(val.maxFactoryDefaultVoltage);
        str += "\n";
        
        str += "Frequency::oc_capabilities_t::maxOcFrequency : ";
        str += std::to_string(val.maxOcFrequency);
        str += "\n";
        
        str += "Frequency::oc_capabilities_t::minOcVoltageOffset : ";
        str += std::to_string(val.minOcVoltageOffset);
        str += "\n";
        
        str += "Frequency::oc_capabilities_t::maxOcVoltageOffset : ";
        str += std::to_string(val.maxOcVoltageOffset);
        str += "\n";
        
        str += "Frequency::oc_capabilities_t::maxOcVoltage : ";
        str += std::to_string(val.maxOcVoltage);
        str += "\n";
        
        str += "Frequency::oc_capabilities_t::isTjMaxSupported : ";
        str += std::to_string(val.isTjMaxSupported);
        str += "\n";
        
        str += "Frequency::oc_capabilities_t::isIccMaxSupported : ";
        str += std::to_string(val.isIccMaxSupported);
        str += "\n";
        
        str += "Frequency::oc_capabilities_t::isHighVoltModeCapable : ";
        str += std::to_string(val.isHighVoltModeCapable);
        str += "\n";
        
        str += "Frequency::oc_capabilities_t::isHighVoltModeEnabled : ";
        str += std::to_string(val.isHighVoltModeEnabled);
        str += "\n";
        
        str += "Frequency::oc_capabilities_t::isExtendedModeSupported : ";
        str += std::to_string(val.isExtendedModeSupported);
        str += "\n";
        
        str += "Frequency::oc_capabilities_t::isFixedModeSupported : ";
        str += std::to_string(val.isFixedModeSupported);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region led
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Led::properties_t to std::string
    std::string to_string( const Led::properties_t val )
    {
        std::string str;
        
        str += "Led::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Led::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Led::properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "Led::properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "Led::properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "Led::properties_t::haveRGB : ";
        str += std::to_string(val.haveRGB);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Led::color_t to std::string
    std::string to_string( const Led::color_t val )
    {
        std::string str;
        
        str += "Led::color_t::red : ";
        str += std::to_string(val.red);
        str += "\n";
        
        str += "Led::color_t::green : ";
        str += std::to_string(val.green);
        str += "\n";
        
        str += "Led::color_t::blue : ";
        str += std::to_string(val.blue);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Led::state_t to std::string
    std::string to_string( const Led::state_t val )
    {
        std::string str;
        
        str += "Led::state_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Led::state_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Led::state_t::isOn : ";
        str += std::to_string(val.isOn);
        str += "\n";
        
        str += "Led::state_t::color : ";
        str += to_string(val.color);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region memory
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Memory::mem_type_t to std::string
    std::string to_string( const Memory::mem_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Memory::mem_type_t::HBM:
            str = "Memory::mem_type_t::HBM";
            break;

        case Memory::mem_type_t::DDR:
            str = "Memory::mem_type_t::DDR";
            break;

        case Memory::mem_type_t::DDR3:
            str = "Memory::mem_type_t::DDR3";
            break;

        case Memory::mem_type_t::DDR4:
            str = "Memory::mem_type_t::DDR4";
            break;

        case Memory::mem_type_t::DDR5:
            str = "Memory::mem_type_t::DDR5";
            break;

        case Memory::mem_type_t::LPDDR:
            str = "Memory::mem_type_t::LPDDR";
            break;

        case Memory::mem_type_t::LPDDR3:
            str = "Memory::mem_type_t::LPDDR3";
            break;

        case Memory::mem_type_t::LPDDR4:
            str = "Memory::mem_type_t::LPDDR4";
            break;

        case Memory::mem_type_t::LPDDR5:
            str = "Memory::mem_type_t::LPDDR5";
            break;

        case Memory::mem_type_t::SRAM:
            str = "Memory::mem_type_t::SRAM";
            break;

        case Memory::mem_type_t::L1:
            str = "Memory::mem_type_t::L1";
            break;

        case Memory::mem_type_t::L3:
            str = "Memory::mem_type_t::L3";
            break;

        case Memory::mem_type_t::GRF:
            str = "Memory::mem_type_t::GRF";
            break;

        case Memory::mem_type_t::SLM:
            str = "Memory::mem_type_t::SLM";
            break;

        default:
            str = "Memory::mem_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Memory::mem_loc_t to std::string
    std::string to_string( const Memory::mem_loc_t val )
    {
        std::string str;

        switch( val )
        {
        case Memory::mem_loc_t::SYSTEM:
            str = "Memory::mem_loc_t::SYSTEM";
            break;

        case Memory::mem_loc_t::DEVICE:
            str = "Memory::mem_loc_t::DEVICE";
            break;

        default:
            str = "Memory::mem_loc_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Memory::mem_health_t to std::string
    std::string to_string( const Memory::mem_health_t val )
    {
        std::string str;

        switch( val )
        {
        case Memory::mem_health_t::UNKNOWN:
            str = "Memory::mem_health_t::UNKNOWN";
            break;

        case Memory::mem_health_t::OK:
            str = "Memory::mem_health_t::OK";
            break;

        case Memory::mem_health_t::DEGRADED:
            str = "Memory::mem_health_t::DEGRADED";
            break;

        case Memory::mem_health_t::CRITICAL:
            str = "Memory::mem_health_t::CRITICAL";
            break;

        case Memory::mem_health_t::REPLACE:
            str = "Memory::mem_health_t::REPLACE";
            break;

        default:
            str = "Memory::mem_health_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Memory::mem_properties_t to std::string
    std::string to_string( const Memory::mem_properties_t val )
    {
        std::string str;
        
        str += "Memory::mem_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Memory::mem_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Memory::mem_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Memory::mem_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "Memory::mem_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "Memory::mem_properties_t::location : ";
        str += to_string(val.location);
        str += "\n";
        
        str += "Memory::mem_properties_t::physicalSize : ";
        str += std::to_string(val.physicalSize);
        str += "\n";
        
        str += "Memory::mem_properties_t::busWidth : ";
        str += std::to_string(val.busWidth);
        str += "\n";
        
        str += "Memory::mem_properties_t::numChannels : ";
        str += std::to_string(val.numChannels);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Memory::mem_state_t to std::string
    std::string to_string( const Memory::mem_state_t val )
    {
        std::string str;
        
        str += "Memory::mem_state_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Memory::mem_state_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Memory::mem_state_t::health : ";
        str += to_string(val.health);
        str += "\n";
        
        str += "Memory::mem_state_t::free : ";
        str += std::to_string(val.free);
        str += "\n";
        
        str += "Memory::mem_state_t::size : ";
        str += std::to_string(val.size);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Memory::mem_bandwidth_t to std::string
    std::string to_string( const Memory::mem_bandwidth_t val )
    {
        std::string str;
        
        str += "Memory::mem_bandwidth_t::readCounter : ";
        str += std::to_string(val.readCounter);
        str += "\n";
        
        str += "Memory::mem_bandwidth_t::writeCounter : ";
        str += std::to_string(val.writeCounter);
        str += "\n";
        
        str += "Memory::mem_bandwidth_t::maxBandwidth : ";
        str += std::to_string(val.maxBandwidth);
        str += "\n";
        
        str += "Memory::mem_bandwidth_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region performance
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts PerformanceFactor::perf_properties_t to std::string
    std::string to_string( const PerformanceFactor::perf_properties_t val )
    {
        std::string str;
        
        str += "PerformanceFactor::perf_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "PerformanceFactor::perf_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "PerformanceFactor::perf_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "PerformanceFactor::perf_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "PerformanceFactor::perf_properties_t::engines : ";
        str += to_string(val.engines);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region power
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::properties_t to std::string
    std::string to_string( const Power::properties_t val )
    {
        std::string str;
        
        str += "Power::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Power::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Power::properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "Power::properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "Power::properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "Power::properties_t::isEnergyThresholdSupported : ";
        str += std::to_string(val.isEnergyThresholdSupported);
        str += "\n";
        
        str += "Power::properties_t::defaultLimit : ";
        str += std::to_string(val.defaultLimit);
        str += "\n";
        
        str += "Power::properties_t::minLimit : ";
        str += std::to_string(val.minLimit);
        str += "\n";
        
        str += "Power::properties_t::maxLimit : ";
        str += std::to_string(val.maxLimit);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::energy_counter_t to std::string
    std::string to_string( const Power::energy_counter_t val )
    {
        std::string str;
        
        str += "Power::energy_counter_t::energy : ";
        str += std::to_string(val.energy);
        str += "\n";
        
        str += "Power::energy_counter_t::timestamp : ";
        str += std::to_string(val.timestamp);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::sustained_limit_t to std::string
    std::string to_string( const Power::sustained_limit_t val )
    {
        std::string str;
        
        str += "Power::sustained_limit_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "Power::sustained_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";
        
        str += "Power::sustained_limit_t::interval : ";
        str += std::to_string(val.interval);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::burst_limit_t to std::string
    std::string to_string( const Power::burst_limit_t val )
    {
        std::string str;
        
        str += "Power::burst_limit_t::enabled : ";
        str += std::to_string(val.enabled);
        str += "\n";
        
        str += "Power::burst_limit_t::power : ";
        str += std::to_string(val.power);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::peak_limit_t to std::string
    std::string to_string( const Power::peak_limit_t val )
    {
        std::string str;
        
        str += "Power::peak_limit_t::powerAC : ";
        str += std::to_string(val.powerAC);
        str += "\n";
        
        str += "Power::peak_limit_t::powerDC : ";
        str += std::to_string(val.powerDC);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Power::energy_threshold_t to std::string
    std::string to_string( const Power::energy_threshold_t val )
    {
        std::string str;
        
        str += "Power::energy_threshold_t::enable : ";
        str += std::to_string(val.enable);
        str += "\n";
        
        str += "Power::energy_threshold_t::threshold : ";
        str += std::to_string(val.threshold);
        str += "\n";
        
        str += "Power::energy_threshold_t::processId : ";
        str += std::to_string(val.processId);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region psu
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Psu::voltage_status_t to std::string
    std::string to_string( const Psu::voltage_status_t val )
    {
        std::string str;

        switch( val )
        {
        case Psu::voltage_status_t::UNKNOWN:
            str = "Psu::voltage_status_t::UNKNOWN";
            break;

        case Psu::voltage_status_t::NORMAL:
            str = "Psu::voltage_status_t::NORMAL";
            break;

        case Psu::voltage_status_t::OVER:
            str = "Psu::voltage_status_t::OVER";
            break;

        case Psu::voltage_status_t::UNDER:
            str = "Psu::voltage_status_t::UNDER";
            break;

        default:
            str = "Psu::voltage_status_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Psu::properties_t to std::string
    std::string to_string( const Psu::properties_t val )
    {
        std::string str;
        
        str += "Psu::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Psu::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Psu::properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "Psu::properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "Psu::properties_t::haveFan : ";
        str += std::to_string(val.haveFan);
        str += "\n";
        
        str += "Psu::properties_t::ampLimit : ";
        str += std::to_string(val.ampLimit);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Psu::state_t to std::string
    std::string to_string( const Psu::state_t val )
    {
        std::string str;
        
        str += "Psu::state_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Psu::state_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Psu::state_t::voltStatus : ";
        str += to_string(val.voltStatus);
        str += "\n";
        
        str += "Psu::state_t::fanFailed : ";
        str += std::to_string(val.fanFailed);
        str += "\n";
        
        str += "Psu::state_t::temperature : ";
        str += std::to_string(val.temperature);
        str += "\n";
        
        str += "Psu::state_t::current : ";
        str += std::to_string(val.current);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region ras
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Ras::error_type_t to std::string
    std::string to_string( const Ras::error_type_t val )
    {
        std::string str;

        switch( val )
        {
        case Ras::error_type_t::CORRECTABLE:
            str = "Ras::error_type_t::CORRECTABLE";
            break;

        case Ras::error_type_t::UNCORRECTABLE:
            str = "Ras::error_type_t::UNCORRECTABLE";
            break;

        default:
            str = "Ras::error_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Ras::error_cat_t to std::string
    std::string to_string( const Ras::error_cat_t val )
    {
        std::string str;

        switch( val )
        {
        case Ras::error_cat_t::RESET:
            str = "Ras::error_cat_t::RESET";
            break;

        case Ras::error_cat_t::PROGRAMMING_ERRORS:
            str = "Ras::error_cat_t::PROGRAMMING_ERRORS";
            break;

        case Ras::error_cat_t::DRIVER_ERRORS:
            str = "Ras::error_cat_t::DRIVER_ERRORS";
            break;

        case Ras::error_cat_t::COMPUTE_ERRORS:
            str = "Ras::error_cat_t::COMPUTE_ERRORS";
            break;

        case Ras::error_cat_t::NON_COMPUTE_ERRORS:
            str = "Ras::error_cat_t::NON_COMPUTE_ERRORS";
            break;

        case Ras::error_cat_t::CACHE_ERRORS:
            str = "Ras::error_cat_t::CACHE_ERRORS";
            break;

        case Ras::error_cat_t::DISPLAY_ERRORS:
            str = "Ras::error_cat_t::DISPLAY_ERRORS";
            break;

        default:
            str = "Ras::error_cat_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Ras::properties_t to std::string
    std::string to_string( const Ras::properties_t val )
    {
        std::string str;
        
        str += "Ras::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Ras::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Ras::properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Ras::properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "Ras::properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Ras::state_t to std::string
    std::string to_string( const Ras::state_t val )
    {
        std::string str;
        
        str += "Ras::state_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Ras::state_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Ras::state_t::category : ";
        {
            std::string tmp;
            for( auto& entry : val.category )
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
    /// @brief Converts Ras::config_t to std::string
    std::string to_string( const Ras::config_t val )
    {
        std::string str;
        
        str += "Ras::config_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Ras::config_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Ras::config_t::totalThreshold : ";
        str += std::to_string(val.totalThreshold);
        str += "\n";
        
        str += "Ras::config_t::detailedThresholds : ";
        str += to_string(val.detailedThresholds);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region scheduler
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Scheduler::sched_properties_t to std::string
    std::string to_string( const Scheduler::sched_properties_t val )
    {
        std::string str;
        
        str += "Scheduler::sched_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Scheduler::sched_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Scheduler::sched_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "Scheduler::sched_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "Scheduler::sched_properties_t::canControl : ";
        str += std::to_string(val.canControl);
        str += "\n";
        
        str += "Scheduler::sched_properties_t::engines : ";
        str += to_string(val.engines);
        str += "\n";
        
        str += "Scheduler::sched_properties_t::supportedModes : ";
        str += std::to_string(val.supportedModes);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region standby
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Standby::type_t to std::string
    std::string to_string( const Standby::type_t val )
    {
        std::string str;

        switch( val )
        {
        case Standby::type_t::GLOBAL:
            str = "Standby::type_t::GLOBAL";
            break;

        default:
            str = "Standby::type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Standby::promo_mode_t to std::string
    std::string to_string( const Standby::promo_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Standby::promo_mode_t::DEFAULT:
            str = "Standby::promo_mode_t::DEFAULT";
            break;

        case Standby::promo_mode_t::NEVER:
            str = "Standby::promo_mode_t::NEVER";
            break;

        default:
            str = "Standby::promo_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Standby::properties_t to std::string
    std::string to_string( const Standby::properties_t val )
    {
        std::string str;
        
        str += "Standby::properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Standby::properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Standby::properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Standby::properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "Standby::properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
#if !defined(__GNUC__)
#pragma region temperature
#endif
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Temperature::temp_sensors_t to std::string
    std::string to_string( const Temperature::temp_sensors_t val )
    {
        std::string str;

        switch( val )
        {
        case Temperature::temp_sensors_t::GLOBAL:
            str = "Temperature::temp_sensors_t::GLOBAL";
            break;

        case Temperature::temp_sensors_t::GPU:
            str = "Temperature::temp_sensors_t::GPU";
            break;

        case Temperature::temp_sensors_t::MEMORY:
            str = "Temperature::temp_sensors_t::MEMORY";
            break;

        case Temperature::temp_sensors_t::GLOBAL_MIN:
            str = "Temperature::temp_sensors_t::GLOBAL_MIN";
            break;

        case Temperature::temp_sensors_t::GPU_MIN:
            str = "Temperature::temp_sensors_t::GPU_MIN";
            break;

        case Temperature::temp_sensors_t::MEMORY_MIN:
            str = "Temperature::temp_sensors_t::MEMORY_MIN";
            break;

        default:
            str = "Temperature::temp_sensors_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Temperature::temp_properties_t to std::string
    std::string to_string( const Temperature::temp_properties_t val )
    {
        std::string str;
        
        str += "Temperature::temp_properties_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Temperature::temp_properties_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Temperature::temp_properties_t::type : ";
        str += to_string(val.type);
        str += "\n";
        
        str += "Temperature::temp_properties_t::onSubdevice : ";
        str += std::to_string(val.onSubdevice);
        str += "\n";
        
        str += "Temperature::temp_properties_t::subdeviceId : ";
        str += std::to_string(val.subdeviceId);
        str += "\n";
        
        str += "Temperature::temp_properties_t::maxTemperature : ";
        str += std::to_string(val.maxTemperature);
        str += "\n";
        
        str += "Temperature::temp_properties_t::isCriticalTempSupported : ";
        str += std::to_string(val.isCriticalTempSupported);
        str += "\n";
        
        str += "Temperature::temp_properties_t::isThreshold1Supported : ";
        str += std::to_string(val.isThreshold1Supported);
        str += "\n";
        
        str += "Temperature::temp_properties_t::isThreshold2Supported : ";
        str += std::to_string(val.isThreshold2Supported);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Temperature::temp_threshold_t to std::string
    std::string to_string( const Temperature::temp_threshold_t val )
    {
        std::string str;
        
        str += "Temperature::temp_threshold_t::enableLowToHigh : ";
        str += std::to_string(val.enableLowToHigh);
        str += "\n";
        
        str += "Temperature::temp_threshold_t::enableHighToLow : ";
        str += std::to_string(val.enableHighToLow);
        str += "\n";
        
        str += "Temperature::temp_threshold_t::threshold : ";
        str += std::to_string(val.threshold);
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Temperature::temp_config_t to std::string
    std::string to_string( const Temperature::temp_config_t val )
    {
        std::string str;
        
        str += "Temperature::temp_config_t::stype : ";
        str += to_string(val.stype);
        str += "\n";
        
        str += "Temperature::temp_config_t::pNext : ";
        {
            std::stringstream ss;
            ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
            str += ss.str();
        }
        str += "\n";
        
        str += "Temperature::temp_config_t::enableCritical : ";
        str += std::to_string(val.enableCritical);
        str += "\n";
        
        str += "Temperature::temp_config_t::threshold1 : ";
        str += to_string(val.threshold1);
        str += "\n";
        
        str += "Temperature::temp_config_t::threshold2 : ";
        str += to_string(val.threshold2);
        str += "\n";

        return str;
    }

#if !defined(__GNUC__)
#pragma endregion
#endif
} // namespace zes
