#include "../../include/model/AudioGenerator.h"
#include <iostream>
#include <cmath>
#include "../../include/model/utils/Parameters.h"
#include "../../include/model/utils/OscillatorManager.h"

constexpr int FRAMES_PER_BUFFER {256};
constexpr int SAMPLE_RATE {48000};

AudioGenerator::AudioGenerator(SynthParameters &parameters, AudioEngine &engine, OscillatorManager& oscManager) :
    parameters(parameters), audioEngine(engine), audioContext{ &parameters, &engine, &oscManager } {
}

double AudioGenerator::currentTimeInSeconds = 0.0;

int AudioGenerator::audioCallback(const void *inputBuffer,
                                  void *outputBuffer,
                                  unsigned long framesPerBuffer,
                                  const PaStreamCallbackTimeInfo *timeInfo,
                                  PaStreamCallbackFlags statusFlags,
                                  void *userData) {

    auto* context = static_cast<AudioContext*>(userData);
    auto* out = static_cast<float*>(outputBuffer);
    (void)inputBuffer;

    {
        std::unique_lock lock(context->synth->mutex);
        currentTimeInSeconds += static_cast<double>(framesPerBuffer) / SAMPLE_RATE;
        context->synth->currentTime = currentTimeInSeconds;
    }

    std::shared_lock noteLock(context->synth->noteMutex);
    std::shared_lock lock(context->synth->mutex);

    Oscillator* osc1 = context->oscManager->getOsc1();
    Oscillator* osc2 = context->oscManager->getOsc2();
    context->oscManager->setStrategyOsc2(0);
    context->oscManager->setStrategyOsc1(context->synth->osc1.waveform);
    context->oscManager->setStrategyOsc2(context->synth->osc2.waveform);

    if (context->synth->osc1.enabled && context->synth->osc2.enabled) {
        context->engine->setMixerOsc1(osc1);
        context->engine->setMixerOsc2(osc2);
        context->engine->mix(out, framesPerBuffer);
        context->engine->process(out, framesPerBuffer);
        context->engine->setAmplitude(0.2f, out, framesPerBuffer);
    } else if (context->synth->osc1.enabled) {
        osc1->fill(out, framesPerBuffer);
        context->engine->process(out, framesPerBuffer);
        context->engine->setAmplitude(0.2f, out, framesPerBuffer);
    } else if (context->synth->osc2.enabled) {
        osc2->fill(out, framesPerBuffer);
        context->engine->process(out, framesPerBuffer);
        context->engine->setAmplitude(0.2f, out, framesPerBuffer);
    } else {
        std::fill_n(out, framesPerBuffer * 2, 0.0f);
    }
    
    return 0;
}

void AudioGenerator::init() {
    PaError errorInit = Pa_Initialize();
    if( errorInit != paNoError ) {
        std::cerr << "PortAudio error in Pa_Initialize(): "
                  << Pa_GetErrorText( errorInit ) << std::endl;
        return;
    }

    PaError errorStream = Pa_OpenDefaultStream(&stream,
                                               0,
                                               2,
                                               paFloat32,
                                               SAMPLE_RATE,
                                               FRAMES_PER_BUFFER,
                                               audioCallback,
                                               &audioContext );
    if (errorStream != paNoError) {
        std::cerr << "PortAudio error in Pa_OpenDefaultStream(): "
                  << Pa_GetErrorText(errorStream) << std::endl;
        return;
    }

    errorStream = Pa_StartStream(stream);
    if (errorStream != paNoError) {
        std::cerr << "PortAudio error in Pa_StartStream(): "
                  << Pa_GetErrorText(errorStream) << std::endl;
        return;
    }
}