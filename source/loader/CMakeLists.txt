# Copyright (C) 2020-2026 Intel Corporation
# SPDX-License-Identifier: MIT


target_sources(${TARGET_LOADER_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_object.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader_internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader_api.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_ldrddi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_ldrddi_driver_ddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_ldrddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_ldrddi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_ldrddi_driver_ddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_ldrddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zes_ldrddi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/zes_ldrddi_driver_ddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zes_ldrddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zer_ldrddi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/zer_ldrddi_driver_ddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zer_ldrddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zel_tracing_ldrddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/driver_discovery.h
)

if(WIN32)
    target_sources(${TARGET_LOADER_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/windows/driver_discovery_win.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/windows/loader_init.cpp
    )
else()
    target_sources(${TARGET_LOADER_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/linux/driver_discovery_lin.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/linux/loader_init.cpp
    )
endif()

# An optional build-time configured directory to search for drivers, in
# addition to LD_LIBRARY_PATH and the system locations.  Packaging (e.g.
# conda-forge) sets this to the install prefix's lib dir so that a driver
# co-installed in the same prefix is discovered by default.  CMake handles the
# string quoting for the compile definition.
if(DEFINED L0_LOADER_EXTRA_DRIVER_DIR AND NOT L0_LOADER_EXTRA_DRIVER_DIR STREQUAL "")
    target_compile_definitions(${TARGET_LOADER_NAME}
        PRIVATE L0_LOADER_EXTRA_DRIVER_DIR="${L0_LOADER_EXTRA_DRIVER_DIR}")
endif()

