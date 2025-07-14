#include "OptionsPanel.h"

#include <cstdio> // debug

OptionsPanel::OptionsPanel(EditorPanel* editorPanel, float x, float y, float panelWidth, float panelHeight) :
    editorPanel(editorPanel),
    panelWidth(panelWidth),
    panelHeight(panelHeight)
{
    setBounds(x, y, panelWidth, panelHeight);
}

void OptionsPanel::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::black);

    if (currentlySelectedComponent != nullptr) {
        g.setColour(juce::Colours::white);
        g.setFont(juce::Font(juce::FontOptions("Arial", 36.0f, juce::Font::plain)));

        g.drawFittedText(currentlySelectedComponent->getEditorComponentName(), 10, 10, panelWidth - 20, 55, juce::Justification::Flags::centred, 1);

        g.setFont(juce::Font(juce::FontOptions("Arial", 12.0f, juce::Font::plain)));

        for (int i = 0; i < currentlySelectedComponent->sliders.size(); i++) {
            std::string name = currentlySelectedComponent->sliders[i].first;

            g.drawFittedText(name, 10, 25 * i + 75, 75, 25, juce::Justification::Flags::left, 1);
        }
    }
}

void OptionsPanel::resized() {

}

void OptionsPanel::onSelectionChange() {
    if (previouslySelectedComponent != nullptr && previouslySelectedComponent != currentlySelectedComponent) {
        for (auto& kv : previouslySelectedComponent->sliders) {
            juce::Slider* s = kv.second;
            removeChildComponent(s);
        }
    }

    if (previouslySelectedComponent != currentlySelectedComponent) {
        previouslySelectedComponent = currentlySelectedComponent;

        if (currentlySelectedComponent != nullptr) {
            for (int i = 0; i < currentlySelectedComponent->sliders.size(); i++) {
                juce::Slider* s = currentlySelectedComponent->sliders[i].second;
                s->setBounds(85, 25 * i + 75, panelWidth - 95, 25);
                addAndMakeVisible(s);
            }
        }
    }

    repaint(); // TODO: Determine if this is necessary in all control paths
}