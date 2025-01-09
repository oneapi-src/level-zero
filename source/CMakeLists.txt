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
add_subdirectory(drivers)
add_subdirectory(utils)

set_target_properties(${TARGET_LOADER_NAME} PROPERTIES
    VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
)

target_link_libraries(${TARGET_LOADER_NAME} PRIVATE ${CMAKE_DL_LIBS} level_zero_utils)

if (UNIX)
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)
    find_package(Threads REQUIRED)
    target_link_libraries (${TARGET_LOADER_NAME} PRIVATE Threads::Threads)
endif()

if(WIN32)
    target_link_libraries (${TARGET_LOADER_NAME} PRIVATE cfgmgr32.lib)
endif()

install(TARGETS ze_loader
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT level-zero-devel
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT level-zero
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT level-zero
    NAMELINK_COMPONENT level-zero-devel
)

file(RELATIVE_PATH pkgconfig_prefix "${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig" "${CMAKE_INSTALL_PREFIX}")
file(RELATIVE_PATH pkgconfig_include_dir "${CMAKE_INSTALL_PREFIX}" "${CMAKE_INSTALL_FULL_INCLUDEDIR}")
file(RELATIVE_PATH pkgconfig_lib_dir "${CMAKE_INSTALL_PREFIX}" "${CMAKE_INSTALL_FULL_LIBDIR}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libze_loader.pc.in ${CMAKE_CURRENT_BINARY_DIR}/libze_loader.pc @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/level-zero.pc.in ${CMAKE_CURRENT_BINARY_DIR}/level-zero.pc @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libze_loader.pc"
              "${CMAKE_CURRENT_BINARY_DIR}/level-zero.pc"
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig" COMPONENT level-zero-devel)
