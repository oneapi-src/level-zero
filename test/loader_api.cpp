/*
 *
 * Copyright (C) 2024-2025 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"

#include "loader/ze_loader.h"
#include "ze_api.h"
#include "zes_api.h"
#include "zer_api.h"

#include <fstream>

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
    #define _dup dup
    #define _dup2 dup2
    #define _close close
    #define putenv_safe putenv
#endif

namespace {

  inline std::string getenv_string(const char *name)
  {

    const char *env = nullptr;
#if defined(_WIN32)
    char buffer[1024];
    auto rc = GetEnvironmentVariable(name, buffer, 1024);
    if (0 != rc && rc <= 1024)
    {
      env = buffer;
    }
#else
    env = getenv(name);
#endif

    if ((nullptr == env))
      return "";
    return std::string(env);
  }

  bool compare_env(const char *api, std::string value)
  {
    auto val = getenv_string(api);
    if (strcmp(val.c_str(), value.c_str()) == 0)
    {
      return true;
    }
    return false;
  }

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
    GivenZeInitDriversUnsupportedOnTheDriverWhenCallingZeInitDriversThenUnSupportedReturned) {

  uint32_t pInitDriversCount = 0;
  uint32_t pDriverGetCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_MISSING_API=zeInitDrivers" ) );
  EXPECT_EQ(ZE_RESULT_ERROR_UNSUPPORTED_FEATURE, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
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
  GivenLevelZeroLoaderPresentWithMultipleDriversMissingInitDriversInOneDriverWhenCallingZeInitDriversThenExpectSuccessForZeInitDrivers) {

  uint32_t pInitDriversCount = 0;
  ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
  desc.flags = UINT32_MAX;
  desc.pNext = nullptr;
  putenv_safe( const_cast<char *>( "ZEL_TEST_MISSING_API_DRIVER_ID=zeInitDrivers:1" ) );
  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
  EXPECT_GT(pInitDriversCount, 0);
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
  EXPECT_FALSE(zelCheckIsLoaderInTearDown());
  EXPECT_FALSE(zelCheckIsLoaderInTearDown());
  EXPECT_FALSE(zelCheckIsLoaderInTearDown());
}

class CaptureOutput {
private:
    int original_fd;
    int fd;
    int stream;
    char filename[50] = "/tmp/capture_output_XXXXXX";

public:
    enum { Stdout = 1, Stderr = 2 };

    CaptureOutput(int stream_) : stream(stream_) {
        original_fd = _dup(stream);
#if defined(__linux__)
        fd = mkstemp(filename);
#elif defined(_WIN32)
        tmpnam_s(filename, sizeof(filename));
        _sopen_s(&fd, filename, _O_CREAT | _O_RDWR, _SH_DENYNO, _S_IREAD | _S_IWRITE);
#endif
        fflush(nullptr);
        _dup2(fd, stream);
        _close(fd);
    }

    ~CaptureOutput() {
        if (original_fd != -1) {
            fflush(nullptr);
            _dup2(original_fd, stream);
            _close(original_fd);
            original_fd = -1;
        }
        if (remove(filename) != 0) {
            std::cerr << "Deleting file " << filename << " failed.";
        }
    }

    std::string GetOutput() {
        if (original_fd != -1) {
            fflush(nullptr);
            _dup2(original_fd, stream);
            _close(original_fd);
            original_fd = -1;
        }
        std::ifstream stream(filename);
        std::string output = std::string((std::istreambuf_iterator<char>(stream)),
            std::istreambuf_iterator<char>());
        return output;
    }
};

TEST(
    LoaderInitDrivers,
    GivenZeInitDriverWhenCalledThenNoOutputIsPrintedToStdout) {
    uint32_t pInitDriversCount = 0;
    ze_init_driver_type_desc_t desc = { ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC };
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    CaptureOutput capture(CaptureOutput::Stdout);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));

    std::string output = capture.GetOutput();
    EXPECT_TRUE(output.empty());
}

TEST(
  LoaderInit,
  GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingDriverGetPropertiesThenExpectSuccess) {

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
    std::vector<ze_driver_handle_t> drivers(pInitDriversCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
    for (uint32_t i = 0; i < pDriverGetCount; ++i) {
      ze_driver_properties_t driverProperties = {ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES};
      EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[i], &driverProperties));
      std::cout << "Driver " << i << " properties:" << std::endl;
      std::cout << "  Driver version: " << driverProperties.driverVersion << std::endl;
      std::cout << "  UUID: ";
      for (auto byte : driverProperties.uuid.id) {
        std::cout << std::hex << static_cast<int>(byte);
      }
      std::cout << std::dec << std::endl;
    }
}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForModule) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1" ) );
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
EXPECT_GT(pInitDriversCount, 0);
std::vector<ze_driver_handle_t> drivers(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
ze_module_handle_t module;
ze_module_desc_t moduleDesc = {ZE_STRUCTURE_TYPE_MODULE_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeModuleCreate(context, devices[0], &moduleDesc, &module, nullptr));
ze_module_handle_t translatedHandle = module;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_MODULE, module, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_NE(translatedHandle, module);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeModuleDestroy(module));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForModule) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
ze_module_handle_t module;
ze_module_desc_t moduleDesc = {ZE_STRUCTURE_TYPE_MODULE_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeModuleCreate(context, devices[0], &moduleDesc, &module, nullptr));
ze_module_handle_t translatedHandle = module;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_MODULE, module, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_EQ(translatedHandle, module);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeModuleDestroy(module));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForModuleBuildLog) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
ze_module_handle_t module;
ze_module_desc_t moduleDesc = {ZE_STRUCTURE_TYPE_MODULE_DESC};
ze_module_build_log_handle_t buildLog;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeModuleCreate(context, devices[0], &moduleDesc, &module, &buildLog));
ze_module_build_log_handle_t translatedHandle = buildLog;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_MODULE_BUILD_LOG, buildLog, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_NE(translatedHandle, buildLog);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeModuleBuildLogDestroy(buildLog));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeModuleDestroy(module));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForModuleBuildLog) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
ze_module_handle_t module;
ze_module_desc_t moduleDesc = {ZE_STRUCTURE_TYPE_MODULE_DESC};
ze_module_build_log_handle_t buildLog;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeModuleCreate(context, devices[0], &moduleDesc, &module, &buildLog));
ze_module_build_log_handle_t translatedHandle = buildLog;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_MODULE_BUILD_LOG, buildLog, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_EQ(translatedHandle, buildLog);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeModuleBuildLogDestroy(buildLog));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeModuleDestroy(module));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForKernel) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
ze_module_handle_t module;
ze_module_desc_t moduleDesc = {ZE_STRUCTURE_TYPE_MODULE_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeModuleCreate(context, devices[0], &moduleDesc, &module, nullptr));
ze_kernel_handle_t kernel;
ze_kernel_desc_t kernelDesc = {ZE_STRUCTURE_TYPE_KERNEL_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeKernelCreate(module, &kernelDesc, &kernel));
ze_kernel_handle_t translatedHandle = kernel;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_KERNEL, kernel, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_NE(translatedHandle, kernel);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeKernelDestroy(kernel));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeModuleDestroy(module));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForKernel) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
ze_module_handle_t module;
ze_module_desc_t moduleDesc = {ZE_STRUCTURE_TYPE_MODULE_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeModuleCreate(context, devices[0], &moduleDesc, &module, nullptr));
ze_kernel_handle_t kernel;
ze_kernel_desc_t kernelDesc = {ZE_STRUCTURE_TYPE_KERNEL_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeKernelCreate(module, &kernelDesc, &kernel));
ze_kernel_handle_t translatedHandle = kernel;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_KERNEL, kernel, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_EQ(translatedHandle, kernel);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeKernelDestroy(kernel));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeModuleDestroy(module));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForSampler) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
ze_sampler_handle_t sampler;
ze_sampler_desc_t samplerDesc = {ZE_STRUCTURE_TYPE_SAMPLER_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeSamplerCreate(context, devices[0], &samplerDesc, &sampler));
ze_sampler_handle_t translatedHandle = sampler;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_SAMPLER, sampler, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_NE(translatedHandle, sampler);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeSamplerDestroy(sampler));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForSampler) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
ze_sampler_handle_t sampler;
ze_sampler_desc_t samplerDesc = {ZE_STRUCTURE_TYPE_SAMPLER_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeSamplerCreate(context, devices[0], &samplerDesc, &sampler));
ze_sampler_handle_t translatedHandle = sampler;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_SAMPLER, sampler, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_EQ(translatedHandle, sampler);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeSamplerDestroy(sampler));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForPhysicalMem) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
ze_physical_mem_handle_t physicalMem;
ze_physical_mem_desc_t physicalMemDesc = {ZE_STRUCTURE_TYPE_PHYSICAL_MEM_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zePhysicalMemCreate(context, devices[0], &physicalMemDesc, &physicalMem));
ze_physical_mem_handle_t translatedHandle = physicalMem;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_PHYSICAL_MEM, physicalMem, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_NE(translatedHandle, physicalMem);
EXPECT_EQ(ZE_RESULT_SUCCESS, zePhysicalMemDestroy(context, physicalMem));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForPhysicalMem) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
ze_physical_mem_handle_t physicalMem;
ze_physical_mem_desc_t physicalMemDesc = {ZE_STRUCTURE_TYPE_PHYSICAL_MEM_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zePhysicalMemCreate(context, devices[0], &physicalMemDesc, &physicalMem));
ze_physical_mem_handle_t translatedHandle = physicalMem;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_PHYSICAL_MEM, physicalMem, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_EQ(translatedHandle, physicalMem);
EXPECT_EQ(ZE_RESULT_SUCCESS, zePhysicalMemDestroy(context, physicalMem));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForFence) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
ze_command_queue_handle_t commandQueue;
ze_command_queue_desc_t commandQueueDesc = {ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC};
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueCreate(context, devices[0], &commandQueueDesc, &commandQueue));
ze_fence_handle_t fence;
ze_fence_desc_t fenceDesc = {ZE_STRUCTURE_TYPE_FENCE_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeFenceCreate(commandQueue, &fenceDesc, &fence));
ze_fence_handle_t translatedHandle = fence;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_FENCE, fence, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_NE(translatedHandle, fence);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeFenceDestroy(fence));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueDestroy(commandQueue));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForFence) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
ze_command_queue_handle_t commandQueue;
ze_command_queue_desc_t commandQueueDesc = {ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC};
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueCreate(context, devices[0], &commandQueueDesc, &commandQueue));
ze_fence_handle_t fence;
ze_fence_desc_t fenceDesc = {ZE_STRUCTURE_TYPE_FENCE_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeFenceCreate(commandQueue, &fenceDesc, &fence));
ze_fence_handle_t translatedHandle = fence;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_FENCE, fence, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_EQ(translatedHandle, fence);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeFenceDestroy(fence));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueDestroy(commandQueue));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForEventPool) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
ze_event_pool_handle_t eventPool;
ze_event_pool_desc_t eventPoolDesc = {ZE_STRUCTURE_TYPE_EVENT_POOL_DESC};
eventPoolDesc.count = 1;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventPoolCreate(context, &eventPoolDesc, 0, nullptr, &eventPool));
ze_event_pool_handle_t translatedHandle = eventPool;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_EVENT_POOL, eventPool, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_NE(translatedHandle, eventPool);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventPoolDestroy(eventPool));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForEventPool) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
ze_event_pool_handle_t eventPool;
ze_event_pool_desc_t eventPoolDesc = {ZE_STRUCTURE_TYPE_EVENT_POOL_DESC};
eventPoolDesc.count = 1;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventPoolCreate(context, &eventPoolDesc, 0, nullptr, &eventPool));
ze_event_pool_handle_t translatedHandle = eventPool;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_EVENT_POOL, eventPool, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_EQ(translatedHandle, eventPool);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventPoolDestroy(eventPool));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForImage) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
ze_image_handle_t image;
ze_image_desc_t imageDesc = {ZE_STRUCTURE_TYPE_IMAGE_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeImageCreate(context, devices[0], &imageDesc, &image));
ze_image_handle_t translatedHandle = image;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_IMAGE, image, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_NE(translatedHandle, image);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeImageDestroy(image));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForImage) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
ze_image_handle_t image;
ze_image_desc_t imageDesc = {ZE_STRUCTURE_TYPE_IMAGE_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeImageCreate(context, devices[0], &imageDesc, &image));
ze_image_handle_t translatedHandle = image;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_IMAGE, image, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_EQ(translatedHandle, image);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeImageDestroy(image));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForContext) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
ze_context_handle_t translatedHandle = context;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_CONTEXT, context, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_NE(translatedHandle, context);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForContext) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
ze_context_handle_t translatedHandle = context;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_CONTEXT, context, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_EQ(translatedHandle, context);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForCommandQueue) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
ze_command_queue_handle_t commandQueue;
ze_command_queue_desc_t commandQueueDesc = {ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC};
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueCreate(context, devices[0], &commandQueueDesc, &commandQueue));
ze_command_queue_handle_t translatedHandle = commandQueue;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_COMMAND_QUEUE, commandQueue, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_NE(translatedHandle, commandQueue);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueDestroy(commandQueue));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForCommandQueue) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
ze_command_queue_handle_t commandQueue;
ze_command_queue_desc_t commandQueueDesc = {ZE_STRUCTURE_TYPE_COMMAND_QUEUE_DESC};
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueCreate(context, devices[0], &commandQueueDesc, &commandQueue));
ze_command_queue_handle_t translatedHandle = commandQueue;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_COMMAND_QUEUE, commandQueue, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_EQ(translatedHandle, commandQueue);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandQueueDestroy(commandQueue));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForCommandList) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
ze_command_list_handle_t commandList;
ze_command_list_desc_t commandListDesc = {ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC};
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListCreate(context, devices[0], &commandListDesc, &commandList));
ze_command_list_handle_t translatedHandle = commandList;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_COMMAND_LIST, commandList, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_NE(translatedHandle, commandList);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListDestroy(commandList));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForCommandList) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
ze_command_list_handle_t commandList;
ze_command_list_desc_t commandListDesc = {ZE_STRUCTURE_TYPE_COMMAND_LIST_DESC};
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListCreate(context, devices[0], &commandListDesc, &commandList));
ze_command_list_handle_t translatedHandle = commandList;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_COMMAND_LIST, commandList, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_EQ(translatedHandle, commandList);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeCommandListDestroy(commandList));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForEvent) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
ze_event_pool_handle_t eventPool;
ze_event_pool_desc_t eventPoolDesc = {ZE_STRUCTURE_TYPE_EVENT_POOL_DESC};
eventPoolDesc.count = 1;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventPoolCreate(context, &eventPoolDesc, 0, nullptr, &eventPool));
ze_event_handle_t event;
ze_event_desc_t eventDesc = {ZE_STRUCTURE_TYPE_EVENT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventCreate(eventPool, &eventDesc, &event));
ze_event_handle_t translatedHandle = event;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_EVENT, event, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_NE(translatedHandle, event);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventDestroy(event));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventPoolDestroy(eventPool));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForEvent) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_context_handle_t context;
ze_context_desc_t contextDesc = {ZE_STRUCTURE_TYPE_CONTEXT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextCreate(drivers[0], &contextDesc, &context));
ze_event_pool_handle_t eventPool;
ze_event_pool_desc_t eventPoolDesc = {ZE_STRUCTURE_TYPE_EVENT_POOL_DESC};
eventPoolDesc.count = 1;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventPoolCreate(context, &eventPoolDesc, 0, nullptr, &eventPool));
ze_event_handle_t event;
ze_event_desc_t eventDesc = {ZE_STRUCTURE_TYPE_EVENT_DESC};
EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventCreate(eventPool, &eventDesc, &event));
ze_event_handle_t translatedHandle = event;
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_EVENT, event, reinterpret_cast<void**>(&translatedHandle)));
EXPECT_EQ(translatedHandle, event);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventDestroy(event));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeEventPoolDestroy(eventPool));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeContextDestroy(context));

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForDriver) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_driver_handle_t translatedHandle = drivers[0];
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_DRIVER, drivers[0], reinterpret_cast<void**>(&translatedHandle)));
EXPECT_NE(translatedHandle, drivers[0]);

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForDriver) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
ze_driver_handle_t translatedHandle = drivers[0];
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_DRIVER, drivers[0], reinterpret_cast<void**>(&translatedHandle)));
EXPECT_EQ(translatedHandle, drivers[0]);

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForDevice) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
ze_device_handle_t translatedHandle = devices[0];
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_DEVICE, devices[0], reinterpret_cast<void**>(&translatedHandle)));
EXPECT_NE(translatedHandle, devices[0]);

}

TEST(
  LoaderTranslateHandles,
  GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForDevice) {

uint32_t pInitDriversCount = 0;
ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
desc.flags = UINT32_MAX;
desc.pNext = nullptr;
putenv_safe( const_cast<char *>( "ZE_ENABLE_LOADER_INTERCEPT=1" ) );
putenv_safe( const_cast<char *>( "ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0" ) );
std::vector<ze_driver_handle_t> drivers;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
drivers.resize(pInitDriversCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
EXPECT_GT(pInitDriversCount, 0);
ze_driver_ddi_handles_ext_properties_t driverDdiHandlesExtProperties = {};
driverDdiHandlesExtProperties.stype = ZE_STRUCTURE_TYPE_DRIVER_DDI_HANDLES_EXT_PROPERTIES;
driverDdiHandlesExtProperties.pNext = nullptr;
ze_driver_properties_t properties = {};
properties.stype = ZE_STRUCTURE_TYPE_DRIVER_PROPERTIES;
properties.pNext = &driverDdiHandlesExtProperties;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGetProperties(drivers[0], &properties));
EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
uint32_t deviceCount = 0;
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, nullptr));
std::vector<ze_device_handle_t> devices(deviceCount);
EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &deviceCount, devices.data()));
ze_device_handle_t translatedHandle = devices[0];
EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderTranslateHandle(ZEL_HANDLE_DEVICE, devices[0], reinterpret_cast<void**>(&translatedHandle)));
EXPECT_EQ(translatedHandle, devices[0]);

}



TEST(
      SysManApiLoaderDriverInteraction,
      GivenLevelZeroLoaderPresentWhenCallingSysManVfApisThenExpectNullDriverIsReachedSuccessfully)
  {
    EXPECT_EQ(ZE_RESULT_SUCCESS, zesInit(0));
    uint32_t driverCount = 0;
    std::vector<zes_driver_handle_t> driverHandles{};
    EXPECT_EQ(ZE_RESULT_SUCCESS, zesDriverGet(&driverCount, nullptr));
    EXPECT_GT(driverCount, 0);
    driverHandles.resize(driverCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zesDriverGet(&driverCount, driverHandles.data()));

    for (std::size_t i = 0; i < driverHandles.size(); i++)
    {
      uint32_t deviceCount = 1;
      zes_device_handle_t deviceHandle{};
      uint32_t count = 1;
      zes_vf_handle_t vfHandle{};
      zes_vf_exp_properties_t vf_properties{};
      zes_vf_util_mem_exp_t util_mem_exp{};
      zes_vf_util_mem_exp2_t util_mem_exp2{};
      zes_vf_util_engine_exp_t util_engine_exp{};
      zes_vf_util_engine_exp2_t util_engine_exp2{};
      zes_vf_exp_capabilities_t vf_exp_capabilities{};
      zes_vf_exp2_capabilities_t vf_exp2_capabilities{};

      EXPECT_EQ(ZE_RESULT_SUCCESS, zesDeviceGet(driverHandles[i], &deviceCount, &deviceHandle));
      EXPECT_TRUE(compare_env("zesDeviceGet", std::to_string(i + 1)));
      EXPECT_EQ(ZE_RESULT_SUCCESS, zesDeviceEnumActiveVFExp(deviceHandle, &count, &vfHandle));
      EXPECT_TRUE(compare_env("zesDeviceEnumActiveVFExp", std::to_string(i + 1)));
      EXPECT_EQ(ZE_RESULT_SUCCESS, zesVFManagementGetVFPropertiesExp(vfHandle, &vf_properties));
      EXPECT_TRUE(compare_env("zesVFManagementGetVFPropertiesExp", std::to_string(i + 1)));
      EXPECT_EQ(ZE_RESULT_SUCCESS, zesVFManagementGetVFMemoryUtilizationExp(vfHandle, &count, &util_mem_exp));
      EXPECT_TRUE(compare_env("zesVFManagementGetVFMemoryUtilizationExp", std::to_string(i + 1)));
      EXPECT_EQ(ZE_RESULT_SUCCESS, zesVFManagementGetVFEngineUtilizationExp(vfHandle, &count, &util_engine_exp));
      EXPECT_TRUE(compare_env("zesVFManagementGetVFEngineUtilizationExp", std::to_string(i + 1)));
      EXPECT_EQ(ZE_RESULT_SUCCESS, zesVFManagementSetVFTelemetryModeExp(vfHandle, 0, 0));
      EXPECT_TRUE(compare_env("zesVFManagementSetVFTelemetryModeExp", std::to_string(i + 1)));
      EXPECT_EQ(ZE_RESULT_SUCCESS, zesVFManagementSetVFTelemetrySamplingIntervalExp(vfHandle, 0, 0));
      EXPECT_TRUE(compare_env("zesVFManagementSetVFTelemetrySamplingIntervalExp", std::to_string(i + 1)));
      EXPECT_EQ(ZE_RESULT_SUCCESS, zesDeviceEnumEnabledVFExp(deviceHandle, &count, &vfHandle));
      EXPECT_TRUE(compare_env("zesDeviceEnumEnabledVFExp", std::to_string(i + 1)));
      EXPECT_EQ(ZE_RESULT_SUCCESS, zesVFManagementGetVFCapabilitiesExp(vfHandle, &vf_exp_capabilities));
      EXPECT_TRUE(compare_env("zesVFManagementGetVFCapabilitiesExp", std::to_string(i + 1)));
      EXPECT_EQ(ZE_RESULT_SUCCESS, zesVFManagementGetVFMemoryUtilizationExp2(vfHandle, &count, &util_mem_exp2));
      EXPECT_TRUE(compare_env("zesVFManagementGetVFMemoryUtilizationExp2", std::to_string(i + 1)));
      EXPECT_EQ(ZE_RESULT_SUCCESS, zesVFManagementGetVFEngineUtilizationExp2(vfHandle, &count, &util_engine_exp2));
      EXPECT_TRUE(compare_env("zesVFManagementGetVFEngineUtilizationExp2", std::to_string(i + 1)));
      EXPECT_EQ(ZE_RESULT_SUCCESS, zesVFManagementGetVFCapabilitiesExp2(vfHandle, &vf_exp2_capabilities));
      EXPECT_TRUE(compare_env("zesVFManagementGetVFCapabilitiesExp2", std::to_string(i + 1)));
    }
  }

// Helper function to clear ZEL_DRIVERS_ORDER environment variable
void clearDriverOrderEnv() {
    putenv_safe(const_cast<char *>("ZEL_DRIVERS_ORDER="));
}

// Helper function to set ZEL_DRIVERS_ORDER environment variable
void setDriverOrderEnv(const std::string& order) {
    // Use static storage to ensure the string persists after the function returns
    // This is necessary because putenv() stores a pointer to the string, not a copy
    static std::string env_var_storage;
    env_var_storage = "ZEL_DRIVERS_ORDER=" + order;
    putenv_safe(const_cast<char *>(env_var_storage.c_str()));
}

// Test Class for Driver Ordering Tests
class DriverOrderingTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Clear any existing environment variables
        clearDriverOrderEnv();
        putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_TYPE=ALL"));
        putenv_safe(const_cast<char *>("ZE_ENABLE_LOADER_INTERCEPT=1"));
    }

    void TearDown() override {
        // Clean up environment variables
        clearDriverOrderEnv();
        putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_TYPE="));
        putenv_safe(const_cast<char *>("ZE_ENABLE_LOADER_INTERCEPT="));
    }
};

///////////////////////////////////////////////////////////////////////////////
// Tests for ZEL_DRIVERS_ORDER: Syntax 1 - Specific type and index within that type
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithSpecificTypeAndIndexWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test case: DISCRETE_GPU_ONLY:1,NPU
    setDriverOrderEnv("DISCRETE_GPU_ONLY:1,NPU");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithGpuTypeAndIndexWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test case: GPU:1,NPU:0
    setDriverOrderEnv("GPU:1,NPU:0");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithIntegratedGpuTypeAndIndexWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test case: INTEGRATED_GPU_ONLY:0,DISCRETE_GPU_ONLY:0
    setDriverOrderEnv("INTEGRATED_GPU_ONLY:0,DISCRETE_GPU_ONLY:0");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithNpuTypeAndIndexWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test case: NPU:0,GPU:0
    setDriverOrderEnv("NPU:0,GPU:0");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Tests for ZEL_DRIVERS_ORDER: Syntax 2 - Specific type only
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithSpecificTypeOnlyWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test case: NPU,DISCRETE_GPU_ONLY
    setDriverOrderEnv("NPU,DISCRETE_GPU_ONLY");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithGpuTypeOnlyWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test case: GPU,NPU
    setDriverOrderEnv("GPU,NPU");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithIntegratedGpuTypeOnlyWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test case: INTEGRATED_GPU_ONLY,DISCRETE_GPU_ONLY,NPU
    setDriverOrderEnv("INTEGRATED_GPU_ONLY,DISCRETE_GPU_ONLY,NPU");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithSingleNpuTypeWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test case: NPU (equivalent to example 4 in documentation)
    setDriverOrderEnv("NPU");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Tests for ZEL_DRIVERS_ORDER: Syntax 3 - Global driver index only
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithGlobalIndexOnlyWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test case: 2,0 (equivalent to example 2 in documentation)
    setDriverOrderEnv("2,0");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithSingleGlobalIndexWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test case: 1
    setDriverOrderEnv("1");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithMultipleGlobalIndicesWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test case: 1,2,0
    setDriverOrderEnv("1,2,0");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Tests for ZEL_DRIVERS_ORDER: Mixed syntax combinations
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithMixedSyntaxWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test case: NPU:0,2,GPU,0 (mixed syntax)
    setDriverOrderEnv("NPU:0,2,GPU,0");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithMixedTypeAndIndexSyntaxWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test case: DISCRETE_GPU_ONLY:1,1,INTEGRATED_GPU_ONLY (type:index, global index, type)
    setDriverOrderEnv("DISCRETE_GPU_ONLY:1,1,INTEGRATED_GPU_ONLY");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Tests for ZEL_DRIVERS_ORDER: Edge cases and error handling
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithInvalidDriverTypeWhenCallingZeInitDriversThenDriversStillInitialize) {

    // Test case: INVALID_TYPE,NPU
    setDriverOrderEnv("INVALID_TYPE,NPU");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Should still get drivers back despite invalid type
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithInvalidIndexWhenCallingZeInitDriversThenDriversStillInitialize) {

    // Test case: NPU:999,GPU:abc
    setDriverOrderEnv("NPU:999,GPU:abc");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Should still get drivers back despite invalid indices
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithEmptyStringWhenCallingZeInitDriversThenDriversUseDefaultOrder) {

    // Test case: empty string
    setDriverOrderEnv("");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Should get drivers back in default order
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithWhitespaceAndCommasWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test case: " NPU : 0 , GPU , 1 " (whitespace handling)
    setDriverOrderEnv(" NPU : 0 , GPU , 1 ");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Should handle whitespace correctly
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithDuplicateEntriesWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test case: GPU,GPU,NPU,NPU (duplicates)
    setDriverOrderEnv("GPU,GPU,NPU,NPU");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Should handle duplicates gracefully
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Tests for ZEL_DRIVERS_ORDER: Compatibility with zeInit
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithzeInitWhenCallingzeInitThenSuccessfulReturn) {

    // Test ZEL_DRIVERS_ORDER compatibility with zeInit
    setDriverOrderEnv("NPU,GPU");

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));

    uint32_t pDriverGetCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&pDriverGetCount, nullptr));
    EXPECT_GT(pDriverGetCount, 0);

    std::vector<ze_driver_handle_t> drivers(pDriverGetCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&pDriverGetCount, drivers.data()));

    // Verify that we got drivers back
    EXPECT_GT(pDriverGetCount, 0);
    for (uint32_t i = 0; i < pDriverGetCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithzeInitAndzeInitDriversWhenCallingBothThenSuccessfulReturn) {

    // Test ZEL_DRIVERS_ORDER compatibility with both zeInit and zeInitDrivers
    setDriverOrderEnv("DISCRETE_GPU_ONLY:0,NPU:0");

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

    std::vector<ze_driver_handle_t> drivers(pDriverGetCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&pDriverGetCount, drivers.data()));

    // Verify that both calls succeed and drivers are available
    EXPECT_GT(pDriverGetCount, 0);
    for (uint32_t i = 0; i < pDriverGetCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

///////////////////////////////////////////////////////////////////////////////
// Tests for ZEL_DRIVERS_ORDER: Complex real-world scenarios
///////////////////////////////////////////////////////////////////////////////

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithComplexScenarioLikeDocumentationExample1WhenCallingZeInitDriversThenSuccessfulReturn) {

    // Documentation Example 1: DISCRETE_GPU_ONLY:1,NPU
    // On a system with 2 GPU Drivers (discrete:0, discrete:1) and 1 NPU Driver
    // Default order: Discrete:0, Discrete:1, NPU
    // Expected order: Discrete:1, NPU:0, Discrete:0
    setDriverOrderEnv("DISCRETE_GPU_ONLY:1,NPU");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithComplexScenarioLikeDocumentationExample3WhenCallingZeInitDriversThenSuccessfulReturn) {

    // Documentation Example 3: GPU:1,NPU:0
    // On a system with 2 GPU Drivers (discrete, integrated) and 1 NPU Driver
    // Default order: Discrete, Integrated, NPU
    // GPU indexes: Discrete(0), Integrated(1); NPU indexes: NPU(0)
    // Expected order: Integrated, NPU, Discrete
    setDriverOrderEnv("GPU:1,NPU:0");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

TEST_F(DriverOrderingTest,
    GivenZelDriversOrderWithAllSupportedDriverTypesWhenCallingZeInitDriversThenSuccessfulReturn) {

    // Test all supported driver types in one ordering
    setDriverOrderEnv("NPU,INTEGRATED_GPU_ONLY,DISCRETE_GPU_ONLY,GPU");

    uint32_t pCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;

    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, nullptr, &desc));
    EXPECT_GT(pCount, 0);

    std::vector<ze_driver_handle_t> drivers(pCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pCount, drivers.data(), &desc));

    // Verify that we got drivers back
    EXPECT_GT(pCount, 0);
    for (uint32_t i = 0; i < pCount; ++i) {
        EXPECT_NE(drivers[i], nullptr);
    }
}

  TEST(
      RuntimeApiLoaderDriverInteraction,
      GivenLevelZeroLoaderPresentWithLoaderInterceptEnabledAndDdiExtSupportedWhenCallingRuntimeApisAfterZeInitDriversThenExpectNullDriverIsReachedSuccessfully)
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

    const char *errorString = nullptr;
    uint32_t deviceId = 0;

    ze_result_t result = zerGetLastErrorDescription(&errorString);
    EXPECT_EQ(ZE_RESULT_SUCCESS, result);
    EXPECT_TRUE(compare_env("zerGetLastErrorDescription", "1"));

    uint32_t device_count = 1;
    std::vector<ze_device_handle_t> devices(device_count);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDeviceGet(drivers[0], &device_count, devices.data()));

    deviceId = zerTranslateDeviceHandleToIdentifier(devices[0]);
    EXPECT_TRUE(compare_env("zerTranslateDeviceHandleToIdentifier", "1"));

    ze_device_handle_t translatedDevice = zerTranslateIdentifierToDeviceHandle(deviceId);
    EXPECT_TRUE(compare_env("zerTranslateIdentifierToDeviceHandle", "1"));
    (void)translatedDevice;

    ze_context_handle_t defaultContext = zerGetDefaultContext();
    EXPECT_TRUE(compare_env("zerGetDefaultContext", "1"));
    (void)defaultContext;
  }

  TEST(
      RuntimeApiLoaderDriverInteraction,
      GivenLevelZeroLoaderPresentWithLoaderInterceptEnabledAndDdiExtSupportedWhenCallingRuntimeApisAfterZeInitThenExpectNullDriverIsReachedSuccessfully)
  {
    putenv_safe(const_cast<char *>("ZE_ENABLE_LOADER_INTERCEPT=1"));
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0"));

    uint32_t driverGetCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverGetCount, nullptr));
    EXPECT_GT(driverGetCount, 0);

    const char *errorString = nullptr;
    uint32_t deviceId = 0;

    ze_result_t result = zerGetLastErrorDescription(&errorString);
    EXPECT_EQ(ZE_RESULT_SUCCESS, result);
    EXPECT_TRUE(compare_env("zerGetLastErrorDescription", "1"));

    deviceId = zerTranslateDeviceHandleToIdentifier(nullptr);
    EXPECT_TRUE(compare_env("zerTranslateDeviceHandleToIdentifier", "1"));

    ze_device_handle_t translatedDevice = zerTranslateIdentifierToDeviceHandle(deviceId);
    EXPECT_TRUE(compare_env("zerTranslateIdentifierToDeviceHandle", "1"));
    (void)translatedDevice;

    ze_context_handle_t defaultContext = zerGetDefaultContext();
    EXPECT_TRUE(compare_env("zerGetDefaultContext", "1"));
    (void)defaultContext;
  }

  TEST(
      RuntimeApiLoaderDriverInteraction,
      GivenLevelZeroLoaderPresentWithLoaderInterceptEnabledAndDdiExtNotSupportedWhenCallingRuntimeApisAfterZeInitDriversThenExpectNullDriverIsReachedSuccessfully)
  {
    uint32_t pInitDriversCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;
    putenv_safe(const_cast<char *>("ZE_ENABLE_LOADER_INTERCEPT=1"));
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1"));
    std::vector<ze_driver_handle_t> drivers;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
    drivers.resize(pInitDriversCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
    EXPECT_GT(pInitDriversCount, 0);

    const char *errorString = nullptr;
    uint32_t deviceId = 0;

    ze_result_t result = zerGetLastErrorDescription(&errorString);
    EXPECT_EQ(ZE_RESULT_SUCCESS, result);
    EXPECT_TRUE(compare_env("zerGetLastErrorDescription", "1"));

    deviceId = zerTranslateDeviceHandleToIdentifier(nullptr);
    EXPECT_TRUE(compare_env("zerTranslateDeviceHandleToIdentifier", "1"));

    ze_device_handle_t translatedDevice = zerTranslateIdentifierToDeviceHandle(deviceId);
    EXPECT_TRUE(compare_env("zerTranslateIdentifierToDeviceHandle", "1"));
    (void)translatedDevice;

    ze_context_handle_t defaultContext = zerGetDefaultContext();
    EXPECT_TRUE(compare_env("zerGetDefaultContext", "1"));
    (void)defaultContext;
  }

    TEST(
      RuntimeApiLoaderDriverInteraction,
      GivenLevelZeroLoaderPresentWithLoaderInterceptEnabledAndDdiExtNotSupportedWhenCallingRuntimeApisAfterZeInitThenExpectNullDriverIsReachedSuccessfully)
  {
    putenv_safe(const_cast<char *>("ZE_ENABLE_LOADER_INTERCEPT=1"));
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1"));

    uint32_t driverGetCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverGetCount, nullptr));
    EXPECT_GT(driverGetCount, 0);
    std::vector<ze_driver_handle_t> drivers;
    drivers.resize(driverGetCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverGetCount, drivers.data()));
    EXPECT_GT(driverGetCount, 0);

    const char *errorString = nullptr;
    uint32_t deviceId = 0;

    ze_result_t result = zerGetLastErrorDescription(&errorString);
    EXPECT_EQ(ZE_RESULT_SUCCESS, result);
    EXPECT_TRUE(compare_env("zerGetLastErrorDescription", "1"));

    deviceId = zerTranslateDeviceHandleToIdentifier(nullptr);
    EXPECT_TRUE(compare_env("zerTranslateDeviceHandleToIdentifier", "1"));

    ze_device_handle_t translatedDevice = zerTranslateIdentifierToDeviceHandle(deviceId);
    EXPECT_TRUE(compare_env("zerTranslateIdentifierToDeviceHandle", "1"));
    (void)translatedDevice;

    ze_context_handle_t defaultContext = zerGetDefaultContext();
    EXPECT_TRUE(compare_env("zerGetDefaultContext", "1"));
    (void)defaultContext;
  }
  
  TEST(
      RuntimeApiLoaderDriverInteraction,
      GivenLevelZeroLoaderPresentWithLoaderInterceptEnabledAndDdiExtSupportedWithVersion1_0WhenCallingRuntimeApisAfterZeInitDriversThenExpectErrorUninitialized)
  {
    uint32_t pInitDriversCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;
    putenv_safe(const_cast<char *>("ZE_ENABLE_LOADER_INTERCEPT=1"));
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0"));
    putenv_safe(const_cast<char *>("ZEL_TEST_DDI_HANDLES_EXT_VERSION=1_0"));
    std::vector<ze_driver_handle_t> drivers;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
    drivers.resize(pInitDriversCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
    EXPECT_GT(pInitDriversCount, 0);

    uint32_t deviceId = 0;

    const char *errorDesc = nullptr;
    ze_result_t errorDescResult{};

    deviceId = zerTranslateDeviceHandleToIdentifier(nullptr);
    EXPECT_EQ(UINT32_MAX, deviceId);

    errorDescResult = zerGetLastErrorDescription(&errorDesc);
    EXPECT_EQ(ZE_RESULT_SUCCESS, errorDescResult);
    EXPECT_NE(errorDesc, nullptr);
    EXPECT_EQ(0, strcmp(errorDesc, "ERROR UNINITIALIZED"));

    ze_device_handle_t translatedDevice = zerTranslateIdentifierToDeviceHandle(deviceId);
    EXPECT_EQ(nullptr, translatedDevice);

    errorDescResult = zerGetLastErrorDescription(&errorDesc);
    EXPECT_EQ(ZE_RESULT_SUCCESS, errorDescResult);
    EXPECT_NE(errorDesc, nullptr);
    EXPECT_EQ(0, strcmp(errorDesc, "ERROR UNINITIALIZED"));

    ze_context_handle_t defaultContext = zerGetDefaultContext();
    EXPECT_EQ(nullptr, defaultContext);

    errorDescResult = zerGetLastErrorDescription(&errorDesc);
    EXPECT_EQ(ZE_RESULT_SUCCESS, errorDescResult);
    EXPECT_NE(errorDesc, nullptr);
    EXPECT_EQ(0, strcmp(errorDesc, "ERROR UNINITIALIZED"));
  }

  TEST(
      RuntimeApiLoaderDriverInteraction,
      GivenLevelZeroLoaderPresentWithLoaderInterceptEnabledAndDdiExtSupportedWithVersion1_0WhenCallingRuntimeApisAfterZeInitThenExpectErrorUninitialized)
  {
    putenv_safe(const_cast<char *>("ZE_ENABLE_LOADER_INTERCEPT=1"));
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=0"));
    putenv_safe(const_cast<char *>("ZEL_TEST_DDI_HANDLES_EXT_VERSION=1_0"));

    uint32_t driverGetCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverGetCount, nullptr));
    EXPECT_GT(driverGetCount, 0);

    uint32_t deviceId = 0;

    const char *errorDesc = nullptr;
    ze_result_t errorDescResult{};

    deviceId = zerTranslateDeviceHandleToIdentifier(nullptr);
    EXPECT_EQ(UINT32_MAX, deviceId);

    errorDescResult = zerGetLastErrorDescription(&errorDesc);
    EXPECT_EQ(ZE_RESULT_SUCCESS, errorDescResult);
    EXPECT_NE(errorDesc, nullptr);
    EXPECT_EQ(0, strcmp(errorDesc, "ERROR UNINITIALIZED"));

    ze_device_handle_t translatedDevice = zerTranslateIdentifierToDeviceHandle(deviceId);
    EXPECT_EQ(nullptr, translatedDevice);

    errorDescResult = zerGetLastErrorDescription(&errorDesc);
    EXPECT_EQ(ZE_RESULT_SUCCESS, errorDescResult);
    EXPECT_NE(errorDesc, nullptr);
    EXPECT_EQ(0, strcmp(errorDesc, "ERROR UNINITIALIZED"));

    ze_context_handle_t defaultContext = zerGetDefaultContext();
    EXPECT_EQ(nullptr, defaultContext);

    errorDescResult = zerGetLastErrorDescription(&errorDesc);
    EXPECT_EQ(ZE_RESULT_SUCCESS, errorDescResult);
    EXPECT_NE(errorDesc, nullptr);
    EXPECT_EQ(0, strcmp(errorDesc, "ERROR UNINITIALIZED"));
  }

  TEST(
      RuntimeApiLoaderDriverInteraction,
      GivenLevelZeroLoaderPresentWithLoaderInterceptEnabledAndRuntimeApiUnsupportedWhenCallingRuntimeApisAfterZeInitDriversThenExpectErrorUnsupportedFeature)
  {
    uint32_t pInitDriversCount = 0;
    ze_init_driver_type_desc_t desc = {ZE_STRUCTURE_TYPE_INIT_DRIVER_TYPE_DESC};
    desc.flags = UINT32_MAX;
    desc.pNext = nullptr;
    putenv_safe(const_cast<char *>("ZE_ENABLE_LOADER_INTERCEPT=1"));
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_DISABLE_ZER_API=1"));

    std::vector<ze_driver_handle_t> drivers;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, nullptr, &desc));
    drivers.resize(pInitDriversCount);
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInitDrivers(&pInitDriversCount, drivers.data(), &desc));
    EXPECT_GT(pInitDriversCount, 0);

    uint32_t deviceId = 0;

    const char *errorDesc = nullptr;
    ze_result_t errorDescResult{};

    deviceId = zerTranslateDeviceHandleToIdentifier(nullptr);
    EXPECT_EQ(UINT32_MAX, deviceId);

    errorDescResult = zerGetLastErrorDescription(&errorDesc);
    EXPECT_EQ(ZE_RESULT_SUCCESS, errorDescResult);
    EXPECT_NE(errorDesc, nullptr);
    EXPECT_EQ(0, strcmp(errorDesc, "ERROR UNSUPPORTED FEATURE"));

    ze_device_handle_t translatedDevice = zerTranslateIdentifierToDeviceHandle(deviceId);
    EXPECT_EQ(nullptr, translatedDevice);

    errorDescResult = zerGetLastErrorDescription(&errorDesc);
    EXPECT_EQ(ZE_RESULT_SUCCESS, errorDescResult);
    EXPECT_NE(errorDesc, nullptr);
    EXPECT_EQ(0, strcmp(errorDesc, "ERROR UNSUPPORTED FEATURE"));

    ze_context_handle_t defaultContext = zerGetDefaultContext();
    EXPECT_EQ(nullptr, defaultContext);

    errorDescResult = zerGetLastErrorDescription(&errorDesc);
    EXPECT_EQ(ZE_RESULT_SUCCESS, errorDescResult);
    EXPECT_NE(errorDesc, nullptr);
    EXPECT_EQ(0, strcmp(errorDesc, "ERROR UNSUPPORTED FEATURE"));
  }

  TEST(
      RuntimeApiLoaderDriverInteraction,
      GivenLevelZeroLoaderPresentWithLoaderInterceptEnabledAndRuntimeApiUnsupportedWhenCallingRuntimeApisAfterZeInitThenExpectErrorUnsupportedFeature)
  {
    putenv_safe(const_cast<char *>("ZE_ENABLE_LOADER_INTERCEPT=1"));
    putenv_safe(const_cast<char *>("ZEL_TEST_NULL_DRIVER_DISABLE_ZER_API=1"));

    uint32_t driverGetCount = 0;
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));
    EXPECT_EQ(ZE_RESULT_SUCCESS, zeDriverGet(&driverGetCount, nullptr));
    EXPECT_GT(driverGetCount, 0);

    uint32_t deviceId = 0;

    const char *errorDesc = nullptr;
    ze_result_t errorDescResult{};

    deviceId = zerTranslateDeviceHandleToIdentifier(nullptr);
    EXPECT_EQ(UINT32_MAX, deviceId);

    errorDescResult = zerGetLastErrorDescription(&errorDesc);
    EXPECT_EQ(ZE_RESULT_SUCCESS, errorDescResult);
    EXPECT_NE(errorDesc, nullptr);
    EXPECT_EQ(0, strcmp(errorDesc, "ERROR UNSUPPORTED FEATURE"));

    ze_device_handle_t translatedDevice = zerTranslateIdentifierToDeviceHandle(deviceId);
    EXPECT_EQ(nullptr, translatedDevice);

    errorDescResult = zerGetLastErrorDescription(&errorDesc);
    EXPECT_EQ(ZE_RESULT_SUCCESS, errorDescResult);
    EXPECT_NE(errorDesc, nullptr);
    EXPECT_EQ(0, strcmp(errorDesc, "ERROR UNSUPPORTED FEATURE"));

    ze_context_handle_t defaultContext = zerGetDefaultContext();
    EXPECT_EQ(nullptr, defaultContext);

    errorDescResult = zerGetLastErrorDescription(&errorDesc);
    EXPECT_EQ(ZE_RESULT_SUCCESS, errorDescResult);
    EXPECT_NE(errorDesc, nullptr);
    EXPECT_EQ(0, strcmp(errorDesc, "ERROR UNSUPPORTED FEATURE"));
  }
  

} // namespace
