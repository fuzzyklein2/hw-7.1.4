/**
 * @file cli.cpp
 *
 * Functions that collect input from the command line.
 */

#include "sysinc.hpp"
using namespace std;

// Local headers
#include "cli.hpp"
#include "constants.hpp"
#include "globals.hpp"

using hello7::constants;

/**
 * getargs
 *
 * @brief Parse the command line.
 *
 * Parses the command line, initializes the application, and starts
 * the main processing loop.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 *
 * @return Exit status.
 */
int getargs(
    int argc,   // Argument count
    char **argv // Cannot be `const` or CLI11 won't work.
)
{
    // Initialize CLI11 object
    CLI::App app{DESCRIPTION};
    argv = app.ensure_utf8(argv);

    // Add options and arguments
    app.add_flag("-d,--debug", _debug, _help[DEBUG_KEY]);
    app.add_flag("-v,--verbose", _verbose, _help[VERBOSE_KEY]);
    app.add_flag("-V,--version", _version, _help[VERSION_KEY]);
    app.add_option("files", _args, _help[ARGS_KEY]);
    // Indexing _help with brackets can cause accidental insertions by mistyped keys.
    
    // Parse the command line arguments
    CLI11_PARSE(app, argc, argv);

    return 0;
}

void get_piped()
{
    // Check if stdin is a terminal (not piped)
    if (!isatty(fileno(stdin))) { // There is piped input
        ostringstream oss;
        oss << cin.rdbuf(); // Read standard input into the sstream.
        _input = oss.str(); // Make input access global.
        // Remove trailing newline (optional, improves output for typical use)
        if (!_input.empty() && _input.back() == '\n')
        {
            _input.pop_back();
        }
    } else _input = WORLD; // Remove or replace `WORLD` here as appropriate.

}