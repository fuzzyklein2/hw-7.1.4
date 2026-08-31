#pragma once
/**
 * @file song.hpp
 *
 * Find and parse the pattern script.
 */
#include "hw7.hpp"

#include <queue>
#include <stack>

#include "clip.hpp"
#include "pattern.hpp"

namespace h2o2
{
    /**
     * Default constructor
     */
    class song
    {
    public:

        /// This is just a test.
        song& operator=(const song&) = delete;
        /**
         * Default constructor.
         */
        song() : title(hw7::EMPTY) {}

        /**
         * @todo Make sure this constructor loads and registers all sound clips by name.
         *       Can be done just by listing the clips directory.
         */
        song (const hw7::str& s, JSON config);

        /**
         * @return The next audio clip to be played, or an empty clip if
         * `pause` is `true`.
         */
        h2o2::audio_clip& next_clip();

        /**
         * Push `pat` to the pattern stack, wait until it pops itself and,
         * when it does, push it back if its `repeat` count is 0 or add it to
         * the pattern map if it has a name that is not already there.
         * If it has no name then it's disposable after its popped for the last time.
         * `pattern` may actually pop itself and handle lookup table registration.
         * @param pat The pattern to load.
         * @return `EXIT_SUCCESS` or some relevant code.
         *
         * NOTE: changed to accept pattern by value so we can move it into the stack
         * and avoid extra copies.
         */
        ErrCode load(h2o2::pattern);
        bool is_clip_name(const hw7::str&);
        static ma_uint32 get_clip_sampleRate();
        static Path get_clips_dir();

        /**
         * Output operator
         */
        friend std::ostream& operator<<(std::ostream& os, const song& s)
        {
            return os << s.title;
        }


    // protected:
        hw7::str title;
        Path base;
        JSON script;
        Path clips_dir;

        // Data structures
        std::stack<h2o2::pattern> patterns;
        std::queue<hw7::str> clips; // Enqueue the clip's name, not the clip itself.
        
        // Lookup tables for named clips and patterns.
        /// Just enqueue the name of the clip & store the clip itself in the registry.
        std::map<hw7::str, audio_clip> clip_map;
        std::map<hw7::str, pattern> pat_map;

        Path folder;
    };

} //h2o2
