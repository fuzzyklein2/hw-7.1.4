#pragma once
/**
 * @file globals.hpp
 *
 * Declare global variables.
 */

// System headers
#include <map>
#include <string>
#include <vector>

// Local headers
#include "fs.hpp"
#include "types.hpp"

/**
 *  @brief Stores all the global variables necessary to run the program.
 */
struct Globals {
    FileSystem FS;
    JSON config;
    JSON data;
    bool debug;
    bool verbose;
    bool version = false;
    StrList args;
    String input;

    public:
    /**
     * @brief Initialize global variables.
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

