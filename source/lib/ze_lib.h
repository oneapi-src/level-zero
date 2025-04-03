/*
 *
 * Copyright (C) 2019-2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_lib.h
 *
 */
#pragma once
#include "ze_api.h"
#include "ze_ddi.h"
#include "zet_api.h"
#include "zet_ddi.h"
#include "zes_api.h"
#include "zes_ddi.h"
#include "layers/zel_tracing_api.h"
#include "layers/zel_tracing_ddi.h"
#include "../utils/logging.h"
#include "ze_util.h"
#include <vector>
#include <mutex>
#include <atomic>
#include <typeinfo>
#include <iostream>

namespace ze_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    class __zedlllocal context_t
    {
    public:
#ifdef DYNAMIC_LOAD_LOADER
        HMODULE loader = nullptr;
#endif

        context_t();
        ~context_t();

    //////////////////////////////////////////////////////////////////////////
    __zedlllocal std::string to_string(const ze_result_t result) {
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
        } else if (result == ZE_RESULT_ERROR_MODULE_LINK_FAILURE) {
            return "ZE_RESULT_ERROR_MODULE_LINK_FAILURE";
        } else if (result == ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS) {
            return "ZE_RESULT_ERROR_INSUFFICIENT_PERMISSIONS";
        } else if (result == ZE_RESULT_ERROR_NOT_AVAILABLE) {
            return "ZE_RESULT_ERROR_NOT_AVAILABLE";
        } else if (result == ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE) {
            return "ZE_RESULT_ERROR_DEPENDENCY_UNAVAILABLE";
        } else if (result == ZE_RESULT_WARNING_DROPPED_DATA) {
            return "ZE_RESULT_WARNING_DROPPED_DATA";
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
        } else if (result == ZE_RESULT_ERROR_INVALID_MODULE_UNLINKED) {
            return "ZE_RESULT_ERROR_INVALID_MODULE_UNLINKED";
        } else if (result == ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE) {
            return "ZE_RESULT_ERROR_INVALID_COMMAND_LIST_TYPE";
        } else if (result == ZE_RESULT_ERROR_OVERLAPPING_REGIONS) {
            return "ZE_RESULT_ERROR_OVERLAPPING_REGIONS";
        } else if (result == ZE_RESULT_ERROR_UNKNOWN) {
            return "ZE_RESULT_ERROR_UNKNOWN";
        } else {
            return std::to_string(static_cast<int>(result));
        }
    }

    //////////////////////////////////////////////////////////////////////////
    __zedlllocal void debug_trace_message(std::string message, std::string result) {
        if (debugTraceEnabled){
            std::string debugTracePrefix = "ZE_LOADER_DEBUG_TRACE:";
            std::cerr << debugTracePrefix << message << result << std::endl;
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    template <typename T, typename TableType>
    __zedlllocal ze_result_t getTableWithCheck(T getTable, ze_api_version_t version, TableType* table) {
        ze_result_t result = ZE_RESULT_ERROR_UNINITIALIZED;
        if (getTable == nullptr) {
            std::string message = "getTableWithCheck Failed for " + std::string(typeid(TableType).name()) + " with ";
            debug_trace_message(message, to_string(result));
            return result;
        }
        result = getTable(version, table);
        if (result != ZE_RESULT_SUCCESS) {
            std::string message = "getTableWithCheck Failed for " + std::string(typeid(TableType).name()) + " with ";
            debug_trace_message(message, to_string(result));
        }
        return result;
    }

        std::once_flag initOnce;
        std::once_flag initOnceDrivers;
        std::once_flag initOnceSysMan;

        ze_result_t Init(ze_init_flags_t flags, bool sysmanOnly, ze_init_driver_type_desc_t* desc);

        ze_result_t zeDdiTableInit(ze_api_version_t version);
        std::atomic<ze_dditable_t *>  zeDdiTable = {nullptr};

        ze_result_t zetDdiTableInit(ze_api_version_t version);
        std::atomic<zet_dditable_t *> zetDdiTable = {nullptr};

        ze_result_t zesDdiTableInit(ze_api_version_t version);
        std::atomic<zes_dditable_t *> zesDdiTable = {nullptr};

        ze_result_t zelTracingDdiTableInit(ze_api_version_t version);
        zel_tracing_dditable_t  zelTracingDdiTable = {};
        std::atomic<ze_dditable_t *> pTracingZeDdiTable = {nullptr};
        ze_dditable_t initialzeDdiTable;
        zet_dditable_t initialzetDdiTable;
        zes_dditable_t initialzesDdiTable;
        std::atomic_uint32_t tracingLayerEnableCounter{0};

        HMODULE tracing_lib = nullptr;
        bool isInitialized = false;
        bool zesInuse = false;
        bool zeInuse = false;
        bool debugTraceEnabled = false;
        bool dynamicTracingSupported = true;
        ze_pfnDriverGet_t loaderDriverGet = nullptr;
    };

    extern bool destruction;
    extern context_t *context;
    #ifdef DYNAMIC_LOAD_LOADER
    extern bool delayContextDestruction;
    #endif

} // namespace ze_lib
