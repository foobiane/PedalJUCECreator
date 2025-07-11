#include "EditorPanel.h"

#include <cstdio>

EditorPanel::EditorPanel(double x, double y, double editorWidth, double editorHeight) :
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

    setBounds(x, y, editorWidth, editorHeight);
}

EditorPanel::~EditorPanel() {
    for (auto* editorComponent : editorComponents)
        delete editorComponent;
}

void EditorPanel::paint(juce::Graphics& g) {
    // Nothing for now.
}

void EditorPanel::resized() {
    for (auto* editorComponent : editorComponents)
        editorComponent->resized();
}

void EditorPanel::mouseUp(const juce::MouseEvent& e) {
    if (currentlySelectedComponent != nullptr && currentlySelectedComponent->isTrashVisible()) {
        currentlySelectedComponent->toggleTrashVisibility(); // turn off trash icon if we clicked elsewhere in the editor
        currentlySelectedComponent = nullptr;

        // Updating listeners
        for (SelectedComponentListener* listener : listeners)
            listener->onSelectionChange();
    }
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