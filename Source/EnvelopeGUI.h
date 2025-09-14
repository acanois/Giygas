//
// Created by David Richter on 9/14/25.
//

#pragma once

#include "GiygasProcessor.h"

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

class EnvelopeGUI : public juce::Component,
                    public juce::Slider::Listener
{
public:
    EnvelopeGUI(GiygasProcessor& processor)
        : processorRef(processor)
    {
        sliderBounds.setBounds(0, 100, 100, 100);
        componentBounds.setBounds(0, 0, sliderBounds.getWidth() * 4, sliderBounds.getHeight());

        std::array<std::string, 4> paramNames = { "attack", "decay", "sustain", "release" };
        for (auto paramName: paramNames) {
            auto* control = new juce::Slider(
                juce::Slider::RotaryVerticalDrag,
                juce::Slider::TextBoxBelow
            );
            auto* attachment = new juce::AudioProcessorValueTreeState::SliderAttachment(
                processorRef.getValueTree(),
                paramName,
                *control
            );

            sliders.add(control);
            attachments.add(attachment);

            addAndMakeVisible(control);
        }
    }

    void resized() override
    {
        auto xPos = componentBounds.getX();

        for (const auto slider: sliders) {
            slider->setBounds(xPos, componentBounds.getY(), sliderBounds.getWidth(), sliderBounds.getHeight());
            xPos += (sliderBounds.getX() + sliderBounds.getWidth() + 10);
        }
    }

    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::black);
    }

    void sliderValueChanged(juce::Slider* slider) override
    {
    }

    int getComponentHeight()
    {
        return sliderBounds.getHeight();
    }

private:
    juce::OwnedArray<juce::Slider> sliders;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> attachments;
    juce::Rectangle<int> componentBounds;
    juce::Rectangle<int> sliderBounds;

    GiygasProcessor& processorRef;
};
