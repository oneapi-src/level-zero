set(TARGET_NAME zello_world)

add_executable(${TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/zello_world.cpp
)
    
if(MSVC)
    set_target_properties(${TARGET_NAME}
        PROPERTIES
            VS_DEBUGGER_COMMAND_ARGUMENTS ""
            VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
    )
endif()

target_link_libraries(${TARGET_NAME}
    ${TARGET_LOADER_NAME}
    ${CMAKE_DL_LIBS}
)
