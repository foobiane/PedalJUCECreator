#pragma once

#include <JuceHeader.h>

#include "EditorComponents/BasicEditorComponent.h"
#include "EditorComponents/Components.h"

class EditorPanel : public juce::Component {
    public:
        EditorPanel(float x, float y, float editorWidth, float editorHeight);
        ~EditorPanel();

        virtual void paint(juce::Graphics& g) override;
        virtual void resized() override;

        virtual void mouseUp(const juce::MouseEvent& e) override;

        void addComponentToEditor(const std::string& name);
        void removeComponentFromEditor(BasicEditorComponent* who);

        juce::Rectangle<float> getMinimumBoundingBoxForComponents();

        float getEditorWidth() { return editorWidth; }
        float getEditorHeight() { return editorHeight; }

        std::unordered_set<BasicEditorComponent*> editorComponents;

    private:
        float editorWidth;
        float editorHeight;

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

        BasicEditorComponent* previouslySelectedComponent = nullptr;
};