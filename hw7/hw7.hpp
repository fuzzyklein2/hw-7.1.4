#pragma once
/**
 * @file hw7.hpp
 *
 * Single header for `hw7`.
 */

// # System headers

#include <nlohmann/json.hpp> // JSON -> struct conversion
#include <vector>
#include <cstdlib>
#include <iostream>   // cin & cout
#include "spdlog/sinks/basic_file_sink.h" // Log file(s)
#include "spdlog/spdlog.h"   // Logging module
#include "spdlog/sinks/stdout_color_sinks.h" // Screen output
#include <string>
#include <filesystem>
#include <map>


#define CONST inline const
#define STATIC inline static
#define CONSTEXPR inline constexpr


// Standard types
namespace fs = std::filesystem;
using Path = fs::path;
using String = std::string;
using StrList = std::vector<String>;
using StrDict = std::map<String, String>;
using PathList = std::vector<Path>;

// Package types
using JSON = nlohmann::json;
using Logger = std::shared_ptr<spdlog::logger>;
using LogLevel = spdlog::level::level_enum;

using Number = unsigned int;
using ErrCode = Number;


namespace hw7
{
    // String constants
    /// Easy way to find the current process.
    CONST String THIS_PROC = "/proc/self/exe";
    CONST Path THIS_PATH = fs::read_symlink(THIS_PROC);
    /// Name of the currently running program.
    CONST String PROGRAM = THIS_PATH.filename();
    // CONST String VERSION = "0.0.0";
    
    /// Ensure Unicode.
    /// \todo `WORLD` and `GREETING` are specific to this 1st project.
    CONST String WORLD = "\U0001F30E"; // 🌎 Earth Globe Americas

    CONST String GREETING = "Hello, ";

    /// Basic strings. May possibly avoid a few typos.
    CONST String SPACE = " ";
    CONST String EMPTY = "";
    CONST String DBL_SPACE = "  ";
    CONST String DOT = ".";
    CONST String CHECK = "✓ ";
    CONST String EQUAL = "=";
    CONST String UNDERSCORE = "_";
    CONST String LEFT_BRACKET = "[";
    CONST String RIGHT_BRACKET = "]";
    CONST String COLON = ":";
    CONST String QUOTE = "\'";
    CONST String DBL_QUOTE = "\"";
    CONST String NEWLINE = "\n";
    
    /// Unicode emojis just to be cute.
    CONST String LOG_PICT = "📜";
    CONST String CRITICAL_PICT = "🛑";
    CONST String ERROR_PICT = "❗";
    CONST String WARNING_PICT = "⚠️";
    CONST String INFO_PICT = "💬";
    CONST String DEBUG_PICT = "🐞";
    CONST String CHECK_PICT = "✅";
    CONST String FAILURE_PICT = "❌";
    
    /// Index strings for the help text in `data/data.json`.
    CONST String DEBUG_KEY = "debug";
    CONST String VERBOSE_KEY = "verbose";
    CONST String ARGS_KEY = "args";
    CONST String VERSION_KEY = "version";
            
    /// File system filenames.
    CONST String CONF_DIR_NAME = ".config";
    CONST String CONF_FILE_NAME = "config.json";
    CONST String LOG_DIR_NAME = ".log";
    CONST String DATA_DIR_NAME = "data";
    CONST String DATA_FILE_NAME = PROGRAM + ".json";
    
    // Environment variables
    
} // namespace hw7


/**
 * now_string
 * 
 * @brief Get the current timestamp and return it.
 * 
 * @return Current timestamp as a string.
 */
String now_string();


namespace hw7
{
    /**
     * Provides convenient string manipulation functions.
     *
     * Extends `std::string` with additional string manipulation functions.
     */
    class str : public String
    {
    public:

        /**
         * Default constructor.
         */
        str() = default;

        /**
         * C string constructor.
         */
        str(const char* s) : String(s) {}

        /**
         * STL basic string constructor.
         */
        str(const String& s) : String(s) {}

        /**
         * string view constructor.
         */
        str(const std::string_view& s) : String(s) {}

        /**
         * @return Lower case version of `this`.
         */
        str lower();

        /**
         * @return Upper case version of `this`.
         */
        str upper();

        /**
         * @return `StrList` of `substr`s separated by contiguous whitespace.
         */
        StrList split() const;

        /**
         * @param sep `str` to be used as a separator to split the `str`.
         * @return `StrList` of `substr`s separated by contiguous whitespace.
         */
        StrList split(const str&) const;

        /**
         * Join a list of strings using `this`.
         * @param sep `str` to be used as a separator to split the `str`.
         * @return `StrList` of `substr`s separated by contiguous whitespace.
         */            
        str join(const StrList&);

        /**
         * Replace a substring of `this` with a different string.
         * @param target The substring to find and replace.
         * @param replacement String to replace the target with.
         * @return Copy of `this` with all occurences of `target` replaced by `replacement`.
         */
        str replace(const str& pattern, const str& replacement);

        /**
         * Partition the string just like Python does.
         * @param sep `str` to be used as a separator to split the `str`.
         * @return `StrList` of 2 `substr`s but not the separator.
         */
        StrList partition(const str& pattern);


    }; //str
} // hw7

template<>
struct std::formatter<hw7::str> : std::formatter<std::string>
{
    auto format(const hw7::str& s, auto& ctx) const
    {
        return std::formatter<std::string>::format(
            static_cast<std::string>(s),
            ctx
        );
    }
};

// Functions
Path cwd();
PathList listdir(const Path& path);
String read_file(const Path& p);
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



template <typename T>
class Filter
{
public:

    /**
     * Default constructor.
     */
    Filter() = default;

    /**
     * StrList constructor.
     * @param S A list of strings.
     */
    Filter(const StrList& S)
    {
        for(const auto& s : S)
        {
            elements.push_back(s);
        }
    }

    /**
     * Process the list of paths.
     * @return ErrCode.
     */
    inline ErrCode process()
    {
        for (const auto& p : elements) process(p);
        return 0;
    }

    /**
     * Process an element.
     * @return ErrCode.
     */
    virtual inline ErrCode process(const T&)
    {
        return EXIT_SUCCESS;
    }

protected:
    std::vector<T> elements; /// List of files to be filtered.

};

template <>
inline ErrCode Filter<Path>::process(const Path& p)
{
    std::cout << p << "is a " << magic_type(p) << " file." << std::endl;
    
    return EXIT_SUCCESS;
}

template <>
inline ErrCode Filter<String>::process(const String& p)
{
    std::cout << p << std::endl;
    
    return EXIT_SUCCESS;
}




JSON configure(const Path&);
JSON load_data(const Path& p);


/**
 * @brief Check for environment variables that override `config.json`.
 *
 * Environment variables should be of the form:
 *
 *     `f"{PROGRAM}_{UNDERSCORE.join(upper(CONFIG_FILE_KEY))}`
 *
 * @param config JSON object to be modified if overridden.
 * @todo This function needs serious debugging. 🤣
 * @bug JSON object appears not to update properly?
 * @warning ⚠️ This function calls `environ`, which does not exist on Windoze.
 */
void check_env(JSON&);

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


/**
 *  @brief Stores all the global variables necessary to run the program.
 */
struct Globals {
public:
    FileSystem FS;
    JSON config;
    JSON data;
    bool _debug;
    bool verbose;
    bool version = false;
    StrList args;
    hw7::str input;

    /**
     * Initialize global variables.
     *
     * @param argc Number of command line arguments passed to `main()`.
     * @param argv Array of args as `C` strings.
     */
    Globals(int, char**); // constructor

    /**
     * @brief Output the values of all the globals.
     */
    void dump();

    private:

    /**
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
    int getargs(int, char**);

    /**
     *  Get any piped input that happens to be their and store it in `input`.
     */
    void get_piped();

    /**
     *  @brief  Initialize the logging system.
     *  
     *  @warning ⚠️ Command line arguments have to have been parsed previously to calling this.
     */
    void init_logs();
};



class Program : public Globals
{
public:

    /**
     * Constructor.
     * @param argc Number of CLI arguments.
     * @param argv C array of arguments as C strings.
     *
     * Arguments are just passed on to `CLI11`.
     *
     * @return Error code to (possibly) be returned by `main`
     */
    Program(int argc, char **argv) : Globals(argc, argv) {}

    /**
     * Run the program.
     */
    inline virtual ErrCode run()
    {
        dump();
        std::cout << hw7::GREETING << input << std::endl;

        Filter<Path> f(args);
        f.process();
        
        return 0;
    }

}; // Program