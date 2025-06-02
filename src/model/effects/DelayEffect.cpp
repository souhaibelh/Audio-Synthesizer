//
// Created by judoj on 02/06/2025.
//
#include "../../include/model/effects/DelayEffect.h"

DelayEffect::DelayEffect(const int &sampleRate, const float &delayMix, const float &delayTimeSec) : sampleRate(sampleRate), delayMix(delayMix), delayTimeSec(delayTimeSec) {

}


void DelayEffect::process(float *audioBuffer, const long &framesPerBuffer) {
    static const int bufferSize = 44100;
    static float delayBufferL[bufferSize] = {0.0f};
    static float delayBufferR[bufferSize] = {0.0f};
    static int writeIndex = 0;

    int delaySamples = static_cast<int>((delayTimeSec * sampleRate)) % sampleRate;
    int readIndex = (writeIndex - delaySamples + bufferSize) % bufferSize;

    for (int i = 0; i < framesPerBuffer; ++i) {
        int bufferPos = 2 * i;

        float inL = audioBuffer[bufferPos];
        float inR = audioBuffer[bufferPos + 1];

        float delayedL = delayBufferL[readIndex];
        float delayedR = delayBufferR[readIndex];

        float outL = inL + delayMix * delayedL;
        float outR = inR + delayMix * delayedR;

        audioBuffer[bufferPos]     = outL;
        audioBuffer[bufferPos + 1] = outR;

        delayBufferL[writeIndex] = outL;
        delayBufferR[writeIndex] = outR;

        writeIndex = (writeIndex + 1) % bufferSize;
        readIndex  = (readIndex + 1) % bufferSize;
    }
}

