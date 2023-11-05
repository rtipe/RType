cmake_minimum_required(VERSION 3.22)

add_executable(RType-server index.cpp)

target_link_libraries(RType-server PUBLIC Uniti)
target_include_directories(RType-server PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(Plugins)

add_custom_command(
        TARGET RType-server
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Json
        ${CMAKE_BINARY_DIR}/bin/Json
)