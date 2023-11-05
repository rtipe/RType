cmake_minimum_required(VERSION 3.22)

add_library(PlayerController SHARED PlayerController.cpp)
set_target_properties(PlayerController PROPERTIES PREFIX "")
target_link_libraries(PlayerController PUBLIC Uniti)

target_include_directories(PlayerController PUBLIC ".")

add_custom_command(
        TARGET PlayerController
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:PlayerController>
        ${CMAKE_BINARY_DIR}/bin/ObjectPlugin/$<TARGET_FILE_NAME:PlayerController>
)