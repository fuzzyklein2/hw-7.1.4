#pragma once
/**
 * @file logging.hpp
 *
 * Declare logging functions.
 *
 * @todo Add `--logfile` option and make it relevant.
 * @todo Only delete files that have a date as their filename, so named logs are more persistent.
 *       Include an overall limit on the number of named logfiles.
 */

#include <filesystem>
#include <string>

// Local headers
#include "fs.hpp"

// --*-- content marker for hw7.hpp

/**
 * @brief Return a default location for the log file.
 * 
 * @return Default logging path.
 */
Path defaultLogFile();

/**
 * @brief Log a string.
 * @param s The string to log.
 */
void debug(const String& s);

/**
 * @brief Log a string.
 *
 * @param ss A `stringstream`.
 * @return `void`, but `ss` is reset.
 */
void debug(std::ostringstream& ss);

/**
 * @brief Log a string.
 * @param s The string to log.
 */
void info(const String& s);

/**
 * @brief Log a string.
 * @param s The string to log.
 */
void warn(const String& s);

/**
 * @brief Log a string.
 * @param s The string to log.
 */
void error(const String& s);

/**
 * @brief Log a string.
 * @param s The string to log.
 */
void stop(const String& s);

/**
 * @brief Ensure that only the `count` most recent logs remain in the `logs` directory.
 *
 * @param directory Current logs folder.
 * @param count Number of logs to keep
 *
 * \todo Should return a result code or something relevant maybe.
 */
void rotate_logs(const Path& directory, size_t count);
