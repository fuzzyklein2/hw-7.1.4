#pragma once
/**
 * @file logging.hpp
 *
 * Declare logging functions.
 */

#include <filesystem>
#include <string>

// Local headers
#include "constants.hpp"
// #include "fs.hpp"

// File system

Path defaultLogFile();
String log_filename();
void init_logs();
void debug(const String& s);
void info(const String& s);
void warn(const String& s);
void error(const String& s);
void stop(const String& s);

void debug(ostringstream& ss);

void rotate_logs(const Path& directory, size_t count);
