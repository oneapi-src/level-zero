/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_driver.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs
 *
 */
#ifndef _ZE_DRIVER_HPP
#define _ZE_DRIVER_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_DRIVER_UUID_SIZE
/// @brief Maximum driver universal unique id (UUID) size in bytes
#define ZE_MAX_DRIVER_UUID_SIZE  16
#endif // ZE_MAX_DRIVER_UUID_SIZE

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Supported initialization flags
    enum class init_flag_t
    {
        NONE = 0,                                       ///< default behavior
        GPU_ONLY = ZE_BIT(0),                           ///< only initialize GPU drivers

    };

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
        );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Driver universal unique id (UUID)
    struct driver_uuid_t
    {
        uint8_t id[ZE_MAX_DRIVER_UUID_SIZE];            ///< Opaque data representing a driver UUID

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a driver instance handle
    class Driver
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported API versions
        /// 
        /// @details
        ///     - API versions contain major and minor attributes, use
        ///       ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION
        enum class api_version_t
        {
            _1_0 = ZE_MAKE_VERSION( 0, 91 ),                ///< 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_driver_properties_t
        enum class properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_driver_ipc_properties_t
        enum class ipc_properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_mem_alloc_desc_t
        enum class device_mem_alloc_desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported memory allocation flags
        enum class device_mem_alloc_flag_t
        {
            DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
            BIAS_CACHED = ZE_BIT( 0 ),                      ///< device should cache allocation
            BIAS_UNCACHED = ZE_BIT( 1 ),                    ///< device should not cache allocation (UC)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_host_mem_alloc_desc_t
        enum class host_mem_alloc_desc_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported host memory allocation flags
        enum class host_mem_alloc_flag_t
        {
            DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
            BIAS_CACHED = ZE_BIT( 0 ),                      ///< host should cache allocation
            BIAS_UNCACHED = ZE_BIT( 1 ),                    ///< host should not cache allocation (UC)
            BIAS_WRITE_COMBINED = ZE_BIT( 2 ),              ///< host memory should be allocated write-combined (WC)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_memory_allocation_properties_t
        enum class memory_allocation_properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory allocation type
        enum class memory_type_t
        {
            UNKNOWN = 0,                                    ///< the memory pointed to is of unknown type
            HOST,                                           ///< the memory pointed to is a host allocation
            DEVICE,                                         ///< the memory pointed to is a device allocation
            SHARED,                                         ///< the memory pointed to is a shared ownership allocation

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported IPC memory flags
        enum class ipc_memory_flag_t
        {
            NONE = 0,                                       ///< No special flags

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Driver properties queried using ::zeDriverGetProperties
        struct properties_t
        {
            properties_version_t version = properties_version_t::CURRENT;   ///< [in] ::ZE_DRIVER_PROPERTIES_VERSION_CURRENT
            driver_uuid_t uuid;                             ///< [out] universal unique identifier.
            uint32_t driverVersion;                         ///< [out] driver version
                                                            ///< The driver version is a non-zero, monotonically increasing value where
                                                            ///< higher values always indicate a more recent version.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief IPC properties queried using ::zeDriverGetIPCProperties
        struct ipc_properties_t
        {
            ipc_properties_version_t version = ipc_properties_version_t::CURRENT;   ///< [in] ::ZE_DRIVER_IPC_PROPERTIES_VERSION_CURRENT
            bool_t memsSupported;                           ///< [out] Supports passing memory allocations between processes. See
                                                            ///< ::::zeDriverGetMemIpcHandle.
            bool_t eventsSupported;                         ///< [out] Supports passing events between processes. See
                                                            ///< ::::zeEventPoolGetIpcHandle.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device mem alloc descriptor
        struct device_mem_alloc_desc_t
        {
            device_mem_alloc_desc_version_t version = device_mem_alloc_desc_version_t::CURRENT; ///< [in] ::ZE_DEVICE_MEM_ALLOC_DESC_VERSION_CURRENT
            device_mem_alloc_flag_t flags = device_mem_alloc_flag_t::DEFAULT;   ///< [in] flags specifying additional allocation controls
            uint32_t ordinal = 0;                           ///< [in] ordinal of the device's local memory to allocate from;
                                                            ///< must be less than the count returned from ::zeDeviceGetMemoryProperties

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Host mem alloc descriptor
        struct host_mem_alloc_desc_t
        {
            host_mem_alloc_desc_version_t version = host_mem_alloc_desc_version_t::CURRENT; ///< [in] ::ZE_HOST_MEM_ALLOC_DESC_VERSION_CURRENT
            host_mem_alloc_flag_t flags = host_mem_alloc_flag_t::DEFAULT;   ///< [in] flags specifying additional allocation controls

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory allocation properties queried using
        ///        ::zeDriverGetMemAllocProperties
        struct memory_allocation_properties_t
        {
            memory_allocation_properties_version_t version = memory_allocation_properties_version_t::CURRENT;   ///< [in] ::ZE_MEMORY_ALLOCATION_PROPERTIES_VERSION_CURRENT
            memory_type_t type;                             ///< [out] type of allocated memory
            uint64_t id;                                    ///< [out] identifier for this allocation

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        driver_handle_t m_handle;                       ///< [in] handle of the driver instance

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Driver( void ) = delete;
        Driver( 
            driver_handle_t handle                          ///< [in] handle of the driver instance
            );

        ~Driver( void ) = default;

        Driver( Driver const& other ) = delete;
        void operator=( Driver const& other ) = delete;

        Driver( Driver&& other ) = delete;
        void operator=( Driver&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }

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
        /// @throws result_t
        static void __zecall
        Get(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of driver instances.
                                                            ///< if count is zero, then the loader will update the value with the total
                                                            ///< number of drivers available.
                                                            ///< if count is non-zero, then the loader will only retrieve that number
                                                            ///< of drivers.
                                                            ///< if count is larger than the number of drivers available, then the
                                                            ///< loader will update the value with the correct number of drivers available.
            Driver** ppDrivers = nullptr                    ///< [in,out][optional][range(0, *pCount)] array of driver instance handles
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the API version supported by the specified driver
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - api_version_t: api version
        /// 
        /// @throws result_t
        api_version_t __zecall
        GetApiVersion(
            void
            );

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
        /// @throws result_t
        void __zecall
        GetProperties(
            properties_t* pDriverProperties                 ///< [in,out] query result for driver properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves IPC attributes of the driver
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - ipc_properties_t: query result for IPC properties
        /// 
        /// @throws result_t
        ipc_properties_t __zecall
        GetIPCProperties(
            void
            );

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
        /// @returns
        ///     - void*: pointer to extension function
        /// 
        /// @throws result_t
        void* __zecall
        GetExtensionFunctionAddress(
            const char* pFuncName                           ///< [in] name of the extension function
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Allocates memory that is shared between the host and one or more
        ///        devices
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
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - void*: pointer to shared allocation
        /// 
        /// @throws result_t
        void* __zecall
        AllocSharedMem(
            const device_mem_alloc_desc_t* device_desc,     ///< [in] pointer to device mem alloc descriptor
            const host_mem_alloc_desc_t* host_desc,         ///< [in] pointer to host mem alloc descriptor
            size_t size,                                    ///< [in] size in bytes to allocate
            size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
            Device* pDevice = nullptr                       ///< [in][optional] device handle to associate with
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Allocates memory specific to a device
        /// 
        /// @details
        ///     - A device allocation is owned by a specific device.
        ///     - In general, a device allocation may only be accessed by the device
        ///       that owns it.
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - void*: pointer to device allocation
        /// 
        /// @throws result_t
        void* __zecall
        AllocDeviceMem(
            const device_mem_alloc_desc_t* device_desc,     ///< [in] pointer to device mem alloc descriptor
            size_t size,                                    ///< [in] size in bytes to allocate
            size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
            Device* pDevice                                 ///< [in] pointer to the device
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Allocates host memory
        /// 
        /// @details
        ///     - A host allocation is owned by the host process.
        ///     - Host allocations are accessible by the host and all devices within the
        ///       driver driver.
        ///     - Host allocations are frequently used as staging areas to transfer data
        ///       to or from devices.
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - void*: pointer to host allocation
        /// 
        /// @throws result_t
        void* __zecall
        AllocHostMem(
            const host_mem_alloc_desc_t* host_desc,         ///< [in] pointer to host mem alloc descriptor
            size_t size,                                    ///< [in] size in bytes to allocate
            size_t alignment                                ///< [in] minimum alignment in bytes for the allocation
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Frees allocated host memory, device memory, or shared memory
        /// 
        /// @details
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the memory before it is freed
        ///     - The implementation of this function will immediately free all Host and
        ///       Device allocations associated with this memory
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same pointer.
        /// @throws result_t
        void __zecall
        FreeMem(
            void* ptr                                       ///< [in][release] pointer to memory to free
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves attributes of a memory allocation
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - Device*: device associated with this allocation
        /// 
        /// @throws result_t
        void __zecall
        GetMemAllocProperties(
            const void* ptr,                                ///< [in] memory pointer to query
            memory_allocation_properties_t* pMemAllocProperties,///< [in,out] query result for memory allocation properties
            Device** ppDevice = nullptr                     ///< [out][optional] device associated with this allocation
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves the base address and/or size of an allocation
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        /// @throws result_t
        void __zecall
        GetMemAddressRange(
            const void* ptr,                                ///< [in] memory pointer to query
            void** pBase = nullptr,                         ///< [in,out][optional] base address of the allocation
            size_t* pSize = nullptr                         ///< [in,out][optional] size of the allocation
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates an IPC memory handle for the specified allocation in the
        ///        sending process
        /// 
        /// @details
        ///     - Takes a pointer to the base of a device memory allocation and exports
        ///       it for use in another process.
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - ipc_mem_handle_t: Returned IPC memory handle
        /// 
        /// @throws result_t
        ipc_mem_handle_t __zecall
        GetMemIpcHandle(
            const void* ptr                                 ///< [in] pointer to the device memory allocation
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Opens an IPC memory handle to retrieve a device pointer in a receiving
        ///        process
        /// 
        /// @details
        ///     - Takes an IPC memory handle from a sending process and associates it
        ///       with a device pointer usable in this process.
        ///     - The device pointer in this process should not be freed with
        ///       ::zeDriverFreeMem, but rather with ::zeDriverCloseMemIpcHandle.
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - void*: pointer to device allocation in this process
        /// 
        /// @throws result_t
        void* __zecall
        OpenMemIpcHandle(
            Device* pDevice,                                ///< [in] pointer to the device to associate with the IPC memory handle
            ipc_mem_handle_t handle,                        ///< [in] IPC memory handle
            ipc_memory_flag_t flags                         ///< [in] flags controlling the operation
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes an IPC memory handle in a receiving process
        /// 
        /// @details
        ///     - Closes an IPC memory handle by unmapping memory that was opened in
        ///       this process using ::zeDriverOpenMemIpcHandle.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same pointer.
        /// @throws result_t
        void __zecall
        CloseMemIpcHandle(
            const void* ptr                                 ///< [in][release] pointer to device allocation in this process
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts init_flag_t to std::string
    std::string to_string( const init_flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts driver_uuid_t to std::string
    std::string to_string( const driver_uuid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::api_version_t to std::string
    std::string to_string( const Driver::api_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::properties_version_t to std::string
    std::string to_string( const Driver::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::properties_t to std::string
    std::string to_string( const Driver::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::ipc_properties_version_t to std::string
    std::string to_string( const Driver::ipc_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::ipc_properties_t to std::string
    std::string to_string( const Driver::ipc_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::device_mem_alloc_desc_version_t to std::string
    std::string to_string( const Driver::device_mem_alloc_desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::device_mem_alloc_flag_t to std::string
    std::string to_string( const Driver::device_mem_alloc_flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::device_mem_alloc_desc_t to std::string
    std::string to_string( const Driver::device_mem_alloc_desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::host_mem_alloc_desc_version_t to std::string
    std::string to_string( const Driver::host_mem_alloc_desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::host_mem_alloc_flag_t to std::string
    std::string to_string( const Driver::host_mem_alloc_flag_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::host_mem_alloc_desc_t to std::string
    std::string to_string( const Driver::host_mem_alloc_desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::memory_allocation_properties_version_t to std::string
    std::string to_string( const Driver::memory_allocation_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::memory_type_t to std::string
    std::string to_string( const Driver::memory_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::memory_allocation_properties_t to std::string
    std::string to_string( const Driver::memory_allocation_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::ipc_memory_flag_t to std::string
    std::string to_string( const Driver::ipc_memory_flag_t val );

} // namespace ze
#endif // defined(__cplusplus)
#endif // _ZE_DRIVER_HPP
