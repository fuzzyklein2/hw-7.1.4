#pragma once
/**
 * @file keyboard.hpp
 *
 * Listen for keyboard events.
 */

/**
 * Listen for events from the computer keyboard.
 * @bug This thread is not terminating. :D
 */
void keyboard_listener();