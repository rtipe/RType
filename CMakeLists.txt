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

if (PACK)
    set(INSTALL_DIR bin)
    set(LIB_DIR bin/lib)
    set(EXT_DIR /bin/ext)
else (PACK)
    set(INSTALL_DIR ${PROJECT_BINARY_DIR}/bin)
    set(LIB_DIR ${PROJECT_BINARY_DIR}/bin/lib)
    set(EXT_DIR ${PROJECT_BINARY_DIR}/bin/ext)
endif (PACK)

set(CPACK_CMAKE_GENERATOR Ninja)
set(CPACK_PACKAGE_NAME "rtypeV2")
set(CPACK_PACKAGE_VERSION ${VERSION_GAME_ENGINE})
set(CPACK_PACKAGE_DESCRIPTION "rtype game !")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "rtypeV2")

set(CPACK_PACKAGE_CONTACT "younes1.bahri@epitech.eu")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_CONTACT}")
set(CPACK_SOURCE_INSTALLED_DIRECTORIES "${CMAKE_BINARY_DIR}/bin;/")

if (WIN32)
    set(CPACK_GENERATOR "NSIS")
elseif (APPLE)
    set(CPACK_GENERATOR "DragNDrop")
else ()
    set(CPACK_GENERATOR "DEB;RPM")
endif ()

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY FALSE)

include(CPack)