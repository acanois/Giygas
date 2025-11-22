//
// Created by David Richter on 11/22/25.
//

#pragma once

#include <juce_events/juce_events.h> // Timer
#include <juce_audio_devices/juce_audio_devices.h> // Midi IO

class SimpleSequencer : public juce::Timer {
public:
    SimpleSequencer(juce::MidiInputCallback& targetSynth);
    ~SimpleSequencer() override;

    void startSequence(double bpm);
    void stopSequence();

private:
    void timerCallback() override;

    juce::MidiInputCallback& synth;

    const juce::Array<int> sequenceData = { 60, 64, 67, 69, 67, 64, 60, 69 };
    int currentStep = 0;
};
