# Copyright (C) 2020 Intel Corporation
# SPDX-License-Identifier: MIT
if (MSVC)
set(TARGET_NAME ze_loader)

add_library(${TARGET_NAME}
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_object.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_core_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_tools_loader.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        ZE_ENABLE_OCL_INTEROP=1
)

else()
target_sources(${TARGET_LOADER_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_object.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_core_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_tools_loader.cpp
)
endif()

file(GLOB LEVEL_ZERO_LOADER_INCLUDES
    "*.h"
)

install(FILES ${LEVEL_ZERO_LOADER_INCLUDES}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/level_zero/lib/loader
    COMPONENT level-zero-devel
)
