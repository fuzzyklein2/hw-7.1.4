/**
 * @file main.cpp
 *
 * Define main().
 */
#include "sysinc.hpp"

// Put this above local headers to reduce typing
using namespace std;

// Local headers
#include "cli.hpp"
#include "config.hpp"
#include "constants.hpp"
#include "datetime.hpp"
#include "fs.hpp"
#include "globals.hpp"
#include "logging.hpp"

// Type aliases
using JSON = nlohmann::json;
using Path = filesystem::path;

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
    getargs(argc, argv);
    
    if (_version) // Display the program and version number, then exit.
    {
        cout << PROGRAM << SPACE << VERSION << endl;
        return 0;
    }
    
    if (_debug) _verbose = true;
    if (_verbose) cout << (_debug ? "Debugg" : "Runn") << "ing " << argv[0] << "." << endl;

    // Get piped input
    get_piped();

    // Set up logs
    init_logs();

    debug("program initialized");

    if (_debug)
    {
        ostringstream ss;
        ss << "Current working directory: " << FS.working;
        debug(ss);
        ss << "Home directory: " << FS.home;
        debug(ss);
        ss << "Base: " << FS.base;
        debug(ss);
        ss << "Configuration file: " << FS.config;
        debug(ss);
        ss << "Config directory: " << FS.config.parent_path();
        debug(ss);
        ss << "User directory: " << FS.user;
        debug(ss);
        ss << "Logs: " << FS.logs;
        debug(ss);
        ss << "Log file: " << FS.logfile;
        debug(ss);
        ss << "Data file: " << FS.data;
        debug(ss);
    }
    
    return 0;
}