target_sources(${TARGET_NAME} 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/zel_events_checker.h
        ${CMAKE_CURRENT_LIST_DIR}/zel_events_checker.cpp

        ${CMAKE_SOURCE_DIR}/third_party/xla/graphcycles.cc
)

target_include_directories(${TARGET_NAME} 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/third_party
)
