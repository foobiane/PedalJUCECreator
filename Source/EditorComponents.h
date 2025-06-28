#pragma once

#include <JuceHeader.h>

// Forward declaration
class EditorPanel;

/**
 * BasicEditorComponent:
 * 
 * This class encapsulates the shared behaviors of all components added to the editor.
 */

class BasicEditorComponent : public juce::Component {
    public:
        BasicEditorComponent(EditorPanel* mainComponent, int width, int height, juce::Colour hslaColour);

        virtual void paint(juce::Graphics& g) override;
        virtual void resized() override;

        virtual void mouseDown(const juce::MouseEvent& e) final;
        virtual void mouseDrag(const juce::MouseEvent& e) final;
        virtual void mouseUp(const juce::MouseEvent& e) final;

        void setWidth(int newWidth);
        void setHeight(int newHeight);
        void setColour(juce::Colour newColour);

    protected:
        void adjustBounds();

        int width;
        int height;
        juce::Colour hslaColour;

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

class RectangleComponent : public BasicEditorComponent {
    public:
        RectangleComponent(EditorPanel* editorPanel, int width, int height, juce::Colour hslaColour);

        virtual void paint(juce::Graphics& g) override;
        virtual void resized() override;

        void setCornerSize(float newCornerSize);

    private:
        float cornerSize;
};