//
// Created by judoj on 30/05/2025.
//
#include "../../include/model/AudioEngine.h"
#include <iostream>

AudioEngine::AudioEngine(
    MixEffect &mixer,
    EnvelopeEffect &enveloper,
    FilterEffect &filter,
    DelayEffect &delay) :
    mixer(mixer),
    enveloper(enveloper),
    filter(filter),
    delay(delay) {
}

void AudioEngine::setMixerOsc1(Oscillator *osc) {
    this->mixer.setOsc1(osc);
}

void AudioEngine::setMixerOsc2(Oscillator *osc) {
    this->mixer.setOsc2(osc);
}

void AudioEngine::mix(float* audioBuffer, const unsigned long& framesPerBuffer) {
    mixer.process(audioBuffer, framesPerBuffer);
}

void AudioEngine::setAmplitude(const float &factor, float* audioBuffer, const unsigned long& framesPerBuffer) {
    for (int i = 0; i < framesPerBuffer * 2; i++) {
        *audioBuffer = (*audioBuffer) * factor;
        audioBuffer++;
    }
}

void AudioEngine::process(float *audioBuffer, const unsigned long &framesPerBuffer) {
    enveloper.process(audioBuffer, framesPerBuffer);
    filter.process(audioBuffer, framesPerBuffer);
    delay.process(audioBuffer, framesPerBuffer);
}