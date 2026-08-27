#pragma once
/**
 * @file song.hpp
 *
 * Find and parse the pattern script.
 */
#include "hw7.hpp"

#include <queue>
#include <stack>

#include "pattern.hpp"

namespace h2o2
{
    /**
     * Default constructor
     */
    class song
    {
    public:

        song() : title(hw7::EMPTY) {}

        /**
         * @todo Make sure this constructor loads and registers all sound clips by name.
         *       Can be done just by listing the clips directory.
         */
        song (const hw7::str& s, JSON config);

        /**
         * @deprecated
         */
        Clip& current_clip()
        {
            return clip_map[clips.front()];
        }

        /**
         * @return The next audio clip to be played, or an empty clip if
         * `pause` is `true`.
         */
        Clip& next_clip();

        /**
         * Push `pat` to the pattern stack, wait until it pops itself and,
         * when it does, push it back if its `repeat` count is 0 or add it to
         * the pattern map if it has a name that is not already there.
         * If it has no name then it's disposable after its popped for the last time.
         * `pattern` may actually pop itself and handle lookup table registration.
         * @return `EXIT_SUCCESS` or some relevant code.
         */
        ErrCode load_pattern(JSON& pat);

        /**
         * Output operator
         */
        friend std::ostream& operator<<(std::ostream& os, const song& s)
        {
            return os << s.title;
        }

    protected:
        hw7::str title;
        Path base;
        JSON script;

        // Data structures
        std::stack<pattern> patterns;
        std::queue<hw7::str> clips; // Enqueue the clip's name, not the clip itself.
        

        // Lookup tables for named clips and patterns.
        /// Just enqueue the name of the clip & store the clip itself in the registry.
        std::map<hw7::str, Clip> clip_map;
        std::map<hw7::str, pattern> pat_map;
    };

} //h2o2
