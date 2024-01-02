# Copyright (C) 2024 Intel Corporation
# SPDX-License-Identifier: MIT

include(FetchContent)
set(SPDLOG_REPO https://github.com/gabime/spdlog)
set(SPDLOG_TAG v1.13.0)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY ${SPDLOG_REPO}
    GIT_TAG ${SPDLOG_TAG}
)
FetchContent_makeAvailable(spdlog)

add_library(utils
  "logging.h"
  "logging.cpp"
)

target_link_libraries(utils spdlog::spdlog)