#pragma once

#include "sprite.h"

class Note : public Sprite
{
public:
    float strum_time;
    int note_direction;
    float sustain_length;

    /**
     * @brief Pointer to the current strum this note is connected to.
     * 
     */
    Sprite *strum;

    /**
     * @brief Construct a new Note:: Note object at x, y pixels while loading sprite_path (oh and using strum_time, note_direction, and sustain_length)
     * 
     * @param x 
     * @param y 
     * @param sprite_path 
     * @param strum_time
     * @param note_direction
     * @param sustain_length
     */
    Note(float x, float y, std::string sprite_path, float strum_time, int note_direction, float sustain_length);

    virtual ~Note(void) = default;

    /**
     * @brief Update positioning and such for the note before rendering.
     * 
     * @param elapsed 
     */
    virtual void update(double elapsed);
};