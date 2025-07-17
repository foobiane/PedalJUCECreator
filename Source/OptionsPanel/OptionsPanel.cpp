#include "OptionsPanel.h"

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
        g.setFont(juce::Font(juce::FontOptions("Arial", 20.0f, juce::Font::plain)));

        g.drawFittedText(currentlySelectedComponent->getEditorComponentName(), 10, 5, panelWidth - 20, 25, juce::Justification::Flags::centred, 1);

        g.setFont(juce::Font(juce::FontOptions("Arial", 12.0f, juce::Font::plain)));

        for (int i = 0; i < currentlySelectedComponent->controls.size(); i++) {
            std::string name = currentlySelectedComponent->controls[i].first;

            g.drawFittedText(name, 10, (25 * i) + 30 + 2, 75, 21, juce::Justification::Flags::left, 1);
        }
    }
}

void OptionsPanel::resized() {

}

void OptionsPanel::onSelectionChange() {
    if (previouslySelectedComponent != nullptr && previouslySelectedComponent != currentlySelectedComponent) {
        for (auto& kv : previouslySelectedComponent->controls)
            removeChildComponent(kv.second);
    }

    if (previouslySelectedComponent != currentlySelectedComponent) {
        previouslySelectedComponent = currentlySelectedComponent;

        if (currentlySelectedComponent != nullptr) {
            if (25 * currentlySelectedComponent->controls.size() + 30 + 2 > getBounds().getHeight())
                setBounds(getPosition().x, getPosition().y, panelWidth, 25 * currentlySelectedComponent->controls.size() + 30 + 2);

            for (int i = 0; i < currentlySelectedComponent->controls.size(); i++) {
                juce::Component* c = currentlySelectedComponent->controls[i].second;
                c->setBounds(85, (25 * i) + 30 + 2, panelWidth - 95, 21);
                addAndMakeVisible(c);
            }
        }
        else
            setBounds(getPosition().x, getPosition().y, panelWidth, panelHeight);
    }

    repaint(); // TODO: Determine if this is necessary in all control paths
}