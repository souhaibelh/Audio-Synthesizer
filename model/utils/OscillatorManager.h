//
// Created by judoj on 30/05/2025.
//

#ifndef OSCILLATORMANAGER_H
#define OSCILLATORMANAGER_H
#include <memory>

#include "../oscillators/Oscillator.h"
#include "../oscillators/SawWaveStrategy.h"
#include "../oscillators/SineWaveStrategy.h"
#include "../oscillators/SquareWaveStrategy.h"

class Oscillator;

class OscillatorManager {
private:
    std::unique_ptr<WaveformStrategy> sineStrategy = std::make_unique<SineWaveStrategy>();
    std::unique_ptr<WaveformStrategy> squareStrategy = std::make_unique<SquareWaveStrategy>();
    std::unique_ptr<WaveformStrategy> sawStrategy = std::make_unique<SawWaveForm>();

    std::unique_ptr<Oscillator> osc1;
    std::unique_ptr<Oscillator> osc2;

    WaveformStrategy* getStrategy(int integer);
public:
    OscillatorManager(std::unique_ptr<Oscillator> o1, std::unique_ptr<Oscillator> o2);
    void setStrategyOsc1(int strategy);
    void setStrategyOsc2(int strategy);
    Oscillator* getOsc1();
    Oscillator* getOsc2();
};

#endif //OSCILLATORMANAGER_H
