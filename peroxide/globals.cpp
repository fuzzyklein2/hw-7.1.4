/**
 * @file globals.cpp
 *
 * Define globals outside of the Globals class for threads.
 */

#include "globals.hpp"
#include "player.hpp"

using namespace h2o2;

Boolean pedal = false;
Boolean running{true};
Boolean repeat = false;
ProgPtr program = nullptr;
PlayerPtr player = nullptr;

