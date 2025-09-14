//
// Created by David Richter on 12/31/24.
//

#pragma once

#include "GiygasProcessor.h"
#include "juce_audio_utils/juce_audio_utils.h"


class GiygasEditor : public juce::AudioProcessorEditor
{
public:
    explicit GiygasEditor(GiygasProcessor&);

    ~GiygasEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;

    void resized() override;

private:
    GiygasProcessor& processorRef;

    juce::MidiKeyboardState midiKeyboardState;
    juce::MidiKeyboardComponent midiKeyboardComponent;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GiygasEditor)
};
