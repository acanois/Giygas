//
// Created by David Richter on 12/31/24.
//

#include "GiygasEditor.h"

GiygasEditor::GiygasEditor (GiygasProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    setSize (400, 300);
}

GiygasEditor::~GiygasEditor() = default;

void GiygasEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void GiygasEditor::resized()
{
}