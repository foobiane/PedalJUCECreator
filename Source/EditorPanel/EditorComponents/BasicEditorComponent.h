#pragma once

#include <JuceHeader.h>

#include <string>
#include <vector>

// Forward declaration
class EditorPanel;

// I'm genuinely SICK of having to type this out.
template <typename T>
using ComponentCallback = std::function<void(T*)>;

/**
 * BasicEditorComponent:
 * 
 * This class encapsulates the shared behaviors of all components added to the editor.
 */
class BasicEditorComponent : public juce::Component
{
    public:
        BasicEditorComponent(std::string editorComponentName, EditorPanel* editorPanel, float width, float height, juce::Colour hslaColour);
        ~BasicEditorComponent();

        // Component logic
        virtual void paint(juce::Graphics& g) override;
        virtual void resized() override;

        virtual void mouseDown(const juce::MouseEvent& e) final;
        virtual void mouseDrag(const juce::MouseEvent& e) final;
        virtual void mouseUp(const juce::MouseEvent& e) final;

        // Code generation
        virtual std::string generateConstructorCode() = 0;
        virtual std::string generatePaintCode() = 0;

        // Trash logic
        bool isTrashVisible();
        void toggleTrashVisibility();

        // Getters
        float getWidth() { return width; }
        float getHeight() { return height; }
        juce::Colour getColour() { return juce::Colour(hue, saturation, lightness, alpha); }
        std::string getEditorComponentName() { return editorComponentName; }
        int getZOrder() { return zOrder; }

        // Setters
        // Since changes to these parameters should cause a visual change, we need to add logic
        // for repaints, etc.
        void setWidth(int newWidth);
        void setHeight(int newHeight);
        void setHue(float newHue);
        void setSaturation(float newSaturation);
        void setLightness(float newLightness);
        void setAlpha(float newAlpha);
        void setZOrder(int newZOrder);

        std::vector<std::pair<std::string, juce::Component*>> controls;

    protected:
        void adjustBounds();

        float width;
        float height;

        float hue;
        float saturation;
        float lightness;
        float alpha;

        int zOrder = -1;

        virtual void addSlider(std::string name, float initialValue, float min, float max, float interval, ComponentCallback<juce::Slider> valueChangeCallback, juce::Slider::SliderStyle style = juce::Slider::SliderStyle::LinearHorizontal) final;
        virtual void addDropdown(std::string name, std::string initialValue, std::vector<std::string> options, ComponentCallback<juce::ComboBox> valueChangeCallback) final;
        virtual void addButton(std::string name, bool isToggle, ComponentCallback<juce::Button> valueChangeCallback) final;
        virtual void addButtonString(std::string buttonStringName, std::vector<std::tuple<std::string, bool, ComponentCallback<juce::Button>>> info) final;
        virtual void addTextBox(std::string name, std::string initialText, ComponentCallback<juce::TextEditor> valueChangeCallback);

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

// Custom wrapper for a string of buttons in the options panel
class TextButtonString : public juce::Component {
    public:
        TextButtonString(std::vector<juce::TextButton*> buttons) :
            buttons(buttons)
        {
        }

        virtual ~TextButtonString() {
            for (auto* button : buttons)
                delete button;
        }

        virtual void resized() override {
            juce::Rectangle<int> bounds = getBounds();

            int buttonWidth = (bounds.getWidth() / buttons.size()) * 0.9f;
            int horizontalPad = ((bounds.getWidth() / buttons.size()) - buttonWidth) / 2;

            int buttonHeight = bounds.getHeight() * 0.9f;
            int verticalPad = (bounds.getHeight() - buttonHeight) / 2;

            for (int i = 0; i < buttons.size(); i++) {
                buttons[i]->setBounds(horizontalPad + (i * (buttonWidth + 2 * horizontalPad)), verticalPad, buttonWidth, buttonHeight);
                addAndMakeVisible(buttons[i]);
            }
        }

    private:
        std::vector<juce::TextButton*> buttons;
};

// Custom listener logic

/**
 * SelectedComponentListener:
 * 
 * Classes that inherit this are able to listen for changes in the currently selected component.
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
 * EditorComponentListener:
 * 
 * Classes that inherit this are able to listen for changes in any editor component.
 */
class EditorComponentListener {
    public:
        EditorComponentListener();
        virtual ~EditorComponentListener() = default;

        virtual void onEditorComponentChange() = 0; 
        static void update();
};

extern std::vector<EditorComponentListener*> editorComponentListeners;

/**
 * ZOrderListener:
 * 
 * Classes that inherit this are able to listen for zOrder changes in a component.
 */
class ZOrderListener {
    public:
        ZOrderListener();
        virtual ~ZOrderListener() = default;

        virtual void onZOrderChange(BasicEditorComponent* changed) = 0;
        static void update(BasicEditorComponent* changed);
};

extern std::vector<ZOrderListener*> zOrderListeners;