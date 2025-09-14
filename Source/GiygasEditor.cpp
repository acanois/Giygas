//
// Created by David Richter on 12/31/24.
//

#include "GiygasEditor.h"

GiygasEditor::GiygasEditor(GiygasProcessor& p)
    : AudioProcessorEditor(&p),
      processorRef(p),
      midiKeyboardComponent(
          midiKeyboardState,
          juce::MidiKeyboardComponent::horizontalKeyboard
      )
{
    juce::ignoreUnused(processorRef);

    addAndMakeVisible(midiKeyboardComponent);

    midiKeyboardState.addListener(&processorRef.getMidiMessageCollector());

    setSize(640, 360);
}

GiygasEditor::~GiygasEditor()
{
    midiKeyboardState.removeListener(&processorRef.getMidiMessageCollector());
}

void GiygasEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void GiygasEditor::resized()
{
    auto area = getLocalBounds();
    juce::Rectangle<int> componentBounds;
    componentBounds.setBounds(100, 100, 100, 100);
    midiKeyboardComponent.setBounds(area.removeFromBottom(80).reduced(8));
}
