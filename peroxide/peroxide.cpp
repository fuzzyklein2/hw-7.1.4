/**
 * @file peroxide.cpp
 *
 * Subclass Program.
 */
#include <csignal>

#include "hw7.hpp"
#include "keyboard.hpp"
#include "midi.hpp"
#include "peroxide.hpp"

using namespace std;
using namespace hw7;
using namespace h2o2;

void data_callback(
    ma_device* device,
    void* output,
    const void* /*input*/,
    ma_uint32 frameCount)
{
    auto* p = static_cast<player*>(device->pUserData);

    p->fill(
        static_cast<float*>(output),
        frameCount
    );
}

void signal_handler(int)
{
    running = false;
}

void Peroxide::play_audio()
{
    try
    {
        debug("Audio thread entered.");
        ostringstream oss;
        
        player p(songs);

        debug("Player constructed");
    
        ma_device_config config = ma_device_config_init(ma_device_type_playback);

        debug("Device config initialized");
        
        config.playback.format = ma_format_f32;
        config.playback.channels = 2;
        config.sampleRate = song::get_clip_sampleRate(); /// @marker Clip needs to be defined.
        
        debug("Sample rate obtained");
    
        config.dataCallback = data_callback;
        config.pUserData = &p;
    
        ma_device device;

        debug("Initializing device");
    
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

        debug("Device initialized");
    
        cout << "Press sustain pedal to start...\n";
        
        while (running && !pedal)
        {
            this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
        cout << "Starting playback.\n";
        p.play();
        debug("p.play() returned");
        cout << "Playing forever... Ctrl-C to quit.\n";
    
        while (running)
        {
            oss << "audio waiting: running = " << running.load() << endl;
            debug(oss);
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        debug("Audio thread terminating");
    
        ma_device_uninit(&device);
    }
    catch (const exception& e)
    {
        cerr << e.what() << "\n";
        running = false;
    }
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
    auto lines = text.split(NEWLINE);
    erase(lines, EMPTY);
    text = str(NEWLINE).join(lines);
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

