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

class TextComponent : public BasicEditorComponent {
    public:
        TextComponent(EditorPanel* editorPanel, float width, float height, juce::Colour hslaColour);

        virtual void paint(juce::Graphics& g) override;
        virtual void resized() override;

        void setFontSize(float newFontSize);
        void setFont(std::string newFontName);
        void setStyleFlags(int styleFlags);

        virtual std::string generateConstructorCode() override;
        virtual std::string generatePaintCode() override;

    private:
        juce::TextEditor textBox;

        float fontSize;
        std::string fontName;
        int styleFlags;
};

class CircleComponent : public BasicEditorComponent {

};

class SliderComponent : public BasicEditorComponent {

};