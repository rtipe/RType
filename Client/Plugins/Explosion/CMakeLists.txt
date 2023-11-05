cmake_minimum_required(VERSION 3.22)

add_library(Explosion SHARED Explosion.cpp)
set_target_properties(Explosion PROPERTIES PREFIX "")
target_link_libraries(Explosion PUBLIC Uniti)

target_include_directories(Explosion PUBLIC ".")

add_custom_command(
        TARGET Explosion
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Explosion>
        ${CMAKE_BINARY_DIR}/bin/ObjectPlugin/$<TARGET_FILE_NAME:Explosion>
)