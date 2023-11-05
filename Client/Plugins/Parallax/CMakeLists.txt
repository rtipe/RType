cmake_minimum_required(VERSION 3.22)

add_library(Parallax SHARED Parallax.cpp)
set_target_properties(Parallax PROPERTIES PREFIX "")
target_link_libraries(Parallax PUBLIC Uniti)

target_include_directories(Parallax PUBLIC ".")

add_custom_command(
        TARGET Parallax
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Parallax>
        ${CMAKE_BINARY_DIR}/bin/ObjectPlugin/$<TARGET_FILE_NAME:Parallax>
)