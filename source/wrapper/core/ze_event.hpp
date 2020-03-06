/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_event.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Event
 *
 */
#ifndef _ZE_EVENT_HPP
#define _ZE_EVENT_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for event pool
    class EventPool
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_event_pool_desc_t
        enum class desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported event pool creation flags
        enum class flag_t
        {
            DEFAULT = 0,                                    ///< signals and waits visible to the entire device and peer devices
            HOST_VISIBLE = ZE_BIT(0),                       ///< signals and waits are also visible to host
            IPC = ZE_BIT(1),                                ///< signals and waits may be shared across processes
            TIMESTAMP = ZE_BIT(2),                          ///< Indicates all events in pool will contain timestamp information that
                                                            ///< can be queried using ::zeEventGetTimestamp

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported timestamp types
        enum class event_timestamp_type_t
        {
            EVENT_TIMESTAMP_GLOBAL_START = 0,               ///< wall-clock time start in GPU clocks for event. Data is uint64_t.
            EVENT_TIMESTAMP_GLOBAL_END,                     ///< wall-clock time end in GPU clocks for event.Data is uint64_t.
            EVENT_TIMESTAMP_CONTEXT_START,                  ///< context time start in GPU clocks for event.  Only includes time while
                                                            ///< HW context is actively running on GPU. Data is uint64_t.
            EVENT_TIMESTAMP_CONTEXT_END,                    ///< context time end in GPU clocks for event.  Only includes time while HW
                                                            ///< context is actively running on GPU. Data is uint64_t.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event pool descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_EVENT_POOL_DESC_VERSION_CURRENT
            flag_t flags = flag_t::DEFAULT;                 ///< [in] creation flags
            uint32_t count;                                 ///< [in] number of events within the pool

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        event_pool_handle_t m_handle;                   ///< [in] handle of event pool object
        Driver* m_pDriver;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the event pool object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        EventPool( void ) = delete;
        EventPool( 
            event_pool_handle_t handle,                     ///< [in] handle of event pool object
            Driver* pDriver,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the event pool object
            );

        ~EventPool( void ) = default;

        EventPool( EventPool const& other ) = delete;
        void operator=( EventPool const& other ) = delete;

        EventPool( EventPool&& other ) = delete;
        void operator=( EventPool&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDriver( void ) const { return m_pDriver; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a pool for a set of event(s) for the driver
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - EventPool*: pointer handle of event pool object created
        /// 
        /// @throws result_t
        static EventPool* __zecall
        Create(
            Driver* pDriver,                                ///< [in] pointer to the driver instance
            const desc_t* desc,                             ///< [in] pointer to event pool descriptor
            uint32_t numDevices,                            ///< [in] number of device handles
            Device** ppDevices = nullptr                    ///< [in][optional][range(0, numDevices)] array of device handles which
                                                            ///< have visibility to the event pool.
                                                            ///< if nullptr, then event pool is visible to all devices supported by the
                                                            ///< driver instance.
            );

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
        /// @throws result_t
        static void __zecall
        Destroy(
            EventPool* pEventPool                           ///< [in][release] pointer to event pool object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Gets an IPC event pool handle for the specified event handle that can
        ///        be shared with another process.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - ipc_event_pool_handle_t: Returned IPC event handle
        /// 
        /// @throws result_t
        ipc_event_pool_handle_t __zecall
        GetIpcHandle(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Opens an IPC event pool handle to retrieve an event pool handle from
        ///        another process.
        /// 
        /// @details
        ///     - The event handle in this process should not be freed with
        ///       ::zeEventPoolDestroy, but rather with ::zeEventPoolCloseIpcHandle.
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - EventPool*: pointer handle of event pool object created
        /// 
        /// @throws result_t
        static EventPool* __zecall
        OpenIpcHandle(
            Driver* pDriver,                                ///< [in] pointer to the driver to associate with the IPC event pool handle
            ipc_event_pool_handle_t pIpc                    ///< [in] IPC event handle
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes an IPC event handle in the current process.
        /// 
        /// @details
        ///     - Closes an IPC event handle by destroying events that were opened in
        ///       this process using ::zeEventPoolOpenIpcHandle.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same event pool handle.
        /// @throws result_t
        void __zecall
        CloseIpcHandle(
            void
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for event
    class Event
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_event_desc_t
        enum class desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported event scope flags
        enum class scope_flag_t
        {
            NONE = 0,                                       ///< execution synchronization only; no cache hierarchies are flushed or
                                                            ///< invalidated
            SUBDEVICE = ZE_BIT(0),                          ///< cache hierarchies are flushed or invalidated sufficient for local
                                                            ///< sub-device access
            DEVICE = ZE_BIT(1),                             ///< cache hierarchies are flushed or invalidated sufficient for global
                                                            ///< device access and peer device access
            HOST = ZE_BIT(2),                               ///< cache hierarchies are flushed or invalidated sufficient for device and
                                                            ///< host access

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::ZE_EVENT_DESC_VERSION_CURRENT
            uint32_t index;                                 ///< [in] index of the event within the pool; must be less-than the count
                                                            ///< specified during pool creation
            scope_flag_t signal = scope_flag_t::NONE;       ///< [in] defines the scope of relevant cache hierarchies to flush on a
                                                            ///< signal action before the event is triggered
            scope_flag_t wait = scope_flag_t::NONE;         ///< [in] defines the scope of relevant cache hierarchies to invalidate on
                                                            ///< a wait action after the event is complete

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        event_handle_t m_handle;                        ///< [in] handle of event object
        EventPool* m_pEventPool;                        ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the event object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Event( void ) = delete;
        Event( 
            event_handle_t handle,                          ///< [in] handle of event object
            EventPool* pEventPool,                          ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the event object
            );

        ~Event( void ) = default;

        Event( Event const& other ) = delete;
        void operator=( Event const& other ) = delete;

        Event( Event&& other ) = delete;
        void operator=( Event&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getEventpool( void ) const { return m_pEventPool; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - Event*: pointer to handle of event object created
        /// 
        /// @throws result_t
        static Event* __zecall
        Create(
            EventPool* pEventPool,                          ///< [in] pointer to the event pool
            const desc_t* desc                              ///< [in] pointer to event descriptor
            );

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
        /// @throws result_t
        static void __zecall
        Destroy(
            Event* pEvent                                   ///< [in][release] pointer to event object to destroy
            );

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
        /// @throws result_t
        void __zecall
        HostSignal(
            void
            );

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
        /// @returns
        ///     - bool_t:'0' when RESULT_NOT_READY
        /// @throws result_t
        bool_t __zecall
        HostSynchronize(
            uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                            ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                            ///< if zero, then operates exactly like ::zeEventQueryStatus;
                                                            ///< if UINT32_MAX, then function will not return until complete or device
                                                            ///< is lost.
            );

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
        /// @returns
        ///     - bool_t:'0' when RESULT_NOT_READY
        /// @throws result_t
        bool_t __zecall
        QueryStatus(
            void
            );

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
        /// @throws result_t
        void __zecall
        HostReset(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Query timestamp information associated with an event. Event must come
        ///        from an event pool that was created using
        ///        ::ZE_EVENT_POOL_FLAG_TIMESTAMP flag.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetTimestamp(
            EventPool::event_timestamp_type_t timestampType,///< [in] specifies timestamp type to query for that is associated with
                                                            ///< hEvent.
            void* dstptr                                    ///< [in,out] pointer to memory for where timestamp will be written to. The
                                                            ///< size of timestamp is specified in the ::ze_event_timestamp_type_t
                                                            ///< definition.
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::desc_version_t to std::string
    std::string to_string( const EventPool::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::flag_t to std::string
    std::string to_string( const EventPool::flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::desc_t to std::string
    std::string to_string( const EventPool::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::event_timestamp_type_t to std::string
    std::string to_string( const EventPool::event_timestamp_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::desc_version_t to std::string
    std::string to_string( const Event::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::scope_flag_t to std::string
    std::string to_string( const Event::scope_flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::desc_t to std::string
    std::string to_string( const Event::desc_t val );

} // namespace ze
#endif // defined(__cplusplus)
#endif // _ZE_EVENT_HPP
