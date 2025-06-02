//
// Created by judoj on 02/06/2025.
//
#include "SquareWaveStrategy.h"
#include <math.h>

float SquareWaveStrategy::generateSample(const float &phase, const float &scale) const {
    return std::sin(phase) > 0.0f ? scale : -scale;
}