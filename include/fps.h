#pragma once

#include <vector>

#include "text.h"
#include "object.h"

class FPS : public Text
{
    public:
        int current_fps; // values so that you can access them outside this class

        float current_memory;
        float peak_memory;

        std::vector<double> tick_vector; // contains a list of all the current tick values (used for calculating FPS)

        double _timer_tick; // a timer for when to update the FPS counter next (string manipulation is expensive with std::string, so we only update about every second)

        FPS(float x, float y);
        virtual ~FPS() = default;

        virtual void update(double elapsed); // calculates fps and stuff basically

        virtual void update_values(); // update the current text variable and variable values
};