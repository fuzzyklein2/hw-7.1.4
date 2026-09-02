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
    //     song(const song&) = delete;
    // song& operator=(const song&) = delete;

    // song(song&&) = default;
    // song& operator=(song&&) = default;

        /// This is just a test.
        song(const song&) = delete;
        song& operator=(const song&) = delete;
    
        song(song&&) = default;
        song& operator=(song&) = default;
        /**
         * Default constructor.
         * @param title Title of the song and the name of its directory inside `songs`.
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
        ErrCode load(JSON);
        ErrCode load(const hw7::str&);

        /**
         * Determine whether a string represents a clip.
         * If it does there is a file with the string as its name in the clips directory.
         * @param s String to check.
         * @return `true` if an existing clip file corresponds to the name.
         * False otherwise.
         */
        static bool is_clip_name(const hw7::str&);

        /**
         * Get the sample rate of a random audio file from the clips directory.
         * @return Sample rate.
         */
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
        // pattern* current_pat;

        // Data structures
        std::stack<std::unique_ptr<pattern>> patterns;
        std::queue<hw7::str> clips; // Enqueue the clip's name, not the clip itself.
        
        // Lookup tables for named clips and patterns.
        /// Just enqueue the name of the clip & store the clip itself in the registry.
        std::map<hw7::str, audio_clip> clip_map;
        std::map<hw7::str, JSON> pat_map;

        Path folder;
    };

    using SongPtr = std::unique_ptr<song>;

} //h2o2
