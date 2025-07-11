#include "MainComponent.h"

MainComponent::MainComponent() :
    editorPanel(0, 0, 0.67 * WINDOW_WIDTH, WINDOW_HEIGHT),
    optionsPanel(&editorPanel, 0.67 * WINDOW_WIDTH, 0, 0.33 * WINDOW_WIDTH, WINDOW_HEIGHT)
{
    addAndMakeVisible(editorPanel);
    addAndMakeVisible(optionsPanel);

    setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

MainComponent::~MainComponent() {
    
}

void MainComponent::paint(juce::Graphics& g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized() {
    
}
