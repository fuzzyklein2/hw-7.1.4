/**
 * @file peroxide.cpp
 *
 * Peroxide class member functions.
 */

#include "peroxide.h"

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
    auto p = Peroxide(argc, argv);
    
    return p.run();
}