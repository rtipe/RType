cmake_minimum_required(VERSION 3.22)

add_library(WaveSpawn SHARED WaveSpawn.cpp)
target_link_libraries(WaveSpawn PUBLIC Uniti)

target_include_directories(WaveSpawn PUBLIC ".")

add_custom_command(
        TARGET WaveSpawn
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:WaveSpawn>
        ${CMAKE_BINARY_DIR}/bin/ObjectPlugin/$<TARGET_FILE_NAME:WaveSpawn>
)