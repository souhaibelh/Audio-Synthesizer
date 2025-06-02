//
// Created by judoj on 27/05/2025.
//

#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <atomic>
#include <mutex>
#include <shared_mutex>

#include "OscillatorManager.h"
#include "../AudioEngine.h"

struct OscillatorSettings {
    bool enabled = false;
    int waveform = 0;
    float frequencyOffset = 0;
};

struct ADSR {
    float attack = 0.1f;
    float release = 0.5f;
};

struct FilterSettings {
    int cutoff = 20000;
    float resonance = 0.0f;
};

struct DelaySettings {
    float time = 0.1f;
    float mix = 0.0f;
};

struct Note {
    float frequency = 440.0f;
    bool isOn = false;
    double noteOnTime = 0.0;
    double noteOffTime = 0.0;
};

struct SynthParameters {
    std::shared_mutex mutex;
    std::shared_mutex noteMutex;
    OscillatorSettings osc1;
    OscillatorSettings osc2;
    ADSR envelope;
    FilterSettings filter;
    DelaySettings delay;
    Note note;
    double currentTime = 0.0;
};

struct AudioContext {
    SynthParameters* synth;
    AudioEngine* engine;
    OscillatorManager* oscManager;

    AudioContext(SynthParameters* synth, AudioEngine* engine, OscillatorManager* oscManager)
        : synth(synth), engine(engine), oscManager(oscManager) {}
};

#endif //PARAMETERS_H
