#include "instrument.hpp"
#include "listenerTask.hpp"
#include <fluidsynth.h>
#include <thread>
#include <iostream>
#include <chrono>
#include <memory>
#include <map>

static int currentPress = NOT_PRESSED; // Default starting key
static int octaveShift = 0;
static int currentInstrument = 0; // 0 - Piano, 1 - Harmonica ,2 - Violin

std::map<int, int> noteMapping = {
    {'A', 60},  // C
    {'S', 61},  // C#
    {'D', 62},  // D
    {'F', 63},  // D#
    {'G', 64},  // E
    {'H', 65},  // F
    {'J', 66},  // F#
    {'K', 67},  // G
    {'L', 68},  // G#
    {'Z', 69},  // A
    {'X', 70},  // A#
    {'C', 71}   // B
};

std::map <int, std::shared_ptr<Instrument>> instrumentsMap;

int main() {
    
    Piano piano;
    Harmonica harmonica;

    instrumentsMap[0] = std::make_shared<Piano>();
    instrumentsMap[1] = std::make_shared<Harmonica>();
    instrumentsMap[2] = std::make_shared<Violin>();
    
    int note = NOT_PRESSED;  // Track the current note being played
    bool heldKey = false; // Track if a key is held

    // Create the keyboard listener object
    KeyboardListener listenerTask;

    // Start the listener thread
    std::thread listThread(&KeyboardListener::StartListening, &listenerTask, std::ref(currentPress),
                                                 std::ref(octaveShift), std::ref(currentInstrument));

    // Main loop: Play notes based on the currentPress value
    while (currentPress != ESCAPE_PRESSED) {
        if (currentPress != NOT_PRESSED) 
        { // If a key is pressed
            if(noteMapping.find(currentPress) != noteMapping.end())
            {   
                int newNote = noteMapping[currentPress] + octaveShift;
                if (!heldKey || note != newNote) {
                    // If no key was previously held or the current key is different from the previous one
                    note = newNote;  // Store the pressed key
                    instrumentsMap[currentInstrument]->PlayNote(note, 100);  // Play the new note
                    heldKey = true;  // Indicate that a key is being held
                    std::cout << "Playing note: " << note << std::endl;
                }
            }
        }
        else if (heldKey ) {
            // If no key is pressed but one was held previously
            instrumentsMap[currentInstrument]->StopAllNotes();  // Stop the note when the key is released
            heldKey = false;  // Reset hold state
            std::cout << "Note stopped." << std::endl;
        }

        // Small delay to avoid high CPU usage in the loop
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }

    // Wait for the listener thread to finish
    listThread.join();

    std::cout << "Program exited." << std::endl;
    return 0;
}
