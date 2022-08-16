#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "game.h"
#include "assets.h"
#include "note.h"
#include "conductor.h"

Note::Note(float x, float y, std::string sprite_path, float strum_time, int note_direction, float sustain_length)
{
    texture = Assets::get_image(sprite_path);

    this->x = x;
    this->y = y;
    this->antialiased = true;

    scale = 1;
    angle = 0;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    _sdl_src = {0, 0, width, height};
    _sdl_dest = {(int)x, (int)y, width, height};

    this->is_animated = true;

    this->strum_time = strum_time;
    this->note_direction = note_direction;
    this->sustain_length = sustain_length;

    last_frame_tick = Game::ticks;
    frame = 0;
    animation = "";

    frames = Assets::get_sparrow(sprite_path + ".xml");
    animations = {};
}

void Note::update(double elapsed)
{
    if (strum != nullptr)
        y = strum->y + (0.45f * ((Conductor::song_position - strum_time) * 2.6f));
    
    if (Conductor::song_position - Conductor::safe_zone_offset > strum_time)
        Note::~Note();
}