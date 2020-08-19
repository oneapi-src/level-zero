/*
 *
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */
#pragma once

#include <iostream>
#include <sstream>
#include "ze_api.h"
#include "zet_api.h"

std::string to_string( const ze_structure_type_t val )
{
    std::string str;

    switch( val )
    {
    case ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES:
        str = "DRIVER_PROPERTIES";
        break;

    case ZE_STRUCTURE_TYPE_DRIVER_IPC_PROPERTIES:
        str = "DRIVER_IPC_PROPERTIES";
        break;

    case ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES:
        str = "DEVICE_PROPERTIES";
        break;

    case ZE_STRUCTURE_TYPE_DEVICE_COMPUTE_PROPERTIES:
        str = "DEVICE_COMPUTE_PROPERTIES";
        break;

    case ZE_STRUCTURE_TYPE_DEVICE_MODULE_PROPERTIES:
        str = "DEVICE_MODULE_PROPERTIES";
        break;

    case ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES:
        str = "COMMAND_QUEUE_GROUP_PROPERTIES";
        break;

    case ZE_STRUCTURE_TYPE_DEVICE_MEMORY_PROPERTIES:
        str = "DEVICE_MEMORY_PROPERTIES";
        break;

    case ZE_STRUCTURE_TYPE_DEVICE_MEMORY_ACCESS_PROPERTIES:
        str = "DEVICE_MEMORY_ACCESS_PROPERTIES";
        break;

    case ZE_STRUCTURE_TYPE_DEVICE_CACHE_PROPERTIES:
        str = "DEVICE_CACHE_PROPERTIES";
        break;

    case ZE_STRUCTURE_TYPE_DEVICE_IMAGE_PROPERTIES:
        str = "DEVICE_IMAGE_PROPERTIES";
        break;

    case ZE_STRUCTURE_TYPE_DEVICE_P2P_PROPERTIES:
        str = "DEVICE_P2P_PROPERTIES";
        break;

    case ZE_STRUCTURE_TYPE_DEVICE_EXTERNAL_MEMORY_PROPERTIES:
        str = "DEVICE_EXTERNAL_MEMORY_PROPERTIES";
        break;

    case ZE_STRUCTURE_TYPE_CONTEXT_DESC:
        str = "CONTEXT_DESC";
        break;

    case ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC:
        str = "COMMAND_QUEUE_DESC";
        break;

    case ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC:
        str = "COMMAND_LIST_DESC";
        break;

    case ZE_STRUCTURE_TYPE_EVENT_POOL_DESC:
        str = "EVENT_POOL_DESC";
        break;

    case ZE_STRUCTURE_TYPE_EVENT_DESC:
        str = "EVENT_DESC";
        break;

    case ZE_STRUCTURE_TYPE_FENCE_DESC:
        str = "FENCE_DESC";
        break;

    case ZE_STRUCTURE_TYPE_IMAGE_DESC:
        str = "IMAGE_DESC";
        break;

    case ZE_STRUCTURE_TYPE_IMAGE_PROPERTIES:
        str = "IMAGE_PROPERTIES";
        break;

    case ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC:
        str = "DEVICE_MEM_ALLOC_DESC";
        break;

    default:
        str = "?";
        break;
    };

    return str;
}

std::string to_string( const ze_device_uuid_t val )
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

std::string to_string(const ze_device_cache_property_flag_t val )
{
    const auto bits = static_cast<uint32_t>( val );

    std::string str;

    if( 0 == bits )
        str += "0 | ";
    
    if( static_cast<uint32_t>(ZE_DEVICE_CACHE_PROPERTY_FLAG_USER_CONTROL) & bits )
        str += "CACHE_PROPERTY_FLAG_USER_CONTROL | ";

    return ( str.size() > 3 ) 
        ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
        : "Device::{ ? }";
}

std::string to_string( ze_device_cache_properties_t val )
{
    std::string str;
    
    str += "ze_device_cache_properties_t.stype : ";
    str += to_string(val.stype);
    str += "\n";
    
    str += "ze_device_cache_properties_t.pNext : ";
    {
        std::stringstream ss;
        ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
        str += ss.str();
    }
    str += "\n";
    
    str += "ze_device_cache_properties_t.flags : ";
    str += to_string((ze_device_cache_property_flag_t)val.flags);
    str += "\n";
    
    str += "ze_device_cache_properties_t.cacheSize : ";
    str += std::to_string(val.cacheSize);
    str += "\n";

    return str;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Device::image_properties_t to std::string
std::string to_string( ze_device_image_properties_t val )
{
    std::string str;
    
    str += "ze_device_image_properties_t.stype : ";
    str += to_string(val.stype);
    str += "\n";
    
    str += "ze_device_image_properties_t.pNext : ";
    {
        std::stringstream ss;
        ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
        str += ss.str();
    }
    str += "\n";
    
    str += "ze_device_image_properties_t.maxImageDims1D : ";
    str += std::to_string(val.maxImageDims1D);
    str += "\n";
    
    str += "ze_device_image_properties_t.maxImageDims2D : ";
    str += std::to_string(val.maxImageDims2D);
    str += "\n";
    
    str += "ze_device_image_properties_t.maxImageDims3D : ";
    str += std::to_string(val.maxImageDims3D);
    str += "\n";
    
    str += "ze_device_image_properties_t.maxImageBufferSize : ";
    str += std::to_string(val.maxImageBufferSize);
    str += "\n";
    
    str += "ze_device_image_properties_t.maxImageArraySlices : ";
    str += std::to_string(val.maxImageArraySlices);
    str += "\n";
    
    str += "ze_device_image_properties_t.maxSamplers : ";
    str += std::to_string(val.maxSamplers);
    str += "\n";
    
    str += "ze_device_image_properties_t.maxReadImageArgs : ";
    str += std::to_string(val.maxReadImageArgs);
    str += "\n";
    
    str += "ze_device_image_properties_t.maxWriteImageArgs : ";
    str += std::to_string(val.maxWriteImageArgs);
    str += "\n";

    return str;
}
std::string to_string( ze_memory_access_cap_flag_t val )
{
    const auto bits = static_cast<uint32_t>( val );

    std::string str;

    if( 0 == bits )
        str += "0 | ";
    
    if( static_cast<uint32_t>(ZE_MEMORY_ACCESS_CAP_FLAG_RW) & bits )
        str += "MEMORY_ACCESS_CAP_FLAG_RW | ";
    
    if( static_cast<uint32_t>(ZE_MEMORY_ACCESS_CAP_FLAG_ATOMIC) & bits )
        str += "MEMORY_ACCESS_CAP_FLAG_ATOMIC | ";
    
    if( static_cast<uint32_t>(ZE_MEMORY_ACCESS_CAP_FLAG_CONCURRENT) & bits )
        str += "MEMORY_ACCESS_CAP_FLAG_CONCURRENT | ";
    
    if( static_cast<uint32_t>(ZE_MEMORY_ACCESS_CAP_FLAG_CONCURRENT_ATOMIC) & bits )
        str += "MEMORY_ACCESS_CAP_FLAG_CONCURRENT_ATOMIC | ";

    return ( str.size() > 3 ) 
        ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
        : "Device::{ ? }";
}



std::string to_string( ze_device_memory_access_properties_t val )
{
    std::string str;
    
    str += "ze_device_memory_access_properties_t.stype : ";
    str += to_string(val.stype);
    str += "\n";
    
    str += "ze_device_memory_access_properties_t.pNext : ";
    {
        std::stringstream ss;
        ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
        str += ss.str();
    }
    str += "\n";
    
    str += "ze_device_memory_access_properties_t.hostAllocCapabilities : ";
    str += to_string((ze_memory_access_cap_flag_t)val.hostAllocCapabilities);
    str += "\n";
    
    str += "ze_device_memory_access_properties_t.deviceAllocCapabilities : ";
    str += to_string((ze_memory_access_cap_flag_t)val.deviceAllocCapabilities);
    str += "\n";
    
    str += "ze_device_memory_access_properties_t.sharedSingleDeviceAllocCapabilities : ";
    str += to_string((ze_memory_access_cap_flag_t)val.sharedSingleDeviceAllocCapabilities);
    str += "\n";
    
    str += "ze_device_memory_access_properties_t.sharedCrossDeviceAllocCapabilities : ";
    str += to_string((ze_memory_access_cap_flag_t)val.sharedCrossDeviceAllocCapabilities);
    str += "\n";
    
    str += "ze_device_memory_access_properties_t.sharedSystemAllocCapabilities : ";
    str += to_string((ze_memory_access_cap_flag_t)val.sharedSystemAllocCapabilities);
    str += "\n";

    return str;
}

std::string to_string( ze_device_memory_property_flag_t val )
{
    const auto bits = static_cast<uint32_t>( val );

    std::string str;

    if( 0 == bits )
        str += "0 | ";
    
    if( static_cast<uint32_t>(ZE_DEVICE_MEMORY_PROPERTY_FLAG_TBD) & bits )
        str += "MEMORY_PROPERTY_FLAG_TBD | ";

    return ( str.size() > 3 ) 
        ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
        : "Device::{ ? }";
}

std::string to_string( const ze_device_memory_properties_t val )
{
    std::string str;
    
    str += "stype : ";
    str += to_string(val.stype);
    str += "\n";
    
    str += "pNext : ";
    {
        std::stringstream ss;
        ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
        str += ss.str();
    }
    str += "\n";
    
    str += "flags : ";
    str += to_string((ze_device_memory_property_flag_t)val.flags);
    str += "\n";
    
    str += "maxClockRate : ";
    str += std::to_string(val.maxClockRate);
    str += "\n";
    
    str += "maxBusWidth : ";
    str += std::to_string(val.maxBusWidth);
    str += "\n";
    
    str += "totalSize : ";
    str += std::to_string(val.totalSize);
    str += "\n";
    
    str += "name : ";
    str += val.name;
    str += "\n";

    return str;
}

std::string to_string( const ze_device_compute_properties_t val )
{
    std::string str;
    
    str += "stype : ";
    str += to_string(val.stype);
    str += "\n";
    
    str += "pNext : ";
    {
        std::stringstream ss;
        ss << "0x" << std::hex << reinterpret_cast<size_t>(val.pNext);
        str += ss.str();
    }
    str += "\n";
    
    str += "maxTotalGroupSize : ";
    str += std::to_string(val.maxTotalGroupSize);
    str += "\n";
    
    str += "maxGroupSizeX : ";
    str += std::to_string(val.maxGroupSizeX);
    str += "\n";
    
    str += "maxGroupSizeY : ";
    str += std::to_string(val.maxGroupSizeY);
    str += "\n";
    
    str += "maxGroupSizeZ : ";
    str += std::to_string(val.maxGroupSizeZ);
    str += "\n";
    
    str += "maxGroupCountX : ";
    str += std::to_string(val.maxGroupCountX);
    str += "\n";
    
    str += "maxGroupCountY : ";
    str += std::to_string(val.maxGroupCountY);
    str += "\n";
    
    str += "maxGroupCountZ : ";
    str += std::to_string(val.maxGroupCountZ);
    str += "\n";
    
    str += "maxSharedLocalMemory : ";
    str += std::to_string(val.maxSharedLocalMemory);
    str += "\n";
    
    str += "numSubGroupSizes : ";
    str += std::to_string(val.numSubGroupSizes);
    str += "\n";
    
    str += "subGroupSizes : ";
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


std::string to_string( const ze_device_type_t val )
{
    std::string str;

    switch( val )
    {
    case ZE_DEVICE_TYPE_GPU:
        str = "ZE_DEVICE_TYPE_GPU";
        break;

    case ZE_DEVICE_TYPE_CPU:
        str = "ZE_DEVICE_TYPE_CPU";
        break;

    case ZE_DEVICE_TYPE_FPGA:
        str = "ZE_DEVICE_TYPE_FPGA";
        break;

    case ZE_DEVICE_TYPE_MCA:
        str = "ZE_DEVICE_TYPE_MCA";
        break;

    default:
        str = "?";
        break;
    };

    return str;
}

std::string to_string( ze_device_property_flag_t val )
{
    const auto bits = static_cast<uint32_t>( val );

    std::string str;

    if( 0 == bits )
        str += "0 | ";
    
    if( static_cast<uint32_t>(ZE_DEVICE_PROPERTY_FLAG_INTEGRATED) & bits )
        str += "PROPERTY_FLAG_INTEGRATED | ";
    
    if( static_cast<uint32_t>(ZE_DEVICE_PROPERTY_FLAG_SUBDEVICE) & bits )
        str += "PROPERTY_FLAG_SUBDEVICE | ";
    
    if( static_cast<uint32_t>(ZE_DEVICE_PROPERTY_FLAG_ECC) & bits )
        str += "PROPERTY_FLAG_ECC | ";
    
    if( static_cast<uint32_t>(ZE_DEVICE_PROPERTY_FLAG_ONDEMANDPAGING) & bits )
        str += "PROPERTY_FLAG_ONDEMANDPAGING | ";

    return ( str.size() > 3 ) 
        ? "Device::{ " + str.substr(0, str.size() - 3) + " }"
        : "Device::{ ? }";
}


std::string to_string(const ze_device_properties_t val)
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
    str += to_string((ze_device_property_flag_t)val.flags);
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


std::string to_string(const ze_api_version_t version) {
  std::stringstream ss;
  ss << ZE_MAJOR_VERSION(version) << "." << ZE_MINOR_VERSION(version);
  return ss.str();
}

std::string to_string(const ze_result_t result) {
  if (result == ZE_RESULT_SUCCESS) {
    return "ZE_RESULT_SUCCESS";
  } else if (result == ZE_RESULT_NOT_READY) {
    return "ZE_RESULT_NOT_READY";
  } else if (result == ZE_RESULT_ERROR_UNINITIALIZED) {
    return "ZE_RESULT_ERROR_UNINITIALIZED";
  } else if (result == ZE_RESULT_ERROR_DEVICE_LOST) {
    return "ZE_RESULT_ERROR_DEVICE_LOST";
  } else if (result == ZE_RESULT_ERROR_INVALID_ARGUMENT) {
    return "ZE_RESULT_ERROR_INVALID_ARGUMENT";
  } else if (result == ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY) {
    return "ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY";
  } else if (result == ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY) {
    return "ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY";
  } else if (result == ZE_RESULT_ERROR_MODULE_BUILD_FAILURE) {
    return "ZE_RESULT_ERROR_MODULE_BUILD_FAILURE";
  } else if (result == ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS) {
    return "ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS";
  } else if (result == ZE_RESULT_ERROR_NOT_AVAILABLE) {
    return "ZE_RESULT_ERROR_NOT_AVAILABLE";
  } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_VERSION) {
    return "ZE_RESULT_ERROR_UNSUPPORTED_VERSION";
  } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_FEATURE) {
    return "ZE_RESULT_ERROR_UNSUPPORTED_FEATURE";
  } else if (result == ZE_RESULT_ERROR_INVALID_NULL_HANDLE) {
    return "ZE_RESULT_ERROR_INVALID_NULL_HANDLE";
  } else if (result == ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE) {
    return "ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE";
  } else if (result == ZE_RESULT_ERROR_INVALID_NULL_POINTER) {
    return "ZE_RESULT_ERROR_INVALID_NULL_POINTER";
  } else if (result == ZE_RESULT_ERROR_INVALID_SIZE) {
    return "ZE_RESULT_ERROR_INVALID_SIZE";
  } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_SIZE) {
    return "ZE_RESULT_ERROR_UNSUPPORTED_SIZE";
  } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT) {
    return "ZE_RESULT_ERROR_UNSUPPORTED_ALIGNMENT";
  } else if (result == ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT) {
    return "ZE_RESULT_ERROR_INVALID_SYNCHRONIZATION_OBJECT";
  } else if (result == ZE_RESULT_ERROR_INVALID_ENUMERATION) {
    return "ZE_RESULT_ERROR_INVALID_ENUMERATION";
  } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION) {
    return "ZE_RESULT_ERROR_UNSUPPORTED_ENUMERATION";
  } else if (result == ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT) {
    return "ZE_RESULT_ERROR_UNSUPPORTED_IMAGE_FORMAT";
  } else if (result == ZE_RESULT_ERROR_INVALID_NATIVE_BINARY) {
    return "ZE_RESULT_ERROR_INVALID_NATIVE_BINARY";
  } else if (result == ZE_RESULT_ERROR_INVALID_GLOBAL_NAME) {
    return "ZE_RESULT_ERROR_INVALID_GLOBAL_NAME";
  } else if (result == ZE_RESULT_ERROR_INVALID_KERNEL_NAME) {
    return "ZE_RESULT_ERROR_INVALID_KERNEL_NAME";
  } else if (result == ZE_RESULT_ERROR_INVALID_FUNCTION_NAME) {
    return "ZE_RESULT_ERROR_INVALID_FUNCTION_NAME";
  } else if (result == ZE_RESULT_ERROR_INVALID_GROUP_SIZE_DIMENSION) {
    return "ZE_RESULT_ERROR_INVALID_GROUP_SIZE_DIMENSION";
  } else if (result == ZE_RESULT_ERROR_INVALID_GLOBAL_WIDTH_DIMENSION) {
    return "ZE_RESULT_ERROR_INVALID_GLOBAL_WIDTH_DIMENSION";
  } else if (result == ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_INDEX) {
    return "ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_INDEX";
  } else if (result == ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_SIZE) {
    return "ZE_RESULT_ERROR_INVALID_KERNEL_ARGUMENT_SIZE";
  } else if (result == ZE_RESULT_ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE) {
    return "ZE_RESULT_ERROR_INVALID_KERNEL_ATTRIBUTE_VALUE";
  } else if (result == ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE) {
    return "ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE";
  } else if (result == ZE_RESULT_ERROR_OVERLAPPING_REGIONS) {
    return "ZE_RESULT_ERROR_OVERLAPPING_REGIONS";
  } else if (result == ZE_RESULT_ERROR_UNKNOWN) {
    return "ZE_RESULT_ERROR_UNKNOWN";
  } else {
    throw std::runtime_error("Unknown ze_result_t value: " +
                             std::to_string(static_cast<int>(result)));
  }
}

std::string to_string(const ze_bool_t ze_bool) {
  if (ze_bool) {
    return "True";
  } else {
    return "False";
  }
}

std::string to_string(const ze_command_queue_flag_t flags) {
  if (flags == 0) {
    return "Default";
  } else if (flags == ZE_COMMAND_QUEUE_FLAG_EXPLICIT_ONLY) {
    return "ZE_COMMAND_QUEUE_FLAG_EXPLICIT_ONLY";
  } else if (flags == ZE_COMMAND_QUEUE_FLAG_FORCE_UINT32) {
    return "ZE_COMMAND_QUEUE_FLAG_FORCE_UINT32";
  } else {
    return "Unknown ze_command_queue_flag_t value: " +
           std::to_string(static_cast<int>(flags));
  }
}

std::string to_string(const ze_command_queue_mode_t mode) {
  if (mode == ZE_COMMAND_QUEUE_MODE_DEFAULT) {
    return "ZE_COMMAND_QUEUE_MODE_DEFAULT";
  } else if (mode == ZE_COMMAND_QUEUE_MODE_SYNCHRONOUS) {
    return "ZE_COMMAND_QUEUE_MODE_SYNCHRONOUS";
  } else if (mode == ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS) {
    return "ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS";
  } else {
    return "Unknown ze_command_queue_mode_t value: " +
           std::to_string(static_cast<int>(mode));
  }
}

std::string to_string(const ze_command_queue_priority_t priority) {
  if (priority == ZE_COMMAND_QUEUE_PRIORITY_NORMAL) {
    return "ZE_COMMAND_QUEUE_PRIORITY_NORMAL";
  } else if (priority == ZE_COMMAND_QUEUE_PRIORITY_PRIORITY_LOW) {
    return "ZE_COMMAND_QUEUE_PRIORITY_LOW";
  } else if (priority == ZE_COMMAND_QUEUE_PRIORITY_PRIORITY_HIGH) {
    return "ZE_COMMAND_QUEUE_PRIORITY_HIGH";
  } else {
    return "Unknown ze_command_queue_priority_t value: " +
           std::to_string(static_cast<int>(priority));
  }
}

std::string to_string(const ze_image_format_layout_t layout) {
  if (layout == ZE_IMAGE_FORMAT_LAYOUT_8) {
    return "ZE_IMAGE_FORMAT_LAYOUT_8";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_16) {
    return "ZE_IMAGE_FORMAT_LAYOUT_16";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_32) {
    return "ZE_IMAGE_FORMAT_LAYOUT_32";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_8_8) {
    return "ZE_IMAGE_FORMAT_LAYOUT_8_8";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_8_8_8_8) {
    return "ZE_IMAGE_FORMAT_LAYOUT_8_8_8_8";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_16_16) {
    return "ZE_IMAGE_FORMAT_LAYOUT_16_16";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_16_16_16_16) {
    return "ZE_IMAGE_FORMAT_LAYOUT_16_16_16_16";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_32_32) {
    return "ZE_IMAGE_FORMAT_LAYOUT_32_32";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_32_32_32_32) {
    return "ZE_IMAGE_FORMAT_LAYOUT_32_32_32_32";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_10_10_10_2) {
    return "ZE_IMAGE_FORMAT_LAYOUT_10_10_10_2";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_11_11_10) {
    return "ZE_IMAGE_FORMAT_LAYOUT_11_11_10";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_5_6_5) {
    return "ZE_IMAGE_FORMAT_LAYOUT_5_6_5";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_5_5_5_1) {
    return "ZE_IMAGE_FORMAT_LAYOUT_5_5_5_1";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_4_4_4_4) {
    return "ZE_IMAGE_FORMAT_LAYOUT_4_4_4_4";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_Y8) {
    return "ZE_IMAGE_FORMAT_LAYOUT_Y8";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_NV12) {
    return "ZE_IMAGE_FORMAT_LAYOUT_NV12";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_YUYV) {
    return "ZE_IMAGE_FORMAT_LAYOUT_YUYV";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_VYUY) {
    return "ZE_IMAGE_FORMAT_LAYOUT_VYUY";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_YVYU) {
    return "ZE_IMAGE_FORMAT_LAYOUT_YVYU";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_UYVY) {
    return "ZE_IMAGE_FORMAT_LAYOUT_UYVY";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_AYUV) {
    return "ZE_IMAGE_FORMAT_LAYOUT_AYUV";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_P010) {
    return "ZE_IMAGE_FORMAT_LAYOUT_P010";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_Y410) {
    return "ZE_IMAGE_FORMAT_LAYOUT_Y410";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_P012) {
    return "ZE_IMAGE_FORMAT_LAYOUT_P012";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_Y16) {
    return "ZE_IMAGE_FORMAT_LAYOUT_Y16";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_P016) {
    return "ZE_IMAGE_FORMAT_LAYOUT_P016";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_Y216) {
    return "ZE_IMAGE_FORMAT_LAYOUT_Y216";
  } else if (layout == ZE_IMAGE_FORMAT_LAYOUT_P216) {
    return "ZE_IMAGE_FORMAT_LAYOUT_P216";
  } else {
    return "Unknown ze_image_format_layout_t value: " +
           std::to_string(static_cast<int>(layout));
  }
}

ze_image_format_layout_t to_layout(const std::string layout) {
  if (layout == "8") {
    return ZE_IMAGE_FORMAT_LAYOUT_8;
  } else if (layout == "16") {
    return ZE_IMAGE_FORMAT_LAYOUT_16;
  } else if (layout == "32") {
    return ZE_IMAGE_FORMAT_LAYOUT_32;
  } else if (layout == "8_8") {
    return ZE_IMAGE_FORMAT_LAYOUT_8_8;
  } else if (layout == "8_8_8_8") {
    return ZE_IMAGE_FORMAT_LAYOUT_8_8_8_8;
  } else if (layout == "16_16") {
    return ZE_IMAGE_FORMAT_LAYOUT_16_16;
  } else if (layout == "16_16_16_16") {
    return ZE_IMAGE_FORMAT_LAYOUT_16_16_16_16;
  } else if (layout == "32_32") {
    return ZE_IMAGE_FORMAT_LAYOUT_32_32;
  } else if (layout == "32_32_32_32") {
    return ZE_IMAGE_FORMAT_LAYOUT_32_32_32_32;
  } else if (layout == "10_10_10_2") {
    return ZE_IMAGE_FORMAT_LAYOUT_10_10_10_2;
  } else if (layout == "11_11_10") {
    return ZE_IMAGE_FORMAT_LAYOUT_11_11_10;
  } else if (layout == "5_6_5") {
    return ZE_IMAGE_FORMAT_LAYOUT_5_6_5;
  } else if (layout == "5_5_5_1") {
    return ZE_IMAGE_FORMAT_LAYOUT_5_5_5_1;
  } else if (layout == "4_4_4_4") {
    return ZE_IMAGE_FORMAT_LAYOUT_4_4_4_4;
  } else if (layout == "Y8") {
    return ZE_IMAGE_FORMAT_LAYOUT_Y8;
  } else if (layout == "NV12") {
    return ZE_IMAGE_FORMAT_LAYOUT_NV12;
  } else if (layout == "YUYV") {
    return ZE_IMAGE_FORMAT_LAYOUT_YUYV;
  } else if (layout == "VYUY") {
    return ZE_IMAGE_FORMAT_LAYOUT_VYUY;
  } else if (layout == "YVYU") {
    return ZE_IMAGE_FORMAT_LAYOUT_YVYU;
  } else if (layout == "UYVY") {
    return ZE_IMAGE_FORMAT_LAYOUT_UYVY;
  } else if (layout == "AYUV") {
    return ZE_IMAGE_FORMAT_LAYOUT_AYUV;
  } else if (layout == "P010") {
    return ZE_IMAGE_FORMAT_LAYOUT_P010;
  } else if (layout == "Y410") {
    return ZE_IMAGE_FORMAT_LAYOUT_Y410;
  } else if (layout == "P012") {
    return ZE_IMAGE_FORMAT_LAYOUT_P012;
  } else if (layout == "Y16") {
    return ZE_IMAGE_FORMAT_LAYOUT_Y16;
  } else if (layout == "P016") {
    return ZE_IMAGE_FORMAT_LAYOUT_P016;
  } else if (layout == "Y216") {
    return ZE_IMAGE_FORMAT_LAYOUT_Y216;
  } else if (layout == "P216") {
    return ZE_IMAGE_FORMAT_LAYOUT_P216;
  } else {
    std::cout << "Unknown ze_image_format_layout_t value: " << layout;
    return static_cast<ze_image_format_layout_t>(-1);
  }
}

std::string to_string(const ze_image_format_type_t type) {
  if (type == ZE_IMAGE_FORMAT_TYPE_UINT) {
    return "ZE_IMAGE_FORMAT_TYPE_UINT";
  } else if (type == ZE_IMAGE_FORMAT_TYPE_SINT) {
    return "ZE_IMAGE_FORMAT_TYPE_SINT";
  } else if (type == ZE_IMAGE_FORMAT_TYPE_UNORM) {
    return "ZE_IMAGE_FORMAT_TYPE_UNORM";
  } else if (type == ZE_IMAGE_FORMAT_TYPE_SNORM) {
    return "ZE_IMAGE_FORMAT_TYPE_SNORM";
  } else if (type == ZE_IMAGE_FORMAT_TYPE_FLOAT) {
    return "ZE_IMAGE_FORMAT_TYPE_FLOAT";
  } else {
    return "Unknown ze_image_format_type_t value: " +
           std::to_string(static_cast<int>(type));
  }
}

ze_image_format_type_t to_format_type(const std::string format_type) {
  if (format_type == "UINT") {
    return ZE_IMAGE_FORMAT_TYPE_UINT;
  } else if (format_type == "SINT") {
    return ZE_IMAGE_FORMAT_TYPE_SINT;
  } else if (format_type == "UNORM") {
    return ZE_IMAGE_FORMAT_TYPE_UNORM;
  } else if (format_type == "SNORM") {
    return ZE_IMAGE_FORMAT_TYPE_SNORM;
  } else if (format_type == "FLOAT") {
    return ZE_IMAGE_FORMAT_TYPE_FLOAT;
  } else {
    std::cout << "Unknown ze_image_format_type_t value: ";
    return (static_cast<ze_image_format_type_t>(-1));
  }
}

std::string to_string(const ze_image_format_swizzle_t swizzle) {
  if (swizzle == ZE_IMAGE_FORMAT_SWIZZLE_R) {
    return "ZE_IMAGE_FORMAT_SWIZZLE_R";
  } else if (swizzle == ZE_IMAGE_FORMAT_SWIZZLE_G) {
    return "ZE_IMAGE_FORMAT_SWIZZLE_G";
  } else if (swizzle == ZE_IMAGE_FORMAT_SWIZZLE_B) {
    return "ZE_IMAGE_FORMAT_SWIZZLE_B";
  } else if (swizzle == ZE_IMAGE_FORMAT_SWIZZLE_A) {
    return "ZE_IMAGE_FORMAT_SWIZZLE_A";
  } else if (swizzle == ZE_IMAGE_FORMAT_SWIZZLE_0) {
    return "ZE_IMAGE_FORMAT_SWIZZLE_0";
  } else if (swizzle == ZE_IMAGE_FORMAT_SWIZZLE_1) {
    return "ZE_IMAGE_FORMAT_SWIZZLE_1";
  } else if (swizzle == ZE_IMAGE_FORMAT_SWIZZLE_X) {
    return "ZE_IMAGE_FORMAT_SWIZZLE_X";
  } else {
    return "Unknown ze_image_format_swizzle_t value: " +
           std::to_string(static_cast<int>(swizzle));
  }
}

std::string to_string(const ze_image_flag_t flag) {
  std::string flags = "";
  if (flag & ZE_IMAGE_FLAG_KERNEL_WRITE) {
    flags.append("|ZE_IMAGE_FLAG_KERNEL_WRITE|");
  }
  if (flag & ZE_IMAGE_FLAG_BIAS_UNCACHED) {
    flags.append("|ZE_IMAGE_FLAG_BIAS_UNCACHED|");
  }

  return flags;
}

ze_image_flag_t to_flag(const std::string flag) {

  // by default setting to READ
  ze_image_flag_t image_flags = {};

  // check if "READ" position is found in flag string
  if (flag.find("WRITE") != std::string::npos) {
    image_flags =
        static_cast<ze_image_flag_t>(image_flags | ZE_IMAGE_FLAG_KERNEL_WRITE);
  }
  if (flag.find("UNCACHED") != std::string::npos) {
    image_flags =
        static_cast<ze_image_flag_t>(image_flags | ZE_IMAGE_FLAG_BIAS_UNCACHED);
  }

  return image_flags;
}

std::string to_string(const ze_image_type_t type) {
  if (type == ZE_IMAGE_TYPE_1D) {
    return "ZE_IMAGE_TYPE_1D";
  } else if (type == ZE_IMAGE_TYPE_2D) {
    return "ZE_IMAGE_TYPE_2D";
  } else if (type == ZE_IMAGE_TYPE_3D) {
    return "ZE_IMAGE_TYPE_3D";
  } else if (type == ZE_IMAGE_TYPE_1DARRAY) {
    return "ZE_IMAGE_TYPE_1DARRAY";
  } else if (type == ZE_IMAGE_TYPE_2DARRAY) {
    return "ZE_IMAGE_TYPE_2DARRAY";
  } else {
    return "Unknown ze_image_type_t value: " +
           std::to_string(static_cast<int>(type));
  }
}

ze_image_type_t to_image_type(const std::string type) {
  if (type == "1D") {
    return ZE_IMAGE_TYPE_1D;
  } else if (type == "2D") {
    return ZE_IMAGE_TYPE_2D;
  } else if (type == "3D") {
    return ZE_IMAGE_TYPE_3D;
  } else if (type == "1DARRAY") {
    return ZE_IMAGE_TYPE_1DARRAY;
  } else if (type == "2DARRAY") {
    return ZE_IMAGE_TYPE_2DARRAY;
  } else {
    std::cout << "Unknown ze_image_type_t value: ";
    return (static_cast<ze_image_type_t>(-1));
  }
}

std::string to_string(const ze_device_fp_flags_t capabilities) {
  std::string capabilities_str = "";
  if (capabilities == 0) {
    capabilities_str.append("|NONE|");
    return capabilities_str;
  }
  if (capabilities & ZE_DEVICE_FP_FLAG_DENORM) {
    capabilities_str.append("|ZE_DEVICE_FP_FLAG_DENORM|");
  }
  if (capabilities & ZE_DEVICE_FP_FLAG_INF_NAN) {
    capabilities_str.append("|ZE_DEVICE_FP_FLAG_INF_NAN|");
  }
  if (capabilities & ZE_DEVICE_FP_FLAG_ROUND_TO_NEAREST) {
    capabilities_str.append("|ZE_DEVICE_FP_FLAG_ROUND_TO_NEAREST|");
  }
  if (capabilities & ZE_DEVICE_FP_FLAG_ROUND_TO_ZERO) {
    capabilities_str.append("|ZE_DEVICE_FP_FLAG_ROUND_TO_ZERO|");
  }
  if (capabilities & ZE_DEVICE_FP_FLAG_ROUND_TO_INF) {
    capabilities_str.append("|ZE_DEVICE_FP_FLAG_ROUND_TO_INF|");
  }
  if (capabilities & ZE_DEVICE_FP_FLAG_FMA) {
    capabilities_str.append("|ZE_DEVICE_FP_FLAG_FMA|");
  }
  if (capabilities & ZE_DEVICE_FP_FLAG_ROUNDED_DIVIDE_SQRT) {
    capabilities_str.append("|ZE_DEVICE_FP_FLAG_ROUNDED_DIVIDE_SQRT|");
  }
  if (capabilities & ZE_DEVICE_FP_FLAG_SOFT_FLOAT) {
    capabilities_str.append("|ZE_DEVICE_FP_FLAG_SOFT_FLOAT|");
  }
  return capabilities_str;
}

std::string to_string(const ze_driver_uuid_t uuid) {
  std::ostringstream result;
  result << "{";
  for (int i = 0; i < ZE_MAX_DRIVER_UUID_SIZE; i++) {
    result << "0x" << std::hex << uuid.id[i] << ",";
  }
  result << "\b}";
  return result.str();
}

std::string to_string(const ze_native_kernel_uuid_t uuid) {
  std::ostringstream result;
  result << "{";
  for (int i = 0; i < ZE_MAX_NATIVE_KERNEL_UUID_SIZE; i++) {
    result << "0x" << std::hex << uuid.id[i] << ",";
  }
  result << "\b}";
  return result.str();
}