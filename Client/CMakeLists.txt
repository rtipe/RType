cmake_minimum_required(VERSION 3.22)

add_executable(RType-client index.cpp)

target_link_libraries(RType-client PUBLIC Uniti)
target_include_directories(RType-client PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(Plugins)