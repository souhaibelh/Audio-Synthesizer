//
// Created by judoj on 02/06/2025.
//
#include "../../include/model/oscillators/SineWaveStrategy.h"
#include <cmath>

float SineWaveStrategy::generateSample(const float &phase, const float &scale) const {
    return scale * std::sin(phase);
}