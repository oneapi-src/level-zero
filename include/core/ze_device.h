/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_device.h
 *
 * @brief Intel 'One API' Level-Zero APIs for Device
 *
 */
 
#ifndef _ZE_DEVICE_H
#define _ZE_DEVICE_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_ZE_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves devices within a driver
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDriver`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zeDeviceGet(
    ze_driver_handle_t hDriver,                     ///< [in] handle of the driver instance
    uint32_t* pCount,                               ///< [in,out] pointer to the number of devices.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of devices available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of devices.
                                                    ///< if count is larger than the number of devices available, then the
                                                    ///< driver will update the value with the correct number of devices available.
    ze_device_handle_t* phDevices                   ///< [in,out][optional][range(0, *pCount)] array of handle of devices
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
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zeDeviceGetSubDevices(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t* pCount,                               ///< [in,out] pointer to the number of sub-devices.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of sub-devices available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of sub-devices.
                                                    ///< if count is larger than the number of sub-devices available, then the
                                                    ///< driver will update the value with the correct number of sub-devices available.
    ze_device_handle_t* phSubdevices                ///< [in,out][optional][range(0, *pCount)] array of handle of sub-devices
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_properties_t
typedef enum _ze_device_properties_version_t
{
    ZE_DEVICE_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),///< version 0.91

} ze_device_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported device types
typedef enum _ze_device_type_t
{
    ZE_DEVICE_TYPE_GPU = 1,                         ///< Graphics Processing Unit
    ZE_DEVICE_TYPE_FPGA,                            ///< Field Programmable Gate Array

} ze_device_type_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_DEVICE_UUID_SIZE
/// @brief Maximum device universal unique id (UUID) size in bytes
#define ZE_MAX_DEVICE_UUID_SIZE  16
#endif // ZE_MAX_DEVICE_UUID_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief Device universal unique id (UUID)
typedef struct _ze_device_uuid_t
{
    uint8_t id[ZE_MAX_DEVICE_UUID_SIZE];            ///< Opaque data representing a device UUID

} ze_device_uuid_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_DEVICE_NAME
/// @brief Maximum device name string size
#define ZE_MAX_DEVICE_NAME  256
#endif // ZE_MAX_DEVICE_NAME

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties queried using ::zeDeviceGetProperties
typedef struct _ze_device_properties_t
{
    ze_device_properties_version_t version;         ///< [in] ::ZE_DEVICE_PROPERTIES_VERSION_CURRENT
    ze_device_type_t type;                          ///< [out] generic device type
    uint32_t vendorId;                              ///< [out] vendor id from PCI configuration
    uint32_t deviceId;                              ///< [out] device id from PCI configuration
    ze_device_uuid_t uuid;                          ///< [out] universal unique identifier.
    ze_bool_t isSubdevice;                          ///< [out] If the device handle used for query represents a sub-device.
    uint32_t subdeviceId;                           ///< [out] sub-device id. Only valid if isSubdevice is true.
    uint32_t coreClockRate;                         ///< [out] Clock rate for device core.
    ze_bool_t unifiedMemorySupported;               ///< [out] Supports unified physical memory between Host and device.
    ze_bool_t eccMemorySupported;                   ///< [out] Supports error correction memory access.
    ze_bool_t onDemandPageFaultsSupported;          ///< [out] Supports on-demand page-faulting.
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

} ze_device_properties_t;

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
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pDeviceProperties`
__ze_api_export ze_result_t __zecall
zeDeviceGetProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_properties_t* pDeviceProperties       ///< [in,out] query result for device properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_compute_properties_t
typedef enum _ze_device_compute_properties_version_t
{
    ZE_DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),///< version 0.91

} ze_device_compute_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_SUBGROUPSIZE_COUNT
/// @brief Maximum number of subgroup sizes supported.
#define ZE_SUBGROUPSIZE_COUNT  8
#endif // ZE_SUBGROUPSIZE_COUNT

///////////////////////////////////////////////////////////////////////////////
/// @brief Device compute properties queried using ::zeDeviceGetComputeProperties
typedef struct _ze_device_compute_properties_t
{
    ze_device_compute_properties_version_t version; ///< [in] ::ZE_DEVICE_COMPUTE_PROPERTIES_VERSION_CURRENT
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

} ze_device_compute_properties_t;

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
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pComputeProperties`
__ze_api_export ze_result_t __zecall
zeDeviceGetComputeProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_compute_properties_t* pComputeProperties  ///< [in,out] query result for compute properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_kernel_properties_t
typedef enum _ze_device_kernel_properties_version_t
{
    ZE_DEVICE_KERNEL_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ), ///< version 0.91

} ze_device_kernel_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_NATIVE_KERNEL_UUID_SIZE
/// @brief Maximum native kernel universal unique id (UUID) size in bytes
#define ZE_MAX_NATIVE_KERNEL_UUID_SIZE  16
#endif // ZE_MAX_NATIVE_KERNEL_UUID_SIZE

///////////////////////////////////////////////////////////////////////////////
/// @brief Native kernel universal unique id (UUID)
typedef struct _ze_native_kernel_uuid_t
{
    uint8_t id[ZE_MAX_NATIVE_KERNEL_UUID_SIZE];     ///< Opaque data representing a native kernel UUID

} ze_native_kernel_uuid_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Floating Point capabilities
/// 
/// @details
///     - floating-point capabilities of the device.
typedef enum _ze_fp_capabilities_t
{
    ZE_FP_CAPS_NONE = 0,                            ///< None
    ZE_FP_CAPS_DENORM = ZE_BIT( 0 ),                ///< Supports denorms
    ZE_FP_CAPS_INF_NAN = ZE_BIT( 1 ),               ///< Supports INF and quiet NaNs
    ZE_FP_CAPS_ROUND_TO_NEAREST = ZE_BIT( 2 ),      ///< Supports rounding to nearest even rounding mode
    ZE_FP_CAPS_ROUND_TO_ZERO = ZE_BIT( 3 ),         ///< Supports rounding to zero.
    ZE_FP_CAPS_ROUND_TO_INF = ZE_BIT( 4 ),          ///< Supports rounding to both positive and negative INF.
    ZE_FP_CAPS_FMA = ZE_BIT( 5 ),                   ///< Supports IEEE754-2008 fused multiply-add.
    ZE_FP_CAPS_ROUNDED_DIVIDE_SQRT = ZE_BIT( 6 ),   ///< Supports rounding as defined by IEEE754 for divide and sqrt
                                                    ///< operations.
    ZE_FP_CAPS_SOFT_FLOAT = ZE_BIT( 7 ),            ///< Uses software implementation for basic floating-point operations.

} ze_fp_capabilities_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties queried using ::zeDeviceGetKernelProperties
typedef struct _ze_device_kernel_properties_t
{
    ze_device_kernel_properties_version_t version;  ///< [in] ::ZE_DEVICE_KERNEL_PROPERTIES_VERSION_CURRENT
    uint32_t spirvVersionSupported;                 ///< [out] Maximum supported SPIR-V version.
                                                    ///< Returns zero if SPIR-V is not supported.
                                                    ///< Contains major and minor attributes, use ::ZE_MAJOR_VERSION and ::ZE_MINOR_VERSION.
    ze_native_kernel_uuid_t nativeKernelSupported;  ///< [out] Compatibility UUID of supported native kernel.
                                                    ///< UUID may or may not be the same across driver release, devices, or
                                                    ///< operating systems.
                                                    ///< Application is responsible for ensuring UUID matches before creating
                                                    ///< module using
                                                    ///< previously created native kernel.
    ze_bool_t fp16Supported;                        ///< [out] Supports 16-bit floating-point operations
    ze_bool_t fp64Supported;                        ///< [out] Supports 64-bit floating-point operations
    ze_bool_t int64AtomicsSupported;                ///< [out] Supports 64-bit atomic operations
    ze_bool_t dp4aSupported;                        ///< [out] Supports four component dot product and accumulate operations
    ze_fp_capabilities_t halfFpCapabilities;        ///< [out] Capabilities for half-precision floating-point operations.
    ze_fp_capabilities_t singleFpCapabilities;      ///< [out] Capabilities for single-precision floating-point operations.
    ze_fp_capabilities_t doubleFpCapabilities;      ///< [out] Capabilities for double-precision floating-point operations.
    uint32_t maxArgumentsSize;                      ///< [out] Maximum kernel argument size that is supported.
    uint32_t printfBufferSize;                      ///< [out] Maximum size of internal buffer that holds output of printf
                                                    ///< calls from kernel.

} ze_device_kernel_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves kernel properties of the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pKernelProperties`
__ze_api_export ze_result_t __zecall
zeDeviceGetKernelProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_kernel_properties_t* pKernelProperties///< [in,out] query result for kernel properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_memory_properties_t
typedef enum _ze_device_memory_properties_version_t
{
    ZE_DEVICE_MEMORY_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ), ///< version 0.91

} ze_device_memory_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device local memory properties queried using
///        ::zeDeviceGetMemoryProperties
typedef struct _ze_device_memory_properties_t
{
    ze_device_memory_properties_version_t version;  ///< [in] ::ZE_DEVICE_MEMORY_PROPERTIES_VERSION_CURRENT
    uint32_t maxClockRate;                          ///< [out] Maximum clock rate for device memory.
    uint32_t maxBusWidth;                           ///< [out] Maximum bus width between device and memory.
    uint64_t totalSize;                             ///< [out] Total memory size in bytes.

} ze_device_memory_properties_t;

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
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCount`
__ze_api_export ze_result_t __zecall
zeDeviceGetMemoryProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    uint32_t* pCount,                               ///< [in,out] pointer to the number of memory properties.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of memory properties available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< memory properties.
                                                    ///< if count is larger than the number of memory properties available,
                                                    ///< then the driver will update the value with the correct number of
                                                    ///< memory properties available.
    ze_device_memory_properties_t* pMemProperties   ///< [in,out][optional][range(0, *pCount)] array of query results for
                                                    ///< memory properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_memory_access_properties_t
typedef enum _ze_device_memory_access_properties_version_t
{
    ZE_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),  ///< version 0.91

} ze_device_memory_access_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Memory access capabilities
/// 
/// @details
///     - Supported access capabilities for different types of memory
///       allocations
typedef enum _ze_memory_access_capabilities_t
{
    ZE_MEMORY_ACCESS_NONE = 0,                      ///< Access not supported
    ZE_MEMORY_ACCESS = ZE_BIT( 0 ),                 ///< Supports load/store access
    ZE_MEMORY_ATOMIC_ACCESS = ZE_BIT( 1 ),          ///< Supports atomic access
    ZE_MEMORY_CONCURRENT_ACCESS = ZE_BIT( 2 ),      ///< Supports concurrent access
    ZE_MEMORY_CONCURRENT_ATOMIC_ACCESS = ZE_BIT( 3 ),   ///< Supports concurrent atomic access

} ze_memory_access_capabilities_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device memory access properties queried using
///        ::zeDeviceGetMemoryAccessProperties
typedef struct _ze_device_memory_access_properties_t
{
    ze_device_memory_access_properties_version_t version;   ///< [in] ::ZE_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_CURRENT
    ze_memory_access_capabilities_t hostAllocCapabilities;  ///< [out] Bitfield describing host memory capabilities
    ze_memory_access_capabilities_t deviceAllocCapabilities;///< [out] Bitfield describing device memory capabilities
    ze_memory_access_capabilities_t sharedSingleDeviceAllocCapabilities;///< [out] Bitfield describing shared (single-device) memory capabilities
    ze_memory_access_capabilities_t sharedCrossDeviceAllocCapabilities; ///< [out] Bitfield describing shared (cross-device) memory capabilities
    ze_memory_access_capabilities_t sharedSystemAllocCapabilities;  ///< [out] Bitfield describing shared (system) memory capabilities

} ze_device_memory_access_properties_t;

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
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pMemAccessProperties`
__ze_api_export ze_result_t __zecall
zeDeviceGetMemoryAccessProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_memory_access_properties_t* pMemAccessProperties  ///< [in,out] query result for memory access properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_cache_properties_t
typedef enum _ze_device_cache_properties_version_t
{
    ZE_DEVICE_CACHE_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),  ///< version 0.91

} ze_device_cache_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device cache properties queried using ::zeDeviceGetCacheProperties
typedef struct _ze_device_cache_properties_t
{
    ze_device_cache_properties_version_t version;   ///< [in] ::ZE_DEVICE_CACHE_PROPERTIES_VERSION_CURRENT
    ze_bool_t intermediateCacheControlSupported;    ///< [out] Support User control on Intermediate Cache (i.e. Resize SLM
                                                    ///< section vs Generic Cache)
    size_t intermediateCacheSize;                   ///< [out] Per-cache Intermediate Cache (L1/L2) size, in bytes
    uint32_t intermediateCachelineSize;             ///< [out] Cacheline size in bytes for intermediate cacheline (L1/L2).
    ze_bool_t lastLevelCacheSizeControlSupported;   ///< [out] Support User control on Last Level Cache (i.e. Resize SLM
                                                    ///< section vs Generic Cache).
    size_t lastLevelCacheSize;                      ///< [out] Per-cache Last Level Cache (L3) size, in bytes
    uint32_t lastLevelCachelineSize;                ///< [out] Cacheline size in bytes for last-level cacheline (L3).

} ze_device_cache_properties_t;

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
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pCacheProperties`
__ze_api_export ze_result_t __zecall
zeDeviceGetCacheProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_cache_properties_t* pCacheProperties  ///< [in,out] query result for cache properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_image_properties_t
typedef enum _ze_device_image_properties_version_t
{
    ZE_DEVICE_IMAGE_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),  ///< version 0.91

} ze_device_image_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device image properties queried using ::zeDeviceGetComputeProperties
typedef struct _ze_device_image_properties_t
{
    ze_device_image_properties_version_t version;   ///< [in] ::ZE_DEVICE_IMAGE_PROPERTIES_VERSION_CURRENT
    ze_bool_t supported;                            ///< [out] Supports reading and writing of images. See
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

} ze_device_image_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves image X_DEVICE_MEMORY_ACCESS_PROPERTIES_VERSION_CURRENT of
///        the device
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pImageProperties`
__ze_api_export ze_result_t __zecall
zeDeviceGetImageProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    ze_device_image_properties_t* pImageProperties  ///< [in,out] query result for image properties
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_device_p2p_properties_t
typedef enum _ze_device_p2p_properties_version_t
{
    ZE_DEVICE_P2P_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 0, 91 ),///< version 0.91

} ze_device_p2p_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Device properties queried using ::zeDeviceGetP2PProperties
typedef struct _ze_device_p2p_properties_t
{
    ze_device_p2p_properties_version_t version;     ///< [in] ::ZE_DEVICE_P2P_PROPERTIES_VERSION_CURRENT
    ze_bool_t accessSupported;                      ///< [out] Supports access between peer devices.
    ze_bool_t atomicsSupported;                     ///< [out] Supports atomics between peer devices.

} ze_device_p2p_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves Peer-to-Peer properties between one device and a peer
///        devices
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///         + `nullptr == hPeerDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == pP2PProperties`
__ze_api_export ze_result_t __zecall
zeDeviceGetP2PProperties(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    ze_device_p2p_properties_t* pP2PProperties      ///< [in,out] Peer-to-Peer properties between source and peer device
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
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///         + `nullptr == hPeerDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == value`
__ze_api_export ze_result_t __zecall
zeDeviceCanAccessPeer(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    ze_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    ze_bool_t* value                                ///< [out] returned access capability
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported Cache Config
/// 
/// @details
///     - Supported Cache Config (Default, Large SLM, Large Data Cache)
typedef enum _ze_cache_config_t
{
    ZE_CACHE_CONFIG_DEFAULT = ZE_BIT( 0 ),          ///< Default Config
    ZE_CACHE_CONFIG_LARGE_SLM = ZE_BIT( 1 ),        ///< Large SLM size
    ZE_CACHE_CONFIG_LARGE_DATA = ZE_BIT( 2 ),       ///< Large General Data size

} ze_cache_config_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the preferred Last Level cache configuration for a device.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same device handle.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + CacheConfig
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_FEATURE
__ze_api_export ze_result_t __zecall
zeDeviceSetLastLevelCacheConfig(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device 
    ze_cache_config_t CacheConfig                   ///< [in] CacheConfig
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_DEVICE_H
