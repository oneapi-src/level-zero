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

#if defined(_WIN32)
#define putenv_safe _putenv
#else
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
