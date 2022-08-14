#include <string>
#include <SDL2/SDL.h>

#include "system_paths.h"

std::string Paths::cwd;

void Paths::init()
{
    Paths::cwd = std::string(SDL_GetBasePath());
}

std::string Paths::get_system_path(std::string local_path)
{
    if (Paths::cwd == "")
        Paths::init();

    return Paths::cwd + "/" + local_path;
}