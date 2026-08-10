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
extern bool _debug;   // Prefix input variables and options with '_'.
extern bool _verbose;
extern bool _version;

// Input variables
extern StrList _args;
extern String _input;

// Global logging variables
extern Logger logger;
extern LogLevel log_level;

extern FileSystem FS;
extern JSON _config;