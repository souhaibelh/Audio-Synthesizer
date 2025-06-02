#include "../../include/model/oscillators/Oscillator.h"
#include <cmath>
#include <iostream>
//
// Created by judoj on 27/05/2025.
//
Oscillator::Oscillator(const int SAMPLE_RATE, const float scale, const float& frequency, const float& frequencyOffset) :
    SAMPLE_RATE(SAMPLE_RATE), scale(scale), frequency(frequency), frequencyOffset(frequencyOffset) {
}

void Oscillator::setStrategy(const WaveformStrategy *strategy) {
    this->strategy = strategy;
}