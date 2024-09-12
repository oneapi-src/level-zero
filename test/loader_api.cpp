/*
 *
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"

#include "loader/ze_loader.h"
#include "ze_api.h"

#if defined(_WIN32)
    #define putenv_safe _putenv
#else
    #define putenv_safe putenv
#endif

namespace {

TEST(
    LoaderAPI,
    GivenLevelZeroLoaderPresentWhenCallingzeGetLoaderVersionsAPIThenValidVersionIsReturned) {

  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));

  size_t size = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderGetVersions(&size, nullptr));
  EXPECT_GT(size, 0);

  std::vector<zel_component_version_t> versions(size);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderGetVersions(&size, versions.data()));

  std::cout << "Found " << versions.size() << " versions" << std::endl;
  std::cout << std::endl;
  const std::string loader_name = "loader";
  for (auto &component : versions) {
    std::cout << "component.component_name: " << component.component_name << std::endl;
    std::cout << "component.component_lib_version.major: " << component.component_lib_version.major << std::endl;
    std::cout << "component.spec_version: " << component.spec_version << std::endl;
    std::cout << "component.component_lib_name: " << component.component_name << std::endl;
    std::cout << std::endl;

    if (loader_name == component.component_name) {
      EXPECT_GE(component.component_lib_version.major, 1);
    }
  }
}

TEST(
    LoaderAPI,
    GivenLevelZeroLoaderPresentWhenCallingZeInitDriversWithGPUTypeThenExpectPassWithGPUorAllOnly) {

  uint32_t pCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=GPU" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  desc.flags = UINT32_MAX;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU | ZE_INIT_DRIVER_TYPE_FLAG_NPU;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
}

TEST(
    LoaderAPI,
    GivenLevelZeroLoaderPresentWhenCallingZeInitDriversWithNPUTypeThenExpectPassWithNPUorAllOnly) {

  uint32_t pCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_NPU;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=NPU" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  desc.flags = UINT32_MAX;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU | ZE_INIT_DRIVER_TYPE_FLAG_NPU;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
}

TEST(
    LoaderAPI,
    GivenLevelZeroLoaderPresentWhenCallingZeInitDriversWithAnyTypeWithNullDriverAcceptingAllThenExpectatLeast1Driver) {

  uint32_t pCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_NPU;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=ALL" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  desc.flags = UINT32_MAX;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU | ZE_INIT_DRIVER_TYPE_FLAG_NPU;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
}

TEST(
    LoaderAPI,
    GivenLevelZeroLoaderPresentWhenCallingZeInitDriversThenzeInitThenBothCallsSucceedWithAllTypes) {

  uint32_t pCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=ALL" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
}

TEST(
    LoaderAPI,
    GivenLevelZeroLoaderPresentWhenCallingZeInitDriversThenzeInitThenBothCallsSucceedWithGPUTypes) {

  uint32_t pCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=GPU" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_GPU_ONLY));
}

TEST(
    LoaderAPI,
    GivenLevelZeroLoaderPresentWhenCallingZeInitDriversThenzeInitThenBothCallsSucceedWithNPUTypes) {

  uint32_t pCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=NPU" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_VPU_ONLY));
}

TEST(
    LoaderAPI,
    GivenLevelZeroLoaderPresentWhenCallingzeInitThenZeInitDriversThenBothCallsSucceedWithAllTypes) {

  uint32_t pCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=ALL" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
}

TEST(
    LoaderAPI,
    GivenLevelZeroLoaderPresentWhenCallingzeInitThenZeInitDriversThenBothCallsSucceedWithGPUTypes) {

  uint32_t pCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=GPU" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_GPU_ONLY));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
}

TEST(
    LoaderAPI,
    GivenLevelZeroLoaderPresentWhenCallingzeInitThenZeInitDriversThenBothCallsSucceedWithNPUTypes) {

  uint32_t pCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=NPU" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_VPU_ONLY));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
}

TEST(
    LoaderAPI,
    GivenLevelZeroLoaderPresentWhenCallingzeInitThenZeInitDriversThenOnlyOneSucceedsforGPUTypes) {

  uint32_t pCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=GPU" ) );
  EXPECT_EQ(ZE_RESULT_ERROR_UNINITIALIZED, zeInit(ZE_INIT_FLAG_VPU_ONLY));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
}

TEST(
    LoaderAPI,
    GivenLevelZeroLoaderPresentWhenCallingzeInitThenZeInitDriversThenOnlyOneSucceedsforNPUTypes) {

  uint32_t pCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=NPU" ) );
  EXPECT_EQ(ZE_RESULT_ERROR_UNINITIALIZED, zeInit(ZE_INIT_FLAG_GPU_ONLY));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
}

} // namespace
