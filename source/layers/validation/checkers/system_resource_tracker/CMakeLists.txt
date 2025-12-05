# System resource tracker is Linux-only (uses /proc/self/status)
if(UNIX AND NOT APPLE)
    target_sources(${TARGET_NAME} 
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/zel_system_resource_tracker_checker.h
            ${CMAKE_CURRENT_LIST_DIR}/zel_system_resource_tracker_checker.cpp
    )
endif()