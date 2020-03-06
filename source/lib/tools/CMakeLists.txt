# Copyright (C) 2020 Intel Corporation
# SPDX-License-Identifier: MIT
set(TARGET_NAME zet_api)

if(MSVC)
add_library(${TARGET_NAME}
    STATIC
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

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(${TARGET_NAME}
    PRIVATE
        ZE_ENABLE_OCL_INTEROP=1
)

target_link_libraries(${TARGET_NAME}
    ${CMAKE_DL_LIBS}
)
else()
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
endif()

file(GLOB LEVEL_ZERO_LIBRARY_TOOLS_INCLUDES
    "*.h"
)

install(FILES ${LEVEL_ZERO_LIBRARY_TOOLS_INCLUDES}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/level_zero/lib/tools
    COMPONENT level-zero-devel
)
