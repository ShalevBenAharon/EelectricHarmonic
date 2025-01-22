#pragma once 

#include <atomic>
#include <thread>
#define VC_ESC 27
#define NOT_PRESSED -1
#define TOTAL_INSTRUMENT 3

class KeyboardListener {
public:
    KeyboardListener();
    ~KeyboardListener();
    void StartListening(int &currentPress, int &octaveShift, int &currentInstrument);

private:
    bool isRunning;
};
