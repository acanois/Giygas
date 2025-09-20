//
// Created by David Richter on 9/13/25.
//

#include "SynthVoice.h"


SynthVoice::SynthVoice()
    : oscillator(std::make_unique<CustomOscillator>())
{
}


void SynthVoice::startNote(const int midiNoteNumber,
                           const float velocity,
                           juce::SynthesiserSound* sound,
                           int currentPitchWheelPosition)
{
    oscillator->setGain(1.f / velocity);
    oscillator->setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    clearCurrentNote();
}


void SynthVoice::prepareVoice(juce::dsp::ProcessSpec& spec)
{
    tempBlock = juce::dsp::AudioBlock<float>(heapBlock, spec.numChannels, spec.maximumBlockSize);
    oscillator->prepare(spec);
}


void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer,
                                 int startSample,
                                 int numSamples)
{
    if (isVoiceActive())
    {
        auto output = tempBlock.getSubBlock(0, numSamples);
        output.clear();

        juce::dsp::ProcessContextReplacing<float> context(output);
        oscillator->process(context);
        juce::dsp::AudioBlock<float>(outputBuffer)
            .getSubBlock(startSample, numSamples)
            .add(tempBlock);
    }
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}
