#pragma once
/**
 * @file fs.hpp
 *
 * Declare file system functions.
 */

// System headers
#include <cstdlib>

// Local headers
#include "constants.hpp"

// Functions
Path cwd();
PathList listdir(const Path& path);
String magic_type(const Path& p);
/**
 * @brief Return the user's home directory.
 * @return path to `~`.
 */
Path getHome(); // Find the user's home directory and return it as a `path` object.
void ensure_file(const Path& p); // Create the file at p if it doesn't exist.

/**
 * @brief Return a string to name the log file with.
 * 
 * @return Current timestamp as a string.
 */
String log_filename();

struct FileSystem {
    Path working = cwd();
    Path home = getenv("HOME");
    Path base = fs::read_symlink(hw7::THIS_PROC).parent_path().parent_path();
    Path conf_dir = home / hw7::CONF_DIR_NAME / hw7::PROGRAM;
    Path config = conf_dir / hw7::CONF_FILE_NAME;
    Path user = home / (hw7::DOT + hw7::PROGRAM);
    Path logs = home / hw7::LOG_DIR_NAME / hw7::PROGRAM;
    Path logfile = logs / log_filename();
    Path data_dir = base / hw7::DATA_DIR_NAME;
    Path data = data_dir / hw7::DATA_FILE_NAME;

    /**
     * Ensure the existence of all required files.
     */
    FileSystem(); // constructor

    /**
     * Output the value of all members.
     */
    void dump();
};

