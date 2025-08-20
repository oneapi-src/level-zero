target_sources(${TARGET_NAME} 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/zel_events_checker.h
        ${CMAKE_CURRENT_LIST_DIR}/zel_events_checker.cpp

        ${THIRD_PARTY_SOURCE_DIR}/xla/graphcycles.cc
)

target_include_directories(${TARGET_NAME} 
    PRIVATE
        ${THIRD_PARTY_SOURCE_DIR}
)
