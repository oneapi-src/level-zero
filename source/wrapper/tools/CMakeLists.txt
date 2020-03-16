set(TARGET_NAME zet_api_cpp)

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
    ze_api zet_api
    ${CMAKE_DL_LIBS}
)

file(GLOB LEVEL_ZERO_WRAPPER_TOOLS_INCLUDES
    "*.h*"
)

install(FILES ${LEVEL_ZERO_WRAPPER_TOOLS_INCLUDES}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/level_zero/wrapper/tools
    COMPONENT level-zero-devel
)