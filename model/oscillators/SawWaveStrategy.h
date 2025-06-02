//
// Created by judoj on 02/06/2025.
//

#ifndef SAWWAVESTRATEGY_H
#define SAWWAVESTRATEGY_H
#include "WaveformStrategy.h"

class SawWaveForm : public WaveformStrategy {
public:
    float generateSample(const float &phase, const float &scale) const override;
};

#endif //SAWWAVESTRATEGY_H
