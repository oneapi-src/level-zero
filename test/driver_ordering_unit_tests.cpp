/*
 *
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"

#include "source/loader/ze_loader_internal.h"
#include "ze_api.h"

#include <fstream>
#include <vector>
#include <string>

#if defined(_WIN32)
    #include <io.h>
    #include <cstdio>
    #include <fcntl.h>
    #include <windows.h>
    #define putenv_safe _putenv
#else
    #include <cstdlib>
    #include <sys/types.h>
    #include <unistd.h>
    #define putenv_safe putenv
#endif

namespace {

// Helper function to create a mock driver with specific type
loader::driver_t createMockDriver(const std::string& name, loader::zel_driver_type_t type) {
    loader::driver_t driver;
    driver.name = name;
    driver.driverType = type;
    driver.handle = nullptr; // Mock handle
    driver.initStatus = ZE_RESULT_SUCCESS;
    driver.driverInuse = false;
    return driver;
}

// Helper function to clear ZEL_DRIVERS_ORDER environment variable
void clearDriverOrderEnv() {
    putenv_safe(const_cast<char *>("ZEL_DRIVERS_ORDER="));
}

// Helper function to set ZEL_DRIVERS_ORDER environment variable
void setDriverOrderEnv(const std::string& order) {
    static std::string env_var_storage;
    env_var_storage = "ZEL_DRIVERS_ORDER=" + order;
    putenv_safe(const_cast<char *>(env_var_storage.c_str()));
}

// Test fixture for direct unit testing of driver ordering functionality
class DriverOrderingUnitTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Clear any existing environment variables
        clearDriverOrderEnv();
        
        // Initialize a test context if needed
        if (!loader::context) {
            loader::context = new loader::context_t();
            loader::context->debugTraceEnabled = false; // Disable debug trace for cleaner tests
        }
    }

    void TearDown() override {
        // Clean up environment variables
        clearDriverOrderEnv();
    }

    // Helper to create a standard test driver setup
    loader::driver_vector_t createStandardDriverSetup() {
        loader::driver_vector_t drivers;
        drivers.push_back(createMockDriver("discrete_gpu_0", loader::ZEL_DRIVER_TYPE_DISCRETE_GPU));
        drivers.push_back(createMockDriver("discrete_gpu_1", loader::ZEL_DRIVER_TYPE_DISCRETE_GPU));
        drivers.push_back(createMockDriver("integrated_gpu_0", loader::ZEL_DRIVER_TYPE_INTEGRATED_GPU));
        drivers.push_back(createMockDriver("gpu_mixed_0", loader::ZEL_DRIVER_TYPE_GPU));
        drivers.push_back(createMockDriver("npu_0", loader::ZEL_DRIVER_TYPE_NPU));
        drivers.push_back(createMockDriver("other_0", loader::ZEL_DRIVER_TYPE_OTHER));
        return drivers;
    }

    // Helper to verify driver order by names
    void verifyDriverOrder(const loader::driver_vector_t& drivers, const std::vector<std::string>& expectedOrder) {
        ASSERT_EQ(drivers.size(), expectedOrder.size()) << "Driver count mismatch";
        for (size_t i = 0; i < drivers.size(); ++i) {
            EXPECT_EQ(drivers[i].name, expectedOrder[i]) << "Driver order mismatch at index " << i;
        }
    }
};

///////////////////////////////////////////////////////////////////////////////
// Tests for basic driver ordering functionality
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingUnitTest, NoEnvironmentVariable_ShouldNotChangeOrder) {
    // Arrange
    auto drivers = createStandardDriverSetup();
    auto originalOrder = drivers;

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - order should remain unchanged
    ASSERT_EQ(drivers.size(), originalOrder.size());
    for (size_t i = 0; i < drivers.size(); ++i) {
        EXPECT_EQ(drivers[i].name, originalOrder[i].name);
        EXPECT_EQ(drivers[i].driverType, originalOrder[i].driverType);
    }
}

TEST_F(DriverOrderingUnitTest, EmptyEnvironmentVariable_ShouldNotChangeOrder) {
    // Arrange
    setDriverOrderEnv("");
    auto drivers = createStandardDriverSetup();
    auto originalOrder = drivers;

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - order should remain unchanged
    ASSERT_EQ(drivers.size(), originalOrder.size());
    for (size_t i = 0; i < drivers.size(); ++i) {
        EXPECT_EQ(drivers[i].name, originalOrder[i].name);
        EXPECT_EQ(drivers[i].driverType, originalOrder[i].driverType);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Tests for global index ordering (Syntax 3)
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingUnitTest, GlobalIndex_SingleIndex_ShouldMoveToFront) {
    // Arrange
    setDriverOrderEnv("2");
    auto drivers = createStandardDriverSetup();

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - driver at index 2 should move to front
    std::vector<std::string> expectedOrder = {
        "integrated_gpu_0",  // was at index 2
        "discrete_gpu_0",    // was at index 0
        "discrete_gpu_1",    // was at index 1
        "gpu_mixed_0",       // was at index 3
        "npu_0",             // was at index 4
        "other_0"            // was at index 5
    };
    verifyDriverOrder(drivers, expectedOrder);
}

TEST_F(DriverOrderingUnitTest, GlobalIndex_MultipleIndices_ShouldReorderAccordingly) {
    // Arrange
    setDriverOrderEnv("4,1,0");
    auto drivers = createStandardDriverSetup();

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert
    std::vector<std::string> expectedOrder = {
        "npu_0",             // was at index 4
        "discrete_gpu_1",    // was at index 1
        "discrete_gpu_0",    // was at index 0
        "integrated_gpu_0",  // was at index 2
        "gpu_mixed_0",       // was at index 3
        "other_0"            // was at index 5
    };
    verifyDriverOrder(drivers, expectedOrder);
}

TEST_F(DriverOrderingUnitTest, GlobalIndex_OutOfBounds_ShouldIgnoreInvalidIndices) {
    // Arrange
    setDriverOrderEnv("999,2,1000");
    auto drivers = createStandardDriverSetup();

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - only valid index 2 should be moved
    std::vector<std::string> expectedOrder = {
        "integrated_gpu_0",  // was at index 2
        "discrete_gpu_0",    // was at index 0
        "discrete_gpu_1",    // was at index 1
        "gpu_mixed_0",       // was at index 3
        "npu_0",             // was at index 4
        "other_0"            // was at index 5
    };
    verifyDriverOrder(drivers, expectedOrder);
}

///////////////////////////////////////////////////////////////////////////////
// Tests for driver type ordering (Syntax 2)
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingUnitTest, DriverType_NPU_ShouldMoveAllNPUDriversToFront) {
    // Arrange
    setDriverOrderEnv("NPU");
    auto drivers = createStandardDriverSetup();

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - NPU drivers should come first, and OTHER drivers are also moved because
    // they're stored in the same npuIndices vector
    std::vector<std::string> expectedOrder = {
        "npu_0",             // NPU driver moved to front
        "other_0",           // OTHER drivers are also moved with NPU
        "discrete_gpu_0",    // remaining drivers in original order
        "discrete_gpu_1",
        "integrated_gpu_0",
        "gpu_mixed_0"
    };
    verifyDriverOrder(drivers, expectedOrder);
}

TEST_F(DriverOrderingUnitTest, DriverType_DiscreteGPU_ShouldMoveAllDiscreteGPUDriversToFront) {
    // Arrange
    setDriverOrderEnv("DISCRETE_GPU_ONLY");
    auto drivers = createStandardDriverSetup();

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert
    std::vector<std::string> expectedOrder = {
        "discrete_gpu_0",    // discrete GPU drivers moved to front
        "discrete_gpu_1",
        "integrated_gpu_0",  // remaining drivers in original order
        "gpu_mixed_0",
        "npu_0",
        "other_0"
    };
    verifyDriverOrder(drivers, expectedOrder);
}

TEST_F(DriverOrderingUnitTest, DriverType_MultipleTypes_ShouldRespectOrder) {
    // Arrange
    setDriverOrderEnv("NPU,DISCRETE_GPU_ONLY,GPU");
    auto drivers = createStandardDriverSetup();

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert
    std::vector<std::string> expectedOrder = {
        "npu_0",             // NPU first
        "other_0",           // OTHER also moved with NPU request
        "discrete_gpu_0",    // DISCRETE_GPU_ONLY second  
        "discrete_gpu_1",
        "gpu_mixed_0",       // GPU third
        "integrated_gpu_0"   // remaining drivers
    };
    verifyDriverOrder(drivers, expectedOrder);
}

///////////////////////////////////////////////////////////////////////////////
// Tests for driver type and index ordering (Syntax 1)
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingUnitTest, DriverTypeAndIndex_ValidTypeAndIndex_ShouldMoveSpecificDriver) {
    // Arrange
    setDriverOrderEnv("DISCRETE_GPU_ONLY:1");
    auto drivers = createStandardDriverSetup();

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - second discrete GPU driver should move to front
    std::vector<std::string> expectedOrder = {
        "discrete_gpu_1",    // DISCRETE_GPU_ONLY index 1
        "discrete_gpu_0",    // remaining drivers
        "integrated_gpu_0",
        "gpu_mixed_0",
        "npu_0",
        "other_0"
    };
    verifyDriverOrder(drivers, expectedOrder);
}

TEST_F(DriverOrderingUnitTest, DriverTypeAndIndex_NPUWithIndex_ShouldMoveSpecificNPUDriver) {
    // Arrange: In the standard setup, we have npu_0 at index 4 and other_0 at index 5
    // Both are stored in npuIndices, so NPU:0 = npu_0, NPU:1 = other_0
    auto drivers = createStandardDriverSetup();
    
    setDriverOrderEnv("NPU:1");

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - NPU index 1 should be the OTHER driver (other_0) since both NPU and OTHER 
    // are stored in the npuIndices vector
    EXPECT_EQ(drivers[0].name, "other_0");
    EXPECT_EQ(drivers[0].driverType, loader::ZEL_DRIVER_TYPE_OTHER);
}

TEST_F(DriverOrderingUnitTest, DriverTypeAndIndex_OutOfBoundsIndex_ShouldIgnore) {
    // Arrange
    setDriverOrderEnv("DISCRETE_GPU_ONLY:999");
    auto drivers = createStandardDriverSetup();
    auto originalOrder = drivers;

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - order should remain unchanged due to invalid index
    ASSERT_EQ(drivers.size(), originalOrder.size());
    for (size_t i = 0; i < drivers.size(); ++i) {
        EXPECT_EQ(drivers[i].name, originalOrder[i].name);
    }
}

TEST_F(DriverOrderingUnitTest, DriverTypeAndIndex_InvalidDriverType_ShouldIgnore) {
    // Arrange
    setDriverOrderEnv("INVALID_TYPE:0");
    auto drivers = createStandardDriverSetup();
    auto originalOrder = drivers;

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - order should remain unchanged due to invalid type
    ASSERT_EQ(drivers.size(), originalOrder.size());
    for (size_t i = 0; i < drivers.size(); ++i) {
        EXPECT_EQ(drivers[i].name, originalOrder[i].name);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Tests for mixed syntax combinations
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingUnitTest, MixedSyntax_GlobalIndexAndType_ShouldRespectOrder) {
    // Arrange
    setDriverOrderEnv("2,NPU,0");
    auto drivers = createStandardDriverSetup();

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert
    std::vector<std::string> expectedOrder = {
        "integrated_gpu_0",  // global index 2
        "npu_0",             // NPU type
        "other_0",           // OTHER treated as NPU
        "discrete_gpu_0",    // global index 0
        "discrete_gpu_1",    // remaining
        "gpu_mixed_0"
    };
    verifyDriverOrder(drivers, expectedOrder);
}

TEST_F(DriverOrderingUnitTest, MixedSyntax_TypeIndexAndGlobal_ShouldRespectOrder) {
    // Arrange
    setDriverOrderEnv("DISCRETE_GPU_ONLY:1,3,NPU:0");
    auto drivers = createStandardDriverSetup();

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert
    std::vector<std::string> expectedOrder = {
        "discrete_gpu_1",    // DISCRETE_GPU_ONLY:1
        "gpu_mixed_0",       // global index 3
        "npu_0",             // NPU:0
        "discrete_gpu_0",    // remaining
        "integrated_gpu_0",
        "other_0"
    };
    verifyDriverOrder(drivers, expectedOrder);
}

///////////////////////////////////////////////////////////////////////////////
// Tests for edge cases and error handling
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingUnitTest, EmptyDriverVector_ShouldNotCrash) {
    // Arrange
    setDriverOrderEnv("NPU,GPU,0");
    loader::driver_vector_t drivers; // empty vector

    // Act & Assert - should not crash
    EXPECT_NO_THROW(loader::context->driverOrdering(&drivers));
    EXPECT_EQ(drivers.size(), 0);
}

TEST_F(DriverOrderingUnitTest, WhitespaceInEnvironmentVariable_ShouldTrimCorrectly) {
    // Arrange
    setDriverOrderEnv("  NPU : 0  ,  GPU  ,  1  ");
    auto drivers = createStandardDriverSetup();

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - should handle whitespace correctly
    // NPU:0 = npu_0, GPU type = gpu_mixed_0, global index 1 = discrete_gpu_1
    EXPECT_EQ(drivers[0].name, "npu_0");         // NPU:0
    EXPECT_EQ(drivers[1].name, "gpu_mixed_0");   // GPU type  
    EXPECT_EQ(drivers[2].name, "discrete_gpu_1"); // global index 1
}

TEST_F(DriverOrderingUnitTest, DuplicateSpecifications_ShouldUseFirstOccurrence) {
    // Arrange
    setDriverOrderEnv("NPU:0,NPU:0,1,1");
    auto drivers = createStandardDriverSetup();

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - duplicates should be ignored
    std::vector<std::string> expectedOrder = {
        "npu_0",             // NPU:0 (first occurrence)
        "discrete_gpu_1",    // global index 1 (first occurrence)
        "discrete_gpu_0",    // remaining
        "integrated_gpu_0",
        "gpu_mixed_0",
        "other_0"
    };
    verifyDriverOrder(drivers, expectedOrder);
}

TEST_F(DriverOrderingUnitTest, InvalidSyntax_ShouldIgnoreInvalidEntries) {
    // Arrange
    setDriverOrderEnv("NPU:,GPU:abc,::,INVALID:SYNTAX,2");
    auto drivers = createStandardDriverSetup();

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - only valid entries should be processed
    // In this case, only "2" should be processed as a valid global index
    // Expected: integrated_gpu_0 (global index 2) should move to front
    std::vector<std::string> expectedOrder = {
        "integrated_gpu_0",  // valid global index 2
        "discrete_gpu_0",    // remaining drivers
        "discrete_gpu_1",
        "gpu_mixed_0",
        "npu_0",
        "other_0"
    };
    verifyDriverOrder(drivers, expectedOrder);
}

TEST_F(DriverOrderingUnitTest, ColonWithoutIndex_ShouldIgnore) {
    // Arrange
    setDriverOrderEnv("NPU:,GPU:");
    auto drivers = createStandardDriverSetup();
    auto originalOrder = drivers;

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - should ignore invalid syntax and maintain original order
    ASSERT_EQ(drivers.size(), originalOrder.size());
    for (size_t i = 0; i < drivers.size(); ++i) {
        EXPECT_EQ(drivers[i].name, originalOrder[i].name);
    }
}

TEST_F(DriverOrderingUnitTest, OnlyCommas_ShouldIgnore) {
    // Arrange
    setDriverOrderEnv(",,,,");
    auto drivers = createStandardDriverSetup();
    auto originalOrder = drivers;

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - should maintain original order
    ASSERT_EQ(drivers.size(), originalOrder.size());
    for (size_t i = 0; i < drivers.size(); ++i) {
        EXPECT_EQ(drivers[i].name, originalOrder[i].name);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Tests for all supported driver types
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingUnitTest, AllSupportedDriverTypes_ShouldHandleCorrectly) {
    // Arrange: Create drivers of all types
    loader::driver_vector_t drivers;
    drivers.push_back(createMockDriver("discrete_0", loader::ZEL_DRIVER_TYPE_DISCRETE_GPU));
    drivers.push_back(createMockDriver("integrated_0", loader::ZEL_DRIVER_TYPE_INTEGRATED_GPU));
    drivers.push_back(createMockDriver("gpu_mixed_0", loader::ZEL_DRIVER_TYPE_GPU));
    drivers.push_back(createMockDriver("mixed_0", loader::ZEL_DRIVER_TYPE_MIXED));
    drivers.push_back(createMockDriver("other_0", loader::ZEL_DRIVER_TYPE_OTHER));
    drivers.push_back(createMockDriver("npu_0", loader::ZEL_DRIVER_TYPE_NPU));

    setDriverOrderEnv("NPU,INTEGRATED_GPU_ONLY,DISCRETE_GPU_ONLY,GPU");

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert
    std::vector<std::string> expectedOrder = {
        "other_0",         // OTHER (moved with NPU request, comes first due to lower original index)
        "npu_0",           // NPU (moved with NPU request, comes second due to higher original index)
        "integrated_0",    // INTEGRATED_GPU_ONLY
        "discrete_0",      // DISCRETE_GPU_ONLY
        "gpu_mixed_0",     // GPU
        "mixed_0"          // remaining (MIXED)
    };
    verifyDriverOrder(drivers, expectedOrder);
}

TEST_F(DriverOrderingUnitTest, ComplexRealWorldScenario_ShouldHandleCorrectly) {
    // Arrange: Simulate a complex real-world system
    loader::driver_vector_t drivers;
    drivers.push_back(createMockDriver("intel_discrete_0", loader::ZEL_DRIVER_TYPE_DISCRETE_GPU));
    drivers.push_back(createMockDriver("intel_discrete_1", loader::ZEL_DRIVER_TYPE_DISCRETE_GPU));
    drivers.push_back(createMockDriver("intel_integrated_0", loader::ZEL_DRIVER_TYPE_INTEGRATED_GPU));
    drivers.push_back(createMockDriver("intel_npu_0", loader::ZEL_DRIVER_TYPE_NPU));
    drivers.push_back(createMockDriver("other_vendor_gpu", loader::ZEL_DRIVER_TYPE_GPU));

    // Test complex ordering: specific discrete GPU, then all NPUs, then specific global index
    setDriverOrderEnv("DISCRETE_GPU_ONLY:1,NPU,2");

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert
    std::vector<std::string> expectedOrder = {
        "intel_discrete_1",   // DISCRETE_GPU_ONLY:1 (second discrete GPU)
        "intel_npu_0",        // NPU (all NPU drivers)
        "intel_integrated_0", // global index 2
        "intel_discrete_0",   // remaining drivers
        "other_vendor_gpu"
    };
    verifyDriverOrder(drivers, expectedOrder);
}

///////////////////////////////////////////////////////////////////////////////
// Tests for boundary conditions
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingUnitTest, SingleDriver_ShouldHandleCorrectly) {
    // Arrange
    loader::driver_vector_t drivers;
    drivers.push_back(createMockDriver("single_driver", loader::ZEL_DRIVER_TYPE_DISCRETE_GPU));
    
    setDriverOrderEnv("DISCRETE_GPU_ONLY:0,NPU,1");

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - single driver should remain
    ASSERT_EQ(drivers.size(), 1);
    EXPECT_EQ(drivers[0].name, "single_driver");
}

TEST_F(DriverOrderingUnitTest, MaxOrderSpecifications_ShouldHandleCorrectly) {
    // Arrange: Test with many order specifications
    auto drivers = createStandardDriverSetup();
    
    // Create a long ordering string
    setDriverOrderEnv("5,4,3,2,1,0,NPU,GPU,DISCRETE_GPU_ONLY,INTEGRATED_GPU_ONLY");

    // Act
    loader::context->driverOrdering(&drivers);

    // Assert - should process all valid specifications
    std::vector<std::string> expectedOrder = {
        "other_0",           // global index 5
        "npu_0",             // global index 4
        "gpu_mixed_0",       // global index 3
        "integrated_gpu_0",  // global index 2
        "discrete_gpu_1",    // global index 1
        "discrete_gpu_0"     // global index 0
    };
    verifyDriverOrder(drivers, expectedOrder);
}

} // namespace
