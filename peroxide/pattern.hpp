#pragma once
/**
 * @file pattern.hpp
 *
 * Class that defines the data structure for a pattern.
 */
#include "hw7.hpp"

#include "clip_list.hpp"

namespace h2o2
{

    class pattern
    {
    public:
        pattern() : name(hw7::EMPTY) {}
        pattern(const JSON& seq)
        {
            
        }

    protected:
        hw7::str name;
        Path base;
        // clip_list clips;
        Index current_clip_index;
    };

} //h2o2
