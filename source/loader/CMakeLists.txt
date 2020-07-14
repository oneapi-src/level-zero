# Copyright (C) 2020 Intel Corporation
# SPDX-License-Identifier: MIT


target_sources(${TARGET_LOADER_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_object.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_ldrddi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_ldrddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_ldrddi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_ldrddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zes_ldrddi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/zes_ldrddi.cpp
)

if(WIN32)
    target_sources(${TARGET_LOADER_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/windows/driver_discovery_win.cpp
    )
else()
    target_sources(${TARGET_LOADER_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/linux/driver_discovery_lin.cpp
    )
endif()

