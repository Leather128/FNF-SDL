#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer_ext.h>

#include <vector>
#include <map>

#include "object.h"
#include "window.h"

enum KeyState
{
    RELEASED = 0,
    PRESSED = 1,
    JUST_RELEASED = 2,
    JUST_PRESSED = 3
};

/**
 * @brief Simple class to handle the lower level things relating to the game
 *
 */
class Game
{
public:
    static std::vector<Object *> objects; // list of all objects being rendered

    static Window window; // current window

    static int width;

    static int height;

    static TTF_Font *default_font; // used as a default font

    static const Uint8 *keyboard_state;
    static std::map<int, KeyState> keyboard;

    static void init();                 // gets called on program startup

    /**
     * @brief Calls update on all the active Objects with elapsed as the delta time
     * 
     * @param elapsed 
     */
    static void update(double elapsed);

    /**
     * @brief Calls render on all the active Objects
     * 
     */
    static void render();

    static double ticks;   // global timer of time elapsed since the program started

    static double elapsed; // global tracker of the current (or sometimes last, depends when you access it) frame's delta time
};