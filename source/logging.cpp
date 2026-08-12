/**
 * @file logging.cpp
 *
 * Logging functions.
 */
#include "sysinc.hpp"
using namespace std;

// Local headers
#include "constants.hpp"
// #include "fs.hpp"
// #include "globals.hpp"
#include "logging.hpp"
#include "types.hpp"

using namespace hello7::constants;

/**
 * defaultLogFile
 * 
 * @brief Return a default location for the log file.
 * 
 * @return Default logging path.
 */
// Path defaultLogFile()
// {
//     return FS.logs / (PROGRAM + ".log");
// }

// void init_logs()
// {
//     // clean up the logs folder
//     rotate_logs(FS.logs, _config["saved logs"]);

//     // for (const auto& path : listdir(FS.logs))
//     // {
//     //     cout << path << endl;
//     // }
//     // cout << "Save the last " << _config["saved logs"] << " files." << endl;

//     // create a color multi-threaded logger
    
//     auto console_sink = make_shared<spdlog::sinks::stdout_color_sink_mt>();
//     auto file_sink = make_shared<spdlog::sinks::basic_file_sink_mt>(FS.logfile);

//     // Set the console log level according to `_debug` and/or `_verbose` values.
//     // So command line arguments have to have been parsed previously to calling this.
//     if (_debug) console_sink->set_level(LogLevel::debug);
//     else if (_verbose) console_sink->set_level(LogLevel::info);
//     else console_sink->set_level(LogLevel::warn);

//     console_sink->set_pattern("[%^%l%$] %v"); // We don't need the date. Maybe the time.
//     file_sink->set_level(LogLevel::debug); // All messages of any level -> logfile.
//     file_sink->set_pattern("[%l] %v"); // We don't need the date. Maybe the time.

//     // logger constructor expects a vector of sinks
//     vector<spdlog::sink_ptr> sinks { console_sink, file_sink };
    
//     G.log.logptr = make_shared<spdlog::logger>(
//         PROGRAM,
//         sinks.begin(),
//         sinks.end()
//     );
    
//     logger->set_level(LogLevel::debug);
    
//     spdlog::register_logger(logger);
//     spdlog::set_default_logger(logger);
//     // logger->warn("This should be everywhere.");
//     // logger->info("This should only be in the file.");
//     // logger->error("Danger, Will Robinson!");
// }

/**
 * debug
 * 
 * @brief Log a string.
 */
void debug(const String& s)
{
    spdlog::get(PROGRAM)->debug(DEBUG_PICT + DBL_SPACE + s);
}

/**
 * info
 * 
 * @brief Log a string.
 */
void info(const String& s)
{
    spdlog::get(PROGRAM)->info(INFO_PICT + DBL_SPACE + s);
}

/**
 * warn
 * 
 * @brief Log a string.
 */
void warn(const String& s)
{
    spdlog::get(PROGRAM)->warn(WARNING_PICT + DBL_SPACE + s);
}

/**
 * error
 * 
 * @brief Log a string.
 */
void error(const String& s)
{
    spdlog::get(PROGRAM)->error(ERROR_PICT + DBL_SPACE + s);
}

/**
 * stop
 * 
 * @brief Log a string.
 */
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

// Log::Log(const String logfile, const int saved, LogLevel ll)
// {
//     // clean up the logs folder
//     rotate_logs(sys.logs, saved);

//     // for (const auto& path : listdir(FS.logs))
//     // {
//     //     cout << path << endl;
//     // }
//     // cout << "Save the last " << _config["saved logs"] << " files." << endl;

//     // create a color multi-threaded logger
    
//     auto console_sink = make_shared<spdlog::sinks::stdout_color_sink_mt>();
//     auto file_sink = make_shared<spdlog::sinks::basic_file_sink_mt>(logfile);

//     // Set the console log level according to `_debug` and/or `_verbose` values.
//     // So command line arguments have to have been parsed previously to calling this.
//     // if (_debug) console_sink->set_level(LogLevel::debug);
//     // else if (_verbose) console_sink->set_level(LogLevel::info);
//     // else console_sink->set_level(LogLevel::warn);
//     console_sink->set_level(ll)

//     console_sink->set_pattern("[%^%l%$] %v"); // We don't need the date. Maybe the time.
//     file_sink->set_level(LogLevel::debug); // All messages of any level -> logfile.
//     file_sink->set_pattern("[%l] %v"); // We don't need the date. Maybe the time.

//     // logger constructor expects a vector of sinks
//     vector<spdlog::sink_ptr> sinks { console_sink, file_sink };
    
//     logptr = make_shared<spdlog::logger>(
//         PROGRAM,
//         sinks.begin(),
//         sinks.end()
//     );
    
//     logptr->set_level(LogLevel::debug);
    
//     spdlog::register_logger(logger);
//     spdlog::set_default_logger(logger);
//     // logger->warn("This should be everywhere.");
//     // logger->info("This should only be in the file.");
//     // logger->error("Danger, Will Robinson!");
// }