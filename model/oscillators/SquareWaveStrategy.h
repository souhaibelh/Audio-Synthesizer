//
// Created by judoj on 02/06/2025.
//

#ifndef SQUAREWAVESTRATEGY_H
#define SQUAREWAVESTRATEGY_H
#include "WaveformStrategy.h"

class SquareWaveStrategy : public WaveformStrategy {
public:
    float generateSample(const float &phase, const float &scale) const override;
};

#endif //SQUAREWAVESTRATEGY_H
