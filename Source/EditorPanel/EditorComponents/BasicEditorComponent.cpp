#include "BasicEditorComponent.h"
#include "../EditorPanel.h"

#include <algorithm>
#include <cassert>
#include <cstdio>

// Externs
BasicEditorComponent* currentlySelectedComponent = nullptr;

std::vector<SelectedComponentListener*> selectedComponentListeners = {};
std::vector<EditorComponentListener*> editorComponentListeners = {};

///////////////////////////////////////////////////////////////////////////////////////////////////
// BasicEditorComponent                                                                          //
///////////////////////////////////////////////////////////////////////////////////////////////////

BasicEditorComponent::BasicEditorComponent(std::string editorComponentName, EditorPanel* editorPanel, float width, float height, juce::Colour hslaColour) :
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
    addSlider("Width", width, 0, 1000, 1, [this](juce::Slider* s){setWidth(s->getValue());});
    addSlider("Height", height, 0, 1000, 1, [this](juce::Slider* s){setHeight(s->getValue());});

    addSlider("Hue", hue, 0.0f, 1.0f, 0.01f, [this](juce::Slider* s){setHue(s->getValue());});
    addSlider("Saturation", saturation, 0.0f, 1.0f, 0.01f, [this](juce::Slider* s){setSaturation(s->getValue());});
    addSlider("Lightness", lightness, 0.0f, 1.0f, 0.01f, [this](juce::Slider* s){setLightness(s->getValue());});
    addSlider("Alpha", alpha, 0.0f, 1.0f, 0.01f, [this](juce::Slider* s){setAlpha(s->getValue());});

    setBounds(0, 0, width, height);
}

BasicEditorComponent::~BasicEditorComponent() {
    for (auto& kv : controls)
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

void BasicEditorComponent::addSlider(std::string name, float initialValue, float min, float max, float interval, std::function<void(juce::Slider* s)> valueChangeCallback, juce::Slider::SliderStyle style) {
    assert(initialValue >= min && initialValue <= max);
    
    controls.push_back({name, new juce::Slider(name)});
    juce::Slider* s = (juce::Slider*) controls[controls.size() - 1].second;

    s->setSliderStyle(style);
    s->setRange(min, max, interval);
    s->setValue(initialValue);

    s->onValueChange = [s, valueChangeCallback](){valueChangeCallback(s);};
}

void BasicEditorComponent::addDropdown(std::string name, std::string initialValue, std::vector<std::string> options, std::function<void(juce::ComboBox* c)> valueChangeCallback) {
    assert(std::find(options.begin(), options.end(), initialValue) != options.end());

    controls.push_back({name, new juce::ComboBox(name)});
    juce::ComboBox* c = (juce::ComboBox*) controls[controls.size() - 1].second;

    for (int i = 0; i < options.size(); i++)
        c->addItem(options[i], i+1);

    c->setText(initialValue);
    c->onChange = [c, valueChangeCallback](){valueChangeCallback(c);};
}

void BasicEditorComponent::addButton(std::string name, bool isToggle, std::function<void(juce::Button*)> valueChangeCallback) {
    controls.push_back({name, new juce::TextButton(name)});
    juce::Button* b = (juce::Button*) controls[controls.size() - 1].second;

    b->setToggleable(isToggle);
    b->onClick = [b, valueChangeCallback](){valueChangeCallback(b);};
}

void BasicEditorComponent::addButtonString(std::string buttonStringName, std::vector<std::tuple<std::string, bool, std::function<void(juce::Button*)>>> namesAndToggle) {
    std::vector<juce::TextButton*> buttons;

    for (auto& info : namesAndToggle) {
        buttons.push_back(new juce::TextButton(std::get<0>(info)));

        juce::Button* b = (juce::Button*) buttons[buttons.size() - 1];
        b->setToggleable(std::get<1>(info));

        auto valueChangeCallback = std::get<2>(info);
        b->onClick = [b, valueChangeCallback](){valueChangeCallback(b);};
    }

    controls.push_back({buttonStringName, new TextButtonString(buttons)});
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
