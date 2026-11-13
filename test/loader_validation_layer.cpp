/*
 *
 * Copyright (C) 2024-2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"
#include "loader/ze_loader.h"
#include "ze_api.h"
#include "zer_api.h"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#if defined(_WIN32)
#include <windows.h>
#define putenv_safe _putenv
#else
#include <unistd.h>
#define putenv_safe putenv
#endif

TEST(
    LoaderValidation,
    GivenLevelZeroLoaderPresentWhenCallingzeCommandListAppendMemoryCopyWithCircularDependencyOnEventsThenValidationLayerPrintsWarningOfDeadlock) {

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_TYPE=GPU"));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_GPU_ONLY));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    ze_result_t status;
    const ze_device_type_t type = ZE_DEVICE_TYPE_GPU;

    ze_driver_handle_t pDriver = nullptr;
    ze_device_handle_t pDevice = nullptr;

    uint32_t driverCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, nullptr));

    std::vector<ze_driver_handle_t> drivers(driverCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, drivers.data()));

    for (uint32_t driver = 0; driver < driverCount; ++driver) {
        pDriver = drivers[driver];

        // get all devices
        uint32_t deviceCount = 0;
        EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(pDriver, &deviceCount, nullptr));

        std::vector<ze_device_handle_t> devices(deviceCount);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(pDriver, &deviceCount, devices.data()));

        // for each device, find the first one matching the type
        for (uint32_t device = 0; device < deviceCount; ++device) {
            auto phDevice = devices[device];

            ze_device_properties_t device_properties = {};
            device_properties.stype = ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES;
            EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGetProperties(phDevice, &device_properties));

            if (type == device_properties.type) {
                pDevice = phDevice;
                break;
            }
        }

        if (pDevice) {
            break;
        }
    }
    EXPECT_NE(pDevice, nullptr);

    ze_context_handle_t context;
    ze_context_desc_t context_desc = {};
    context_desc.stype = ZE_STRUCTURE_TYPE_CONTEXT_DESC;

    status = zeContextCreate(pDriver, &context_desc, &context);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    // Create an  command list for direct submission
    ze_command_list_desc_t altdesc = {};
    altdesc.stype = ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC;

    ze_command_list_handle_t command_list = {};
    status = zeCommandListCreate(context, pDevice, &altdesc, &command_list);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    // Create an event to be signaled by the device
    ze_event_pool_desc_t ep_desc = {};
    ep_desc.stype = ZE_STRUCTURE_TYPE_EVENT_POOL_DESC;
    ep_desc.count = 3;
    ep_desc.flags = ZE_EVENT_POOL_FLAG_HOST_VISIBLE;

    ze_event_pool_handle_t event_pool;

    status = zeEventPoolCreate(context, &ep_desc, 1, &pDevice, &event_pool);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    std::vector<ze_event_handle_t> event{};
    // Three events for memcpy that will form a circular dependency.
    event.resize(3);

    ze_event_desc_t ev_desc = {};
    ev_desc.stype = ZE_STRUCTURE_TYPE_EVENT_DESC;
    ev_desc.signal = ZE_EVENT_SCOPE_FLAG_DEVICE;
    ev_desc.wait = ZE_EVENT_SCOPE_FLAG_HOST;

    for (uint32_t i = 0; i < 3; ++i) {
        ev_desc.index = i;
        status = zeEventCreate(event_pool, &ev_desc, &event[i]);
        EXPECT_EQ(ZE_RESULT_SUCCESS, status);
    }

    ze_host_mem_alloc_desc_t host_desc = {};
    host_desc.stype = ZE_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC;
    host_desc.pNext = nullptr;
    host_desc.flags = 0;

    size_t buffer_size = 1024;
    void *host_mem_ptr = nullptr;
    status = zeMemAllocHost(context, &host_desc, buffer_size, 1, &host_mem_ptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    ze_device_mem_alloc_desc_t device_desc = {};
    device_desc.stype = ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC;
    device_desc.pNext = nullptr;
    // device_desc.ordinal = 0;
    device_desc.flags = 0;

    void *device_mem_ptr = nullptr;
    status = zeMemAllocDevice(context, &device_desc, buffer_size, 0, pDevice, &device_mem_ptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    // Action_0: Host to Device, is dependent on a future action called Action_2 (see below).
    status = zeCommandListAppendMemoryCopy(command_list, device_mem_ptr, host_mem_ptr, buffer_size, event[0], 1 /* 1 */, &event[2] /* &start_event */);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    // Action_1: Host to Device, is dependent on Action_0
    status = zeCommandListAppendMemoryCopy(command_list, device_mem_ptr, host_mem_ptr, buffer_size, event[1], 1, &event[0]);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    std::stringstream capture;
    std::streambuf *old_buf;

    old_buf = std::cerr.rdbuf();
    std::cerr.rdbuf(capture.rdbuf());

    // Action_2: Host to Device, is dependent on Action_1. It also creates a deadlock by having Action_0 dependent on it.
    status = zeCommandListAppendMemoryCopy(command_list, device_mem_ptr, host_mem_ptr, buffer_size, event[2], 1, &event[1]);
    std::cerr.rdbuf(old_buf);

    auto found = capture.str().find("Warning: There may be a potential event deadlock");
    EXPECT_NE(found, std::string::npos);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeCommandListClose(command_list);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    ze_command_queue_desc_t command_queue_description{};
    command_queue_description.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC;
    command_queue_description.pNext = nullptr;
    // command_queue_description.ordinal = 0;
    // command_queue_description.index = 0;
    command_queue_description.mode = ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;

    ze_command_queue_handle_t command_queue{};
    status = zeCommandQueueCreate(context, pDevice, &command_queue_description, &command_queue);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeCommandQueueExecuteCommandLists(command_queue, 1, &command_list, nullptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeCommandQueueSynchronize(command_queue, UINT64_MAX);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeCommandQueueDestroy(command_queue);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeMemFree(context, host_mem_ptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);
    status = zeMemFree(context, device_mem_ptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeEventDestroy(event[0]);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);
    status = zeEventDestroy(event[1]);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);
    status = zeEventDestroy(event[2]);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeEventPoolDestroy(event_pool);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeCommandListDestroy(command_list);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeContextDestroy(context);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);
}

TEST(
    LoaderValidation,
    GivenLevelZeroLoaderPresentWhenCallingzeCommandListAppendMemoryCopyWithCircularDependencyOnEventsAndExplicitCallzeEventHostSignalThenValidationLayerPrintsWarningOfIllegalUsage) {

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_TYPE=GPU"));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_GPU_ONLY));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    ze_result_t status;
    const ze_device_type_t type = ZE_DEVICE_TYPE_GPU;

    ze_driver_handle_t pDriver = nullptr;
    ze_device_handle_t pDevice = nullptr;

    uint32_t driverCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, nullptr));

    std::vector<ze_driver_handle_t> drivers(driverCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, drivers.data()));

    for (uint32_t driver = 0; driver < driverCount; ++driver) {
        pDriver = drivers[driver];

        // get all devices
        uint32_t deviceCount = 0;
        EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(pDriver, &deviceCount, nullptr));

        std::vector<ze_device_handle_t> devices(deviceCount);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(pDriver, &deviceCount, devices.data()));

        // for each device, find the first one matching the type
        for (uint32_t device = 0; device < deviceCount; ++device) {
            auto phDevice = devices[device];

            ze_device_properties_t device_properties = {};
            device_properties.stype = ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES;
            EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGetProperties(phDevice, &device_properties));

            if (type == device_properties.type) {
                pDevice = phDevice;
                break;
            }
        }

        if (pDevice) {
            break;
        }
    }
    EXPECT_NE(pDevice, nullptr);

    ze_context_handle_t context;
    ze_context_desc_t context_desc = {};
    context_desc.stype = ZE_STRUCTURE_TYPE_CONTEXT_DESC;

    status = zeContextCreate(pDriver, &context_desc, &context);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    // Create an  command list for direct submission
    ze_command_list_desc_t altdesc = {};
    altdesc.stype = ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC;

    ze_command_list_handle_t command_list = {};
    status = zeCommandListCreate(context, pDevice, &altdesc, &command_list);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    // Create an event to be signaled by the device
    ze_event_pool_desc_t ep_desc = {};
    ep_desc.stype = ZE_STRUCTURE_TYPE_EVENT_POOL_DESC;
    ep_desc.count = 3;
    ep_desc.flags = ZE_EVENT_POOL_FLAG_HOST_VISIBLE;

    ze_event_pool_handle_t event_pool;

    status = zeEventPoolCreate(context, &ep_desc, 1, &pDevice, &event_pool);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    std::vector<ze_event_handle_t> event{};
    // Three events for memcpy that will form a circular dependency.
    event.resize(3);

    ze_event_desc_t ev_desc = {};
    ev_desc.stype = ZE_STRUCTURE_TYPE_EVENT_DESC;
    ev_desc.signal = ZE_EVENT_SCOPE_FLAG_DEVICE;
    ev_desc.wait = ZE_EVENT_SCOPE_FLAG_HOST;

    for (uint32_t i = 0; i < 3; ++i) {
        ev_desc.index = i;
        status = zeEventCreate(event_pool, &ev_desc, &event[i]);
        EXPECT_EQ(ZE_RESULT_SUCCESS, status);
    }

    ze_host_mem_alloc_desc_t host_desc = {};
    host_desc.stype = ZE_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC;
    host_desc.pNext = nullptr;
    host_desc.flags = 0;

    size_t buffer_size = 1024;
    void *host_mem_ptr = nullptr;
    status = zeMemAllocHost(context, &host_desc, buffer_size, 1, &host_mem_ptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    ze_device_mem_alloc_desc_t device_desc = {};
    device_desc.stype = ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC;
    device_desc.pNext = nullptr;
    // device_desc.ordinal = 0;
    device_desc.flags = 0;

    void *device_mem_ptr = nullptr;
    status = zeMemAllocDevice(context, &device_desc, buffer_size, 0, pDevice, &device_mem_ptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    // Action_0: Host to Device, is dependent on a future action called Action_2 (see below).
    status = zeCommandListAppendMemoryCopy(command_list, device_mem_ptr, host_mem_ptr, buffer_size, event[0], 1 /* 1 */, &event[2] /* &start_event */);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    // Action_1: Host to Device, is dependent on Action_0
    status = zeCommandListAppendMemoryCopy(command_list, device_mem_ptr, host_mem_ptr, buffer_size, event[1], 1, &event[0]);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    std::stringstream capture;
    std::streambuf *old_cerr_buf = std::cerr.rdbuf();
    std::streambuf *old_cout_buf = std::cout.rdbuf();
    std::cerr.rdbuf(capture.rdbuf());
    std::cout.rdbuf(capture.rdbuf());

    // Action_2: Host to Device, is dependent on Action_1. It also creates a deadlock by having Action_0 dependent on it.
    status = zeCommandListAppendMemoryCopy(command_list, device_mem_ptr, host_mem_ptr, buffer_size, event[2], 1, &event[1]);

    std::cerr.rdbuf(old_cerr_buf);
    std::cout.rdbuf(old_cout_buf);

    auto found = capture.str().find("Warning: There may be a potential event deadlock");
    EXPECT_NE(found, std::string::npos);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeCommandListClose(command_list);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    ze_command_queue_desc_t command_queue_description{};
    command_queue_description.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC;
    command_queue_description.pNext = nullptr;
    // command_queue_description.ordinal = 0;
    // command_queue_description.index = 0;
    command_queue_description.mode = ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;

    ze_command_queue_handle_t command_queue{};
    status = zeCommandQueueCreate(context, pDevice, &command_queue_description, &command_queue);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    // clear the capture stringstream for reuse
    capture.str("");
    capture.clear();

    old_cerr_buf = std::cerr.rdbuf();
    old_cout_buf = std::cout.rdbuf();
    std::cerr.rdbuf(capture.rdbuf());
    std::cout.rdbuf(capture.rdbuf());

    // Explicitly break the dependency by signaling the last event.
    status = zeEventHostSignal(event[2]);
    std::cerr.rdbuf(old_cerr_buf);
    std::cout.rdbuf(old_cout_buf);

    found = capture.str().find("Warning: zeEventHostSignal is using the same ze_event_handle_t");
    EXPECT_NE(found, std::string::npos);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeCommandQueueExecuteCommandLists(command_queue, 1, &command_list, nullptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeCommandQueueSynchronize(command_queue, UINT64_MAX);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeCommandQueueDestroy(command_queue);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeMemFree(context, host_mem_ptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);
    status = zeMemFree(context, device_mem_ptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeEventDestroy(event[0]);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);
    status = zeEventDestroy(event[1]);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);
    status = zeEventDestroy(event[2]);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeEventPoolDestroy(event_pool);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeCommandListDestroy(command_list);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeContextDestroy(context);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);
}

TEST(
    LoaderValidation,
    GivenLevelZeroLoaderPresentWhenCallingzeEventHostResetWithAlreadySignaledEventThenUsingEventAgainThenValidationLayerDoesNotPrintsWarningOfIllegalUsage) {

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_TYPE=GPU"));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_GPU_ONLY));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    ze_result_t status;
    const ze_device_type_t type = ZE_DEVICE_TYPE_GPU;

    ze_driver_handle_t pDriver = nullptr;
    ze_device_handle_t pDevice = nullptr;

    uint32_t driverCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, nullptr));

    std::vector<ze_driver_handle_t> drivers(driverCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, drivers.data()));

    for (uint32_t driver = 0; driver < driverCount; ++driver) {
        pDriver = drivers[driver];

        // get all devices
        uint32_t deviceCount = 0;
        EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(pDriver, &deviceCount, nullptr));

        std::vector<ze_device_handle_t> devices(deviceCount);
        EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(pDriver, &deviceCount, devices.data()));

        // for each device, find the first one matching the type
        for (uint32_t device = 0; device < deviceCount; ++device) {
            auto phDevice = devices[device];

            ze_device_properties_t device_properties = {};
            device_properties.stype = ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES;
            EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGetProperties(phDevice, &device_properties));

            if (type == device_properties.type) {
                pDevice = phDevice;
                break;
            }
        }

        if (pDevice) {
            break;
        }
    }
    EXPECT_NE(pDevice, nullptr);

    ze_context_handle_t context;
    ze_context_desc_t context_desc = {};
    context_desc.stype = ZE_STRUCTURE_TYPE_CONTEXT_DESC;

    status = zeContextCreate(pDriver, &context_desc, &context);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    // Create an  command list for direct submission
    ze_command_list_desc_t altdesc = {};
    altdesc.stype = ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC;

    ze_command_list_handle_t command_list = {};
    status = zeCommandListCreate(context, pDevice, &altdesc, &command_list);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    // Create an event to be signaled by the device
    ze_event_pool_desc_t ep_desc = {};
    ep_desc.stype = ZE_STRUCTURE_TYPE_EVENT_POOL_DESC;
    ep_desc.count = 1;
    ep_desc.flags = ZE_EVENT_POOL_FLAG_HOST_VISIBLE;

    ze_event_pool_handle_t event_pool;

    status = zeEventPoolCreate(context, &ep_desc, 1, &pDevice, &event_pool);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    std::vector<ze_event_handle_t> event{};
    // event for memcpy.
    event.resize(1);

    ze_event_desc_t ev_desc = {};
    ev_desc.stype = ZE_STRUCTURE_TYPE_EVENT_DESC;
    ev_desc.signal = ZE_EVENT_SCOPE_FLAG_DEVICE;
    ev_desc.wait = ZE_EVENT_SCOPE_FLAG_HOST;

    for (uint32_t i = 0; i < 1; ++i) {
        ev_desc.index = i;
        status = zeEventCreate(event_pool, &ev_desc, &event[i]);
        EXPECT_EQ(ZE_RESULT_SUCCESS, status);
    }

    ze_host_mem_alloc_desc_t host_desc = {};
    host_desc.stype = ZE_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC;
    host_desc.pNext = nullptr;
    host_desc.flags = 0;

    size_t buffer_size = 1024;
    void *host_mem_ptr = nullptr;
    status = zeMemAllocHost(context, &host_desc, buffer_size, 1, &host_mem_ptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    ze_device_mem_alloc_desc_t device_desc = {};
    device_desc.stype = ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC;
    device_desc.pNext = nullptr;
    // device_desc.ordinal = 0;
    device_desc.flags = 0;

    void *device_mem_ptr = nullptr;
    status = zeMemAllocDevice(context, &device_desc, buffer_size, 0, pDevice, &device_mem_ptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    // Host to Device, signals event[0] and is dependent on nothing.
    status = zeCommandListAppendMemoryCopy(command_list, device_mem_ptr, host_mem_ptr, buffer_size, event[0], 0, nullptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeCommandListClose(command_list);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    ze_command_queue_desc_t command_queue_description{};
    command_queue_description.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC;
    command_queue_description.pNext = nullptr;
    // command_queue_description.ordinal = 0;
    // command_queue_description.index = 0;
    command_queue_description.mode = ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;

    ze_command_queue_handle_t command_queue{};
    status = zeCommandQueueCreate(context, pDevice, &command_queue_description, &command_queue);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeCommandQueueExecuteCommandLists(command_queue, 1, &command_list, nullptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeCommandQueueSynchronize(command_queue, UINT64_MAX);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    // Explicitly reset the event to be used again.
    status = zeEventHostReset(event[0]);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    std::stringstream capture;
    std::streambuf *old_cerr_buf = std::cerr.rdbuf();
    std::streambuf *old_cout_buf = std::cout.rdbuf();
    std::cerr.rdbuf(capture.rdbuf());
    std::cout.rdbuf(capture.rdbuf());

    // Host to Device, signals event[0] and is dependent on nothing.
    status = zeCommandListAppendMemoryCopy(command_list, device_mem_ptr, host_mem_ptr, buffer_size, event[0], 0, nullptr);
    std::cerr.rdbuf(old_cerr_buf);
    std::cout.rdbuf(old_cout_buf);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    auto warningText = capture.str();
    EXPECT_EQ(warningText, "");

    status = zeCommandQueueDestroy(command_queue);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeMemFree(context, host_mem_ptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);
    status = zeMemFree(context, device_mem_ptr);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeEventDestroy(event[0]);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeEventPoolDestroy(event_pool);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeCommandListDestroy(command_list);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);

    status = zeContextDestroy(context);
    EXPECT_EQ(ZE_RESULT_SUCCESS, status);
}

  TEST(
      RuntimeApiParameterValidation,
      GivenLevelZeroLoaderPresentWhenCallingZerApiWithParameterValidationEnabledThenExpectValidationsAreTriggered)
  {
    uint32_t pInitDriversCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;
    putenv_safe(const_cast<char *>("ZE_ENABLE_LOADER_INTERCEPT=1"));
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0"));
    std::vector<ze_driver_handle_t> drivers;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
    drivers.resize(pInitDriversCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
    EXPECT_GT(pInitDriversCount, 0);

    ze_result_t result = zerGetLastErrorDescription(nullptr);
    EXPECT_EQ(ZE_RESULT_ERROR_INVALID_NULL_POINTER, result);
  }

///////////////////////////////////////////////////////////////////////////////
// API Call Tracing Tests
//
// These tests validate that API call tracing in the validation layer works
// correctly on both Linux and Windows without crashing. They test:
// 1. Basic API calls with single output parameters  
// 2. APIs with multiple output parameters
// 3. Event creation and management
// 4. Memory allocation APIs  
// 5. Immediate command lists
// 6. Command queues with integer output parameters
//
// The tests ensure that when trace-level logging is enabled, the validation
// layer can properly dereference and log output parameter values without
// causing segfaults or other crashes. This validates the dereferencing logic
// added to logAndPropagateResult functions.
//
// Note: These tests require the null driver to be built and available.
///////////////////////////////////////////////////////////////////////////////

TEST(
    ValidationLayerApiTracing,
    GivenValidationLayerEnabledWithTraceLevelLoggingWhenCallingBasicApisThenTracingDoesNotCrash) {

    // Enable validation layer and trace level logging
    putenv_safe(const_cast<char *>("ZE_ENABLE_VALIDATION_LAYER=1"));
    putenv_safe(const_cast<char *>("ZEL_ENABLE_LOADER_LOGGING=1"));
    putenv_safe(const_cast<char *>("ZEL_LOADER_LOGGING_LEVEL=trace"));
    putenv_safe(const_cast<char *>("ZE_ENABLE_NULL_DRIVER=1"));
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_TYPE=GPU"));

    // Initialize Level Zero
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_GPU_ONLY));
    
    uint32_t pInitDriversCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
    EXPECT_GT(pInitDriversCount, 0);

    // Get driver
    uint32_t driverCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, nullptr));
    EXPECT_GT(driverCount, 0);

    std::vector<ze_driver_handle_t> drivers(driverCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, drivers.data()));

    // Get device
    uint32_t deviceCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
    EXPECT_GT(deviceCount, 0);

    std::vector<ze_device_handle_t> devices(deviceCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));

    // Create context
    ze_context_desc_t context_desc = {};
    context_desc.stype = ZE_STRUCTURE_TYPE_CONTEXT_DESC;
    ze_context_handle_t context = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &context_desc, &context));
    EXPECT_NE(context, nullptr);

    // Create command list - this will trigger trace logging with output parameters
    ze_command_list_desc_t cmdlist_desc = {};
    cmdlist_desc.stype = ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC;
    ze_command_list_handle_t commandList = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListCreate(context, devices[0], &cmdlist_desc, &commandList));
    EXPECT_NE(commandList, nullptr);

    // Cleanup
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListDestroy(commandList));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));
}

TEST(
    ValidationLayerApiTracing,
    GivenValidationLayerEnabledWithTraceLevelLoggingWhenCallingApiWithMultipleOutputParametersThenTracingDoesNotCrash) {

    // Enable validation layer and trace level logging
    putenv_safe(const_cast<char *>("ZE_ENABLE_VALIDATION_LAYER=1"));
    putenv_safe(const_cast<char *>("ZEL_ENABLE_LOADER_LOGGING=1"));
    putenv_safe(const_cast<char *>("ZEL_LOADER_LOGGING_LEVEL=trace"));
    putenv_safe(const_cast<char *>("ZE_ENABLE_NULL_DRIVER=1"));
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_TYPE=GPU"));

    // Initialize
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_GPU_ONLY));
    
    uint32_t pInitDriversCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
    EXPECT_GT(pInitDriversCount, 0);

    uint32_t driverCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, nullptr));
    EXPECT_GT(driverCount, 0);

    std::vector<ze_driver_handle_t> drivers(driverCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, drivers.data()));

    uint32_t deviceCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
    EXPECT_GT(deviceCount, 0);

    std::vector<ze_device_handle_t> devices(deviceCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));

    // Test API with multiple output parameters
    uint64_t hostTimestamp = 0;
    uint64_t deviceTimestamp = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGetGlobalTimestamps(devices[0], &hostTimestamp, &deviceTimestamp));

    // Get device properties - tests struct output parameters
    ze_device_properties_t deviceProperties = {};
    deviceProperties.stype = ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGetProperties(devices[0], &deviceProperties));
}

TEST(
    ValidationLayerApiTracing,
    GivenValidationLayerEnabledWithTraceLevelLoggingWhenCallingEventApisThenTracingDoesNotCrash) {

    // Enable validation layer and trace level logging
    putenv_safe(const_cast<char *>("ZE_ENABLE_VALIDATION_LAYER=1"));
    putenv_safe(const_cast<char *>("ZEL_ENABLE_LOADER_LOGGING=1"));
    putenv_safe(const_cast<char *>("ZEL_LOADER_LOGGING_LEVEL=trace"));
    putenv_safe(const_cast<char *>("ZE_ENABLE_NULL_DRIVER=1"));
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_TYPE=GPU"));

    // Initialize
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_GPU_ONLY));
    
    uint32_t pInitDriversCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
    EXPECT_GT(pInitDriversCount, 0);

    uint32_t driverCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, nullptr));
    EXPECT_GT(driverCount, 0);

    std::vector<ze_driver_handle_t> drivers(driverCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, drivers.data()));

    uint32_t deviceCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
    EXPECT_GT(deviceCount, 0);

    std::vector<ze_device_handle_t> devices(deviceCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));

    // Create context
    ze_context_desc_t context_desc = {};
    context_desc.stype = ZE_STRUCTURE_TYPE_CONTEXT_DESC;
    ze_context_handle_t context = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &context_desc, &context));

    // Create event pool
    ze_event_pool_desc_t ep_desc = {};
    ep_desc.stype = ZE_STRUCTURE_TYPE_EVENT_POOL_DESC;
    ep_desc.count = 1;
    ep_desc.flags = ZE_EVENT_POOL_FLAG_HOST_VISIBLE;
    ze_event_pool_handle_t event_pool = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventPoolCreate(context, &ep_desc, 1, &devices[0], &event_pool));
    EXPECT_NE(event_pool, nullptr);

    // Create event - tests handle creation tracing
    ze_event_desc_t ev_desc = {};
    ev_desc.stype = ZE_STRUCTURE_TYPE_EVENT_DESC;
    ev_desc.index = 0;
    ev_desc.signal = ZE_EVENT_SCOPE_FLAG_DEVICE;
    ev_desc.wait = ZE_EVENT_SCOPE_FLAG_HOST;
    ze_event_handle_t event = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventCreate(event_pool, &ev_desc, &event));
    EXPECT_NE(event, nullptr);

    // Cleanup
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventDestroy(event));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventPoolDestroy(event_pool));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));
}

TEST(
    ValidationLayerApiTracing,
    GivenValidationLayerEnabledWithTraceLevelLoggingWhenCallingMemoryApisThenTracingDoesNotCrash) {

    // Enable validation layer and trace level logging
    putenv_safe(const_cast<char *>("ZE_ENABLE_VALIDATION_LAYER=1"));
    putenv_safe(const_cast<char *>("ZEL_ENABLE_LOADER_LOGGING=1"));
    putenv_safe(const_cast<char *>("ZEL_LOADER_LOGGING_LEVEL=trace"));
    putenv_safe(const_cast<char *>("ZE_ENABLE_NULL_DRIVER=1"));
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_TYPE=GPU"));

    // Initialize
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_GPU_ONLY));
    
    uint32_t pInitDriversCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
    EXPECT_GT(pInitDriversCount, 0);

    uint32_t driverCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, nullptr));
    EXPECT_GT(driverCount, 0);

    std::vector<ze_driver_handle_t> drivers(driverCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, drivers.data()));

    uint32_t deviceCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
    EXPECT_GT(deviceCount, 0);

    std::vector<ze_device_handle_t> devices(deviceCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));

    // Create context
    ze_context_desc_t context_desc = {};
    context_desc.stype = ZE_STRUCTURE_TYPE_CONTEXT_DESC;
    ze_context_handle_t context = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &context_desc, &context));

    // Allocate host memory - tests pointer output parameters
    ze_host_mem_alloc_desc_t host_desc = {};
    host_desc.stype = ZE_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC;
    void *host_mem = nullptr;
    size_t size = 1024;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeMemAllocHost(context, &host_desc, size, 1, &host_mem));
    EXPECT_NE(host_mem, nullptr);

    // Allocate device memory
    ze_device_mem_alloc_desc_t device_desc = {};
    device_desc.stype = ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC;
    void *device_mem = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeMemAllocDevice(context, &device_desc, size, 0, devices[0], &device_mem));
    EXPECT_NE(device_mem, nullptr);

    // Cleanup
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeMemFree(context, host_mem));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeMemFree(context, device_mem));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));
}

TEST(
    ValidationLayerApiTracing,
    GivenValidationLayerEnabledWithTraceLevelLoggingWhenCallingImmediateCommandListApisThenTracingDoesNotCrash) {

    // Enable validation layer and trace level logging
    putenv_safe(const_cast<char *>("ZE_ENABLE_VALIDATION_LAYER=1"));
    putenv_safe(const_cast<char *>("ZEL_ENABLE_LOADER_LOGGING=1"));
    putenv_safe(const_cast<char *>("ZEL_LOADER_LOGGING_LEVEL=trace"));
    putenv_safe(const_cast<char *>("ZE_ENABLE_NULL_DRIVER=1"));
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_TYPE=GPU"));

    // Initialize
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_GPU_ONLY));
    
    uint32_t pInitDriversCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
    EXPECT_GT(pInitDriversCount, 0);

    uint32_t driverCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, nullptr));
    EXPECT_GT(driverCount, 0);

    std::vector<ze_driver_handle_t> drivers(driverCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, drivers.data()));

    uint32_t deviceCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
    EXPECT_GT(deviceCount, 0);

    std::vector<ze_device_handle_t> devices(deviceCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));

    // Create context
    ze_context_desc_t context_desc = {};
    context_desc.stype = ZE_STRUCTURE_TYPE_CONTEXT_DESC;
    ze_context_handle_t context = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &context_desc, &context));

    // Create immediate command list - tests immediate command list handle tracing
    ze_command_queue_desc_t cmdqueue_desc = {};
    cmdqueue_desc.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC;
    ze_command_list_handle_t immediateCommandList = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListCreateImmediate(context, devices[0], &cmdqueue_desc, &immediateCommandList));
    EXPECT_NE(immediateCommandList, nullptr);

    // Test if command list is immediate
    ze_bool_t isImmediate = false;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListIsImmediate(immediateCommandList, &isImmediate));

    // Cleanup
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListDestroy(immediateCommandList));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));
}

TEST(
    ValidationLayerApiTracing,
    GivenValidationLayerEnabledWithTraceLevelLoggingWhenCallingCommandQueueApisThenTracingDoesNotCrash) {

    // Enable validation layer and trace level logging
    putenv_safe(const_cast<char *>("ZE_ENABLE_VALIDATION_LAYER=1"));
    putenv_safe(const_cast<char *>("ZEL_ENABLE_LOADER_LOGGING=1"));
    putenv_safe(const_cast<char *>("ZEL_LOADER_LOGGING_LEVEL=trace"));
    putenv_safe(const_cast<char *>("ZE_ENABLE_NULL_DRIVER=1"));
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_TYPE=GPU"));

    // Initialize
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_GPU_ONLY));
    
    uint32_t pInitDriversCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
    EXPECT_GT(pInitDriversCount, 0);

    uint32_t driverCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, nullptr));
    EXPECT_GT(driverCount, 0);

    std::vector<ze_driver_handle_t> drivers(driverCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, drivers.data()));

    uint32_t deviceCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
    EXPECT_GT(deviceCount, 0);

    std::vector<ze_device_handle_t> devices(deviceCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));

    // Create context
    ze_context_desc_t context_desc = {};
    context_desc.stype = ZE_STRUCTURE_TYPE_CONTEXT_DESC;
    ze_context_handle_t context = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &context_desc, &context));

    // Create command queue - tests queue handle tracing
    ze_command_queue_desc_t cmdqueue_desc = {};
    cmdqueue_desc.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC;
    cmdqueue_desc.mode = ZE_COMMAND_QUEUE_MODE_ASYNCHRONOUS;
    ze_command_queue_handle_t commandQueue = nullptr;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueCreate(context, devices[0], &cmdqueue_desc, &commandQueue));
    EXPECT_NE(commandQueue, nullptr);

    // Get queue ordinal and index - tests integer output parameters
    uint32_t ordinal = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueGetOrdinal(commandQueue, &ordinal));

    uint32_t index = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueGetIndex(commandQueue, &index));

    // Cleanup
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueDestroy(commandQueue));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));
}

///////////////////////////////////////////////////////////////////////////////
// Handle Lifetime Tests
//
// These tests validate the ZE_ENABLE_HANDLE_LIFETIME feature of the validation
// layer. Handle lifetime tracking registers handles when they are created and
// validates them on every subsequent API call, returning
// ZE_RESULT_ERROR_INVALID_NULL_HANDLE for any unregistered handle.
//
// The tests are run as separate CTest invocations with the environment:
//   ZE_ENABLE_VALIDATION_LAYER=1
//   ZE_ENABLE_HANDLE_LIFETIME=1
//   ZE_ENABLE_NULL_DRIVER=1

// Regression test: driver handles obtained via zeInitDrivers must be registered
// in the handle lifetime tracker so that subsequent API calls succeed.
// Before the fix, zeInitDrivers had no handle-registration epilogue (unlike
// zeDriverGet), causing zeDeviceGet to return ZE_RESULT_ERROR_INVALID_NULL_HANDLE.
TEST(
    HandleLifetimeValidation,
    GivenHandleLifetimeEnabledWhenCallingzeDeviceGetWithDriverHandleFromzeInitDriversThenSucceeds) {

    ze_init_driver_type_desc_t driverTypeDesc = {};
    driverTypeDesc.stype = ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC;
    driverTypeDesc.pNext = nullptr;
    driverTypeDesc.flags = UINT32_MAX;

    uint32_t count = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&count, nullptr, &driverTypeDesc));
    EXPECT_GT(count, 0);

    std::vector<ze_driver_handle_t> drivers(count);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&count, drivers.data(), &driverTypeDesc));

    // Regression: driver handles from zeInitDrivers must be registered with the
    // handle lifetime tracker so that zeDeviceGet does not fail with
    // ZE_RESULT_ERROR_INVALID_NULL_HANDLE.
    uint32_t deviceCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
    EXPECT_GT(deviceCount, 0);

    std::vector<ze_device_handle_t> devices(deviceCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
}

// Verify that driver handles obtained via zeDriverGet are registered correctly
// and can be used with zeDeviceGet when handle lifetime tracking is enabled.
TEST(
    HandleLifetimeValidation,
    GivenHandleLifetimeEnabledWhenCallingzeDeviceGetWithDriverHandleFromzeDriverGetThenSucceeds) {

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_GPU_ONLY));

    uint32_t driverCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, nullptr));
    EXPECT_GT(driverCount, 0);

    std::vector<ze_driver_handle_t> drivers(driverCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverCount, drivers.data()));

    uint32_t deviceCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
    EXPECT_GT(deviceCount, 0);

    std::vector<ze_device_handle_t> devices(deviceCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
}

// Verify that calling an API with a null (unregistered) handle returns
// ZE_RESULT_ERROR_INVALID_NULL_HANDLE when handle lifetime tracking is enabled.
TEST(
    HandleLifetimeValidation,
    GivenHandleLifetimeEnabledWhenCallingzeDeviceGetWithNullDriverHandleThenReturnsInvalidHandle) {

    ze_init_driver_type_desc_t driverTypeDesc = {};
    driverTypeDesc.stype = ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC;
    driverTypeDesc.pNext = nullptr;
    driverTypeDesc.flags = UINT32_MAX;

    uint32_t count = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&count, nullptr, &driverTypeDesc));

    // A null handle is never registered; the handle lifetime checker must reject it.
    uint32_t deviceCount = 0;
    EXPECT_EQ(ZE_RESULT_ERROR_INVALID_NULL_HANDLE, zeDeviceGet(nullptr, &deviceCount, nullptr));
}

namespace {

// Reads the JSON Lines stream written by the fabric topology checker for this process.
std::vector<std::string> readFabricTopologyLog() {
    const char *dir = getenv("ZEL_FABRIC_TOPOLOGY_OUTPUT");
    if (dir == nullptr)
        return {};
#if defined(_WIN32)
    char host[MAX_COMPUTERNAME_LENGTH + 1] = {};
    DWORD hostLen = sizeof(host);
    GetComputerNameA(host, &hostLen);
    unsigned long pid = GetCurrentProcessId();
#else
    char host[256] = {};
    gethostname(host, sizeof(host) - 1);
    unsigned long pid = static_cast<unsigned long>(getpid());
#endif
    std::string path = std::string(dir) + "/fabric_topology_" + host + "_" + std::to_string(pid) + ".jsonl";
    std::ifstream in(path);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line))
        lines.push_back(line);
    return lines;
}

size_t countLinesContaining(const std::vector<std::string> &lines, const std::string &a, const std::string &b = "") {
    size_t n = 0;
    for (const auto &l : lines)
        if (l.find(a) != std::string::npos && (b.empty() || l.find(b) != std::string::npos))
            ++n;
    return n;
}

// Returns the value of a string field ("key":"value") from a JSON line.
std::string jsonStringField(const std::string &line, const std::string &key) {
    std::string tag = "\"" + key + "\":\"";
    auto start = line.find(tag);
    if (start == std::string::npos)
        return "";
    start += tag.size();
    auto end = line.find('"', start);
    return end == std::string::npos ? "" : line.substr(start, end - start);
}

} // namespace

// The checker runs with ZEL_FABRIC_TOPOLOGY_INTERVAL_MS=0 so every submission is
// written (and flushed) as its own traffic record.
TEST(
    FabricTopologyChecker,
    GivenFabricTopologyCheckerEnabledWhenCopiesFillsAndIpcAreUsedThenTrafficIsAttributedToMemoryLocations) {

    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_TYPE=GPU"));
    ASSERT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_GPU_ONLY));
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    uint32_t driverCount = 0;
    ASSERT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&driverCount, nullptr, &desc));
    ASSERT_GT(driverCount, 0u);
    // The topology is populated as soon as the loader completes zeInitDrivers,
    // even when the application only asked for the driver count.
    EXPECT_GE(countLinesContaining(readFabricTopologyLog(), "\"type\":\"topology\""), 1u);
    EXPECT_GE(countLinesContaining(readFabricTopologyLog(), "\"fabric_query\":{"), 1u);
    std::vector<ze_driver_handle_t> drivers(driverCount);
    ASSERT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&driverCount, drivers.data(), &desc));

    // Use the null driver's device so the result does not depend on installed hardware.
    ze_driver_handle_t hDriver = nullptr;
    ze_device_handle_t hDevice = nullptr;
    ze_device_properties_t deviceProps = {ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES};
    for (auto driver : drivers) {
        uint32_t deviceCount = 0;
        ASSERT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(driver, &deviceCount, nullptr));
        std::vector<ze_device_handle_t> devices(deviceCount);
        ASSERT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(driver, &deviceCount, devices.data()));
        for (auto device : devices) {
            ze_device_properties_t props = {ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES};
            ASSERT_EQ(ZE_RESULT_SUCCESS, zeDeviceGetProperties(device, &props));
            if (hDevice == nullptr || strcmp(props.name, "Null Device") == 0) {
                hDriver = driver;
                hDevice = device;
                deviceProps = props;
            }
        }
    }
    ASSERT_NE(nullptr, hDevice);
    static const char digits[] = "0123456789abcdef";
    std::string dev = "dev:";
    for (uint32_t i = 0; i < ZE_MAX_DEVICE_UUID_SIZE; ++i) {
        dev += digits[deviceProps.uuid.id[i] >> 4];
        dev += digits[deviceProps.uuid.id[i] & 0xf];
    }

    ze_context_handle_t hContext = nullptr;
    ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
    ASSERT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(hDriver, &contextDesc, &hContext));

    void *hostBuf = nullptr;
    void *devBuf = nullptr;
    ze_host_mem_alloc_desc_t hostDesc = {ZE_STRUCTURE_TYPE_HOST_MEM_ALLOC_DESC};
    ze_device_mem_alloc_desc_t devDesc = {ZE_STRUCTURE_TYPE_DEVICE_MEM_ALLOC_DESC};
    ASSERT_EQ(ZE_RESULT_SUCCESS, zeMemAllocHost(hContext, &hostDesc, 4096, 64, &hostBuf));
    ASSERT_EQ(ZE_RESULT_SUCCESS, zeMemAllocDevice(hContext, &devDesc, 4096, 64, hDevice, &devBuf));

    // Immediate command list: accounted at append time.
    ze_command_list_handle_t hImmediate = nullptr;
    ze_command_queue_desc_t queueDesc = {ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC};
    ASSERT_EQ(ZE_RESULT_SUCCESS, zeCommandListCreateImmediate(hContext, hDevice, &queueDesc, &hImmediate));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListAppendMemoryCopy(hImmediate, devBuf, hostBuf, 4096, nullptr, 0, nullptr));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListAppendMemoryCopy(hImmediate, hostBuf, devBuf, 1024, nullptr, 0, nullptr));
    uint32_t pattern = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListAppendMemoryFill(hImmediate, devBuf, &pattern, sizeof(pattern), 256, nullptr, 0, nullptr));

    // Regular command list: accounted on every execution, not at append time.
    ze_command_list_handle_t hRegular = nullptr;
    ze_command_list_desc_t listDesc = {ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC};
    ASSERT_EQ(ZE_RESULT_SUCCESS, zeCommandListCreate(hContext, hDevice, &listDesc, &hRegular));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListAppendMemoryCopy(hRegular, devBuf, hostBuf, 512, nullptr, 0, nullptr));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListClose(hRegular));
    auto beforeExecute = readFabricTopologyLog();
    EXPECT_EQ(0u, countLinesContaining(beforeExecute, "\"bytes\":512,"));
    ze_command_queue_handle_t hQueue = nullptr;
    ASSERT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueCreate(hContext, hDevice, &queueDesc, &hQueue));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueExecuteCommandLists(hQueue, 1, &hRegular, nullptr));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueExecuteCommandLists(hQueue, 1, &hRegular, nullptr));

    // IPC: export the device buffer, then "import" it. The null driver does not
    // fill IPC outputs, so seed the handle and the imported pointer.
    ze_ipc_mem_handle_t ipcHandle;
    memset(ipcHandle.data, 0x5a, sizeof(ipcHandle.data));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeMemGetIpcHandle(hContext, devBuf, &ipcHandle));
    std::vector<char> importedStorage(4096);
    void *imported = importedStorage.data();
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeMemOpenIpcHandle(hContext, hDevice, ipcHandle, 0, &imported));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListAppendMemoryCopy(hImmediate, hostBuf, imported, 128, nullptr, 0, nullptr));

    auto lines = readFabricTopologyLog();
    ASSERT_FALSE(lines.empty()) << "no fabric topology output written";

    EXPECT_EQ(1u, countLinesContaining(lines, "\"type\":\"process_start\""));
    EXPECT_GE(countLinesContaining(lines, "\"type\":\"topology\"", "\"" + dev + "\""), 1u);
    EXPECT_EQ(1u, countLinesContaining(lines, "\"type\":\"device\"", "\"id\":\"" + dev + "\""));

    const std::string exec = "{\"exec\":\"" + dev + "\",";
    EXPECT_EQ(1u, countLinesContaining(lines, exec + "\"src\":\"host\",\"dst\":\"" + dev + "\",\"op\":\"copy\",\"bytes\":4096,\"ops\":1}"));
    EXPECT_EQ(1u, countLinesContaining(lines, exec + "\"src\":\"" + dev + "\",\"dst\":\"host\",\"op\":\"copy\",\"bytes\":1024,\"ops\":1}"));
    EXPECT_EQ(1u, countLinesContaining(lines, exec + "\"src\":null,\"dst\":\"" + dev + "\",\"op\":\"fill\",\"bytes\":256,\"ops\":1}"));
    // Two executions of the regular list => two traffic records of 512 bytes.
    EXPECT_EQ(2u, countLinesContaining(lines, exec + "\"src\":\"host\",\"dst\":\"" + dev + "\",\"op\":\"copy\",\"bytes\":512,\"ops\":1}"));

    // Export and import carry the same join key; traffic from the import is attributed to it.
    std::string exportHash, importHash, importLoc;
    for (const auto &l : lines) {
        if (l.find("\"type\":\"ipc_export\"") != std::string::npos) {
            exportHash = jsonStringField(l, "handle_hash");
            EXPECT_EQ(dev, jsonStringField(l, "loc"));
        }
        if (l.find("\"type\":\"ipc_import\"") != std::string::npos) {
            importHash = jsonStringField(l, "handle_hash");
            importLoc = jsonStringField(l, "loc");
        }
    }
    EXPECT_FALSE(exportHash.empty());
    EXPECT_EQ(exportHash, importHash);
    EXPECT_EQ("ipc:0", importLoc);
    EXPECT_EQ(1u, countLinesContaining(lines, exec + "\"src\":\"ipc:0\",\"dst\":\"host\",\"op\":\"copy\",\"bytes\":128,\"ops\":1}"));

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeMemCloseIpcHandle(hContext, imported));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueDestroy(hQueue));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListDestroy(hRegular));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListDestroy(hImmediate));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeMemFree(hContext, devBuf));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeMemFree(hContext, hostBuf));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(hContext));
    EXPECT_EQ(1u, countLinesContaining(readFabricTopologyLog(), "\"type\":\"ipc_close\""));
}
