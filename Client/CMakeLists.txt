cmake_minimum_required(VERSION 3.22)

add_executable(RType-client index.cpp)

target_link_libraries(RType-client PUBLIC Uniti)
target_include_directories(RType-client PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(Plugins)

add_custom_command(
        TARGET RType-client
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Assets
        ${CMAKE_BINARY_DIR}/bin/Assets
)
add_custom_command(
        TARGET RType-client
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Json
        ${CMAKE_BINARY_DIR}/bin/Json
)