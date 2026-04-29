# Copyright (C) 2024-2026 Intel Corporation
# SPDX-License-Identifier: MIT

set(logging_files ze_logger.h ze_logger.cpp ze_to_string.h zes_to_string.h zet_to_string.h zer_to_string.h)
add_library(level_zero_utils STATIC ${logging_files})

target_include_directories(level_zero_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_property(TARGET level_zero_utils PROPERTY POSITION_INDEPENDENT_CODE ON)

# Hide all symbols — ZeLogger is an internal implementation detail, not a public ABI.
# Each consumer (loader, validation layer, static shim) links its own copy.
# Prevents runtime symbol interposition when multiple copies coexist in one process.
if(NOT WIN32)
    target_compile_options(level_zero_utils PRIVATE -fvisibility=hidden -fvisibility-inlines-hidden)
endif()
