//
// Created by judoj on 30/05/2025.
//

#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include "effects/EnvelopeEffect.h"
#include "effects/DelayEffect.h"
#include "effects/FilterEffect.h"
#include "effects/MixEffect.h"

class AudioEngine {
    MixEffect& mixer;
    EnvelopeEffect& enveloper;
    FilterEffect& filter;
    DelayEffect& delay;
public:
    void process(float *audioBuffer, const unsigned long &framesPerBuffer);
    void mix(float* audioBuffer, const unsigned long& framesPerBuffer);
    void setMixerOsc1(Oscillator* osc);
    void setMixerOsc2(Oscillator* osc);
    void setAmplitude(const float& factor, float* audioBuffer, const unsigned long& framesPerBuffer);
    AudioEngine(MixEffect& mixer, EnvelopeEffect& enveloper, FilterEffect& filter, DelayEffect& delay);
};

#endif //AUDIOENGINE_H
