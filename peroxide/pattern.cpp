/**
 * @file pattern.cpp
 *
 * Pattern operations.
 */

#include "globals.hpp"
#include "pattern.hpp"
#include "player.hpp"
// #include "song.hpp"
// #include <utility> // std::move
using namespace std;
using namespace hw7;
using namespace h2o2;

pattern::pattern(const JSON& j) : repeat_count(1), j(j), i(0), // N(j.size()),
                                  current_repeat(0)
{
}

ErrCode pattern::load()
{
    // Move this pattern into the parent's pattern stack so the stack owns the instance
    // that will be advanced during playback. Do not call next_clip() here — playback
    // should advance the pattern that's actually on the stack.
    
    // parent.load(*this);
    return EXIT_SUCCESS;
}

ErrCode pattern::next_clip()
{
    auto& current_song = player->songs[player->current_song_index];
    std::cerr << "NEXT_CLIP: ENTERED\n";
    std::cerr << "NEXT_CLIP: this = " << this << "\n";
    std::cerr << "NEXT_CLIP: parent = " << current_song.title << "\n";
    std::cerr << "NEXT_CLIP: i = " << i << "\n";
    // std::cerr << "NEXT_CLIP: N = " << N << "\n";
    std::cerr << "NEXT_CLIP: j.size = " << j.size() << "\n";
    // Iteratively process the JSON sequence until we either enqueue a clip or
    // decide the pattern has finished and should pop itself.
    /// @todo: Give player a simple get_current_song.
    while (running && player->playing)
    {
        std::cerr << "CHECK: i=" << i
                  << " j.size()=" << j.size()
                  << " i >= j.size()=" << (i >= j.size())
                  << "\n";
        if (i >= j.size()) // Pattern processing is complete for one pass.
        {
            if (repeat_count == 0 && !pedal)
            {
                // repeat forever (or until some external condition)
                i = 0;
                // current_song.patterns.push(this);
                return EXIT_SUCCESS;
            }
            else
            {
                // Completed one run; increment and compare to requested repeat_count
                current_repeat++;
                if (repeat_count != 0 && current_repeat >= repeat_count)
                {
                    // We're done with this pattern's repeats — remove it from the stack.
                    current_song.patterns.pop();
                } else { i = 0; }
                return EXIT_SUCCESS;
                // Otherwise reset to start the next repetition.
                // i = 0;
            }
        }

        std::cerr << "NEXT_CLIP: about to access j[" << i << "]\n";
        const auto value = j[i];
        std::cerr << "NEXT_CLIP: processing element " << i
                  << ", type = " << value.type_name() << "\n";
        std::cerr << "NEXT_CLIP: got value\n";
        
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
            if (song::is_clip_name(value))
            {
                current_song.clips.push(value);
                i++;
                return EXIT_SUCCESS; // We found a clip to play.
            }
            else
            {
                // Named pattern: register or load it.
                if (!current_song.pat_map.contains(value))
                {
                    // Register the current JSON (or appropriate pattern JSON) under this name.
                    current_song.pat_map.emplace(value, j);
                    i++;
                    continue; // Continue scanning the current pattern after registration.
                }
                else
                {
                    // Load the named pattern (push it onto the stack) and let playback use it.
                    i++;
                    current_song.load(current_song.pat_map.at(value));
                    return EXIT_SUCCESS;
                }
            }
        }
        else if (value.is_array())
        {
            // Anonymous subpattern — push it onto the stack for handling.
            // std::cerr << "NEXT_CLIP: constructing subpattern\n";
            // pattern pat(value);
            // std::cerr << "NEXT_CLIP: subpattern constructed\n";
            
            current_song.load(value);
            std::cerr << "NEXT_CLIP: subpattern loaded\n";
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
    return EXIT_FAILURE;
}

ErrCode pattern::dump(const ErrCode e)
{
    std::cout << "PATTERN STATUS:\n"
          << " this=" << this
          << " i=" << i
          // << " N=" << N
          << " j.size=" << j.size()
          << '\n';
    return e;
}