#include "../include/model/AudioGenerator.h"
#include "../include/ui/MainWindow.h"
#include "../include/model/utils/Parameters.h"
#include "../include/model/effects/DelayEffect.h"
#include "../include/model/effects/FilterEffect.h"

int main() {
    SynthParameters parameters;
    int sampleRate = 48000;
    double scale = 0.5;

    FilterEffect filter(sampleRate, parameters.filter.cutoff, parameters.filter.resonance);
    EnvelopeEffect envelope(
        parameters.envelope.attack,
        parameters.envelope.release,
        parameters.note.isOn,
        parameters.note.noteOffTime,
        parameters.note.noteOnTime,
        parameters.currentTime
    );
    MixEffect mixer;
    DelayEffect delay(sampleRate, parameters.delay.mix, parameters.delay.time);

    AudioEngine engine(mixer, envelope, filter, delay);

    auto osc1 = std::make_unique<Oscillator>(sampleRate, scale, parameters.note.frequency,
                                             parameters.osc1.frequencyOffset);
    auto osc2 = std::make_unique<Oscillator>(sampleRate, scale, parameters.note.frequency,
                                             parameters.osc2.frequencyOffset);
    OscillatorManager oscManager(std::move(osc1), std::move(osc2));

    MainWindow mainWindow(parameters);
    mainWindow.init();

    AudioGenerator generator(parameters, engine, oscManager);
    generator.init();

    mainWindow.run();
}