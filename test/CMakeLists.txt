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

add_test(NAME tests COMMAND tests)
set_property(TEST tests PROPERTY ENVIRONMENT "ZE_ENABLE_NULL_DRIVER=1")