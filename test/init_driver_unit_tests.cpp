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

// ---------------------------------------------------------------------------
// Tests: no DDI tables initialized — zeInit context (flags, no desc)
// ---------------------------------------------------------------------------

// Simulates zeInit(ZE_INIT_FLAG_GPU_ONLY) when only an NPU driver is present.
// The type mismatch means init_driver never loads the library, so every DDI
// init-result field must remain at its initial ZE_RESULT_ERROR_UNINITIALIZED.
TEST_F(InitDriverUnitTest, zeInit_NoDDITablesInitialized_WhenGPUFlagOnlyAndNPUDriver) {
    loader::driver_t npuDriver = createNullDriver("ze_fake_npu", loader::ZEL_DRIVER_TYPE_NPU);
    ze_result_t result = loader::context->init_driver(npuDriver, ZE_INIT_FLAG_GPU_ONLY, nullptr);
    EXPECT_EQ(result, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_FALSE(npuDriver.ddiInitialized);
    EXPECT_EQ(npuDriver.zeddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_EQ(npuDriver.zesddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_EQ(npuDriver.zetddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_EQ(npuDriver.zerddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
}

// Simulates zeInit(ZE_INIT_FLAG_VPU_ONLY) when only a GPU driver is present.
TEST_F(InitDriverUnitTest, zeInit_NoDDITablesInitialized_WhenVPUFlagOnlyAndGPUDriver) {
    loader::driver_t gpuDriver = createNullDriver("ze_fake_gpu", loader::ZEL_DRIVER_TYPE_DISCRETE_GPU);
    ze_result_t result = loader::context->init_driver(gpuDriver, ZE_INIT_FLAG_VPU_ONLY, nullptr);
    EXPECT_EQ(result, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_FALSE(gpuDriver.ddiInitialized);
    EXPECT_EQ(gpuDriver.zeddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_EQ(gpuDriver.zesddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_EQ(gpuDriver.zetddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_EQ(gpuDriver.zerddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
}

// Simulates zeInit(0) (all-types) when only an OTHER-type driver is present;
// OTHER is not matched by the default flags path, so DDI tables stay empty.
TEST_F(InitDriverUnitTest, zeInit_NoDDITablesInitialized_WhenAllFlagsAndOtherTypeDriver) {
    loader::driver_t otherDriver = createNullDriver("ze_fake_other", loader::ZEL_DRIVER_TYPE_OTHER);
    ze_result_t result = loader::context->init_driver(otherDriver, 0, nullptr);
    EXPECT_EQ(result, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_FALSE(otherDriver.ddiInitialized);
    EXPECT_EQ(otherDriver.zeddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_EQ(otherDriver.zesddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_EQ(otherDriver.zetddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_EQ(otherDriver.zerddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
}

// Multiple drivers all fail type matching under a zeInit(GPU-only) call.
TEST_F(InitDriverUnitTest, zeInit_AllDDITablesUninitialized_WhenNoDriverTypeMatchesGPUFlag) {
    std::vector<loader::driver_t> drivers = {
        createNullDriver("ze_fake_npu",  loader::ZEL_DRIVER_TYPE_NPU),
        createNullDriver("ze_fake_npu2", loader::ZEL_DRIVER_TYPE_NPU),
    };
    for (auto& driver : drivers) {
        ze_result_t result = loader::context->init_driver(driver, ZE_INIT_FLAG_GPU_ONLY, nullptr);
        EXPECT_EQ(result, ZE_RESULT_ERROR_UNINITIALIZED);
        EXPECT_FALSE(driver.ddiInitialized);
        EXPECT_EQ(driver.zeddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
        EXPECT_EQ(driver.zesddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
        EXPECT_EQ(driver.zetddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
        EXPECT_EQ(driver.zerddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    }
}

// ---------------------------------------------------------------------------
// Tests: no DDI tables initialized — zeInitDrivers context (desc, no flags)
// ---------------------------------------------------------------------------

// Simulates zeInitDrivers(GPU) when only an NPU driver is present.
TEST_F(InitDriverUnitTest, zeInitDrivers_NoDDITablesInitialized_WhenGPUDescAndNPUDriver) {
    loader::driver_t npuDriver = createNullDriver("ze_fake_npu", loader::ZEL_DRIVER_TYPE_NPU);
    ze_init_driver_type_desc_t desc = {};
    desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU;
    ze_result_t result = loader::context->init_driver(npuDriver, 0, &desc);
    EXPECT_EQ(result, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_FALSE(npuDriver.ddiInitialized);
    EXPECT_EQ(npuDriver.zeddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_EQ(npuDriver.zesddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_EQ(npuDriver.zetddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_EQ(npuDriver.zerddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
}

// Simulates zeInitDrivers(NPU) when only a discrete GPU driver is present.
TEST_F(InitDriverUnitTest, zeInitDrivers_NoDDITablesInitialized_WhenNPUDescAndGPUDriver) {
    loader::driver_t gpuDriver = createNullDriver("ze_fake_gpu", loader::ZEL_DRIVER_TYPE_DISCRETE_GPU);
    ze_init_driver_type_desc_t desc = {};
    desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_NPU;
    ze_result_t result = loader::context->init_driver(gpuDriver, 0, &desc);
    EXPECT_EQ(result, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_FALSE(gpuDriver.ddiInitialized);
    EXPECT_EQ(gpuDriver.zeddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_EQ(gpuDriver.zesddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_EQ(gpuDriver.zetddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_EQ(gpuDriver.zerddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
}

// Multiple GPU and NPU drivers all fail when the desc requests the opposite type.
TEST_F(InitDriverUnitTest, zeInitDrivers_AllDDITablesUninitialized_WhenNoDriverTypeMatchesDesc) {
    std::vector<loader::driver_t> drivers = {
        createNullDriver("ze_fake_gpu",  loader::ZEL_DRIVER_TYPE_DISCRETE_GPU),
        createNullDriver("ze_fake_igpu", loader::ZEL_DRIVER_TYPE_INTEGRATED_GPU),
    };
    ze_init_driver_type_desc_t desc = {};
    desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_NPU; // No GPU drivers should match
    for (auto& driver : drivers) {
        ze_result_t result = loader::context->init_driver(driver, 0, &desc);
        EXPECT_EQ(result, ZE_RESULT_ERROR_UNINITIALIZED);
        EXPECT_FALSE(driver.ddiInitialized);
        EXPECT_EQ(driver.zeddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
        EXPECT_EQ(driver.zesddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
        EXPECT_EQ(driver.zetddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
        EXPECT_EQ(driver.zerddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    }
}

// ---------------------------------------------------------------------------
// Tests: no DDI tables initialized — zesInit context (sysman DDI status)
// ---------------------------------------------------------------------------

// Simulates the zesInit path: a driver whose type does not match the requested
// flags never has its sysman DDI table populated.  zesddiInitResult must stay
// at ZE_RESULT_ERROR_UNINITIALIZED and ddiInitialized must remain false so
// that the zesInit intercept correctly skips the driver.
TEST_F(InitDriverUnitTest, zesInit_SysmanDDINotInitialized_WhenDriverTypeDoesNotMatchFlags) {
    loader::driver_t gpuDriver = createNullDriver("ze_fake_gpu", loader::ZEL_DRIVER_TYPE_DISCRETE_GPU);
    ze_init_driver_type_desc_t desc = {};
    desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_NPU; // GPU driver will not match
    ze_result_t result = loader::context->init_driver(gpuDriver, 0, &desc);
    EXPECT_EQ(result, ZE_RESULT_ERROR_UNINITIALIZED);
    // ddiInitialized == false causes the zesInit intercept to skip this driver
    EXPECT_FALSE(gpuDriver.ddiInitialized);
    // The sysman DDI result must be untouched since the library was never loaded
    EXPECT_EQ(gpuDriver.zesddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
}

// Same check for NPU driver when only GPU is requested (covers the symmetric case).
TEST_F(InitDriverUnitTest, zesInit_SysmanDDINotInitialized_WhenNPUDriverAndGPUFlagOnly) {
    loader::driver_t npuDriver = createNullDriver("ze_fake_npu", loader::ZEL_DRIVER_TYPE_NPU);
    ze_result_t result = loader::context->init_driver(npuDriver, ZE_INIT_FLAG_GPU_ONLY, nullptr);
    EXPECT_EQ(result, ZE_RESULT_ERROR_UNINITIALIZED);
    EXPECT_FALSE(npuDriver.ddiInitialized);
    EXPECT_EQ(npuDriver.zesddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
}

// All drivers in a mixed pool leave zesddiInitResult unset when none of them
// match the zeInitDrivers(GPU) descriptor, confirming the zesInit intercept
// would find no usable sysman DDI tables.
TEST_F(InitDriverUnitTest, zesInit_AllSysmanDDITablesUninitialized_WhenNoDriverMatchesDesc) {
    std::vector<loader::driver_t> drivers = {
        createNullDriver("ze_fake_npu",  loader::ZEL_DRIVER_TYPE_NPU),
        createNullDriver("ze_fake_npu2", loader::ZEL_DRIVER_TYPE_NPU),
    };
    ze_init_driver_type_desc_t desc = {};
    desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU;
    for (auto& driver : drivers) {
        ze_result_t result = loader::context->init_driver(driver, 0, &desc);
        EXPECT_EQ(result, ZE_RESULT_ERROR_UNINITIALIZED);
        EXPECT_FALSE(driver.ddiInitialized);
        EXPECT_EQ(driver.zesddiInitResult, ZE_RESULT_ERROR_UNINITIALIZED);
    }
}
