# Copyright (C) 2024-2025 Intel Corporation
# SPDX-License-Identifier: MIT

add_executable(
  tests
  loader_api.cpp
  loader_validation_layer.cpp
  driver_ordering_helper_tests.cpp
  loader_tracing_layer.cpp
)

# Only include driver_ordering_unit_tests for static builds or non-Windows platforms
# as it requires internal loader symbols that are not exported in Windows DLLs
if(BUILD_STATIC OR NOT WIN32)
  target_sources(tests PRIVATE driver_ordering_unit_tests.cpp)
endif()

# For builds on non-Windows platforms, include init_driver_unit_tests
# The tests rely on ablity to locate fake drivers by specific names which is not possible on Windows.
if(NOT WIN32)
  target_sources(tests PRIVATE init_driver_unit_tests.cpp)
endif()

# Only build init_driver_dynamic_unit_tests for dynamic builds on non-Windows platforms
# as it requires internal loader symbols that are not exported in Windows DLLs
if(NOT BUILD_STATIC AND NOT WIN32)
  target_sources(tests PRIVATE init_driver_dynamic_unit_tests.cpp)
endif()

# For static builds, we need to include the loader source files directly
# since they are not built into the library when BUILD_STATIC=1
if(BUILD_STATIC)
  target_sources(tests PRIVATE
    ${CMAKE_SOURCE_DIR}/source/loader/ze_loader.cpp
    ${CMAKE_SOURCE_DIR}/source/loader/ze_loader_api.cpp
    ${CMAKE_SOURCE_DIR}/source/loader/ze_ldrddi.cpp
    ${CMAKE_SOURCE_DIR}/source/loader/ze_ldrddi_driver_ddi.cpp
    ${CMAKE_SOURCE_DIR}/source/loader/zet_ldrddi.cpp
    ${CMAKE_SOURCE_DIR}/source/loader/zet_ldrddi_driver_ddi.cpp
    ${CMAKE_SOURCE_DIR}/source/loader/zes_ldrddi.cpp
    ${CMAKE_SOURCE_DIR}/source/loader/zes_ldrddi_driver_ddi.cpp
    ${CMAKE_SOURCE_DIR}/source/loader/zer_ldrddi_driver_ddi.cpp
    ${CMAKE_SOURCE_DIR}/source/loader/zer_ldrddi.cpp
    ${CMAKE_SOURCE_DIR}/source/loader/zel_tracing_ldrddi.cpp
  )
  
  # Platform-specific source files
  if(WIN32)
    target_sources(tests PRIVATE
      ${CMAKE_SOURCE_DIR}/source/loader/windows/driver_discovery_win.cpp
      ${CMAKE_SOURCE_DIR}/source/loader/windows/loader_init.cpp
    )
  else()
    target_sources(tests PRIVATE
      ${CMAKE_SOURCE_DIR}/source/loader/linux/driver_discovery_lin.cpp
      ${CMAKE_SOURCE_DIR}/source/loader/linux/loader_init.cpp
    )
  endif()
  
  # Add the same definitions as the source CMakeLists.txt
  target_compile_definitions(tests PRIVATE
    L0_LOADER_VERSION="${PROJECT_VERSION_MAJOR}"
    L0_VALIDATION_LAYER_SUPPORTED_VERSION="${PROJECT_VERSION_MAJOR}"
    L0_STATIC_LOADER_BUILD="1"
  )
endif()

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/source/inc)
target_link_libraries(
  tests
  PRIVATE
  GTest::gtest_main
  ${TARGET_LOADER_NAME}
  level_zero_utils
)

# For static builds, we need additional system libraries
if(BUILD_STATIC)
  target_link_libraries(tests PRIVATE ${CMAKE_DL_LIBS})
  if(UNIX AND NOT APPLE)
    target_link_libraries(tests PRIVATE pthread)
  endif()
endif()

# Create fake driver copies for init_driver_unit_tests
if(NOT BUILD_STATIC)
  if(MSVC)
    add_custom_command(TARGET tests POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:ze_null>
        $<TARGET_FILE_DIR:tests>/ze_fake_gpu.dll
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:ze_null_test1>
        $<TARGET_FILE_DIR:tests>/ze_fake_npu.dll
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:ze_null_test2>
        $<TARGET_FILE_DIR:tests>/ze_fake_vpu.dll
      COMMENT "Copying null drivers to fake driver names for init_driver_unit_tests"
    )
  else()
    add_custom_command(TARGET tests POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/lib/libze_null.so.1
        ${CMAKE_BINARY_DIR}/lib/libze_fake_gpu.so.1
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/lib/libze_null_test1.so.1
        ${CMAKE_BINARY_DIR}/lib/libze_fake_npu.so.1
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/lib/libze_null_test2.so.1
        ${CMAKE_BINARY_DIR}/lib/libze_fake_vpu.so.1
      COMMENT "Copying null drivers to fake driver names for init_driver_unit_tests"
    )
  endif()
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
add_test(NAME tests_missing_api COMMAND tests --gtest_filter=*GivenZeInitDriversUnsupportedOnTheDriverWhenCallingZeInitDriversThenUnSupportedReturned*)
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

add_test(NAME tests_multi_driver_one_driver_missing_initDrivers COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversMissingInitDriversInOneDriverWhenCallingZeInitDriversThenExpectSuccessForZeInitDrivers)
if (MSVC)
  set_property(TEST tests_multi_driver_one_driver_missing_initDrivers PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_one_driver_missing_initDrivers PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
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

add_test(NAME test_zello_world_legacy COMMAND zello_world --enable_legacy_init --enable_null_driver --force_loader_intercepts --enable_validation_layer --enable_tracing_layer --enable_tracing_layer_runtime)
set_property(TEST test_zello_world_legacy PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1")

add_test(NAME test_zello_world_legacy_intercept COMMAND zello_world --enable_legacy_init --enable_null_driver --force_loader_intercepts)
set_property(TEST test_zello_world_legacy_intercept PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1")

add_test(NAME test_zello_world_legacy_validation_layer COMMAND zello_world --enable_legacy_init --enable_null_driver --enable_validation_layer)
set_property(TEST test_zello_world_legacy_validation_layer PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1")

add_test(NAME test_zello_world_legacy_tracing COMMAND zello_world --enable_legacy_init --enable_null_driver --enable_tracing_layer)
set_property(TEST test_zello_world_legacy_tracing PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1")

add_test(NAME test_zello_world_legacy_dynamic_tracing COMMAND zello_world --enable_legacy_init --enable_null_driver --enable_tracing_layer_runtime)
set_property(TEST test_zello_world_legacy_dynamic_tracing PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1")

add_test(NAME test_zello_world_legacy_all_tracing COMMAND zello_world --enable_legacy_init --enable_null_driver --force_loader_intercepts --enable_validation_layer --enable_tracing_layer)
set_property(TEST test_zello_world_legacy_all_tracing PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1")

add_test(NAME test_zello_world_legacy_all_tracing_dynamic COMMAND zello_world --enable_legacy_init --enable_null_driver --force_loader_intercepts --enable_validation_layer --enable_tracing_layer_runtime)
set_property(TEST test_zello_world_legacy_all_tracing_dynamic PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1")

add_test(NAME tests_multi_driver_stdout COMMAND tests --gtest_filter=*GivenZeInitDriverWhenCalledThenNoOutputIsPrintedToStdout)
if (MSVC)
  set_property(TEST tests_multi_driver_stdout APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_stdout APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_sigle_driver_stdout COMMAND tests --gtest_filter=*GivenZeInitDriverWhenCalledThenNoOutputIsPrintedToStdout)
set_property(TEST tests_sigle_driver_stdout PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_multi_driver_drivergetproperties_sort COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingDriverGetPropertiesThenExpectSuccess)
if (MSVC)
  set_property(TEST tests_multi_driver_drivergetproperties_sort APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_drivergetproperties_sort APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

# Run with multiple drivers with one driver using legacy mode
add_test(NAME tests_multi_driver_missing_initDrivers_onelegacy COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversMissingInitDriversWhenCallingZeInitDriversThenExpectSuccessForZeInit)
if (MSVC)
  set_property(TEST tests_multi_driver_missing_initDrivers_onelegacy PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_missing_initDrivers_onelegacy PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_multi_driver_missing_initDrivers_sort_after_error_onelegacy COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversMissingInitDriversWhenCallingZeInitDriversThenExpectSuccessForZeInitWithDriverGetAfterInitDrivers)
if (MSVC)
  set_property(TEST tests_multi_driver_missing_initDrivers_sort_after_error_onelegacy APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_missing_initDrivers_sort_after_error_onelegacy APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_multi_driver_sort_onelegacy COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingZeInitDriversThenExpectSuccessForZeInit)
if (MSVC)
  set_property(TEST tests_multi_driver_sort_onelegacy PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_sort_onelegacy PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_multi_driver_driverget_sort_onelegacy COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingZeInitThenZeInitDriversThenExpectSuccessForZeInitWithDriverGetAfterInitDrivers)
if (MSVC)
  set_property(TEST tests_multi_driver_driverget_sort_onelegacy APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_driverget_sort_onelegacy APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_multi_driver_drivergetproperties_sort_onelegacy COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingDriverGetPropertiesThenExpectSuccess)
if (MSVC)
  set_property(TEST tests_multi_driver_drivergetproperties_sort_onelegacy APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_drivergetproperties_sort_onelegacy APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

# Run with multiple drivers with both drivers using legacy mode
add_test(NAME tests_multi_driver_missing_initDrivers_legacy COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversMissingInitDriversWhenCallingZeInitDriversThenExpectSuccessForZeInit)
if (MSVC)
  set_property(TEST tests_multi_driver_missing_initDrivers_legacy PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=3;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_missing_initDrivers_legacy PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=3;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_multi_driver_missing_initDrivers_sort_after_error_legacy COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversMissingInitDriversWhenCallingZeInitDriversThenExpectSuccessForZeInitWithDriverGetAfterInitDrivers)
if (MSVC)
  set_property(TEST tests_multi_driver_missing_initDrivers_sort_after_error_legacy APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=3;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_missing_initDrivers_sort_after_error_legacy APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=3;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_multi_driver_sort_legacy COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingZeInitDriversThenExpectSuccessForZeInit)
if (MSVC)
  set_property(TEST tests_multi_driver_sort_legacy PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=3;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_sort_legacy PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=3;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_multi_driver_driverget_sort_legacy COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingZeInitThenZeInitDriversThenExpectSuccessForZeInitWithDriverGetAfterInitDrivers)
if (MSVC)
  set_property(TEST tests_multi_driver_driverget_sort_legacy APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=3;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_driverget_sort_legacy APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=3;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_multi_driver_drivergetproperties_sort_legacy COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithMultipleDriversWhenCallingDriverGetPropertiesThenExpectSuccess)
if (MSVC)
  set_property(TEST tests_multi_driver_drivergetproperties_sort_legacy APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=3;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_drivergetproperties_sort_legacy APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZEL_TEST_NULL_DRIVER_DISABLE_DDI_EXT=3;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_loader_translate_handles_module COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForModule)
set_property(TEST tests_loader_translate_handles_module PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_module_ddi_enabled COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForModule)
set_property(TEST tests_loader_translate_handles_module_ddi_enabled PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_module_build_log COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForModuleBuildLog)
set_property(TEST tests_loader_translate_handles_module_build_log PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_module_build_log_ddi_enabled COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForModuleBuildLog)
set_property(TEST tests_loader_translate_handles_module_build_log_ddi_enabled PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_kernel COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForKernel)
set_property(TEST tests_loader_translate_handles_kernel PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_kernel_ddi_enabled COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForKernel)
set_property(TEST tests_loader_translate_handles_kernel_ddi_enabled PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_sampler COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForSampler)
set_property(TEST tests_loader_translate_handles_sampler PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_sampler_ddi_enabled COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForSampler)
set_property(TEST tests_loader_translate_handles_sampler_ddi_enabled PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_physical_mem COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForPhysicalMem)
set_property(TEST tests_loader_translate_handles_physical_mem PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_physical_mem_ddi_enabled COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForPhysicalMem)
set_property(TEST tests_loader_translate_handles_physical_mem_ddi_enabled PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_fence COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForFence)
set_property(TEST tests_loader_translate_handles_fence PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_fence_ddi_enabled COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForFence)
set_property(TEST tests_loader_translate_handles_fence_ddi_enabled PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_event_pool COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForEventPool)
set_property(TEST tests_loader_translate_handles_event_pool PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_event_pool_ddi_enabled COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForEventPool)
set_property(TEST tests_loader_translate_handles_event_pool_ddi_enabled PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_image COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForImage)
set_property(TEST tests_loader_translate_handles_image PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_image_ddi_enabled COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForImage)
set_property(TEST tests_loader_translate_handles_image_ddi_enabled PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_context COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForContext)
set_property(TEST tests_loader_translate_handles_context PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_context_ddi_enabled COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForContext)
set_property(TEST tests_loader_translate_handles_context_ddi_enabled PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_command_queue COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForCommandQueue)
set_property(TEST tests_loader_translate_handles_command_queue PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_command_queue_ddi_enabled COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForCommandQueue)
set_property(TEST tests_loader_translate_handles_command_queue_ddi_enabled PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_command_list COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForCommandList)
set_property(TEST tests_loader_translate_handles_command_list PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_command_list_ddi_enabled COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForCommandList)
set_property(TEST tests_loader_translate_handles_command_list_ddi_enabled PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_event COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForEvent)
set_property(TEST tests_loader_translate_handles_event PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_event_ddi_enabled COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForEvent)
set_property(TEST tests_loader_translate_handles_event_ddi_enabled PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_driver COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForDriver)
set_property(TEST tests_loader_translate_handles_driver PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_driver_ddi_enabled COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForDriver)
set_property(TEST tests_loader_translate_handles_driver_ddi_enabled PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_device COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForDevice)
set_property(TEST tests_loader_translate_handles_device PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_loader_translate_handles_device_ddi_enabled COMMAND tests --gtest_filter=*LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForDevice)
set_property(TEST tests_loader_translate_handles_device_ddi_enabled PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

# Add new versions of the tests with ZE_ENABLE_ALT_DRIVERS for Linux and Windows with both null drivers
if (MSVC)
  set(ALT_DRIVERS_ENV "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set(ALT_DRIVERS_ENV "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

foreach(test_name IN ITEMS
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForModule
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForModule
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForModuleBuildLog
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForModuleBuildLog
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForKernel
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForKernel
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForSampler
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForSampler
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForPhysicalMem
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForPhysicalMem
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForFence
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForFence
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForEventPool
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForEventPool
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForImage
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForImage
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForContext
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForContext
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForCommandQueue
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForCommandQueue
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForCommandList
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForCommandList
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForEvent
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForEvent
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForDriver
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForDriver
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportDisabledThenExpectHandleTranslationForDevice
    LoaderTranslateHandles.GivenLevelZeroLoaderPresentWhenCallingZelLoaderTranslateHandleInternalWithInterceptEnabledAndDDiSupportEnabledThenExpectNoHandleTranslationForDevice)
  add_test(NAME ${test_name}_alt_drivers COMMAND tests --gtest_filter=*${test_name})
  set_property(TEST ${test_name}_alt_drivers APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;${ALT_DRIVERS_ENV}")
endforeach()

add_test(NAME tests_single_driver_sysman_vf_management_api COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingSysManVfApisThenExpectNullDriverIsReachedSuccessfully)
set_property(TEST tests_single_driver_sysman_vf_management_api PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME tests_multi_driver_sysman_vf_management_api COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingSysManVfApisThenExpectNullDriverIsReachedSuccessfully)
if (MSVC)
  set_property(TEST tests_multi_driver_sysman_vf_management_api APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_multi_driver_sysman_vf_management_api APPEND PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

# Driver ordering tests - each test added individually
add_test(NAME tests_driver_ordering_specific_type_and_index COMMAND tests --gtest_filter=*GivenZelDriversOrderWithSpecificTypeAndIndexWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_specific_type_and_index PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_specific_type_and_index PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_gpu_type_and_index COMMAND tests --gtest_filter=*GivenZelDriversOrderWithGpuTypeAndIndexWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_gpu_type_and_index PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_gpu_type_and_index PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_integrated_gpu_type_and_index COMMAND tests --gtest_filter=*GivenZelDriversOrderWithIntegratedGpuTypeAndIndexWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_integrated_gpu_type_and_index PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_integrated_gpu_type_and_index PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_npu_type_and_index COMMAND tests --gtest_filter=*GivenZelDriversOrderWithNpuTypeAndIndexWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_npu_type_and_index PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_npu_type_and_index PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_specific_type_only COMMAND tests --gtest_filter=*GivenZelDriversOrderWithSpecificTypeOnlyWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_specific_type_only PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_specific_type_only PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_gpu_type_only COMMAND tests --gtest_filter=*GivenZelDriversOrderWithGpuTypeOnlyWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_gpu_type_only PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_gpu_type_only PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_integrated_gpu_type_only COMMAND tests --gtest_filter=*GivenZelDriversOrderWithIntegratedGpuTypeOnlyWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_integrated_gpu_type_only PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_integrated_gpu_type_only PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_single_npu_type COMMAND tests --gtest_filter=*GivenZelDriversOrderWithSingleNpuTypeWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_single_npu_type PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_single_npu_type PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_global_index_only COMMAND tests --gtest_filter=*GivenZelDriversOrderWithGlobalIndexOnlyWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_global_index_only PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_global_index_only PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_single_global_index COMMAND tests --gtest_filter=*GivenZelDriversOrderWithSingleGlobalIndexWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_single_global_index PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_single_global_index PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_multiple_global_indices COMMAND tests --gtest_filter=*GivenZelDriversOrderWithMultipleGlobalIndicesWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_multiple_global_indices PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_multiple_global_indices PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_mixed_syntax COMMAND tests --gtest_filter=*GivenZelDriversOrderWithMixedSyntaxWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_mixed_syntax PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_mixed_syntax PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_mixed_type_and_index_syntax COMMAND tests --gtest_filter=*GivenZelDriversOrderWithMixedTypeAndIndexSyntaxWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_mixed_type_and_index_syntax PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_mixed_type_and_index_syntax PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_invalid_driver_type COMMAND tests --gtest_filter=*GivenZelDriversOrderWithInvalidDriverTypeWhenCallingZeInitDriversThenDriversStillInitialize)
if (MSVC)
  set_property(TEST tests_driver_ordering_invalid_driver_type PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_invalid_driver_type PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_invalid_index COMMAND tests --gtest_filter=*GivenZelDriversOrderWithInvalidIndexWhenCallingZeInitDriversThenDriversStillInitialize)
if (MSVC)
  set_property(TEST tests_driver_ordering_invalid_index PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_invalid_index PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_empty_string COMMAND tests --gtest_filter=*GivenZelDriversOrderWithEmptyStringWhenCallingZeInitDriversThenDriversUseDefaultOrder)
if (MSVC)
  set_property(TEST tests_driver_ordering_empty_string PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_empty_string PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_whitespace_and_commas COMMAND tests --gtest_filter=*GivenZelDriversOrderWithWhitespaceAndCommasWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_whitespace_and_commas PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_whitespace_and_commas PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_duplicate_entries COMMAND tests --gtest_filter=*GivenZelDriversOrderWithDuplicateEntriesWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_duplicate_entries PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_duplicate_entries PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_zeinit_compatibility COMMAND tests --gtest_filter=*GivenZelDriversOrderWithzeInitWhenCallingzeInitThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_zeinit_compatibility PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_zeinit_compatibility PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_zeinit_and_zeinitdrivers COMMAND tests --gtest_filter=*GivenZelDriversOrderWithzeInitAndzeInitDriversWhenCallingBothThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_zeinit_and_zeinitdrivers PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_zeinit_and_zeinitdrivers PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_complex_scenario_example1 COMMAND tests --gtest_filter=*GivenZelDriversOrderWithComplexScenarioLikeDocumentationExample1WhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_complex_scenario_example1 PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_complex_scenario_example1 PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_complex_scenario_example3 COMMAND tests --gtest_filter=*GivenZelDriversOrderWithComplexScenarioLikeDocumentationExample3WhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_complex_scenario_example3 PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_complex_scenario_example3 PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

add_test(NAME tests_driver_ordering_all_supported_driver_types COMMAND tests --gtest_filter=*GivenZelDriversOrderWithAllSupportedDriverTypesWhenCallingZeInitDriversThenSuccessfulReturn)
if (MSVC)
  set_property(TEST tests_driver_ordering_all_supported_driver_types PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
else()
  set_property(TEST tests_driver_ordering_all_supported_driver_types PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_ALT_DRIVERS=${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
endif()

# Driver Ordering Unit Tests
add_test(NAME driver_ordering_unit_tests COMMAND tests --gtest_filter=DriverOrderingUnitTest.*)
set_property(TEST driver_ordering_unit_tests PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

# Individual Driver Ordering Unit Tests for better granular reporting
add_test(NAME driver_ordering_no_env COMMAND tests --gtest_filter=DriverOrderingUnitTest.NoEnvironmentVariable_ShouldNotChangeOrder)
set_property(TEST driver_ordering_no_env PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME driver_ordering_empty_env COMMAND tests --gtest_filter=DriverOrderingUnitTest.EmptyEnvironmentVariable_ShouldNotChangeOrder)
set_property(TEST driver_ordering_empty_env PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME driver_ordering_global_index COMMAND tests --gtest_filter=DriverOrderingUnitTest.GlobalIndex_*)
set_property(TEST driver_ordering_global_index PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME driver_ordering_driver_type COMMAND tests --gtest_filter=DriverOrderingUnitTest.DriverType_*)
set_property(TEST driver_ordering_driver_type PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME driver_ordering_type_and_index COMMAND tests --gtest_filter=DriverOrderingUnitTest.DriverTypeAndIndex_*)
set_property(TEST driver_ordering_type_and_index PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME driver_ordering_mixed_syntax COMMAND tests --gtest_filter=DriverOrderingUnitTest.MixedSyntax_*)
set_property(TEST driver_ordering_mixed_syntax PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME driver_ordering_edge_cases COMMAND tests --gtest_filter=DriverOrderingUnitTest.GlobalIndex_OutOfBounds_*:DriverOrderingUnitTest.DriverTypeAndIndex_OutOfBoundsIndex_*:DriverOrderingUnitTest.DriverTypeAndIndex_InvalidDriverType_*:DriverOrderingUnitTest.DuplicateSpecifications_*:DriverOrderingUnitTest.InvalidSyntax_*:DriverOrderingUnitTest.ColonWithoutIndex_*:DriverOrderingUnitTest.OnlyCommas_*)
set_property(TEST driver_ordering_edge_cases PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME driver_ordering_boundary_conditions COMMAND tests --gtest_filter=DriverOrderingUnitTest.SingleDriver_*:DriverOrderingUnitTest.MaxOrderSpecifications_*)
set_property(TEST driver_ordering_boundary_conditions PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

# Driver Ordering Helper Function Tests
add_test(NAME driver_ordering_helper_functions COMMAND tests --gtest_filter=DriverOrderingHelperFunctionsTest.*)
set_property(TEST driver_ordering_helper_functions PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

# Individual Helper Function Tests for better granular reporting
add_test(NAME driver_ordering_string_to_driver_type COMMAND tests --gtest_filter=DriverOrderingHelperFunctionsTest.StringToDriverType_*)
set_property(TEST driver_ordering_string_to_driver_type PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME driver_ordering_trim_function COMMAND tests --gtest_filter=DriverOrderingHelperFunctionsTest.Trim_*)
set_property(TEST driver_ordering_trim_function PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME driver_ordering_parse_driver_order COMMAND tests --gtest_filter=DriverOrderingHelperFunctionsTest.ParseDriverOrder_*)
set_property(TEST driver_ordering_parse_driver_order PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

# Init Driver Unit Tests
add_test(NAME init_driver_unit_tests COMMAND tests --gtest_filter=InitDriverUnitTest.*)
if (MSVC)
  set_property(TEST init_driver_unit_tests PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;")
elseif(NOT BUILD_STATIC)
  set_property(TEST init_driver_unit_tests PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/lib_fake:${CMAKE_BINARY_DIR}/lib/")
else()
  set_property(TEST init_driver_unit_tests PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;")
endif()

# These tests are currently not supported on Windows. The reason is that the std::cerr is not being redirected to a pipe in Windows to be then checked against the expected output.
if(NOT MSVC)
    add_test(NAME tests_event_deadlock COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingzeCommandListAppendMemoryCopyWithCircularDependencyOnEventsThenValidationLayerPrintsWarningOfDeadlock*)
    set_property(TEST tests_event_deadlock PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_VALIDATION_LAYER=1;ZEL_ENABLE_EVENTS_CHECKER=1")
    add_test(NAME tests_event_deadlock_reset COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingzeCommandListAppendMemoryCopyWithCircularDependencyOnEventsAndExplicitCallzeEventHostSignalThenValidationLayerPrintsWarningOfIllegalUsage*)
    set_property(TEST tests_event_deadlock_reset PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_VALIDATION_LAYER=1;ZEL_ENABLE_EVENTS_CHECKER=1")
    add_test(NAME tests_event_reset_reuse COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingzeEventHostResetWithAlreadySignaledEventThenUsingEventAgainThenValidationLayerDoesNotPrintsWarningOfIllegalUsage*)
    set_property(TEST tests_event_reset_reuse PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_VALIDATION_LAYER=1;ZEL_ENABLE_EVENTS_CHECKER=1")
endif()

# ZER Runtime API Tests

# Helper function to add runtime API tests
function(add_runtime_api_test test_scenario init_method driver_config)
    set(test_name "tests_${driver_config}_runtime_api_${test_scenario}_${init_method}")
    
    # Define test scenarios and their corresponding gtest filters
    if(test_scenario STREQUAL "ddi_ext_v1_1")
        set(gtest_filter "*GivenLevelZeroLoaderPresentWithLoaderInterceptEnabledAndDdiExtSupportedWhenCallingRuntimeApisAfter${init_method}ThenExpectNullDriverIsReachedSuccessfully")
    elseif(test_scenario STREQUAL "ddi_ext_unsupported")
        set(gtest_filter "*GivenLevelZeroLoaderPresentWithLoaderInterceptEnabledAndDdiExtNotSupportedWhenCallingRuntimeApisAfter${init_method}ThenExpectNullDriverIsReachedSuccessfully")
    elseif(test_scenario STREQUAL "ddi_ext_v1_0")
        set(gtest_filter "*GivenLevelZeroLoaderPresentWithLoaderInterceptEnabledAndDdiExtSupportedWithVersion1_0WhenCallingRuntimeApisAfter${init_method}ThenExpectErrorUninitialized")
    elseif(test_scenario STREQUAL "unsupported")
        set(gtest_filter "*GivenLevelZeroLoaderPresentWithLoaderInterceptEnabledAndRuntimeApiUnsupportedWhenCallingRuntimeApisAfter${init_method}ThenExpectErrorUnsupportedFeature")
    endif()
    
    # Add the test
    add_test(NAME ${test_name} COMMAND tests --gtest_filter=${gtest_filter})
    
    # Set base environment variables
    set(base_env "ZE_ENABLE_LOADER_DRIVER_DDI_PATH=1;ZE_ENABLE_LOADER_DEBUG_TRACE=1")
    
    if(driver_config STREQUAL "single_driver")
        # Single driver configuration
        set_property(TEST ${test_name} PROPERTY ENVIRONMENT "${base_env};ZE_ENABLE_NULL_DRIVER=1")
    elseif(driver_config STREQUAL "multi_driver")
        # Multi-driver configuration
        if(MSVC)
            set(alt_drivers "${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test1.dll,${CMAKE_BINARY_DIR}/bin/$<CONFIG>/ze_null_test2.dll")
        else()
            set(alt_drivers "${CMAKE_BINARY_DIR}/lib/libze_null_test1.so,${CMAKE_BINARY_DIR}/lib/libze_null_test2.so")
        endif()
        set_property(TEST ${test_name} APPEND PROPERTY ENVIRONMENT "${base_env};ZE_ENABLE_ALT_DRIVERS=${alt_drivers}")
    endif()
endfunction()

# Generate all ZER Runtime API tests using loops
set(test_scenarios "ddi_ext_v1_1;ddi_ext_unsupported;ddi_ext_v1_0")
set(init_methods "ZeInitDrivers;ZeInit")

foreach(init_method IN LISTS init_methods)
    foreach(test_scenario IN LISTS test_scenarios)
        # Add single driver tests
        add_runtime_api_test(${test_scenario} ${init_method} "single_driver")
        
        # Add multi-driver tests
        add_runtime_api_test(${test_scenario} ${init_method} "multi_driver")
    endforeach()
    # Add runtime_api_unsupported tests for single driver
    if(init_method STREQUAL "ZeInitDrivers" OR init_method STREQUAL "ZeInit")
        add_runtime_api_test("unsupported" ${init_method} "single_driver")
    endif()
endforeach()

# ZER API Tracing Tests
add_test(NAME test_zer_tracing_static_prologue COMMAND tests --gtest_filter=*TracingParameterizedTest*GivenLoaderWhenCallingZerApisWithStaticTracingEnabledAndPrologueCallbacksRegisteredThenExpectTracingToWork*)
set_property(TEST test_zer_tracing_static_prologue PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME test_zer_tracing_static_epilogue COMMAND tests --gtest_filter=*TracingParameterizedTest*GivenLoaderWhenCallingZerApisWithStaticTracingEnabledAndEpilogueCallbacksRegisteredThenExpectTracingToWork*)
set_property(TEST test_zer_tracing_static_epilogue PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME test_zer_tracing_static_both COMMAND tests --gtest_filter=*TracingParameterizedTest*GivenLoaderWhenCallingZerApisWithStaticTracingEnabledAndBothCallbacksRegisteredThenExpectBothToWork*)
set_property(TEST test_zer_tracing_static_both PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME test_zer_tracing_dynamic_prologue COMMAND tests --gtest_filter=*TracingParameterizedTest*GivenLoaderWhenCallingZerApisWithDynamicTracingEnabledAndPrologueCallbacksRegisteredThenExpectCallbacksToWorkCorrectly*)
set_property(TEST test_zer_tracing_dynamic_prologue PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME test_zer_tracing_dynamic_epilogue COMMAND tests --gtest_filter=*TracingParameterizedTest*GivenLoaderWhenCallingZerApisWithDynamicTracingEnabledAndEpilogueCallbacksRegisteredThenExpectTracingToWork*)
set_property(TEST test_zer_tracing_dynamic_epilogue PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME test_zer_tracing_dynamic_both COMMAND tests --gtest_filter=*TracingParameterizedTest*GivenLoaderWhenCallingZerApisWithDynamicTracingEnabledAndBothCallbacksRegisteredThenExpectFullTracingFunctionality*)
set_property(TEST test_zer_tracing_dynamic_both PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME test_zer_tracing_static_multi_tracers COMMAND tests --gtest_filter=*TracingParameterizedTest*GivenLoaderWithStaticTracingEnabledAndMultipleTracersWithBothCallbacksRegisteredWhenCallingZerApisThenAllTracersReceiveCallbacks*)
set_property(TEST test_zer_tracing_static_multi_tracers PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME test_zer_tracing_static_multi_enabled_disabled_tracers COMMAND tests --gtest_filter=*TracingParameterizedTest*GivenLoaderWithStaticTracingEnabledAndMultipleEnabledAndDisabledTracersWithPrologueCallbacksRegisteredWhenCallingZerApisThenOnlyEnabledTracersReceiveCallbacks*)
set_property(TEST test_zer_tracing_static_multi_enabled_disabled_tracers PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME test_zer_tracing_static_multi_tracers_different_callbacks COMMAND tests --gtest_filter=*TracingParameterizedTest*GivenLoaderWithStaticTracingEnabledAndMultipleTracersWithDifferentCallbacksRegisteredWhenCallingZerApisThenEachTracerWorksIndependently*)
set_property(TEST test_zer_tracing_static_multi_tracers_different_callbacks PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME test_zer_tracing_static_selective COMMAND tests --gtest_filter=*TracingParameterizedTest*GivenLoaderWithStaticTracingEnabledAndSelectiveCallbackRegistrationWhenCallingZerApisThenOnlyRegisteredCallbacksAreTriggered*)
set_property(TEST test_zer_tracing_static_selective PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME test_ze_and_zer_tracing_static COMMAND tests --gtest_filter=*TracingParameterizedTest*GivenLoaderWithStaticTracingEnabledAndBothZeAndZerCallbacksRegisteredWhenCallingBothApisThenBothAreTraced*)
set_property(TEST test_ze_and_zer_tracing_static PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME test_ze_and_zer_tracing_dynamic COMMAND tests --gtest_filter=*TracingParameterizedTest*GivenLoaderWithDynamicTracingEnabledAndBothZeAndZerCallbacksRegisteredWhenCallingBothApisThenBothAreTraced*)
set_property(TEST test_ze_and_zer_tracing_dynamic PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")

add_test(NAME test_zer_unsupported_and_ze_tracing_dynamic COMMAND tests --gtest_filter=*TracingParameterizedTest*GivenLoaderWithDynamicTracingEnabledAndZerApisUnsupportedAndBothZeAndZerCallbacksRegisteredWhenCallingBothApisThenTracingWorksForZeAndZerCallbacksAreStillInvoked*)
set_property(TEST test_zer_unsupported_and_ze_tracing_dynamic PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")

# ZER API Validation Layer Tests
add_test(NAME test_zer_validation_layer_positive_case COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWithLoaderInterceptEnabledAndDdiExtSupportedWhenCallingRuntimeApisAfterZeInitDriversThenExpectNullDriverIsReachedSuccessfully)
set_property(TEST test_zer_validation_layer_positive_case PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_VALIDATION_LAYER=1;ZE_ENABLE_PARAMETER_VALIDATION=1;ZE_ENABLE_HANDLE_LIFETIME=0;ZEL_ENABLE_EVENTS_CHECKER=1;ZEL_ENABLE_BASIC_LEAK_CHECKER=1;ZEL_ENABLE_CERTIFICATION_CHECKER=1")

add_test(NAME test_zer_parameter_validation_layer_negative_case COMMAND tests --gtest_filter=*GivenLevelZeroLoaderPresentWhenCallingZerApiWithParameterValidationEnabledThenExpectValidationsAreTriggered)
set_property(TEST test_zer_parameter_validation_layer_negative_case PROPERTY ENVIRONMENT "ZE_ENABLE_LOADER_DEBUG_TRACE=1;ZE_ENABLE_NULL_DRIVER=1;ZE_ENABLE_VALIDATION_LAYER=1;ZE_ENABLE_PARAMETER_VALIDATION=1;ZE_ENABLE_HANDLE_LIFETIME=1;ZEL_ENABLE_EVENTS_CHECKER=1;ZEL_ENABLE_BASIC_LEAK_CHECKER=1;ZEL_ENABLE_CERTIFICATION_CHECKER=1")