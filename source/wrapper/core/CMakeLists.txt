# Copyright (C) 2020 Intel Corporation
# SPDX-License-Identifier: MIT
set(TARGET_NAME ze_api_cpp)

add_library(${TARGET_NAME}
    STATIC
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

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        ZE_ENABLE_OCL_INTEROP=1
)

target_link_libraries(${TARGET_NAME}
    ze_api ze_api
    ${CMAKE_DL_LIBS}
)

file(GLOB LEVEL_ZERO_WRAPPER_CORE_INCLUDES
    "*.h*"
)

install(FILES ${LEVEL_ZERO_WRAPPER_CORE_INCLUDES}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/level_zero/wrapper/core
    COMPONENT level-zero-devel
)
