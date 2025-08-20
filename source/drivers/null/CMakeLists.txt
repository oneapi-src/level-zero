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
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT level-zero-devel
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT level-zero
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT level-zero
        NAMELINK_COMPONENT level-zero-devel
    )
endif()

if (BUILD_L0_LOADER_TESTS)
add_library(ze_null_test1 SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_null.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_null.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_nullddi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zet_nullddi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zes_nullddi.cpp
)

add_library(ze_null_test2 SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_null.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_null.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ze_nullddi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zet_nullddi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zes_nullddi.cpp
)

set_target_properties(ze_null_test1 PROPERTIES
    VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
)

set_target_properties(ze_null_test2 PROPERTIES
    VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
)

target_include_directories(ze_null_test1
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(ze_null_test2
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(ze_null_test1 PUBLIC ZEL_NULL_DRIVER_ID=1)
target_compile_definitions(ze_null_test2 PUBLIC ZEL_NULL_DRIVER_ID=2)
target_compile_definitions(ze_null PUBLIC ZEL_NULL_DRIVER_ID=1)

if(INSTALL_NULL_DRIVER)
    install(TARGETS ze_null_test1
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT level-zero-devel
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT level-zero
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT level-zero
        NAMELINK_COMPONENT level-zero-devel
    )
    install(TARGETS ze_null_test2
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT level-zero-devel
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT level-zero
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT level-zero
        NAMELINK_COMPONENT level-zero-devel
    )
endif()
endif()

if(UNIX)
    set(GCC_COVERAGE_COMPILE_FLAGS "-fvisibility=hidden -fvisibility-inlines-hidden -fno-strict-aliasing")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
endif()