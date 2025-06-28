#include "MainComponent.h"

MainComponent::MainComponent() :
    editorPanel(WINDOW_WIDTH, WINDOW_HEIGHT)
{
    addAndMakeVisible(editorPanel);

    setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

MainComponent::~MainComponent() {
    
}

void MainComponent::paint (juce::Graphics& g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized() {
    
}
