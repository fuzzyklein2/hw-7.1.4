/**
 * @file song.cpp
 *
 * Functions for the `h2o2::song` class.
 */
#include "clip.hpp"
#include "globals.hpp"
#include "song.hpp"

using namespace std;
using namespace hw7;
using namespace h2o2;

song::song (const hw7::str& s, JSON config) : 
            title(s),
            base(config["session folder"].get<std::string>())
{
    info("Loading song: " + title);
    const auto SONG_DIR = base / "songs" / string(title);

    // Load all sound clips to the registry in advance.

    // List the clips directory and add everything with the stem of each file
    // being its name in the registry.
    
    script = load_data(SONG_DIR / "song.json");

    // Loop through the pattern defined by song.json.
    load_pattern(script);

}

Clip& song::next_clip()
{
    const auto name = clips.front();
    if (!repeat) clips.pop();
    Clip& result = clip_map[name];
    return result; // It won't really be this simple.
}

ErrCode song::load_pattern(JSON& pat)
{
    for (auto item = pat.begin(); item != pat.end(); ++item)
    {
        JSON value = *item;
        if (value.is_number_integer())
        {
            // Should be the number of times to repeat the pattern.
        }
        if (value.is_string())
        {
            // Should be the name by which the pattern can be referenced in the
            // rest of the script, OR the filename of a clip, not necessarily in
            // that order.
        }
        if (value.is_array())
        {
            // Should be another pattern. If it's not that's an error.
            /// @todo Exactly when and where does a pattern get pushed on to the stack?
            load_pattern(value);
        }
        else stop("Error loading pattern!");
    }
}
