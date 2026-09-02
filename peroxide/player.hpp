#pragma once
/**
 * @file player.hpp
 *
 * Find and parse the pattern script.
 */
#include "miniaudio.h"

#include "hw7.hpp"
#include "song_list.hpp"

namespace h2o2
{
    class audio_player
    {
    public:
        audio_player(song_list&);
        void fill(float* output, ma_uint32 frames);
        void play() {playing = true;}
        /// Return the current clip.
        // h2o2::audio_clip clip() { return current_song.current_clip(); }

        song_list& songs;
        Index current_song_index;
    protected:
        bool playing = false;
        bool step = false;
        size_t pos = 0;
    }; // player

    using PlayerPtr = std::unique_ptr<audio_player>;
} // h2o2