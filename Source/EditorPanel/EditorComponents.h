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
        BasicEditorComponent(std::string editorComponentName, EditorPanel* editorPanel, double width, double height, juce::Colour hslaColour);
        ~BasicEditorComponent();

        virtual void paint(juce::Graphics& g) override;
        virtual void resized() override;

        virtual void mouseDown(const juce::MouseEvent& e) final;
        virtual void mouseDrag(const juce::MouseEvent& e) final;
        virtual void mouseUp(const juce::MouseEvent& e) final;

        virtual void sliderValueChanged(juce::Slider* s) override;
        virtual void userDefinedSliderChecks(std::string name, juce::Slider* s) = 0;

        virtual std::string generateConstructorCode() = 0;
        virtual std::string generatePaintCode() = 0;

        bool isTrashVisible();
        void toggleTrashVisibility();

        float getWidth() { return width; }
        float getHeight() { return height; }
        juce::Colour getColour() { return juce::Colour(hue, saturation, lightness, alpha); }

        std::string getEditorComponentName() { return editorComponentName; }

        void setWidth(int newWidth);
        void setHeight(int newHeight);

        void setHue(float newHue);
        void setSaturation(float newSaturation);
        void setLightness(float newLightness);
        void setAlpha(float newAlpha);

        std::vector<std::pair<std::string, juce::Slider*>> sliders;

    protected:
        void adjustBounds();

        float width;
        float height;

        float hue;
        float saturation;
        float lightness;
        float alpha;

        virtual void addSlider(std::string name, double initialValue, double min, double max, double interval, juce::Slider::SliderStyle style = juce::Slider::SliderStyle::LinearHorizontal) final;

        EditorPanel* editorPanel;

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
        
        std::string editorComponentName;
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
        virtual void userDefinedSliderChecks(std::string name, juce::Slider* s) override;

        void setCornerSize(float newCornerSize);

        virtual std::string generateConstructorCode() override;
        virtual std::string generatePaintCode() override;

    private:
        float cornerSize;
};

/**
 * Contains the logic for the classes that listen for the currently selected component.
 */

extern BasicEditorComponent* currentlySelectedComponent;

class SelectedComponentListener {
    public:
        SelectedComponentListener();
        virtual ~SelectedComponentListener() = default;

        virtual void onSelectionChange() = 0;
        static void update();
};

extern std::vector<SelectedComponentListener*> selectedComponentListeners;

/**
 * Contains the logic for classes that listen for changes in any editor component.
 */

 class EditorComponentListener {
    public:
        EditorComponentListener();
        virtual ~EditorComponentListener() = default;

        virtual void onEditorComponentChange() = 0; 
        static void update();
 };

extern std::vector<EditorComponentListener*> editorComponentListeners;