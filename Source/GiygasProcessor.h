//
// Created by David Richter on 12/31/24.
//

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>

#include "SimpleSequencer.h"
#include "SynthVoice.h"


#if (MSVC)
#include "ipps.h"
#endif

class GiygasProcessor : public juce::AudioProcessor,
                        public juce::AudioProcessorValueTreeState::Listener,
                        public juce::MidiInputCallback
{
public:
    GiygasProcessor();

    ~GiygasProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;

    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor *createEditor() override;

    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;

    bool producesMidi() const override;

    bool isMidiEffect() const override;

    double getTailLengthSeconds() const override;

    int getNumPrograms() override;

    int getCurrentProgram() override;

    void setCurrentProgram(int index) override;

    const juce::String getProgramName(int index) override;

    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;

    void setStateInformation(const void* data, int sizeInBytes) override;

    // Value Tree State Listener =========================================
    void parameterChanged(const juce::String& parameterID, float newValue) override;

    //====================================================================
    juce::MidiMessageCollector& getMidiMessageCollector() { return midiMessageCollector; }

    juce::AudioProcessorValueTreeState& getValueTree() { return valueTreeState; }

private:
    void handleIncomingMidiMessage(juce::MidiInput* source,
                                   const juce::MidiMessage& message) override;

    juce::MidiMessageCollector midiMessageCollector;

    juce::dsp::ProcessSpec processSpec;

    // Synth stuff
    juce::Synthesiser synthesiser;
    SynthSound* synthSound;
    SynthVoice* synthVoice;
    std::unique_ptr<SimpleSequencer> sequencer { nullptr };

    juce::AudioProcessorValueTreeState valueTreeState;

    juce::Atomic<float> gain { 0.f };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GiygasProcessor)
};
