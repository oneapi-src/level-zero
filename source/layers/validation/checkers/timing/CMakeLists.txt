# Copyright (C) 2026 Intel Corporation
# SPDX-License-Identifier: MIT

target_sources(${TARGET_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/zel_timing_checker.h
        ${CMAKE_CURRENT_LIST_DIR}/zel_timing_checker.cpp
        ${CMAKE_CURRENT_LIST_DIR}/zel_global_timing_state.h
        ${CMAKE_CURRENT_LIST_DIR}/generated/ze_timing.h
        ${CMAKE_CURRENT_LIST_DIR}/generated/zes_timing.h
        ${CMAKE_CURRENT_LIST_DIR}/generated/zet_timing.h
        ${CMAKE_CURRENT_LIST_DIR}/generated/zer_timing.h
)
