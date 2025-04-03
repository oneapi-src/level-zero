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
#include "zes_api.h"

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
    LoaderInit,
    GivenLevelZeroLoaderPresentWhenCallingZeInitDriversWithTypesUnsupportedWithFailureThenSupportedTypesThenSuccessReturned) {

  uint32_t pCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_NPU;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=GPU" ) );
  EXPECT_EQ(ZE_RESULT_ERROR_UNINITIALIZED, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_EQ(pCount, 0);
  pCount = 0;
  desc.flags = UINT32_MAX;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
}

TEST(
    LoaderInit,
    GivenLevelZeroLoaderPresentWhenCallingZeInitDriversWithGPUTypeThenExpectPassWithGPUorAllOnly) {

  uint32_t pCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=GPU" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  pCount = 0;
  desc.flags = UINT32_MAX;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  pCount = 0;
  desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU | ZE_INIT_DRIVER_TYPE_FLAG_NPU;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
}

TEST(
    LoaderInit,
    GivenLevelZeroLoaderPresentWhenCallingZeInitDriversWithNPUTypeThenExpectPassWithNPUorAllOnly) {

  uint32_t pCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_NPU;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=NPU" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  pCount = 0;
  desc.flags = UINT32_MAX;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  pCount = 0;
  desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU | ZE_INIT_DRIVER_TYPE_FLAG_NPU;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
}

TEST(
    LoaderInit,
    GivenLevelZeroLoaderPresentWhenCallingZeInitDriversWithAnyTypeWithNullDriverAcceptingAllThenExpectatLeast1Driver) {

  uint32_t pCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_NPU;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=ALL" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  pCount = 0;
  desc.flags = UINT32_MAX;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  pCount = 0;
  desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
  pCount = 0;
  desc.flags = ZE_INIT_DRIVER_TYPE_FLAG_GPU | ZE_INIT_DRIVER_TYPE_FLAG_NPU;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
  EXPECT_GT(pCount, 0);
}

TEST(
    LoaderInit,
    GivenLevelZeroLoaderPresentWhenCallingZeInitDriversThenzeInitThenBothCallsSucceedWithAllTypes) {

  uint32_t pInitDriversCount = 0;
  uint32_t pDriverGetCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=ALL" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
  EXPECT_GT(pInitDriversCount, 0);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&pDriverGetCount, nullptr));
  EXPECT_GT(pDriverGetCount, 0);
}

TEST(
    LoaderInit,
    GivenLevelZeroLoaderPresentWhenCallingZeInitDriversThenzeInitThenBothCallsSucceedWithGPUTypes) {

  uint32_t pInitDriversCount = 0;
  uint32_t pDriverGetCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=GPU" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
  EXPECT_GT(pInitDriversCount, 0);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_GPU_ONLY));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&pDriverGetCount, nullptr));
  EXPECT_GT(pDriverGetCount, 0);
}

TEST(
    LoaderInit,
    GivenZeInitDriversUnsupportedOnTheDriverWhenCallingZeInitDriversThenUninitializedReturned) {

  uint32_t pInitDriversCount = 0;
  uint32_t pDriverGetCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_MISSING_API=zeInitDrivers" ) );
  EXPECT_EQ(ZE_RESULT_ERROR_UNINITIALIZED, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
  EXPECT_EQ(pInitDriversCount, 0);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&pDriverGetCount, nullptr));
  EXPECT_GT(pDriverGetCount, 0);
}

TEST(
    LoaderInit,
    GivenLevelZeroLoaderPresentWhenCallingZeInitDriversThenzeInitThenBothCallsSucceedWithNPUTypes) {

  uint32_t pInitDriversCount = 0;
  uint32_t pDriverGetCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=NPU" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
  EXPECT_GT(pInitDriversCount, 0);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_VPU_ONLY));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&pDriverGetCount, nullptr));
  EXPECT_GT(pDriverGetCount, 0);
}

TEST(
    LoaderInit,
    GivenLevelZeroLoaderPresentWhenCallingzeInitThenZeInitDriversThenBothCallsSucceedWithAllTypes) {

  uint32_t pInitDriversCount = 0;
  uint32_t pDriverGetCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=ALL" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
  EXPECT_GT(pInitDriversCount, 0);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&pDriverGetCount, nullptr));
  EXPECT_GT(pDriverGetCount, 0);
}

TEST(
    LoaderInit,
    GivenLevelZeroLoaderPresentWhenCallingzeInitThenZeInitDriversThenBothCallsSucceedWithGPUTypes) {

  uint32_t pInitDriversCount = 0;
  uint32_t pDriverGetCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=GPU" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_GPU_ONLY));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
  EXPECT_GT(pInitDriversCount, 0);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&pDriverGetCount, nullptr));
  EXPECT_GT(pDriverGetCount, 0);
}

TEST(
    LoaderInit,
    GivenLevelZeroLoaderPresentWhenCallingzeInitThenZeInitDriversThenBothCallsSucceedWithNPUTypes) {

  uint32_t pInitDriversCount = 0;
  uint32_t pDriverGetCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_TYPE=NPU" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(ZE_INIT_FLAG_VPU_ONLY));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
  EXPECT_GT(pInitDriversCount, 0);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&pDriverGetCount, nullptr));
  EXPECT_GT(pDriverGetCount, 0);
}

TEST(
  LoaderInit,
  GivenLevelZeroLoaderPresentWithMultipleDriversMissingInitDriversWhenCallingZeInitDriversThenExpectSuccessForZeInit) {

  uint32_t pInitDriversCount = 0;
  uint32_t pDriverGetCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_MISSING_API=zeInitDrivers" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&pDriverGetCount, nullptr));
  EXPECT_GT(pDriverGetCount, 0);
  EXPECT_EQ(ZE_RESULT_ERROR_UNINITIALIZED, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
  EXPECT_EQ(pInitDriversCount, 0);
}

TEST(
  LoaderInit,
  GivenLevelZeroLoaderPresentWithMultipleDriversMissingInitDriversWhenCallingZeInitDriversThenExpectSuccessForZeInitWithDriverGetAfterInitDrivers) {

  uint32_t pInitDriversCount = 0;
  uint32_t pDriverGetCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_MISSING_API=zeInitDrivers" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
  EXPECT_EQ(ZE_RESULT_ERROR_UNINITIALIZED, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
  EXPECT_EQ(pInitDriversCount, 0);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&pDriverGetCount, nullptr));
  EXPECT_GT(pDriverGetCount, 0);
}

TEST(
  LoaderInit,
  GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingZeInitDriversThenExpectSuccessForZeInit) {

  uint32_t pInitDriversCount = 0;
  uint32_t pDriverGetCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
  EXPECT_GT(pInitDriversCount, 0);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&pDriverGetCount, nullptr));
  EXPECT_GT(pDriverGetCount, 0);
}

TEST(
  LoaderInit,
  GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingZeInitThenZeInitDriversThenExpectSuccessForZeInitWithDriverGetAfterInitDrivers) {

  uint32_t pInitDriversCount = 0;
  uint32_t pDriverGetCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
  EXPECT_GT(pInitDriversCount, 0);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&pDriverGetCount, nullptr));
  EXPECT_GT(pDriverGetCount, 0);
}

TEST(
  LoaderInit,
  GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingZesInitThenExpectSuccessForZesDriverGet) {

  uint32_t pDriverGetCount = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zesInit(0));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zesDriverGet(&pDriverGetCount, nullptr));
  EXPECT_GT(pDriverGetCount, 0);
}

TEST(
  LoaderInit,
  GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingZesInitThenZeInitDriversExpectSuccessForZesDriverGetAndZeInitDrivers) {

  uint32_t pInitDriversCount = 0;
  uint32_t pDriverGetCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zesInit(0));
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
  EXPECT_GT(pInitDriversCount, 0);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zesDriverGet(&pDriverGetCount, nullptr));
  EXPECT_GT(pDriverGetCount, 0);
}

TEST(
  LoaderTearDown,
  GivenLoaderNotInDestructionStateWhenCallingzelCheckIsLoaderInTearDownThenFalseIsReturned) {

  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
  EXPECT_FALSE(zelCheckIsLoaderInTearDown());
}

} // namespace
