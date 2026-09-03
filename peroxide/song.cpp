/**
 * @file song.cpp
 *
 * Functions for the `h2o2::song` class.
 */
#include "clip.hpp"
#include "globals.hpp"
#include "pattern.hpp"
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
    /// @todo Find the place where a `song` is being constructed with `EMPTY_STR`;l.
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

    load(script);

}

audio_clip* song::next_clip()
{
    Number n = 0;
    std::cerr << "SONG NEXT_CLIP this = " << this << "\n";
    std::cerr << "NEXT_CLIP: ENTERED\n";
    while (clips.empty() && n < 1000)
    {
        std::cerr << "SONG NEXT_CLIP: stack size = "
                  << patterns.size() << '\n';
        if (!patterns.top())
        {
            player->playing = false;
            return nullptr;
        }
        else
        {
            patterns.top()->next_clip();
            std::cerr << "SONG NEXT_CLIP: returned, stack size = "
                      << patterns.size() << '\n';
            n++;
        }
    }
    if (clips.empty()) { // throw runtime_error("Pattern failed to supply a clip!");
        player->playing = false;
        return nullptr;
    }
    else
    {
        const auto name = clips.front();
        if (!repeat) clips.pop();
    
        cout << "NEXT CLIP: " << name << endl;
        return &(clip_map[name]); // It won't really be this simple.
    }
}

// ErrCode song::load(pattern p)
// {
//     // Move the incoming pattern into the stack so the version on the stack
//     // is the one used by playback code.
//     patterns.push(std::move(p));
//     return EXIT_SUCCESS;
// }

// ErrCode song::load(JSON j)
// {
//     std::cerr << "LOAD: entered\n";

//     current_pat = make_unique<pattern>(j);

//     patterns.push(current_pat.get());

//     std::cerr << "LOAD: pushed\n";

//     return EXIT_SUCCESS;
// }

// ErrCode song::load(const str& s)
// {
//     patterns.push(current_pat = make_unique<pattern>(pat_map.at(s)).get());
// }

ErrCode song::load(JSON j)
{
    patterns.push(std::make_unique<pattern>(j));
    return EXIT_SUCCESS;
}

ErrCode song::load(const str& s)
{
    patterns.push(std::make_unique<pattern>(pat_map.at(s)));
    return EXIT_SUCCESS;
}

bool song::is_clip_name(const str& s)
{
    const auto SONGS = Path(program->config["session folder"].get<string>()) / "songs";
    /// @todo Make `str` compatible with `path / str`.
    for ( const auto& f : listdir(SONGS / string(player->songs[player->current_song_index].title) / "clips") )
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
