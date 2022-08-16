#pragma once

#include <string>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer_ext.h>

/**
 * @brief Class to load cached assets easier.
 * 
 */
class Assets
{
public:
    /**
     * @brief An std::map to store the amount of times an asset is used (to calculate whether or not to delete it.)
     * 
     */
    static std::map<std::string, int> assets_use_counts;

    /**
     * @brief Map of std::string to SDL_Texture* to act as a cache for any image getting in future.
     * 
     */
    static std::map<std::string, SDL_Texture *> image_cache;

    /**
     * @brief Get and return the SDL_Texture* at path.
     * 
     * @param path 
     * @return SDL_Texture* 
     */
    static SDL_Texture *get_image(std::string path);

    /**
     * @brief Map of std::string to Mix_Chunk* to act as a cache for any sound getting in future.
     * 
     */
    static std::map<std::string, Mix_Chunk *> sound_cache;

    /**
     * @brief Get and return the Mix_Chunk* at path.
     * 
     * @param path 
     * @return Mix_Chunk* 
     */
    static Mix_Chunk *get_sound(std::string path);

    /**
     * @brief Get and return the Mix_Music* at path.
     * 
     * @param path 
     * @return Mix_Music* 
     */
    static Mix_Music *get_music(std::string path);

    /**
     * @brief Map of std::string to TTF_Font* to act as a cache for any sound getting in future.
     * 
     */
    static std::map<std::string, TTF_Font *> font_cache;

    /**
     * @brief Get and return the TTF_Font* at path.
     * 
     * @param path 
     * @return TTF_Font* 
     */
    static TTF_Font *get_font(std::string path);

    /**
     * @brief Returns a std::map<std::string, SDL_Rect> of animation frame names to their coordinates
     * on a spritesheet (with ones with an appended _offsets after for storing offsets)
     * 
     * @TODO: Possibly change the _offests system to a custom container of 2 SDL_Rect(s)?
     * 
     * @param sparrow_path 
     * @return std::map<std::string, SDL_Rect> 
     */
    static std::map<std::string, SDL_Rect> get_sparrow(std::string sparrow_path);
};