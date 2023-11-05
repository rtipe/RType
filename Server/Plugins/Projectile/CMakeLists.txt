cmake_minimum_required(VERSION 3.22)

add_library(Projectile SHARED Projectile.cpp ../Entity/Entity.cpp)
target_link_libraries(Projectile PUBLIC Uniti)

target_include_directories(Projectile PUBLIC ".")

add_custom_command(
        TARGET Projectile
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Projectile>
        ${CMAKE_BINARY_DIR}/bin/ObjectPlugin/$<TARGET_FILE_NAME:Projectile>
)