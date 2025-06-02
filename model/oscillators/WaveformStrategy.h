//
// Created by judoj on 02/06/2025.
//

#ifndef WAVEFORMSTRATEGY_H
#define WAVEFORMSTRATEGY_H

class  WaveformStrategy {
public:
    virtual ~WaveformStrategy() = default;
    virtual float generateSample(const float& phase, const float& scale) const = 0;
};

#endif //WAVEFORMSTRATEGY_H
