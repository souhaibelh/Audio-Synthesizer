#ifndef SIMPLE_SYNTH_AUDIOGENERATOR_H
#define SIMPLE_SYNTH_AUDIOGENERATOR_H

#include "AudioEngine.h"
#include "utils/OscillatorManager.h"
#include "portaudio.h"
#include "utils/Parameters.h"

class AudioGenerator {
public:
    explicit AudioGenerator(SynthParameters& parameters, AudioEngine& audioEngine, OscillatorManager& oscManager);
    void init();

private:
    AudioEngine& audioEngine;
    SynthParameters& parameters;
    AudioContext audioContext;
    static int audioCallback( const void *inputBuffer, void *outputBuffer,
                              unsigned long framesPerBuffer,
                              const PaStreamCallbackTimeInfo* timeInfo,
                              PaStreamCallbackFlags statusFlags,
                              void *userData );

    static double currentTimeInSeconds;

};

#endif //SIMPLE_SYNTH_AUDIOGENERATOR_H
