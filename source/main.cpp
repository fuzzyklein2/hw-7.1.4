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

    // if (G.debug)
    // {
    //     ostringstream ss;
    //     ss << "Current working directory: " << G.FS.working;
    //     debug(ss);
    //     ss << "Home directory: " << G.FS.home;
    //     debug(ss);
    //     ss << "Base: " << G.FS.base;
    //     debug(ss);
    //     ss << "Configuration file: " << G.FS.config;
    //     debug(ss);
    //     ss << "Config directory: " << G.FS.config.parent_path();
    //     debug(ss);
    //     ss << "User directory: " << G.FS.user;
    //     debug(ss);
    //     ss << "Logs: " << G.FS.logs;
    //     debug(ss);
    //     ss << "Log file: " << G.FS.logfile;
    //     debug(ss);
    //     ss << "Data file: " << G.FS.data;
    //     debug(ss);
    // }
    
    return 0;
}