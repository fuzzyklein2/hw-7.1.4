/**
 * @file peroxide.cpp
 *
 * Define main().
 */

// Put this above local headers to reduce typing
using namespace std;

// Local headers
// #include "logging.hpp"
// #include "program.hpp"

#include "hw7.hpp"
using namespace hw7;

/**
 * Subclass `Filter`.
 */
class SongList : Filter<String>
{
public:
    SongList() = default;
    SongList (const StrList& S) : Filter<String>(S) {}
    SongList (const str& s) : Filter<String>(s.split()) {}
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
    debug("Arguments:");
    ostringstream oss;
    for (const auto& s : args)
    {
        oss << s;
    }
    oss << endl;
    debug(oss);
    oss << "Session folder: " << config["session folder"];
    info(oss.str());

    SongList songs;

    // If there is input, it should be the song list itself.
    if (!input.empty()) {}

    auto SONG_LISTS_DIR = Path(config["session folder"]) / "lists";
    
    auto SONG_LIST_FILE = "20260802.txt";

    
    str s = read_file(Path(config["session folder"]) / "lists" / SONG_LIST_FILE);

    info(s);
    
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