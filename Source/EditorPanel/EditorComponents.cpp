#include "EditorComponents.h"
#include "EditorPanel.h"

#include <cassert>
#include <cstdio>

// Externs
BasicEditorComponent* currentlySelectedComponent = nullptr;

std::vector<SelectedComponentListener*> selectedComponentListeners = {};
std::vector<EditorComponentListener*> editorComponentListeners = {};

///////////////////////////////////////////////////////////////////////////////////////////////////
// BasicEditorComponent                                                                          //
///////////////////////////////////////////////////////////////////////////////////////////////////

BasicEditorComponent::BasicEditorComponent(std::string editorComponentName, EditorPanel* editorPanel, double width, double height, juce::Colour hslaColour) :
    editorComponentName(editorComponentName),
    editorPanel(editorPanel),
    width(width),
    height(height),
    hue(hslaColour.getHue()),
    saturation(hslaColour.getSaturation()),
    lightness(hslaColour.getLightness()),
    alpha(hslaColour.getFloatAlpha()),
    trashIcon(this)
{
    addSlider("Width", width, 0, 1000, 1);
    addSlider("Height", height, 0, 1000, 1);

    addSlider("Hue", hue, 0.0f, 1.0f, 0.01f);
    addSlider("Saturation", saturation, 0.0f, 1.0f, 0.01f);
    addSlider("Lightness", lightness, 0.0f, 1.0f, 0.01f);
    addSlider("Alpha", alpha, 0.0f, 1.0f, 0.01f);

    setBounds(0, 0, width, height);
}

void BasicEditorComponent::sliderValueChanged(juce::Slider* s) {
    for (auto& kv : sliders) {
        if (kv.second == s) {
            if (kv.first == "Width") {
                width = s->getValue();
                adjustBounds();
            }

            else if (kv.first == "Height") {
                height = s->getValue();
                adjustBounds();
            }

            else if (kv.first == "Hue")
                setHue(s->getValue());

            else if (kv.first == "Saturation")
                setSaturation(s->getValue());

            else if (kv.first == "Lightness")
                setLightness(s->getValue());
            
            else if (kv.first == "Alpha")
                setAlpha(s->getValue());

            userDefinedSliderChecks(kv.first, s);

            break;
        }
    }
}

BasicEditorComponent::~BasicEditorComponent() {
    for (auto& kv : sliders)
        delete kv.second;
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

    trashIcon.setBounds(width - 25, 0, 25, 25);

    repaint();
}

void BasicEditorComponent::addSlider(std::string name, double initialValue, double min, double max, double interval, juce::Slider::SliderStyle style) {
    assert(initialValue >= min && initialValue <= max);
    
    sliders.push_back({name, new juce::Slider(name)});

    sliders[sliders.size() - 1].second->setSliderStyle(style);
    // sliders[name]->showTextBox();

    sliders[sliders.size() - 1].second->setRange(min, max, interval);
    sliders[sliders.size() - 1].second->setValue(initialValue);

    sliders[sliders.size() - 1].second->addListener(this);
}

void BasicEditorComponent::mouseDown(const juce::MouseEvent& e) {
    drag.startDraggingComponent(this, e);
}

void BasicEditorComponent::mouseDrag(const juce::MouseEvent& e) {
    drag.dragComponent(this, e, nullptr);
}

void BasicEditorComponent::mouseUp(const juce::MouseEvent& e) {
    if (
        currentlySelectedComponent != nullptr && 
        currentlySelectedComponent != this && 
        currentlySelectedComponent->isTrashVisible()
    )
        currentlySelectedComponent->toggleTrashVisibility(); // turn off trash icon for previous selection, if applicable

    else if (currentlySelectedComponent != this) {
        currentlySelectedComponent = this;
        currentlySelectedComponent->toggleTrashVisibility(); // turn on trash icon for new selection

        SelectedComponentListener::update();
    }

    EditorComponentListener::update();
}

bool BasicEditorComponent::isTrashVisible() {
    return showingTrashIcon;
}

void BasicEditorComponent::toggleTrashVisibility() {
    if (showingTrashIcon) {
        showingTrashIcon = false;
        removeChildComponent(&trashIcon);
    }
    else {
        showingTrashIcon = true;
        trashIcon.setBounds(width - 25, 0, 25, 25);
        addAndMakeVisible(&trashIcon);
    }
}

void BasicEditorComponent::setWidth(int newWidth) {
    width = newWidth;
    EditorComponentListener::update();
    adjustBounds();
}

void BasicEditorComponent::setHeight(int newHeight) {
    height = newHeight; 
    EditorComponentListener::update();
    adjustBounds();
}

void BasicEditorComponent::setHue(float newHue) { 
    hue = newHue; 
    EditorComponentListener::update();
    repaint(); 
}

void BasicEditorComponent::setSaturation(float newSaturation) { 
    saturation = newSaturation; 
    EditorComponentListener::update();
    repaint(); 
}

void BasicEditorComponent::setLightness(float newLightness) { 
    lightness = newLightness; 
    EditorComponentListener::update();
    repaint(); 
}

void BasicEditorComponent::setAlpha(float newAlpha) { 
    alpha = newAlpha; 
    EditorComponentListener::update();
    repaint(); 
}


void BasicEditorComponent::TrashIcon::mouseUp(const juce::MouseEvent& e) {
    currentlySelectedComponent = nullptr;
    SelectedComponentListener::update();

    editorComponent->editorPanel->editorComponents.erase(editorComponent);
    EditorComponentListener::update();

    editorComponent->editorPanel->removeComponentFromEditor(editorComponent);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// RectangleComponent                                                                            //
///////////////////////////////////////////////////////////////////////////////////////////////////

RectangleComponent::RectangleComponent(EditorPanel* editorPanel, double width, double height, juce::Colour hslaColour) :
    BasicEditorComponent("Rectangle", editorPanel, width, height, hslaColour)
{
    addSlider("Corner Size", cornerSize, 0, 100, 1);
}

void RectangleComponent::paint(juce::Graphics& g) {
    g.setColour(getColour());
    g.fillRoundedRectangle(getLocalBounds().toFloat(), cornerSize);
}

void RectangleComponent::resized() {
    // Nothing here.
}

void RectangleComponent::userDefinedSliderChecks(std::string name, juce::Slider* s) {
    if (name == "Corner Size")
        setCornerSize(s->getValue());
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
// SelectedComponentListener                                                                     //
///////////////////////////////////////////////////////////////////////////////////////////////////

SelectedComponentListener::SelectedComponentListener() {
    selectedComponentListeners.push_back(this);
}

void SelectedComponentListener::update() {
    for (SelectedComponentListener* listener : selectedComponentListeners)
        listener->onSelectionChange();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// EditorComponentListener                                                                       //
///////////////////////////////////////////////////////////////////////////////////////////////////

EditorComponentListener::EditorComponentListener() {
    editorComponentListeners.push_back(this);
}

void EditorComponentListener::update() {
    for (EditorComponentListener* listener : editorComponentListeners)
        listener->onEditorComponentChange();
}
