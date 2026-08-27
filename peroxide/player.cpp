/**
 * @file player.cpp
 *
 * Play a sequence of sound clips according to the `song_list`.
 */
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "hw7.hpp"
#include "globals.hpp"
#include "player.hpp"
using namespace std;
using namespace hw7;
using namespace h2o2;


player::player(const song_list& sl) : songs(sl)
{
    // Load all the audio clips of every song in the song_list.
};

void player::fill(float* output, ma_uint32 frames)
{
    if (!playing)
    {
        std::fill(output, output + frames * 2, 0.0f);
        return;
    }
    
    for (ma_uint32 i = 0; i < frames; i++)
    {
        Clip& clip = current_song.next_clip();

        if (pos == 0)
        {
            cout << "Starting " << current_song << endl;
            //  << (playingBreak ? "Break" : "Intro")
            //  << "\n";
            
        }
        
        if (clip.samples.empty())
        {
            output[i * 2] = 0;
            output[i * 2 + 1] = 0;
            continue;
        }
        

        // Assuming stereo float samples:
        output[i * 2]     = clip.samples[pos * 2];     // left
        output[i * 2 + 1] = clip.samples[pos * 2 + 1]; // right

        pos++;

        if (pos >= clip.frames)
        {
            pos = 0;

            if (pedal) // Someone stepped on the sustain pedal
            {
                pedal = false;
                // playingBreak = true;
                cout << "Signal received from sustain pedal" << endl;
            }
        }
    }
}

