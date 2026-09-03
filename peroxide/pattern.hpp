#pragma once
/**
 * @file pattern.hpp
 *
 * Class that defines the data structure for a pattern.
 */
#include "hw7.hpp"
#include "types.hpp"

namespace h2o2
{
    // class song;

    class pattern
    {
    public:
        // pattern() : name(hw7::EMPTY) {}

        /**
         * Initialize the pattern based on the JSON.
         * If there is a Number that's the repeat count. If there's not
         * then `repeat_count` is 1.
         * @return Error code.
         * @todo Find
         */
        pattern(const JSON& seq);

        /**
         * Copy a pattern object.
         * @param name Unused, but may very well be needed anyway.
         * @param repeat_count Number of times this pattern should be repeated. 0 means forever.
         * @param j JSON object (not text) representation of the program.
         * @param i Index of the element currently being processed.
         * @param N Number of elements in the JSON (j.size())
         */
        pattern(const pattern& p)
          : name(p.name), // Optional. May not exist.
            repeat_count(p.repeat_count), // Number of times to repeat.
            j(p.j), // JSON object representation.
            i(0), // Index of the next element to process.
            N(p.N), // Number of elements.
            // @deprecated parent(p.parent),
            current_repeat(0) /// index of the current repetition.
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

        ErrCode dump(const ErrCode);
    
    protected:
        hw7::str name;
        Number repeat_count;
        JSON j;
        Index i;
        Index N;
        Index current_repeat;
    };

    using PatPtr = std::unique_ptr<pattern>;

} //h2o2
