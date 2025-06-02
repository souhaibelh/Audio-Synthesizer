#include "../include/model/AudioGenerator.h"
#include "../include/ui/MainWindow.h"
#include "../include/model/utils/Parameters.h"
#include "../include/model/effects/DelayEffect.h"
#include "../include/model/effects/FilterEffect.h"
#define SAMPLE_RATE (44100)
#define SCALE (0.5)

int main() {
    SynthParameters parameters;

    std::shared_lock noteLock(parameters.noteMutex);
    std::shared_lock lock(parameters.mutex);

    FilterEffect filter(SAMPLE_RATE, parameters.filter.cutoff, parameters.filter.resonance);
    EnvelopeEffect envelope(
        parameters.envelope.attack,
        parameters.envelope.release,
        parameters.note.isOn,
        parameters.note.noteOffTime,
        parameters.note.noteOnTime,
        parameters.currentTime
    );
    MixEffect mixer;
    DelayEffect delay(SAMPLE_RATE, parameters.delay.mix, parameters.delay.time);

    AudioEngine engine(mixer, envelope, filter, delay);

    auto osc1 = std::make_unique<Oscillator>(SAMPLE_RATE, SCALE, parameters.note.frequency,
                                             parameters.osc1.frequencyOffset);
    auto osc2 = std::make_unique<Oscillator>(SAMPLE_RATE, SCALE, parameters.note.frequency,
                                             parameters.osc2.frequencyOffset);
    OscillatorManager oscManager(std::move(osc1), std::move(osc2));

    MainWindow mainWindow(parameters);
    mainWindow.init();

    AudioGenerator generator(parameters, engine, oscManager);
    generator.init();

    mainWindow.run();
}