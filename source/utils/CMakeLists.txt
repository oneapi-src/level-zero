# Copyright (C) 2024 Intel Corporation
# SPDX-License-Identifier: MIT

add_library(utils
  STATIC
  "logging.h"
  "logging.cpp"
)

target_include_directories(utils PRIVATE ${CMAKE_SOURCE_DIR}/third_party/spdlog_headers/)
