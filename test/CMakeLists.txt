# Copyright (C) 2024 Intel Corporation
# SPDX-License-Identifier: MIT

add_executable(
  tests
  loader_api.cpp
)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(
  tests
  GTest::gtest_main
  ${TARGET_LOADER_NAME}
)

# For some reason the MSVC runtime libraries used by googletest and test
# binaries don't match, so force the test binary to use the dynamic runtime.
if(MSVC)
    target_compile_options(tests PRIVATE "/MD$<$<CONFIG:Debug>:d>")
endif()

add_test(NAME tests_api COMMAND tests --gtest_filter=-*LoaderInit*)
set_property(TEST tests_api PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_init_gpu_all COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingZeInitDriversWithGPUTypeThenExpectPassWithGPUorAllOnly*)
set_property(TEST tests_init_gpu_all PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_init_npu_all COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingZeInitDriversWithNPUTypeThenExpectPassWithNPUorAllOnly*)
set_property(TEST tests_init_npu_all PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_any COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingZeInitDriversWithAnyTypeWithNullDriverAcceptingAllThenExpectatLeast1Driver*)
set_property(TEST tests_any PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_both_init_all COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingZeInitDriversThenzeInitThenBothCallsSucceedWithAllTypes*)
set_property(TEST tests_both_init_all PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_both_init_gpu COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingZeInitDriversThenzeInitThenBothCallsSucceedWithGPUTypes*)
set_property(TEST tests_both_init_gpu PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_both_init_npu COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingZeInitDriversThenzeInitThenBothCallsSucceedWithNPUTypes*)
set_property(TEST tests_both_init_npu PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_both_succeed COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingzeInitThenZeInitDriversThenBothCallsSucceedWithAllTypes*)
set_property(TEST tests_both_succeed PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_both_gpu COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingzeInitThenZeInitDriversThenBothCallsSucceedWithGPUTypes*)
set_property(TEST tests_both_gpu PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_both_npu COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingzeInitThenZeInitDriversThenBothCallsSucceedWithNPUTypes*)
set_property(TEST tests_both_npu PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_missing_api COMMAND tests --gtest_filter=*GivenZeInitDriversUnsupportedOnTheDriverWhenCallingZeInitDriversThenUninitializedReturned*)
set_property(TEST tests_missing_api PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")