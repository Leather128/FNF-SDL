#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <map>
#include <vector>

#include "object.h"

struct AnimationData
{
    std::string name;
    std::vector<SDL_Rect> frames;
    std::vector<SDL_Rect> offsets;
    SDL_Rect offset;
    int fps;
    bool looped;
};

class Sprite : public Object
{
public:
    SDL_Texture *texture; // basic sprite variables
    std::string _texture_path;

    SDL_Rect _sdl_src;
    SDL_Rect _sdl_dest;

    bool _custom_sdl_dest;

    bool antialiased;

    float x;
    float y;

    int width;
    int height;

    float scale;
    double angle;

    bool is_animated; // animated sprite variables :scream
    bool animation_finished;

    int frame;
    double last_frame_tick;

    std::string animation;

    std::map<std::string, AnimationData> animations;
    std::map<std::string, SDL_Rect> frames;

    /**
     * @brief Default Sprite:: Sprite constructor
     * 
     */
    Sprite();

    /**
     * @brief Construct a new Sprite:: Sprite object at x, y pixels while loading sprite_path
     * 
     * @param x 
     * @param y 
     * @param sprite_path 
     */
    Sprite(float x, float y, std::string sprite_path);

    /**
     * @brief Construct a new Sprite:: Sprite object at x, y pixels while loading sprite_path (with an option to be animated)
     * 
     * @param x 
     * @param y 
     * @param sprite_path 
     * @param is_animated 
     */
    Sprite(float x, float y, std::string sprite_path, bool is_animated);
    
    /**
     * @brief Destroy the Sprite:: Sprite object and clear it's information from memory.
     * 
     */
    virtual ~Sprite(void);

    /**
     * @brief Update the sprite by elapsed with whatever stuff we are doing
     * 
     * @param elapsed 
     */
    virtual void update(double elapsed);

    /**
     * @brief Render the sprite with it's current properties
     * 
     */
    virtual void render();

    /**
     * @brief Sets the size of the sprite to a certain pixel value (if either is 0, it will be scaled by the amount the other is scaled by)
     * 
     * @param width 
     * @param height 
     */
    virtual void set_size(float width, float height); // setting to specific pixel size cuz frick you

    /**
     * @brief Play animation 'name' without forcing
     * 
     * @param name 
     */
    virtual void play_animation(std::string name); // animation functions

    /**
     * @brief Play animation 'name' with an option to 'force' it to play
     * 
     * @param name 
     * @param force 
     */
    virtual void play_animation(std::string name, bool force);

    /**
     * @brief Add animation to animations map by prefix
     * 
     * @param name 
     * @param prefix 
     */
    virtual void add_animation_by_prefix(std::string name, std::string prefix);

    /**
     * @brief Add animation to animations map by prefix at fps framerate
     * 
     * @param name 
     * @param prefix 
     * @param fps 
     */
    virtual void add_animation_by_prefix(std::string name, std::string prefix, int fps);

    /**
     * @brief Add animation to animations map by prefix with looped looping
     * 
     * @param name 
     * @param prefix 
     * @param looped 
     */
    virtual void add_animation_by_prefix(std::string name, std::string prefix, bool looped);

    /**
     * @brief Add animation to animations map by prefix at fps framerate with looped looping
     * 
     * @param name 
     * @param prefix 
     * @param fps 
     * @param looped 
     */
    virtual void add_animation_by_prefix(std::string name, std::string prefix, int fps, bool looped);

    /**
     * @brief Adds frames with prefix to animation_data
     * 
     * @param prefix 
     * @param animation_data 
     */
    virtual void add_frames_by_prefix(std::string prefix, AnimationData *animation_data);

    /**
     * @brief Add offset 'offset' to 'name' in the animations['name'].offset std::map
     * 
     * @param name 
     * @param offset 
     */
    virtual void add_offset(std::string name, SDL_Rect offset);

    /**
     * @brief Center the offset of `to` to match `from`.
     * 
     * @param to 
     * @param from 
     */
    virtual void center_offset(std::string to, std::string from);

    /**
     * @brief Center the offset of `to` (at `to_frame`) to match `from`.
     * 
     * @param to 
     * @param from 
     * @param to_frame
     */
    virtual void center_offset(std::string to, std::string from, int to_frame);

    /**
     * @brief Updates the `width` and `height` variables to be correct for the current animation and such.
     * 
     */
    virtual void update_xy_size();
};