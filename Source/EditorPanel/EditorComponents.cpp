#include "EditorComponents.h"
#include "EditorPanel.h"

// Externs
std::vector<SelectedComponentListener*> listeners;
BasicEditorComponent* currentlySelectedComponent = nullptr;

///////////////////////////////////////////////////////////////////////////////////////////////////
// BasicEditorComponent                                                                          //
///////////////////////////////////////////////////////////////////////////////////////////////////

BasicEditorComponent::BasicEditorComponent(EditorPanel* editorPanel, double width, double height, juce::Colour hslaColour) :
    editorPanel(editorPanel),
    width(width),
    height(height),
    hue(hslaColour.getHue()),
    saturation(hslaColour.getSaturation()),
    lightness(hslaColour.getLightness()),
    alpha(hslaColour.getAlpha()),
    trashIcon(this)
{
    addSlider("Width", width, 0, 1000, 1);
    addSlider("Height", height, 0, 1000, 1);

    addSlider("Hue", hue, 0, 1, 0.01);
    addSlider("Saturation", saturation, 0, 1, 0.01);
    addSlider("Lightness", lightness, 0, 1, 0.01);
    addSlider("Alpha", alpha, 0, 1, 0.01);

    setBounds(0, 0, width, height);
}

void BasicEditorComponent::sliderValueChanged(juce::Slider* s) {
    for (auto& kv : sliders) {
        if (kv.second == s) {
            if (kv.first == "Width") {
                width = s->getValue();

                juce::Point<float> pos = getPosition().toFloat();
                setBounds(pos.x, pos.y, width, height);
                repaint();
            }
            else if (kv.first == "Height") {
                height = s->getValue();

                juce::Point<float> pos = getPosition().toFloat();
                setBounds(pos.x, pos.y, width, height);
                repaint();
            }
            // TODO: Do the same for HSLA
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
    repaint();
}

void BasicEditorComponent::addSlider(std::string name, double initialValue, double min, double max, double interval) {
    static_assert(initial_value >= min && initialValue <= max);
    
    sliders.insert({name, new juce::Slider(name)});

    sliders[name].second->setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    sliders[name].second->showTextBox();

    sliders[name].second->setRange(min, max, interval);
    sliders[name].second->setValue(initialValue);

    sliders[name].second->addListener(this);
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

    currentlySelectedComponent = this;
    currentlySelectedComponent->toggleTrashVisibility(); // turn on trash icon for new selection

    for (auto* listener : listeners)
        listener->onSelectionChange();
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
    adjustBounds();
}

void BasicEditorComponent::setHeight(int newHeight) {
    height = newHeight; 
    adjustBounds();
}

void BasicEditorComponent::setColour(juce::Colour newColour) {
    hue = newColour.getHue();
    saturation = newColour.getSaturation();
    lightness = newColour.getLightness();
    alpha = newColour.getAlpha();

    repaint();
}


void BasicEditorComponent::TrashIcon::mouseUp(const juce::MouseEvent& e) {
    editorComponent->editorPanel->removeComponentFromEditor(editorComponent);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// RectangleComponent                                                                            //
///////////////////////////////////////////////////////////////////////////////////////////////////

RectangleComponent::RectangleComponent(EditorPanel* editorPanel, double width, double height, juce::Colour hslaColour) :
    BasicEditorComponent(editorPanel, width, height, hslaColour)
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

///////////////////////////////////////////////////////////////////////////////////////////////////
// SelectedComponentListener                                                                     //
///////////////////////////////////////////////////////////////////////////////////////////////////

SelectedComponentListener::SelectedComponentListener() {
    listeners.push_back(this);
}

void SelectedComponentListener::onSelectionChange() {
    // Nothing.
}