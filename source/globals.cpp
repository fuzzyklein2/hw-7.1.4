/**
 * @file globals.cpp
 *
 * Define and initialize global variables.
 */

#include "sysinc.hpp"
using namespace std;

// Local headers
#include "config.hpp"
#include "constants.hpp"
#include "fs.hpp"
#include "globals.hpp"
#include "logging.hpp"

using namespace hello7::constants;

// // Execution modes
// bool _debug = true;   // Prefix input variables and options with '_'.
// bool _verbose = false;
// bool _version = false;

// // Input variables
// StrList _args;
// string _input;

// // Global logging variables
// Logger logger;
// LogLevel log_level = LogLevel::warn;

// FileSystem FS;
// JSON _config = configure(FS.config);
// JSON _data = load_data(FS.data);

Globals::Globals(int argc, char **argv)
{
    // cout << "Initializing Globals" << endl;
    // cout << "Configuration file: " << FS.config << endl;
    // cout << "Data file: " << FS.data << endl;
    config = configure(FS.config);
    data = load_data(FS.data);
    debug = config["debug"];
    verbose = debug;
    getargs(argc, argv);
    // cout << "Version switch: " << version << endl;
    if (version)
    {
        cout << PROGRAM << SPACE << data["version"] << endl;
        exit(0);
    }
    if (debug) verbose = true;
    if (verbose) cout << "`Globals` object initializing...";
    get_piped();
    init_logs();
    // log = logger;
}

/**
 * getargs
 *
 * @brief Parse the command line.
 *
 * Parses the command line, initializes the application, and starts
 * the main processing loop.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 *
 * @return Exit status.
 */
int Globals::getargs(
    int argc,   // Argument count
    char **argv // Cannot be `const` or CLI11 won't work.
)
{
    // Initialize CLI11 object
    
    CLI::App app{data["description"]};
    argv = app.ensure_utf8(argv);

    // Add options and arguments
    app.add_flag("-d,--debug", debug, data["help"][DEBUG_KEY]);
    app.add_flag("-v,--verbose", verbose, data["help"][VERBOSE_KEY]);
    app.add_flag("-V,--version", version, data["help"][VERSION_KEY]);
    app.add_option("files", args, data["help"][ARGS_KEY]);
    // Indexing _help with brackets can cause accidental insertions by mistyped keys.
    
    // Parse the command line arguments
    CLI11_PARSE(app, argc, argv);

    // cout << "Version switch: " << version << endl;
    
    return 0;
}

void Globals::get_piped()
{
    // Check if stdin is a terminal (not piped)
    if (!isatty(fileno(stdin))) { // There is piped input
        ostringstream oss;
        oss << cin.rdbuf(); // Read standard input into the sstream.
        input = oss.str(); // Make input access global.
        // Remove trailing newline (optional, improves output for typical use)
        if (!input.empty() && input.back() == '\n')
        {
            input.pop_back();
        }
    } else input = WORLD; // Remove or replace `WORLD` here as appropriate.

}

void Globals::init_logs()
{
    // clean up the logs folder
    rotate_logs(FS.logs, config["saved logs"]);

    // for (const auto& path : listdir(FS.logs))
    // {
    //     cout << path << endl;
    // }
    // cout << "Save the last " << _config["saved logs"] << " files." << endl;

    // create a color multi-threaded logger
    
    auto console_sink = make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = make_shared<spdlog::sinks::basic_file_sink_mt>(FS.logfile);

    // Set the console log level according to `_debug` and/or `_verbose` values.
    // So command line arguments have to have been parsed previously to calling this.
    // if (_debug) console_sink->set_level(LogLevel::debug);
    // else if (_verbose) console_sink->set_level(LogLevel::info);
    // else console_sink->set_level(LogLevel::warn);
    // console_sink->set_level(ll)

    if (debug) console_sink->set_level(LogLevel::debug);
    else if (verbose) console_sink->set_level(LogLevel::info);
    else console_sink->set_level(LogLevel::warn);

    console_sink->set_pattern("[%^%l%$] %v"); // We don't need the date. Maybe the time.
    file_sink->set_level(LogLevel::debug); // All messages of any level -> logfile.
    file_sink->set_pattern("[%l] %v"); // We don't need the date. Maybe the time.

    // logger constructor expects a vector of sinks
    vector<spdlog::sink_ptr> sinks { console_sink, file_sink };
    
    Logger logptr = make_shared<spdlog::logger>(
        PROGRAM,
        sinks.begin(),
        sinks.end()
    );
    
    logptr->set_level(LogLevel::debug);
    
    spdlog::register_logger(logptr);
    spdlog::set_default_logger(logptr);
    // logger->warn("This should be everywhere.");
    // logger->info("This should only be in the file.");
    // logger->error("Danger, Will Robinson!");
}