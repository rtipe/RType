cmake_minimum_required(VERSION 3.22)
project(RType)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
include(GNUInstallDirs)

add_subdirectory(Libs)

add_subdirectory(Plugins)
add_subdirectory(Client)
add_subdirectory(Server)

install(DIRECTORY "${CMAKE_BINARY_DIR}/bin" DESTINATION ${CMAKE_INSTALL_BINDIR})

include(InstallRequiredSystemLibraries)

include(CPack)