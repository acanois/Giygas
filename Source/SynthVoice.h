//
// Created by David Richter on 9/13/25.
//

#pragma once

#include "SynthSound.h"
#include "CustomOscillator.h"

#include "juce_audio_basics/juce_audio_basics.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    SynthVoice();

    bool canPlaySound(juce::SynthesiserSound* sound) override
    {
        return dynamic_cast<SynthSound *>(sound) != nullptr;
    }

    void startNote(int midiNoteNumber,
                   float velocity,
                   juce::SynthesiserSound* sound,
                   int currentPitchWheelPosition) override;

    void stopNote(float velocity, bool allowTailOff) override;

    void prepareVoice(juce::dsp::ProcessSpec& spec);

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer,
                         int startSample,
                         int numSamples) override;

    void pitchWheelMoved(int newPitchWheelValue) override;

    void controllerMoved(int controllerNumber, int newControllerValue) override;

private:
    juce::HeapBlock<char> heapBlock;
    juce::dsp::AudioBlock<float> tempBlock;

    juce::ADSR envelope;
    juce::ADSR::Parameters envelopeParameters;

    std::unique_ptr<CustomOscillator> oscillator { nullptr };

    juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> frequencyRamp;
};
