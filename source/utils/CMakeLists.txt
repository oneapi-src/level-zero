# Copyright (C) 2024 Intel Corporation
# SPDX-License-Identifier: MIT

set(logging_files logging.h logging.cpp)
add_library(level_zero_utils STATIC ${logging_files})

if(SYSTEM_SPDLOG)
       target_link_libraries(level_zero_utils PUBLIC spdlog::spdlog)
else()
       target_include_directories(level_zero_utils PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/third_party/spdlog_headers>)
endif()

target_include_directories(level_zero_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_property(TARGET level_zero_utils PROPERTY POSITION_INDEPENDENT_CODE ON)
