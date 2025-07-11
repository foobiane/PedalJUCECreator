#include "OptionsPanel.h"

#include <cstdio> // debug

OptionsPanel::OptionsPanel(EditorPanel* editorPanel, double x, double y, double panelWidth, double panelHeight) :
    editorPanel(editorPanel),
    panelWidth(panelWidth),
    panelHeight(panelHeight)
{
    setBounds(x, y, panelWidth, panelHeight);
}

void OptionsPanel::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::black);
}

void OptionsPanel::resized() {

}

void OptionsPanel::onSelectionChange() {
    if (previouslySelectedComponent != nullptr && previouslySelectedComponent != currentlySelectedComponent) {
        for (auto& kv : previouslySelectedComponent->sliders) {
            juce::Slider* s = kv.second;
            removeChildComponent(s);
            printf("Removing slider\n"); // debug
        }
    }

    if (previouslySelectedComponent != currentlySelectedComponent) {
        previouslySelectedComponent = currentlySelectedComponent;

        if (currentlySelectedComponent != nullptr) {
            int i = 0;
            for (auto& kv : currentlySelectedComponent->sliders) {
                juce::Slider* s = kv.second;
                
                s->setBounds(10, 25 * (i + 1), panelWidth - 20, 25);
                addAndMakeVisible(s);
                printf("Adding slider\n"); // debug

                i++;
            }
        }
    }

    // repaint(); // TODO: Determine if this is necessary in all control paths
}