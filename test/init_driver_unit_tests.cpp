/*
 * Copyright (C) 2025 Intel Corporation
 * SPDX-License-Identifier: MIT
 */


#include "test/init_driver_unit_tests_common.h"

// Helper to create a mock null driver with a given name and type
loader::driver_t createNullDriver(const std::string& name, loader::zel_driver_type_t type) {
    loader::driver_t driver;

    std::string libraryPath;
    auto loaderLibraryPathEnv = getenv_string("ZEL_LIBRARY_PATH");
    if (!loaderLibraryPathEnv.empty()) {
        libraryPath = loaderLibraryPathEnv;
#ifdef _WIN32
        libraryPath.append("\\");
#else
        libraryPath.append("/");
#endif
    }

#ifdef _WIN32
    driver.name = libraryPath + name + ".dll";
#else
    driver.name = libraryPath + "lib" + name + ".so.1";
#endif
    driver.driverType = type;
    driver.handle = nullptr; // Simulate null driver
    driver.initStatus = ZE_RESULT_SUCCESS;
    driver.driverInuse = false;
    driver.ddiInitialized = false;
    return driver;
}


TEST_F(InitDriverUnitTest, InitWithSingleGPUDriver) {
    loader::driver_t gpuDriver = createNullDriver("ze_fake_gpu", loader::ZEL_DRIVER_TYPE_DISCRETE_GPU);
    ze_result_t result = loader::context->init_driver(gpuDriver, ZE_INIT_FLAG_GPU_ONLY, nullptr);
    EXPECT_EQ(result, ZE_RESULT_SUCCESS);
    EXPECT_TRUE(gpuDriver.ddiInitialized);
}

TEST_F(InitDriverUnitTest, InitWithSingleNPUDriver) {
    loader::driver_t npuDriver = createNullDriver("ze_fake_npu", loader::ZEL_DRIVER_TYPE_NPU);
    ze_init_driver_type_desc_t desc = {};
    desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_NPU;
    ze_result_t result = loader::context->init_driver(npuDriver, 0, &desc);
    EXPECT_EQ(result, ZE_RESULT_SUCCESS);
    EXPECT_TRUE(npuDriver.ddiInitialized);
}

TEST_F(InitDriverUnitTest, InitWithSingleVPUDriver) {
    loader::driver_t vpuDriver = createNullDriver("ze_fake_vpu", loader::ZEL_DRIVER_TYPE_NPU);
    ze_result_t result = loader::context->init_driver(vpuDriver, ZE_INIT_FLAG_VPU_ONLY, nullptr);
    EXPECT_EQ(result, ZE_RESULT_SUCCESS);
    EXPECT_TRUE(vpuDriver.ddiInitialized);
}

TEST_F(InitDriverUnitTest, zeInitWithMultipleDrivers) {
    std::vector<loader::driver_t> drivers = {
        createNullDriver("ze_fake_gpu", loader::ZEL_DRIVER_TYPE_DISCRETE_GPU),
        createNullDriver("ze_fake_npu", loader::ZEL_DRIVER_TYPE_NPU),
        createNullDriver("ze_fake_vpu", loader::ZEL_DRIVER_TYPE_NPU)
    };
    for (auto& driver : drivers) {
        ze_result_t result = loader::context->init_driver(driver, 0, nullptr);
        EXPECT_EQ(result, ZE_RESULT_SUCCESS);
        EXPECT_TRUE(driver.ddiInitialized);
    }
}

TEST_F(InitDriverUnitTest, zeInitDriversWithMultipleDrivers) {
    std::vector<loader::driver_t> drivers = {
        createNullDriver("ze_fake_gpu", loader::ZEL_DRIVER_TYPE_DISCRETE_GPU),
        createNullDriver("ze_fake_npu", loader::ZEL_DRIVER_TYPE_NPU),
        createNullDriver("ze_fake_vpu", loader::ZEL_DRIVER_TYPE_NPU)
    };
    ze_init_driver_type_desc_t desc = {};
    desc.flags = UINT32_MAX; // Request all driver types
    for (auto& driver : drivers) {
        ze_result_t result = loader::context->init_driver(driver, 0, &desc);
        EXPECT_EQ(result, ZE_RESULT_SUCCESS);
        EXPECT_TRUE(driver.ddiInitialized);
    }
}

TEST_F(InitDriverUnitTest, zeInitDriversWithMultipleDriversNPURequested) {
    std::vector<loader::driver_t> drivers = {
        createNullDriver("ze_fake_gpu", loader::ZEL_DRIVER_TYPE_DISCRETE_GPU),
        createNullDriver("ze_fake_npu", loader::ZEL_DRIVER_TYPE_NPU),
        createNullDriver("ze_fake_vpu", loader::ZEL_DRIVER_TYPE_NPU)
    };
    ze_init_driver_type_desc_t desc = {};
    desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_NPU; // Request NPU driver types
    for (auto& driver : drivers) {
        if (driver.driverType == loader::ZEL_DRIVER_TYPE_NPU) {
            ze_result_t result = loader::context->init_driver(driver, 0, &desc);
            EXPECT_EQ(result, ZE_RESULT_SUCCESS);
            EXPECT_TRUE(driver.ddiInitialized);
        } else {
            ze_result_t result = loader::context->init_driver(driver, 0, &desc);
            EXPECT_NE(result, ZE_RESULT_SUCCESS);
            EXPECT_FALSE(driver.ddiInitialized);
        }
    }
}

TEST_F(InitDriverUnitTest, zeInitDriversWithMultipleDriversGPURequested) {
    std::vector<loader::driver_t> drivers = {
        createNullDriver("ze_fake_gpu", loader::ZEL_DRIVER_TYPE_DISCRETE_GPU),
        createNullDriver("ze_fake_npu", loader::ZEL_DRIVER_TYPE_NPU),
        createNullDriver("ze_fake_vpu", loader::ZEL_DRIVER_TYPE_NPU)
    };
    ze_init_driver_type_desc_t desc = {};
    desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU; // Request GPU driver types
    for (auto& driver : drivers) {
        if (driver.driverType == loader::ZEL_DRIVER_TYPE_DISCRETE_GPU) {
            ze_result_t result = loader::context->init_driver(driver, 0, &desc);
            EXPECT_EQ(result, ZE_RESULT_SUCCESS);
            EXPECT_TRUE(driver.ddiInitialized);
        } else {
            ze_result_t result = loader::context->init_driver(driver, 0, &desc);
            EXPECT_NE(result, ZE_RESULT_SUCCESS);
            EXPECT_FALSE(driver.ddiInitialized);
        }
    }
}

TEST_F(InitDriverUnitTest, InitWithUnsupportedNullDriverType) {
    loader::driver_t otherDriver = createNullDriver("ze_fake_other", loader::ZEL_DRIVER_TYPE_OTHER);
    ze_result_t result = loader::context->init_driver(otherDriver, 0, nullptr);
    EXPECT_NE(result, ZE_RESULT_SUCCESS);
    EXPECT_FALSE(otherDriver.ddiInitialized);
}
