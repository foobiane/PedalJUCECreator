#include "Components.h"
#include "../EditorPanel.h"

#include <cassert> // debug

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
    BasicEditorComponent("Text", editorPanel, width, height, hslaColour)
{
    initializeFontsToUse();
    setBounds(0, 0, width, height);

    addSlider("Font Size", 12, 0, 200, 1, [this](juce::Slider* s){setFont(font.withHeight(s->getValue()));});

    addDropdown("Font Name", "Arial", fontsToUse, [this](juce::ComboBox* c){
        juce::Font f(juce::FontOptions(c->getText(), font.getHeight(), font.getStyleFlags()));
        setFont(f);
    });

    addButtonString("Typeface", {
        {"Bold", true, [this](juce::Button* b){
            juce::Font f = font;
            f.setBold(b->isDown());
            setFont(f);
        }},
        {"Italic", true, [this](juce::Button* b){
            juce::Font f = font;
            f.setItalic(b->isDown());
            setFont(f);
        }},
        {"Underline", true, [this](juce::Button* b){
            juce::Font f = font;
            f.setUnderline(b->isDown());
            setFont(f);
        }}
    });

    addTextBox("Text", "Enter text here...", [this](juce::TextEditor* t){setText(t->getText().toStdString());});
}

void TextComponent::initializeFontsToUse() {
    juce::Array<juce::Font> fonts;
    juce::Font::findFonts(fonts);

    for (auto& font : fonts)
        fontsToUse.push_back(font.getTypefaceName().toStdString());
}

void TextComponent::paint(juce::Graphics& g) {
    g.setColour(getColour());
    g.setFont(font);
    g.drawFittedText(text, getLocalBounds(), juce::Justification::Flags::centred, -1);

    // If selected, draw a thin outline.
    if (isSelected) {
        g.setColour(juce::Colours::white);
        g.drawRect(getLocalBounds(), 1.0f);
    }
}

void TextComponent::resized() {
    // Nothing for now.
}

void TextComponent::onSelectionChange() {
    isSelected = (currentlySelectedComponent == this);
    repaint(); // TODO: this only needs to happen if isSelected changes
}

void TextComponent::setText(std::string newText) {
    text = newText;
    repaint();
}

void TextComponent::setFont(juce::Font newFont) {
    font = newFont;
    repaint();
}


std::string TextComponent::generateConstructorCode() {
    return "";
}

std::string TextComponent::generatePaintCode() {
    juce::Rectangle<float> trueBounds = editorPanel->getMinimumBoundingBoxForComponents();
    juce::Point<float> topLeftAdjusted = getBounds().getTopLeft().toFloat() - trueBounds.getTopLeft();

    std::string colourCode = ("\tg.setColour(juce::Colour(" + 
        std::to_string(hue) + "f, " +
        std::to_string(saturation) + "f, " +
        std::to_string(lightness) + "f, " +
        std::to_string(alpha) + "f));\n"
    );

    std::string textCode = ("\tg.drawFittedText(" +
        ("\"" + text + "\"") + 
        std::to_string(topLeftAdjusted.x) + "f, " +
        std::to_string(topLeftAdjusted.y) + "f, " +
        std::to_string(width) + "f, " +
        std::to_string(height) + "f, " +
        "juce::Justification::Flags::centred, " + 
        "-1);\n\n"
    );

    return colourCode + textCode;
}

/**
 * TODO:
 * 
 * 4. Make the font selections in the text box have the same font as the one they describe (might be too annoying to do)
 * 5. Make the options panel scrollable
 * 6. Fix typeface stuff
 */