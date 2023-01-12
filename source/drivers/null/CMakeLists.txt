set(TARGET_NAME ze_null)

add_library(${TARGET_NAME}
    SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_null.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_null.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ze_nullddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zet_nullddi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/zes_nullddi.cpp
)

set_target_properties(${TARGET_NAME} PROPERTIES
    VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if(INSTALL_NULL_DRIVER)
    install(TARGETS ze_null
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT level-zero
            NAMELINK_SKIP
    )
    install(TARGETS ze_null
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT level-zero-devel
        NAMELINK_ONLY
    )
endif()


if(UNIX)
    set(GCC_COVERAGE_COMPILE_FLAGS "-fvisibility=hidden -fvisibility-inlines-hidden -fno-strict-aliasing")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
endif()