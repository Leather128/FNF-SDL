#include <stdio.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "window.h"

/**
 * @brief Construct a new Window object
 * 
 * @param window_title 
 * @param window_w 
 * @param window_h 
 */
Window::Window(const char *window_title, int window_w, int window_h) : window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_w, window_h, SDL_WINDOW_SHOWN);

    if (window == NULL)
        printf("Window failed to exist in real life :scream: %s\n", SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        printf("Somehow, SDL_CreateRenderer has to use Software rendering :( %s\n", SDL_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

        if (renderer == NULL)
            printf("Ok so I guess SDL_CreateRenderer just isn't working, here is the error, %s\n", SDL_GetError());
    }
}

/**
 * @brief Cleans up SDL Variables relating to the Window object.
 * 
 */
void Window::destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

/**
 * @brief Loads and return an SDL_Texture from file_path.
 * 
 * @param file_path 
 * @return SDL_Texture* 
 */
SDL_Texture* Window::load_texture(std::string file_path)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, file_path.c_str());

    if (texture == NULL)
        printf("Couldn't find image %s with IMG_LoadTexture\n", file_path.c_str());
    
    return texture;
}

/**
 * @brief Clears the screen to start the next render with a blank slate.
 * 
 */
void Window::clear()
{
    SDL_RenderClear(renderer);
}

/**
 * @brief Renders the current texture to the screen.
 * 
 * @param texture 
 */
void Window::render(SDL_Texture *texture)
{
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}

/**
 * @brief Renders the current texture to the screen at the dest.
 * 
 * @param texture 
 * @param dest 
 */
void Window::render(SDL_Texture *texture, const SDL_Rect *dest)
{
    SDL_RenderCopy(renderer, texture, NULL, dest);
}

/**
 * @brief Renders src at current texture to the dest.
 * 
 * @param texture 
 * @param src 
 * @param dest 
 */
void Window::render(SDL_Texture *texture, const SDL_Rect *src, const SDL_Rect *dest)
{
    SDL_RenderCopy(renderer, texture, src, dest);
}

/**
 * @brief Displays the current frame onto the screen.
 * 
 */
void Window::display()
{
    SDL_RenderPresent(renderer);
}