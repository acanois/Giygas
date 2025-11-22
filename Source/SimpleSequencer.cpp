//
// Created by David Richter on 11/22/25.
//

#include "SimpleSequencer.h"

#include "juce_audio_plugin_client/juce_audio_plugin_client.h"

SimpleSequencer::SimpleSequencer(juce::MidiInputCallback& targetSynth)
    : synth(targetSynth)
{
}

SimpleSequencer::~SimpleSequencer()
{

}


void SimpleSequencer::startSequence(double bpm)
{
    double subdivisions = 4.0; // 16ths

    // interval(ms) = 60000 / (bpm * subdivisions)
    int intervalMs = (int) (60000.0 / (bpm * subdivisions));

    currentStep = 0;
    startTimer(intervalMs);
}

void SimpleSequencer::stopSequence()
{
    stopTimer();
    // Note off messages could be set here
}

void SimpleSequencer::timerCallback()
{
    int noteNumber = sequenceData[currentStep];

    auto currentTime = juce::Time::getMillisecondCounterHiRes() * 0.001;

    if (currentStep > 0 && sequenceData[currentStep - 1] != 0)
    {
        auto prevNote = sequenceData[currentStep - 1];
        auto offMessage = juce::MidiMessage::noteOff(1, prevNote);
        offMessage.setTimeStamp(currentTime);
        synth.handleIncomingMidiMessage(nullptr, offMessage);
    }

    if (noteNumber != 0)
    {
        // Channel 1, Note, Velocity 100
        auto onMessage = juce::MidiMessage::noteOn(1, noteNumber, (juce::uint8) 100);
        onMessage.setTimeStamp(currentTime);
        synth.handleIncomingMidiMessage(nullptr, onMessage);
    }

    currentStep = (currentStep + 1) % sequenceData.size();
}
