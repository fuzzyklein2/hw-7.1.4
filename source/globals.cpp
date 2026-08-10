/**
 * @file globals.cpp
 *
 * Define and initialize global variables.
 */

#include "sysinc.hpp"
using namespace std;

// Local headers
#include "config.hpp"
#include "constants.hpp"
#include "fs.hpp"
#include "globals.hpp"
#include "logging.hpp"

// Execution modes
bool _debug = true;   // Prefix input variables and options with '_'.
bool _verbose = false;
bool _version = false;

// Input variables
StrList _args;
string _input;

// Global logging variables
Logger logger;
LogLevel log_level = LogLevel::warn;

FileSystem FS;
JSON _config = configure(FS.config);
JSON _data = load_data(FS.data);