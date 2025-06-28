#include "EditorPanel.h"

EditorPanel::EditorPanel(int editorWidth, int editorHeight) :
    editorWidth(editorWidth),
    editorHeight(editorHeight)
{
    addComponent.setBounds((editorWidth - 135) / 2.0f, editorHeight - 35, 25, 25);
    componentSelect.setBounds((editorWidth - 135) / 2.0f + 35, editorHeight - 35, 100, 25);

    addComponent.onClick = [this](){
        addComponentToEditor(componentSelect.getText().toStdString());
    };

    componentSelect.addItemList(juce::StringArray({
        "Rectangle"
    }), 1);
    componentSelect.setText("Rectangle");

    addAndMakeVisible(addComponent);
    addAndMakeVisible(componentSelect);

    setSize(editorWidth, editorHeight);
}

EditorPanel::~EditorPanel() {
    for (auto* editorComponent : editorComponents)
        delete editorComponent;
}

void EditorPanel::paint(juce::Graphics& g) {

}

void EditorPanel::resized() {
    for (auto* editorComponent : editorComponents)
        editorComponent->resized();
}

void EditorPanel::addComponentToEditor(const std::string& name) {
    if (name == "Rectangle") {
        BasicEditorComponent* rect = new RectangleComponent(this, 100, 100, juce::Colour(0.5f, 0.5f, 0.5f, 1.0f));
        editorComponents.insert(rect);

        addAndMakeVisible(rect);
    }
}

void EditorPanel::removeComponentFromEditor(BasicEditorComponent* who) {
    removeChildComponent(who);
    editorComponents.erase(who);
    delete who;
}