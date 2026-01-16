/*
 *
 * Copyright (C) 2026 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"

#include "source/loader/ze_loader_internal.h"
#include "ze_api.h"

#include <set>
#include <vector>
#include <string>

#if defined(_WIN32)
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

namespace {

// Mock handle values for testing (using distinct non-null values)
#if defined(_WIN32)
    #define MOCK_HANDLE_1 reinterpret_cast<HMODULE>(0x1000)
    #define MOCK_HANDLE_2 reinterpret_cast<HMODULE>(0x2000)
    #define MOCK_HANDLE_3 reinterpret_cast<HMODULE>(0x3000)
    #define MOCK_HANDLE_4 reinterpret_cast<HMODULE>(0x4000)
#else
    #define MOCK_HANDLE_1 reinterpret_cast<void*>(0x1000)
    #define MOCK_HANDLE_2 reinterpret_cast<void*>(0x2000)
    #define MOCK_HANDLE_3 reinterpret_cast<void*>(0x3000)
    #define MOCK_HANDLE_4 reinterpret_cast<void*>(0x4000)
#endif

// Helper function to create a mock driver with specific handle
loader::driver_t createMockDriverWithHandle(const std::string& name, HMODULE handle, loader::zel_driver_type_t type = loader::ZEL_DRIVER_TYPE_GPU) {
    loader::driver_t driver;
    driver.name = name;
    driver.handle = handle;
    driver.driverType = type;
    driver.initStatus = ZE_RESULT_SUCCESS;
    driver.driverInuse = false;
    driver.ddiInitialized = false;
    return driver;
}

// Helper function to collect unique handles (mimics destructor logic)
std::set<HMODULE> collectUniqueHandles(
    const loader::driver_vector_t& allDrivers,
    const loader::driver_vector_t& zeDrivers,
    const loader::driver_vector_t& zesDrivers)
{
    std::set<HMODULE> uniqueHandles;
    
    for (const auto& drv : allDrivers) {
        if (drv.handle) {
            uniqueHandles.insert(drv.handle);
        }
    }
    for (const auto& drv : zeDrivers) {
        if (drv.handle) {
            uniqueHandles.insert(drv.handle);
        }
    }
    for (const auto& drv : zesDrivers) {
        if (drv.handle) {
            uniqueHandles.insert(drv.handle);
        }
    }
    
    return uniqueHandles;
}

// Test fixture for driver teardown functionality
class DriverTeardownUnitTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Clear all driver vectors before each test
        allDrivers.clear();
        zeDrivers.clear();
        zesDrivers.clear();
    }

    void TearDown() override {
        // Cleanup after each test
        allDrivers.clear();
        zeDrivers.clear();
        zesDrivers.clear();
    }

    loader::driver_vector_t allDrivers;
    loader::driver_vector_t zeDrivers;
    loader::driver_vector_t zesDrivers;
};

///////////////////////////////////////////////////////////////////////////////
// Tests for basic handle collection
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverTeardownUnitTest, NoDrivers_ShouldReturnEmptySet) {
    // Arrange - all vectors are empty from SetUp

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert
    EXPECT_EQ(uniqueHandles.size(), 0);
}

TEST_F(DriverTeardownUnitTest, AllNullHandles_ShouldReturnEmptySet) {
    // Arrange
    allDrivers.push_back(createMockDriverWithHandle("driver1", nullptr));
    allDrivers.push_back(createMockDriverWithHandle("driver2", nullptr));
    zeDrivers.push_back(createMockDriverWithHandle("driver1", nullptr));
    zesDrivers.push_back(createMockDriverWithHandle("driver1", nullptr));

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert
    EXPECT_EQ(uniqueHandles.size(), 0);
}

TEST_F(DriverTeardownUnitTest, SingleDriverInAllDrivers_ShouldReturnOneHandle) {
    // Arrange
    allDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert
    EXPECT_EQ(uniqueHandles.size(), 1);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
}

TEST_F(DriverTeardownUnitTest, MultipleUniqueHandlesInAllDrivers_ShouldReturnAllHandles) {
    // Arrange
    allDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    allDrivers.push_back(createMockDriverWithHandle("driver2", MOCK_HANDLE_2));
    allDrivers.push_back(createMockDriverWithHandle("driver3", MOCK_HANDLE_3));

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert
    EXPECT_EQ(uniqueHandles.size(), 3);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_2), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_3), uniqueHandles.end());
}

///////////////////////////////////////////////////////////////////////////////
// Tests for duplicate handle scenarios
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverTeardownUnitTest, SameHandleInAllThreeVectors_ShouldReturnOneHandle) {
    // Arrange - simulate the case where all vectors have copies with the same handle
    allDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zeDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zesDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert - should deduplicate to single handle
    EXPECT_EQ(uniqueHandles.size(), 1);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
}

TEST_F(DriverTeardownUnitTest, MultipleDuplicateHandlesAcrossVectors_ShouldDeduplicate) {
    // Arrange
    allDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    allDrivers.push_back(createMockDriverWithHandle("driver2", MOCK_HANDLE_2));
    
    zeDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zeDrivers.push_back(createMockDriverWithHandle("driver2", MOCK_HANDLE_2));
    
    zesDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zesDrivers.push_back(createMockDriverWithHandle("driver2", MOCK_HANDLE_2));

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert - should have only 2 unique handles
    EXPECT_EQ(uniqueHandles.size(), 2);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_2), uniqueHandles.end());
}

TEST_F(DriverTeardownUnitTest, SameHandleInZeAndZesOnly_ShouldReturnOneHandle) {
    // Arrange - allDrivers has null, but zeDrivers and zesDrivers have handles
    allDrivers.push_back(createMockDriverWithHandle("driver1", nullptr));
    zeDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zesDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert - should deduplicate the handle from zeDrivers and zesDrivers
    EXPECT_EQ(uniqueHandles.size(), 1);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
}

///////////////////////////////////////////////////////////////////////////////
// Tests for handle distribution across vectors
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverTeardownUnitTest, OnlyZeDriversHaveHandles_ShouldReturnThoseHandles) {
    // Arrange
    allDrivers.push_back(createMockDriverWithHandle("driver1", nullptr));
    allDrivers.push_back(createMockDriverWithHandle("driver2", nullptr));
    
    zeDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zeDrivers.push_back(createMockDriverWithHandle("driver2", MOCK_HANDLE_2));

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert
    EXPECT_EQ(uniqueHandles.size(), 2);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_2), uniqueHandles.end());
}

TEST_F(DriverTeardownUnitTest, OnlyZesDriversHaveHandles_ShouldReturnThoseHandles) {
    // Arrange
    allDrivers.push_back(createMockDriverWithHandle("driver1", nullptr));
    allDrivers.push_back(createMockDriverWithHandle("driver2", nullptr));
    
    zesDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zesDrivers.push_back(createMockDriverWithHandle("driver2", MOCK_HANDLE_2));

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert
    EXPECT_EQ(uniqueHandles.size(), 2);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_2), uniqueHandles.end());
}

TEST_F(DriverTeardownUnitTest, DifferentHandlesInEachVector_ShouldReturnAllUniqueHandles) {
    // Arrange - each vector has different handles
    allDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zeDrivers.push_back(createMockDriverWithHandle("driver2", MOCK_HANDLE_2));
    zesDrivers.push_back(createMockDriverWithHandle("driver3", MOCK_HANDLE_3));

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert
    EXPECT_EQ(uniqueHandles.size(), 3);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_2), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_3), uniqueHandles.end());
}

///////////////////////////////////////////////////////////////////////////////
// Tests for realistic initialization scenarios
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverTeardownUnitTest, SingleDriverScenario_AllVectorsHaveSameHandle) {
    // Arrange - simulate single driver initialization where all vectors get the handle
    allDrivers.push_back(createMockDriverWithHandle("gpu_driver", MOCK_HANDLE_1));
    zeDrivers.push_back(createMockDriverWithHandle("gpu_driver", MOCK_HANDLE_1));
    zesDrivers.push_back(createMockDriverWithHandle("gpu_driver", MOCK_HANDLE_1));

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert - should deduplicate to single handle
    EXPECT_EQ(uniqueHandles.size(), 1);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
}

TEST_F(DriverTeardownUnitTest, MultipleDriversScenario_AllDriversHasNulls_OthersHaveHandles) {
    // Arrange - simulate multiple drivers where allDrivers initially has nulls,
    // but zeDrivers and zesDrivers get handles loaded via init_driver()
    allDrivers.push_back(createMockDriverWithHandle("driver1", nullptr));
    allDrivers.push_back(createMockDriverWithHandle("driver2", nullptr));
    allDrivers.push_back(createMockDriverWithHandle("driver3", nullptr));
    
    // After init, zeDrivers and zesDrivers have handles loaded
    zeDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zeDrivers.push_back(createMockDriverWithHandle("driver2", MOCK_HANDLE_2));
    zeDrivers.push_back(createMockDriverWithHandle("driver3", MOCK_HANDLE_3));
    
    zesDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zesDrivers.push_back(createMockDriverWithHandle("driver2", MOCK_HANDLE_2));
    zesDrivers.push_back(createMockDriverWithHandle("driver3", MOCK_HANDLE_3));

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert - should deduplicate to 3 unique handles
    EXPECT_EQ(uniqueHandles.size(), 3);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_2), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_3), uniqueHandles.end());
}

TEST_F(DriverTeardownUnitTest, PartialInitialization_SomeDriversInitialized) {
    // Arrange - simulate partial initialization where only some drivers loaded
    allDrivers.push_back(createMockDriverWithHandle("driver1", nullptr));
    allDrivers.push_back(createMockDriverWithHandle("driver2", nullptr));
    allDrivers.push_back(createMockDriverWithHandle("driver3", nullptr));
    
    // Only first two drivers initialized in zeDrivers
    zeDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zeDrivers.push_back(createMockDriverWithHandle("driver2", MOCK_HANDLE_2));
    zeDrivers.push_back(createMockDriverWithHandle("driver3", nullptr));
    
    // All three initialized in zesDrivers
    zesDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zesDrivers.push_back(createMockDriverWithHandle("driver2", MOCK_HANDLE_2));
    zesDrivers.push_back(createMockDriverWithHandle("driver3", MOCK_HANDLE_3));

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert - should have all 3 handles
    EXPECT_EQ(uniqueHandles.size(), 3);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_2), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_3), uniqueHandles.end());
}

TEST_F(DriverTeardownUnitTest, DifferentDriversInitializedInZeVsZes) {
    // Arrange - simulate where zeDrivers and zesDrivers initialized different sets
    allDrivers.push_back(createMockDriverWithHandle("driver1", nullptr));
    allDrivers.push_back(createMockDriverWithHandle("driver2", nullptr));
    
    // Only driver1 initialized in zeDrivers
    zeDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zeDrivers.push_back(createMockDriverWithHandle("driver2", nullptr));
    
    // Only driver2 initialized in zesDrivers
    zesDrivers.push_back(createMockDriverWithHandle("driver1", nullptr));
    zesDrivers.push_back(createMockDriverWithHandle("driver2", MOCK_HANDLE_2));

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert - should have both handles
    EXPECT_EQ(uniqueHandles.size(), 2);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_2), uniqueHandles.end());
}

///////////////////////////////////////////////////////////////////////////////
// Tests for edge cases and mixed scenarios
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverTeardownUnitTest, MixedNullAndValidHandles_ShouldOnlyReturnValid) {
    // Arrange
    allDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    allDrivers.push_back(createMockDriverWithHandle("driver2", nullptr));
    allDrivers.push_back(createMockDriverWithHandle("driver3", MOCK_HANDLE_2));
    
    zeDrivers.push_back(createMockDriverWithHandle("driver1", nullptr));
    zeDrivers.push_back(createMockDriverWithHandle("driver2", MOCK_HANDLE_3));
    
    zesDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert - should have 3 unique valid handles
    EXPECT_EQ(uniqueHandles.size(), 3);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_2), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_3), uniqueHandles.end());
}

TEST_F(DriverTeardownUnitTest, VectorSizeMismatch_ShouldHandleCorrectly) {
    // Arrange - vectors have different sizes
    allDrivers.push_back(createMockDriverWithHandle("driver1", nullptr));
    allDrivers.push_back(createMockDriverWithHandle("driver2", nullptr));
    allDrivers.push_back(createMockDriverWithHandle("driver3", nullptr));
    
    zeDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zeDrivers.push_back(createMockDriverWithHandle("driver2", MOCK_HANDLE_2));
    // zeDrivers has only 2 elements
    
    zesDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    // zesDrivers has only 1 element

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert - should handle size mismatch and return unique handles
    EXPECT_EQ(uniqueHandles.size(), 2);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_2), uniqueHandles.end());
}

TEST_F(DriverTeardownUnitTest, LargeNumberOfDrivers_ShouldHandleEfficiently) {
    // Arrange - simulate a large number of drivers
    const size_t numDrivers = 100;
    
    for (size_t i = 0; i < numDrivers; ++i) {
        HMODULE handle = reinterpret_cast<HMODULE>(0x1000 + i * 0x100);
        allDrivers.push_back(createMockDriverWithHandle("driver" + std::to_string(i), handle));
        zeDrivers.push_back(createMockDriverWithHandle("driver" + std::to_string(i), handle));
        zesDrivers.push_back(createMockDriverWithHandle("driver" + std::to_string(i), handle));
    }

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert - should deduplicate all to numDrivers unique handles
    EXPECT_EQ(uniqueHandles.size(), numDrivers);
}

TEST_F(DriverTeardownUnitTest, CustomDriverScenario_ShouldIncludeCustomHandles) {
    // Arrange - simulate custom drivers alongside standard drivers
    allDrivers.push_back(createMockDriverWithHandle("standard_driver", MOCK_HANDLE_1));
    allDrivers.push_back(createMockDriverWithHandle("custom_driver", MOCK_HANDLE_2));
    
    auto customDriver = createMockDriverWithHandle("custom_driver", MOCK_HANDLE_2);
    customDriver.customDriver = true;
    
    zeDrivers.push_back(createMockDriverWithHandle("standard_driver", MOCK_HANDLE_1));
    zeDrivers.push_back(customDriver);

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert
    EXPECT_EQ(uniqueHandles.size(), 2);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_2), uniqueHandles.end());
}

///////////////////////////////////////////////////////////////////////////////
// Tests for driver type specific scenarios
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverTeardownUnitTest, MixedDriverTypes_ShouldCollectAllHandles) {
    // Arrange - different driver types
    allDrivers.push_back(createMockDriverWithHandle("discrete_gpu", MOCK_HANDLE_1, 
                                                     loader::ZEL_DRIVER_TYPE_DISCRETE_GPU));
    allDrivers.push_back(createMockDriverWithHandle("integrated_gpu", MOCK_HANDLE_2, 
                                                     loader::ZEL_DRIVER_TYPE_INTEGRATED_GPU));
    allDrivers.push_back(createMockDriverWithHandle("npu", MOCK_HANDLE_3, 
                                                     loader::ZEL_DRIVER_TYPE_NPU));
    
    zeDrivers = allDrivers; // Copy to zeDrivers
    zesDrivers = allDrivers; // Copy to zesDrivers

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert - should deduplicate regardless of driver type
    EXPECT_EQ(uniqueHandles.size(), 3);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_2), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_3), uniqueHandles.end());
}

TEST_F(DriverTeardownUnitTest, ComplexRealWorldScenario_ShouldHandleCorrectly) {
    // Arrange - simulate a complex real-world scenario
    // Initial state: allDrivers has some handles, some nulls
    allDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    allDrivers.push_back(createMockDriverWithHandle("driver2", nullptr));
    allDrivers.push_back(createMockDriverWithHandle("driver3", nullptr));
    allDrivers.push_back(createMockDriverWithHandle("driver4", MOCK_HANDLE_4));
    
    // After zeInit: some drivers initialized
    zeDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zeDrivers.push_back(createMockDriverWithHandle("driver2", MOCK_HANDLE_2));
    zeDrivers.push_back(createMockDriverWithHandle("driver3", nullptr)); // Failed to init
    zeDrivers.push_back(createMockDriverWithHandle("driver4", MOCK_HANDLE_4));
    
    // After zesInit: different set initialized
    zesDrivers.push_back(createMockDriverWithHandle("driver1", MOCK_HANDLE_1));
    zesDrivers.push_back(createMockDriverWithHandle("driver2", nullptr)); // Not needed for sysman
    zesDrivers.push_back(createMockDriverWithHandle("driver3", MOCK_HANDLE_3)); // Sysman initialized this
    zesDrivers.push_back(createMockDriverWithHandle("driver4", MOCK_HANDLE_4));

    // Act
    auto uniqueHandles = collectUniqueHandles(allDrivers, zeDrivers, zesDrivers);

    // Assert - should collect all unique handles
    EXPECT_EQ(uniqueHandles.size(), 4);
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_1), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_2), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_3), uniqueHandles.end());
    EXPECT_NE(uniqueHandles.find(MOCK_HANDLE_4), uniqueHandles.end());
}

} // namespace
