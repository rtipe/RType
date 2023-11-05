cmake_minimum_required(VERSION 3.22)

add_library(UserController SHARED UserController.cpp)
set_target_properties(UserController PROPERTIES PREFIX "")
target_link_libraries(UserController PUBLIC Uniti)

target_include_directories(UserController PUBLIC ".")

add_custom_command(
        TARGET UserController
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:UserController>
        ${CMAKE_BINARY_DIR}/bin/ObjectPlugin/$<TARGET_FILE_NAME:UserController>
)