/*
 * ***THIS FILE IS GENERATED. ***
 * See to_string.h.mako for modifications
 *
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_to_string.h
 * 
 * to_string functions for Level Zero types
 */

#ifndef _ZE_TO_STRING_H
#define _ZE_TO_STRING_H

#include "ze_api.h"
#include <string>
#include <sstream>
#include <iomanip>

namespace loader {

// Forward declarations
std::string to_string(const ze_result_t result);

// Pointer to_string
template<typename T>
inline std::string to_string(const T* ptr) {
    if (ptr == nullptr) {
        return "nullptr";
    }
    std::ostringstream oss;
    oss << "0x" << std::hex << reinterpret_cast<uintptr_t>(ptr);
    return oss.str();
}

// Handle to_string functions
inline std::string to_string(ze_driver_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_device_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_context_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_command_queue_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_command_list_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_fence_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_event_pool_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_event_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_image_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_module_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_module_build_log_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_kernel_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_sampler_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_physical_mem_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_fabric_vertex_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_fabric_edge_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_external_semaphore_ext_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_rtas_builder_ext_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_rtas_parallel_operation_ext_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_rtas_builder_exp_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

inline std::string to_string(ze_rtas_parallel_operation_exp_handle_t handle) {
    return to_string(reinterpret_cast<const void*>(handle));
}

// For primitive types and Level Zero typedef'd types
// Since most Level Zero types are typedef'd to uint32_t, we can't distinguish them by type
inline std::string to_string(uint32_t value) { return std::to_string(value); }
inline std::string to_string(uint64_t value) { return std::to_string(value); }
inline std::string to_string(uint8_t value) { return std::to_string(static_cast<unsigned>(value)); }
inline std::string to_string(uint16_t value) { return std::to_string(value); }
inline std::string to_string(int32_t value) { return std::to_string(value); }
inline std::string to_string(int64_t value) { return std::to_string(value); }
#if SIZE_MAX != UINT64_MAX
inline std::string to_string(size_t value) { return std::to_string(value); }
#endif
inline std::string to_string(double value) { return std::to_string(value); }
inline std::string to_string(const char* str) {
    if (!str) return "nullptr";
    return std::string("\"") + str + "\"";
}

// Pointer to primitive types - dereference and print value
inline std::string to_string(const uint32_t* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}
inline std::string to_string(const uint64_t* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}
inline std::string to_string(const uint8_t* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}
inline std::string to_string(const uint16_t* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}
inline std::string to_string(const int32_t* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}
inline std::string to_string(const int64_t* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}
#if SIZE_MAX != UINT64_MAX
inline std::string to_string(const size_t* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}
#endif
inline std::string to_string(const double* ptr) {
    if (!ptr) return "nullptr";
    return to_string(*ptr);
}

// Struct to_string functions
inline std::string to_string(const ze_ipc_mem_handle_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "data=" << to_string(desc->data);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_ipc_mem_handle_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_ipc_event_pool_handle_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "data=" << to_string(desc->data);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_ipc_event_pool_handle_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_uuid_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "id=" << to_string(desc->id);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_uuid_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_base_cb_params_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_base_cb_params_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_base_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_base_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_base_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_base_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_ipc_event_counter_based_handle_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "data=" << to_string(desc->data);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_ipc_event_counter_based_handle_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_init_driver_type_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_init_driver_type_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_driver_uuid_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "id=" << to_string(desc->id);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_driver_uuid_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_driver_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", uuid=" << to_string(&desc->uuid);
    oss << ", driverVersion=" << to_string(desc->driverVersion);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_driver_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_driver_ipc_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_driver_ipc_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_driver_extension_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "name=" << to_string(desc->name);
    oss << ", version=" << to_string(desc->version);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_driver_extension_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_uuid_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "id=" << to_string(desc->id);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_uuid_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << ", vendorId=" << to_string(desc->vendorId);
    oss << ", deviceId=" << to_string(desc->deviceId);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", subdeviceId=" << to_string(desc->subdeviceId);
    oss << ", coreClockRate=" << to_string(desc->coreClockRate);
    oss << ", maxMemAllocSize=" << to_string(desc->maxMemAllocSize);
    oss << ", maxHardwareContexts=" << to_string(desc->maxHardwareContexts);
    oss << ", maxCommandQueuePriority=" << to_string(desc->maxCommandQueuePriority);
    oss << ", numThreadsPerEU=" << to_string(desc->numThreadsPerEU);
    oss << ", physicalEUSimdWidth=" << to_string(desc->physicalEUSimdWidth);
    oss << ", numEUsPerSubslice=" << to_string(desc->numEUsPerSubslice);
    oss << ", numSubslicesPerSlice=" << to_string(desc->numSubslicesPerSlice);
    oss << ", numSlices=" << to_string(desc->numSlices);
    oss << ", timerResolution=" << to_string(desc->timerResolution);
    oss << ", timestampValidBits=" << to_string(desc->timestampValidBits);
    oss << ", kernelTimestampValidBits=" << to_string(desc->kernelTimestampValidBits);
    oss << ", uuid=" << to_string(&desc->uuid);
    oss << ", name=" << to_string(desc->name);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_thread_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "slice=" << to_string(desc->slice);
    oss << ", subslice=" << to_string(desc->subslice);
    oss << ", eu=" << to_string(desc->eu);
    oss << ", thread=" << to_string(desc->thread);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_thread_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_compute_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", maxTotalGroupSize=" << to_string(desc->maxTotalGroupSize);
    oss << ", maxGroupSizeX=" << to_string(desc->maxGroupSizeX);
    oss << ", maxGroupSizeY=" << to_string(desc->maxGroupSizeY);
    oss << ", maxGroupSizeZ=" << to_string(desc->maxGroupSizeZ);
    oss << ", maxGroupCountX=" << to_string(desc->maxGroupCountX);
    oss << ", maxGroupCountY=" << to_string(desc->maxGroupCountY);
    oss << ", maxGroupCountZ=" << to_string(desc->maxGroupCountZ);
    oss << ", maxSharedLocalMemory=" << to_string(desc->maxSharedLocalMemory);
    oss << ", numSubGroupSizes=" << to_string(desc->numSubGroupSizes);
    oss << ", subGroupSizes=" << to_string(desc->subGroupSizes);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_compute_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_native_kernel_uuid_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "id=" << to_string(desc->id);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_native_kernel_uuid_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_module_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", spirvVersionSupported=" << to_string(desc->spirvVersionSupported);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", fp16flags=" << to_string(&desc->fp16flags);
    oss << ", fp32flags=" << to_string(&desc->fp32flags);
    oss << ", fp64flags=" << to_string(&desc->fp64flags);
    oss << ", maxArgumentsSize=" << to_string(desc->maxArgumentsSize);
    oss << ", printfBufferSize=" << to_string(desc->printfBufferSize);
    oss << ", nativeKernelSupported=" << to_string(&desc->nativeKernelSupported);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_module_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_command_queue_group_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", maxMemoryFillPatternSize=" << to_string(desc->maxMemoryFillPatternSize);
    oss << ", numQueues=" << to_string(desc->numQueues);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_command_queue_group_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_memory_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", maxClockRate=" << to_string(desc->maxClockRate);
    oss << ", maxBusWidth=" << to_string(desc->maxBusWidth);
    oss << ", totalSize=" << to_string(desc->totalSize);
    oss << ", name=" << to_string(desc->name);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_memory_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_memory_access_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", hostAllocCapabilities=" << to_string(&desc->hostAllocCapabilities);
    oss << ", deviceAllocCapabilities=" << to_string(&desc->deviceAllocCapabilities);
    oss << ", sharedSingleDeviceAllocCapabilities=" << to_string(&desc->sharedSingleDeviceAllocCapabilities);
    oss << ", sharedCrossDeviceAllocCapabilities=" << to_string(&desc->sharedCrossDeviceAllocCapabilities);
    oss << ", sharedSystemAllocCapabilities=" << to_string(&desc->sharedSystemAllocCapabilities);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_memory_access_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_cache_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", cacheSize=" << to_string(desc->cacheSize);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_cache_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_image_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", maxImageDims1D=" << to_string(desc->maxImageDims1D);
    oss << ", maxImageDims2D=" << to_string(desc->maxImageDims2D);
    oss << ", maxImageDims3D=" << to_string(desc->maxImageDims3D);
    oss << ", maxImageBufferSize=" << to_string(desc->maxImageBufferSize);
    oss << ", maxImageArraySlices=" << to_string(desc->maxImageArraySlices);
    oss << ", maxSamplers=" << to_string(desc->maxSamplers);
    oss << ", maxReadImageArgs=" << to_string(desc->maxReadImageArgs);
    oss << ", maxWriteImageArgs=" << to_string(desc->maxWriteImageArgs);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_image_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_external_memory_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", memoryAllocationImportTypes=" << to_string(&desc->memoryAllocationImportTypes);
    oss << ", memoryAllocationExportTypes=" << to_string(&desc->memoryAllocationExportTypes);
    oss << ", imageImportTypes=" << to_string(&desc->imageImportTypes);
    oss << ", imageExportTypes=" << to_string(&desc->imageExportTypes);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_external_memory_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_p2p_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_p2p_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_event_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_event_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_context_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_context_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_command_queue_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", ordinal=" << to_string(desc->ordinal);
    oss << ", index=" << to_string(desc->index);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", mode=" << to_string(&desc->mode);
    oss << ", priority=" << to_string(&desc->priority);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_command_queue_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_command_list_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", commandQueueGroupOrdinal=" << to_string(desc->commandQueueGroupOrdinal);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_command_list_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_copy_region_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "originX=" << to_string(desc->originX);
    oss << ", originY=" << to_string(desc->originY);
    oss << ", originZ=" << to_string(desc->originZ);
    oss << ", width=" << to_string(desc->width);
    oss << ", height=" << to_string(desc->height);
    oss << ", depth=" << to_string(desc->depth);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_copy_region_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_image_region_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "originX=" << to_string(desc->originX);
    oss << ", originY=" << to_string(desc->originY);
    oss << ", originZ=" << to_string(desc->originZ);
    oss << ", width=" << to_string(desc->width);
    oss << ", height=" << to_string(desc->height);
    oss << ", depth=" << to_string(desc->depth);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_image_region_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_event_pool_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", count=" << to_string(desc->count);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_event_pool_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_event_sync_mode_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", syncModeFlags=" << to_string(&desc->syncModeFlags);
    oss << ", externalInterruptId=" << to_string(desc->externalInterruptId);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_event_sync_mode_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_event_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", index=" << to_string(desc->index);
    oss << ", signal=" << to_string(&desc->signal);
    oss << ", wait=" << to_string(&desc->wait);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_event_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_event_counter_based_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", signal=" << to_string(&desc->signal);
    oss << ", wait=" << to_string(&desc->wait);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_event_counter_based_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_event_counter_based_external_sync_allocation_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", deviceAddress=" << to_string(desc->deviceAddress);
    oss << ", hostAddress=" << to_string(desc->hostAddress);
    oss << ", completionValue=" << to_string(desc->completionValue);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_event_counter_based_external_sync_allocation_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_event_counter_based_external_aggregate_storage_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", deviceAddress=" << to_string(desc->deviceAddress);
    oss << ", incrementValue=" << to_string(desc->incrementValue);
    oss << ", completionValue=" << to_string(desc->completionValue);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_event_counter_based_external_aggregate_storage_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_kernel_timestamp_data_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "kernelStart=" << to_string(desc->kernelStart);
    oss << ", kernelEnd=" << to_string(desc->kernelEnd);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_kernel_timestamp_data_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_kernel_timestamp_result_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "global=" << to_string(&desc->global);
    oss << ", context=" << to_string(&desc->context);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_kernel_timestamp_result_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_fence_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_fence_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_image_format_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "layout=" << to_string(&desc->layout);
    oss << ", type=" << to_string(&desc->type);
    oss << ", x=" << to_string(&desc->x);
    oss << ", y=" << to_string(&desc->y);
    oss << ", z=" << to_string(&desc->z);
    oss << ", w=" << to_string(&desc->w);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_image_format_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_image_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", type=" << to_string(&desc->type);
    oss << ", format=" << to_string(&desc->format);
    oss << ", width=" << to_string(desc->width);
    oss << ", height=" << to_string(desc->height);
    oss << ", depth=" << to_string(desc->depth);
    oss << ", arraylevels=" << to_string(desc->arraylevels);
    oss << ", miplevels=" << to_string(desc->miplevels);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_image_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_image_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", samplerFilterFlags=" << to_string(&desc->samplerFilterFlags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_image_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_mem_alloc_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", ordinal=" << to_string(desc->ordinal);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_mem_alloc_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_host_mem_alloc_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_host_mem_alloc_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_memory_allocation_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << ", id=" << to_string(desc->id);
    oss << ", pageSize=" << to_string(desc->pageSize);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_memory_allocation_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_external_memory_export_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_external_memory_export_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_external_memory_import_fd_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", fd=" << to_string(desc->fd);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_external_memory_import_fd_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_external_memory_export_fd_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", fd=" << to_string(desc->fd);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_external_memory_export_fd_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_external_memory_import_win32_handle_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", handle=" << to_string(desc->handle);
    oss << ", name=" << to_string(desc->name);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_external_memory_import_win32_handle_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_external_memory_export_win32_handle_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", handle=" << to_string(desc->handle);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_external_memory_export_win32_handle_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_module_constants_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "numConstants=" << to_string(desc->numConstants);
    oss << ", pConstantIds=" << to_string(desc->pConstantIds);
    oss << ", pConstantValues=" << to_string(desc->pConstantValues);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_module_constants_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_module_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", format=" << to_string(&desc->format);
    oss << ", inputSize=" << to_string(desc->inputSize);
    oss << ", pInputModule=" << to_string(desc->pInputModule);
    oss << ", pBuildFlags=" << to_string(desc->pBuildFlags);
    oss << ", pConstants=" << to_string(desc->pConstants);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_module_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_command_list_append_launch_kernel_param_cooperative_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", isCooperative=" << to_string(&desc->isCooperative);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_command_list_append_launch_kernel_param_cooperative_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_module_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_module_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_kernel_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", pKernelName=" << to_string(desc->pKernelName);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_kernel_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_kernel_uuid_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "kid=" << to_string(desc->kid);
    oss << ", mid=" << to_string(desc->mid);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_kernel_uuid_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_kernel_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", numKernelArgs=" << to_string(desc->numKernelArgs);
    oss << ", requiredGroupSizeX=" << to_string(desc->requiredGroupSizeX);
    oss << ", requiredGroupSizeY=" << to_string(desc->requiredGroupSizeY);
    oss << ", requiredGroupSizeZ=" << to_string(desc->requiredGroupSizeZ);
    oss << ", requiredNumSubGroups=" << to_string(desc->requiredNumSubGroups);
    oss << ", requiredSubgroupSize=" << to_string(desc->requiredSubgroupSize);
    oss << ", maxSubgroupSize=" << to_string(desc->maxSubgroupSize);
    oss << ", maxNumSubgroups=" << to_string(desc->maxNumSubgroups);
    oss << ", localMemSize=" << to_string(desc->localMemSize);
    oss << ", privateMemSize=" << to_string(desc->privateMemSize);
    oss << ", spillMemSize=" << to_string(desc->spillMemSize);
    oss << ", uuid=" << to_string(&desc->uuid);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_kernel_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_kernel_preferred_group_size_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", preferredMultiple=" << to_string(desc->preferredMultiple);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_kernel_preferred_group_size_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_group_count_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "groupCountX=" << to_string(desc->groupCountX);
    oss << ", groupCountY=" << to_string(desc->groupCountY);
    oss << ", groupCountZ=" << to_string(desc->groupCountZ);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_group_count_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_group_size_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "groupSizeX=" << to_string(desc->groupSizeX);
    oss << ", groupSizeY=" << to_string(desc->groupSizeY);
    oss << ", groupSizeZ=" << to_string(desc->groupSizeZ);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_group_size_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_module_program_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", count=" << to_string(desc->count);
    oss << ", inputSizes=" << to_string(desc->inputSizes);
    oss << ", pInputModules=" << to_string(desc->pInputModules);
    oss << ", pBuildFlags=" << to_string(desc->pBuildFlags);
    oss << ", pConstants=" << to_string(desc->pConstants);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_module_program_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_raytracing_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", maxBVHLevels=" << to_string(desc->maxBVHLevels);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_raytracing_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_raytracing_mem_alloc_ext_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_raytracing_mem_alloc_ext_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_sampler_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", addressMode=" << to_string(&desc->addressMode);
    oss << ", filterMode=" << to_string(&desc->filterMode);
    oss << ", isNormalized=" << to_string(&desc->isNormalized);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_sampler_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_physical_mem_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", size=" << to_string(desc->size);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_physical_mem_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_physical_mem_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", id=" << to_string(desc->id);
    oss << ", size=" << to_string(desc->size);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_physical_mem_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_float_atomic_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", fp16Flags=" << to_string(&desc->fp16Flags);
    oss << ", fp32Flags=" << to_string(&desc->fp32Flags);
    oss << ", fp64Flags=" << to_string(&desc->fp64Flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_float_atomic_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_relaxed_allocation_limits_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_relaxed_allocation_limits_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_driver_ddi_handles_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_driver_ddi_handles_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_external_semaphore_ext_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_external_semaphore_ext_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_external_semaphore_win32_ext_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", handle=" << to_string(desc->handle);
    oss << ", name=" << to_string(desc->name);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_external_semaphore_win32_ext_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_external_semaphore_fd_ext_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", fd=" << to_string(desc->fd);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_external_semaphore_fd_ext_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_external_semaphore_signal_params_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", value=" << to_string(desc->value);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_external_semaphore_signal_params_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_external_semaphore_wait_params_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", value=" << to_string(desc->value);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_external_semaphore_wait_params_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_cache_line_size_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", cacheLineSize=" << to_string(desc->cacheLineSize);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_cache_line_size_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_ext_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", builderVersion=" << to_string(&desc->builderVersion);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_ext_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", rtasBufferSizeBytesExpected=" << to_string(desc->rtasBufferSizeBytesExpected);
    oss << ", rtasBufferSizeBytesMaxRequired=" << to_string(desc->rtasBufferSizeBytesMaxRequired);
    oss << ", scratchBufferSizeBytes=" << to_string(desc->scratchBufferSizeBytes);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_parallel_operation_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", maxConcurrency=" << to_string(desc->maxConcurrency);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_parallel_operation_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_device_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", rtasFormat=" << to_string(&desc->rtasFormat);
    oss << ", rtasBufferAlignment=" << to_string(desc->rtasBufferAlignment);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_device_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_float3_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "x=" << to_string(desc->x);
    oss << ", y=" << to_string(desc->y);
    oss << ", z=" << to_string(desc->z);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_float3_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_transform_float3x4_column_major_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "vx_x=" << to_string(desc->vx_x);
    oss << ", vx_y=" << to_string(desc->vx_y);
    oss << ", vx_z=" << to_string(desc->vx_z);
    oss << ", vy_x=" << to_string(desc->vy_x);
    oss << ", vy_y=" << to_string(desc->vy_y);
    oss << ", vy_z=" << to_string(desc->vy_z);
    oss << ", vz_x=" << to_string(desc->vz_x);
    oss << ", vz_y=" << to_string(desc->vz_y);
    oss << ", vz_z=" << to_string(desc->vz_z);
    oss << ", p_x=" << to_string(desc->p_x);
    oss << ", p_y=" << to_string(desc->p_y);
    oss << ", p_z=" << to_string(desc->p_z);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_transform_float3x4_column_major_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_transform_float3x4_aligned_column_major_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "vx_x=" << to_string(desc->vx_x);
    oss << ", vx_y=" << to_string(desc->vx_y);
    oss << ", vx_z=" << to_string(desc->vx_z);
    oss << ", pad0=" << to_string(desc->pad0);
    oss << ", vy_x=" << to_string(desc->vy_x);
    oss << ", vy_y=" << to_string(desc->vy_y);
    oss << ", vy_z=" << to_string(desc->vy_z);
    oss << ", pad1=" << to_string(desc->pad1);
    oss << ", vz_x=" << to_string(desc->vz_x);
    oss << ", vz_y=" << to_string(desc->vz_y);
    oss << ", vz_z=" << to_string(desc->vz_z);
    oss << ", pad2=" << to_string(desc->pad2);
    oss << ", p_x=" << to_string(desc->p_x);
    oss << ", p_y=" << to_string(desc->p_y);
    oss << ", p_z=" << to_string(desc->p_z);
    oss << ", pad3=" << to_string(desc->pad3);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_transform_float3x4_aligned_column_major_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_transform_float3x4_row_major_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "vx_x=" << to_string(desc->vx_x);
    oss << ", vy_x=" << to_string(desc->vy_x);
    oss << ", vz_x=" << to_string(desc->vz_x);
    oss << ", p_x=" << to_string(desc->p_x);
    oss << ", vx_y=" << to_string(desc->vx_y);
    oss << ", vy_y=" << to_string(desc->vy_y);
    oss << ", vz_y=" << to_string(desc->vz_y);
    oss << ", p_y=" << to_string(desc->p_y);
    oss << ", vx_z=" << to_string(desc->vx_z);
    oss << ", vy_z=" << to_string(desc->vy_z);
    oss << ", vz_z=" << to_string(desc->vz_z);
    oss << ", p_z=" << to_string(desc->p_z);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_transform_float3x4_row_major_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_aabb_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "lower=" << to_string(&desc->lower);
    oss << ", upper=" << to_string(&desc->upper);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_aabb_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_triangle_indices_uint32_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "v0=" << to_string(desc->v0);
    oss << ", v1=" << to_string(desc->v1);
    oss << ", v2=" << to_string(desc->v2);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_triangle_indices_uint32_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_quad_indices_uint32_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "v0=" << to_string(desc->v0);
    oss << ", v1=" << to_string(desc->v1);
    oss << ", v2=" << to_string(desc->v2);
    oss << ", v3=" << to_string(desc->v3);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_quad_indices_uint32_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_geometry_info_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "geometryType=" << to_string(&desc->geometryType);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_geometry_info_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_triangles_geometry_info_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "geometryType=" << to_string(&desc->geometryType);
    oss << ", geometryFlags=" << to_string(&desc->geometryFlags);
    oss << ", geometryMask=" << to_string(desc->geometryMask);
    oss << ", triangleFormat=" << to_string(&desc->triangleFormat);
    oss << ", vertexFormat=" << to_string(&desc->vertexFormat);
    oss << ", triangleCount=" << to_string(desc->triangleCount);
    oss << ", vertexCount=" << to_string(desc->vertexCount);
    oss << ", triangleStride=" << to_string(desc->triangleStride);
    oss << ", vertexStride=" << to_string(desc->vertexStride);
    oss << ", pTriangleBuffer=" << to_string(desc->pTriangleBuffer);
    oss << ", pVertexBuffer=" << to_string(desc->pVertexBuffer);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_triangles_geometry_info_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_quads_geometry_info_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "geometryType=" << to_string(&desc->geometryType);
    oss << ", geometryFlags=" << to_string(&desc->geometryFlags);
    oss << ", geometryMask=" << to_string(desc->geometryMask);
    oss << ", quadFormat=" << to_string(&desc->quadFormat);
    oss << ", vertexFormat=" << to_string(&desc->vertexFormat);
    oss << ", quadCount=" << to_string(desc->quadCount);
    oss << ", vertexCount=" << to_string(desc->vertexCount);
    oss << ", quadStride=" << to_string(desc->quadStride);
    oss << ", vertexStride=" << to_string(desc->vertexStride);
    oss << ", pQuadBuffer=" << to_string(desc->pQuadBuffer);
    oss << ", pVertexBuffer=" << to_string(desc->pVertexBuffer);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_quads_geometry_info_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_geometry_aabbs_ext_cb_params_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", primID=" << to_string(desc->primID);
    oss << ", primIDCount=" << to_string(desc->primIDCount);
    oss << ", pGeomUserPtr=" << to_string(desc->pGeomUserPtr);
    oss << ", pBuildUserPtr=" << to_string(desc->pBuildUserPtr);
    oss << ", pBoundsOut=" << to_string(desc->pBoundsOut);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_geometry_aabbs_ext_cb_params_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_procedural_geometry_info_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "geometryType=" << to_string(&desc->geometryType);
    oss << ", geometryFlags=" << to_string(&desc->geometryFlags);
    oss << ", geometryMask=" << to_string(desc->geometryMask);
    oss << ", reserved=" << to_string(desc->reserved);
    oss << ", primCount=" << to_string(desc->primCount);
    oss << ", pfnGetBoundsCb=" << to_string(&desc->pfnGetBoundsCb);
    oss << ", pGeomUserPtr=" << to_string(desc->pGeomUserPtr);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_procedural_geometry_info_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_instance_geometry_info_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "geometryType=" << to_string(&desc->geometryType);
    oss << ", instanceFlags=" << to_string(&desc->instanceFlags);
    oss << ", geometryMask=" << to_string(desc->geometryMask);
    oss << ", transformFormat=" << to_string(&desc->transformFormat);
    oss << ", instanceUserID=" << to_string(desc->instanceUserID);
    oss << ", pTransform=" << to_string(desc->pTransform);
    oss << ", pBounds=" << to_string(desc->pBounds);
    oss << ", pAccelerationStructure=" << to_string(desc->pAccelerationStructure);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_instance_geometry_info_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_build_op_ext_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", rtasFormat=" << to_string(&desc->rtasFormat);
    oss << ", buildQuality=" << to_string(desc->buildQuality);
    oss << ", buildFlags=" << to_string(&desc->buildFlags);
    oss << ", ppGeometries=" << to_string(desc->ppGeometries);
    oss << ", numGeometries=" << to_string(desc->numGeometries);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_build_op_ext_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_vector_width_properties_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", vector_width_size=" << to_string(desc->vector_width_size);
    oss << ", preferred_vector_width_char=" << to_string(desc->preferred_vector_width_char);
    oss << ", preferred_vector_width_short=" << to_string(desc->preferred_vector_width_short);
    oss << ", preferred_vector_width_int=" << to_string(desc->preferred_vector_width_int);
    oss << ", preferred_vector_width_long=" << to_string(desc->preferred_vector_width_long);
    oss << ", preferred_vector_width_float=" << to_string(desc->preferred_vector_width_float);
    oss << ", preferred_vector_width_double=" << to_string(desc->preferred_vector_width_double);
    oss << ", preferred_vector_width_half=" << to_string(desc->preferred_vector_width_half);
    oss << ", native_vector_width_char=" << to_string(desc->native_vector_width_char);
    oss << ", native_vector_width_short=" << to_string(desc->native_vector_width_short);
    oss << ", native_vector_width_int=" << to_string(desc->native_vector_width_int);
    oss << ", native_vector_width_long=" << to_string(desc->native_vector_width_long);
    oss << ", native_vector_width_float=" << to_string(desc->native_vector_width_float);
    oss << ", native_vector_width_double=" << to_string(desc->native_vector_width_double);
    oss << ", native_vector_width_half=" << to_string(desc->native_vector_width_half);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_vector_width_properties_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_external_memmap_sysmem_ext_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", pSystemMemory=" << to_string(desc->pSystemMemory);
    oss << ", size=" << to_string(desc->size);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_external_memmap_sysmem_ext_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_kernel_allocation_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", base=" << to_string(desc->base);
    oss << ", size=" << to_string(desc->size);
    oss << ", type=" << to_string(&desc->type);
    oss << ", argIndex=" << to_string(desc->argIndex);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_kernel_allocation_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_usablemem_size_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", currUsableMemSize=" << to_string(desc->currUsableMemSize);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_usablemem_size_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_image_format_support_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", supported=" << to_string(&desc->supported);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_image_format_support_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_ipc_mem_handle_type_ext_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", typeFlags=" << to_string(&desc->typeFlags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_ipc_mem_handle_type_ext_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_cache_reservation_ext_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", maxCacheReservationSize=" << to_string(desc->maxCacheReservationSize);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_cache_reservation_ext_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_image_memory_properties_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", size=" << to_string(desc->size);
    oss << ", rowPitch=" << to_string(desc->rowPitch);
    oss << ", slicePitch=" << to_string(desc->slicePitch);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_image_memory_properties_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_image_view_planar_ext_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", planeIndex=" << to_string(desc->planeIndex);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_image_view_planar_ext_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_image_view_planar_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", planeIndex=" << to_string(desc->planeIndex);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_image_view_planar_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_scheduling_hint_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", schedulingHintFlags=" << to_string(desc->schedulingHintFlags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_scheduling_hint_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_scheduling_hint_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_scheduling_hint_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_context_power_saving_hint_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", hint=" << to_string(desc->hint);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_context_power_saving_hint_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_eu_count_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", numTotalEUs=" << to_string(desc->numTotalEUs);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_eu_count_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_pci_address_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "domain=" << to_string(desc->domain);
    oss << ", bus=" << to_string(desc->bus);
    oss << ", device=" << to_string(desc->device);
    oss << ", function=" << to_string(desc->function);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_pci_address_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_pci_speed_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "genVersion=" << to_string(desc->genVersion);
    oss << ", width=" << to_string(desc->width);
    oss << ", maxBandwidth=" << to_string(desc->maxBandwidth);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_pci_speed_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_pci_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", address=" << to_string(&desc->address);
    oss << ", maxSpeed=" << to_string(&desc->maxSpeed);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_pci_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_srgb_ext_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", sRGB=" << to_string(&desc->sRGB);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_srgb_ext_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_image_allocation_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", id=" << to_string(desc->id);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_image_allocation_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_linkage_inspection_ext_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_linkage_inspection_ext_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_memory_compression_hints_ext_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_memory_compression_hints_ext_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_driver_memory_free_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", freePolicies=" << to_string(&desc->freePolicies);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_driver_memory_free_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_memory_free_ext_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", freePolicy=" << to_string(&desc->freePolicy);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_memory_free_ext_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_p2p_bandwidth_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", logicalBandwidth=" << to_string(desc->logicalBandwidth);
    oss << ", physicalBandwidth=" << to_string(desc->physicalBandwidth);
    oss << ", bandwidthUnit=" << to_string(&desc->bandwidthUnit);
    oss << ", logicalLatency=" << to_string(desc->logicalLatency);
    oss << ", physicalLatency=" << to_string(desc->physicalLatency);
    oss << ", latencyUnit=" << to_string(&desc->latencyUnit);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_p2p_bandwidth_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_copy_bandwidth_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", copyBandwidth=" << to_string(desc->copyBandwidth);
    oss << ", copyBandwidthUnit=" << to_string(&desc->copyBandwidthUnit);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_copy_bandwidth_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_luid_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "id=" << to_string(desc->id);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_luid_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_luid_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", luid=" << to_string(&desc->luid);
    oss << ", nodeMask=" << to_string(desc->nodeMask);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_luid_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_fabric_vertex_pci_exp_address_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "domain=" << to_string(desc->domain);
    oss << ", bus=" << to_string(desc->bus);
    oss << ", device=" << to_string(desc->device);
    oss << ", function=" << to_string(desc->function);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_fabric_vertex_pci_exp_address_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_fabric_vertex_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", uuid=" << to_string(&desc->uuid);
    oss << ", type=" << to_string(&desc->type);
    oss << ", remote=" << to_string(&desc->remote);
    oss << ", address=" << to_string(&desc->address);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_fabric_vertex_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_fabric_edge_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", uuid=" << to_string(&desc->uuid);
    oss << ", model=" << to_string(desc->model);
    oss << ", bandwidth=" << to_string(desc->bandwidth);
    oss << ", bandwidthUnit=" << to_string(&desc->bandwidthUnit);
    oss << ", latency=" << to_string(desc->latency);
    oss << ", latencyUnit=" << to_string(&desc->latencyUnit);
    oss << ", duplexity=" << to_string(&desc->duplexity);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_fabric_edge_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_memory_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", type=" << to_string(&desc->type);
    oss << ", physicalSize=" << to_string(desc->physicalSize);
    oss << ", readBandwidth=" << to_string(desc->readBandwidth);
    oss << ", writeBandwidth=" << to_string(desc->writeBandwidth);
    oss << ", bandwidthUnit=" << to_string(&desc->bandwidthUnit);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_memory_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_ip_version_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", ipVersion=" << to_string(desc->ipVersion);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_ip_version_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_kernel_max_group_size_properties_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", maxGroupSize=" << to_string(desc->maxGroupSize);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_kernel_max_group_size_properties_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_sub_allocation_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "base=" << to_string(desc->base);
    oss << ", size=" << to_string(desc->size);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_sub_allocation_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_memory_sub_allocations_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", pCount=" << to_string(desc->pCount);
    oss << ", pSubAllocations=" << to_string(desc->pSubAllocations);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_memory_sub_allocations_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_event_query_kernel_timestamps_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_event_query_kernel_timestamps_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_synchronized_timestamp_data_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "kernelStart=" << to_string(desc->kernelStart);
    oss << ", kernelEnd=" << to_string(desc->kernelEnd);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_synchronized_timestamp_data_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_synchronized_timestamp_result_ext_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "global=" << to_string(&desc->global);
    oss << ", context=" << to_string(&desc->context);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_synchronized_timestamp_result_ext_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_event_query_kernel_timestamps_results_ext_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", pKernelTimestampsBuffer=" << to_string(desc->pKernelTimestampsBuffer);
    oss << ", pSynchronizedTimestampsBuffer=" << to_string(desc->pSynchronizedTimestampsBuffer);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_event_query_kernel_timestamps_results_ext_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", builderVersion=" << to_string(&desc->builderVersion);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", rtasBufferSizeBytesExpected=" << to_string(desc->rtasBufferSizeBytesExpected);
    oss << ", rtasBufferSizeBytesMaxRequired=" << to_string(desc->rtasBufferSizeBytesMaxRequired);
    oss << ", scratchBufferSizeBytes=" << to_string(desc->scratchBufferSizeBytes);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_parallel_operation_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", maxConcurrency=" << to_string(desc->maxConcurrency);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_parallel_operation_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_device_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << ", rtasFormat=" << to_string(&desc->rtasFormat);
    oss << ", rtasBufferAlignment=" << to_string(desc->rtasBufferAlignment);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_device_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_float3_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "x=" << to_string(desc->x);
    oss << ", y=" << to_string(desc->y);
    oss << ", z=" << to_string(desc->z);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_float3_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_transform_float3x4_column_major_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "vx_x=" << to_string(desc->vx_x);
    oss << ", vx_y=" << to_string(desc->vx_y);
    oss << ", vx_z=" << to_string(desc->vx_z);
    oss << ", vy_x=" << to_string(desc->vy_x);
    oss << ", vy_y=" << to_string(desc->vy_y);
    oss << ", vy_z=" << to_string(desc->vy_z);
    oss << ", vz_x=" << to_string(desc->vz_x);
    oss << ", vz_y=" << to_string(desc->vz_y);
    oss << ", vz_z=" << to_string(desc->vz_z);
    oss << ", p_x=" << to_string(desc->p_x);
    oss << ", p_y=" << to_string(desc->p_y);
    oss << ", p_z=" << to_string(desc->p_z);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_transform_float3x4_column_major_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_transform_float3x4_aligned_column_major_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "vx_x=" << to_string(desc->vx_x);
    oss << ", vx_y=" << to_string(desc->vx_y);
    oss << ", vx_z=" << to_string(desc->vx_z);
    oss << ", pad0=" << to_string(desc->pad0);
    oss << ", vy_x=" << to_string(desc->vy_x);
    oss << ", vy_y=" << to_string(desc->vy_y);
    oss << ", vy_z=" << to_string(desc->vy_z);
    oss << ", pad1=" << to_string(desc->pad1);
    oss << ", vz_x=" << to_string(desc->vz_x);
    oss << ", vz_y=" << to_string(desc->vz_y);
    oss << ", vz_z=" << to_string(desc->vz_z);
    oss << ", pad2=" << to_string(desc->pad2);
    oss << ", p_x=" << to_string(desc->p_x);
    oss << ", p_y=" << to_string(desc->p_y);
    oss << ", p_z=" << to_string(desc->p_z);
    oss << ", pad3=" << to_string(desc->pad3);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_transform_float3x4_aligned_column_major_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_transform_float3x4_row_major_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "vx_x=" << to_string(desc->vx_x);
    oss << ", vy_x=" << to_string(desc->vy_x);
    oss << ", vz_x=" << to_string(desc->vz_x);
    oss << ", p_x=" << to_string(desc->p_x);
    oss << ", vx_y=" << to_string(desc->vx_y);
    oss << ", vy_y=" << to_string(desc->vy_y);
    oss << ", vz_y=" << to_string(desc->vz_y);
    oss << ", p_y=" << to_string(desc->p_y);
    oss << ", vx_z=" << to_string(desc->vx_z);
    oss << ", vy_z=" << to_string(desc->vy_z);
    oss << ", vz_z=" << to_string(desc->vz_z);
    oss << ", p_z=" << to_string(desc->p_z);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_transform_float3x4_row_major_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_aabb_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "lower=" << to_string(&desc->lower);
    oss << ", upper=" << to_string(&desc->upper);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_aabb_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_triangle_indices_uint32_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "v0=" << to_string(desc->v0);
    oss << ", v1=" << to_string(desc->v1);
    oss << ", v2=" << to_string(desc->v2);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_triangle_indices_uint32_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_quad_indices_uint32_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "v0=" << to_string(desc->v0);
    oss << ", v1=" << to_string(desc->v1);
    oss << ", v2=" << to_string(desc->v2);
    oss << ", v3=" << to_string(desc->v3);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_quad_indices_uint32_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_geometry_info_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "geometryType=" << to_string(&desc->geometryType);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_geometry_info_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_triangles_geometry_info_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "geometryType=" << to_string(&desc->geometryType);
    oss << ", geometryFlags=" << to_string(&desc->geometryFlags);
    oss << ", geometryMask=" << to_string(desc->geometryMask);
    oss << ", triangleFormat=" << to_string(&desc->triangleFormat);
    oss << ", vertexFormat=" << to_string(&desc->vertexFormat);
    oss << ", triangleCount=" << to_string(desc->triangleCount);
    oss << ", vertexCount=" << to_string(desc->vertexCount);
    oss << ", triangleStride=" << to_string(desc->triangleStride);
    oss << ", vertexStride=" << to_string(desc->vertexStride);
    oss << ", pTriangleBuffer=" << to_string(desc->pTriangleBuffer);
    oss << ", pVertexBuffer=" << to_string(desc->pVertexBuffer);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_triangles_geometry_info_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_quads_geometry_info_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "geometryType=" << to_string(&desc->geometryType);
    oss << ", geometryFlags=" << to_string(&desc->geometryFlags);
    oss << ", geometryMask=" << to_string(desc->geometryMask);
    oss << ", quadFormat=" << to_string(&desc->quadFormat);
    oss << ", vertexFormat=" << to_string(&desc->vertexFormat);
    oss << ", quadCount=" << to_string(desc->quadCount);
    oss << ", vertexCount=" << to_string(desc->vertexCount);
    oss << ", quadStride=" << to_string(desc->quadStride);
    oss << ", vertexStride=" << to_string(desc->vertexStride);
    oss << ", pQuadBuffer=" << to_string(desc->pQuadBuffer);
    oss << ", pVertexBuffer=" << to_string(desc->pVertexBuffer);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_quads_geometry_info_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_geometry_aabbs_exp_cb_params_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", primID=" << to_string(desc->primID);
    oss << ", primIDCount=" << to_string(desc->primIDCount);
    oss << ", pGeomUserPtr=" << to_string(desc->pGeomUserPtr);
    oss << ", pBuildUserPtr=" << to_string(desc->pBuildUserPtr);
    oss << ", pBoundsOut=" << to_string(desc->pBoundsOut);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_geometry_aabbs_exp_cb_params_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_procedural_geometry_info_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "geometryType=" << to_string(&desc->geometryType);
    oss << ", geometryFlags=" << to_string(&desc->geometryFlags);
    oss << ", geometryMask=" << to_string(desc->geometryMask);
    oss << ", reserved=" << to_string(desc->reserved);
    oss << ", primCount=" << to_string(desc->primCount);
    oss << ", pfnGetBoundsCb=" << to_string(&desc->pfnGetBoundsCb);
    oss << ", pGeomUserPtr=" << to_string(desc->pGeomUserPtr);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_procedural_geometry_info_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_instance_geometry_info_exp_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "geometryType=" << to_string(&desc->geometryType);
    oss << ", instanceFlags=" << to_string(&desc->instanceFlags);
    oss << ", geometryMask=" << to_string(desc->geometryMask);
    oss << ", transformFormat=" << to_string(&desc->transformFormat);
    oss << ", instanceUserID=" << to_string(desc->instanceUserID);
    oss << ", pTransform=" << to_string(desc->pTransform);
    oss << ", pBounds=" << to_string(desc->pBounds);
    oss << ", pAccelerationStructure=" << to_string(desc->pAccelerationStructure);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_instance_geometry_info_exp_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_rtas_builder_build_op_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", rtasFormat=" << to_string(&desc->rtasFormat);
    oss << ", buildQuality=" << to_string(desc->buildQuality);
    oss << ", buildFlags=" << to_string(&desc->buildFlags);
    oss << ", ppGeometries=" << to_string(desc->ppGeometries);
    oss << ", numGeometries=" << to_string(desc->numGeometries);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_rtas_builder_build_op_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_event_pool_counter_based_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_event_pool_counter_based_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_image_bindless_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_image_bindless_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_image_pitched_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", ptr=" << to_string(desc->ptr);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_image_pitched_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_device_pitched_alloc_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", maxImageLinearWidth=" << to_string(desc->maxImageLinearWidth);
    oss << ", maxImageLinearHeight=" << to_string(desc->maxImageLinearHeight);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_device_pitched_alloc_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_pitched_alloc_2dimage_linear_pitch_exp_info_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", pitchAlign=" << to_string(desc->pitchAlign);
    oss << ", maxSupportedPitch=" << to_string(desc->maxSupportedPitch);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_pitched_alloc_2dimage_linear_pitch_exp_info_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_custom_pitch_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", rowPitch=" << to_string(desc->rowPitch);
    oss << ", slicePitch=" << to_string(desc->slicePitch);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_custom_pitch_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_mutable_command_id_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_mutable_command_id_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_mutable_command_list_exp_properties_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", mutableCommandListFlags=" << to_string(&desc->mutableCommandListFlags);
    oss << ", mutableCommandFlags=" << to_string(&desc->mutableCommandFlags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_mutable_command_list_exp_properties_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_mutable_command_list_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(&desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_mutable_command_list_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_mutable_commands_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", flags=" << to_string(desc->flags);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_mutable_commands_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_mutable_kernel_argument_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", commandId=" << to_string(desc->commandId);
    oss << ", argIndex=" << to_string(desc->argIndex);
    oss << ", argSize=" << to_string(desc->argSize);
    oss << ", pArgValue=" << to_string(desc->pArgValue);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_mutable_kernel_argument_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_mutable_group_count_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", commandId=" << to_string(desc->commandId);
    oss << ", pGroupCount=" << to_string(desc->pGroupCount);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_mutable_group_count_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_mutable_group_size_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", commandId=" << to_string(desc->commandId);
    oss << ", groupSizeX=" << to_string(desc->groupSizeX);
    oss << ", groupSizeY=" << to_string(desc->groupSizeY);
    oss << ", groupSizeZ=" << to_string(desc->groupSizeZ);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_mutable_group_size_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_mutable_global_offset_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", commandId=" << to_string(desc->commandId);
    oss << ", offsetX=" << to_string(desc->offsetX);
    oss << ", offsetY=" << to_string(desc->offsetY);
    oss << ", offsetZ=" << to_string(desc->offsetZ);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_mutable_global_offset_exp_desc_t& desc) {
    return to_string(&desc);
}

inline std::string to_string(const ze_mutable_graph_argument_exp_desc_t* desc) {
    if (!desc) return "nullptr";
    std::ostringstream oss;
    oss << "{";
    oss << "stype=" << to_string(&desc->stype);
    oss << ", commandId=" << to_string(desc->commandId);
    oss << ", argIndex=" << to_string(desc->argIndex);
    oss << ", pArgValue=" << to_string(desc->pArgValue);
    oss << "}";
    return oss.str();
}

inline std::string to_string(const ze_mutable_graph_argument_exp_desc_t& desc) {
    return to_string(&desc);
}

} // namespace loader

#endif // _ZE_TO_STRING_H
