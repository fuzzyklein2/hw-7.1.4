#pragma once
/**
 * @file constants.hpp
 *
 * Declare logging functions.
 */

// Local headers
#include "types.hpp"

namespace hello7
{
    namespace constants
    {
        // String constants
        // @todo Move `PROGRAM` and `VERSION` definitions to data/hello.json.
        // @todo Move `DESCRIPTION` to the data file.
        // @todo `WORLD` and `GREETING` are specific to this 1st project.
        CONST String PROGRAM = "hello";
        CONST String VERSION = "0.0.0";
        CONST String WORLD = "\U0001F30E"; // 🌎 Earth Globe Americas
        CONST String DESCRIPTION = "Simple C++ CLI app framework.";
        CONST String GREETING = "Hello, ";
        
        CONST String SPACE = " ";
        CONST String EMPTY = "";
        CONST String DBL_SPACE = "  ";
        CONST String DOT = ".";
        CONST String CHECK = "✓ ";
        
        // Unicode emojis
        CONST String LOG_PICT = "📜";
        CONST String CRITICAL_PICT = "🛑";
        CONST String ERROR_PICT = "❗";
        CONST String WARNING_PICT = "⚠️";
        CONST String INFO_PICT = "💬";
        CONST String DEBUG_PICT = "🐞";
        CONST String CHECK_PICT = "✅";
        CONST String FAILURE_PICT = "❌";
        
        // Index strings
        CONST String DEBUG_KEY = "DEBUG";
        CONST String VERBOSE_KEY = "VERBOSE";
        CONST String ARGS_KEY = "ARGS";
        CONST String VERSION_KEY = "VERSION";
        
        // Help text
        // TODO: Create a `BASE/data` directory to keep these in.
        inline StrDict _help = {
            {DEBUG_KEY, "Debugging mode."},
            {VERBOSE_KEY, "Extra output."},
            {ARGS_KEY, "Files to process."},
            {VERSION_KEY, "Display program version."}
        };
        
        // File system
        CONST String CONF_DIR_NAME = ".config";
        CONST String CONF_FILE_NAME = "config.json";
        CONST String LOG_DIR_NAME = ".log";
        CONST String DATA_DIR_NAME = "data";
        CONST String DATA_FILE_NAME = "hello.json";
        
        // Environment variables
        
    } // namespace constants
} // namespace hello7
