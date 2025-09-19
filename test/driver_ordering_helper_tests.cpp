/*
 *
 * Copyright (C) 2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"

// To test internal functions, we need to include the implementation
// In a real scenario, these functions might need to be exposed via a test interface
// or moved to a separate testable module

#include <string>
#include <vector>

// Include the loader types we need
#include "source/loader/ze_loader_internal.h"
#include "source/loader/ze_loader_utils.h"

///////////////////////////////////////////////////////////////////////////////
// Unit tests for helper functions
///////////////////////////////////////////////////////////////////////////////

class DriverOrderingHelperFunctionsTest : public ::testing::Test {
protected:
    void SetUp() override {
        // No setup needed for these pure function tests
    }

    void TearDown() override {
        // No cleanup needed
    }
};

///////////////////////////////////////////////////////////////////////////////
// Tests for stringToDriverType function
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingHelperFunctionsTest, StringToDriverType_ValidTypes_ShouldReturnCorrectEnum) {
    // Test all valid driver type strings
    EXPECT_EQ(loader::stringToDriverType("DISCRETE_GPU_ONLY"), loader::ZEL_DRIVER_TYPE_DISCRETE_GPU);
    EXPECT_EQ(loader::stringToDriverType("GPU"), loader::ZEL_DRIVER_TYPE_GPU);
    EXPECT_EQ(loader::stringToDriverType("INTEGRATED_GPU_ONLY"), loader::ZEL_DRIVER_TYPE_INTEGRATED_GPU);
    EXPECT_EQ(loader::stringToDriverType("NPU"), loader::ZEL_DRIVER_TYPE_NPU);
}

TEST_F(DriverOrderingHelperFunctionsTest, StringToDriverType_InvalidTypes_ShouldReturnForceUint32) {
    // Test invalid driver type strings
    EXPECT_EQ(loader::stringToDriverType("INVALID_TYPE"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32);
    EXPECT_EQ(loader::stringToDriverType(""), loader::ZEL_DRIVER_TYPE_FORCE_UINT32);
    EXPECT_EQ(loader::stringToDriverType("gpu"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32); // lowercase
    EXPECT_EQ(loader::stringToDriverType("discrete_gpu"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32); // wrong format
    EXPECT_EQ(loader::stringToDriverType("GPU_ONLY"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32); // wrong suffix
}

TEST_F(DriverOrderingHelperFunctionsTest, StringToDriverType_CaseSensitivity_ShouldBeStrict) {
    // Test case sensitivity
    EXPECT_EQ(loader::stringToDriverType("npu"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32);
    EXPECT_EQ(loader::stringToDriverType("Npu"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32);
    EXPECT_EQ(loader::stringToDriverType("NPu"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32);
    EXPECT_EQ(loader::stringToDriverType("discrete_gpu_only"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32);
}

///////////////////////////////////////////////////////////////////////////////
// Tests for trim function
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingHelperFunctionsTest, Trim_NoWhitespace_ShouldReturnOriginal) {
    EXPECT_EQ(loader::trim("NPU"), "NPU");
    EXPECT_EQ(loader::trim("DISCRETE_GPU_ONLY"), "DISCRETE_GPU_ONLY");
    EXPECT_EQ(loader::trim("123"), "123");
}

TEST_F(DriverOrderingHelperFunctionsTest, Trim_LeadingWhitespace_ShouldRemove) {
    EXPECT_EQ(loader::trim(" NPU"), "NPU");
    EXPECT_EQ(loader::trim("  NPU"), "NPU");
    EXPECT_EQ(loader::trim("\tNPU"), "NPU");
    EXPECT_EQ(loader::trim("\nNPU"), "NPU");
    EXPECT_EQ(loader::trim("\r\n NPU"), "NPU");
}

TEST_F(DriverOrderingHelperFunctionsTest, Trim_TrailingWhitespace_ShouldRemove) {
    EXPECT_EQ(loader::trim("NPU "), "NPU");
    EXPECT_EQ(loader::trim("NPU  "), "NPU");
    EXPECT_EQ(loader::trim("NPU\t"), "NPU");
    EXPECT_EQ(loader::trim("NPU\n"), "NPU");
    EXPECT_EQ(loader::trim("NPU \r\n"), "NPU");
}

TEST_F(DriverOrderingHelperFunctionsTest, Trim_BothSidesWhitespace_ShouldRemove) {
    EXPECT_EQ(loader::trim(" NPU "), "NPU");
    EXPECT_EQ(loader::trim("  NPU  "), "NPU");
    EXPECT_EQ(loader::trim("\t NPU \t"), "NPU");
    EXPECT_EQ(loader::trim("\n\r NPU \r\n"), "NPU");
}

TEST_F(DriverOrderingHelperFunctionsTest, Trim_OnlyWhitespace_ShouldReturnEmpty) {
    EXPECT_EQ(loader::trim(""), "");
    EXPECT_EQ(loader::trim(" "), "");
    EXPECT_EQ(loader::trim("  "), "");
    EXPECT_EQ(loader::trim("\t"), "");
    EXPECT_EQ(loader::trim("\n"), "");
    EXPECT_EQ(loader::trim("\r\n\t "), "");
}

TEST_F(DriverOrderingHelperFunctionsTest, Trim_MiddleWhitespace_ShouldKeep) {
    EXPECT_EQ(loader::trim("DISCRETE GPU ONLY"), "DISCRETE GPU ONLY");
    EXPECT_EQ(loader::trim(" DISCRETE GPU ONLY "), "DISCRETE GPU ONLY");
}

///////////////////////////////////////////////////////////////////////////////
// Tests for parseDriverOrder function
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_EmptyString_ShouldReturnEmpty) {
    auto specs = loader::parseDriverOrder("");
    EXPECT_TRUE(specs.empty());
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_SingleGlobalIndex_ShouldParseCorrectly) {
    auto specs = loader::parseDriverOrder("2");
    ASSERT_EQ(specs.size(), 1);
    EXPECT_EQ(specs[0].type, loader::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[0].globalIndex, 2);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_MultipleGlobalIndices_ShouldParseCorrectly) {
    auto specs = loader::parseDriverOrder("2,0,1");
    ASSERT_EQ(specs.size(), 3);
    
    EXPECT_EQ(specs[0].type, loader::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[0].globalIndex, 2);
    
    EXPECT_EQ(specs[1].type, loader::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[1].globalIndex, 0);
    
    EXPECT_EQ(specs[2].type, loader::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[2].globalIndex, 1);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_SingleDriverType_ShouldParseCorrectly) {
    auto specs = loader::parseDriverOrder("NPU");
    ASSERT_EQ(specs.size(), 1);
    EXPECT_EQ(specs[0].type, loader::BY_TYPE);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_MultipleDriverTypes_ShouldParseCorrectly) {
    auto specs = loader::parseDriverOrder("NPU,DISCRETE_GPU_ONLY,GPU");
    ASSERT_EQ(specs.size(), 3);
    
    EXPECT_EQ(specs[0].type, loader::BY_TYPE);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    
    EXPECT_EQ(specs[1].type, loader::BY_TYPE);
    EXPECT_EQ(specs[1].driverType, loader::ZEL_DRIVER_TYPE_DISCRETE_GPU);
    
    EXPECT_EQ(specs[2].type, loader::BY_TYPE);
    EXPECT_EQ(specs[2].driverType, loader::ZEL_DRIVER_TYPE_GPU);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_DriverTypeWithIndex_ShouldParseCorrectly) {
    auto specs = loader::parseDriverOrder("NPU:1");
    ASSERT_EQ(specs.size(), 1);
    EXPECT_EQ(specs[0].type, loader::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 1);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_MultipleDriverTypesWithIndices_ShouldParseCorrectly) {
    auto specs = loader::parseDriverOrder("NPU:1,DISCRETE_GPU_ONLY:0,GPU:2");
    ASSERT_EQ(specs.size(), 3);
    
    EXPECT_EQ(specs[0].type, loader::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 1);
    
    EXPECT_EQ(specs[1].type, loader::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[1].driverType, loader::ZEL_DRIVER_TYPE_DISCRETE_GPU);
    EXPECT_EQ(specs[1].typeIndex, 0);
    
    EXPECT_EQ(specs[2].type, loader::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[2].driverType, loader::ZEL_DRIVER_TYPE_GPU);
    EXPECT_EQ(specs[2].typeIndex, 2);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_MixedSyntax_ShouldParseCorrectly) {
    auto specs = loader::parseDriverOrder("NPU:1,2,GPU,0");
    ASSERT_EQ(specs.size(), 4);
    
    EXPECT_EQ(specs[0].type, loader::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 1);
    
    EXPECT_EQ(specs[1].type, loader::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[1].globalIndex, 2);
    
    EXPECT_EQ(specs[2].type, loader::BY_TYPE);
    EXPECT_EQ(specs[2].driverType, loader::ZEL_DRIVER_TYPE_GPU);
    
    EXPECT_EQ(specs[3].type, loader::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[3].globalIndex, 0);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_WithWhitespace_ShouldTrimAndParseCorrectly) {
    auto specs = loader::parseDriverOrder(" NPU : 1 , 2 , GPU ");
    ASSERT_EQ(specs.size(), 3);
    
    EXPECT_EQ(specs[0].type, loader::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 1);
    
    EXPECT_EQ(specs[1].type, loader::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[1].globalIndex, 2);
    
    EXPECT_EQ(specs[2].type, loader::BY_TYPE);
    EXPECT_EQ(specs[2].driverType, loader::ZEL_DRIVER_TYPE_GPU);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_InvalidEntries_ShouldSkipInvalid) {
    auto specs = loader::parseDriverOrder("NPU:1,INVALID_TYPE,abc,GPU:xyz,2");
    ASSERT_EQ(specs.size(), 2);
    
    EXPECT_EQ(specs[0].type, loader::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 1);
    
    EXPECT_EQ(specs[1].type, loader::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[1].globalIndex, 2);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_EmptyTokens_ShouldSkipEmpty) {
    auto specs = loader::parseDriverOrder("NPU,,2,,,GPU");
    ASSERT_EQ(specs.size(), 3);
    
    EXPECT_EQ(specs[0].type, loader::BY_TYPE);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    
    EXPECT_EQ(specs[1].type, loader::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[1].globalIndex, 2);
    
    EXPECT_EQ(specs[2].type, loader::BY_TYPE);
    EXPECT_EQ(specs[2].driverType, loader::ZEL_DRIVER_TYPE_GPU);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_ColonWithoutIndex_ShouldSkip) {
    auto specs = loader::parseDriverOrder("NPU:,GPU:");
    EXPECT_TRUE(specs.empty());
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_OnlyCommas_ShouldReturnEmpty) {
    auto specs = loader::parseDriverOrder(",,,,");
    EXPECT_TRUE(specs.empty());
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_InvalidIndexes_ShouldSkipInvalidOnes) {
    auto specs = loader::parseDriverOrder("NPU:0,GPU:abc,DISCRETE_GPU_ONLY:999999999999999999999");
    ASSERT_EQ(specs.size(), 1); // Only NPU:0 should be valid
    
    EXPECT_EQ(specs[0].type, loader::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 0);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_LargeValidIndex_ShouldParseCorrectly) {
    auto specs = loader::parseDriverOrder("NPU:4294967295"); // Max uint32_t
    ASSERT_EQ(specs.size(), 1);
    
    EXPECT_EQ(specs[0].type, loader::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 4294967295u);
}

///////////////////////////////////////////////////////////////////////////////
// Integration tests for the parsing functionality
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_RealWorldExamples_ShouldParseCorrectly) {
    // Documentation Example 1: DISCRETE_GPU_ONLY:1,NPU
    auto specs = loader::parseDriverOrder("DISCRETE_GPU_ONLY:1,NPU");
    ASSERT_EQ(specs.size(), 2);
    
    EXPECT_EQ(specs[0].type, loader::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_DISCRETE_GPU);
    EXPECT_EQ(specs[0].typeIndex, 1);
    
    EXPECT_EQ(specs[1].type, loader::BY_TYPE);
    EXPECT_EQ(specs[1].driverType, loader::ZEL_DRIVER_TYPE_NPU);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_ComplexScenario_ShouldParseCorrectly) {
    // Complex example: "NPU:0,2,GPU,0,DISCRETE_GPU_ONLY:1"
    auto specs = loader::parseDriverOrder("NPU:0,2,GPU,0,DISCRETE_GPU_ONLY:1");
    ASSERT_EQ(specs.size(), 5);
    
    EXPECT_EQ(specs[0].type, loader::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 0);
    
    EXPECT_EQ(specs[1].type, loader::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[1].globalIndex, 2);
    
    EXPECT_EQ(specs[2].type, loader::BY_TYPE);
    EXPECT_EQ(specs[2].driverType, loader::ZEL_DRIVER_TYPE_GPU);
    
    EXPECT_EQ(specs[3].type, loader::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[3].globalIndex, 0);
    
    EXPECT_EQ(specs[4].type, loader::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[4].driverType, loader::ZEL_DRIVER_TYPE_DISCRETE_GPU);
    EXPECT_EQ(specs[4].typeIndex, 1);
}
