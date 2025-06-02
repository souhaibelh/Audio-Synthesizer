//
// Created by judoj on 31/05/2025.
//
#include "MixEffect.h"

void MixEffect::process(float *audioBuffer, const long &framesPerBuffer) {
    this->osc1->fill(audioBuffer, framesPerBuffer);

    float tempBuffer[framesPerBuffer * 2];
    this->osc2->fill(tempBuffer, framesPerBuffer);

    for (unsigned int i = 0; i < framesPerBuffer * 2; i++) {
        *audioBuffer++ += tempBuffer[i];
    }
}

void MixEffect::setOsc1(Oscillator *osc1) {
    this->osc1 = osc1;
}

void MixEffect::setOsc2(Oscillator *osc2) {
    this->osc2 = osc2;
}