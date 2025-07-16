#include "Components.h"
#include "../EditorPanel.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// RectangleComponent                                                                            //
///////////////////////////////////////////////////////////////////////////////////////////////////

RectangleComponent::RectangleComponent(EditorPanel* editorPanel, float width, float height, juce::Colour hslaColour) :
    BasicEditorComponent("Rectangle", editorPanel, width, height, hslaColour)
{
    addSlider("Corner Size", cornerSize, 0, 100, 1, [this](juce::Slider* s){setCornerSize(s->getValue());});
}

void RectangleComponent::paint(juce::Graphics& g) {
    g.setColour(getColour());
    g.fillRoundedRectangle(getLocalBounds().toFloat(), cornerSize);
}

void RectangleComponent::resized() {
    // Nothing here.
}

void RectangleComponent::setCornerSize(float newCornerSize) {
    cornerSize = newCornerSize;
    EditorComponentListener::update();
    repaint();
}

std::string RectangleComponent::generateConstructorCode() {
    return "";
}

std::string RectangleComponent::generatePaintCode() {
    juce::Rectangle<float> trueBounds = editorPanel->getMinimumBoundingBoxForComponents();
    juce::Point<float> topLeftAdjusted = getBounds().getTopLeft().toFloat() - trueBounds.getTopLeft();

    std::string colourCode = ("\tg.setColour(juce::Colour(" + 
        std::to_string(hue) + "f, " +
        std::to_string(saturation) + "f, " +
        std::to_string(lightness) + "f, " +
        std::to_string(alpha) + "f));\n"
    );

    std::string rectCode = ("\tg.fillRoundedRectangle(" + 
        std::to_string(topLeftAdjusted.x) + "f, " +
        std::to_string(topLeftAdjusted.y) + "f, " +
        std::to_string(width) + "f, " +
        std::to_string(height) + "f, " +
        std::to_string(cornerSize) + "f);\n\n"
    );

    return colourCode + rectCode;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// TextComponent                                                                                 //
///////////////////////////////////////////////////////////////////////////////////////////////////

TextComponent::TextComponent(EditorPanel* editorPanel, float width, float height, juce::Colour hslaColour) :
    BasicEditorComponent("Text", editorPanel, width, height, hslaColour),
    fontSize(12.0f),
    fontName("Arial"),
    styleFlags(juce::Font::plain)
{
    textBox.setMultiLine(false);
    textBox.setReadOnly(false);

    textBox.setFont(juce::Font(juce::FontOptions(fontName, fontSize, styleFlags)));
    textBox.applyColourToAllText(getColour());

    textBox.setBounds(0, 0, width, height);

    addAndMakeVisible(textBox);

    addSlider("Font Size", fontSize, 0, 200, 1, [this](juce::Slider* s){setFontSize(s->getValue());});

    setBounds(0, 0, width, height);
}

void TextComponent::paint(juce::Graphics& g) {
    // Nothing.
}

void TextComponent::resized() {
    // Nothing.
}

void TextComponent::setFontSize(float newFontSize) {
    // TODO
}

void TextComponent::setFont(std::string newFontName) {
    // TODO
}

std::string TextComponent::generateConstructorCode() {
    return "";
}

std::string TextComponent::generatePaintCode() {
    return "";
}