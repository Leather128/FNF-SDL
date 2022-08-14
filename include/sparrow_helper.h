#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <map>
#include <string>

class SparrowHelper
{
    public:
        static std::map<std::string, SDL_Rect> get_sparrow(std::string sparrow_path);
};