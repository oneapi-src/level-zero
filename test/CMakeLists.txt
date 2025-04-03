# Copyright (C) 2024 Intel Corporation
# SPDX-License-Identifier: MIT

add_executable(
  tests
  loader_api.cpp
  loader_validation_layer.cpp
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

add_test(NAME tests_api COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingzeGetLoaderVersionsAPIThenValidVersionIsReturned*)
set_property(TEST tests_api PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_init_gpu_all COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingZeInitDriversWithGPUTypeThenExpectPassWithGPUorAllOnly*)
set_property(TEST tests_init_gpu_all PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_init_npu_all COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingZeInitDriversWithNPUTypeThenExpectPassWithNPUorAllOnly*)
set_property(TEST tests_init_npu_all PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_any COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingZeInitDriversWithAnyTypeWithNullDriverAcceptingAllThenExpectatLeast1Driver*)
set_property(TEST tests_any PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_both_init_all COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingZeInitDriversThenzeInitThenBothCallsSucceedWithAllTypes*)
set_property(TEST tests_both_init_all PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_both_init_gpu COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingZeInitDriversThenzeInitThenBothCallsSucceedWithGPUTypes*)
set_property(TEST tests_both_init_gpu PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_both_init_npu COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingZeInitDriversThenzeInitThenBothCallsSucceedWithNPUTypes*)
set_property(TEST tests_both_init_npu PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_both_succeed COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingzeInitThenZeInitDriversThenBothCallsSucceedWithAllTypes*)
set_property(TEST tests_both_succeed PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_both_gpu COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingzeInitThenZeInitDriversThenBothCallsSucceedWithGPUTypes*)
set_property(TEST tests_both_gpu PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_both_npu COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingzeInitThenZeInitDriversThenBothCallsSucceedWithNPUTypes*)
set_property(TEST tests_both_npu PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_missing_api COMMAND tests --gtest_filter=*GivenZeInitDriversUnsupportedOnTheDriverWhenCallingZeInitDriversThenUninitializedReturned*)
set_property(TEST tests_missing_api PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")
add_test(NAME tests_multi_call_failure COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingZeInitDriversWithTypesUnsupportedWithFailureThenSupportedTypesThenSuccessReturned*)
set_property(TEST tests_multi_call_failure PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

# Run with multiple drivers
add_test(NAME tests_multi_driver_missing_initDrivers COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversMissingInitDriversWhenCallingZeInitDriversThenExpectSuccessForZeInit)
if (MSVC)
  set_property(TEST tests_multi_driver_missing_initDrivers PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_missing_initDrivers PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_multi_driver_missing_initDrivers_sort_after_error COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversMissingInitDriversWhenCallingZeInitDriversThenExpectSuccessForZeInitWithDriverGetAfterInitDrivers)
if (MSVC)
  set_property(TEST tests_multi_driver_missing_initDrivers_sort_after_error APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_missing_initDrivers_sort_after_error APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_multi_driver_sort COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingZeInitDriversThenExpectSuccessForZeInit)
if (MSVC)
  set_property(TEST tests_multi_driver_sort PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_sort PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_multi_driver_driverget_sort COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingZeInitThenZeInitDriversThenExpectSuccessForZeInitWithDriverGetAfterInitDrivers)
if (MSVC)
  set_property(TEST tests_multi_driver_driverget_sort APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_driverget_sort APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_multi_driver_zesdriverget_sort COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingZesInitThenExpectSuccessForZesDriverGet)
if (MSVC)
  set_property(TEST tests_multi_driver_zesdriverget_sort APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_zesdriverget_sort APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_multi_driver_zeandzesdriverget_sort COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingZesInitThenZeInitDriversExpectSuccessForZesDriverGetAndZeInitDrivers)
if (MSVC)
  set_property(TEST tests_multi_driver_zeandzesdriverget_sort APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_zeandzesdriverget_sort APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_loader_teardown_check COMMAND tests --gtest_filter=*GivenLoaderNotInDestructionStateWhenCallingzelCheckIsLoaderInTearDownThenFalseIsReturned)
set_property(TEST tests_loader_teardown_check PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

# These tests are currently not supported on Windows. The reason is that the std::cerr is not being redirected to a pipe in Windows to be then checked against the expected output.
if(NOT MSVC)
    add_test(NAME tests_event_deadlock COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingzeCommandListAppendMemoryCopyWithCircularDependencyOnEventsThenValidationLayerPrintsWarningOfDeadlock*)
    set_property(TEST tests_event_deadlock PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_VALIDATION_LAYER=1;ZEL_ENABLE_EVENTS_CHECKER=1")
    add_test(NAME tests_event_deadlock_reset COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingzeCommandListAppendMemoryCopyWithCircularDependencyOnEventsAndExplicitCallzeEventHostSignalThenValidationLayerPrintsWarningOfIllegalUsage*)
    set_property(TEST tests_event_deadlock_reset PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_VALIDATION_LAYER=1;ZEL_ENABLE_EVENTS_CHECKER=1")
    add_test(NAME tests_event_reset_reuse COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingzeEventHostResetWithAlreadySignaledEventThenUsingEventAgainThenValidationLayerDoesNotPrintsWarningOfIllegalUsage*)
    set_property(TEST tests_event_reset_reuse PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_VALIDATION_LAYER=1;ZEL_ENABLE_EVENTS_CHECKER=1")
endif()
