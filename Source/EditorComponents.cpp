#include "EditorComponents.h"
#include "EditorPanel.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// BasicEditorComponent                                                                          //
///////////////////////////////////////////////////////////////////////////////////////////////////

BasicEditorComponent::BasicEditorComponent(EditorPanel* editorPanel, int width, int height, juce::Colour hslaColour) :
    editorPanel(editorPanel),
    width(width),
    height(height),
    hslaColour(hslaColour),
    trashIcon(this)
{
    setBounds(0, 0, width, height);
}

void BasicEditorComponent::paint(juce::Graphics& g) {
    // Nothing here.
}

void BasicEditorComponent::resized() {
    // Nothing here.
}

void BasicEditorComponent::adjustBounds() {
    juce::Point<int> pos = getPosition();
    setBounds(pos.x, pos.y, width, height);
    repaint();
}

void BasicEditorComponent::mouseDown(const juce::MouseEvent& e) {
    drag.startDraggingComponent(this, e);
}

void BasicEditorComponent::mouseDrag(const juce::MouseEvent& e) {
    drag.dragComponent(this, e, nullptr);
}

void BasicEditorComponent::mouseUp(const juce::MouseEvent& e) {
    if (!showingTrashIcon) {
        showingTrashIcon = true;
        trashIcon.setBounds(width - 25, 0, 25, 25);
        addAndMakeVisible(trashIcon);
    }
    else if (showingTrashIcon && !getBounds().contains(e.getScreenPosition())) {
        showingTrashIcon = false;
        removeChildComponent(&trashIcon);
    }
}

void BasicEditorComponent::setWidth(int newWidth) {
    width = newWidth;
    adjustBounds();
}

void BasicEditorComponent::setHeight(int newHeight) {
    height = newHeight; 
    adjustBounds();
}

void BasicEditorComponent::setColour(juce::Colour newColour) {
    hslaColour = newColour;
    repaint();
}


void BasicEditorComponent::TrashIcon::mouseUp(const juce::MouseEvent& e) {
    editorComponent->editorPanel->removeComponentFromEditor(editorComponent);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// RectangleComponent                                                                            //
///////////////////////////////////////////////////////////////////////////////////////////////////

RectangleComponent::RectangleComponent(EditorPanel* editorPanel, int width, int height, juce::Colour hslaColour) :
    BasicEditorComponent(editorPanel, width, height, hslaColour)
{
}

void RectangleComponent::paint(juce::Graphics& g) {
    g.setColour(hslaColour);
    g.fillRoundedRectangle(getLocalBounds().toFloat(), cornerSize);
}

void RectangleComponent::resized() {
    // Nothing here.
}

void RectangleComponent::setCornerSize(float newCornerSize) {
    cornerSize = newCornerSize;
    repaint();
}