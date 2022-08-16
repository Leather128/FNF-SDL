#pragma once

#include <vector>

#include "text.h"
#include "object.h"

/**
 * @brief Simple extension of the Text class that displays
 * the current framerate of the game (and some other info).
 * 
 */
class FPS : public Text
{
public:
    /**
     * @brief Current framerate of the game.
     * 
     */
    int current_fps;

    /**
     * @brief Game's current memory usage.
     * 
     */
    float current_memory;

    /**
     * @brief Game's peak memory usage.
     * 
     */
    float peak_memory;

    /**
     * @brief A std::vector of all the current ticks to calculate the framerate.
     * 
     */
    std::vector<double> tick_vector;

    /**
     * @brief Timer to track when to update the FPS counter.
     * (we use this because string manipulation is painfully slow)
     * 
     */
    double _timer_tick;

    /**
     * @brief Construct a new FPS::FPS object at x, y and update the values.
     * 
     * @param x 
     * @param y 
     */
    FPS(float x, float y);

    virtual ~FPS() = default;

    /**
     * @brief Update the current FPS and track game ticks to determine it.
     * 
     * @param elapsed 
     */
    virtual void update(double elapsed);

    /**
     * @brief Updates the current text value to the correct one (with memory included!).
     * 
     */
    virtual void update_values();
};