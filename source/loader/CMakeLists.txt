# Copyright (C) 2020 Intel Corporation
# SPDX-License-Identifier: MIT


target_sources(${TARGET_LOADER_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_object.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader_internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader_api.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_ldrddi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_ldrddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_ldrddi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_ldrddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zes_ldrddi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/zes_ldrddi.cpp
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

