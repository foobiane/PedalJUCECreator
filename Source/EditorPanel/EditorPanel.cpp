#include "EditorPanel.h"

#include <cstdio>
#include <limits>

EditorPanel::EditorPanel(float x, float y, float editorWidth, float editorHeight) :
    editorWidth(editorWidth),
    editorHeight(editorHeight)
{
    addComponent.setBounds((editorWidth - 135) / 2.0f, editorHeight - 35, 25, 25);
    componentSelect.setBounds((editorWidth - 135) / 2.0f + 35, editorHeight - 35, 100, 25);

    addComponent.onClick = [this](){
        addComponentToEditor(componentSelect.getText().toStdString());
    };

    componentSelect.addItemList(juce::StringArray({
        "Rectangle",
        "Text"
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

        SelectedComponentListener::update();
    }
}

void EditorPanel::onZOrderChange(BasicEditorComponent* changed) {
    removeChildComponent(changed);
    addAndMakeVisible(changed, changed->getZOrder());
}

void EditorPanel::addComponentToEditor(const std::string& name) {
    BasicEditorComponent* toAdd = nullptr;

    if (name == "Rectangle") 
        toAdd = new RectangleComponent(this, 100, 100, juce::Colour(0.5f, 0.5f, 0.5f, 1.0f));

    else if (name == "Text")
        toAdd = new TextComponent(this, 200, 50, juce::Colours::white);

    editorComponents.insert(toAdd);
    addAndMakeVisible(toAdd, toAdd->getZOrder());
}

void EditorPanel::removeComponentFromEditor(BasicEditorComponent* who) {
    removeChildComponent(who);
    editorComponents.erase(who);
    delete who;
}

/**
 * getMinimumBoundingBoxForComponents:
 * 
 * Returns the minimum-sized bounding box that contains all elements in the editor panel. 
 */
juce::Rectangle<float> EditorPanel::getMinimumBoundingBoxForComponents() {
    if (editorComponents.size() >= 1) {
        juce::Rectangle<float> result = (*editorComponents.begin())->getBounds().toFloat();

        for (auto itr = editorComponents.begin(); itr != editorComponents.end(); itr++)
            result = result.getUnion((*itr)->getBounds().toFloat());

        return result;
    }

    return getBounds().toFloat(); // no components -> return the bounds of the panel by default
}
