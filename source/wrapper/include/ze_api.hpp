/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_api.hpp
 *
 */
#ifndef _ZE_API_HPP
#define _ZE_API_HPP
#if defined(__cplusplus)
#pragma once

// C API headers
#include "ze_api.h"

// standard headers
#include <stdint.h>
#include <string.h>
#include <exception>
#include <tuple>
#include <vector>
#include <string>
#include <sstream>

// Intel 'oneAPI' Level-Zero API common types
#pragma region common
///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAKE_VERSION
/// @brief Generates generic 'oneAPI' API versions
#define ZE_MAKE_VERSION( _major, _minor )  (( _major << 16 )|( _minor & 0x0000ffff))
#endif // ZE_MAKE_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAJOR_VERSION
/// @brief Extracts 'oneAPI' API major version
#define ZE_MAJOR_VERSION( _ver )  ( _ver >> 16 )
#endif // ZE_MAJOR_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MINOR_VERSION
/// @brief Extracts 'oneAPI' API minor version
#define ZE_MINOR_VERSION( _ver )  ( _ver & 0x0000ffff )
#endif // ZE_MINOR_VERSION

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_APICALL
#if defined(_WIN32)
/// @brief Calling convention for all API functions
#define ZE_APICALL  __cdecl
#else
#define ZE_APICALL  
#endif // defined(_WIN32)
#endif // ZE_APICALL

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_APIEXPORT
#if defined(_WIN32)
/// @brief Microsoft-specific dllexport storage-class attribute
#define ZE_APIEXPORT  __declspec(dllexport)
#else
#define ZE_APIEXPORT  
#endif // defined(_WIN32)
#endif // ZE_APIEXPORT

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_DLLEXPORT
#if defined(_WIN32)
/// @brief Microsoft-specific dllexport storage-class attribute
#define ZE_DLLEXPORT  __declspec(dllexport)
#endif // defined(_WIN32)
#endif // ZE_DLLEXPORT

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_DLLEXPORT
#if __GNUC__ >= 4
/// @brief GCC-specific dllexport storage-class attribute
#define ZE_DLLEXPORT  __attribute__ ((visibility ("default")))
#else
#define ZE_DLLEXPORT  
#endif // __GNUC__ >= 4
#endif // ZE_DLLEXPORT

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_IPC_HANDLE_SIZE
/// @brief Maximum IPC handle size
#define ZE_MAX_IPC_HANDLE_SIZE  64
#endif // ZE_MAX_IPC_HANDLE_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_BIT
/// @brief Generic macro for enumerator bit masks
#define ZE_BIT( _i )  ( 1 << _i )
#endif // ZE_BIT

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief compiler-independent type
    using bool_t = uint8_t;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of a driver instance
    class Driver;
    struct _driver_handle_t;
    using driver_handle_t = _driver_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's device object
    class Device;
    struct _device_handle_t;
    using device_handle_t = _device_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's context object
    class Context;
    struct _context_handle_t;
    using context_handle_t = _context_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's command queue object
    class CommandQueue;
    struct _command_queue_handle_t;
    using command_queue_handle_t = _command_queue_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's command list object
    class CommandList;
    struct _command_list_handle_t;
    using command_list_handle_t = _command_list_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's fence object
    class Fence;
    struct _fence_handle_t;
    using fence_handle_t = _fence_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's event pool object
    class EventPool;
    struct _event_pool_handle_t;
    using event_pool_handle_t = _event_pool_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's event object
    class Event;
    struct _event_handle_t;
    using event_handle_t = _event_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's image object
    class Image;
    struct _image_handle_t;
    using image_handle_t = _image_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's module object
    class Module;
    struct _module_handle_t;
    using module_handle_t = _module_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of module's build log object
    class ModuleBuildLog;
    struct _module_build_log_handle_t;
    using module_build_log_handle_t = _module_build_log_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's kernel object
    class Kernel;
    struct _kernel_handle_t;
    using kernel_handle_t = _kernel_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of driver's sampler object
    class Sampler;
    struct _sampler_handle_t;
    using sampler_handle_t = _sampler_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Handle of physical memory object
    class PhysicalMem;
    struct _physical_mem_handle_t;
    using physical_mem_handle_t = _physical_mem_handle_t*;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief IPC handle to a memory allocation
    struct ipc_mem_handle_t
    {
        char data[ZE_MAX_IPC_HANDLE_SIZE];              ///< [out] Opaque data representing an IPC handle

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief IPC handle to a event pool allocation
    struct ipc_event_pool_handle_t
    {
        char data[ZE_MAX_IPC_HANDLE_SIZE];              ///< [out] Opaque data representing an IPC handle

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Defines Return/Error codes
    enum class result_t : uint32_t
    {
        SUCCESS = 0,                                    ///< [Core] success
        NOT_READY = 1,                                  ///< [Core] synchronization primitive not signaled
        ERROR_DEVICE_LOST = 0x70000001,                 ///< [Core] device hung, reset, was removed, or driver update occurred
        ERROR_OUT_OF_HOST_MEMORY = 0x70000002,          ///< [Core] insufficient host memory to satisfy call
        ERROR_OUT_OF_DEVICE_MEMORY = 0x70000003,        ///< [Core] insufficient device memory to satisfy call
        ERROR_MODULE_BUILD_FAILURE = 0x70000004,        ///< [Core] error occurred when building module, see build log for details
        ERROR_MODULE_LINK_FAILURE = 0x70000005,         ///< [Core] error occurred when linking modules, see build log for details
        ERROR_INSUFFICIENT_PERMISSIONS = 0x70010000,    ///< [Sysman] access denied due to permission level
        ERROR_NOT_AVAILABLE = 0x70010001,               ///< [Sysman] resource already in use and simultaneous access not allowed
                                                        ///< or resource was removed
        ERROR_DEPENDENCY_UNAVAILABLE = 0x70020000,      ///< [Tools] external required dependency is unavailable or missing
        ERROR_UNINITIALIZED = 0x78000001,               ///< [Validation] driver is not initialized
        ERROR_UNSUPPORTED_VERSION = 0x78000002,         ///< [Validation] generic error code for unsupported versions
        ERROR_UNSUPPORTED_FEATURE = 0x78000003,         ///< [Validation] generic error code for unsupported features
        ERROR_INVALID_ARGUMENT = 0x78000004,            ///< [Validation] generic error code for invalid arguments
        ERROR_INVALID_NULL_HANDLE = 0x78000005,         ///< [Validation] handle argument is not valid
        ERROR_HANDLE_OBJECT_IN_USE = 0x78000006,        ///< [Validation] object pointed to by handle still in-use by device
        ERROR_INVALID_NULL_POINTER = 0x78000007,        ///< [Validation] pointer argument may not be nullptr
        ERROR_INVALID_SIZE = 0x78000008,                ///< [Validation] size argument is invalid (e.g., must not be zero)
        ERROR_UNSUPPORTED_SIZE = 0x78000009,            ///< [Validation] size argument is not supported by the device (e.g., too
                                                        ///< large)
        ERROR_UNSUPPORTED_ALIGNMENT = 0x7800000a,       ///< [Validation] alignment argument is not supported by the device (e.g.,
                                                        ///< too small)
        ERROR_INVALID_SYNCHRONIZATION_OBJECT = 0x7800000b,  ///< [Validation] synchronization object in invalid state
        ERROR_INVALID_ENUMERATION = 0x7800000c,         ///< [Validation] enumerator argument is not valid
        ERROR_UNSUPPORTED_ENUMERATION = 0x7800000d,     ///< [Validation] enumerator argument is not supported by the device
        ERROR_UNSUPPORTED_IMAGE_FORMAT = 0x7800000e,    ///< [Validation] image format is not supported by the device
        ERROR_INVALID_NATIVE_BINARY = 0x7800000f,       ///< [Validation] native binary is not supported by the device
        ERROR_INVALID_GLOBAL_NAME = 0x78000010,         ///< [Validation] global variable is not found in the module
        ERROR_INVALID_KERNEL_NAME = 0x78000011,         ///< [Validation] kernel name is not found in the module
        ERROR_INVALID_FUNCTION_NAME = 0x78000012,       ///< [Validation] function name is not found in the module
        ERROR_INVALID_GROUP_SIZE_DIMENSION = 0x78000013,///< [Validation] group size dimension is not valid for the kernel or
                                                        ///< device
        ERROR_INVALID_GLOBAL_WIDTH_DIMENSION = 0x78000014,  ///< [Validation] global width dimension is not valid for the kernel or
                                                        ///< device
        ERROR_INVALID_KERNEL_ARGUMENT_INDEX = 0x78000015,   ///< [Validation] kernel argument index is not valid for kernel
        ERROR_INVALID_KERNEL_ARGUMENT_SIZE = 0x78000016,///< [Validation] kernel argument size does not match kernel
        ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE = 0x78000017,  ///< [Validation] value of kernel attribute is not valid for the kernel or
                                                        ///< device
        ERROR_INVALID_MODULE_UNLINKED = 0x78000018,     ///< [Validation] module with imports needs to be linked before kernels can
                                                        ///< be created from it.
        ERROR_INVALID_COMMAND_LIST_TYPE = 0x78000019,   ///< [Validation] command list type does not match command queue type
        ERROR_OVERLAPPING_REGIONS = 0x7800001a,         ///< [Validation] copy operations do not support overlapping regions of
                                                        ///< memory
        ERROR_UNKNOWN = 0x7ffffffe,                     ///< [Core] unknown or internal error
        FORCE_UINT32 = 0x7fffffff

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Defines structure types
    enum class structure_type_t : uint32_t
    {
        DRIVER_PROPERTIES = 0x1,                        ///< ::ze_driver_properties_t
        DRIVER_IPC_PROPERTIES = 0x2,                    ///< ::ze_driver_ipc_properties_t
        DEVICE_PROPERTIES = 0x3,                        ///< ::ze_device_properties_t
        DEVICE_COMPUTE_PROPERTIES = 0x4,                ///< ::ze_device_compute_properties_t
        DEVICE_MODULE_PROPERTIES = 0x5,                 ///< ::ze_device_module_properties_t
        COMMAND_QUEUE_GROUP_PROPERTIES = 0x6,           ///< ::ze_command_queue_group_properties_t
        DEVICE_MEMORY_PROPERTIES = 0x7,                 ///< ::ze_device_memory_properties_t
        DEVICE_MEMORY_ACCESS_PROPERTIES = 0x8,          ///< ::ze_device_memory_access_properties_t
        DEVICE_CACHE_PROPERTIES = 0x9,                  ///< ::ze_device_cache_properties_t
        DEVICE_IMAGE_PROPERTIES = 0xa,                  ///< ::ze_device_image_properties_t
        DEVICE_P2P_PROPERTIES = 0xb,                    ///< ::ze_device_p2p_properties_t
        DEVICE_EXTERNAL_MEMORY_PROPERTIES = 0xc,        ///< ::ze_device_external_memory_properties_t
        CONTEXT_DESC = 0xd,                             ///< ::ze_context_desc_t
        COMMAND_QUEUE_DESC = 0xe,                       ///< ::ze_command_queue_desc_t
        COMMAND_LIST_DESC = 0xf,                        ///< ::ze_command_list_desc_t
        EVENT_POOL_DESC = 0x10,                         ///< ::ze_event_pool_desc_t
        EVENT_DESC = 0x11,                              ///< ::ze_event_desc_t
        FENCE_DESC = 0x12,                              ///< ::ze_fence_desc_t
        IMAGE_DESC = 0x13,                              ///< ::ze_image_desc_t
        IMAGE_PROPERTIES = 0x14,                        ///< ::ze_image_properties_t
        DEVICE_MEM_ALLOC_DESC = 0x15,                   ///< ::ze_device_mem_alloc_desc_t
        HOST_MEM_ALLOC_DESC = 0x16,                     ///< ::ze_host_mem_alloc_desc_t
        MEMORY_ALLOCATION_PROPERTIES = 0x17,            ///< ::ze_memory_allocation_properties_t
        EXTERNAL_MEMORY_EXPORT_DESC = 0x18,             ///< ::ze_external_memory_export_desc_t
        EXTERNAL_MEMORY_IMPORT_FD = 0x19,               ///< ::ze_external_memory_import_fd_t
        EXTERNAL_MEMORY_EXPORT_FD = 0x1a,               ///< ::ze_external_memory_export_fd_t
        MODULE_DESC = 0x1b,                             ///< ::ze_module_desc_t
        MODULE_PROPERTIES = 0x1c,                       ///< ::ze_module_properties_t
        KERNEL_DESC = 0x1d,                             ///< ::ze_kernel_desc_t
        KERNEL_PROPERTIES = 0x1e,                       ///< ::ze_kernel_properties_t
        SAMPLER_DESC = 0x1f,                            ///< ::ze_sampler_desc_t
        PHYSICAL_MEM_DESC = 0x20,                       ///< ::ze_physical_mem_desc_t
        RAYTRACING_MEM_ALLOC_EXT_DESC = 0x00010001,     ///< ::ze_raytracing_mem_alloc_ext_desc_t
        FORCE_UINT32 = 0x7fffffff

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief External memory type flags
    struct external_memory_type_flags_t
    {
        uint32_t value;
        external_memory_type_flags_t() : value(0) {}
        external_memory_type_flags_t( const uint32_t v ) : value(v) {}
        operator uint32_t() const { return value; }
    };

    enum external_memory_type_flag_t
    {
        EXTERNAL_MEMORY_TYPE_FLAG_OPAQUE_FD = ZE_BIT(0),///< an opaque POSIX file descriptor handle
        EXTERNAL_MEMORY_TYPE_FLAG_DMA_BUF = ZE_BIT(1),  ///< a file descriptor handle for a Linux dma_buf
        EXTERNAL_MEMORY_TYPE_FLAG_FORCE_UINT32 = 0x7fffffff

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Base for all properties types
    struct base_properties_t
    {
        structure_type_t stype;                         ///< [in] type of this structure
        void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Base for all descriptor types
    struct base_desc_t
    {
        structure_type_t stype;                         ///< [in] type of this structure
        const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Forces driver to only report devices (and sub-devices) as specified by
    ///        values

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Forces driver to report devices from lowest to highest PCI bus ID

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Forces all shared allocations into device memory

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ipc_mem_handle_t to std::string
    std::string to_string( const ipc_mem_handle_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ipc_event_pool_handle_t to std::string
    std::string to_string( const ipc_event_pool_handle_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts result_t to std::string
    std::string to_string( const result_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts structure_type_t to std::string
    std::string to_string( const structure_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts external_memory_type_flags_t to std::string
    std::string to_string( const external_memory_type_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts base_properties_t to std::string
    std::string to_string( const base_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts base_desc_t to std::string
    std::string to_string( const base_desc_t val );

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    class exception_t : public std::exception
    {
    protected:
        static std::string formatted( const result_t, const char*, const char*, const char* );

        const std::string _msg;
        const result_t _result;

    public:
        exception_t() = delete;

        exception_t( const result_t result, const char* file, const char* line, const char* func )
            : std::exception(),
            _msg( formatted(result, file, line, func) ),
            _result(result)
        {
        }

        const char* what() const noexcept { return _msg.c_str(); }
        result_t value() const noexcept { return _result; }
    };

} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero APIs
#pragma region driver
///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_DRIVER_UUID_SIZE
/// @brief Maximum driver universal unique id (UUID) size in bytes
#define ZE_MAX_DRIVER_UUID_SIZE  16
#endif // ZE_MAX_DRIVER_UUID_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_EXTENSION_NAME
/// @brief Maximum extension name string size
#define ZE_MAX_EXTENSION_NAME  256
#endif // ZE_MAX_EXTENSION_NAME

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Supported initialization flags
    struct init_flags_t
    {
        uint32_t value;
        init_flags_t() : value(0) {}
        init_flags_t( const uint32_t v ) : value(v) {}
        operator uint32_t() const { return value; }
    };

    enum init_flag_t
    {
        INIT_FLAG_GPU_ONLY = ZE_BIT(0),                 ///< only initialize GPU drivers
        INIT_FLAG_FORCE_UINT32 = 0x7fffffff

    };

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
        );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Driver universal unique id (UUID)
    struct driver_uuid_t
    {
        uint8_t id[ZE_MAX_DRIVER_UUID_SIZE];            ///< [out] opaque data representing a driver UUID

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
        enum class api_version_t : uint32_t
        {
            _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
            CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported IPC property flags
        struct ipc_property_flags_t
        {
            uint32_t value;
            ipc_property_flags_t() : value(0) {}
            ipc_property_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum ipc_property_flag_t
        {
            IPC_PROPERTY_FLAG_MEMORY = ZE_BIT(0),           ///< Supports passing memory allocations between processes. See
                                                            ///< ::zeMemGetIpcHandle.
            IPC_PROPERTY_FLAG_EVENT_POOL = ZE_BIT(1),       ///< Supports passing event pools between processes. See
                                                            ///< ::zeEventPoolGetIpcHandle.
            IPC_PROPERTY_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Driver properties queried using ::zeDriverGetProperties
        struct properties_t
        {
            structure_type_t stype = structure_type_t::DRIVER_PROPERTIES;   ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            driver_uuid_t uuid;                             ///< [out] universal unique identifier.
            uint32_t driverVersion;                         ///< [out] driver version
                                                            ///< The driver version is a non-zero, monotonically increasing value where
                                                            ///< higher values always indicate a more recent version.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief IPC properties queried using ::zeDriverGetIpcProperties
        struct ipc_properties_t
        {
            structure_type_t stype = structure_type_t::DRIVER_IPC_PROPERTIES;   ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            ipc_property_flags_t flags;                     ///< [out] 0 (none) or a valid combination of ::ze_ipc_property_flag_t

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Extension properties queried using ::zeDriverGetExtensionProperties
        struct extension_properties_t
        {
            char name[ZE_MAX_EXTENSION_NAME];               ///< [out] extension name
            uint32_t version;                               ///< [out] extension version using ::ZE_MAKE_VERSION

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
        /// @throws result_t
        static void ZE_APICALL
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
        api_version_t ZE_APICALL
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
        void ZE_APICALL
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
        ipc_properties_t ZE_APICALL
        GetIpcProperties(
            void
            );

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
        /// @throws result_t
        void ZE_APICALL
        GetExtensionProperties(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of extension properties.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of extension properties available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< extension properties.
                                                            ///< if count is larger than the number of extension properties available,
                                                            ///< then the driver will update the value with the correct number of
                                                            ///< extension properties available.
            extension_properties_t* pExtensionProperties = nullptr  ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                            ///< extension properties
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts init_flags_t to std::string
    std::string to_string( const init_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts driver_uuid_t to std::string
    std::string to_string( const driver_uuid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::api_version_t to std::string
    std::string to_string( const Driver::api_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::properties_t to std::string
    std::string to_string( const Driver::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::ipc_property_flags_t to std::string
    std::string to_string( const Driver::ipc_property_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::ipc_properties_t to std::string
    std::string to_string( const Driver::ipc_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Driver::extension_properties_t to std::string
    std::string to_string( const Driver::extension_properties_t val );

} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero APIs for Device
#pragma region device
///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_DEVICE_UUID_SIZE
/// @brief Maximum device universal unique id (UUID) size in bytes
#define ZE_MAX_DEVICE_UUID_SIZE  16
#endif // ZE_MAX_DEVICE_UUID_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_DEVICE_NAME
/// @brief Maximum device name string size
#define ZE_MAX_DEVICE_NAME  256
#endif // ZE_MAX_DEVICE_NAME

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_SUBGROUPSIZE_COUNT
/// @brief Maximum number of subgroup sizes supported.
#define ZE_SUBGROUPSIZE_COUNT  8
#endif // ZE_SUBGROUPSIZE_COUNT

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_NATIVE_KERNEL_UUID_SIZE
/// @brief Maximum native kernel universal unique id (UUID) size in bytes
#define ZE_MAX_NATIVE_KERNEL_UUID_SIZE  16
#endif // ZE_MAX_NATIVE_KERNEL_UUID_SIZE

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Device universal unique id (UUID)
    struct device_uuid_t
    {
        uint8_t id[ZE_MAX_DEVICE_UUID_SIZE];            ///< [out] opaque data representing a device UUID

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a device
    class Device
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported device types
        enum class type_t : uint32_t
        {
            GPU = 1,                                        ///< Graphics Processing Unit
            CPU = 2,                                        ///< Central Processing Unit
            FPGA = 3,                                       ///< Field Programmable Gate Array
            MCA = 4,                                        ///< Memory Copy Accelerator
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported device property flags
        struct property_flags_t
        {
            uint32_t value;
            property_flags_t() : value(0) {}
            property_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum property_flag_t
        {
            PROPERTY_FLAG_INTEGRATED = ZE_BIT(0),           ///< Device is integrated with the Host.
            PROPERTY_FLAG_SUBDEVICE = ZE_BIT(1),            ///< Device handle used for query represents a sub-device.
            PROPERTY_FLAG_ECC = ZE_BIT(2),                  ///< Device supports error correction memory access.
            PROPERTY_FLAG_ONDEMANDPAGING = ZE_BIT(3),       ///< Device supports on-demand page-faulting.
            PROPERTY_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported device module flags
        struct module_flags_t
        {
            uint32_t value;
            module_flags_t() : value(0) {}
            module_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum module_flag_t
        {
            MODULE_FLAG_FP16 = ZE_BIT(0),                   ///< Device supports 16-bit floating-point operations
            MODULE_FLAG_FP64 = ZE_BIT(1),                   ///< Device supports 64-bit floating-point operations
            MODULE_FLAG_INT64_ATOMICS = ZE_BIT(2),          ///< Device supports 64-bit atomic operations
            MODULE_FLAG_DP4A = ZE_BIT(3),                   ///< Device supports four component dot product and accumulate operations
            MODULE_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported floating-Point capability flags
        struct fp_flags_t
        {
            uint32_t value;
            fp_flags_t() : value(0) {}
            fp_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum fp_flag_t
        {
            FP_FLAG_DENORM = ZE_BIT(0),                     ///< Supports denorms
            FP_FLAG_INF_NAN = ZE_BIT(1),                    ///< Supports INF and quiet NaNs
            FP_FLAG_ROUND_TO_NEAREST = ZE_BIT(2),           ///< Supports rounding to nearest even rounding mode
            FP_FLAG_ROUND_TO_ZERO = ZE_BIT(3),              ///< Supports rounding to zero.
            FP_FLAG_ROUND_TO_INF = ZE_BIT(4),               ///< Supports rounding to both positive and negative INF.
            FP_FLAG_FMA = ZE_BIT(5),                        ///< Supports IEEE754-2008 fused multiply-add.
            FP_FLAG_ROUNDED_DIVIDE_SQRT = ZE_BIT(6),        ///< Supports rounding as defined by IEEE754 for divide and sqrt
                                                            ///< operations.
            FP_FLAG_SOFT_FLOAT = ZE_BIT(7),                 ///< Uses software implementation for basic floating-point operations.
            FP_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command queue group property flags
        struct command_queue_group_property_flags_t
        {
            uint32_t value;
            command_queue_group_property_flags_t() : value(0) {}
            command_queue_group_property_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum command_queue_group_property_flag_t
        {
            COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE = ZE_BIT(0),  ///< Command queue group supports enqueing compute commands.
            COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COPY = ZE_BIT(1), ///< Command queue group supports enqueing copy commands.
            COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COOPERATIVE_KERNELS = ZE_BIT(2),  ///< Command queue group supports cooperative kernels.
                                                            ///< See ::zeCommandListAppendLaunchCooperativeKernel for more details.
            COMMAND_QUEUE_GROUP_PROPERTY_FLAG_METRICS = ZE_BIT(3),  ///< Command queue groups supports metric streamers and queries.
            COMMAND_QUEUE_GROUP_PROPERTY_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported device memory property flags
        struct memory_property_flags_t
        {
            uint32_t value;
            memory_property_flags_t() : value(0) {}
            memory_property_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum memory_property_flag_t
        {
            MEMORY_PROPERTY_FLAG_TBD = ZE_BIT(0),           ///< reserved for future use
            MEMORY_PROPERTY_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory access capability flags
        /// 
        /// @details
        ///     - Supported access capabilities for different types of memory
        ///       allocations
        struct memory_access_cap_flags_t
        {
            uint32_t value;
            memory_access_cap_flags_t() : value(0) {}
            memory_access_cap_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum memory_access_cap_flag_t
        {
            MEMORY_ACCESS_CAP_FLAG_RW = ZE_BIT(0),          ///< Supports load/store access
            MEMORY_ACCESS_CAP_FLAG_ATOMIC = ZE_BIT(1),      ///< Supports atomic access
            MEMORY_ACCESS_CAP_FLAG_CONCURRENT = ZE_BIT(2),  ///< Supports concurrent access
            MEMORY_ACCESS_CAP_FLAG_CONCURRENT_ATOMIC = ZE_BIT(3),   ///< Supports concurrent atomic access
            MEMORY_ACCESS_CAP_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported cache control property flags
        struct cache_property_flags_t
        {
            uint32_t value;
            cache_property_flags_t() : value(0) {}
            cache_property_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum cache_property_flag_t
        {
            CACHE_PROPERTY_FLAG_USER_CONTROL = ZE_BIT(0),   ///< Device support User Cache Control (i.e. SLM section vs Generic Cache)
            CACHE_PROPERTY_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported device peer-to-peer property flags
        struct p2p_property_flags_t
        {
            uint32_t value;
            p2p_property_flags_t() : value(0) {}
            p2p_property_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum p2p_property_flag_t
        {
            P2P_PROPERTY_FLAG_ACCESS = ZE_BIT(0),           ///< Device supports access between peer devices.
            P2P_PROPERTY_FLAG_ATOMICS = ZE_BIT(1),          ///< Device supports atomics between peer devices.
            P2P_PROPERTY_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device properties queried using ::zeDeviceGetProperties
        struct properties_t
        {
            structure_type_t stype = structure_type_t::DEVICE_PROPERTIES;   ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            type_t type;                                    ///< [out] generic device type
            uint32_t vendorId;                              ///< [out] vendor id from PCI configuration
            uint32_t deviceId;                              ///< [out] device id from PCI configuration
            property_flags_t flags;                         ///< [out] 0 (none) or a valid combination of ::ze_device_property_flag_t
            uint32_t subdeviceId;                           ///< [out] sub-device id. Only valid if ::ZE_DEVICE_PROPERTY_FLAG_SUBDEVICE
                                                            ///< is set.
            uint32_t coreClockRate;                         ///< [out] Clock rate for device core.
            uint64_t maxMemAllocSize;                       ///< [out] Maximum memory allocation size.
            uint32_t maxHardwareContexts;                   ///< [out] Maximum number of logical hardware contexts.
            uint32_t maxCommandQueuePriority;               ///< [out] Maximum priority for command queues. Higher value is higher
                                                            ///< priority.
            uint32_t numThreadsPerEU;                       ///< [out] Number of threads per EU.
            uint32_t physicalEUSimdWidth;                   ///< [out] The physical EU simd width.
            uint32_t numEUsPerSubslice;                     ///< [out] Number of EUs per sub-slice.
            uint32_t numSubslicesPerSlice;                  ///< [out] Number of sub-slices per slice.
            uint32_t numSlices;                             ///< [out] Number of slices.
            uint64_t timerResolution;                       ///< [out] Returns the resolution of device timer in nanoseconds used for
                                                            ///< profiling, timestamps, etc.
            uint32_t timestampValidBits;                    ///< [out] Returns the number of valid bits in the timestamp value.
            uint32_t kernelTimestampValidBits;              ///< [out] Returns the number of valid bits in the kernel timestamp values
            device_uuid_t uuid;                             ///< [out] universal unique identifier. Note: Subdevices will have their
                                                            ///< own uuid.
            char name[ZE_MAX_DEVICE_NAME];                  ///< [out] Device name

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device thread identifier.
        struct thread_t
        {
            uint32_t slice;                                 ///< [in,out] the slice number.
                                                            ///< Must be UINT32_MAX (all) or less than ::ze_device_properties_t.numSlices.
            uint32_t subslice;                              ///< [in,out] the sub-slice number within its slice.
                                                            ///< Must be UINT32_MAX (all) or less than ::ze_device_properties_t.numSubslicesPerSlice.
            uint32_t eu;                                    ///< [in,out] the EU number within its sub-slice.
                                                            ///< Must be UINT32_MAX (all) or less than ::ze_device_properties_t.numEUsPerSubslice.
            uint32_t thread;                                ///< [in,out] the thread number within its EU.
                                                            ///< Must be UINT32_MAX (all) or less than ::ze_device_properties_t.numThreadsPerEU.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device compute properties queried using ::zeDeviceGetComputeProperties
        struct compute_properties_t
        {
            structure_type_t stype = structure_type_t::DEVICE_COMPUTE_PROPERTIES;   ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            uint32_t maxTotalGroupSize;                     ///< [out] Maximum items per compute group. (groupSizeX * groupSizeY *
                                                            ///< groupSizeZ) <= maxTotalGroupSize
            uint32_t maxGroupSizeX;                         ///< [out] Maximum items for X dimension in group
            uint32_t maxGroupSizeY;                         ///< [out] Maximum items for Y dimension in group
            uint32_t maxGroupSizeZ;                         ///< [out] Maximum items for Z dimension in group
            uint32_t maxGroupCountX;                        ///< [out] Maximum groups that can be launched for x dimension
            uint32_t maxGroupCountY;                        ///< [out] Maximum groups that can be launched for y dimension
            uint32_t maxGroupCountZ;                        ///< [out] Maximum groups that can be launched for z dimension
            uint32_t maxSharedLocalMemory;                  ///< [out] Maximum shared local memory per group.
            uint32_t numSubGroupSizes;                      ///< [out] Number of subgroup sizes supported. This indicates number of
                                                            ///< entries in subGroupSizes.
            uint32_t subGroupSizes[ZE_SUBGROUPSIZE_COUNT];  ///< [out] Size group sizes supported.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Native kernel universal unique id (UUID)
        struct native_kernel_uuid_t
        {
            uint8_t id[ZE_MAX_NATIVE_KERNEL_UUID_SIZE];     ///< [out] opaque data representing a native kernel UUID

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device module properties queried using ::zeDeviceGetModuleProperties
        struct module_properties_t
        {
            structure_type_t stype = structure_type_t::DEVICE_MODULE_PROPERTIES;///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            uint32_t spirvVersionSupported;                 ///< [out] Maximum supported SPIR-V version.
                                                            ///< Returns zero if SPIR-V is not supported.
                                                            ///< Contains major and minor attributes, use ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION.
            module_flags_t flags;                           ///< [out] 0 or a valid combination of ::ze_device_module_flag_t
            fp_flags_t fp16flags;                           ///< [out] Capabilities for half-precision floating-point operations.
                                                            ///< returns 0 (if ::ZE_DEVICE_MODULE_FLAG_FP16 is not set) or a
                                                            ///< combination of ::ze_device_fp_flag_t.
            fp_flags_t fp32flags;                           ///< [out] Capabilities for single-precision floating-point operations.
                                                            ///< returns a combination of ::ze_device_fp_flag_t.
            fp_flags_t fp64flags;                           ///< [out] Capabilities for double-precision floating-point operations.
                                                            ///< returns 0 (if ::ZE_DEVICE_MODULE_FLAG_FP64 is not set) or a
                                                            ///< combination of ::ze_device_fp_flag_t.
            uint32_t maxArgumentsSize;                      ///< [out] Maximum kernel argument size that is supported.
            uint32_t printfBufferSize;                      ///< [out] Maximum size of internal buffer that holds output of printf
                                                            ///< calls from kernel.
            native_kernel_uuid_t nativeKernelSupported;     ///< [out] Compatibility UUID of supported native kernel.
                                                            ///< UUID may or may not be the same across driver release, devices, or
                                                            ///< operating systems.
                                                            ///< Application is responsible for ensuring UUID matches before creating
                                                            ///< module using
                                                            ///< previously created native kernel.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Command queue group properties queried using
        ///        ::zeDeviceGetCommandQueueGroupProperties
        struct command_queue_group_properties_t
        {
            structure_type_t stype = structure_type_t::COMMAND_QUEUE_GROUP_PROPERTIES;  ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            command_queue_group_property_flags_t flags;     ///< [out] 0 (none) or a valid combination of
                                                            ///< ::ze_command_queue_group_property_flag_t
            size_t maxMemoryFillPatternSize;                ///< [out] maximum `pattern_size` supported by command queue group.
                                                            ///< See ::zeCommandListAppendMemoryFill for more details.
            uint32_t numQueues;                             ///< [out] the number of physical command queues within the group.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device local memory properties queried using
        ///        ::zeDeviceGetMemoryProperties
        struct memory_properties_t
        {
            structure_type_t stype = structure_type_t::DEVICE_MEMORY_PROPERTIES;///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            memory_property_flags_t flags;                  ///< [out] 0 (none) or a valid combination of
                                                            ///< ::ze_device_memory_property_flag_t
            uint32_t maxClockRate;                          ///< [out] Maximum clock rate for device memory.
            uint32_t maxBusWidth;                           ///< [out] Maximum bus width between device and memory.
            uint64_t totalSize;                             ///< [out] Total memory size in bytes that is available to the device.
            char name[ZE_MAX_DEVICE_NAME];                  ///< [out] Memory name

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device memory access properties queried using
        ///        ::zeDeviceGetMemoryAccessProperties
        struct memory_access_properties_t
        {
            structure_type_t stype = structure_type_t::DEVICE_MEMORY_ACCESS_PROPERTIES; ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            memory_access_cap_flags_t hostAllocCapabilities;///< [out] host memory capabilities.
                                                            ///< returns 0 (unsupported) or a combination of ::ze_memory_access_cap_flag_t.
            memory_access_cap_flags_t deviceAllocCapabilities;  ///< [out] device memory capabilities.
                                                            ///< returns 0 (unsupported) or a combination of ::ze_memory_access_cap_flag_t.
            memory_access_cap_flags_t sharedSingleDeviceAllocCapabilities;  ///< [out] shared, single-device memory capabilities.
                                                            ///< returns 0 (unsupported) or a combination of ::ze_memory_access_cap_flag_t.
            memory_access_cap_flags_t sharedCrossDeviceAllocCapabilities;   ///< [out] shared, cross-device memory capabilities.
                                                            ///< returns 0 (unsupported) or a combination of ::ze_memory_access_cap_flag_t.
            memory_access_cap_flags_t sharedSystemAllocCapabilities;///< [out] shared, system memory capabilities.
                                                            ///< returns 0 (unsupported) or a combination of ::ze_memory_access_cap_flag_t.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device cache properties queried using ::zeDeviceGetCacheProperties
        struct cache_properties_t
        {
            structure_type_t stype = structure_type_t::DEVICE_CACHE_PROPERTIES; ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            cache_property_flags_t flags;                   ///< [out] 0 (none) or a valid combination of
                                                            ///< ::ze_device_cache_property_flag_t
            size_t cacheSize;                               ///< [out] Per-cache size, in bytes

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device image properties queried using ::zeDeviceGetImageProperties
        struct image_properties_t
        {
            structure_type_t stype = structure_type_t::DEVICE_IMAGE_PROPERTIES; ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            uint32_t maxImageDims1D;                        ///< [out] Maximum image dimensions for 1D resources. if 0, then 1D images
                                                            ///< are unsupported.
            uint32_t maxImageDims2D;                        ///< [out] Maximum image dimensions for 2D resources. if 0, then 2D images
                                                            ///< are unsupported.
            uint32_t maxImageDims3D;                        ///< [out] Maximum image dimensions for 3D resources. if 0, then 3D images
                                                            ///< are unsupported.
            uint64_t maxImageBufferSize;                    ///< [out] Maximum image buffer size in bytes. if 0, then buffer images are
                                                            ///< unsupported.
            uint32_t maxImageArraySlices;                   ///< [out] Maximum image array slices. if 0, then image arrays are
                                                            ///< unsupported.
            uint32_t maxSamplers;                           ///< [out] Max samplers that can be used in kernel. if 0, then sampling is
                                                            ///< unsupported.
            uint32_t maxReadImageArgs;                      ///< [out] Returns the maximum number of simultaneous image objects that
                                                            ///< can be read from by a kernel. if 0, then reading images is
                                                            ///< unsupported.
            uint32_t maxWriteImageArgs;                     ///< [out] Returns the maximum number of simultaneous image objects that
                                                            ///< can be written to by a kernel. if 0, then writing images is
                                                            ///< unsupported.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device external memory import and export properties
        struct external_memory_properties_t
        {
            structure_type_t stype = structure_type_t::DEVICE_EXTERNAL_MEMORY_PROPERTIES;   ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            external_memory_type_flags_t memoryAllocationImportTypes;   ///< [out] Supported external memory import types for memory allocations.
            external_memory_type_flags_t memoryAllocationExportTypes;   ///< [out] Supported external memory export types for memory allocations.
            external_memory_type_flags_t imageImportTypes;  ///< [out] Supported external memory import types for images.
            external_memory_type_flags_t imageExportTypes;  ///< [out] Supported external memory export types for images.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device peer-to-peer properties queried using
        ///        ::zeDeviceGetP2PProperties
        struct p2p_properties_t
        {
            structure_type_t stype = structure_type_t::DEVICE_P2P_PROPERTIES;   ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            p2p_property_flags_t flags;                     ///< [out] 0 (none) or a valid combination of
                                                            ///< ::ze_device_p2p_property_flag_t

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        device_handle_t m_handle;                       ///< [in] handle of device object
        Driver* m_pDriver;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Device( void ) = delete;
        Device( 
            device_handle_t handle,                         ///< [in] handle of device object
            Driver* pDriver                                 ///< [in] pointer to owner object
            );

        ~Device( void ) = default;

        Device( Device const& other ) = delete;
        void operator=( Device const& other ) = delete;

        Device( Device&& other ) = delete;
        void operator=( Device&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDriver( void ) const { return m_pDriver; }

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
        /// @throws result_t
        static void ZE_APICALL
        Get(
            Driver* pDriver,                                ///< [in] pointer to the driver instance
            uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of devices available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of devices.
                                                            ///< if count is larger than the number of devices available, then the
                                                            ///< driver will update the value with the correct number of devices available.
            Device** ppDevices = nullptr                    ///< [in,out][optional][range(0, *pCount)] array of pointer to devices
            );

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
        /// @throws result_t
        void ZE_APICALL
        GetSubDevices(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-devices.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of sub-devices available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of sub-devices.
                                                            ///< if count is larger than the number of sub-devices available, then the
                                                            ///< driver will update the value with the correct number of sub-devices available.
            Device** ppSubdevices = nullptr                 ///< [in,out][optional][range(0, *pCount)] array of pointer to sub-devices
            );

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
        /// @throws result_t
        void ZE_APICALL
        GetProperties(
            properties_t* pDeviceProperties                 ///< [in,out] query result for device properties
            );

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
        /// @throws result_t
        void ZE_APICALL
        GetComputeProperties(
            compute_properties_t* pComputeProperties        ///< [in,out] query result for compute properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves module properties of the device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void ZE_APICALL
        GetModuleProperties(
            module_properties_t* pModuleProperties          ///< [in,out] query result for module properties
            );

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
        /// @throws result_t
        void ZE_APICALL
        GetCommandQueueGroupProperties(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of command queue group properties.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of command queue group properties available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< command queue group properties.
                                                            ///< if count is larger than the number of command queue group properties
                                                            ///< available, then the driver will update the value with the correct
                                                            ///< number of command queue group properties available.
            command_queue_group_properties_t* pCommandQueueGroupProperties = nullptr///< [in,out][optional][range(0, *pCount)] array of query results for
                                                            ///< command queue group properties
            );

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
        /// @throws result_t
        void ZE_APICALL
        GetMemoryProperties(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of memory properties available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< memory properties.
                                                            ///< if count is larger than the number of memory properties available,
                                                            ///< then the driver will update the value with the correct number of
                                                            ///< memory properties available.
            memory_properties_t* pMemProperties = nullptr   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                            ///< memory properties
            );

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
        /// @throws result_t
        void ZE_APICALL
        GetMemoryAccessProperties(
            memory_access_properties_t* pMemAccessProperties///< [in,out] query result for memory access properties
            );

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
        /// @throws result_t
        void ZE_APICALL
        GetCacheProperties(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of cache properties.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of cache properties available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of
                                                            ///< cache properties.
                                                            ///< if count is larger than the number of cache properties available, then
                                                            ///< the driver will update the value with the correct number of cache
                                                            ///< properties available.
            cache_properties_t* pCacheProperties = nullptr  ///< [in,out][optional][range(0, *pCount)] array of query results for cache
                                                            ///< properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves image properties of the device
        /// 
        /// @details
        ///     - See ::zeImageGetProperties for format-specific capabilities.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void ZE_APICALL
        GetImageProperties(
            image_properties_t* pImageProperties            ///< [in,out] query result for image properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves external memory import and export of the device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void ZE_APICALL
        GetExternalMemoryProperties(
            external_memory_properties_t* pExternalMemoryProperties ///< [in,out] query result for external memory properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves peer-to-peer properties between one device and a peer
        ///        devices
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void ZE_APICALL
        GetP2PProperties(
            Device* pPeerDevice,                            ///< [in] pointer to the peer device with the allocation
            p2p_properties_t* pP2PProperties                ///< [in,out] Peer-to-Peer properties between source and peer device
            );

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
        /// @returns
        ///     - bool_t: returned access capability
        /// 
        /// @throws result_t
        bool_t ZE_APICALL
        CanAccessPeer(
            Device* pPeerDevice                             ///< [in] pointer to the peer device with the allocation
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Returns current status of the device.
        /// 
        /// @details
        ///     - Once a device is reset, this call will update the OS handle attached
        ///       to the device handle.
        ///     - The application may call this function from simultaneous threads with
        ///       the same device handle.
        ///     - The implementation of this function must be thread-safe.
        /// @throws result_t
        void ZE_APICALL
        GetStatus(
            void
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts device_uuid_t to std::string
    std::string to_string( const device_uuid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::type_t to std::string
    std::string to_string( const Device::type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::property_flags_t to std::string
    std::string to_string( const Device::property_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::properties_t to std::string
    std::string to_string( const Device::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::thread_t to std::string
    std::string to_string( const Device::thread_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::compute_properties_t to std::string
    std::string to_string( const Device::compute_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::native_kernel_uuid_t to std::string
    std::string to_string( const Device::native_kernel_uuid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::module_flags_t to std::string
    std::string to_string( const Device::module_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::fp_flags_t to std::string
    std::string to_string( const Device::fp_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::module_properties_t to std::string
    std::string to_string( const Device::module_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::command_queue_group_property_flags_t to std::string
    std::string to_string( const Device::command_queue_group_property_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::command_queue_group_properties_t to std::string
    std::string to_string( const Device::command_queue_group_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_property_flags_t to std::string
    std::string to_string( const Device::memory_property_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_properties_t to std::string
    std::string to_string( const Device::memory_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_access_cap_flags_t to std::string
    std::string to_string( const Device::memory_access_cap_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_access_properties_t to std::string
    std::string to_string( const Device::memory_access_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::cache_property_flags_t to std::string
    std::string to_string( const Device::cache_property_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::cache_properties_t to std::string
    std::string to_string( const Device::cache_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::image_properties_t to std::string
    std::string to_string( const Device::image_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::external_memory_properties_t to std::string
    std::string to_string( const Device::external_memory_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::p2p_property_flags_t to std::string
    std::string to_string( const Device::p2p_property_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::p2p_properties_t to std::string
    std::string to_string( const Device::p2p_properties_t val );

} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero APIs for Context
#pragma region context
namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for context
    class Context
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported context creation flags
        struct flags_t
        {
            uint32_t value;
            flags_t() : value(0) {}
            flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum flag_t
        {
            FLAG_TBD = ZE_BIT(0),                           ///< reserved for future use
            FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported raytracing memory allocation flags
        struct raytracing_mem_alloc_ext_flags_t
        {
            uint32_t value;
            raytracing_mem_alloc_ext_flags_t() : value(0) {}
            raytracing_mem_alloc_ext_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum raytracing_mem_alloc_ext_flag_t
        {
            RAYTRACING_MEM_ALLOC_EXT_FLAG_TBD = ZE_BIT(0),  ///< reserved for future use
            RAYTRACING_MEM_ALLOC_EXT_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Context descriptor
        struct desc_t
        {
            structure_type_t stype = structure_type_t::CONTEXT_DESC;///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            flags_t flags = 0;                              ///< [in] creation flags.
                                                            ///< must be 0 (default) or a valid combination of ::ze_context_flag_t;
                                                            ///< default behavior may use implicit driver-based heuristics.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Raytracing memory allocation descriptor
        /// 
        /// @details
        ///     - This structure must be passed to ::zeMemAllocShared or
        ///       ::zeMemAllocDevice, via `pNext` member of
        ///       ::ze_device_mem_alloc_desc_t, for any memory allocation that is to be
        ///       accessed by raytracing fixed-function of the device.
        struct raytracing_mem_alloc_ext_desc_t
        {
            structure_type_t stype = structure_type_t::RAYTRACING_MEM_ALLOC_EXT_DESC;   ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            raytracing_mem_alloc_ext_flags_t flags = 0;     ///< [in] flags specifying additional allocation controls.
                                                            ///< must be 0 (default) or a valid combination of ::ze_raytracing_mem_alloc_ext_flag_t;
                                                            ///< default behavior may use implicit driver-based heuristics.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        context_handle_t m_handle;                      ///< [in] handle of context object
        Driver* m_pDriver;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Context( void ) = delete;
        Context( 
            context_handle_t handle,                        ///< [in] handle of context object
            Driver* pDriver                                 ///< [in] pointer to owner object
            );

        ~Context( void ) = default;

        Context( Context const& other ) = delete;
        void operator=( Context const& other ) = delete;

        Context( Context&& other ) = delete;
        void operator=( Context&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDriver( void ) const { return m_pDriver; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a context for the driver.
        /// 
        /// @details
        ///     - The application must only use the context for the driver which was
        ///       provided during creation.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function must be thread-safe.
        /// @returns
        ///     - Context*: pointer to handle of context object created
        /// 
        /// @throws result_t
        static Context* ZE_APICALL
        Create(
            Driver* pDriver,                                ///< [in] pointer to the driver object
            const desc_t* desc                              ///< [in] pointer to context descriptor
            );

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
        /// @throws result_t
        static void ZE_APICALL
        Destroy(
            Context* pContext                               ///< [in][release] pointer to context object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Returns current status of the context.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads with
        ///       the same context handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void ZE_APICALL
        GetStatus(
            void
            );

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
        /// @throws result_t
        void ZE_APICALL
        SystemBarrier(
            Device* pDevice                                 ///< [in] pointer to the device
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Makes memory resident for the device.
        /// 
        /// @details
        ///     - The application must ensure the memory is resident before being
        ///       referenced by the device
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void ZE_APICALL
        MakeMemoryResident(
            Device* pDevice,                                ///< [in] pointer to the device
            void* ptr,                                      ///< [in] pointer to memory to make resident
            size_t size                                     ///< [in] size in bytes to make resident
            );

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
        /// @throws result_t
        void ZE_APICALL
        EvictMemory(
            Device* pDevice,                                ///< [in] pointer to the device
            void* ptr,                                      ///< [in] pointer to memory to evict
            size_t size                                     ///< [in] size in bytes to evict
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Makes image resident for the device.
        /// 
        /// @details
        ///     - The application must ensure the image is resident before being
        ///       referenced by the device
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void ZE_APICALL
        MakeImageResident(
            Device* pDevice,                                ///< [in] pointer to the device
            Image* pImage                                   ///< [in] pointer to image to make resident
            );

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
        /// @throws result_t
        void ZE_APICALL
        EvictImage(
            Device* pDevice,                                ///< [in] pointer to the device
            Image* pImage                                   ///< [in] pointer to image to make evict
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Context::flags_t to std::string
    std::string to_string( const Context::flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Context::desc_t to std::string
    std::string to_string( const Context::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Context::raytracing_mem_alloc_ext_flags_t to std::string
    std::string to_string( const Context::raytracing_mem_alloc_ext_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Context::raytracing_mem_alloc_ext_desc_t to std::string
    std::string to_string( const Context::raytracing_mem_alloc_ext_desc_t val );

} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero APIs for Command Queue
#pragma region cmdqueue
namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command queue
    class CommandQueue
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command queue flags
        struct flags_t
        {
            uint32_t value;
            flags_t() : value(0) {}
            flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum flag_t
        {
            FLAG_EXPLICIT_ONLY = ZE_BIT(0),                 ///< command queue should be optimized for submission to a single device engine.
                                                            ///< driver **must** disable any implicit optimizations for distributing
                                                            ///< work across multiple engines.
                                                            ///< this flag should be used when applications want full control over
                                                            ///< multi-engine submission and scheduling.
            FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command queue modes
        enum class mode_t : uint32_t
        {
            DEFAULT = 0,                                    ///< implicit default behavior; uses driver-based heuristics
            SYNCHRONOUS = 1,                                ///< Device execution always completes immediately on execute;
                                                            ///< Host thread is blocked using wait on implicit synchronization object
            ASYNCHRONOUS = 2,                               ///< Device execution is scheduled and will complete in future;
                                                            ///< explicit synchronization object must be used to determine completeness
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command queue priorities
        enum class priority_t : uint32_t
        {
            NORMAL = 0,                                     ///< [default] normal priority
            PRIORITY_LOW = 1,                               ///< lower priority than normal
            PRIORITY_HIGH = 2,                              ///< higher priority than normal
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Command Queue descriptor
        struct desc_t
        {
            structure_type_t stype = structure_type_t::COMMAND_QUEUE_DESC;  ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            uint32_t ordinal;                               ///< [in] command queue group ordinal
            uint32_t index;                                 ///< [in] command queue index within the group;
                                                            ///< must be zero if ::ZE_COMMAND_QUEUE_FLAG_EXPLICIT_ONLY is not set
            flags_t flags = 0;                              ///< [in] usage flags.
                                                            ///< must be 0 (default) or a valid combination of ::ze_command_queue_flag_t;
                                                            ///< default behavior may use implicit driver-based heuristics to balance
                                                            ///< latency and throughput.
            mode_t mode = mode_t::DEFAULT;                  ///< [in] operation mode
            priority_t priority = priority_t::NORMAL;       ///< [in] priority

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        command_queue_handle_t m_handle;                ///< [in] handle of command queue object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the command queue object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        CommandQueue( void ) = delete;
        CommandQueue( 
            command_queue_handle_t handle,                  ///< [in] handle of command queue object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the command queue object
            );

        ~CommandQueue( void ) = default;

        CommandQueue( CommandQueue const& other ) = delete;
        void operator=( CommandQueue const& other ) = delete;

        CommandQueue( CommandQueue&& other ) = delete;
        void operator=( CommandQueue&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - CommandQueue*: pointer to handle of command queue object created
        /// 
        /// @throws result_t
        static CommandQueue* ZE_APICALL
        Create(
            Context* pContext,                              ///< [in] pointer to the context object
            Device* pDevice,                                ///< [in] pointer to the device object
            const desc_t* desc                              ///< [in] pointer to command queue descriptor
            );

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
        /// @throws result_t
        static void ZE_APICALL
        Destroy(
            CommandQueue* pCommandQueue                     ///< [in][release] pointer to command queue object to destroy
            );

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
        /// @throws result_t
        void ZE_APICALL
        ExecuteCommandLists(
            uint32_t numCommandLists,                       ///< [in] number of command lists to execute
            CommandList** ppCommandLists,                   ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                            ///< to execute
            Fence* pFence = nullptr                         ///< [in][optional] pointer to the fence to signal on completion
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Synchronizes a command queue by waiting on the host.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - bool_t:'0' when RESULT_NOT_READY
        /// @throws result_t
        bool_t ZE_APICALL
        Synchronize(
            uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                            ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                            ///< if zero, then immediately returns the status of the command queue;
                                                            ///< if UINT64_MAX, then function will not return until complete or device
                                                            ///< is lost.
                                                            ///< Due to external dependencies, timeout may be rounded to the closest
                                                            ///< value allowed by the accuracy of those dependencies.
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::flags_t to std::string
    std::string to_string( const CommandQueue::flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::mode_t to std::string
    std::string to_string( const CommandQueue::mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::priority_t to std::string
    std::string to_string( const CommandQueue::priority_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandQueue::desc_t to std::string
    std::string to_string( const CommandQueue::desc_t val );

} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero APIs for Command List
#pragma region cmdlist
namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command list
    class CommandList
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported command list creation flags
        struct flags_t
        {
            uint32_t value;
            flags_t() : value(0) {}
            flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum flag_t
        {
            FLAG_RELAXED_ORDERING = ZE_BIT(0),              ///< driver may reorder commands (e.g., kernels, copies) between barriers
                                                            ///< and synchronization primitives.
                                                            ///< using this flag may increase Host overhead of ::zeCommandListClose.
                                                            ///< therefore, this flag should **not** be set for low-latency usage-models.
            FLAG_MAXIMIZE_THROUGHPUT = ZE_BIT(1),           ///< driver may perform additional optimizations that increase execution
                                                            ///< throughput. 
                                                            ///< using this flag may increase Host overhead of ::zeCommandListClose and ::zeCommandQueueExecuteCommandLists.
                                                            ///< therefore, this flag should **not** be set for low-latency usage-models.
            FLAG_EXPLICIT_ONLY = ZE_BIT(2),                 ///< command list should be optimized for submission to a single command
                                                            ///< queue and device engine.
                                                            ///< driver **must** disable any implicit optimizations for distributing
                                                            ///< work across multiple engines.
                                                            ///< this flag should be used when applications want full control over
                                                            ///< multi-engine submission and scheduling.
            FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported memory advice hints
        enum class memory_advice_t : uint32_t
        {
            SET_READ_MOSTLY = 0,                            ///< hint that memory will be read from frequently and written to rarely
            CLEAR_READ_MOSTLY = 1,                          ///< removes the affect of ::ZE_MEMORY_ADVICE_SET_READ_MOSTLY
            SET_PREFERRED_LOCATION = 2,                     ///< hint that the preferred memory location is the specified device
            CLEAR_PREFERRED_LOCATION = 3,                   ///< removes the affect of ::ZE_MEMORY_ADVICE_SET_PREFERRED_LOCATION
            SET_NON_ATOMIC_MOSTLY = 4,                      ///< hints that memory will mostly be accessed non-atomically
            CLEAR_NON_ATOMIC_MOSTLY = 5,                    ///< removes the affect of ::ZE_MEMORY_ADVICE_SET_NON_ATOMIC_MOSTLY
            BIAS_CACHED = 6,                                ///< hints that memory should be cached
            BIAS_UNCACHED = 7,                              ///< hints that memory should be not be cached
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Command List descriptor
        struct desc_t
        {
            structure_type_t stype = structure_type_t::COMMAND_LIST_DESC;   ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            uint32_t commandQueueGroupOrdinal;              ///< [in] command queue group ordinal to which this command list will be
                                                            ///< submitted
            flags_t flags = 0;                              ///< [in] usage flags.
                                                            ///< must be 0 (default) or a valid combination of ::ze_command_list_flag_t;
                                                            ///< default behavior may use implicit driver-based heuristics to balance
                                                            ///< latency and throughput.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Copy region descriptor
        struct copy_region_t
        {
            uint32_t originX;                               ///< [in] The origin x offset for region in bytes
            uint32_t originY;                               ///< [in] The origin y offset for region in rows
            uint32_t originZ;                               ///< [in] The origin z offset for region in slices
            uint32_t width;                                 ///< [in] The region width relative to origin in bytes
            uint32_t height;                                ///< [in] The region height relative to origin in rows
            uint32_t depth;                                 ///< [in] The region depth relative to origin in slices. Set this to 0 for
                                                            ///< 2D copy.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Region descriptor
        struct image_region_t
        {
            uint32_t originX;                               ///< [in] The origin x offset for region in pixels
            uint32_t originY;                               ///< [in] The origin y offset for region in pixels
            uint32_t originZ;                               ///< [in] The origin z offset for region in pixels
            uint32_t width;                                 ///< [in] The region width relative to origin in pixels
            uint32_t height;                                ///< [in] The region height relative to origin in pixels
            uint32_t depth;                                 ///< [in] The region depth relative to origin. For 1D or 2D images, set
                                                            ///< this to 1.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel dispatch group count.
        struct group_count_t
        {
            uint32_t groupCountX = 0;                       ///< [in] number of thread groups in X dimension
            uint32_t groupCountY = 0;                       ///< [in] number of thread groups in Y dimension
            uint32_t groupCountZ = 0;                       ///< [in] number of thread groups in Z dimension

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        command_list_handle_t m_handle;                 ///< [in] handle of command list object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the command list object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        CommandList( void ) = delete;
        CommandList( 
            command_list_handle_t handle,                   ///< [in] handle of command list object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the command list object
            );

        ~CommandList( void ) = default;

        CommandList( CommandList const& other ) = delete;
        void operator=( CommandList const& other ) = delete;

        CommandList( CommandList&& other ) = delete;
        void operator=( CommandList&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - CommandList*: pointer to handle of command list object created
        /// 
        /// @throws result_t
        static CommandList* ZE_APICALL
        Create(
            Context* pContext,                              ///< [in] pointer to the context object
            Device* pDevice,                                ///< [in] pointer to the device object
            const desc_t* desc                              ///< [in] pointer to command list descriptor
            );

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
        /// @returns
        ///     - CommandList*: pointer to handle of command list object created
        /// 
        /// @throws result_t
        static CommandList* ZE_APICALL
        CreateImmediate(
            Context* pContext,                              ///< [in] pointer to the context object
            Device* pDevice,                                ///< [in] pointer to the device object
            const CommandQueue::desc_t* altdesc             ///< [in] pointer to command queue descriptor
            );

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
        /// @throws result_t
        static void ZE_APICALL
        Destroy(
            CommandList* pCommandList                       ///< [in][release] pointer to command list object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes a command list; ready to be executed by a command queue.
        /// 
        /// @details
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void ZE_APICALL
        Close(
            void
            );

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
        /// @throws result_t
        void ZE_APICALL
        Reset(
            void
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendWriteGlobalTimestamp(
            uint64_t* dstptr,                               ///< [in,out] pointer to memory where timestamp value will be written; must
                                                            ///< be 8byte-aligned.
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before executing query;
                                                            ///< must be 0 if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before executing query
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendBarrier(
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before executing barrier;
                                                            ///< must be 0 if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before executing barrier
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendMemoryRangesBarrier(
            uint32_t numRanges,                             ///< [in] number of memory ranges
            const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
            const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before executing barrier;
                                                            ///< must be 0 if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before executing barrier
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendMemoryCopy(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            const void* srcptr,                             ///< [in] pointer to source memory to copy from
            size_t size,                                    ///< [in] size in bytes to copy
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching; must be 0
                                                            ///< if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendMemoryFill(
            void* ptr,                                      ///< [in] pointer to memory to initialize
            const void* pattern,                            ///< [in] pointer to value to initialize memory to
            size_t pattern_size,                            ///< [in] size in bytes of the value to initialize memory to
            size_t size,                                    ///< [in] size in bytes to initialize
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching; must be 0
                                                            ///< if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendMemoryCopyRegion(
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
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching; must be 0
                                                            ///< if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendMemoryCopyFromContext(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            Context* pContextSrc,                           ///< [in] pointer to source context object
            const void* srcptr,                             ///< [in] pointer to source memory to copy from
            size_t size,                                    ///< [in] size in bytes to copy
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching; must be 0
                                                            ///< if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendImageCopy(
            Image* pDstImage,                               ///< [in] pointer to destination image to copy to
            Image* pSrcImage,                               ///< [in] pointer to source image to copy from
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching; must be 0
                                                            ///< if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendImageCopyRegion(
            Image* pDstImage,                               ///< [in] pointer to destination image to copy to
            Image* pSrcImage,                               ///< [in] pointer to source image to copy from
            const image_region_t* pDstRegion = nullptr,     ///< [in][optional] destination region descriptor
            const image_region_t* pSrcRegion = nullptr,     ///< [in][optional] source region descriptor
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching; must be 0
                                                            ///< if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendImageCopyToMemory(
            void* dstptr,                                   ///< [in] pointer to destination memory to copy to
            Image* pSrcImage,                               ///< [in] pointer to source image to copy from
            const image_region_t* pSrcRegion = nullptr,     ///< [in][optional] source region descriptor
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching; must be 0
                                                            ///< if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendImageCopyFromMemory(
            Image* pDstImage,                               ///< [in] pointer to destination image to copy to
            const void* srcptr,                             ///< [in] pointer to source memory to copy from
            const image_region_t* pDstRegion = nullptr,     ///< [in][optional] destination region descriptor
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching; must be 0
                                                            ///< if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendMemoryPrefetch(
            const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
            size_t size                                     ///< [in] size in bytes of the memory range to prefetch
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendMemAdvise(
            Device* pDevice,                                ///< [in] device associated with the memory advice
            const void* ptr,                                ///< [in] Pointer to the start of the memory range
            size_t size,                                    ///< [in] Size in bytes of the memory range
            memory_advice_t advice                          ///< [in] Memory advice for the memory range
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendSignalEvent(
            Event* pEvent                                   ///< [in] pointer to the event
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendWaitOnEvents(
            uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
            Event** ppEvents                                ///< [in][range(0, numEvents)] handles of the events to wait on before
                                                            ///< continuing
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendEventReset(
            Event* pEvent                                   ///< [in] pointer to the event
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendQueryKernelTimestamps(
            uint32_t numEvents,                             ///< [in] the number of timestamp events to query
            Event** ppEvents,                               ///< [in][range(0, numEvents)] handles of timestamp events to query
            void* dstptr,                                   ///< [in,out] pointer to memory where ::ze_kernel_timestamp_result_t will
                                                            ///< be written; must be size-aligned.
            const size_t* pOffsets = nullptr,               ///< [in][optional][range(0, numEvents)] offset, in bytes, to write
                                                            ///< results; address must be 4byte-aligned and offsets must be
                                                            ///< size-aligned.
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before executing query;
                                                            ///< must be 0 if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before executing query
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendLaunchKernel(
            Kernel* pKernel,                                ///< [in] pointer to the kernel object
            const group_count_t* pLaunchFuncArgs,           ///< [in] thread group launch arguments
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching; must be 0
                                                            ///< if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendLaunchCooperativeKernel(
            Kernel* pKernel,                                ///< [in] pointer to the kernel object
            const group_count_t* pLaunchFuncArgs,           ///< [in] thread group launch arguments
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching; must be 0
                                                            ///< if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendLaunchKernelIndirect(
            Kernel* pKernel,                                ///< [in] pointer to the kernel object
            const group_count_t* pLaunchArgumentsBuffer,    ///< [in] pointer to device buffer that will contain thread group launch
                                                            ///< arguments
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching; must be 0
                                                            ///< if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

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
        /// @throws result_t
        void ZE_APICALL
        AppendLaunchMultipleKernelsIndirect(
            uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
            Kernel** ppKernels,                             ///< [in][range(0, numKernels)] handles of the kernel objects
            const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                            ///< number of kernels to launch; value must be less-than or equal-to
                                                            ///< numKernels
            const group_count_t* pLaunchArgumentsBuffer,    ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                            ///< a contiguous array of thread group launch arguments
            Event* pSignalEvent = nullptr,                  ///< [in][optional] pointer to the event to signal on completion
            uint32_t numWaitEvents = 0,                     ///< [in][optional] number of events to wait on before launching; must be 0
                                                            ///< if `nullptr == phWaitEvents`
            Event** ppWaitEvents = nullptr                  ///< [in][optional][range(0, numWaitEvents)] pointer to the events to wait
                                                            ///< on before launching
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::flags_t to std::string
    std::string to_string( const CommandList::flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::desc_t to std::string
    std::string to_string( const CommandList::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::copy_region_t to std::string
    std::string to_string( const CommandList::copy_region_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::image_region_t to std::string
    std::string to_string( const CommandList::image_region_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::memory_advice_t to std::string
    std::string to_string( const CommandList::memory_advice_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts CommandList::group_count_t to std::string
    std::string to_string( const CommandList::group_count_t val );

} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero APIs for Barrier
#pragma region barrier
namespace ze
{
} // namespace ze

namespace ze
{
} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero APIs for Copies
#pragma region copy
namespace ze
{
} // namespace ze

namespace ze
{
} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero APIs for Event
#pragma region event
namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for event pool
    class EventPool
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported event pool creation flags
        struct flags_t
        {
            uint32_t value;
            flags_t() : value(0) {}
            flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum flag_t
        {
            FLAG_HOST_VISIBLE = ZE_BIT(0),                  ///< signals and waits are also visible to host
            FLAG_IPC = ZE_BIT(1),                           ///< signals and waits may be shared across processes
            FLAG_KERNEL_TIMESTAMP = ZE_BIT(2),              ///< Indicates all events in pool will contain kernel timestamps; cannot be
                                                            ///< combined with ::ZE_EVENT_POOL_FLAG_IPC
            FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event pool descriptor
        struct desc_t
        {
            structure_type_t stype = structure_type_t::EVENT_POOL_DESC; ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            flags_t flags = 0;                              ///< [in] creation flags.
                                                            ///< must be 0 (default) or a valid combination of ::ze_event_pool_flag_t;
                                                            ///< default behavior is signals and waits are visible to the entire device
                                                            ///< and peer devices.
            uint32_t count;                                 ///< [in] number of events within the pool; must be greater than 0

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        event_pool_handle_t m_handle;                   ///< [in] handle of event pool object
        Context* m_pContext;                            ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the event pool object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        EventPool( void ) = delete;
        EventPool( 
            event_pool_handle_t handle,                     ///< [in] handle of event pool object
            Context* pContext,                              ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the event pool object
            );

        ~EventPool( void ) = default;

        EventPool( EventPool const& other ) = delete;
        void operator=( EventPool const& other ) = delete;

        EventPool( EventPool&& other ) = delete;
        void operator=( EventPool&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getContext( void ) const { return m_pContext; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a pool of events on the context.
        /// 
        /// @details
        ///     - The application must only use events within the pool for the
        ///       device(s), or their sub-devices, which were provided during creation.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function must be thread-safe.
        /// @returns
        ///     - EventPool*: pointer handle of event pool object created
        /// 
        /// @throws result_t
        static EventPool* ZE_APICALL
        Create(
            Context* pContext,                              ///< [in] pointer to the context object
            const desc_t* desc,                             ///< [in] pointer to event pool descriptor
            uint32_t numDevices = 0,                        ///< [in][optional] number of device handles; must be 0 if `nullptr ==
                                                            ///< phDevices`
            Device** ppDevices = nullptr                    ///< [in][optional][range(0, numDevices)] array of device handles which
                                                            ///< have visibility to the event pool.
                                                            ///< if nullptr, then event pool is visible to all devices supported by the
                                                            ///< driver instance.
            );

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
        /// @throws result_t
        static void ZE_APICALL
        Destroy(
            EventPool* pEventPool                           ///< [in][release] pointer to event pool object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Gets an IPC event pool handle for the specified event handle that can
        ///        be shared with another process.
        /// 
        /// @details
        ///     - Event pool must have been created with ::ZE_EVENT_POOL_FLAG_IPC.
        ///     - The application may call this function from simultaneous threads.
        /// @returns
        ///     - ipc_event_pool_handle_t: Returned IPC event handle
        /// 
        /// @throws result_t
        ipc_event_pool_handle_t ZE_APICALL
        GetIpcHandle(
            void
            );

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
        /// @returns
        ///     - EventPool*: pointer handle of event pool object created
        /// 
        /// @throws result_t
        static EventPool* ZE_APICALL
        OpenIpcHandle(
            Context* pContext,                              ///< [in] pointer to the context object to associate with the IPC event
                                                            ///< pool handle
            ipc_event_pool_handle_t pIpc                    ///< [in] IPC event pool handle
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes an IPC event handle in the current process.
        /// 
        /// @details
        ///     - Closes an IPC event handle by destroying events that were opened in
        ///       this process using ::zeEventPoolOpenIpcHandle.
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same event pool handle.
        /// @throws result_t
        void ZE_APICALL
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
        /// @brief Supported event scope flags
        struct scope_flags_t
        {
            uint32_t value;
            scope_flags_t() : value(0) {}
            scope_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum scope_flag_t
        {
            SCOPE_FLAG_SUBDEVICE = ZE_BIT(0),               ///< cache hierarchies are flushed or invalidated sufficient for local
                                                            ///< sub-device access
            SCOPE_FLAG_DEVICE = ZE_BIT(1),                  ///< cache hierarchies are flushed or invalidated sufficient for global
                                                            ///< device access and peer device access
            SCOPE_FLAG_HOST = ZE_BIT(2),                    ///< cache hierarchies are flushed or invalidated sufficient for device and
                                                            ///< host access
            SCOPE_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Event descriptor
        struct desc_t
        {
            structure_type_t stype = structure_type_t::EVENT_DESC;  ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            uint32_t index;                                 ///< [in] index of the event within the pool; must be less-than the count
                                                            ///< specified during pool creation
            scope_flags_t signal = 0;                       ///< [in] defines the scope of relevant cache hierarchies to flush on a
                                                            ///< signal action before the event is triggered.
                                                            ///< must be 0 (default) or a valid combination of ::ze_event_scope_flag_t;
                                                            ///< default behavior is execution synchronization only, no cache
                                                            ///< hierarchies are flushed.
            scope_flags_t wait = 0;                         ///< [in] defines the scope of relevant cache hierarchies to invalidate on
                                                            ///< a wait action after the event is complete.
                                                            ///< must be 0 (default) or a valid combination of ::ze_event_scope_flag_t;
                                                            ///< default behavior is execution synchronization only, no cache
                                                            ///< hierarchies are invalidated.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel timestamp clock data
        /// 
        /// @details
        ///     - The timestamp frequency can be queried from
        ///       ::ze_device_properties_t.timerResolution.
        ///     - The number of valid bits in the timestamp value can be queried from
        ///       ::ze_device_properties_t.kernelTimestampValidBits.
        struct kernel_timestamp_data_t
        {
            uint64_t kernelStart;                           ///< [out] device clock at start of kernel execution
            uint64_t kernelEnd;                             ///< [out] device clock at end of kernel execution

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel timestamp result
        struct kernel_timestamp_result_t
        {
            kernel_timestamp_data_t global;                 ///< [out] wall-clock data
            kernel_timestamp_data_t context;                ///< [out] context-active data; only includes clocks while device context
                                                            ///< was actively executing.

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
        /// @returns
        ///     - Event*: pointer to handle of event object created
        /// 
        /// @throws result_t
        static Event* ZE_APICALL
        Create(
            EventPool* pEventPool,                          ///< [in] pointer to the event pool
            const desc_t* desc                              ///< [in] pointer to event descriptor
            );

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
        /// @throws result_t
        static void ZE_APICALL
        Destroy(
            Event* pEvent                                   ///< [in][release] pointer to event object to destroy
            );

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
        /// @throws result_t
        void ZE_APICALL
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
        bool_t ZE_APICALL
        HostSynchronize(
            uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                            ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                            ///< if zero, then operates exactly like ::zeEventQueryStatus;
                                                            ///< if UINT64_MAX, then function will not return until complete or device
                                                            ///< is lost.
                                                            ///< Due to external dependencies, timeout may be rounded to the closest
                                                            ///< value allowed by the accuracy of those dependencies.
            );

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
        /// @returns
        ///     - bool_t:'0' when RESULT_NOT_READY
        /// @throws result_t
        bool_t ZE_APICALL
        QueryStatus(
            void
            );

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
        /// @throws result_t
        void ZE_APICALL
        HostReset(
            void
            );

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
        /// @returns
        ///     - bool_t:'0' when RESULT_NOT_READY
        /// @throws result_t
        bool_t ZE_APICALL
        QueryKernelTimestamp(
            kernel_timestamp_result_t* dstptr               ///< [in,out] pointer to memory for where timestamp result will be written.
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::flags_t to std::string
    std::string to_string( const EventPool::flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts EventPool::desc_t to std::string
    std::string to_string( const EventPool::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::scope_flags_t to std::string
    std::string to_string( const Event::scope_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::desc_t to std::string
    std::string to_string( const Event::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::kernel_timestamp_data_t to std::string
    std::string to_string( const Event::kernel_timestamp_data_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Event::kernel_timestamp_result_t to std::string
    std::string to_string( const Event::kernel_timestamp_result_t val );

} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero APIs for Fence
#pragma region fence
namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for fence
    class Fence
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported fence creation flags
        struct flags_t
        {
            uint32_t value;
            flags_t() : value(0) {}
            flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum flag_t
        {
            FLAG_SIGNALED = ZE_BIT(0),                      ///< fence is created in the signaled state, otherwise not signaled.
            FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Fence descriptor
        struct desc_t
        {
            structure_type_t stype = structure_type_t::FENCE_DESC;  ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            flags_t flags = 0;                              ///< [in] creation flags.
                                                            ///< must be 0 (default) or a valid combination of ::ze_fence_flag_t.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        fence_handle_t m_handle;                        ///< [in] handle of fence object
        CommandQueue* m_pCommandQueue;                  ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the fence object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Fence( void ) = delete;
        Fence( 
            fence_handle_t handle,                          ///< [in] handle of fence object
            CommandQueue* pCommandQueue,                    ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the fence object
            );

        ~Fence( void ) = default;

        Fence( Fence const& other ) = delete;
        void operator=( Fence const& other ) = delete;

        Fence( Fence&& other ) = delete;
        void operator=( Fence&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getCommandqueue( void ) const { return m_pCommandQueue; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - Fence*: pointer to handle of fence object created
        /// 
        /// @throws result_t
        static Fence* ZE_APICALL
        Create(
            CommandQueue* pCommandQueue,                    ///< [in] pointer to command queue
            const desc_t* desc                              ///< [in] pointer to fence descriptor
            );

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
        /// @throws result_t
        static void ZE_APICALL
        Destroy(
            Fence* pFence                                   ///< [in][release] pointer to fence object to destroy
            );

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
        /// @returns
        ///     - bool_t:'0' when RESULT_NOT_READY
        /// @throws result_t
        bool_t ZE_APICALL
        HostSynchronize(
            uint64_t timeout                                ///< [in] if non-zero, then indicates the maximum time (in nanoseconds) to
                                                            ///< yield before returning ::ZE_RESULT_SUCCESS or ::ZE_RESULT_NOT_READY;
                                                            ///< if zero, then operates exactly like ::zeFenceQueryStatus;
                                                            ///< if UINT64_MAX, then function will not return until complete or device
                                                            ///< is lost.
                                                            ///< Due to external dependencies, timeout may be rounded to the closest
                                                            ///< value allowed by the accuracy of those dependencies.
            );

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
        /// @returns
        ///     - bool_t:'0' when RESULT_NOT_READY
        /// @throws result_t
        bool_t ZE_APICALL
        QueryStatus(
            void
            );

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
        /// @throws result_t
        void ZE_APICALL
        Reset(
            void
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::flags_t to std::string
    std::string to_string( const Fence::flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Fence::desc_t to std::string
    std::string to_string( const Fence::desc_t val );

} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero APIs for Images
#pragma region image
namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for image
    class Image
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported image creation flags
        struct flags_t
        {
            uint32_t value;
            flags_t() : value(0) {}
            flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum flag_t
        {
            FLAG_KERNEL_WRITE = ZE_BIT(0),                  ///< kernels will write contents
            FLAG_BIAS_UNCACHED = ZE_BIT(1),                 ///< device should not cache contents
            FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported image types
        enum class type_t : uint32_t
        {
            _1D = 0,                                        ///< 1D
            _1DARRAY = 1,                                   ///< 1D array
            _2D = 2,                                        ///< 2D
            _2DARRAY = 3,                                   ///< 2D array
            _3D = 4,                                        ///< 3D
            BUFFER = 5,                                     ///< Buffer
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported image format layouts
        enum class format_layout_t : uint32_t
        {
            _8 = 0,                                         ///< 8-bit single component layout
            _16 = 1,                                        ///< 16-bit single component layout
            _32 = 2,                                        ///< 32-bit single component layout
            _8_8 = 3,                                       ///< 2-component 8-bit layout
            _8_8_8_8 = 4,                                   ///< 4-component 8-bit layout
            _16_16 = 5,                                     ///< 2-component 16-bit layout
            _16_16_16_16 = 6,                               ///< 4-component 16-bit layout
            _32_32 = 7,                                     ///< 2-component 32-bit layout
            _32_32_32_32 = 8,                               ///< 4-component 32-bit layout
            _10_10_10_2 = 9,                                ///< 4-component 10_10_10_2 layout
            _11_11_10 = 10,                                 ///< 3-component 11_11_10 layout
            _5_6_5 = 11,                                    ///< 3-component 5_6_5 layout
            _5_5_5_1 = 12,                                  ///< 4-component 5_5_5_1 layout
            _4_4_4_4 = 13,                                  ///< 4-component 4_4_4_4 layout
            Y8 = 14,                                        ///< Media Format: Y8. Format type and swizzle is ignored for this.
            NV12 = 15,                                      ///< Media Format: NV12. Format type and swizzle is ignored for this.
            YUYV = 16,                                      ///< Media Format: YUYV. Format type and swizzle is ignored for this.
            VYUY = 17,                                      ///< Media Format: VYUY. Format type and swizzle is ignored for this.
            YVYU = 18,                                      ///< Media Format: YVYU. Format type and swizzle is ignored for this.
            UYVY = 19,                                      ///< Media Format: UYVY. Format type and swizzle is ignored for this.
            AYUV = 20,                                      ///< Media Format: AYUV. Format type and swizzle is ignored for this.
            P010 = 21,                                      ///< Media Format: P010. Format type and swizzle is ignored for this.
            Y410 = 22,                                      ///< Media Format: Y410. Format type and swizzle is ignored for this.
            P012 = 23,                                      ///< Media Format: P012. Format type and swizzle is ignored for this.
            Y16 = 24,                                       ///< Media Format: Y16. Format type and swizzle is ignored for this.
            P016 = 25,                                      ///< Media Format: P016. Format type and swizzle is ignored for this.
            Y216 = 26,                                      ///< Media Format: Y216. Format type and swizzle is ignored for this.
            P216 = 27,                                      ///< Media Format: P216. Format type and swizzle is ignored for this.
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported image format types
        enum class format_type_t : uint32_t
        {
            UINT = 0,                                       ///< Unsigned integer
            SINT = 1,                                       ///< Signed integer
            UNORM = 2,                                      ///< Unsigned normalized integer
            SNORM = 3,                                      ///< Signed normalized integer
            FLOAT = 4,                                      ///< Float
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported image format component swizzle into channel
        enum class format_swizzle_t : uint32_t
        {
            R = 0,                                          ///< Red component
            G = 1,                                          ///< Green component
            B = 2,                                          ///< Blue component
            A = 3,                                          ///< Alpha component
            _0 = 4,                                         ///< Zero
            _1 = 5,                                         ///< One
            X = 6,                                          ///< Don't care
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported sampler filtering flags
        struct sampler_filter_flags_t
        {
            uint32_t value;
            sampler_filter_flags_t() : value(0) {}
            sampler_filter_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum sampler_filter_flag_t
        {
            SAMPLER_FILTER_FLAG_POINT = ZE_BIT(0),          ///< device supports point filtering
            SAMPLER_FILTER_FLAG_LINEAR = ZE_BIT(1),         ///< device supports linear filtering
            SAMPLER_FILTER_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Image format 
        struct format_t
        {
            format_layout_t layout;                         ///< [in] image format component layout
            format_type_t type;                             ///< [in] image format type. Media formats can't be used for
                                                            ///< ::ZE_IMAGE_TYPE_BUFFER.
            format_swizzle_t x;                             ///< [in] image component swizzle into channel x
            format_swizzle_t y;                             ///< [in] image component swizzle into channel y
            format_swizzle_t z;                             ///< [in] image component swizzle into channel z
            format_swizzle_t w;                             ///< [in] image component swizzle into channel w

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Image descriptor
        struct desc_t
        {
            structure_type_t stype = structure_type_t::IMAGE_DESC;  ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            flags_t flags;                                  ///< [in] creation flags.
                                                            ///< must be 0 (default) or a valid combination of ::ze_image_flag_t;
                                                            ///< default is read-only, cached access.
            type_t type;                                    ///< [in] image type
            format_t format;                                ///< [in] image format
            uint64_t width = 0;                             ///< [in] width dimension.
                                                            ///< ::ZE_IMAGE_TYPE_BUFFER: size in bytes; see
                                                            ///< ::ze_device_image_properties_t.maxImageBufferSize for limits.
                                                            ///< ::ZE_IMAGE_TYPE_1D, ::ZE_IMAGE_TYPE_1DARRAY: width in pixels; see
                                                            ///< ::ze_device_image_properties_t.maxImageDims1D for limits.
                                                            ///< ::ZE_IMAGE_TYPE_2D, ::ZE_IMAGE_TYPE_2DARRAY: width in pixels; see
                                                            ///< ::ze_device_image_properties_t.maxImageDims2D for limits.
                                                            ///< ::ZE_IMAGE_TYPE_3D: width in pixels; see
                                                            ///< ::ze_device_image_properties_t.maxImageDims3D for limits.
            uint32_t height = 0;                            ///< [in] height dimension.
                                                            ///< ::ZE_IMAGE_TYPE_2D, ::ZE_IMAGE_TYPE_2DARRAY: height in pixels; see
                                                            ///< ::ze_device_image_properties_t.maxImageDims2D for limits.
                                                            ///< ::ZE_IMAGE_TYPE_3D: height in pixels; see
                                                            ///< ::ze_device_image_properties_t.maxImageDims3D for limits.
                                                            ///< other: ignored.
            uint32_t depth = 0;                             ///< [in] depth dimension.
                                                            ///< ::ZE_IMAGE_TYPE_3D: depth in pixels; see
                                                            ///< ::ze_device_image_properties_t.maxImageDims3D for limits.
                                                            ///< other: ignored.
            uint32_t arraylevels = 1;                       ///< [in] array levels.
                                                            ///< ::ZE_IMAGE_TYPE_1DARRAY, ::ZE_IMAGE_TYPE_2DARRAY: see
                                                            ///< ::ze_device_image_properties_t.maxImageArraySlices for limits.
                                                            ///< other: ignored.
            uint32_t miplevels = 0;                         ///< [in] mipmap levels (must be 0)

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Image properties
        struct properties_t
        {
            structure_type_t stype = structure_type_t::IMAGE_PROPERTIES;///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            sampler_filter_flags_t samplerFilterFlags;      ///< [out] supported sampler filtering.
                                                            ///< returns 0 (unsupported) or a combination of ::ze_image_sampler_filter_flag_t.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        image_handle_t m_handle;                        ///< [in] handle of image object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the image object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Image( void ) = delete;
        Image( 
            image_handle_t handle,                          ///< [in] handle of image object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the image object
            );

        ~Image( void ) = default;

        Image( Image const& other ) = delete;
        void operator=( Image const& other ) = delete;

        Image( Image&& other ) = delete;
        void operator=( Image&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves supported properties of an image.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - properties_t: pointer to image properties
        /// 
        /// @throws result_t
        static properties_t ZE_APICALL
        GetProperties(
            Device* pDevice,                                ///< [in] pointer to the device
            const desc_t* desc                              ///< [in] pointer to image descriptor
            );

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
        /// @returns
        ///     - Image*: pointer to handle of image object created
        /// 
        /// @throws result_t
        static Image* ZE_APICALL
        Create(
            Context* pContext,                              ///< [in] pointer to the context object
            Device* pDevice,                                ///< [in] pointer to the device
            const desc_t* desc                              ///< [in] pointer to image descriptor
            );

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
        /// @throws result_t
        static void ZE_APICALL
        Destroy(
            Image* pImage                                   ///< [in][release] pointer to image object to destroy
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::flags_t to std::string
    std::string to_string( const Image::flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::type_t to std::string
    std::string to_string( const Image::type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_layout_t to std::string
    std::string to_string( const Image::format_layout_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_type_t to std::string
    std::string to_string( const Image::format_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_swizzle_t to std::string
    std::string to_string( const Image::format_swizzle_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::format_t to std::string
    std::string to_string( const Image::format_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::desc_t to std::string
    std::string to_string( const Image::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::sampler_filter_flags_t to std::string
    std::string to_string( const Image::sampler_filter_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Image::properties_t to std::string
    std::string to_string( const Image::properties_t val );

} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero APIs for Memory
#pragma region memory
namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for memory allocation
    class Mem
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported memory allocation flags
        struct device_alloc_flags_t
        {
            uint32_t value;
            device_alloc_flags_t() : value(0) {}
            device_alloc_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum device_alloc_flag_t
        {
            DEVICE_ALLOC_FLAG_BIAS_CACHED = ZE_BIT(0),      ///< device should cache allocation
            DEVICE_ALLOC_FLAG_BIAS_UNCACHED = ZE_BIT(1),    ///< device should not cache allocation (UC)
            DEVICE_ALLOC_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported host memory allocation flags
        struct host_alloc_flags_t
        {
            uint32_t value;
            host_alloc_flags_t() : value(0) {}
            host_alloc_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum host_alloc_flag_t
        {
            HOST_ALLOC_FLAG_BIAS_CACHED = ZE_BIT(0),        ///< host should cache allocation
            HOST_ALLOC_FLAG_BIAS_UNCACHED = ZE_BIT(1),      ///< host should not cache allocation (UC)
            HOST_ALLOC_FLAG_BIAS_WRITE_COMBINED = ZE_BIT(2),///< host memory should be allocated write-combined (WC)
            HOST_ALLOC_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory allocation type
        enum class memory_type_t : uint32_t
        {
            UNKNOWN = 0,                                    ///< the memory pointed to is of unknown type
            HOST = 1,                                       ///< the memory pointed to is a host allocation
            DEVICE = 2,                                     ///< the memory pointed to is a device allocation
            SHARED = 3,                                     ///< the memory pointed to is a shared ownership allocation
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported IPC memory flags
        struct ipc_memory_flags_t
        {
            uint32_t value;
            ipc_memory_flags_t() : value(0) {}
            ipc_memory_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum ipc_memory_flag_t
        {
            IPC_MEMORY_FLAG_TBD = ZE_BIT(0),                ///< reserved for future use
            IPC_MEMORY_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device memory allocation descriptor
        struct device_alloc_desc_t
        {
            structure_type_t stype = structure_type_t::DEVICE_MEM_ALLOC_DESC;   ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            device_alloc_flags_t flags = 0;                 ///< [in] flags specifying additional allocation controls.
                                                            ///< must be 0 (default) or a valid combination of ::ze_device_mem_alloc_flag_t;
                                                            ///< default behavior may use implicit driver-based heuristics.
            uint32_t ordinal = 0;                           ///< [in] ordinal of the device's local memory to allocate from.
                                                            ///< must be less than the count returned from ::zeDeviceGetMemoryProperties.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Host memory allocation descriptor
        struct host_alloc_desc_t
        {
            structure_type_t stype = structure_type_t::HOST_MEM_ALLOC_DESC; ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            host_alloc_flags_t flags = 0;                   ///< [in] flags specifying additional allocation controls.
                                                            ///< must be 0 (default) or a valid combination of ::ze_host_mem_alloc_flag_t;
                                                            ///< default behavior may use implicit driver-based heuristics.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory allocation properties queried using ::zeMemGetAllocProperties
        struct memory_allocation_properties_t
        {
            structure_type_t stype = structure_type_t::MEMORY_ALLOCATION_PROPERTIES;///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            memory_type_t type;                             ///< [out] type of allocated memory
            uint64_t id;                                    ///< [out] identifier for this allocation
            uint64_t pageSize;                              ///< [out] page size used for allocation

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Additional allocation descriptor for exporting external memory
        /// 
        /// @details
        ///     - This structure may be passed to ::zeMemAllocDevice, via the `pNext`
        ///       member of ::ze_device_mem_alloc_desc_t, to indicate an exportable
        ///       memory allocation.
        ///     - This structure may be passed to ::zeImageCreate, via the `pNext`
        ///       member of ::ze_image_desc_t, to indicate an exportable image.
        struct external_memory_export_desc_t
        {
            structure_type_t stype = structure_type_t::EXTERNAL_MEMORY_EXPORT_DESC; ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            external_memory_type_flags_t flags = 0;         ///< [in] flags specifying memory export types for this allocation.
                                                            ///< must be 0 (default) or a valid combination of ::ze_external_memory_type_flags_t

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Additional allocation descriptor for importing external memory as a
        ///        file descriptor
        /// 
        /// @details
        ///     - This structure may be passed to ::zeMemAllocDevice, via the `pNext`
        ///       member of ::ze_device_mem_alloc_desc_t, to import memory from a file
        ///       descriptor.
        ///     - This structure may be passed to ::zeImageCreate, via the `pNext`
        ///       member of ::ze_image_desc_t, to import memory from a file descriptor.
        struct external_memory_import_fd_t
        {
            structure_type_t stype = structure_type_t::EXTERNAL_MEMORY_IMPORT_FD;   ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            external_memory_type_flags_t flags = 0;         ///< [in] flags specifying the memory import type for the file descriptor.
                                                            ///< must be 0 (default) or a valid combination of ::ze_external_memory_type_flags_t
            int fd;                                         ///< [in] the file descriptor handle to import

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Exports an allocation as a file descriptor
        /// 
        /// @details
        ///     - This structure may be passed to ::zeMemGetAllocProperties, via the
        ///       `pNext` member of ::ze_memory_allocation_properties_t, to export a
        ///       memory allocation as a file descriptor.
        ///     - This structure may be passed to ::zeImageGetProperties, via the
        ///       `pNext` member of ::ze_image_properties_t, to export an image as a
        ///       file descriptor.
        ///     - The requested memory export type must have been specified when the
        ///       allocation was made.
        struct external_memory_export_fd_t
        {
            structure_type_t stype = structure_type_t::EXTERNAL_MEMORY_EXPORT_FD;   ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            external_memory_type_flags_t flags = 0;         ///< [in] flags specifying the memory export type for the file descriptor.
                                                            ///< must be 0 (default) or a valid combination of ::ze_external_memory_type_flags_t
            int fd;                                         ///< [out] the exported file descriptor handle representing the allocation.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Mem( void ) = delete;
        ~Mem( void ) = delete;

        Mem( Mem const& other ) = delete;
        void operator=( Mem const& other ) = delete;

        Mem( Mem&& other ) = delete;
        void operator=( Mem&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

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
        /// @returns
        ///     - void*: pointer to shared allocation
        /// 
        /// @throws result_t
        static void* ZE_APICALL
        AllocShared(
            Context* pContext,                              ///< [in] pointer to the context object
            const device_alloc_desc_t* device_desc,         ///< [in] pointer to device memory allocation descriptor
            const host_alloc_desc_t* host_desc,             ///< [in] pointer to host memory allocation descriptor
            size_t size,                                    ///< [in] size in bytes to allocate; must be less-than
                                                            ///< ::ze_device_properties_t.maxMemAllocSize.
            size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                            ///< two.
            Device* pDevice = nullptr                       ///< [in][optional] device handle to associate with
            );

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
        /// @returns
        ///     - void*: pointer to device allocation
        /// 
        /// @throws result_t
        static void* ZE_APICALL
        AllocDevice(
            Context* pContext,                              ///< [in] pointer to the context object
            const device_alloc_desc_t* device_desc,         ///< [in] pointer to device memory allocation descriptor
            size_t size,                                    ///< [in] size in bytes to allocate; must be less-than
                                                            ///< ::ze_device_properties_t.maxMemAllocSize.
            size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                            ///< two.
            Device* pDevice                                 ///< [in] pointer to the device
            );

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
        /// @returns
        ///     - void*: pointer to host allocation
        /// 
        /// @throws result_t
        static void* ZE_APICALL
        AllocHost(
            Context* pContext,                              ///< [in] pointer to the context object
            const host_alloc_desc_t* host_desc,             ///< [in] pointer to host memory allocation descriptor
            size_t size,                                    ///< [in] size in bytes to allocate; must be less-than
                                                            ///< ::ze_device_properties_t.maxMemAllocSize.
            size_t alignment                                ///< [in] minimum alignment in bytes for the allocation; must be a power of
                                                            ///< two.
            );

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
        /// @throws result_t
        static void ZE_APICALL
        Free(
            Context* pContext,                              ///< [in] pointer to the context object
            void* ptr                                       ///< [in][release] pointer to memory to free
            );

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
        /// @returns
        ///     - Device*: device associated with this allocation
        /// 
        /// @throws result_t
        static void ZE_APICALL
        GetAllocProperties(
            Context* pContext,                              ///< [in] pointer to the context object
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
        static void ZE_APICALL
        GetAddressRange(
            Context* pContext,                              ///< [in] pointer to the context object
            const void* ptr,                                ///< [in] memory pointer to query
            void** pBase = nullptr,                         ///< [in,out][optional] base address of the allocation
            size_t* pSize = nullptr                         ///< [in,out][optional] size of the allocation
            );

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
        /// @returns
        ///     - ipc_mem_handle_t: Returned IPC memory handle
        /// 
        /// @throws result_t
        static ipc_mem_handle_t ZE_APICALL
        GetIpcHandle(
            Context* pContext,                              ///< [in] pointer to the context object
            const void* ptr                                 ///< [in] pointer to the device memory allocation
            );

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
        /// @returns
        ///     - void*: pointer to device allocation in this process
        /// 
        /// @throws result_t
        static void* ZE_APICALL
        OpenIpcHandle(
            Context* pContext,                              ///< [in] pointer to the context object
            Device* pDevice,                                ///< [in] pointer to the device to associate with the IPC memory handle
            ipc_mem_handle_t handle,                        ///< [in] IPC memory handle
            ipc_memory_flags_t flags                        ///< [in] flags controlling the operation.
                                                            ///< must be 0 (default) or a valid combination of ::ze_ipc_memory_flag_t.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Closes an IPC memory handle
        /// 
        /// @details
        ///     - Closes an IPC memory handle by unmapping memory that was opened in
        ///       this process using ::zeMemOpenIpcHandle.
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same pointer.
        ///     - The implementation of this function must be thread-safe.
        /// @throws result_t
        static void ZE_APICALL
        CloseIpcHandle(
            Context* pContext,                              ///< [in] pointer to the context object
            const void* ptr                                 ///< [in][release] pointer to device allocation in this process
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::device_alloc_flags_t to std::string
    std::string to_string( const Mem::device_alloc_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::device_alloc_desc_t to std::string
    std::string to_string( const Mem::device_alloc_desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::host_alloc_flags_t to std::string
    std::string to_string( const Mem::host_alloc_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::host_alloc_desc_t to std::string
    std::string to_string( const Mem::host_alloc_desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::memory_type_t to std::string
    std::string to_string( const Mem::memory_type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::memory_allocation_properties_t to std::string
    std::string to_string( const Mem::memory_allocation_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::ipc_memory_flags_t to std::string
    std::string to_string( const Mem::ipc_memory_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::external_memory_export_desc_t to std::string
    std::string to_string( const Mem::external_memory_export_desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::external_memory_import_fd_t to std::string
    std::string to_string( const Mem::external_memory_import_fd_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Mem::external_memory_export_fd_t to std::string
    std::string to_string( const Mem::external_memory_export_fd_t val );

} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero APIs for Module
#pragma region module
///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_KERNEL_UUID_SIZE
/// @brief Maximum kernel universal unique id (UUID) size in bytes
#define ZE_MAX_KERNEL_UUID_SIZE  16
#endif // ZE_MAX_KERNEL_UUID_SIZE

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_MODULE_UUID_SIZE
/// @brief Maximum module universal unique id (UUID) size in bytes
#define ZE_MAX_MODULE_UUID_SIZE  16
#endif // ZE_MAX_MODULE_UUID_SIZE

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Kernel universal unique id (UUID)
    struct kernel_uuid_t
    {
        uint8_t kid[ZE_MAX_KERNEL_UUID_SIZE];           ///< [out] opaque data representing a kernel UUID
        uint8_t mid[ZE_MAX_MODULE_UUID_SIZE];           ///< [out] opaque data representing the kernel's module UUID

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for module
    class Module
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported module creation input formats
        enum class format_t : uint32_t
        {
            IL_SPIRV = 0,                                   ///< Format is SPIRV IL format
            NATIVE = 1,                                     ///< Format is device native format
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported module property flags
        struct property_flags_t
        {
            uint32_t value;
            property_flags_t() : value(0) {}
            property_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum property_flag_t
        {
            PROPERTY_FLAG_IMPORTS = ZE_BIT(0),              ///< Module has imports (i.e. imported global variables and/or kernels).
                                                            ///< See ::zeModuleDynamicLink.
            PROPERTY_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Specialization constants - User defined constants
        struct constants_t
        {
            uint32_t numConstants;                          ///< [in] Number of specialization constants.
            const uint32_t* pConstantIds;                   ///< [in][range(0, numConstants)] Array of IDs that is sized to
                                                            ///< numConstants.
            const void** pConstantValues;                   ///< [in][range(0, numConstants)] Array of pointers to values that is sized
                                                            ///< to numConstants.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Module descriptor
        struct desc_t
        {
            structure_type_t stype = structure_type_t::MODULE_DESC; ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            format_t format;                                ///< [in] Module format passed in with pInputModule
            size_t inputSize = 0;                           ///< [in] size of input IL or ISA from pInputModule.
            const uint8_t* pInputModule = nullptr;          ///< [in] pointer to IL or ISA
            const char* pBuildFlags = nullptr;              ///< [in][optional] string containing compiler flags. Following options are supported.
                                                            ///<  - "-ze-opt-disable"
                                                            ///<       - Disable optimizations
                                                            ///<  - "-ze-opt-greater-than-4GB-buffer-required"
                                                            ///<       - Use 64-bit offset calculations for buffers.
                                                            ///<  - "-ze-opt-large-register-file"
                                                            ///<       - Increase number of registers available to threads.
                                                            ///<  - "-ze-opt-has-buffer-offset-arg"
                                                            ///<       - Extend stateless to stateful optimization to more
                                                            ///<         cases with the use of additional offset (e.g. 64-bit
                                                            ///<         pointer to binding table with 32-bit offset).
                                                            ///<  - "-g"
                                                            ///<       - Include debugging information.
            const constants_t* pConstants = nullptr;        ///< [in][optional] pointer to specialization constants. Valid only for
                                                            ///< SPIR-V input. This must be set to nullptr if no specialization
                                                            ///< constants are provided.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Module properties
        struct properties_t
        {
            structure_type_t stype = structure_type_t::MODULE_PROPERTIES;   ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            property_flags_t flags;                         ///< [out] 0 (none) or a valid combination of ::ze_module_property_flag_t

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        module_handle_t m_handle;                       ///< [in] handle of module object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the module object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Module( void ) = delete;
        Module( 
            module_handle_t handle,                         ///< [in] handle of module object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the module object
            );

        ~Module( void ) = default;

        Module( Module const& other ) = delete;
        void operator=( Module const& other ) = delete;

        Module( Module&& other ) = delete;
        void operator=( Module&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - Module*: pointer to handle of module object created
        ///     - ModuleBuildLog*: pointer to handle of module's build log.
        /// 
        /// @throws result_t
        static Module* ZE_APICALL
        Create(
            Context* pContext,                              ///< [in] pointer to the context object
            Device* pDevice,                                ///< [in] pointer to the device
            const desc_t* desc,                             ///< [in] pointer to module descriptor
            ModuleBuildLog** ppBuildLog = nullptr           ///< [out][optional] pointer to pointer to module's build log.
            );

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
        /// @throws result_t
        static void ZE_APICALL
        Destroy(
            Module* pModule                                 ///< [in][release] pointer to the module
            );

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
        /// @returns
        ///     - ModuleBuildLog*: pointer to handle of dynamic link log.
        /// 
        /// @throws result_t
        static void ZE_APICALL
        DynamicLink(
            uint32_t numModules,                            ///< [in] number of modules to be linked pointed to by phModules.
            Module** ppModules,                             ///< [in][range(0, numModules)] pointer to an array of modules to
                                                            ///< dynamically link together.
            ModuleBuildLog** ppLinkLog = nullptr            ///< [out][optional] pointer to pointer to dynamic link log.
            );

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
        /// @throws result_t
        void ZE_APICALL
        GetNativeBinary(
            size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
            uint8_t* pModuleNativeBinary = nullptr          ///< [in,out][optional] byte pointer to native binary
            );

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
        /// @throws result_t
        void ZE_APICALL
        GetGlobalPointer(
            const char* pGlobalName,                        ///< [in] name of global variable in module
            size_t* pSize = nullptr,                        ///< [in,out][optional] size of global variable
            void** pptr = nullptr                           ///< [in,out][optional] device visible pointer
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve all kernel names in the module.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void ZE_APICALL
        GetKernelNames(
            uint32_t* pCount,                               ///< [in,out] pointer to the number of names.
                                                            ///< if count is zero, then the driver will update the value with the total
                                                            ///< number of names available.
                                                            ///< if count is non-zero, then driver will only retrieve that number of names.
                                                            ///< if count is larger than the number of names available, then the driver
                                                            ///< will update the value with the correct number of names available.
            const char** pNames = nullptr                   ///< [in,out][optional][range(0, *pCount)] array of names of functions
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve module properties.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void ZE_APICALL
        GetProperties(
            properties_t* pModuleProperties                 ///< [in,out] query result for module properties.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve a function pointer from a module by name
        /// 
        /// @details
        ///     - The function pointer is unique for the device on which the module was
        ///       created.
        ///     - The function pointer is no longer valid if module is destroyed.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - void*: pointer to function.
        /// 
        /// @throws result_t
        void* ZE_APICALL
        GetFunctionPointer(
            const char* pFunctionName                       ///< [in] Name of function to retrieve function pointer for.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for buildlog
    class ModuleBuildLog
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////
        module_build_log_handle_t m_handle;             ///< [in] handle of the buildlog object
        Module* m_pModule;                              ///< [in] pointer to owner object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        ModuleBuildLog( void ) = delete;
        ModuleBuildLog( 
            module_build_log_handle_t handle,               ///< [in] handle of the buildlog object
            Module* pModule                                 ///< [in] pointer to owner object
            );

        ~ModuleBuildLog( void ) = default;

        ModuleBuildLog( ModuleBuildLog const& other ) = delete;
        void operator=( ModuleBuildLog const& other ) = delete;

        ModuleBuildLog( ModuleBuildLog&& other ) = delete;
        void operator=( ModuleBuildLog&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getModule( void ) const { return m_pModule; }

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
        /// @throws result_t
        static void ZE_APICALL
        Destroy(
            ModuleBuildLog* pModuleBuildLog                 ///< [in][release] pointer to the module build log object.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves text string for build log.
        /// 
        /// @details
        ///     - The caller can pass nullptr for pBuildLog when querying only for size.
        ///     - The caller must provide memory for build log.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void ZE_APICALL
        GetString(
            size_t* pSize,                                  ///< [in,out] size of build log string.
            char* pBuildLog = nullptr                       ///< [in,out][optional] pointer to null-terminated string of the log.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for kernel
    class Kernel
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported kernel creation flags
        struct flags_t
        {
            uint32_t value;
            flags_t() : value(0) {}
            flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum flag_t
        {
            FLAG_FORCE_RESIDENCY = ZE_BIT(0),               ///< force all device allocations to be resident during execution
            FLAG_EXPLICIT_RESIDENCY = ZE_BIT(1),            ///< application is responsible for all residency of device allocations.
                                                            ///< driver may disable implicit residency management.
            FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel indirect access flags
        struct indirect_access_flags_t
        {
            uint32_t value;
            indirect_access_flags_t() : value(0) {}
            indirect_access_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum indirect_access_flag_t
        {
            INDIRECT_ACCESS_FLAG_HOST = ZE_BIT(0),          ///< Indicates that the kernel accesses host allocations indirectly.
            INDIRECT_ACCESS_FLAG_DEVICE = ZE_BIT(1),        ///< Indicates that the kernel accesses device allocations indirectly.
            INDIRECT_ACCESS_FLAG_SHARED = ZE_BIT(2),        ///< Indicates that the kernel accesses shared allocations indirectly.
            INDIRECT_ACCESS_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported Cache Config flags
        struct cache_config_flags_t
        {
            uint32_t value;
            cache_config_flags_t() : value(0) {}
            cache_config_flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum cache_config_flag_t
        {
            CACHE_CONFIG_FLAG_LARGE_SLM = ZE_BIT(0),        ///< Large SLM size
            CACHE_CONFIG_FLAG_LARGE_DATA = ZE_BIT(1),       ///< Large General Data size
            CACHE_CONFIG_FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel descriptor
        struct desc_t
        {
            structure_type_t stype = structure_type_t::KERNEL_DESC; ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            flags_t flags = 0;                              ///< [in] creation flags.
                                                            ///< must be 0 (default) or a valid combination of ::ze_kernel_flag_t;
                                                            ///< default behavior may use driver-based residency.
            const char* pKernelName = nullptr;              ///< [in] null-terminated name of kernel in module

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Kernel properties
        struct properties_t
        {
            structure_type_t stype = structure_type_t::KERNEL_PROPERTIES;   ///< [in] type of this structure
            void* pNext = nullptr;                          ///< [in,out][optional] pointer to extension-specific structure
            uint32_t numKernelArgs;                         ///< [out] number of kernel arguments.
            uint32_t requiredGroupSizeX;                    ///< [out] required group size in the X dimension,
                                                            ///< or zero if there is no required group size
            uint32_t requiredGroupSizeY;                    ///< [out] required group size in the Y dimension,
                                                            ///< or zero if there is no required group size
            uint32_t requiredGroupSizeZ;                    ///< [out] required group size in the Z dimension,
                                                            ///< or zero if there is no required group size
            uint32_t requiredNumSubGroups;                  ///< [out] required number of subgroups per thread group,
                                                            ///< or zero if there is no required number of subgroups
            uint32_t requiredSubgroupSize;                  ///< [out] required subgroup size,
                                                            ///< or zero if there is no required subgroup size
            uint32_t maxSubgroupSize;                       ///< [out] maximum subgroup size
            uint32_t maxNumSubgroups;                       ///< [out] maximum number of subgroups per thread group
            uint32_t localMemSize;                          ///< [out] local memory size used by each thread group
            uint32_t privateMemSize;                        ///< [out] private memory size allocated by compiler used by each thread
            uint32_t spillMemSize;                          ///< [out] spill memory size allocated by compiler
            kernel_uuid_t uuid;                             ///< [out] universal unique identifier.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        kernel_handle_t m_handle;                       ///< [in] handle of kernel object
        Module* m_pModule;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the kernel object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Kernel( void ) = delete;
        Kernel( 
            kernel_handle_t handle,                         ///< [in] handle of kernel object
            Module* pModule,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the kernel object
            );

        ~Kernel( void ) = default;

        Kernel( Kernel const& other ) = delete;
        void operator=( Kernel const& other ) = delete;

        Kernel( Kernel&& other ) = delete;
        void operator=( Kernel&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getModule( void ) const { return m_pModule; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Create a kernel from the module.
        /// 
        /// @details
        ///     - Modules that have unresolved imports need to be dynamically linked
        ///       before a kernel can be created from them. (See ::zeModuleDynamicLink)
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function must be thread-safe.
        /// @returns
        ///     - Kernel*: handle of the Function object
        /// 
        /// @throws result_t
        static Kernel* ZE_APICALL
        Create(
            Module* pModule,                                ///< [in] pointer to the module
            const desc_t* desc                              ///< [in] pointer to kernel descriptor
            );

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
        /// @throws result_t
        static void ZE_APICALL
        Destroy(
            Kernel* pKernel                                 ///< [in][release] pointer to the kernel object
            );

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
        /// @throws result_t
        void ZE_APICALL
        SetCacheConfig(
            cache_config_flags_t flags                      ///< [in] cache configuration. 
                                                            ///< must be 0 (default configuration) or a valid combination of ::ze_cache_config_flag_t.
            );

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
        /// @throws result_t
        void ZE_APICALL
        SetGroupSize(
            uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
            uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
            uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Query a suggested group size for a kernel given a global size for each
        ///        dimension.
        /// 
        /// @details
        ///     - This function ignores the group size that is set using
        ///       ::zeKernelSetGroupSize.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - uint32_t: recommended size of group for X dimension
        ///     - uint32_t: recommended size of group for Y dimension
        ///     - uint32_t: recommended size of group for Z dimension
        /// 
        /// @throws result_t
        std::tuple<uint32_t, uint32_t, uint32_t> ZE_APICALL
        SuggestGroupSize(
            uint32_t globalSizeX,                           ///< [in] global width for X dimension
            uint32_t globalSizeY,                           ///< [in] global width for Y dimension
            uint32_t globalSizeZ                            ///< [in] global width for Z dimension
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Query a suggested max group count for a cooperative kernel.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - uint32_t: recommended total group count.
        /// 
        /// @throws result_t
        uint32_t ZE_APICALL
        SuggestMaxCooperativeGroupCount(
            void
            );

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
        /// @throws result_t
        void ZE_APICALL
        SetArgumentValue(
            uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
            size_t argSize,                                 ///< [in] size of argument type
            const void* pArgValue = nullptr                 ///< [in][optional] argument value represented as matching arg type. If
                                                            ///< null then argument value is considered null.
            );

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
        /// @throws result_t
        void ZE_APICALL
        SetIndirectAccess(
            indirect_access_flags_t flags                   ///< [in] kernel indirect access flags
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve kernel indirect access flags.
        /// 
        /// @details
        ///     - This function may be called from simultaneous threads with the same
        ///       Kernel handle.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - indirect_access_flags_t: query result for kernel indirect access flags.
        /// 
        /// @throws result_t
        indirect_access_flags_t ZE_APICALL
        GetIndirectAccess(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve all declared kernel attributes (i.e. can be specified with
        ///        __attribute__ in runtime language).
        /// 
        /// @details
        ///     - This function may be called from simultaneous threads with the same
        ///       Kernel handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void ZE_APICALL
        GetSourceAttributes(
            uint32_t* pSize,                                ///< [in,out] pointer to size of string in bytes.
                                                            ///< if size is zero, then the driver will update string argument.
                                                            ///< if size is non-zero, then driver will only retrieve string size in bytes.
                                                            ///< if size is larger than source attributes string, then the driver will
                                                            ///< update the string.
            char** pString = nullptr                        ///< [in,out][optional] pointer to null-terminated string where kernel
                                                            ///< source attributes are separated by space.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve kernel properties.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void ZE_APICALL
        GetProperties(
            properties_t* pKernelProperties                 ///< [in,out] query result for kernel properties.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieve kernel name from Kernel.
        /// 
        /// @details
        ///     - The caller can pass nullptr for pName when querying only for size.
        ///     - The implementation will copy the kernel name into a buffer supplied by
        ///       the caller.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void ZE_APICALL
        GetName(
            size_t* pSize,                                  ///< [in,out] size of kernel name string, including null terminator, in
                                                            ///< bytes.
            char* pName = nullptr                           ///< [in,out][optional] char pointer to kernel name.
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts kernel_uuid_t to std::string
    std::string to_string( const kernel_uuid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::format_t to std::string
    std::string to_string( const Module::format_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::constants_t to std::string
    std::string to_string( const Module::constants_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::desc_t to std::string
    std::string to_string( const Module::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::property_flags_t to std::string
    std::string to_string( const Module::property_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Module::properties_t to std::string
    std::string to_string( const Module::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::flags_t to std::string
    std::string to_string( const Kernel::flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::desc_t to std::string
    std::string to_string( const Kernel::desc_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::indirect_access_flags_t to std::string
    std::string to_string( const Kernel::indirect_access_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::cache_config_flags_t to std::string
    std::string to_string( const Kernel::cache_config_flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Kernel::properties_t to std::string
    std::string to_string( const Kernel::properties_t val );

} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero Extension APIs for Raytracing
#pragma region raytracing
///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_RAYTRACING_EXT_NAME
/// @brief Raytracing Extension Name
#define ZE_RAYTRACING_EXT_NAME  "ZE_extension_raytracing"
#endif // ZE_RAYTRACING_EXT_NAME

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Raytracing Extension Version(s)
    enum class raytracing_ext_version_t : uint32_t
    {
        _1_0 = ZE_MAKE_VERSION( 1, 0 ),                 ///< version 1.0
        CURRENT = ZE_MAKE_VERSION( 1, 0 ),              ///< latest known version
        FORCE_UINT32 = 0x7fffffff

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts raytracing_ext_version_t to std::string
    std::string to_string( const raytracing_ext_version_t val );

} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero APIs for Memory Residency
#pragma region residency
namespace ze
{
} // namespace ze

namespace ze
{
} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero APIs for Sampler
#pragma region sampler
namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief c++ wrapper for sampler
    class Sampler
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sampler addressing modes
        enum class address_mode_t : uint32_t
        {
            NONE = 0,                                       ///< No coordinate modifications for out-of-bounds image access.
            REPEAT = 1,                                     ///< Out-of-bounds coordinates are wrapped back around.
            CLAMP = 2,                                      ///< Out-of-bounds coordinates are clamped to edge.
            CLAMP_TO_BORDER = 3,                            ///< Out-of-bounds coordinates are clamped to border color which is (0.0f,
                                                            ///< 0.0f, 0.0f, 0.0f) if image format swizzle contains alpha, otherwise
                                                            ///< (0.0f, 0.0f, 0.0f, 1.0f).
            MIRROR = 4,                                     ///< Out-of-bounds coordinates are mirrored starting from edge.
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sampler filtering modes
        enum class filter_mode_t : uint32_t
        {
            NEAREST = 0,                                    ///< No coordinate modifications for out of bounds image access.
            LINEAR = 1,                                     ///< Out-of-bounds coordinates are wrapped back around.
            FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sampler descriptor
        struct desc_t
        {
            structure_type_t stype = structure_type_t::SAMPLER_DESC;///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            address_mode_t addressMode = address_mode_t::NONE;  ///< [in] Sampler addressing mode to determine how out-of-bounds
                                                            ///< coordinates are handled.
            filter_mode_t filterMode = filter_mode_t::NEAREST;  ///< [in] Sampler filter mode to determine how samples are filtered.
            bool_t isNormalized = true;                     ///< [in] Are coordinates normalized [0, 1] or not.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sampler_handle_t m_handle;                      ///< [in] handle of the sample object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] sampler descriptor

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Sampler( void ) = delete;
        Sampler( 
            sampler_handle_t handle,                        ///< [in] handle of the sample object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] sampler descriptor
            );

        ~Sampler( void ) = default;

        Sampler( Sampler const& other ) = delete;
        void operator=( Sampler const& other ) = delete;

        Sampler( Sampler&& other ) = delete;
        void operator=( Sampler&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates sampler on the context.
        /// 
        /// @details
        ///     - The application must only use the sampler for the device, or its
        ///       sub-devices, which was provided during creation.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function must be thread-safe.
        /// @returns
        ///     - Sampler*: handle of the sampler
        /// 
        /// @throws result_t
        static Sampler* ZE_APICALL
        Create(
            Context* pContext,                              ///< [in] pointer to the context object
            Device* pDevice,                                ///< [in] pointer to the device
            const desc_t* desc                              ///< [in] pointer to sampler descriptor
            );

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
        /// @throws result_t
        static void ZE_APICALL
        Destroy(
            Sampler* pSampler                               ///< [in][release] pointer to the sampler
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::address_mode_t to std::string
    std::string to_string( const Sampler::address_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::filter_mode_t to std::string
    std::string to_string( const Sampler::filter_mode_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::desc_t to std::string
    std::string to_string( const Sampler::desc_t val );

} // namespace ze
#pragma endregion
// Intel 'oneAPI' Level-Zero APIs for Virtual Memory Management
#pragma region virtual
namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for virtual memory allocation
    class VirtualMem
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Virtual memory page access attributes
        enum class memory_access_attribute_t : uint32_t
        {
            NONE = 0,                                       ///< Indicates the memory page is inaccessible.
            READWRITE = 1,                                  ///< Indicates the memory page supports read write access.
            READONLY = 2,                                   ///< Indicates the memory page supports read-only access.
            FORCE_UINT32 = 0x7fffffff

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        VirtualMem( void ) = delete;
        ~VirtualMem( void ) = delete;

        VirtualMem( VirtualMem const& other ) = delete;
        void operator=( VirtualMem const& other ) = delete;

        VirtualMem( VirtualMem&& other ) = delete;
        void operator=( VirtualMem&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

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
        /// @returns
        ///     - void*: pointer to virtual reservation.
        /// 
        /// @throws result_t
        static void* ZE_APICALL
        Reserve(
            Context* pContext,                              ///< [in] pointer to the context object
            const void* pStart,                             ///< [in] pointer to start of region to reserve. If nullptr then
                                                            ///< implementation will choose a start address.
            size_t size                                     ///< [in] size in bytes to reserve; must be page aligned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Free pages in a reserved virtual address range.
        /// 
        /// @details
        ///     - Any existing virtual mappings for the range will be unmapped.
        ///     - Physical allocations objects that were mapped to this range will not
        ///       be destroyed. These need to be destroyed explicitly.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function must be thread-safe.
        /// @throws result_t
        static void ZE_APICALL
        Free(
            Context* pContext,                              ///< [in] pointer to the context object
            const void* ptr,                                ///< [in] pointer to start of region to free.
            size_t size                                     ///< [in] size in bytes to free; must be page aligned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Queries page size to use for aligning virtual memory reservations and
        ///        physical memory allocations.
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function must be thread-safe.
        /// @returns
        ///     - size_t: pointer to page size to use for start address and size alignments.
        /// 
        /// @throws result_t
        static size_t ZE_APICALL
        QueryPageSize(
            Context* pContext,                              ///< [in] pointer to the context object
            Device* pDevice,                                ///< [in] pointer to the device object
            size_t size                                     ///< [in] unaligned allocation size in bytes
            );

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
        /// @throws result_t
        static void ZE_APICALL
        Map(
            Context* pContext,                              ///< [in] pointer to the context object
            const void* ptr,                                ///< [in] pointer to start of virtual address range to map.
            size_t size,                                    ///< [in] size in bytes of virtual address range to map; must be page
                                                            ///< aligned.
            PhysicalMem* pPhysicalMemory,                   ///< [in] handle to physical memory object.
            size_t offset,                                  ///< [in] offset into physical memory allocation object; must be page
                                                            ///< aligned.
            memory_access_attribute_t access                ///< [in] specifies page access attributes to apply to the virtual address
                                                            ///< range.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Unmaps pages in virtual address space from pages from a physical
        ///        memory object.
        /// 
        /// @details
        ///     - The page access attributes for virtual address range will revert back
        ///       to none.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function must be thread-safe.
        /// @throws result_t
        static void ZE_APICALL
        Unmap(
            Context* pContext,                              ///< [in] pointer to the context object
            const void* ptr,                                ///< [in] pointer to start of region to unmap.
            size_t size                                     ///< [in] size in bytes to unmap; must be page aligned.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set memory access attributes for a virtual address range.
        /// 
        /// @details
        ///     - This function may be called from simultaneous threads with the same
        ///       function handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        static void ZE_APICALL
        SetAccessAttribute(
            Context* pContext,                              ///< [in] pointer to the context object
            const void* ptr,                                ///< [in] pointer to start of reserved virtual address region.
            size_t size,                                    ///< [in] size in bytes; must be page aligned.
            memory_access_attribute_t access                ///< [in] specifies page access attributes to apply to the virtual address
                                                            ///< range.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get memory access attribute for a virtual address range.
        /// 
        /// @details
        ///     - If size and outSize are equal then the pages in the specified virtual
        ///       address range have the same access attributes.
        ///     - This function may be called from simultaneous threads with the same
        ///       function handle.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - memory_access_attribute_t: query result for page access attribute.
        ///     - size_t: query result for size of virtual address range, starting at ptr, that shares same access attribute.
        /// 
        /// @throws result_t
        static std::tuple<memory_access_attribute_t, size_t> ZE_APICALL
        GetAccessAttribute(
            Context* pContext,                              ///< [in] pointer to the context object
            const void* ptr,                                ///< [in] pointer to start of virtual address region for query.
            size_t size                                     ///< [in] size in bytes; must be page aligned.
            );

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for physical memory allocation
    class PhysicalMem
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported physical memory creation flags
        struct flags_t
        {
            uint32_t value;
            flags_t() : value(0) {}
            flags_t( const uint32_t v ) : value(v) {}
            operator uint32_t() const { return value; }
        };

        enum flag_t
        {
            FLAG_TBD = ZE_BIT(0),                           ///< reserved for future use.
            FLAG_FORCE_UINT32 = 0x7fffffff

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Physical memory descriptor
        struct desc_t
        {
            structure_type_t stype = structure_type_t::PHYSICAL_MEM_DESC;   ///< [in] type of this structure
            const void* pNext = nullptr;                    ///< [in][optional] pointer to extension-specific structure
            flags_t flags = 0;                              ///< [in] creation flags.
                                                            ///< must be 0 (default) or a valid combination of ::ze_physical_mem_flag_t.
            size_t size;                                    ///< [in] size in bytes to reserve; must be page aligned.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        physical_mem_handle_t m_handle;                 ///< [in] handle of physical memory object
        Context* m_pContext;                            ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the physical memory object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        PhysicalMem( void ) = delete;
        PhysicalMem( 
            physical_mem_handle_t handle,                   ///< [in] handle of physical memory object
            Context* pContext,                              ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the physical memory object
            );

        ~PhysicalMem( void ) = default;

        PhysicalMem( PhysicalMem const& other ) = delete;
        void operator=( PhysicalMem const& other ) = delete;

        PhysicalMem( PhysicalMem&& other ) = delete;
        void operator=( PhysicalMem&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getContext( void ) const { return m_pContext; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a physical memory object for the context.
        /// 
        /// @details
        ///     - The application must only use the physical memory object on the
        ///       context for which it was created.
        ///     - The size must be page aligned. See ::zeVirtualMemQueryPageSize.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function must be thread-safe.
        /// @returns
        ///     - PhysicalMem*: pointer to handle of physical memory object created
        /// 
        /// @throws result_t
        static PhysicalMem* ZE_APICALL
        Create(
            Context* pContext,                              ///< [in] pointer to the context object
            Device* pDevice,                                ///< [in] pointer to the device object
            desc_t* desc                                    ///< [in] pointer to physical memory descriptor.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys a physical memory object.
        /// 
        /// @details
        ///     - The application must ensure the device is not currently referencing
        ///       the physical memory object before it is deleted
        ///     - The application must **not** call this function from simultaneous
        ///       threads with the same physical memory handle.
        ///     - The implementation of this function must be thread-safe.
        /// @throws result_t
        static void ZE_APICALL
        Destroy(
            Context* pContext,                              ///< [in] pointer to the context object
            PhysicalMem* pPhysicalMemory                    ///< [in][release] pointer to physical memory object to destroy
            );

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts VirtualMem::memory_access_attribute_t to std::string
    std::string to_string( const VirtualMem::memory_access_attribute_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts PhysicalMem::flags_t to std::string
    std::string to_string( const PhysicalMem::flags_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts PhysicalMem::desc_t to std::string
    std::string to_string( const PhysicalMem::desc_t val );

} // namespace ze
#pragma endregion
#endif // defined(__cplusplus)
#endif // _ZE_API_HPP