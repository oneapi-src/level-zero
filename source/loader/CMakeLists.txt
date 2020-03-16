# Copyright (C) 2020 Intel Corporation
# SPDX-License-Identifier: MIT

target_sources(${TARGET_LOADER_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_object.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_core_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_tools_loader.cpp
)

file(GLOB LEVEL_ZERO_LOADER_INCLUDES
    "*.h"
)

install(FILES ${LEVEL_ZERO_LOADER_INCLUDES}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/level_zero/lib/loader
    COMPONENT level-zero-devel
)
