//
// Created by David Richter on 11/22/25.
//

#pragma once

#include <juce_events/juce_events.h> // Timer
#include <juce_audio_devices/juce_audio_devices.h> // Midi IO

class SimpleSequencer : public juce::Timer
{
public:
    explicit SimpleSequencer(juce::MidiInputCallback& targetSynth);

    ~SimpleSequencer() override;

    void startSequence();

    void stopSequence();

    void setBpm(double newBpm) { bpm = newBpm; }

private:
    void timerCallback() override;

    juce::MidiInputCallback& synth;

    const juce::Array<int> debugScale = { 60, 64, 67, 69, 67, 64, 60, 69 };
    const juce::Array<int> scaleDegrees = {
        0, 1, 3, 5, 7, 8, 10, 12, 13, 15, 17, 19, 20, 22, 24
    };

    double bpm { 93 };

    int midiChannel { 1 };
    int currentStep { 0 };
    int rootNote { 39 };
    int velocity { 100 };
};
