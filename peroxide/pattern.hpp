#pragma once
/**
 * @file pattern.hpp
 *
 * Class that defines the data structure for a pattern.
 */
#include "hw7.hpp"
#include "globals.hpp"


namespace h2o2
{
    class song;

    class pattern
    {
    public:
        // pattern() : name(hw7::EMPTY) {}

        /**
         * Initialize the pattern based on the JSON.
         * If there is a Number that's the repeat count. If there's not
         * then `repeat_count` is 1.
         * @return Error code.
         */
        pattern(const JSON& seq, h2o2::song&);

        pattern(const pattern& p)
          : name(p.name),
            repeat_count(p.repeat_count),
            j(p.j),
            i(0),
            N(p.N),
            parent(p.parent),
            current_repeat(0)
        {
            std::cerr << "PATTERN COPY: constructed\n";
        }

        ErrCode load();

        /**
         * Process until a clip is found.
         * @return Error code.
         * @todo Check for errors. :D
         */
        ErrCode next_clip();
    
    protected:
        hw7::str name;
        Number repeat_count;
        JSON j;
        Index i;
        Index N;
        song& parent;
        Index current_repeat;
    };

} //h2o2
