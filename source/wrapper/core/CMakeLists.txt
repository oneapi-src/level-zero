# Copyright (C) 2020 Intel Corporation
# SPDX-License-Identifier: MIT

target_sources(${TARGET_LOADER_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_common.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_device.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_cmdqueue.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_cmdlist.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_barrier.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_copy.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_event.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_fence.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_image.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_memory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_module.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_residency.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_sampler.cpp
)

file(GLOB LEVEL_ZERO_WRAPPER_CORE_INCLUDES
    "*.h*"
)

install(FILES ${LEVEL_ZERO_WRAPPER_CORE_INCLUDES}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/level_zero/
    COMPONENT level-zero-devel
)
