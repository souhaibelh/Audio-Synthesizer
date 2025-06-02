//
// Created by judoj on 01/06/2025.
//

#ifndef ENVELOPEEFFECT_H
#define ENVELOPEEFFECT_H
#include "AudioEffect.h"

// Class that represents an envelope effect, it makes the start smoother and the end of the note too

class EnvelopeEffect : public AudioEffect {
private:
    const float& attackTime;
    const float& releaseTime;
    const bool& isOn;
    const double& offTime;
    const double& onTime;
    const double& currentTime;

public:
    EnvelopeEffect(
        const float& attackTime,
        const float& releaseTime,
        const bool& isOn,
        const double& offTime,
        const double& onTime,
        const double& currentTime
    );

    // Method that applies a delay effect to the audio buffer
    void process(float* audioBuffer, const long& framesPerBuffer) override;
};

#endif //ENVELOPEEFFECT_H
