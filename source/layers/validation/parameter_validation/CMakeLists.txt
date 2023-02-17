target_sources(${TARGET_NAME} 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/param_validation.h
        ${CMAKE_CURRENT_LIST_DIR}/ze_parameter_validation.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ze_parameter_validation.h
        ${CMAKE_CURRENT_LIST_DIR}/zes_parameter_validation.cpp
        ${CMAKE_CURRENT_LIST_DIR}/zes_parameter_validation.h
        ${CMAKE_CURRENT_LIST_DIR}/zet_parameter_validation.cpp    
        ${CMAKE_CURRENT_LIST_DIR}/zet_parameter_validation.h
)

