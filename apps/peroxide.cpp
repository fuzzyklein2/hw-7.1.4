/**
 * @file peroxide.cpp
 *
 * Define main().
 */
#include "sysinc.hpp"

// Put this above local headers to reduce typing
using namespace std;

// Local headers
// #include "logging.hpp"
// #include "program.hpp"

#include "hw7.hpp"

/**
 * Subclass `Filter`.
 */
class SongList : StrList
{
    SongList (const StrList& S) : StrList(S) {} 
};

/**
 * Subclass `Program`.
 */
class Peroxide : Program
{
public:
    Peroxide(int argc, char **argv) : Program (argc, argv) {}

    ErrCode run();
};

ErrCode Peroxide::run()
{
    debug("Running peroxide");
    return EXIT_SUCCESS;
}

/**
 * main
 *
 * @brief Entry point of the program.
 *
 * Parses the command line, initializes the application, and starts
 * the main processing loop.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 *
 * @return Exit status.
 */
int main(
    int argc, // Argument count
    char **argv // Cannot be `const` or CLI11 won't work.
) {
    auto p = Peroxide(argc, argv);
    
    return p.run();
}