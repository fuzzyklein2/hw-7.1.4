#pragma once
/**
 * @file song.hpp
 *
 * Find and parse the pattern script.
 */
#include "hw7.hpp"
#include "song.hpp"

namespace h2o2
{
    class song_list : public std::vector<song>
    {
    public:
        song_list() = default;
        song_list(const hw7::str& s, JSON config)
        {
            for (const hw7::str s2 : s.split("\n"))
            {
                emplace_back(s2, config);
            }
        }
        bool is_clip_name(const hw7::str&);
    protected:
        
    }; // song_list

} // h2o2
