#pragma once
/**
 * @file globals.hpp
 *
 * Global boolean switches to signal threads with.
 */
#include "hw7.hpp"
#include "types.hpp"
struct Clip
{
    Vector samples;
    ma_uint64 frames = 0;
    ma_uint32 channels = 0;
    ma_uint32 sampleRate = 0;
};

bool loadClip(std::string filename, Clip &clip);
