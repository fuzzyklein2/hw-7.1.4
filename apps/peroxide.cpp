/**
 * @file peroxide.cpp
 *
 * Define main().
 */
#include <algorithm> // sort
#include <sstream>   // ostringstream

#include "hw7.hpp"
using namespace std;
using namespace hw7;

namespace h2o2
{
    class str_list : StrList
    {
        /**
         * Default constructor.
         */
        str_list() = default;

        /**
         * Construct a `StrList` by splitting `text` on `endl`.
         * 
         * Make sure the returned value is a `str_list` and no demotion occurs.
         */
        str_list(const str& text) : StrList(text.split(str("\n"))) {}
    };
} // h2o2
using namespace h2o2;

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

    auto SONG_LISTS_DIR = Path(config["session folder"]) / "lists";

    ostringstream oss;
    for (const auto& s : args)
    {
        oss << s;
    }
    oss << endl;
    debug(oss);
    oss << "Session folder: " << config["session folder"];
    info(oss.str());

    str text;
    SongList songs;
    PathList song_list_files;

    // If there is input, it should be the song list itself.
    if (!input.empty())
    {
        text = str(input);
        // songs = SongList{input};
    }
    else if (!args.empty())
    {
        text = str(read_file(Path(args[0])));
    }
    else
    {
        song_list_files = listdir(SONG_LISTS_DIR);
        sort(song_list_files.begin(), song_list_files.end(), greater<>());
        text = str(read_file(song_list_files[0]));
        // C++ will `throw` here on errors without any help?
    }
    
    // auto SONG_LIST_FILE = "20260802.txt";

    
    // str s = read_file(Path(config["session folder"]) / "lists" / SONG_LIST_FILE);

    info(text);
    
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