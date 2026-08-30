/**
 * @file midi.cpp
 *
 * Listen for MIDI events.
 */
#include <rtmidi/RtMidi.h>
#include "hw7.hpp"
using namespace std;
// using namespace hw7;

#include "globals.hpp"
#include "midi.hpp"
#include "types.hpp"

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
    debug("Midi thread terminating.");
} // midi_listener

