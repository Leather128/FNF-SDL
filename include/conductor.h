#pragma once

/**
 * @brief Simple class to hold music data (song position, current beat, etc.)
 * 
 */
class Conductor
{
public:
    /**
     * @brief Current time of the song (in milliseconds!)
     * 
     */
    static double song_position;

    static double safe_zone_offset;

    static int cur_beat;
    static int cur_step;
};