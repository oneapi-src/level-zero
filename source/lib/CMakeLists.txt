

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
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_tracing_register_cb_libapi.cpp
)



if(WIN32)
    target_sources(${TARGET_LOADER_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/windows/lib_init.cpp
    )
else()
    target_sources(${TARGET_LOADER_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/linux/lib_init.cpp
    )
endif()

