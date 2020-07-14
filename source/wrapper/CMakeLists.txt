

target_sources(${TARGET_LOADER_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_wprapi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_wprapi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zes_wprapi.cpp
)

file(GLOB LEVEL_ZERO_WRAPPER_CORE_INCLUDES
    "include/*.h*"
)

install(FILES ${LEVEL_ZERO_WRAPPER_CORE_INCLUDES}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/level_zero/
    COMPONENT level-zero-devel
)
