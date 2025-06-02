//
// Created by judoj on 02/06/2025.
//

#ifndef DELAYEFFECT_H
#define DELAYEFFECT_H
#include "AudioEffect.h"

// Class that represents a delay effect applied to a audio buffer

class DelayEffect : public AudioEffect {
private:
    const int& sampleRate;
    const float& delayMix;
    const float& delayTimeSec;

public:
    DelayEffect(const int& sampleRate, const float& delayMix, const float& delayTimeSec);

    // Method that takes an audioBuffer and framesPerBuffer and applies a delay effect to it,
    // the delayTimeSec parameter is how far in the past to go in seconds, the delayMix is how
    // strong the delay is.
    void process(float* audioBuffer, const long& framesPerBuffer) override;
};

#endif //DELAYEFFECT_H