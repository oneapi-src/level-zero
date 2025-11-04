/*
 * Copyright (C) 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */


#include "test/init_driver_unit_tests_common.h"


TEST_F(InitDriverUnitTest, zeInitDriversWithFakeIntelGPUAndNPU_InitGPUFirst) {
    // First, initialize GPU drivers using zeInitDrivers with GPU flag
    uint32_t driverCount = 0;
    ze_init_driver_type_desc_t descGPU = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    descGPU.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU;
    descGPU.pNext = nullptr;
    
    // Call zeInitDrivers to init GPU drivers
    ze_result_t result = zeInitDrivers(&driverCount, nullptr, &descGPU);
    EXPECT_EQ(result, ZE_RESULT_SUCCESS);
    
    if (driverCount > 0) {
        std::vector<ze_driver_handle_t> gpuDrivers(driverCount);
        result = zeInitDrivers(&driverCount, gpuDrivers.data(), &descGPU);
        EXPECT_EQ(result, ZE_RESULT_SUCCESS);
        
        // Make sure we can call into GPU drivers
        for (uint32_t i = 0; i < driverCount; i++) {
            EXPECT_NE(gpuDrivers[i], nullptr);
            
            // Try to get devices from this GPU driver
            uint32_t deviceCount = 0;
            ze_result_t devResult = zeDeviceGet(gpuDrivers[i], &deviceCount, nullptr);
            // Should succeed (even if 0 devices for null driver)
            EXPECT_EQ(devResult, ZE_RESULT_SUCCESS);
        }
        
        // Verify that GPU drivers were initialized in the context
        bool foundGPUDriver = false;
        for (const auto& driver : loader::context->zeDrivers) {
            if (driver.driverType == loader::ZEL_DRIVER_TYPE_DISCRETE_GPU ||
                driver.driverType == loader::ZEL_DRIVER_TYPE_GPU ||
                driver.driverType == loader::ZEL_DRIVER_TYPE_INTEGRATED_GPU) {
                foundGPUDriver = true;
                EXPECT_TRUE(driver.ddiInitialized);
                break;
            }
        }
        EXPECT_TRUE(foundGPUDriver);
    }
}

TEST_F(InitDriverUnitTest, zeInitDriversWithFakeIntelGPUAndNPU_InitNPUFirst) {
    // First, initialize NPU drivers using zeInitDrivers with NPU flag
    uint32_t driverCount = 0;
    ze_init_driver_type_desc_t descNPU = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    descNPU.flags = ZE_INIT_DRIVER_TYPE_FLAG_NPU;
    descNPU.pNext = nullptr;
    
    // Call zeInitDrivers to init NPU drivers
    ze_result_t result = zeInitDrivers(&driverCount, nullptr, &descNPU);
    EXPECT_EQ(result, ZE_RESULT_SUCCESS);
    
    if (driverCount > 0) {
        std::vector<ze_driver_handle_t> npuDrivers(driverCount);
        result = zeInitDrivers(&driverCount, npuDrivers.data(), &descNPU);
        EXPECT_EQ(result, ZE_RESULT_SUCCESS);
        
        // Make sure we can call into NPU drivers
        for (uint32_t i = 0; i < driverCount; i++) {
            EXPECT_NE(npuDrivers[i], nullptr);
            
            // Try to get devices from this NPU driver
            uint32_t deviceCount = 0;
            ze_result_t devResult = zeDeviceGet(npuDrivers[i], &deviceCount, nullptr);
            // Should succeed (even if 0 devices for null driver)
            EXPECT_EQ(devResult, ZE_RESULT_SUCCESS);
        }
        
        // Verify that NPU drivers were initialized in the context
        bool foundNPUDriver = false;
        for (const auto& driver : loader::context->zeDrivers) {
            printf("Driver Name: %s, Type: %u, DDI Initialized: %d\n", driver.name.c_str(), driver.driverType, driver.ddiInitialized);
            if (driver.driverType == loader::ZEL_DRIVER_TYPE_NPU) {
                foundNPUDriver = true;
                EXPECT_TRUE(driver.ddiInitialized);
                break;
            }
        }
        EXPECT_TRUE(foundNPUDriver);
    }
}

TEST_F(InitDriverUnitTest, zeInitDriversWithFakeIntelGPUAndNPU_InitGPUThenNPU) {
    // Step 1: Initialize GPU drivers first
    uint32_t gpuDriverCount = 0;
    ze_init_driver_type_desc_t descGPU = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    descGPU.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU;
    descGPU.pNext = nullptr;
    
    ze_result_t result = zeInitDrivers(&gpuDriverCount, nullptr, &descGPU);
    EXPECT_EQ(result, ZE_RESULT_SUCCESS);
    
    std::vector<ze_driver_handle_t> gpuDrivers(gpuDriverCount);
    if (gpuDriverCount > 0) {
        result = zeInitDrivers(&gpuDriverCount, gpuDrivers.data(), &descGPU);
        EXPECT_EQ(result, ZE_RESULT_SUCCESS);
        
        // Verify we can call GPU driver APIs
        for (uint32_t i = 0; i < gpuDriverCount; i++) {
            EXPECT_NE(gpuDrivers[i], nullptr);
            uint32_t deviceCount = 0;
            EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(gpuDrivers[i], &deviceCount, nullptr));
        }
    }
    
    // Step 2: Now initialize NPU drivers
    uint32_t npuDriverCount = 0;
    ze_init_driver_type_desc_t descNPU = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    descNPU.flags = ZE_INIT_DRIVER_TYPE_FLAG_NPU;
    descNPU.pNext = nullptr;
    
    result = zeInitDrivers(&npuDriverCount, nullptr, &descNPU);
    EXPECT_EQ(result, ZE_RESULT_SUCCESS);
    
    std::vector<ze_driver_handle_t> npuDrivers(npuDriverCount);
    if (npuDriverCount > 0) {
        result = zeInitDrivers(&npuDriverCount, npuDrivers.data(), &descNPU);
        EXPECT_EQ(result, ZE_RESULT_SUCCESS);
        
        // Verify we can call NPU driver APIs
        for (uint32_t i = 0; i < npuDriverCount; i++) {
            EXPECT_NE(npuDrivers[i], nullptr);
            uint32_t deviceCount = 0;
            EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(npuDrivers[i], &deviceCount, nullptr));
        }
    }
    
    // Step 3: Verify both GPU and NPU drivers still work
    // Ensure GPU drivers still respond to API calls
    for (uint32_t i = 0; i < gpuDriverCount; i++) {
        uint32_t deviceCount = 0;
        EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(gpuDrivers[i], &deviceCount, nullptr));
    }
    
    // Ensure NPU drivers respond to API calls
    for (uint32_t i = 0; i < npuDriverCount; i++) {
        uint32_t deviceCount = 0;
        EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(npuDrivers[i], &deviceCount, nullptr));
    }
}

TEST_F(InitDriverUnitTest, zeInitWithFakeIntelGPU_ThenzeInitDriversWithNPU) {
    // Step 1: Use zeInit to initialize (typically gets all drivers)
    ze_result_t result = zeInit(0);
    EXPECT_EQ(result, ZE_RESULT_SUCCESS);
    
    // Get GPU drivers using zeDriverGet
    uint32_t allDriverCount = 0;
    result = zeDriverGet(&allDriverCount, nullptr);
    EXPECT_EQ(result, ZE_RESULT_SUCCESS);
    
    std::vector<ze_driver_handle_t> allDrivers(allDriverCount);
    if (allDriverCount > 0) {
        result = zeDriverGet(&allDriverCount, allDrivers.data());
        EXPECT_EQ(result, ZE_RESULT_SUCCESS);
        
        // Try calling APIs on the drivers returned by zeDriverGet
        for (uint32_t i = 0; i < allDriverCount; i++) {
            EXPECT_NE(allDrivers[i], nullptr);
            uint32_t deviceCount = 0;
            EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(allDrivers[i], &deviceCount, nullptr));
        }
    }
    
    // Step 2: Now use zeInitDrivers to get NPU drivers specifically
    uint32_t npuDriverCount = 0;
    ze_init_driver_type_desc_t descNPU = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    descNPU.flags = ZE_INIT_DRIVER_TYPE_FLAG_NPU;
    descNPU.pNext = nullptr;
    
    result = zeInitDrivers(&npuDriverCount, nullptr, &descNPU);
    EXPECT_EQ(result, ZE_RESULT_SUCCESS);
    
    std::vector<ze_driver_handle_t> npuDrivers(npuDriverCount);
    if (npuDriverCount > 0) {
        result = zeInitDrivers(&npuDriverCount, npuDrivers.data(), &descNPU);
        EXPECT_EQ(result, ZE_RESULT_SUCCESS);
        
        // Verify we can call NPU driver APIs
        for (uint32_t i = 0; i < npuDriverCount; i++) {
            EXPECT_NE(npuDrivers[i], nullptr);
            uint32_t deviceCount = 0;
            EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(npuDrivers[i], &deviceCount, nullptr));
        }
    }
    
    // Step 3: Verify original drivers from zeDriverGet still work
    for (uint32_t i = 0; i < allDriverCount; i++) {
        uint32_t deviceCount = 0;
        EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(allDrivers[i], &deviceCount, nullptr));
    }
}

TEST_F(InitDriverUnitTest, zeInitDriversWithAllTypes_VerifyRoutingToCorrectDriver) {
    // Initialize all driver types
    uint32_t allDriverCount = 0;
    ze_init_driver_type_desc_t descAll = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    descAll.flags = UINT32_MAX; // All driver types
    descAll.pNext = nullptr;
    
    ze_result_t result = zeInitDrivers(&allDriverCount, nullptr, &descAll);
    EXPECT_EQ(result, ZE_RESULT_SUCCESS);
    
    std::vector<ze_driver_handle_t> allDrivers(allDriverCount);
    if (allDriverCount > 0) {
        result = zeInitDrivers(&allDriverCount, allDrivers.data(), &descAll);
        EXPECT_EQ(result, ZE_RESULT_SUCCESS);
        
        // Verify each driver responds to API calls
        for (uint32_t i = 0; i < allDriverCount; i++) {
            EXPECT_NE(allDrivers[i], nullptr);
            
            // Call zeDeviceGet to verify routing works
            uint32_t deviceCount = 0;
            ze_result_t devResult = zeDeviceGet(allDrivers[i], &deviceCount, nullptr);
            EXPECT_EQ(devResult, ZE_RESULT_SUCCESS);
            
            // Try to get driver properties
            ze_driver_properties_t props = {};
            props.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
            ze_result_t propResult = zeDriverGetProperties(allDrivers[i], &props);
            // Should succeed for properly initialized drivers
            EXPECT_EQ(propResult, ZE_RESULT_SUCCESS);
        }
        
        // Verify that both GPU and NPU drivers are initialized in the context
        bool foundGPUDriver = false;
        bool foundNPUDriver = false;
        for (const auto& driver : loader::context->zeDrivers) {
            if (driver.driverType == loader::ZEL_DRIVER_TYPE_DISCRETE_GPU ||
                driver.driverType == loader::ZEL_DRIVER_TYPE_GPU ||
                driver.driverType == loader::ZEL_DRIVER_TYPE_INTEGRATED_GPU) {
                foundGPUDriver = true;
                EXPECT_TRUE(driver.ddiInitialized);
            }
            if (driver.driverType == loader::ZEL_DRIVER_TYPE_NPU) {
                foundNPUDriver = true;
                EXPECT_TRUE(driver.ddiInitialized);
            }
        }
        
        // At least one type of driver should be found if we have drivers
        EXPECT_TRUE(foundGPUDriver || foundNPUDriver);
    }
}