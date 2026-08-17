/**
 * @file main.cpp
 *
 * Define main().
 */
#include "sysinc.hpp"

// Put this above local headers to reduce typing
using namespace std;

// Local headers
#include "globals.hpp"
#include "logging.hpp"

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
    Globals G(argc, argv);

    debug(format("{} initialized", hw7::PROGRAM));
    G.dump();
    
    return 0;
}