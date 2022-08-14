#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer_ext.h>

#include <iostream>
#include <sstream>
#include <string>

#include "object.h"
#include "text.h"
#include "game.h"

Text::Text()
{
    this->x = 0;
    this->y = 0;
    this->scale = 1;
    this->antialiased = true;
    this->color = {255, 255, 255};
    this->font = Game::default_font;

    this->wrap_length = Game::width;
    
    set_text("");
}

/**
 * @brief Construct a new Text:: Text object and sets the 'text' to the text specified at 0, 0
 * 
 * @param text 
 */
Text::Text(std::string text)
{
    this->x = 0;
    this->y = 0;
    this->scale = 1;
    this->antialiased = true;
    this->color = {255, 255, 255};
    this->font = Game::default_font;

    this->wrap_length = Game::width;
    
    set_text(text);
}

/**
 * @brief Construct a new Text:: Text object and sets the 'text' to the text specified at x, y
 * 
 * @param x 
 * @param y 
 * @param text 
 */
Text::Text(float x, float y, std::string text)
{
    this->x = x;
    this->y = y;
    this->scale = 1;
    this->antialiased = true;
    this->color = {255, 255, 255};
    this->font = Game::default_font;

    this->wrap_length = Game::width;

    set_text(text);
}

/**
 * @brief Destroy the Text:: Text object and destroy the texture (haha no memory leaks)
 * 
 */
Text::~Text()
{
    SDL_DestroyTexture(texture);
}

/**
 * @brief Currently does nothing, because Text:: Text objects don't have special functions here.
 * 
 * @param elapsed 
 */
void Text::update(double elapsed) { }

/**
 * @brief Render the Text:: Text object to the screen.
 * 
 */
void Text::render()
{
    _sdl_dest.x = x;
    _sdl_dest.y = y;

    // set antialiasing to false or true for the current texture
    if (antialiased)
        SDL_SetTextureScaleMode(texture, SDL_ScaleModeLinear);
    else
        SDL_SetTextureScaleMode(texture, SDL_ScaleModeNearest);
    
    Game::window.render(texture, &_sdl_dest);
}

/**
 * @brief Set the 'text' variable for this Text:: Text object to the 'text' parameter
 * specified and also render it into the 'texture' variable.
 * 
 * @param text 
 */
void Text::set_text(std::string text)
{
    // set text value
    this->text = text;

    // no memory leaks???
    if (texture != nullptr)
        SDL_DestroyTexture(texture);

    // create texture
    SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, wrap_length);
    texture = SDL_CreateTextureFromSurface(Game::window.renderer, surface);

    // set width and height of destination SDL_Rect
    SDL_QueryTexture(texture, NULL, NULL, &_sdl_dest.w, &_sdl_dest.h);

    // account for scaling
    _sdl_dest.w *= scale;
    _sdl_dest.h *= scale;

    // free surface so no memory leaks
    SDL_FreeSurface(surface);
}