//
// Created by David Richter on 9/13/25.
//

#include "SynthVoice.h"


SynthVoice::SynthVoice()
    : oscillator(std::make_unique<CustomOscillator>()) {
}


void SynthVoice::startNote(int midiNoteNumber,
                           float velocity,
                           juce::SynthesiserSound* sound,
                           int currentPitchWheelPosition) {
}

void SynthVoice::stopNote(float velocity, bool allowTailOff) {
}


void SynthVoice::prepareVoice(juce::dsp::ProcessSpec& spec) {
    oscillator->prepare(spec);
}


void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer,
                                 int startSample,
                                 int numSamples) {
    oscillator->setFrequency(220.f);
    oscillator->setGain(0.75f);

    juce::AudioBuffer<float> tempBuffer(outputBuffer);
    tempBuffer.clear();

    juce::dsp::AudioBlock<float> block { tempBuffer };

    oscillator->process(juce::dsp::ProcessContextReplacing(block));

    for (auto channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
        outputBuffer.addFrom(channel, startSample, tempBuffer, channel, startSample, numSamples);
    }
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) {
}
