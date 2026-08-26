/**
 * @file keyboard.cpp
 *
 * Play a sequence of sound clips according to the `song_list`.
 */
#include <termios.h>
#include "hw7.hpp"
#include "globals.hpp"
#include "keyboard.hpp"
#include "player.hpp"
using namespace std;
using namespace hw7;
using namespace h2o2;

void keyboard_listener()
{
    termios old_settings;
    termios new_settings;

    tcgetattr(STDIN_FILENO, &old_settings);
    new_settings = old_settings;

    new_settings.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

    while (running)
    {
        char c;

        if (read(STDIN_FILENO, &c, 1) == 1)
        {
            debug("Keyboard event received: " + c);
            if (c == ' ')
                pedal = true;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
}

