cmake_minimum_required(VERSION 3.22)

add_library(Animation SHARED Animation.cpp)
target_link_libraries(Animation PUBLIC Uniti)

target_include_directories(Animation PUBLIC ".")

add_custom_command(
        TARGET Animation
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Animation>
        ${CMAKE_BINARY_DIR}/bin/ObjectPlugin/$<TARGET_FILE_NAME:Animation>
)