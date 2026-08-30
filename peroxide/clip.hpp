#pragma once
/**
 * @file clip.hpp
 *
 * Global boolean switches to signal threads with.
 */
#include "miniaudio.h"
#include "hw7.hpp"
#include "types.hpp"

struct Clip
{
    Vector samples;
    ma_uint64 frames = 0;
    ma_uint32 channels = 0;
    ma_uint32 sampleRate = 0;
};

/**
 * Load a sound file into memory.
 * @return `true` if all frames were read.
 * @todo Move this function inside the `Clip` class.
 * @deprecated Replaced by `audio_clip::load`.
 */
bool loadClip(std::string filename, Clip &clip);

namespace h2o2
{

    class audio_clip
    {
    public:
        audio_clip() = default;
        audio_clip(const Path& p);

        /**
         * Load a sound file into memory.
         * @return `true` if all frames were read.
         * @todo Move this function inside the `Clip` class.
         */
        bool load(const hw7::str&);
        // static bool is_clip_name(const hw7::str&);


        static ma_uint32 get_clip_sampleRate();

        Path fp;
        Vector samples;
        ma_uint64 frames = 0;
        ma_uint32 channels = 0;
        ma_uint32 sampleRate = 0;
    };
}
