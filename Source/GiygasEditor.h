//
// Created by David Richter on 12/31/24.
//

#pragma once

#include "GiygasProcessor.h"



class GiygasEditor : public juce::AudioProcessorEditor
{
public:
    explicit GiygasEditor (GiygasProcessor&);
    ~GiygasEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GiygasProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GiygasEditor)
};
