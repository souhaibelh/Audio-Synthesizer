//
// Created by judoj on 27/05/2025.
//

#ifndef OSCILLATOR_H
#define OSCILLATOR_H
#include <cmath>

#include "WaveformStrategy.h"

class WaveformStrategy;

inline static const float defaultFreq = 440.0f;
inline static const float defaultOffset = 0.0f;

class Oscillator {
protected:
    float phase = 0.0f;
    float scale;
    const float& frequency;
    const float& frequencyOffset;
    int SAMPLE_RATE;
    const WaveformStrategy* strategy;

public:
    explicit Oscillator(int, float scale, const float& frequency, const float& frequencyOffset);
    void setStrategy(const WaveformStrategy* strategy);
    void fill(float* audioBuffer, const unsigned long& framesPerBuffer) {
        for (unsigned int i = 0; i < framesPerBuffer; i++) {
            const float sample = this->strategy->generateSample(phase, scale);
            *audioBuffer++ = sample;
            *audioBuffer++ = sample;
            phase += 2.0f * M_PI * (frequency + frequencyOffset) / SAMPLE_RATE;
            if (phase >= 2.0 * M_PI) {
                phase -= 2.0 * M_PI;
            }
        }
    }
};

#endif //OSCILLATOR_H
