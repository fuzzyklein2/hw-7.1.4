/**
 * @file fs.cpp
 *
 * Define and initialize global variables.
 */

// System headers
#include "sysinc.hpp"
using namespace std;

// Local headers
#include "logging.hpp"

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

String log_filename()
{
    auto now = chrono::system_clock::now();
    auto t = chrono::system_clock::to_time_t(now);

    stringstream ss;
    ss << put_time(localtime(&t), "%Y-%m-%d_%H-%M-%S")
       << ".log";

    return ss.str();
}

void FileSystem::dump()
{
    debug(format(R"(FILE SYSTEM

        Current working directory: {}
        User's home directory:     {}
        Base directory:            {}
        Configuration directory:   {}
        Configuration file:        {}
        User data:                 {}
        Logs:                      {}
        Log file:                  {}
        Data directory:            {}
        Data file:                 {}
    )", working.string(),
        home.string(),
        base.string(),
        conf_dir.string(),
        config.string(),
        user.string(),
        logs.string(),
        logfile.string(),
        data_dir.string(),
        data.string()
    ));
}