/**
 * @file clip.cpp
 *
 * Class that loads an audio file.
 */
#include "miniaudio.h"
#include "hw7.hpp"
#include "clip.hpp"

using namespace std;
using namespace hw7;
using namespace h2o2;

audio_clip::audio_clip(const Path& p) : fp(p) {}

bool audio_clip::load(const str& filename)
{
    ma_decoder decoder;

    if (ma_decoder_init_file(filename.c_str(), nullptr, &decoder) != MA_SUCCESS)
        return false;

    channels = decoder.outputChannels;
    sampleRate = decoder.outputSampleRate;

    ma_uint64 totalFrames;

    ma_decoder_get_length_in_pcm_frames(&decoder, &totalFrames);

    frames = totalFrames;

    samples.resize(
        totalFrames * channels
    );

    ma_uint64 framesRead = 0;
    ma_decoder_read_pcm_frames(
        &decoder,
        samples.data(),
        totalFrames,
        &framesRead
    );

    ma_decoder_uninit(&decoder);

    return framesRead == totalFrames;
}

bool loadClip(string filename, Clip &clip)
{
    ma_decoder decoder;

    if (ma_decoder_init_file(filename.c_str(), nullptr, &decoder) != MA_SUCCESS)
        return false;

    clip.channels = decoder.outputChannels;
    clip.sampleRate = decoder.outputSampleRate;

    ma_uint64 totalFrames;

    ma_decoder_get_length_in_pcm_frames(&decoder, &totalFrames);

    clip.frames = totalFrames;

    clip.samples.resize(
        totalFrames * clip.channels
    );

    ma_uint64 framesRead = 0;
    ma_decoder_read_pcm_frames(
        &decoder,
        clip.samples.data(),
        totalFrames,
        &framesRead
    );

    ma_decoder_uninit(&decoder);

    return framesRead == totalFrames;
}

