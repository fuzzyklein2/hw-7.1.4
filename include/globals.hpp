#pragma once
/**
 * @file globals.hpp
 *
 * Declare global variables.
 */

// System headers
#include <map>
#include <string>
#include <vector>

// Local headers
#include "fs.hpp"
#include "types.hpp"

// Execution modes
// extern bool _debug;   // Prefix input variables and options with '_'.
// extern bool _verbose;
// extern bool _version;

// // Input variables
// extern StrList _args;
// extern String _input;

// // Global logging variables
// extern Logger logger;
// extern LogLevel log_level;

// // File system
// extern FileSystem FS;

// // Configuration
// extern JSON _config;
// extern JSON _data;

struct Globals {
    FileSystem FS;
    JSON config;
    JSON data;
    bool debug;
    bool verbose;
    bool version = false;
    StrList args;
    String input;
    // Log log;

    Globals(int, char**); // constructor
    int getargs(int, char**);
    void get_piped();
    void init_logs();
};

