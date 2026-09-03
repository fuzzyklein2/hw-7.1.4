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


/**
 * @warn There must be a valid `audio_clip` in the queue at exit.
 *       (`player::play_audio` wants to know its sample rate.)
 * @return Error code.
 */
audio_player::audio_player(song_list& sl) : songs(sl),
                                            current_song_index(0),
                                            current_clip(nullptr)
{
    // Load all the audio clips of every song in the song_list.
};

void audio_player::fill(float* output, ma_uint32 frames)
{
    if (!running) {
        return;
    }

    info(str("FILL: ") + to_string(frames) + " frames.\n");

    if (!playing) {
        std::fill(output, output + frames * 2, 0.0f);
        return;
    }

    for (ma_uint32 i = 0; i < frames; i++)
    {
        // Get the first clip, or get the next one after
        // the previous clip has been exhausted.
        if (current_clip == nullptr)
        {
            current_clip = next_clip();
            if (current_clip == nullptr)
            {
                continue;
            }
            pos = 0;
        }

        output[i * 2]     = current_clip->samples[pos * 2];
        output[i * 2 + 1] = current_clip->samples[pos * 2 + 1];

        ++pos;

        if (pos >= current_clip->frames)
        {
            current_clip = nullptr;
        }
    }
}
// void audio_player::fill(float* output, ma_uint32 frames)
// {
//     if (running) {
//     cout << "FILL: " << frames << " frames\n";
    
//     if (!playing)
//     {
//         std::fill(output, output + frames * 2, 0.0f);
//         return;
//     }
    
//     for (ma_uint32 i = 0; i < frames; i++)
//     {
//         // Debugging test I haven't tried it yet. Should make a noise.
//         output[i * 2]     = 0.25f;
//         output[i * 2 + 1] = 0.25f;

//         std::cout << "FILL: about to get next clip\n";
//         audio_clip& clip = songs[current_song_index].next_clip();
//         std::cout << "FILL: got next clip\n";
        
//         if (pos == 0)
//         {
//             cout << "Starting " << songs[current_song_index] << endl;
//             //  << (playingBreak ? "Break" : "Intro")
//             //  << "\n";
            
//         }
        
//         if (clip.samples.empty())
//         {
//             output[i * 2] = 0;
//             output[i * 2 + 1] = 0;
//             continue;
//         }
        
//         if (pos * 2 + 1 >= clip.samples.size())
//         {
//             cerr << "BAD CLIP: pos=" << pos
//                  << " frames=" << clip.frames
//                  << " samples=" << clip.samples.size()
//                  << endl;
//             abort();
//         }
        
//         // Assuming stereo float samples:
//         output[i * 2]     = clip.samples[pos * 2];     // left
//         output[i * 2 + 1] = clip.samples[pos * 2 + 1]; // right

//         pos++;

//         if (pos >= clip.frames)
//         {
//             pos = 0;

//             if (pedal) // Someone stepped on the sustain pedal
//             {
//                 pedal = false;
//                 // playingBreak = true;
//                 cout << "Signal received from sustain pedal" << endl;
//             }
//         }
//     }
//     } else { // if (running)
//         error("`player::fill` called after `running == false`!");
//     }
// }

