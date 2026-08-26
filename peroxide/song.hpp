#pragma once
/**
 * @file song.hpp
 *
 * Find and parse the pattern script.
 */
#include "hw7.hpp"

#include "clip_list.hpp"

namespace h2o2
{

    class song
    {
    public:
        song() : title(hw7::EMPTY) {}
        song (const hw7::str& s, JSON config) : 
            title(s),
            base(config["session folder"].get<std::string>()),
            current_clip_index(0)
        {
            script = load_data(base / "songs" / std::string(title) / "song.json");
        }

        Clip& current_clip()
        {
            return clips[current_clip_index];
        }

        Clip& next_clip()
        {
            return clips[current_clip_index++]; // It won't really be this simple.
        }

        friend std::ostream& operator<<(std::ostream& os, const song& s)
        {
            return os << s.title;
        }

    protected:
        hw7::str title;
        Path base;
        JSON script;
        clip_list clips;
        Index current_clip_index;
    };

} //h2o2
