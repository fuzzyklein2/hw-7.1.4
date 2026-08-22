/**
 * @file fs.cpp
 *
 * File functions and the `FileSystem` class.
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

String read_file(const Path& p)
{
    ifstream f(p);
    ostringstream oss;
    oss << f.rdbuf();
    return oss.str();
}

String magic_type(const Path& p)
{
    magic_t cookie = magic_open(MAGIC_MIME_TYPE);
    if (!cookie) throw runtime_error("magic_open() failed");
    if (magic_load(cookie, nullptr) != 0)
    {
        String err = magic_error(cookie);
        magic_close(cookie);
        throw runtime_error(err);
    }
    const auto result = magic_file(cookie, p.c_str());
    if (!result)
    {
        String error = magic_error(cookie);
        magic_close(cookie);
        throw runtime_error(error);
    }
    String type(result);
    magic_close(cookie);
    return type;
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

/**
 * ## File Types
 * 
 * ### Directory
 * 
 * ### Text
 * 
 *     * `.txt`
 * 
 * #### Headers
 * 
 *     * `.h`
 *     * `.hpp`
 * 
 * #### Source Code
 * 
 *     * `.c`
 *     * `.cpp`
 *     * `.js`
 *     * `.py`
 *     * `.sh`
 * 
 * #### HTML
 * 
 *     * `.htm`
 *     * `.html`
 * 
 * #### Configuration
 * 
 *     * `.cfg`
 * 
 * #### CSV
 * 
 *     * `.csv`
 * 
 * #### Data
 * 
 *     * `.json`
 * 
 * #### Logs
 * 
 *     * `.log`
 * 
 * #### Stylesheets
 * 
 *     * `.css`
 * 
 * #### CGI
 * 
 *     * `.cgi`
 * 
 * ### Binary
 * 
 * #### Executables
 * 
 * #### Archives
 * 
 *     * `.deb`
 *     * `.pkl`
 *     * `.tar.gz`
 *     * `.zip`
 * 
 * #### Graphics
 * 
 *     * `.gif`
 *     * `.jpeg`
 *     * `.png`
 * 
 * #### Audio
 * 
 *     * `.flac`
 *     * `.mp3`
 * 
 * #### Video
 * 
 *     * `.mp4`
 * 
 * ### Databases
 * 
 *     * `.db`
 * 
 * ### FIFO
 * 
 * ### Links
 * 
 * #### Hard
 * #### Symbolic
 * 
 */
