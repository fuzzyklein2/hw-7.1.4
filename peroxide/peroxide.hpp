#pragma once
/**
 * @file peroxide.hpp
 *
 * Peroxide class.
 */
#include "miniaudio.h"

#include "hw7.hpp"

#include "globals.hpp"
#include "player.hpp"

void data_callback(ma_device*, void*, const void*, ma_uint32);
void signal_handler(int);

/**
 * Subclass `Program`.
 */
class Peroxide : Program
{
public:
    Peroxide(int argc, char **argv) : Program (argc, argv)
    {
        base = config["session folder"].get<std::string>();
    }

    void play_audio();
    ErrCode run();
protected:
    Path base;
    h2o2::song_list songs;
};

