/*
 *
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"

#include "logging/logging.hpp"
#include "test_harness/test_harness.hpp"
#include <level_zero/loader/ze_loader.h>
#include <level_zero/ze_api.h>

namespace lzt = level_zero_tests;

namespace {

TEST(
    LoaderTest,
    GivenLevelZeroLoaderPresentWhenCallingzeGetLoaderVersionsAPIThenValidVersionIsReturned) {

  size_t size = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderGetVersions(&size, nullptr));

  std::vector<zel_component_version_t> versions;

  EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderGetVersions(&size, versions.data()));

  for (auto &component : versions) {
    LOG_INFO << "component.component_name: " << component.component_name;
    LOG_INFO << " " << component.component_lib_version.major;
    LOG_INFO << "component.spec_version: " << component.spec_version;
    LOG_INFO << "component.component_lib_name: " << component.component_name;

    if ("loader" == component.component_name) {
      EXPECT_GE(component.component_lib_version.major, 1);
    }
  }
}

} // namespace
