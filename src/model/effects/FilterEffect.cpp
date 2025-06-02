//
// Created by judoj on 02/06/2025.
//
#include "../../include/model/effects/FilterEffect.h"
#include "math.h"

FilterEffect::FilterEffect(const int &sampleRate, const int &cutoff, const float &resonance) : sampleRate(sampleRate), cutoff(cutoff), resonance(resonance) {

}

void FilterEffect::process(float *audioBuffer, const long &framesPerBuffer) {
    double q = 0.5 / (1.0 - resonance);
    double omega = 2.0 * M_PI * cutoff / sampleRate;
    double alpha = std::sin(omega) / (2.0 * q);
    double cosw = std::cos(omega);

    const double norm = 1.0 / (1.0 + alpha);
    const double a0 = (1.0 - cosw) * 0.5 * norm;
    const double a1 = (1.0 - cosw) * norm;
    const double a2 = (1.0 - cosw) * 0.5 * norm;
    const double b1 = -2.0 * cosw * norm;
    const double b2 = (1.0 - alpha) * norm;

    static float x1L = 0.0f, x2L = 0.0f, y1L = 0.0f, y2L = 0.0f;
    static float x1R = 0.0f, x2R = 0.0f, y1R = 0.0f, y2R = 0.0f;

    for (long i = 0; i < framesPerBuffer; ++i) {
        float inputL = *audioBuffer;
        float outputL = a0 * inputL + a1 * x1L + a2 * x2L - b1 * y1L - b2 * y2L;
        *audioBuffer++ = outputL;
        x2L = x1L;
        x1L = inputL;
        y2L = y1L;
        y1L = outputL;

        float inputR = *audioBuffer;
        float outputR = a0 * inputR + a1 * x1R + a2 * x2R - b1 * y1R - b2 * y2R;
        *audioBuffer++ = outputR;
        x2R = x1R;
        x1R = inputR;
        y2R = y1R;
        y1R = outputR;
    }
}