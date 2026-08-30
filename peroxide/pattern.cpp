/**
 * @file pattern.cpp
 *
 * Pattern operations.
 */

#include "pattern.hpp"
#include "song.hpp"
using namespace std;
using namespace hw7;
using namespace h2o2;

pattern::pattern(const JSON& pat, song& owner) : repeat_count(1),
                                                 j(pat),
                                                 i(0),
                                                 N(j.size()),
                                                 parent(owner),
                                                 current_repeat(0)
{
}

ErrCode pattern::load()
{
    // /// If the only elements are a valid clip name and a repeat count of 0,
    // /// just go ahead and push the clip name to the queue and be done with all this.
    // if (j.is_array && j.size() == 2 && j[0].is_number_integer() && audio_clip::is_clip_name(j[1]))
    // {
    //     parent.clips.push(j[1]);
    //     i++;
    //     return EXIT_SUCCESS; /// Obviously there should be some error checking here.
    // }
    parent.patterns.push(*this);
    // next_clip();
    return EXIT_SUCCESS;

}

ErrCode pattern::next_clip()
{
    if (i >= N) // Pattern processing is complete.
    {
        if (repeat_count == 0 and !pedal)
        {
            i = 0;
        }
        else if (current_repeat < repeat_count)
        {
            i = 0;
            current_repeat++;
        }
        else
        {
            parent.patterns.pop(); // Shouldn't need to call next_clip on the top pattern here.
                                   // There may not even be a pattern left on the stack.
            return EXIT_SUCCESS;
        }
    }
    const auto value = j[i];
    if (value.is_number_integer())
    {
        // Should be the number of times to repeat the pattern.
        // Should also be the first value if present.
        repeat_count = value.get<int>();
        i++;
        next_clip();
    }
    else if (value.is_string())
    {
        // Should be the name by which the pattern can be referenced in the
        // rest of the script, OR the filename of a clip, not necessarily in
        // that order.
        if (parent.is_clip_name(value))
        {
            parent.clips.push(value);
            i++;
            // return EXIT_SUCCESS;
        }
        else
        {
            if (!parent.pat_map.contains(value))
            {
                parent.pat_map.emplace(value, pattern(j, parent));
                i++;
                next_clip();
            }
            else
            {
                i++;
                parent.load(parent.pat_map.at(value));
                // return EXIT_SUCCESS; // ?
            }
        }
    }
    else if (value.is_array())
    {
        // Should be another pattern. If it's not that's an error.
        /// @todo Exactly when and where does a pattern get pushed on to the stack?
        pattern pat(value, parent);
        parent.load(pat);
        i++;
        // return EXIT_SUCCESS;
    }
    // else stop("Error loading pattern!");
    return 1;
    
    return EXIT_SUCCESS;
}