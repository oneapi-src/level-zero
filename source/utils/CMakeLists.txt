# Copyright (C) 2024 Intel Corporation
# SPDX-License-Identifier: MIT

set(logging_files logging.h logging.cpp)
add_library(utils STATIC ${logging_files})

if(SYSTEM_SPDLOG)
       target_link_libraries(utils PUBLIC spdlog::spdlog)
else()
       target_include_directories(utils PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/third_party/spdlog_headers>)
endif()
set_property(TARGET utils PROPERTY POSITION_INDEPENDENT_CODE ON)
