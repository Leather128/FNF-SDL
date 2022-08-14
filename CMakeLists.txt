cmake_minimum_required(VERSION 3.23.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -Wall -std=c++20")

project(Funkin)

find_package(SDL2 REQUIRED)

set(SOURCE_FILES 
    src/main.cpp
    src/window.cpp
    src/game.cpp
    src/object.cpp
    src/text.cpp
    src/sprite.cpp
    src/system_paths.cpp
    src/fps.cpp
    src/sparrow_helper.cpp
    src/external/xml_parser.cpp
)

add_executable(Funkin ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)

set(SDL2MIXER_LIBRARIES
    /usr/local/lib/libSDL2_mixer_ext.a
    /usr/local/lib/libSDL2_mixer_ext.so
    /usr/local/lib/libSDL2_mixer_ext.so.2
    /usr/local/lib/libSDL2_mixer_ext.so.2.6.0.0
)

INCLUDE_DIRECTORIES(include/ ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})