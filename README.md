# FNF-SDL
FNF Made in C++ with SDL2 cuz I got bored or something idfk lool

# Building the game

## Dependencies

Currently you will need to be using Linux (hopefully Arch based distro) to build without tinkering.

The libraries required are: `sdl2`, `sdl2_image`, `sdl2_ttf`, `sdl2_mixer`, and `sdl2_mixer_ext`.

### SDL2_MIXER_EXT

`sdl2_mixer_ext` is a fork of the main `sdl2_mixer` library we use for multiple music tracks. To install it run the script `Install SDL2_mixer_ext.sh` from the project directory (Linux only for now).

## Building

The build system used for the project is CMake.

To make a build first run `cmake ./` in your terminal of choice while in the project directory to create build files.

Then run `make` to create an executable for the project and run the exetuable afterwards.