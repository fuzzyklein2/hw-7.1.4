#pragma once
/**
 * @file constants.hpp
 *
 * Declare logging functions.
 */

// Local headers
#include "types.hpp"

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
