//
// Created by judoj on 30/05/2025.
//
#include "../../include/model/utils/OscillatorManager.h"

OscillatorManager::OscillatorManager(std::unique_ptr<Oscillator> o1, std::unique_ptr<Oscillator> o2)
    : osc1(std::move(o1)), osc2(std::move(o2)) {}

Oscillator* OscillatorManager::getOsc1() {
    return this->osc1.get();
}

Oscillator* OscillatorManager::getOsc2() {
    return this->osc2.get();
}

WaveformStrategy *OscillatorManager::getStrategy(int integer) {
    switch (integer) {
        case 0: {
            return this->sineStrategy.get();
        }
        case 1: {
            return this->squareStrategy.get();
        }
        case 2: {
            return this->sawStrategy.get();
        }
        default: {
            return this->sineStrategy.get();
        };
    }
}

void OscillatorManager::setStrategyOsc1(int strategy) {
    this->osc1->setStrategy(getStrategy(strategy));
}

void OscillatorManager::setStrategyOsc2(int strategy) {
    this->osc2->setStrategy(getStrategy(strategy));
}