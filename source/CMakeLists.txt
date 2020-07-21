# Copyright (C) 2020 Intel Corporation
# SPDX-License-Identifier: MIT

add_definitions(-DL0_LOADER_VERSION="${PROJECT_VERSION_MAJOR}")
add_definitions(-DL0_VALIDATION_LAYER_SUPPORTED_VERSION="${PROJECT_VERSION_MAJOR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/ZeLoaderVersion.rc.in
    ${CMAKE_CURRENT_BINARY_DIR}/ZeLoaderVersion.rc
    @ONLY)

include(GNUInstallDirs)
add_library(${TARGET_LOADER_NAME}
    SHARED
    ""
    ${CMAKE_CURRENT_BINARY_DIR}/ZeLoaderVersion.rc
)

add_subdirectory(lib)
add_subdirectory(loader)
add_subdirectory(layers)
add_subdirectory(wrapper)
add_subdirectory(drivers)

set_target_properties(${TARGET_LOADER_NAME} PROPERTIES
    VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
)

target_link_libraries(${TARGET_LOADER_NAME}
    ${CMAKE_DL_LIBS}
)

if(WIN32)
    target_link_libraries (${TARGET_LOADER_NAME} cfgmgr32.lib)
endif()

install(TARGETS ze_loader
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT level-zero
        NAMELINK_SKIP
)

install(TARGETS ze_loader
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT level-zero-devel
        NAMELINK_ONLY
)
