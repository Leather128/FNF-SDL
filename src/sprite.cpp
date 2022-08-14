#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <algorithm>
#include <stdio.h>
#include <iostream>

#include "sprite.h"
#include "object.h"
#include "window.h"
#include "game.h"
#include "system_paths.h"
#include "sparrow_helper.h"

/**
 * @brief Construct a new Sprite:: Sprite object at x, y pixels while loading sprite_path
 * 
 * @param x 
 * @param y 
 * @param sprite_path 
 */
Sprite::Sprite(float x, float y, std::string sprite_path)
{
    texture = Game::window.load_texture(Paths::get_system_path((sprite_path + ".png").c_str()));

    this->x = x;
    this->y = y;
    this->antialiased = true;

    scale = 1;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    _sdl_src = {0, 0, width, height};
    _sdl_dest = {(int)x, (int)y, width, height};
}

/**
 * @brief Construct a new Sprite:: Sprite object at x, y pixels while loading sprite_path (with an option to be animated)
 * 
 * @param x 
 * @param y 
 * @param sprite_path 
 * @param is_animated 
 */
Sprite::Sprite(float x, float y, std::string sprite_path, bool is_animated)
{
    texture = Game::window.load_texture(Paths::get_system_path((sprite_path + ".png").c_str()));

    this->x = x;
    this->y = y;
    this->antialiased = true;

    scale = 1;

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    _sdl_src = {0, 0, width, height};
    _sdl_dest = {(int)x, (int)y, width, height};

    this->is_animated = is_animated;

    if (is_animated)
    {
        last_frame_tick = Game::ticks;
        frame = 0;
        animation = "";

        frames = SparrowHelper::get_sparrow(sprite_path + ".xml");
        animations = {};
    }
}

/**
 * @brief Destroy the Sprite:: Sprite object and clear it's information from memory.
 * 
 */
Sprite::~Sprite()
{
    SDL_DestroyTexture(texture);
}

/**
 * @brief Update the sprite by elapsed with whatever stuff we are doing
 * 
 * @param elapsed 
 */
void Sprite::update(double elapsed)
{
    // set frame values
    if (is_animated)
    {
        if (animations.contains(animation))
        {
            // check if 1 / animation fps time has passed (for next frame)
            if (Game::ticks - last_frame_tick >= 1.0f / (float)animations[animation].fps)
            {
                animation_finished = false;

                last_frame_tick = Game::ticks;

                frame += 1;

                if (frame >= (int)animations[animation].frames.size() - 1)
                {
                    if (animations[animation].looped)
                        frame = 0;
                    else
                    {
                        animation_finished = true;
                        frame = animations[animation].frames.size() - 1;
                    }
                }
            }
        }
    }
}

/**
 * @brief Render the sprite with it's current properties
 * 
 */
void Sprite::render()
{
    _sdl_dest.x = x;
    _sdl_dest.y = y;

    // add animation offsets to dest
    if (is_animated)
    {
        if (animations.contains(animation))
        {
            if (animations[animation].frames.size() > 0 && (int)animations[animation].offsets.size() > 0)
            {
                _sdl_src = animations[animation].frames[frame];

                width = _sdl_src.w;
                height = _sdl_src.h;

                _sdl_dest.x -= animations[animation].offsets[frame].x;
                _sdl_dest.y -= animations[animation].offsets[frame].y;
            }

            _sdl_dest.x -= animations[animation].offset.x;
            _sdl_dest.y -= animations[animation].offset.y;
        }
    }

    // yees we use da funny
    _sdl_dest.w = (int)(width * scale);
    _sdl_dest.h = (int)(height * scale);

    // set antialiasing to false or true for the current texture
    if (antialiased)
        SDL_SetTextureScaleMode(texture, SDL_ScaleModeLinear);
    else
        SDL_SetTextureScaleMode(texture, SDL_ScaleModeNearest);

    // render to window :scream: (but only if on screen)
    if (Window::rect_on_screen(&_sdl_dest))
        Game::window.render(texture, &_sdl_src, &_sdl_dest);
}

/**
 * @brief Add animation to animations map by prefix
 * 
 * @param name 
 * @param prefix 
 */
void Sprite::add_animation_by_prefix(std::string name, std::string prefix)
{
    AnimationData animation_data = {name, {}, {}, {0, 0, width, height}, 24, false};
    add_frames_by_prefix(prefix, &animation_data);
    animations[name] = animation_data;
}

/**
 * @brief Add animation to animations map by prefix at fps framerate
 * 
 * @param name 
 * @param prefix 
 * @param fps 
 */
void Sprite::add_animation_by_prefix(std::string name, std::string prefix, int fps)
{
    AnimationData animation_data = {name, {}, {}, {0, 0, width, height}, fps, false};
    add_frames_by_prefix(prefix, &animation_data);
    animations[name] = animation_data;
}

/**
 * @brief Add animation to animations map by prefix with looped looping
 * 
 * @param name 
 * @param prefix 
 * @param looped 
 */
void Sprite::add_animation_by_prefix(std::string name, std::string prefix, bool looped)
{
    AnimationData animation_data = {name, {}, {}, {0, 0, width, height}, 24, looped};
    add_frames_by_prefix(prefix, &animation_data);
    animations[name] = animation_data;
}

/**
 * @brief Add animation to animations map by prefix at fps framerate with looped looping
 * 
 * @param name 
 * @param prefix 
 * @param fps 
 * @param looped 
 */
void Sprite::add_animation_by_prefix(std::string name, std::string prefix, int fps, bool looped)
{
    AnimationData animation_data = {name, {}, {}, {0, 0, width, height}, fps, looped};
    add_frames_by_prefix(prefix, &animation_data);
    animations[name] = animation_data;
}

/**
 * @brief Play animation 'name' without forcing
 * 
 * @param name 
 */
void Sprite::play_animation(std::string name)
{
    Sprite::play_animation(name, false);
}

/**
 * @brief Play animation 'name' with an option to 'force' it to play
 * 
 * @param name 
 * @param force 
 */
void Sprite::play_animation(std::string name, bool force)
{
    if (force || !animations.contains(animation) || frame == (int)animations[animation].frames.size() - 1)
    {
        animation = name;
        frame = 0;
        last_frame_tick = Game::ticks;
    }
}

/**
 * @brief Adds frames with prefix to animation_data
 * 
 * @param prefix 
 * @param animation_data 
 */
void Sprite::add_frames_by_prefix(std::string prefix, AnimationData *animation_data)
{
    for (auto const& [key, val] : frames)
    {
        if (key.starts_with(prefix) && !key.ends_with("_offsets"))
            animation_data->frames.push_back(val);
        else if (key.starts_with(prefix) && key.ends_with("_offsets"))
            animation_data->offsets.push_back(val);
    }
}

/**
 * @brief Add offset 'offset' to 'name' in the animations['name'].offset std::map
 * 
 * @param name 
 * @param offset 
 */
void Sprite::add_offset(std::string name, SDL_Rect offset)
{
    if (animations.contains(name))
        animations[name].offset = offset;
}

/**
 * @brief Sets the size of the sprite to a certain pixel value (if either is 0, it will be scaled by the amount the other is scaled by)
 * 
 * @param width 
 * @param height 
 */
void Sprite::set_size(float width, float height)
{
    if (width != 0 && height != 0)
    {
        this->width = width;
        this->height = height;
    }
    else if (height == 0)
    {
        this->height *= (width / this->width);
        this->width = width;
    }
    else if (width == 0)
    {
        this->width *= height / this->height;
        this->height = height;
    }
}