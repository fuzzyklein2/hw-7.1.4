/**
 * @file sysinc.hpp
 *
 * Source code for precompiled header.
 */

// C Standard Library headers
#include <cstdlib>

// STL headers
#include <algorithm>
#include <chrono>     // datetime module
#include <filesystem> // pathlib equivalent
#include <fstream>    // file streams
#include <iomanip>    // ?
#include <iostream>   // cin & cout
#include <regex>      // regular expressions
#include <sstream>    // string streams
#include <stdexcept>  // exception handling
#include <string>     // Unicode strings, apparently.
#include <unistd.h>   // for isatty() and fileno()

// GNOME headers
#include <glib.h>

// Third party headers
#include <nlohmann/json.hpp> // JSON <-> struct conversion
#include "CLI11.hpp"         // Command line argument parser

// Logging module headers
#include "spdlog/spdlog.h"   // Logging module
#include "spdlog/sinks/stdout_color_sinks.h" // Screen output
#include "spdlog/sinks/basic_file_sink.h" // Log file(s)

// GUI headers
#include <gtkmm.h> // GTK wrapper

