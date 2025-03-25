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
if (BUILD_STATIC)
    message(STATUS "Building loader as static library")
    add_library(${TARGET_LOADER_NAME}
        STATIC
        ""
        ${CMAKE_CURRENT_BINARY_DIR}/ZeLoaderVersion.rc
    )
    add_definitions(-DDYNAMIC_LOAD_LOADER="1")
else()
    message(STATUS "Building loader as dynamic library")
    add_library(${TARGET_LOADER_NAME}
        SHARED
        ""
        ${CMAKE_CURRENT_BINARY_DIR}/ZeLoaderVersion.rc
    )
endif()

if(MSVC AND L0_DLL_INTEGRITY_CHECKS)
    set_target_properties(ze_loader PROPERTIES LINK_FLAGS "${CMAKE_CXX_LINKER_WRAPPER_FLAG}/INTEGRITYCHECK")
endif()

add_subdirectory(lib)
if (NOT BUILD_STATIC)
    add_subdirectory(loader)
    add_subdirectory(layers)
endif()
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

set(SDK_COMPONENT_STRING "level-zero-devel")
set(LIB_COMPONENT_STRING "level-zero")

if(BUILD_INSTALLER)
    set(SDK_COMPONENT_STRING "SDK")
    set(LIB_COMPONENT_STRING "Loader")
endif()

install(TARGETS ze_loader
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT ${SDK_COMPONENT_STRING}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT ${LIB_COMPONENT_STRING}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT ${LIB_COMPONENT_STRING}
    NAMELINK_COMPONENT ${SDK_COMPONENT_STRING}
)

if(NOT BUILD_INSTALLER)
file(RELATIVE_PATH pkgconfig_prefix "${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig" "${CMAKE_INSTALL_PREFIX}")
file(RELATIVE_PATH pkgconfig_include_dir "${CMAKE_INSTALL_PREFIX}" "${CMAKE_INSTALL_FULL_INCLUDEDIR}")
file(RELATIVE_PATH pkgconfig_lib_dir "${CMAKE_INSTALL_PREFIX}" "${CMAKE_INSTALL_FULL_LIBDIR}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libze_loader.pc.in ${CMAKE_CURRENT_BINARY_DIR}/libze_loader.pc @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/level-zero.pc.in ${CMAKE_CURRENT_BINARY_DIR}/level-zero.pc @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/libze_loader.pc"
              "${CMAKE_CURRENT_BINARY_DIR}/level-zero.pc"
        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig" COMPONENT ${SDK_COMPONENT_STRING})
endif()
