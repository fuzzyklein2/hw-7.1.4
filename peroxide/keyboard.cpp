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

    ostringstream oss;

    tcgetattr(STDIN_FILENO, &old_settings);
    new_settings = old_settings;

    new_settings.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

    while (running)
    {
        char c;

        if (read(STDIN_FILENO, &c, 1) == 1)
        {
            oss << "Keyboard event received: 0x"
                << std::hex
                << std::uppercase
                << static_cast<unsigned int>(static_cast<unsigned char>(c)) << endl;
            debug(oss);
            if (c == ' ')
                pedal = true;
            else if (c == '\x1B')
            {
                running = false; 
                exit(EXIT_SUCCESS);
            }
        }
    }
    debug("Exiting the program");
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
    // exit(EXIT_SUCCESS);
}

