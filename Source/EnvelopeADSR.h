//
// Created by David Richter on 9/20/25.
//

#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class EnvelopeADSR
{
public:
    EnvelopeADSR()
    {

    }

    void reset()
    {

    }

    void noteOn()
    {

    }

    void noteOff()
    {

    }

private:
    juce::ADSR envelope;
    juce::ADSR::Parameters envelopeParameters;
};
