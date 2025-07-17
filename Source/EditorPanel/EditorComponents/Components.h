#pragma once

#include <JuceHeader.h>

#include "BasicEditorComponent.h"

#include <string>
#include <vector>

/**
 * RectangleComponent:
 * 
 * A simple rectangle object, with additional controls for corner size.
 */
class RectangleComponent : public BasicEditorComponent {
    public:
        RectangleComponent(EditorPanel* editorPanel, float width, float height, juce::Colour hslaColour);

        virtual void paint(juce::Graphics& g) override;
        virtual void resized() override;

        void setCornerSize(float newCornerSize);

        virtual std::string generateConstructorCode() override;
        virtual std::string generatePaintCode() override;

    private:
        float cornerSize;
};

class TextComponent : public BasicEditorComponent, public SelectedComponentListener {
    public:
        TextComponent(EditorPanel* editorPanel, float width, float height, juce::Colour hslaColour);

        virtual void paint(juce::Graphics& g) override;
        virtual void resized() override;

        virtual void onSelectionChange() override;

        void setText(std::string newText);
        void setFont(juce::Font newFont);

        virtual std::string generateConstructorCode() override;
        virtual std::string generatePaintCode() override;

    private:
        std::vector<std::string> fontsToUse;
        void initializeFontsToUse();

        std::string text;
        juce::Font font;

        bool isSelected = false;
};

class CircleComponent : public BasicEditorComponent {

};

class SliderComponent : public BasicEditorComponent {

};