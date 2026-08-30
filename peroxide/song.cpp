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
    /// @bug `title` is an empty string at some point.
    /// @todo Find the place where a `song` is being constructed with `EMPTY_STR`.;l.
    const auto SONG_DIR = base / "songs" / string(title);
    folder = SONG_DIR;
    cout << "Song folder: " << string(folder) << endl;
    // Load all sound clips to the registry in advance.

    // List the clips directory and add everything with the stem of each file
    // being its name in the registry.

    for (const auto& p : listdir(folder / "clips"))
    {
        clip_map.insert( {hw7::str(p.stem()), audio_clip(p)} );
    }
    
    script = load_data(SONG_DIR / "song.json");

    // Loop through the pattern defined by song.json.
    pattern pat(script, *this);
    load(pat);

}

audio_clip& song::next_clip()
{
    Number n = 0;
    while (clips.empty() && n < 1000)
    {
        patterns.top().next_clip();
        n++;
    }
    if (clips.empty()) throw runtime_error("Pattern failed to supply a clip!");
    const auto name = clips.front();
    if (!repeat) clips.pop();
    audio_clip& result = clip_map[name];

    cout << "NEXT CLIP: " << name << endl;
    
    return result; // It won't really be this simple.
}

ErrCode song::load(pattern& p)
{
    return p.load();
}

bool song::is_clip_name(const str& s)
{
    const Path CONFIG = Path(getenv("HOME")) / CONF_DIR_NAME / PROGRAM / CONF_FILE_NAME;
    const auto cfg = load_data(CONFIG);
    const auto SONGS = Path(cfg["session folder"].get<string>()) / "songs";
    for ( const auto& f : listdir(SONGS / string(title) / "clips") )
    {
        if (str(f) == s) { return true; }
    }
    return false;
}

ma_uint32 song::get_clip_sampleRate()
{
    Clip c;
    const auto CLIP_FILE = str(listdir(song::get_clips_dir())[0]);
    loadClip(CLIP_FILE, c);
    return c.sampleRate;
}

Path song::get_clips_dir()
{
    const Path CONFIG = Path(getenv("HOME")) / CONF_DIR_NAME / PROGRAM / CONF_FILE_NAME;
    const auto cfg = load_data(CONFIG);
    return Path(cfg["session folder"].get<string>()) / "songs" / "Jack the Ripper" / "clips";
}