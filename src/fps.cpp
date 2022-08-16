#include <vector>
#include <sstream>

#include "external/memory_usage.h"

#include "fps.h"
#include "game.h"

FPS::FPS(float x, float y)
{
    this->x = x;
    this->y = y;

    update_values();
}

void FPS::update(double elapsed)
{
    tick_vector.push_back(Game::ticks);
    
    while (tick_vector.size() > 0 && Game::ticks - tick_vector[0] >= 1)
        tick_vector.erase(tick_vector.begin());

    _timer_tick += elapsed;
    
    if (_timer_tick >= 1)
    {
        update_values();
        _timer_tick = 0;
    }
}

void FPS::update_values()
{
    current_fps = tick_vector.size();

    current_memory = (int)(getCurrentRSS() / 104857.6f) / 10.0f;
    peak_memory = (int)(getPeakRSS() / 104857.6f) / 10.0f;

    std::stringstream stream;
    stream << "FPS: " << current_fps << "\nMemory: " << current_memory << "mb / " << peak_memory << "mb";

    set_text(stream.str());
}