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
#include "logging.hpp"

// Functions
Path cwd();
PathList listdir(const Path& path);
Path getHome(); // Find the user's home directory and return it as a `path` object.
void ensure_file(const Path& p); // Create the file at p if it doesn't exist.

struct FileSystem {
    Path working = cwd();
    Path home = getenv("HOME");
    Path base = fs::read_symlink("/proc/self/exe").parent_path().parent_path();
    Path conf_dir = home / CONF_DIR_NAME / PROGRAM;
    Path config = conf_dir / CONF_FILE_NAME;
    Path user = home / (DOT + PROGRAM);
    Path logs = home / LOG_DIR_NAME / PROGRAM;
    Path logfile = logs / log_filename();
    Path data_dir = base / DATA_DIR_NAME;
    Path data = data_dir / DATA_FILE_NAME;

    FileSystem(); // constructor
};

