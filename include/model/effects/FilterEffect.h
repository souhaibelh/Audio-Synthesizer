//
// Created by judoj on 01/06/2025.
//

#ifndef FILTEREFFECT_H
#define FILTEREFFECT_H
#include "AudioEffect.h"

// Class that represents a low pass filter

class FilterEffect : public AudioEffect {
private:
    const int& sampleRate;
    const int& cutoff;
    const float& resonance;
public:
    FilterEffect(const int& sampleRate, const int& cutoff, const float& resonance);
    void process(float* audioBuffer, const long& framesPerBuffer) override;
};

#endif //FILTEREFFECT_H
