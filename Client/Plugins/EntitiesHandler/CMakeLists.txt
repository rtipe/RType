cmake_minimum_required(VERSION 3.22)

add_library(EntitiesHandler SHARED EntitiesHandler.cpp)
set_target_properties(EntitiesHandler PROPERTIES PREFIX "")
target_link_libraries(EntitiesHandler PUBLIC Uniti)

target_include_directories(EntitiesHandler PUBLIC ".")

add_custom_command(
        TARGET EntitiesHandler
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:EntitiesHandler>
        ${CMAKE_BINARY_DIR}/bin/ObjectPlugin/$<TARGET_FILE_NAME:EntitiesHandler>
)