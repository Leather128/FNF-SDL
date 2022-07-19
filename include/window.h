#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

class Window
{
public:
    // window variables
    SDL_Window *window;
    SDL_Renderer *renderer;

    // class functions
    Window(const char *window_title, int window_w, int window_h);
    void destroy();

    // utilities
    SDL_Texture* load_texture(std::string file_path);
    
    // display stuff
    void clear();
    void display();

    // rendering textures
    void render(SDL_Texture* texture);
    void render(SDL_Texture* texture, const SDL_Rect *dest);
    void render(SDL_Texture* texture, const SDL_Rect *src, const SDL_Rect *dest);
};