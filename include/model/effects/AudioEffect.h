//
// Created by judoj on 31/05/2025.
//

#ifndef AUDIOEFFECT_H
#define AUDIOEFFECT_H

class AudioEffect {
public:
    virtual void process(float* audioBuffer, const long& framesPerBuffer) = 0;
    virtual ~AudioEffect() = default;
};

#endif //AUDIOEFFECT_H
