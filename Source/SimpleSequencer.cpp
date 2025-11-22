//
// Created by David Richter on 11/22/25.
//

#include "SimpleSequencer.h"

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
    // Get the current note value
    int noteNumber = sequenceData[currentStep];

    // Create the MIDI messages (Note Off for the previous step, Note On for the current)
    // Send Note Off for the previously played note (if it wasn't a rest '0')
    if (currentStep > 0 && sequenceData[currentStep - 1] != 0)
    {
        int prevNote = sequenceData[currentStep - 1];
        auto offMessage = juce::MidiMessage::noteOff(1, prevNote); // Channel 1, Note
        synth.handleIncomingMidiMessage(nullptr, offMessage);
    }

    // Send Note On for the new note (if it's not a rest '0')
    if (noteNumber != 0)
    {
        // Channel 1, Note, Velocity 100
        auto onMessage = juce::MidiMessage::noteOn(1, noteNumber, (juce::uint8) 100);
        synth.handleIncomingMidiMessage(nullptr, onMessage);
    }

    // --- 3. Advance the step counter
    currentStep = (currentStep + 1) % sequenceData.size();
}
