#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer_ext.h>

#include <string>

#include "object.h"

class Text : public Object
{
public:
    std::string text; // actual text variables
    TTF_Font *font;
    SDL_Color color;

    SDL_Texture *texture; // rendering
    SDL_Rect _sdl_dest;

    Uint32 wrap_length;

    bool antialiased;

    float x;
    float y;

    float scale;

    Text();
    Text(float x, float y, std::string text); // position
    Text(std::string text);                   // 0, 0
    virtual ~Text(void);

    virtual void update(double elapsed); // basic updates
    virtual void render();

    virtual void set_text(std::string text); // set text and update texture :scream:
};