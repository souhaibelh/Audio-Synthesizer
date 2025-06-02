
#ifndef TESTINSTRUCT_MAINWINDOW_H
#define TESTINSTRUCT_MAINWINDOW_H
#include <string>
#include <bits/std_thread.h>
#include <SDL3/SDL.h>
#include "../model/utils/Parameters.h"

class MainWindow {
public :
    explicit MainWindow(SynthParameters& parameters);
    void oscillatorOptions();
    void envelopeOptions();
    void filterOptions();
    void delayOptions();
    void handleNoteTrigger();
    void playNote(float frequency, int durationMs);
    void init();
    void run();
private:
    SynthParameters& parameters;
    std::thread samplesThread;
    std::atomic<bool> stopSamplesThread{false};
    void draw();
    SDL_Window* window { nullptr };
    SDL_Renderer* renderer { nullptr };
};

#endif //TESTINSTRUCT_MAINWINDOW_H
