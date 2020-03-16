# Copyright (C) 2020 Intel Corporation
# SPDX-License-Identifier: MIT
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

if(UNIX)
set(TARGET_LOADER_NAME ze_loader)
include(GNUInstallDirs)
add_library(${TARGET_LOADER_NAME}
    SHARED
    ""
)
endif()

add_subdirectory(lib)
add_subdirectory(loader)
add_subdirectory(layers)
add_subdirectory(wrapper)

if(UNIX)
target_compile_definitions(${TARGET_LOADER_NAME}
    PRIVATE
        ZE_ENABLE_OCL_INTEROP=1
)

set_target_properties(${TARGET_LOADER_NAME} PROPERTIES
    VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
    SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
)

target_link_libraries(${TARGET_LOADER_NAME}
    ${CMAKE_DL_LIBS}
)

endif()

install(TARGETS ze_loader
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT level-zero
        NAMELINK_SKIP
)

install(TARGETS ze_loader
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT level-zero-devel
        NAMELINK_ONLY
)

file(GLOB_RECURSE LEVEL_ZERO_SOURCE_UTILITY_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h")

install(FILES ${LEVEL_ZERO_SOURCE_UTILITY_HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/level_zero/
    COMPONENT level-zero-devel
)
