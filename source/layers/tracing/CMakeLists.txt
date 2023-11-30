# Copyright (C) 2020 Intel Corporation
# SPDX-License-Identifier: MIT
set(TARGET_NAME ze_tracing_layer)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/ZeTracingLayerVersion.rc.in
    ${CMAKE_CURRENT_BINARY_DIR}/ZeTracingLayerVersion.rc
    @ONLY)

add_library(${TARGET_NAME}
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_tracing_layer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/tracing.h
        ${CMAKE_CURRENT_SOURCE_DIR}/tracing_imp.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_tracing_layer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_trcddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tracing_imp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_tracing.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_tracing_cb_structs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_tracing_register_cb.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/ZeTracingLayerVersion.rc
)

if(WIN32)
    target_sources(${TARGET_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/windows/tracing_init.cpp
    )
else()
    target_sources(${TARGET_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/linux/tracing_init.cpp
    )
endif()

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if(UNIX)
    set(GCC_COVERAGE_COMPILE_FLAGS "-fvisibility=hidden -fvisibility-inlines-hidden")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
endif()

set_target_properties(${TARGET_NAME} PROPERTIES
    VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
    SOVERSION  "${PROJECT_VERSION_MAJOR}"
)

install(TARGETS ze_tracing_layer
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT level-zero
        NAMELINK_SKIP
)

install(TARGETS ze_tracing_layer
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT level-zero-devel
        NAMELINK_ONLY
)

