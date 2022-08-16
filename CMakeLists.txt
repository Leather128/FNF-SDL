cmake_minimum_required(VERSION 3.23.3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -Wall -std=c++20 -I/usr/local/include -L/usr/local/lib -Bstatic")

project(Funkin)

find_package(SDL2 REQUIRED)

set(SOURCE_FILES 
    src/main.cpp
    src/window.cpp
    src/game.cpp
    src/system_paths.cpp
    src/assets.cpp
    src/object.cpp
    src/sprite.cpp
    src/external/xml_parser.cpp
    src/note.cpp
    src/text.cpp
    src/fps.cpp
)

add_executable(Funkin ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer)

set(LIBRARIES
    SDL2_mixer_ext
    opusfile
    opus
    ogg
    xmp
    modplug
    ADLMIDI
    OPNMIDI
    EDMIDI
    gme
    zlib
)

INCLUDE_DIRECTORIES(include/ ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${LIBRARIES})