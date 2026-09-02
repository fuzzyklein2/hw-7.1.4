#pragma once
/**
 * @file globals.hpp
 *
 * Global boolean switches to signal threads with.
 */
#include "types.hpp"
#include "player.hpp"

extern Boolean pedal;
extern Boolean running;
/// Applies only to the current clip, not patterns.
extern Boolean repeat;
extern ProgPtr program;
extern h2o2::PlayerPtr player;
