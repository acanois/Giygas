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

    auto block = tempBlock.getSubBlock(0, numSamples);

    juce::dsp::ProcessContextReplacing<float> context(block);

    oscillator->process(context);
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) {
}
