//
// Created by judoj on 31/05/2025.
//

#ifndef MIXEFFECT_H
#define MIXEFFECT_H
#include <vector>

#include "AudioEffect.h"
#include "../oscillators/Oscillator.h"

// Class that represents a mix effect

class MixEffect : public AudioEffect {
private:
    Oscillator* osc1 = nullptr;
    Oscillator* osc2 = nullptr;

public:
    void process(float* audioBuffer, const long& framesPerBuffer) override;
    void setOsc1(Oscillator* osc1);
    void setOsc2(Oscillator* osc2);
};

#endif //MIXEFFECT_H