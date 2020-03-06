/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_event.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Event
 *
 */
#include "ze_api.hpp"
#include "ze_singleton.h"

#define _STRING(s) #s
#define STRING(s) _STRING(s)

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    EventPool::EventPool( 
        event_pool_handle_t handle,                     ///< [in] handle of event pool object
        Driver* pDriver,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] descriptor of the event pool object
        ) :
        m_handle( handle ),
        m_pDriver( pDriver ),
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
    /// @brief Creates a pool for a set of event(s) for the driver
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - EventPool*: pointer handle of event pool object created
    /// 
    /// @throws result_t
    EventPool* __zecall
    EventPool::Create(
        Driver* pDriver,                                ///< [in] pointer to the driver instance
        const desc_t* desc,                             ///< [in] pointer to event pool descriptor
        uint32_t numDevices,                            ///< [in] number of device handles
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
            reinterpret_cast<ze_driver_handle_t>( pDriver->getHandle() ),
            reinterpret_cast<const ze_event_pool_desc_t*>( desc ),
            numDevices,
            hDevices.data(),
            &hEventPool ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::EventPool::Create" );

        EventPool* pEventPool = nullptr;

        try
        {
            pEventPool = new EventPool( reinterpret_cast<event_pool_handle_t>( hEventPool ), pDriver, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pEventPool;
            pEventPool = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::EventPool::Create" );
        }

        return pEventPool;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes an event pool object.
    /// 
    /// @details
    ///     - The application is responsible for destroying all event handles
    ///       created from the pool before destroying the pool itself
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the any event within the pool before it is
    ///       deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this event pool
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same event pool handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    EventPool::Destroy(
        EventPool* pEventPool                           ///< [in][release] pointer to event pool object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeEventPoolDestroy(
            reinterpret_cast<ze_event_pool_handle_t>( pEventPool->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::EventPool::Destroy" );

        delete pEventPool;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates an event on the device.
    /// 
    /// @details
    ///     - Multiple events cannot be created using the same location within the
    ///       same pool.
    ///     - The application may call this function from simultaneous threads.
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
    Event* __zecall
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
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Event::Create" );

        Event* pEvent = nullptr;

        try
        {
            pEvent = new Event( reinterpret_cast<event_handle_t>( hEvent ), pEventPool, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pEvent;
            pEvent = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::Event::Create" );
        }

        return pEvent;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Deletes an event object.
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the event before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this event
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same event handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clReleaseEvent**
    ///     - vkDestroyEvent
    /// 
    /// @throws result_t
    void __zecall
    Event::Destroy(
        Event* pEvent                                   ///< [in][release] pointer to event object to destroy
        )
    {
        auto result = static_cast<result_t>( ::zeEventDestroy(
            reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Event::Destroy" );

        delete pEvent;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Gets an IPC event pool handle for the specified event handle that can
    ///        be shared with another process.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - ipc_event_pool_handle_t: Returned IPC event handle
    /// 
    /// @throws result_t
    ipc_event_pool_handle_t __zecall
    EventPool::GetIpcHandle(
        void
        )
    {
        ze_ipc_event_pool_handle_t hIpc;

        auto result = static_cast<result_t>( ::zeEventPoolGetIpcHandle(
            reinterpret_cast<ze_event_pool_handle_t>( getHandle() ),
            &hIpc ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::EventPool::GetIpcHandle" );

        return *reinterpret_cast<ipc_event_pool_handle_t*>( &hIpc );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Opens an IPC event pool handle to retrieve an event pool handle from
    ///        another process.
    /// 
    /// @details
    ///     - The event handle in this process should not be freed with
    ///       ::zeEventPoolDestroy, but rather with ::zeEventPoolCloseIpcHandle.
    ///     - The application may call this function from simultaneous threads.
    /// 
    /// @returns
    ///     - EventPool*: pointer handle of event pool object created
    /// 
    /// @throws result_t
    EventPool* __zecall
    EventPool::OpenIpcHandle(
        Driver* pDriver,                                ///< [in] pointer to the driver to associate with the IPC event pool handle
        ipc_event_pool_handle_t pIpc                    ///< [in] IPC event handle
        )
    {
        ze_event_pool_handle_t hEventPool;

        auto result = static_cast<result_t>( ::zeEventPoolOpenIpcHandle(
            reinterpret_cast<ze_driver_handle_t>( pDriver->getHandle() ),
            *reinterpret_cast<ze_ipc_event_pool_handle_t*>( &pIpc ),
            &hEventPool ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::EventPool::OpenIpcHandle" );

        EventPool* pEventPool = nullptr;

        try
        {
            pEventPool = new EventPool( reinterpret_cast<event_pool_handle_t>( hEventPool ), pDriver, nullptr );
        }
        catch( std::bad_alloc& )
        {
            delete pEventPool;
            pEventPool = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::EventPool::OpenIpcHandle" );
        }

        return pEventPool;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Closes an IPC event handle in the current process.
    /// 
    /// @details
    ///     - Closes an IPC event handle by destroying events that were opened in
    ///       this process using ::zeEventPoolOpenIpcHandle.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same event pool handle.
    /// 
    /// @throws result_t
    void __zecall
    EventPool::CloseIpcHandle(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventPoolCloseIpcHandle(
            reinterpret_cast<ze_event_pool_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::EventPool::CloseIpcHandle" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends a signal of the event from the device into a command list.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **clSetUserEventStatus**
    ///     - vkCmdSetEvent
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendSignalEvent(
        Event* pEvent                                   ///< [in] pointer to the event
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendSignalEvent(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendSignalEvent" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Appends wait on event(s) on the device into a command list.
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendWaitOnEvents(
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        Event** ppEvents                                ///< [in][range(0, numEvents)] pointer to the events to wait on before
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
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendWaitOnEvents" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Signals a event from host.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - clSetUserEventStatus
    /// 
    /// @throws result_t
    void __zecall
    Event::HostSignal(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventHostSignal(
            reinterpret_cast<ze_event_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Event::HostSignal" );
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
    bool_t __zecall
    Event::HostSynchronize(
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                        ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::zeEventQueryStatus;
                                                        ///< if UINT32_MAX, then function will not return until complete or device
                                                        ///< is lost.
        )
    {
        auto result = static_cast<result_t>( ::zeEventHostSynchronize(
            reinterpret_cast<ze_event_handle_t>( getHandle() ),
            timeout ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Event::HostSynchronize" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Queries an event object's status.
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
    bool_t __zecall
    Event::QueryStatus(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventQueryStatus(
            reinterpret_cast<ze_event_handle_t>( getHandle() ) ) );

        if( result_t::NOT_READY == result )
            return 0; // false
        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Event::QueryStatus" );
        return 1; // true
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset an event back to not signaled state
    /// 
    /// @details
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - vkResetEvent
    /// 
    /// @throws result_t
    void __zecall
    CommandList::AppendEventReset(
        Event* pEvent                                   ///< [in] pointer to the event
        )
    {
        auto result = static_cast<result_t>( ::zeCommandListAppendEventReset(
            reinterpret_cast<ze_command_list_handle_t>( getHandle() ),
            reinterpret_cast<ze_event_handle_t>( pEvent->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::CommandList::AppendEventReset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reset an event back to not signaled state
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
    void __zecall
    Event::HostReset(
        void
        )
    {
        auto result = static_cast<result_t>( ::zeEventHostReset(
            reinterpret_cast<ze_event_handle_t>( getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Event::HostReset" );
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Query timestamp information associated with an event. Event must come
    ///        from an event pool that was created using
    ///        ::ZE_EVENT_POOL_FLAG_TIMESTAMP flag.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @throws result_t
    void __zecall
    Event::GetTimestamp(
        EventPool::event_timestamp_type_t timestampType,///< [in] specifies timestamp type to query for that is associated with
                                                        ///< hEvent.
        void* dstptr                                    ///< [in,out] pointer to memory for where timestamp will be written to. The
                                                        ///< size of timestamp is specified in the ::ze_event_timestamp_type_t
                                                        ///< definition.
        )
    {
        auto result = static_cast<result_t>( ::zeEventGetTimestamp(
            reinterpret_cast<ze_event_handle_t>( getHandle() ),
            static_cast<ze_event_timestamp_type_t>( timestampType ),
            dstptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Event::GetTimestamp" );
    }

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::desc_version_t to std::string
    std::string to_string( const EventPool::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case EventPool::desc_version_t::CURRENT:
            str = "EventPool::desc_version_t::CURRENT";
            break;

        default:
            str = "EventPool::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::flag_t to std::string
    std::string to_string( const EventPool::flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "DEFAULT   ";
        
        if( static_cast<uint32_t>(EventPool::flag_t::HOST_VISIBLE) & bits )
            str += "HOST_VISIBLE | ";
        
        if( static_cast<uint32_t>(EventPool::flag_t::IPC) & bits )
            str += "IPC | ";
        
        if( static_cast<uint32_t>(EventPool::flag_t::TIMESTAMP) & bits )
            str += "TIMESTAMP | ";

        return ( str.size() > 3 ) 
            ? "EventPool::flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "EventPool::flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::event_timestamp_type_t to std::string
    std::string to_string( const EventPool::event_timestamp_type_t val )
    {
        std::string str;

        switch( val )
        {
        case EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_GLOBAL_START:
            str = "EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_GLOBAL_START";
            break;

        case EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_GLOBAL_END:
            str = "EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_GLOBAL_END";
            break;

        case EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_CONTEXT_START:
            str = "EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_CONTEXT_START";
            break;

        case EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_CONTEXT_END:
            str = "EventPool::event_timestamp_type_t::EVENT_TIMESTAMP_CONTEXT_END";
            break;

        default:
            str = "EventPool::event_timestamp_type_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::desc_t to std::string
    std::string to_string( const EventPool::desc_t val )
    {
        std::string str;
        
        str += "EventPool::desc_t::version : ";
        str += to_string(val.version);
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
    /// @brief Converts Event::desc_version_t to std::string
    std::string to_string( const Event::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Event::desc_version_t::CURRENT:
            str = "Event::desc_version_t::CURRENT";
            break;

        default:
            str = "Event::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::scope_flag_t to std::string
    std::string to_string( const Event::scope_flag_t val )
    {
        const auto bits = static_cast<uint32_t>( val );

        std::string str;
        
        if( 0 == bits )
            str += "NONE   ";
        
        if( static_cast<uint32_t>(Event::scope_flag_t::SUBDEVICE) & bits )
            str += "SUBDEVICE | ";
        
        if( static_cast<uint32_t>(Event::scope_flag_t::DEVICE) & bits )
            str += "DEVICE | ";
        
        if( static_cast<uint32_t>(Event::scope_flag_t::HOST) & bits )
            str += "HOST | ";

        return ( str.size() > 3 ) 
            ? "Event::scope_flag_t::{ " + str.substr(0, str.size() - 3) + " }"
            : "Event::scope_flag_t::{ ? }";
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::desc_t to std::string
    std::string to_string( const Event::desc_t val )
    {
        std::string str;
        
        str += "Event::desc_t::version : ";
        str += to_string(val.version);
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

} // namespace ze
