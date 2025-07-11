#pragma once

#include <JuceHeader.h>

#include <string>
#include <vector>

// Forward declarations
class EditorPanel;

/**
 * BasicEditorComponent:
 * 
 * This class encapsulates the shared behaviors of all components added to the editor.
 */

class BasicEditorComponent : public juce::Component, public juce::Slider::Listener {
    public:
        BasicEditorComponent(EditorPanel* mainComponent, double width, double height, juce::Colour hslaColour);
        ~BasicEditorComponent();

        virtual void paint(juce::Graphics& g) override;
        virtual void resized() override;

        virtual void mouseDown(const juce::MouseEvent& e) final;
        virtual void mouseDrag(const juce::MouseEvent& e) final;
        virtual void mouseUp(const juce::MouseEvent& e) final;

        virtual void sliderValueChanged(juce::Slider* s) override;
        virtual void userDefinedSliderChecks(juce::Slider* s) {  }

        bool isTrashVisible();
        void toggleTrashVisibility();

        int getWidth() { return width; }
        int getHeight() { return height; }
        juce::Colour getColour() { return juce::Colour(hue, saturation, lightness, alpha); }

        void setWidth(int newWidth);
        void setHeight(int newHeight);

        void setHue(float newHue) { hue = newHue; repaint(); }
        void setSaturation(float newSaturation) { saturation = newSaturation; repaint(); }
        void setLightness(float newLightness) { lightness = newLightness; repaint(); }
        void setAlpha(float newAlpha) { alpha = newAlpha; repaint(); }

        std::vector<std::pair<std::string, juce::Slider*>> sliders;

    protected:
        void adjustBounds();

        float width;
        float height;

        float hue;
        float saturation;
        float lightness;
        float alpha;

        virtual void addSlider(std::string name, double initialValue, double min, double max, double interval) final;

    private:
        juce::ComponentDragger drag;

        class TrashIcon : public juce::Component {
            public:
                TrashIcon(BasicEditorComponent* editorComponent) : 
                    editorComponent(editorComponent),
                    icon(juce::ImageFileFormat::loadFrom(BinaryData::trashsolid_png, BinaryData::trashsolid_pngSize))
                {
                }

                void paint(juce::Graphics& g) override {
                    float width = getLocalBounds().getWidth();
                    float height = getLocalBounds().getHeight();
                    g.drawImageWithin(icon, 0, 0, width, height, juce::RectanglePlacement::stretchToFit);
                }

                // Defining in EditorComponents.cpp since we need the contents of EditorPanel
                virtual void mouseUp(const juce::MouseEvent& e) override;

            private:
                BasicEditorComponent* editorComponent;
                juce::Image icon;
        };

        bool showingTrashIcon = false;
        TrashIcon trashIcon;

        EditorPanel* editorPanel;
};

/**
 * RectangleComponent:
 * 
 * A simple rectangle object, with additional controls for corner size.
 */
class RectangleComponent : public BasicEditorComponent {
    public:
        RectangleComponent(EditorPanel* editorPanel, double width, double height, juce::Colour hslaColour);

        virtual void paint(juce::Graphics& g) override;
        virtual void resized() override;
        virtual void userDefinedSliderChecks(juce::Slider* s) override {}

    private:
        double cornerSize;
};

/**
 * Logic for the currently selected component.
 */

extern BasicEditorComponent* currentlySelectedComponent;

class SelectedComponentListener {
    public:
        SelectedComponentListener();
        virtual void onSelectionChange();
};

extern std::vector<SelectedComponentListener*> listeners;