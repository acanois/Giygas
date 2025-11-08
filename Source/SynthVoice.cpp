//
// Created by David Richter on 9/13/25.
//

#include "SynthVoice.h"


SynthVoice::SynthVoice()
    : tempBlock(), oscillator(std::make_unique<CustomOscillator>())
{
    envelopeParameters.attack = 0.01f;
    envelopeParameters.decay = 0.1f;
    envelopeParameters.sustain = 0.5f;
    envelopeParameters.release = 0.5f;
}

void SynthVoice::startNote(int midiNoteNumber,
                           float velocity,
                           juce::SynthesiserSound* sound,
                           int currentPitchWheelPosition)
{
    oscillator->setGain(1.f / velocity);
    frequencyRamp.setCurrentAndTargetValue(
        juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)
    );
    envelope.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    envelope.noteOff();
    clearCurrentNote();
}


void SynthVoice::prepareVoice(juce::dsp::ProcessSpec& spec)
{
    tempBlock = juce::dsp::AudioBlock<float>(
        heapBlock,
        spec.numChannels,
        spec.maximumBlockSize
    );

    envelope.setParameters(envelopeParameters);
    envelope.setSampleRate(spec.sampleRate);

    frequencyRamp.reset(spec.sampleRate, 0.1);
    frequencyRamp.setCurrentAndTargetValue(440.0f);

    oscillator->prepare(spec);
}


void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer,
                                 int startSample,
                                 int numSamples)
{
    if (envelope.isActive())
    {
        auto output = tempBlock.getSubBlock(0, numSamples);
        output.clear();

        juce::dsp::ProcessContextReplacing<float> context(output);

        oscillator->setFrequency(frequencyRamp.getNextValue(), true);
        oscillator->process(context);
        juce::dsp::AudioBlock<float>(outputBuffer)
            .getSubBlock(startSample, numSamples)
            .clear()
            .add(tempBlock);

        // This will need a temp buffer
        envelope.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
    }
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}
