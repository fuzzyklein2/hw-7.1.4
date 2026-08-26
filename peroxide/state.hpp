#pragma once
/**
 * @file state.hpp
 *
 * Current state of the audio player.
 */
namespace h2o2
{

    enum class State
    {
        PAUSE, PLAY, FF, REWIND, STOP
    }; // State

} // h2o2