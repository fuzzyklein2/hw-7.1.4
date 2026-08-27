#pragma once
/**
 * @file song.hpp
 *
 * Find and parse the pattern script.
 */
#include "miniaudio.h"

#include "hw7.hpp"
#include "song_list.hpp"
namespace h2o2
{
    class player
    {
    public:
        player(const song_list&);
        void fill(float* output, ma_uint32 frames);
        void play() {playing = true;}
        /// Return the current clip.
        Clip clip() { return current_song.current_clip(); }
    protected:
        bool playing = false;
        bool step = false;
        size_t pos = 0;
        song_list songs;
        song current_song;
    }; // player
} // h2o2