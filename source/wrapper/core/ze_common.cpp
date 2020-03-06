/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_common.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero API common types
 *
 */
#include "ze_api.hpp"
#include "ze_singleton.h"

#define _STRING(s) #s
#define STRING(s) _STRING(s)

namespace ze
{
} // namespace ze

namespace ze
{
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

        case result_t::ERROR_INSUFFICIENT_PERMISSIONS:
            str = "result_t::ERROR_INSUFFICIENT_PERMISSIONS";
            break;

        case result_t::ERROR_NOT_AVAILABLE:
            str = "result_t::ERROR_NOT_AVAILABLE";
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

} // namespace ze

namespace ze
{
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
} // namespace ze
