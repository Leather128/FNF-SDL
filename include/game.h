#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer_ext.h>

#include <vector>

#include "object.h"
#include "window.h"

/**
 * @brief Simple class to handle the lower level things relating to the game
 * 
 */
class Game
{
    public:
        static std::vector<Object*> objects; // list of all objects being rendered

        static Window window; // current window

        static int width;
        static int height;

        static TTF_Font *default_font; // used as a default font

        static void init(); // gets called on program startup
        static void update(double elapsed); // gets called every frame to update the game with logic
        static void render(); // gets called every frame to render the current state of the game

        static double ticks; // global timer of time elapsed since the program started
        static double elapsed; // global tracker of the current (or sometimes last, depends when you access it) frame's delta time
};