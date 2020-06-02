# Copyright (C) 2020 Intel Corporation
# SPDX-License-Identifier: MIT
set(TARGET_NAME ze_validation_layer)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/ZeValidationLayerVersion.rc.in
    ${CMAKE_CURRENT_BINARY_DIR}/ZeValidationLayerVersion.rc
    @ONLY)

add_library(${TARGET_NAME}
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_layer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_layer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_core_layer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_tools_layer.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/ZeValidationLayerVersion.rc
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        ZE_ENABLE_OCL_INTEROP=1
)

set_target_properties(${TARGET_NAME} PROPERTIES
    VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
    SOVERSION  "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
)

install(TARGETS ze_validation_layer
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT level-zero
        NAMELINK_SKIP
)

install(TARGETS ze_validation_layer
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT level-zero-devel
        NAMELINK_ONLY
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/ze_layer.h
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/level_zero/layers/validation
    COMPONENT level-zero-devel
)
