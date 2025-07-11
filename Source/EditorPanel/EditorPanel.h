#pragma once

#include <JuceHeader.h>

#include "EditorComponents.h"

class EditorPanel : public juce::Component {
    public:
        EditorPanel(double x, double y, double editorWidth, double editorHeight);
        ~EditorPanel();

        virtual void paint(juce::Graphics& g) override;
        virtual void resized() override;

        virtual void mouseUp(const juce::MouseEvent& e) override;

        void addComponentToEditor(const std::string& name);
        void removeComponentFromEditor(BasicEditorComponent* who);

    private:
        double editorWidth;
        double editorHeight;

        juce::ComboBox componentSelect;

        class AddComponentButton : public juce::TextButton {
            public:
                void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {
                    g.setColour(juce::Colours::lightblue);
                    g.fillEllipse(getLocalBounds().toFloat());

                    g.setColour(juce::Colours::white);
                    g.setFont(juce::Font(juce::FontOptions("Arial", getLocalBounds().getHeight(), 0)));
                    g.drawFittedText("+", getLocalBounds(), juce::Justification::centred, 1);
                }
        };

        AddComponentButton addComponent;

        std::unordered_set<BasicEditorComponent*> editorComponents;
};