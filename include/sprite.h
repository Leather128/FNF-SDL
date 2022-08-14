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

        Sprite(float x, float y, std::string sprite_path);
        Sprite(float x, float y, std::string sprite_path, bool is_animated);  // constructor and destructor
        virtual ~Sprite(void);
        
        virtual void update(double elapsed); // basic updates
        virtual void render();

        virtual void set_size(float width, float height); // setting to specific pixel size cuz frick you

        virtual void play_animation(std::string name); // animation functions
        virtual void play_animation(std::string name, bool force);

        virtual void add_animation_by_prefix(std::string name, std::string prefix);
        virtual void add_animation_by_prefix(std::string name, std::string prefix, int fps);
        virtual void add_animation_by_prefix(std::string name, std::string prefix, bool looped);
        virtual void add_animation_by_prefix(std::string name, std::string prefix, int fps, bool looped);

        virtual void add_frames_by_prefix(std::string prefix, AnimationData *animation_data);

        virtual void add_offset(std::string name, SDL_Rect offset);
        virtual void center_offset(std::string to, std::string from); // center the offset of to, depending on from
};