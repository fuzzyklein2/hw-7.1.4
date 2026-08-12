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
// #include "logging.hpp"

// Functions
Path cwd();
PathList listdir(const Path& path);
Path getHome(); // Find the user's home directory and return it as a `path` object.
void ensure_file(const Path& p); // Create the file at p if it doesn't exist.
String log_filename();

struct FileSystem {
    Path working = cwd();
    Path home = getenv("HOME");
    Path base = fs::read_symlink(hello7::constants::THIS_PROC).parent_path().parent_path();
    Path conf_dir = home / hello7::constants::CONF_DIR_NAME / hello7::constants::PROGRAM;
    Path config = conf_dir / hello7::constants::CONF_FILE_NAME;
    Path user = home / (hello7::constants::DOT + hello7::constants::PROGRAM);
    Path logs = home / hello7::constants::LOG_DIR_NAME / hello7::constants::PROGRAM;
    Path logfile = logs / log_filename();
    Path data_dir = base / hello7::constants::DATA_DIR_NAME;
    Path data = data_dir / hello7::constants::DATA_FILE_NAME;

    FileSystem(); // constructor
};

