/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_device.hpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Device
 *
 */
#ifndef _ZE_DEVICE_HPP
#define _ZE_DEVICE_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_ZE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

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
        uint8_t id[ZE_MAX_DEVICE_UUID_SIZE];            ///< Opaque data representing a device UUID

    };

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for a device
    class Device
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_properties_t
        enum class properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported device types
        enum class type_t
        {
            GPU = 1,                                        ///< Graphics Processing Unit
            FPGA,                                           ///< Field Programmable Gate Array

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_compute_properties_t
        enum class compute_properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_kernel_properties_t
        enum class kernel_properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Floating Point capabilities
        /// 
        /// @details
        ///     - floating-point capabilities of the device.
        enum class fp_capabilities_t
        {
            FP_CAPS_NONE = 0,                               ///< None
            FP_CAPS_DENORM = ZE_BIT( 0 ),                   ///< Supports denorms
            FP_CAPS_INF_NAN = ZE_BIT( 1 ),                  ///< Supports INF and quiet NaNs
            FP_CAPS_ROUND_TO_NEAREST = ZE_BIT( 2 ),         ///< Supports rounding to nearest even rounding mode
            FP_CAPS_ROUND_TO_ZERO = ZE_BIT( 3 ),            ///< Supports rounding to zero.
            FP_CAPS_ROUND_TO_INF = ZE_BIT( 4 ),             ///< Supports rounding to both positive and negative INF.
            FP_CAPS_FMA = ZE_BIT( 5 ),                      ///< Supports IEEE754-2008 fused multiply-add.
            FP_CAPS_ROUNDED_DIVIDE_SQRT = ZE_BIT( 6 ),      ///< Supports rounding as defined by IEEE754 for divide and sqrt
                                                            ///< operations.
            FP_CAPS_SOFT_FLOAT = ZE_BIT( 7 ),               ///< Uses software implementation for basic floating-point operations.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_memory_properties_t
        enum class memory_properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_memory_access_properties_t
        enum class memory_access_properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Memory access capabilities
        /// 
        /// @details
        ///     - Supported access capabilities for different types of memory
        ///       allocations
        enum class memory_access_capabilities_t
        {
            MEMORY_ACCESS_NONE = 0,                         ///< Access not supported
            MEMORY_ACCESS = ZE_BIT( 0 ),                    ///< Supports load/store access
            MEMORY_ATOMIC_ACCESS = ZE_BIT( 1 ),             ///< Supports atomic access
            MEMORY_CONCURRENT_ACCESS = ZE_BIT( 2 ),         ///< Supports concurrent access
            MEMORY_CONCURRENT_ATOMIC_ACCESS = ZE_BIT( 3 ),  ///< Supports concurrent atomic access

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_cache_properties_t
        enum class cache_properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_image_properties_t
        enum class image_properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::ze_device_p2p_properties_t
        enum class p2p_properties_version_t
        {
            CURRENT = ZE_MAKE_VERSION( 0, 91 ),             ///< version 0.91

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Supported Cache Config
        /// 
        /// @details
        ///     - Supported Cache Config (Default, Large SLM, Large Data Cache)
        enum class cache_config_t
        {
            DEFAULT = ZE_BIT( 0 ),                          ///< Default Config
            LARGE_SLM = ZE_BIT( 1 ),                        ///< Large SLM size
            LARGE_DATA = ZE_BIT( 2 ),                       ///< Large General Data size

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device properties queried using ::zeDeviceGetProperties
        struct properties_t
        {
            properties_version_t version = properties_version_t::CURRENT;   ///< [in] ::ZE_DEVICE_PROPERTIES_VERSION_CURRENT
            type_t type;                                    ///< [out] generic device type
            uint32_t vendorId;                              ///< [out] vendor id from PCI configuration
            uint32_t deviceId;                              ///< [out] device id from PCI configuration
            device_uuid_t uuid;                             ///< [out] universal unique identifier.
            bool_t isSubdevice;                             ///< [out] If the device handle used for query represents a sub-device.
            uint32_t subdeviceId;                           ///< [out] sub-device id. Only valid if isSubdevice is true.
            uint32_t coreClockRate;                         ///< [out] Clock rate for device core.
            bool_t unifiedMemorySupported;                  ///< [out] Supports unified physical memory between Host and device.
            bool_t eccMemorySupported;                      ///< [out] Supports error correction memory access.
            bool_t onDemandPageFaultsSupported;             ///< [out] Supports on-demand page-faulting.
            uint32_t maxCommandQueues;                      ///< [out] Maximum number of logical command queues.
            uint32_t numAsyncComputeEngines;                ///< [out] Number of asynchronous compute engines
            uint32_t numAsyncCopyEngines;                   ///< [out] Number of asynchronous copy engines
            uint32_t maxCommandQueuePriority;               ///< [out] Maximum priority for command queues. Higher value is higher
                                                            ///< priority.
            uint32_t numThreadsPerEU;                       ///< [out] Number of threads per EU.
            uint32_t physicalEUSimdWidth;                   ///< [out] The physical EU simd width.
            uint32_t numEUsPerSubslice;                     ///< [out] Number of EUs per sub-slice.
            uint32_t numSubslicesPerSlice;                  ///< [out] Number of sub-slices per slice.
            uint32_t numSlices;                             ///< [out] Number of slices.
            uint64_t timerResolution;                       ///< [out] Returns the resolution of device timer in nanoseconds used for
                                                            ///< profiling, timestamps, etc.
            char name[ZE_MAX_DEVICE_NAME];                  ///< [out] Device name

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device compute properties queried using ::zeDeviceGetComputeProperties
        struct compute_properties_t
        {
            compute_properties_version_t version = compute_properties_version_t::CURRENT;   ///< [in] ::ZE_DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT
            uint32_t maxTotalGroupSize;                     ///< [out] Maximum items per compute group. (maxGroupSizeX * maxGroupSizeY
                                                            ///< * maxGroupSizeZ) <= maxTotalGroupSize
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
            uint8_t id[ZE_MAX_NATIVE_KERNEL_UUID_SIZE];     ///< Opaque data representing a native kernel UUID

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device properties queried using ::zeDeviceGetKernelProperties
        struct kernel_properties_t
        {
            kernel_properties_version_t version = kernel_properties_version_t::CURRENT; ///< [in] ::ZE_DEVICE_KERNEL_PROPERTIES_VERSION_CURRENT
            uint32_t spirvVersionSupported;                 ///< [out] Maximum supported SPIR-V version.
                                                            ///< Returns zero if SPIR-V is not supported.
                                                            ///< Contains major and minor attributes, use ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION.
            native_kernel_uuid_t nativeKernelSupported;     ///< [out] Compatibility UUID of supported native kernel.
                                                            ///< UUID may or may not be the same across driver release, devices, or
                                                            ///< operating systems.
                                                            ///< Application is responsible for ensuring UUID matches before creating
                                                            ///< module using
                                                            ///< previously created native kernel.
            bool_t fp16Supported;                           ///< [out] Supports 16-bit floating-point operations
            bool_t fp64Supported;                           ///< [out] Supports 64-bit floating-point operations
            bool_t int64AtomicsSupported;                   ///< [out] Supports 64-bit atomic operations
            bool_t dp4aSupported;                           ///< [out] Supports four component dot product and accumulate operations
            fp_capabilities_t halfFpCapabilities;           ///< [out] Capabilities for half-precision floating-point operations.
            fp_capabilities_t singleFpCapabilities;         ///< [out] Capabilities for single-precision floating-point operations.
            fp_capabilities_t doubleFpCapabilities;         ///< [out] Capabilities for double-precision floating-point operations.
            uint32_t maxArgumentsSize;                      ///< [out] Maximum kernel argument size that is supported.
            uint32_t printfBufferSize;                      ///< [out] Maximum size of internal buffer that holds output of printf
                                                            ///< calls from kernel.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device local memory properties queried using
        ///        ::zeDeviceGetMemoryProperties
        struct memory_properties_t
        {
            memory_properties_version_t version = memory_properties_version_t::CURRENT; ///< [in] ::ZE_DEVICE_MEMORY_PROPERTIES_VERSION_CURRENT
            uint32_t maxClockRate;                          ///< [out] Maximum clock rate for device memory.
            uint32_t maxBusWidth;                           ///< [out] Maximum bus width between device and memory.
            uint64_t totalSize;                             ///< [out] Total memory size in bytes.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device memory access properties queried using
        ///        ::zeDeviceGetMemoryAccessProperties
        struct memory_access_properties_t
        {
            memory_access_properties_version_t version = memory_access_properties_version_t::CURRENT;   ///< [in] ::ZE_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_CURRENT
            memory_access_capabilities_t hostAllocCapabilities; ///< [out] Bitfield describing host memory capabilities
            memory_access_capabilities_t deviceAllocCapabilities;   ///< [out] Bitfield describing device memory capabilities
            memory_access_capabilities_t sharedSingleDeviceAllocCapabilities;   ///< [out] Bitfield describing shared (single-device) memory capabilities
            memory_access_capabilities_t sharedCrossDeviceAllocCapabilities;///< [out] Bitfield describing shared (cross-device) memory capabilities
            memory_access_capabilities_t sharedSystemAllocCapabilities; ///< [out] Bitfield describing shared (system) memory capabilities

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device cache properties queried using ::zeDeviceGetCacheProperties
        struct cache_properties_t
        {
            cache_properties_version_t version = cache_properties_version_t::CURRENT;   ///< [in] ::ZE_DEVICE_CACHE_PROPERTIES_VERSION_CURRENT
            bool_t intermediateCacheControlSupported;       ///< [out] Support User control on Intermediate Cache (i.e. Resize SLM
                                                            ///< section vs Generic Cache)
            size_t intermediateCacheSize;                   ///< [out] Per-cache Intermediate Cache (L1/L2) size, in bytes
            uint32_t intermediateCachelineSize;             ///< [out] Cacheline size in bytes for intermediate cacheline (L1/L2).
            bool_t lastLevelCacheSizeControlSupported;      ///< [out] Support User control on Last Level Cache (i.e. Resize SLM
                                                            ///< section vs Generic Cache).
            size_t lastLevelCacheSize;                      ///< [out] Per-cache Last Level Cache (L3) size, in bytes
            uint32_t lastLevelCachelineSize;                ///< [out] Cacheline size in bytes for last-level cacheline (L3).

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device image properties queried using ::zeDeviceGetComputeProperties
        struct image_properties_t
        {
            image_properties_version_t version = image_properties_version_t::CURRENT;   ///< [in] ::ZE_DEVICE_IMAGE_PROPERTIES_VERSION_CURRENT
            bool_t supported;                               ///< [out] Supports reading and writing of images. See
                                                            ///< ::::zeImageGetProperties for format-specific capabilities.
            uint32_t maxImageDims1D;                        ///< [out] Maximum image dimensions for 1D resources.
            uint32_t maxImageDims2D;                        ///< [out] Maximum image dimensions for 2D resources.
            uint32_t maxImageDims3D;                        ///< [out] Maximum image dimensions for 3D resources.
            uint64_t maxImageBufferSize;                    ///< [out] Maximum image buffer size in bytes.
            uint32_t maxImageArraySlices;                   ///< [out] Maximum image array slices
            uint32_t maxSamplers;                           ///< [out] Max samplers that can be used in kernel.
            uint32_t maxReadImageArgs;                      ///< [out] Returns the maximum number of simultaneous image objects that
                                                            ///< can be read from by a kernel.
            uint32_t maxWriteImageArgs;                     ///< [out] Returns the maximum number of simultaneous image objects that
                                                            ///< can be written to by a kernel.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Device properties queried using ::zeDeviceGetP2PProperties
        struct p2p_properties_t
        {
            p2p_properties_version_t version = p2p_properties_version_t::CURRENT;   ///< [in] ::ZE_DEVICE_P2P_PROPERTIES_VERSION_CURRENT
            bool_t accessSupported;                         ///< [out] Supports access between peer devices.
            bool_t atomicsSupported;                        ///< [out] Supports atomics between peer devices.

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
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        static void __zecall
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
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - clCreateSubDevices
        /// @throws result_t
        void __zecall
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
        void __zecall
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
        void __zecall
        GetComputeProperties(
            compute_properties_t* pComputeProperties        ///< [in,out] query result for compute properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves kernel properties of the device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetKernelProperties(
            kernel_properties_t* pKernelProperties          ///< [in,out] query result for kernel properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves local memory properties of the device.
        /// 
        /// @details
        ///     - Properties are reported for each physical memory type supported by the
        ///       device.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// 
        /// @remarks
        ///   _Analogues_
        ///     - clGetDeviceInfo
        /// @throws result_t
        void __zecall
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
        void __zecall
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
        void __zecall
        GetCacheProperties(
            cache_properties_t* pCacheProperties            ///< [in,out] query result for cache properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves image X_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_CURRENT of
        ///        the device
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        GetImageProperties(
            image_properties_t* pImageProperties            ///< [in,out] query result for image properties
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves Peer-to-Peer properties between one device and a peer
        ///        devices
        /// 
        /// @details
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
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
        bool_t __zecall
        CanAccessPeer(
            Device* pPeerDevice                             ///< [in] pointer to the peer device with the allocation
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the preferred Last Level cache configuration for a device.
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same device handle.
        /// @throws result_t
        void __zecall
        SetLastLevelCacheConfig(
            cache_config_t CacheConfig                      ///< [in] CacheConfig
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Ensures in-bound writes to the device are globally observable.
        /// 
        /// @details
        ///     - This is a special-case system level barrier that can be used to ensure
        ///       global observability of writes; typically needed after a producer
        ///       (e.g., NIC) performs direct writes to the device's memory (e.g.,
        ///       Direct RDMA writes).  This is typically required when the memory
        ///       corresponding to the writes is subsequently accessed from a remote
        ///       device.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        SystemBarrier(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Makes memory resident for the device.
        /// 
        /// @details
        ///     - If the application does not properly manage residency then the device
        ///       may experience unrecoverable page-faults.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        MakeMemoryResident(
            void* ptr,                                      ///< [in] pointer to memory to make resident
            size_t size                                     ///< [in] size in bytes to make resident
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Allows memory to be evicted from the device.
        /// 
        /// @details
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the memory before it is evicted
        ///     - Memory is always implicitly evicted if it is resident when freed.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        EvictMemory(
            void* ptr,                                      ///< [in] pointer to memory to evict
            size_t size                                     ///< [in] size in bytes to evict
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Makes image resident for the device.
        /// 
        /// @details
        ///     - If the application does not properly manage residency then the device
        ///       may experience unrecoverable page-faults.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        MakeImageResident(
            Image* pImage                                   ///< [in] pointer to image to make resident
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Allows image to be evicted from the device.
        /// 
        /// @details
        ///     - The application is responsible for making sure the device is not
        ///       currently referencing the memory before it is evicted
        ///     - An image is always implicitly evicted if it is resident when
        ///       destroyed.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        void __zecall
        EvictImage(
            Image* pImage                                   ///< [in] pointer to image to make evict
            );

#if ZE_ENABLE_OCL_INTEROP
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Registers OpenCL memory with 'One API'
        /// @returns
        ///     - void*: pointer to device allocation
        /// 
        /// @throws result_t
        void* __zecall
        RegisterCLMemory(
            cl_context context,                             ///< [in] the OpenCL context that created the memory
            cl_mem mem                                      ///< [in] the OpenCL memory to register
            );
#endif // ZE_ENABLE_OCL_INTEROP

#if ZE_ENABLE_OCL_INTEROP
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Registers OpenCL program with 'One API'
        /// @returns
        ///     - Module*: pointer to handle of module object created
        /// 
        /// @throws result_t
        Module* __zecall
        RegisterCLProgram(
            cl_context context,                             ///< [in] the OpenCL context that created the program
            cl_program program                              ///< [in] the OpenCL program to register
            );
#endif // ZE_ENABLE_OCL_INTEROP

#if ZE_ENABLE_OCL_INTEROP
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Registers OpenCL command queue with 'One API'
        /// @returns
        ///     - CommandQueue*: pointer to handle of command queue object created
        /// 
        /// @throws result_t
        CommandQueue* __zecall
        RegisterCLCommandQueue(
            cl_context context,                             ///< [in] the OpenCL context that created the command queue
            cl_command_queue command_queue                  ///< [in] the OpenCL command queue to register
            );
#endif // ZE_ENABLE_OCL_INTEROP

    };

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts device_uuid_t to std::string
    std::string to_string( const device_uuid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::properties_version_t to std::string
    std::string to_string( const Device::properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::type_t to std::string
    std::string to_string( const Device::type_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::properties_t to std::string
    std::string to_string( const Device::properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::compute_properties_version_t to std::string
    std::string to_string( const Device::compute_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::compute_properties_t to std::string
    std::string to_string( const Device::compute_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::kernel_properties_version_t to std::string
    std::string to_string( const Device::kernel_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::native_kernel_uuid_t to std::string
    std::string to_string( const Device::native_kernel_uuid_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::fp_capabilities_t to std::string
    std::string to_string( const Device::fp_capabilities_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::kernel_properties_t to std::string
    std::string to_string( const Device::kernel_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_properties_version_t to std::string
    std::string to_string( const Device::memory_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_properties_t to std::string
    std::string to_string( const Device::memory_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_access_properties_version_t to std::string
    std::string to_string( const Device::memory_access_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_access_capabilities_t to std::string
    std::string to_string( const Device::memory_access_capabilities_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::memory_access_properties_t to std::string
    std::string to_string( const Device::memory_access_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::cache_properties_version_t to std::string
    std::string to_string( const Device::cache_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::cache_properties_t to std::string
    std::string to_string( const Device::cache_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::image_properties_version_t to std::string
    std::string to_string( const Device::image_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::image_properties_t to std::string
    std::string to_string( const Device::image_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::p2p_properties_version_t to std::string
    std::string to_string( const Device::p2p_properties_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::p2p_properties_t to std::string
    std::string to_string( const Device::p2p_properties_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Device::cache_config_t to std::string
    std::string to_string( const Device::cache_config_t val );

} // namespace ze
#endif // defined(__cplusplus)
#endif // _ZE_DEVICE_HPP
