//
// Created by David Richter on 12/31/24.
//

#pragma once

#include "GiygasProcessor.h"
#include "EnvelopeGUI.h"

#include <juce_audio_utils/juce_audio_utils.h>


class GiygasEditor : public juce::AudioProcessorEditor,
                     public juce::Button::Listener
{
public:
    GiygasEditor(GiygasProcessor&);

    ~GiygasEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;

    void resized() override;

    //==============================================================================
    void buttonClicked(juce::Button* button) override;

private:
    GiygasProcessor& processorRef;

    juce::MidiKeyboardState midiKeyboardState;
    juce::MidiKeyboardComponent midiKeyboardComponent;

    std::unique_ptr<EnvelopeGUI> envelopeGUI { nullptr };

    juce::TextButton playButton { "Play" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GiygasEditor)
};
