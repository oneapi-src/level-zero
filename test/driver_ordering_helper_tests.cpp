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

// Since the helper functions are currently static/internal, we'll redefine them here for testing
// In a production environment, these would ideally be extracted to a testable module

namespace loader_test {

// Copy of the internal helper functions for testing purposes
enum DriverOrderSpecType { BY_GLOBAL_INDEX, BY_TYPE, BY_TYPE_AND_INDEX };

struct DriverOrderSpec {
    DriverOrderSpecType type;
    uint32_t globalIndex = 0;
    loader::zel_driver_type_t driverType = loader::ZEL_DRIVER_TYPE_FORCE_UINT32;
    uint32_t typeIndex = 0;
};

// Helper function to map driver type string to enum (copy from implementation)
loader::zel_driver_type_t stringToDriverType(const std::string& typeStr) {
    if (typeStr == "DISCRETE_GPU_ONLY") {
        return loader::ZEL_DRIVER_TYPE_DISCRETE_GPU;
    } else if (typeStr == "GPU") {
        return loader::ZEL_DRIVER_TYPE_GPU;
    } else if (typeStr == "INTEGRATED_GPU_ONLY") {
        return loader::ZEL_DRIVER_TYPE_INTEGRATED_GPU;
    } else if (typeStr == "NPU") {
        return loader::ZEL_DRIVER_TYPE_NPU;
    }
    return loader::ZEL_DRIVER_TYPE_FORCE_UINT32; // Invalid
}

// Helper function to trim whitespace (copy from implementation)
std::string trim(const std::string& str) {
    const std::string whitespace = " \t\n\r\f\v";
    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}

// Parse ZEL_DRIVERS_ORDER environment variable (copy from implementation)
std::vector<DriverOrderSpec> parseDriverOrder(const std::string& orderStr) {
    std::vector<DriverOrderSpec> specs;

    // Split by comma
    std::vector<std::string> tokens;
    std::stringstream ss(orderStr);
    std::string token;

    while (std::getline(ss, token, ',')) {
        token = trim(token);
        if (token.empty()) continue;

        DriverOrderSpec spec;

        // Check if it contains a colon (type:index format)
        size_t colonPos = token.find(':');
        if (colonPos != std::string::npos) {
            // Format: <driver_type>:<driver_index>
            std::string typeStr = trim(token.substr(0, colonPos));
            std::string indexStr = trim(token.substr(colonPos + 1));

            spec.driverType = stringToDriverType(typeStr);
            if (spec.driverType == loader::ZEL_DRIVER_TYPE_FORCE_UINT32) {
                continue; // Invalid driver type, skip
            }

            try {
                spec.typeIndex = std::stoul(indexStr);
                spec.type = BY_TYPE_AND_INDEX;
                specs.push_back(spec);
            } catch (const std::exception&) {
                // Invalid index, skip
                continue;
            }
        } else {
            // Check if it's a pure number (global index) or driver type
            try {
                spec.globalIndex = std::stoul(token);
                spec.type = BY_GLOBAL_INDEX;
                specs.push_back(spec);
            } catch (const std::exception&) {
                // Not a number, try as driver type
                spec.driverType = stringToDriverType(token);
                if (spec.driverType != loader::ZEL_DRIVER_TYPE_FORCE_UINT32) {
                    spec.type = BY_TYPE;
                    specs.push_back(spec);
                }
            }
        }
    }

    return specs;
}

} // namespace loader_test

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
    EXPECT_EQ(loader_test::stringToDriverType("DISCRETE_GPU_ONLY"), loader::ZEL_DRIVER_TYPE_DISCRETE_GPU);
    EXPECT_EQ(loader_test::stringToDriverType("GPU"), loader::ZEL_DRIVER_TYPE_GPU);
    EXPECT_EQ(loader_test::stringToDriverType("INTEGRATED_GPU_ONLY"), loader::ZEL_DRIVER_TYPE_INTEGRATED_GPU);
    EXPECT_EQ(loader_test::stringToDriverType("NPU"), loader::ZEL_DRIVER_TYPE_NPU);
}

TEST_F(DriverOrderingHelperFunctionsTest, StringToDriverType_InvalidTypes_ShouldReturnForceUint32) {
    // Test invalid driver type strings
    EXPECT_EQ(loader_test::stringToDriverType("INVALID_TYPE"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32);
    EXPECT_EQ(loader_test::stringToDriverType(""), loader::ZEL_DRIVER_TYPE_FORCE_UINT32);
    EXPECT_EQ(loader_test::stringToDriverType("gpu"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32); // lowercase
    EXPECT_EQ(loader_test::stringToDriverType("discrete_gpu"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32); // wrong format
    EXPECT_EQ(loader_test::stringToDriverType("GPU_ONLY"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32); // wrong suffix
}

TEST_F(DriverOrderingHelperFunctionsTest, StringToDriverType_CaseSensitivity_ShouldBeStrict) {
    // Test case sensitivity
    EXPECT_EQ(loader_test::stringToDriverType("npu"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32);
    EXPECT_EQ(loader_test::stringToDriverType("Npu"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32);
    EXPECT_EQ(loader_test::stringToDriverType("NPu"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32);
    EXPECT_EQ(loader_test::stringToDriverType("discrete_gpu_only"), loader::ZEL_DRIVER_TYPE_FORCE_UINT32);
}

///////////////////////////////////////////////////////////////////////////////
// Tests for trim function
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingHelperFunctionsTest, Trim_NoWhitespace_ShouldReturnOriginal) {
    EXPECT_EQ(loader_test::trim("NPU"), "NPU");
    EXPECT_EQ(loader_test::trim("DISCRETE_GPU_ONLY"), "DISCRETE_GPU_ONLY");
    EXPECT_EQ(loader_test::trim("123"), "123");
}

TEST_F(DriverOrderingHelperFunctionsTest, Trim_LeadingWhitespace_ShouldRemove) {
    EXPECT_EQ(loader_test::trim(" NPU"), "NPU");
    EXPECT_EQ(loader_test::trim("  NPU"), "NPU");
    EXPECT_EQ(loader_test::trim("\tNPU"), "NPU");
    EXPECT_EQ(loader_test::trim("\nNPU"), "NPU");
    EXPECT_EQ(loader_test::trim("\r\n NPU"), "NPU");
}

TEST_F(DriverOrderingHelperFunctionsTest, Trim_TrailingWhitespace_ShouldRemove) {
    EXPECT_EQ(loader_test::trim("NPU "), "NPU");
    EXPECT_EQ(loader_test::trim("NPU  "), "NPU");
    EXPECT_EQ(loader_test::trim("NPU\t"), "NPU");
    EXPECT_EQ(loader_test::trim("NPU\n"), "NPU");
    EXPECT_EQ(loader_test::trim("NPU \r\n"), "NPU");
}

TEST_F(DriverOrderingHelperFunctionsTest, Trim_BothSidesWhitespace_ShouldRemove) {
    EXPECT_EQ(loader_test::trim(" NPU "), "NPU");
    EXPECT_EQ(loader_test::trim("  NPU  "), "NPU");
    EXPECT_EQ(loader_test::trim("\t NPU \t"), "NPU");
    EXPECT_EQ(loader_test::trim("\n\r NPU \r\n"), "NPU");
}

TEST_F(DriverOrderingHelperFunctionsTest, Trim_OnlyWhitespace_ShouldReturnEmpty) {
    EXPECT_EQ(loader_test::trim(""), "");
    EXPECT_EQ(loader_test::trim(" "), "");
    EXPECT_EQ(loader_test::trim("  "), "");
    EXPECT_EQ(loader_test::trim("\t"), "");
    EXPECT_EQ(loader_test::trim("\n"), "");
    EXPECT_EQ(loader_test::trim("\r\n\t "), "");
}

TEST_F(DriverOrderingHelperFunctionsTest, Trim_MiddleWhitespace_ShouldKeep) {
    EXPECT_EQ(loader_test::trim("DISCRETE GPU ONLY"), "DISCRETE GPU ONLY");
    EXPECT_EQ(loader_test::trim(" DISCRETE GPU ONLY "), "DISCRETE GPU ONLY");
}

///////////////////////////////////////////////////////////////////////////////
// Tests for parseDriverOrder function
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_EmptyString_ShouldReturnEmpty) {
    auto specs = loader_test::parseDriverOrder("");
    EXPECT_TRUE(specs.empty());
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_SingleGlobalIndex_ShouldParseCorrectly) {
    auto specs = loader_test::parseDriverOrder("2");
    ASSERT_EQ(specs.size(), 1);
    EXPECT_EQ(specs[0].type, loader_test::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[0].globalIndex, 2);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_MultipleGlobalIndices_ShouldParseCorrectly) {
    auto specs = loader_test::parseDriverOrder("2,0,1");
    ASSERT_EQ(specs.size(), 3);
    
    EXPECT_EQ(specs[0].type, loader_test::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[0].globalIndex, 2);
    
    EXPECT_EQ(specs[1].type, loader_test::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[1].globalIndex, 0);
    
    EXPECT_EQ(specs[2].type, loader_test::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[2].globalIndex, 1);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_SingleDriverType_ShouldParseCorrectly) {
    auto specs = loader_test::parseDriverOrder("NPU");
    ASSERT_EQ(specs.size(), 1);
    EXPECT_EQ(specs[0].type, loader_test::BY_TYPE);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_MultipleDriverTypes_ShouldParseCorrectly) {
    auto specs = loader_test::parseDriverOrder("NPU,DISCRETE_GPU_ONLY,GPU");
    ASSERT_EQ(specs.size(), 3);
    
    EXPECT_EQ(specs[0].type, loader_test::BY_TYPE);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    
    EXPECT_EQ(specs[1].type, loader_test::BY_TYPE);
    EXPECT_EQ(specs[1].driverType, loader::ZEL_DRIVER_TYPE_DISCRETE_GPU);
    
    EXPECT_EQ(specs[2].type, loader_test::BY_TYPE);
    EXPECT_EQ(specs[2].driverType, loader::ZEL_DRIVER_TYPE_GPU);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_DriverTypeWithIndex_ShouldParseCorrectly) {
    auto specs = loader_test::parseDriverOrder("NPU:1");
    ASSERT_EQ(specs.size(), 1);
    EXPECT_EQ(specs[0].type, loader_test::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 1);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_MultipleDriverTypesWithIndices_ShouldParseCorrectly) {
    auto specs = loader_test::parseDriverOrder("NPU:1,DISCRETE_GPU_ONLY:0,GPU:2");
    ASSERT_EQ(specs.size(), 3);
    
    EXPECT_EQ(specs[0].type, loader_test::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 1);
    
    EXPECT_EQ(specs[1].type, loader_test::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[1].driverType, loader::ZEL_DRIVER_TYPE_DISCRETE_GPU);
    EXPECT_EQ(specs[1].typeIndex, 0);
    
    EXPECT_EQ(specs[2].type, loader_test::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[2].driverType, loader::ZEL_DRIVER_TYPE_GPU);
    EXPECT_EQ(specs[2].typeIndex, 2);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_MixedSyntax_ShouldParseCorrectly) {
    auto specs = loader_test::parseDriverOrder("NPU:1,2,GPU,0");
    ASSERT_EQ(specs.size(), 4);
    
    EXPECT_EQ(specs[0].type, loader_test::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 1);
    
    EXPECT_EQ(specs[1].type, loader_test::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[1].globalIndex, 2);
    
    EXPECT_EQ(specs[2].type, loader_test::BY_TYPE);
    EXPECT_EQ(specs[2].driverType, loader::ZEL_DRIVER_TYPE_GPU);
    
    EXPECT_EQ(specs[3].type, loader_test::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[3].globalIndex, 0);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_WithWhitespace_ShouldTrimAndParseCorrectly) {
    auto specs = loader_test::parseDriverOrder(" NPU : 1 , 2 , GPU ");
    ASSERT_EQ(specs.size(), 3);
    
    EXPECT_EQ(specs[0].type, loader_test::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 1);
    
    EXPECT_EQ(specs[1].type, loader_test::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[1].globalIndex, 2);
    
    EXPECT_EQ(specs[2].type, loader_test::BY_TYPE);
    EXPECT_EQ(specs[2].driverType, loader::ZEL_DRIVER_TYPE_GPU);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_InvalidEntries_ShouldSkipInvalid) {
    auto specs = loader_test::parseDriverOrder("NPU:1,INVALID_TYPE,abc,GPU:xyz,2");
    ASSERT_EQ(specs.size(), 2);
    
    EXPECT_EQ(specs[0].type, loader_test::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 1);
    
    EXPECT_EQ(specs[1].type, loader_test::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[1].globalIndex, 2);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_EmptyTokens_ShouldSkipEmpty) {
    auto specs = loader_test::parseDriverOrder("NPU,,2,,,GPU");
    ASSERT_EQ(specs.size(), 3);
    
    EXPECT_EQ(specs[0].type, loader_test::BY_TYPE);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    
    EXPECT_EQ(specs[1].type, loader_test::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[1].globalIndex, 2);
    
    EXPECT_EQ(specs[2].type, loader_test::BY_TYPE);
    EXPECT_EQ(specs[2].driverType, loader::ZEL_DRIVER_TYPE_GPU);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_ColonWithoutIndex_ShouldSkip) {
    auto specs = loader_test::parseDriverOrder("NPU:,GPU:");
    EXPECT_TRUE(specs.empty());
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_OnlyCommas_ShouldReturnEmpty) {
    auto specs = loader_test::parseDriverOrder(",,,,");
    EXPECT_TRUE(specs.empty());
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_InvalidIndexes_ShouldSkipInvalidOnes) {
    auto specs = loader_test::parseDriverOrder("NPU:0,GPU:abc,DISCRETE_GPU_ONLY:999999999999999999999");
    ASSERT_EQ(specs.size(), 1); // Only NPU:0 should be valid
    
    EXPECT_EQ(specs[0].type, loader_test::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 0);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_LargeValidIndex_ShouldParseCorrectly) {
    auto specs = loader_test::parseDriverOrder("NPU:4294967295"); // Max uint32_t
    ASSERT_EQ(specs.size(), 1);
    
    EXPECT_EQ(specs[0].type, loader_test::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 4294967295u);
}

///////////////////////////////////////////////////////////////////////////////
// Integration tests for the parsing functionality
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_RealWorldExamples_ShouldParseCorrectly) {
    // Documentation Example 1: DISCRETE_GPU_ONLY:1,NPU
    auto specs = loader_test::parseDriverOrder("DISCRETE_GPU_ONLY:1,NPU");
    ASSERT_EQ(specs.size(), 2);
    
    EXPECT_EQ(specs[0].type, loader_test::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_DISCRETE_GPU);
    EXPECT_EQ(specs[0].typeIndex, 1);
    
    EXPECT_EQ(specs[1].type, loader_test::BY_TYPE);
    EXPECT_EQ(specs[1].driverType, loader::ZEL_DRIVER_TYPE_NPU);
}

TEST_F(DriverOrderingHelperFunctionsTest, ParseDriverOrder_ComplexScenario_ShouldParseCorrectly) {
    // Complex example: "NPU:0,2,GPU,0,DISCRETE_GPU_ONLY:1"
    auto specs = loader_test::parseDriverOrder("NPU:0,2,GPU,0,DISCRETE_GPU_ONLY:1");
    ASSERT_EQ(specs.size(), 5);
    
    EXPECT_EQ(specs[0].type, loader_test::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[0].driverType, loader::ZEL_DRIVER_TYPE_NPU);
    EXPECT_EQ(specs[0].typeIndex, 0);
    
    EXPECT_EQ(specs[1].type, loader_test::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[1].globalIndex, 2);
    
    EXPECT_EQ(specs[2].type, loader_test::BY_TYPE);
    EXPECT_EQ(specs[2].driverType, loader::ZEL_DRIVER_TYPE_GPU);
    
    EXPECT_EQ(specs[3].type, loader_test::BY_GLOBAL_INDEX);
    EXPECT_EQ(specs[3].globalIndex, 0);
    
    EXPECT_EQ(specs[4].type, loader_test::BY_TYPE_AND_INDEX);
    EXPECT_EQ(specs[4].driverType, loader::ZEL_DRIVER_TYPE_DISCRETE_GPU);
    EXPECT_EQ(specs[4].typeIndex, 1);
}
