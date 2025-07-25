#include "MainComponent.h"

MainComponent::MainComponent() :
    editorPanel(0, 0, 0.67 * WINDOW_WIDTH, WINDOW_HEIGHT),
    optionsPanel(&editorPanel, 0, 0, 0.33 * WINDOW_WIDTH, 0.5 * WINDOW_HEIGHT), // bounds are relative to the viewport; see below
    codePanel(&editorPanel, 0.67 * WINDOW_WIDTH, 0.5 * WINDOW_HEIGHT, 0.33 * WINDOW_WIDTH, 0.5 * WINDOW_HEIGHT)
{
    addAndMakeVisible(editorPanel);
    addAndMakeVisible(codePanel);

    optionsPanelViewport.setViewedComponent(&optionsPanel, false);
    optionsPanelViewport.setScrollBarsShown(true, false);
    optionsPanelViewport.setBounds(0.67 * WINDOW_WIDTH, 0, 0.33 * WINDOW_WIDTH, 0.5 * WINDOW_HEIGHT); // true, global bounds
    addAndMakeVisible(optionsPanelViewport);

    setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

MainComponent::~MainComponent() {
    
}

void MainComponent::paint(juce::Graphics& g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized() {
    
}
