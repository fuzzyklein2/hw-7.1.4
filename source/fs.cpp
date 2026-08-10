/**
 * @file globals.cpp
 *
 * Define and initialize global variables.
 */

#include "sysinc.hpp"
using namespace std;

// Local headers
#include "fs.hpp"

Path cwd()
{
    return fs::current_path();
}

PathList listdir(const Path& path)
{
    PathList result;

    for (const auto& entry : fs::directory_iterator(path))
        result.push_back(entry.path());
    sort(result.begin(), result.end());
    return result;
}

/**
 * getHome
 *
 * @brief Return the user's home directory.
 * @return path to `~`.
 */
Path getHome()
{
    const char* home = getenv("HOME");
    if (!home) throw runtime_error("HOME not set!");
    return home;
}

void ensure_file(const Path& p)
{
    if (!fs::exists(p)) {
        ofstream f(p);
    }
}

FileSystem::FileSystem()
{
    fs::create_directories(home);
    fs::create_directories(base);
    fs::create_directories(conf_dir);
    ensure_file(config);
    fs::create_directories(user);
    fs::create_directories(logs);
    fs::create_directories(data_dir);
    ensure_file(data);
}
