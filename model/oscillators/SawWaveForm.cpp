//
// Created by judoj on 02/06/2025.
//
#include "SawWaveStrategy.h"
#include "math.h"

float SawWaveForm::generateSample(const float &phase, const float &scale) const {
    return scale * (2.0f * (phase / (2.0 * M_PI)) - 1.0f);
}