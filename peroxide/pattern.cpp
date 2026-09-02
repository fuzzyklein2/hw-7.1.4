/**
 * @file pattern.cpp
 *
 * Pattern operations.
 */

#include "pattern.hpp"
#include "song.hpp"
#include <utility> // std::move
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
    // Move this pattern into the parent's pattern stack so the stack owns the instance
    // that will be advanced during playback. Do not call next_clip() here — playback
    // should advance the pattern that's actually on the stack.
    parent.load(std::move(*this));
    return EXIT_SUCCESS;
}

ErrCode pattern::next_clip()
{
    // Iteratively process the JSON sequence until we either enqueue a clip or
    // decide the pattern has finished and should pop itself.
    while (true)
    {
        if (i >= N) // Pattern processing is complete for one pass.
        {
            if (repeat_count == 0 && !pedal)
            {
                // repeat forever (or until some external condition)
                i = 0;
            }
            else
            {
                // Completed one run; increment and compare to requested repeat_count
                current_repeat++;
                if (repeat_count != 0 && current_repeat >= repeat_count)
                {
                    // We're done with this pattern's repeats — remove it from the stack.
                    parent.patterns.pop();
                    return EXIT_SUCCESS;
                }
                // Otherwise reset to start the next repetition.
                i = 0;
            }
        }

        const auto value = j[i];

        if (value.is_number_integer())
        {
            // The first (or current) element can be a repeat count.
            repeat_count = value.get<int>();
            i++;
            continue;
        }
        else if (value.is_string())
        {
            // Either a clip name or a named pattern reference.
            if (parent.is_clip_name(value))
            {
                parent.clips.push(value);
                i++;
                return EXIT_SUCCESS; // We found a clip to play.
            }
            else
            {
                // Named pattern: register or load it.
                if (!parent.pat_map.contains(value))
                {
                    // Register the current JSON (or appropriate pattern JSON) under this name.
                    parent.pat_map.emplace(value, j);
                    i++;
                    continue; // Continue scanning the current pattern after registration.
                }
                else
                {
                    // Load the named pattern (push it onto the stack) and let playback use it.
                    i++;
                    parent.load(parent.pat_map.at(value));
                    return EXIT_SUCCESS;
                }
            }
        }
        else if (value.is_array())
        {
            // Anonymous subpattern — push it onto the stack for handling.
            pattern pat(value, parent);
            parent.load(pat);
            i++;
            return EXIT_SUCCESS;
        }
        else
        {
            // Malformed entry — treat as an error for now.
            return EXIT_FAILURE;
        }
    }

    // unreachable
    return EXIT_SUCCESS;
}
