/*
 *
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "logging.h"
namespace loader {

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
} // namespace loader