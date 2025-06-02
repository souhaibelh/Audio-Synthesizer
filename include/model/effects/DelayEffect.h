//
// Created by judoj on 02/06/2025.
//

#ifndef DELAYEFFECT_H
#define DELAYEFFECT_H
#include "AudioEffect.h"

class DelayEffect : public AudioEffect {
private:
    const int& sampleRate;
    const float& delayMix;
    const float& delayTimeSec;

public:
    DelayEffect(const int& sampleRate, const float& delayMix, const float& delayTimeSec);
    void process(float* audioBuffer, const long& framesPerBuffer) override;
};

#endif //DELAYEFFECT_H