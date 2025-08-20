# Copyright (C) 2025 Intel Corporation
# SPDX-License-Identifier: MIT

target_sources(${TARGET_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/zel_certification_checker.h
        ${CMAKE_CURRENT_LIST_DIR}/zel_certification_checker.cpp
        ${CMAKE_CURRENT_LIST_DIR}/zel_global_certification_state.h
        ${CMAKE_CURRENT_LIST_DIR}/generated/ze_certification.h
        ${CMAKE_CURRENT_LIST_DIR}/generated/zes_certification.h
        ${CMAKE_CURRENT_LIST_DIR}/generated/zet_certification.h
)
