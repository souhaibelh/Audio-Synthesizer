//
// Created by judoj on 02/06/2025.
//

#ifndef SINEWAVESTRATEGY_H
#define SINEWAVESTRATEGY_H
#include "WaveformStrategy.h"

class SineWaveStrategy : public WaveformStrategy {
public:
    float generateSample(const float &phase, const float &scale) const override;
};

#endif //SINEWAVESTRATEGY_H
