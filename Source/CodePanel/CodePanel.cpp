#include "CodePanel.h"

CodePanel::CodePanel(EditorPanel* editorPanel, float x, float y, float panelWidth, float panelHeight) :
    editorPanel(editorPanel),
    panelWidth(panelWidth),
    panelHeight(panelHeight)
{
    codeBox.setMultiLine(true);
    codeBox.setReadOnly(true);
    codeBox.setScrollbarsShown(true);

    codeBox.setFont(juce::Font(juce::FontOptions("Courier", 12.0f, juce::Font::plain)));
    codeBox.applyColourToAllText(juce::Colours::white);

    codeBox.setBounds(10, 10, panelWidth - 20, panelHeight - 20);

    addAndMakeVisible(codeBox);

    setBounds(x, y, panelWidth, panelHeight);
}

std::string CodePanel::generateCodeForAllEditorComponents() {
    std::string constructorCode = "";
    std::string paintCode = "";

    for (BasicEditorComponent* editorComponent : editorPanel->editorComponents) {
        constructorCode += editorComponent->generateConstructorCode();
        paintCode += editorComponent->generatePaintCode();
    }

    constructorCode = "MyPedalClass::MyPedalClass() {\n" + constructorCode + "}\n";
    paintCode = "void MyPedalClass::paint(juce::Graphics& g) {\n" + paintCode + "}\n";

    return constructorCode + "\n" + paintCode;
}

void CodePanel::onEditorComponentChange() {
    codeBox.setText(generateCodeForAllEditorComponents()); // trigger code regeneration
}

void CodePanel::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::white);
}

void CodePanel::resized() {

}