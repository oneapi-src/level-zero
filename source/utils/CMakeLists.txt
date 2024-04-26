# Copyright (C) 2024 Intel Corporation
# SPDX-License-Identifier: MIT

find_package(spdlog)
if (NOT spdlog_FOUND)
  include(FetchContent)
  set(SPDLOG_REPO https://github.com/gabime/spdlog)
  set(SPDLOG_TAG v1.13.0)
  FetchContent_Declare(
      spdlog
      GIT_REPOSITORY ${SPDLOG_REPO}
      GIT_TAG ${SPDLOG_TAG}
  )
  FetchContent_makeAvailable(spdlog)
endif (NOT spdlog_FOUND)

add_library(utils
  STATIC
  "logging.h"
  "logging.cpp"
)

target_include_directories(utils
  PUBLIC
  ${FETCHCONTENT_BASE_DIR}/spdlog-src/include
)
