//
// Created by judoj on 01/06/2025.
//
#include "../../include/model/effects/EnvelopeEffect.h"

#include <iostream>

EnvelopeEffect::EnvelopeEffect(
    const float &attackTime,
    const float &releaseTime,
    const bool &isOn,
    const double &offTime,
    const double &onTime,
    const double &currentTime) :
    attackTime(attackTime),
    releaseTime(releaseTime),
    isOn(isOn), offTime(offTime),
    onTime(onTime),
    currentTime(currentTime)  {
}

void EnvelopeEffect::process(float* audioBuffer, const long& framesPerBuffer) {
    double multiplier;

    if (isOn) {
        if (currentTime - onTime <= attackTime) {
            multiplier = (currentTime - onTime) / attackTime;
        } else {
            multiplier = 1.0f;
        }
    } else {
        if (currentTime - offTime <= releaseTime) {
            multiplier = 1.0 - (currentTime - offTime) / releaseTime;
            if (multiplier < 0.0) multiplier = 0.0;
        }
    }

    for (unsigned int i = 0; i < framesPerBuffer; ++i) {
        *audioBuffer++ *= multiplier;
        *audioBuffer++ *= multiplier;
    }
}