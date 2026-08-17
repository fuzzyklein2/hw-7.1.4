/**
 * @file logging.cpp
 *
 * Logging functions.
 */
#include "sysinc.hpp"
using namespace std;

// Local headers
// #include "constants.hpp"
#include "logging.hpp"
// #include "types.hpp"

using namespace hw7;

void debug(const String& s)
{
    spdlog::get(PROGRAM)->debug(DEBUG_PICT + DBL_SPACE + s);
}

void info(const String& s)
{
    spdlog::get(PROGRAM)->info(INFO_PICT + DBL_SPACE + s);
}

void warn(const String& s)
{
    spdlog::get(PROGRAM)->warn(WARNING_PICT + DBL_SPACE + s);
}

void error(const String& s)
{
    spdlog::get(PROGRAM)->error(ERROR_PICT + DBL_SPACE + s);
}

void stop(const String& s)
{
    spdlog::get(PROGRAM)->critical(CRITICAL_PICT + DBL_SPACE + s);
    exit(EXIT_FAILURE);
}

void debug(ostringstream& ss)
{
    debug(ss.str());
    ss.str(EMPTY);
    ss.clear();
}

void rotate_logs(const Path& directory, size_t count)
{
    auto logs = listdir(directory);

    std::erase_if(logs, [](const Path& p) {
        return p.extension() != ".log";
    });

    std::sort(logs.begin(), logs.end());

    while (logs.size() > count) {
        fs::remove(logs.front());
        logs.erase(logs.begin());
    }
}
