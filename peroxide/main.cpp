/**
 * @file peroxide.cpp
 *
 * Peroxide class member functions.
 *
 * @bug Sometimes the log file is empty. Any log file that exists should have some content.
 *      This might be due to debugging sessions messing it up somehow. I've seen it twice now.
 *      In between sightings I saw a log file with content, so it's kind of a mystery.
 */

#include "peroxide.hpp"

using namespace std;

/**
 * main
 *
 * @brief Entry point of the program.
 *
 * Parses the command line, initializes the application, and starts
 * the main processing loop.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 *
 * @return Exit status.
 */
int main(
    int argc, // Argument count
    char **argv // Cannot be `const` or CLI11 won't work.
) {
    program = make_unique<Peroxide>(argc, argv);
    return program->run();
}
