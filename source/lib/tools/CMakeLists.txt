# Copyright (C) 2020 Intel Corporation
# SPDX-License-Identifier: MIT
set(TARGET_NAME zet_api)

target_sources(${TARGET_LOADER_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_common.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_device.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_cmdlist.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_debug.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_metric.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_module.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_pin.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_sysman.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_tracing.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_tools_lib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_lib.h
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_lib.cpp
)

file(GLOB LEVEL_ZERO_LIBRARY_TOOLS_INCLUDES
    "*.h"
)

install(FILES ${LEVEL_ZERO_LIBRARY_TOOLS_INCLUDES}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/level_zero/lib/tools
    COMPONENT level-zero-devel
)
