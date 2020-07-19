cmake_minimum_required(VERSION 3.10)

project(fractal)

include(ExternalProject)

ExternalProject_Add(ext_sdl
    PREFIX "${CMAKE_BINARY_DIR}/external"
    URL "https://www.libsdl.org/release/SDL2-2.0.12.tar.gz"
    URL_HASH SHA256=349268f695c02efbc9b9148a70b85e58cefbbf704abd3e91be654db7f1e2c863
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external/installed
)
# ExternalProject_Add(ext_sdl_image
#     PREFIX "${CMAKE_BINARY_DIR}/external"
#     URL "https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.5-VC.zip"
#     URL_HASH SHA256=a180f9b75c4d3fbafe02af42c42463cc7bc488e763cfd1ec2ffb75678b4387ac
#     UPDATE_COMMAND ""
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND ""
#     INSTALL_COMMAND
#         ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/external/src/ext_sdl_image/include ${CMAKE_BINARY_DIR}/external/installed/include/SDL2
#         COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/external/src/ext_sdl_image/lib/${CMAKE_GENERATOR_PLATFORM} ${CMAKE_BINARY_DIR}/external/installed/lib

# )

# ExternalProject_Add(ext_sdl_ttf
#     PREFIX "${CMAKE_BINARY_DIR}/external"
#     URL "https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.15-VC.zip"
#     URL_HASH SHA256=aab0d81f1aa6fe654be412efc85829f2b188165dca6c90eb4b12b673f93e054b
#     UPDATE_COMMAND ""
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND ""
#     INSTALL_COMMAND
#         ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/external/src/ext_sdl_ttf/include ${CMAKE_BINARY_DIR}/external/installed/include/SDL2
#         COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/external/src/ext_sdl_ttf/lib/${CMAKE_GENERATOR_PLATFORM} ${CMAKE_BINARY_DIR}/external/installed/lib

# )

find_package(SDL2 HINTS ${CMAKE_BINARY_DIR}/external/installed)
# set(SDL2_IMAGE_LIBRARIES SDL2_image.lib)
# set(SDL2_TTF_LIBRARIES SDL2_ttf.lib)

add_executable(fractal
    src/main.cpp
    src/CApp.cpp
    src/Global.cpp
    )
set_property(GLOBAL PROPERTY CXX_STANDARD 17)
target_include_directories(fractal PRIVATE ${CMAKE_SOURCE_DIR}/src ${SDL2_INCLUDE_DIRS})
target_link_libraries(fractal PRIVATE SDL2::SDL2main)
