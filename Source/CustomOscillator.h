//
// Created by David Richter on 9/7/25.
//

#pragma once

#include <juce_dsp/juce_dsp.h>

class CustomOscillator
{
public:
    CustomOscillator()
    {
        auto& osc = processorChain.get<oscIndex>();
        osc.initialise([] (const float x) { return std::sin(x); }, 128);
    }

    void prepare(juce::dsp::ProcessSpec& spec)
    {
        processorChain.prepare(spec);
    }

    void reset() noexcept
    {
        processorChain.reset();
    }

    void setFrequency(const float frequency)
    {
        auto& osc = processorChain.get<oscIndex>();
        osc.setFrequency(frequency);
    }

    void setGain(const float newGain)
    {
        auto& gain = processorChain.get<gainIndex>();
        gain.setGainLinear(newGain);
    }

    template<typename ProcessContext>
    void process(const ProcessContext& context) noexcept
    {
        processorChain.process(context);
    }

private:
    // Processor chain and index enum
    enum
    {
        oscIndex,
        gainIndex
    };

    juce::dsp::ProcessorChain<
        juce::dsp::Oscillator<float>,
        juce::dsp::Gain<float>
    > processorChain;
};
