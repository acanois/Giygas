//
// Created by David Richter on 9/13/25.
//

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>


class SynthSound : public juce::SynthesiserSound {
public:
    bool appliesToNote(int midiNoteNumber) override {
        return true;
    }

    bool appliesToChannel(int midiNoteNumber) override {
        return true;
    }
};
