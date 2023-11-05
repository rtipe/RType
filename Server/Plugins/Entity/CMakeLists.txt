cmake_minimum_required(VERSION 3.22)

add_library(Entity SHARED Entity.cpp EntryPoint.cpp)
target_link_libraries(Entity PUBLIC Uniti)

target_include_directories(Entity PUBLIC ".")

add_custom_command(
        TARGET Entity
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Entity>
        ${CMAKE_BINARY_DIR}/bin/ObjectPlugin/$<TARGET_FILE_NAME:Entity>
)