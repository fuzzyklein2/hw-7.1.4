/**
 * @file peroxide.cpp
 *
 * Peroxide class member functions.
 */

#include <termios.h>
#include <unistd.h>

#include <csignal>

#include <algorithm> // sort
#include <sstream>   // ostringstream

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <rtmidi/RtMidi.h>

#include "hw7.hpp"

using namespace std;
using namespace hw7;

using Boolean = atomic<bool>;
using Index = Number;

Boolean pedal = false;
Boolean running = true;

struct Clip
{
    vector<float> samples;
    ma_uint64 frames = 0;
    ma_uint32 channels = 0;
    ma_uint32 sampleRate = 0;
};

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

namespace h2o2
{

    enum class State
    {
        PAUSE, PLAY, FF, REWIND, STOP
    };

    class str_list : StrList
    {
    public:

        /**
         * Default constructor.
         */
        str_list() = default;

        /**
         * Construct a `StrList` by splitting `text` on `endl`.
         * 
         * Make sure the returned value is a `str_list` and no demotion occurs.
         */
        str_list(const str& text) : StrList(text.split(str("\n"))) {}
    };

    class clip_list : public vector<Clip> {};

    class song
    {
    public:
        song() : title(EMPTY) {}
        song (const str& s, JSON config) : 
            title(s),
            base(config["session folder"].get<string>()),
            current_clip_index(0)
        {
            script = load_data(base / "songs" / string(title) / "song.json");
        }

        Clip& current_clip()
        {
            return clips[current_clip_index];
        }

        Clip& next_clip()
        {
            return clips[current_clip_index++]; // It won't really be this simple.
        }

        friend ostream& operator<<(ostream& os, const song& s)
        {
            return os << s.title;
        }

    protected:
        str title;
        Path base;
        JSON script;
        clip_list clips;
        Index current_clip_index;
    };

    class song_list : public vector<song>
    {
    public:
        song_list() = default;
        song_list(const str& s, JSON config)
        {
            for (const str s2 : s.split("\n"))
            push_back(song(s2, config));
        }
        
    protected:
        
    };

    class player
    {
    public:
        player(const song_list&);
        void fill(float* output, ma_uint32 frames);
        void play() {playing = true;}
        /// Return the current clip.
        Clip clip() { return current_song.current_clip(); }
    protected:
        bool playing = false;
        bool step = false;
        size_t pos = 0;
        song_list songs;
        song current_song;
    };

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

} // h2o2
using namespace h2o2;

/**
 * Subclass `Filter`.
 */
class SongList : Filter<String>
{
public:
    SongList() = default;
    SongList (const StrList& S) : Filter<String>(S) {}

    SongList (const str& s) : Filter<String>(s.split("\n")) {}
};

/**
 * Subclass `Program`.
 */
class Peroxide : Program
{
public:
    Peroxide(int argc, char **argv) : Program (argc, argv)
    {
        base = config["session folder"].get<string>();
    }

    void play_audio();
    ErrCode run();
protected:
    Path base;
    song_list songs;
};

void keyboard_listener()
{
    termios old_settings;
    termios new_settings;

    tcgetattr(STDIN_FILENO, &old_settings);
    new_settings = old_settings;

    new_settings.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

    while (running)
    {
        char c;

        if (read(STDIN_FILENO, &c, 1) == 1)
        {
            debug("Keyboard event received: " + c);
            if (c == ' ')
                pedal = true;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
}

void midi_listener()
{
    RtMidiIn midi;
    const auto ports = midi.getPortCount();
    cout << "MIDI inputs: " << ports << endl;
    for (Index i = 0; i < ports; i++)
    {
        cout << i << ": " << midi.getPortName(i) << endl;
    }

    // Open the Alesis port, not Midi Through
    midi.openPort(1);

    // Listen for MIDI messages...
    
    cout << "Listening..." << endl;

    vector<unsigned char> message;

    while (running)
    {
        midi.getMessage(&message);

        if (!message.empty())
        {
            cout << "Message:";
            for (auto byte : message)
                cout << " " << (int)byte;
            cout << "\n";

            if (message.size() == 3 &&
                message[0] == 0xB0 &&
                message[1] == 64)
            {
                if (message[2] > 63)
                {
                    cout << "PEDAL DOWN\n";
                    if (!pedal)
                        pedal = true;
                    // else
                    //     breakRequested = true;
                }
            }
        }

        this_thread::sleep_for(chrono::milliseconds(10));
    }
} // midi_listener
 // I don't know where the brackets got misaligned but the compiler thinks they are.

void data_callback(
    ma_device* device,
    void* output,
    const void* input,
    ma_uint32 frameCount)
{
    auto* p =
        static_cast<player*>(device->pUserData);

    p->fill(
        static_cast<float*>(output),
        frameCount
    );
}

void Peroxide::play_audio()
{
    try
    {
        player p(songs);
    
        // TODO: load intro and breakClip here
    
        ma_device_config config =
            ma_device_config_init(ma_device_type_playback);
    
        config.playback.format = ma_format_f32;
        config.playback.channels = 2;
        config.sampleRate = p.clip().sampleRate; /// @marker Clip needs to be defined.
    
        config.dataCallback = data_callback;
        config.pUserData = &p;
    
        ma_device device;
    
        if (ma_device_init(nullptr, &config, &device) != MA_SUCCESS)
        {
            cerr << "Couldn't open playback device.\n";
            return;
        }
    
        if (ma_device_start(&device) != MA_SUCCESS)
        {
            cerr << "Couldn't start playback.\n";
            ma_device_uninit(&device);
            return;
        }
    
        cout << "Press sustain pedal to start...\n";
        
        while (running && !pedal)
        {
            this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
        cout << "Starting playback.\n";
        p.play();
        cout << "Playing forever... Ctrl-C to quit.\n";
    
        while (running)
        {
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    
        ma_device_uninit(&device);
    }
    catch (const exception& e)
    {
        cerr << e.what() << "\n";
        running = false;
    }
}

void signal_handler(int)
{
    running = false;
}



ErrCode Peroxide::run()
{
    debug("Running peroxide");
    debug("Arguments:");

    auto SONG_LISTS_DIR = Path(config["session folder"]) / "lists";

    ostringstream oss;
    for (const auto& s : args)
    {
        oss << s;
    }
    oss << endl;
    debug(oss);
    oss << "Session folder: " << config["session folder"];
    info(oss.str());

    str text;
    // SongList songs;
    PathList song_list_files;

    // If there is input, it should be the song list itself.
    if (!input.empty())
    {
        text = str(input);
        // songs = SongList{input};
    }
    else if (!args.empty())
    {
        text = str(read_file(Path(args[0])));
    }
    else
    {
        song_list_files = listdir(SONG_LISTS_DIR);
        sort(song_list_files.begin(), song_list_files.end(), greater<>());
        text = str(read_file(song_list_files[0]));
        // C++ will `throw` here on errors without any help?
    }
    
    // auto SONG_LIST_FILE = "20260802.txt";

    
    // str s = read_file(Path(config["session folder"]) / "lists" / SONG_LIST_FILE);

    info(text);

    /// @warn `text` must be valid before calling `play_audio`.
    songs = song_list(text, config);

    signal(SIGINT, signal_handler);
    thread keyboardThread(keyboard_listener);
    thread midiThread(midi_listener);
    // thread audioThread(play_audio); /// @see Warning above.
    thread audioThread(&Peroxide::play_audio, this);
    keyboardThread.join();
    midiThread.join();
    audioThread.join();

        
    
    return EXIT_SUCCESS;
}

/**
 * main
 *
 * @brief Entry point of the program.
 *
 * Parses the command line, initializes the application, and starts
 * the main processing loop.
 *
 * @param argc Number of command line arguments.
 * @param argv Array of command line arguments.
 *
 * @return Exit status.
 */
int main(
    int argc, // Argument count
    char **argv // Cannot be `const` or CLI11 won't work.
) {
    auto p = Peroxide(argc, argv);
    
    return p.run();
}
