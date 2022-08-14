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
    SDL_Surface *screen;

    // class functions

    Window();
    Window(const char *window_title, int window_w, int window_h);
    void destroy();

    // utilities

    SDL_Texture* load_texture(std::string file_path);
    bool static rect_on_screen(const SDL_Rect *rect);
    
    // display stuff

    void clear();
    void display();

    // rendering textures

    void render(SDL_Texture* texture);
    void render(SDL_Texture* texture, const SDL_Rect *dest);
    void render(SDL_Texture* texture, const SDL_Rect *src, const SDL_Rect *dest);

    void set_antialiased(bool antialiased);
};