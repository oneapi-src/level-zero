

target_sources(${TARGET_LOADER_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_libapi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_libddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_libapi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_libddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zes_libapi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zes_libddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zel_tracing_libapi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zel_tracing_libddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_lib.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_lib.cpp
)
